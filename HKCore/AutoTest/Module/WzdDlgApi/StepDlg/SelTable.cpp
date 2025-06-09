// SelTable.cpp : 实现文件
//

#include "stdafx.h"
#include "SelTable.h"
#include "MessageDlg.h"


// SelTable 对话框

IMPLEMENT_DYNAMIC(SelTable, CDialog)

SelTable::SelTable(CWnd* pParent /*=NULL*/)
	: CDialog(SelTable::IDD, pParent)
	, m_strTableName(_T(""))
{
	m_pPdfDBInfo = NULL;
	m_plistTable = NULL;
	m_pSelectTable = NULL;
}

SelTable::~SelTable()
{
}
//20240312 huangliang 模态显示对话框
void SelTable::ShowManualConfirm()
{
	DoModal();
}

void SelTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE, m_Tree);
	DDX_Control(pDX, IDC_CMB_NAME, m_CmbName);
	DDX_Control(pDX, IDC_CMB_VAL, m_CmbVal);
	DDX_Control(pDX, IDC_CMB_DW, m_CmbDW);
	DDX_Control(pDX, IDC_GRID, m_Gird);
	DDX_Text(pDX, IDC_STATIC_TABLENAME, m_strTableName);
	DDX_Control(pDX, IDC_RADIO_NOUSE, m_radioNoUse);
	DDX_Control(pDX, IDC_RADIO_PARAMETER, m_radioParameter);
	DDX_Control(pDX, IDC_RADIO_ENA, m_radioEna);
	DDX_Control(pDX, IDC_RADIO_SETTING, m_radioSetting);
	DDX_Control(pDX, IDC_RADIO_MATRIX, m_radioMatrix);
	DDX_Control(pDX, IDC_CHECK_HEAD, m_CheckHeadBtn);
}


BEGIN_MESSAGE_MAP(SelTable, CDialog)
	ON_BN_CLICKED(IDCANCEL, &SelTable::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_TREE, &SelTable::OnNMClickTree)
	ON_CBN_SELCHANGE(IDC_CMB_NAME, &SelTable::OnCbnSelchangeCmbName)
	ON_CBN_SELCHANGE(IDC_CMB_VAL, &SelTable::OnCbnSelchangeCmbVal)
	ON_CBN_SELCHANGE(IDC_CMB_DW, &SelTable::OnCbnSelchangeCmbDw)
	ON_BN_CLICKED(IDC_RADIO_NOUSE, &SelTable::OnBnClickedRadioNouse)
	ON_BN_CLICKED(IDC_RADIO_PARAMETER, &SelTable::OnBnClickedRadioParameter)
	ON_BN_CLICKED(IDC_RADIO_ENA, &SelTable::OnBnClickedRadioEna)
	ON_BN_CLICKED(IDC_RADIO_SETTING, &SelTable::OnBnClickedRadioSetting)
	ON_BN_CLICKED(IDC_RADIO_MATRIX, &SelTable::OnBnClickedRadioMatrix)
	ON_BN_CLICKED(IDC_CHECK_HEAD, &SelTable::OnBnClickedCheckHead)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// SelTable 消息处理程序
void SelTable::OnBnClickedCancel()//取消
{
	if(!CheckTableData())
	{
		if( MessageDlg::MessageBox("提示", "将不使用未确认的表？", MessageDlg::YESANDNO) != IDOK )
			return;
		SetTableNoUse();
	}

	OnCancel();
}
BOOL SelTable::CheckTableData()
{
	CPdfXmlStringTable* pXmlTable = NULL;
	POS pos = m_plistTable->GetHeadPosition();
	while (pos != NULL)
	{
		pXmlTable = (CPdfXmlStringTable *)m_plistTable->GetNext(pos);
		if(pXmlTable->m_strName.Find(_T(" *")) != -1)
		{
			return FALSE;
		}
	}
	
	return TRUE;
}
void SelTable::SetTableNoUse()
{
	CPdfXmlStringTable* pXmlTable = NULL;
	POS pos = m_plistTable->GetHeadPosition();
	while (pos != NULL)
	{
		pXmlTable = (CPdfXmlStringTable *)m_plistTable->GetNext(pos);
		if(pXmlTable->m_strName.Find(_T(" *")) != -1)
		{
			set_table_identify(pXmlTable, NO_USE_TABLE);
		}
	}
}

