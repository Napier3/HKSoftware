// D:\WorkPM\Source\PMTest\Module\ItemTestUI\MyMFCTabCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "XUiTabCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyMFCTabCtrl

IMPLEMENT_DYNAMIC(CXUiTabCtrl, CMFCTabCtrl)

CXUiTabCtrl::CXUiTabCtrl()
{
	m_pMainFrame = NULL;
	m_pWndInfo = NULL;


}

CXUiTabCtrl::~CXUiTabCtrl()
{
	if (m_pWndInfo != NULL)
	{
		delete m_pWndInfo;
		m_pWndInfo = NULL;
	}

}

BEGIN_MESSAGE_MAP(CXUiTabCtrl, CMFCTabCtrl)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMyMFCTabCtrl ��Ϣ�������

int CXUiTabCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Font.CreateStockObject(DEFAULT_GUI_FONT);

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_VSCROLL 
		| ES_AUTOVSCROLL | ES_READONLY | ES_MULTILINE;

	m_pWndInfo = new CXUiOutputLog(TRUE);
	m_pWndInfo->Create(dwStyle,rectDummy,this,1002);
	AddTab(m_pWndInfo,_T("��ʾ��Ϣ"), (UINT)1);
	m_pWndInfo->SetFont(g_pGlobalFont12);
	UINT nLimit = m_pWndInfo->GetLimitText();
	nLimit *= 8;
	m_pWndInfo->SetLimitText(nLimit);
	
	return 0;
}

void CXUiTabCtrl::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CMFCTabCtrl::OnClose();
}

