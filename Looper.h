#ifndef LOOPER_H
#define LOOPER_H

#include "base.h"
#include <vector>
#include <iostream>
using namespace std;

class Looper{

public:
	Looper()
	{
		loop_ = uv_loop_new();
	}
	~Looper()
	{
		cout << "some connected to me !!!" << endl;
	}

	void Add(uv_tcp_s * tcp)
	{
		uv_tcp_init(loop_, tcp);
	}

	int Run()
	{
		return uv_run(loop_, UV_RUN_DEFAULT);
	}

	uv_loop_t * get(){ return loop_;}

private:
	uv_loop_t				*loop_ ;
	
};



class LoopPool{

private:
	struct  LooperInfo
	{
		uv_thread_t * tid;
		Looper		* looper;
	};

public:
	LoopPool()
	{

	}
	~LoopPool()
	{

	}

	Looper * getLooper(int idx)
	{
		if (looper_info_.size() >= idx) {
			return looper_info_[idx]->looper;
		}

		return NULL;
	}

	void Create(int num)
	{
		for (int i = 0 ; i < num; i++)
		{
			uv_thread_t *thread = new uv_thread_t();
			Looper *looper = new Looper();

			LooperInfo *looer_info = new LooperInfo();
			looer_info->tid = thread;
			looer_info->looper = looper;

			looper_info_.push_back(looer_info);
			
		}
	}

	void Run()
	{
		vector<LooperInfo *>::iterator it = looper_info_.begin();
		for (;it != looper_info_.end();it ++)
		{
			uv_thread_create((*it)->tid, LoopThread, (void *)((*it)->looper));
		}
	}


private:
	static void LoopThread(void *arg)
	{
		Looper *looper = (Looper *) arg;
		looper->Run();
	}

private:
	vector<LooperInfo *>	looper_info_ ;
};

#endif