//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIBaseFileTypes.h  CUIBaseFileTypes

#pragma once

#include "UIBaseGlobal.h"


#include "UIBaseFileType.h"

class CUIBaseFileTypes : public CExBaseList
{
public:
	CUIBaseFileTypes();
	virtual ~CUIBaseFileTypes();

	CString m_strRootPath;
	CString m_strRootName;
	long    m_bOnllySearchMainTypeFile;

//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASEFILETYPES;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseFileTypesKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	CString GetRootPath();
	CString GetRootName();
	void InitXFileTypes(CXFileTypes *pXFileTypes);
	void InitXFilePostfix(CExBaseList &oList);
};

