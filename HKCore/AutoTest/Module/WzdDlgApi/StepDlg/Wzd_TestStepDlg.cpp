// Wzd_TestStepDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_TestStepDlg.h"
#include "WzdMainDlg.h"

// CWzd_TestStepDlg 对话框

IMPLEMENT_DYNAMIC(CWzd_TestStepDlg, CDialog)

CWzd_TestStepDlg::CWzd_TestStepDlg(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzd_TestStepDlg::IDD, pParent)
{

}

CWzd_TestStepDlg::~CWzd_TestStepDlg()
{
}

void CWzd_TestStepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_STEP_LIST, m_ctrlCheckStepList);
}


BEGIN_MESSAGE_MAP(CWzd_TestStepDlg, CDialog)	
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_CHECK_STEP_LIST, &CWzd_TestStepDlg::OnNMClickCheckStepList)
	ON_WM_CREATE()
//	ON_NOTIFY(LVN_GETDISPINFO, IDC_CHECK_STEP_LIST, &CWzd_TestStepDlg::OnLvnGetdispinfoCheckStepList)
END_MESSAGE_MAP()


// CWzd_TestStepDlg 消息处理程序

void CWzd_TestStepDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	//具体移动
	XUI_AddWnd(&m_ctrlCheckStepList, 0, 0, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

int CWzd_TestStepDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWzdDlgBase::OnCreate(lpCreateStruct) == -1)
		return -1;

