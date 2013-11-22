#ifndef SESSION_H
#define SESSION_H

#include "base.h"
#include "Looper.h"

typedef void (*LISTEN_CALLBACK)(void);

class Session
{
public:
	Session(Looper *looper)
	{
		looper->Add(&peer_);
	}
	~Session()
	{}

	void Addatch(Looper *looper)
	{
		looper->Add(&peer_);
	}

	void Listen(string ip, int port, uv_connection_cb callback)
	{
		struct sockaddr_in bind_addr ; 
		uv_ip4_addr(ip.c_str(), port, &bind_addr);
		uv_tcp_bind(&peer_, (sockaddr *)&bind_addr);
		int r = uv_listen((uv_stream_t*) &peer_, 128, callback);
	}
	
private:
	uv_tcp_s peer_;
};

#endif