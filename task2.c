#include <signal.h>
#include <stdio.h>
#include <unistd.h>
//Ctrl C1 program
/*
void ouch(int sig)
{
printf("OUCH! - I got signal %d\n", sig);
(void) signal(SIGINT, SIG_DFL);
}

int main()
{
  (void) signal(SIGINT, ouch);
  while(1) 
  {
    printf("Hello World!\n");
    sleep(1);
  }
}
*/

void ouch(int sig)
{
  printf("OUCH! - I got signal %d\n", sig);
}

int main()
{
  struct sigaction act;
  act.sa_handler = ouch;
  sigemptyset(&act.sa_mask);
  //overrides the previous signal
  act.sa_flags = SA_RESETHAND;
  sigaction(SIGINT, &act, 0);
  while(1) 
  {
    printf("Hello World!\n");
    sleep(1);
  }
}