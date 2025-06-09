#pragma once
    
#include "..\BaseClass\TLinkList.h"
// #include <string>
// #include <vector>
// using namespace std;

#define _MAX_IP_STRING_LENTH_ 2560

class CTagAdapter
{
public:
	CTagAdapter()
	{
		m_arrIP.RemoveAll();
		m_arrNetMask.RemoveAll();
		m_arrNetGate.RemoveAll();
	}
	virtual ~CTagAdapter(){}

	CString m_strName;			// 适配器名称
	CString m_strDriverDesc;	// 适配器描述
	CStringArray m_arrIP;			// IP地址
	CStringArray m_arrNetMask;		// 子网掩码
	CStringArray m_arrNetGate;		// 网关
};

class CTagAdapters : public CTLinkList<CTagAdapter>
{
public:
	CTagAdapters(){}
	virtual ~CTagAdapters(){}
};


class CIPAddrModifyTool  
{
public:
	CIPAddrModifyTool();
	virtual ~CIPAddrModifyTool();

	CTagAdapters m_oTagAdapers;

public:
	BOOL InitGetAdapterInfo();
	void SetLocalNetName(const CString &strLocalNetName){m_strLocalNetName = strLocalNetName;}
	BOOL RegGetIP(CTagAdapter *pAI);
	BOOL RegSetIP(CTagAdapter *pAI);
	BOOL AddIPForLocalNet_MultiDevs(const CStringArray &straIPAddress);
	BOOL ReleaseIPForLocalNet_MultiDevs(const CStringArray &straIPAddress);
	BOOL AddIP_To_TagAdpter(const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate);
	BOOL DeleteIP_To_TagAdpter(const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate);
	BOOL RegedtAllIP_To_TagAdpter();
	BOOL AddIPForLocalNet_SingleDev(const CString &strIPAddress, const CString &strNetMask = _T(""));
	BOOL DeleteIPForLocalNet(const CStringArray &arrIPs);
	BOOL DeleteIPForLocalNet(const CString &strIPAddress);
	BOOL RestartNetWork();
	BOOL NeedAddNetworkSegmentIP(const CString &strDriverDesc,const CString &strIP,long nBeginIndex = 20);
	BOOL AddIPForLocalNet_SameSegment(const CString &strIP,long nBeginIndex = 20);//添加同一个网段的IP，参数2为尝试添加的IP最后一段的起始数值

protected:
	BOOL AddIPForLocalNet_SingleDev(const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate);
	BOOL IsLocalNetAdpter(const CString &strDriverDesc);
	BOOL AddStringToArry(CStringArray &arrIP ,char *pszData ,long nMaxLenth);
	BOOL AddArryToString(const CStringArray &arrIP ,char *pszData ,long &nMaxLenth);
	BOOL AddIPToArray(CTagAdapter *pAI ,const CString &strIPAddress, const CString &strNetMask, const CString &strNetGate);
	BOOL DeleteIPToArray(CTagAdapter *pAI ,const CStringArray &arrIPs);
	BOOL DeleteIPToArray(CTagAdapter *pAI ,const CString &strIPAddress);
	void DeleteIPRepeat(CTagAdapter *pAI);
	BOOL CheckIPAddr(const CString &strLocalIP,CString &strSubNet);

	BOOL ExcuteControlCMD(const CString &strCmd);

	CString m_strLocalNetName;

};

