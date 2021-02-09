// Server code which contains a name/email pairs and will fulfill
// requests from a client through FIFOs.
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

// data the server has and clients want: pairings of name and email
char *data[][2] = {
  {"Chris Kauffman"       ,"kauffman@umn.edu"},
  {"Christopher Jonathan" ,"jonat003@umn.edu"},
  {"Amy Larson"           ,"larson@cs.umn.edu"},
  {"Chris Dovolis"        ,"dovolis@cs.umn.edu"},
  {"Dan Knights"          ,"knights@cs.umn.edu"},
  {"George Karypis"       ,"karypis@cs.umn.edu"},
  {"Steven Jensen"        ,"sjensen@cs.umn.edu"},
  {"Daniel Keefe"         ,"dfk@umn.edu"},
  {"Michael W. Whalen"    ,"whalen@cs.umn.edu"},
  {"Catherine Qi Zhao"    ,"qzhao@umn.edu"},
  {"Dan Challou"          ,"challou@cs.umn.edu"},
  {"Steven Wu"            ,"zsw@umn.edu"},
  {"Michael Steinbach"    ,"steinbac@cs.umn.edu"},
  {"Jon Weissman"         ,"jon@cs.umn.edu"},
  {"Victoria Interrante"  ,"interran@cs.umn.edu"},
  {"Shana Watters"        ,"watt0087@umn.edu"},
  {"James Parker"         ,"jparker@cs.umn.edu"},
  {"James Moen"           ,"moen0017@cs.umn.edu"},
  {"Daniel Giesel"        ,"giese138@umn.edu"},
  {"Jon Read"             ,"readx028@umn.edu"},
  {"Sara Stokowski"       ,"stoko004@umn.edu"},
  {NULL                   , NULL},
};

// structure to store a lookup_t. client fills in with name, server
// fills in email if found in
typedef struct {
  int pid;
  char name[256];
  char email[256];
} lookup_t;

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  printf("starting server\n");

  remove("requests.fifo");
  remove("completions.fifo");
  remove("data.fifo");
  printf("SERVER: removed old fifos\n");

  mkfifo("requests.fifo", S_IRUSR | S_IWUSR);
  mkfifo("completions.fifo", S_IRUSR | S_IWUSR);
  mkfifo("data.fifo", S_IRUSR | S_IWUSR);
  printf("SERVER: created new fifos\n");

  int requests_fd    = open("requests.fifo", O_RDWR);     // open read/write in case server hasn't started
  int completions_fd = open("completions.fifo", O_RDWR);  // open read or write only may cause hangs if the
  int data_fd =        open("data.fifo", O_RDWR);         // other end of the pipe has not be openened
  printf("SERVER: opened FIFOs, listening\n");

  while(1){
    lookup_t request;
    read(requests_fd, &request, sizeof(lookup_t));
    printf("%d B SERVER: received request {pid=%d  name=\"%s\" }\n",
           request.pid, request.pid, request.name);
    char *name = request.name;
    int found = 0;
    for(int i=0; data[i][0] != NULL; i++){
      if(strcmp(name, data[i][0]) == 0){
        strcpy(request.email, data[i][1]);
        found = 1;
      }
    }
    if(!found){
      strcpy(request.email, "NOT FOUND");
    }
    printf("%d B SERVER: filling request {pid=%d  name=\"%s\"  email=\"%s\" }\n",
           request.pid,request.pid, request.name, request.email);
    write(data_fd, &request, sizeof(request));
    printf("%d B SERVER: signaling pid %d\n",
           request.pid, request.pid);
    kill(request.pid, SIGCONT);
    int done_pid = -1;
    read(completions_fd, &done_pid, sizeof(int));
    printf("%d E SERVER: %d completion\n",done_pid,done_pid);
    if(request.pid != done_pid){
      printf("Server Problems: PID %d vs %d",
             request.pid, done_pid);
    }
  }

  exit(0);
}
