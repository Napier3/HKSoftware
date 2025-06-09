#pragma once

#define CMPSTATE_MATCH     1
#define CMPSTATE_UNMATCH   0


class CStringCmpBlock
{
public:
	CStringCmpBlock();
	virtual ~CStringCmpBlock();

public:
	long m_nBeginPos;	// 字符块开始位置
	long m_nLength;    // 字符块结束位置
	UINT m_nCmpState;
    CString *m_pStringRef;

public:
	BOOL IsMatch()						{	return m_nCmpState == CMPSTATE_MATCH;	}
	void GetString(CString &strText);
	CString GetString();
	virtual long Draw(CDC *pDC,  CRect rc, UINT nFormat=DT_LEFT , COLORREF crMatch=RGB(0,0,0), COLORREF crUnmatch=RGB(255,0,0));
};
