
// PingTest.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#include "../OSInterface/OSInterface.h"

/*
* ������: rawping.h
* ˵��: 
* ��Ҫ������ͷ�ļ�
*/

BOOL XInitSocket();
void XExitSocket();

int xping(char* pszIP);
BOOL xping(const CString &strIP);

BOOL GetIPFromHostNameAndMac(const CString &strHost,const CString &strServerMac,const CString &strLocalGatewayMac,CString &strIP);