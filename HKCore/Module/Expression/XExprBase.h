//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprBase.h  CXExprBase

#pragma once

#include "XExprGlobal.h"
#include "XExprValue_Ex.h"
#include "../DataMngr/DvmValue.h"

class CXExprBase : public CExBaseList
{
public:
	CXExprBase();
	virtual ~CXExprBase();

	CString m_strUse;   //该属性用于保存文件
	long m_nIsUse;   //是否启用，该属性用于逻辑判断
	long m_nResult;
	long m_nCntRslt; //是否参与结论评判。默认为1。配置为0，表示表达式只作计算，不参与最终结论评判

//重载函数
public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual void InitAfterRead();

public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface) = 0;
	virtual long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes)	{	return 0;	}
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface) = 0;
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues) = 0;

	virtual void GetRsltExprValues_ExprMode(const CString &strMode, CExBaseList *pRsltExprValues);
	virtual BOOL ExprModeValid(const CString &strMode);
	virtual BOOL GetValueName(const CString &strID, CString &strName)	{	return FALSE;	}

};

