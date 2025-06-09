//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprErrorEx_I.h  CXExprErrorEx_I

#pragma once

#include "XExprBase.h"
//扩展误差判断：测试结果参数，和基准值算误差值，误差值再和误差限作误差判断
//支持“绝对误差”、“相对误差”、“绝对误差 或 相对误差”、“绝对误差 和 相对误差”、“组合误差”
//绝对误差判断方法：误差值 = 实测值 - 整定值。1、误差 = 0 时，合格。2、误差 > 0 时，误差判定小于正误差，为合格.3、误差 < 0 时，误差的绝对值判定小于负误差，为合格
class CXExprErrorEx_I : public CXExprBase
{
public:
	CXExprErrorEx_I();
	virtual ~CXExprErrorEx_I();


	CString  m_strMode;  //误差判断模式：abs、real、or、and、combined
	CString  m_strOptr;  //误差结果与误差限的比较逻辑：<= 或者 <（仅限于相对误差）
//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRERROREX_I;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprErrorEx_IKey();     }
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
	CXExprValueErrorAbs_P *m_pErrorAbs_P;   //绝对误差数据对象（绝对误差限-正值）
	CXExprValueErrorAbs_N *m_pErrorAbs_N;   //绝对误差数据对象（绝对误差限-负值）

	CXExprValueRslt *m_pValueRslt;  //误差判断结果，是否满足误差限，输出值
	CXExprValueErrorRelRslt *m_pValueErrorRelRslt;  //相对误差计算结果，相对误差值，输出值
	CXExprValueErrorAbsRslt *m_pValueErrorAbsRslt;  //绝对误差计算结果，绝对误差值，输出值

//私有成员变量访问方法
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValStd, double &dVal, double &dErrRel, double &dErrAbs_P, double &dErrAbs_N
		, CString &strValStd, CString &strValue, CString &strErrorRel, CString &strErrorAbs_P, CString &strErrorAbs_N);
	long Calc_Abs(double &dCal, double dValStd, double dVal, double dErrAbs_P, double dErrAbs_N);
	long Calc_Rel(double &dCal, double dValStd, double dVal, double dErrRel);
	long Calc_Or(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs_P, double dErrAbs_N);
	long Calc_And(double &dCalRel, double &dCalAbs, double dValStd, double dVal, double dErrRel, double dErrAbs_P, double dErrAbs_N);
	long Calc_Combined(double &dCal, double dValStd, double dVal, double dErrRel, double dErrAbs_P, double dErrAbs_N);
	long Calc_NotAct(double dVal);  //未动作 | 不动作。当成是cmp特殊处理，固定判定动作时间 < 0.001为合格
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue* GetExprValue();
	CXExprValueStd* GetExprValueStd();
	CXExprValueErrorRel* GetExprValueErrorRel();
	CXExprValueErrorAbs_P* GetExprValueErrorAbs_P();
	CXExprValueErrorAbs_N* GetExprValueErrorAbs_N();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRelRslt* GetExprValueErrorRelRslt();
	CXExprValueErrorAbsRslt* GetExprValueErrorAbsRslt();
};

