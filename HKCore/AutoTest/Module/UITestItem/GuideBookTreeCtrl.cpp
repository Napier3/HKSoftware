#include "stdafx.h"
#include "GuideBookTreeCtrl.h"
#include "../../../Module/api/GloblaDrawFunctions.h"
#include "../TestControl/TctrlCntrBaseApp.h"
#include "../TCtrlCntrDefine.h"
#include "ViewSetsDialog.h"
#include "..\AutoTestDocFrame\AutoTestBaseTreeView.h"

#include "..\XLanguageResourceAts.h"
#include "..\TestControl/AtsNewTestTool.h"
#include "../../../Module/EpotoInterface/EpotoInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// #include "..\..\..\Module\Encrypt\EncryptTool.h"

extern UINT UI_GetTestItemReportID();

BEGIN_MESSAGE_MAP(CGuideBookTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CGuideBookTreeCtrl::OnCustomdraw)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(WM_TESTPOINT,OnTestPoint)
	ON_COMMAND(WM_TEST_ALL_INLEGIBLE_ITEMS,OnTestAllInlegibleItems)
	ON_COMMAND(WM_TESTPOINT_MD_ONE,OnTestPoint_MdOne)
	ON_COMMAND(WM_UPDATE_GBITEMOBJ,OnUpdateGbItem)
	ON_COMMAND(WM_UPDATE_PARA_TO_GBDEV,OnUpdateGbItemToGb)
	ON_COMMAND(WM_VIEW_DEVICESETS,OnViewDeviceSets)
	ON_COMMAND(WM_EXPAND_ALL_CHILDREN,OnExpandAllChildren)
	ON_COMMAND(WM_TESTBELOW,OnTestBelow)
	ON_COMMAND(WM_ITEM_PARA_EDIT,OnEditItemPara)
	ON_COMMAND(WM_SHOWREPORT,OnShowReport)
	ON_COMMAND(WM_SHOWRECORD,OnQueryRecord)
	ON_COMMAND(WM_SHOWCHARDRAW,OnShowCharDraw)
	ON_WM_CONTEXTMENU()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, &CGuideBookTreeCtrl::OnTvnItemexpanded)
	ON_NOTIFY_REFLECT(TVN_ITEMCHANGED, &CGuideBookTreeCtrl::OnTvnItemChanged)
	ON_MESSAGE(WM_INSERT_ITEMS,&CGuideBookTreeCtrl::OnInsertItems)
END_MESSAGE_MAP()

#define GAP_TESTITEMFLAG 1

CGuideBookTreeCtrl::CGuideBookTreeCtrl()
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
	strcpy(m_lfFont.lfFaceName,"宋体");
#endif // UNICODE

	m_lfFont.lfHeight = -14;
	m_lfFont.lfWeight = 400;
	m_SSerif8Font.CreateFontIndirect(&m_lfFont);

	m_nTimerIDEvent = 2;
	m_bShowOnlySelTestItems = false;

	m_crWindow = RGB(255,255,255);

	CSize sizeCheck;
	GetCheckBoxSize(sizeCheck);

	//选择框的位置
	m_xSelCheckBox = GAP_TESTITEMFLAG;
	m_xSelCheckBox += sizeCheck.cx / 2;
	m_xItemTypeIcon = GAP_TESTITEMFLAG + sizeCheck.cx;

	//测试项目类型图标位置
	m_xItemTitle = GAP_TESTITEMFLAG * 2 + 16/*ICON*/ + sizeCheck.cx;
	m_bInUpdateItemsState = FALSE;

	m_pCurrSelTestItem = NULL;
	m_nCurrSelTestItemIndex = -1;
	m_hCurrSelTestItem = NULL;
	m_bInTestItemInitState = FALSE;

	m_pTestControl = NULL;
	m_pParent = NULL;
}

CGuideBookTreeCtrl::~CGuideBookTreeCtrl()
{

}

