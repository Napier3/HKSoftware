#pragma once

#include "../RptFillInterface.h"
#include "../../../../../Module/GridBase/ExBaseListGrid.h"

#define SYSTEMREPORT_VIEW_MIN_WIDTH  800
#define WM_ADJUSTVIEWSIZE  (WM_USER + 1232)

extern BOOL g_bSysReportFillShowAllDatas;
//////////////////////////////////////////////////////////////////////////
//CSystemRptFillItem
class CSystemRptFillItem : public CExBaseObject
{
public:
	CSystemRptFillItem();
	virtual ~CSystemRptFillItem();
	long GetOffset();
	void Offset(long nOffset, CWnd *pParentWnd);

public:
	CStatic *m_pWndTitle;
	CExBaseListGrid *m_pGridRpt;
	CGbItemBase *m_pGbItem;
};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillItems
class CSystemRptFillItems : public CExBaseList
{
public:
	CSystemRptFillItems();
	virtual ~CSystemRptFillItems();

public:
	void AddSystemRptFillItem(CGbItemBase *pGbItem, CStatic *pWndTitle, CExBaseListGrid *pGridRpt);

};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid
class CSystemRptFillGridBase : public CExBaseListGrid
{
public:
	CSystemRptFillGridBase();
	virtual ~CSystemRptFillGridBase();

public:
	long m_yCurrPos;
};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_ItemsRsltScript
class CSystemRptFillGrid_ItemsRsltScript : public CSystemRptFillGridBase
{
public:
	CSystemRptFillGrid_ItemsRsltScript();
	virtual ~CSystemRptFillGrid_ItemsRsltScript();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void UpdateDatas();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_MacroTest
class CSystemRptFillGrid_MacroTest : public CSystemRptFillGridBase
{
public:
	CSystemRptFillGrid_MacroTest();
	virtual ~CSystemRptFillGrid_MacroTest();
	CValues *m_pValues;
	CExBaseList *m_pFaultParas;

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void UpdateDatas();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void ShowDataEx(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

protected:
	void ShowDatas_FaultPara(CExBaseList *pResults, int &nRowIndex);
	void ShowDatas_FaultParaEx(CExBaseList *pResults, int &nRowIndex);
	void ShowDatas_Result(CExBaseList *pResults, int &nRowIndex);
};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_CommCmd
class CSystemRptFillGrid_CommCmd : public CSystemRptFillGridBase
{
public:
	CSystemRptFillGrid_CommCmd();
	virtual ~CSystemRptFillGrid_CommCmd();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void UpdateDatas();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_Safety
class CSystemRptFillGrid_Safety : public CSystemRptFillGridBase
{
public:
	CSystemRptFillGrid_Safety();
	virtual ~CSystemRptFillGrid_Safety();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void UpdateDatas();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFillGrid_SysParaEdit
class CSystemRptFillGrid_SysParaEdit : public CSystemRptFillGridBase
{
public:
	CSystemRptFillGrid_SysParaEdit();
	virtual ~CSystemRptFillGrid_SysParaEdit();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void UpdateDatas();
	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
};

//////////////////////////////////////////////////////////////////////////
//CSystemRptFill
class CSystemRptFill : public CRptFillInterface
{
public:
	CSystemRptFill(void);
	virtual ~CSystemRptFill(void);

protected:
	CSystemRptFillGridBase *m_pLastGrid;
	CExBaseObject *m_pLastRptFillObject;
	CExBaseObject *m_pLastRptFillObjectSub;
	CReport  *m_pLastReport;
	long m_nLastItemsScriptTestIndex;
	UINT m_nCtrlID;
	CSystemRptFillItems m_listSysRptFillItems;
	long m_nViewWidth;
	long m_nViewHeight;
	long m_yCurrRptCtrlPos;

	long m_nSysRptShowMaxCount;

	//重载父类成员虚函数
public:
	virtual CString GetReportFillClassID();
	virtual long New(CString strReportMapFile, CString strReportTemplFile, CString strReportFile, BOOL bFirst);
	virtual long Open(const CString  &strReportFile, BOOL bFirst);
	virtual long Save();
	virtual long SaveAs(CString  strRptFile);
	virtual long Close(long nSave);

	virtual void SetSysRptShowMaxCount(long nSysRptShowMaxCount);

	//根据可显示试图的大小调整报告试图大小
	virtual void AdjustReportWindowOnSize();

	//是否包含需要填写的报告数据的位置
	virtual long HasReportNeedFill(const CGbItemBase* pItem);

	//设置报告数据，填写报告
	virtual long FillReport(CReport* pReport, long nRepeatIndex, long nInsertDataLinkWhenEligible);

	//在报告中定位
	virtual long LocateReport(CGbItemBase* pItem);

	//调整报告
	virtual long AdjustReport(CThreadProgressInterface *pProgress=NULL);
	virtual long AdjustReport_FillEmpty();

	virtual BOOL ActiveWindow(const CString &strTitle);
	virtual BOOL AddNewReport(const CString &strRptTmplFile);

	virtual void PrintReport();
	virtual void ExportPdf();
	virtual void ZoomReport(long nPercentage);
	virtual long GetZoomReport();
	virtual void EmptyReportText();

	virtual void CmbmMgrpt(CRptFillInterface *pRptFill, long nMgbrpIndex){};

private:
	CItemsRsltExprScript* GetItemsRsltExprScript(CGbItemBase* pItem);
	void ShowReport(CCommCmd *pCommCmd, CReport *pReport);
	void ShowReport(CMacroTest *pMacroTest, CReport *pReport);
	void ShowReport(CSafety *pSafety, CReport *pReport);
	void ShowReport(CSysParaEdit *pSysParaEdit, CReport *pReport);
	void ShowReport(CItemsRsltExprScript *pItemsRsltExprScript, CReport *pReport, CGbItemBase *pGbItem);

	void CreateReportShow(CGbItemBase *pGbItem, CSystemRptFillGridBase *pReportGrid, CExBaseList *pDatas);
	void UpdateGrid(CGbItemBase *pGbItem);
	void UpdateGrid(CGbItemBase *pGbItem, CSystemRptFillGridBase *pRptFillGrid);

public:
	void AdjustSystemReportFills();

	long GetWidth();
	long GetHeight();
	long GetCurrPos();
private:
	void CreateSystemApp();
	BOOL CloseSystemDocWindow();
	void AdjustSystemWindow();
};
