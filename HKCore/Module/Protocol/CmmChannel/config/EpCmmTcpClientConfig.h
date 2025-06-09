#pragma once
#include "..\..\..\..\module\baseclass\exbaseobject.h"
#include "EpCmmConfigBase.h"


class CEpCmmTcpClientConfig :	public CEpCmmConfigBase
{
public:
	CString m_strRemoteIP;
	long    m_nRemotePort;
	CString m_strLocalIP;
	long    m_nLocalPort;

public:
	CEpCmmTcpClientConfig(void);
	~CEpCmmTcpClientConfig(void);

public:
	virtual UINT GetClassID(){return EPCLASSID_CMM_TCP_CLIENT_CONFIG;};

	//´®ÐÐ»¯
 	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strTcpClientKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
};
