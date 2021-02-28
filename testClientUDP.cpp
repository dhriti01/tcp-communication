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
	if(argc !=3)
	{
		cout<<"Missing hostname and port no.";
		exit(0);
	}

	char *serverName = argv[1];
	int port= atoi(argv[2]);

	char message[MAXSIZE]; 

	struct hostent * host=gethostbyname(serverName);

	sockaddr_in clientSocket;

	bzero((char*)&clientSocket, sizeof(clientSocket));

	clientSocket.sin_family = AF_INET; // IPv4 
	clientSocket.sin_port = htons(port); 
    clientSocket.sin_addr.s_addr = INADDR_ANY; 

	int clientSocketID = socket(AF_INET, SOCK_DGRAM, 0); // Socket file descripter

	if (clientSocketID < 0) 
	{ 
		cerr<<"Not Successful"<<endl;
		exit(0); 
	} 

	socklen_t clientSocketLen = sizeof(clientSocket); 

	while(1)
    {
	string data;
	cout<<"Client: ";
	cin>>data;

	strcpy(message, data.c_str());

	sendto(clientSocketID, message, MAXSIZE, MSG_CONFIRM, (sockaddr *) &clientSocket, clientSocketLen);
	cout<<"Server: ";
	
	if(data=="exit")
	{
		cout<<"Connection terminated\n";
		break;
	}

	recvfrom(clientSocketID, (char *)message, MAXSIZE, MSG_WAITALL, (sockaddr *) &clientSocket, &clientSocketLen); 

	if(!strcmp(message, "exit"))
    {
	    cout<<"Connection terminated\n";
	   break;
    }

    cout<<message<<endl;

    }


	close(clientSocketID); 
	return 0; 
} 
