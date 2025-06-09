// Wzd_CheckItemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_CheckItemDlg.h"
#include "WzdMainDlg.h"
#include "Wzd_DetailInfoDlg.h"

// CWzd_CheckItemDlg �Ի���

IMPLEMENT_DYNAMIC(CWzd_CheckItemDlg, CDialog)

CWzd_CheckItemDlg::CWzd_CheckItemDlg(CWnd* pParent /*=NULL*/)
	: CWzdDlgBase(CWzd_CheckItemDlg::IDD, pParent)
{
	m_pCurrentStepItem = NULL;
	m_pTestItem = NULL;
}

CWzd_CheckItemDlg::~CWzd_CheckItemDlg()
{
}

void CWzd_CheckItemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ITEM_LIST, m_ctrlChectItemList);
}

void CWzd_CheckItemDlg::XUI_InitAdjust()
{
	CXUIAdjItem_Area::XUI_SetParentWnd(this);
	//�����ƶ�
	XUI_AddWnd(&m_ctrlChectItemList, 0, 0, 1, 1);
	CXUIAdjItem_Area::XUI_OnSize();
}

BEGIN_MESSAGE_MAP(CWzd_CheckItemDlg, CDialog)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_CHECK_ITEM_LIST, &CWzd_CheckItemDlg::OnNMClickCheckItemList)
	ON_NOTIFY(NM_RCLICK, IDC_CHECK_ITEM_LIST, &CWzd_CheckItemDlg::OnNMRClickCheckItemList)
	ON_COMMAND(ID_TEST_CURRENT_ITEM, &CWzd_CheckItemDlg::OnTestCurrentItem)
	ON_COMMAND(ID_FROM_TEST_ITEM, &CWzd_CheckItemDlg::OnFromTestItem)
	ON_COMMAND(ID_CHECK_DETAIL_INFO, &CWzd_CheckItemDlg::OnCheckDetailInfo)
	ON_WM_CREATE()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CWzd_CheckItemDlg ��Ϣ�������
void CWzd_CheckItemDlg::InitCheckItemInfo(CItems* pStep)
{
	m_ctrlChectItemList.SetImageList(&m_ImageList,LVSIL_SMALL);
	m_ctrlChectItemList.SetExtendedStyle(m_ctrlChectItemList.GetExtendedStyle() | LVS_EX_FULLROWSELECT /*| LVS_SHOWSELALWAYS | LVS_SINGLESEL*/ | 
												LVS_EX_CHECKBOXES |LVS_EX_SUBITEMIMAGES |LVS_NOCOLUMNHEADER);
	m_ctrlChectItemList.InsertColumn(0, _T("ttt"), LVCFMT_LEFT, 450);
	m_ctrlChectItemList.InsertColumn(1, _T("tt"), LVCFMT_CENTER, 50);

	if(pStep == NULL)
	{
		return;
	}
	m_pCurrentStepItem = pStep;

	CString strText = _T("��ʼ��������");
	g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText);

	CItems CheckItems;
	pStep->SelectChildrenByClassID(CheckItems,GBCLASSID_ITEMS);

	POS posHead = CheckItems.GetHeadPosition();
	int nPos = 0;
	while(posHead != NULL)
	{
		CItems* pTestItem = (CItems*)CheckItems.GetNext(posHead);
		m_ctrlChectItemList.InsertItem(nPos,pTestItem->m_strName,-1);
		m_ctrlChectItemList.SetItemData(nPos,(DWORD)pTestItem);
		//m_ctrlChectItemList.SetItem(nPos,1,LVIF_IMAGE,NULL,1,0,0,0);
		if(pTestItem->GetState() == TEST_STATE_TESTING) //������
		{
			m_ctrlChectItemList.SetItem(nPos,1,LVIF_IMAGE,NULL,2,0,0,0);
			m_ctrlChectItemList.SetListSelectRow(nPos,m_ctrlChectItemList.GetListSelectRow());
		}
		else if(pTestItem->GetState() == TEST_STATE_ELIGIBLE) //�ϸ�
		{
			m_ctrlChectItemList.SetItem(nPos,1,LVIF_IMAGE,NULL,1,0,0,0);
		}
		else if(pTestItem->GetState() == TEST_STATE_INLEGIBLE) //���ϸ�
		{
			m_ctrlChectItemList.SetItem(nPos,1,LVIF_IMAGE,NULL,0,0,0,0);
		}
		else
		{
			m_ctrlChectItemList.SetItem(nPos,1,LVIF_IMAGE,NULL,-1,0,0,0);
		}

		m_ctrlChectItemList.SetCheck(nPos, pTestItem->m_nSelect);
		nPos++;
	}
	m_ctrlChectItemList.SetListSelectRow(0,-1);
	//m_ctrlChectItemList.SetItemState(0, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	m_ctrlChectItemList.UpdateData(FALSE);
	CheckItems.RemoveAll();
}

