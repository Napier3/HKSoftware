#pragma once
#include "rpteditinterface.h"
#include "../../../../Module/Office/mso9.h"
#include "../../../../Module/Office/msword9.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"
#include "RptItem.h"
#include "WordRptApi.h"


class CWordRptEdit : public CRptEditInterface
{
public:
	CWordRptEdit(void);
	virtual ~CWordRptEdit(void);
        virtual CString GetReportEditClassID(){	return REPORTFILL_PROGID_WORD; };
	virtual CString GetReportSuffix(){ return _T("doc");};

public:
	//Word ±‰¡ø
	MSWord::_Application	m_WordApp;
	MSWord::_Document		m_doc;

	//Word Mathods
	BOOL CreateWordApplication(BOOL bVisible=FALSE);
	BOOL OpenWordReportFile(const CString &strRptFile);
	BOOL OpenReportTemplate(const CString &strRptFile);
	BOOL NewWordReportFile();

	//Member Functions
	void InitAllBookmarks();

	void HideCommandBar(MSO9::_CommandBars cmdBars );
	CExBaseObject * ReLocateBkmk();

public:
	//Interface
	void ExitWord(BOOL bExitApp=TRUE);
	long OpenWord(const CString &strGuideBookFile);
	virtual long LocateBkmk(const CString &  strBkmk);
	virtual long DeleteBkmk(const CString &  strBkmk, BOOL bSelect=FALSE);
	virtual CExBaseObject* AddBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode);
	virtual void InsertBkmk(const CString &strBkmk);
	virtual CExBaseObject* AddArea(CExBaseList *pRptArea);
	virtual CExBaseObject* AddArea(CGbItemBase *pItem, long nStart, long nEnd);
	long GetCurrPos();

	virtual long InitPage(BOOL bHort=FALSE);
	virtual long Save();
	virtual long SaveAs(const CString &strFile);
	virtual long CloseWord();
    virtual BOOL IsValidDoc();

	CString InitCurrBkmk();
	long GetAllSelBkmk(CExBaseList &oListWordBkmk);
	BOOL CanAddArea();
	
	virtual BOOL ReplaceBkmk(const CString & strBkmkSrc, const CString & strBkmkDest);
	BOOL UpdateBkmk(CRptBkmk *pRptBkmk);

	void InsertTitle(const CString &strTitle, long nTitleLevel);
	
	virtual BOOL rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem);
	virtual BOOL rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem);
	virtual BOOL rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols);
	virtual void InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks);
	
	virtual void GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols);
	virtual void GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows);
	virtual void GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols);

private:
	CRptBkmk* InsertNewAreaBkmk(DWORD &dwBkmkIndex, CExBaseList *pRptArea, MSWord::Bookmarks wordBookmarks, MSWord::Selection wordSelection, long nPos);
	void ClearBkmkText(CRptBkmk *pBkmk);

	BOOL ActiveWindow(const CString &strTitle);
	//////////////////////////////////////////////////////////////////////////
	long GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos);
	long AdjustReport_DelArea(CRptArea *pArea);

	BOOL GetBkmkRowCol(CRptBkmk *pRptBkmk, MSWord::Table &oTable, MSWord::Cells &oCells);
	long GetIndex(MSWord::Cells &oCells, long nBkmkID);

	CWnd* AdjustSizeView();
	void SetAppVisible(BOOL bVisible);
	void SetDisplayStatusBar(BOOL bVisible);

	void CopyApp(CRptEditInterface *pRptEditDest);
	void rpt_RenameRptBkmks(CExBaseList *pList);
	void InsertWordEdit(CRptEditInterface *pRptEdit,long nAddRptGroupTitle);
};
