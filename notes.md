
The follow image is the architecture network inside the operating system kernel, based with this 
we can get a better understanding to follow up in our studys.

![alt text](/images/architecture.png)

https://youtu.be/LNN3ZY632CM?list=PL9ueu6QbfMC3SYOBOkDHed09gnsGlhfVl



The Raw sockets is a resource that permits you to manufacture packets and inject into the 
network, also permits you to receive the packets from the network, rougly speaking is a network
resource that permits you to bypass the network stack and receive/deliver packets directly to 
the applicaiton.


**Unix like uses Sockets from Berkley**
- PF_PACKET
    - *Send/Receive packets at the Layer 2 of the OSI*
    - *All packets receive will be complete with headers and data*
    - *All packets send will be transmited without modifications by kerrnel*
    - *Supports filtering using Berkley Packets Filterring*
    


**Libs Necessary**
- stdio.h


**Commands**
- socket()     -> Create a socket
- bind()       -> Set the socket intoa interface (remebet to put the interface on promiscuous mode)
- recvfrom()   -> Receive packets on the socket
- sendto()     -> Send packet on the socket
- close()      -> close the socket

