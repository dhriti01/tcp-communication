# tcp-communication
# Introduction

A network protocol is a set of rules that defines how data is transmitted among devices in same network. We here discuss two of the important network protocols, namely - TCP (Transmission Control Protocol) and UDP (User Datagram Protocol). They both transfer the data over the internet from your device to a web server by dividing it into smaller packets (also known as the data packets). This data consists of 3 parts: Sender's and receiver's  IP addresses, actual data being communicated and the data indicating the end of the communication.

The only difference we observe is in the way the data is transported.

TCP is a connection oriented protocol ( a connection must be established between the devices before the start of communication (the 3 way handshake) and must close after it is completed) while this is not the case with UDP. Due to this feature as well as it's error checking and acknowledging mechanisms , TCP is more reliable than UDP. Also the sequence of packets sent by the sender remains intact and is received as it is by the receiver. But at the same time this also makes TCP a slower network protocol than UDP.  

Due to the above mentioned features, TCP is identified as a better medium for one-to-one communication like chatting and and e-mails and also to transmit data from other higher-level protocols (ex: FTP, SMTP, HTTP) that require all transmitted data to arrive, while UDP is better for applications like streaming audios and videos .

So now, the main part of the project is communication in form of chats between client and server using TCP protocol while we'll be implementing the same using UDP protocol as an additional part of it. 

# Tech Stack used

- Socket Programming
- Coded in C++
- Operating System: Linux

# How To Run

The code consists of 2 c++ files, 1 corresponding to server and the client each. You should know the complete path to these files. In our case it is Desktop/testServer.cpp and Desktop/testClient.cpp respectively and these will be used in the steps specified. But be sure you use the paths of these files as present on your machine.  We will be running the code in Linux OS. In case you do not have linux, you can download WSL since we want to use the linux terminal. 

**Step 1:** Open both the files and terminal in Linux (and open 2 tabs in it).

**Step 2:** In the first tab, we will be operating the server side, so type: g++ -o testServer         Desktop/testServer.cpp and press Enter.

**Step 3:** Next type ./testServer 2000 and press Enter. This should display "Waiting for client to connect..."

**Step 4:** Next move to the second tab we opened. This will be used for the client's side

**Step 5:** Type: g++ -o testServer Desktop/testClient.cpp and press Enter.

**Step 6:** Next type ./testServer [localhost](http://localhost) 2000 and press Enter.

**Step 7:** The terminal should now display "Successful connection " and "Client : " in the next line.

So we're ready to start the conversation!

**Step 8:** The client side of terminal is asking from input. Type whatever you feel like. We here start the conversation by typing "Hey" and it's visible in the Server side. Next type a message in the server side and it will be visible in the client side and the process goes on.

**Step 9:** If you feel like exiting the chat simply type "exit" on either of the sides and the chat will end with a message " Connection terminated" or " Session Terminated"
(The UDP implementation can also be carried out using the similar steps - just replace the file names accordingly)

# Important Logic Used

The logic used in the modeling of the project is as follows:

### For the Server Side:

So first of all we model the server socket which has 2 parts: Type of the socket and the address of the socket. For the address of the socket we use sockaddr_in structure and then specify the properties of the sockaddr structure (present in sockaddr_in) as follows:

- family = AF_INET (this property specifies the type of addresses our socket can communicate with. Here we choose IPv4 addresses since these are safest to use)
- convert port to htons (port) (we do so because it is possible that our device uses little endian format to store numbers while this may not be the case with the device we're communicating with. so we convert everything to the big endian format to avoid errors)
- Next using htonl (INADDR_ANY) we bind our socket to all the available interfaces

Next, we create file descripter for our socket. It specifies the address domain, socket type and the protocol we use. Since we are using TCP protocol (a connection based protocol) hence we use SOCK_STREAM (in the case of UDP we would have used SOCK_DGRAM)

And now we bind both the socket descripter and the address together.

Finally, since we're using TCP protocol we call the accept() function which terminates the further server process until a client attempts to connect and we get the address and the descripter of our client once it does so. This is point where our 3 way handshake takes place.

Next all we do is the data transfer from server to client and vice versa until the process is terminated by either server or client after which we close our sockets.

### For the Client Side:

Here first of all we retrieve the host information corresponding to a host name from a host database using the function  gethostbyname() function and store it in hostent structure (a struct that stores information of host). Next, we create our client socket in the simialar manner we did for server and set family = AF_INET and convert the port in big endian format using htons(port).

Again, we create the file descripter for this socket and set the arguments similar to how we did for server. Next, we initiate (start of 3 way handshake) to connect with the server by calling the connect(int (socket desripter), const struct sockaddr * (client socket variable), socklen_t (length of client socket variable length) ) function.

For stream sockets (type SOCK_STREAM), an active connection is initiated to the host using client socket variable name.

For a datagram socket (type SOCK_DGRAM), a default destination is set, which is used in subsequent send() and recv() calls.

Once the connection is established we can start the chat

# Results obtained

So the final result we obtain here is that a connection is established between the client and server and we can start the chat ( beginning with the client) which continues up to the point either of them sends an "exit" message. 

Hence it effectively highlights the following features of TCP protocol:

- Connection Orientation
- 3 way handshake
- Sequencing of Data
- Closing the connection after all data has been transmitted

# Addition to the Project

I have developed a similar communication between a server and a client but this time using the UDP protocol, the c++ codes for which can be found in the same repository (named as testServerUDP.cpp and testClientUDP.cpp) in order to bring out the clarity of differences between the 2.

# Future Goals

Currently we can host a chat communication between 1 server and 1 client only. The upcoming version of this project should be able to do so between 1 server and multiple clients. This can be achieved by forking the process in our server code so that multiple clients can be connected with a single server.

A second innovation could be to make this a chatbot which employs Natural language processing to understand human needs by the questions they ask and answer accordingly as well Machine learning and AI so that it learns automatically with multiple uses and hence continuously gets better with time
