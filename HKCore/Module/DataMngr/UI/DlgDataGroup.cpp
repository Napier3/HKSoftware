// D:\WorkPM\Source\Protocol\PpDev\PpTemplateFileMngr\DlgDataGroup.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgDataGroup.h"

#include "..\..\API\GloblaDrawFunctions.h"
#include "..\..\API\FileApi.h"
#include "..\..\XLanguage\XLanguageMngr.h"
#include "..\ValuesParse.h"

// CDlgDataGroup 对话框

IMPLEMENT_DYNAMIC(CDlgDataGroup, CDialog)

void CDlgDataGroup::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	CShortData *pData = (CShortData*)((CExBaseListGrid*)pGridCtrl)->GetDataRow(nRow, 1);

	m_listSelDatas.OnDataSelChanged(pData);
}

BOOL CDlgDataGroup::OnEditCellLBDblClk(CXGridCtrlBase *pGridCtrl, int nRow, int nCol, UINT nChar)
{
	return FALSE;
}

void CDlgDataGroup::OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	CShortData *pData = (CShortData*)((CExBaseListGrid*)pGridCtrl)->GetDataRow(nRow, 1);

	if (nCol == DATAMNGRFOLDER_COL_SEL)
	{
		m_listSelDatas.OnDataSelChanged(pData);
	}
	else if (nCol == DATAMNGRFOLDER_COL_VALUE)
	{
		m_listSelDatas.OnDataValueChanged(pData);
	}

	//m_listSelDatas.OnDataValueChanged(pData);
}


CDlgDataGroup::CDlgDataGroup(const CString &strFile, const CString &strDatas,CWnd* pParent)
: CDynDialogEx(pParent)
{
	m_strDatas = strDatas;
	m_oFolderRoot.OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	m_oFolderRoot.InitReserved(0);
	m_oFolderRoot.InitItemData(0);

	CString strDataTypeFile;
	strDataTypeFile = GetPathFromFilePathName(strFile);
	strDataTypeFile += m_oFolderRoot.m_strDataType;
	m_oDataTypes.Open(strDataTypeFile, CDataMngrXmlRWKeys::g_pXmlKeys);

	CValuesParse oParse;
	oParse.Parse(m_strDatas);

	POS pos = oParse.GetHeadPosition();
	CValue *pValue = NULL;
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)oParse.GetNext(pos);
		pData = FindData(pValue->m_strID);

		if (pData != NULL)
		{
			pData->m_dwReserved = 1;
			pData->m_dwItemData = CString_To_long(pValue->m_strValue);
			pData->m_strValue = pValue->m_strValue;
			m_listShortDatas.AddTail(pData);
		}
	}
}

