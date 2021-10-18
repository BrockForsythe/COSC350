#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>
#include<ctype.h>

#define BUFF 1
#define numBUFF 90

int str_to_int(char* string)
{
	char str; // Correct string
    	int i; // Loop iterator
   	int neg = 0; // Assumes number is positive
    	int rtn=0;
    	for(i=0; string[i]!='\0'; i++)
	{
        	str = string[i];
		//If a negative sign is read
        	if(str=='-' && i==0)
		{
            		neg = 1;
        	}
		//If non number entered
		else if(str<'0'||str>'9')
		{
            		printf("%s is a invalid number!\n", string);
            		return -1;
        	}
		else
		{
            		rtn*=10;
            		rtn+=(str - '0');
        	}
    	}
    	if(neg==1)
        	return -1*rtn;
    return rtn;
}

int int_to_str(char* str, int x)
{
	sprintf(str, "%d", x);
	return(strlen(str));
}

int main(int argc, char** argv)
{
	if (argc < 1)
	{
		printf("Insufficient arguments supplied\n");
		return 1;
	}
	if(argc > 2)
	{
		printf("Too many arguments supplied\n");
		return 1;	
	}
	
	char inFile[] = "num.txt";

	int in = open(inFile, O_RDONLY);
	if(in == -1)
	{
		puts("Read error");
		return 2;
	}

	char buf[BUFF];//for reading
	char cnum[numBUFF];//For the possible number
	int nread;//hold file reading
	int num=0;//hold end number
	int i=0;//Hold what digit the number is
	int j=0;
        int isNum = 0; //Checks if a num is in file
	//Checks read file for num values assigns to a char array
	while((nread=read(in, buf, BUFF)) > 0)
	{
        	if(j>80)
            		break;
        	j++;
        	if(buf[0]>='0' && buf[0]<='9')
		{
			cnum[i]=buf[0];
			i++;
            		isNum=1;
		}
	}
    	if(isNum==0)
	{
        	printf("No number in file!\n");
        	return 1;
    	}
	num = str_to_int(cnum); //Converts string to int on char array
	num+=10;
	
	close(in);
	if(nread == -1)
	{
		printf("Reading error!\n");
		return 4;
	}

    	int temp = num;
    	int count = 0;
    	while(temp>0)
	{
        	temp/=10;
        	count++;
    	}
	//Dynamically allocate the return value
    	char* rtn = malloc(count);
    	int size = int_to_str(rtn, num);
    	write(1, rtn, count);// Print results to screen
    	printf("\n");
    	free(rtn); //Frees the memory
	return 0;
}
