//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_TestMacroUiRptDef.h  CRptTemp_TestMacroUiRptDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_MacroCharItems.h"
#include "RptTemp_MacroTest.h"
#include "RptTemp_ReportTemplateDef.h"
#include "RptTemp_Group.h"

//每个测试功能模块，配置的“报告数据配置文件”的根节点：test-macro-ui-rpt-def
class CRptTemp_TestMacroUiRptDef : public CExBaseList
{
public:
	CRptTemp_TestMacroUiRptDef();
	virtual ~CRptTemp_TestMacroUiRptDef();


//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TESTMACROUIRPTDEF;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TestMacroUiRptDefKey();     }
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
	CRptTemp_ReportTemplateDef *m_pReportTemplateDef;
	CRptTemp_Group *m_pItemsTec;  //2023-10-23 shaolei   南瑞windows软件，要求填写到报告中的“技术要求”、“报告数据保留小数位数”可编辑

//私有成员变量访问方法
public:
	CRptTemp_ReportTemplateDef* GetReportTemplateDef()	{	return m_pReportTemplateDef;	}
	void SetReportTemplateDef(CRptTemp_ReportTemplateDef* pReportTemplateDef)	{	m_pReportTemplateDef = pReportTemplateDef;	}
	CRptTemp_Group* GetItemsTec()	{	return m_pItemsTec;	}
	void SetItemsTec(CRptTemp_Group* pItemsTec)	{	m_pItemsTec = pItemsTec;	}

//属性变量访问方法
public:
	CRptTemp_MacroTest* FindMacroTestByMacroID(const CString &strMacroID, CExBaseList *pListParas);
	CRptTemp_MacroCharItems* FindMacroCharItemsByMacroID(const CString &strMacroID);
};

