// WzdDlgSendState.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "WzdDlgSendState.h"


// CWzdDlgSendState �Ի���

IMPLEMENT_DYNAMIC(CWzdDlgSendState, CDialog)

CWzdDlgSendState::CWzdDlgSendState(CWnd* pParent /*=NULL*/)
	: CDialog(CWzdDlgSendState::IDD, pParent)
{
	m_iModal = DLG_TYPE_NONE;
}

CWzdDlgSendState::~CWzdDlgSendState()
{
}

void CWzdDlgSendState::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgressCtrl);
	DDX_Control(pDX, IDC_STATIC_TIME, m_strTime);
}


BEGIN_MESSAGE_MAP(CWzdDlgSendState, CDialog)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_MESSAGE(WM_SET_MAX_RANG, &CWzdDlgSendState::OnReSetRang)
	ON_MESSAGE(WM_ADD_RANG, &CWzdDlgSendState::OnStepIt)
END_MESSAGE_MAP()


// CWzdDlgSendState ��Ϣ�������
BOOL CWzdDlgSendState::PreTranslateMessage(MSG* pMsg)
{
    if (pMsg->message == WM_KEYDOWN)
    {
        switch (pMsg->wParam)
        {
        case VK_RETURN: //���λس���
            return TRUE;
        case VK_ESCAPE: //����ESC��
            return TRUE;     
        default:
            break;
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}

void CWzdDlgSendState::OnTimer(UINT_PTR nIDEvent)
{
	if(nIDEvent == SENDSTATE_TIMER_ID)
	{
		m_iTimeCount++;

		CString strTime;
		strTime.Format("%ds", m_iTimeCount);
		if(m_strTime.m_hWnd != NULL)
			m_strTime.SetWindowText(strTime);
	}

	__super::OnTimer(nIDEvent);
}

void CWzdDlgSendState::SetModal()
{
	m_iModal = DLG_TYPE_MODAL;
}
void CWzdDlgSendState::ShowStart(const CString &strWinName)
{
	if(m_hWnd == NULL || m_iModal != DLG_TYPE_MODAL)
		return ;

	ShowMsg(strWinName);
	SetWindowText(strWinName);
	m_iTimeCount = 0;
	SetTimer(SENDSTATE_TIMER_ID, 1000, NULL);
}
void CWzdDlgSendState::SetTitle(const CString &strWinName)
{
	if(m_hWnd == NULL)
		return ;

	m_iModal = DLG_TYPE_NOMORL;
	ShowMsg(strWinName);
	SetWindowText(strWinName);

	m_iTimeCount = 0;
	SetTimer(SENDSTATE_TIMER_ID, 1000, NULL);

	CenterWindow();
	ShowWindow(SW_SHOW);
}

void CWzdDlgSendState::Finish(DWORD dwParam)
{
	KillTimer(SENDSTATE_TIMER_ID);

	switch(m_iModal)
	{
	case DLG_TYPE_NONE:
		break ;
	case DLG_TYPE_MODAL:	
		m_iModal = DLG_TYPE_NONE;	//��ģ̬�Ի�����Ҫȥ�ر�
		SendMessage(WM_CLOSE, 0, 0);
		break;
	case DLG_TYPE_NOMORL:
		ShowWindow(SW_HIDE);
		break;
	}
}
void CWzdDlgSendState::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch(m_iModal)
	{
	case DLG_TYPE_NONE:
		CDialog::OnClose();
		break ;
	case DLG_TYPE_MODAL:
		break;
	case DLG_TYPE_NOMORL:
		ShowWindow(SW_HIDE);
		break;
	}	
}

void CWzdDlgSendState::ShowMsg(const CString &sWord)
{
	m_strShowWord = sWord;
}

LRESULT CWzdDlgSendState::OnReSetRang(WPARAM wPara,LPARAM lPara)
{
	m_nMaxRange = (int)lPara;
	m_nOneStepIndex = 0;
	m_ProgressCtrl.SetRange32(0, m_nMaxRange);
	m_ProgressCtrl.SetPos(m_nOneStepIndex);
	m_ProgressCtrl.SetStep(1);
	return 0;
}
LRESULT CWzdDlgSendState::OnStepIt(WPARAM wPara,LPARAM lPara)
{
	m_nOneStepIndex++;
	if(m_nOneStepIndex >= m_nMaxRange)
		m_nOneStepIndex = m_nMaxRange;

	m_ProgressCtrl.SetPos(m_nOneStepIndex);

	if(m_strShowWord.Find(" / ") != -1)//�ⲿ�Ѿ�������%d / %d��ֱ��ʹ��
	{
		SetWindowText(m_strShowWord);
		return 0;
	}

	CString sTile;
	sTile.Format("%d / %d  %s", m_nOneStepIndex, m_nMaxRange, m_strShowWord);
	SetWindowText(sTile);
	return 0;
}

void CWzdDlgSendState::SetMaxRange(long iMaxR)
{
	if(m_hWnd == NULL || m_iModal == DLG_TYPE_NONE)
		return ;
	this->SendMessage(WM_SET_MAX_RANG, 0, (LPARAM)iMaxR);
}
void CWzdDlgSendState::StepIt()
{
	if(m_hWnd == NULL || m_iModal == DLG_TYPE_NONE)
		return ;
	this->SendMessage(WM_ADD_RANG, 0, 0);
}