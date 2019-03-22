#pragma comment(lib,"ws2_32.lib")
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <vector>


using namespace std;
int main()
{
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr;
	int sizeOfAddr = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("64.183.98.170");
	addr.sin_port = htons(3800);
	addr.sin_family = AF_INET;

	SOCKET Connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (connect(Connection, (SOCKADDR*)&addr, sizeOfAddr) != 0)
	{
		MessageBoxA(NULL, "Falled to connect", "error", MB_OK | MB_ICONERROR);
		return 0;
	}
	
	cout << "Connecting on:"<<endl;
	cout << "IP: 64.183.98.170" << endl;
	cout << "Port: 3800\n" << endl;
	
	char response[256] = { 0 };
	
	recv(Connection, response, sizeof(response), NULL);
	cout << "Response: "<<response << endl;

	string msg = "version\n";
	cout << "Sending " + msg << endl;
	send(Connection, msg.c_str(), msg.size(), NULL);

	recv(Connection, response, sizeof(response), NULL);
	cout << "Response: " << response << endl;
	system("pause");
}