#pragma once
#include "rpteditinterface.h"

class CHtmlRptEdit :
	public CRptEditInterface
{
public:
	CHtmlRptEdit(void);
	virtual ~CHtmlRptEdit(void);
	virtual CString GetReportEditClassID(){	return REPORTFILL_PROGID_HTML; };
	virtual CString GetReportSuffix(){ return _T("html");};
};
