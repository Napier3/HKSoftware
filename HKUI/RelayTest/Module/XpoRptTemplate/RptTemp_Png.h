﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_Png.h  CRptTemp_Png

#pragma once

#include "TestMacroRptTemplateGlobal.h"

class CRptTemp_Png : public CExBaseObject
{
public:
	CRptTemp_Png();
	virtual ~CRptTemp_Png();

	CString  m_strPngPath;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_PNG;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_PngKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

