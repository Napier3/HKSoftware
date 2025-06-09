// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// ("Fluent UI")，该示例仅作为参考资料提供， 
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问  
// http://msdn.microsoft.com/officeui。
//
// 版权所有 (C) Microsoft Corporation
// 保留所有权利。

#include "stdafx.h"
#include "MainFrm.h"
#include "CharLibPane.h"
#include "Resource.h"
#include "CharLibDev.h"
#include "DlgCharFolder.h"
#include "XLanguageResourceAts_CharLibDev.h"
#include "..\..\Module\XLanguage\XLangMenu.h"
class CCharLibViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CCharLibPane;

	DECLARE_SERIAL(CCharLibViewMenuButton)

public:
	CCharLibViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
};

IMPLEMENT_SERIAL(CCharLibViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// 构造/析构
//////////////////////////////////////////////////////////////////////

CCharLibPane::CCharLibPane()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}

CCharLibPane::~CCharLibPane()
{
}

BEGIN_MESSAGE_MAP(CCharLibPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLASS_ADD_MEMBER_FUNCTION, OnClassAddMemberFunction)
	ON_COMMAND(ID_CLASS_ADD_MEMBER_VARIABLE, OnClassAddMemberVariable)
	ON_COMMAND(ID_CLASS_DEFINITION, OnClassDefinition)
	ON_COMMAND(ID_CLASS_PROPERTIES, OnClassProperties)
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_COMMAND(ID_EDIT_FOLDER, OnEditFolder)
	ON_UPDATE_COMMAND_UI(ID_EDIT_FOLDER, OnUpdateEditFolder)
	ON_COMMAND(ID_DELETE_FOLDER, OnDeleteFolder)
	ON_UPDATE_COMMAND_UI(ID_DELETE_FOLDER, OnUpdateDeleteFolder)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnSort)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SORTING_GROUPBYTYPE, ID_SORTING_SORTBYACCESS, OnUpdateSort)
	ON_NOTIFY(NM_DBLCLK, IDC_CHARLIB_REECTRL, &CCharLibPane::OnNMDblclkCharLibTree)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCharLibPane 消息处理程序

int CCharLibPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndCharLibView.Create(dwViewStyle, rectDummy, this, IDC_CHARLIB_REECTRL))
	{
		TRACE0("未能创建类视图\n");
		return -1;      // 未能创建
	}

	// 加载图像:
	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

// 	CMenu menuSort;
// 	menuSort.LoadMenu(IDR_POPUP_SORT);
// 
// 	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CCharLibViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));
// 
// 	CCharLibViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CCharLibViewMenuButton, m_wndToolBar.GetButton(0));
// 
// 	if (pButton != NULL)
// 	{
// 		pButton->m_bText = FALSE;
// 		pButton->m_bImage = TRUE;
// 		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
// 		pButton->SetMessageWnd(this);
// 	}

	return 0;
}

void CCharLibPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CCharLibPane::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndCharLibView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// 选择已单击的项:
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CCharLibPane::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndCharLibView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CCharLibPane::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CCharLibPane::OnSort(UINT id)
{
	if (m_nCurrSort == id)
	{
		return;
	}

	m_nCurrSort = id;

	CCharLibViewMenuButton* pButton =  DYNAMIC_DOWNCAST(CCharLibViewMenuButton, m_wndToolBar.GetButton(0));

	if (pButton != NULL)
	{
		pButton->SetImage(GetCmdMgr()->GetCmdImage(id));
		m_wndToolBar.Invalidate();
		m_wndToolBar.UpdateWindow();
	}
}

void CCharLibPane::OnUpdateSort(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrSort);
}

void CCharLibPane::OnClassAddMemberFunction()
{
	AfxMessageBox(g_sLangTxt_AddMemberFctn/*_T("添加成员函数...")*/);
}

void CCharLibPane::OnClassAddMemberVariable()
{
	// TODO: 在此处添加命令处理程序代码
}