/*	m_imgList.Create(16,16,ILC_COLOR32|ILC_MASK,2,0);
	m_imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_PLUS));
	m_imgList.Add(AfxGetApp()->LoadIcon(IDI_ICON_MINUS));
	m_tree.SetImageList(&m_imgList,TVSIL_NORMAL);
	m_tree.InsertItem(_T("root"));*/

	// TODO:  在此添加您专用的创建代码
	m_ImageList.Create(24,24,ILC_MASK|ILC_COLOR32,4,4);
	m_ImageList.SetBkColor(CLR_NONE);
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/test/";
	//CBitmap bmp;
	//bmp.LoadBitmap("D:/Program Files/EPOTO_YuYin/e-Report/Resource/Audio/ttt.png");
	CString strImg1 = strImg+ "fail.ico";
	HICON IcImage1 = (HICON)LoadImage(NULL, strImg1, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	m_ImageList.Add(IcImage1);

	CString strImg2 = strImg+ "success.ico";
	HICON IcImage2 = (HICON)LoadImage(NULL,strImg2,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	m_ImageList.Add(IcImage2);

	/*CString strImg2 = strImg+ "success.bmp";
	HBITMAP IcImage2 = (HBITMAP)LoadImage(NULL,strImg2,IMAGE_BITMAP,24,24,LR_LOADFROMFILE);
	CBitmap *pBmp = NULL;
	pBmp = CBitmap::FromHandle( IcImage2);
	//m_ImageList.Add(pBmp,RGB(0,0,0));
	//m_ImageList.Add(pBmp,RGB(255,255,255));
	m_ImageList.Add(pBmp,RGB(242,248,248));*/

	CString strImg3 = strImg+ "testing.ico";
	HICON IcImage3 = (HICON)LoadImage(NULL,strImg3,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	m_ImageList.Add(IcImage3);

	return 0;
}

HBRUSH CWzd_TestStepDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
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
		pDC->SetBkMode(TRANSPARENT);   
		pDC->SetTextColor(RGB(0,0,0));   
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH); 
	/*case CTLCOLOR_SCROLLBAR:
		HBRUSH aBrush2;
		aBrush2 = CreateSolidBrush(RGB(242,248,248));
		hbr = aBrush2;
		break;*/
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CWzd_TestStepDlg::InitCheckStepInfo(CItems& stepItems)
{
	m_ctrlCheckStepList.SetImageList(&m_ImageList,LVSIL_SMALL);
	m_ctrlCheckStepList.SetExtendedStyle(m_ctrlCheckStepList.GetExtendedStyle() | LVS_EX_FULLROWSELECT /*| LVS_SHOWSELALWAYS | LVS_SINGLESEL*/ | 
									LVS_EX_CHECKBOXES |LVS_EX_SUBITEMIMAGES |LVS_NOCOLUMNHEADER);
	
	m_ctrlCheckStepList.InsertColumn(0, _T("ttt"), LVCFMT_LEFT, 400);
	m_ctrlCheckStepList.InsertColumn(1, _T("tt"), LVCFMT_CENTER, 50);
	if(stepItems.GetCount() <= 0)
	{
		return;
	}
//	CItems* pItems = stepItems.FindFirstRootTypeItem();
	POS posHead = stepItems.GetHeadPosition();
	int nPos = 0;
	while(posHead != NULL)
	{
		CItems* pStep = (CItems*)stepItems.GetNext(posHead);
		m_ctrlCheckStepList.InsertItem(nPos,pStep->m_strName,-1);
		//m_ctrlCheckStepList.InsertItem (LVIF_IMAGE | LVIF_TEXT,nPos, pStep->m_strName, 0, 0, I_IMAGECALLBACK, 0);
		m_ctrlCheckStepList.SetItemData(nPos,(DWORD)pStep);
		m_ctrlCheckStepList.SetCheck(nPos, pStep->m_nSelect);
		//m_ctrlCheckStepList.SetItem(nPos,1,LVIF_IMAGE,NULL,1,0,0,0);
		if(pStep->GetState() == TEST_STATE_TESTING) //测试中
		{
			m_ctrlCheckStepList.SetItem(nPos,1,LVIF_IMAGE,NULL,2,0,0,0);
			m_ctrlCheckStepList.SetListSelectRow(nPos,m_ctrlCheckStepList.GetListSelectRow());
		}
		else if(pStep->GetState() == TEST_STATE_ELIGIBLE) //合格
		{
			m_ctrlCheckStepList.SetItem(nPos,1,LVIF_IMAGE,NULL,1,0,0,0);
		}
		else if(pStep->GetState() == TEST_STATE_INLEGIBLE) //不合格
		{
			m_ctrlCheckStepList.SetItem(nPos,1,LVIF_IMAGE,NULL,0,0,0,0);
		}
		else
		{
			m_ctrlCheckStepList.SetItem(nPos,1,LVIF_IMAGE,NULL,-1,0,0,0);
		}
		//m_ctrlCheckStepList.SetItem(nPos,1,I_IMAGECALLBACK,NULL,1,0,0,0);
		nPos++;
	}

	CString strText = _T("初始化作业指导书");
	g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText);

	//默认选中第一个
	m_ctrlCheckStepList.SetListSelectRow(0,-1);
	//m_ctrlCheckStepList.SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);
	//m_ctrlCheckStepList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);
	m_ctrlCheckStepList.UpdateData(FALSE);
}

void CWzd_TestStepDlg::UpdateCheckStepState(CGbItemBase* pStep)
{
	if(pStep == NULL)
	{
		return;
	}
	int nCount = m_ctrlCheckStepList.GetItemCount();
	for(int i = 0;i < nCount;i++)
	{
		CItems* pItem = NULL;
		pItem = (CItems*)m_ctrlCheckStepList.GetItemData(i);
		if(pItem == NULL)
		{
			return;
		}
		if(pItem == pStep)
		{
			if(pStep->GetState() == TEST_STATE_TESTING) //测试中 走不到
			{
				m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,2,0,0,0);
				m_ctrlCheckStepList.SetListSelectRow(i,m_ctrlCheckStepList.GetListSelectRow());
				// g_pWzdMainDlg->m_pAutoTest->m_dlgCheckItem.UpdateCheckItemState(pItem);
			}
			else if(pStep->GetState() == TEST_STATE_ELIGIBLE) //合格
			{
				m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,1,0,0,0);
				m_ctrlCheckStepList.SetListRowState(i);
			}
			else if(pStep->GetState() == TEST_STATE_INLEGIBLE) //不合格
			{
				m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,0,0,0,0);
				m_ctrlCheckStepList.SetListRowState(i);
			}
			else
			{
				m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,-1,0,0,0);
			}
			break;
		}
	}
	m_ctrlCheckStepList.UpdateData(FALSE);
	
}

