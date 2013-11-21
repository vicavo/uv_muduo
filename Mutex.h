#ifndef		GUARD_H
#define		GUARD_H

#include "base.h"


class MutexLock
{
public:
	MutexLock()
	{
		uv_mutex_init(&mutex_);
	}

	~MutexLock()
	{
		uv_mutex_destroy(&mutex_);
	}

	void lock()
	{
		uv_mutex_lock(&mutex_);
	}

	uv_mutex_t * getUVthreadMutex()
	{
		return &mutex_;
	}

	void unlock()
	{
		uv_mutex_unlock(&mutex_);
	}
private:
	uv_mutex_t	mutex_;
};

class MutexLockGuard
{
public:
	MutexLockGuard(MutexLock & mutexlock) : mutex_lock_(mutexlock)
	{
		mutex_lock_.lock();
	}
	~MutexLockGuard()
	{
		mutex_lock_.unlock();
	}

private:
	MutexLock & mutex_lock_;
};



#endif