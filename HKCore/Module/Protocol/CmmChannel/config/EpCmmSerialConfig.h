#pragma once
#include "..\..\..\..\module\baseclass\exbaseobject.h"
#include "EpCmmConfigBase.h"


class CEpCmmSerialConfig :	public CEpCmmConfigBase
{
public:
	CEpCmmSerialConfig(void);
	~CEpCmmSerialConfig(void);

	LONG m_nBaudRate;
	LONG m_nDataBit;
	float m_fStopBit;
	LONG m_nParity;
	LONG m_nPortNum;

public:
	virtual UINT GetClassID(){return EPCLASSID_CMM_SERIAL_CONFIG;};

	//´®ÐÐ»¯
	virtual BSTR GetXmlElementKey()  {      return CEpCmmConfigXmlKeys::g_pXmlRWKeys->m_strSerialKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);

	BYTE GetStopBits();

};
