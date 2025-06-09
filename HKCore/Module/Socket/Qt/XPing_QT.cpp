
// XPing_QT.cpp : 定义应用程序的类行为。
//
#include "../XPing.h"
#include <QString>
#include <QProcess>

///////////////////////////////////////////////////////////////////////
// Program entry point

int xping(char* pszIP)
{
    char pszCmd[64];
    sprintf(pszCmd, "ping -c 1 %s ", pszIP);

    if (system(pszCmd) == 0)
    {
        return 1;
    }
    else
    {
       	 return 0;
    }
}

BOOL GetIPFromHostNameAndMac(const CString &strHost,const CString &strServerMac,const CString &strLocalGatewayMac,CString &strIP)
{
	return FALSE; 
}

BOOL XInitSocket()
{
	return TRUE;
}

void XExitSocket()
{
	
}
