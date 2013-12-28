Monkey-Wrench
=============
Monkey Wrench is a WIP library that is designed with the idea of reducing code size and increasing speed.

We have many diverse features and documentation to boot.

Installation:
Compile the Visual Studio solution or port the Source Code into another editor and compiler.
Copy the generated .dll (Wrench.dll) into wherever your program is attempting to start from.
Link against the .lib file in your project.
Include Wrench.h
Include what ever other Wrench extension you may need.
Enjoy!


Documentation:

Objects:
	Name: WClock
	File: Wrench_Timer.h
	Type: Class
	Functions: 
		int GetTimeMilliseconds();
		int GetTimeSeconds();
		int GetTimeMinutes();
		int GetTimeHours();
		int GetDay();
		int GetYear();
		char* GetMonth();
		void PullTime();
	Description: WClock is designed to make specific details about the current time much easier. It can also give the precise time in Hours, Minutes, Seconds and Milliseconds.
	Example Usage: 
		Wrench::WClock * newClock = new WClock();
		int Year = WClock.GetYear();
		int Seconds = WClock.GetTimeSeconds();
		int Milliseconds = WClock.GetTimeMilliseconds();
		
	Name: WThread
	File: Wrench_Thread.h
	Type: Struct
	Members:
		WUint ThreadID;
		WPVoid ThreadHandle;
	Description: WThread allows for easy access to a thread's handle and ID.
	Example Usage:
		int sample()
		{
			std::cout << "Hello!";
			return 0;
		}
	
		int main()
		{
			Wrench::WThread nt = Wrench::MakeThread(sample);
			return 0;
		}
	
	
	Name: WConnectionInformation
	File: Wrench_Net.h
	Type: Struct
	Members:
		sockaddr_in sockAddr;
		bool AutoRetry;
		std::queue<char*> Messages;
		SOCKET Local;
		std::map<std::string, SOCKET*> Connections;
	Description: WConnectionInformation contains all information needed for hosting, connecting and sending data in a concise format.
	Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
	 
	 
