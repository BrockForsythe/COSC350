#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>

void sig_handler(int signo)
{
  signal(SIGQUIT, SIG_DFL);
}

int main()
{
  int i;
  sigset_t mask;
  sigemptyset(&mask);
  //Add SIGINT and SIGQUIT to the signal set
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGQUIT);
  sigprocmask(SIG_BLOCK, &mask, NULL);
  for(i = 1; i < 6; i++)
  {
      printf("Value of I: %d\n",i);
      sleep(1);
  }
  
  //Process signal again.
  signal(SIGQUIT, sig_handler);
  signal(SIGINT, sig_handler);
  
  //Unblock signals in set of signals
  sigprocmask(SIG_UNBLOCK, &mask, NULL);
  
  //reset calls in the signal set
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigprocmask(SIG_BLOCK, &mask, NULL);
  
  for(i = 1; i < 6; i++)
  {
      printf("Value of I: %d\n",i);
      sleep(1);
  }
 return 0; 
}
