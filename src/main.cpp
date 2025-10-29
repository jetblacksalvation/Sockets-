#include <Sockets++.hpp>

//int main()
//{
//	SocketsPlusPlus::Socket socket(SocketsPlusPlus::SocketType::Stream, SocketsPlusPlus::ProtocolType::TCP);
//	socket.Connect("www.stackoverflow.com", 80);
//	const char request[] =
//		"GET / HTTP/1.1\r\nHost: " "www.stackoverflow.com"  "\r\nConnection: close\r\n\r\n";
//
//	std::vector<char> requestVec(sizeof(request));
//	memcpy_s(requestVec.data(), sizeof(request), request, sizeof(request));
//	
//	socket.Send(requestVec);
//	std::vector<char> readBuffer(20000);
//
//
//	socket.Recieve(readBuffer,readBuffer.capacity());
//	std::string s(readBuffer.begin(), readBuffer.end());
//	printf(s.c_str());
//	
//}

int main()
{
	SocketsPlusPlus::Socket socket(SocketsPlusPlus::SocketType::Stream, SocketsPlusPlus::ProtocolType::TCP);
	socket.Bind("127.0.0.1", 80);
	std::printf("http://127.0.0.1:80");

	socket.Listen();
	std::string bruh = ("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length: 12\r\n\r\nHello World");
	std::vector<char> requestVec(bruh.begin(),bruh.end()) ;

	SocketsPlusPlus::Socket clientSock = socket.Accept(NULL, NULL);
	std::vector<char>response(10000);
	clientSock.Recieve(response,response.capacity());

	clientSock.Send(requestVec);


	

	clientSock.Close();

	std::string s(response.begin(), response.end());
	printf(s.c_str());
}