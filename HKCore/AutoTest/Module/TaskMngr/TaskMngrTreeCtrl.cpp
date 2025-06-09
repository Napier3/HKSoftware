// D:\WorkPM\Source\PMTest\Module\UITestItem\TaskMngrTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "TaskMngrTreeCtrl.h"
#include "../../../Module/api/GloblaDrawFunctions.h"
#include "../TCtrlCntrDefine.h"
#include "..\..\Module\EpotoInterface\EpotoInterface.h"
#include "../XLanguageResourceAts.h"
// CTaskMngrTreeCtrl

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ID_NEW_TEST_TASK						1000
#define ID_NEW_TEST_PROJECT				1001
#define ID_DELETE_TEST_TASK				1002
#define ID_DELETE_TEST_PROJECT		1003
#define ID_FILE_TEST_TASK						1004
#define ID_FILE_TEST_PROJECT				1005

#define ID_OPEN_PROJECT							1006
#define ID_CLOSE_PROJECT							1007

IMPLEMENT_DYNAMIC(CTaskMngrTreeCtrl, CTreeCtrl)

CTaskMngrTreeCtrl::CTaskMngrTreeCtrl()
{
	m_lfFont.lfHeight=-12;
	m_lfFont.lfWidth=0;
	m_lfFont.lfEscapement=0;
	m_lfFont.lfOrientation=0;
	m_lfFont.lfWeight=400;
	m_lfFont.lfItalic=0;
	m_lfFont.lfUnderline=0;
	m_lfFont.lfStrikeOut=0;
	m_lfFont.lfCharSet = DEFAULT_CHARSET;
	m_lfFont.lfOutPrecision=0;
	m_lfFont.lfClipPrecision=0;
	m_lfFont.lfQuality=0;
	m_lfFont.lfPitchAndFamily=0;
#ifdef UNICODE
	lstrcpy(m_lfFont.lfFaceName,g_sLangTxt_LetterForm/*L"宋体"*/);
#else
	strcpy(m_lfFont.lfFaceName,g_sLangTxt_LetterForm/*L"宋体"*/);
#endif // UNICODE

	m_lfFont.lfHeight = -14;
	m_lfFont.lfWeight = 400;
	m_SSerif8Font.CreateFontIndirect(&m_lfFont);

	CSize sizeCheck;
	GetCheckBoxSize(sizeCheck);
	//选择框的位置
	m_xSelCheckBox = 1;
	m_xSelCheckBox += sizeCheck.cx / 2;
	m_xItemTypeIcon = 1 + sizeCheck.cx;

	//测试项目类型图标位置
	m_xItemTitle = 1 * 2 + 16/*ICON*/ + sizeCheck.cx;
	m_bInUpdateItemsState = FALSE;

	m_bInUpdateItemsState = FALSE;
	m_crWindow = RGB(255,255,255);

	//m_pWorkSpace = NULL;
	m_pCurrTestProject = NULL;
	m_pItemSelected = NULL;
}

CTaskMngrTreeCtrl::~CTaskMngrTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CTaskMngrTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CTaskMngrTreeCtrl::OnNMCustomdraw)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_NEW_TEST_TASK,&CTaskMngrTreeCtrl::OnNewTestTask)
	ON_COMMAND(ID_NEW_TEST_PROJECT,&CTaskMngrTreeCtrl::OnNewTestProject)
	ON_COMMAND(ID_DELETE_TEST_TASK,&CTaskMngrTreeCtrl::OnDeleteTestTask)
	ON_COMMAND(ID_DELETE_TEST_PROJECT,&CTaskMngrTreeCtrl::OnDeleteTestProject)
	ON_COMMAND(ID_FILE_TEST_TASK,&CTaskMngrTreeCtrl::OnFileTestTask)
	ON_COMMAND(ID_FILE_TEST_PROJECT,&CTaskMngrTreeCtrl::OnFileTestProject)
	ON_COMMAND(ID_OPEN_PROJECT,&CTaskMngrTreeCtrl::OnOpenProject)
	ON_COMMAND(ID_CLOSE_PROJECT,&CTaskMngrTreeCtrl::OnCloseProject)
END_MESSAGE_MAP()


