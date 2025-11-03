#include <Sockets++.hpp>
#include <string>
#include <istream>
#include <fstream>
#include <format>
#include <sstream>
#include <iostream>
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
	std::cout << "Hello Web! http://127.0.0.1:80 is the local host url! \n";

	// Create Socket and create response for clients that connect
	SocketsPlusPlus::Socket socket(SocketsPlusPlus::SocketType::Stream, SocketsPlusPlus::ProtocolType::TCP);

	std::ifstream htmlFileContent(std::string(WWWROOT) + "/bruh.html");
	std::string fileContent(
		(std::istreambuf_iterator<char>(htmlFileContent)),
		std::istreambuf_iterator<char>()
	);
	
	std::string httpResponse = std::format("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nContent-Length:{}\r\n\r\n{}",
		fileContent.size(),fileContent);
	
	std::vector<char> response(httpResponse.begin(), httpResponse.end()) ;
	// Bind to local host on port 80, the default port for http websites
	socket.Bind("127.0.0.1", 80);
	// Listen sets a flag on the socket that allows for clients to connect,
	// and takes in an integer which sets the maximum allowed clients, 25 clients can connect at one time.
	socket.Listen(25);
	while (true)
	{
		//Accept takes a single connection at a time
		SocketsPlusPlus::Socket clientSock = socket.Accept(NULL, NULL);
		std::vector<char>request(10000);

		//Recieve takes in whatever is sent from the client to the server
		clientSock.Recieve(request, request.capacity());
		/*
			TODO : Parse user paramters and handle routing
			GET /Bruh <HTML VER>
			if bruh is inside of a map, you should send the associated data.
			<img></img> tags work in the same way, they request an image from you

		*/
		//Send sends over the response we created earlier.
		clientSock.Send(response);



		//Closes the client socket, causing the web page to load.
		//without this the client doesn't know when we stop sending data
		clientSock.Close();

		std::string s(response.begin(), response.end());
		printf(s.c_str());
	}


}