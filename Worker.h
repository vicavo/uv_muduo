#ifndef		WORKER_H
#define		WORKER_H

#include <iostream>
#include "base.h"
#include "BlockingQueue.h"

#define BUFF_SIZE 128

class WorkThread
{
public:
	WorkThread() : msg_pipe_()
	{

	}
	
	void ProducerWorkThread()
	{
		while(1)
		{
			char * buff = new char[BUFF_SIZE];
 			memset(buff, 0, BUFF_SIZE);
 			memcpy(buff, "hello~~", 8);

			msg_pipe_.put(buff);
			cout << "Producer (" << uv_thread_self() << ")" << "push msg" << endl;
			//Sleep(1000);
		}
	}

	void ConsumerWokrThead()
	{
		while(1)
		{
			char * msg = msg_pipe_.take();
			cout << "Consumer (" << uv_thread_self() << ")" << "take msg : " << msg << endl;
			delete msg;
			//Sleep(1000);
		}
	}

private:

	BlockingQueue<char *> msg_pipe_;
};

#endif