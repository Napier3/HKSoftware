//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define XEXPRCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00050000)
#define XEXPRCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00050000)

#define XEXPRCLASSID_CXEXPRVALUE       (XEXPRCLASSID_BASECLASS + 0X00000000)
#define XEXPRCLASSID_CXEXPRCMP       (XEXPRCLASSID_EXLISTCLASS + 0X00000001)
#define XEXPRCLASSID_CXEXPRERROR       (XEXPRCLASSID_EXLISTCLASS + 0X00000002)
#define XEXPRCLASSID_CXEXPRRANGE       (XEXPRCLASSID_EXLISTCLASS + 0X00000003)
#define XEXPRCLASSID_CXEXPRNODE       (XEXPRCLASSID_EXLISTCLASS + 0X00000004)
#define XEXPRCLASSID_CXEXPRVALUERSLT       (XEXPRCLASSID_BASECLASS + 0X00000005)
#define XEXPRCLASSID_CXEXPRVALUE1       (XEXPRCLASSID_BASECLASS + 0X00000006)
#define XEXPRCLASSID_CXEXPRVALUE2       (XEXPRCLASSID_BASECLASS + 0X00000007)
#define XEXPRCLASSID_CXEXPRVALUEMAX       (XEXPRCLASSID_BASECLASS + 0X00000008)
#define XEXPRCLASSID_CXEXPRVALUEMIN       (XEXPRCLASSID_BASECLASS + 0X00000009)
#define XEXPRCLASSID_CXEXPRVALUESTD       (XEXPRCLASSID_BASECLASS + 0X0000000A)
#define XEXPRCLASSID_CXEXPRVALUEERROR       (XEXPRCLASSID_BASECLASS + 0X0000000B)
#define XEXPRCLASSID_CXEXPRVALUEERRORRSLT       (XEXPRCLASSID_BASECLASS + 0X0000000C)
#define XEXPRCLASSID_CXEXPRVALUECAL       (XEXPRCLASSID_EXLISTCLASS + 0X0000000D)
#define XEXPRCLASSID_CXEXPRVALUECALRSLT       (XEXPRCLASSID_BASECLASS + 0X0000000E)
#define XEXPRCLASSID_CXEXPRERROREX       (XEXPRCLASSID_EXLISTCLASS + 0X0000000F)
#define XEXPRCLASSID_CXEXPRVALUEERRORREL       (XEXPRCLASSID_BASECLASS + 0X00000010)
#define XEXPRCLASSID_CXEXPRVALUEERRORABS       (XEXPRCLASSID_BASECLASS + 0X00000011)
#define XEXPRCLASSID_CXEXPRVALUEERRORRELRSLT       (XEXPRCLASSID_BASECLASS + 0X00000012)
#define XEXPRCLASSID_CXEXPRVALUEERRORABSRSLT       (XEXPRCLASSID_BASECLASS + 0X00000013)
#define XEXPRCLASSID_CXEXPRVALUECALEX       (XEXPRCLASSID_EXLISTCLASS + 0X00000014)
#define XEXPRCLASSID_CXEXPRERRORCOMBINED       (XEXPRCLASSID_EXLISTCLASS + 0X00000015)
#define XEXPRCLASSID_CXEXPRCAL       (XEXPRCLASSID_EXLISTCLASS + 0X00000016)
#define XEXPRCLASSID_CXEXPRQUERYMAX       (XEXPRCLASSID_BASECLASS + 0X00000017)
#define XEXPRCLASSID_CXEXPRQUERYMIN       (XEXPRCLASSID_BASECLASS + 0X00000018)
#define XEXPRCLASSID_CXEXPRRANGEEX       (XEXPRCLASSID_EXLISTCLASS + 0X00000019)
#define XEXPRCLASSID_CXEXPRCALSRPT       (XEXPRCLASSID_EXLISTCLASS + 0X00000020)


