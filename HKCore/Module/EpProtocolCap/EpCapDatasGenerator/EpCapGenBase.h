//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//EpCapGenBase.h  CEpCapGenBase

#pragma once

#include "EpCapDatasGeneratorGlobal.h"



class CEpCapGenBase : public CExBaseObject
{
public:
	CEpCapGenBase();
	virtual ~CEpCapGenBase();


	CString  m_strFile;
//���غ���
public:
	virtual UINT GetClassID() {    return ECGCLASSID_CEPCAPGENBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CEpCapDatasGeneratorXmlRWKeys::CEpCapGenBaseKey();     }
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

