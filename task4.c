#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>

#define BUFF 1

int main(int argc, char** argv)
{
	int len = (strlen(getenv("HOME")) + 1);
	char* home = malloc(len*sizeof(char));
	char* dir1 = malloc(len+5);
	char* dir2 = malloc(len+5);
	char* dir12 = malloc(len+10);
	char* helloCopy = malloc(len+10+6);

	strcpy(home, getenv("HOME"));
	strcpy(dir1, home);
	strcpy(dir2, home);
	strcpy(dir12, home);

	strcat(dir1, "/Dir1");
	strcat(dir2, "/Dir2");
	strcat(dir12, "/Dir2/Dir21");
	strcat(helloCopy, dir12);
	strcat(helloCopy, "/hello");

	struct stat buff;
	if(stat(dir1, &buff) < 0)
	{
		if(mkdir(dir1, 0775) < 0)
		{
			printf("Error making Dir1\n");
			return 1;
		}
	}

	if(stat(dir2, &buff) < 0)
	{	
		if(mkdir(dir2, 0775) < 0)
		{
			printf("Error making Dir2\n");
			return 1;
		}
	}
	
	if(stat(dir12, &buff) < 0)
	{	
		if(mkdir(dir12, 0775) < 0)
		{
			printf("Error making Dir12\n");
			return 1;
		}
	}
	
	int copy = open(helloCopy, O_WRONLY|O_CREAT, 0777);
	if(copy == -1)
	{
		printf("Error opening file\n");
		return 1;
	}
	int in = open("hello", O_RDONLY);
	if(in == -1)
	{
		printf("Error opening file\n");
		return 1;
	}
	int nread;
	char buf[BUFF];
	while((nread = read(in, buf, BUFF)) > 0)
	{
		if(write(copy, buf, nread) == -1)
		{
			printf("error reading\n");
			return 1;
		}
	}
	
	if(nread == -1)
	{
		printf("Read error\n");
		return 1;
	}
	close(copy);
	
	char* toHello = malloc(len + 5 + 8);
	strcpy(toHello, dir1);
	strcpy(toHello, "/toHello");
	
	char* toDir12 = malloc(len + 5 + 8);
	strcpy(toDir12, dir1);
	strcpy(toDir12, "/toDir12");

	if(stat(toHello, &buff) < 0)
	{
		if(symlink(helloCopy, toHello) < 0)
		{
			printf("Error in symlink toHello\n");
			return 1;
		}
	}

	if(stat(toDir12, &buff) < 0)
	{
		if(symlink(dir12, toDir12) < 0)
		{
			printf("\n");
		return 1;
		}
	}
	return 0;
}