class CXExprXmlRWKeys : public CXmlRWKeys
{
protected:
	CXExprXmlRWKeys();
	virtual ~CXExprXmlRWKeys();
	static long g_nEXPRRef;

public:
	static CXExprXmlRWKeys* g_pXmlKeys;
	static CXExprXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCXExprNodeKey; //node
	BSTR m_strCXExprRangeKey; //range
	BSTR m_strCXExprRangeExKey; //range-ex
	BSTR m_strCXExprErrorKey; //error
	BSTR m_strCXExprErrorExKey; //error-ex
	BSTR m_strCXExprErrorCombinedKey; //error-combined
	BSTR m_strCXExprCmpKey; //cmp
	BSTR m_strCXExprValueKey; //value
	BSTR m_strTypeKey; //type
	BSTR m_strValueKey; //value
	BSTR m_strOptrKey; //optr
	BSTR m_strUseKey; //use
	BSTR m_strCntRsltKey; //cntrslt
	BSTR m_strCalOptrKey; //cal-optr
	BSTR m_strModeKey; //mode
	BSTR m_strLogicKey; //logic
	BSTR m_strValue1Key; //value1
	BSTR m_strValue2Key; //value2
	BSTR m_strValueStdKey; //value-std
	BSTR m_strErrorKey; //error
	BSTR m_strErrorRelKey; //error-rel	
	BSTR m_strErrorAbsKey; //error-abs	
	BSTR m_strValueMaxKey; //value-max
	BSTR m_strValueMinKey; //value-min
	BSTR m_strValueRsltKey; //value-rslt
	BSTR m_strValueErrorRsltKey;  //value-error 
	BSTR m_strValueErrorRelRsltKey;  //value-error-rel 
	BSTR m_strValueErrorAbsRsltKey;  //value-error-abs 
	BSTR m_strValueCalRsltKey;  //value-cal-rslt 
	BSTR m_strMinOptrKey;  //min-optr
	BSTR m_strMaxOptrKey;  //max-optr
	BSTR m_strValueIDKey;   //value-id
	BSTR m_strValueNameKey;   //value-name
	BSTR m_strValueUnitKey;   //value-unit
	BSTR m_strValueTypeKey;  //value-type
	BSTR m_strItemPathKey;  //item-path
	BSTR m_strCXExprValueCalKey;  //valuecal
	BSTR m_strCXExprValueCalExKey;  //valuecal-ex

