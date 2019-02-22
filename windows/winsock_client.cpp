// TCP Client

#pragma comment(lib, "ws2_32.lib")
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
using namespace std;

char sendbuf[256];
char recvbuf[256];

int main()
{
	long rc;

	WSADATA wsaData;
	SOCKET sConnect;
	sockaddr_in conpar;

	// ws2_32.dll aktivieren
	rc = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if(rc == 0 )
		cout << "WSAStartup()\t\t successful" << endl;
	else
		cout << "error WSAStartup(): " << WSAGetLastError() << endl;

	// socket einrichten
	sConnect = socket(AF_INET, SOCK_STREAM, 0);
	if(sConnect != INVALID_SOCKET )
		cout << "socket()  \t\t successful" << endl;
	else
		cout << "error socket(): " << WSAGetLastError() << endl;

	// verbindungsparameter
	conpar.sin_addr.s_addr = inet_addr("127.0.0.1");
	conpar.sin_family      = AF_INET;
	conpar.sin_port        = htons(54345);
	int conparlen = sizeof(conpar);

	// server vor client starten, oder hier eine connect-schleife erstellen 
	rc = connect(sConnect, (struct sockaddr*)&conpar, conparlen);
	if(rc != SOCKET_ERROR)
		cout << "connect()   \t\t successful" << endl;
	else
		cout << "not connected(): " << WSAGetLastError() << endl;

	while(1)
	{
		memset(&sendbuf, 0, sizeof(sendbuf));
		memset(&recvbuf, 0, sizeof(recvbuf));

		rc = recv(sConnect, recvbuf, 256, 0);
		if(rc == SOCKET_ERROR)
			cout << "error recv(): " << WSAGetLastError() << endl;
		else
		{
			cout << rc << " bytes received: "
				 << recvbuf << endl;
		}

		cout << "send: ";
		cin.getline(sendbuf, 256);

		rc = send(sConnect, sendbuf, strlen(sendbuf), 0);
		if(rc == SOCKET_ERROR)
			cout << "error send(): " << WSAGetLastError() << endl;
		else
			cout << rc << " bytes sent" << endl;
	}

	closesocket(sConnect);
	WSACleanup();
	return 0;
}