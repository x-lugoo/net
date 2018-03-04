#include <stdio.h> // for printf(),perror()
#include <stdlib.h>// for exit()
#include <unistd.h> // for write()
#include <string.h> // for strncpy()
#include <netinet/in.h> //for htons()
#include <net/if.h> // for IFNAMSIZ

int main(int argc,char **argv)
{
	char ifname[IFNAMSIZ] = {0};
	int sock;
	int oval = 1;
	int ovlen;
	
	if(argc == 1)
		strcpy(ifname,"lo");
	else 
		strncpy(ifname,argv[1],IFNAMSIZ-1);
	sock = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if(sock < 0){
		perror("socket");
		exit(1);
	}
	ovlen = sizeof(oval);
	if(setsockopt(sock,SOL_SOCKET,SO_BROADCAST,&oval,ovlen) < 0){
		perror("setsockopt broadcast");
		exit(1);
	}	

	if(setsockopt(sock,SOL_SOCKET,SO_BINDTODEVICE,&ifname,IFNAMSIZ) < 0){
		perror("setsockopt bindtodevice");
		exit(1);
	}
	int ttl = 5;
	int tlen = sizeof(ttl);
	if(setsockopt(sock,SOL_IP,IP_TTL,&ttl,tlen) < 0){
		perror("setsockopt SOL_IP");
		exit(1);
	}
	struct sockaddr_in saddr;
	socklen_t salen = sizeof(saddr);
	bzero(&saddr,salen);
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(0);
	saddr.sin_addr.s_addr= htonl(INADDR_BROADCAST);
	if(connect(sock,(sockaddr*)&saddr,salen) < 0){
		perror("connect");
		exit(1);
	}
	char msg[] = "This a demo from jeff\n";
	int len = sizeof(msg);
	int tx  = write(sock,msg,len);
	if(tx < 0){
		perror("write");	
		exit(1);
	}

	printf("wrote %d bytes to interface\'%s\' \n",tx,ifname);
	return 0;
}













