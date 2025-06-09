//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprValueCal.h  CXExprValueCal

#pragma once

#include "XExprBase.h"

//数据运算，根据数据1和数据2，做运算后，运算结果再和基准值作误差判断
//其中，real是百分比误差，不是相对误差。是运算结果/基准值*100%。目前仅用于遥测试验
class CXExprValueCal : public CXExprBase
{
public:
	CXExprValueCal();
	virtual ~CXExprValueCal();

	CString  m_strCalOptr;  //运算符：+、-、*、/
	CString  m_strMode;  //误差判断模式：abs、real
	CString  m_strOptr;  //误差结果与误差限的比较逻辑：<= 或者 <

//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUECAL;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueCalKey();     }
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
	CXExprValueCalRslt *m_pValueCalRslt;  //数据1和数据2作运算后，形成的运算结果，输出值
	CXExprValueStd *m_pValueStd;  //作误差计算的基准值，输入值
	CXExprValueError *m_pError;   //误差数据对象（误差限），输入值
	CXExprValueRslt *m_pValueRslt;  //误差判断结果，是否满足误差限，输出值
	CXExprValueErrorRslt *m_pValueErrorRslt;  //误差计算结果，误差值，输出值

//私有成员变量访问方法
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);
	virtual void GetRsltExprValues_ExprMode(const CString &strMode, CExBaseList *pRsltExprValues);

	CXExprValue1* GetExprValue1();
	CXExprValue2* GetExprValue2();
	CXExprValueCalRslt* GetExprValueCalRslt();
	CXExprValueStd* GetExprValueStd();
	CXExprValueError* GetExprValueError();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRslt* GetExprValueErrorRslt();
};

