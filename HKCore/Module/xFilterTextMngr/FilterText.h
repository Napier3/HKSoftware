//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//FilterText.h  CFilterText

#pragma once

#include "GlobalDataMngrGlobal.h"



class CFilterText : public CExBaseObject
{
public:
	CFilterText();
	virtual ~CFilterText();


//���غ���
public:
	virtual UINT GetClassID() {    return TFLTCLASSID_CFILTERTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CGlobalDataMngrXmlRWKeys::CFilterTextKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

