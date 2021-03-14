#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <arpa/inet.h>

int hn2ip(char *hostname, char *ip);

int main(int argc, char **argv){
	char *hostname;
	char ip[256];

	if( argc<2 ){
		fprintf(stderr, "usage: %s <hostname>\n", argv[0]);
		exit(1);
	}

	hostname = argv[1] ;
	hn2ip(hostname, ip);
	printf("%s", ip);
	return 0 ;
}

int hn2ip(char *hostname, char *ip){
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if(!( he = gethostbyname(hostname) )){
		herror("gethostbyname");
		return 1 ;
	}

	addr_list = (struct in_addr **)he->h_addr_list ;
	for( i=0 ; addr_list[i] ; ++i ){
		strcpy( ip, inet_ntoa(*addr_list[i]) );
		return 0 ;
	}

	return 1 ;
}
