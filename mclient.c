
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>


int main(int argc,char *argv[])

{

  int sock, readn,writen,received;  
  int send_data[5],recv_data[5],h1,h2;
	 char *servIP;
	 unsigned short clport;
        struct hostent *host;
        struct sockaddr_in server_addr;
	//	printf("%c",argv[1]);  
	//	servIP=argv[0];
	 host = gethostbyname(argv[1]);

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }
        clport=atoi(argv[2]);

        server_addr.sin_family = AF_INET;     
        server_addr.sin_port = htons(clport);   
        server_addr.sin_addr =*((struct in_addr *)host->h_addr);
        bzero(&(server_addr.sin_zero),8); 

        if (connect(sock, (struct sockaddr *)&server_addr,
                    sizeof(struct sockaddr)) == -1) 
        {
            perror("Connect");
            exit(1);
        }
	if(argc<3)
	  {
	    printf("\n Entered the wrong choice");
	  }
	else if(argc == 5)
	  {
	    if(atoi(argv[3])==1)
	      {
		send_data[0]=1;
		send_data[1]=atoi(argv[4]);
	      
            writen=write(sock,send_data,5*sizeof(int));
	      }
	  }
	else if(argc == 6)
	  {
	    if(atoi(argv[5])== 0)
	      {
                send_data[0]=3;
                send_data[1]=atoi(argv[4]);
		send_data[2]=1;
		writen=write(sock,send_data,5*sizeof(int));
		readn=read(sock,recv_data,5*sizeof(int));
		if(recv_data[0]>0)
		  {
	printf(" Sum is %d",recv_data[0]);
		  }
		else
		  {
		    printf("For this client,Memory has not yet been created\n");                 }
	      }
	    
	    else if(0<atoi(argv[5]) && atoi(argv[5])<=32767)
	     {
	       send_data[0]=2;
	       send_data[1]=atoi(argv[4]);
	       send_data[2]=atoi(argv[5]);
	       writen=write(sock,send_data,5*sizeof(int));
		  writen=write(sock,send_data,5*sizeof(int));
		  readn=read(sock,recv_data,5*sizeof(int));
		  if(recv_data[0]==0)
		    {
		      printf("server has created required memory and filled the numbers");
		   }
		  else
		    {
		      printf("\n Server coold not create the memory");
		    }
	     
	     }
	  }
	    //	printf("\n you have entered the wrong arguments");
	      
	      else  if(argc == 4)
	      {
		if(atoi(argv[3])==4)
		  {
		    send_data[0]=0;
		    writen=write(sock,send_data,5*sizeof(int));
		  }
		else
		  {
		    printf("You have enetered the wrong arguments");
		  }
	      }

	      else
		{
		  printf("You have entered the wrong arguments");
		}

	    
	/*
	send_data[0]=3;
       
	writen=write(sock,send_data,sizeof(int));
	readn=read(sock,recv_data,sizeof(int));
 
	printf("\n %d",recv_data[0]); 
	*/  

           close(sock);
          
        
           

	   return 0;
}