//�������У����²���ֵ ���Ե�״̬ͼ��
void CWzd_CheckItemDlg::UpdateCheckItemInfo(CItems* pStep)
{
	if(pStep == NULL)
	{
		return;
	}
	if(pStep == m_pCurrentStepItem)
	{
		return;
	}

	m_pCurrentStepItem = pStep;
	CItems CheckItems;
	pStep->SelectChildrenByClassID(CheckItems,GBCLASSID_ITEMS);

	m_ctrlChectItemList.DeleteAllItems();
	//int nSize = CheckItems.GetCount();
	POS pos = CheckItems.GetHeadPosition();
	int nPosIndex = 0;
	while(pos != NULL)
	{
		CItems* pTestItem = NULL;
		pTestItem = (CItems*)CheckItems.GetNext(pos);
		m_ctrlChectItemList.InsertItem(nPosIndex,pTestItem->m_strName,-1);
		m_ctrlChectItemList.SetItemData(nPosIndex,(DWORD)pTestItem);
		//m_ctrlChectItemList.SetItem(nPosIndex,1,LVIF_IMAGE,NULL,1,0,0,0);
		if(pTestItem->GetState() == TEST_STATE_TESTING) //������
		{
			m_ctrlChectItemList.SetItem(nPosIndex,1,LVIF_IMAGE,NULL,2,0,0,0);
			m_ctrlChectItemList.SetListSelectRow(nPosIndex,m_ctrlChectItemList.GetListSelectRow());
		}
		else if(pTestItem->GetState() == TEST_STATE_ELIGIBLE) //�ϸ�
		{
			m_ctrlChectItemList.SetItem(nPosIndex,1,LVIF_IMAGE,NULL,1,0,0,0);
		}
		else if(pTestItem->GetState() == TEST_STATE_INLEGIBLE) //���ϸ�
		{
			m_ctrlChectItemList.SetItem(nPosIndex,1,LVIF_IMAGE,NULL,0,0,0,0);
		}
		else
		{
			m_ctrlChectItemList.SetItem(nPosIndex,1,LVIF_IMAGE,NULL,-1,0,0,0);
		}

		m_ctrlChectItemList.SetCheck(nPosIndex, pTestItem->m_nSelect);
		nPosIndex++;
	}
	//m_ctrlChectItemList.SetListSelectRow(0,-1);
	m_ctrlChectItemList.UpdateData(FALSE);
	CheckItems.RemoveAll();
}

void CWzd_CheckItemDlg::UpdateCheckItemState(CGbItemBase* pTestItem) 
{
	if(pTestItem == NULL)
	{
		return;
	}
	int nCount = m_ctrlChectItemList.GetItemCount();
	for(int i = 0;i < nCount;i++)
	{
		CItems* pItem = NULL;
		pItem = (CItems*)m_ctrlChectItemList.GetItemData(i);
		if(pItem == NULL)
		{
			return;
		}
		if(pItem == pTestItem)
		{
			if(pTestItem->GetState() == TEST_STATE_TESTING) //������
			{
				m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,2,0,0,0);
				m_ctrlChectItemList.SetListSelectRow(i,m_ctrlChectItemList.GetListSelectRow());
			}
			else if(pTestItem->GetState() == TEST_STATE_ELIGIBLE) //�ϸ�
			{
				m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,1,0,0,0);
				m_ctrlChectItemList.SetListRowState(i);

				CString strText = _T("");
				strText += pTestItem->m_strName;
				strText += _T("  ���Ժϸ�");
				g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText);
				
			}
			else if(pTestItem->GetState() == TEST_STATE_INLEGIBLE) //���ϸ�
			{
				m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,0,0,0,0);
				m_ctrlChectItemList.SetListRowState(i);

				CString strText = _T("");
				strText += pTestItem->m_strName;
				strText += _T("  ���Բ��ϸ�");
				g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText,Log_Type_Error);
			}
			else
			{
				m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,-1,0,0,0);
			}

			m_ctrlChectItemList.UpdateData(FALSE);
			break;
		}
	}
}