BOOL SelTable::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadTreeData();

	m_Gird.m_nCount = 0;
	m_Gird.InitGrid();

	//直接获取第一个表格
	SetSelectTable(m_plistTable->GetHead());
	if(m_pSelectTable != NULL)
	{
		CPdfXmlStringRow *pXmlRow = (CPdfXmlStringRow *)m_pSelectTable->GetTail();
		m_Gird.m_nCount = pXmlRow->GetCount()+1;
		m_Gird.InitGrid();
	}

	UpdateDlg_CMB();
	UpdateDlg_Grid();
	return TRUE;
}

void SelTable::LoadTreeData()
{
	m_Tree.DeleteAllItems();
	m_Tree.AddClassID(PDFPCLASSID_TABLE);
	m_Tree.ShowBaseList(m_plistTable, false);
}

void SelTable::OnNMClickTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	CPoint pt = GetCurrentMessage()->pt;
	m_Tree.ScreenToClient(&pt);
	UINT uFlags = 0;  
	HTREEITEM hItem = m_Tree.HitTest(pt, &uFlags);//然后做点击测试
	if(hItem == NULL)
		return ;

	CExBaseObject* pSelectTable = (CExBaseObject*)m_Tree.GetItemData(hItem);
	SetSelectTable(pSelectTable);

	UpdateDlg_Grid();
	UpdateDlg_CMB();
	
	*pResult = 0;
}
void SelTable::SetSelectTable(CExBaseObject* pSelectTable)
{
	if(pSelectTable == NULL)
		return;
	if(pSelectTable->GetClassID() != PDFPCLASSID_TABLE)
		return;
	m_pSelectTable = (CPdfXmlStringTable*)pSelectTable;

	m_strTableName = m_pSelectTable->m_strName;
	UpdateData(FALSE);
}
void SelTable::UpdateDlg_Grid()
{
	if(m_pSelectTable == NULL)
		return;

	m_CheckHeadBtn.SetCheck(m_pSelectTable->m_AddTile);

	CPdfXmlStringRow *pXmlRow = NULL;
	POS pos = m_pSelectTable->GetHeadPosition();
	int nCount = 1;

	m_Gird.DeleteAllItems();
	pXmlRow = (CPdfXmlStringRow *)m_pSelectTable->GetTail();
	m_Gird.m_nCount = pXmlRow->GetCount()+1;
	m_Gird.InitGrid();
	m_Gird.SetRowCount(m_pSelectTable->GetCount()+1, TRUE);
	while (pos)
	{
		pXmlRow = (CPdfXmlStringRow *)m_pSelectTable->GetNext(pos);
		m_Gird.ShowData((CExBaseObject *)pXmlRow,nCount);
	}
	m_Gird.SetRowCount(nCount, TRUE);
	m_Gird.AfterShowDatas(1, TRUE);
}
void SelTable::UpdateDlg_CMB()
{
	if(m_pSelectTable == NULL)
		return;

	ShowClickedRadio(m_pSelectTable->m_strIdentify);

	CPdfXmlStringRow *pXmlRow = (CPdfXmlStringRow *)m_pSelectTable->GetTail();
	m_CmbName.ResetContent();
	m_CmbVal.ResetContent();
	m_CmbDW.ResetContent();
	SetCMB(&m_CmbName,pXmlRow->GetCount());
	SetCMB(&m_CmbVal,pXmlRow->GetCount());
	m_CmbDW.AddString("0");
	SetCMB(&m_CmbDW,pXmlRow->GetCount());

	if(m_pSelectTable->m_iNameHeadCol != -1)
	{
		m_CmbName.SetCurSel(m_pSelectTable->m_iNameHeadCol);
		if(m_pSelectTable->m_iValueHeadCol != -1)
			m_CmbVal.SetCurSel(m_pSelectTable->m_iValueHeadCol);
		if(m_pSelectTable->m_iDWHeadCol != -1)
			m_CmbDW.SetCurSel(m_pSelectTable->m_iDWHeadCol+1);
	}
}
void SelTable::SetCMB(CComboBox *cmb,int count)
{
	for(int i=1;i<count+1;i++)
	{
		CString tmp;
		tmp.Format("%d",i);
		cmb->AddString(tmp);
	}
}
void SelTypeGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(m_nCount);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
}
void SelTypeGrid::InitGridTitle()
{
	CString astrSclIedsGirdTitle[30];
	for(int i= 0;i<m_nCount;i++)
	{
		CString tmp;
		tmp.Format("%d",i);
		astrSclIedsGirdTitle[i] = tmp;
	}
	const int nSclIedsWidth[30]={40,120,120,120,120,120,120,120,120,120};
	SetColumnCount(m_nCount);
	CExBaseListGrid::InitGridTitle(astrSclIedsGirdTitle, nSclIedsWidth, m_nCount);
}
void SelTypeGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/* =TRUE */)
{
	CExBaseList* pDataTmp = (CExBaseList*)pData;
	POS pos = pDataTmp->GetHeadPosition();
	int nCount = 1;
	CString tmp;
	tmp.Format("%d",nRow);
	Show_StaticString(pData, nRow, 0, tmp);
	while (pos)
	{
		CExBaseObject *pXml = pDataTmp->GetNext(pos);
		Show_StaticString(pData, nRow, nCount, pXml->m_strName);
		nCount++;
	}
	nRow++;
}

