#include <iostream>
//#include <stdio.h>
#include <winsock2.h>


#define PORT 3600
#define IP "110.12.78.189"

#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

void main() {
	
	WSADATA WSAData;
	SOCKADDR_IN addr;
	SOCKET s;
	char buffer[1024];
	int readbytes;
	int i, len;
	

	if (WSAStartup(MAKEWORD(2, 2), &WSAData) != 0) {
		return;
	}
	while (1) {
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET) {
		return;
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.S_un.S_addr = inet_addr(IP);

	if (connect(s, (struct sockaddr *)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		printf("fail to connect\n");
		closesocket(s);
		return;
	}
	
		printf("enter messages\n");

		for (i = 0; 1; i++) {
			buffer[i] = getchar();
			if (buffer[i] == '\n')
			{
				buffer[i++] = '\0';
				break;
			}
		}

		len = i;

		printf("send message (%d bytes)\n", len);
		send(s, buffer, len, 0);
		
		//for (readbytes = 0; readbytes < len;)
			//readbytes += recv(s, buffer + readbytes, len - readbytes, 0);
		
			recv(s, buffer, len, 0);
			printf("recv messages = %s\n", buffer);
			

	
	closesocket(s);
	}
	WSACleanup();
	
}