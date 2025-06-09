#pragma once
#include "CmmNetServerConfig.h"

class CCmmUdpServerConfig :	public CCmmNetServerConfig
{
public:
	CCmmUdpServerConfig(void);
	virtual ~CCmmUdpServerConfig(void);

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_UDP_SERVER_CONFIG;};

	//串行化
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strUdpServerKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// 复制
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

public:
	CString m_strMulticastIP;//组播地址
	long m_nMulticastPort;//组播地址
	long    m_nUseBroadcast;
};
