#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>


#define BUFSZ 200
int port = 8888;

int main(void)
{
	int fd;
	int rc;
	struct sockaddr_in sin;
	struct sockaddr_in cin;
	char buf[BUFSZ];

	fd = socket(AF_INET,SOCK_STREAM,0);
	
	if(fd == -1){
		printf("socket:%s\n",strerror(errno));
		exit(-1);
	}
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);
	sin.sin_port = htons(port);
	if(bind(fd,(struct sockaddr*)&sin,sizeof(sin)) == -1){
			printf("bind:%s\n",strerror(errno));
			exit(-1);
	}
	if(listen(fd,1) == -1){
		printf("listen:%s\n",strerror(errno));
		exit(-1);
	}

	printf("bind fd=%d\n",fd);
	while(1){
	socklen_t cli_sz = sizeof(cin);
	int fa = accept(fd,(struct sockaddr*)&cin,&cli_sz);
	printf("accept return fd=%d\n",fa);
	if(fa == -1){
		printf("accept:%s\n",strerror(errno));
		continue;
	}
	if(sizeof(cin) == cli_sz)
		printf("connetc from:%s:%d\n",inet_ntoa(cin.sin_addr),
				(int)ntohs(cin.sin_port));
				
	do{
		memset(buf,0,BUFSZ);
		rc = read(fa,buf,BUFSZ);
		if(rc == -1) printf("read:%s\n",strerror(errno));
		else if(rc == 0) printf("close\n");
		else printf("received %d bytes.content:%s\n",rc,buf);
	}while(rc > 0);
		close(fa);
	}
	return 0;
}



