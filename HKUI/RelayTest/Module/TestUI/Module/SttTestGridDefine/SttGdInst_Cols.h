﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdInst_Cols.h  CSttGdInst_Cols

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdInst_Col.h"
#include "SttGdGridDefine.h"

class CSttGdInst_Cols : public CExBaseList
{
public:
	CSttGdInst_Cols();
	virtual ~CSttGdInst_Cols();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDINST_COLS;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdInst_ColsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL GetGridColsTitleWidth(CString *pstrTitle,int *pnWidth,int nCols);
	void InitGridCols(CSttGdGridDefine *pSttGdGridDefine);
};

