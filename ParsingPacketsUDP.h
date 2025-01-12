#include <stdio.h>

void parseUDP(unsigned char *packetUDP){
    unsigned char SourcePortData[2] = {packetUDP[26], packetUDP[27]};
    unsigned short SourcePort = (SourcePortData[0] << 8) | SourcePortData[1];

    unsigned char DestinationPortData[2] = {packetUDP[28], packetUDP[29]};
    unsigned short DestinationPort = (DestinationPortData[0] << 8) | DestinationPortData[1];

    unsigned char LengthData[2] = {packetUDP[30], packetUDP[31]};
    unsigned short Length = (LengthData[0] << 8) | LengthData[1];

    unsigned char ChecksumData[2] = {packetUDP[32], packetUDP[33]};
    unsigned short Checksum = (ChecksumData[0] << 8) | ChecksumData[1];

    printf("[+] Source Port: %d\n",SourcePort);
    printf("[+] Destination Port: %d\n", DestinationPort);
    printf("[+] Length: %d\n", Length);
    printf("[+] Checksum: 0x%04x\n", Checksum);
 
}