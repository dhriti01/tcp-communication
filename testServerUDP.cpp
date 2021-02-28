#include<sys/types.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <bits/stdc++.h>
using namespace std;

#define MAXSIZE 1024 

// Driver code 
int main(int argc, char *argv[]) 
{
	if (argc !=2)
    {
        cerr<<"Missing port number"<<endl;
        exit(0);
    }
    
    int port = atoi(argv[1]);
	char message[MAXSIZE]; 

	sockaddr_in serverSocket;

	bzero((char*)&serverSocket, sizeof(serverSocket));

	serverSocket.sin_family = AF_INET; // IPv4 
	serverSocket.sin_port = htons(port); 
    serverSocket.sin_addr.s_addr = INADDR_ANY; 

	int serverSocketID = socket(AF_INET, SOCK_DGRAM, 0); // Socket file descripter

	if (serverSocketID < 0) 
	{ 
		cerr<<"Not Successful"<<endl;
		exit(0); 
	} 
	
	 int bindStatus = bind(serverSocketID, (sockaddr *)&serverSocket, sizeof(serverSocket));
     if(bindStatus<0)
     {
        cerr<<"Not successful bind"<<endl;
        exit(0);
     }
	
	
    sockaddr_in newSocket;
    socklen_t newSocketLen = sizeof(newSocket);
	
	       while(1)
           {
                cout<<"Waiting for a message from client"<<endl;
                recvfrom(serverSocketID, (char *)message, MAXSIZE, MSG_WAITALL, (sockaddr *) &newSocket, &newSocketLen); 
                if(!strcmp(message, "exit"))
                {
                      cout<<"Session terminated";
                      break;
                }
                cout<<message<<endl;
                string data;
                cin>>data;
                strcpy(message, data.c_str());
                if(data=="exit")
                {
                     cout<<"Session terminated";
                     break;
                }
                sendto(serverSocketID, (char *) message, MAXSIZE, MSG_CONFIRM, (sockaddr *) &newSocket, newSocketLen);
            }

	return 0; 
} 
