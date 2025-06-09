// StringVariableReplace.h: interface for the CStringVariableReplace class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CStringVariableReplace_H__)
#define _CStringVariableReplace_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringVariableReplace  
{
private:
	char *m_pData;
	char *m_pDestBuffer;
	long m_nDataLength;
	long m_nDestBufferLen;
	char *m_pDestCurr;
	char *m_pDestEnd;
	BOOL    m_bDataNew;
	BOOL m_bBufAttach;
	
public:
	CStringVariableReplace();
	CStringVariableReplace(CString &strBuffer, const CString &strSrc, const CString &strDest);
	virtual ~CStringVariableReplace();

	long Replace(CString &strBuffer, const CString &strSrc, const CString &strDest);
	long Replace(char *pSrcBuf, char *pDestBuf, const CString &strSrc, const CString &strDest, BOOL bValidSeparator=TRUE);
	long HasReplace(char *pSrcBuf, char *pDestBuf, const CString &strSrc, BOOL bValidSeparator=TRUE);
	void GetString(CString &strBuffer);

	void InitBuffer(long nSrcBufLen, long nDestBufLen);

private:

	static BOOL IsVariableChar(char ch)
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

	void AddToDestBuffer(const char *pBuffer, long nLen);
	void AddToDestBuffer(char ch)
	{
		*m_pDestCurr = ch;
		m_pDestCurr++;
	}
};

#endif // !defined(_CStringVariableReplace_H__)
