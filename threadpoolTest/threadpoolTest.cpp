// threadpoolTest.cpp : �������̨Ӧ�ó������ڵ㡣
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

// �����ռ�
namespace ilovers {
	class TaskExecutor;
}

class ilovers::TaskExecutor {
	using Task = std::function<void()>;
private:
	// �̳߳�
	std::vector<std::thread> pool;
	// �������
	std::queue<Task> tasks;
	// ͬ��
	std::mutex m_task;
	std::condition_variable cv_task;
	// �Ƿ�ر��ύ
	std::atomic<bool> stop;

public:
	// ����
	TaskExecutor(size_t size = 4) : stop{ false } {
		size = size < 1 ? 1 : size;
		for (size_t i = 0; i< size; ++i) {
			pool.emplace_back(&TaskExecutor::schedual, this);    // push_back(std::thread{...})
		}
	}

	// ����
	~TaskExecutor() {
		for (std::thread& thread : pool) {
			thread.detach();    // ���̡߳���������
								//thread.join();        // �ȴ���������� ǰ�᣺�߳�һ����ִ����
		}
	}

	// ֹͣ�����ύ
	void shutdown() {
		this->stop.store(true);
	}

	// ���������ύ
	void restart() {
		this->stop.store(false);
	}

	// �ύһ������
	template<class F, class... Args>
	auto commit(F&& f, Args&&... args) ->std::future<decltype(f(args...))> {
		if (stop.load()) {    // stop == true ??
			throw std::runtime_error("task executor have closed commit.");
		}

		using ResType = decltype(f(args...));    // typename std::result_of<F(Args...)>::type, ���� f �ķ���ֵ����
		auto task = std::make_shared<std::packaged_task<ResType()>>(
			std::bind(std::forward<F>(f), std::forward<Args>(args)...)
			);    // wtf !
		{    // ������񵽶���
			std::lock_guard<std::mutex> lock{ m_task };
			tasks.emplace([task]() {   // push(Task{...})
				(*task)();
			});
		}
		cv_task.notify_all();    // �����߳�ִ��

		std::future<ResType> future = task->get_future();
		return future;
	}

private:
	// ��ȡһ����ִ�е� task
	Task get_one_task() {
		std::unique_lock<std::mutex> lock{ m_task };
		cv_task.wait(lock, [this]() { return !tasks.empty(); });    // wait ֱ���� task
		Task task{ std::move(tasks.front()) };    // ȡһ�� task
		tasks.pop();
		return task;
	}

	// �������
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
	executor.restart();    // ��������
	executor.commit(f).get();    //

	std::cout << "end..." << std::endl;

