// StringTokenizer.h: interface for the CStringTokenizer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(STRINGTOKENIZER_H__)
#define STRINGTOKENIZER_H__

#include "../OSInterface/OSInterface.h"

class CStringTokenizer  
{
private:
	char *m_pData;
	char m_chDelimiter;
	char *m_pIndex;
	long m_nLength;
	BOOL m_bAttach;
	
public:
	CStringTokenizer();
	CStringTokenizer(const char *pszDataLine);
	CStringTokenizer(const char *pszDataLine,char chDelimiter);
	virtual ~CStringTokenizer();

	void Format(char chDelimiter);
	void Init(const char *pszDataLine,char chDelimiter);
	void Init(const CString &strDataLine,char chDelimiter);
	void AttatchInit(char *pszDataLine,char chDelimiter);
	BOOL HasMoreElements();
	const char* NextToken();
	const char* GetToken(long nIndex);
	void ResetIndexPointer();
	long GetStringsCount();
	//xxy 20210427
	BOOL HasSubString(const CString &strSub);

private:
	void Free();
};

#endif // !defined(STRINGTOKENIZER_H__)
