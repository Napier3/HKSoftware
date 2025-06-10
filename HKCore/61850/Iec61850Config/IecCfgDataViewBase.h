#pragma once


#include "resource.h"
#include "..\Module\IecCfgTool\IecCfgFile.h"
#include "IecCfgDataChsViewBase.h"
#include "..\Module\UI\IecCfgDataGridBase.h"

#define IDC_BTN_IECCFG_DATA_OPTR_ADD         20001
#define IDC_BTN_IECCFG_DATA_OPTR_DELETE      20002
// #define IDC_BTN_IECCFG_DATA_OPTR_DELETEALL   20003
#define IDC_BTN_IECCFG_DATA_OPTR_MOVEUP      20003
#define IDC_BTN_IECCFG_DATA_OPTR_MOVEDOWN    20004
#define IDC_BTN_IECCFG_DATA_OPTR_COPY        20005
#define IDC_BTN_IECCFG_DATA_OPTR_PASTE       20006
#define IDC_BTN_IECCFG_DATA_OPTR_EXPORTTO    20007
#define IDC_BTN_IECCFG_DATA_OPTR_INCREASE    20008
#define IDC_BTN_IECCFG_DATA_OPTR_DECREASE    20009
#define IDC_BTN_IECCFG_DATA_OPTR_SELALL      20010

#define INDEX_BTN_IECCFG_DATA_OPTR_ADD         (IDC_BTN_IECCFG_DATA_OPTR_ADD       - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_DELETE      (IDC_BTN_IECCFG_DATA_OPTR_DELETE    - IDC_BTN_IECCFG_DATA_OPTR_ADD)
// #define INDEX_BTN_IECCFG_DATA_OPTR_DELETEALL   (IDC_BTN_IECCFG_DATA_OPTR_DELETEALL - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_MOVEUP      (IDC_BTN_IECCFG_DATA_OPTR_MOVEUP    - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_MOVEDOWN    (IDC_BTN_IECCFG_DATA_OPTR_MOVEDOWN  - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_COPY        (IDC_BTN_IECCFG_DATA_OPTR_COPY      - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_PASTE       (IDC_BTN_IECCFG_DATA_OPTR_PASTE     - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_EXPORTTO    (IDC_BTN_IECCFG_DATA_OPTR_EXPORTTO  - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_INCREASE    (IDC_BTN_IECCFG_DATA_OPTR_INCREASE  - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_DECREASE    (IDC_BTN_IECCFG_DATA_OPTR_DECREASE  - IDC_BTN_IECCFG_DATA_OPTR_ADD)
#define INDEX_BTN_IECCFG_DATA_OPTR_SELALL      (IDC_BTN_IECCFG_DATA_OPTR_SELALL  - IDC_BTN_IECCFG_DATA_OPTR_ADD)


#define IDC_BTN_IECCFG_DATA_OPTR_COUNT       10

#define IDC_GRID_IECCFG_DATA_BASE            21000

#define IDC_IECCFG_DATAVIEW_CY_MIN           130
#define IDC_BTN_IECCFG_DATA_OPTR_WIDTH       63
#define IDC_BTN_IECCFG_DATA_OPTR_HEIGHT      23

// CIecCfgDataViewBase 窗体视图
class CIecCfgDataCopyPasteTool : public CExBaseList
{
protected:
	CIecCfgDataCopyPasteTool();
	virtual ~CIecCfgDataCopyPasteTool();

public:
	static CIecCfgDataCopyPasteTool* Create();
	static void Release();
	static void SetIecCfgDataClassID(UINT nIecCfgDataClassID);

private:
	static long g_nGlobalRef;
	static CIecCfgDataCopyPasteTool *g_pGlobal;

public:
	static void AddPasteButton(UINT nClassID, CButton *pBtnPaste);
	static void SetPasteButton(CButton *pBtnPaste, UINT nClassID);
	static void RemovePasteButton(CButton *pBtnPaste);
	static void RestCopySrcList();
	static void AddCopySrcData(CIecCfgDataBase *pIecCfgData);
	static void AddCopySrcData(CExBaseList *pListIecCfgDatas);
	static void EnableAllPasteButtons();
	static void EnableAllPasteButton(CButton *pBtnPaste);
	static void OnCfgDatasDelete(CExBaseList *pListDatas);
	static void OnCfgDatasDelete(CIecCfgDataBase *pIecCfgData);
	static void GetNewDatas(CExBaseList *pListDatas);

protected:
	void In_AddPasteButton(UINT nClassID, CButton *pBtnPaste);
	void In_SetPasteButton(CButton *pBtnPaste, UINT nClassID);
	void In_RemovePasteButton(CButton *pBtnPaste);
	void In_RestCopySrcList();
	void In_AddCopySrcData(CIecCfgDataBase *pIecCfgData);
	void In_AddCopySrcData(CExBaseList *pListIecCfgDatas);
	void In_EnableAllPasteButtons();
	void In_EnablePasteButton(CButton *pBtnPaste);
	void In_OnCfgDatasDelete(CExBaseList *pListDatas);
	BOOL In_OnCfgDatasDelete(CIecCfgDataBase *pIecCfgData);
	void In_GetNewDatas(CExBaseList *pListDatas);

