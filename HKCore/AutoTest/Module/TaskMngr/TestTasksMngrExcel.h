#pragma once

#include "TestTasksMngr.h"

#define _TestTasksExcel_TitleID_ChannelNum                              _T("ChannelNum")
#define _TestTasksExcel_TitleID_CityCompany                             _T("CityCompany")
#define _TestTasksExcel_TitleID_CountyCompany                           _T("CountyCompany")
#define _TestTasksExcel_TitleID_ProjectName                             _T("ProjectName")
#define _TestTasksExcel_TitleID_TestDate                                _T("TestDate")
#define _TestTasksExcel_TitleID_SoftwareVersion                         _T("SoftwareVersion")

//////////////////////////////////////////////////////////////////////////
//CTestTasksMngrExcelTool
class CTestTasksMngrExcelTool : public CExBaseList
{
public:
	CTestTasksMngrExcelTool();
	virtual ~CTestTasksMngrExcelTool();

	static const CString g_strExcelFileFilter;

	static BOOL PopupOpenFileDialog_Excel(CWnd *pParentWnd, CString &strFile);
	static BOOL PopupSaveFileDialog_Excel(CWnd *pParentWnd, CString &strFile);

public:
	CTestTasksMngr* ImportFromExcel(CWnd *pParentWnd);
	BOOL ImportFromExcel(CTestTasksMngr *pTestTasksMngr, const CString &strExcelFile);
	CTestTasksMngr* ImportFromExcel(const CString &strExcelFile);
	
protected:
	CString m_strDvIDKey;
};

