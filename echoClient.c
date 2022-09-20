#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <unistd.h>
#include "sys/types.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include <arpa/inet.h>
#define BUF_LEN 128
//메시지 송수신에 사용될 버퍼 크기를 선언

int main(int argc, char *argv[]){  
    int s_sock, n;
    struct sockaddr_in server_addr;
        //struct sockaddr_in server_addr : 
        // 서버의 소켓주소 구조체
    char buffer[BUF_LEN];
 
    if(argc != 3)
    {
        printf("usage : %s [ip_Address] [port]\n", argv[0]);
        exit(0);
    }

    bzero((char *)&server_addr, 
           sizeof(server_addr));
        //서버의 소켓주소 구조체 server_addr을 NULL로 초기화
 
    server_addr.sin_family = AF_INET;  //주소 체계를 AF_INET 로 선택
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
        //32비트의 IP주소로 변환
    server_addr.sin_port = htons(atoi(argv[2]));
        // 서버 포트 번호
 
    if((s_sock = socket(AF_INET,  SOCK_STREAM, 0)) < 0)
    {//소켓 생성과 동시에 소켓 생성 유효검사
        printf("can't create socket\n");
        exit(0);         }
    if(connect(s_sock, (struct sockaddr *)&server_addr, 
                sizeof(server_addr)) < 0)
    {//서버로 연결요청
        printf("can't connect.\n");
        exit(0);
    }
    memset(buffer, 0x00, sizeof(buffer));
    char message[] = "Hello, I am a client";
    if (write(s_sock, message, sizeof(message)-1) < 0)
        printf("write error\n");
    n = read(s_sock, buffer, BUF_LEN);
    printf("Message from server: %s\n",    buffer);
    close(s_sock);
        //사용이 완료된 소켓을 닫기
    return 0;
}



