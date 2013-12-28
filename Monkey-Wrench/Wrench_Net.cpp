#include "Wrench_Net.h"

	SOCKET* _CTSP( SOCKET _t )
	{
		SOCKET* _ta = new SOCKET[sizeof(_t) + 1];
		memcpy(_ta, &_t, sizeof(_t));
		return _ta;
	}

namespace Wrench
{

	int InitializeWrenchNet(WConnectionInformation* con, int AFType, int SOCKET_TYPE, int protocol)
	{
		WORD socketVersion;
		WSADATA wsaData;
		bool wsaStart = (WSAStartup(MAKEWORD(2 ,2), &wsaData) == 0);
		bool  mVer = (LOBYTE(wsaData.wVersion) >= 2);
		if(wsaStart && mVer)
		{
			con->Local = socket(AFType, SOCKET_TYPE, protocol);
			bool sockInit = (con->Local != INVALID_SOCKET);
			if(sockInit == true)
				return 0;

		}
		else
			return 1;
	}

	int StartServer( int port, WConnectionInformation* con )
	{
		//Setup the server information
		sockaddr_in sAddr;
		sAddr.sin_family = AF_INET;
		sAddr.sin_port = htons(port);
		sAddr.sin_addr.S_un.S_addr = INADDR_ANY;

		//Create the socket
		int hSockInit = bind(con->Local, (SOCKADDR*)&sAddr, sizeof(sAddr));

		switch(hSockInit)
		{
		case SOCKET_ERROR:
			return WSAGetLastError();
			break;

		default:
			return 0;
		}
	}

	int Listen( WConnectionInformation* con)
	{
		
			sockaddr_in addrbuf;

			while(listen(con->Local, 1) == SOCKET_ERROR);
			int len = sizeof(addrbuf);
			SOCKET RemoteBuffer = accept(con->Local, (sockaddr*)&addrbuf, &len);

			std::string IP = inet_ntoa(addrbuf.sin_addr);
			if(strcmp(IP.c_str(), WRENCHNET_FAILURE) == 0)
				Listen(con);

			if(con->Connections.find(IP) == con->Connections.end())
				con->Connections[IP] = _CTSP(RemoteBuffer);

			char buffer[WRENCHNET_BUFFER];
			int bytes = recv(*con->Connections[inet_ntoa(addrbuf.sin_addr)], buffer, WRENCHNET_BUFFER, 0);

			if(bytes == 0)
			{
				std::string* msg = new std::string();
				msg->append(IP);
				msg->append(" has disconnected.");
				con->Messages.push((char*)msg->c_str());
				con->Connections.erase(IP);
				Listen(con);
			}

			if(bytes == SOCKET_ERROR && bytes != WSAEWOULDBLOCK)
				Listen(con);

			if(bytes > 0)
			{
				std::string strRecv = buffer;
				std::string output = strRecv.substr(0, bytes);
				std::string* msg = new std::string();
				msg->append(IP);
				msg->append(":");
				msg->append(output.c_str());
				con->Messages.push((char*)msg->c_str());
			}

			Listen(con);
	
		return 0;
	}

	int Connect(int port, char* IP, WConnectionInformation* con)
	{
		con->sockAddr.sin_family = AF_INET; 
		con->sockAddr.sin_port = htons(port); 
		con->sockAddr.sin_addr.S_un.S_addr = inet_addr(IP);

		int ret = connect(con->Local, (sockaddr*)(&con->sockAddr), sizeof(con->sockAddr));

		switch(ret)
		{
		case SOCKET_ERROR:
			if(WSAGetLastError() == 10061)
				return 1;
			else
				return WSAGetLastError();
			break;
		default:
			return 0;
			break;
		}

		return 0; //This should NEVER get called. It is only to settle the compiler.
	}

	WVOID Disconnect( WConnectionInformation* con )
	{
		closesocket(con->Local);
		con->Local = socket(AF_INET, SOCK_STREAM, 0);
	}

	int Established(WConnectionInformation* con)
	{
		while(true)
		{
			char buffer[WRENCHNET_BUFFER];
			char* cleanbuf;
			int bytes = recv(con->Local,buffer, WRENCHNET_BUFFER, 0);

			if(bytes == 0)
				return -1;

			else if(bytes == SOCKET_ERROR)
			{
				if(WSAGetLastError() == 10054 && con->AutoRetry)
					return 1;
				else
					return WSAGetLastError();
			}
			else if(bytes > 0)
			{
				std::string strRecv = buffer;
				std::string output = strRecv.substr(0, bytes);
				std::string* msg = new std::string();
				std::string IP = inet_ntoa(con->sockAddr.sin_addr);
				msg->append(IP);
				msg->append(":");
				msg->append(output.c_str());
				con->Messages.push((char*)msg->c_str());
			}
		}
	}

	WVOID Send( char* data, WConnectionInformation* con )
	{
		Send(data, con->Local);
	}

	WVOID Send( char* data, SOCKET s )
	{
		send(s, data, strlen(data), 0);
	}



}