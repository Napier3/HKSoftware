// Wzd_ConfigSetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_ConfigSetDlg.h"

CConfigSetGrid::CConfigSetGrid(void)
{
}

CConfigSetGrid::~CConfigSetGrid(void)
{
}

void CConfigSetGrid::InitGrid()
{
	SetListMode(TRUE);
	SetRowCount(1);
	SetColumnCount(3);
	SetFixedRowCount(1);
	SetFixedColumnCount(0);
	InitGridTitle();
}

void CConfigSetGrid::InitGridTitle()
{
	CString astrGridTitle[3] = {_T("����"),_T("ֵ"), _T("��λ")};
	int iGridWidth[3]={150,150,150};
	CExBaseListGrid::InitGridTitle(astrGridTitle, iGridWidth, 3);
}
void CConfigSetGrid::ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow)
{
	CDataObj *pDataObj = (CDataObj *)pData;
	Show_StaticString(pDataObj, nRow, 0, &pDataObj->m_strName);	
	Show_String(pDataObj, nRow, 1, &pDataObj->m_strValue,EndEditCell_String);
	Show_StaticString(pDataObj, nRow, 2, &pDataObj->m_strUnit);

	nRow++;
}

// CWzd_ConfigSetDlg �Ի���

IMPLEMENT_DYNAMIC(CWzd_ConfigSetDlg, CDialog)

CWzd_ConfigSetDlg::CWzd_ConfigSetDlg(CWnd* pParent /*=NULL*/)
	: CUIDialog(CWzd_ConfigSetDlg::IDD, pParent)
{
	m_pDatas = NULL;
	m_pGridDatas = NULL;
	m_strTestParas = "";
}

CWzd_ConfigSetDlg::~CWzd_ConfigSetDlg()
{
}

void CWzd_ConfigSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
}


BEGIN_MESSAGE_MAP(CWzd_ConfigSetDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWzd_ConfigSetDlg::OnBnClickedOk)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CWzd_ConfigSetDlg ��Ϣ�������
BOOL CWzd_ConfigSetDlg::OnInitDialog()
{
	CUIDialog::OnInitDialog();

	CRect rc;
	GetClientRect(rc);
	m_ConfigSetGrid.Create(CRect(5,5,rc.Width() - 10,240),this,XIDC_SET_GRID);
	m_ConfigSetGrid.UseImage(FALSE, COLOR_LIGHTGREEN);
	m_ConfigSetGrid.InitGrid();
	m_ConfigSetGrid.ShowDatas(m_pGridDatas);

	m_btnOK.InitUI("normalȷ��.png", "hoverȷ��.png");
	m_btnCancel.InitUI("normalȡ��.png", "hoverȡ��.png");

	InitUI(COLOR_LIGHTGREEN, COLOR_DEEPBLUE);
	SetWindowTitle("ϵͳ��������");

	MoveChildWindow(&m_btnOK);
	MoveChildWindow(&m_btnCancel);
	MoveChildWindow(&m_ConfigSetGrid);

	return TRUE; 
}
//�����е��ȷ���󣬽�����ת��XML�ı�����ʽΪ��
	/*
	<group name="" id="Paras">  //ID�̶�
		<data name="����1" id="Para1" value="0.25" />
		<data name="����2" id="Para2" value="0.25999999" />
		<data name="����3" id="Para3" value="0.75" />
		����
	</group>
	*/
void CWzd_ConfigSetDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int ncount = 1;
	CDataGroup savexml;
	savexml.m_strID = "Paras";
	POS pos = m_pGridDatas->GetHeadPosition();//����ȡ���򲻱����޸�����
	while(pos != NULL)
	{
		CString strID;
		strID.Format("%s%d",savexml.m_strID,ncount);
		ncount++;
		CDataObj *pGridData = (CDataObj *)m_pGridDatas->GetNext(pos);
		savexml.AddNewData(pGridData->m_strName,strID,"",pGridData->m_strValue);
		if(m_pDatas == NULL)
			continue;
		CDataObj*pData = (CDataObj *)m_pDatas->FindByID(pGridData->m_strID);
		pData->m_strValue = pGridData->m_strValue;
	}
	m_strTestParas = (CString)savexml.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);//������ϵͳ������Ϣת����xml��ʽ
	OnOK();
}

void CWzd_ConfigSetDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
}
void CWzd_ConfigSetDlg::SetGridData(CExBaseList *pDatas)
{
	if(pDatas == NULL)
	{
		return;
	}
	m_pDatas = pDatas;
	m_pGridDatas = (CExBaseList *)pDatas->Clone();
}
