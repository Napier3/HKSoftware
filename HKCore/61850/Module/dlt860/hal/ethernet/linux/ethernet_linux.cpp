/*
 *  ethernet_linux.c
 */

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <poll.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "gsp_lib_memory.h"
#include "gsp_hal_ethernet.h"

#ifndef DEBUG_SOCKET
#define DEBUG_SOCKET 0
#endif

// 以太网数据
struct sGspEthernetSocket {
    int rawSocket;
    bool isBind;
    struct sockaddr_ll socketAddress;
};

// 以太网的数据集合
struct sGspEthernetHandleSet {
    struct pollfd *handles;
    int nhandles;
};

GspEthernetHandleSet
EthernetHandleSet_new(void)
{
    GspEthernetHandleSet result = (GspEthernetHandleSet) GLOBAL_MALLOC(sizeof(struct sGspEthernetHandleSet));

    if (result != NULL) {
        result->handles = NULL;
        result->nhandles = 0;
    }

    return result;
}

void
GspEthernetHandleSet_addSocket(GspEthernetHandleSet self, const GspEthernetSocket sock)
{
    if (self != NULL && sock != NULL) {

        int i = self->nhandles++;

        self->handles = (pollfd *)realloc(self->handles, self->nhandles * sizeof(struct pollfd));

        self->handles[i].fd = sock->rawSocket;
        self->handles[i].events = POLLIN;
    }
}

void
GspEthernetHandleSet_removeSocket(GspEthernetHandleSet self, const GspEthernetSocket sock)
{
    if ((self != NULL) && (sock != NULL)) {

        int i;

        for (i = 0; i < self->nhandles; i++) {
            if (self->handles[i].fd == sock->rawSocket) {
                memmove(&self->handles[i], &self->handles[i+1], sizeof(struct pollfd) * (self->nhandles - i - 1));
                self->nhandles--;
                return;
            }
        }
    }
}

int
GspEthernetHandleSet_waitReady(GspEthernetHandleSet self, unsigned int timeoutMs)
{
    int result;

    if ((self != NULL) && (self->nhandles >= 0)) {
        result = poll(self->handles, self->nhandles, timeoutMs);
    }
    else {
       result = -1;
    }

    return result;
}

void
GspEthernetHandleSet_destroy(GspEthernetHandleSet self)
{
    if (self->nhandles)
        free(self->handles);

    GLOBAL_FREEMEM(self);
}

static int
getInterfaceIndex(int sock, const char* deviceName)
{
    struct ifreq ifr;

    strncpy(ifr.ifr_name, deviceName, IFNAMSIZ);

    if (ioctl(sock, SIOCGIFINDEX, &ifr) == -1) {
        if (DEBUG_SOCKET)
            printf("ETHERNET_LINUX: Failed to get interface index");
        return -1;
    }

    int interfaceIndex = ifr.ifr_ifindex;

    if (ioctl (sock, SIOCGIFFLAGS, &ifr) == -1)
    {
        if (DEBUG_SOCKET)
            printf("ETHERNET_LINUX: Problem getting device flags");
        return -1;
    }

    ifr.ifr_flags |= IFF_PROMISC;
    if (ioctl (sock, SIOCSIFFLAGS, &ifr) == -1)
    {
        if (DEBUG_SOCKET)
            printf("ETHERNET_LINUX: Setting device to promiscuous mode failed");
        return -1;
    }

    return interfaceIndex;
}


void
GspEthernet_getInterfaceMACAddress(const char* interfaceId, uint8_t* addr)
{
    struct ifreq buffer;

    int sock = socket(PF_INET, SOCK_DGRAM, 0);

    memset(&buffer, 0x00, sizeof(buffer));

    strncpy(buffer.ifr_name, interfaceId, IFNAMSIZ);

    ioctl(sock, SIOCGIFHWADDR, &buffer);

    close(sock);

    int i;

    for(i = 0; i < 6; i++ )
    {
        addr[i] = (unsigned char)buffer.ifr_hwaddr.sa_data[i];
    }
}


GspEthernetSocket
GspEthernet_createSocket(const char* interfaceId, uint8_t* destAddress)
{
    GspEthernetSocket ethernetSocket = (GspEthernetSocket)GLOBAL_CALLOC(1, sizeof(struct sGspEthernetSocket));

    if (ethernetSocket) {
        ethernetSocket->rawSocket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

        if (ethernetSocket->rawSocket == -1) {
            if (DEBUG_SOCKET)
                printf("Error creating raw socket!\n");
            GLOBAL_FREEMEM(ethernetSocket);
            return NULL;
        }

        ethernetSocket->socketAddress.sll_family = PF_PACKET;
        ethernetSocket->socketAddress.sll_protocol = htons(ETH_P_IP);

        int ifcIdx =  getInterfaceIndex(ethernetSocket->rawSocket, interfaceId);

        if (ifcIdx == -1) {
            GspEthernet_destroySocket(ethernetSocket);
            return NULL;
        }

        ethernetSocket->socketAddress.sll_ifindex = ifcIdx;

        ethernetSocket->socketAddress.sll_hatype =  ARPHRD_ETHER;
        ethernetSocket->socketAddress.sll_pkttype = PACKET_OTHERHOST;

        ethernetSocket->socketAddress.sll_halen = ETH_ALEN;

        memset(ethernetSocket->socketAddress.sll_addr, 0, 8);

        if (destAddress != NULL)
            memcpy(ethernetSocket->socketAddress.sll_addr, destAddress, 6);

        ethernetSocket->isBind = false;
    }

    return ethernetSocket;
}

void
GspEthernet_setProtocolFilter(GspEthernetSocket ethSocket, uint16_t etherType)
{
    ethSocket->socketAddress.sll_protocol = htons(etherType);
}


/* non-blocking receive */
int
GspEthernet_receivePacket(GspEthernetSocket self, uint8_t* buffer, int bufferSize)
{
    if (self->isBind == false) {
        if (bind(self->rawSocket, (struct sockaddr*) &self->socketAddress, sizeof(self->socketAddress)) == 0)
            self->isBind = true;
        else
            return 0;
    }

    return recvfrom(self->rawSocket, buffer, bufferSize, MSG_DONTWAIT, 0, 0);
}

void
GspEthernet_sendPacket(GspEthernetSocket ethSocket, uint8_t* buffer, int packetSize)
{
    sendto(ethSocket->rawSocket, buffer, packetSize,
                0, (struct sockaddr*) &(ethSocket->socketAddress), sizeof(ethSocket->socketAddress));
}

void
GspEthernet_destroySocket(GspEthernetSocket ethSocket)
{
    close(ethSocket->rawSocket);
    GLOBAL_FREEMEM(ethSocket);
}

bool
GspEthernet_isSupported()
{
    return true;
}

