
#pragma once



class CAtsUiOutputLog : public CEdit, public CLogBase
{
	// 构造
public:
	CAtsUiOutputLog(BOOL bUseLog);

	virtual void LogString(long nLevel, const char *strMsg);
	virtual void LogString(long nLevel, const CString &strMsg);
	void CreateTestTempFile();

private:
	BOOL m_bUseLog;
// 	static long m_nOpenFile;
// 	static CFile *m_pFile;

	// 实现
public:
	virtual ~CAtsUiOutputLog();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnShowMsg(UINT uCommandID);
	afx_msg void OnUpdateShowMsg(CCmdUI* pCmdUI);
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};
