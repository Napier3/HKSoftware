//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//FuncParas.h  CFuncParas

#pragma once

#include "DllCallGlobal.h"

#include "..\..\..\Module\DataMngr\DvmData.h"


class CFuncParas : public CDvmData
{
public:
	CFuncParas();
	virtual ~CFuncParas();


//重载函数
public:
	virtual UINT GetClassID() {    return DLCLCLASSID_CFUNCPARAS;   }
	virtual BSTR GetXmlElementKey()  {      return CDllCallXmlRWKeys::CFuncParasKey();     }
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
	void InitByString_Equation(const CString &strParas);
};

