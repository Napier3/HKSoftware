
// PingTest.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#include "../OSInterface/OSInterface.h"

/*
* 程序名: rawping.h
* 说明: 
* 主要函数库头文件
*/

BOOL XInitSocket();
void XExitSocket();

int xping(char* pszIP);
BOOL xping(const CString &strIP);

BOOL GetIPFromHostNameAndMac(const CString &strHost,const CString &strServerMac,const CString &strLocalGatewayMac,CString &strIP);