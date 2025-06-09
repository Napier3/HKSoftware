//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterText.h  CFilterText

#pragma once

#include "FilterTextGlobal.h"



class CFilterText : public CExBaseObject
{
public:
	CFilterText();
	virtual ~CFilterText();


//重载函数
public:
	virtual UINT GetClassID() {    return FLTCLASSID_CFILTERTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CFilterTextXmlRWKeys::CFilterTextKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
	CString GetFile();
	void SetFile(const CString &strFile);
};

