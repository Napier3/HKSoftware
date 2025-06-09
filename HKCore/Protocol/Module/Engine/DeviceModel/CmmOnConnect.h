#pragma once
#include "DeviceModelXmlKeys.h"

class CCmmOnConnect :	public CExBaseObject
{
public:
	CCmmOnConnect(void);
	virtual ~CCmmOnConnect(void);

	CString m_strText;

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_ONCONNECT;};
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strOnConnectKey;     }
	//´®ÐÐ»¯
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
};
