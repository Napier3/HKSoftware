#include "StdAfx.h"
#include "CfgSclCmpParaObject.h"

CCfgSclCmpParaObject::CCfgSclCmpParaObject(void)
{
}

CCfgSclCmpParaObject::~CCfgSclCmpParaObject(void)
{
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,int *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,long *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,DWORD *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,float *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,double *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,unsigned char *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,short *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,char **value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

CCfgSclCmpParaObject::CCfgSclCmpParaObject(const CString &strName,CString *value,DWORD dwType, long nLength)
{
	Init();
	m_strName = strName;
	m_strID = strName;;
	m_varValue = value;
	m_dwShowType = dwType;
	m_nShowLength = nLength;
}

void CCfgSclCmpParaObject::SetValue(const CString &strValue)
{
	char *pStr = NULL;
	CString_to_char(strValue, &pStr);
	m_varValue.FromString(pStr);
	delete pStr;
}

float CCfgSclCmpParaObject::GetValue()
{
	float fTemp;
	fTemp = (float)_tstof(m_varValue.ToString());

	return fTemp;
}


void CCfgSclCmpParaObject::Compare(CCfgSclCmpParaObject *pCmp)
{
	ASSERT (m_strID == pCmp->m_strID);
	m_pRef = pCmp;
	pCmp->m_pRef = this;

	if (m_dwShowType == CFGSCL_PARA_TYPE_HEX || pCmp->m_dwShowType == CFGSCL_PARA_TYPE_HEX)
	{
		CString str1 = GetValueString();
		CString str2 = pCmp->GetValueString();

		if (str1.Left(2) != _T("0x"))
		{
			str1 = _T("0x") + str1;
		}

		if (str2.Left(2) != _T("0x"))
		{
			str2 = _T("0x") + str2;
		}

		m_bSameValue = st_CompareString(str1, str2);
	}
	else
	{
		try
		{
			m_bSameValue = (m_varValue == pCmp->m_varValue);
		}
		catch (...)
		{
			CString str1 = GetValueString();
			CString str2 = pCmp->GetValueString();
			m_bSameValue = st_CompareString(str1, str2);
		}
	}

	pCmp->m_bSameValue = m_bSameValue;
}

CString CCfgSclCmpParaObject::GetValueString()
{		

	if (m_dwShowType == CFGSCL_PARA_TYPE_HEX)
	{
		if (m_varValue.IsCString())
		{
			CString str = _T("0x");
			str += *m_varValue.pString;
			return  str;
		}
		else
		{
			if (m_nShowLength > 0)
			{
				CString strFormat;
				strFormat.Format(_T(".%dX"), m_nShowLength*2);
				strFormat = _T("0x%") + strFormat;
				return m_varValue.ToString(strFormat);
			}
			else
			{
				return m_varValue.ToString(_T("0x%X"));
			}
		}
	}
	else
	{
		return m_varValue.ToString();
	}
}