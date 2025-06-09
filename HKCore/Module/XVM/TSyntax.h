#ifndef _TSYNTAX_H__
#define _TSYNTAX_H__

#include <string.h>
#include "../BaseClass/TLinkList.h"

#define  MAX_ERROR_SIZE 200

#define TSYNTAX_TYPE_ERROR       0
#define TSYNTAX_TYPE_WARNING  1

class CTSyntax
{
public:
	CTSyntax(const char* pszError, int nLineIndex, long nType=TSYNTAX_TYPE_ERROR);
	CTSyntax(const char* pszErrorFormat, char ch, int nLineIndex, long nType=TSYNTAX_TYPE_ERROR)
	{
		memset(m_pszError, 0, MAX_ERROR_SIZE);
		sprintf(m_pszError, pszErrorFormat, ch);
		m_nLineIndex = nLineIndex;
		m_pszFuncName[0] = 0;
		m_nType = nType;
	}
	CTSyntax(const char* pszErrorFormat, const char* pstrMsg, int nLineIndex, long nType=TSYNTAX_TYPE_ERROR)
	{
		memset(m_pszError, 0, MAX_ERROR_SIZE);
		sprintf(m_pszError, pszErrorFormat, pstrMsg);
		m_nLineIndex = nLineIndex;
		m_pszFuncName[0] = 0;
		m_nType = nType;
	}
	virtual ~CTSyntax()
	{
	}

	void GetSyntax(CString &strSyntax)
	{
#ifdef _UNICODE
		strSyntax.AppendFormat(_T("Line %d error: %s\r\n"), m_nLineIndex, CString (m_pszError));
#else
		strSyntax.AppendFormat(_T("Line %d error: %s\r\n"), m_nLineIndex, m_pszError);
#endif;
	}
	void Log()
	{
		if (m_nType == TSYNTAX_TYPE_ERROR)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Line %d error: %s\r\n", m_nLineIndex, m_pszError);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Line %d warning: %s\r\n", m_nLineIndex, m_pszError);
		}
	}

	void SetFuncName(const char *pszFuncName)
	{
		strcpy(m_pszFuncName, pszFuncName);
	}

	char* GetFuncName()
	{
		return m_pszFuncName;
	}

	BOOL IsError()
	{
		return m_nType == TSYNTAX_TYPE_ERROR;
	}

private:
	char m_pszError[MAX_ERROR_SIZE];
	int  m_nLineIndex;
	char m_pszFuncName[120];
	long m_nType;  //0=error 1=warning

	CTSyntax()
	{
	}
};

class CTSyntaxs : public CTLinkList<CTSyntax>
{
public:
	CTSyntaxs()
	{
	}
	virtual ~CTSyntaxs()
	{
		DeleteAll();
	}

	CTSyntax* AddSyntax(const char* pszError, int nLineIndex, long nType=TSYNTAX_TYPE_ERROR)
	{
		CTSyntax *pNew = new CTSyntax(pszError, nLineIndex, nType);
		AddTail(pNew);
		return pNew;
	}
	CTSyntax* AddSyntax(const char* pszErrorFormat, char ch, int nLineIndex=0, long nType=TSYNTAX_TYPE_ERROR)
	{
		CTSyntax *pNew = new CTSyntax(pszErrorFormat, ch, nLineIndex, nType);
		AddTail(pNew);
		return pNew;
	}
	CTSyntax* AddSyntax(const char* pszErrorFormat, const char* pstrMsg, int nLineIndex=0, long nType=TSYNTAX_TYPE_ERROR)
	{
		CTSyntax *pNew = new CTSyntax(pszErrorFormat, pstrMsg, nLineIndex, nType);
		AddTail(pNew);
		return pNew;
	}

	void GetSyntax(CString &strSyntax)
	{
		strSyntax.Empty();
		POS pos = GetHeadPosition();
		CTSyntax *p = NULL;

		while (pos != NULL)
		{
			p = (CTSyntax*)GetNext(pos);
			p->GetSyntax(strSyntax);
		}
	}

	void Log()
	{
		POS pos = GetHeadPosition();
		CTSyntax *p = NULL;
		long nCount = 0;

		while (pos != NULL)
		{
			p = (CTSyntax*)GetNext(pos);
			p->Log();

			if (p->IsError())
			{
				nCount++;
			}
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Error=%d Warning=%d"), nCount, GetCount() - nCount);
	}

	long GetErrorCount()
	{
		POS pos = GetHeadPosition();
		CTSyntax *p = NULL;
		long nCount = 0;

		while (pos != NULL)
		{
			p = (CTSyntax*)GetNext(pos);
			
			if (p->IsError())
			{
				nCount++;
			}
		}

		return nCount;
	}
};


#endif
