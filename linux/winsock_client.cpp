// TCP Client

#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

char sendbuf[256];
char recvbuf[256];

int main()
{
	long rc;

    int sConnect;
	sockaddr_in conpar;

	// socket einrichten
	sConnect = socket(AF_INET, SOCK_STREAM, 0);
	if(sConnect != -1 )
		cout << "socket()  \t\t successful" << endl;
	else
		cout << "error socket(): " << errno << endl;

	// verbindungsparameter
	conpar.sin_addr.s_addr = inet_addr("127.0.0.1");
	conpar.sin_family      = AF_INET;
	conpar.sin_port        = htons(54345);
	int conparlen = sizeof(conpar);

	// server vor client starten, oder hier eine connect-schleife erstellen
	rc = connect(sConnect, (struct sockaddr*)&conpar, conparlen);
	if(rc != -1)
		cout << "connect()   \t\t successful" << endl;
	else
		cout << "not connected(): " << errno << endl;

	while(1)
	{
		memset(&sendbuf, 0, sizeof(sendbuf));
		memset(&recvbuf, 0, sizeof(recvbuf));

		rc = recv(sConnect, recvbuf, 256, 0);
		if(rc == -1)
			cout << "error recv(): " << errno << endl;
		else
		{
			cout << rc << " bytes received: "
				 << recvbuf << endl;
		}

		cout << "send: ";
		cin.getline(sendbuf, 256);

		rc = send(sConnect, sendbuf, strlen(sendbuf), 0);
		if(rc == -1)
			cout << "error send(): " << errno << endl;
		else
			cout << rc << " bytes sent" << endl;
	}

	return 0;
}
