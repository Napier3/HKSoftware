#include "stdafx.h"
#include "IPAddrModifyTool.h"
#include "..\System\TickCount32.h"
#include "..\Socket\XPing.h"


#define A_TYPE_SUBNET         "255.0.0.0"
#define B_TYPE_SUBNET         "255.255.0.0"
#define C_TYPE_SUBNET         "255.255.255.0"

#pragma comment(lib, "ws2_32.lib")

CIPAddrModifyTool::CIPAddrModifyTool()
{
	m_strLocalNetName = "本地连接";
}

CIPAddrModifyTool::~CIPAddrModifyTool()
{
}

BOOL CIPAddrModifyTool::InitGetAdapterInfo()
{
	// 这里的代码适合WINDOWS2000，对于NT需要读取HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\NetworkCards
	HKEY hKey, hSubKey, hNdiIntKey;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
				"System\\CurrentControlSet\\Control\\Class\\{4d36e972-e325-11ce-bfc1-08002be10318}",
				0,
				KEY_READ,
				&hKey) != ERROR_SUCCESS)
		return FALSE;

	DWORD dwIndex = 0;
	DWORD dwBufSize = 256;
	DWORD dwDataType;
	char szSubKey[256];
	unsigned char szData[256];
	CTagAdapter *pAI = NULL;
	m_oTagAdapers.DeleteAll();

	while(RegEnumKeyEx(hKey, dwIndex++, szSubKey, &dwBufSize, NULL, NULL, NULL, NULL) == ERROR_SUCCESS)
	{
		if(RegOpenKeyEx(hKey, szSubKey, 0, KEY_READ, &hSubKey) == ERROR_SUCCESS)
		{		
			if(RegOpenKeyEx(hSubKey, "Ndi\\Interfaces", 0, KEY_READ, &hNdiIntKey) == ERROR_SUCCESS)
			{
				dwBufSize = 256;
				if(RegQueryValueEx(hNdiIntKey, "LowerRange", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
				{
					if(strcmp((char*)szData, "ethernet") == 0)		//	判断是不是以太网卡
					{
						dwBufSize = 256;
						if(RegQueryValueEx(hSubKey, "DriverDesc", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
						{
							pAI = new CTagAdapter();
							pAI->m_strDriverDesc = (LPCTSTR)szData;

							if (IsLocalNetAdpter(pAI->m_strDriverDesc))
							{
								dwBufSize = 256;

								if(RegQueryValueEx(hSubKey, "NetCfgInstanceID", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
								{
									pAI->m_strName = (LPCTSTR)szData;
									RegGetIP(pAI);
								}

								m_oTagAdapers.AddTail(pAI);
							}
							else
							{
								delete pAI;
							}
						}
					}
				}
				RegCloseKey(hNdiIntKey);
			}
			RegCloseKey(hSubKey);
		}

		dwBufSize = 256;
	}	/* end of while */
		
	RegCloseKey(hKey);

	return TRUE;
}

BOOL CIPAddrModifyTool::RegGetIP(CTagAdapter *pAI)
{
	ASSERT(pAI);

	HKEY hKey;
	CString strKeyName = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
	strKeyName += pAI->m_strName;
	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		strKeyName,
		0,
		KEY_READ,
		&hKey) != ERROR_SUCCESS)
		return FALSE;

	unsigned char szData[_MAX_IP_STRING_LENTH_];
	DWORD dwDataType, dwBufSize;

	dwBufSize = _MAX_IP_STRING_LENTH_;
	if(RegQueryValueEx(hKey, "IPAddress", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		AddStringToArry(pAI->m_arrIP ,(char*)szData,_MAX_IP_STRING_LENTH_);

	dwBufSize = _MAX_IP_STRING_LENTH_;
	if(RegQueryValueEx(hKey, "SubnetMask", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		AddStringToArry(pAI->m_arrNetMask ,(char*)szData,_MAX_IP_STRING_LENTH_);

	dwBufSize = _MAX_IP_STRING_LENTH_;
	if(RegQueryValueEx(hKey, "DefaultGateway", 0, &dwDataType, szData, &dwBufSize) == ERROR_SUCCESS)
		AddStringToArry(pAI->m_arrNetGate ,(char*)szData,_MAX_IP_STRING_LENTH_);

	DeleteIPRepeat(pAI);
	RegCloseKey(hKey);
	return TRUE;
}

void CIPAddrModifyTool::DeleteIPRepeat(CTagAdapter *pAI)
{
	long nSize = pAI->m_arrIP.GetSize();
	long nCount1 = 0 ,nCount2;
	CString strIP1,strIP2;

	for (nCount1 = 0;nCount1<nSize;nCount1++)
	{
		strIP1 = pAI->m_arrIP.GetAt(nCount1);

		for (nCount2 = nCount1+1;nCount2<nSize;nCount2++)
		{
			strIP2 = pAI->m_arrIP.GetAt(nCount2);

			if (strIP1 == strIP2)
			{
				pAI->m_arrIP.RemoveAt(nCount2);
				pAI->m_arrNetMask.RemoveAt(nCount2);
				DeleteIPRepeat(pAI);
				return;
			}
		}
	}
}

BOOL CIPAddrModifyTool::AddIPForLocalNet_MultiDevs(const CStringArray &straIPAddress)
{
	CString strCurIP,strSubNet,strTmp;
	long nSize = straIPAddress.GetSize();
	long nIndex = 0;
	strTmp = "";

	for(nIndex=0;nIndex<nSize;nIndex++)
	{
		strCurIP = straIPAddress.GetAt(nIndex);
// 		strTmp.Format("%s-%s;",strCurIP,strSubNet);
// 		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,"新增IP地址(%s).",strTmp);

		if (!CheckIPAddr(strCurIP,strSubNet))
		{
			continue;
		}

		AddIP_To_TagAdpter(strCurIP,strSubNet,"");
	}

	RegedtAllIP_To_TagAdpter();
	RestartNetWork();
	return TRUE;
}

BOOL CIPAddrModifyTool::ReleaseIPForLocalNet_MultiDevs(const CStringArray &straIPAddress)
{
	CTagAdapter *pAI = NULL;
	POS pos = m_oTagAdapers.GetHeadPosition();

	while(pos!=NULL)
	{
		pAI = m_oTagAdapers.GetNext(pos);
		DeleteIPToArray(pAI,straIPAddress);
	}

	RegedtAllIP_To_TagAdpter();
	RestartNetWork();
	return TRUE;
}

BOOL CIPAddrModifyTool::AddIPForLocalNet_SingleDev(const CString &strIPAddress, const CString &strNetMask)
{
	if (strIPAddress == _T("127.0.0.1"))
	{
		return TRUE;
	}

	CString strSubNet;

	if (!CheckIPAddr(strIPAddress,strSubNet))
	{
		return FALSE;
	}

	if (!strNetMask.IsEmpty())
	{
		strSubNet = strNetMask;
	}

	return AddIPForLocalNet_SingleDev(strIPAddress ,strSubNet ,"");;
}

BOOL CIPAddrModifyTool::AddIPForLocalNet_SameSegment(const CString &strIP,long nBeginIndex)
{
	CString strTmp,strNewIP;
	long nIndex = strIP.ReverseFind('.');

	if (nIndex<=0)
	{
		return FALSE;
	}

	strTmp = strIP.Left(nIndex);
	BOOL bFindAddIP = FALSE;

	for (nIndex = nBeginIndex;nIndex<255;nIndex++)
	{
		strNewIP.Format(_T("%s.%d"),strTmp,nIndex);

		if (strNewIP == strIP)
		{
			continue;
		}

		if (xping(strNewIP) != 1)
		{
			bFindAddIP = TRUE;
			break;
		}
	}

	if (!bFindAddIP)
	{
		return FALSE;
	}

	return AddIPForLocalNet_SingleDev(strNewIP);
}

BOOL CIPAddrModifyTool::CheckIPAddr(const CString &strLocalIP,CString &strSubNet)
{
	CString strTmp;
	strTmp = strLocalIP;
	long nIndex = strTmp.Replace(".",".");

	if (nIndex != 3)
	{
		return FALSE;
	}

	nIndex = strLocalIP.Find('.');
	strTmp = strLocalIP.Left(nIndex);
	nIndex = CString_To_long(strTmp);

	if ((nIndex>=0)&&(nIndex<128))
	{
		strSubNet = A_TYPE_SUBNET;
	}
	else if ((nIndex>=128)&&(nIndex<192))
	{
		strSubNet = B_TYPE_SUBNET;
	}
	else if ((nIndex>=192)&&(nIndex<224))
	{
		strSubNet = C_TYPE_SUBNET;
	}
	else
		return FALSE;

	return TRUE;
}

BOOL CIPAddrModifyTool::AddIPForLocalNet_SingleDev(const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate)
{
	CTagAdapter *pAI = NULL;
	BOOL bRestartNet = FALSE;
	char szIPAddr[100] = {0};
	CString_to_char(strIPAddress,szIPAddr);

 	if (xping(szIPAddr) == 1)
 	{
		return TRUE;
 	}

	if (m_oTagAdapers.GetCount()>0)
	{
		CString strTmp ,strTmp1;
		POS pos = m_oTagAdapers.GetHeadPosition();

		while(pos!=NULL)
		{
			pAI = m_oTagAdapers.GetNext(pos);
			//strTmp1.Format("%s,%s;",pAI->m_strName,pAI->m_strDriverDesc);
			//strTmp += strTmp1;
			if (!AddIPToArray(pAI ,strIPAddress ,strNetMask ,strNetGate))
				continue;

			if(!RegSetIP(pAI))
				continue;

			bRestartNet = TRUE;
		}
		//strTmp1.Format("%ld;",m_oTagAdapers.GetCount());
		//strTmp += strTmp1;
		//AfxMessageBox(strTmp);
	}
	else
		return FALSE;

	if (bRestartNet)
	{
		RestartNetWork();
	}

	return bRestartNet;
}

BOOL CIPAddrModifyTool::AddIP_To_TagAdpter(const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate)
{
	CTagAdapter *pAI = NULL;
	POS pos = m_oTagAdapers.GetHeadPosition();

	while(pos!=NULL)
	{
		pAI = m_oTagAdapers.GetNext(pos);
		AddIPToArray(pAI ,strIPAddress ,strNetMask ,strNetGate);
	}

	return TRUE;
}

BOOL CIPAddrModifyTool::DeleteIP_To_TagAdpter(const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate)
{
	CTagAdapter *pAI = NULL;
	POS pos = m_oTagAdapers.GetHeadPosition();

	while(pos!=NULL)
	{
		pAI = m_oTagAdapers.GetNext(pos);
		AddIPToArray(pAI ,strIPAddress ,strNetMask ,strNetGate);
	}

	return TRUE;
}

BOOL CIPAddrModifyTool::RegedtAllIP_To_TagAdpter()
{
	CTagAdapter *pAI = NULL;
	POS pos = m_oTagAdapers.GetHeadPosition();

	while(pos!=NULL)
	{
		pAI = m_oTagAdapers.GetNext(pos);
		RegSetIP(pAI);
	}

	return TRUE;
}

BOOL CIPAddrModifyTool::DeleteIPForLocalNet(const CStringArray &arrIPs)
{
	CTagAdapter *pAI = NULL;
	BOOL bRestartNet = FALSE;

	if (m_oTagAdapers.GetCount()>0)
	{
		POS pos = m_oTagAdapers.GetHeadPosition();

		while(pos!=NULL)
		{
			pAI = m_oTagAdapers.GetNext(pos);

			if (!DeleteIPToArray(pAI ,arrIPs))
				continue;

			if(!RegSetIP(pAI))
				continue;

			bRestartNet = TRUE;
		}
	}
	else
		return FALSE;

	if (bRestartNet)
	{
		RestartNetWork();
	}

	return bRestartNet;
}

BOOL CIPAddrModifyTool::DeleteIPForLocalNet(const CString &strIPAddress)
{
	CTagAdapter *pAI = NULL;
	BOOL bRestartNet = FALSE;

	if (m_oTagAdapers.GetCount()>0)
	{
		POS pos = m_oTagAdapers.GetHeadPosition();

		while(pos!=NULL)
		{
			pAI = m_oTagAdapers.GetNext(pos);

			if (!DeleteIPToArray(pAI ,strIPAddress))
				continue;

			if(!RegSetIP(pAI))
				continue;

			bRestartNet = TRUE;
		}
	}
	else
		return FALSE;

	if (bRestartNet)
	{
		RestartNetWork();
	}

	return bRestartNet;
}

BOOL CIPAddrModifyTool::RegSetIP(CTagAdapter *pAI)
{
	HKEY hKey;
	long nIP, nMask, nGate;	
	CString strKeyName = "SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\";
	strKeyName += pAI->m_strName;

	if(RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		strKeyName,
		0,
		KEY_WRITE,
		&hKey) != ERROR_SUCCESS)
		return FALSE;

	char mszIPAddress[_MAX_IP_STRING_LENTH_];
	char mszNetMask[_MAX_IP_STRING_LENTH_];
	char mszNetGate[_MAX_IP_STRING_LENTH_];
	AddArryToString(pAI->m_arrIP,mszIPAddress,nIP);

	if (nIP>_MAX_IP_STRING_LENTH_)
	{
		AfxMessageBox("IP地址总数太多,数组长度越限.");
	}

	AddArryToString(pAI->m_arrNetMask,mszNetMask,nMask);

	if (nMask>_MAX_IP_STRING_LENTH_)
	{
		AfxMessageBox("IP地址总数太多,数组长度越限.");
	}

	AddArryToString(pAI->m_arrNetGate,mszNetGate,nGate);

	if (nGate>_MAX_IP_STRING_LENTH_)
	{
		AfxMessageBox("IP地址总数太多,数组长度越限.");
	}

	DWORD dwEnableDHCP;
	dwEnableDHCP = 0;

	RegSetValueEx(hKey, "EnableDHCP", 0, REG_DWORD, (LPBYTE)&dwEnableDHCP, sizeof(DWORD));
	RegSetValueEx(hKey, "IPAddress", 0, REG_MULTI_SZ, (unsigned char*)mszIPAddress, nIP);
	RegSetValueEx(hKey, "SubnetMask", 0, REG_MULTI_SZ, (unsigned char*)mszNetMask, nMask);
	RegSetValueEx(hKey, "DefaultGateway", 0, REG_MULTI_SZ, (unsigned char*)mszNetGate, nGate);
//	CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("新增IP地址(%s)"),mszIPAddress);
	RegCloseKey(hKey);

	return TRUE;
}

BOOL CIPAddrModifyTool::RestartNetWork()
{
	CString strRestartCMD;
	strRestartCMD.Format("netsh interface set interface \"%s\" disabled" ,_T("本地连接"));
	ExcuteControlCMD(strRestartCMD);
	strRestartCMD.Format("netsh interface set interface \"%s\" disabled" ,_T("以太网"));
	ExcuteControlCMD(strRestartCMD);
	CTickCount32 oTickCount;
	oTickCount.DoEvents(500);
	strRestartCMD.Format("netsh interface set interface \"%s\" enabled" ,_T("本地连接"));
	ExcuteControlCMD(strRestartCMD);
	strRestartCMD.Format("netsh interface set interface \"%s\" enabled" ,_T("以太网"));
	ExcuteControlCMD(strRestartCMD);
	return TRUE;
}

BOOL CIPAddrModifyTool::NeedAddNetworkSegmentIP(const CString &strDriverDesc,const CString &strIP,long nBeginIndex)
{
	CString strIP_NetSegment;
	long nIndex = strIP.ReverseFind('.');

	if (nIndex<=0)
	{
		return FALSE;
	}

	strIP_NetSegment = strIP.Left(nIndex);
	BOOL bFindAddIP = FALSE;
	CTagAdapter *pAI = NULL;
	POS pos = m_oTagAdapers.GetHeadPosition();
	long nSize = 0;
	long nCount = 0;
	CString strCurrIP,strCurrIP_NetSegment;

	while(pos!=NULL)
	{
		pAI = m_oTagAdapers.GetNext(pos);

		if (pAI->m_strDriverDesc.Find(strDriverDesc) == -1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("当前网卡信息(%s)不匹配."),pAI->m_strDriverDesc.GetString());
			continue;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("网卡信息(%s)与待匹配网卡字符信息(%s)一致,匹配成功."),pAI->m_strDriverDesc.GetString(),strDriverDesc.GetString());
		nSize = pAI->m_arrIP.GetSize();
		
		for (nCount = 0;nCount<nSize;nCount++)
		{
			strCurrIP = pAI->m_arrIP.GetAt(nCount);
			nIndex = strCurrIP.ReverseFind('.');

			if (nIndex > 0)
			{
				strCurrIP_NetSegment = strCurrIP.Left(nIndex);

				if (strCurrIP_NetSegment == strIP_NetSegment)
				{
					return FALSE;
				}
			}
		}
	}


// 	for (nIndex = nBeginIndex;nIndex<255;nIndex++)
// 	{
// 		strNewIP.Format(_T("%s.%d"),strTmp,nIndex);
// 
// 		if (xping(strNewIP) == 1)
// 		{
// 			return FALSE;
// 		}
// 	}

	return TRUE;
}

BOOL CIPAddrModifyTool::ExcuteControlCMD(const CString &strCmd)
{
	CString cmdLine = strCmd;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi,sizeof(pi));

	if(CreateProcess(NULL,cmdLine.GetBufferSetLength(MAX_PATH+1),NULL,NULL,FALSE,CREATE_NO_WINDOW,NULL,NULL,&si,&pi))
	{	
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}

	WaitForSingleObject(pi.hProcess,INFINITE);
	return TRUE;
}

BOOL CIPAddrModifyTool::IsLocalNetAdpter(const CString &strDriverDesc)
{
	if (strDriverDesc == "Realtek USB GBE Family Controller")
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIPAddrModifyTool::AddStringToArry(CStringArray &arrIP ,char *pszData ,long nMaxLenth)
{
	char *pSingleIP = pszData;
	long nLenth = strlen(pSingleIP);
	CString strSingleIP;
	strSingleIP = pSingleIP;
	strSingleIP.Trim();
	
	if (!strSingleIP.IsEmpty())
	{
		arrIP.Add(strSingleIP);
	}
	
	pSingleIP += nLenth;
	pSingleIP++;

	while((*pSingleIP != 0)&&((pSingleIP-pszData) < nMaxLenth))
	{
		strSingleIP = pSingleIP;
		nLenth = strlen(pSingleIP);
		strSingleIP.Trim();

		if (!strSingleIP.IsEmpty())
		{
			arrIP.Add(strSingleIP);
		}
		
		pSingleIP += nLenth;
		pSingleIP++;
	}

	return TRUE;
}

BOOL CIPAddrModifyTool::AddArryToString(const CStringArray &arrIP ,char *pszData ,long &nMaxLenth)
{
	long nLenth, nSize = arrIP.GetSize();
	char *pSingleIP = pszData;
	CString strSingleIP;
	long nCount = 0;

	for (nCount = 0;nCount<nSize;nCount++)
	{
		strSingleIP = arrIP.GetAt(nCount);
		CString_to_char(strSingleIP ,pSingleIP);
		nLenth = strlen(pSingleIP);
		pSingleIP += nLenth;
		pSingleIP++;
	}

	*pSingleIP = 0x00;
	nMaxLenth = pSingleIP-pszData;
	nMaxLenth++;
	return TRUE;
}

BOOL CIPAddrModifyTool::AddIPToArray(CTagAdapter *pAI ,const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate)
{
	if (strIPAddress.IsEmpty()||strNetMask.IsEmpty())
	{
		return FALSE;
	}

	CString strCurrIP;
	long nSize = pAI->m_arrIP.GetSize();
	long nCount = 0;

	for (nCount = 0;nCount<nSize;nCount++)
	{
		strCurrIP = pAI->m_arrIP.GetAt(nCount);

		if (strCurrIP == strIPAddress)
		{
			return FALSE;
		}
	}

	pAI->m_arrIP.Add(strIPAddress);
	pAI->m_arrNetMask.Add(strNetMask);

	if (!strNetGate.IsEmpty())
	{
		pAI->m_arrNetGate.Add(strNetGate);
	}

	return TRUE;
}

BOOL CIPAddrModifyTool::DeleteIPToArray(CTagAdapter *pAI ,const CStringArray &arrIPs)
{
	CString strCurrIP;
	long nSize = arrIPs.GetSize();
	long nCount = 0;
	BOOL bFind = FALSE;

	for (nCount = 0;nCount<nSize;nCount++)
	{
		strCurrIP = arrIPs.GetAt(nCount);

		if (DeleteIPToArray(pAI ,strCurrIP))
		{
			bFind = TRUE;
		}
	}

	return bFind;
}

BOOL CIPAddrModifyTool::DeleteIPToArray(CTagAdapter *pAI ,const CString &strIPAddress)
{
	if (strIPAddress.IsEmpty())
	{
		return FALSE;
	}

	CString strCurrIP;
	long nSize = pAI->m_arrIP.GetSize();
	long nCount = 0;
	BOOL bFind = FALSE;

	for (nCount = 0;nCount<nSize;nCount++)
	{
		strCurrIP = pAI->m_arrIP.GetAt(nCount);

		if (strCurrIP == strIPAddress)
		{
			bFind = TRUE;
			pAI->m_arrIP.RemoveAt(nCount);
			pAI->m_arrNetMask.RemoveAt(nCount);
			break;
		}
	}

	return bFind;
}

