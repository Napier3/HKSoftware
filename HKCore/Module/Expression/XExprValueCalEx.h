//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprValueCalEx.h  CXExprValueCalEx

#pragma once

#include "XExprBase.h"

//扩展数据运算，根据数据1和数据2，做运算后，运算结果再和基准值作扩展误差判断
//扩展误差判断，包括：real、abs、or、and
class CXExprValueCalEx : public CXExprBase
{
public:
	CXExprValueCalEx();
	virtual ~CXExprValueCalEx();

	CString  m_strCalOptr;  //运算符：+、-、*、÷
	CString  m_strMode;  //误差判断模式：abs、real、or、and
	CString  m_strOptr;  //误差结果与误差限的比较逻辑：<= 或者 <

//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUECALEX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueCalExKey();     }
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

	//WriteXml
	//virtual long XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);	

//私有成员变量
private:
	CXExprValue1 *m_pValue1;      //数据1，输入值
	CXExprValue2 *m_pValue2;      //数据2，输入值
	CXExprValueStd *m_pValueStd;  //作误差计算的基准值，输入值
	CXExprValueErrorRel *m_pErrorRel;   //相对误差数据对象（相对误差限），输入值
	CXExprValueErrorAbs *m_pErrorAbs;   //绝对误差数据对象（绝对误差限），输入值

	CXExprValueCalRslt *m_pValueCalRslt;  //数据1和数据2作运算后，形成的运算结果，输出值
	CXExprValueRslt *m_pValueRslt;  //误差判断结果，是否满足误差限，输出值
	CXExprValueErrorRelRslt *m_pValueErrorRelRslt;  //相对误差计算结果，相对误差值，输出值
	CXExprValueErrorAbsRslt *m_pValueErrorAbsRslt;  //绝对误差计算结果，绝对误差值，输出值

//私有成员变量访问方法
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface
		, double &dValStd, double &dValue1, double &dValue2, double &dErrRel, double &dErrAbs
		, CString &strValStd, CString &strValue1, CString &strValue2, CString &strErrorRel, CString &strErrorAbs);
	long Calc_Abs(double &dCal, double dValStd, double dVal, double dErrAbs);
	long Calc_Rel(double &dCal, double dValStd, double dVal, double dErrRel);
	long Calc_Or(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs);
	long Calc_And(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue1* GetExprValue1();
	CXExprValue2* GetExprValue2();
	CXExprValueCalRslt* GetExprValueCalRslt();
	CXExprValueStd* GetExprValueStd();
	CXExprValueErrorRel* GetExprValueErrorRel();
	CXExprValueErrorAbs* GetExprValueErrorAbs();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRelRslt* GetExprValueErrorRelRslt();
	CXExprValueErrorAbsRslt* GetExprValueErrorAbsRslt();
};

