﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttGdColDef_Fuc_Max.h  CSttGdColDef_Fuc_Max

#pragma once

#include "SttTestGridDefineGlobal.h"


#include "SttGdColDef_Para.h"
#include "SttGdColDef_TextComb.h"
#include "../../../../../Module/DataMngr/DvmValues.h"

//////////////////////////////////////////////////////////////CSttGdColDef_Fuc_Base//////////////////////////////////////////////////////////////////////////////////////////////////

class CSttGdColDef_Fuc_Base : public CExBaseList
{
public:
	CSttGdColDef_Fuc_Base();
	virtual ~CSttGdColDef_Fuc_Base();
	virtual BOOL GetTestRsltString(CDvmValues *pDvmValues,CString &strText);
};

////////////////////////////////////////////////////////////////CSttGdColDef_Fuc_Max////////////////////////////////////////////////////////////////////////////////////////////////

class CSttGdColDef_Fuc_Max : public CSttGdColDef_Fuc_Base
{
public:
	CSttGdColDef_Fuc_Max();
	virtual ~CSttGdColDef_Fuc_Max();

//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CSTTGDCOLDEF_FUC_MAX;   }
	virtual BSTR GetXmlElementKey()  {      return CSttTestGridDefineXmlRWKeys::CSttGdColDef_Fuc_MaxKey();     }
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
	virtual BOOL GetTestRsltString(CDvmValues *pDvmValues,CString &strText);
};

