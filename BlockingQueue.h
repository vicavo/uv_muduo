#ifndef		BLOCKINGQUEUE_H
#define		BLOCKINGQUEUE_H

#include <deque>
using namespace std;

#include "Mutex.h"
#include "Condition.h"

template<class T>
class BlockingQueue
{
public:
	BlockingQueue() : mutex_lock_(), notEmpty_(mutex_lock_), msg_quene_()
	{
	}

	void put(T & msg)
	{
		MutexLockGuard guard(mutex_lock_);
		msg_quene_.push_back(msg);
		notEmpty_.notify();
	}

	T take()
	{
		MutexLockGuard guard(mutex_lock_);
		
		while(msg_quene_.empty())
		{
			notEmpty_.wait();
		}

		T front(msg_quene_.front());
		msg_quene_.pop_front();

		return front;
	}

private:
	deque<T>		msg_quene_;
	MutexLock		mutex_lock_;
	Condition		notEmpty_;
};

#endif