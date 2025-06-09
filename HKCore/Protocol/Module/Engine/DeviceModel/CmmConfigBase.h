#pragma once
#include "../../../../module/baseclass/exbaselist.h"

#include "DeviceClassIDDefine.h"

static const CString NET_CMM_MODE_BROADCAST = _T("broadcast");  //�㲥��ʽ
static const CString NET_CMM_MODE_MULTICAST = _T("multicast");  //�鲥��ʽ
static const CString NET_CMM_MODE_TOPOINT   = _T("to-point");   //��Ե㷽ʽ

class CCmmConfigBase :	public CExBaseList
{
public:
	CCmmConfigBase(void);
	virtual ~CCmmConfigBase(void);

	long m_nSendTimeout;
	long m_nReceiveTimeout;

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_CONFIG_BASE;};
	
	//���л�
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	//�༭
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//�����Ӷ���
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);

	//2023-4-18 lijunqing
	virtual void SetPort(long nPort);

};

UINT CmmCfg_GetPort(long nPort);