void CGuideBookTreeCtrl::InitShowTestControl(CTestControl* pTestControl)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_pTestControl = pTestControl;
	pTestControl->m_pGbTreeCtrl = this;

	if(m_pTestControl != NULL)
	{
		m_bInTestItemInitState = TRUE;
		DeleteAllItems();

		InsertGbItemChildrenToTreeCtrl(m_pTestControl->m_pGuideBook,NULL);
// 		if (m_pTestControl->GetTestProject() != NULL)
// 		{
// 		}

		m_bInTestItemInitState = FALSE;
	}
}	
void CGuideBookTreeCtrl::InitShowTestControl2(CTestControlBase* pTestControl)
{
	CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;

	m_pTestControl = pTestControl;
	//m_pTestControl->m_pGbTreeCtrl = this;

	if(m_pTestControl != NULL)
	{
		m_bInTestItemInitState = TRUE;
		DeleteAllItems();

		InsertGbItemChildrenToTreeCtrl(m_pTestControl->m_pGuideBook,NULL);
// 		if (m_pTestControl->GetTestProject() != NULL)
// 		{
// 		}

		m_bInTestItemInitState = FALSE;
	}
}	
//弹出菜单：测试菜单、查看报告菜单根据不同情况弹出
//李俊庆
void CGuideBookTreeCtrl::OnContextMenuEx_Testing(CWnd* pWnd, CPoint point)
{
	HTREEITEM hItem = GetSelectedItem();
	CBaseObject *pObj = (CBaseObject*)GetItemData(hItem);

	if ( pObj == NULL)
	{
		return;
	}

	UINT nClassID = pObj->GetClassID();
	BOOL bAddReportMenu = FALSE;
	UINT nParentClassID = 0;
	BOOL bAddDeviceMenu = FALSE;

	CGbItemBase *pGbItem = NULL;
	CReports *pReports = NULL;

	if (Gb_IsItemBaseClassID(nClassID))
	{
		pGbItem = (CGbItemBase*)pObj;
		pReports = pGbItem->GetReports();

		if (pReports == NULL)
		{
			bAddReportMenu = FALSE;
		}
		else
		{
			bAddReportMenu = (pReports->GetCount() > 0);
		}
	}

	if (nClassID == GBCLASSID_MACROTEST)
	{
		if (pGbItem->FindRecordFile() != NULL)
		{
			bAddReportMenu = TRUE;
		}
	}

	CMenu menu;		
	menu.CreatePopupMenu();

	if (GBCLASSID_DEVICE == nClassID)
	{
		menu.AppendMenu(MF_STRING,WM_VIEW_DEVICESETS,g_sLangTxt_ViewDevPara/*L"查看设备参数"*/);
		menu.AppendMenu(MF_SEPARATOR);
		bAddDeviceMenu = TRUE;
	}

	if (bAddReportMenu)
	{
		menu.AppendMenu(MF_STRING, WM_SHOWREPORT,g_sLangTxt_ViewReport/*L"查看报告"*/); 
		menu.AppendMenu(MF_STRING, WM_SHOWRECORD,g_sLangTxt_ViewRecordFile/*L"查看录波文件"*/); 
	}

	if (GBCLASSID_ITEMS == nClassID)
	{
		menu.AppendMenu(MF_STRING,WM_EXPAND_ALL_CHILDREN,g_sLangTxt_ExpdNodes/*L"展开全部子节点"*/);
	}

	//确定弹出式菜单的位置
	if (bAddReportMenu || bAddDeviceMenu)
	{
		menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			

		//资源回收
		HMENU hmenu=menu.Detach();			
		menu.DestroyMenu();	
	}	
}

