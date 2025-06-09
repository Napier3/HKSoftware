//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//RptTemp_ReportTemplates.h  CRptTemp_ReportTemplates

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "RptTemp_ReportTemplate.h"

class CRptTemp_ReportTemplates : public CExBaseList
{
public:
	CRptTemp_ReportTemplates();
	virtual ~CRptTemp_ReportTemplates();


	//重载函数
public:
	virtual UINT GetClassID() { return MNGRCLASSID_CRPTTEMP_REPORTTEMPLATES; } //ftt 2024.6.17 change new ClassID
	virtual BSTR GetXmlElementKey() { return CTestMacroRptTemplateXmlRWKeys::CRptTemp_ReportTemplatesKey(); } //ftt 2024.6.17 change new key
	virtual long XmlReadOwn(CXmlRWNodeBase& oNode, CXmlRWKeys* pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase& oXMLDoc, CXmlRWElementBase& oElement, CXmlRWKeys* pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer& oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn = TRUE, BOOL bCopyChildren = FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString& strClassID, BOOL& bAddToTail, CXmlRWKeys* pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//ftt 2024.6.17 delete begin
//	//私有成员变量
//private:
//	CRptTemp_ReportTemplate* m_pReportTemplate;
//
//	//私有成员变量访问方法
//public:
//	CRptTemp_ReportTemplate* GetReportTemplate() { return m_pReportTemplate; }
//	void SetReportTemplate(CRptTemp_ReportTemplate* pReportTemplate) { m_pReportTemplate = pReportTemplate; }
//ftt 2024.6.17 delete end
 
	//属性变量访问方法
public:
};

