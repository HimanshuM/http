/* Command to compile the code:
	g++ main.cpp src/* -Iinclude -o bin/Debug/http -pthread -std=c++17
*/
#include "server.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{

	}

	char *portno = argv[1];
	Server s = Server(portno);
	s.initialize();

	return 0;
}