void CGuideBookTreeCtrl::OnContextMenuEx_Normal(CWnd* pWnd, CPoint point)
{
	HTREEITEM hItem = GetSelectedItem();
	CBaseObject *pObj = (CBaseObject*)GetItemData(hItem);

	if ( pObj == NULL)
	{
		return;
	}

	UINT nClassID = pObj->GetClassID();
	BOOL bAddTestMenu = TRUE;
	BOOL bAddEditMenu = FALSE;
	BOOL bAddUpdateMenu = FALSE;
	BOOL bAddReportMenu = FALSE;
	UINT nParentClassID = 0;
	BOOL bAddRecordMenu = FALSE;

	if (nClassID == GBCLASSID_COMMCMD)
	{
		CBaseObject *pParent = pObj->GetParent();
		nParentClassID = pParent->GetClassID();

		if (nParentClassID == GBCLASSID_ITEMS || nParentClassID == GBCLASSID_JOBGUIDE
			|| nParentClassID == GBCLASSID_DEVICE)
		{
		}
		else
		{
			bAddTestMenu = FALSE;
		}
	}

	if (nClassID == GBCLASSID_MACROTEST || nClassID == GBCLASSID_COMMCMD)
	{
		bAddEditMenu = TRUE;
	}

	if (Gb_IsGbItemClassID(nClassID) || nClassID == GBCLASSID_ITEMS)
	{
		bAddUpdateMenu = TRUE;
	}

	CGbItemBase *pGbItem = NULL;
	CReports *pReports = NULL;

	if (Gb_IsItemBaseClassID(nClassID))
	{
		pGbItem = (CGbItemBase*)pObj;
		pReports = pGbItem->GetReports();

		if (pReports == NULL)
		{
			bAddReportMenu = FALSE;
		}
		else
		{
			bAddReportMenu = (pReports->GetCount() > 0);
		}
	}

	if (nClassID == GBCLASSID_MACROTEST)
	{
		if (pGbItem->FindRecordFile() != NULL)
		{
			bAddReportMenu = TRUE;
		}
	}

	CMenu menu;		
	menu.CreatePopupMenu();

	if (GBCLASSID_DEVICE == nClassID)
	{
		menu.AppendMenu(MF_STRING,WM_VIEW_DEVICESETS,g_sLangTxt_ViewDevPara/*L"查看设备参数"*/);

		if (((CDevice*)pObj)->GetState() == TEST_STATE_INLEGIBLE)
		{
			menu.AppendMenu(MF_STRING,WM_TEST_ALL_INLEGIBLE_ITEMS,g_sLangTxt_TestInlegibleItems);
		}

		menu.AppendMenu(MF_SEPARATOR);
	}

	//if (m_pTestControl->GetParent() == NULL)
	{
		if (bAddTestMenu)
		{
			if (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_nUseSttAtsSvr == 0
				|| (CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_nUseSttAtsSvr == 1 && CTCtrlCntrConfig::g_pTCtrlCntrConfig->m_nDisableOptrWhenUseAtsSvr == 0))
			{
				menu.AppendMenu(MF_STRING,WM_TESTPOINT,g_sLangTxt_TestCurrtItem/*L"测试当前项目"*/);

				if ( ((nClassID == GBCLASSID_SAFETY) || (nClassID == GBCLASSID_SYSPARAEDIT)) && (ats_IsTestControlMode_MDGBRPT(m_pTestControl)) )
				{
					menu.AppendMenu(MF_STRING,WM_TESTPOINT_MD_ONE,g_sLangTxt_TestCurrtItemDev/*L"测试当前项目-装置独立测试"*/);
				}

				menu.AppendMenu(MF_STRING,WM_TESTBELOW,g_sLangTxt_TestCurrtItemStart/*L"从当前项目开始测试"*/);
			}
		}
	}

	if (bAddEditMenu || bAddUpdateMenu)
	{
		if (bAddTestMenu)
		{
			menu.AppendMenu(MF_SEPARATOR);
		}

		if (bAddEditMenu)
		{
			menu.AppendMenu(MF_STRING,WM_ITEM_PARA_EDIT,g_sLangTxt_ParaMdf/*L"参数修改"*/);
		}

		menu.AppendMenu(MF_STRING,WM_UPDATE_GBITEMOBJ,g_sLangTxt_UpdataPara/*L"更新参数"*/);
		menu.AppendMenu(MF_STRING,WM_UPDATE_PARA_TO_GBDEV,g_sLangTxt_UpdataParaToGb/*L"更新参数至模板"*/);
	}

	if (bAddReportMenu)
	{
		if (bAddTestMenu || bAddEditMenu)
		{
			menu.AppendMenu(MF_SEPARATOR);
		}

		menu.AppendMenu(MF_STRING, WM_SHOWREPORT,g_sLangTxt_ViewReport/*L"查看报告"*/); 

		if (bAddReportMenu)
		{
			menu.AppendMenu(MF_STRING, WM_SHOWRECORD,g_sLangTxt_ViewRecordFile/*L"查看录波文件"*/); 
		}
	}

	if (GBCLASSID_ITEMS == nClassID)
	{
		menu.AppendMenu(MF_STRING,WM_EXPAND_ALL_CHILDREN,g_sLangTxt_ExpdNodes/*L"展开全部子节点"*/);
	}

	if (GBCLASSID_MACROCHARITEMS == nClassID)
	{
		menu.AppendMenu(MF_STRING,WM_SHOWCHARDRAW,g_sLangTxt_ViewCharCurve/*L"查看特性曲线"*/);
	}

	//确定弹出式菜单的位置
	if (bAddTestMenu || bAddReportMenu || bAddEditMenu || bAddRecordMenu)
	{
		menu.TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,pWnd);			

		//资源回收
		HMENU hmenu=menu.Detach();			
		menu.DestroyMenu();	
	}	
}

void CGuideBookTreeCtrl::OnContextMenuEx(CWnd* pWnd, CPoint point)
{
	if(m_pTestControl == NULL)
	{
		return;
	}

	if (m_pTestControl->IsNowTesting())
	{
		OnContextMenuEx_Testing(pWnd, point);
		return;
	}

	OnContextMenuEx_Normal(pWnd, point);
}

