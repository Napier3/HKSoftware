#pragma once


// CEditEx

class CEditEx : public CEdit
{
	DECLARE_DYNAMIC(CEditEx)

public:
	CEditEx();
	virtual ~CEditEx();
	void SetState(int nState);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	// 1 ֻ��������   2 ������ĸ   3 ����
	int   m_nState;
};


