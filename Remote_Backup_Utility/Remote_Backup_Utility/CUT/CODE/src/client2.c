#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 4455
#define SIZE 1000

void send_file(FILE *fp,int client)
{
	char data[SIZE] = {0};
	while(fgets(data,SIZE,fp)!=NULL)
	  {
		  if(send(client,data,sizeof(data),0) ==-1){
			   printf("Error in sending Data\n");
			   exit(1);
		  }
		 bzero(data,SIZE);
	}
}

int main(int argc,char* argv[])
{
	int client;
	struct sockaddr_in serveraddress;
	FILE *fp;
	char* filename = argv[1];

	client = socket(PF_INET,SOCK_STREAM,0);
	if(client<0)
	{
		printf("Error in client creation\n");
		exit(1);
	}
	else
	printf("Client is created successfully\n");


	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        int C;
	C = connect(client,(struct sockaddr*)&serveraddress,sizeof(serveraddress));
	if(C<0)
	{
		printf("Error in connecting to the server\n");
		exit(1);
	}
	else
        printf("Connected to the server\n");
        
        fp = fopen(filename, "r");
	if(fp == NULL)
	{
		printf("Error in opening a file\n");
                exit(1);
         }
     
	send_file(fp,client);
	printf("File data send successfully\n");
	printf("Closing the connection\n");

	close(client);
}
