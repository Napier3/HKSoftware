// IecfgDeviceDockablePane.cpp : 实现文件
//

#include "stdafx.h"
#include "IecfgDeviceDockablePane.h"
#include "..\..\Module\API\GloblaDrawFunctions.h"
#include "Iec61850Config.h"
#include "../../Module/System/TickCount32.h"

//////////////////////////////////////////////////////////////////////////
//


CIecfgDeviceGridCtrl::CIecfgDeviceGridCtrl()
{
	m_nAdjustBeginCol = 0;
}

CIecfgDeviceGridCtrl::~CIecfgDeviceGridCtrl()
{

}

void CIecfgDeviceGridCtrl::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);
	InitGridTitle();
}

void CIecfgDeviceGridCtrl::InitGridTitle()
{
	CString cTempStr[3]={CXLanguageResourceIec_61850Cfg::g_sLangTxt_Index/*_T("编号")*/,CXLanguageResourceIec_61850Cfg::g_sLangTxt_Name/*_T("名称")*/,_T("标识")};
	int iWidth[3]={60,160,120};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 3);
}

void CIecfgDeviceGridCtrl::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	UINT nClassID = pData->GetClassID();
//	ASSERT (nClassID == CFGCLASSID_CIECCFGDATASMNGR);

	if (nClassID != CFGCLASSID_CIECCFGDATASMNGR)
	{
		return;
	}

	if (bInsertRow)
	{
		InsertRow(NULL);
	}

	CIecCfgDatasMngr *pCfgDataMngr = (CIecCfgDatasMngr*)pData;
	Show_Index(pData, nRow, 0);
	Show_String(pData, nRow, 1, &pCfgDataMngr->m_strName, EndEditCell_String_Name_Local );
	Show_String(pData, nRow, 2, &pCfgDataMngr->m_strID, EndEditCell_String_ID_Local );

	nRow++;
}


void CIecfgDeviceGridCtrl::EndEditCell_String_Name_Local (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

	if (*pVCellData->pString == pCell->szText)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)pVCellData->pObj->GetParent();

	if (pParent == NULL)
	{
		return;
	}

	if (pParent->FindByName(pCell->szText) != NULL)
	{
		pCell->szText = pVCellData->pObj->m_strName;
		pGrid->InvalidateGrid(FALSE);
		return;
	}

	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strName = pCell->szText;

	pGrid->AutoSizeColumn(nCol);
	pGrid->ResetScrollBars();
	pGrid->InvalidateGrid(FALSE);

	theApp.UpdateIecfgFileTitle(pVCellData->pObj);
}

void CIecfgDeviceGridCtrl::EndEditCell_String_ID_Local (int nRow, int nCol, CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
	ASSERT(pVCellData != NULL && pCell != NULL && pGrid != NULL);
	ASSERT(pVCellData->pObj != NULL);
	ASSERT (pVCellData->nVt == VCD_STRING);

	if (*pVCellData->pString == pCell->szText)
	{
		return;
	}

	CExBaseList *pParent = (CExBaseList*)pVCellData->pObj->GetParent();

	if (pParent == NULL)
	{
		return;
	}

	if (pParent->FindByName(pCell->szText) != NULL)
	{
		pCell->szText = pVCellData->pObj->m_strID;
		pGrid->InvalidateGrid(FALSE);
		return;
	}

	((CExBaseListGrid*)pGrid)->SetModifiedFlag(pVCellData->pObj);
	pVCellData->pObj->m_strID = pCell->szText;

	pGrid->AutoSizeColumn(nCol);
	pGrid->ResetScrollBars();
	pGrid->InvalidateGrid(FALSE);

	theApp.UpdateIecfgFileTitle(pVCellData->pObj);
}


void CIecfgDeviceGridCtrl::SetModifiedFlag(CExBaseObject *pData, BOOL bModified)
{
	iecfg_SetModified(pData);
}