	class CBtnAndDatasRefObj : public CExBaseObject
	{
	private:
		CBtnAndDatasRefObj()	{	}

	public:
		CBtnAndDatasRefObj(UINT nClassID, CButton *pBtnPaste);
		virtual ~CBtnAndDatasRefObj()	{}

		void EnablePasteButton(UINT nClassID, long nSrcDataCount);
	public:
		UINT m_nClassID;
		CButton *m_pBtnPaste;
	};

	class CBtnAndDatasRefObjMngr : public CExBaseList
	{
	public:
		CBtnAndDatasRefObjMngr()	{}
		virtual ~CBtnAndDatasRefObjMngr()	{}

	public:
		void AddBtnAndDatasRefObj(UINT nClassID, CButton *pBtnPaste);
		void EnableButtons(UINT nClassID, long nSrcDataCount);
		void EnableButton(CButton *pBtnPaste, UINT nClassID, long nSrcDataCount);
		void SetPasteButton(CButton *pBtnPaste, UINT nClassID);
		void RemovePasteButton(CButton *pBtnPaste);
		CBtnAndDatasRefObj* FindButton(CButton *pBtnPaste);

	};

	UINT m_nIecCfgDataClassID;
	CBtnAndDatasRefObjMngr m_oBtnAndDatasRefObjMngr;
};

class CIecCfgDataViewBase : public CFormView,  public CExBaseListGridOptrInterface
{
public:
	CIecCfgDataChsViewBase *m_pChsView;
	CIecCfgFile *m_pIecCfgFile;
	CIecCfgDatasBase *m_pIecCfgDatas;

//公共功能函数定义
public:
	virtual void ShowIecCfgData();
	virtual CIecCfgDatasBase* GetIecCfgDatas() = 0;
	virtual void CreateIecCfgDataGrid() = 0;
	virtual void FreeGrid(CRect &rcGrid);
	virtual void FreeGrid();


protected:
	CIecCfgDataViewBase(UINT nIDTemplate);
	virtual ~CIecCfgDataViewBase();

	virtual void InitView(CIecCfgDataGridBase *pIecCfgDataGrid);
	virtual void AdjustSize(int cx, int cy);

	CIecCfgDataGridBase *m_pIecCfgDataGrid;

public:
	virtual void OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol);

protected:
	CIecCfgDataBase *m_pLastSelIecCfgData;
	BOOL	m_bSelAllState;

//////////////////////////////////////////////////////////////////////////
//系列按钮定义63*23
protected:
	long    m_nGridTop;
	CButton m_btnIecCfgDataOptr[IDC_BTN_IECCFG_DATA_OPTR_COUNT];
	static const UINT    g_nIecCfgDataOptrID[IDC_BTN_IECCFG_DATA_OPTR_COUNT];
	static CString g_strIecCfgDataOptrText[IDC_BTN_IECCFG_DATA_OPTR_COUNT];
	
	//按钮创建和使能
	void GetAddButtonRect(CRect &rc, long cy);
	virtual void CreateAllButtons(int cx, int cy);
	virtual void EnableAllButtons();

	void AutoSetCfgDataValue(long nOffset);
	void AutoSetCfgDataValue(CIecCfgDataBase *pCfgData, long nOffset);
	CIecCfgDataBase* GetNextIecCfgData(CExBaseList &oListIecCfgData);
	//按钮功能函数定义
// 	virtual CIecCfgDataBase* Add();
// 	virtual void OnBnClickedBtnDelete();
// 	virtual void OnBnClickedBtnDeleteAll();
// 	virtual void OnBnClickedBtnMoveUp();
// 	virtual void OnBnClickedBtnMoveDown();
// 	virtual void OnBnClickedBtnCopy();
// 	virtual void OnBnClickedBtnPaste();
// 	virtual void OnBnClickedBtnExport();
// 	virtual void OnBnClickedBtnIncreate();
// 	virtual void OnBnClickedBtnDecrease();

public:
	//按钮功能响应函数
	afx_msg void OnBnClickedBtnAdd();
	afx_msg void OnBnClickedBtnDelete();
	afx_msg void OnBnClickedBtnDeleteAll();
	afx_msg void OnBnClickedBtnMoveUp();
	afx_msg void OnBnClickedBtnMoveDown();
	afx_msg void OnBnClickedBtnCopy();
	afx_msg void OnBnClickedBtnPaste();
	afx_msg void OnBnClickedBtnExportTo();
	afx_msg void OnBnClickedBtnIncrease();
	afx_msg void OnBnClickedBtnDecrease();
	afx_msg void OnBnClickedBtnSelAll();

public:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);

};


