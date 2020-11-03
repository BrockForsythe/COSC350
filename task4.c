#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

void sigUser(int sig)
{
 if(sig == SIGUSR1)
 {
  puts("Hi honey! Anything wrong?");
 }
 else if(sig == SIGUSR2)
 {
  puts("Do you make trouble again?");
 }
}

int main()
{
  pid_t pid1, pid2;
  pid1 = fork();
  if(pid1 < 0)
  {
     puts("Fork failed.");
     exit(1);
  }
  //Child process
  else if(pid1 == 0)
  {
    kill(pid1, SIGUSR1);
    pause();
  }
  //Parent Process
  else
  {
    pid2 = fork();
    if(pid2 < 0)
    {
     puts("Fork failed.");
     exit(1);
    }
    else if(pid2 == 0)
    {
     kill(pid2, SIGUSR2);
     pause();
    }
    else
    {
     signal(SIGUSR1, sigUser);
     signal(SIGUSR2, sigUser);
    }
  }
  return 0;
}