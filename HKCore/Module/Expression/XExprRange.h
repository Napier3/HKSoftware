//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprRange.h  CXExprRange

#pragma once

#include "XExprBase.h"

class CXExprRange : public CXExprBase
{
public:
	CXExprRange();
	virtual ~CXExprRange();

	CString m_strMinOptr;  //和最小值的比较逻辑：>= 或者 >
	CString m_strMaxOptr;  //和最大值的比较逻辑：<= 或者 <


//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRRANGE;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprRangeKey();     }
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
	CXExprValueMin *m_pValueMin;    //基准值-最小值，输入值
	CXExprValueMax *m_pValueMax;    //基准值-最大值，输入值
	CXExprValue *m_pValue;          //测试结果数据，输入值

	CXExprValueRslt *m_pValueRslt;  //测试结果与基准值的范围比较结果，输出值

//私有成员变量访问方法
public:
	virtual long Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual BOOL GetValueName(const CString &strID, CString &strName);

	CXExprValueMin* GetExprValueMin();
	CXExprValueMax* GetExprValueMax();
	CXExprValue* GetExprValue();
	CXExprValueRslt* GetExprValueRslt();
};

