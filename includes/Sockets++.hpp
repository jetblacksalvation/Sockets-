#ifndef SOCKETSPLUSPLUS
#define SOCKETSPLUSPLUS

#include "SocketType.hpp"
#include <string>
#include <vector>

namespace SocketsPlusPlus
{
	inline static WSADATA wsaData;
	inline static bool _isInitializedWSA;
	inline std::string WSAErrorToString(int);
	inline int _initializeWSA()
	{
		if (not _isInitializedWSA)
		{
			printf("Initializing WSA\n");
			int iResult;

			// Initialize Winsock
			iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) {
				printf("WSAStartup failed: %d\n", iResult);
				return 1;
			}
			_isInitializedWSA = true;
			return 0;
		}
		else 
		{
			return 0;
		}
		

	}
	class Socket
	{
	public:
		Socket(SocketsPlusPlus::SocketType type, SocketsPlusPlus::ProtocolType protoType):
			type(type), protoType(protoType)
		{
			_initializeWSA();

		}

		void Connect(std::string hostName, int port);
		std::uint64_t Send(std::vector<char> bytesInput);
		std::uint64_t Recieve(std::vector<char>& bytesbuffer, std::uint64_t bytesMaxRead = 200000);

		
	private:
		SocketsPlusPlus::SocketType type;
		SocketsPlusPlus::ProtocolType protoType;

		SOCKET ConnectSocket;

	};

    std::string WSAErrorToString(int errorCode) {
        switch (errorCode) {
        case WSAEINTR:           return "Interrupted function call";
        case WSAEBADF:           return "File handle is not valid";
        case WSAEACCES:          return "Permission denied";
        case WSAEFAULT:          return "Bad address";
        case WSAEINVAL:          return "Invalid argument";
        case WSAEMFILE:          return "Too many open sockets";
        case WSAEWOULDBLOCK:     return "Resource temporarily unavailable";
        case WSAEINPROGRESS:     return "Operation now in progress";
        case WSAEALREADY:        return "Operation already in progress";
        case WSAENOTSOCK:        return "Socket operation on nonsocket";
        case WSAEDESTADDRREQ:    return "Destination address required";
        case WSAEMSGSIZE:        return "Message too long";
        case WSAEPROTOTYPE:      return "Protocol wrong type for socket";
        case WSAENOPROTOOPT:     return "Bad protocol option";
        case WSAEPROTONOSUPPORT: return "Protocol not supported";
        case WSAESOCKTNOSUPPORT: return "Socket type not supported";
        case WSAEOPNOTSUPP:      return "Operation not supported";
        case WSAEPFNOSUPPORT:    return "Protocol family not supported";
        case WSAEAFNOSUPPORT:    return "Address family not supported by protocol family";
        case WSAEADDRINUSE:      return "Address already in use";
        case WSAEADDRNOTAVAIL:   return "Cannot assign requested address";
        case WSAENETDOWN:        return "Network is down";
        case WSAENETUNREACH:     return "Network is unreachable";
        case WSAENETRESET:       return "Network dropped connection on reset";
        case WSAECONNABORTED:    return "Software caused connection abort";
        case WSAECONNRESET:      return "Connection reset by peer";
        case WSAENOBUFS:         return "No buffer space available";
        case WSAEISCONN:         return "Socket is already connected";
        case WSAENOTCONN:        return "Socket is not connected";
        case WSAESHUTDOWN:       return "Cannot send after socket shutdown";
        case WSAETOOMANYREFS:    return "Too many references";
        case WSAETIMEDOUT:       return "Connection timed out";
        case WSAECONNREFUSED:    return "Connection refused";
        case WSAELOOP:           return "Cannot translate name";
        case WSAENAMETOOLONG:    return "Name too long";
        case WSAEHOSTDOWN:       return "Host is down";
        case WSAEHOSTUNREACH:    return "No route to host";
        case WSAENOTEMPTY:       return "Directory not empty";
        case WSAEPROCLIM:        return "Too many processes";
        case WSAEUSERS:          return "User quota exceeded";
        case WSAEDQUOT:          return "Disk quota exceeded";
        case WSAESTALE:          return "Stale file handle reference";
        case WSAEREMOTE:         return "Item is remote";
        case WSASYSNOTREADY:     return "Network subsystem is unavailable";
        case WSAVERNOTSUPPORTED: return "Winsock.dll version out of range";
        case WSANOTINITIALISED:  return "Successful WSAStartup not yet performed";
        case WSAEDISCON:         return "Graceful shutdown in progress";
        case WSATYPE_NOT_FOUND:  return "Class type not found";
        case WSAHOST_NOT_FOUND:  return "Host not found";
        case WSATRY_AGAIN:       return "Nonauthoritative host not found";
        case WSANO_RECOVERY:     return "This is a nonrecoverable error";
        case WSANO_DATA:         return "Valid name, no data record of requested type";
        default:                 return "Unknown WSA error code";
        }
    }

}
#endif
