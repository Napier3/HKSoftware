﻿//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprCal.h  

#pragma once
#include "XExprGlobal.h"

//CXExprQueryMax
class CXExprQueryMax : public CExBaseObject
{
public:
	CXExprQueryMax();
	virtual ~CXExprQueryMax();

	CString m_strValueSrcID;

//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRQUERYMAX;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprQueryMaxKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
	BOOL CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes, double &dValRet);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprQueryMin
class CXExprQueryMin : public CExBaseObject
{
public:
	CXExprQueryMin();
	virtual ~CXExprQueryMin();

	CString m_strValueSrcID;

	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRQUERYMIN;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprQueryMinKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

	//私有成员变量
private:

	//私有成员变量访问方法
public:
	BOOL CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes, double &dValRet);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
//CXExprCal
//用于固定计算误差最大值和最小值
class CXExprCal : public CExBaseList
{
public:
	CXExprCal();
	virtual ~CXExprCal();


	CString  m_strValue;  
	CString  m_strValueDstID;  //计算结果绑定回结果参数
	CString  m_strValueName;   //计算结果绑定回结果参数的名称
	//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRCAL;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprCalKey();     }
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

	//私有成员变量
private:
	CXExprQueryMax *m_pQueryMax;
	CXExprQueryMin *m_pQueryMin;

	//私有成员变量访问方法
public:
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual BOOL CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	void AddQueryMax(const CString &strValueSrcID);
	void AddQueryMin(const CString &strValueSrcID);
};