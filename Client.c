/*
	C ECHO client example using sockets
*/
#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
#include <unistd.h>   //gethostname
#include <netdb.h>   //gethostbyaddress
#include <sys/types.h>

const int MAX_HOSTNAME = 255;

int main(int argc , char *argv[])
{
	int sock , hname, i, j, cnt, addrLen, on=1;
	struct sockaddr_in localaddr, peeraddr, addr;
	int la_len, ret, retrn, pa_len;
	char hostbuffer[MAX_HOSTNAME+1];
	struct hostent *hp;
	struct servent *sp;
	char buffer[512];
	
	//char message[1000] , server_reply[2000];
	
	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("The Socket cannot be created due to certain error that can't be identified");
	}
	puts("Socket created");
	
	/*/1. Using getsockname to gather the local address information for a socket
	la_len = sizeof(localaddr);
	ret = getsockname( sock, (struct sockaddr_in *)&localaddr, &la_len );
	
	if (ret == 0) {
	  printf( "Local Address is : %s\n", inet_ntoa( localaddr.sin_addr ) );
	  printf( "Local Port is : %d\n", localaddr.sin_port );
	}
	*/
	//2. getting the host name
	hname = gethostname (hostbuffer, MAX_HOSTNAME);
	if (hname == 0){
			printf("The hostname is %s\n", hostbuffer);
	}
	
	//3. to identify the IP address given a fully qualified domain name
	hp = gethostbyname( "www.microsoft.com");
	
	if (hp){
		printf("h_name is %s\n", hp->h_name);
		printf("h_addrtype is %d\n", hp->h_addrtype);
		
		i=0;
		printf("Aliases: \n" );
		while(1){
			if ( hp->h_aliases[i] ) 
			{
				printf( "h_aliases[%d] = %s\n", i, hp->h_aliases[i] );
				i++;
			}
			else break;
		}
		
		i=0;
		printf( "Addresses:\n" );
		while (1) 
		{
			if ( hp->h_addr_list[i] ) 
			{
				struct in_addr theAddr;
				memcpy( &theAddr.s_addr, hp->h_addr_list[i], sizeof(theAddr.s_addr) );
				printf( "  h_addr_list[%d] = %s\n", i, inet_ntoa( theAddr ) );
				i++;
			}
			else break;
		}
	}
	
	//4. Takes a service name and protocol and yields among other things
	sp = getservbyname( "smtp", "tcp" );

	if (sp) 
	{
	  printf( "s_name  = %s\n", sp->s_name );
	  printf( "s_port  = %d\n", ntohs(sp->s_port) );
	  printf( "s_proto = %s\n", sp->s_proto );

	  j = 0;
	  printf( "Aliases:\n" );
	  while (1) 
	  {
		if ( sp->s_aliases[j] ) 
		{
		  printf(" s_aliases[%d] = %s\n", j, sp->s_aliases[j] );
		  j++;
		} else break;
	  }

	}
	
	//5.  To identify the service and its characteristics given a port number
	sp = getservbyport(htons(80), NULL);
	if (sp)
	{
		printf("Service %s is at port %d\n", sp->s_name, ntohs( sp->s_port));
	}

	//Chapter 5
	//1. Permit a socket to send datagrams to a broadcast address
	sock = socket (AF_INET, SOCK_DGRAM, 0);
	
	//Permit sending broadcast datagrams
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(BCAST_PORT);
	addr.sin_addr.s_addr = inet_addr("255.255.255.255");
	addrLen = sizeof(addr);

	//send a broadcast datagram
	snt = sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr_in*)&addr, addrLen);

	//2. To disable the underlying routing algorithms for a  given socket.
	len = sizeof(val);
	ret = getsockopt(sock, SOL_SOCKET, SO_DONTROUTE, (void *)&val, &len);
	printf(" so_dontroute = %d\n", val);

	val = 1;
	ret = setsockopt(sock, SOL_SOCKET, SO_DONTROUTE, (void *)&val, sizeof(int));

	//3. so_error
	len = sizeof (val);
	ret = getsock(sock, SOL_SOCKET, SO_ERROR, (void *)&val, &len);
	printf("so_error = %d\n", val);

	//4.so_linger
	struct linger ling;

	ling.l_onoff = 1;
	ling.l_linger = 10;
	
	ret = setsockopt(sock, SOL_SOCKET, SO_LINGER, (void *) &ling, sizeof(ling));

	ret = close(sock);

	//5. so_keepalive
	sock = socket(AF_INET,SOCK_STREAM, 0);

	on = 1;
	ret = setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, (void*)&on, sizeof(on));
	/*server.sin_addr.s_addr = inet_addr("192.168.35.138");
	server.sin_family = AF_INET;
	server.sin_port = htons( 8080 );*/

	return 0;
}
