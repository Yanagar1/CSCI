// Client code to look up an email based on name

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>

// structure to store a lookup_t. client fills in with name, server
// fills in email if found in
typedef struct {
  int pid;
  char name[256];
  char email[256];
} lookup_t;

int signalled = 0;
void handle_signals(int sig_num){
  signalled = 1;
}

int main(int argc, char *argv[]){
  setvbuf(stdout, NULL, _IONBF, 0);
  struct sigaction my_sa = {};                                       // portable signal handling setup with sigaction()
  my_sa.sa_handler = handle_signals;                                 // run function handle_signals
  sigaction(SIGCONT, &my_sa, NULL);                                  // register SIGCONT with given action


  if(argc < 2){
    printf("usage: %s <name>\n",argv[0]);
    exit(1);
  }

  lookup_t request = {};
  request.pid = getpid();
  strcpy(request.name, argv[1]);

  int requests_fd    = open("requests.fifo", O_RDWR);     // open read/write in case server hasn't started
  int completions_fd = open("completions.fifo", O_RDWR);  // open read or write only may cause hangs if the
  int data_fd =        open("data.fifo", O_RDWR);         // other end of the pipe has not be openened

  printf("%d A CLIENT: sending request: {pid=%d  name=\"%s\" }\n",
         request.pid, request.pid, request.name);
  write(requests_fd, &request, sizeof(lookup_t));
  printf("%d B CLIENT: pid %d stopping\n",request.pid,request.pid);

  while(!signalled){
    sleep(1);                   // sleep for 1 second, wake up on on signal
  }

//   while(!signalled);            // poll for busy waiting

   raise(SIGSTOP);               // buggy waiting

  // if(!signalled){               // also buggy but much harder to hit a stall
  //  raise(SIGSTOP);             // try 'run_simulation.sh 3000' if you have some time
//   }

  printf("%d B CLIENT: pid %d signalled to continue\n",request.pid,request.pid);

  lookup_t response;
  read(data_fd, &response, sizeof(lookup_t));
  printf("%d C CLIENT: received response: {pid=%d  name=\"%s\" email=\"%s\"}\n",
         response.pid, response.pid, response.name, response.email);


  if(request.pid != response.pid){
    printf("CLIENT PROBLEM: PID %d vs %d\n", request.pid, response.pid);
    exit(1);
  }

  int pid = getpid();
  write(completions_fd, &pid, sizeof(int));
  printf("%d D CLIENT: pid %d indicating completion\n",request.pid,request.pid);

  // printf("CLIENT: result: %s\n",response.email);

  exit(0);
}
