// threadpoolTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <functional>
#include <thread>
#include <condition_variable>
#include <future>
#include <atomic>
#include <vector>
#include <queue>

// 命名空间
namespace ilovers {
	class TaskExecutor;
}

class ilovers::TaskExecutor {
	using Task = std::function<void()>;
private:
	// 线程池
	std::vector<std::thread> pool;
	// 任务队列
	std::queue<Task> tasks;
	// 同步
	std::mutex m_task;
	std::condition_variable cv_task;
	// 是否关闭提交
	std::atomic<bool> stop;

public:
	// 构造
	TaskExecutor(size_t size = 4) : stop{ false } {
		size = size < 1 ? 1 : size;
		for (size_t i = 0; i< size; ++i) {
			pool.emplace_back(&TaskExecutor::schedual, this);    // push_back(std::thread{...})
		}
	}

	// 析构
	~TaskExecutor() {
		for (std::thread& thread : pool) {
			thread.detach();    // 让线程“自生自灭”
								//thread.join();        // 等待任务结束， 前提：线程一定会执行完
		}
	}

	// 停止任务提交
	void shutdown() {
		this->stop.store(true);
	}

	// 重启任务提交
	void restart() {
		this->stop.store(false);
	}

	// 提交一个任务
	template<class F, class... Args>
	auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))> {
		if (stop.load()) {    // stop == true ??
			throw std::runtime_error("task executor have closed commit.");
		}

		using ResType = decltype(f(args...));    // typename std::result_of<F(Args...)>::type, 函数 f 的返回值类型
		auto task = std::make_shared<std::packaged_task<ResType()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);    // wtf !
		{    // 添加任务到队列
			std::lock_guard<std::mutex> lock{ m_task };
			tasks.emplace([task]() {   // push(Task{...})
				(*task)();
			});
		}
		cv_task.notify_all();    // 唤醒线程执行

		std::future<ResType> future = task->get_future();
		return future;
	}

private:
	// 获取一个待执行的 task
	Task get_one_task() {
		std::unique_lock<std::mutex> lock{ m_task };
		cv_task.wait(lock, [this]() { return !tasks.empty(); });    // wait 直到有 task
		Task task{ std::move(tasks.front()) };    // 取一个 task
		tasks.pop();
		return task;
	}

	// 任务调度
	void schedual() {
		while (true) {
			if (Task task = get_one_task()) {
				task();    //
			}
			else {
				// return;    // done
			}
		}
	}
};


void f()
{
	std::cout << "hello, f !" << std::endl;
}

struct G {
	int operator()() {
		std::cout << "hello, g !" << std::endl;
		return 42;
	}
};

