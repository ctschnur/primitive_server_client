// TCP Server

#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>


char recvbuf[256];

int main()
{
	// Hilfsvariable
	long res;

	// Socket Deskriptoren
	int slisten, client;

	// Socket anforder bzw. Kommunikationsendpunkt einrichten
	slisten = socket(AF_INET, SOCK_STREAM, 0);
	if(slisten != -1 )
		cout << "socket()  \t\t successful" << endl;
	else
		cout << "error socket(): " << errno << endl;

	// Verbindungsinformationen
	sockaddr_in info;		// sockaddr
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_family		 = AF_INET;
	info.sin_port		 = htons(54345);
	int infolen = sizeof(info);

	res = bind(slisten, (struct sockaddr*)&info, infolen);
	if(res != -1 )
		cout << "bind()  \t\t successful" << endl;
	else
		cout << "error bind(): " << errno << endl;

	// Warteschlange für einkommende Verbindungen
	res = listen(slisten, SOMAXCONN);
	if(res != -1 )
		cout << "listen()  \t\t successful" << endl;
	else
		cout << "error listen(): " << errno << endl;

	sockaddr_in clientinfo;
	socklen_t clientinfolen = sizeof(clientinfo);

	while(1)
	{
		// Verbindung aus der Warteschlange abholen
		client = accept(slisten, (struct sockaddr*)&clientinfo, &clientinfolen);
		if(client != -1)
			cout << "client accepted: " << inet_ntoa(clientinfo.sin_addr) << ":"
			     << ntohs(clientinfo.sin_port) << endl;

		// über das Socket kommunizieren
		res = send(client, "server message received", strlen("server message received"), 0);
		if(res == -1)
			cout << "error send()" << errno << endl;

		res = recv(client, recvbuf, 256, 0);
		if(res == -1)
			cout << "error recv(): " << errno << endl;
		else
			cout << res << " bytes received: "
				 << recvbuf << endl;
	}

	return 0;
}
