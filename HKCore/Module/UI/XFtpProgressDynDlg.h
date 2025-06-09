#pragma once
#include "../DialogBase/DynDialogEx.h"
#include "../BaseClass/SttFileTransferProgress.h"

#define X_PROGRESS_FTP			0x000012010
#define X_EDIT_PROGRESS			0x000012011
#define X_EDIT_FILELIST			0x000012012

// CXFtpProgressDynDlg 对话框

class CXFtpProgressDynDlg : public CDynDialogEx, public CSttSocketFileTransferProgress
{
	//	DECLARE_DYNAMIC(CXFtpProgressDynDlg)

public:
	CXFtpProgressDynDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CXFtpProgressDynDlg();
public:
	virtual void TransferStep(long nCurrSendSize);
	virtual void TransferFinish(const CString &strFile);
	virtual void TransferError(const CString &strFile,long nErrNo);
	virtual void Init(CStringArray &strArray);
	virtual void TransferStart(const CString &strFile, long nTotalSize);

	// 对话框数据
	//	enum { IDD = IDD_TESTAPPCONFIG_LOCALCONFIG_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();

public:
	CProgressCtrl m_prgsSttXftp;
	CEdit m_edtProgress;
	CEdit m_edtFileList;
	long m_nMaxRange;
	long m_nPos;
	long m_nProgressPos;

	void UpdateEditProgress();
	void SetWindowTopMost(BOOL bTopMost);
};