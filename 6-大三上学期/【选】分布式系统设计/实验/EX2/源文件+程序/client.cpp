// client.cpp: client process
#include <iostream>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_STR_LEN 256  // maximum length of the message sent to server

using namespace std;


int main()
{
	int server_socket = 0;
	struct sockaddr_in server_addr;
	char server_ip[INET_ADDRSTRLEN] = "";
	int server_port = 0;
	char message[MAX_STR_LEN] = "";
	pthread_t tid;
	struct timeval tv;
    
	
	// get IP address and port number of server:
	cout << "IP address of server: ";
	cin.getline(server_ip, INET_ADDRSTRLEN);
	cout << "Port number of server: ";
	cin >> server_port;
	
	// create a socket using TCP:
	server_socket = socket(AF_INET, SOCK_STREAM, 0);  // address family = Internet, type = TCP, protocol = auto
	if (server_socket == -1)
	{
		cerr << "ERROR: failed to create socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	// address:
	server_addr.sin_family = AF_INET;  // ipv4
	server_addr.sin_port = htons(server_port);  // port
	server_addr.sin_addr.s_addr = inet_addr(server_ip);  // ip address of server
	
	// connect:
    if (connect(server_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
		cerr << "ERROR: failed to connect to server" << endl;
		exit(EXIT_FAILURE);
    }
    else
    	cout << endl << "Connection to "
    		 << inet_ntoa(server_addr.sin_addr) << ':' << ntohs(server_addr.sin_port)
    		 << " is established." << endl << endl;
    		 
	tv.tv_sec = 0;
    tv.tv_usec = 5000;
    setsockopt(server_socket, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv) );
    
	// send hello to server:
	const char *hello = "Hello, server!";
	if (send(server_socket, hello, strlen(hello), 0) == -1)
		cerr << "ERROR: failed to send message" << endl;
	
	// receive and send: 
	getchar();
    while (true)
    {
    	// read and print message from server:
		while (true)
		{
			char recv_data[MAX_STR_LEN] = "";
			int n = recv(server_socket, recv_data, sizeof(recv_data), 0);
			if (n == -1)
			{
				//cerr << "ERROR: failed to receive data" << endl;
				break;
			}
			else
			{
				// print what is received:
				cout << "Server(" << inet_ntoa(server_addr.sin_addr) << ':'
				 	 << ntohs(server_addr.sin_port) << ") sent "
				 	 << n << " bytes data: " << recv_data << endl;
				continue;
			}
		}
		
		// get message:
		cout << endl << "Message to be sent to server: ";
		cin.getline(message, MAX_STR_LEN);
		
		// send message:
		if (send(server_socket, message, strlen(message), 0) == -1)
		{
			cerr << "ERROR: failed to send message" << endl;
			break;
		}
		
		if (!strcmp(message, "quit"))
			break;
    }
    
    // close socket:
	cout << "Connection to "
    	 << server_ip << ':' << server_port
    	 << " is released." << endl;
    close(server_socket);
    
    // thread exit:
	pthread_exit(0);
}

