// CharElementInvI2TDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CharLibDev.h"
#include "CharElementInvOwnDefDlg.h"
#include "..\..\Module\api\GloblaDrawFunctions.h"

#include "DlgAddPoint.h"


// CCharElementInvOwnDefDlg 对话框

IMPLEMENT_DYNAMIC(CCharElementInvOwnDefDlg, CDialog)

CCharElementInvOwnDefDlg::CCharElementInvOwnDefDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCharElementInvOwnDefDlg::IDD, pParent)
	, m_strXMAX(_T(""))
	, m_strTMAX(_T(""))
{

}

CCharElementInvOwnDefDlg::~CCharElementInvOwnDefDlg()
{
}

void CCharElementInvOwnDefDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IOWNDEF_XMAX, m_strXMAX);
	DDX_Text(pDX, IDC_IOWNDEF_TMAX, m_strTMAX);
	DDX_Control(pDX, IDC_INVOWNDEF_GRID, m_gridInvOwnDef);
	DDX_Control(pDX, IDC_INVOWNDEF_DELPOINT, m_btnInvOwnDefDel);
	DDX_Control(pDX, IDC_INVOWNDEF_DELALLPOINT, m_btnInvOwnDefDelAll);
	DDX_Control(pDX, IDC_INVOWNDEF_ADDPOINTPREV, m_btnInvOwnDefAddPrev);
	DDX_Control(pDX, IDC_INVOWNDEF_ADDPOINTAFTER, m_btnInvOwnDefAddAfter);
}


BEGIN_MESSAGE_MAP(CCharElementInvOwnDefDlg, CDialog)
	ON_BN_CLICKED(IDC_INVOWNDEF_ADDPOINT, &CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpoint)
	ON_BN_CLICKED(IDC_INVOWNDEF_DELPOINT, &CCharElementInvOwnDefDlg::OnBnClickedInvowndefDelpoint)
	ON_BN_CLICKED(IDC_INVOWNDEF_DELALLPOINT, &CCharElementInvOwnDefDlg::OnBnClickedInvowndefDelallpoint)
	ON_BN_CLICKED(IDC_INVOWNDEF_ADDPOINTHEAD, &CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpointhead)
	ON_BN_CLICKED(IDC_INVOWNDEF_ADDPOINTPREV, &CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpointprev)
	ON_BN_CLICKED(IDC_INVOWNDEF_ADDPOINTAFTER, &CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpointafter)
END_MESSAGE_MAP()

BOOL CCharElementInvOwnDefDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_gridInvOwnDef.SetFont(g_pGlobalFont11);
	m_gridInvOwnDef.InitGrid();
	m_gridInvOwnDef.AttachDataViewOptrInterface(this);

	EnableButtons();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// CCharElementInvOwnDefDlg 消息处理程序
void CCharElementInvOwnDefDlg::CreateDlg(CWnd *pParent)
{	
	Create(IDD, pParent);
	m_pDialog = this;
}

void CCharElementInvOwnDefDlg::ShowData()
{
	CCharElementInvOwnDef * pCharData= (CCharElementInvOwnDef *) m_pCharElementBase;

	m_strXMAX = pCharData->m_strXmax;
	m_strTMAX = pCharData->m_strTmax;
	
	m_oPoints.DeleteAll();
	m_oPoints.AppendClone(pCharData->m_oPoints);

	m_gridInvOwnDef.ShowDatas(&m_oPoints);

	UpdateData(FALSE);
}

void CCharElementInvOwnDefDlg::GetData()
{
	CCharElementInvOwnDef * pCharData= (CCharElementInvOwnDef *) m_pCharElementBase;
	UpdateData(TRUE);

	pCharData->m_strXmax = m_strXMAX;
	pCharData->m_strTmax = m_strTMAX;

	(pCharData->m_oPoints).DeleteAll();
	(pCharData->m_oPoints).AppendClone(m_oPoints);
}

BOOL CCharElementInvOwnDefDlg::IsEnable()
{
 	if (m_strXMAX.IsEmpty())
 	{
 		return FALSE;
 	}
 
 	if (m_strTMAX.IsEmpty())
 	{
 		return FALSE;
 	}

	return TRUE;
}

void CCharElementInvOwnDefDlg::EnableButtons()
{
	CExBaseObject *pSelPoint = m_gridInvOwnDef.GetCurrSelData();
	if(pSelPoint == NULL)
	{
		m_btnInvOwnDefDel.EnableWindow(FALSE);
		m_btnInvOwnDefAddPrev.EnableWindow(FALSE);
		m_btnInvOwnDefAddAfter.EnableWindow(FALSE);
	}
	else
	{
		m_btnInvOwnDefDel.EnableWindow(TRUE);
		m_btnInvOwnDefAddPrev.EnableWindow(TRUE);
		m_btnInvOwnDefAddAfter.EnableWindow(TRUE);
	}

	m_btnInvOwnDefDelAll.EnableWindow(TRUE);
}

