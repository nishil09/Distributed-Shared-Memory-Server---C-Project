#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include<sys/mman.h>
#include<sys/ipc.h>

//int data[100];
char *ptr,*temp;
int size=0;
int sum=0;
int main(int argc,char *argv[])
{
  int sock, connected, readn,writen , true = 1,received,pipefd[2];  
  int send_data[5],recv_data[5],data[100][1000],buff[100][1000];
  int x,y,shmid[20];
  for(x=0;x<100;x++)
    {data[x][0]=-1;
      buff[x][0]=-1;
      buff[x][1]=-1;
       data[x][1]=-1;
    }
  //int temp=-1;       
 //    pipe(pipefd);
         
        struct sockaddr_in server_addr,client_addr;    
        int sin_size,j=0,count=0,clientnum;
        pid_t pid;
        srand(time(NULL));
        unsigned short servport;
        if((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("Socket");
            exit(1);
        }

        if(setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int)) == -1) {
            perror("Setsockopt");
            exit(1);
        }
        servport=atoi(argv[1]);
        server_addr.sin_family = AF_INET;         
        server_addr.sin_port = htons(servport);     
        server_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(server_addr.sin_zero),8); 

        if(bind(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))
                                                                       == -1) {
            perror("Unable to bind");

	    exit(1);
        }
     
        if(listen(sock, 5) == -1) {
            perror("Listen");
	      exit(1);
        }
	for(x=0;x<20;x++)
	  {
	shmid[x]=shmget(0x0001 + x,sizeof(int)*1000,IPC_CREAT|0666);
	if(shmid<0)
	  {
	    printf("shm failed\n");
	    exit(1);
	  }
	ptr=(char *)shmat(shmid[x],NULL,0);
        ptr[x]=-1;
	  }	
	printf("\nTCPServer Waiting for client");
	   fflush(stdout);


	  
	   // if(writen=write(pipefd[1],buff,100*1000*sizeof(int))<0)
	   // {
	   // printf("Error in pipe");
	   // }

            sin_size = sizeof(struct sockaddr_in);
	    //	    close(sock);
	    while(1)
	      {
		//    	connected=accept(sock,(struct sockaddr *)&client_addr,&sin_size);
		//	close(sock);
			pid=fork();
		  
		    if(pid<0)
		      { 
			printf("\n Fork error");
		      }
		    else
		      {
				 connected = accept(sock, (struct sockaddr *)&client_addr,&sin_size);
				 //	 	close(sock);
            printf("\n I got a connection \n");
       
	      
	    readn=read(connected,recv_data,5*sizeof(int));
	   
	    if(recv_data[0]==0)
	      { // printf("hi       %d",*count);
		printf("Server is Terminating......Terminated!!");
		int k=shmdt(ptr);
		for(x=0;x<20;x++)
		  {
		    k=shmctl(shmid[x],IPC_RMID,0);
		  }

		//	break; 
		//		close(connected);
		break;
			//	break;
		///		close(sock);
				//	exit(0);
			//	break;

		// return 0;
	      
             }
           else if(recv_data[0]==1) 
	     {

	       //  readn=read(pipefd[0],data,100*1000*sizeof(int));
		//	data=buff;
		clientnum=recv_data[1];
		ptr=(char *)shmat(shmid[clientnum],NULL,0);
	       if(ptr[0]!=clientnum)
		   {
		     printf("\n There isn No memory for client %d \n",clientnum);
		     // writen=write(pipefd[1],data,100*1000*sizeof(int));
		     //  close(connected);
		   }
             
           	     
	       else
		 {  
		   printf("\n Memory for client number %d is \n",clientnum);   
			   
			j=1; 
                     while(ptr[j]!=-1)
		       {
                           printf("\n %d",ptr[j]);
                          j++;
                         }
		     // close(connected);
		     //  writen=write(pipefd[1],data,100*1000*sizeof(int));
		     // exit(0);
	          }
		  
	     }		      
	     
		      
		      
	      
          else if(recv_data[0]==3)
	    { 
              clientnum=recv_data[1];
	      ptr=(char *)shmat(shmid[clientnum],NULL,0);
	      //	  readn=read(pipefd[0],data,100*1000*sizeof(int));
		  // data=(int *)buff;
	         
		//	printf("HhhhHHHHHHH");
	       if(ptr[clientnum]==-1)
		 {printf("\nMemory for client %d is  not created",clientnum);
		  //readn=read(pipefd[0],buff,100*1000*sizeof(int));
		  send_data[0]=0;
		  writen=write(connected,send_data,5*sizeof(int));
		  // printf("\nSum for client  %d  is sent\n",clientnum);
		  // writen=write(pipefd[1],data,100*1000*sizeof(int));
		  //  close(connected);
		}
	      else
		{
		  j=1;
		  sum=0;
                  while(ptr[j]!=-1)
		    {
		      sum=sum+ptr[j];
		      // printf("\n %d",ptr[j]);
		      j++;
		    }
		  send_data[0]=sum;
		  printf("Sum for client %d is sent",clientnum);
		  writen=write(connected,send_data,5*sizeof(int));
		  // close(connected);
		  // printf("\n Sum for client %d is sent",clientnum);
		  //  writen=write(pipefd[1],data,100*1000*sizeof(int));
		}

             
 
		  
	    }
		      
 

              else if(recv_data[0]==2)
               {
		 // printf("\n bsdhbsdb\n");
		 //	 readn=read(pipefd[0],buff,100*1000*sizeof(int));
		     if(1)
		       {
			 ptr=(char *)shmat(shmid[recv_data[1]],NULL,0);
               size=recv_data[2];
	    
	       // data=(int *)malloc(100*(size+2)*(sizeof(int)));
	       printf("\n Created memory for client %d is below:",recv_data[1]);
	       j=1;
	       ptr[0]=recv_data[1];
	       // printf("\n %d \n",ptr[0]);
               while(j<size+1)
                {
                ptr[j]=rand()%100;
                printf("\n %d",ptr[j]);
               j++;
               }
               ptr[size+1]=-1;
            
       
               printf("\n Memory has been filled with the data for client %d\n",recv_data[1]);
	       send_data[0]=0;
	       writen=write(connected,send_data,5*sizeof(int));
	       // close(connected);
	       //	       if(writen=write(pipefd[1],data,100*1000*sizeof(int))<0)
	       // {
	       //  printf("pipe error");
	       // } 
	       // *count=1;
	       //  send_data[0]=0;
		//  printf("hey %d",count);
	       //        writen=write(connected,send_data,5*sizeof(int));
		//		exit(0);
		       }
		     else
		       {
			 printf("\n Sorry! Server has no data for this client\n");
			 //	 close(connected);
		       }
	       }
               
             else
               {
               printf("Client has sent wrong arguments");
	       //   close(connected);
               }

 
	      close(connected);
		  // exit(0);
		      }
		  
	      }
	    //	    close(connected);
	    //	    x=shutdown(sock,SHUT_RDWR);
	      close(sock);
	     // exit(0);
	     //  return 0;
}


