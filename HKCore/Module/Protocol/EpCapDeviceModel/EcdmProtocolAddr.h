//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EcdmProtocolAddr.h  CEcdmProtocolAddr

#pragma once

#include "EpCapDeviceModelGlobal.h"



class CEcdmProtocolAddr : public CExBaseObject
{
public:
	CEcdmProtocolAddr();
	virtual ~CEcdmProtocolAddr();


	long  m_nYxAddr;
	long  m_nYcAddr;
	long  m_nYtAddr;
//���غ���
public:
	virtual UINT GetClassID() {    return ECDMCLASSID_CECDMPROTOCOLADDR;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDeviceModelXmlRWKeys::CEcdmProtocolAddrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

