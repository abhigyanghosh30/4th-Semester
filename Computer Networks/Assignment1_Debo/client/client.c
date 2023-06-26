// client code for UDP socket programming 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h> 

#define IP_PROTOCOL 0 
#define IP_ADDRESS "127.0.0.1" // localhost 
#define PORT_NO 15050 
#define NET_BUF_SIZE 32 
#define cipherKey 'S' 
#define sendrecvflag 0 

// funtion to clear buffer 
void clearBuf(char* b) 
{ 
	int i; 
	for (i = 0; i < NET_BUF_SIZE; i++) 
		b[i] = '\0'; 
} 

// function for decryption 
char Cipher(char ch) 
{ 
	return ch ^ cipherKey; 
} 

// function to receive file 
int recvFile(char* buf, int s, FILE *file_ptr) 
{ 
	int i; 
	char ch; 
	for (i = 0; i < s; i++) { 
		ch = buf[i]; 
		ch = Cipher(ch); 
		if (ch == EOF) 
			return 1; 
		else
			fprintf(file_ptr,"%c", ch); 
	} 
	return 0; 
} 

// driver code 
int main() 
{ 
	int sockfd, nBytes; 
	struct sockaddr_in addr_con; 
	int addrlen = sizeof(addr_con); 
	addr_con.sin_family = AF_INET; 
	addr_con.sin_port = htons(PORT_NO); 
	addr_con.sin_addr.s_addr = inet_addr(IP_ADDRESS); 
	char net_buf[NET_BUF_SIZE]; 
	FILE* fp; 

	// socket() 
	sockfd = socket(AF_INET, SOCK_DGRAM, 
					IP_PROTOCOL); 

	if (sockfd < 0) 
		printf("\nfile descriptor not received!!\n"); 
	else
		printf("\nfile descriptor %d received\n", sockfd); 

	while (1) { 
		printf("\nPlease enter file name to receive:\n"); 
		gets(net_buf); 

        if(net_buf==NULL || strcmp(net_buf,"")==0){
            continue;
        }
        char *command = strtok(net_buf," ");

        if(strcmp(command,"listall")==0){
            sendto(sockfd, "../listall", NET_BUF_SIZE, 
                sendrecvflag, (struct sockaddr*)&addr_con, 
                addrlen); 

            printf("\n---------Data Received---------\n"); 
            while (1) { 
                // receive 
                clearBuf(net_buf); 
                nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, 
                                sendrecvflag, (struct sockaddr*)&addr_con, 
                                &addrlen); 

                // process 
                if (recvFile(net_buf, NET_BUF_SIZE,stdout)) { 
                    break; 
                } 
            }

        }
        else if(strcmp(command,"send")==0){

            char *file = strtok(NULL," ");
            char fname_copy[100];
            strcpy(fname_copy,file);
            printf("%s",fname_copy);
            if(file == NULL){
                printf("No file name");
                continue;
            }    


            FILE *file_ptr;
            remove(file);
            
            file_ptr = fopen(file,"a+");
            FILE* file_ptr2 = fopen(file,"r");

            sendto(sockfd, file, NET_BUF_SIZE, 
                sendrecvflag, (struct sockaddr*)&addr_con, 
                addrlen); 

            printf("\n---------Data Received---------\n"); 

            while (1) { 
                // receive 
                clearBuf(net_buf); 
                nBytes = recvfrom(sockfd, net_buf, NET_BUF_SIZE, 
                                sendrecvflag, (struct sockaddr*)&addr_con, 
                                &addrlen); 

                // process 
                if (recvFile(net_buf, NET_BUF_SIZE,file_ptr)) { 
                    break; 
                } 
            } 
            fclose(file_ptr);

            char line[100];

            fscanf(file_ptr2,"%[^\n]",line);
            if(strcmp(line,"!File")==0){
                remove(fname_copy);
            }

        }
        else{
            printf("Command not found");
        }
		printf("\n-------------------------------\n"); 
	} 
	return 0; 
} 
