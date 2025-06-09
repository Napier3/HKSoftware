//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmResultParas.h  CTmResultParas

#pragma once

#include "TestMacroGlobal.h"


class CTmResultParas : public CShortDatas
{
public:
	CTmResultParas();
	virtual ~CTmResultParas();


//重载函数
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMRESULTPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmResultParasKey();     }
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

//私有成员变量
private:

//私有成员变量访问方法
public:
};


class CTmSearchResultParas : public CShortDatas
{
public:
	CTmSearchResultParas();
	virtual ~CTmSearchResultParas();


//重载函数
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMSEARCHRESULTPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmSearchResultParasKey();     }
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