long CGuideBookTreeCtrl::_DrawItem(OLE_HANDLE hDC,OLE_HANDLE hItem,DWORD dwDrawStage,LRESULT* pResult)
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
				brush.DeleteObject();
			}
		}

		*pResult = CDRF_NOTIFYPOSTPAINT | CDRF_NEWFONT;
	}
	else if (dwDrawStage == CDDS_ITEMPOSTPAINT && !m_bInUpdateItemsState)	// after an item has been drawn
	{
		CGbItemBase* pTestItem = GetTestItemByTreeItem((long)hCurrItem);

		if(pTestItem != NULL)
		{
			HTREEITEM hSelItem = GetSelectedItem();

			//绘制项目名称
			BOOL bSelected = FALSE;
			if(hSelItem == hCurrItem)
				bSelected = TRUE;

			BOOL bChangeFont = FALSE;
			CFont *pOldFont = NULL;
			COLORREF clrTextSave,clrBkSave;

			if(pTestItem->GetState() == TEST_STATE_TESTING)
			{
				bChangeFont = TRUE;
				pOldFont = dc.SelectObject(&m_SSerif8Font);
			}

			//绘制checkbox
			BOOL bEnable = TRUE;

			if(m_pTestControl->IsNowTesting())
			{
				bEnable = FALSE;
			}

			CRect rectItem;
			GetItemRect(hCurrItem, &rectItem, FALSE);		// get rect for entire item
			CRect rectText;
			GetItemRect(hCurrItem, &rectText, TRUE);		// get rect for text
			rectText.right = rectItem.right;

			dc.FillSolidRect(&rectText, m_crWindow);

			long yItemCenter = rectItem.CenterPoint().y;
			BOOL bEnableAndShow = pTestItem->IsEnableAndShow();

			if (bEnableAndShow)
			{
				DrawCheckBoxRect(rectText.left + m_xSelCheckBox, yItemCenter,  pTestItem->GetSelect(), &dc, bEnable);
			}
			else
			{
				DrawCheckBoxRect(rectText.left + m_xSelCheckBox, yItemCenter, 0, &dc, FALSE);
			}

			//绘制图标，未完成
			long nImageID = Gb_GetImgIndex(pTestItem);//pTestItem->GetClassID() & 0x000000FF;

			ImageList_DrawEx(pApp->GetGbTreeImageList()->m_hImageList,nImageID,
				dc.m_hDC,rectText.left + m_xItemTypeIcon,yItemCenter -8, 16, 16,
				RGB(255,0,0), RGB(255,255,255), ILD_TRANSPARENT);

			CRect rectTitle = rectText;
			rectTitle.left = rectText.left + m_xItemTitle;

			//绘制选择的Item的底色
			if (bSelected)
			{
				clrTextSave = dc.SetTextColor(::GetSysColor(COLOR_HIGHLIGHTTEXT));
				clrBkSave = dc.SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
				dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_HIGHLIGHT)));
			}
			else
			{
				clrTextSave = dc.SetTextColor(TCC_GetItemStateColor(pTestItem, bEnableAndShow));
				dc.FillRect(rectTitle, &CBrush(::GetSysColor(COLOR_WINDOW)));
			}

			CString strName ;
			strName = pTestItem->m_strName;// pTestItem->GetName();

			if(pTestItem->GetState() == TEST_STATE_TESTING)
			{
				strName = _T(">>") + strName;
			}

			dc.DrawText(strName,rectTitle,DT_SINGLELINE /*| DT_NOPREFIX | DT_NOCLIP */| DT_VCENTER);

			dc.SetTextColor(clrTextSave);

			if (bSelected)
			{
				dc.SetBkColor(clrBkSave);
			}

			if (bChangeFont)
			{
				dc.SelectObject(pOldFont);
			}
		}
	}

	dc.Detach();
	return S_OK;	
}

long CGuideBookTreeCtrl::_OnSelChange()
{
	return 0;
}

long CGuideBookTreeCtrl::_OnLButtonDown(long xPoint,long yPoint)
{
	CPoint point(xPoint,yPoint);
	HTREEITEM hSelItem = GetSelectedItem();
	if(hSelItem == NULL || m_bInUpdateItemsState)
	{
		return FALSE;
	}

	CGbItemBase* pItem = GetTestItemByTreeItem((long)hSelItem);

	if(pItem != NULL)
	{
		CRect rectText;
		GetItemRect(hSelItem, &rectText, TRUE);
		CRect rectCheck;
		GetCheckBoxRect(rectText, rectCheck);
		BOOL bInCheck = rectCheck.PtInRect(point);

		if (bInCheck)
		{
			if( pItem->IsEnableAndShow())
			{
				//改变测试项目的Select状态
				SetTestItemSelectedState(pItem, pItem->GetSelect());
				CTCtrlCntrBaseApp* pApp = g_theTCtrlCntrApp;
				Gb_SetGbModifiedFlag(m_pTestControl->m_pGuideBook, TRUE);
		
// 				if(m_pTestControl != NULL)
// 				{
// 					m_pTestControl->m_oTCtrlMsgRcv.OnCurrItemStateChanged(pItem);
// 				}
			
				Invalidate(FALSE);
			}
		}
	}

	ShowReport(FALSE);

	return 0;
}

long CGuideBookTreeCtrl::_OnRButtonDown(long xPoint,long yPoint)
{
	return 0;
}

long CGuideBookTreeCtrl::_OnLButtonDblClk(long xPoint,long yPoint)
{
	HTREEITEM hSelItem = GetSelectedItem();
	if(hSelItem == NULL || m_bInUpdateItemsState)
	{
		return FALSE;
	}

	CGbItemBase* pItem = GetTestItemByTreeItem((long)hSelItem);
	if(pItem != NULL)
	{
		//测试报告视图，通过此函数定位
		m_pTestControl->LocateReport(pItem);

#ifndef _SMARTTEST_CORE_
		if (m_pParent != NULL)
		{
			((CAutoTestBaseTreeView *)m_pParent)->LocateVisio(pItem);
		}
#endif
	}

	return 0;
}

void CGuideBookTreeCtrl::_SetShowOnlySelTestItems(long nShow)
{
}

long CGuideBookTreeCtrl::OnItemExpandStateChanged(OLE_HANDLE hItem,long nAction)
{
	return 0;
}

void CGuideBookTreeCtrl::GetCheckBoxRect(CRect &rcText,CRect &rcCheck)
{
	CSize sizeCheck;
	GetCheckBoxSize(sizeCheck);

	//选择框的位置
	rcCheck = rcText;
	rcCheck.left += GAP_TESTITEMFLAG;
	rcCheck.right = rcCheck.left + sizeCheck.cx;
	rcCheck.top = rcText.CenterPoint().y - sizeCheck.cy / 2;
	rcCheck.bottom  =rcCheck.top + sizeCheck.cy;
}

