//
//
#include "utils.h"

int get_connection_state(char *domain_name) {
    int i = 0;
    while (i < 1000) {
        pid_t pid;
        if ((pid = vfork()) < 0) {
            perror("create socket fail\n");
            return DISCONNECTED;
        } else if (pid == 0) {
            if (execlp("ping", "ping", "-c", "1", domain_name, (char *) 0) < 0) {
                //
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

int get_mac(char *mac) {
    struct ifreq tmp;
    int sock_mac;
    char mac_addr[30];
    sock_mac = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_mac == -1) {
        perror("create socket fail\n");
        return -1;
    }
    memset(&tmp, 0, sizeof(tmp));
    strncpy(tmp.ifr_name, IF_INTERFACE_NAME, sizeof(tmp.ifr_name) - 1);
    if ((ioctl(sock_mac, SIOCGIFHWADDR, &tmp)) < 0) {
        perror("mac ioctl error\n");
        return -1;
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
    return 1;
}

int main() {
    return 0;
}