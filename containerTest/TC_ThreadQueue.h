#pragma once
template<typename T, typename D = deque<T> >
class TC_ThreadQueue : protected TC_ThreadLock
{
public:


	typedef D queue_type;


	/**
	* ��ͷ����ȡ����, û��������ȴ�
	*
	* @param t
	* @param millsecond : �����ȴ�ʱ��(ms)
	* @return bool: true, ��ȡ������, false, ������
	*/
	bool pop_front(T& t, size_t millsecond = 0)
	{
		Lock lock(*this);   //����ͬ����


		if (_queue.empty())
		{
			if (millsecond == 0)
			{
				return false;
			}
			timedWait(millsecond);    //�ȴ�ʱ��
		}


		if (_queue.empty())    //�����ʱ������Ȼ�ǿյģ��򷵻�false
		{
			return false;
		}


		t = _queue.front();
		_queue.pop_front();   //��������ɾ��


		return true;
	}


	/**
	* ֪ͨ�ȴ��ڶ���������̶߳��ѹ���
	*/
	void notifyT()
	{
		Lock lock(*this);
		notifyAll();
	}


	/**
	* �����ݵ�����
	* @param t
	*/
	void push_back(const T& t)
	{
		Lock lock(*this);


		//������ն����ǿյ�, ���ڸõ��ú�, ��������, ���֪ͨ�����߳�
		if (_queue.empty())
		{
			notifyAll();       //�����ͺ�֪ͨ�����壬��push_back�ķ���ĩβ��ʽ���wait������
		}


		_queue.push_back(t);
		//�������wait��������
	}


	/**
	* �ȵ������ݲŽ���
	* @param q
	* @millsecond : �����ȴ�ʱ��(ms), 0:��ʾ������
	* @return true:������, false:������
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
	* ���д�С
	*
	* @return size_t
	*/
	size_t size() const
	{
		Lock lock(*this);
		return _queue.size();
	}


	/**
	* ��ն���
	*/
	void clear()
	{
		Lock lock(*this);
		_queue.clear();
	}


	/**
	* �Ƿ�����Ϊ��
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
	* ����
	*/
	queue_type         _queue;


};