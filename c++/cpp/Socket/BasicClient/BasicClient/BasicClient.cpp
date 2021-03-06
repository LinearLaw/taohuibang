﻿#include <iostream>
#include <winsock.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
void initialization();

int main()
{	
	/*  发送的字符串长度，
		接收的字符串长度 
	*/
	int send_len = 0;
	int recv_len = 0;

	/*	发送的字符串缓冲
		接收的字符串缓冲
	*/
	char send_buf[100];
	char recv_buf[100];

	/*	定义服务端socket
		定义服务端地址	
	*/
	SOCKET s_server;
	SOCKADDR_IN server_addr;
	initialization();

	/*	设置服务端的地址信息
	*/
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	server_addr.sin_port = htons(5010);

	/*  创建socket并connect到服务端 */
	s_server = socket(AF_INET, SOCK_STREAM, 0);
	if(connect(s_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR))
		== SOCKET_ERROR	
	){
		cout << "[Fail] 服务器连接失败" << endl;
		WSACleanup();
		return 0;
	}
	else {
		cout << "[Success] 服务器连接成功" << endl;
	}

	while (1) {
		/*  输入内容，作为client发送的内容，将其send到服务端 */
		cout << "[Client]：";
		cin >> send_buf;
		send_len = send(s_server, send_buf, 100, 0);

		if (send_len < 0) {
			cout << "[Fail] 发送失败" << endl;
			break;
		}

		/*  等待server的返回结果  */
		recv_len = recv(s_server, recv_buf, 100, 0);
		if (recv_len < 0) {
			cout << "[Fail] 接收失败" << endl;
			break;
		}
		else {
			cout << "[Server]：" << recv_buf << endl;
		}
	}

	closesocket(s_server);
	WSACleanup();
	return 0;
}

/*	对socket库进行初始化 */
void initialization() {
	WORD w_req = MAKEWORD(2, 2);
	WSADATA wsadata;

	int err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "[Fail] 初始化Socket库失败" << endl;
	}
	else
	{
		cout << "[Success]初始化Socket库成功" << endl;
	}

	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion)!=2) {
		cout << "[Fail] Socket库版本号不符" << endl;
	}
	else {
		cout << "[Success] Socket库版本号正确" << endl;
	}
}