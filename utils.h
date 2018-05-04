#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <time.h>

#ifndef C_UTILS_UTILS_H
#define C_UTILS_UTILS_H
#endif

#define CONNECTED 1
#define DISCONNECTED 0
#define OK 1
#define NO -1
#define SUCCESS 1
#define FAILED 0

int get_mac_by_name(char *mac, char* if_name);

int get_connection_state(char *domain_name);

int http_get(char *domain, char * url, int port, char * res, int res_len);