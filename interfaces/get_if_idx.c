#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <netinet/in.h>

/*
struct ifreq;
j
   */
int main(int argc,char *argv[])
{
	struct ifreq ifr;
	char *eth = "ens33";
	int fd;
	struct sockaddr_in sin;
	 char mac[20] = {0};

	memset(&ifr,0,sizeof(ifr));
	if(argc > 1) eth = argv[1];
	fd = socket(AF_INET,SOCK_DGRAM,0);
	if(fd == -1)
		return -1;
	strncpy(ifr.ifr_name,eth,sizeof(ifr.ifr_name));

/*	if(ioctl(fd,SIOCGIFINDEX,&ifr) == -1)
		return -1;
	memcpy(&sin,&ifr.ifr_netmask,sizeof(sin));
	printf("%s->%d\n,netmask=%s\n",eth,ifr.ifr_ifindex,inet_ntoa(sin.sin_addr));
	*/
	if(ioctl(fd,SIOCGIFHWADDR,&ifr) == -1)
		return -1;
	memcpy(mac,ifr.ifr_hwaddr.sa_data,IFHWADDRLEN);
	for(int i = 0;i < IFHWADDRLEN;i++){
		printf("%02X ",(unsigned char)(mac[i]));
	}

	return 0;
}

	
