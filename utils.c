#include "utils.h"

int http_get(char *domain, char *url, int port, char *res, int res_len) {

    char text[4096];
    char request_line[128];
    char header_host[256];

    sprintf(request_line, "GET http://%s:%d%s HTTP/1.1\r\n", domain, port, url);
    sprintf(header_host, "Host: %s:%d\r\n", domain, port);
    strcat(text, request_line);
    strcat(text, "Accept: */*\r\n");
    strcat(text, header_host);
    strcat(text, "Connection: Close\r\n");
    strcat(text, "\r\n");

    printf("%s\n", text);

    int sock_fd;

    struct sockaddr_in addr_serv;
    // getnameinfo
    struct hostent *host_info = gethostbyname(domain);

    bzero(&addr_serv, sizeof(addr_serv));
    addr_serv.sin_family = AF_INET;
    addr_serv.sin_port = htons(port);
    memcpy(&addr_serv.sin_addr, &(*host_info->h_addr_list[0]), host_info->h_length);

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        perror("sock error\n");
    } else {
        printf("socket created\n");
    }

    if (connect(sock_fd, (struct sockaddr *) (&addr_serv), sizeof(addr_serv)) < 0) {
        perror("connect error\n");
    } else {
        printf("connecting\n");
    }

    if (send(sock_fd, text, strlen(text), 0) < 0) {
        perror("send error\n");
    } else {
        if (recv(sock_fd, res, res_len, 0) < 0) {
            perror("receive error\n");
        } else {
            return SUCCESS;
        }
    }
    close(sock_fd);
    return FAILED;
}

int get_connection_state(char *domain_name) {
    int i = 0;
    while (i < 1000) {
        pid_t pid;
        if ((pid = vfork()) < 0) {
            perror("vfork error\n");
            return DISCONNECTED;
        } else if (pid == 0) {
            if (execlp("ping", "ping", "-c", "1", domain_name, (char *) 0) < 0) {
                perror("execlp error\n");
                return DISCONNECTED;
            }
        }
        int stat;
        waitpid(pid, &stat, 0);
        if (stat == 0) {
            return CONNECTED;
        }
        sleep(1);
        i++;
    }
    return DISCONNECTED;
}

int get_mac(char *mac, char *if_name) {
    struct ifreq tmp;
    int sock_mac;
    char mac_addr[30];
    sock_mac = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_mac == -1) {
        perror("create socket fail\n");
        return NO;
    }
    memset(&tmp, 0, sizeof(tmp));
    strncpy(tmp.ifr_name, if_name, sizeof(tmp.ifr_name) - 1);
    if ((ioctl(sock_mac, SIOCGIFHWADDR, &tmp)) < 0) {
        perror("mac ioctl error\n");
        return NO;
    }
    sprintf(mac_addr, "%02x%02x%02x%02x%02x%02x",
            (unsigned char) tmp.ifr_hwaddr.sa_data[0],
            (unsigned char) tmp.ifr_hwaddr.sa_data[1],
            (unsigned char) tmp.ifr_hwaddr.sa_data[2],
            (unsigned char) tmp.ifr_hwaddr.sa_data[3],
            (unsigned char) tmp.ifr_hwaddr.sa_data[4],
            (unsigned char) tmp.ifr_hwaddr.sa_data[5]
    );
    close(sock_mac);
    memcpy(mac, mac_addr, strlen(mac_addr));
    return OK;
}

int main() {
    return 0;
}