CGbItemBase* CGuideBookTreeCtrl::GetTestItemByTreeItem(long hTreeItem)
{
	if(m_pTestControl != NULL)
	{
		return (CGbItemBase*)GetItemData((HTREEITEM)hTreeItem);
	}
	return NULL;
}

void CGuideBookTreeCtrl::SetTestItemSelectedState(CGbItemBase *pItem,long nSelect)
{
	ASSERT (m_pTestControl != NULL);
	m_pTestControl->SetTestItemSelectedState(pItem, nSelect);
/*
	if (!(pItem->GetEnable() && pItem->GetShow() ) )
	{
		return;
	}

	if (nSelect == 0)
	{
		nSelect = 1;
	}
	else
	{
		nSelect = 0;
	}

	Gb_SetTestItemSelectedState(pItem, nSelect);
*/
// 	if(nSelect == 1)
// 		pItem->SetSelect(0);
// 	else 
// 		pItem->SetSelect(1);
// 
// 	CGbItemBase* pParent = (CGbItemBase*)pItem->GetParent();
// 
// 	if(pParent != NULL)
// 	{
// 		UpdateItemSelectedState(pParent);
// 	}
// 
// 	POS pos = pItem->GetHeadPosition();
// 	CExBaseObject *pChildItem = NULL;
// 
// 	while(pos != NULL)
// 	{
// 		pChildItem = pItem->GetNext(pos);
// 
// 		if(Gb_IsItemBaseClassID(pChildItem->GetClassID()))
// 		{
// 			SetTestItemSelectedState((CGbItemBase*)pChildItem,nSelect);
// 		}
// 	}
// 
// 	Gb_UpdateGbItemParentTestState(pItem);  //更新测试状态
}

//更新选择树形控件时的显示效果
//nSelect = 0 表示未选中,nSelect = 1表示选中,nSelect = 2表示子节点中既包含选中也包含未选中的测试项目(中间状态)
void CGuideBookTreeCtrl::UpdateItemSelectedState(CGbItemBase* pItem)
{
	Gb_UpdateItemSelectedState(pItem);
// 	if (pItem->GetClassID() == GBCLASSID_GUIDEBOOK)
// 	{
// 		return;
// 	}
// 
// 	ASSERT(pItem != NULL);
// 	long nVal[3] = {0,0,0};
// 
// 	POS pos = pItem->GetHeadPosition();
// 	CGbItemBase* pChildItem = NULL;
// 	long nSelect = 0;
// 
// 	while(pos != NULL)
// 	{
// 		pChildItem = (CGbItemBase*)pItem->GetNext(pos);
// 
// 		if(Gb_IsItemBaseClassID(pChildItem->GetClassID()))
// 		{
// 			nSelect = pChildItem->GetSelect();
// 
// 			if( 0 <= nSelect && nSelect <= 2)
// 				nVal[nSelect] = 1;
// 			else
// 				nVal[2] = 1;
// 		}
// 	}
// 
// 	nSelect = 0;
// 
// 	if (nVal[0] == 1 && nVal[1]==0 && nVal[2] == 0)
// 		nSelect = 0;
// 	else if (nVal[0] == 0 && nVal[1]==1 && nVal[2] == 0)
// 		nSelect = 1;
// 	else
// 		nSelect = 2;
// 
// 	long n1 = pItem->GetSelect();
// 
// 	if (nSelect == 0 || nSelect == 1)
// 	{
// 		if (nSelect != pItem->GetSelect())
// 		{
// 			pItem->SetSelect(nSelect);
// 			CGbItemBase* pParent = (CGbItemBase*)pItem->GetParent();
// 
// 			if (pParent != NULL)
// 			{
// 				UpdateItemSelectedState(pParent);
// 			}
// 		}
// 	}
// 	else
// 	{
// 		pItem->SetSelect(nSelect);
// 		CGbItemBase* pParent = (CGbItemBase*)pItem->GetParent();
// 
// 		if (pParent  != NULL)
// 		{
// 			UpdateItemSelectedState(pParent);
// 		}
// 	}
// 
// 	Gb_UpdateGbItemParentTestState(pItem);  //更新测试状态
}

void CGuideBookTreeCtrl::InsertGbItemToTreeCtrl(CGbItemBase* pItem,HTREEITEM htiParent)
{
	ASSERT(m_pTestControl != NULL);

	DWORD dwItemData = 0;
	HTREEITEM hTreeItem = NULL;

	if(Gb_IsItemBaseClassID(pItem->GetClassID()))
	{
		//hTreeItem = InsertItem(pItem->m_strName,0,0,htiParent);
		hTreeItem = InsertItem(_T(""),0,0,htiParent);
		pItem->m_dwItemData = (DWORD)hTreeItem;
		SetItemData(hTreeItem, (DWORD)pItem);
		InsertGbItemChildrenToTreeCtrl(pItem,hTreeItem);
		//展开树形节点
		if(pItem->GetExpandState())
		{
			Expand(hTreeItem,TVE_EXPAND);
		}
	}
}