void CIecfgDeviceGridCtrl::OnEditCellLBDblClk(int nRow, int nCol, UINT nChar)
{
	CIecCfgDatasMngr *pIecfgDataMngr = (CIecCfgDatasMngr*)GetCurrSelData(1);
	ASSERT (pIecfgDataMngr != NULL);

	if (pIecfgDataMngr == NULL)
	{
		return;
	}

	theApp.CreateNewIecCfgFrame(pIecfgDataMngr);
}

//////////////////////////////////////////////////////////////////////////
// CIecfgDeviceDockablePane

IMPLEMENT_DYNAMIC(CIecfgDeviceDockablePane, CDockablePane)

CIecfgDeviceDockablePane::CIecfgDeviceDockablePane()
{
	m_pIecfgDevice = NULL;
	m_pIecCfgFileDevice = NULL;
}

CIecfgDeviceDockablePane::~CIecfgDeviceDockablePane()
{
}


BEGIN_MESSAGE_MAP(CIecfgDeviceDockablePane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_IECFGDEVICE_NEW, OnIecfgDeviceNew)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_NEW, OnUpdateIecfgDeviceNew)
	ON_COMMAND(ID_IECFGDEVICE_INSERT, OnIecfgDeviceInsert)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_INSERT, OnUpdateIecfgDeviceInsert)
	ON_COMMAND(ID_IECFGDEVICE_CLONE, OnIecfgDeviceClone)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_CLONE, OnUpdateIecfgDeviceClone)
	ON_COMMAND(ID_IECFGDEVICE_DELETE, OnIecfgDeviceDelete)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_DELETE, OnUpdateIecfgDeviceDelete)
	ON_COMMAND(ID_IECFGDEVICE_MOVEUP, OnIecfgDeviceMoveUp)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_MOVEUP, OnUpdateIecfgDeviceMoveUp)
	ON_COMMAND(ID_IECFGDEVICE_MOVEDOWN, OnIecfgDeviceMoveDown)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_MOVEDOWN, OnUpdateIecfgDeviceMoveDown)
	ON_COMMAND(ID_IECFGDEVICE_SAVE, OnIecfgDeviceSave)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_SAVE, OnUpdateIecfgDeviceSave)
	ON_COMMAND(ID_IECFGDEVICE_OPEN, OnIecfgDeviceOpen)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_OPEN, OnUpdateIecfgDeviceOpen)
	ON_COMMAND(ID_IECFGDEVICE_CLOSE, OnIecfgDeviceClose)
	ON_UPDATE_COMMAND_UI(ID_IECFGDEVICE_CLOSE, OnUpdateIecfgDeviceClose)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CIecfgDeviceDockablePane 消息处理程序
int CIecfgDeviceDockablePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	if (!m_gridIecfgDevice.Create(rectDummy, this, ID_IecfgDevice_GRIDCTRL))
	{
		TRACE0("未能创建表格\n");
		return -1;      // 未能创建
	}

	m_gridIecfgDevice.SetFont(g_pGlobalFont12);

	// 加载图像:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_TOOLBAR_DEVICE);
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR_DEVICE, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	m_gridIecfgDevice.InitGrid();
	AdjustLayout();

	return 0;
}

void CIecfgDeviceDockablePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
	//st_PostAdjustCfgMsg();
}

void CIecfgDeviceDockablePane::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_gridIecfgDevice.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CIecfgDeviceDockablePane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_gridIecfgDevice.SetFocus();
}

void CIecfgDeviceDockablePane::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	if (m_gridIecfgDevice.GetSafeHwnd() == NULL)
	{
		return;
	}

	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_gridIecfgDevice.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);

}

void CIecfgDeviceDockablePane::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{

}

