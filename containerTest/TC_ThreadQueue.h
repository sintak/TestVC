#pragma once
template<typename T, typename D = deque<T> >
class TC_ThreadQueue : protected TC_ThreadLock
{
public:


	typedef D queue_type;


	/**
	* 从头部获取数据, 没有数据则等待
	*
	* @param t
	* @param millsecond : 阻塞等待时间(ms)
	* @return bool: true, 获取了数据, false, 无数据
	*/
	bool pop_front(T& t, size_t millsecond = 0)
	{
		Lock lock(*this);   //方法同步块


		if (_queue.empty())
		{
			if (millsecond == 0)
			{
				return false;
			}
			timedWait(millsecond);    //等待时间
		}


		if (_queue.empty())    //如果到时间了仍然是空的，则返回false
		{
			return false;
		}


		t = _queue.front();
		_queue.pop_front();   //弹出并且删除


		return true;
	}


	/**
	* 通知等待在队列上面的线程都醒过来
	*/
	void notifyT()
	{
		Lock lock(*this);
		notifyAll();
	}


	/**
	* 放数据到队列
	* @param t
	*/
	void push_back(const T& t)
	{
		Lock lock(*this);


		//如果接收队列是空的, 由于该调用后, 将有数据, 因此通知其他线程
		if (_queue.empty())
		{
			notifyAll();       //根据滞后通知的语义，在push_back的方法末尾正式解除wait的阻塞
		}


		_queue.push_back(t);
		//解除所有wait阻塞操作
	}


	/**
	* 等到有数据才交换
	* @param q
	* @millsecond : 阻塞等待时间(ms), 0:表示不阻塞
	* @return true:有数据, false:无数据
	*/
	bool swap(queue_type &q, size_t millsecond = 0)
	{
		Lock lock(*this);


		if (_queue.empty())
		{
			if (millsecond == 0)
			{
				return false;
			}
			timedWait(millsecond);
		}


		if (_queue.empty())
		{
			return false;
		}


		q.swap(_queue);


		return true;
	}


	/**
	* 队列大小
	*
	* @return size_t
	*/
	size_t size() const
	{
		Lock lock(*this);
		return _queue.size();
	}


	/**
	* 清空队列
	*/
	void clear()
	{
		Lock lock(*this);
		_queue.clear();
	}


	/**
	* 是否数据为空
	*
	* @return bool
	*/
	bool empty() const
	{
		Lock lock(*this);
		return _queue.empty();
	}


protected:
	/**
	* 队列
	*/
	queue_type         _queue;


};