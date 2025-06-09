
#pragma once

#include "../../CriticalSection/SynCriticalSection.h"

class CXUiOutputLog : public CEdit, public CLogBase
{
	// 构造
public:
	CXUiOutputLog(BOOL bUseLog=TRUE);

	virtual void LogString(long nLevel, const char *strMsg);
	virtual void LogString(long nLevel, const CString &strMsg);

	void  CreateAutoCriticSection();
private:
	BOOL m_bUseLog;
	CAutoCriticSection *m_pAutoCriticSection;
	void XLogString(long nLevel, const CString &strMsg); 

	// 实现
public:
	virtual ~CXUiOutputLog();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnShowMsg(UINT uCommandID);
	afx_msg void OnUpdateShowMsg(CCmdUI* pCmdUI);
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};