void CIecfgDeviceDockablePane::ShowIecfgDevice(CIecCfgFileDevice *pIecfgDevice)
{
	m_pIecCfgFileDevice = pIecfgDevice;
	m_pIecfgDevice = m_pIecCfgFileDevice->GetIecCfgDevice();
	m_gridIecfgDevice.ShowDatas(m_pIecfgDevice);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceNew()
{
	CIecCfgDatasMngr *pNew  = new CIecCfgDatasMngr();
	pNew->CreateDefaultCfgDataMngr();
	pNew->m_strName = CXLanguageResourceIec_61850Cfg::g_sLangTxt_NewConf/*_T("新配置")*/;
	pNew->m_strID = pNew->m_strName;
	m_pIecfgDevice->AddNewChild(pNew, TRUE);
	m_gridIecfgDevice.InsertData(pNew);
	iecfg_SetModified(pNew, TRUE);
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceNew(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pIecCfgFileDevice != NULL);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceInsert()
{
	CString strFile = CIecCfgTool::PopSelIecfgFile(NULL);

	if (strFile.GetLength() <= 5)
	{
		return;
	}

	CIecCfgDatasMngr *pNew  = new CIecCfgDatasMngr();
	pNew->CreateDefaultCfgDataMngr();
	pNew->OpenIecCfgFile(strFile);
	pNew->m_strName = ParseFileName(strFile);
	pNew->m_strID = pNew->m_strName;
	m_pIecfgDevice->AddNewChild(pNew, TRUE);
	m_gridIecfgDevice.InsertData(pNew);
	iecfg_SetModified(pNew, TRUE);
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceInsert(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pIecCfgFileDevice != NULL);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceClone()
{
	CExBaseObject *pSel = m_gridIecfgDevice.GetCurrSelData(1);

	if (pSel == NULL)
	{
		return;
	}

	CIecCfgDatasMngr *pNew  = (CIecCfgDatasMngr*)pSel->Clone();
	m_pIecfgDevice->AddNewChild(pNew, TRUE);
	m_pIecfgDevice->InitSclRef(pNew);
	m_gridIecfgDevice.InsertData(pNew);
	iecfg_SetModified(pNew, TRUE);
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceClone(CCmdUI* pCmdUI)
{
	if (m_pIecCfgFileDevice == NULL)
	{
		pCmdUI->Enable(FALSE);
		return ;
	}

	CExBaseObject *pSel = m_gridIecfgDevice.GetCurrSelData(1);
	pCmdUI->Enable(pSel != NULL);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceDelete()
{
	CExBaseObject *pSel = m_gridIecfgDevice.GetCurrSelData(1);

	if (pSel == NULL)
	{
		return;
	}

	CString strMsg;
	strMsg.Format(CXLanguageResourceIec_61850Cfg::g_sLangTxt_ConfirmDel/*_T("确定要删除【%s】吗？")*/, pSel->m_strID);

	if (MessageBox(strMsg,CXLanguageResourceIec_61850Cfg::g_sLangTxt_Message /*_T("提示")*/, MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		return;
	}

	theApp.CloseIecfgFrame(pSel, TRUE);
	long nRow = m_gridIecfgDevice.GetDataRow(pSel);
	m_gridIecfgDevice.DeleteRow(nRow);
	m_pIecfgDevice->Delete(pSel);
	iecfg_SetModified(m_pIecfgDevice, TRUE);
	m_gridIecfgDevice.ResetScrollBars();
	m_gridIecfgDevice.Invalidate(FALSE);
	m_gridIecfgDevice.UpdateDataIndex(1);
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceDelete(CCmdUI* pCmdUI)
{
	if (m_pIecCfgFileDevice == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	CExBaseObject *pSel = m_gridIecfgDevice.GetCurrSelData(1);
	pCmdUI->Enable(pSel != NULL);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceMoveUp()
{
	m_gridIecfgDevice.MoveUp();
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceMoveUp(CCmdUI* pCmdUI)
{
	if (m_pIecCfgFileDevice == NULL)
	{
		pCmdUI->Enable(FALSE);
		return ;
	}

	long nCurrRow = m_gridIecfgDevice.GetFocusCell().row;

	pCmdUI->Enable(nCurrRow > 1);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceMoveDown()
{
	m_gridIecfgDevice.MoveDown();
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceMoveDown(CCmdUI* pCmdUI)
{
	if (m_pIecCfgFileDevice == NULL)
	{
		pCmdUI->Enable(FALSE);
		return;
	}

	long nCurrRow = m_gridIecfgDevice.GetFocusCell().row;
	long nRows = m_gridIecfgDevice.GetRowCount();

	pCmdUI->Enable(nCurrRow <= nRows-2);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceSave()
{
	theApp.SaveIecfg(m_pIecCfgFileDevice);
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceSave(CCmdUI* pCmdUI)
{
	if (m_pIecCfgFileDevice == NULL)
	{
		pCmdUI->Enable(FALSE);
		return ;
	}
}

void CIecfgDeviceDockablePane::OnIecfgDeviceOpen()
{
	CIecCfgDatasMngr *pIecfgDataMngr = (CIecCfgDatasMngr*)m_gridIecfgDevice.GetCurrSelData(1);
	ASSERT (pIecfgDataMngr != NULL);

	if (pIecfgDataMngr == NULL)
	{
		return;
	}

	theApp.CreateNewIecCfgFrame(pIecfgDataMngr);
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceOpen(CCmdUI* pCmdUI)
{
	OnUpdateIecfgDeviceDelete(pCmdUI);
}

void CIecfgDeviceDockablePane::OnIecfgDeviceClose()
{
	if (m_pIecfgDevice == NULL)//zhouhongjun  20200621
	{
		return;
	}

	CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)m_pIecfgDevice->GetParent();

	if (m_pIecfgDevice->m_bModified)
	{
		CString strMsg;
		strMsg.Format(_T("配置文件【%s】已修改,是否保存?"), pIecCfgFileDevice->m_strName);

		UINT nRet = MessageBox(strMsg, CXLanguageResourceIec_61850Cfg::g_sLangTxt_Message/*_T("提示")*/, MB_YESNOCANCEL | MB_ICONQUESTION);

		if (nRet == IDCANCEL)
		{
			return;
		}

		if (nRet == IDYES)
		{
			theApp.SaveIecfg(m_pIecfgDevice);
		}
	}
	
	POS pos = m_pIecfgDevice->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = m_pIecfgDevice->GetNext(pos);
		theApp.CloseIecfgFrame(p, FALSE);
	}

	m_gridIecfgDevice.ShowDatas(NULL);
	ShowPane(FALSE, FALSE, FALSE);
	CTickCount32 oTickCount;
	long nCountIndex = 0;

	while((pIecCfgFileDevice->GetOpenFileCount()>0)&&(nCountIndex<10))
	{
		oTickCount.DoEvents(200);
	}

	CIecCfgTool::CloseIecFile((CIecCfgFile*)m_pIecfgDevice->GetParent(), FALSE);
	m_pIecfgDevice = NULL;  //zhouhongjun  20200621  CloseIecFile函数中可能会将此对象删除
	m_pIecCfgFileDevice = NULL;

//	SetTimer(CLOSE_IECFG_FILE_DEVICE_TIMERID, 200, NULL);
}

void CIecfgDeviceDockablePane::OnUpdateIecfgDeviceClose(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_pIecCfgFileDevice != NULL);
}

void CIecfgDeviceDockablePane::OnTimer(UINT_PTR nIDEvent)
{
	ASSERT(m_pIecfgDevice);
	CIecCfgFileDevice *pIecFileDevice = (CIecCfgFileDevice*)m_pIecfgDevice->GetParent();
	
	if (pIecFileDevice->GetOpenFileCount() == 0)
	{
		KillTimer(CLOSE_IECFG_FILE_DEVICE_TIMERID);
		CIecCfgTool::CloseIecFile((CIecCfgFile*)m_pIecfgDevice->GetParent(), FALSE);
		m_pIecfgDevice = NULL;  //zhouhongjun  20200621  CloseIecFile函数中可能会将此对象删除
	}

	m_pIecCfgFileDevice = NULL;
	CDockablePane::OnTimer(nIDEvent);
}
