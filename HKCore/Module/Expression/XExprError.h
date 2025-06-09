//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprError.h  CXExprError

#pragma once

#include "XExprBase.h"
//误差判断：测试结果参数，和基准值算误差值，误差值再和误差限作误差判断
class CXExprError : public CXExprBase
{
public:
	CXExprError();
	virtual ~CXExprError();


	CString  m_strMode;  //误差判断模式：abs、real
	CString  m_strOptr;  //误差结果与误差限的比较逻辑：<= 或者 <
//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRERROR;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprErrorKey();     }
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
	CXExprValueError *m_pError;   //误差数据对象（误差限）

	CXExprValueRslt *m_pValueRslt;  //误差判断结果，是否满足误差限，输出值
	CXExprValueErrorRslt *m_pValueErrorRslt;  //误差计算结果，误差值，输出值

//私有成员变量访问方法
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValue* GetExprValue();
	CXExprValueStd* GetExprValueStd();
	CXExprValueError* GetExprValueError();
	CXExprValueRslt* GetExprValueRslt();
	CXExprValueErrorRslt* GetExprValueErrorRslt();
};

