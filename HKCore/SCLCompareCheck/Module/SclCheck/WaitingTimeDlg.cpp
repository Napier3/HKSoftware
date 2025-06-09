// WaitingTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
//#include "SCLCompareCheckDev.h"
#include "WaitingTimeDlg.h"

bool CWaitingTimeDlg::g_bOver = false;

// CWaitingTimeDlg 对话框

IMPLEMENT_DYNAMIC(CWaitingTimeDlg, CDialog)

CWaitingTimeDlg::CWaitingTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaitingTimeDlg::IDD, pParent)
{
	g_bOver = false;
	m_Font = NULL;
	nRecTime = 0;

	m_strMsgDesc = "正在检查Schema语法错误 , 需要等待一段时间";

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


// CWaitingTimeDlg 消息处理程序

void CWaitingTimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	nRecTime++;

	m_strText.Format("%s , 已耗时 %d s..." ,m_strMsgDesc ,nRecTime );

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
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect   rect;   
	GetClientRect(&rect);   
	CDC   dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BITMAP_WAITING);   //IDB_BITMAP是你自己的图对应的ID   ，由于我刚刚加入的位图资源 
	//被我命名成了IDB_Bg，因而我这句就是bmpBackground.LoadBitmap(IDB_Bg);  

	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);   
	dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem,0,0,   
		bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
}

HBRUSH CWaitingTimeDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
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
	m_Font->CreateFont(20,0,0,0,FW_MEDIUM,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_SWISS,"宋体");

	GetDlgItem(IDC_STATIC_WAITING)->SetFont(m_Font);
	SetTimer(1, 1000, NULL);
	OnTimer(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CWaitingTimeDlg::ChgStaticText(CStatic *cTxt, const CString sContect)  
{  
	cTxt->SetWindowText(sContect);  
	// 重绘 文本控件  
	CRect rect;  
	cTxt->GetWindowRect(&rect); // 只局部刷新  
	CWnd *pParent = cTxt->GetParent();  
	if (pParent)  
	{  
		pParent->ScreenToClient(&rect); // 把屏幕坐标转换为窗口坐标  
		pParent->InvalidateRect(&rect); // 更新矩形区域（重绘）  
	}  
} 