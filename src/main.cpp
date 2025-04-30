#include <Sockets++.hpp>

int main()
{
	SocketsPlusPlus::Socket socket(SocketsPlusPlus::SocketType::Stream, SocketsPlusPlus::ProtocolType::TCP);
	socket.Connect("www.stackoverflow.com", 80);
	const char request[] =
		"GET / HTTP/1.1\r\nHost: " "www.stackoverflow.com"  "\r\nConnection: close\r\n\r\n";

	std::vector<char> requestVec(sizeof(request));
	memcpy_s(requestVec.data(), sizeof(request), request, sizeof(request));
	
	socket.Send(requestVec);
	std::vector<char> readBuffer(20000);


	socket.Recieve(readBuffer,readBuffer.capacity());
	std::string s(readBuffer.begin(), readBuffer.end());
	printf(s.c_str());
	
}
