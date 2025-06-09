// XmlDocTransWord.h: interface for the CXmlDocTransWord class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XmlDocTransWord_H__)
#define _XmlDocTransWord_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//暂时只支持Word
#include "msword9.h"

class CXmlDocTransWord 
{
public:
	CXmlDocTransWord();
	virtual ~CXmlDocTransWord();

public:
	void XmlDocTrans(const CString &strDocFile);
	
protected:
	CString m_strXmlDocFile;
	long IsXmlDocFile(const CString &strDocFile);
	
private:
	MSWord::_Application m_WordApp;
	void GetWordApp(BOOL bShow=FALSE);
	void XmlDocTrans();

	DWORD m_dwBeginTickCount;

	void Enter()
	{
		m_dwBeginTickCount = GetTickCount();
	}


	long CalTickCountLong(DWORD dwEndTick, DWORD dwBeginTick)
	{
		DWORD dwLong = 0;

		if (dwEndTick < dwBeginTick)
		{
			dwLong = 0xFFFFFFFF - dwBeginTick;
			dwLong += dwEndTick;
		}
		else
		{
			dwLong = dwEndTick - dwBeginTick;
		}

		return dwLong;
	}


	long GetTickCountLong(BOOL bUdate=TRUE)
	{
		DWORD dwEnd = GetTickCount();
		DWORD dwLong = 0;

		dwLong = CalTickCountLong(dwEnd, m_dwBeginTickCount);

		if (bUdate)
		{
			m_dwBeginTickCount = dwEnd;
		}

		return dwLong;
	}
	void MessageTickCount(const CString &strTitle);

};

#endif // !defined(_XmlDocTransWordMNGR_H__)
