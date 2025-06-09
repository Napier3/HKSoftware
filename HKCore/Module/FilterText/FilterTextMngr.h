//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FilterTextMngr.h  CFilterTextMngr

#pragma once

#include "FilterTextGlobal.h"


#include "FilterText.h"

class CFilterTextMngr : public CExBaseList
{
        friend class CFilterText;

public:
	CFilterTextMngr();
	virtual ~CFilterTextMngr();

	BOOL IsChanged()	{	return m_bChanged;	}
	void SetChanged(BOOL b)	{	m_bChanged = b;	}

//重载函数
public:
	virtual UINT GetClassID() {    return FLTCLASSID_CFILTERTEXTMNGR;   }
	virtual BSTR GetXmlElementKey()  {      return CFilterTextXmlRWKeys::CFilterTextMngrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CString m_strFile;

	//作为文件进行
	CString m_strRootPath;

	BOOL m_bChanged;

//私有成员变量访问方法
public:
	virtual BOOL OpenXmlFile(const CString &strFile);
	virtual BOOL SaveXmlFile();
	
	CFilterText* AddText(const CString &strText);

	void SetRootPath(const CString &strRootPath);
};

