//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprValueRslt.cpp  CXExprValueRslt


#include "stdafx.h"
#include "XExprValue_Ex.h"

CXExprValueRslt::CXExprValueRslt()
{
	//初始化属性
	m_strValue = _T("未计算");
	//初始化成员变量
}

CXExprValueRslt::~CXExprValueRslt()
{
}

CBaseObject* CXExprValueRslt::Clone()
{
	CXExprValueRslt *p = new CXExprValueRslt();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValue1::CXExprValue1()
{
	//初始化属性

	//初始化成员变量
}

CXExprValue1::~CXExprValue1()
{
}

CBaseObject* CXExprValue1::Clone()
{
	CXExprValue1 *p = new CXExprValue1();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValue2::CXExprValue2()
{
	//初始化属性

	//初始化成员变量
}

CXExprValue2::~CXExprValue2()
{
}

CBaseObject* CXExprValue2::Clone()
{
	CXExprValue2 *p = new CXExprValue2();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueMax::CXExprValueMax()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueMax::~CXExprValueMax()
{
}

CBaseObject* CXExprValueMax::Clone()
{
	CXExprValueMax *p = new CXExprValueMax();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueMin::CXExprValueMin()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueMin::~CXExprValueMin()
{
}

CBaseObject* CXExprValueMin::Clone()
{
	CXExprValueMin *p = new CXExprValueMin();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueStd::CXExprValueStd()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueStd::~CXExprValueStd()
{
}

CBaseObject* CXExprValueStd::Clone()
{
	CXExprValueStd *p = new CXExprValueStd();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueError::CXExprValueError()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueError::~CXExprValueError()
{
}

CBaseObject* CXExprValueError::Clone()
{
	CXExprValueError *p = new CXExprValueError();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueErrorRel::CXExprValueErrorRel()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueErrorRel::~CXExprValueErrorRel()
{
}

CBaseObject* CXExprValueErrorRel::Clone()
{
	CXExprValueErrorRel *p = new CXExprValueErrorRel();
	Copy(p);
	return p;
}

/////////////////////////////////////////////////////////////////////////
CXExprValueErrorAbs::CXExprValueErrorAbs()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueErrorAbs::~CXExprValueErrorAbs()
{
}

CBaseObject* CXExprValueErrorAbs::Clone()
{
	CXExprValueErrorAbs *p = new CXExprValueErrorAbs();
	Copy(p);
	return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRslt   误差结果对象 = 计算得到的误差值
CXExprValueErrorRslt::CXExprValueErrorRslt()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueErrorRslt::~CXExprValueErrorRslt()
{
}

CBaseObject* CXExprValueErrorRslt::Clone()
{
	CXExprValueErrorRslt *p = new CXExprValueErrorRslt();
	Copy(p);
	return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRelRslt   相对误差结果对象 = 计算得到的相对误差值
CXExprValueErrorRelRslt::CXExprValueErrorRelRslt()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueErrorRelRslt::~CXExprValueErrorRelRslt()
{
}

CBaseObject* CXExprValueErrorRelRslt::Clone()
{
	CXExprValueErrorRelRslt *p = new CXExprValueErrorRelRslt();
	Copy(p);
	return p;
}

void CXExprValueErrorRelRslt::ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface)
{
	//SetRelCalVal(TRUE);
	CXExprValue::ExprRsltBind(pExprParent, pCalInterface);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorAbsRslt   绝对误差结果对象 = 计算得到的绝对误差值
CXExprValueErrorAbsRslt::CXExprValueErrorAbsRslt()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueErrorAbsRslt::~CXExprValueErrorAbsRslt()
{
}

CBaseObject* CXExprValueErrorAbsRslt::Clone()
{
	CXExprValueErrorAbsRslt *p = new CXExprValueErrorAbsRslt();
	Copy(p);
	return p;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueCalRslt   数据运算结果对象。两个数据对象作数据运算（+、-、*、÷）的结果对象
CXExprValueCalRslt::CXExprValueCalRslt()
{
	//初始化属性

	//初始化成员变量
}

CXExprValueCalRslt::~CXExprValueCalRslt()
{
}

CBaseObject* CXExprValueCalRslt::Clone()
{
	CXExprValueCalRslt *p = new CXExprValueCalRslt();
	Copy(p);
	return p;
}