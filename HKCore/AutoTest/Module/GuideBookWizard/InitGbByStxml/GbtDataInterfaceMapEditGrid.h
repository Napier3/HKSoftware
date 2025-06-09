#pragma once
#include "..\..\..\..\Module\GridCtrl\GridCtrl.h"
#include "..\GbInsertStxmlFileTool.h"
#include "..\..\..\..\Module\KeyDb\XMatchRefObjectSelDlg.h"

#include "..\..\..\..\Module\KeyDb\XMatchDatasetSelDlg.h"


class CGbtDataInterfaceMapEditGrid :	public CGridCtrl, public CXMatchRefObjectSelEdit
{
public:
	CGbtDataInterfaceMapEditGrid(void);
	~CGbtDataInterfaceMapEditGrid(void);

public:
	//virtual void ShowTool(CGbInsertStxmlFileTool *pTool);
	virtual void ShowGbInsertStxmlFile(CGbInsertStxmlFile *pGbInsertStxmlFile);
	void UpdateMap();

	virtual void InitExGrid();
	virtual void InitGridTitle();

	virtual void SetMatchRefData(CExBaseObject *pRefObject);
	virtual BOOL OnCellRButtonUp(const CCellID &idCell);
	virtual BOOL OnCellKeyDelete(const CCellID &idCell);

	static CXMatchDatasetSelDlg* GetXMatchDatasetSelDlg()
	{
		return m_pXMatchDatasetSelDlg;
	}

	void SetDataSelChangeMsgRcvWnd(CWnd  *pWnd)
	{
		m_pDataSelChangeMsgRcvWnd = pWnd;
	}

	void PostKeyChangeMessage()
	{
		if (m_pDataSelChangeMsgRcvWnd)
		{
			m_pDataSelChangeMsgRcvWnd->PostMessage(WM_MAPEDIT_KEY_CHANGED, 0, 0);
		}
	}

protected:
	static CXMatchRefObjectSelDlg *m_pXMatchRefObjectSelDlg;
	static long m_nXMatchRefObjectSelDlgRef;

	static CXMatchDatasetSelDlg *m_pXMatchDatasetSelDlg;
	static long g_nXMatchDatasetSelDlgRef;


protected:
	CGbInsertStxmlFile *m_pGbInsertStxmlFile;
	CGbInsertStxmlFileTool *m_pTool;
	long m_nShowDataMode;
	CWnd *m_pDataSelChangeMsgRcvWnd;

	void ShowGbtDataInterfaceMap(CGbtDataInterfaceMap *pGbtDataInterfaceMap, int &nRowIndex);
	void ShowGbtDataScript(CGbtDataScriptMap *pGbtScptMap, int &nRowIndex);

	void Show_XMatchSrc(CXMatchObject *pXMatchObj, const int &nRow, const int &nCol);
	void Show_XMatchDst(CXMatchObject *pXMatchObj, const int &nRow, const int &nCol);

	static void EndEdit_XMatchDst(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

protected:
	virtual void  OnEditCell(int nRow, int nCol, UINT nChar);
	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);

	virtual void Show_StaticString(const int& nRow, const int& nCol, const CString &strText, LPARAM lParam=0);
	virtual void Show_Index(const int& nRow, const int& nCol);
	virtual void Show_ScriptRefObjs(const int& nRow, CGbtDataScriptMap *pGbtScptMap);
	void ShowXMatchRefObjectSelDlgDatas(CExBaseList *pDatas);
	void ShowXMatchRefObjectSelDlgDataset();

	void SetMatchRefData(CExBaseObject *pRefObject, const CCellID &idCell);
};
