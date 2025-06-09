#pragma once 

/*
	功能描述：Safety测试项目多项录入窗口
*/
//

#include "../../../Module/BaseClass/TLinkList.h"

class CUISftRsltWndInterface;

class CUISftRsltWndMultiSel : public CCheckListBox
{
public:
	CUISftRsltWndMultiSel();
	CUISftRsltWndMultiSel(const CString &strFormat);

	virtual ~CUISftRsltWndMultiSel();

public:
	CUISftRsltWndInterface* m_pResultWndInterface;
	CString m_strFormat;

	void InitMultiSel(const CString& strFormat,const CString& strValue);

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};