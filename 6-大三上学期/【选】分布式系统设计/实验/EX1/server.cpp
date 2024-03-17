// server.cpp: server process
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define PORT 8080  // port number
#define MAX_STR_LEN 128  // maximum length of the message received from client

using namespace std;


int main()
{
	int server_socket = 0;
	int client_socket = 0;
	sockaddr_in server_addr;
	sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);
	char hostname[128] = "";
	char host_ip[INET_ADDRSTRLEN] = "";
	int port = 0;
	
	// create a socket using TCP:
	server_socket = socket(AF_INET, SOCK_STREAM, 0);  // address family = Internet, type = TCP, protocol = auto
	if (server_socket == -1)
	{
		cerr << "ERROR: failed to create socket" << endl;
		exit(EXIT_FAILURE);
	}

	// address:
	server_addr.sin_family = AF_INET;  // ipv4
	server_addr.sin_port = htons(PORT);  // port
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // any network interface
	
	// get and print: hostname, IP address and the port number being listened on:
	gethostname(hostname, sizeof(hostname));
	strcpy(host_ip, inet_ntoa(server_addr.sin_addr));
	port = ntohs(server_addr.sin_port);
	cout << "Hostname: " << hostname << endl
		 << "IP address of the host: " << host_ip << endl
		 << "Port number to be listened on: " << port <<endl;
	
	// bind address and port on socket:
	if (bind(server_socket, (struct sockaddr*)&server_addr,
		sizeof(server_addr)) == -1)
	{
		cerr << "ERROR: failed to bind socket" << endl;
		exit(EXIT_FAILURE);
	}
	
	// listen on socket:
	if (listen(server_socket, MAX_STR_LEN) == -1)
    {
        cerr << "ERROR: failed to listen on socket" << endl;
        exit(EXIT_FAILURE);
    }
	cout << "Listening on " << host_ip << ':' << port << endl;
	
	// read and print received data:
	client_socket = accept(server_socket, (sockaddr *)&client_addr, &length);
	while (true)
    {
        if(client_socket == -1)
        	continue;
 
        char recv_data[MAX_STR_LEN] = "";
        int n = recv(client_socket, recv_data, sizeof(recv_data), 0);
        if (n > 0)
            cout <<"Client(" << inet_ntoa(client_addr.sin_addr) << ':'
            	 << client_addr.sin_port << ") sent " << n << " bytes data: "
            	 << recv_data << endl;
        else if (n == 0)
        	break;
        else
        {
        	cerr << "ERROR: failed to receive data" << endl;
        	break;
        }
    }
    
    // close socket:
    close(client_socket);
    close(server_socket);
    
	return 0;
}
