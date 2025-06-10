#pragma once

#include "..\Module\CfgDataMngr\IecCfgDevice.h"
#include "..\..\Module\GridBase\ExBaseListGrid.h"
#include "..\Module\IecCfgTool\IecCfgFile.h"

#define ID_IecfgDevice_DOCPANE   4322
#define ID_IecfgDevice_GRIDCTRL  4323

#define CLOSE_IECFG_FILE_DEVICE_TIMERID  1537

class CIecfgDeviceToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CIecfgDeviceGridCtrl : public CExBaseListGrid
{
public:
	CIecfgDeviceGridCtrl();
	virtual ~CIecfgDeviceGridCtrl();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	virtual void  OnEditCellLBDblClk(int nRow, int nCol, UINT nChar);
	virtual void SetModifiedFlag(CExBaseObject *pData, BOOL bModified=TRUE);

	static void EndEditCell_String_Name_Local (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);
	static void EndEditCell_String_ID_Local (int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid);

};

class CIecfgDeviceDockablePane : public CDockablePane
{
	DECLARE_DYNAMIC(CIecfgDeviceDockablePane)

public:
	CIecfgDeviceDockablePane();
	virtual ~CIecfgDeviceDockablePane();

	void AdjustLayout();//自适应调整尺寸

	void ShowIecfgDevice(CIecCfgFileDevice *pIecfgDevice);
private:
	CIecfgDeviceToolBar m_wndToolBar;
	CIecCfgDevice *m_pIecfgDevice;
	CIecCfgFileDevice *m_pIecCfgFileDevice;
	CIecfgDeviceGridCtrl m_gridIecfgDevice;

// 属性
public:

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);

	afx_msg void OnIecfgDeviceNew();
	afx_msg void OnUpdateIecfgDeviceNew(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceInsert();
	afx_msg void OnUpdateIecfgDeviceInsert(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceClone();
	afx_msg void OnUpdateIecfgDeviceClone(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceDelete();
	afx_msg void OnUpdateIecfgDeviceDelete(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceMoveUp();
	afx_msg void OnUpdateIecfgDeviceMoveUp(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceMoveDown();
	afx_msg void OnUpdateIecfgDeviceMoveDown(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceSave();
	afx_msg void OnUpdateIecfgDeviceSave(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceClose();
	afx_msg void OnUpdateIecfgDeviceClose(CCmdUI* pCmdUI);
	afx_msg void OnIecfgDeviceOpen();
	afx_msg void OnUpdateIecfgDeviceOpen(CCmdUI* pCmdUI);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