void CCharLibPane::OnClassDefinition()
{
	// TODO: 在此处添加命令处理程序代码
}

void CCharLibPane::OnClassProperties()
{
	// TODO: 在此处添加命令处理程序代码
}

CCharacterFolder* CCharLibPane::GetCurrSelFolder()
{
	CCharacterFolder *pFolder = m_wndCharLibView.GetCurrSelFolder(TRUE);

	if (pFolder == NULL)
	{
		pFolder = &theApp.m_oCharacteristicLib;
	}

	return pFolder;
}

void CCharLibPane::OnNewFolder()
{
	CCharacterFolder *pFolder = GetCurrSelFolder();
	CDlgCharFolder dlg;
	dlg.m_pParentFolder = pFolder;

	if (dlg.DoModal() == IDOK)
	{
		CCharacterFolder *pNew = new CCharacterFolder();
		pNew->m_strName = dlg.m_strName;
		pNew->m_strID   = dlg.m_strName;
		pFolder->AddNewChild(pNew);
		m_wndCharLibView.InsertCharFolder(pNew);
		char_dev_SetModifiedFlag(&theApp.m_oCharacteristicLib, TRUE);
	}

}

void CCharLibPane::OnEditFolder()
{
	CCharacterFolder *pFolder = m_wndCharLibView.GetCurrSelFolder(FALSE);

	if (pFolder == NULL)
	{
		return;
	}

	CDlgCharFolder dlg;
	dlg.m_pParentFolder = (CExBaseList*)pFolder->GetParent();
	dlg.m_strName = pFolder->m_strName;

	if (dlg.DoModal() == IDOK)
	{
		pFolder->m_strName = dlg.m_strName;
		pFolder->m_strID   = dlg.m_strName;
		m_wndCharLibView.UpdateCharFolder(pFolder);
		char_dev_SetModifiedFlag(&theApp.m_oCharacteristicLib, TRUE);
	}
}

void CCharLibPane::OnUpdateEditFolder(CCmdUI* pCmdUI)
{
	CCharacterFolder *pFolder = m_wndCharLibView.GetCurrSelFolder(FALSE);

	pCmdUI->Enable(pFolder != NULL);

}

void CCharLibPane::OnDeleteFolder()
{
	MessageBox(g_sLangTxt_NotReali/*_T("还没有实现")*/);
}

void CCharLibPane::OnUpdateDeleteFolder(CCmdUI* pCmdUI)
{
	CCharacterFolder *pFolder = m_wndCharLibView.GetCurrSelFolder(FALSE);

	pCmdUI->Enable(pFolder != NULL);
}

void CCharLibPane::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndCharLibView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CCharLibPane::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndCharLibView.SetFocus();
}

void CCharLibPane::ShowCharLib()
{
	m_wndCharLibView.ShowCharLib(&theApp.m_oCharacteristicLib);
}

void CCharLibPane::InsertCharTemp(CCharacteristic *pCharTemp)
{
	m_wndCharLibView.InsertCharTemp(pCharTemp);
}

void CCharLibPane::UpdateCharTemp(CCharacteristic *pCharTemp)
{
	m_wndCharLibView.UpdateCharTemp(pCharTemp);
}

void CCharLibPane::OnChangeVisualStyle()
{
	m_CharLibViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(g_sLangTxt_UnAddPic/*_T("无法加载位图: %x\n")*/, uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_CharLibViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_CharLibViewImages.Add(&bmp, RGB(255, 0, 0));

	m_wndCharLibView.SetImageList(&m_CharLibViewImages, TVSIL_NORMAL);

// 	m_wndToolBar.CleanUpLockedImages();
// 	m_wndToolBar.LoadBitmap(IDB_SORT_24, 0, 0, TRUE);
}


void CCharLibPane::OnNMDblclkCharLibTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CCharacteristic *pCharTemplate = m_wndCharLibView.GetCurrSelChar();

	theApp.OpenCharTemplate(pCharTemplate);
}
