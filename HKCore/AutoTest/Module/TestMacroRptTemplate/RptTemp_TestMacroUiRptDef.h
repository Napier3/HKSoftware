//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//RptTemp_TestMacroUiRptDef.h  CRptTemp_TestMacroUiRptDef

#pragma once

#include "TestMacroRptTemplateGlobal.h"


#include "RptTemp_MacroCharItems.h"
#include "RptTemp_MacroTest.h"
#include "RptTemp_ReportTemplateDef.h"
#include "RptTemp_Group.h"

//ÿ�����Թ���ģ�飬���õġ��������������ļ����ĸ��ڵ㣺test-macro-ui-rpt-def
class CRptTemp_TestMacroUiRptDef : public CExBaseList
{
public:
	CRptTemp_TestMacroUiRptDef();
	virtual ~CRptTemp_TestMacroUiRptDef();


//���غ���
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

//˽�г�Ա����
private:
	CRptTemp_ReportTemplateDef *m_pReportTemplateDef;
	CRptTemp_Group *m_pItemsTec;  //2023-10-23 shaolei   ����windows�����Ҫ����д�������еġ�����Ҫ�󡱡����������ݱ���С��λ�����ɱ༭

//˽�г�Ա�������ʷ���
public:
	CRptTemp_ReportTemplateDef* GetReportTemplateDef()	{	return m_pReportTemplateDef;	}
	void SetReportTemplateDef(CRptTemp_ReportTemplateDef* pReportTemplateDef)	{	m_pReportTemplateDef = pReportTemplateDef;	}
	CRptTemp_Group* GetItemsTec()	{	return m_pItemsTec;	}
	void SetItemsTec(CRptTemp_Group* pItemsTec)	{	m_pItemsTec = pItemsTec;	}

//���Ա������ʷ���
public:
	CRptTemp_MacroTest* FindMacroTestByMacroID(const CString &strMacroID, CExBaseList *pListParas);
	CRptTemp_MacroCharItems* FindMacroCharItemsByMacroID(const CString &strMacroID);
};