void j(int num)
{
	std::cout << "hello, j !" << " " << num << std::endl;
}
int main()
try {
	ilovers::TaskExecutor executor{ 10 };

	std::future<void> ff = executor.commit(f);
	std::future<int> fg = executor.commit(G{});
	std::future<std::string> fh = executor.commit([]()->std::string { std::cout << "hello, h !" << std::endl; return "hello,fh !"; });

	std::future<void> fj = executor.commit(j, 233);

	executor.shutdown();

	ff.get();
	std::cout << fg.get() << " " << fh.get().c_str() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	executor.restart();    // 重启任务
	executor.commit(f).get();    //

	std::cout << "end..." << std::endl;

	system("pause");
	return 0;
}
catch (std::exception& e) {
	std::cout << "some unhappy happened... " << e.what() << std::endl;
}
/**
## 实现原理
接着前面的废话说。“管理一个任务队列，一个线程队列，然后每次取一个任务分配给一个线程去做，循环往复。” 这个思路有神马问题？线程池一般要复用线程，所以如果是取一个 task 分配给某一个 thread，执行完之后再重新分配，在语言层面基本都是不支持的：一般语言的 thread 都是执行一个固定的 task 函数，执行完毕线程也就结束了(至少 c++ 是这样)。so 要如何实现 task 和 thread 的分配呢？

让每一个 thread 都去执行调度函数：循环获取一个 task，然后执行之。

idea 是不是很赞！保证了 thread 函数的唯一性，而且复用线程执行 task 。

即使理解了 idea，me 想代码还是需要详细解释一下的。

一个线程 pool，一个任务队列 queue ，应该没有意见；
任务队列是典型的生产者-消费者模型，本模型至少需要两个工具：一个 mutex + 一个条件变量，或是一个 mutex + 一个信号量。mutex 实际上就是锁，保证任务的添加和移除(获取)的互斥性，一个条件变量是保证获取 task 的同步性：一个 empty 的队列，线程应该等待(阻塞)；
stop 控制任务提交，是受了 Java 的影响，还有实现类不叫 ThreadPool 而是叫 TaskExecutor；
atomic<bool> 本身是原子类型，从名字上就懂：它们的操作 load()/store() 是原子操作，所以不需要再加 mutex。


## c++语言细节
即使懂原理也不代表能写出程序，上面用了众多c++11的“奇技淫巧”，下面简单描述之。

using Task = function<void()> 是类型别名，简化了 typedef 的用法。function<void()> 可以认为是一个函数类型，接受任意原型是 void() 的函数，或是函数对象，或是匿名函数。void() 意思是不带参数，没有返回值。最初的实现版本 Task 类型不是单纯的函数类型，而是一个 class，包含一个 status 字段，表明 Task 的状态：未调度、执行中、执行结束。后来因为简化，故删掉了。
pool.emplace_back(&TaskExecutor::schedual, this); 和 pool.push_back(thread{&TaskExecutor::schedual, this}) 功能一样，只不过前者性能会更好；
thread{&TaskExecutor::schedual, this} 是构造了一个线程对象，执行函数是成员函数 TaskExecutor::schedual ；
所有对象的初始化方式均采用了 {}，而不再使用之前的 () 方式，因为风格不够一致且容易出错；
匿名函数： [](int a, int b)->int { return a+b; } 不多说。[] 是捕捉器，&r 是引用域外的变量 r， =r 是拷贝域外的 r 值；
delctype(expr) 用来推断 expr 的类型，和 auto 是类似的，相当于类型占位符，占据一个类型的位置；auto f(A a, B b) -> decltype(a+b) 是一种用法，不能写作 decltype(a+b) f(A a, B b)，为啥？！ c++ 就是这么规定的！
commit 方法是不是略奇葩！可以带任意多的参数，第一个参数是 f，后面依次是函数 f 的参数！ 可变参数模板是 c++11 的一大亮点，够亮！至于为什么是 Arg... 和 arg... ，因为规定就是这么用的！
make_shared 用来构造 shared_ptr 智能指针。用法大体是 shared_ptr<int> p = make_shared<int>(4) 然后 *p == 4 。智能指针的好处就是， 自动 delete ！
bind 函数，接受函数 f 和部分参数，返回currying后的匿名函数，譬如 bind(add, 4) 可以实现类似 add4 的函数！
forward() 函数，类似于 move() 函数，后者是将参数右值化，前者是... 肿么说呢？大概意思就是：不改变最初传入的类型的引用类型(左值还是左值，右值还是右值)；
packaged_task 就是任务函数的封装类，通过 get_future 获取 future ， 然后通过 future 可以获取函数的返回值(future.get())；packaged_task 本身可以像函数一样调用 () ；
queue 是队列类， front() 获取头部元素， pop() 移除头部元素；back() 获取尾部元素，push() 尾部添加元素；
lock_guard 是 mutex 的 stack 封装类，构造的时候 lock()，析构的时候 unlock()，是 c++ RAII 的 idea；
condition_variable cv; 条件变量， 需要配合 unique_lock 使用；unique_lock 相比 lock_guard 的好处是：可以随时 unlock() 和 lock()。 cv.wait() 之前需要持有 mutex，wait 本身会 unlock() mutex，如果条件满足则会重新持有 mutex。
*/
