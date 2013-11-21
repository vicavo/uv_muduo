#include <iostream>
using namespace std;

#include "base.h"

#include "Server.h"


int main()
{
	Server *server = Server::CreateServer("0.0.0.0", 9999);
	server->Run();
}