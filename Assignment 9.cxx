#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>

using namespace std;

int main()
{
	int pid;
	int status;
	int rs;
	char command[256];
	
	//loop to process input commands
	do 
	{	
		cout << "Enter command: ";
		cin.getline(command, 256);
		
		//if exit then terminate program successfully
		if (strcmp(command, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		
		char *tok = strtok(command, " ");
		char *argv[] = {tok, 0};
		
		//call fork
		pid = fork();
		
		//error check
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		
		if (pid == 0)
		{
			//runs command by using execvp
			rs = execvp(argv[0], argv);
			
			//error check
			if (rs == -1)
			{
				perror(tok);
				exit(EXIT_FAILURE);
			}
		}
		else 
		{
			wait(&status);
		}
	} while (pid);
	return 0;
}

