#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>


//char *server = "47.91.206.25";
char *server = "127.0.0.1";
int port = 8888;

int main(void)
{
	int fd;
	int rc;
	struct sockaddr_in sin;
	char *buf = "hello";
	int buflen = strlen(buf);

	fd = socket(AF_INET,SOCK_STREAM,0);
	
	if(fd == -1){
		printf("socket:%s\n",strerror(errno));
		exit(-1);
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr(server);
	sin.sin_port = htons(port);
	if(sin.sin_addr.s_addr == INADDR_NONE){
		printf("invalid remote ip%s\n",server);
		exit(-1);
	}
	if(connect(fd,(struct sockaddr*)&sin,sizeof(sin)) == -1){
		printf("connect: %s\n",strerror(errno));
		exit(-1);
	}
	if((rc = write(fd,buf,buflen)) != buflen){
		printf("write:%s\n",(rc < 0)?strerror(errno):"incomplete");
		exit(-1);
	}
	return 0;
}


