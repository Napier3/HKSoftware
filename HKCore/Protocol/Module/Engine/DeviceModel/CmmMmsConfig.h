#pragma once
#include "DeviceModelXmlKeys.h"
#include "CmmConfigBase.h"


class CCmmMmsConfig :	public CCmmConfigBase
{
public:
	CCmmMmsConfig(void);
	virtual ~CCmmMmsConfig(void);

	CString m_strRemoteIP;
	CString  m_strPSW;
	CString  m_strKey;

	BOOL m_bPingState;

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_MMS_CONFIG;};

	//´®ÐÐ»¯
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMmsKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

};
