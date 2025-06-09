#pragma once

#include "../../ReportMap/WordRptFillBase.h"
#include "../../../../../Module/Office/msword9.h"
#include "../../../../../Module/Office/WordCommandBarMngr.h"
//#include "../../../TctrlCntrBaseApp.h"

#include "stack"
using namespace std;

class CWordRptBkmkMgrpCmbn : public CExBaseObject
{
public:
	CWordRptBkmkMgrpCmbn()
	{
		m_pBkmkRef = NULL;
		m_oBkmk = NULL;
	}
	virtual ~CWordRptBkmkMgrpCmbn()
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
	MSWord::Bookmark m_oBkmk;
	CRptBkmk *m_pBkmkRef;
};

class CRptFillWordApp : public CRptFillAppBase
{
public:
	CRptFillWordApp();
	virtual ~CRptFillWordApp();

	static CRptFillAppBase* New()	{	return new CRptFillWordApp();	}
public:
	MSWord::_Application m_WordApp;
	MSWord::_Application GetWordApp(BOOL bShow=FALSE);

	CWordCommandBarMngr m_WordCommandBarMngr;

public:
	virtual void CreateApplication(BOOL bShow=FALSE,long nHideAllCmdbars=0); 
	virtual void SetViewSettings();
	virtual void RestoreViewSettings();
	virtual	void CloseApplication();	
	virtual void RestoreCommandBars();
};

class CWordRptFill : public CWordRptFillBase, public CExBaseList
{
public:
	CWordRptFill(void);
	virtual ~CWordRptFill(void);

	long OpenOnly(const CString &strReportFile);
	
public:
	MSWord::_Document m_oDoc;

	CRptFillWordApp* m_pWordApp;

	//重载父类成员虚函数
public:
	virtual CString GetReportFillClassID(){
		return REPORTFILL_PROGID_WORD;
	};
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

	//填写报告相关函数
	//2021-10-16  lijunqing
	virtual void FillReportDatasetRowMode(CRptData *pData, CDvmDataset *pDataset);
	virtual	void FillReportGroupColMode(CRptData *pData, CReport *pReport, CShortData * oTagDataDef);
	virtual	void FillReport_Cell(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE);
	virtual	void FillReport_Row(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE);
	virtual	void FillReport_Col(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE);

	virtual	void FillReportFile(const CString &strValue, CRptBkmk *pBkmk);
	virtual void FillReportClipboard(CRptBkmk *pBkmk);

	virtual void CmbmMgrpt(CRptFillInterface *pRptFill, long nMgbrpIndex);
	virtual void CmbmMgrpt(CExBaseList *pListItems, CWordRptFillBase *pRptFill);
	virtual void CmbmMgrpt(CItems *pItems, CWordRptFillBase *pRptFill);
	virtual void CmbmMgrpt(CRptArea *pArea, CWordRptFillBase *pRptFill);

private:
	MSWord::Cells GetCells(CRptBkmk *pBkmk, BOOL bRowMode);
	long GetBkmkPos(MSWord::_Document &oDoc, CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos);
	BOOL GetBkmkRowCol(CRptBkmk *pRptBkmk, MSWord::Table &oTable, MSWord::Cells &oCells);
	void DeleteBkmk(MSWord::Bookmarks bookmarks, const CString &strBkmk);

	void ClearBkmksText(CExBaseList *pList, MSWord::Selection &sel, MSWord::Bookmarks &bookmarks);
	void ClearBkmkText(CRptBkmk *pBkmk, MSWord::Selection &sel, MSWord::Bookmarks &bookmarks);

	CString GetBkmkText(MSWord::Bookmark &bookmark);
	CString GetBkmkText(MSWord::_Document &oDoc, CRptBkmk *pBkmk);
	void After_Put_Text(MSWord::Selection &sel, MSWord::Bookmark &bookmark, long lRangeEndPrev);

public:
	void FillReportCell(const _bstr_t &strValue, MSWord::Cell oCell);
	void FillReport_Cell(const CString &strValue, MSWord::Bookmark &bookmark, long nRptIndex, BOOL bSetColor=FALSE);

	BOOL CmbnSelectBkmk(CRptBkmk *pBkmk, MSWord::_Document& oDoc);
	BOOL CmbnCopyMgrpt(CRptArea *pArea, MSWord::_Document &oDoc);
	void CmbnPasteMgrpt(CRptBkmk *pEndBkmk);

	//标签合并部分
	virtual void InitWordRptBkmkMgrpCmbn();
	void InitWordRptBkmkMgrpCmbn(CExBaseList *pList, MSWord::Bookmarks &oBookmarks);
	void WordRptBkmkMgrpCmbn(MSWord::_Document &oDoc);
	void WordRptBkmkMgrpCmbn(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, MSWord::_Document &oDoc);
	void WordRptBkmkMgrpCmbn_max_len(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WordRptBkmkMgrpCmbn_min_len(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WordRptBkmkMgrpCmbn_max_val(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WordRptBkmkMgrpCmbn_min_val(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WordRptBkmkMgrpCmbn_avg(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
	void WordRptBkmkMgrpCmbn_sum(CWordRptBkmkMgrpCmbn *pBkmkMgrpCmbn, const CString &strText);
};
