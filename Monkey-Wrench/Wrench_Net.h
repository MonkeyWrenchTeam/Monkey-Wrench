#ifndef WRENCH_NET
#define WRENCH_NET

#include "Wrench.h"
#include "Wrench_Thread.h"
#include <map>
#include <queue>
#include <string>

#ifdef WRENCH_WINDOWS
#include <Windows.h>
#pragma comment(lib, "ws2_32.lib")

#endif

#ifdef WRENCH_POSIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
typedef int SOCKET;
#endif

typedef WRENCHLIB_API std::map<std::string, SOCKET*> _WCM; //Wrench Connection map

namespace Wrench
{

#define WRENCHNET_BUFFER 2048
#define WRENCHNET_FAILURE "204.204.204.204"

	struct WRENCHLIB_API WConnectionInformation
	{
		sockaddr_in sockAddr;
		bool AutoRetry;
		std::queue<char*> Messages; //LIFO Inbound messages, NOT outbound.
		SOCKET Local;
		_WCM Connections;
		int AFType;
		int SocketType;
		int Protocol;
		bool _ket; //Boolean that is passed to the established function when Disconnect is called. Stands for KillEstablishedThread.
	};



	//Initialization
WRENCHLIB_API int InitializeWrenchNet(WConnectionInformation* con, int AFType, int SOCKET_TYPE, int protocol = 0);

	//Hosting
WRENCHLIB_API int StartServer(int port, WConnectionInformation* con);
WRENCHLIB_API int Listen(WConnectionInformation* con);

	//Connection
WRENCHLIB_API int Connect(int port, char* IP, WConnectionInformation* con);
WRENCHLIB_API WVOID Disconnect(WConnectionInformation* con, WThread EstablishedThread);
WRENCHLIB_API int Established(WConnectionInformation* con);
WRENCHLIB_API char* ResolveHost(char* host);
WRENCHLIB_API SOCKET* GetSocket(char* IP, WConnectionInformation* con);

	//Communication
WRENCHLIB_API WVOID Send(char* data, WConnectionInformation* con);
WRENCHLIB_API WVOID Send(char* data, SOCKET s);


}

#endif
