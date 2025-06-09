#ifndef _SOCKET_API_LINUX_
#define _SOCKET_API_LINUX_


int tnfs_get_net_mac(unsigned char *pMacAddr);
int tnfs_get_net_mac_str(char *pszMacAddr, char chDelimiter='-');

#endif
