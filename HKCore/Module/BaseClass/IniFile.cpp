#include "StdAfx.h"
#include "IniFile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// CIniFile::CIniFile()
// { 
// 
// }

void CIniFile::LinkRealFile(const CString &strIniFile)
{
	m_strFileName = strIniFile;
}

CIniFile::CIniFile(CString FileName)
{
	m_strFileName = FileName;
}

void CIniFile::SetFile(CString FileName)
{
	m_strFileName = FileName;
}

CIniFile::~CIniFile()
{
}

bool CIniFile::SectionExists(CString Section)
{
	CStringArray Strings;
	ReadSection(Section, Strings);
	return Strings.GetSize()>0;
}

CString CIniFile::ReadString(CString Section, CString Ident, CString Default)
{
	int nSize = 0, nLen = nSize-2;
	CString strReturn = _T("");
	while(nLen==nSize-2)
	{
		nSize+=MAX_BUFFER_SIZE;
		nLen = GetPrivateProfileString(Section
			,Ident
			,Default
			,strReturn.GetBuffer(2048)
			,nSize						//如果返回nSize-2
			,m_strFileName);			//则表示缓冲区长度不足，递增MAX_BUFFER_SIZE
	}
	CString strReturnEx;
	strReturnEx.Format(_T("%s"), strReturn);
	return strReturnEx;
}

void CIniFile::WriteString(CString Section, CString Ident, CString Value)
{
	if(WritePrivateProfileString(Section,Ident,Value,m_strFileName)==0)
		throw CIniFileException();
}

int CIniFile::ReadInteger(CString Section, CString Ident, int Default)
{
	CString strInt = ReadString(Section,Ident,_T(""));

	if (strInt == _T(""))
	{
		return Default;
	}
	else
	{
#ifdef _UNICODE
		return _wtoi(strInt);
#else
		return atoi(strInt);
#endif
	}
}

void CIniFile::WriteInteger(CString Section, CString Ident, int Value)
{
	CString strData;
	strData.Format(_T("%d"),Value);
	WriteString(Section,Ident,strData);
}

float CIniFile::ReadFloat(CString Section, CString Ident, float Default)
{
	CString strFloat = ReadString(Section,Ident,_T(""));

	if (strFloat == _T(""))
	{
		return Default;
	}
	else
	{
#ifdef _UNICODE
		return (float)_wtof(strFloat);
#else
		return (float)atof(strFloat);
#endif
	}

}

void CIniFile::WriteFloat(CString Section, CString Ident, float Value)
{
	CString strData;
	strData.Format(_T("%.5f"),Value);
	WriteString(Section,Ident,strData);
}

void CIniFile::ReadSection(CString Section, CStringArray &Strings)
{
	Strings.RemoveAll();//清空字符串数组
	int nSize = 0, nLen = nSize-2;
	TCHAR *lpszReturnBuffer = 0;
	while(nLen==nSize-2)
	{
		nSize+=MAX_BUFFER_SIZE;
		if(lpszReturnBuffer) delete lpszReturnBuffer;
		lpszReturnBuffer = new TCHAR[nSize];
		nLen = GetPrivateProfileString(Section,NULL,NULL,lpszReturnBuffer,//如果返回nSize-2
			nSize,m_strFileName);	//则表示缓冲区长度不足，递增MAX_BUFFER_SIZE
	}
	TCHAR *pName = new TCHAR[MAX_PATH];
	TCHAR *pStart, *pEnd;
	pStart = lpszReturnBuffer;
	pEnd =0;
	while(pStart!=pEnd)
	{
		pEnd = _tcschr(pStart,0);
		nLen = pEnd-pStart;
		if(nLen==0) break;
		_tcsncpy_s(pName,MAX_PATH,pStart,nLen);
		pName[nLen] = 0;
		Strings.Add(pName);
		pStart = pEnd+1;
	}	
	delete lpszReturnBuffer;
	delete pName;
}

void CIniFile::ReadSections(CStringArray &Strings)
{
	Strings.RemoveAll();//清空字符串数组
	int nSize = 0, nLen = nSize-2;
	TCHAR *lpszReturnBuffer = 0;
	while(nLen==nSize-2)
	{
		nSize+=MAX_BUFFER_SIZE;
		if(lpszReturnBuffer) delete lpszReturnBuffer;
		lpszReturnBuffer = new TCHAR[nSize];
		nLen = GetPrivateProfileSectionNames(lpszReturnBuffer,nSize,//如果返回nSize-2则表示
			m_strFileName);	//缓冲区长度不足，递增MAX_BUFFER_SIZE
	}
	TCHAR *pName = new TCHAR[MAX_PATH];
	TCHAR *pStart, *pEnd;
	pStart = lpszReturnBuffer;
	pEnd =0;
	while(pStart!=pEnd)
	{
		pEnd = _tcschr(pStart,0);
		nLen = pEnd-pStart;
		if(nLen==0) break;
		_tcsncpy_s(pName,MAX_PATH,pStart,nLen);
		pName[nLen] = 0;
		Strings.Add(pName);
		pStart = pEnd+1;
	}
	delete lpszReturnBuffer;
	delete pName;
}

void CIniFile::EraseSection(CString Section)
{
	if(WritePrivateProfileString(Section,NULL,NULL,m_strFileName)==0)
		throw CIniFileException();
}
