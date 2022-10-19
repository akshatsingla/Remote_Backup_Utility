
//******   First Server run and then waiting for a connection request from client and this will create a backup of data which it gets from client
#include <header.h>

void Write_Data(int sockfd)//Defining a function for writing a data into Backup directory
{
	int n;
	FILE *fp;
	char* filename = "../Backup/File.txt";//Giving location for backup the data

	char buffer[SIZE];

	fp = fopen(filename,"w");//Opening a file in Backup directory
	if(fp==NULL)//Checking file is opening or not
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
	       fprintf(fp,"%s",buffer);//Writing data into a backup directory
	       bzero(buffer,SIZE);
	}
	fclose(fp);
	return;
}

int main(){

	int sockfd;
           int n;
	int B;
	struct sockaddr_in serveraddress;

	int newSocket;
	struct sockaddr_in newaddress;

	socklen_t addr_size;
	char buffer[SIZE];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);//Creating a Server
	if(sockfd<0)//Checking server is created successfully or not
	{
		printf("Error in server creation\n");
		exit(1);
	}
	else{
	printf("\n\n\n\n");
	printf("\t\t\t\tServer Created Sucessfully"); 
        }

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");

	B = bind(sockfd, (struct sockaddr*)&serveraddress, sizeof(serveraddress));//Binding the server to the port number
        if(B<0)
	{
		printf("\n\n\t\t\t\tError in Binding\n");
		exit(1);
	}
	else
	printf("\n\n");
	printf("\t\t\t\tBind to Port number : - %d.", 4455);
	printf("\n\n");
	printf("\t\t\t\tServer Is Listening.........");
        int L;
        while(1){
        
        
	L = listen(sockfd, 5);//Make server listining the client
	
	printf("\n\n");
	if(L==0)
	printf("\t\t\t\tServer Got The Data Successfully From Client Side");
	else{
		printf("Error in Listening\n");
		exit(1);
   	}
        addr_size = sizeof(newaddress);
	newSocket = accept(sockfd, (struct sockaddr*)&newaddress, &addr_size);

       	Write_Data(newSocket);//Calling the function
       	
       	
       	printf("\n\n");
        printf("\t\t\t\tData is successfully Backuped in The Backup Directory\n");
        printf("\n\n");
	printf("\t\t\t\tServer Is Again Listening\n");
	
	}



}  
