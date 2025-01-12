#include <stdio.h>

void parseIP(unsigned char *packetIP){

    unsigned char IPVersion = (packetIP[14] >> 4) & 0x0F;
    unsigned short IHL = packetIP[14] & 0x0F;
    unsigned short ToS = packetIP[15]; 

    unsigned char TotalLengthData[2] = {packetIP[16], packetIP[17]}; 
    unsigned short TotalLength = (TotalLengthData[0] << 8) | TotalLengthData[1];

    unsigned char IdentificationData[2] = {packetIP[18], packetIP[19]};
    unsigned short Identification = (IdentificationData[0] << 8) | IdentificationData[1];

    unsigned short Flags = (packetIP[20] >> 5); // 20

    unsigned char OffsetData[2] = {packetIP[20], packetIP[21]};
    unsigned short Offset = (OffsetData[0] << 3) | OffsetData[1];

    unsigned char TTL = packetIP[22];
    unsigned short Protocol = packetIP[23];

    unsigned char HeaderChecksumData[2] = {packetIP[24], packetIP[25]};
    unsigned short HeaderChecksum = (HeaderChecksumData[0] << 8) | HeaderChecksumData[1];


    // ----------------------------------------------------------------------------

    printf("[+] Version: %x\n", IPVersion);
    printf("[+] IHL: %d\n", IHL);
    

    if(((ToS >> 2) & 0x0F) == 0x07)
        printf("[+] ToS (Formated): NetworkControl\n[+] ToS (Bytes): 0x%x\n", ToS);
    
    else if(((ToS >> 2) & 0x0F) == 0x06)
        printf("[+] ToS (Formated): InterNetworkControl\n[+] ToS (Bytes): 0x%x\n", ToS);
    
    else if(((ToS >> 2) & 0x0F) == 0x05)
        printf("[+] ToS (Formated): CriticECP\n[+] ToS (Bytes): 0x%x\n", ToS);
    
    else if(((ToS >> 2) & 0x0F) == 0x04)
        printf("[+] ToS (Formated): FlashOverride\n[+] ToS (Bytes): 0x%x\n", ToS);
    
    else if(((ToS >> 2) & 0x0F) == 0x03)
        printf("[+] ToS (Formated): Flash\n[+] ToS (Bytes): 0x%x\n", ToS);
    
    else if(((ToS >> 2) & 0x0F) == 0x02)
        printf("[+] ToS (Formated): Immediate\n[+] ToS (Bytes): 0x%x\n", ToS);

    else if(((ToS >> 2) & 0x0F) == 0x01)
        printf("[+] ToS (Formated): Priority\n[+] ToS (Bytes): 0x%x\n", ToS);
    
    else if(((ToS >> 2) & 0x0F) == 0x00)
        printf("[+] ToS (Formated): Routine\n[+] ToS (Bytes): 0x%x\n", ToS);
    
    else
        printf("[-] Some error occurs");


    printf("[+] Total Length: %d\n", TotalLength);
    printf("[+] Identification (Integer): %d\n", Identification);

    if(Flags == 0x2)
        printf("[+] Flags: Don't Fragment\n");

    else if(Flags == 0x1)
        printf("[+] Flags: More Fragments\n");

    else if(Flags == 0x0)
        printf("[+] Flags: May Fragment and Last Fragments\n");
    
    printf("[+] Fragment Offset: 0x%04x\n", Offset);
    printf("[+] TTL: %d\n", TTL);

    
    if(Protocol == 0x06){
        printf("[+] Protocol: TCP\n");
        printf("[+] Protocol (Bytes): 0x%04x\n", Protocol);

    }else if(Protocol == 0x11){
        printf("[+] Protocol: UDP\n");
        printf("[+] Protocol (Bytes): 0x%04x\n", Protocol);

    }
    
    printf("[+] Header Checksum: 0x%x\n", HeaderChecksum);

    printf("[+] Destination Address: %d.%d.%d.%d\n", packetIP[26], packetIP[27], packetIP[28], packetIP[29]);
    printf("[+] Source Address: %d.%d.%d.%d\n", packetIP[30], packetIP[31], packetIP[32], packetIP[33]);
    

}