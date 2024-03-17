// client.cpp: client process
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_STR_LEN 128  // maximum length of the message sent to server

using namespace std;

int main()
{
	int client_socket = 0;
	struct sockaddr_in server_addr;
	char server_ip[INET_ADDRSTRLEN] = "";
	int server_port = 0;
	char message[MAX_STR_LEN] = "";
	
	// get IP address and port number of server:
	cout << "IP address of server: ";
	cin.getline(server_ip, INET_ADDRSTRLEN);
	cout << "Port number of server: ";
	cin >> server_port;
	
	// create a socket using TCP:
	client_socket = socket(AF_INET, SOCK_STREAM, 0);  // address family = Internet, type = TCP, protocol = auto
	if (client_socket == -1)
	{
		cerr << "ERROR: failed to create socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	// address:
	server_addr.sin_family = AF_INET;  // ipv4
	server_addr.sin_port = htons(server_port);  // port
	server_addr.sin_addr.s_addr = inet_addr(server_ip);  // ip address of server
	
	// connect:
    if (connect(client_socket, (sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
		cerr << "ERROR: failed to connect to server" << endl;
		exit(EXIT_FAILURE);
    }
    else
    	cout << endl << "Connection to "
    		 << server_ip << ':' << server_port
    		 << " is established." << endl << endl;
	
	// send hello to server:
	const char *hello = "Hello, server!";
	if (send(client_socket, hello, strlen(hello), 0) == -1)
		cerr << "ERROR: failed to send message" << endl;
	// receive and print hello from server:
	char hello_from_server[MAX_STR_LEN] = "";
	int n = recv(client_socket, hello_from_server, sizeof(hello_from_server), 0);
	if (n > 0)
		cout << "Server(" << server_ip << ':'
			 << server_port << ") sent "
			 << n << " bytes data: " << hello_from_server << endl;
	
	// send and receive:
	getchar();
    while (true)
    {
		// get message:
		cout << endl << "Message to be sent to server: ";
		cin.getline(message, MAX_STR_LEN);
		
		// send message:
		if (send(client_socket, message, strlen(message), 0) == -1)
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
    close(client_socket);
    
	return 0;
}