CShortData* CDlgDataGroup::FindData(const CString &strPath)
{
	POS pos = m_oFolderRoot.GetHeadPosition();
	CDataGroup *pDataGroup = NULL;
	CShortData *pFind = NULL;

	while (pos != NULL)
	{
		pDataGroup = (CDataGroup *)m_oFolderRoot.GetNext(pos);

		if (pDataGroup->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			pFind = FindData(pDataGroup, strPath);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CShortData* CDlgDataGroup::FindData(CDataGroup *pGroup, const CString &strPath)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *pObj = NULL;
	CShortData *pFind = NULL;

	CString strLeft, strRight;
	long nPos = strPath.Find(m_oFolderRoot.m_strValue);

	if (nPos > 0)
	{
		strLeft = strPath.Left(nPos);
		strRight = strPath.Mid(nPos+1);
	}
	else
	{
		strLeft = strPath;
	}

	if (strLeft != pGroup->m_strValue)
	{
		return NULL;
	}

	while (pos)
	{
		pObj = (CExBaseObject *)pGroup->GetNext(pos);

		if (pObj->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			pFind = FindData((CDataGroup*)pObj, strRight);

			if (pFind != NULL)
			{
				break;
			}
		}
		else if (pObj->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			if (strRight == ((CShortData*)pObj)->m_strRemark)
			{
				pFind = (CShortData*)pObj;
				break;
			}
		}
	}

	return pFind;
}


CDlgDataGroup::~CDlgDataGroup()
{

}

void CDlgDataGroup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	if (!::IsWindow(m_folderTree.m_hWnd))
	{
		return;
	}
}


BEGIN_MESSAGE_MAP(CDlgDataGroup, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgDataGroup::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, XDMF_IDC_LIST_DATA, &CDlgDataGroup::OnNMDblclkListData)
	ON_NOTIFY(TVN_SELCHANGED, XDMF_IDC_TREE_DATAGROUP, &CDlgDataGroup::OnTvnSelchangedTree)
END_MESSAGE_MAP()


int CDlgDataGroup::DoModal()   
{   
	int iRet = CDynDialogEx::DoModal();   

	m_listShortDatas.RemoveAll();
	return iRet;   
}   

// CDlgDataGroup 消息处理程序
void CDlgDataGroup::OnCancel()
{
	CDialog::OnCancel();
}

void CDlgDataGroup::InitDestDatas()
{
	POS pos = m_listShortDatas.GetHeadPosition();
	CShortData *pData = NULL;
	CString strPath;
	m_strDatas = _T("\"");

	while(pos != NULL)
	{
		pData = (CShortData *)m_listShortDatas.GetNext(pos);
		strPath = CDataGroupListView::GetDataPath(pData, &m_oFolderRoot, m_oFolderRoot.m_strValue);
		m_strDatas.AppendFormat(_T("(%s,%s)"), strPath, pData->m_strValue);
	}

	m_strDatas += _T("\"");

}


void CDlgDataGroup::OnBnClickedOk()
{
	UpdateData(TRUE);

	InitDestDatas();


	OnOK();
}

void CDlgDataGroup::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CDataGroup *pDataGroup = m_folderTree.GetCurrSelGroup();
	m_gridDatas.ShowDatas(pDataGroup);
}

void CDlgDataGroup::CreateControls()
{
	CreateTreeCtrl(m_folderTree, CRect(14, 5, 189, 260), XDMF_IDC_TREE_DATAGROUP, this);

	m_gridDatas.Create(CRect(198, 5, 626, 260), this, XDMF_IDC_GRID_DATA);
	m_gridDatas.SetFont(g_pGlobalFont11);
	m_gridDatas.InitGrid();

	CreateListCtrl(m_listSelDatas, CRect(14, 265, 626, 355), XDMF_IDC_LIST_DATA, this);

	
	CreateButton(m_btnOK, /*_T("确定")*/g_sLangTxt_OK, CRect(463, 360, 533, 381), IDOK, this);
	CreateButton(m_btnCancel, /*_T("取消")*/g_sLangTxt_Cancel, CRect(552, 360, 622, 381), IDCANCEL, this);

	m_folderTree.SetFont(g_pGlobalFont11);
	m_listSelDatas.SetFont(g_pGlobalFont11);
	
	m_btnOK.SetFont(g_pGlobalFont11);
	m_btnCancel.SetFont(g_pGlobalFont11);
}


BOOL CDlgDataGroup::OnInitDialog()
{
	CDialog::OnInitDialog();

	CreateControls();

	EnableToolTips(TRUE);
	m_gridDatas.m_pDataTypesRef = &m_oDataTypes;
	m_gridDatas.AttachDataViewOptrInterface(this);

	HTREEITEM hRoot = m_folderTree.ShowCDataGroup(&m_oFolderRoot);
	m_folderTree.Expand(hRoot, TVE_EXPAND);

	m_listSelDatas.m_pRoot = &m_oFolderRoot;
	m_listSelDatas.m_strFlag = m_oFolderRoot.m_strValue;
	m_listSelDatas.InitCollumns();
	m_listSelDatas.ShowBaseList(&m_listShortDatas);
	m_gridDatas.m_pDataGroupListViewRef = &m_listSelDatas;
	
	m_btnOK.EnableWindow(TRUE);

	MoveWindow(CRect( 0, 0, 650, 420), TRUE);
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDlgDataGroup::OnNMDblclkListData(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	CExBaseObject* pObj = m_listSelDatas.GetSelectObject();
	
	if (pObj == NULL)
	{
		
	}

	*pResult = 0;
}


BOOL CDlgDataGroup::PreTranslateMessage(MSG* pMsg)
{
	return CDialog::PreTranslateMessage(pMsg);
}
