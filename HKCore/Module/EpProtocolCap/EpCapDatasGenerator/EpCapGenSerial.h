//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EpCapGenSerial.h  CEpCapGenSerial

#pragma once

#include "EpCapGenBase.h"


class CEpCapGenSerial : public CEpCapGenBase
{
public:
	CEpCapGenSerial();
	virtual ~CEpCapGenSerial();


	long  m_nBaudRate;
	long  m_nDataBit;
	long  m_nStopBit;
	float  m_fParity;
	long  m_nPort;
//重载函数
public:
	virtual UINT GetClassID() {    return ECGCLASSID_CEPCAPGENSERIAL;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDatasGeneratorXmlRWKeys::CEpCapGenSerialKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

