#pragma once
#include "../../../../module/baseclass/exbaselist.h"

#include "DeviceClassIDDefine.h"

static const CString NET_CMM_MODE_BROADCAST = _T("broadcast");  //广播方式
static const CString NET_CMM_MODE_MULTICAST = _T("multicast");  //组播方式
static const CString NET_CMM_MODE_TOPOINT   = _T("to-point");   //点对点方式

class CCmmConfigBase :	public CExBaseList
{
public:
	CCmmConfigBase(void);
	virtual ~CCmmConfigBase(void);

	long m_nSendTimeout;
	long m_nReceiveTimeout;

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_CONFIG_BASE;};
	
	//串行化
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//编辑
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//创建子对象
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//2023-4-18 lijunqing
	virtual void SetPort(long nPort);

};

UINT CmmCfg_GetPort(long nPort);
