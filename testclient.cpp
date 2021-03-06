// testclient.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<stdio.h>

#include<stdlib.h>

#include<winsock2.h>



int main(int argc, char *argv[])

{



	SOCKET clientsock;

	WSADATA wsa;

	struct sockaddr_in sockinfo;



	char message[30];

	int strlen;



	if (argc != 3)

	{

		printf("Usage : %s <IP> <PORT> \n", argv[0]);

		exit(1);

	}





	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)

		printf("초기화 실패\n");



	clientsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);



	if (clientsock == INVALID_SOCKET)

		printf("소켓 생성 실패\n");



	memset(&sockinfo, 0, sizeof(sockinfo));



	sockinfo.sin_family = AF_INET;

	sockinfo.sin_port = htons(atoi(argv[2]));

	sockinfo.sin_addr.s_addr = inet_addr(argv[1]);



	if (connect(clientsock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)

		printf(" 서버 접속 실패 ");



	strlen = recv(clientsock, message, sizeof(message) - 1, 0);

	if (strlen == -1)

		printf(" 메세지 수신 실패 ");



	printf(" Server say: %s \n", message);







	closesocket(clientsock);







	WSACleanup();









}
