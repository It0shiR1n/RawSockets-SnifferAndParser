// REMEBER TO PUT YOUR NIC IN TO A PROMISCUOUS MODE
// Exists a tool called cscope, learn how to use then.

// Continue from this Vídeo: https://youtu.be/DhI62V2iOBM?list=PL9ueu6QbfMC3SYOBOkDHed09gnsGlhfVl

#include <stdio.h>            // For printf and standard I/O functions
#include <stdlib.h>           // For exit function
#include <string.h>           // For bzero and strncpy functions
#include <unistd.h>           // For close function
#include <sys/socket.h>       // For socket functions
#include <linux/if_ether.h>   // For ETH_P_IP and Ethernet header definitions
#include <linux/if_packet.h>  // For sockaddr_ll and packet interface definitions
#include <net/if.h>           // For struct ifreq and interface names
#include <sys/ioctl.h>        // For ioctl function


int bindRawSocketToIface(char *device, int sockfd, int protocol){
    struct sockaddr_ll iface;          // Define uma estrutura para receber
    struct ifreq ifaceRequisition;     // Define uma requisição de interface

    bzero(&iface, sizeof(iface));                         //| - Poupalate the memory space with zeros (to avoid more problems with chars)
    bzero(&ifaceRequisition, sizeof(ifaceRequisition));   //|

    strncpy((char *) ifaceRequisition.ifr_name, device, IFNAMSIZ); // movimenta o valor de Device para ifr_name de tamanho "IFNAMSIZ" (Adiciona a placa de rede)

    if((ioctl(sockfd, SIOCGIFINDEX, &ifaceRequisition)) == -1 ){
        printf("Error to get the interface index! \n");
        exit(-1);
        
    }

    return 0;
    
}


void printHexDump(unsigned char *packet, int len){
    unsigned char *p = packet;

    printf("-----------------------------\n");    
    
    while(len--){
        printf("%.2x", *p);
        p++;
        
    }
    
    printf("\n-----------------------------\n");    
    
}


int main(){ 
    int sockfd;                                             // Socket descriptor
    unsigned char packet_buffer[2048];                      // Buffer to receive packet

    int len; 
    int packet_to_sniff;
    struct sockaddr_ll packet_info;                         // Informations of the packets provided by the kernel
    unsigned int packet_info_size = sizeof(packet_info_size);

    
    // Creating the Raw Socket
    sockfd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP));

    if(sockfd == -1){
        printf("Error in socket creation");
        exit(-1);
        
    }

    bindRawSocketToIface("enp0s3", sockfd, ETH_P_IP);

    packet_to_sniff = 1;

    while(packet_to_sniff--){
        if((len = recvfrom(sockfd, packet_buffer, 2048, 0, (struct sockaddr *)&packet_info, &packet_info_size)) == -1 ) {
            printf("Error in recvfrom");
            exit(-1);
            
        }else {
            printHexDump(packet_buffer, len);
            
        }
        
    }
    

    // how much packets do you want sniff?
    
}