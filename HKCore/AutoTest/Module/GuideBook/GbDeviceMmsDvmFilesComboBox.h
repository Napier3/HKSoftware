#pragma once

#include "../../../Module/FilterText/FilterTextComboBox.h"
#include "../../../Module/FilterText/FilterTextMngr.h"
#include "../../../Module/DataMngr/DvmDevice.h"

class CGbDeviceMmsDvmFilesComboBox :public CFilterTextComboBox
{
public:
	CGbDeviceMmsDvmFilesComboBox(void);
	virtual ~CGbDeviceMmsDvmFilesComboBox(void);

private:
	static CFilterTextMngr *g_pFilterTextMngr;
	static long g_nFilterTextMngrRef;
	
public:
	void InitGbDeviceMmsDvmFiles(const CString &strFile=_T(""));
	void BringCurrToTop();

	virtual void OnRbtnDelete();
	virtual void AddFilterText(CFilterText *pText);
	CFilterText* AddFilterText(CString &strFilterText);

private:
	virtual void GetAddString(CString &strText);
	virtual CString GetAddString2(const CString &strText);

public:
	virtual CFilterText* PopOpenDvmDlg(CString &strPath, CWnd *pParentWnd = NULL, const CString &strCaption=_T(""));
	virtual BOOL DeleteCurrSelObject();  //2021-1-8  lijunqing

};

