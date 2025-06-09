
// TestGridVs2008Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestGridVs2008.h"
#include "TestGridVs2008Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestGridVs2008Dlg �Ի���




CTestGridVs2008Dlg::CTestGridVs2008Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGridVs2008Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGridVs2008Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestGridVs2008Dlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CTestGridVs2008Dlg ��Ϣ�������

BOOL CTestGridVs2008Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	CreateGrid();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestGridVs2008Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestGridVs2008Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestGridVs2008Dlg::CreateGrid()
{
	CRect rcClient;
	GetClientRect(&rcClient);
	rcClient.left = 5;
	rcClient.top = 5;
	rcClient.right -= 5;
	rcClient.bottom -= 50;
	m_gridex.Create(rcClient, this, IDC_CUSTOM1+1000);
	m_gridex.InitGrid(60);
	//m_gridex.CreateTitleTip();
	m_gridex.InitData();
	m_gridex.SelectRow(4);	
}