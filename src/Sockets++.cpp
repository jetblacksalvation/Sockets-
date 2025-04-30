#include "Sockets++.hpp"

namespace SocketsPlusPlus
{
	
	void Socket::Connect(std::string hostName, int port)
	{


		struct hostent* host;

		// Create a SOCKET for connecting to server
		ConnectSocket = socket(AF_INET, this->type,
			this->protoType);
		SOCKADDR_IN SockAddr;
		host = gethostbyname(hostName.c_str());
		if (ConnectSocket == INVALID_SOCKET) {
			printf("Error at Connect(): %ld\n", WSAErrorToString(WSAGetLastError()).c_str());

			//WSACleanup();
			return;
		}
		SockAddr.sin_port = htons(80);
		SockAddr.sin_family = AF_INET;
		SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);


		int connectResult = connect(ConnectSocket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr));
		if (connectResult != 0)
		{
			printf("socket Connect rreturned a non zero value!\n");
		}
		printf("Finished Creating The Socket!\n");
	}
	std::uint64_t Socket::Send(std::vector<char>bytesInput)
	{
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Socket Hasn't Connected To Anything Yet\n");
		}
		int result = send(ConnectSocket, bytesInput.data(), bytesInput.size(), 0);
		if (SOCKET_ERROR == result)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
		}
		return result;
	}
	std::uint64_t Socket::Recieve(std::vector<char>& bytesbuffer, std::uint64_t bytesMaxRead)
	{
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("Socket Hasn't Connected TO Anything Yet\n");

		}
		int result =  recv(ConnectSocket, bytesbuffer.data(), bytesMaxRead, 0);
		if (SOCKET_ERROR == result)
		{
			printf("Erorr raised! : %s\n", WSAErrorToString(WSAGetLastError()).c_str());
		}
		return result;
	}

}