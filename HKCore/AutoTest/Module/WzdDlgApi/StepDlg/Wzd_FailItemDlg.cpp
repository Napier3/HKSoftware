// Wzd_FailItemDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_FailItemDlg.h"
#include "Wzd_FailItemAdviseDlg.h"
#include "WzdMainDlg.h"
#include "HeaderCtrlEx.h"

// CWzd_FailItemDlg 对话框

IMPLEMENT_DYNAMIC(CWzd_FailItemDlg, CDialog)

CWzd_FailItemDlg::CWzd_FailItemDlg(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzd_FailItemDlg::IDD, pParent)
{

}

CWzd_FailItemDlg::~CWzd_FailItemDlg()
{
}

void CWzd_FailItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_FAIL_ITEM_LIST, m_ctrlFailItemList);
	DDX_Control(pDX, IDC_STATIC1, m_Static1);
}

void CWzd_FailItemDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	//具体移动
	XUI_AddWnd(&m_ctrlFailItemList, 0, 0, 1, 1);
	XUI_AddWnd(&m_Static1, 0, 0, 1, 0);

	CXUIAdjItem_Area::XUI_OnSize();
}
BEGIN_MESSAGE_MAP(CWzd_FailItemDlg, CDialog)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_RCLICK, IDC_FAIL_ITEM_LIST, &CWzd_FailItemDlg::OnNMRClickFailItemList)
	ON_COMMAND(ID_FAIL_ITEM_ADVISE, &CWzd_FailItemDlg::OnFailItemAdvise)
	ON_COMMAND(ID_FIND_FAIL_ITEM, &CWzd_FailItemDlg::OnFindFailItem)
	//ON_WM_PAINT()
END_MESSAGE_MAP()


// CWzd_FailItemDlg 消息处理程序
void CWzd_FailItemDlg::InitFailItemInfo()
{
	//XUI_InitAdjust();
	m_ImageList.Create(7,24,ILC_MASK|ILC_COLOR32,4,4);
	m_ImageList.SetBkColor(CLR_NONE);
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/test/";
	CString strImg1 = strImg+ "fail.ico";
	HICON IcImage1 = (HICON)LoadImage(NULL, strImg1, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	m_ImageList.Add(IcImage1);


	m_ctrlFailItemList.SetImageList(&m_ImageList,LVSIL_SMALL);
	m_ctrlFailItemList.SetExtendedStyle(m_ctrlFailItemList.GetExtendedStyle() | LVS_EX_FULLROWSELECT /*|LVS_EX_GRIDLINES*/);
	m_ctrlFailItemList.SetIsShowLine(true);
	CHeaderCtrlEx* pHeader = new CHeaderCtrlEx();
	pHeader->SubclassWindow(m_ctrlFailItemList.GetHeaderCtrl()->GetSafeHwnd());
	pHeader->ModifyStyle(WS_CAPTION,0,SWP_DRAWFRAME);
	pHeader->SetHeaderCtrlBKColor(RGB(242,248,248));

	CRect rect;
	m_ctrlFailItemList.GetClientRect(&rect);
	m_ctrlFailItemList.InsertColumn(0, _T("序号"), LVCFMT_LEFT, 70);
	m_ctrlFailItemList.InsertColumn(1, _T("不合格项目"), LVCFMT_LEFT, rect.Width()-70);

//	m_Edit.SetWindowText("");
//	m_Edit.SetReadOnly(TRUE);

	/*m_ctrlFailItemList.InsertItem(0,"1",-1);
	m_ctrlFailItemList.SetItemText(0,1,"shdkajsdhajks");

	m_ctrlFailItemList.InsertItem(1,"2",-1);
	m_ctrlFailItemList.SetItemText(1,1,"cccccccc");*/
}

void CWzd_FailItemDlg::UpdateFailItemInfo(CGbItemBase* pTestItem)
{
	if(pTestItem == NULL)
	{
		return;
	}

	if(FindRow(pTestItem) > 0)
	{
		return;
	}

	int nRowCount = m_ctrlFailItemList.GetItemCount();
	CString strXH = "";
	strXH.Format(_T("%d"),nRowCount+1);
	m_ctrlFailItemList.InsertItem(nRowCount,strXH,-1);
	m_ctrlFailItemList.SetItemText(nRowCount,1,pTestItem->m_strName);
	m_ctrlFailItemList.SetItemData(nRowCount,(DWORD)pTestItem);
}

void CWzd_FailItemDlg::DeleteFailItemItem(CGbItemBase* pTestItem)
{
	if(pTestItem == NULL)
	{
		return;
	}
	int nCount = m_ctrlFailItemList.GetItemCount();
	for(int i = 0;i < nCount;i++)
	{
		CGbItemBase* pItem = NULL;
		pItem = (CGbItemBase*)m_ctrlFailItemList.GetItemData(i);
		if(pItem == NULL)
		{
			return;
		}
		if(pItem == pTestItem)
		{
			m_ctrlFailItemList.DeleteItem(i);
			return;
		}
	}
}

int CWzd_FailItemDlg::FindRow(CGbItemBase* pTestItem)
{
	if(pTestItem == NULL)
	{
		return -1;
	}
	int nRow = -1;
	int nCount = m_ctrlFailItemList.GetItemCount();
	for(int i = 0;i < nCount;i++)
	{
		CGbItemBase* pItem = NULL;
		pItem = (CGbItemBase*)m_ctrlFailItemList.GetItemData(i);
		if(pItem == NULL)
		{
			return -1;
		}
		if(pItem == pTestItem)
		{
			nRow = i;
			break;
		}
	}
	return nRow;
}

////////////////////////
void CWzd_FailItemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
	if(m_ctrlFailItemList.GetSafeHwnd() == NULL)
	{
		return;
	}
	CRect rect;
	m_ctrlFailItemList.GetClientRect(&rect);
	m_ctrlFailItemList.SetColumnWidth(1,rect.Width() -70);
}

