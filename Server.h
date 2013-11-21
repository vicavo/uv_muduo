#ifndef		SERVER_H
#define		SERVER_H

extern "C"
{
#include <uv.h>
}

#include "BlockingQueue.h"
#include "Worker.h"
#include "util.h"

#define  THREAD_NUM 6

WorkThread *work_thread  = new WorkThread();

void test_worker(void *arg)
{
	int * num = (int *)arg;
	if (*num == 0)  // producer
	{
		work_thread->ProducerWorkThread();
	}else{			// consumer
		work_thread->ConsumerWokrThead();
	}

	free(num);
}


class Server
{
public:
	Server()
	{

	}

	~Server()
	{

	}

	static Server * CreateServer(string ip, int port)
	{
		Server * server = new Server();
		server->Listen(ip,port);
		return server;
	}

	int Listen(string ip, int port)
	{
		loop = uv_default_loop();

		uv_tcp_t server;
		uv_tcp_init(loop, &server);

		//create thread
		uv_thread_t thread[THREAD_NUM];
		
		for (int i = 0 ; i < THREAD_NUM ; i++)
		{
			int *num = new int;
			*num = i;
			uv_thread_create(&thread[i], test_worker, (void *)num);
			//free(num);
		}

		struct sockaddr_in bind_addr ; 
		uv_ip4_addr(ip.c_str(), port, &bind_addr);
		uv_tcp_bind(&server, (sockaddr *)&bind_addr);
		int r = uv_listen((uv_stream_t*) &server, 128, on_new_connection);
		if (r) {
			/*fprintf(stderr, "Listen error %s\n", uv_err_name(uv_last_error(loop)));*/
			return 1;
		}

		return 0;
	}

	int Run()
	{
		return uv_run(loop, UV_RUN_DEFAULT);
	}

private:

};

#endif