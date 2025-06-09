// SelDataDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DvmMapSelDataDlg.h"

//////////////////////////////////////////////////////////////////////////
//
CDvmDatasetTreeCtrl::CDvmDatasetTreeCtrl()
{
	m_pSelDvmObject = NULL;
	m_hSelDvmItem = NULL;
}

CDvmDatasetTreeCtrl::~CDvmDatasetTreeCtrl()
{

}

void CDvmDatasetTreeCtrl::ShowDataset(CExBaseList *pListDs)
{
	POS pos = pListDs->GetHeadPosition();
	CDvmDataset *pDataset = NULL;

	while (pos != NULL)
	{
		pDataset = (CDvmDataset *)pListDs->GetNext(pos);
		ShowDataset(pDataset, NULL);
	}

	if (m_hSelDvmItem != NULL)
	{
		SelectItem(m_hSelDvmItem);
	}
}

void CDvmDatasetTreeCtrl::ShowDataset(CDvmDataset *pDataset, HTREEITEM hParent)
{
	HTREEITEM hDs = NULL;
	CString strText;
	strText.Format(_T("%s$%s"), ((CExBaseObject*)pDataset->GetParent())->m_strID, pDataset->m_strID);
	hDs = InsertItem(strText, 0, 0, TVI_ROOT);
	SetItemData(hDs, (DWORD)pDataset);

	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);
		ShowData(pData, hDs);
	}

	Expand(hDs, TVE_EXPAND);
}

void CDvmDatasetTreeCtrl::ShowData(CDvmData *pData, HTREEITEM hParent)
{
	HTREEITEM hData = NULL;
	CString strText;
	
	if (pData->m_strName.GetLength() > 0)
	{
		strText.Format(_T("%s  [%s]"), pData->m_strName, pData->m_strID);
	}
	else
	{
		strText = pData->m_strID;
	}

	hData = InsertItem(strText, 0, 0, hParent);
	SetItemData(hData, (DWORD)pData);

	if (m_pSelDvmObject == pData)
	{
		m_hSelDvmItem = hData;
	}

	POS pos = pData->GetHeadPosition();
	CDvmValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CDvmValue *)pData->GetNext(pos);
		ShowValues(pValue, hData);
	}
}

void CDvmDatasetTreeCtrl::ShowValues(CDvmValue *pValue, HTREEITEM hParent)
{
	HTREEITEM hValue = NULL;
	hValue = InsertItem(pValue->m_strID, 0, 0, hParent);
	SetItemData(hValue, (DWORD)pValue);

	if (m_pSelDvmObject == pValue)
	{
		m_hSelDvmItem = hValue;
	}

	POS pos = pValue->GetHeadPosition();
	CDvmValue *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmValue *)pValue->GetNext(pos);
		ShowValues(p, hValue);
	}
}

//////////////////////////////////////////////////////////////////////////
// CDvmMap_SelDataDlg 对话框

IMPLEMENT_DYNAMIC(CDvmMap_SelDataDlg, CDialog)

CDvmMap_SelDataDlg::CDvmMap_SelDataDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDvmMap_SelDataDlg::IDD, pParent)
{
	m_pSelMapObject = NULL;
	m_nMatchCount = 1;
	m_nGapStand = 1;
	m_nGapDest = 1;
}

CDvmMap_SelDataDlg::~CDvmMap_SelDataDlg()
{
	m_listDataset.RemoveAll();
}

void CDvmMap_SelDataDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_DATASETS, m_treeDataset);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDC_CMB_NUMBER, m_cmbNumber);
	DDX_Control(pDX, IDC_CMB_KEY_SEL, m_cmbKeySel);
	DDX_Control(pDX, IDC_BTN_MATCH_MORE, m_btnMatchMore);
	DDX_Control(pDX, IDC_CMB_GAP_STAND, m_cmbGapStand);
	DDX_Control(pDX, IDC_CMB_GAP_DEST, m_cmbGapDest);
	DDX_Control(pDX, IDC_STATIC_SEARCHDATA, m_xFrameSearchData);
	DDX_Control(pDX, IDC_BTN_FIND, m_btnSeldataFind);
	DDX_Control(pDX, IDC_STATIC_SELDATAMATCH, m_xFrameSelDataMatch);
	DDX_Control(pDX, IDC_STATIC_STANDBLANK, m_wndSelDataStanBlank);
	DDX_Control(pDX, IDC_STATIC_SELGEBLANK, m_wndSelDataGeBlank);
	DDX_Control(pDX, IDC_STATIC_SELDATAGE, m_wndSelDataGe);
	DDX_Control(pDX, IDC_STATIC_SELDATAGE2, m_wndSelDataGe2);
	DDX_Control(pDX, IDCANCEL, m_btnSelDataCancel);
}


