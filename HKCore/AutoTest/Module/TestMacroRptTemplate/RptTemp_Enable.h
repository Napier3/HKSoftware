//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//ItemsGenEnable.h  CRptTemp_Enable

#pragma once

#include "TestMacroRptTemplateGlobal.h"

class CRptTemp_ParaOptr : public CExBaseObject
{
public:
	CRptTemp_ParaOptr();
	virtual ~CRptTemp_ParaOptr();


	CString  m_strOptr;
	CString  m_strValue;
	//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_PARAOPTR;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ParaOptrKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);

	//私有成员变量
private:

	//私有成员变量访问方法
public:

	//属性变量访问方法
public:
	BOOL IsEnable_Optr_Eql()	{	return m_strOptr == RPT_TEMPLATE_ENABLE_OPTR_EQL;	}
	BOOL IsEnable_Optr_UnEql()	{	return m_strOptr == RPT_TEMPLATE_ENABLE_OPTR_UNEQL;	}
	BOOL IsEnable(CExBaseList *pParas);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRptTemp_Enable : public CExBaseList
{
public:
	CRptTemp_Enable();
	virtual ~CRptTemp_Enable();

	CString  m_strMode;  //使能模式：与=and；或=or；
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_ENABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_EnableKey();     }
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

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL IsEnableMode_And()	{	return m_strMode == RPT_TEMPLATE_ENABLE_MODE_AND;	}
	BOOL IsEnableMode_Or()	{	return m_strMode == RPT_TEMPLATE_ENABLE_MODE_OR;		}
	BOOL IsEnable(CExBaseList *pParas);
	BOOL IsEnable_And(CExBaseList *pParas);
	BOOL IsEnable_Or(CExBaseList *pParas);

};

