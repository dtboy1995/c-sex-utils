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
#include <openssl/crypto.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#define CONNECTED 1
#define DISCONNECTED 0
#define OK 1
#define NO -1
#define SUCCESS 1
#define FAILED 0

const char * HTTP_BR = "\r\n\r\n";

int get_mac_by_name(char *mac, char* if_name);

int get_connection_state(char *domain_name);

int http_get(char *domain, char * url, int port, char * res, int res_len);

int https_get(char *domain, char * url, int port, char * res, int res_len);

char* get_res_body(char* res);