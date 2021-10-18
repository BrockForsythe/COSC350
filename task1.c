#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define BUFF 4

int main(int argc, char** argv)
{
	if (argc <= 2)
	{
		printf("Too few arguments\n");
		return 1;
	}
	if (argc > 3)
	{
		printf("Too many arguments\n");
		return 1;
	}
	char buf[BUFF];
	char inFile[] = "foo";
	char outFile[] = "foo1";
	int nread;
	
	int in = open(argv[1], O_RDONLY);
	
	if(in == -1)
	{
		printf("Read error\n");
		return 2;
	}
	
	umask(0);
	int out = open(argv[2], O_WRONLY|O_CREAT, 0660);
	if(out == -1)
	{
		puts("Write error");
		close(in);
		close(out);
		return 2;
	}	

	int done = 0;
        int i; // Iterates the inner for loop
        int num=0;// Number read in
       
	char strBuff[1];// This will be the converted char
        while((nread=read(in, buf, BUFF) > 0))
	{
        	num=0;
        	for(i=1; i<4; i++)
		{
            		num*=10;
            		num+=(buf[i] - '0');
        	}
        	strBuff[0]=(char)num;
        	printf("num: %d | char: %c\n", num, strBuff[0]);
        	if(write(out, strBuff, 1) == -1)
		{
        		printf("Writing error in file!\n");
                	return 3;
        	}
        }
	
	close(in);
	close(out);
	if (nread == -1)
	{
		printf("Read error\n");
		return 4;
	}
	return 0;
}
