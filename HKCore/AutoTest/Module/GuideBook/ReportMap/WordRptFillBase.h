#pragma once
/*
   报告处理模块的接口
   开放报告处理的全部功能入口
*/
#include "RptFillInterface.h"
#include "../../GuideBook/GuideBook.h"
#include "../../../../Module/BaseClass/ThreadProgressInterface.h"

//////////////////////////////////////////////////////////////////////////
//CRptFillAppBase
class CRptFillAppBase
{
public:
	CRptFillAppBase(){};
	virtual ~CRptFillAppBase(){};

	BOOL m_bShowParagraphs;
	BOOL m_bShowBookmarks;

public:
	virtual void CreateApplication(BOOL bShow=FALSE,long nHideAllCmdbars=0)=0; 
	virtual void SetViewSettings()=0;
	virtual void RestoreViewSettings()=0;
	virtual	void CloseApplication()=0;	
	virtual void RestoreCommandBars()=0;
};

typedef CRptFillAppBase* (PFUNC_RPTFILLAPP_CREATE)();

//////////////////////////////////////////////////////////////////////////
//CWordRptFillBase
class CWordRptFillBase : public CRptFillInterface
{
public:
	CWordRptFillBase(void);
	virtual ~CWordRptFillBase(void);

public:
	HWND m_hWordWnd;
	COLORREF m_crReport;
	COLORREF m_crReportBackground;  //2021-06-19 shaolei
	long m_nInlegibleFontBold;  //2021-2-26  lijunqing
	CRptBkmk *m_pCurrBkmk;

public:
	//公共函数
	void AdjustDocWindow(CWnd* pWnd);
	void CloseWord();
	COLORREF TCC_GetItemReportColor(CGbItemBase *pItem);
	COLORREF TCC_GetItemReportBackgroundColor(CGbItemBase *pItem);
	long TCC_GetItemReportBold(CGbItemBase *pItem);
	BOOL TCC_GetReportDataColor(CRptData *pData, CReport *pReport, COLORREF &crData, COLORREF &crBackground, long &nInlegibleFontBold);
	CExBaseList* FillReportParentItem(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible);
	long FillReport(CReport* pReport, CExBaseList *pRptDataList);
	long FillReport_Dataset(CReport* pReport, CExBaseList *pRptDataList);
	long FillReport(CReport* pReport, CRptMapRepeat *pRepeat);
	long FillReport(CReport* pReport, CReportMap *pMap);
	virtual void FillReport(CRptData *pData, CReport *pReport);   //shaolei 20220507 改为virtual
	long FillReportGroup(CRptData *pData, CReport *pReport, CShortData * oTag);
	long Gb_RptFill_GetReportGroupDataCount(CCommCmd *pCommCmd, CReport *pReport);
	
	long AdjustReport_FillEmpty(const CString &strReplace, CExBaseObject *pObj);
	long AdjustReport_FillEmpty(const CString &strReplace, CExBaseList *pList);
	long AdjustReport_FillEmpty(const CString &strReplace, CRptData *pData);
	long AdjustReport_FillEmpty(const CString &strReplace, CRptBkmk *pBkmk);

	long AdjustReport_Area();
	long AdjustReport_Area(CExBaseList *pList);
	long AdjustReport_Area(CItems *pItems);
	long AdjustReport_DelArea(CGbItemBase *pItem);

	long AdjustReport_SysBkmkDataProcess(CRptBkmk *pBkmk);

	BOOL IsRptDataSingleMode(CRptData *pData, CReport *pReport, CShortData **ppTag);

	void FillReportGroupRowMode(CRptData *pData, CReport *pReport, CShortData * oTagDataDef);
	
	long FillReportSingle(CRptData *pData, CReport *pReport);
	BOOL GetReportDataFilePath(CRptData *pData, CValue *pValue, CString &strFile);
	BOOL IsDataABitmapFile(CRptData *pData, CReport *pReport, CString &strFile);
	BOOL IsDataAComtradeFile(CRptData *pData, CReport *pReport, CString &strFile);

	void FillReport(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE);
	long LocateReport(CRptData *pData);

	//虚函数
	virtual long OpenOnly(const CString& strReportFile)=0;

	virtual CString GetReportFillClassID()=0;

	virtual long New(CString strReportMapFile, CString strReportTemplFile, CString strReportFile, BOOL bFirst) = 0;
	virtual long Open(const CString& strReportFile, BOOL bFirst) = 0;
	virtual long Save() = 0;
	virtual long SaveAs(CString strRptFile)= 0;
	virtual long Close(long nSave) = 0;
	virtual void CloseDoc(DWORD dwFlag=0)= 0;

	virtual BOOL IsValidApp()=0;
	virtual BOOL IsValidDoc()=0;

	virtual void SetSysRptShowMaxCount(long nSysRptShowMaxCount){};

	virtual void AdjustReportWindowOnSize();//根据可显示试图的大小调整报告试图大小
	virtual long HasReportNeedFill(const CGbItemBase* pItem);

	virtual long LocateReport(CGbItemBase* pItemBase);
	virtual long AdjustReport(CThreadProgressInterface *pProgress);
	virtual	long AdjustReport_FillEmpty();

	virtual void AdjustWordWindow()=0;
	virtual BOOL CloseWordDocWindow()=0;
	virtual BOOL ActiveWindow(const CString &strTitle)=0;

	virtual BOOL AddNewReport(const CString &strRptTmplFile)=0;
	virtual long FillReport(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible)=0;
	virtual void FillReportComtrdeFile(CRptData *pData, CReport *pReport, const CString &strFile);

	virtual void PrintReport()=0;
	virtual void ExportPdf()=0;
	virtual void ZoomReport(long nPercentage)=0;
	virtual long GetZoomReport()=0;
	virtual void EmptyReportText()=0;

	virtual long AdjustReport_DelArea(CRptArea *pArea)=0;
	virtual long LocateReport(CRptBkmk *pBkmk)=0;
	virtual long GetBkmkPos(CRptBkmk *pBkmk, long &nBeginPos, long &nEndPos)=0;

	virtual void DeleteBkmk(const CString &strBkmk)=0;

	//2021-10-16  lijunqing
	virtual void FillReportDatasetRowMode(CRptData *pData, CDvmDataset *pDataset) = 0;

	virtual void FillReportGroupColMode(CRptData *pData, CReport *pReport, CShortData * oTagDataDef)=0;
	virtual void FillReport_Col(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor=FALSE)=0;
	virtual void FillReport_Cell(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)=0;
	virtual void FillReport_Row(const CString &strValue, CRptBkmk *pBkmk, long nRptIndex, BOOL bSetColor)=0;
	virtual void FillReportFile(const CString &strValue, CRptBkmk *pBkmk)=0;
	virtual void FillReportClipboard(CRptBkmk *pBkmk)=0;

	virtual void CmbmMgrpt(CRptFillInterface *pRptFill, long nMgbrpIndex)=0;
	virtual void CmbmMgrpt(CExBaseList *pListItems, CWordRptFillBase *pRptFill)=0;
	virtual void CmbmMgrpt(CItems *pItems, CWordRptFillBase *pRptFill)=0;
	virtual void CmbmMgrpt(CRptArea *pArea, CWordRptFillBase *pRptFill)=0;
	
	virtual void InitWordRptBkmkMgrpCmbn()=0;

	//2019-7-19  书签的系统处理
	virtual void AdjustReport_DelRow(CRptBkmk *pBkmk) = 0;
	virtual void AdjustReport_DelCol(CRptBkmk *pBkmk) = 0;
};

