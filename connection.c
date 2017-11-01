#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<arpa/inet.h>

#define IP "193.226.12.217"
#define PORT 20236

void error1(char *msg)
{
  perror(msg);
  exit(1);
}

int connectSocket(char * ip,int portno)
{
  int sockfd;
  struct sockaddr_in serv_addr;
  struct hostent;

  sockfd = socket(AF_INET, SOCK_STREAM,0);
  if (sockfd < 0)
      error1("Error opening socket");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(portno);
  if(inet_pton(AF_INET,ip,&serv_addr.sin_addr) <= 0)
  {
    error1("Error inet_pton");
  }
  if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
  {
    error1("Error connecting");
  }

  return sockfd;
}

int sendToSocket(int socket, char * buffer)
{
  int n;
  n = send(socket,buffer,strlen(buffer),0);
  if(n == 0)
    error1("Error writing to socket");

  return n;
}

int main( int argc, char *argv[])
{
  int openSocket;
  char buffer[256] = "fsbs";

  openSocket = connectSocket(IP,PORT);
  sendToSocket(openSocket,buffer);

  return 0;
}
