// PoE_Port_Control.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
//#include <fstream>
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include "format.h"
#include <fstream>


SOCKET sock;
#define POE_HUB_ADDR "192.168.0.55"

// 소켓 함수 오류 출력 후 종료
void err_quit(char *msg)
{
	printf("error: %s\n", msg);
	exit(1);
}

// 소켓 함수 오류 출력
void err_display(char *msg)
{
	printf("error: %s\n", msg);
}


int init_socket_connect()
{
	int retval;


	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(POE_HUB_ADDR);
	serveraddr.sin_port = htons(80);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) {
		err_display("connect()");
		closesocket(sock);
		return -1;
	}
	return 0;
}

void send_data(const char* buf, int length)
{
	int retval;
	// 데이터 보내기
	
	printf("send: %s\n", buf);
	retval = send(sock, buf, length, 0);
	if (retval != length) {
		err_display("send() 1");
		return;
	}
}



bool check_ok()
{
	char buf[2048 + 1];
	int n;
	do {
		n = recv(sock, buf, 2048, 0);
	} while (n == 0);
	if (!strncmp(buf, "HTTP/1.", strlen("HTTP/1."))) {
		char* p = buf + strlen("HTTP/1.1") + 1;
		char* ret = strtok(p, " ");
		if (!strcmp(ret, "200")) {
			return true;
		}
	}
	return false;

}

char* get_sid()
{
	static char sid[10];
	char buf[1024 + 1];
	int n = recv(sock, buf, 1024, 0);
	printf("set sid=%s\n", buf);
	if (!strncmp(buf, "HTTP/1.", strlen("HTTP/1."))) {
		char* p = buf + strlen("HTTP/1.1") + 1;
		char* ret = strtok(p, " ");
		if (!strcmp(ret, "200")) {
			char* p = strstr(ret + 10, "Set-Cookie:");
			if (!p)
				return NULL;
			p = strtok(p, "=\r\n");
			p = strtok(NULL, "=\r\n");
			strcpy(sid, p);
			return sid;
		}
	}
	return NULL;
}

bool login(const char* ip, const char* sid = NULL)
{
	char buf[1024];
	printf("*** Login\n");
	if (sid)
		sprintf(buf, LOGIN_COOKIE, ip, ip, ip, sid);
	else
		sprintf(buf, LOGIN, ip, ip);
		
	send_data(buf, strlen(buf));

	if (check_ok())
		printf("ok\n");
	else {
		printf("failed\n");
		return false;
	}

	return true;
}

bool logout(const char* ip, const char* sid)
{
	char buf[1024];
	printf("*** Logout\n");
	sprintf(buf, LOGOUT, ip, ip, ip, sid);

	send_data(buf, strlen(buf));

	return true;
}

bool accept(const char* ip, char* sid)
{
	char buf[1024];
	bool bSid = (strlen(sid) != 0);
	if (bSid)
		sprintf(buf, ACCEPT_COOKIE, ip, ip, sid);
	else
		sprintf(buf, ACCEPT, ip, ip);

	send_data(buf, strlen(buf));

	if (bSid) {
		if (!check_ok())
			return false;
	}
	else {
		char* p = get_sid();
		if (!p) return false;
		strcpy(sid, p);
	}
	return true;
}

bool port_control(const char* ip, const char* sid, int port, bool enable)
{
	char content[1024];
	char buf[1024];
	sprintf(content, PORT_CONTROL_CONTENT, enable ? 1 : 2, port, port);
	sprintf(buf, PORT_CONTROL, ip, strlen(content), ip , ip, sid, content);
	send_data(buf, strlen(buf));
	if (check_ok())
		printf("ok\n");
	else {
		printf("failed\n");
		return false;
	}
	return true;
}

int main()
{
	char sid[10] = { 0, };
	char buf[1024];
	int port = 15;
	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return -1;
	//if (init_packet_capture() < 0)
	//	return 0;
	if (init_socket_connect() < 0)
		return 0;

	std::ifstream sid_file;
	sid_file.open("sid.txt");
	if (!sid_file.fail()) {
		size_t n = sid_file.read(sid, 10).gcount();
		sid[n] = '\0';
		sid_file.close();
	}

	printf("send data login\n");
	login(POE_HUB_ADDR, sid);
	
	closesocket(sock);
	if (init_socket_connect() < 0)
		return 0;

	printf("send data accept\n");
	accept(POE_HUB_ADDR, sid);

	printf("sid=%s\n", sid);
	std::ofstream fileOfstream("sid.txt");
	fileOfstream << sid;
	fileOfstream.close();
	
	port_control(POE_HUB_ADDR, sid, port, false);
	
	closesocket(sock);
	if (init_socket_connect() < 0)
		return 0;

	port_control(POE_HUB_ADDR, sid, port, true);

	//log_off
	logout(POE_HUB_ADDR, sid);

	closesocket(sock);
	// 윈속 종료
	WSACleanup();
    return 0;
}

