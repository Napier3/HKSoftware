//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapSerialGroup.h  CEpCapSerialGroup

#pragma once

#include "EpCapConfigGlobal.h"


#include "EpCapSerialDevice.h"

class CEpCapSerialGroup : public CExBaseList
{
public:
	CEpCapSerialGroup();
	virtual ~CEpCapSerialGroup();


	long  m_nIndex;
//���غ���
public:
	virtual UINT GetClassID() {    return ECCLASSID_CEPCAPSERIALGROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapConfigXmlRWKeys::CEpCapSerialGroupKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

