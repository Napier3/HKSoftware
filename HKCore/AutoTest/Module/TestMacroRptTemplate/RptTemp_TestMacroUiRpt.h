//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_TestMacroUiRpt.h  CRptTemp_TestMacroUiRpt

#pragma once

#include "TestMacroRptTemplateGlobal.h"
#include "RptTemp_ReportTemplate.h"
#include "RptTemp_Items.h"

class CRptTemp_TestMacroUiRpt : public CExBaseList
{
public:
	CRptTemp_TestMacroUiRpt();
	virtual ~CRptTemp_TestMacroUiRpt();


//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CRPTTEMP_TESTMACROUIRPT;   }
	virtual BSTR GetXmlElementKey()  {      return CTestMacroRptTemplateXmlRWKeys::CRptTemp_TestMacroUiRptKey();     }
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

//˽�г�Ա����
private:
	CRptTemp_ReportTemplate *m_pReportTemplate;

//˽�г�Ա�������ʷ���
public:
	CRptTemp_ReportTemplate* GetReportTemplate()	{	return m_pReportTemplate;	}
	void SetReportTemplate(CRptTemp_ReportTemplate* pReportTemplate)	{	m_pReportTemplate = pReportTemplate;	}

//���Ա������ʷ���
public:
};

