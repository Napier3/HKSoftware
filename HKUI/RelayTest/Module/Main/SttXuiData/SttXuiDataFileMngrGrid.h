﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttXuiDataFileMngrGrid.h  CSttXuiDataFileMngrGrid

#pragma once

#include "SttXMainConfigGlobal.h"

#include "SttXuiDataBase.h"

#include "SttXuiDataFileTypes.h"
#include "SttXuiDataCmd.h"

class CSttXuiDataFileMngrGrid : public CSttXuiDataBase
{
public:
	CSttXuiDataFileMngrGrid();
	virtual ~CSttXuiDataFileMngrGrid();


	long  m_nX;
	long  m_nY;
	long  m_nCx;
	long  m_nCy;
	CString  m_strEmit_Mode;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTXUIDATAFILEMNGRGRID;   }
	virtual BSTR GetXmlElementKey()  {      return CSttXMainConfigXmlRWKeys::CSttXuiDataFileMngrGridKey();     }
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
};

