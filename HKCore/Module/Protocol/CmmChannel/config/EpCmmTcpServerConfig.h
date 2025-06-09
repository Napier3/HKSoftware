#pragma once
#include "..\..\..\..\module\baseclass\exbaseobject.h"
#include "EpCmmConfigBase.h"


class CEpCmmTcpServerConfig :	public CEpCmmConfigBase
{
public:
	CEpCmmTcpServerConfig(void);
	~CEpCmmTcpServerConfig(void);

	CString m_strLocalIP;
	long    m_nLocalPort;

public:
	virtual UINT GetClassID(){return EPCLASSID_CMM_TCP_SERVER_CONFIG;};

	//´®ÐÐ»¯
	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strTcpServerKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);
};