CGbItemBase* CWzd_TestStepDlg::UpdateCheckStepState2()
{
	int nCount = m_ctrlCheckStepList.GetItemCount();
	//CItems* pItem = NULL;
	CItems* pTestingItem = NULL;
	for(int i = 0;i < nCount;i++)
	{
		CItems* pItem = NULL;
		pItem = (CItems*)m_ctrlCheckStepList.GetItemData(i);
		if(pItem == NULL)
		{
			return NULL;
		}
		if(pItem->GetState() == TEST_STATE_TESTING) //测试中
		{
			m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,2,0,0,0);
			m_ctrlCheckStepList.SetListSelectRow(i,m_ctrlCheckStepList.GetListSelectRow());
			//m_ctrlCheckStepList.UpdateData(FALSE);
			pTestingItem = pItem;
			//m_ctrlCheckStepList.UpdateData(FALSE);
			//g_pWzdMainDlg->m_pAutoTest->m_dlgCheckItem.UpdateCheckItemState(pItem);
			//return pItem;
			//break;
		}
		else if(pItem->GetState() == TEST_STATE_ELIGIBLE) //合格
		{
			m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,1,0,0,0);
			m_ctrlCheckStepList.SetListRowState(i);
		}
		else if(pItem->GetState() == TEST_STATE_INLEGIBLE) //不合格
		{
			m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,0,0,0,0);
			m_ctrlCheckStepList.SetListRowState(i);
		}
		else
		{
			m_ctrlCheckStepList.SetItem(i,1,LVIF_IMAGE,NULL,-1,0,0,0);
		}
		
	}
	//m_ctrlCheckStepList.UpdateData(FALSE);
	return pTestingItem;
}

///////////////////////
void CWzd_TestStepDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}
void CWzd_TestStepDlg::OnNMClickCheckStepList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}

	CItems* pStep = NULL;
	pStep = (CItems*)m_ctrlCheckStepList.GetItemData(pNMItemActivate->iItem);
	if(pStep == NULL)
	{
		return;
	}

	//m_ctrlCheckStepList.SetItem(pNMItemActivate->iItem,1,LVIF_IMAGE,NULL,1,0,0,0);
	//m_ctrlCheckStepList.UpdateData(FALSE);
	
	::PostMessage(g_pWzdMainDlg->m_pAutoTest->GetSafeHwnd(),WM_TEST_STEP_CHANG,reinterpret_cast<WPARAM>((void*)(pStep)),0);
	//yzj 2024.2.26 checkbox改变时向自动测试发送改变消息
	LVHITTESTINFO lvinfo;  
	lvinfo.pt = pNMItemActivate->ptAction;
	int nItem = m_ctrlCheckStepList.HitTest(&lvinfo);  
	if(lvinfo.flags == LVHT_ONITEMSTATEICON)
	{
		CString strIDPath = pStep->m_strID;
		CExBaseList* pParent = (CExBaseList*)pStep->GetParent();
		while (pParent)
		{
			strIDPath = pParent->m_strID + "$" + strIDPath;

			if(pParent->GetClassID() == GBCLASSID_DEVICE)
			{	
				break;
			}

			pParent = (CExBaseList*)pParent->GetParent();
		}

		long nCheck = m_ctrlCheckStepList.GetCheck(pNMItemActivate->iItem);
		pStep->m_nSelect = !nCheck;
		g_pWzdMainDlg->SetItemState(strIDPath, pStep->m_nSelect);
	}
	*pResult = 0;
}