void SelTable::SaveTableConfig()
{
	if(m_pPdfDBInfo == NULL)
		return ;

	CString strTableName;
	CPdfDBHead *tmp_Head = NULL;
	CPdfXmlStringTable* pXmlTable = NULL;
	POS pos = m_plistTable->GetHeadPosition();
	while (pos != NULL)
	{
		pXmlTable = (CPdfXmlStringTable *)m_plistTable->GetNext(pos);

		strTableName = pXmlTable->m_strName;
		strTableName.Replace(_T(" *"), _T(""));
		tmp_Head = (CPdfDBHead *)m_pPdfDBInfo->FindByID(strTableName);
		if(tmp_Head == NULL)
		{
			tmp_Head = new CPdfDBHead();
			m_pPdfDBInfo->AddTail(tmp_Head);
		}
		if(pXmlTable->m_strIdentify != _T(""))
		{
			tmp_Head->m_strID = strTableName;
			tmp_Head->m_strName = pXmlTable->m_strIdentify;
		}
		if(pXmlTable->m_iNameHeadCol != -1)
		{
			tmp_Head->m_nNameHead = pXmlTable->m_iNameHeadCol;
			tmp_Head->m_nDWHead = pXmlTable->m_iDWHeadCol;
			tmp_Head->m_nValueHead = pXmlTable->m_iValueHeadCol;
		}
		if(pXmlTable->m_AddTile)	//添加了表头
		{
			tmp_Head->m_nExistHead = 1;
		}
	}
}

void SelTable::OnCbnSelchangeCmbName()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pSelectTable == NULL)
		return ;

	int iIndex = m_CmbName.GetCurSel();
	m_pSelectTable->m_iNameHeadCol = iIndex;
	ChangeTableInfo();
}

void SelTable::OnCbnSelchangeCmbVal()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pSelectTable == NULL)
		return ;

	int iIndex = m_CmbVal.GetCurSel();
	m_pSelectTable->m_iValueHeadCol = iIndex;
	ChangeTableInfo();
}

void SelTable::OnCbnSelchangeCmbDw()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_pSelectTable == NULL)
		return ;

	int iIndex = m_CmbDW.GetCurSel();
	m_pSelectTable->m_iDWHeadCol = iIndex - 1;
	ChangeTableInfo();
}

