#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
  pid_t pid;
  int i, infile, outfile;
  char buf;
  
  pid = fork();
  
  if(pid < 0)
  {
    puts("KFork failed.");
    exit(1);
  }
  //Child process
  else if(pid == 0)
  {
    outfile = open("foo", O_WRONLY | O_CREAT| O_EXCL, S_IREAD | S_IWRITE);
    if(outfile < 0)
    {
     puts("Output file already exists");
     exit(1);
    }
    char hello[] = "Hi, Mom.\n";
    write(outfile, &hello, sizeof(hello));
  }
  
  //Parent Process
  else
  {
    wait(&pid);
    
    infile = open("foo", O_RDONLY);
    if(infile < 0)
    {
     puts("Input file error");
     exit(1);
    }
    printf("My son said, ");
    while(read(infile, &buf, 1) > 0)
    {
     printf("%c", buf); 
    }
  }
  close(infile);
  close(outfile);
  return 0;
}
