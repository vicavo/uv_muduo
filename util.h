#include "base.h"

uv_loop_t *loop;

void alloc_buffer(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) {
	void * buff = malloc(suggested_size);
	memset(buff, 0, suggested_size);
	uv_buf_t * inited_buff= new uv_buf_t();
	*inited_buff = uv_buf_init((char*) buff, (unsigned int)suggested_size);
	buf = inited_buff;
}

void echo_write(uv_write_t *req, int status) {
	if (status == -1) {
		//fprintf(stderr, "Write error %s\n", uv_err_name(uv_last_error(loop)));
	}
	char *base = (char*) req->data;
	free(base);
	free(req);
}

void echo_read(uv_stream_t *client, ssize_t nread, const uv_buf_t* buf) {
	if (nread == -1) {
// 		if (uv_last_error(loop).code != UV_EOF)
// 			fprintf(stderr, "Read error %s\n", uv_err_name(uv_last_error(loop)));
		uv_close((uv_handle_t*) client, NULL);
		return;
	}
	
	/*
	 * add by wanchunye
	 */
	uv_tcp_t * tcp_client = (uv_tcp_t *)client;
	struct sockaddr peername;
	int namelen = sizeof peername;
	int r = uv_tcp_getpeername(tcp_client, &peername, &namelen);
	char check_ip[17]={0};
	int r2 = uv_ip4_name((sockaddr_in *)&peername, (char*) check_ip, sizeof check_ip);
	cout << "msg from  " << check_ip << " : " << buf->base << endl;

	uv_write_t *req = (uv_write_t *) malloc(sizeof(uv_write_t));
	req->data = (void*) buf->base;
	uv_write(req, client, buf, 1, echo_write);
}

void on_new_connection(uv_stream_t *server, int status) {
	if (status == -1) {
		// error!
		return;
	}

	uv_tcp_t *client = (uv_tcp_t*) malloc(sizeof(uv_tcp_t));
	uv_tcp_init(loop, client);
	if (uv_accept(server, (uv_stream_t*) client) == 0) {
		uv_read_start((uv_stream_t*) client, alloc_buffer, echo_read);
	}
	else {
		uv_close((uv_handle_t*) client, NULL);
	}
}