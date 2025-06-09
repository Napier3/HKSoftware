#pragma once

#include "../../GuideBook/GuideBook.h"

class CRptBaseFill
{
public:
	CRptBaseFill(void);
	virtual ~CRptBaseFill(void);

	//long m_nMatchCount;
	CGuideBook *m_pGuideBook;

public:
	virtual CString GetReportFillClassID()=0;
	virtual long OpenRptTemplateFile(const CString  &strReportTemplateFile)=0;
	virtual long SaveRptFile(const CString &strRptFile)=0;
	virtual long FillRpt(CGuideBook* pGuideBook)=0;

public:	
	CValue* FindRptValueByID(const CString &strPath);
	CValue* FindRptDataByPath(const CString &strPath);

protected:
	CValue* FindRptDataByPath(CGbItemBase *pCurrItem, const CString &strPath);
	long MatchID(CGbItemBase *pCurrItem, const CString &strPath);
	CValue* FindRptData(CGbItemBase *pCurrItem, const CString &strPath);
};