	//2023-6-30新增
	BSTR m_strValueDstIDKey;   //value-dst-id
	BSTR m_strValueSrcIDKey;   //value-src-id
	BSTR m_strCXExprCalKey;      //expr-cal
	BSTR m_strCXQueryMaxKey;     //query-max
	BSTR m_strCXQueryMinKey;     //query-min
	BSTR m_strCXExprCalSRptKey;      //expr-cal-srpt
	BSTR m_strValueSrcIDHasKey;      //value-src-id-has
	BSTR m_strCalModeKey;      //cal-mode

public:
	static BSTR CXExprNodeKey()  {   return g_pXmlKeys->m_strCXExprNodeKey;  }
	static BSTR CXExprRangeKey()  {   return g_pXmlKeys->m_strCXExprRangeKey;  }
	static BSTR CXExprRangeExKey()  {   return g_pXmlKeys->m_strCXExprRangeExKey;  }
	static BSTR CXExprErrorKey()  {   return g_pXmlKeys->m_strCXExprErrorKey;  }
	static BSTR CXExprErrorExKey()  {   return g_pXmlKeys->m_strCXExprErrorExKey;  }
	static BSTR CXExprErrorCombinedKey()  {   return g_pXmlKeys->m_strCXExprErrorCombinedKey;  }
	static BSTR CXExprCmpKey()  {   return g_pXmlKeys->m_strCXExprCmpKey;  }
	static BSTR CXExprValueKey()  {   return g_pXmlKeys->m_strCXExprValueKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
	static BSTR OptrKey()  {   return g_pXmlKeys->m_strOptrKey;  }
	static BSTR ModeKey()  {   return g_pXmlKeys->m_strModeKey;  }
	static BSTR LogicKey()  {   return g_pXmlKeys->m_strLogicKey;  }

	static BSTR CXExprValue1Key()	{	return g_pXmlKeys->m_strValue1Key;	}	//value1
	static BSTR CXExprValue2Key()	{	return g_pXmlKeys->m_strValue2Key;	}	 //value2
	static BSTR CXExprValueStdKey()	{	return g_pXmlKeys->m_strValueStdKey;	}	 //value-std
	static BSTR CXExprValueErrorKey()	{	return g_pXmlKeys->m_strErrorKey;	}	 //error
	static BSTR CXExprValueErrorRelKey()	{	return g_pXmlKeys->m_strErrorRelKey;	}	 //error-rel
	static BSTR CXExprValueErrorAbsKey()	{	return g_pXmlKeys->m_strErrorAbsKey;	}	 //error-abs
	static BSTR CXExprValueMaxKey()	{	return g_pXmlKeys->m_strValueMaxKey;	}	 //value-max
	static BSTR CXExprValueMinKey()	{	return g_pXmlKeys->m_strValueMinKey;	}	 //value-min
	static BSTR CXExprValueRsltKey()	{	return g_pXmlKeys->m_strValueRsltKey;	}	 //value-rslt
	static BSTR CXExprValueErrorRsltKey()	{	return g_pXmlKeys->m_strValueErrorRsltKey;	}	 //value-error
	static BSTR CXExprValueErrorRelRsltKey()	{	return g_pXmlKeys->m_strValueErrorRelRsltKey;	}	 //value-error-rel
	static BSTR CXExprValueErrorAbsRsltKey()	{	return g_pXmlKeys->m_strValueErrorAbsRsltKey;	}	 //value-error-abs
	static BSTR CXExprValueCalKey()	{	return g_pXmlKeys->m_strCXExprValueCalKey;	}	 //valuecal
	static BSTR CXExprValueCalExKey()	{	return g_pXmlKeys->m_strCXExprValueCalExKey;	}	 //valuecal-ex
	static BSTR CXExprValueCalRsltKey()	{	return g_pXmlKeys->m_strValueCalRsltKey;	}	 //value-cal-rslt

	//2023-6-30新增
	static BSTR CXExprCalKey()	{	return g_pXmlKeys->m_strCXExprCalKey;	}	 //expr-cal
	static BSTR CXExprQueryMaxKey()	{	return g_pXmlKeys->m_strCXQueryMaxKey;	}	 //query-max
	static BSTR CXExprQueryMinKey()	{	return g_pXmlKeys->m_strCXQueryMinKey;	}	 //query-min
	static BSTR CXExprCalSRptKey()	{	return g_pXmlKeys->m_strCXExprCalSRptKey;	}	 //expr-cal-srpt
};



class CXExprConstGlobal
{
private:
	CXExprConstGlobal();
	virtual ~CXExprConstGlobal();

public:
	static CXExprConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CXExprConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

class CXExprCalInterface
{
public:
	//表达式计算，strType：表达式的类型；strExpression：表达式 , pExprParent表达式的父对象（测试项目）
	//strParentPath：当表达式绑定report数据时，report对象的父对象相对于表达式父对象的相对路径
	//返回double类型的浮点数
	//2024-7-5 新增形参 CString &strDataType。用于处理数据类型，例如：utc_time等
	virtual BOOL ExprCal(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, double &dValRet, CString &strValRet, const CString &strDataType) = 0;
	//表达式绑定，strType：表达式的类型；strExpression：表达式, pExprParent表达式的父对象，strValue：表达式的值
	virtual BOOL ExprRsltBind(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strDataName, const CString &strParentPath, const CString &strValue) = 0;
	virtual BOOL ExprGetValueAttr(CExBaseObject *pExprParent, const CString &strType, const CString &strExpression, const CString &strParentPath, CString &strValueAttrRet, const CString &strAttr) = 0;
	virtual void ExprCal_GetReportsForCal(CExBaseList* pListReportsForCal, long nCurrTestTimes, long nRepeatTimes, CExBaseObject* pExprParent) = 0;
	virtual BOOL ExprCal_Min(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet) = 0;  //计算最小值
	virtual BOOL ExprCal_Max(CExBaseList* pListReportsForCal, const CString &strExpression, double &dValRet) = 0;  //计算最大值
	virtual BOOL ExprCal_SRpt(CExBaseObject *pExprParent, const CString &strSrcIDHas, const CString &strCalMode, double &dValRet) = 0;  //计算单个报告中指定数据的max、min、avg
};

