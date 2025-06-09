//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_MacroTest.h  CRptTemp_MacroTest

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "RptTemp_ReportTemplateDef.h"
#include "RptTemp_ReportsDef.h"
#include "RptTemp_ReportTemplate.h"
#include "RptTemp_Reports.h"
#include "RptTemp_Enable.h"

class CRptTemp_ReportTemplateDef;

class CRptTemp_MacroTest : public CExBaseList
{
public:
	CRptTemp_MacroTest();
	virtual ~CRptTemp_MacroTest();


	CString  m_strMacro_Id;
	//报告导出模式：
	//1、item：表示一个电气量项目，单独生成一个word表格。用于动作时间、动作值测试
	//2、items：表示最小的叶子CItems节点，下面所有的电气量项目，生成一个统一的表格
	CString  m_strRpt_Mode;  
//重载函数
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_MACROTEST;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_MacroTestKey();     }
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
	CRptTemp_ReportsDef *m_pRpeortsDef;
	CRptTemp_ReportTemplateDef *m_pReportTemplateDef;
	CRptTemp_Reports *m_pRpeorts;
	CRptTemp_ReportTemplate *m_pReportTemplate;
	CRptTemp_Enable *m_pEnable;

//私有成员变量访问方法
public:
	CRptTemp_ReportsDef* GetRpeortsDef()	{	return m_pRpeortsDef;	}
	void SetRpeortsDef(CRptTemp_ReportsDef* pRpeortsDef)	{	m_pRpeortsDef = pRpeortsDef;	}
	CRptTemp_ReportTemplateDef* GetReportTemplateDef()	{	return m_pReportTemplateDef;	}
	void SetReportTemplateDef(CRptTemp_ReportTemplateDef* pReportTemplateDef)	{	m_pReportTemplateDef = pReportTemplateDef;	}
	CRptTemp_Reports* GetRpeorts()	{	return m_pRpeorts;	}
	void SetRpeorts(CRptTemp_Reports* pRpeorts)	{	m_pRpeorts = pRpeorts;	}
	CRptTemp_ReportTemplate* GetReportTemplate()	{	return m_pReportTemplate;	}
	void SetReportTemplate(CRptTemp_ReportTemplate* pReportTemplate)	{	m_pReportTemplate = pReportTemplate;	}

//属性变量访问方法
public:
	CRptTemp_Reports* AddReprots();
	BOOL IsEnable(CExBaseList *pParas);
};

