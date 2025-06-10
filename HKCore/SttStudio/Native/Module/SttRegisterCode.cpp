#include "stdafx.h"
#include "SttRegisterCode.h"


//20200827  lijunqing
#ifdef _PSX_QT_LINUX_

//#include "../../Module/Socket/SocketApi_linux.h"

int tnfs_get_net_mac(unsigned char *pMacAddr);
int tnfs_get_net_mac_str(char *pszMacAddr, char chDelimiter='-');


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


void stt_GetMachineCode_hd(CString &strRet)
{
    char pszMac[32];
    tnfs_get_net_mac_str(pszMac, 0);
    strRet = pszMac;
    strRet = _T("00-00-") + strRet;
}

#else

#include "../../Module/Encrypt/GetDiskID32.h"
#include "../../Module/Encrypt/SystemCode.h"

void stt_GetMachineCode_hd(CString &strRet)
{
	CSystemCode code;
	CString strTmp, str;
	CString strHdCode, strCpu, strMac;

	UINT i = 0;
	int j = 0;

	CGetDiskID32 oDiskID32;
	oDiskID32.GetDiskID32();
	strHdCode = oDiskID32.GetDiskID32Ex();

	strRet += strHdCode;

	code.GetCPUCode();
	for (i=2; i<code.uSystemInfoLen; i++)
	{
		strTmp.Format(_T("%02X"), code.szSystemInfo[i]);	
		strCpu += strTmp;
	}

	strRet += strCpu;

	code.GetMacCode();
	for (i=0; i<code.uSystemInfoLen; i++)
	{
		strTmp.Format(_T("%02X"), code.szSystemInfo[i]);	
		strMac += strTmp;
	}

	strRet += strMac;
}


#endif


__uint64 stt_GetMachineCode_U64(const CString &strMachine)
{
    __uint64 nRet = 0;
    BYTE nxor=0;
    BYTE sum=0, sub=0, sft_l=0, sft_r=0, mul=1, mass=0, oth=0;

    for (int i=0; i<strMachine.GetLength(); i++)
    {
        nxor ^= strMachine.GetAt(i) + 0x0a;
        sum += strMachine.GetAt(i) & 0x7e;
        sub -= strMachine.GetAt(i);
        sft_l += _rotl(strMachine.GetAt(i), i);
        sft_r += _rotr(strMachine.GetAt(i), i);
        mul += strMachine.GetAt(i)*strMachine.GetAt(i) + strMachine.GetAt(i)*3 - i;
        mass += strMachine.GetAt(i) + (sum^nxor) + (sft_l*sft_r);
        oth += sub*sum + mass*2 + (i%6) + (mul&0x4e);
    }


    // 1
    nRet = sft_r;

    // 2
    nRet = (nRet << 8) + mul;

    // 3
    nRet = (nRet << 8) + sum;

    // 4
    nRet = (nRet << 8) + sft_l;

    // 5
    nRet = (nRet << 8) + mass;

    // 6
    nRet = (nRet << 8) + nxor;

    // 7
    nRet = (nRet << 8) + oth;

    // 8
    nRet = (nRet << 8) + sub;

    return nRet;
}

CString stt_GetMachineRegCode(const CString &strMachine)
{
    __uint64 nMachine = stt_GetMachineCode_U64(strMachine);
    CString strRet;
    long nOffset = 48;
    unsigned short nVal = 0;

    for (long nIndex=0; nIndex<4; nIndex++)
    {
        nVal = (nMachine >> nOffset) & 0xFFFF;
        strRet.AppendFormat(_T("%04X-"), nVal);
        nOffset -= 16;
    }

    strRet = strRet.Left(strRet.GetLength() - 1);

    return strRet;
}

CString stt_GetMachineRegCode()
{
    CString strRet, strMachineCode;

    stt_GetMachineCode_hd(strRet);
    strMachineCode = stt_GetMachineRegCode(strRet);

    return strMachineCode;
}

__uint64 stt_GetMachineCode_U64()
{
    CString strRet;

    stt_GetMachineCode_hd(strRet);

    return stt_GetMachineCode_U64(strRet);
}

unsigned long stt_GetMachineCode_U32()
{
    __uint64 n64Code = stt_GetMachineCode_U64();

    unsigned long nRet = n64Code & 0xFFFFFFFF;

    return nRet;
}

