//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprErrorEx.h  CXExprErrorEx

#pragma once

#include "XExprBase.h"
//扩展误差判断：测试结果参数，和基准值算误差值，误差值再和误差限作误差判断
//支持“绝对误差”、“相对误差”、“绝对误差 或 相对误差”、“绝对误差 和 相对误差”、“组合误差”
class CXExprErrorEx : public CXExprBase
{
public:
	CXExprErrorEx();
	virtual ~CXExprErrorEx();


	CString  m_strMode;  //误差判断模式：abs、real、or、and、combined
	CString  m_strOptr;  //误差结果与误差限的比较逻辑：<= 或者 <
//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRERROREX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprErrorExKey();     }
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
	CXExprValue *m_pValue;        //结果数据对象，输入值
	CXExprValueStd *m_pValueStd;  //基准值，输入值
	CXExprValueErrorRel *m_pErrorRel;   //相对误差数据对象（相对误差限）
	CXExprValueErrorAbs *m_pErrorAbs;   //绝对误差数据对象（绝对误差限）

	CXExprValueRslt *m_pValueRslt;  //误差判断结果，是否满足误差限，输出值
	CXExprValueErrorRelRslt *m_pValueErrorRelRslt;  //相对误差计算结果，相对误差值，输出值
	CXExprValueErrorAbsRslt *m_pValueErrorAbsRslt;  //绝对误差计算结果，绝对误差值，输出值

//私有成员变量访问方法
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValStd, double &dVal, double &dErrRel, double &dErrAbs
		, CString &strValStd, CString &strValue, CString &strErrorRel, CString &strErrorAbs);
	long Calc_Abs(double &dCal, double dValStd, double dVal, double dErrAbs);
	long Calc_Rel(double &dCal, double dValStd, double dVal, double dErrRel);
	long Calc_Or(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs);
	long Calc_And(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs);
	long Calc_Combined(double &dCal, double dValStd, double dVal, double dErrRel, double dErrAbs);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue* GetExprValue();
	CXExprValueStd* GetExprValueStd();
	CXExprValueErrorRel* GetExprValueErrorRel();
	CXExprValueErrorAbs* GetExprValueErrorAbs();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRelRslt* GetExprValueErrorRelRslt();
	CXExprValueErrorAbsRslt* GetExprValueErrorAbsRslt();
};

