//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XLangItem.h  CXLangItem

#pragma once

#include "XLanguageGlobal.h"



class CXLangItem : public CExBaseObject
{
public:
	CXLangItem();
	virtual ~CXLangItem();

	CString  m_strSrcText;
	CString  m_strTranslation;
	CString  *m_pstrResourceRef;
//���غ���
public:
	virtual UINT GetClassID() {    return LGUGCLASSID_CLANGITEM;   }
	virtual BSTR GetXmlElementKey()  {      return CXLanguageXmlRWKeys::CXLangItemKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
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

