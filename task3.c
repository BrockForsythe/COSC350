#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

#define BUFF 1

int palind(int fd1, int fd2)
{
    char buf1[BUFF];
    char buf2[BUFF];
    //Make sure the files start where the need to be
    lseek(fd1, 0, SEEK_SET);
    lseek(fd2, -3, SEEK_END);
    int read1;
    int read2;
    int i=0;
    do
    {
        lseek(fd1, i, SEEK_SET);
        read1=read(fd1, buf1, BUFF);
        if(i==0)
        {
            lseek(fd2, -2, SEEK_END);
        }else{
		lseek(fd2, (i+2) * -1, SEEK_END);
	}
	read2=read(fd2, buf2, BUFF);
	if(read1 == -1 ||read2 == -2)
	{
		return 0;
	}
	i++;
	if(buf1[0] == '\n')
	{
		break;
	}
	printf("buf1[0]: %c | buf2[0]: %c\n", buf1[0],buf2[0]);
	if(buf1[0] != buf2[0])
	{
		printf("This file doesnt contain a palindrome\n");
		return 0;
	}
    }while(read1 > 0 && read2 > 0);
	printf("The file contains a palindrome\n");
return 0;
}

int main(int argc, char** argv)
{
	if(argc == 1)
	{
		printf("Need one file input!");
		return 1;
	}else if(argc > 2)
	{
		printf("Too many arguments\n");
		return 1;
	}
	int in = open(argv[1], O_RDONLY);
	if(in == -1)
	{
		printf("Error opening file\n");
		return 2;
	}
	int copy = dup(in);

	palind(in, copy);
	
	return 0;
}
