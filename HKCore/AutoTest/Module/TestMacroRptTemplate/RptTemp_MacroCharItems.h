//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_MacroCharItems.h  CRptTemp_MacroCharItems

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_RpeortDef.h"
#include "RptTemp_Rpeort.h"
#include "RptTemp_MacroTest.h"
#include "RptTemp_ReportTemplateDef.h"

class CRptTemp_MacroCharItems : public CExBaseList
{
public:
	CRptTemp_MacroCharItems();
	virtual ~CRptTemp_MacroCharItems();


	CString  m_strMacro_Id;
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_MACROCHARITEMS;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_MacroCharItemsKey();     }
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
	CRptTemp_ReportDef *m_pReportDef;
	CRptTemp_MacroTest *m_pMacroTest;
	CRptTemp_Report *m_pReport;
	CRptTemp_ReportTemplate *m_pReportTemplate;

//私有成员变量访问方法
public:
	CRptTemp_ReportTemplateDef* GetReportTemplateDef()	{	return m_pReportTemplateDef;	}
	void SetReportTemplateDef(CRptTemp_ReportTemplateDef* pReportTemplateDef)	{	m_pReportTemplateDef = pReportTemplateDef;	}
	CRptTemp_ReportDef* GetReportDef()	{	return m_pReportDef;	}
	void SetReportDef(CRptTemp_ReportDef* pReportDef)	{	m_pReportDef = pReportDef;	}
	CRptTemp_MacroTest* GetMacroTest()	{	return m_pMacroTest;	}
	void SetMacroTest(CRptTemp_MacroTest* pMacroTest)	{	m_pMacroTest = pMacroTest;	}
	CRptTemp_Report* GetReport()	{	return m_pReport;	}
	void SetReport(CRptTemp_Report* pReport)	{	m_pReport = pReport;	}
	CRptTemp_ReportTemplate* GetReportTemplate()	{	return m_pReportTemplate;	}
	void SetReportTemplate(CRptTemp_ReportTemplate* pReportTemplate)	{	m_pReportTemplate = pReportTemplate;	}

//属性变量访问方法
public:
	long GetMacroTestCount();
	CRptTemp_MacroTest* GetMacroTestByIndex(long nIndex);

};

