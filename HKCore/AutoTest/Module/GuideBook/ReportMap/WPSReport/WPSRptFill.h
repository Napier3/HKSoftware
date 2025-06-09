#pragma once

#include "../../ReportMap/WordRptFillBase.h"
#include "../../../../../Module/Office/WPS.h"
#include "../../../../../Module/Office/WPSCommandBarMngr.h"

// #include "stack"
// using namespace std;

class CWPSRptBkmkMgrpCmbn : public CExBaseObject
{
public:
	CWPSRptBkmkMgrpCmbn()
	{
		m_pBkmkRef = NULL;
		m_oBkmk = NULL;
	}
	virtual ~CWPSRptBkmkMgrpCmbn()
	{
		m_pBkmkRef = NULL;

		try
		{
			m_oBkmk = NULL;
		}
		catch (...)
		{
		}
	}

	CString m_strValue;
	WPS::Bookmark m_oBkmk;
	CRptBkmk *m_pBkmkRef;
};

class CRptFillWPSApp : public CRptFillAppBase
{
public:
	CRptFillWPSApp();
	virtual ~CRptFillWPSApp();

	static CRptFillAppBase* New()	{	return new CRptFillWPSApp();	}
public:
	WPS::_Application m_WPSApp;
	WPS::_Application GetWPSApp(BOOL bShow=FALSE);

	CWPSCommandBarMngr m_WPSCommandBarMngr;

public:
	virtual void CreateApplication(BOOL bShow=FALSE,long nHideAllCmdbars=0); 
	virtual void SetViewSettings();
	virtual void RestoreViewSettings();
	virtual	void CloseApplication();	
	virtual void RestoreCommandBars();
};

class CWPSRptFill :	public CWordRptFillBase, public CExBaseList
{
public:
	CWPSRptFill(void);
	virtual ~CWPSRptFill(void);

	long OpenOnly(const CString  &strReportFile);
	
public:
	WPS::_Document m_oDoc;
	
	CRptFillWPSApp* m_pWPSApp;

	//重载父类成员虚函数
public:
	virtual CString GetReportFillClassID()		{		return REPORTFILL_PROGID_WPS;	};
	virtual long New(CString strReportMapFile, CString strReportTemplFile, CString strReportFile, BOOL bFirst);
	virtual long Open(const CString  &strReportFile, BOOL bFirst);
	virtual long Save();
	virtual long SaveAs(CString  strRptFile);
	virtual long Close(long nSave);
	virtual void CloseDoc(DWORD dwFlag=0);

	virtual BOOL IsValidApp();
	virtual BOOL IsValidDoc();

	virtual void AdjustWordWindow();
	virtual BOOL CloseWordDocWindow();
	virtual BOOL ActiveWindow(const CString &strTitle);

	virtual BOOL AddNewReport(const CString &strRptTmplFile);
	virtual long FillReport(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible);

	virtual void PrintReport();
	virtual void ExportPdf();
	virtual void ZoomReport(long nPercentage);
	virtual long GetZoomReport();

	//调整报告
	virtual long AdjustReport_DelArea(CRptArea *pArea);
	
	virtual long LocateReport(CRptBkmk *pBkmk);
	virtual long GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos);

	virtual void EmptyReportText();
	virtual void DeleteBkmk(const CString &strBkmk);
	
	//2019-7-19  书签的系统处理
	virtual void AdjustReport_DelRow(CRptBkmk *pBkmk);
	virtual void AdjustReport_DelCol(CRptBkmk *pBkmk);

private:
	WPS::Cells GetCells(CRptBkmk *pBkmk, BOOL bRowMode);
	long GetBkmkPos(WPS::_Document &oDoc, CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos);
	BOOL GetBkmkRowCol(CRptBkmk *pRptBkmk, WPS::Table &oTable, WPS::Cells &oCells);
	void DeleteBkmk(WPS::Bookmarks bookmarks, const CString &strBkmk);

	void ClearBkmksText(CExBaseList *pList, WPS::Selection &sel, WPS::Bookmarks &bookmarks);
	void ClearBkmkText(CRptBkmk *pBkmk, WPS::Selection &sel, WPS::Bookmarks &bookmarks);
	void After_Put_Text(WPS::Selection &sel, WPS::Bookmark &bookmark, long lRangeEndPrev);

public:
	//填写报告相关函数
	//2021-10-16  lijunqing
	virtual void FillReportDatasetRowMode(CRptData *pData, CDvmDataset *pDataset);

	void FillReportGroupColMode(CRptData *pData, CReport *pReport, CShortData * oTagDataDef);
	void FillReportCell(const _bstr_t &strValue, WPS::Cell oCell);
	void FillReport_Cell(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE);
	void FillReport_Cell(const CString &strValue, WPS::Bookmark &bookmark, long nRptIndex, BOOL bSetColor=FALSE);
	void FillReport_Row(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE);
	void FillReport_Col(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE);
	CString GetBkmkText(WPS::Bookmark &bookmark);
	CString GetBkmkText(WPS::_Document &oDoc, CRptBkmk *pBkmk);

public:
	virtual void CmbmMgrpt(CRptFillInterface *pRptFill, long nMgbrpIndex);
	virtual void CmbmMgrpt(CExBaseList *pListItems, CWordRptFillBase *pRptFill);
	virtual void CmbmMgrpt(CItems *pItems, CWordRptFillBase *pRptFill);
	virtual void CmbmMgrpt(CRptArea *pArea, CWordRptFillBase *pRptFill);
	virtual void FillReportFile(const CString &strValue, CRptBkmk *pBkmk);
	virtual void FillReportClipboard(CRptBkmk *pBkmk);

	BOOL CmbnSelectBkmk(CRptBkmk *pBkmk, WPS::_Document &oDoc);
	BOOL CmbnCopyMgrpt(CRptArea *pArea, WPS::_Document &oDoc);
	void CmbnPasteMgrpt(CRptBkmk *pEndBkmk);

	//标签合并部分
	void InitWordRptBkmkMgrpCmbn();
	void InitWordRptBkmkMgrpCmbn(CExBaseList *pList, WPS::Bookmarks &oBookmarks);
	void WPSRptBkmkMgrpCmbn(WPS::_Document &oDoc);

	void WPSRptBkmkMgrpCmbn(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, WPS::_Document &oDoc);
	void WPSRptBkmkMgrpCmbn_max_len(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WPSRptBkmkMgrpCmbn_min_len(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WPSRptBkmkMgrpCmbn_max_val(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WPSRptBkmkMgrpCmbn_min_val(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WPSRptBkmkMgrpCmbn_avg(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WPSRptBkmkMgrpCmbn_sum(CWPSRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
};
