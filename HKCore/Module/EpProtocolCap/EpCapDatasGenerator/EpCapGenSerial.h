//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
public:
	virtual UINT GetClassID() {    return ECGCLASSID_CEPCAPGENSERIAL;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDatasGeneratorXmlRWKeys::CEpCapGenSerialKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

