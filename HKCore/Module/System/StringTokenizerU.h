// StringTokenizerU.h: interface for the CStringTokenizerU class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(STRINGTOKENIZER_H__)
#define STRINGTOKENIZER_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CStringTokenizerU  
{
private:
	wchar_t *m_pData;
	wchar_t m_chDelimiter;
	wchar_t *m_pIndex;
	long m_nLength;
	
public:
	CStringTokenizerU();
	CStringTokenizerU(const wchar_t *pszDataLine);
	CStringTokenizerU(const wchar_t *pszDataLine,wchar_t chDelimiter);
	virtual ~CStringTokenizerU();

	void Init(const wchar_t *pszDataLine,wchar_t chDelimiter);
	void Init(const CString &strDataLine,wchar_t chDelimiter);
	BOOL HasMoreElements();
	const wchar_t* NextToken();
	void ResetIndexPointer();
	long GetStringsCount();

private:
	void Free();
	void Format(wchar_t chDelimiter);
};

#endif // !defined(STRINGTOKENIZER_H__)