void CWzd_CheckItemDlg::UpdateCheckItemState2()
{
	int nCount = m_ctrlChectItemList.GetItemCount();
	for(int i = 0;i < nCount;i++)
	{
		CItems* pItem = NULL;
		pItem = (CItems*)m_ctrlChectItemList.GetItemData(i);
		if(pItem == NULL)
		{
			return;
		}
		
		if(pItem->GetState() == TEST_STATE_TESTING) //������
		{
			m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,2,0,0,0);
			m_ctrlChectItemList.SetListSelectRow(i,m_ctrlChectItemList.GetListSelectRow());
			//m_ctrlChectItemList.UpdateData(FALSE);
			if(m_pTestItem != pItem)
			{
				CString strText = _T("���ڲ��ԣ�");
				strText += pItem->m_strName;
				g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText);
				m_pTestItem = pItem;
			}
			break;
		}
		/*else if(pItem->GetState() == TEST_STATE_ELIGIBLE) //�ϸ�
		{
			m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,1,0,0,0);
		}
		else if(pItem->GetState() == TEST_STATE_INLEGIBLE) //���ϸ�
		{
			m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,0,0,0,0);
		}
		else
		{
			m_ctrlChectItemList.SetItem(i,1,LVIF_IMAGE,NULL,-1,0,0,0);
		}
		m_ctrlChectItemList.UpdateData(FALSE);
		break;*/
	}
}

void CWzd_CheckItemDlg::SetSelectRow(CItems* pTestItem)
{
	if(pTestItem == NULL)
	{
		return;
	}
	int nCount = m_ctrlChectItemList.GetItemCount();
	for(int i = 0;i < nCount;i++)
	{
		CItems* pItem = NULL;
		pItem = (CItems*)m_ctrlChectItemList.GetItemData(i);
		if(pItem == NULL)
		{
			return;
		}
		if(pItem == pTestItem)
		{
			m_ctrlChectItemList.SetListSelectRow(i,m_ctrlChectItemList.GetListSelectRow());
			//m_ctrlChectItemList.SetItemState(i, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED, LVIS_SELECTED|LVIS_FOCUSED|LVIS_DROPHILITED);
			return;
		}
	}
}

bool CWzd_CheckItemDlg::GetCurrentItemInfo(CItems* &pTestItem)
{
	POSITION pos = m_ctrlChectItemList.GetFirstSelectedItemPosition();
	int nItem = -1;
	nItem = m_ctrlChectItemList.GetNextSelectedItem(pos);
	if(nItem < 0)
	{
		return false;
	}

	pTestItem = (CItems*)m_ctrlChectItemList.GetItemData(nItem);
	if(pTestItem == NULL)
	{
		return false;
	}
	return true;
}

////////////////////////
void CWzd_CheckItemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	XUI_OnSize(cx, cy);
}

int CWzd_CheckItemDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWzdDlgBase::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	m_ImageList.Create(24,24,ILC_MASK,10,4);
	CString strImg = _P_GetResourcePath();
	strImg += "iSmartTestWzd/test/";

	CString strImg1 = strImg+ "fail.ico";
	HICON IcImage1 = (HICON)LoadImage(NULL, strImg1, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	m_ImageList.Add(IcImage1);
	CString strImg2 = strImg+ "success.ico";
	HICON IcImage2 = (HICON)LoadImage(NULL,strImg2,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	m_ImageList.Add(IcImage2);
	CString strImg3 = strImg+ "testing.ico";
	HICON IcImage3 = (HICON)LoadImage(NULL,strImg3,IMAGE_ICON,0,0,LR_LOADFROMFILE);
	m_ImageList.Add(IcImage3);
	return 0;
}

void CWzd_CheckItemDlg::OnNMClickCheckItemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}
	CItems* pTestItem = NULL;
	pTestItem = (CItems*)m_ctrlChectItemList.GetItemData(pNMItemActivate->iItem);
	if(pTestItem == NULL)
	{
		return;
	}
	//����б����������Խ�����ݽڵ� ��ʾ����Ĳ��Խ����
	//if(!m_nTestResultState)
	{
		CSafety *pRslt = NULL;
		pRslt = (CSafety *)pTestItem->FindByID(ID_CONSTANT_ITEM_RPTVIEW);
		if (pRslt != NULL)
		{
			//CReports *pRpts = pRslt->GetReports();reinterpret_cast<WPARAM>((void*)(pItem))
			//g_pWzdMainDlg->m_pAutoTest->OnReport(pRslt,0);
			g_pWzdMainDlg->m_pAutoTest->OnReport(reinterpret_cast<WPARAM>((void*)(pRslt)),0);
		}
		else
		{
			//�����һ���ڵ�� �������ǰ�ڵ�û�в��Խ��
			g_pWzdMainDlg->m_pAutoTest->ClearResult();
		}
	}
	

	LVHITTESTINFO lvinfo;  
	lvinfo.pt = pNMItemActivate->ptAction;
	int nItem = m_ctrlChectItemList.HitTest(&lvinfo);  
	if(lvinfo.flags == LVHT_ONITEMSTATEICON)
	{
		CString strIDPath = pTestItem->m_strID;
		CExBaseList* pParent = (CExBaseList*)pTestItem->GetParent();
		while (pParent)
		{
			strIDPath = pParent->m_strID + "$" + strIDPath;

			if(pParent->GetClassID() == GBCLASSID_DEVICE)
			{	
				break;
			}

			pParent = (CExBaseList*)pParent->GetParent();
		}

		long nCheck = m_ctrlChectItemList.GetCheck(pNMItemActivate->iItem);
		pTestItem->m_nSelect = !nCheck;
		g_pWzdMainDlg->SetItemState(strIDPath, pTestItem->m_nSelect);
	}
	*pResult = 0;
}

