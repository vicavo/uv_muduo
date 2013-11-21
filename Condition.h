#ifndef		CONDITION_H
#define		CONDITION_H

#include "base.h"
#include "Mutex.h"

class Condition
{
public:
	Condition(MutexLock & mutexloack) : mutex_lock_(mutexloack)
	{
		uv_cond_init(&cond_);
	}

	~Condition()
	{
		uv_cond_destroy(&cond_);
	}

	void wait()
	{
		uv_cond_wait(&cond_, mutex_lock_.getUVthreadMutex());
	}

	void notify()
	{
		uv_cond_signal(&cond_);
	}

private:
	uv_cond_t		cond_;
	MutexLock	&	mutex_lock_;
};

#endif