#include <stdio.h>
#include <stdint.h> 
#include <string.h>
#include <strings.h>


void parseETH(unsigned char *packetETH){
    
    unsigned short type;
    type = (packetETH[12] << 8) + packetETH[13];

    if (packetETH == NULL) {
        printf("the header was incomplete\n");
        return;

    }


    printf("[+] Source Mac Address: ");
    
    for(int i = 0; i <= 5; i++){
        printf("%x", packetETH[i]);
        
        if (i < 5) 
            printf(":");        

    }
    printf("\n");

    printf("[+] Destination Mac Address: ");
    
    for(int i = 6; i <= 11; i++){
        printf("%x", packetETH[i]);

        if(i < 11)
            printf(":");


    }
    printf("\n");


    printf("[+] Type: 0x%04x\n", type);

}