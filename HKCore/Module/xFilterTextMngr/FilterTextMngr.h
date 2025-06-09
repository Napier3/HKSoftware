//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//FilterTextMngr.h  CFilterTextMngr

#pragma once

#include "GlobalDataMngrGlobal.h"


#include "FilterText.h"

class CFilterTextMngr : public CExBaseList
{
public:
	CFilterTextMngr();
	virtual ~CFilterTextMngr();


//���غ���
public:
	virtual UINT GetClassID() {    return TFLTCLASSID_CFILTERTEXTMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CGlobalDataMngrXmlRWKeys::CFilterTextMngrKey();     }
	virtual long XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CExBaseObject* pObj);
	virtual BOOL CopyOwn(CExBaseObject* pDest);
	virtual CExBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CString m_strFile;

//˽�г�Ա�������ʷ���
public:
	virtual BOOL OpenXmlFile(const CString &strFile);
	virtual BOOL SaveXmlFile();
	
	CFilterText* AddText(const CString &strText);
};

