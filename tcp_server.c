/* A simple server in the internet domain using TCP
 * Answer the questions below in your writeup
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* 1. What is argc and *argv[]?
     * argc => argument count, integer of how many CL arguments passed into program
     * argv => argument vector, it is an array of char * with the actual parameters
     */
    int sockfd, newsockfd, portno;
    /* 2. What is a UNIX file descriptor and file descriptor table?
     * unix file descrip => small integer that represents an open file, device, or socket (helps keep track of open file or socket
     * file descr table => is like a list that maps these integers to the actual resources managed by the kernel (numbers to the real files or connections)
     */
    socklen_t clilen;

    struct sockaddr_in serv_addr, cli_addr;
    /* 3. What is a struct? What's the structure of sockaddr_in?
     * struct => way to put different variables together under one name. (container that lets you group different pieces of data together into one unit)
     * sockaddr_in => stores information for an internet socket: it has the address family (sin_family), the port number (sin_port), the IP address (sin_addr), and some padding (sin_zero).
     */
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    /* 4. What are the input parameters and return value of socket()
     * sockaddr_in => stores information for an internet socket: it has the address family (sin_family), the port number (sin_port), the IP address (sin_addr), and some padding (sin_zero).
     * /* 4. What are the input parameters and return value of socket()
     * inputs: he domain (for example AF_INET for IPv4), the type (like SOCK_STREAM for TCP), and the protocol (usually 0 so the system chooses)
     * return val: gives back a number for the new socket, or -1 if something went wrong
     */
    
    if (sockfd < 0) 
       error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    /* 5. What are the input parameters of bind() and listen()?
     * bind() needs three things: the socket number, the address you want to attach it to, and the size of that address
     * listen() needs the socket number and how many clients you'll let wait in line to connect
     */
    
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    
    while(1) {
        /* 6.  Why use while(1)? Based on the code below, what problems might occur if there are multiple simultaneous connections to handle?
        * listen() needs the socket number and how many clients you\u2019ll let wait in line to connect
        */
        
	char buffer[256];
        newsockfd = accept(sockfd, 
                    (struct sockaddr *) &cli_addr, 
                    &clilen);
	/* 7. Research how the command fork() works. How can it be applied here to better handle multiple connections?
         * fork() makes a new process that is a copy of the current one. In a server, after accept(), you can call fork() so the child process handles that single client, while the parent goes back to listen for new connections. this then allows for multiple clients/connections to be served and handled at the same time. 
         */
        
	if (newsockfd < 0) 
             error("ERROR on accept");
	bzero(buffer,256);
        
	n = read(newsockfd,buffer,255);
        if (n < 0) 
            error("ERROR reading from socket");
        printf("Here is the message: %s\n",buffer);
        n = write(newsockfd,"I got your message",18);
        if (n < 0) 
            error("ERROR writing to socket");
        close(newsockfd);
    }
    close(sockfd);
    return 0; 
}
  
/* This program makes several system calls such as 'bind', and 'listen.' What exactly is a system call?
 * A system call is a way for a program to ask the operating system to do something it can\u2019t do directly, like open a file, create a socket, or talk to hardware. It\u2019s the bridge between user code and the kernel.
 */