HBRUSH CWzd_FailItemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWzdDlgBase::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
		HBRUSH aBrush;
		aBrush = CreateSolidBrush(RGB(242,248,248));
		hbr = aBrush;
		break;
	case CTLCOLOR_STATIC:
		if(pWnd->GetDlgCtrlID() == IDC_STATIC1)
		{
			pDC->SetTextColor(RGB(0,0,0));
			pDC->SetBkColor(RGB(255,255,255));
			HBRUSH b=CreateSolidBrush(RGB(255,255,255));
			return b;
		}
		else
		{
			pDC->SetBkMode(TRANSPARENT);   
			pDC->SetTextColor(RGB(0,0,0));   
			return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
		}		
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CWzd_FailItemDlg::OnNMRClickFailItemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}
	CPoint ptCurSel(0,0);
	GetCursorPos(&ptCurSel);
	//转换为当前控件坐标系的坐标
	m_ctrlFailItemList.ScreenToClient(&ptCurSel);
	LVHITTESTINFO HitTestInfo;
	HitTestInfo.pt = ptCurSel;   
	//判断坐标命中第几项
	int nItem = m_ctrlFailItemList.HitTest(&HitTestInfo);
  
   //如果有选中项
	if (nItem != -1)
	{
		CMenu menu;
		menu.LoadMenu(IDR_TEST_ITEM_MENU);
		CPoint point;
		GetCursorPos(&point);

		CMenu* pSubMenu = menu.GetSubMenu(1);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	}
	*pResult = 0;
}

void CWzd_FailItemDlg::OnFailItemAdvise()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_ctrlFailItemList.GetFirstSelectedItemPosition();
	int nItem = -1;
	nItem = m_ctrlFailItemList.GetNextSelectedItem(pos);
	if(nItem < 0)
	{
		return;
	}

	CItems* pTestItem = NULL;
	pTestItem = (CItems*)m_ctrlFailItemList.GetItemData(nItem);
	if(pTestItem == NULL)
	{
		return;
	}
	//获取当前测试失败项目的建议
	CString stAdvise = "";

	CWzd_FailItemAdviseDlg dlg;
	dlg.InitFailItemAdvise(stAdvise);
	dlg.DoModal();
}

void CWzd_FailItemDlg::OnFindFailItem()
{
	// TODO: 在此添加命令处理程序代码
	POSITION pos = m_ctrlFailItemList.GetFirstSelectedItemPosition();
	int nItem = -1;
	nItem = m_ctrlFailItemList.GetNextSelectedItem(pos);
	if(nItem < 0)
	{
		return;
	}

	CItems* pTestItem = NULL;
	pTestItem = (CItems*)m_ctrlFailItemList.GetItemData(nItem);
	if(pTestItem == NULL)
	{
		return;
	}

	CItems* pStep = NULL;
	pStep = (CItems*)pTestItem->GetParent();
	if(pStep == NULL)
	{
		return;
	}
	::PostMessage(g_pWzdMainDlg->m_pAutoTest->GetSafeHwnd(),WM_FAIL_ITEM_FING_CHANG,reinterpret_cast<WPARAM>((void*)(pStep)),reinterpret_cast<LPARAM>((void*)(pTestItem)));
}

//void CWzd_FailItemDlg::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//	// TODO: 在此处添加消息处理程序代码
//	// 不为绘图消息调用 CWzdDlgBase::OnPaint()
//}