BEGIN_MESSAGE_MAP(CDvmMap_SelDataDlg, CDialog)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_DATASETS, &CDvmMap_SelDataDlg::OnTvnSelchangedTreeDatasets)
	ON_BN_CLICKED(IDC_BTN_MATCH_MORE, &CDvmMap_SelDataDlg::OnBnClickedBtnMatchMore)
	ON_BN_CLICKED(IDC_BTN_FIND, &CDvmMap_SelDataDlg::OnBnClickedBtnFind)
	ON_BN_CLICKED(IDCANCEL, &CDvmMap_SelDataDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDvmMap_SelDataDlg 消息处理程序
void CDvmMap_SelDataDlg::AddDataset(CDvmDataset *pDataset)
{
	m_listDataset.AddTail(pDataset);
}

void CDvmMap_SelDataDlg::AppendDataset(CExBaseList *pList)
{
	m_listDataset.Append(pList);
}
// 
// void CDvmMap_SelDataDlg::xlang_InitAndAdjust()
// {
// 	if (xlang_IsCurrXLanguageChinese())
// 	{
// 		return;
// 	}
// 
// 	m_xFrameSearchData.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_SearchData);
// 	m_btnSeldataFind.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_Find);
// 	m_xFrameSelDataMatch.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_BatchMatch);
// 	m_wndSelDataStanBlank.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_AverageDistance);
// 	m_wndSelDataGeBlank.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_MapBlank);
// 	m_wndSelDataGe.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_Ge);
// 	m_wndSelDataGe2.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_Ge);
// 	m_btnMatchMore.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_MatchingTurn);
// 	m_btnOK.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_OK);
// 	m_btnSelDataCancel.SetLanguageID(CXLanguageResourceDvm_DvmMap::g_sLangID_Cancel);
// 
// 	CXLangWndAdjMngr oWndAdjMngr;                      
// 	CXLangWndAdjFrame *pXAdjFrame = NULL;            
// 	oWndAdjMngr.RegisterCols(); //一行，分三列
// 	oWndAdjMngr.RegisterCol();   //第一列
//     pXAdjFrame = oWndAdjMngr.RegisterXFrame(&m_xFrameSearchData); 
// 	pXAdjFrame->RegisterCol();
//     pXAdjFrame->RegisterXWnd(&m_btnSeldataFind);
//     oWndAdjMngr.Adjust(this, TRUE);
// 
// 	oWndAdjMngr.RegisterCol();  //第二列   分小两行
// 	pXAdjFrame = oWndAdjMngr.RegisterXFrame(&m_xFrameSelDataMatch); 
// 	pXAdjFrame->RegisterCol();
//     pXAdjFrame->RegisterXWnd(&m_wndSelDataStanBlank);
//     pXAdjFrame->RegisterXWnd(&m_btnMatchMore);
// 	pXAdjFrame->RegisterCol();
// 	pXAdjFrame->RegisterWnd(&m_cmbGapStand);
// 	pXAdjFrame->RegisterWnd(&m_cmbNumber);
// 	pXAdjFrame->RegisterCol();
// 	pXAdjFrame->RegisterXWnd(&m_wndSelDataGeBlank);
// 	pXAdjFrame->RegisterXWnd(&m_wndSelDataGe2);
// 	pXAdjFrame->RegisterCol();
// 	pXAdjFrame->RegisterWnd(&m_cmbGapDest);
// 	pXAdjFrame->RegisterCol();
// 	pXAdjFrame->RegisterXWnd(&m_wndSelDataGe);
// 	oWndAdjMngr.Adjust(this, TRUE);
// 	
// 
// 	oWndAdjMngr.RegisterCol();    //第三列
// 	oWndAdjMngr.RegisterXWnd(&m_btnOK);
// 	oWndAdjMngr.RegisterXWnd(&m_btnSelDataCancel);
// 
// 	oWndAdjMngr.Adjust(this, TRUE);
// 	xlang_InitByLgugStr(CXLanguageResourceDvm_DvmMap::g_sLangID_SelMatchData, this);
// }

BOOL CDvmMap_SelDataDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_treeDataset.m_pSelDvmObject = m_pSelDvmObject;
	m_treeDataset.ShowDataset(&m_listDataset);

	m_cmbNumber.InitNumbers(1, 80, 3);
	m_cmbGapStand.InitNumbers(1, 10, 1);
	m_cmbGapDest.InitNumbers(1, 10, 1);

	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += _T("DvmMapKey.xml");
	m_oFilterTextMngr.OpenXmlFile(strFile);
	m_cmbKeySel.SetAddEmptyString(TRUE);
	m_cmbKeySel.ShowBaseList(&m_oFilterTextMngr);

  //  xlang_InitAndAdjust();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDvmMap_SelDataDlg::OnTvnSelchangedTreeDatasets(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	if (pNMTreeView->itemNew.hItem == NULL)
	{
		m_pSelDvmObject = NULL;
	}
	else
	{
		m_pSelDvmObject = (CExBaseObject *)m_treeDataset.GetItemData(pNMTreeView->itemNew.hItem);
	}

	EnableOkButton();
	*pResult = 0;
}

