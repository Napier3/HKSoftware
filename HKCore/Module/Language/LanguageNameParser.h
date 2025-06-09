// LanguageNameParser.h: interface for the CLanguageNameParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LANGUAGENAMEPARSER_H__B8AF27D5_BAA4_4AAD_AB75_F84C3799EC73__INCLUDED_)
#define AFX_LANGUAGENAMEPARSER_H__B8AF27D5_BAA4_4AAD_AB75_F84C3799EC73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\MEMBUFFER\BufferBase.h"
#define MAX_LanguageString 8
#define LanguageString_Buffer_DefLen 1024

/*
���ڽ����������������ֵ��ַ���,����:UaƵ��,UaFreqencyΪ���Ļ�Ӣ���ַ���,����������Ϊ"Ua$sFreqency$"
CLanguageNameParserʵ�ֽ�"Ua$sFreqency$"����Ϊ"UaƵ��"/"UaFreqency"
�����������ַ������ܰ����������������Դ��ʾ"$xxx$".
*/
class CLanguageNameParser : public CBufferBase  
{
public:
	CLanguageNameParser();
	virtual ~CLanguageNameParser();

	static const char g_chLanguageSeparator;
	
public:
	long ParseLanguageString(CString &strName);
	long GetLanguageStringCount()
	{
		return m_nLanguageStringCount;
	}
	const char* GetLanguageString(long nIndex)
	{
		ASSERT(nIndex >= 0 && nIndex< MAX_LanguageString);
		ASSERT(nIndex >= 0 && nIndex< m_nLanguageStringCount);
		return m_oLanguageString[nIndex].pLanguageStringBegin;
	}

private:
	struct structLanguageString
	{
		char *pLanguageStringBegin;
		char *pLanguageStringEnd;
	};
	typedef structLanguageString LANGUAGESTRING;

	LANGUAGESTRING m_oLanguageString[MAX_LanguageString];
	long m_nLanguageStringCount;

private:
	char *m_pLanguageStringBuffer;
	char *m_pCurrLanguageStringPos;
	long m_nLanguageStringBufferLen;
	void ReAllocLanguageStringBuffer();
	void Parse();
};

#endif // !defined(AFX_LANGUAGENAMEPARSER_H__B8AF27D5_BAA4_4AAD_AB75_F84C3799EC73__INCLUDED_)