void SelTable::ChangeTableInfo()
{
	if(m_pSelectTable->m_strIdentify == NO_USE_TABLE)
	{
		m_pSelectTable->m_strName.Replace(_T(" *"), _T(""));
	}
	else
	{
		if(m_pSelectTable->m_strIdentify != _T("") && m_pSelectTable->m_iNameHeadCol != -1)
			m_pSelectTable->m_strName.Replace(_T(" *"), _T(""));
		else if(m_pSelectTable->m_strName.Find(_T("*")) == -1)
			m_pSelectTable->m_strName += _T(" *");
	}

	LoadTreeData();
	SaveTableConfig();

	m_strTableName = m_pSelectTable->m_strName;
	UpdateData(FALSE);
}
void SelTable::Addtile()//新增表头
{
	if(m_pSelectTable == NULL)
		return ;
	if(m_pSelectTable->m_AddTile)
		return;

	CString strHeadName,strHeadDW,strHeadVal;
	m_CmbName.GetWindowText(strHeadName);
	if(strHeadName == _T(""))
	{
		MessageDlg::MessageBox("提示", "请选择那一列属于表头名称", MessageDlg::YES);
		m_CheckHeadBtn.SetCheck(0);
		SaveTableConfig();
		return;
	}

	m_pSelectTable->m_AddTile = TRUE;
	m_CheckHeadBtn.SetCheck(m_pSelectTable->m_AddTile);

	m_CmbVal.GetWindowText(strHeadVal);
	m_CmbDW.GetWindowText(strHeadDW);

	CPdfXmlStringRow *pXmlTileRow = new CPdfXmlStringRow;
	m_pSelectTable->AddHead(pXmlTileRow);

	for(int i=1;i<m_Gird.m_nCount;i++)
	{
		CString sortmp;
		sortmp.Format("%d",i);
		CExBaseObject *tmp = new CExBaseObject;
		pXmlTileRow->AddTail(tmp);
		if(sortmp == strHeadName)
			tmp->m_strName = _T("名称");
		else if(sortmp == strHeadVal)
			tmp->m_strName = _T("定值");
		else if(sortmp == strHeadDW)
			tmp->m_strName = _T("单位");
		else
			tmp->m_strName = _T("");
	}
	UpdateDlg_Grid();
	SaveTableConfig();
}

void SelTable::Deltile()
{
	if(m_pSelectTable == NULL)
		return ;
	if(!m_pSelectTable->m_AddTile)
		return;

	m_pSelectTable->DeleteHead();
	m_pSelectTable->m_AddTile = FALSE;
	m_CheckHeadBtn.SetCheck(m_pSelectTable->m_AddTile);

	UpdateDlg_Grid();
	SaveTableConfig();
}


void SelTable::OnBnClickedRadioNouse()
{
	// TODO: 在此添加控件通知处理程序代码
	SetClickedRadio(0);
}
void SelTable::OnBnClickedRadioParameter()
{
	// TODO: 在此添加控件通知处理程序代码
	SetClickedRadio(1);
}
void SelTable::OnBnClickedRadioEna()
{
	// TODO: 在此添加控件通知处理程序代码
	SetClickedRadio(2);
}
void SelTable::OnBnClickedRadioSetting()
{
	// TODO: 在此添加控件通知处理程序代码
	SetClickedRadio(3);
}
void SelTable::OnBnClickedRadioMatrix()
{
	// TODO: 在此添加控件通知处理程序代码
	SetClickedRadio(4);
}
void SelTable::SetClickedRadio(int iRadio)
{
	if(m_pSelectTable == NULL)
		return ;

	CString strIdentify;
	switch(iRadio)
	{
	case 1:
		strIdentify = SETS_TITLE_ID_PARAMETER;
		break;
	case 2:
		strIdentify = SETS_TITLE_ID_ENA;
		break;
	case 3:
		strIdentify = SETS_TITLE_ID_SETTING;
		break;
	case 4:
		strIdentify = SETS_TITLE_ID_MATRIX;
		break;
	default:
		strIdentify = NO_USE_TABLE;
		break;
	}

	set_table_identify(m_pSelectTable, strIdentify);
	ChangeTableInfo();
}
void SelTable::ShowClickedRadio(CString strIdentify)
{
	if(m_pSelectTable == NULL)
		return;

	m_radioNoUse.SetCheck(FALSE);
	m_radioParameter.SetCheck(FALSE);
	m_radioEna.SetCheck(FALSE);
	m_radioSetting.SetCheck(FALSE);
	m_radioMatrix.SetCheck(FALSE);

	if(strIdentify == SETS_TITLE_ID_PARAMETER)
		m_radioParameter.SetCheck(TRUE);
	else if(strIdentify == SETS_TITLE_ID_ENA)
		m_radioEna.SetCheck(TRUE);
	else if(strIdentify == SETS_TITLE_ID_SETTING)
		m_radioSetting.SetCheck(TRUE);
	else if(strIdentify == SETS_TITLE_ID_MATRIX)
		m_radioMatrix.SetCheck(TRUE);
	else 
		m_radioNoUse.SetCheck(TRUE);
}

void SelTable::OnBnClickedCheckHead()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_CheckHeadBtn.GetCheck())
	{
		Addtile();
	}
	else
	{
		Deltile();
	}
}

//20240312 huangliang 关闭时，隐藏对话框
void SelTable::OnClose()
{
	ShowWindow(SW_HIDE);
	//CDialog::OnClose();
}