void CCharElementInvOwnDefDlg::OnDataSelChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if(pGridCtrl == &m_gridInvOwnDef)
	{
		EnableButtons();
	}
}

void CCharElementInvOwnDefDlg::OnDataEditChanged(CXGridCtrlBase *pGridCtrl, int nRow, int nCol)
{
	if (pGridCtrl == &m_gridInvOwnDef)
	{
		CCharElementPoint *pSelPoint = (CCharElementPoint*)(m_gridInvOwnDef.GetCurrSelData());
		ASSERT(pSelPoint != NULL);

		(pSelPoint->m_strX).Format(_T("%lf"), pSelPoint->m_fX);
		(pSelPoint->m_strY).Format(_T("%lf"), pSelPoint->m_fY);

		//UpdateData(FALSE);
	}
}

void CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpoint() //添加末尾
{
	// TODO: 在此添加控件通知处理程序代码

	CDlgAddPoint dlg;
	if(dlg.DoModal() == IDOK)
	{
		//if(m_oPoints.FindObj(dlg.m_pPoint) == NULL)
		//{
		m_oPoints.AddNewChild(dlg.m_pPoint);
		m_gridInvOwnDef.ShowDatas(&m_oPoints);
		//UpdateData(FALSE);
		//}
	}

	EnableButtons();
}

void CCharElementInvOwnDefDlg::OnBnClickedInvowndefDelpoint() //删除选中点
{
	// TODO: 在此添加控件通知处理程序代码
	CExBaseObject *pSelPoint = m_gridInvOwnDef.GetCurrSelData();
	ASSERT(pSelPoint != NULL);

	m_oPoints.Delete(pSelPoint);

	m_gridInvOwnDef.ShowDatas(&m_oPoints);
	/*UpdateData(FALSE);*/

	EnableButtons();
}

void CCharElementInvOwnDefDlg::OnBnClickedInvowndefDelallpoint() //删除所有点
{
	// TODO: 在此添加控件通知处理程序代码
	m_oPoints.DeleteAll();

	m_gridInvOwnDef.ShowDatas(&m_oPoints);
	/*UpdateData(FALSE);*/

	EnableButtons();
}

void CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpointhead() //添加开头
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgAddPoint dlg;
	if(dlg.DoModal() == IDOK)
	{
		//if(m_oPoints.FindObj(dlg.m_pPoint) == NULL)
		//{
		m_oPoints.AddHead(dlg.m_pPoint);
		m_gridInvOwnDef.ShowDatas(&m_oPoints);
		//UpdateData(FALSE);
		//}
	}

	EnableButtons();
}

void CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpointprev() //添加选中节点前一个位置
{
	CExBaseObject *pSelPoint = m_gridInvOwnDef.GetCurrSelData();
	ASSERT(pSelPoint != NULL);

	// TODO: 在此添加控件通知处理程序代码
	CDlgAddPoint dlg;
	if(dlg.DoModal() == IDOK)
	{
		//if(m_oPoints.FindObj(dlg.m_pPoint) == NULL)
		//{
		m_oPoints.InsertBefore(m_oPoints.GetPos((CCharElementPoint*)pSelPoint),dlg.m_pPoint);
		m_gridInvOwnDef.ShowDatas(&m_oPoints);
		//UpdateData(FALSE);
		//}
	}

	EnableButtons();
}

void CCharElementInvOwnDefDlg::OnBnClickedInvowndefAddpointafter() //添加选中节点后一个位置
{
	// TODO: 在此添加控件通知处理程序代码
	CExBaseObject *pSelPoint = m_gridInvOwnDef.GetCurrSelData();
	ASSERT(pSelPoint != NULL);

	// TODO: 在此添加控件通知处理程序代码
	CDlgAddPoint dlg;
	if(dlg.DoModal() == IDOK)
	{
		//if(m_oPoints.FindObj(dlg.m_pPoint) == NULL)
		//{
		m_oPoints.InsertAfter(m_oPoints.GetPos((CCharElementPoint*)pSelPoint),dlg.m_pPoint);
		m_gridInvOwnDef.ShowDatas(&m_oPoints);
		//UpdateData(FALSE);
		//}
	}

	EnableButtons();
}
