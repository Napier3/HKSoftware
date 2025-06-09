// EquationKey.cpp: implementation of the CEquationKey class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EquationKey.h"
#include "EquationBuffer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEquationKey::CEquationKey()
{
	
}

CEquationKey::CEquationKey(const char *pszKeyName,const char *pszValue)
{
	if (pszKeyName == NULL || pszValue == NULL)
		return;

	m_pszKeyName = pszKeyName;
	m_pszKeyValue = pszValue;
}

CEquationKey::CEquationKey(const CString &strKeyName,const CString &strValue)
{
	m_pszKeyName = strKeyName;
	m_pszKeyValue = strValue;
}

CEquationKey::CEquationKey(const char *pszKeyNameBegin,const char *pszKeyNameEnd
			 ,const char *pszValueBegin,const char *pszValueEnd)
{
	//2021-1-3  lijunqing 考虑末尾没有分隔符号的特殊情况
	if (pszKeyNameBegin == NULL || pszKeyNameEnd == NULL
		|| pszValueBegin == NULL) //|| pszValueEnd == NULL)
		return;
	
	long lLen = pszKeyNameEnd - pszKeyNameBegin + 1;
	if (lLen <= 0)
		return;
	
	char *pTemp = new char [lLen + 5];
	memcpy(pTemp,pszKeyNameBegin,lLen);
	pTemp[lLen] = 0;
	m_pszKeyName = pTemp;
	delete pTemp;
	
	//2021-1-3  lijunqing 考虑末尾没有分隔符号的特殊情况
	if (pszValueEnd != NULL)
	{
		lLen = pszValueEnd - pszValueBegin + 1;
	}
	else
	{
		lLen = strlen(pszValueBegin);
	}
	
	if (lLen <= 0)
	{
		pTemp = new char [5];
		pTemp[0] = 0;
	}
	else
	{
		pTemp = new char [lLen + 5];
		memcpy(pTemp,pszValueBegin,lLen);
		pTemp[lLen] = 0;
	}

	m_pszKeyValue = pTemp;
	delete pTemp;
}

CEquationKey::~CEquationKey()
{
	
}

CString CEquationKey::GetKeyName()
{
	return m_pszKeyName;
}

CString CEquationKey::GetKeyValue()
{
	return m_pszKeyValue;
}
// 
// const char* CEquationKey::GetKeyName2()
// {
// 	return m_pszKeyName;
// }
// 
// const char* CEquationKey::GetKeyValue2()
// {
// 	return m_pszKeyValue;
// }

void CEquationKey::GetKeyName(CString &strName)
{
	strName = m_pszKeyName;
}

void CEquationKey::GetKeyValue(CString &strValue)
{
	strValue = m_pszKeyValue;
}

void CEquationKey::GetKeyValue(int *pVal)
{
#ifdef _UNICODE
	*pVal = _wtol(m_pszKeyValue);
#else
    *pVal = atoi(m_pszKeyValue.GetString());
#endif
}

void CEquationKey::GetKeyValue(long *pVal)
{
#ifdef _UNICODE
	*pVal = _wtol(m_pszKeyValue);
#else
    *pVal = atol(m_pszKeyValue.GetString());
#endif
}

void CEquationKey::GetKeyValue(float *pVal)
{
#ifdef _UNICODE
	*pVal = (float)_wtof(m_pszKeyValue);
#else
    *pVal = (float)atof(m_pszKeyValue.GetString());
#endif
}

void CEquationKey::GetKeyValue(double *pVal)
{
#ifdef _UNICODE
	*pVal = _wtof(m_pszKeyValue);
#else
    *pVal = atof(m_pszKeyValue.GetString());
#endif
}

void CEquationKey::SetKeyValue(const CString &strValue)
{
	m_pszKeyValue = strValue;
}

void CEquationKey::SetKeyValue(const char* strValue)
{
	m_pszKeyValue = strValue;
}
void CEquationKey::SetKeyValue(int nVal)
{
#ifdef _UNICODE
		m_pszKeyValue.Format(_T("%d"),nVal);
#else
		m_pszKeyValue.Format("%d",nVal);
#endif
}

void CEquationKey::SetKeyValue(long nVal)
{
#ifdef _UNICODE
	m_pszKeyValue.Format(_T("%d"),nVal);
#else
	m_pszKeyValue.Format("%d",nVal);
#endif
}

void CEquationKey::SetKeyValue(float fVal)
{
#ifdef _UNICODE
	m_pszKeyValue.Format(_T("%f"),fVal);
#else
	m_pszKeyValue.Format("%f",fVal);
#endif
}

void CEquationKey::SetKeyValue(double dVal)
{
#ifdef _UNICODE
	m_pszKeyValue.Format(_T("%f"),dVal);
#else
	m_pszKeyValue.Format("%f",dVal);
#endif
}

//判断字符是否为分隔字符
bool CEquationKey::IsASeparateChar(char ch)
{
	return ( (ch == ';') || (ch == '=') || (ch == '\r') || (ch == '\n') );
}
