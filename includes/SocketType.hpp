#ifndef SOCKETTYPES
#define SOCKETTYPES
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
namespace SocketsPlusPlus
{
	enum SocketType : int
	{
		Stream = SOCK_STREAM

	};
	/*   Maybe SocketType should map to AddrFamily...     */
	enum AddressFamily : int
	{
		LOOPBACK = AF_UNSPEC,
		IPV4 = AF_INET,
		IPV6 = AF_INET6
	};
	enum ProtocolType : int
	{
		TCP = IPPROTO_TCP,
		UDP = IPPROTO_UDP
	};
}

#endif	