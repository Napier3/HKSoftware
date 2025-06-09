// StringVariableReplaceU.h: interface for the CStringVariableReplaceU class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CStringVariableReplaceU_H__)
#define _CStringVariableReplaceU_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringVariableReplaceU  
{
private:
	const wchar_t *m_pData;
	wchar_t *m_pDestBuffer;
	long m_nDataLength;
	long m_nDestBufferLen;
	wchar_t *m_pDestCurr;
	wchar_t *m_pDestEnd;
	BOOL    m_bDataNew;
	BOOL m_bBufAttach;
	
public:
	CStringVariableReplaceU();
	CStringVariableReplaceU(CString &strBuffer, const CString &strSrc, const CString &strDest);
	virtual ~CStringVariableReplaceU();

	long Replace(CString &strBuffer, const CString &strSrc, const CString &strDest);
	long Replace(wchar_t *pSrcBuf, wchar_t *pDestBuf, const CString &strSrc, const CString &strDest, BOOL bValidSeparator=TRUE);
	long HasReplace(wchar_t *pSrcBuf, wchar_t *pDestBuf, const CString &strSrc, BOOL bValidSeparator=TRUE);
	void GetString(CString &strBuffer);

	void InitBuffer(long nSrcBufLen, long nDestBufLen);

	static BOOL IsVariableChar(wchar_t ch)
	{
		if (ch == '_')
		{
			return TRUE;
		}

		if (('a' <= ch && ch <= 'z') || ('A' <= ch && ch <= 'Z') )
		{
			return TRUE;
		}

		if ( '0' <= ch && ch <= '9' )
		{
			return TRUE;
		}

		return FALSE;
	}

private:
	long Replace(const CString &strSrc, const CString &strDest);
	long Replace2(const CString &strSrc, const CString &strDest);

	long HasReplace(const CString &strSrc);
	long HasReplace2(const CString &strSrc);

	void Init(const CString &strBuffer);
	void FreeSrc(BOOL bDelete=FALSE);
	void FreeDest(BOOL bDelete=FALSE);
	void InitDestBuffer(long nAddLen);
	void ExpandDestBuffer(long nLen);

	void AddToDestBuffer(const wchar_t *pBuffer, long nLen);
	void AddToDestBuffer(wchar_t ch)
	{
		*m_pDestCurr = ch;
		m_pDestCurr++;
	}
};

#endif // !defined(_CStringVariableReplaceU_H__)
