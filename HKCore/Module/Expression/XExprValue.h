//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XExprValue.h  CXExprValue

#pragma once

#include "XExprGlobal.h"

class CXExprValue : public CExBaseObject
{
public:
	CXExprValue();
	virtual ~CXExprValue();

/*
m_strType：绑定的数据对象的种类：
包括：dataset、sys-para、global-para、report、number(数值类型，无绑定数据)、script(计算表达式)

m_strValueType：m_strValue值的数据类型：bool、number、utc_time等
m_strValueID：绑定的数据对象的ID。当没有绑定时，m_strValueID为空字符串
m_strValueName：参数的名称。当没有绑定数据对象时，参数的名称以该属性为准。绑定时，以被绑定参数的名称为准
m_strValueUnit：参数的单位。当没有绑定数据对象时，参数的单位以该属性为准。绑定时，以被绑定参数的单位为准
m_strItemPath：当绑定的数据对象是report数据时，该属性记录report对象所属的项目的相对路径
*/
	CString  m_strType;   
	CString  m_strValue;
	CString  m_strValueID;
	CString  m_strValueName;
	CString  m_strValueUnit;   //单位。暂时只处理时间类的单位。ms或s
	CString  m_strValueType;
	CString  m_strItemPath;
//重载函数
public:
	virtual UINT GetClassID() {    return XEXPRCLASSID_CXEXPRVALUE;   }
	virtual BSTR GetXmlElementKey()  {      return CXExprXmlRWKeys::CXExprValueKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

protected:
	BOOL m_bRelCalVal;  //是否是相对误差计算结果

//私有成员变量访问方法
public:
	virtual BOOL IsValueUint_ms();
	virtual void SetRelCalVal(BOOL bRelCalVal)	{	m_bRelCalVal = bRelCalVal;	}
	virtual void ExprRsltBind(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface);
	//2023-11-8 新增形参 CString &strValRet。用于返回字符串结果，例如“未动作”
	virtual BOOL Calc(CExBaseObject *pExprParent, CXExprCalInterface *pCalInterface, double &dValRet, CString &strValRet);
	virtual void GetRsltExprValues(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues, CExBaseList *pListXExprValues);
	virtual void GetRsltExprValues_RelPath(CExBaseObject *pExprParent, CExBaseList *pReportValues, CXExprCalInterface *pCalInterface, CExBaseList *pRsltExprValues);//仅处理相对项目路径
	virtual BOOL GetValueName(const CString &strID, CString &strName);
};

