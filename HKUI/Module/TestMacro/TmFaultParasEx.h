﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmFaultParasEx.h  CTmFaultParasEx

#pragma once

#include "TestMacroGlobal.h"

#include "../DataMngr/DataGroup.h"


class CTmFaultParasEx : public CDataGroup
{
public:
	CTmFaultParasEx();
	virtual ~CTmFaultParasEx();


//重载函数
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMFAULTPARASEX;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmFaultParasExKey();     }
// 	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
// 	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
// 	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
// 	virtual void InitAfterRead();
// 	virtual BOOL IsEqualOwn(CBaseObject* pObj);
//	virtual BOOL CopyOwn(CBaseObject* pDest);
 	virtual CBaseObject* Clone();
// 	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
// 	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);


//私有成员变量
private:

//私有成员变量访问方法
public:
};

