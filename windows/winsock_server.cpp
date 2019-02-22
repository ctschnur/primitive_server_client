// Netzwerkprogrammierung, WINSOCK API, Sockets
// TCP Server

#pragma comment(lib, "ws2_32.lib")
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
using namespace std;

char recvbuf[256];

int main()
{
	// Hilfsvariable
	long res;

	// Versionsdaten
	WSADATA wsaData;

	// ws2_32.dll aktivieren
	res = WSAStartup(MAKEWORD(2, 1), &wsaData);
	if(res == 0 )
		cout << "WSAStartup()\t\t successful" << endl;
	else
		cout << "error WSAStartup(): " << WSAGetLastError() << endl;

	// Socket Deskriptoren
	SOCKET slisten, client;

	// Socket anforder bzw. Kommunikationsendpunkt einrichten
	slisten = socket(AF_INET, SOCK_STREAM, 0);
	if(slisten != INVALID_SOCKET )
		cout << "socket()  \t\t successful" << endl;
	else
		cout << "error socket(): " << WSAGetLastError() << endl;

	// Verbindungsinformationen
	sockaddr_in info;		// sockaddr
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_family		 = AF_INET;
	info.sin_port		 = htons(54345);
	int infolen = sizeof(info);

	res = bind(slisten, (struct sockaddr*)&info, infolen);
	if(res != SOCKET_ERROR )
		cout << "bind()  \t\t successful" << endl;
	else
		cout << "error bind(): " << WSAGetLastError() << endl;

	// Warteschlange für einkommende Verbindungen
	res = listen(slisten, SOMAXCONN);
	if(res != SOCKET_ERROR )
		cout << "listen()  \t\t successful" << endl;
	else
		cout << "error listen(): " << WSAGetLastError() << endl;

	sockaddr_in clientinfo;
	int clientinfolen = sizeof(clientinfo);

	while(1)
	{
		// Verbindung aus der Warteschlange abholen
		client = accept(slisten, (struct sockaddr*)&clientinfo, &clientinfolen);
		if(client != SOCKET_ERROR)
			cout << "client accepted: " << inet_ntoa(clientinfo.sin_addr) << ":"
			     << ntohs(clientinfo.sin_port) << endl;

		// über das Socket kommunizieren
		res = send(client, "server message received", strlen("server message received"), 0);
		if(res == SOCKET_ERROR)
			cout << "error send()" << WSAGetLastError() << endl;

		res = recv(client, recvbuf, 256, 0);
		if(res == SOCKET_ERROR)
			cout << "error recv(): " << WSAGetLastError() << endl;
		else
			cout << res << " bytes received: " 
				 << recvbuf << endl;
	}

	closesocket(client);
	closesocket(slisten);
	WSACleanup();
	return 0;
}