BOOL CTaskMngrTreeCtrl::InitShowTaskTree(CTestProject* pTestProject)
{
	m_pCurrTestProject = pTestProject;

	if(CTCtrlCntrWorkSpace::g_pWorkSpace == NULL)
	{
		return FALSE;
	}
	else
	{
		DeleteAllItems();
		InsertChildrenTaskItem(CTCtrlCntrWorkSpace::g_pWorkSpace,NULL);
	}

	//else
	//{
	//	DeleteAllItems();
	//	CTCtrlCntrWorkSpace::g_pWorkSpace ->InsertChildrenTreeCtrl(this,NULL);
	//	Invalidate(FALSE);
	//}

	//展开全部子项目
	HTREEITEM hItem = GetFirstVisibleItem();

	while (hItem != NULL)
	{
		Expand(hItem,TVE_EXPAND);
		hItem = GetNextVisibleItem(hItem);
	}

	return TRUE;
}

// CTaskMngrTreeCtrl 消息处理程序

BOOL CTaskMngrTreeCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	return CTreeCtrl::Create(dwStyle, rect, pParentWnd, nID);
}

long CTaskMngrTreeCtrl::_DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult)
{
	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;

	CDC dc;
	dc.Attach((HDC)hDC);
	HTREEITEM hCurrItem = (HTREEITEM)hItem;
	*pResult = CDRF_DODEFAULT;

	//=========================================================================
	if (dwDrawStage == CDDS_PREPAINT)	// before the painting cycle begins
	{
		*pResult = CDRF_NOTIFYITEMDRAW /*| CDRF_NOTIFYPOSTPAINT*/;
	}
	else if (dwDrawStage == CDDS_ITEMPREPAINT)	// before an item is drawn
	{
		if (hCurrItem)
		{
			CRect rectItem1;
			GetItemRect(hCurrItem, &rectItem1, FALSE);	// get rect for item

			if (!IsBadRect(rectItem1))
			{
				CBrush brush(m_crWindow);
				dc.FillRect(&rectItem1, &brush);		// erase entire background
			}
		}

		*pResult = CDRF_NOTIFYPOSTPAINT | CDRF_NEWFONT;
	}
	else if (dwDrawStage == CDDS_ITEMPOSTPAINT && !m_bInUpdateItemsState)	// after an item has been drawn
	{
		CExBaseObject* pCurSel = (CExBaseObject*)GetItemData((HTREEITEM)hCurrItem);

		if(pCurSel != NULL)
		{
			//如果是CTestProject类别
			if(pCurSel->GetClassID() == CLASSID_TESTPROJECT)
			{
				HTREEITEM hSelItem = GetSelectedItem();
				//绘制项目名称
				BOOL bSelected = FALSE;
				if(hSelItem == hCurrItem)
					bSelected = TRUE;

				BOOL bChangeFont = FALSE;
				CFont *pOldFont = NULL;
				CFont fontChange;
				COLORREF clrTextSave,clrBkSave;

				LOGFONT lfFont;

				if(pCurSel == m_pCurrTestProject)
				{
					bChangeFont = TRUE;
					lfFont = m_lfFont;
					lfFont.lfWeight = 600;
				}

				if(bChangeFont)
				{
					fontChange.CreateFontIndirect(&lfFont);
					pOldFont = dc.SelectObject(&fontChange);
				}

				BOOL bEnable = TRUE;
				CRect rectItem;
				GetItemRect(hCurrItem, &rectItem, FALSE);		// get rect for entire item
				CRect rectText;
				GetItemRect(hCurrItem, &rectText, TRUE);		// get rect for text
				rectText.right = rectItem.right;
				dc.FillSolidRect(&rectText, m_crWindow);

				long yItemCenter = rectItem.CenterPoint().y;

				CRect rectTitle = rectText;
				//绘制选择的Item的底色
				if (bSelected)
				{
					clrTextSave = dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
					clrBkSave = dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
					dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
				}
				else
				{
					clrTextSave = dc.SetTextColor(GetStateColor(pCurSel));
					dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_WINDOW)));
				}

				CString strName ;
				if(pCurSel != NULL)
					strName = pCurSel->m_strName;
				dc.DrawText(strName,rectTitle,DT_SINGLELINE /*| DT_NOPREFIX | DT_NOCLIP */| DT_VCENTER);

				dc.SetTextColor(clrTextSave);
				if (bSelected)
				{
					dc.SetBkColor(clrBkSave);
				}

				if (bChangeFont)
				{
					dc.SelectObject(pOldFont);
					fontChange.DeleteObject();
				}	
			}
		}
	}

	dc.Detach();
	return S_OK;		
}

void CTaskMngrTreeCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		NMTVCUSTOMDRAW* pCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
		CDC* pDC = CDC::FromHandle(pCD->nmcd.hdc);
		HTREEITEM hItem = reinterpret_cast<HTREEITEM> (pCD->nmcd.dwItemSpec);
		*pResult = CDRF_DODEFAULT;

		LPNMHDR pNmhdr = (LPNMHDR)pNMHDR;          
		LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)pNMHDR;

		if(CTCtrlCntrWorkSpace::g_pWorkSpace  == NULL)
		{
			return ;
		}
		else 
		{
			_DrawItem((long)pCD->nmcd.hdc
				,(long)hItem
				,pCD->nmcd.dwDrawStage
				,pResult);
		}
	}
	catch(...)
	{

	}
}

//双击树形控件，新建框架，用于测试 2010-07-29
void CTaskMngrTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
#ifndef AUTOTEST_DEMO
	
#endif

	HTREEITEM hSelItem = GetSelectedItem();
	if(hSelItem == NULL)
	{
		return ;
	}
	
	CExBaseObject* pObj = (CExBaseObject*)GetItemData(hSelItem);

	if(pObj->GetClassID() == CLASSID_TESTPROJECT)
	{
		CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
		AfxGetApp()->PostThreadMessage(WM_CREATE_NEW_PROJECT_FRAME,(WPARAM)pObj,(LPARAM)pWnd);
	}
	
	CTreeCtrl::OnLButtonDblClk(nFlags, point);
}

//根据Project的打开状态获取其节点的颜色
COLORREF CTaskMngrTreeCtrl::GetStateColor(CExBaseObject* pObj)
{
	COLORREF color = RGB(0,0,0);

	if(pObj != NULL)
	{
		if(pObj->GetClassID() == CLASSID_TESTPROJECT)
		{
			CTestProject* pTestProject = (CTestProject*)pObj;

			BOOL bFlag = IsProjectOpen(pTestProject);
			
			if(bFlag == TRUE)
			{
				color = RGB(0,0,255);
			}
			else
			{
				color = RGB(0,0,0);
			}
		}
	}

	return color;
}
void CTaskMngrTreeCtrl::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
{
	// TODO: 在此处添加消息处理程序代码
}

void CTaskMngrTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//CTreeCtrl::OnRButtonDown(nFlags, point);
	UINT uFlags;
	HTREEITEM hItem = HitTest(point, &uFlags);

	if ((hItem != NULL) && (TVHT_ONITEM & uFlags))
	{
		SelectItem(hItem);
	}


	HTREEITEM hItemSelected = GetSelectedItem();
	if(hItemSelected != NULL)
	{
		m_pItemSelected= (CExBaseObject*)GetItemData(hItemSelected);
		ASSERT(m_pItemSelected != NULL);
		ClientToScreen(&point);
		PopUpContextMenu(this, point,m_pItemSelected->GetClassID());
	}
}

void CTaskMngrTreeCtrl::PopUpContextMenu(CWnd* pWnd, CPoint point,UINT nClassID)
{
	CMenu menu;		
	menu.CreatePopupMenu();

	// 添加菜单项
	if(nClassID == CLASSID_TESTTASK)
	{
		menu.AppendMenu(MF_STRING,ID_NEW_TEST_TASK,g_sLangTxt_NewCreatTask/*_T("新建任务")*/);
		menu.AppendMenu(MF_STRING,ID_NEW_TEST_PROJECT,g_sLangTxt_NewProject/*_T("新建工程")*/);
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_DELETE_TEST_TASK,g_sLangTxt_DeleteTask/*_T("删除任务")*/);
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_FILE_TEST_TASK,g_sLangTxt_TaskArchive/*_T("任务归档")*/);
	}
	else if(nClassID == CLASSID_TESTPROJECT)
	{
		if( !IsProjectOpen((CTestProject*)m_pItemSelected) )
		{
			menu.AppendMenu(MF_STRING,ID_OPEN_PROJECT, g_sLangTxt_OpenProject/*_T("打开工程")*/);
			menu.AppendMenu(MF_SEPARATOR);
		}
		else
		{
			if(m_pItemSelected == m_pCurrTestProject)
			{
				menu.AppendMenu(MF_STRING,ID_CLOSE_PROJECT, g_sLangTxt_CloseProject/*_T("关闭工程")*/);
				menu.AppendMenu(MF_SEPARATOR);
			}
		}
		
		menu.AppendMenu(MF_STRING,ID_DELETE_TEST_PROJECT,g_sLangTxt_DeleteProject/*_T("删除工程")*/);
		menu.AppendMenu(MF_SEPARATOR);
		menu.AppendMenu(MF_STRING,ID_FILE_TEST_PROJECT,g_sLangTxt_ProjectArchive/*_T("工程归档")*/);
	}
	
	//确定弹出式菜单的位置
	menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			
	//资源回收
	HMENU hmenu=menu.Detach();			
	menu.DestroyMenu();	
}

