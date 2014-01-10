#include "Wrench_Net.h"
#ifdef WRENCH_POSIX
#include "Wrench_Manipulation.h"
#endif



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
        con->AFType = AFType;
        con->SocketType = SOCKET_TYPE;
        con->Protocol = protocol;
	#ifdef WRENCH_WINDOWS
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
        #else
            con->Local = socket(AFType, SOCKET_TYPE, protocol);
            if(con->Local < 0)
                return 1;

            return 0;
        #endif
	}

	int StartServer( int port, WConnectionInformation* con )
	{
        std::cout << "Attempting to start server.\n";
		//Setup the server information

		sockaddr_in sAddr;
		sAddr.sin_family = AF_INET;
		sAddr.sin_port = htons(port);



		#ifdef WRENCH_WINDOWS
        sAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		//Create the socket
		int hSockInit = bind(con->Local, (struct sockaddr*)&sAddr, sizeof(sAddr));
		#else
        sAddr.sin_addr.s_addr = INADDR_ANY;
		int hSockInit = bind(con->Local, (struct sockaddr*)&sAddr, sizeof(sAddr));
		#endif

		if(hSockInit >= 0)
		{
            std::cout << "Server created successfully!\n";
		}
		else
		{
            if(con->Local < 0)
                std::cout << "Socket null!\n";


            std::cout << "Error starting server!!!\n";
            std::cout << "Error No:" << hSockInit << std::endl;
		}

        #ifdef WRENCH_WINDOWS
		switch(hSockInit)
		{

		case SOCKET_ERROR:
			return WSAGetLastError();
			break;



		default:
			return 0;
		}
		#else

        return 0;
        #endif
	}

	int Listen( WConnectionInformation* con)
	{

			sockaddr_in addrbuf;

            #ifdef WRENCH_WINDOWS
			while(listen(con->Local, 1) == SOCKET_ERROR);
			#else
			while(listen(con->Local, 1) < 0);
			#endif

            #ifdef WRENCH_WINDOWS
			int len = sizeof(addrbuf);

			SOCKET RemoteBuffer = accept(con->Local, (sockaddr*)&addrbuf, &len);
			#else
			socklen_t len = sizeof(addrbuf);

			SOCKET RemoteBuffer = accept(con->Local, (struct sockaddr*)&addrbuf, &len);
			#endif

			std::string IP = inet_ntoa(addrbuf.sin_addr);
			std::cout << "Incoming connection from: " << IP << std::endl;
			if(strcmp(IP.c_str(), WRENCHNET_FAILURE) == 0)
				Listen(con);

			if(con->Connections.find(IP) == con->Connections.end())
				con->Connections[IP] = _CTSP(RemoteBuffer);
            std::cout << "Attempted to add them to the connections." << std::endl;

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

            #ifdef WRENCH_WINDOWS
			if(bytes == SOCKET_ERROR && bytes != WSAEWOULDBLOCK)
				Listen(con);
            #else
            if(bytes < 0)
                Listen(con);
            #endif

			if(bytes > 0)
			{
				std::string strRecv = buffer;
				std::string output = strRecv.substr(0, bytes);
				std::string* msg = new std::string();
				msg->append(IP);
				msg->append(":");
				msg->append(output.c_str());
				con->Messages.push((char*)msg->c_str());
				std::cout << msg->c_str() << std::endl;
			}

			Listen(con);

		return 0;
	}

	int Connect(int port, char* IP, WConnectionInformation* con)
	{
        std::cout << "Connecting to " << IP << ":" << port << std::endl;
		con->sockAddr.sin_family = AF_INET;
		con->sockAddr.sin_port = htons(port);


        //Create the socket
        #ifdef WRENCH_WINDOWS
		con->sockAddr.sin_addr.S_un.S_addr = inet_addr(IP);

		int ret = connect(con->Local, (sockaddr*)(&con->sockAddr), sizeof(con->sockAddr));
		#else
		con->sockAddr.sin_addr.s_addr = inet_addr(IP);
		int ret = connect(con->Local, (struct sockaddr*)(&con->sockAddr), sizeof(con->sockAddr));
		#endif

		if(ret >= 0)
		{
            std::cout << "Connected!\n";
		}

        #ifdef WRENCH_WINDOWS
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
		#else
		if(ret < 0)
            return 1;

		return 0; //Under Windows this should NEVER get called. It is only to settle the compiler.
		#endif
	}

	WVOID Disconnect( WConnectionInformation* con, WThread EstablishedThread )
	{
        #ifdef WRENCH_WINDOWS
		closesocket(con->Local); //Close socket for Windows
		#else
		shutdown(con->Local, 2); //Close socket for POSIX, do not accept or transmit any more information.
		#endif

        con->_ket = true;
		con->Local = socket(con->AFType, con->SocketType, con->Protocol); //Give the socket its old settings
	}

	int Established(WConnectionInformation* con)
	{
        std::cout << "Connected established!!!\n";
		while(true)
		{
			char buffer[WRENCHNET_BUFFER];
			char* cleanbuf;
			int bytes = recv(con->Local,buffer, WRENCHNET_BUFFER, 0);

			if(bytes == 0)
				return -1;

            if(con->_ket == true) //Kill established thread
            {
                con->_ket = false;

				break;
            }

            #ifdef WRENCH_WINDOWS
			else if(bytes == SOCKET_ERROR)
			{
				return WSAGetLastError();
			}
			#endif
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

		Send("Disconnecting.", con);
		#ifdef WRENCH_WINDOWS
			ExitThread(0);
		#else
			pthread_exit(0);
		#endif
	}

	WVOID Send( char* data, WConnectionInformation* con )
	{
        std::cout << "Sending:" << data << std::endl;
		Send(data, con->Local);
	}

	WVOID Send( char* data, SOCKET s )
	{
         std::cout << "Sending:" << data << std::endl;
		send(s, data, strlen(data), 0);
	}



}