void CGuideBookTreeCtrl::InsertGbItemChildrenToTreeCtrl(CGbItemBase* pItem,HTREEITEM htiParent)
{
	ASSERT(pItem != NULL);
	CGbItemBase* pObj = NULL;
	POS pos = pItem->GetHeadPosition();

	while(pos != NULL)
	{
		pObj = (CGbItemBase*)pItem->GetNext(pos);
		InsertGbItemToTreeCtrl(pObj,htiParent);
	}
}

//CGuideBookTreeCtrl 消息响应
void CGuideBookTreeCtrl::OnCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	try
	{
		NMTVCUSTOMDRAW* pCD = reinterpret_cast<NMTVCUSTOMDRAW*>(pNMHDR);
		HTREEITEM hItem = reinterpret_cast<HTREEITEM> (pCD->nmcd.dwItemSpec);
		*pResult = CDRF_DODEFAULT;

		LPNMHDR pNmhdr = (LPNMHDR)pNMHDR;          
		LPNMTVCUSTOMDRAW pCustomDraw = (LPNMTVCUSTOMDRAW)pNMHDR;

		if(m_pTestControl == NULL)
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
	catch (...)
	{
		AfxMessageBox(_T("GuideBookTreeCtrl::OnCustomdraw Error"));
	}


}

void CGuideBookTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point,&uFlags);
	HTREEITEM hItemSelected = GetSelectedItem();

	if(hItem != hItemSelected)
	{
		this->SelectItem(hItem);
	}

	_OnLButtonDown(point.x,point.y);
	CTreeCtrl::OnLButtonDown(nFlags, point);
}

void CGuideBookTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	SetFocus();
	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point, &uFlags);
	HTREEITEM hItemSelected = GetSelectedItem();

	if (hItem != hItemSelected)
	{
		this->SelectItem(hItem);
	}

	if (hItem == NULL)
	{
		return;
	}

	m_pCurrSelTestItem = GetTestItemByTreeItem((long)hItem);
	TRACE(L"%s\r\n", m_pCurrSelTestItem->m_strID);

	CTreeCtrl::OnRButtonDown(nFlags, point);

	ClientToScreen(&point);
	OnContextMenuEx(this, point);
}


void CGuideBookTreeCtrl::SelectTopItem(CGbItemBase* pCurrItem)
{
	long nVisibleCount = 0;
	long nCurrItemIndex = 0;

	SelectItem((HTREEITEM)pCurrItem->m_dwItemData);
	GetVisibleItemCount(nVisibleCount, nCurrItemIndex, pCurrItem, m_pTestControl->m_pGuideBook);
	nCurrItemIndex -= 7;

	if (nCurrItemIndex <= 1)
	{
		nCurrItemIndex = 0;
	}

	//SendMessage(WM_VSCROLL,MAKELONG(SB_THUMBTRACK,nCurrItemIndex),0); 
}

long CGuideBookTreeCtrl::GetVisibleItemCount(long &nVisibleCount, long &nCurrItemIndex, CGbItemBase *pCurrItem, CGbItemBase *pParent)
{
	CGbItemBase *pTestItem = NULL;

	POS pos = pParent->GetHeadPosition();

	while (pos != NULL)
	{
		pTestItem = (CGbItemBase*)pParent->GetNext(pos);

		if(pTestItem->m_nShow == 1)
		{
			nVisibleCount ++;
		}

		if (pTestItem == pCurrItem)
		{
			nCurrItemIndex = nVisibleCount;
		}

		//父对象展开
		if(!Gb_IsItemBaseClassID(pTestItem->GetClassID()) && pTestItem->m_nExpandState == 1)
		{
			GetVisibleItemCount(nVisibleCount,nCurrItemIndex,pCurrItem,pTestItem);
		}
	}

	return 0;
}

void CGuideBookTreeCtrl::GB_InsertItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	if (pParentItem == NULL || pSubItem == NULL)
	{
		return;
	}

	Invalidate(FALSE);
	HTREEITEM hParentTreeItem = (HTREEITEM)pParentItem->m_dwItemData;
	DWORD dwItemData = 0;
	HTREEITEM hTreeItem = InsertItem(_T(""),0,0,hParentTreeItem);
	pSubItem->m_dwItemData = (DWORD)hTreeItem;
	SetItemData(hTreeItem, (DWORD)pSubItem);
	Expand(hParentTreeItem, TVE_EXPAND);
}

void CGuideBookTreeCtrl::GB_DeleteItem(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	if (pParentItem == NULL || pSubItem == NULL)
	{
		return;
	}

	HTREEITEM hParentTreeItem = (HTREEITEM)pParentItem->m_dwItemData;
	HTREEITEM hSubTreeItem = (HTREEITEM)pSubItem->m_dwItemData;
	DeleteItem(hSubTreeItem);
	Expand(hParentTreeItem, TVE_EXPAND);
	pSubItem->m_dwItemData = 0;
}

