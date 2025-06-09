//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttContents.h  CSttContents

#pragma once

#include "../SttCmdDefineGlobal.h"
#include "SttContents.h"
#include "../../../../Module/DataMngr/DataGroup.h"

class CSttContents : public CDataGroup
{
public:
	CSttContents();
	virtual ~CSttContents();

    CString  m_strText;

//重载函数
public:
	virtual UINT GetClassID() {    return STTGBXMLCLASSID_CSTTCONTENTS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttCmdDefineXmlRWKeys::CSttContentsKey();     }
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

