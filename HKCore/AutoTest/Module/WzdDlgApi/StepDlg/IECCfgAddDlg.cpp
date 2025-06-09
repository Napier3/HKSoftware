#include "stdafx.h"
#include "IECCfgAddDlg.h"

#define IECCFG_ADDTYPE_COLS 3
#define IECCFG_ADDAPP_COLS 4
#define IECCFG_ADDCHS_COLS 6

void CIECCfgAddTypeGrid::InitGrid()
{
	m_nFilter = 0;

	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_ADDTYPE_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
	SetRowsHeight(20);
}

void CIECCfgAddTypeGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_ADDTYPE_COLS]={ _T("���"), _T("װ������"), _T("װ������") };
	int iWidth[IECCFG_ADDTYPE_COLS]={50, 160, 160};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, IECCFG_ADDTYPE_COLS);
}

void CIECCfgAddTypeGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/* =TRUE */)
{
	CExBaseList* pIED = (CExBaseList*)pData;
	if(pIED->GetClassID() != SCLIECCLASSID_IED)
	{
		return;
	}

	CSclIed* pSclIed = (CSclIed*)pIED;
	//���ڱ���
	BOOL bHasProt = pSclIed->IsIed_Prot() || pSclIed->IsIed_Prot_Meas();
	bHasProt = bHasProt && (m_nFilter == 1);
	//���ڲ��
	BOOL bHasMeas = pSclIed->IsIed_Meas() || pSclIed->IsIed_Prot_Meas();
	bHasMeas = bHasMeas && (m_nFilter == 2);
	//��������
	BOOL bHasRPIT = pSclIed->IsIed_RPIT() || pSclIed->IsIed_RPIT_MU();
	bHasRPIT = bHasRPIT && (m_nFilter == 3);
	//���ںϲ�
	BOOL bHasMU = pSclIed->IsIed_MU() || pSclIed->IsIed_RPIT_MU();
	bHasMU = bHasMU && (m_nFilter == 4);
	//��������
	BOOL bHasOther = pSclIed->IsIed_Meas() || pSclIed->IsIed_MU() || pSclIed->IsIed_Prot() || pSclIed->IsIed_RPIT();
	bHasOther = !bHasOther && (m_nFilter == 5);
	
	if(m_nFilter == 0 || bHasMeas || bHasMU || bHasProt || bHasRPIT || bHasOther)
	{
		CString strIndex;
		strIndex.Format("%d", nRow);
		Show_StaticString(pData, nRow, 0, strIndex);
		Show_StaticString(pData, nRow, 1, pSclIed->m_strName);
		Show_StaticString(pData, nRow, 2, pSclIed->m_strModel);
	}
	else
	{
		return;
	}

	nRow++;
}

void CIECCfgAddAppGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(IECCFG_ADDAPP_COLS);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	InitGridTitle();
	SetRowsHeight(20);
}

void CIECCfgAddAppGrid::InitGridTitle()
{
	CString cTempStr[IECCFG_ADDAPP_COLS]={ _T("���"), _T("APPID"), _T("MAC"), _T("��ӵ����ƿ�") };
	int iWidth[IECCFG_ADDAPP_COLS]={50, 120, 180, 140};

	CExBaseListGrid::InitGridTitle(cTempStr, iWidth, IECCFG_ADDAPP_COLS);
}

void CIECCfgAddAppGrid::AddNewCtrl(CSclCtrlBase* pData)
{
	CSclIed* pIed = (CSclIed*)pData->GetAncestor(SCLIECCLASSID_IED);
	CSclCtrlBase* pScl = (CSclCtrlBase*)pData->Clone();
	pScl->SetParent(pIed);
	m_oList.AddTail(pScl);
}

void CIECCfgAddAppGrid::DeleteCtrl(CSclCtrlBase* pData)
{
	m_oList.DeleteByID(pData->m_strID);
}