	system("pause");
	return 0;
}
catch (std::exception& e) {
	std::cout << "some unhappy happened... " << e.what() << std::endl;
}
/**
## ʵ��ԭ��
����ǰ��ķϻ�˵��������һ��������У�һ���̶߳��У�Ȼ��ÿ��ȡһ����������һ���߳�ȥ����ѭ���������� ���˼·���������⣿�̳߳�һ��Ҫ�����̣߳����������ȡһ�� task �����ĳһ�� thread��ִ����֮�������·��䣬�����Բ���������ǲ�֧�ֵģ�һ�����Ե� thread ����ִ��һ���̶��� task ������ִ������߳�Ҳ�ͽ�����(���� c++ ������)��so Ҫ���ʵ�� task �� thread �ķ����أ�

��ÿһ�� thread ��ȥִ�е��Ⱥ�����ѭ����ȡһ�� task��Ȼ��ִ��֮��

idea �ǲ��Ǻ��ޣ���֤�� thread ������Ψһ�ԣ����Ҹ����߳�ִ�� task ��

��ʹ����� idea��me ����뻹����Ҫ��ϸ����һ�µġ�

һ���߳� pool��һ��������� queue ��Ӧ��û�������
��������ǵ��͵�������-������ģ�ͣ���ģ��������Ҫ�������ߣ�һ�� mutex + һ����������������һ�� mutex + һ���ź�����mutex ʵ���Ͼ���������֤�������Ӻ��Ƴ�(��ȡ)�Ļ����ԣ�һ�����������Ǳ�֤��ȡ task ��ͬ���ԣ�һ�� empty �Ķ��У��߳�Ӧ�õȴ�(����)��
stop ���������ύ�������� Java ��Ӱ�죬����ʵ���಻�� ThreadPool ���ǽ� TaskExecutor��
atomic<bool> ������ԭ�����ͣ��������ϾͶ������ǵĲ��� load()/store() ��ԭ�Ӳ��������Բ���Ҫ�ټ� mutex��


## c++����ϸ��
��ʹ��ԭ��Ҳ��������д���������������ڶ�c++11�ġ��漼���ɡ������������֮��

using Task = function<void()> �����ͱ��������� typedef ���÷���function<void()> ������Ϊ��һ���������ͣ���������ԭ���� void() �ĺ��������Ǻ������󣬻�������������void() ��˼�ǲ���������û�з���ֵ�������ʵ�ְ汾 Task ���Ͳ��ǵ����ĺ������ͣ�����һ�� class������һ�� status �ֶΣ����� Task ��״̬��δ���ȡ�ִ���С�ִ�н�����������Ϊ�򻯣���ɾ���ˡ�
pool.emplace_back(&TaskExecutor::schedual, this); �� pool.push_back(thread{&TaskExecutor::schedual, this}) ����һ����ֻ����ǰ�����ܻ���ã�
thread{&TaskExecutor::schedual, this} �ǹ�����һ���̶߳���ִ�к����ǳ�Ա���� TaskExecutor::schedual ��
���ж���ĳ�ʼ����ʽ�������� {}��������ʹ��֮ǰ�� () ��ʽ����Ϊ��񲻹�һ�������׳���
���������� [](int a, int b)->int { return a+b; } ����˵��[] �ǲ�׽����&r ����������ı��� r�� =r �ǿ�������� r ֵ��
delctype(expr) �����ƶ� expr �����ͣ��� auto �����Ƶģ��൱������ռλ����ռ��һ�����͵�λ�ã�auto f(A a, B b) -> decltype(a+b) ��һ���÷�������д�� decltype(a+b) f(A a, B b)��Ϊɶ���� c++ ������ô�涨�ģ�
commit �����ǲ��������⣡���Դ������Ĳ�������һ�������� f�����������Ǻ��� f �Ĳ����� �ɱ����ģ���� c++11 ��һ�����㣬����������Ϊʲô�� Arg... �� arg... ����Ϊ�涨������ô�õģ�
make_shared �������� shared_ptr ����ָ�롣�÷������� shared_ptr<int> p = make_shared<int>(4) Ȼ�� *p == 4 ������ָ��ĺô����ǣ� �Զ� delete ��
bind ���������ܺ��� f �Ͳ��ֲ���������currying�������������Ʃ�� bind(add, 4) ����ʵ������ add4 �ĺ�����
forward() ������������ move() �����������ǽ�������ֵ����ǰ����... ��ô˵�أ������˼���ǣ����ı������������͵���������(��ֵ������ֵ����ֵ������ֵ)��
packaged_task �����������ķ�װ�࣬ͨ�� get_future ��ȡ future �� Ȼ��ͨ�� future ���Ի�ȡ�����ķ���ֵ(future.get())��packaged_task �����������һ������ () ��
queue �Ƕ����࣬ front() ��ȡͷ��Ԫ�أ� pop() �Ƴ�ͷ��Ԫ�أ�back() ��ȡβ��Ԫ�أ�push() β�����Ԫ�أ�
lock_guard �� mutex �� stack ��װ�࣬�����ʱ�� lock()��������ʱ�� unlock()���� c++ RAII �� idea��
condition_variable cv; ���������� ��Ҫ��� unique_lock ʹ�ã�unique_lock ��� lock_guard �ĺô��ǣ�������ʱ unlock() �� lock()�� cv.wait() ֮ǰ��Ҫ���� mutex��wait ����� unlock() mutex�������������������³��� mutex��
*/
