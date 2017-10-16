// sender.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

// ���� �Լ� ���� ��� �� ����
void err_quit(char *msg)
{
	printf("error: %s\n", msg);
	exit(1);
}

// ���� �Լ� ���� ���
void err_display(char *msg)
{
	printf("error: %s\n", msg);
}

#define HTTP_HEAD_FMT "POST /cgi-bin/setisp HTTP/1.1\r\n" \
		"Authorization: Basic cm9vdDoxcWF6QFdTWA==\r\n" \
		"Connection: Keep-Alive\r\n" \
		"Host: %s:80\r\n" \
		"content-length: %d\r\n\r\n" 
void send_data(char* ip, unsigned char* buf, int length)
{
	int retval;
	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(ip);
	serveraddr.sin_port = htons(80);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) {
		err_display("connect()");
		closesocket(sock);
		return;
	}

	// ������ ������
	char data[1024];
	sprintf(data, HTTP_HEAD_FMT, ip, length);
	retval = send(sock, data, strlen(data), 0);
	if (retval == SOCKET_ERROR) {
		err_display("send() 1");
		return;
	}

	retval = send(sock, (char*)buf, length, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send() 2");
		return;
	}

	closesocket(sock);
	
}

int main(int argc, char *argv[])
{
	int retval;

	// ���� �ʱ�ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	char buf[1024];

	if (argc < 2) {
		printf("%s <filename> [ip]\n", argv[0]);
		exit(1);
	}
	FILE* fp = fopen(argv[1], "rb");
	fseek(fp, 0, SEEK_END);
	long length = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fread(buf, 1, length, fp);

	// connect()
	char ip[20];
	if (argc > 2) {
		send_data(argv[2], (unsigned char*)buf, length);
	}
	else {
		for (int col = 0; col < 8; col++) {
			for (int row = 0; row < 8; row++) {
				sprintf(ip, "192.168.0.1%d%d", col + 1, row + 1);
				printf("send %s\n", ip);
				send_data(ip, (unsigned char*)buf, length);
			}

		}
	}


	// ���� ����
	WSACleanup();
	return 0;
}