void CTaskMngrTreeCtrl::OnNewTestTask()
{
	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(WM_NEW_TEST_TASK,(WPARAM)m_pItemSelected,0);
}

void CTaskMngrTreeCtrl::OnNewTestProject()
{
	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(WM_NEW_TEST_PROJECT,(WPARAM)m_pItemSelected,0);	
}

void CTaskMngrTreeCtrl::OnDeleteTestTask()
{
	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(WM_DELETE_TEST_TASK,(WPARAM)m_pItemSelected,0);
}

void CTaskMngrTreeCtrl::OnDeleteTestProject()
{
	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(WM_DELETE_TEST_PROJECT,(WPARAM)m_pItemSelected,0);
}

void CTaskMngrTreeCtrl::OnFileTestTask()
{
	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(WM_FILE_TEST_TASK,(WPARAM)m_pItemSelected,0);
}

void CTaskMngrTreeCtrl::OnFileTestProject()
{
	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(WM_FILE_TEST_PROJECT,(WPARAM)m_pItemSelected,0);
}

void CTaskMngrTreeCtrl::OnOpenProject()
{
#ifndef AUTOTEST_DEMO

#endif

	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	AfxGetApp()->PostThreadMessage(WM_CREATE_NEW_PROJECT_FRAME,(WPARAM)m_pItemSelected,(LPARAM)pWnd);
}

void CTaskMngrTreeCtrl::OnCloseProject()
{
	CWnd* pWnd = GetParent()->GetParent()->GetParent()->GetParent();
	ASSERT(pWnd != NULL);
	pWnd->PostMessage(WM_CLOSE_TEST_PROJECT,(WPARAM)m_pItemSelected,1);
}

BOOL CTaskMngrTreeCtrl::IsProjectOpen(CTestProject* pTestProject)
{
	BOOL bFlag = FALSE;
	POS pos = CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.GetHeadPosition();

// 	while(pos != NULL)
// 	{
// 		CTestControl* pTestControl = (CTestControl*)CTCtrlCntrWorkSpace::g_pWorkSpace->m_oTestControlList.GetNext(pos);
// 		if(pTestProject == pTestControl->GetTestProject())
// 		{
// 			bFlag = TRUE;
// 		}
// 	}

	return bFlag;
}

void CTaskMngrTreeCtrl::InsertTaskTreeItem(CExBaseObject* pObj,HTREEITEM hParent)
{
	long nCount = pObj->GetClassID()  & 0x0000FFFF;
	DWORD dwItemData = (DWORD)InsertItem(pObj->m_strName,nCount,nCount,hParent);
	SetItemData((HTREEITEM)dwItemData,(DWORD_PTR)pObj);
	InsertChildrenTaskItem(pObj,(HTREEITEM)dwItemData);
}

void CTaskMngrTreeCtrl::InsertChildrenTaskItem(CExBaseObject* pObj,HTREEITEM hParent)
{
	if( pObj->IsBaseList() )
	{
		CExBaseList* pList = (CExBaseList*)pObj;

		POS pos = pList->GetHeadPosition();
		
		CExBaseObject* pItem = NULL;
		while(pos)
		{
			pItem = pList->GetNext(pos);
			InsertTaskTreeItem(pItem,hParent);
		}
	}
}