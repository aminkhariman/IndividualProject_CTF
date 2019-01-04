#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BLACK	"\x1b[1m\033[30m"
#define WHITE   "\x1b[1m\033[37m"
#define RESET   "\x1b[0m"
#define PORT "9999" //the port users will be connecting t

#define BACKLOG 10 //how many pending connections queue 

void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void signchld_handler(int s)
{
	while(waitpid(-1, NULL, WNOHANG) > 0);
}
//get sockaddr, IPV4 or IPV6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(void)
{
	int sockfd, new_fd,sret,nz;
	struct addrinfo hints, *servinfo, *p;
	struct sockaddr_storage their_addr;
	struct sigaction sa;
	socklen_t sinsize;
	int yes=1,n;
	int rv;
	//char s[INET6_ADDRSTRLEN];
	char ipstr[INET6_ADDRSTRLEN];
	char sendline[1024];
	pid_t childpid;
	time_t waktu;
	waktu = time(NULL);
	//sini
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo))!=0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return 1;
	} 

	for(p = servinfo; p !=NULL;p = p->ai_next)
	{
	
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			perror("server: socket");
			continue;
		}	

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int))== -1)
		{
			perror("setsockopt");
			exit(1);	
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen)== -1)
		{
			close(sockfd);
			perror("server:bind");
			continue;	
		}
		break;
	}

	if (p == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		return 2;
	}
	
	freeaddrinfo(servinfo);

	if (listen(sockfd, BACKLOG)==-1)
	{
		perror("listen");
		exit(1);
	}

	sa.sa_handler = signchld_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;

	if (sigaction(SIGCHLD, &sa, NULL)==-1)
	{
		perror("sigaction");
		exit(1);
	}
	
	printf("server: waiting for connections....\n");

	//jawapan
    //char soalanA[1000]="\nCall this number to get this flags and \npass this message to him without making any sound: \n\nAlan Turing: +765252336365\nMessage:\n\n…-…-.-.-..-…-..-..-.-…-…-\n\nhurry! He's not going to wait for you\n\n\n";
    //char soalanB[1000]="\nGo0d ! y0u g0t th3 f1rst fl4g:\n\nNow you have to meet Mr. Turing at the KTM @ Station KL Sentral \nplatform and dont send this to him or else you will die:\n\ng43Dn{Sarce}emsg_Evm3ei\n\n\n";
    char a[100]="rojakcendol";
	char b[100]="m3sS4age_r3cEiveD";
	char c[100]="twentyone";

	while(nz=1)
	{
		new_fd = accept(sockfd, (struct sockaddr*)&their_addr, &sinsize);
		if (new_fd == -1)
		{
			perror("accept");
			continue;
		}
		int port;

		if (their_addr.ss_family == AF_INET) 
		{
		    struct sockaddr_in *sockfd = (struct sockaddr_in *)&their_addr;
		    port = ntohs(sockfd->sin_port);
		    inet_ntop(AF_INET, &sockfd->sin_addr, ipstr, sizeof ipstr);
		} else 
		{ 
			// AF_INET6
		    struct sockaddr_in6 *sockfd = (struct sockaddr_in6 *)&their_addr;
		    port = ntohs(sockfd->sin6_port);
		    inet_ntop(AF_INET6, &sockfd->sin6_addr, ipstr, sizeof ipstr);
		}
			

		if((childpid = fork()) == 0){
			close(sockfd);
			printf("server: got connection from %s:%d\n", ipstr,port);
			printf("server: time connected %s\n",ctime(&waktu));

				write(new_fd,CYAN "\nCall this number to get this flags and \npass this message to him without making any sound: \n\nAlan Turing: +765252336365\nMessage:\n\n…-…-.-.-..-…-..-..-.-…-…-\n\nhurry! He's not going to wait for you\n\n\n" RESET,strlen(CYAN "\nCall this number to get this flags and \npass this message to him without making any sound: \n\nAlan Turing: +765252336365\nMessage:\n\n…-…-.-.-..-…-..-..-.-…-…-\n\nhurry! He's not going to wait for you\n\n\n" RESET));
				bzero(sendline, 100);
				read(new_fd,sendline,100);
            	printf("Question 1: Client[%d]: %s",port,sendline);
				if(strncmp(sendline,a,11)==0)
				{
					write(new_fd,RED "\n\nmeng{h3lLo!h3LLo!}\n" RESET,strlen("\n\nmeng{h3lLo!h3LLo!}\n" RESET));
					write(new_fd, BLUE "\n\nGo0d ! y0u g0t th3 f1rst fl4g:\n\nNow you have to meet Mr. Turing at the KTM @ Station KL Sentral \nplatform and dont send this to him or else you will die:\n\ng43Dn{Sarce}emsg_Evm3ei\n\n\n" RESET,strlen(BLUE "\nGo0d ! y0u g0t th3 f1rst fl4g:\n\nNow you have to meet Mr. Turing at the KTM @ Station KL Sentral \nplatform and dont send this to him or else you will die:\n\ng43Dn{Sarce}emsg_Evm3ei\n\n\n" RESET));
					bzero(sendline, 100);
					read(new_fd,sendline,100);
                    	printf("Question 2: Client[%d]: %s",port,sendline);
                    	if(strncmp(sendline,b,17)==0)
                    	{
                            write(new_fd, RED "\n\nmeng{0n3_mIssIon_l3Ft}\n\n" RESET,strlen(RED "\n\nmeng{0n3_mIssIon_l3Ft}\n\n" RESET));
                            write(new_fd, GREEN "\n\nGet this one and you're done! \n\nWhat nine plus 10?\n\n" RESET,strlen(GREEN "\n\nGet this one and you're done! \n\nWhat nine plus 10?\n\n" RESET));
                            bzero(sendline, 100);
							read(new_fd,sendline,100);
								printf("Question 3: Client[%d]: %s",port,sendline);
								if(strncmp(sendline,c,9)==0)
								{
									write(new_fd, RED "\n\nmeng{aNigMa}\n\n" RESET,strlen(RED "\n\nmeng{aNigMa}\n\n" RESET));
									write(new_fd,YELLOW "\n\nCONGRATULATION MISSION IS DONE\n\n" RESET, strlen(YELLOW "\n\nCONGRATULATION MISSION IS DONE\n\n" RESET));
									nz=0;
									exit(1);
									break;
	                        	}
	                        	else if (strncmp(sendline,"19",2)==0)
	                        	{
	                        		write(new_fd, MAGENTA "\n\nBro do you even meme?\n\n" RESET, strlen(MAGENTA "\n\nBro do you even meme?\n\n" RESET));
	                        		nz=0;
	                        		exit(1);
	                        		break;
	                        	}
	                        	else if (strncmp(sendline,"21",2)==0)
	                        	{
	                        		write(new_fd,MAGENTA "\n\nSpell it for me bro plsss\n\n" RESET,strlen(MAGENTA "\n\nSpell it for me bro plsss\n\n" RESET));
	                        		nz=0;
	                        		exit(1);
	                        		break;

	                        	}
	                        	else{
			                      	write(new_fd, MAGENTA "\n\nHE NEED SOME MILKKK!\n\n" RESET,strlen(MAGENTA "\n\nHE NEED SOME MILKKK!\n\n" RESET));
		                            nz=0;
		                            exit(1);
		                            break;
	                        	}
                    	}
                        else if(strncmp(sendline,"g43Dn{Sarce}emsg_Evm3ei",23)==0)
                        {
                            write(new_fd, RED "\n\nBANG !! .....YOURE A DEAD\n\n" RESET,strlen(RED "\n\nBANG !! .....YOURE A DEAD\n\n" RESET));
                            nz=0;
                            exit(1);
                            break;
                        }
                        else
                        {                            
                            write(new_fd, YELLOW "\n. . . .Mr. Turing is at platform 4\n" RESET,strlen(YELLOW "\n. . . .Mr. Turing is at platform 4\n" RESET));
                            nz=0;
                            exit(1);
                            break;
                        }
				}
				else if(strncmp(sendline,"",99)==0) //Concert the morse code and replace the answer to ""
				{	
					write(new_fd,"\n\nBEEP..BEEP...The number you're calling is not available\n\n", strlen("\n\nBEEP..BEEP...The number you're calling is not available\n\n"));
					nz=0;
					exit(1);
     				break;				
				}
				else{
					write(new_fd, RED "\n\nTry again. Call sampai angkat ! !\n\n\n" RESET,strlen(RED "\n\nTry again. Call sampai angkat ! !\n\n\n"RESET));
					nz=0;
					exit(1);
     				break;
				}
			nz=0;
			close(new_fd);
			break;	
		}
		close(new_fd);
	}
	close(new_fd);
	close(sockfd);	
	return 0;
}


