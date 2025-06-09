// Wzd_FailItemAdviseDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "iSmartTestWzd.h"
#include "Wzd_FailItemAdviseDlg.h"


// CWzd_FailItemAdviseDlg �Ի���

IMPLEMENT_DYNAMIC(CWzd_FailItemAdviseDlg, CDialog)

CWzd_FailItemAdviseDlg::CWzd_FailItemAdviseDlg(CWnd* pParent /*=NULL*/)
	: CUIDialog(CWzd_FailItemAdviseDlg::IDD, pParent)
{
	m_strAdvise = "";
}

CWzd_FailItemAdviseDlg::~CWzd_FailItemAdviseDlg()
{
}

void CWzd_FailItemAdviseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_INFO_STATIC, m_txtAdvise);
}


BEGIN_MESSAGE_MAP(CWzd_FailItemAdviseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CWzd_FailItemAdviseDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CWzd_FailItemAdviseDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CWzd_FailItemAdviseDlg ��Ϣ�������
void CWzd_FailItemAdviseDlg::InitFailItemAdvise(CString strAdvise)
{
	m_strAdvise = strAdvise;
	if(m_strAdvise == "")
	{
		m_strAdvise = _T("��ʱû�н���");
	}
	GetDlgItem(IDC_INFO_STATIC)->SetWindowText(m_strAdvise);

	m_btnOK.InitUI("normalȷ��.png", "hoverȷ��.png");
	m_btnCancel.InitUI("normalȡ��.png", "hoverȡ��.png");
}

void CWzd_FailItemAdviseDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnOK();
}

void CWzd_FailItemAdviseDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	OnCancel();
}
