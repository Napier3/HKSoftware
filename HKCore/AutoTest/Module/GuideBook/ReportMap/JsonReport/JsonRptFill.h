#pragma once

#include "../../ReportMap/RptBaseFill.h"
#include "../../../../../Module/xml/JSON/CJSON.h"

class CJsonRptFill : public CRptBaseFill
{
public:
	CJsonRptFill(void);
	virtual ~CJsonRptFill(void);
	
protected:
	CJSON *m_pJsonDoc;

	void FreeJsonDoc();

	void Cal(CJSON *pJson);
	void CalChild(CJSON *pJson);
	void CalChildArr(CJSON *pJson);
	void Cal_String(CJSON *pJson);


	//重载父类成员虚函数
public:
	virtual CString GetReportFillClassID(){	return REPORTFILL_PROGID_JSON;	};
	virtual long OpenRptTemplateFile(const CString  &strReportFile);
	virtual long SaveRptFile(const CString &strRptFile);
	virtual long FillRpt(CGuideBook* pGuideBook);
	
};
