// server.cpp: server process
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>

#define PORT 8080        // port number
#define MAX_STR_LEN 256  // maximum length of the message received from client
#define MAX_THRD_NUM 5   // maximum number of threads
#define MAX_STU_NUM 3    // maximum number of students to store

using namespace std;

/***** STRUCTS *****/
// define a struct to store data of students:
struct students_data {
  string name = "";
  string student_id = "";
  float score = 0.0;
};

// define a struct as arg to be passed in:
struct socket_info {
  struct sockaddr_in client_addr;
  int client_socket;
};

/***** GLOBAL VARIABLES *****/
struct students_data sd[MAX_STU_NUM];
int student_idx = 0;
struct socket_info si[MAX_THRD_NUM];
int thread_cnt = 0;
int a;

/***** FUNCTIONS *****/
// interact with clients:
void *interact(void *arg) {
  int thread_idx = *((int *)arg);
  // send hello to client:
  const char *hello =
      "Hello, client!\n  - Enter \"SCORE <name> <student_id> <score>\" to "
      "upload score of a student.\n  - Enter \"quit\" to release the "
      "connection.";
  if (send(si[thread_idx].client_socket, hello, strlen(hello), 0) == -1)
    cerr << "ERROR: failed to send message" << endl;
  // receive and print hello from client:
  char hello_from_client[MAX_STR_LEN] = "";
  int n = recv(si[thread_idx].client_socket, hello_from_client,
               sizeof(hello_from_client), 0);
  if (n > 0)
    cout << "Client(" << inet_ntoa(si[thread_idx].client_addr.sin_addr) << ':'
         << ntohs(si[thread_idx].client_addr.sin_port) << ") sent " << n
         << " bytes data: " << hello_from_client << endl;

  // read, send message and process data:
  while (true) {
    // receive data from client:
    char recv_data[MAX_STR_LEN] = "";
    int n = recv(si[thread_idx].client_socket, recv_data, sizeof(recv_data), 0);
    if (n == -1) {
      cerr << "ERROR: failed to receive data" << endl;
      break;
    } else {
      // if "quit" is received, release connection:
      if (!strcmp(recv_data, "quit")) {
        cout << "Connection to "
             << inet_ntoa(si[thread_idx].client_addr.sin_addr) << ':'
             << si[thread_idx].client_addr.sin_port << " is released." << endl;
        break;
      }

      // print what is received:
      cout << "Client(" << inet_ntoa(si[thread_idx].client_addr.sin_addr) << ':'
           << si[thread_idx].client_addr.sin_port << ") sent " << n
           << " bytes data: " << recv_data << endl;

      // reply:
      const char *reply = "Copy that.";
      if (send(si[thread_idx].client_socket, reply, strlen(reply), 0) == -1)
        cerr << "ERROR: failed to send message" << endl;

      // read a line and split:
      // copy string:
      char temp_message[MAX_STR_LEN] = "";
      strcpy(temp_message, recv_data);
      // split the string, delimeter is " ", and get the first word:
      char *save_ptr = NULL;
      char *first_word = strtok_r(temp_message, " ", &save_ptr);
      // if the first word is "SCORE", split the string as "SCORE <name>
      // <student_id> <score>"
      if (!strcmp(first_word, "SCORE")) {
        // store:
        char *temp_sd[3];
        int temp_idx = 0;
        while ((temp_sd[temp_idx] = strtok_r(NULL, " ", &save_ptr)) != NULL &&
               ++temp_idx < 3)
          ;
        sd[student_idx].name = temp_sd[0];
        sd[student_idx].student_id = temp_sd[1];
        sd[student_idx].score = stof(temp_sd[2]);
        student_idx++;
        // print current record:
        cout << "[INFO]Current record of students:" << endl;
        for (int i = 0; i < student_idx; ++i)
          cout << "Student_" << i << ':' << endl
               << "- Name: " << sd[i].name << endl
               << "- ID: " << sd[i].student_id << endl
               << "- Score: " << sd[i].score << endl;
        // calculate and send average score:
        if (student_idx == MAX_STU_NUM) {
          // calculate average score and make up the message:
          string message = " Average score of ";
          float sum = 0;
          for (int i = 0; i < MAX_STU_NUM; ++i) {
            sum += sd[i].score;
            message.append(sd[i].name);
            message.append("(ID: ");
            message.append(sd[i].student_id);
            if (i != MAX_STU_NUM - 1)
              message.append("), ");
            else
              message.append(") ");
          }
          float avrg = sum / MAX_STU_NUM;
          message.append("is ");
          message.append(to_string(avrg));
          // send to all clients:
          for (int i = 0; i < thread_cnt; ++i)
            if (send(si[i].client_socket, message.c_str(), message.length(),
                     0) == -1)
              cerr << "ERROR: failed to send message" << endl;
          // reset index to 0:
          student_idx = 0;
        }
      }
    }
  }

  // close socket:
  close(si->client_socket);

  // thread exit:
  pthread_exit(0);
}

int main() {
  int server_socket = 0;
  int client_socket = 0;
  sockaddr_in server_addr;
  sockaddr_in client_addr;
  socklen_t length = sizeof(client_addr);
  char hostname[128] = "";
  char host_ip[INET_ADDRSTRLEN] = "";
  int port = 0;
  pthread_t tid;

  // create a socket using TCP:
  server_socket =
      socket(AF_INET, SOCK_STREAM,
             0);  // address family = Internet, type = TCP, protocol = auto
  if (server_socket == -1) {
    cerr << "ERROR: failed to create socket" << endl;
    exit(EXIT_FAILURE);
  }

  // address:
  server_addr.sin_family = AF_INET;                 // ipv4
  server_addr.sin_port = htons(PORT);               // port
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);  // any network interface

  // get and print: hostname, IP address and the port number being listened on:
  gethostname(hostname, sizeof(hostname));
  strcpy(host_ip, inet_ntoa(server_addr.sin_addr));
  port = ntohs(server_addr.sin_port);
  cout << "Hostname: " << hostname << endl
       << "IP address of the host: " << host_ip << endl
       << "Port number to be listened on: " << port << endl;

  // bind address and port on socket:
  if (bind(server_socket, (struct sockaddr *)&server_addr,
           sizeof(server_addr)) == -1) {
    cerr << "ERROR: failed to bind socket" << endl;
    exit(EXIT_FAILURE);
  }

  // listen on socket:
  if (listen(server_socket, MAX_STR_LEN) == -1) {
    cerr << "ERROR: failed to listen on socket" << endl;
    exit(EXIT_FAILURE);
  }
  cout << "Listening on " << host_ip << ':' << port << "..." << endl << endl;

  // accept requests and create threads:
  while (thread_cnt < MAX_THRD_NUM) {
    // accept connection requests from clients:
    client_socket = accept(server_socket, (sockaddr *)&client_addr, &length);
    if (client_socket == -1) {
      cerr << "ERROR: failed to accept" << endl;
      continue;
    }
    // arg:
    si[thread_cnt].client_socket = client_socket;
    si[thread_cnt].client_addr = client_addr;
    // create a thread:
    int arg = thread_cnt;
    pthread_create(&tid, NULL, interact, (void *)&arg);
    pthread_detach(tid);
    ++thread_cnt;
  }

  // thread exit:
  pthread_exit(0);
}
