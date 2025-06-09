#pragma once
#include "rpteditinterface.h"
#include "../../../../Module/Office/WPS.h"
#include "../../../../Module/Office/KSO.h"
#include "../../../../Module/CriticalSection/SynCriticalSection.h"
#include "RptItem.h"
#include "WPSRptApi.h"

class CWPSRptEdit : public CRptEditInterface
{
public:
	CWPSRptEdit(void);
	~CWPSRptEdit(void);
	virtual CString GetReportEditClassID(){	return REPORTFILL_PROGID_WPS; };
	virtual CString GetReportSuffix(){ return _T("doc");};

public:
	//WPS ±‰¡ø
	WPS::_Application	m_WPSApp;
	WPS::_Document		m_doc;

    //WPS Mathods
	virtual BOOL CreateWordApplication(BOOL bVisible=FALSE);
	virtual BOOL OpenWordReportFile(const CString &strRptFile);
	virtual BOOL NewWordReportFile();
	
    //Member Functions
    virtual void InitAllBookmarks();

    void HideCommandBar(KSO::_CommandBars cmdBars );
	CExBaseObject * ReLocateBkmk();

public:
	//Interface
    virtual void ExitWord(BOOL bExitApp=TRUE);
    virtual long OpenWord(const CString &strGuideBookFile);
    virtual long LocateBkmk(const CString & strBkmk);
    virtual long DeleteBkmk(const CString &  strBkmk, BOOL bSelect=FALSE);
    virtual CExBaseObject* AddBkmk(CRptData *pData, const CString & strAttrID, const CString &strDataProcess, const CString &strFillMode);
	virtual void InsertBkmk(const CString & strBkmk);
    virtual CExBaseObject* AddArea(CExBaseList *pRptArea);
    virtual CExBaseObject* AddArea(CGbItemBase *pItem, long nStart, long nEnd);
    virtual long GetCurrPos();

    virtual long InitPage(BOOL bHort=FALSE);
	virtual long Save();
	virtual long SaveAs(const CString &strFile);
	virtual long CloseWord();
	virtual BOOL IsValidDoc();

	virtual void ClearBkmkText(CRptBkmk *pBkmk);
	virtual CString InitCurrBkmk();
	virtual long GetAllSelBkmk(CExBaseList &oListWordBkmk);
	virtual BOOL CanAddArea();

	virtual BOOL ReplaceBkmk(const CString &strBkmkSrc, const CString &strBkmkDest);
	virtual BOOL UpdateBkmk(CRptBkmk *pRptBkmk);

	virtual void InsertTitle(const CString &strTitle, long nTitleLevel);
	void InsertWPSEdit(CWPSRptEdit *pEdit,long nAddRptGroupTitle);

	CRptBkmk* InsertNewAreaBkmk(DWORD &dwBkmkIndex, CExBaseList *pRptArea, WPS::Bookmarks wpsBookmarks, WPS::Selection wpsSelection, long nPos);
	virtual BOOL ActiveWindow(const CString &strTitle);

	virtual long GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos);
	virtual long AdjustReport_DelArea(CRptArea *pArea);

	BOOL GetBkmkRowCol(CRptBkmk *pRptBkmk, WPS::Table &oTable, WPS::Cells &oCells);
	long GetIndex(WPS::Cells &oCells, long nBkmkID);

	virtual CWnd* AdjustSizeView();
	virtual void SetAppVisible(BOOL bVisible);
	virtual void SetDisplayStatusBar(BOOL bVisible);

	virtual void CopyApp(CRptEditInterface *pRptEditDest);
	virtual void rpt_RenameRptBkmks(CExBaseList *pList);
	virtual void InsertWordEdit(CRptEditInterface *pRptEdit,long nAddRptGroupTitle);
	
	virtual BOOL rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem);
	virtual BOOL rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem);
	virtual BOOL rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols);
	virtual void InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks);
	
	virtual void GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols);
	virtual void GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows);
	virtual void GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols);
};

