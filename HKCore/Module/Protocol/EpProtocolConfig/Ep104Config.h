//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ep104Config.h  CEp104Config

#pragma once

#include "EpProtocolConfigGlobal.h"



class CEp104Config : public CExBaseObject
{
public:
	CEp104Config();
	virtual ~CEp104Config();


	long  m_nOddr;
	long  m_nYxAddr;
	long  m_nYcAddr;
	long  m_nYtAddr;
//���غ���
public:
	virtual UINT GetClassID() {    return EPCCLASSID_CEP104CONFIG;   }
	virtual BSTR GetXmlElementKey()  {      return CEpProtocolConfigXmlRWKeys::CEp104ConfigKey();     }
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

