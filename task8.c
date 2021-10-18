#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define BUFF 1

int main(int argc, char** argv)
{
	if(argc <=2)
	{
		printf("Need to input 2 files\n");
		return 1;
	}
	else if(argc > 3)
	{
		printf("Too many files input\n");
		return 1;
	}

	char buf[BUFF];

	int nread;
	int in = open(argv[1], O_RDONLY);
	if(in == -1)
	{
		printf("Read error");
		return 1;
	}
	umask(0);
	int out = open(argv[2], O_WRONLY|O_CREAT, 0660);
	if(out == -1)
	{
		printf("Write error");
		close(in);
		close(out);
		return 2;
	}
	int done = 0;
	int i, num;
	char strBuff[4];
	strBuff[0] = ' ';
	while((nread = read(in, buf, BUFF) > 0))
	{
		num = *buf - '\0';
		for(i = 3; i >= 1; i--)
		{
			strBuff[i] = (num%10) + '0';
			num /= 10;
		}
		if(write(out, strBuff, 4) == -1)
		{
			printf("Writing error\n");
			return 3;
		}
	}
	close(in);
	close(out);
	if(nread == -1)
	{
		printf("Read error\n");
		return 4;
	}
	return 0;
}
