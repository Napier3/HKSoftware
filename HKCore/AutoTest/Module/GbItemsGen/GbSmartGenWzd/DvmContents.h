//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmContents.h  CDvmContents

#pragma once

#include "GbSmartGenWzdGlobal.h"

class CDvmContents : public CDataGroup
{
public:
	CDvmContents();
	virtual ~CDvmContents();

    CString  m_strText;

//重载函数
public:
	virtual UINT GetClassID() {    return DTMCLASSID_CCONTENTS;   }
	virtual BSTR GetXmlElementKey()  {      return CGbSmartGenWzdXmlRWKeys::CDvmContentsKey();     }
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);

    virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
    virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);

	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);


//私有成员变量
private:


//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

