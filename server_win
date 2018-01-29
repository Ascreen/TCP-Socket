// test01.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"
#include<stdio.h>

#include<winsock2.h>



int main(int argc, char *argv[])

{



	SOCKET sock, clientsock;

	WSADATA wsa;

	struct sockaddr_in sockinfo, clientinfo;

	int clientsize;

	char message[] = "hello";





	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)

		printf("초기화 실패\n");



	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);



	if (sock == INVALID_SOCKET)

		printf("소켓 생성 실패\n");



	memset(&sockinfo, 0, sizeof(sockinfo));



	sockinfo.sin_family = AF_INET;

	sockinfo.sin_port = htons(1234);

	sockinfo.sin_addr.s_addr = htonl(INADDR_ANY);



	if (bind(sock, (SOCKADDR*)&sockinfo, sizeof(sockinfo)) == SOCKET_ERROR)

		printf(" bind 실패 ");



	if (listen(sock, 5) == SOCKET_ERROR)

		printf(" 대기열 실패 ");



	clientsize = sizeof(clientinfo);



	printf("클라이언트로부터 접속을 기다리고 있습니다...\n");



	clientsock = accept(sock, (SOCKADDR*)&clientinfo, &clientsize);



	if (clientsock == INVALID_SOCKET)

		printf(" 클라이언트 소켓 연결 실패 ");



	send(clientsock, message, sizeof(message), 0);





	closesocket(sock);

	closesocket(clientsock);









	WSACleanup();









}