void CGuideBookTreeCtrl::GB_InsertItemEx(CGbItemBase *pParentItem, CGbItemBase *pSubItem)
{
	GB_InsertItem(pParentItem, pSubItem);

	POS pos = pSubItem->GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = pSubItem->GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == GBCLASSID_ITEMS
			|| Gb_IsGbItemClassID(nClassID))
		{
			CGbItemBase *pItemBase = (CGbItemBase *)pObj;
			GB_InsertItemEx(pSubItem, pItemBase);
		}
	}
}

void CGuideBookTreeCtrl::OnTestPoint()
{
	//if (!m_pTestControl->m_pGuideBook->IsAuthority())
	//2021-7-31  lijunqing
	if (! Encrypt_CanUseGuideBook(m_pTestControl->m_pGuideBook))
	{
		return;
	}

	//2023-5-25  shaolei
	if (! Encrypt_IsEncrypt_CanUseAutoTest())
	{
		return;
	}

	m_pTestControl->m_pItemContainer->SetTestMode(TestOptrMode_TestSingle);

	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
	pApp->SetTestMode_Report();

	m_pTestControl->TestSingle(m_pCurrSelTestItem);
}

void CGuideBookTreeCtrl::OnTestAllInlegibleItems()
{
	//if (!m_pTestControl->m_pGuideBook->IsAuthority())
	//2021-7-31  lijunqing
	if (! Encrypt_CanUseGuideBook(m_pTestControl->m_pGuideBook))
	{
		return;
	}

	//2023-5-25  shaolei
	if (! Encrypt_IsEncrypt_CanUseAutoTest())
	{
		return;
	}

	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
	pApp->SetTestMode_Report();

	m_pTestControl->OnTestAllInlegibleItems();
}

void CGuideBookTreeCtrl::OnTestPoint_MdOne()
{
	//if (!m_pTestControl->m_pGuideBook->IsAuthority())
	//2021-7-31  lijunqing
	if (! Encrypt_CanUseGuideBook(m_pTestControl->m_pGuideBook))
	{
		return;
	}

	//2023-5-25  shaolei
	if (! Encrypt_IsEncrypt_CanUseAutoTest())
	{
		return;
	}

	CTCtrlCntrBaseApp *pApp = g_theTCtrlCntrApp;
	pApp->SetTestMode_Report();

	m_pTestControl->TestSingle_MdOne(m_pCurrSelTestItem);
}

void CGuideBookTreeCtrl::OnUpdateGbItem()
{
	Gb_GetItemPara(XMODULE_ID_GuideBookDev, m_pCurrSelTestItem, m_pTestControl->m_pGuideBook->m_strGbXmlFile, TRUE);
}

void CGuideBookTreeCtrl::OnUpdateGbItemToGb()
{
	Gb_SetItemPara(XMODULE_ID_GuideBookDev, m_pCurrSelTestItem, m_pTestControl->m_pGuideBook->m_strGbXmlFile, TRUE);
}

void CGuideBookTreeCtrl::OnViewDeviceSets()
{
	//AfxGetApp()->PostThreadMessage(WM_VIEW_DEVICESETS, (WPARAM)m_pCurrSelTestItem, (LPARAM)m_pCurrSelTestItem);
	//m_pTestControl->TestSingle(m_pCurrSelTestItem);
	CViewSetsDialog dlg;

	CGbItemBase *pGbItem = gbui_GetActiveTestItem(m_pCurrSelTestItem);
	dlg.m_pDevice = pGbItem;

	dlg.DoModal();
}

void CGuideBookTreeCtrl::OnExpandAllChildren()
{
	HTREEITEM hSel = GetSelectedItem();
	UI_ExpandAllChildren(this, hSel);
}

void CGuideBookTreeCtrl::OnEditItemPara()
{
	m_pTestControl->EditItemPara(m_pCurrSelTestItem);
}

void CGuideBookTreeCtrl::OnTestBelow()
{
	//if (!m_pTestControl->m_pGuideBook->IsAuthority())
	//2021-7-31  lijunqing
	if (! Encrypt_CanUseGuideBook(m_pTestControl->m_pGuideBook))
	{
		return;
	}

	//2023-5-25  shaolei
	if (! Encrypt_IsEncrypt_CanUseAutoTest())
	{
		return;
	}

	m_pTestControl->m_pItemContainer->SetTestMode(TestOptrMode_TestFrom);

	m_pTestControl->TestFrom(m_pCurrSelTestItem);

	//发送消息
	AfxGetApp()->PostThreadMessage(WM_TESTBELOW, 0, 0);
}

void CGuideBookTreeCtrl::ShowReport(BOOL bCreate)
{
	HTREEITEM hItem = GetSelectedItem();

	if (hItem != NULL)
	{
		CExBaseObject *pItem = (CExBaseObject*)GetItemData(hItem);
		m_pTestControl->ShowItemReport(pItem, bCreate);
	}
}

