#include "Network.h"

void Network::StartServer()
{
	//init winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);
	WSAStartup(version, &data);

	//create a socket
	listeningSocket = socket(AF_INET, SOCK_STREAM, 0);

	//bind IP and port to socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(listeningSocket, (sockaddr*)&hint, sizeof(hint));

	//set socket for listening
	listen(listeningSocket, SOMAXCONN);

	//wait for connection
	clientSize = sizeof(client);
	clientSocket = accept(listeningSocket, (sockaddr*)&client, &clientSize);
	char host[NI_MAXHOST];
	char service[NI_MAXHOST];
	ZeroMemory(host, NI_MAXHOST);
	ZeroMemory(service, NI_MAXHOST);
	if (getnameinfo((sockaddr*)&client, clientSize, host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
	}

	//close listening socket
	closesocket(listeningSocket);
}

void Network::WaitForClientData()
{
	//clear the buffer
	ZeroMemory(buf, 4096);

	//wait for client to send data
	int bytesReceived = recv(clientSocket, buf, 4096, 0);
	if (bytesReceived == 0)
	{
		std::cout << "client disconnected" << std::endl;
		//break;
	}
}

const std::string Network::CheckData()
{
	std::string msg = buf;
	return msg;
}

void Network::SendData(std::string s)
{
	const char* msg = s.c_str();
	send(clientSocket, msg, sizeof(msg) + 1, 0);
}

void Network::StopServer()
{
	//close socket
	closesocket(clientSocket);

	//clean up winsock
	WSACleanup();
}
