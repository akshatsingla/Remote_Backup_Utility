#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>

#define PORT 4455
#define SIZE 1000

void Write_Data(int);
void Send_Data(FILE*,int );
void Increment_Backup(char*,FILE* ,int);
void Just_In_Time_Backup(char*,FILE*,int);
void Scheduled_Backup(char*, FILE*, int );
void Full_Backup(FILE*,int);


#endif