Functions:
	Name: Print
	File: Wrench_Logging.h
	Formal Name(s):
		void Print(char* message);
		void Print(char* message, WORD color);
		void Print(char* message, WORD foreground, WORD background);
	Description: Print allows the user to write text to the console with color.
	Example Usage:
		Wrench::Print("Hello"); //Prints Hello
		Wrench::Print("Hello", 0xA0); // Prints Hello with a green background.
		Wrench::Print("Hello", 0xA0, 0x0B); //Prints Hello with a green background and an aqua foreground
		
	Name: Printfile
	File: Wrench_Logging.h
	Formal Name(s):
		void Printfile(char* message, bool truncate, char* path); //Prints to a message to a file (Truncation optional)
		void Printfile(char* message, bool truncate, char* path, int placement, char* ix); //Prints a message to a file with a selectable prefix or suffix (Truncation optional)
		void Printfile(char* message, bool truncate, char* path, char* prefix, char* suffix); //Prints a message to a file with a prefix and a suffix (Truncation optional)
	Possible placements:
		PLACEMENT_SUFFIX
		PLACEMENT_PREFIX
		PLACEMENT_PREFIX_AND_SUFFIX
		
	Name: ModifyMemory
	File: Wrench_Memory.h
	Formal Name(s):
		ModifyMemory(char* Window, unsigned long Pointer, WPVOID Val);
	Description: Modify the value of a pointer in a foreign application.
	Example Usage:
		Wrench::ModifyMemory("Sample", 0x00000000, (WPVOID)28);
		
	Name: FreezeMemory
	File: Wrench_Memory.h
	Formal Name(s):
		WThread FreezeMemory(char* Window, unsigned long Pointer);
	Description: Freeze the value of a pointer in a foreign application. Returns a thread that the freeze is running on.
	Example Usage:
		Wrench::ModifyMemory("Sample", 0x00000000, (WPVOID)28); //Sets the pointer to 28
		Wrench::FreezeMemory("Sample", 0x00000000); //Freezes the value at 28
		
	Name: ExecuteShellcode
	File: Wrench_Shellcode.h
	Formal Name(s):
		void ExecuteShellcode(char* sc);
	Description: Execute Shellcode / Machine code
	Example Usage:
		char code[] = "\x00\x00\x00";
		Wrench::ExecuteShellcode(code);
		
	Name: MakeThread
	File: Wrench_Thread.h
	Formal Name(s):
		WThread MakeThread(WPVOID Function);
		WThread MakeThread(WPVOID Function, WPVOID args);
	Description: Creates a new thread and returns its Handle + ID.
	Example Usage:
		int sample()
		{
			std::cout << "Hello!";
			return 0;
		}
	
		int main()
		{
			Wrench::WThread nt = Wrench::MakeThread(sample);
			return 0;
		}
		
	Name: InitializeWrenchNet
	File: Wrench_Net.h
	Formal Name(s):
		int InitializeWrenchNet(WConnectionInformation* con, int AFType, int SOCKET_TYPE, int protocol = 0);
	Description: Initializes the WrenchNet system and fills out an instance of WConnectionInformation.
	Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		Wrench::InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
		
	Name: StartServer
	File: Wrench_Net.h
	Formal Name(s):
		int StartServer(int port, WConnectionInformation* con);
	Description: Attempts to create a server instance. The socket to be bound is provided with WConnectionInformation.
	Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		Wrench::InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
		int ret = StartServer(8080, con);
		if(ret == 0)
		{
			std::cout << "Server started on port 8080!" << std::endl;
		}
		
	Name: Listen
	File: Wrench_Net.h
	Formal Name(s):
		int Listen(WConnectionInformation* con);
	Description: Attempts to listen for incoming connections and messages. 
		NOTE: A server instance must already be started.
		NOTE: Messages will be stored in the WConnectionInformation's Messages queue with a FIFO order.
		NOTE: It is advised to run this function in a seperate thread as it runs in a loop and will occupy the thread indefinetly unless told otherwise.
	Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		Wrench::InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
		int ret = StartServer(8080, con);
		if(ret == 0)
		{
			std::cout << "Server started on port 8080!" << std::endl
			Wrench::MakeThread(Wrench::Listen, con); //Calls the function in a seperate thread whilst passing an instance of WConnectionInformation.
		}
		
	Name: Connect
	File: Wrench_Net.h
	Formal Name(s):
		int Connect(int port, char* IP, WConnectionInformation* con);
	Description: Attempts to connect to a remote (or local) server from a given IP.
	Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		Wrench::InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
		int ret = Wrench::Connect(8080, "127.0.0.1", con);
		if(ret == 0)
			std::cout << "Connected to the local server successfully!" << std::endl;
		else
			std::cout << "Error, unable to connect. Error code:" << ret << std::endl;
			
	Name: Disconnect
	File: Wrench_Net.h
	Formal Name(s):
		WVOID Disconnect(WConnectionInformation* con);
	Description: Attempts to disconnect from the remote server.
	Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		Wrench::InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
		int ret = Wrench::Connect(8080, "127.0.0.1", con);
		if(ret == 0)
		{
			std::cout << "Connected to the local server successfully!" << std::endl;
			Wrench::Disconnect(con);
		}
		
	Name: Established
	File: Wrench_Net.h
	Formal Name(s):
		int Established(WConnectionInformation* con);
	Description: Attempts to listen for incoming messages from the Server. Messages will be stored in the WConnectionInformation's Messages queue with a FIFO order.
		NOTE: A connection instance must already be started.
		NOTE: It is advised to run this function in a seperate thread as it runs in a loop and will occupy the thread indefinetly unless told otherwise.
	 Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		Wrench::InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
		int ret = Wrench::Connect(8080, "127.0.0.1", con);
		if(ret == 0)
		{
			std::cout << "Connected to the local server successfully!" << std::endl;
			Wrench::MakeThread(Wrench::Established, con);
		}
		
	Name: ResolveHost
	File: Wrench_Net.h
	Formal Name(s):
		char* ResolveHost(char* host);
	Description: Attempts to obtain the IP from a hostname.
	Example Usage:
		char* IP = Wrench::ResolveHost("www.google.com");
		
	Name: GetSocket
	File: Wrench_Net.h
	Formal Name(s):
		SOCKET* GetSocket(char* IP, WConnectionInformation* con);
	Description: Attempts to grab the socket linked to a specific IP from a connection.
		NOTE: It is more than possible to grab this manually through WConnectionInformation, this function serves only to simplify it and make it easier to read.
	Example Usage:
		SOCKET* a = Wrench::GetSocket("127.0.0.1", con);
		
	Name: Send
	File: Wrench_Net.h
	Formal Name(s):
		WVOID Send(char* data, WConnectionInformation* con);
		WVOID Send(char* data, SOCKET s);
	Description: Attempts to send data to a client or server.
	Example Usage:
		Wrench::WConnectionInformation* con = new Wrench::WConnectionInformation;
		Wrench::InitializeWrenchNet(con, AF_INET, SOCK_STREAM);
		int ret = Wrench::Connect(8080, "127.0.0.1", con);
		if(ret == 0)
		{
			std::cout << "Connected to the local server successfully!" << std::endl;
			Wrench::Send("Hello, Server!", con);
		}