BOOL CIECCfgAddAppGrid::IsCtrlExisted(CSclCtrlBase* pData)
{
	CSclCtrlBase* pScl = (CSclCtrlBase*)m_oList.FindByID(pData->m_strID);
	return pScl != NULL;
}

void CIECCfgAddAppGrid::EndEditCell_AddCtrl(int nRow, int nCol,CGridCell *pCell, CXGridCtrlBase *pGrid)
{
	if(nCol == 3 && nRow > 0)
	{
		PEXBASECELLDATA pVCellData = (PEXBASECELLDATA)pCell->lParam;
		CSclCtrlBase* pScl = (CSclCtrlBase*)pVCellData->pObj;
		if(((CIECCfgAddAppGrid*)pGrid)->IsCtrlExisted(pScl))
		{
			((CIECCfgAddAppGrid*)pGrid)->DeleteCtrl(pScl);
		}
		else
		{
			((CIECCfgAddAppGrid*)pGrid)->AddNewCtrl(pScl);
		}
	}
}

CExBaseList* CIECCfgAddAppGrid::GetAddCtrls()
{
	return &m_oList;
}

void CIECCfgAddAppGrid::RemoveAllCtrl()
{
	m_oList.RemoveAll();
}

void CIECCfgAddAppGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/* =TRUE */)
{
	CSclCtrlBase* pSclData = (CSclCtrlBase*)pData;

	CString strIndex;
	strIndex.Format("%d", nRow);
	Show_StaticString(pData, nRow, 0, strIndex);

	CString strAppID;
	if(pData->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN
		|| pData->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)
	{
		strAppID.Format("0x%04X", ((CSclCtrlSmv*)pSclData)->m_dwAppID);
	}
	else if(pData->GetClassID() == SCLIECCLASSID_CTRL_GS_IN
		||pData->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
	{
		strAppID.Format("0x%04X", ((CSclCtrlGsIn*)pSclData)->m_dwAppID);
	}
	
	Show_StaticString(pData, nRow, 1, strAppID);
	Show_StaticString(pData, nRow, 2, pSclData->m_strMac);
	
	long nCheck = 0;
	if (IsCtrlExisted(pSclData))
	{
		nCheck = 1;
	}
	Show_Check(pData, nRow, 3, &nCheck, EndEditCell_AddCtrl);

	nRow++;
}

void CIECCfgAddChsGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetFixedRowCount(1);
	SetFixedColumnCount(1);
	SetRowsHeight(20);
}

void CIECCfgAddChsGrid::InitGridTitle()
{
	if(!m_pDatas)
	{
		return;
	}

	if(m_pDatas->GetClassID() == SCLIECCLASSID_CTRL_SMV_OUT)
	{
		SetColumnCount(5);
		CString cTempStr[5] = {_T("���"),_T("LN����"),_T("DOI����"),_T("DU����"), _T("��ַ")};
		int iWidth[5] = { 60, 60, 80, 80, 80 };
		CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 5);
	}
	else if(m_pDatas->GetClassID() == SCLIECCLASSID_CTRL_SMV_IN)
	{
		SetColumnCount(11);
		CString cTempStr[11] = {_T("���"),_T("�ڲ�LN����"),_T("�ⲿLN����"), _T("�ڲ�DO����"),
			_T("�ⲿDO����"), _T("�ڲ�DU����"), _T("�ⲿDU����"), _T("�ڲ����"),_T("�ⲿ���"),_T("�ڲ�·��"),  _T("�ⲿ·��")};
		int iWidth[11] = { 50,180, 180,180,180,180,180, 50,50,180,180 };
		CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 11);
	}
	else if (m_pDatas->GetClassID() == SCLIECCLASSID_CTRL_GS_OUT)
	{
		SetColumnCount(6);
		CString cTempStr[6] = {_T("���"),_T("LN����"),_T("DOI����"),_T("DAI����"),_T("����"),_T("��ַ")};
		int iWidth[6] = { 50,180, 180,180,50,180 };
		CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 6);
	}
	else if (m_pDatas->GetClassID() == SCLIECCLASSID_CTRL_GS_IN)
	{
		SetColumnCount(13);
		CString cTempStr[13] = {_T("���"),_T("ӳ��"), _T("����"), _T("�ڲ�LN����"),_T("�ⲿLN����"), _T("�ڲ�DO����"),
			_T("�ⲿDO����"), _T("�ڲ�DU����"), _T("�ⲿDU����"), _T("�ڲ����"),_T("�ⲿ���"),_T("�ڲ�·��"),  _T("�ⲿ·��")};
		int iWidth[13] = { 50,50, 50,180,180,180, 180,180,180,50, 50,180,180 };
		CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 13);
	}
	else
	{
		SetColumnCount(1);
		CString cTempStr[1] = {_T("���")};
		int iWidth[1] = { 60 };
		CExBaseListGrid::InitGridTitle(cTempStr, iWidth, 1);
	}
}

void CIECCfgAddChsGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow/* =TRUE */)
{
	UINT nClassID = pData->GetClassID();

	switch (nClassID)
	{
	case SCLIECCLASSID_CH_SMV_OUT:
		ShowData_SMVOutputChn((CSclChSmvOut*)pData, nRow);
		break;

	case SCLIECCLASSID_CH_SMV_IN:
		ShowData_SMVInputChn((CSclChSmvIn*)pData, nRow);
		break;

	case SCLIECCLASSID_CH_GS_OUT:
		ShowData_GooseOutputChn((CSclChGsOut*)pData, nRow);
		break;

	case SCLIECCLASSID_CH_GS_IN:
		ShowData_GooseInputChn((CSclChGsIn*)pData, nRow);
		break;
	}
	
	nRow++;
}

void CIECCfgAddChsGrid::ShowData_GooseInputChn(CSclChGsIn *pChn,int nRow)
{
	//_T("���")
	Show_Index(pChn, nRow, 0);

	//_T("ӳ��")
	Show_StaticString(pChn, nRow, 1, &pChn->fcda_map);

	// _T("����")
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_type);

	// _T("�ڲ�LN����")
	Show_StaticString(pChn, nRow, 3, &pChn->inLNDesc);

	//_T("�ⲿLN����")
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_lndesc);

	// _T("�ڲ�DO����")
	Show_StaticString(pChn, nRow, 5, &pChn->inDODesc);

	//_T("�ⲿDO����")
	Show_StaticString(pChn, nRow, 6, &pChn->fcda_dodesc);

	// _T("�ڲ�DU����")
	Show_StaticString(pChn, nRow, 7, &pChn->inDADesc);

	// _T("�ⲿDU����")
	Show_StaticString(pChn, nRow, 8, &pChn->fcda_desc);

	// _T("�ڲ����")
	Show_Long(pChn, nRow, 9, &pChn->inIndex, FALSE);

	//_T("�ⲿ���")
	Show_Long(pChn, nRow, 10, &pChn->outIndex, FALSE);

	//_T("�ڲ�·��")
	Show_StaticString(pChn, nRow, 11, &pChn->inPath);

	// _T("�ⲿ·��")
	Show_StaticString(pChn, nRow, 12, &pChn->fcda_name);
}

void CIECCfgAddChsGrid::ShowData_GooseOutputChn(CSclChGsOut *pChn,int nRow)
{
	// ���
	Show_Index(pChn, nRow, 0);

	// LN����
	Show_StaticString(pChn, nRow, 1, &pChn->fcda_lndesc);

	// DOI����
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_dodesc);

	// DAI����
	Show_StaticString(pChn, nRow, 3, &pChn->fcda_desc);

	// ����
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_type);

	// ��ַ
	Show_StaticString(pChn, nRow, 5, &pChn->fcda_name);
}

