//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ep101Config.h  CEp101Config

#pragma once

#include "EpProtocolConfigGlobal.h"



class CEp101Config : public CExBaseObject
{
public:
	CEp101Config();
	virtual ~CEp101Config();


	long  m_nOddr;
	long  m_nYxAddr;
	long  m_nYcAddr;
	long  m_nYtAddr;
//���غ���
public:
	virtual UINT GetClassID() {    return EPCCLASSID_CEP101CONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CEpProtocolConfigXmlRWKeys::CEp101ConfigKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

