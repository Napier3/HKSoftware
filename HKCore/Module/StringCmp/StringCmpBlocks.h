#pragma once
#include "../BaseClass/TLinkList.h"
#include "StringCmpBlock.h"

class CStringCmpBlocks : public CTLinkListEx<CStringCmpBlock>
{
public:
	CStringCmpBlocks();
	virtual ~CStringCmpBlocks();

	CString *m_pStringRef;

public:
	virtual void Draw(CDC *pDC,CRect rc, UINT nFormat=DT_LEFT, COLORREF crMatch=RGB(0,0,0) , COLORREF crUnmatch=RGB(255,0,0));
	CStringCmpBlock* AddNew(int nBegin, int nLen, BYTE bCmpState, CString *pStr);
	long GetAllBlocksByState(CStringCmpBlocks &listBlks, UINT nCmpState = CMPSTATE_MATCH);

	void Log(UINT nCmpState = CMPSTATE_UNMATCH);
};
