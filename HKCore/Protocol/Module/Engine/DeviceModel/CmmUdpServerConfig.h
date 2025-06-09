#pragma once
#include "CmmNetServerConfig.h"

class CCmmUdpServerConfig :	public CCmmNetServerConfig
{
public:
	CCmmUdpServerConfig(void);
	virtual ~CCmmUdpServerConfig(void);

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_UDP_SERVER_CONFIG;};

	//���л�
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey;     }
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
