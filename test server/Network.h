#pragma once
#include <iostream>
#include <WS2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

class Network
{
public:
	Network() = default;
	~Network() = default;
	void StartServer();				//starts up the server and waits until a connection is made
	void WaitForClientData();		//waits until the client has send something to the server
	const std::string CheckData();	//checks what the client has sent to the server
	void SendData(std::string s);	//sends something to the client
	void StopServer();				//shuts down the server
private:
	char buf[4096];
	SOCKET listeningSocket;
	SOCKET clientSocket;
	sockaddr_in client;
	int clientSize;
};

