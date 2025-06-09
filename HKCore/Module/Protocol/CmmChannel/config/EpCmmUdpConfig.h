#pragma once
#include "..\..\..\..\module\baseclass\exbaseobject.h"
#include "EpCmmConfigBase.h"

class CEpCmmUdpConfig :	public CEpCmmConfigBase
{
public:
	CEpCmmUdpConfig(void);
	~CEpCmmUdpConfig(void);

public:
	virtual UINT GetClassID(){return EPCLASSID_CMM_UDP_CONFIG;};

	//���л�
	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strUdpServerKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	// ����
	virtual BOOL CopyOwn(CBaseObject* pDest);

public:
	CString m_strLocalIP;
	long    m_nLocalPort;
	CString m_strRemoteIP;
	long    m_nRemotePort;

	long    m_nUseBroadcast;
	CString m_strMulticastIP;//�鲥��ַ
	long m_nMulticastPort;//�鲥��ַ
};
