//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SmmRefGroupKey.h  CSmmRefGroupKey

#pragma once

#include "StringMatchMapGlobal.h"



class CSmmRefGroupKey : public CExBaseObject
{
public:
	CSmmRefGroupKey();
	virtual ~CSmmRefGroupKey();


	long  m_nIndex;
//���غ���
public:
	virtual UINT GetClassID() {    return SMMCLASSID_CSMMREFGROUPKEY;   }
	virtual BSTR GetXmlElementKey()  {      return CStringMatchMapXmlRWKeys::CSmmRefGroupKeyKey();     }
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

