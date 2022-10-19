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

void write_file(int sockfd,char* str)
{
	int n;
	FILE *fp;
	
	
	printf("%s",*str);

	char buffer[SIZE];

	fp = fopen("../Backup/"+*str,"w");
	if(fp==NULL)
	{
		printf("Error in creating file\n");
		exit(1);
	}

	while(1){
               n = recv(sockfd,buffer,SIZE,0);
	       if(n<=0){
		       break;
		       return;
	       }
	       fprintf(fp,"%s",buffer);
	       bzero(buffer,SIZE);
	}
	return;
}

int main(int argc,char* argv[]){

	int sockfd;
	char *str = argv[1];
	int B;
	struct sockaddr_in serveraddress;

	int newSocket;
	struct sockaddr_in newaddress;

	socklen_t addr_size;
	char buffer[SIZE];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
	{
		printf("Error in server creation\n");
		exit(1);
	}
	else
	printf("Server Created Sucessfully.\n"); 


	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	B = bind(sockfd, (struct sockaddr*)&serveraddress, sizeof(serveraddress));
        if(B<0)
	{
		printf("Error in Binding\n");
		exit(1);
	}
	else
	printf("Bind to Port number %d.\n", 4455);
        int L;
	L = listen(sockfd, 5);
	if(L==0)
	printf("[+]Listening...\n");
	else{
		printf("Error in Listening\n");
		exit(1);
   	}
        addr_size = sizeof(newaddress);
	newSocket = accept(sockfd, (struct sockaddr*)&newaddress, &addr_size);

       	write_file(newSocket,str);
        printf("Data is successfully written in file 2\n");
	printf("[+]Closing the connection.\n");



}  