void CGuideBookTreeCtrl::UpdateTestItem(CExBaseObject *pNewItem, CExBaseObject *pOldItem)
{
	HTREEITEM hParent = (HTREEITEM)pOldItem->m_dwItemData;
	SetItemData(hParent, (DWORD)pNewItem);
	pNewItem->m_dwItemData = (DWORD)hParent;
	m_pCurrSelTestItem = (CGbItemBase*)pNewItem;

	if (ItemHasChildren(hParent))
	{//删除所有子节点
		HTREEITEM hChildItem = GetChildItem(hParent);

		while (hChildItem != NULL)
		{
			DeleteItem(hChildItem);
			hChildItem = GetChildItem(hParent);
		}
	}

	InsertGbItemChildrenToTreeCtrl((CGbItemBase*)pNewItem, hParent);
}

void CGuideBookTreeCtrl::OnShowReport()
{
	if (m_pTestControl == NULL)
	{
		return;
	}

	ShowReport(TRUE);
}

void CGuideBookTreeCtrl::OnQueryRecord()
{
	if (m_pTestControl == NULL)
	{
		return;
	}

	HTREEITEM hItem = GetSelectedItem();

	if (hItem != NULL)
	{
		CGbItemBase *pItem = (CGbItemBase*)GetItemData(hItem);
		m_pTestControl->QueryRecord(pItem);
	}

}

void CGuideBookTreeCtrl::OnShowCharDraw()
{
	if (m_pTestControl == NULL)
	{
		return;
	}

	HTREEITEM hItem = GetSelectedItem();

	if (hItem != NULL)
	{
		CExBaseObject *pItem = (CExBaseObject*)GetItemData(hItem);
		m_pTestControl->ShowCharDraw(pItem);
	}
}

void CGuideBookTreeCtrl::OnShowRecord()
{
	if (m_pTestControl == NULL)
	{
		return;
	}

	HTREEITEM hItem = GetSelectedItem();

	if (hItem != NULL)
	{
		CExBaseObject *pItem = (CExBaseObject*)GetItemData(hItem);
		m_pTestControl->ShowItemRecord(pItem);
	}
}

void CGuideBookTreeCtrl::OnContextMenu(CWnd* pWnd, CPoint point)
{
}

//void CGuideBookTreeCtrl::CreateGuideBookTreeImageList(UINT nBitmapID,int cx ,int nGrow,COLORREF crMask)
//{
//	m_GuideBookTreeImageList.DeleteImageList();
//	m_GuideBookTreeImageList.Create (nBitmapID, cx, nGrow, crMask);
//
//	LOGFONT lf = InitLogFont();
//	lf.lfHeight = 14;
//	lf.lfWeight = 400;
//
//#ifdef UNICODE
//	lstrcpy(lf.lfFaceName,L"宋体");
//#else
//	strcpy(lf.lfFaceName,"宋体");	
//#endif // UNICODE
//
//	if (m_pFontTestItem == NULL)
//	{
//		m_pFontTestItem =  new CFont;
//		m_pFontTestItem->CreateFontIndirect(&lf);	
//	}
//}

int CGuideBookTreeCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码

	return 0;
}

void CGuideBookTreeCtrl::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	UINT uFlags = 0;
	HTREEITEM hItem = HitTest(point,&uFlags);
	HTREEITEM hItemSelected = GetSelectedItem();

	if(hItem != hItemSelected)
	{
		this->SelectItem(hItem);
	}

	CTreeCtrl::OnLButtonDblClk(nFlags, point);

	_OnLButtonDblClk(point.x,point.y);

}

void CGuideBookTreeCtrl::OnTvnItemexpanded(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	// TODO: 在此添加控件通知处理程序代码
	if( !m_bInTestItemInitState)
	{
		HTREEITEM hCurTreeItem = pNMTreeView->itemNew.hItem;
		UINT nAction  = pNMTreeView->action;

		CGbItemBase* pItem = (CGbItemBase*)GetItemData(hCurTreeItem);
		if(nAction == TVE_EXPAND)
		{
			pItem->SetExpandState(1);
		}
		else if(nAction == TVE_COLLAPSE)
		{
			pItem->SetExpandState(0);
		}

		Gb_SetGbModifiedFlag(m_pTestControl->m_pGuideBook, TRUE);
		Invalidate(FALSE);
	}

	*pResult = 0;
}

void CGuideBookTreeCtrl::CloseTestProject()
{
	DeleteAllItems();
	m_pTestControl = NULL;

}void CGuideBookTreeCtrl::OnTvnItemChanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMTVITEMCHANGE *pNMTVItemChange = reinterpret_cast<NMTVITEMCHANGE*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}

LRESULT CGuideBookTreeCtrl::OnInsertItems(WPARAM wParam, LPARAM lParam)
{
	CGbItemBase *pItemParent = (CGbItemBase *)wParam;

	POS pos = g_oListItemsInsertToTree.GetHeadPosition();

	while (pos != NULL)
	{
		CItems *pNewItems = (CItems *)g_oListItemsInsertToTree.GetNext(pos);

#ifndef _PSX_IDE_QT_
		GB_InsertItemEx(pItemParent, pNewItems);
#endif
	}

	g_oListItemsInsertToTree.RemoveAll();

	return 0;
}