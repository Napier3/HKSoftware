#pragma once

#include "PdfDBTable.h"

#define NO_USE_TABLE  _T("≤ª π”√")



class CSetsFileManualConfirmInterface
{
public:
	CSetsFileManualConfirmInterface(void);
	virtual ~CSetsFileManualConfirmInterface(void);

	virtual void ShowManualConfirm()=0;

public:
	CPdfDBTable *m_pPdfDBInfo;
	CExBaseList *m_plistTable;
};
