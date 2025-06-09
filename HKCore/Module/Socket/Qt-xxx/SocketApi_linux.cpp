#include "stdafx.h"
#include "SocketApi_linux.h"

#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int tnfs_get_net_mac(unsigned char *pMacAddr)
{
	struct ifreq temp_ifreq;
    int nSock;

    if((nSock=socket(AF_INET,SOCK_STREAM,0)) <0)
	{
		return 2;
	}
	
	char *device="enp5s0"; //enp5s0是网卡设备名
	strcpy(temp_ifreq.ifr_name,device);
	
    if(ioctl(nSock, SIOCGIFHWADDR, &temp_ifreq) <0)
	{
		return 3;
	}
	
    memcpy(pMacAddr, temp_ifreq.ifr_hwaddr.sa_data, 6);

	return 0;
}

int tnfs_get_net_mac_str(char *pszMacAddr, char chDelimiter)
{
	unsigned char pMacAddr[6];
	int nRet = tnfs_get_net_mac(pMacAddr);
	
    if (chDelimiter > 0)
    {
        sprintf(pszMacAddr,  "%02X%c%02X%c%02X%c%02X%c%02X%c%02X",
            pMacAddr[0], chDelimiter,
            pMacAddr[1], chDelimiter,
            pMacAddr[2], chDelimiter,
            pMacAddr[3], chDelimiter,
            pMacAddr[4], chDelimiter,
            pMacAddr[5], chDelimiter);
    }
    else
    {
        sprintf(pszMacAddr,  "%02X%02X%02X%02X%02X%02X",
            pMacAddr[0],            pMacAddr[1],
            pMacAddr[2],             pMacAddr[3],
            pMacAddr[4],             pMacAddr[5]);
    }

    return nRet;
}
