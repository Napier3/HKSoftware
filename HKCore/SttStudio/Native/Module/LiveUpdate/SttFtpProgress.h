#pragma once

#include "../../Module/DialogBase/DynDialogEx.h"
#include "../../Module/BaseClass/SttFileTransferProgress.h"

#define XFIDC_CTRL_PROGRESS       0X00002001

// CSttFtpProgress �Ի���

class CSttFtpProgress : public CDynDialogEx, public CSttSocketFileTransferProgress
{
//	DECLARE_DYNAMIC(CSttFtpProgress)

public:
	CSttFtpProgress(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSttFtpProgress();

	virtual void TransferStart(const CString &strFile, long nTotalSize);
	virtual void TransferStep(long nCurrSendSize);
	virtual void TransferFinish(const CString &strFile);
	virtual void TransferError(const CString &strFile,long nErrNo);

// �Ի�������
	CProgressCtrl m_prgsSttXftp;
	CString m_strTitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
