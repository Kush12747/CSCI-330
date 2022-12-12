#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

void processRequest(int connectionSocket);
        
int main(int argc, char *argv[]) 
{
	//Attempt for extra credit but not working properly
	/*char command[256];
	cout << "Enter INFO to get the time and date" << endl;
	cin.getline(command, 256);
	char *tok = strtok(command, " ");
	char *argv[] = {tok, 0};*/
	
	//check command line arguments
	if (argc != 2) 
	{
		cerr << "Error: port number\n";
		exit(EXIT_FAILURE);
	}
	
	//creates a socket and error checks
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("Error: socket");
		exit(EXIT_FAILURE);
	}
	
	//address structures for server and the client
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;
	unsigned int addrlen = sizeof(client_address);	

	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(atoi(argv[1]));

	//Bind the socket
	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) 
	{
		perror("bind");
		exit(EXIT_FAILURE);
	}	
	
	if (listen(sock, 64) < 0) 
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	
	cout << "listening on port: " << argv[1] << endl;
	do 
	{
		int connectionSocket = accept(sock, (struct sockaddr *) &client_address, &addrlen);
		
		if (fork()) 
		{ 	
			//parent process
			close(connectionSocket);
		}
		else 
		{ 
			//child process
			processRequest(connectionSocket);
		}
	} while (true);	
}

void processRequest(int connectionSocket) 
{
	//variabels
	int check;
	char path[256];
	char buffer[256];

	//read a message from the client
	if ((check = read(connectionSocket, path, sizeof(path))) < 0) 
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	cout << path << endl;

	//checks and opens directory	
	DIR *directory = opendir(path);
	if (directory == 0) 
	{
		strcpy(buffer, path);
		strcat(buffer, "Error: can't open directory\n");
		exit(EXIT_FAILURE);
	}
	
	//reads directory entries
	struct dirent *dirEntry;
	while ((dirEntry = readdir(directory)) != NULL) 
	{
		strcpy(buffer, dirEntry->d_name);
		strcat(buffer, "\n");
		cout << buffer;
	}
	
	//closes everything
	closedir(directory);
	close(connectionSocket);
	exit(EXIT_SUCCESS);
}
