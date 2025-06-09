//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmFaultParas.h  CTmFaultParas

#pragma once

#include "TestMacroGlobal.h"


class CTmFaultParas : public CShortDatas
{
public:
	CTmFaultParas();
	virtual ~CTmFaultParas();


//重载函数
public:
	virtual UINT GetClassID() {    return TMCLASSID_CTMFAULTPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroXmlRWKeys::CTmFaultParasKey();     }
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);

//私有成员变量
private:

//私有成员变量访问方法
public:
};

