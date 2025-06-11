#pragma once
#include "ExBaseObject.h"
#include "CmmNetClientConfig.h"


class CCmmTcpClientConfig :	public CCmmNetClientConfig
{
public:
	CCmmTcpClientConfig(void);
	virtual ~CCmmTcpClientConfig(void);

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_TCP_CLIENT_CONFIG;};

	//´®ÐÐ»¯
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpClientKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};
