// WaitingTimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "SCLCompareCheckDev.h"
#include "WaitingTimeDlg.h"

bool CWaitingTimeDlg::g_bOver = false;

// CWaitingTimeDlg �Ի���

IMPLEMENT_DYNAMIC(CWaitingTimeDlg, CDialog)

CWaitingTimeDlg::CWaitingTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitingTimeDlg::IDD, pParent)
{
	g_bOver = false;
	m_Font = NULL;
	nRecTime = 0;

	m_strMsgDesc = "���ڼ��Schema�﷨���� , ��Ҫ�ȴ�һ��ʱ��";

}

CWaitingTimeDlg::~CWaitingTimeDlg()
{
	if (m_Font != NULL)
	{
		delete m_Font;
	}
}

void CWaitingTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_STATIC_WAITING, m_staText);
}


BEGIN_MESSAGE_MAP(CWaitingTimeDlg, CDialog)
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CWaitingTimeDlg ��Ϣ�������

void CWaitingTimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	nRecTime++;

	m_strText.Format("%s , �Ѻ�ʱ %d s..." ,m_strMsgDesc ,nRecTime );

	SetDlgItemText(IDC_STATIC_WAITING,m_strText);

	ChgStaticText(&m_staText ,m_strText);

	if (g_bOver)
	{
		KillTimer(nIDEvent);
		CDialog::OnOK();

		Sleep(100);
	}
}

void CWaitingTimeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	CRect   rect;   
	GetClientRect(&rect);   
	CDC   dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BITMAP_WAITING);   //IDB_BITMAP�����Լ���ͼ��Ӧ��ID   �������Ҹոռ����λͼ��Դ 
	//������������IDB_Bg�������������bmpBackground.LoadBitmap(IDB_Bg);  

	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
}

HBRUSH CWaitingTimeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	if(pWnd->GetDlgCtrlID( ) == (IDC_STATIC_WAITING))
	{
		pDC->SetBkMode(TRANSPARENT);
		pDC->SetTextColor(RGB(255,0,255));
		return HBRUSH(GetStockObject(HOLLOW_BRUSH));
	}
	return hbr;
}

BOOL CWaitingTimeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Font = new CFont; 
	m_Font->CreateFont(20,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"����");

	GetDlgItem(IDC_STATIC_WAITING)->SetFont(m_Font);
	SetTimer(1, 1000, NULL);
	OnTimer(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CWaitingTimeDlg::ChgStaticText(CStatic *cTxt, const CString sContect)  
{  
	cTxt->SetWindowText(sContect);  
	// �ػ� �ı��ؼ�  
	CRect rect;  
	cTxt->GetWindowRect(&rect); // ֻ�ֲ�ˢ��  
	CWnd *pParent = cTxt->GetParent();  
	if (pParent)  
	{  
		pParent->ScreenToClient(&rect); // ����Ļ����ת��Ϊ��������  
		pParent->InvalidateRect(&rect); // ���¾��������ػ棩  
	}  
} 