void CIECCfgAddChsGrid::ShowData_SMVInputChn(CSclChSmvIn *pChn,int nRow)
{
	//_T("���")
	Show_Index(pChn, nRow, 0);

	// _T("�ڲ�LN����")
	Show_StaticString(pChn, nRow, 1, &pChn->inLNDesc);

	//_T("�ⲿLN����")
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_lndesc);

	// _T("�ڲ�DO����")
	Show_StaticString(pChn, nRow, 3, &pChn->inDODesc);

	//_T("�ⲿDO����")
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_dodesc);

	// _T("�ڲ�DU����")
	Show_StaticString(pChn, nRow, 5, &pChn->inDADesc);

	// _T("�ⲿDU����")
	Show_StaticString(pChn, nRow, 6, &pChn->fcda_desc);

	// _T("�ڲ����")
	Show_Long(pChn, nRow, 7, &pChn->inIndex, FALSE);

	//_T("�ⲿ���")
	Show_Long(pChn, nRow, 8, &pChn->outIndex, FALSE);

	//_T("�ڲ�·��")
	Show_StaticString(pChn, nRow, 9, &pChn->inPath);

	// _T("�ⲿ·��")
	Show_StaticString(pChn, nRow, 10, &pChn->fcda_name);
}

void CIECCfgAddChsGrid::ShowData_SMVOutputChn(CSclChSmvOut *pChn,int nRow)
{
	// ���
	Show_Index(pChn, nRow, 0);

	// LN����
	Show_StaticString(pChn, nRow, 1, &pChn->fcda_lndesc);

	// DOI����
	Show_StaticString(pChn, nRow, 2, &pChn->fcda_dodesc);

	// DU����
	Show_StaticString(pChn, nRow, 3, &pChn->fcda_desc);

	// ��ַ
	Show_StaticString(pChn, nRow, 4, &pChn->fcda_name);
}


IMPLEMENT_DYNAMIC(CIECCfgAddDlg, CDialog)
BEGIN_MESSAGE_MAP(CIECCfgAddDlg, CDialog)

	ON_BN_CLICKED(IDC_ADDDLG_TYPE1, &CIECCfgAddDlg::OnBnClickedAdddlgType1)
	ON_BN_CLICKED(IDC_ADDDLG_TYPE2, &CIECCfgAddDlg::OnBnClickedAdddlgType2)
	ON_BN_CLICKED(IDC_ADDDLG_TYPE3, &CIECCfgAddDlg::OnBnClickedAdddlgType3)
	ON_BN_CLICKED(IDC_ADDDLG_TYPE4, &CIECCfgAddDlg::OnBnClickedAdddlgType4)
	ON_BN_CLICKED(IDC_ADDDLG_OTHER, &CIECCfgAddDlg::OnBnClickedAdddlgOther)
	ON_NOTIFY(TCN_SELCHANGE, IDC_ADDDLG_TAB, &CIECCfgAddDlg::OnTcnSelchangeAdddlgTab)
	ON_BN_CLICKED(IDC_ADDDLG_FIND, &CIECCfgAddDlg::OnBnClickedAdddlgFind)
	ON_BN_CLICKED(IDCANCEL, &CIECCfgAddDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CIECCfgAddDlg::OnBnClickedOk)
END_MESSAGE_MAP()

CIECCfgAddDlg::CIECCfgAddDlg(CWnd* pParent /*=NULL*/)
: CDialog(CIECCfgAddDlg::IDD, pParent)
{
	m_pListApp = NULL;
	m_pSclStation = NULL;
}

CIECCfgAddDlg::~CIECCfgAddDlg()
{

};

void CIECCfgAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDDLG_STATIC, m_txtListType);
	DDX_Control(pDX, IDC_ADDDLG_LIST, m_gridList);
	DDX_Control(pDX, IDC_ADDDLG_APP, m_gridApp);
	DDX_Control(pDX, IDC_ADDDLG_CHS, m_gridChs);
	DDX_Control(pDX, IDC_ADDDLG_TYPE1, m_btnPro);
	DDX_Control(pDX, IDC_ADDDLG_TYPE2, m_btnTest);
	DDX_Control(pDX, IDC_ADDDLG_TYPE3, m_btnSmart);
	DDX_Control(pDX, IDC_ADDDLG_TYPE4, m_btnUnion);
	DDX_Control(pDX, IDC_ADDDLG_OTHER, m_btnOther);
	DDX_Control(pDX, IDC_ADDDLG_EDIT, m_editFind);
	DDX_Control(pDX, IDC_ADDDLG_FIND, m_btnFind);
	DDX_Control(pDX, IDC_ADDDLG_TAB, m_tabAdd);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_ADDDLG_BK, m_btnBk);
}

BOOL CIECCfgAddDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridList.InitGrid();
	m_gridList.AttachDataViewOptrInterface(this);
	m_gridApp.InitGrid();
	m_gridApp.AttachDataViewOptrInterface(this);
	m_gridChs.InitGrid();
	m_gridChs.AttachDataViewOptrInterface(this);

	m_tabAdd.InsertItem(0, "SMV����");
	m_tabAdd.InsertItem(1, "GOOSE����");
	m_tabAdd.InsertItem(2, "GOOSE����");

	if(m_pSclStation)
	{
		m_gridList.ShowDatas(m_pSclStation);
	}

	CString strIcon = _P_GetResourcePath();
	strIcon += "iSmartTestWzd/";
	m_txtListType.SetImgMode(TRUE);
	m_txtListType.LoadImage(strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png");
	m_txtListType.SetTxtColor(RGB(255, 255, 255));
	//m_btnBk.SetImgMode(TRUE);
	//m_btnBk.LoadImage(strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png", strIcon + "bk.png");

	return TRUE;
}

void CIECCfgAddDlg::Init(CSclStation* pSclStation)
{
	m_pSclStation = pSclStation;
}

void CIECCfgAddDlg::SetAllTypeBtnDefault()
{
	m_gridList.m_nFilter = 0;
	m_gridList.SetRowCount(1);
}

void CIECCfgAddDlg::OnBnClickedAdddlgType1()
{
	SetAllTypeBtnDefault();
	m_gridList.m_nFilter = 1;
	m_gridList.ShowDatas(m_gridList.GetGridData());
	m_gridApp.SetRowCount(1);
	m_gridChs.SetRowCount(1);
}

void CIECCfgAddDlg::OnBnClickedAdddlgType2()
{
	SetAllTypeBtnDefault();
	m_gridList.m_nFilter = 2;
	m_gridList.ShowDatas(m_gridList.GetGridData());
	m_gridApp.SetRowCount(1);
	m_gridChs.SetRowCount(1);
}

void CIECCfgAddDlg::OnBnClickedAdddlgType3()
{
	SetAllTypeBtnDefault();
	m_gridList.m_nFilter = 3;
	m_gridList.ShowDatas(m_gridList.GetGridData());
	m_gridApp.SetRowCount(1);
	m_gridChs.SetRowCount(1);
}

void CIECCfgAddDlg::OnBnClickedAdddlgType4()
{
	SetAllTypeBtnDefault();
	m_gridList.m_nFilter = 4;
	m_gridList.ShowDatas(m_gridList.GetGridData());
	m_gridApp.SetRowCount(1);
	m_gridChs.SetRowCount(1);
}

void CIECCfgAddDlg::OnBnClickedAdddlgOther()
{
	SetAllTypeBtnDefault();
	m_gridList.m_nFilter = 5;
	m_gridList.ShowDatas(m_gridList.GetGridData());
	m_gridApp.SetRowCount(1);
	m_gridChs.SetRowCount(1);
}

