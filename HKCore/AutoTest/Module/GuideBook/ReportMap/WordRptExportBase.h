#pragma once

#include "..\..\TaskMngr\TestProject.h"
#include "..\..\TestControl\TestControl.h"

//#include "..\..\Module\Office\ExcelReadWrite.h"

#define WM_EXPORT_REPORT_WORD  (WM_USER + 915)
#define WM_EXPORT_REPORT_RPC   (WM_USER + 916)

#define WORD_EXPORT_STATE_EXPORT_BEGIN     0
#define WORD_EXPORT_STATE_EXPORT_FINISH    1
#define WORD_EXPORT_STATE_CMBN_BEGIN        2
#define WORD_EXPORT_STATE_CMBN_FINISH       3

class CWordRptExportBase : public CExBaseList
{
public:
	CWordRptExportBase(void);
	virtual ~CWordRptExportBase(void);

	void AttachMsgRcvWnd(CWnd *pWnd, UINT nMsg);
	void SetShowWordApp(BOOL bShow)	{	m_bShowWordApp = bShow;	}
	void SetExportDetailWord(BOOL b)	{	m_bExportDetailWord = b;	}
	void SetCloseWordApp(BOOL b)	{	m_bCloseWordApp = b;	}
	void SetCmbnMgrp(BOOL bShow)	{	m_bCmbnMgrp = bShow;	}
	void SetCmbnMgrp(const CString &strCmbnDestPath, const CString &strWordFileSubPath , const CString &strXmlFileSubPath , const CString &strGbrptFileSubPath);
	void SetCmbnMgrpExportUse(BOOL bUseXmlFile, BOOL bUseGbrptFile);
	void SetUseUpdateGudeBook(BOOL bUseUpdateGudeBook)	{	m_bUseUpdateGudeBook = bUseUpdateGudeBook;	}
	void SetNotExportErrRpt(BOOL bNotExportErrRpt)	{	m_bNotExportErrRpt = bNotExportErrRpt;	}
	
	void AttachGuideBook(CGuideBook *pGuideBook);

	//虚函数
	virtual void ExportReports(CExBaseList &listTestControls, CExBaseList &listTestProject, CWnd *pMsgWnd)=0;
	virtual void CmbnReports(CExBaseList &listTestControls, CWnd *pMsgWnd)=0;
	
	//导出单个报告
	virtual void ExportReport(CTestControlBase *pTestControl)=0;

	virtual void ExportDetailWord(CTestControlBase *pTestControl)=0;
	virtual BOOL AddReportFileWord(const CString &strGbFile)=0;

	virtual void ExportReport_Values(const CString &strTitle, CValues *pValues)=0;
	virtual void ExportReport_Datasets(const CString &strTitle, CDvmDataset *pDvmDataset)=0;
	virtual void InsertTitle(const CString &strTitle, long nTitleLevel)=0;
	virtual void GotoDocEnd()=0;

protected:
	CExBaseList *m_pListTestControls;
	CExBaseList *m_pListTestProject;
	UINT m_nExportMsg;
	CWnd *m_pExportMsgRcvWnd;
	BOOL m_bShowWordApp;
	BOOL m_bExportDetailWord;
	BOOL m_bCmbnMgrp;
	BOOL m_bUseUpdateGudeBook;
	BOOL m_bNotExportErrRpt;

	CString m_strCmbnDestPath;
	//2021-1-2 lijunqing Word、XML、Gbrpt，使用单独的文件夹导出
	CString m_strWordFileSubPath, m_strXmlFileSubPath, m_strGbrptFileSubPath;
	BOOL m_bCmbnExort_XML, m_bCmbnExort_GBRPT;

	//在批量导出模式下，可以选择测试模板，使用新的测试模板、报告模板进行报告的导出
	CGuideBook *m_pNewGuideBook;
	CString m_strNewWordRptFile;
	BOOL m_bCloseWordApp;
	
	void SaveFinalXMLReport(CTestControlBase *pTestControl);
	void ExportReport(CTestControlBase *pTestControl, CTestProject *pTestProject, CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd);
	void ExportReport_AllWord(CTestControlBase *pTestControl, CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd);
	void ExportReport_Word(CTestControlBase *pTestControl, CBinarySerialBuffer &oBuffer, CWnd *pMsgWnd, const CString &strDocFile);

	void CmbnMgrpReport(CTestControlBase *pTestControl, CTestProject *pTestProject, CWnd *pMsgWnd);
	void CmbnMgrpReport(CTestControlBase *pTestControl, CTestControlBase *pGbrpt, long nIndex);
	void CopyReportFileToDest(CTestControlBase *pTestControl);

	void ExportDetailWord_GbItem(CGbItemBase *pGbItem);
	void ExportDetailWord_CommCmd(CCommCmd *pCommCmd);
	void ExportDetailWord_MacroTest(CMacroTest *pMacroTest);
	void ExportDetailWord_Safety(CSafety *pSafety);
	void ExportDetailWord_SysParaEdit(CSysParaEdit *pSysparaEdit);

protected:
// 	long m_nExcelRowIndex;

	virtual void ExportDetailExcel(CTestControlBase *pTestControl);
// 	virtual BOOL AddReportFileExcel(const CString &strGbFile);
// 	virtual void ExportDetailExcel_GbItem(CGbItemBase *pGbItem);
// 	virtual void ExportReport_Values_Excel(const CString &strTitle, CValues *pValues);
// 	virtual void ExportReport_Values_Excel(const CString &strTitle, CValues *pValues, CExBaseList *pListParas);
// 	virtual void ExportReport_Datasets_Excel(const CString &strTitle, CDvmDataset *pDvmDataset);
// 	virtual void InsertTitle_Excel(const CString &strTitle, long nCol, long nTitleLevel);
};
