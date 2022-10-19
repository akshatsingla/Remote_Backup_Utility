


/* *****        This client run after ther server is created and then client request to a server for a a connection and after the connection is
              is done client send a data to server for do the backup in Backup Directory *******   */
              
              
#include <header.h>


void Send_Data(FILE *fp,int client)    //This is the function of sending data to server for backup
{
	char data[SIZE] = {0};
	while(fgets(data,SIZE,fp)!=NULL)//Read data line by line and sending to the server
	  {
		  if(send(client,data,sizeof(data),0) ==-1){//Checking Data is send Successfully or not
			   printf("Error in sending Data\n");
			   exit(1);
		  }
		 bzero(data,SIZE);
	}
	 printf("\n\t\t\t\tBACKUP SUCCESSFULL");
}

void Full_Backup(FILE* fp,int client)//Defining Full Backup function
{
	Send_Data(fp,client);//calling send file function to read the data by client then it will send data to the server for backup

}


void Increment_Backup(char* filename,FILE* fp,int client)       //Defining a function for INCREMENT BACKUP
{

       //If file is updated today then we do back otherwise not
 
	struct stat filestat;

	//time_t timeSt = NULL ;
	struct tm *f = NULL ;

      stat(filename ,&filestat);
    /* newline included in ctime() output */

	f = localtime(&filestat.st_mtime);//Last modified Date for a file
	
    

	struct tm *t = NULL ;
	time_t now      = time(0);

	t = localtime(&now);//Date of today
   
    
     
      if(f->tm_year +1900 == t->tm_year + 1900 && f->tm_mday == t->tm_mday && f->tm_mon + 1== t->tm_mon + 1)//Check for Last modified Date for a file and Date of today
      {
          Send_Data(fp,client);//If file is updated today then sending a data for backup
      }
      else
      {
          printf("\n\n\t\t\t\tToday there is not change in a file so dont need to update");//Otherwise not sending a data for backup
      }
     
}





void Scheduled_Backup(char *filename, FILE *filep, int client)//Defining a function for schedule backup
{
        //File Will me automatically at 12:00 PM automatically
            
	char *confFile = "../conf.txt";
	FILE *fp = fopen(confFile, "r");//Opening a cong file

	time_t current_time;
	struct tm *time_info;
	char timeString[9];

	time(&current_time);
	time_info = localtime(&current_time);

	strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);

	if (fp == NULL)
	{
		return;
	}

	char line[1024] = {0};
	while (!feof(fp))//Reading a conf file because it contains all the time details when will schedule backup work in a day
	{
		memset(line, 0, 1024);
		fgets(line, 1024, fp);
		if (line[0] == '#')
		{
			continue;
		}

		int len = strlen(line);
		char *pos = strchr(line, '=');
		if (pos == NULL)
		{
			continue;
		}
		char key[64] = {0};
		char val[64] = {0};

		int offset = 1;
		if (line[len - 1] == '\n')
		{
			offset = 2;
		}

		strncpy(key, line, pos - line);
		strncpy(val, pos + 1, line + len - offset - pos);

		if (timeString == val)//If we got the time we are sending data for Backup
		{
			Send_Data(filep, client);
		}
	}
	

}

void Just_In_Time_Backup(char *filename,FILE *fp,int client)
{
	char *command,*result;
	strcpy(command,"find ../Data -mmin -60 # modification time");
	result = system(command);

	while(result)
	{
		Send_Data(fp,client);
	}
}

int main(int argc,char* argv[])
{ 
        
	//Taking files at command line from Data Directory
	int client;
	struct sockaddr_in serveraddress;
	FILE *fp;
	char* filename = argv[1];//Storing a file name int filename variable

	client = socket(PF_INET,SOCK_STREAM,0);//Creating a Client
	if(client<0)
	{
		printf("Error in client creation\n");
		exit(1);
	}
	else{
	printf("\n\n\n\t\t\t\t");
	printf("Client is created successfully");
	}


	serveraddress.sin_family = AF_INET;
	serveraddress.sin_port = htons(PORT);
	serveraddress.sin_addr.s_addr = inet_addr("127.0.0.1");
        int C;
	C = connect(client,(struct sockaddr*)&serveraddress,sizeof(serveraddress));//Connecting a client to the server
	if(C<0)
	{
		printf("Error in connecting to the server\n");
		exit(1);
	}
	else
	{
	printf("\n\n\t\t\t\t");
        printf("Connected to the server\n");
        }
        
        fp = fopen(filename, "r");//Opening a file which is given for backup
	if(fp == NULL)
	{
		printf("Error in opening a file\n");
                exit(1);
         }
         
        int choice;
        while(1)//Asking a backup choice from user which type of backup he wants
        {       printf("\n\n\n");
                printf("\t\t\t\tEnter Your Choice Of Backup");
                printf("\n\n\t\t\t\t1 : Full Backup\n\n\t\t\t\t2 : Increment Backup\n\n\t\t\t\t3 : Schedule Backup\n\n\t\t\t\t4 : Just In Time Backup\n\n\t\t\t\t5 : Exit\n");
                printf("\n\n\t\t\t\t");
                scanf("%d",&choice);
                switch(choice)
                {
                  case 1: Full_Backup(fp,client);//Calling Full Backup Function
                         
                          break;

	          case 2: Increment_Backup(filename,fp,client);//Calling Increment Backup
			  break;
			  
                  case 3:printf("\n\n\t\t\t\tBackup Will Be Automatic Created At 12:00 PM"); 
                  Scheduled_Backup(filename,fp,client);//Calling Schedule Backup
                          break;
			  
		  case 4: Just_In_Time_Backup(filename,fp,client);//Calling Just in time back up
		          break;

                  case 5: printf("\n\t\t\t\tClosing the connection\n");//Closing the connection
                  return 0;
                }
        }

     
	
	

	close(client);
}
