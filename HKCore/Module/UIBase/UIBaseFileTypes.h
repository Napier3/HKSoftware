//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
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

//私有成员变量
private:

//私有成员变量访问方法
public:
	CString GetRootPath();
	CString GetRootName();
	void InitXFileTypes(CXFileTypes *pXFileTypes);
	void InitXFilePostfix(CExBaseList &oList);
};

