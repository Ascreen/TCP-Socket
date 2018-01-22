// client.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main()
{
  int iDs;
  int iDSize;
  int iRet;
  unsigned char ucBuf[256];
  
  struct sockaddr_in stAddr; // 서버 주소 구조체

  iDSize = sizeof(struct sockaddr_in);
  bzero(&stAddr, iDSize); // 0으로 구조체 초기화  
  
  // TCP를 사용하여 스트림 소켓을 연다.(반환형은 int)
  // 첫번째 인자는 IP protocol family - 2층 선택
  // 두번째 인자는 TCP설정, 세번째 인자는 Transmission Control Protocol - 3층
  iDs = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(iDs<0) // 예외 처리 - 소켓 생성에 실패했을 때
    {
    perror("socket() failed");
    close(iDs);
        return -10;
    }
  stAddr.sin_family = AF_INET; // socket()의 첫번째 인자와 같다.
  // 주소 변환
  iRet = inet_pton(AF_INET, "0.0.0.0", &stAddr.sin_addr.s_addr);
  if(iRet == 0)
  {
    printf("inet_pton() failed", "invalid address string");
    close(iDs);
        return -10;
  }
  else if(iRet < 0)
  {
    perror("inet_pton() failded");  
    close(iDs);
        return -10;
  }
  // ip 출력  
  printf("IP : %s\n", inet_ntoa(stAddr.sin_addr));
  // 서버 포트
  stAddr.sin_port = htons(3000);

  // 에코 서버에 연결 설정(connect) - 소켓 연결을 시작한다.
  // connect는 접속하기 전까지 client가 알 수 없다. 운영체제가 랜덤 생성
  // connect와 accept가 쌍을 이루고 3hand shake가 일어난다.
  if(0 > connect(iDs, (struct sockaddr *)&stAddr, iDSize))
  {
    perror("connect() failed");
    close(iDs);
    return -10;
  }
  write(iDs, "ping" , sizeof("ping"));
  iRet = read(iDs, ucBuf, sizeof(ucBuf));
  ucBuf[iRet] = 0;
  printf("%s\n", ucBuf);
  
  close(iDs); // 열었던 소켓을 닫는다.  
  return 0;
}
