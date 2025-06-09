#pragma once

#include "../../../../../Module/LogicShapeMngr/VFlowExec_Visio.h"
#include "../../GuideBook.h"
#include "../../../TestControl/TestControlBase.h"

using namespace std;

class CVisioLogicRptFill : public CExBaseList
{
public:
	CVisioLogicRptFill(void);
	virtual ~CVisioLogicRptFill(void);
	
public:
	CTestControlBase *m_pTestControl;
	CVFlowExec_Visio *m_pVisioExec;
	HWND m_hVisioWnd;
	CWnd*	m_pParentWnd;
	HWND	m_hParentWnd;
	CString m_strFilePath;

public:
	long InitVisioRptFill();
	BOOL OpenVisioFile(const CString &strFile = _T(""));
	BOOL SaveVisioFile();
	void CloseFile();
	void CloseApplication();
	void AdjustReportWindowOnSize();//根据可显示试图的大小调整报告试图大小
	void SetParentWnd(CWnd* pParentWnd);
	void AdjustVisioWindow();
	void AdjustDocWindow(CWnd *pWnd);
	void OnItemTestFinished(CGbItemBase* pItem, const CString &strActLogic);
	CString GetItemPath(const CString &strOrignData, CString &strDataID);
	CString GetReportString(CGbItemBase* pItem, const CString &strDataID, CString &strDataType, CString &strUnit);
	BOOL GetReportString_CommCmd(CCommCmd* pCommCmd, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit);
	BOOL GetReportString_MacroTest(CMacroTest* pMacroTest, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit);
	BOOL GetReportString_SysParaEdit(CSysParaEdit *pSysparaEdit, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit);
	BOOL GetReportString_Safety(CSafety *pSafety, CReport* pReport, const CString &strDataID, CString &strValue, CString &strDataType, CString &strUnit);
	CString GetVisioFilePath();
	void LocateVisio(CExBaseObject *pItem);
};