void CDvmMap_SelDataDlg::EnableOkButton()
{
	if (m_pSelDvmObject == NULL)
	{
		m_btnOK.SetEnabled(FALSE);
		m_btnMatchMore.SetEnabled(FALSE);
		return;
	}

	if (m_pSelDvmObject->m_dwReserved == 1)
	{
		m_btnOK.SetEnabled(FALSE);
		m_btnMatchMore.SetEnabled(FALSE);
		return;
	}
	if (m_pSelDvmObject->GetClassID() == m_pDvmMapSrcObject->GetClassID())
	{
		m_btnOK.SetEnabled(TRUE);
		m_btnMatchMore.SetEnabled(TRUE);
		//20231103 luozibing 类型相同时，要另外判断是否都存在子节点
		if(((CExBaseList *)m_pSelDvmObject)->GetHead() == NULL&&((CExBaseList *)m_pDvmMapSrcObject)->GetHead() != NULL)
		{
			m_btnOK.SetEnabled(FALSE);
			m_btnMatchMore.SetEnabled(FALSE);
		}
		else if(((CExBaseList *)m_pDvmMapSrcObject)->GetHead() == NULL&&((CExBaseList *)m_pSelDvmObject)->GetHead() != NULL)
		{
			m_btnOK.SetEnabled(FALSE);
			m_btnMatchMore.SetEnabled(FALSE);
		}

// 		if (m_pSelDvmObject->GetClassID() == DVMCLASSID_CDVMDATA)
// 		{
// 			m_btnMatchMore.EnableWindow(TRUE);
// 		}
// 		else
// 		{
// 			m_btnMatchMore.EnableWindow(FALSE);
// 		}
	}
	else
	{
		m_btnOK.SetEnabled(FALSE);
		m_btnMatchMore.SetEnabled(FALSE);
	}
	//20231103 luozibing 判断是否都不存在子节点
	if(((CExBaseList *)m_pSelDvmObject)->GetHead() == NULL&&((CExBaseList *)m_pDvmMapSrcObject)->GetHead() == NULL)
	{
		m_btnOK.SetEnabled(TRUE);
		m_btnMatchMore.SetEnabled(TRUE);
	}
}

void CDvmMap_SelDataDlg::OnBnClickedBtnMatchMore()
{
	m_nGapStand = m_cmbGapStand.GetNumber();
	m_nGapDest  = m_cmbGapDest.GetNumber();
	m_nMatchCount = m_cmbNumber.GetNumber();
	CDialog::OnOK();
}

void CDvmMap_SelDataDlg::OnBnClickedBtnFind()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CDvmMap_SelDataDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	OnCancel();
}
