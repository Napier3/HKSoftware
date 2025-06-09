#pragma once
#include "rpteditinterface.h"
//#include "XmlProssData.h"
#include "XmlPathData.h"
#include "../../../ReportTemplateDev/DialogEditRpt.h"

class CXmlRptEdit :
	public CRptEditInterface
{
public:
	CXmlRptEdit(void);
	virtual ~CXmlRptEdit(void);
	virtual CString GetReportEditClassID(){	return REPORTFILL_PROGID_XML; };
	virtual CString GetReportSuffix(){ return _T("xml");};

public:
	CXmlPathData m_XmlProssData;
	CDialogEditRpt m_xmlDlg;

	//重载函数
	BOOL CreateWordApplication(BOOL bVisible=FALSE);
	BOOL OpenWordReportFile(const CString &strRptFile);
	BOOL NewWordReportFile();

	void InitAllBookmarks();
	void ExitWord(BOOL bExitApp=TRUE);
	long OpenWord(const CString &strGuideBookFile);
	CExBaseObject* AddBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode);
	CExBaseObject* BindBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode, const CString &strBkmk);
	void InsertBkmk(const CString &strBkmk);
	CExBaseObject* AddArea(CExBaseList *pRptArea);
	CExBaseObject* AddArea(CGbItemBase *pItem, long nStart, long nEnd);
	long GetCurrPos();

	long InitPage(BOOL bHort=FALSE);
	long Save();
	long SaveAs(const CString &strFile);
	long CloseWord();
	BOOL IsValidDoc();
	void ClearBkmkText(CRptBkmk *pBkmk);
	CString InitCurrBkmk();
  	long GetAllSelBkmk(CExBaseList &oListWordBkmk);

	BOOL CanAddArea();
	BOOL ReplaceBkmk(const CString &  strBkmkSrc, const CString &  strBkmkDest);
	BOOL UpdateBkmk(CRptBkmk *pRptBkmk);

	void InsertTitle(const CString &strTitle, long nTitleLevel);
	BOOL ActiveWindow(const CString &strTitle);
	long GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos);
	long AdjustReport_DelArea(CRptArea *pArea);

	CExBaseObject * ReLocateBkmk();

	CWnd* AdjustSizeView();
	void SetAppVisible(BOOL bVisible);
	void SetDisplayStatusBar(BOOL bVisible);

	void CopyApp(CRptEditInterface *pRptEditDest);
	void rpt_RenameRptBkmks(CExBaseList *pList);
	void InsertWordEdit(CRptEditInterface *pRptEdit, long nAddRptGroupTitle);

	BOOL rpt_CanEnterRptBkmkBatchAdd(CExBaseObject *pItem);
	BOOL rpt_CanEnterRptBkmkBatchAddYc(CExBaseObject *pItem);
	BOOL rpt_GetRptBkmkBatchRowsCols(long &nRows, long &nCols);
	virtual void InsertBkmks(CExBaseList& oListCells, CExBaseList& oListBkmks);
	
	virtual void GetBatchCellList_ROWITEM_COLDATA(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nCols);
	virtual void GetBatchCellList_ROWDATA_COLITEM(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRows);
	virtual void GetBatchCellList_ROWREPEAT_COLDATA_ITEMROW(CExBaseList &oListBatchCell,CRptBatchItemMaps *pItemMaps, CRptBatchDataMaps *pDataMaps, long nRepeatCount, long nCols);

	//Bkmk Mathods
	virtual long LocateBkmk(const CString &  strBkmk);
	long DeleteBkmk(const CString &  strBkmk, BOOL bSelect=FALSE);

	void UpdateToFaceTree();
	void UpdateToFaceGrid();

	virtual BOOL CheckChoosePoint();

	//20231010 huangliang 关联标签
	virtual void AttachBookmarksAndRptBkmks();
	CWordBkmk *FindWorkList(const CString &strId, int iIndex);

	//20230926 huangliang 创建标签
	virtual CString CreateNewBkmk(CRptData *pData);
};
