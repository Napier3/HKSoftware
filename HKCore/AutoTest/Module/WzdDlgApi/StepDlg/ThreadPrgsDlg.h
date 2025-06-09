#pragma once

#include "../../../../Module/BaseClass/ThreadProgressInterface.h"
#include "afxcmn.h"
#include "afxwin.h"
// CThreadPrgsDlg �Ի���

class CThreadPrgsDlg : public CDialog, public CThreadProgressInterface
{
	DECLARE_DYNAMIC(CThreadPrgsDlg)

//����ʵ�ֵĽӿڲ���
public:
	virtual void SetTitle(const CString &strTitle)	;
	virtual void SetMaxRange(long nMaxRange);
	virtual void ResetProcess();
	virtual void StepIt();
	virtual void ShowMsg(const CString &strMsg) ;
	virtual void StartTimer(long nTimerLong);

	virtual void Finish(DWORD dwParam=0)	;
	virtual void StepPos(long nPos);
	virtual void Exit();

public:
	CThreadPrgsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CThreadPrgsDlg();

// �Ի�������
	enum { IDD = IDD_THREAD_PRGS_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_wndPrgs;
	CEdit m_wndInfor;

protected:
	virtual void OnOK();
	virtual void OnCancel();
};


extern CThreadProgressInterface *g_theThreadPrgsDlg;

