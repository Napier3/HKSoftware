//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprValueRslt.h  
//CXExprValueRslt,CXExprValue1,CXExprValue2,CXExprValueMin,CXExprValueMax,CXExprValueStd,CXExprValueError

#pragma once

#include "XExprValue.h"

//CXExprValueRslt
class CXExprValueRslt : public CXExprValue
{
public:
	CXExprValueRslt();
	virtual ~CXExprValueRslt();

//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUERSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueRsltKey();     }
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValue1
class CXExprValue1 : public CXExprValue
{
public:
	CXExprValue1();
	virtual ~CXExprValue1();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUE1;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValue1Key();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValue2
class CXExprValue2 : public CXExprValue
{
public:
	CXExprValue2();
	virtual ~CXExprValue2();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUE2;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValue2Key();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueMax
class CXExprValueMax : public CXExprValue
{
public:
	CXExprValueMax();
	virtual ~CXExprValueMax();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEMAX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueMaxKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueMin
class CXExprValueMin : public CXExprValue
{
public:
	CXExprValueMin();
	virtual ~CXExprValueMin();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEMIN;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueMinKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueStd
class CXExprValueStd : public CXExprValue
{
public:
	CXExprValueStd();
	virtual ~CXExprValueStd();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUESTD;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueStdKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueError   误差数据对象（误差限）
class CXExprValueError : public CXExprValue
{
public:
	CXExprValueError();
	virtual ~CXExprValueError();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERROR;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRel   相对误差数据对象（相对误差限）
class CXExprValueErrorRel : public CXExprValue
{
public:
	CXExprValueErrorRel();
	virtual ~CXExprValueErrorRel();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORREL;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorRelKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorAbs   绝对误差数据对象（绝对误差限）
class CXExprValueErrorAbs : public CXExprValue
{
public:
	CXExprValueErrorAbs();
	virtual ~CXExprValueErrorAbs();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORABS;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorAbsKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRslt   误差结果对象 = 计算得到的误差值
class CXExprValueErrorRslt : public CXExprValue
{
public:
	CXExprValueErrorRslt();
	virtual ~CXExprValueErrorRslt();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorRsltKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorRelRslt   相对误差结果对象 = 计算得到的相对误差值
class CXExprValueErrorRelRslt : public CXExprValue
{
public:
	CXExprValueErrorRelRslt();
	virtual ~CXExprValueErrorRelRslt();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORRELRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorRelRsltKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprValueErrorAbsRslt   绝对误差结果对象 = 计算得到的绝对误差值
class CXExprValueErrorAbsRslt : public CXExprValue
{
public:
	CXExprValueErrorAbsRslt();
	virtual ~CXExprValueErrorAbsRslt();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUEERRORABSRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueErrorAbsRsltKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};

//CXExprValueCalRslt   数据运算结果对象。两个数据对象作数据运算（+、-、*、÷）的结果对象
class CXExprValueCalRslt : public CXExprValue
{
public:
	CXExprValueCalRslt();
	virtual ~CXExprValueCalRslt();

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUECALRSLT;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueCalRsltKey();     }
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
};