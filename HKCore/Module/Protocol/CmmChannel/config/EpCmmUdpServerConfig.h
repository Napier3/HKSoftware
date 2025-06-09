#pragma once
#include "EpCmmUdpConfig.h"

class CEpCmmUdpServerConfig :	public CEpCmmUdpConfig
{
public:
	CEpCmmUdpServerConfig(void);
	~CEpCmmUdpServerConfig(void);

public:
	virtual UINT GetClassID(){return EPCLASSID_CMM_UDP_SERVER_CONFIG;};

	//´®ÐÐ»¯
	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strUdpServerKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);

public:
	CString m_strClientIP;
};
