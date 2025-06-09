//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprNode.h  CXExprNode

#pragma once

#include "XExprCmp.h"
#include "XExprError.h"
#include "XExprErrorEx.h"
#include "XExprRange.h"
#include "XExprValueCal.h"
#include "XExprValueCalEx.h"
#include "XExprErrorCombined.h"
//#include "XExprCal.h"
#include "XExprRangeEx.h"

class CXExprNode : public CXExprBase
{
public:
	CXExprNode();
	virtual ~CXExprNode();


	CString  m_strLogic;
//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRNODE;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprNodeKey();     }
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
	CXExprValueRslt* m_pValueRslt;

//私有成员变量访问方法
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual long CalcEx(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes);
	long CalcEx_MaxMin(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, long nCurrTestTimes, long nRepeatTimes);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	CXExprValueRslt* GetValueRslt();

	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);
};

