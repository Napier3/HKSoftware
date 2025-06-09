#pragma once
#include "../../../../module/baseclass/exbaseobject.h"
#include "CmmNetClientConfig.h"


class CCmmUdpClientConfig :	public CCmmNetClientConfig
{
public:
	CCmmUdpClientConfig(void);
	virtual ~CCmmUdpClientConfig(void);

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_UDP_CLIENT_CONFIG;};

	//���л�
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpClientKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ����
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	CString m_strMulticastIP;//�鲥��ַ
	long m_nMulticastPort;//�鲥��ַ
	long    m_nUseBroadcast;
};
