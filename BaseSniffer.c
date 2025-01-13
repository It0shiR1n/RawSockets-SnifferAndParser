#include <stdio.h>            
#include <stdlib.h>           
#include <string.h>           
#include <unistd.h>           
#include <sys/socket.h>       
#include <linux/if_ether.h>   
#include <linux/if_packet.h>  
#include <net/if.h>            
#include <sys/ioctl.h>        

#include "ParsingPacketsETH.h"
#include "ParsingPacketsIP.h"
#include "ParsingPacketsTCP.h"
#include "ParsingPacketsUDP.h"


int bindRawSocketToIface(char *device, int sockfd, int protocol){
    struct sockaddr_ll iface;          
    struct ifreq ifaceRequisition;     

    bzero(&iface, sizeof(iface));                         
    bzero(&ifaceRequisition, sizeof(ifaceRequisition));   

    strncpy((char *) ifaceRequisition.ifr_name, device, IFNAMSIZ); 

    if((ioctl(sockfd, SIOCGIFINDEX, &ifaceRequisition)) == -1 ){    
        printf("Error to get the interface index! \n");
        exit(-1);
        
    }

    return 0;
    
}



int main(){ 
    int sockfd;                                             
    unsigned char packet_buffer[1024];                      

    int confirming; 
    int packet_to_sniff;

    struct sockaddr_ll packet_info;                         
    unsigned int packet_info_size = sizeof(packet_info_size);

    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));  

    if(sockfd == -1){
        printf("Error in socket creation");
        exit(-1);
        
    }

    bindRawSocketToIface("enp3s0", sockfd, ETH_P_IP);
    packet_to_sniff = 1;

    while(packet_to_sniff--){
        if((confirming = recvfrom(sockfd, packet_buffer, 1024, 0, (struct sockaddr *)&packet_info, &packet_info_size)) == -1 ) {
            printf("Error in recvfrom");
            exit(-1);
            
        }else {
        
            unsigned char *p = packet_buffer;
            

            printf("\n----------------------------- Ethernet Header\n");    
            parseETH(packet_buffer);
        
            printf("\n----------------------------- IP Header\n");    
            parseIP(packet_buffer);
            

            if(packet_buffer[23] == 0x06){
                printf("\n----------------------------- TCP Header\n");    
                parseTCP(packet_buffer);

            }else if(packet_buffer[23] == 0x11){
                printf("\n----------------------------- UDP Header\n");    
                parseUDP(packet_buffer);

            }

            printf("\n----------------------------- RAW Bytes\n");    
            
            while(confirming--){
                printf("0x%x ", *p);
                p++;
                
            }

            printf("\n-----------------------------\n");   

        }
    }
}