void CWzd_CheckItemDlg::OnNMRClickCheckItemList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem < 0)
	{
		return;
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint ptCurSel(0,0);
	GetCursorPos(&ptCurSel);
	//ת��Ϊ��ǰ�ؼ�����ϵ������
	m_ctrlChectItemList.ScreenToClient(&ptCurSel);
	LVHITTESTINFO HitTestInfo;
	HitTestInfo.pt = ptCurSel;   
	//�ж��������еڼ���
	int nItem = m_ctrlChectItemList.HitTest(&HitTestInfo);

	CItems* pTestItem = NULL;
	pTestItem = (CItems*)m_ctrlChectItemList.GetItemData(pNMItemActivate->iItem);
	if(pTestItem == NULL)
	{
		return;
	}

	//�����ѡ����
	if (nItem != -1)
	{
		CMenu menu;
		menu.LoadMenu(IDR_TEST_ITEM_MENU);
		CPoint point;
		GetCursorPos(&point);

		CMenu* pSubMenu = menu.GetSubMenu(0);

		//shaolei  2024-3-9�˴��߼�д���ˣ�Ӧ�����������Բ����ڲ����е�״̬������enableΪtrue��
		//�����ǲ�������״̬
		//if(pTestItem->GetState() == TEST_STATE_TESTING)
		if(g_pWzdMainDlg->m_pAutoTest->GetAutoTestState() == AUTOTEST_START
			|| g_pWzdMainDlg->m_pAutoTest->GetAutoTestState() == AUTOTEST_NULL)
		{
			pSubMenu->EnableMenuItem(ID_TEST_CURRENT_ITEM,MF_GRAYED );
			pSubMenu->EnableMenuItem(ID_FROM_TEST_ITEM,MF_GRAYED );
		}
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,point.x,point.y,this);
	}
	*pResult = 0;
}

void CWzd_CheckItemDlg::OnTestCurrentItem()
{
	// TODO: �ڴ���������������
	CItems* pTestItem = NULL;
	if(!GetCurrentItemInfo(pTestItem))
	{
		return;
	}
	if(pTestItem == NULL)
	{
		return;
	}

	CString strText = _T("���� ");
	strText += pTestItem->m_strName;
	strText += _T("������");
	g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText);

	CString strItemPath = Gb_GetItemPath(pTestItem);
	g_pWzdMainDlg->TestCurrentItem(strItemPath);
	
}

void CWzd_CheckItemDlg::OnFromTestItem()
{
	// TODO: �ڴ���������������
	CItems* pTestItem = NULL;
	if(!GetCurrentItemInfo(pTestItem))
	{
		return;
	}
	if(pTestItem == NULL)
	{
		return;
	}

	CString strText = _T("�ӵ�ǰ������ ");
	strText += pTestItem->m_strName;
	strText += _T("��ʼ����");
	g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText);

	CString strItemPath = Gb_GetItemPath(pTestItem);
	g_pWzdMainDlg->TestFromItem(strItemPath);

}

void CWzd_CheckItemDlg::OnCheckDetailInfo()
{
	// TODO: �ڴ���������������
	CItems* pTestItem = NULL;
	if(!GetCurrentItemInfo(pTestItem))
	{
		return;
	}
	if(pTestItem == NULL)
	{
		return;
	}

	CString strText = _T("�鿴 ");
	strText += pTestItem->m_strName;
	strText += _T("��������ϸ��Ϣ");
	g_pWzdMainDlg->m_pAutoTest->SetCurrentLog(strText);

	CWzd_DetailInfoDlg detailInfoDlg;
	detailInfoDlg.ShowItemDetailInfo(pTestItem);
	detailInfoDlg.DoModal();
}

HBRUSH CWzd_CheckItemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CWzdDlgBase::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
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
	}
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}
