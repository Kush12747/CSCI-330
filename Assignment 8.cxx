#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <cstring>
#include <errno.h>
#include <fcntl.h>
using namespace std;

int main(int argc, char *argv[])
{
	int fd;
	char buffer[] = "";
	char fileName[] = "log.txt";
	
	fd = open(fileName, O_WRONLY | O_APPEND | O_CREAT, 00000);
	
	//if no file exist then exit
	if (fd == -1)
	{
		perror(fileName);
		exit(EXIT_FAILURE);
	}
	
	//close the file
	close(fd);
	
	struct stat permissions;
	fd = stat(fileName, &permissions);
	if (fd == -1)
	{
		perror(fileName);
		exit(EXIT_FAILURE);
	}
	
	if (S_IRUSR & permissions.st_mode)
	{
		exit(EXIT_FAILURE);
	}
	if (S_IWUSR & permissions.st_mode)
	{
		exit(EXIT_FAILURE);
	}
	if (S_IXUSR & permissions.st_mode)
	{
		exit(EXIT_FAILURE);
	}
	
	//change permissions to add write
	chmod(fileName, O_WRONLY);
	fd = open(fileName, O_WRONLY);
	
	//write to file
	write(fd, buffer, strlen(buffer));
	
	if (fd == -1)
	{
		perror(fileName);
		exit(EXIT_FAILURE);
	}
	
	if (string(argv[0]) == "-c")
	{
		open(fileName, O_RDONLY);
		if (fd == -1)
		{
			perror(fileName);
			exit(EXIT_FAILURE);
		}
	}
	
	//clear the perimissions of the file and close
	chmod(fileName, 00000);
	close(fd);
}
