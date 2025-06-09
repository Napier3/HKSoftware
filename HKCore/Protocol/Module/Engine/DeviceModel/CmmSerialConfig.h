#pragma once
#include "DeviceModelXmlKeys.h"
#include "CmmConfigBase.h"


class CCmmSerialConfig :	public CCmmConfigBase
{
public:
	CCmmSerialConfig(void);
	virtual ~CCmmSerialConfig(void);

	long m_nBaudRate;
	long m_nDataBit;
	float m_fStopBit;
	long m_nParity;
	long m_nPortNum;

public:
	virtual UINT GetClassID(){return DMCLASSID_CMM_SERIAL_CONFIG;};

	//´®ÐÐ»¯
	virtual BSTR GetXmlElementKey()  {      return CDeviceModelXmlKeys::g_pXmlRWKeys->m_strSerialKey;     }
	virtual long BinarySerializeOwn(CBinarySerialBuffer &oBinaryBuff);
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode,CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	// ¸´ÖÆ
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	BYTE GetStopBits();

	//2023-4-18 lijunqing
	virtual void SetPort(long nPort)
	{
		m_nPortNum = nPort;
	}

};
