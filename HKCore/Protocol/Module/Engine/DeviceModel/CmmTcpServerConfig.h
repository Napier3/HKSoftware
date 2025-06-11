#pragma once
#include "ExBaseObject.h"
#include "CmmNetServerConfig.h"


class CCmmTcpServerConfig :	public CCmmNetServerConfig
{
public:
	CCmmTcpServerConfig(void);
	virtual ~CCmmTcpServerConfig(void);

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_TCP_SERVER_CONFIG;};

	//´®ÐÐ»¯
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strTcpServerKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};
