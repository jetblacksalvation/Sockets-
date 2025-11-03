#include "Sockets++.hpp"

namespace SocketsPlusPlus
{
	
	void Socket::Bind(std::string hostName, int port)
	{
		struct hostent* host;

		// Create a SOCKET for connecting to server
		this->ConnectSocket = socket(AF_INET, this->type,
			this->protoType);

		host = gethostbyname(hostName.c_str());
		if (this->ConnectSocket == INVALID_SOCKET) {
			printf("Error at Connect(): %s\n", WSAErrorToString(WSAGetLastError()).c_str());

			//WSACleanup();
			return;
		}
		SOCKADDR_IN SockAddr;
		SockAddr.sin_port = htons(port);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

		if (bind(this->ConnectSocket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr))== SOCKET_ERROR)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
		}
	
	}
	void Socket::Connect(std::string hostName, int port)
	{


		struct hostent* host;

		// Create a SOCKET for connecting to server
		this->ConnectSocket = socket(AF_INET, this->type,
			this->protoType);
		SOCKADDR_IN SockAddr;
		host = gethostbyname(hostName.c_str());
		if (this->ConnectSocket == INVALID_SOCKET) {
			printf("Error at Connect(): %s\n", WSAErrorToString(WSAGetLastError()).c_str());

			//WSACleanup();
			return;
		}
		SockAddr.sin_port = htons(port);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);


		int connectResult = connect(this->ConnectSocket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
		if (connectResult != 0)
		{
			printf("socket Connect rreturned a non zero value!\n");
		}
		if (connectResult == INVALID_SOCKET)
		{
			printf("The socket was invalid!\n");
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());

		}
		printf("Finished Creating The Socket!\n");
	}
	std::uint64_t Socket::Send(std::vector<char>bytesInput)
	{
		if (this->ConnectSocket == INVALID_SOCKET)
		{
			printf("Socket Hasn't Connected To Anything Yet\n");
		}
		int result = send(this->ConnectSocket, bytesInput.data(), bytesInput.size(), 0);
		if (SOCKET_ERROR == result)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
		}
		return result;
	}
	std::uint64_t Socket::Recieve(std::vector<char>& bytesbuffer)
	{
		if (this->ConnectSocket == INVALID_SOCKET)
		{
			printf("Socket Hasn't Connected TO Anything Yet\n");

		}
		int result = recv(this->ConnectSocket, bytesbuffer.data(), bytesbuffer.size(), 0);
		if (SOCKET_ERROR == result)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
		}
		return result;
	}
	std::uint64_t Socket::Recieve(std::vector<char>& bytesbuffer, std::uint64_t bytesMaxRead)
	{
		if (this->ConnectSocket == INVALID_SOCKET)
		{
			printf("Socket Hasn't Connected TO Anything Yet\n");

		}
		int result =  recv(this->ConnectSocket, bytesbuffer.data(), bytesMaxRead, 0);
		if (SOCKET_ERROR == result)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
		}
		return result;
	}
	void Socket::Listen(int backLog )
	{
		if (listen(this->ConnectSocket, backLog) == SOCKET_ERROR)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
			return;
		}
	}
	Socket Socket::Accept(sockaddr* addr,
		int* addrlen)
	{
		SOCKET accSock = accept(this->ConnectSocket, NULL,NULL);
		if (accSock == INVALID_SOCKET)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
		}
		//this->ConnectSocket = accSock;
		Socket s(type,protoType);
		s.ConnectSocket = accSock;
		return s;

	}
	void Socket::Close()
	{
		closesocket(this->ConnectSocket);
	}

}