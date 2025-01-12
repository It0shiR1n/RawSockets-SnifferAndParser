#include <stdio.h>


void parseTCP(unsigned char *packetTCP){
    unsigned char SourcePortData[2] = {packetTCP[26], packetTCP[27]}; // 0x23 = 26 0xd7 = 27
    unsigned short SourcePort = (SourcePortData[0] << 8 ) | SourcePortData[1]; 

    unsigned char DestinationPortData[2] = {packetTCP[28], packetTCP[29]};
    unsigned short DestinationPort = (DestinationPortData[0] << 8) | DestinationPortData[1];


    unsigned char SequenceNumberData[4] = {packetTCP[30], packetTCP[31], packetTCP[32], packetTCP[33]};
    unsigned int SequenceNumber = (SequenceNumberData[0] << 24) | (SequenceNumberData[1] << 16) | SequenceNumberData[2] << 8 |  SequenceNumberData[3];

    unsigned char AcknowledgmentNumberData[4] = {packetTCP[34], packetTCP[35], packetTCP[36], packetTCP[37]};
    unsigned int AcknowledgmentNumber = (AcknowledgmentNumberData[0] << 24) | (AcknowledgmentNumberData[1] << 16) | AcknowledgmentNumberData[2] << 8 |  AcknowledgmentNumberData[3];

    unsigned char DataOffset = (packetTCP[38] >> 4) & 0x0F;
    //unsigned char Reserved = (char) *"0";

    unsigned char FlagsBits = packetTCP[39] & 0x3F;

    unsigned char WindowData[2] = {packetTCP[40], packetTCP[41]};
    unsigned short Window = (WindowData[0] << 8) | WindowData[1];
    
    unsigned char ChecksumData[2] = {packetTCP[42], packetTCP[43]};
    unsigned short Checksum = (ChecksumData[0] << 8) | ChecksumData[1];
    
    unsigned char UrgentPointerData[2] = {packetTCP[44], packetTCP[45]};
    unsigned short UrgentPointer = (UrgentPointerData[0] << 8) | UrgentPointerData[1];


    printf("[+] Source Port: %d\n", SourcePort);
    printf("[+] Destination Port: %d\n", DestinationPort);
    printf("[+] Sequence Number: %d\n", SequenceNumber);
    printf("[+] Acknowledgment Number: %d\n", AcknowledgmentNumber);
    printf("[+] Data Offset: %x\n", DataOffset);
    printf("[+] Reserved: 0\n");


    if(FlagsBits == 0x08){
        printf("[+] Flags: SYN\n");
        printf("[+] Flags (Bytes): 0x8\n");

    }else if(FlagsBits == 0x48){
        printf("[+] Flags: SYN + ACK\n");
        printf("[+] Flags (Bytes): 0x48\n");

    }else if(FlagsBits == 0x40){
        printf("[+] Flags: ACK\n");
        printf("[+] Flags (Bytes): 0x40\n");

    }else if(FlagsBits == 0x60){
        printf("[+] Flags: PSH + ACK\n");
        printf("[+] Flags (Bytes): 0x60\n");

    }else if(FlagsBits == 0x44){
        printf("[+] Flags: FIN + ACK\n");
        printf("[+] Flags (Bytes): 0x44\n");

    }else if(FlagsBits == 0x10){
        printf("[+] Flags: RST\n");
        printf("[+] Flags: 0x10\n");

    }else if(FlagsBits == 0xc0){
        printf("[+] Flags: URG + ACK\n");
        printf("[+] Flags (Bytes): 0xc0\n");

    }else {
        printf("[+] Flags: Broken packet\n");

    }

    printf("[+] Window: %d\n", Window);
    printf("[+] Checksum: 0x%04x\n", Checksum);
    printf("[+] Urgent Pointer: %d\n", UrgentPointer);

}