#include <iostream>
using namespace std;

#include "base.h"

#include "Server.h"
#include "Looper.h"
#include "Session.h"

enum LOOPTYPE
{
	SERVER0_LOOP,
	SERVER1_LOOP,
	SERVER2_LOOP,
	MAX,
};

// called by muti-thread
void my_new_connection(uv_stream_t *stream, int status) {

	uv_tcp_s * tcp = (uv_tcp_s *)stream;
	uv_loop_t *loop = tcp->loop;
	

	cout << "some connected to me !!!" << " looper : " << (int)(loop) << endl;
}

int main()
{
	//Server *server = Server::CreateServer("0.0.0.0", 9999);
	//server->Run();

	LoopPool lp;
	lp.Create(LOOPTYPE::MAX);

	Session *session1 = new Session(lp.getLooper(1));
	//Session *session2 = new Session(lp.getLooper(2));

	session1->Addatch(lp.getLooper(2));

	uv_loop_t * ptr = lp.getLooper(1)->get();
	cout << "loop1" << (int)(ptr) << endl;

	ptr = lp.getLooper(2)->get();
	cout << "loop1" << (int)(ptr) << endl;


	session1->Listen("0.0.0.0", 30001, my_new_connection);
	//session2->Listen("0.0.0.0", 30002, my_new_connection);

	lp.Run();

	while(1)
	{
		Sleep(1000);
	}

	free(session1);

	//getchar();
}