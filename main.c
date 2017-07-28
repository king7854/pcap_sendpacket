#include <stdio.h>    //printf
#include <string.h>   //strncpy
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>   //ifreq
#include <unistd.h>   //close

unsigned char attackerMac[6];

void getAttackerMAC(){
    int fd;
    struct ifreq ifr;
    char *iface = "eth0";
    unsigned char *mac;

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    ifr.ifr_addr.sa_family = AF_INET;
    strncpy(ifr.ifr_name , iface , IFNAMSIZ-1);

    ioctl(fd, SIOCGIFHWADDR, &ifr);

    close(fd);



    //printf("Mac : %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n" , mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    //printf("Attacker Mac : ");
    for(int i=0; i<6; i++){
        attackerMac[i] = ifr.ifr_hwaddr.sa_data[i];
        //printf("%.2x", (unsigned char *)attackerMac[i]);
        //if(i!=5)
          //  printf(":");
    }
    printf("\n");
}

int main()
{
    getAttackerMAC();
    for(int i=0; i<6; i++){
        printf("%.2x", attackerMac[i]);
        if(i!=5)
            printf(":");
    }

    return 0;
}
