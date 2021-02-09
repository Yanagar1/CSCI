// Simple HTTP get request program. Name host and file on command line
// to retrieve a file. Ex:
//
// $> http-get www-users.cs.umn.edu /~kauffman/congrads.txt  # default text get
// $> http-get www-users.cs.umn.edu /~kauffman/not-there.txt # missing file
// $> http-get www.google.com /                              # get's google's home page
// $> http-get umn.edu /                                     # UMN homepage?
// $> http-get twin-cities.umn.edu /                         # UMN homepage?


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <assert.h>
#include <arpa/inet.h>

#define PORT "80"                                   // the port client will be connecting to 
#define MAXDATASIZE 1024                            // max number of bytes we can get at once 

void get_address_string(struct addrinfo *addr, char buffer[]);

int main(int argc, char *argv[]) {
  if(argc > 1 && strcmp(argv[1],"-h")==0){
    printf("usage: %s <hostname> <file>\n",argv[0]);
    return 0;
  }

  char *hostname = "www-users.cs.umn.edu";
  char *hostfile = "/~kauffman/congrads.txt";
  if(argc >= 3){
    hostname = argv[1];
    hostfile = argv[2];
  }

  printf("Host: %s\nFile: %s\n",hostname, hostfile);

  int ret;
  struct addrinfo *serv_addr;   // filled by getaddrinfo
  ret = getaddrinfo(hostname, PORT, NULL, &serv_addr);
  assert(ret == 0);

  int sockfd = socket(serv_addr->ai_family,          // create a socket with the appropriate params
                      serv_addr->ai_socktype,        // to the server
                      serv_addr->ai_protocol);
  assert(ret != -1);

  ret = connect(sockfd,                             // connect the socket to the server so that 
                serv_addr->ai_addr,                  // writes will send over the network
                serv_addr->ai_addrlen);
  assert(ret != -1);

  char address_str[INET6_ADDRSTRLEN];                 // fill in a string version of the addrss which was resolved
  get_address_string(serv_addr, address_str);         // defined below, fills in buffer with printable address
  printf("connected to %s\n", address_str);

  freeaddrinfo(serv_addr);                           // all done with this structure

  char request[MAXDATASIZE] = {};                   // form the HTTP request for data
  int off = 0;
  off += snprintf(request+off, MAXDATASIZE, "GET %s HTTP/1.0\r\n", hostfile);
  off += snprintf(request+off, MAXDATASIZE, "Host: %s\r\n", hostname);
  off += snprintf(request+off, MAXDATASIZE, "Connection: close\r\n\r\n");

  int request_len = off;

  printf("REQUEST\n");
  printf("-------\n");
  printf("%s",request);
  printf("-------\n");

  int nbytes;
  nbytes = write(sockfd, request, request_len);
  assert(nbytes == request_len);

  printf("RESPONSE\n");
  printf("-------\n");

  char response[MAXDATASIZE];
  while(1){
    nbytes = read(sockfd, response, MAXDATASIZE-1);    // receive data data from the server
    assert(nbytes != -1);
    if(nbytes == 0){
      break;
    }
    write(STDOUT_FILENO, response, nbytes);
  }
  printf("-------\n");

  close(sockfd);

  return 0;
}

// Fill in the given buffer with a string version of the address from
// the given addrinfo.  This involves some nasty casting.  addrinfo
// structs have the member.
// 
//  struct sockaddr *ai_addr;	/* Socket address for socket.  */
// 
// which may be either a sockaddr_in (IPv4) or sockaddr_in6 (IPv6).
// The exact type is defined in the sin_family which is supposed be
// identical to the ai_family field of the addrinfo.
//
// The main workhorse is inet_ntop() which does the actual fill-in of
// the buffer with the translated address.
void get_address_string(struct addrinfo *addr, char buffer[]){
  void *ip_address = NULL;
  if(addr->ai_family == AF_INET){               // ipv4 address
    ip_address = (void *) &((struct sockaddr_in*)addr->ai_addr)->sin_addr;
  }
  else if(addr->ai_family == AF_INET6){         // ipv6 address
    ip_address = (void *) &((struct sockaddr_in6*)addr->ai_addr)->sin6_addr;
  }
  inet_ntop(addr->ai_family, ip_address, buffer, INET6_ADDRSTRLEN);
}
