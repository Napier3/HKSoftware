#pragma once
#include "StringCmpBlocks.h"


class CStringCmp
{
public:
	CStringCmp();
	virtual ~CStringCmp();

public:
	CString *m_pStrRef1,*m_pStrRef2;
	CStringCmpBlocks m_oStrCmpBlks1;
	CStringCmpBlocks m_oStrCmpBlks2;

public:
	virtual void StrCmp(CString *pStr1,CString *pStr2);
	virtual BOOL IsSameStrCmp(CString *pStr1,CString *pStr2);

private:
	void InitBlocks(CStringCmpBlocks *pBlocks, BYTE *pBuff, long nLen, CString *pStr);
};

BOOL CStringCmp_FilePath(const CString &strPathSrc, const CString &strPathDest);