void CIECCfgAddDlg::Attach(CExBaseList* pList)
{
	m_pListApp = pList;
}

void CIECCfgAddDlg::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if(nRow <= 0 || nCol <= 0)
	{
		return;
	}

	CSclIed* pSclIed = (CSclIed*)m_gridList.GetCurrSelData();
	if(!pSclIed)
	{
		return;
	}

	if(pGridCtrl->GetGridClassID() == "CIECCfgAddTypeGrid")
	{
		m_gridApp.ShowDatas(pSclIed->GetSmvIns());
		CSclCtrlSmv* pCtrls = (CSclCtrlSmvIn*)pSclIed->GetSmvIns()->GetHead();
		if(pCtrls)
		{
			m_gridChs.AttachDatas(pCtrls);
			m_gridChs.InitGridTitle();
			m_gridChs.ShowDatas(pCtrls);//��ShowDatas������UpdateDatas����ΪUpdate��û�е���SetRowsHeight,�߶Ȼᱻ�ı�
		}
		else
		{
			m_gridChs.SetRowCount(1);
			m_gridChs.SetColumnCount(1);
		}
		m_tabAdd.SetCurSel(0);
	}
	else if(pGridCtrl->GetGridClassID() == "CIECCfgAddAppGrid")
	{
		//�л�ѡ��
		long nIndex = m_tabAdd.GetCurSel();
		switch(nIndex)
		{
		case 0:
			m_gridChs.ShowDatas((CExBaseList*)pSclIed->GetSmvIns()->GetAt((long)nRow - 1));
			break;
		case 1:
			m_gridChs.ShowDatas((CExBaseList*)pSclIed->GetGsIns()->GetAt((long)nRow - 1));
			break;
		case 2:
			m_gridChs.ShowDatas((CExBaseList*)pSclIed->GetGsOuts()->GetAt((long)nRow - 1));
			break;
		default:
			break;
		}
	}
}
void CIECCfgAddDlg::OnTcnSelchangeAdddlgTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	CSclIed* pSclIed = (CSclIed*)m_gridList.GetCurrSelData();
	if(!pSclIed)
	{
		return;
	}

	long nIndex = m_tabAdd.GetCurSel();
	switch(nIndex)
	{
	case 0:
		m_gridApp.ShowDatas(pSclIed->GetSmvIns());
		m_gridChs.AttachDatas((CExBaseList*)pSclIed->GetSmvIns()->GetHead());
		m_gridChs.InitGridTitle();
		m_gridChs.ShowDatas((CExBaseList*)pSclIed->GetSmvIns()->GetHead());
		break;
	case 1:
		m_gridApp.ShowDatas(pSclIed->GetGsIns());
		m_gridChs.AttachDatas((CExBaseList*)pSclIed->GetGsIns()->GetHead());
		m_gridChs.InitGridTitle();
		m_gridChs.ShowDatas((CExBaseList*)pSclIed->GetGsIns()->GetHead());
		break;
	case 2:
		m_gridApp.ShowDatas(pSclIed->GetGsOuts());
		m_gridChs.AttachDatas((CExBaseList*)pSclIed->GetGsOuts()->GetHead());
		m_gridChs.InitGridTitle();
		m_gridChs.ShowDatas((CExBaseList*)pSclIed->GetGsOuts()->GetHead());
		break;
	default:
		break;
	}

	*pResult = 0;
}

void CIECCfgAddDlg::OnBnClickedAdddlgFind()
{
	CString m_strText;
	m_editFind.GetWindowText(m_strText);


}

void CIECCfgAddDlg::OnBnClickedCancel()
{
	m_gridApp.RemoveAllCtrl();
	CDialog::OnCancel();
}

void CIECCfgAddDlg::OnBnClickedOk()
{
	m_pListApp->Append(m_gridApp.GetAddCtrls());
	m_gridApp.RemoveAllCtrl();
	CDialog::OnOK();
}
