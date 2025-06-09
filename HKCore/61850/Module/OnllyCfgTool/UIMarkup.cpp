#include "StdAfx.h"
#include "UIMarkup.h"


CUIMarkup::CUIMarkup(void)
{

}


CUIMarkup::~CUIMarkup(void)
{

}


// set LPCTSTR value
BOOL CUIMarkup::SetValue( LPCTSTR lpszValue )
{
	CString strValue(lpszValue);
	return SetData(strValue);
}

// set bool value
BOOL CUIMarkup::SetValue( bool bValue )
{
	CString strValue;
	strValue = bValue ? _T("1") : _T("0");

	return SetData(strValue);
}

// set int value
BOOL CUIMarkup::SetValue( int nValue )
{
	CString strValue;
	strValue.Format( _T("%d"), nValue);

	return SetData(strValue);
}

// set long value
BOOL CUIMarkup::SetValue( long lValue )
{
	CString strValue;
	strValue.Format( _T("%ld"), lValue);

	return SetData(strValue);
}

// set __int64 value
BOOL CUIMarkup::SetValue( __int64 llValue )
{
	CString strValue;
	strValue.Format( _T("%I64d"), llValue);

	return SetData(strValue);
}


// set float value
BOOL CUIMarkup::SetValue( float fValue )
{
	CString strValue;
	strValue.Format( _T("%f"), fValue);

	return SetData(strValue);
}

// set double value
BOOL CUIMarkup::SetValue( double dValue )
{
	CString strValue;
	strValue.Format( _T("%e"), dValue);

	return SetData(strValue);
}

// set DWORD value
BOOL CUIMarkup::SetValue( DWORD dwValue )
{
	CString strValue;
	strValue.Format( _T("%lu"), dwValue);

	return SetData(strValue);
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, LPCTSTR lpszValue )
{
	if(AddElem(name))
	{
		return SetValue(lpszValue);
	}

	return FALSE;
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, bool bValue )
{
	if(AddElem(name))
	{
		return SetValue(bValue);
	}

	return FALSE;
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, int nValue )
{
	if(AddElem(name))
	{
		return SetValue(nValue);
	}

	return FALSE;
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, long lValue )
{
	if(AddElem(name))
	{
		return SetValue(lValue);
	}

	return FALSE;
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, __int64 llValue )
{
	if(AddElem(name))
	{
		return SetValue(llValue);
	}

	return FALSE;
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, float fValue )
{
	if(AddElem(name))
	{
		return SetValue(fValue);
	}

	return FALSE;
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, double dValue )
{
	if(AddElem(name))
	{
		return SetValue(dValue);
	}

	return FALSE;
}

BOOL CUIMarkup::AddElemSetData(LPCTSTR name, DWORD dwValue )
{
	if(AddElem(name))
	{
		return SetValue(dwValue);
	}

	return FALSE;
}

// get CString value
CString CUIMarkup::GetChildElemValue(LPCTSTR name, LPCTSTR lpszValue /* = NULL */ )
{
	if (FindChildElem(name))
	{
		return GetChildData();
	}

	return lpszValue;
}

// get bool value
bool CUIMarkup::GetChildElemValue(LPCTSTR name, bool bDefault )
{
	CString strValue;
	if (FindChildElem(name))
	{
		strValue = GetChildData();
	}

	if( strValue.CompareNoCase(_T("1")) == 0 )
	{
		return true;
	}
	else if( strValue.CompareNoCase(_T("0")) == 0 )
	{
		return false;
	}
	else
	{
		return bDefault;
	}	
}

// get int value
int CUIMarkup::GetChildElemValue(LPCTSTR name, int nDefault )
{
	CString strValue;
	if (FindChildElem(name))
	{
		strValue = GetChildData();
	}

	if( strValue.IsEmpty() )
	{
		return nDefault;
	}

	return _ttoi(strValue);
}

// get long value
long CUIMarkup::GetChildElemValue(LPCTSTR name, long lDefault )
{
	CString strValue;
	if (FindChildElem(name))
	{
		strValue = GetChildData();
	}

	if( strValue.IsEmpty() )
	{
		return lDefault;
	}

	return _ttol(strValue);
}

// get __int64 value
__int64 CUIMarkup::GetChildElemValue(LPCTSTR name, __int64 llDefault )
{
	CString strValue;
	if (FindChildElem(name))
	{
		strValue = GetChildData();
	}

	if( strValue.IsEmpty() )
	{
		return llDefault;
	}

	return _ttoi64(strValue);
}

// get float value
float CUIMarkup::GetChildElemValue(LPCTSTR name, float fDefault )
{
	CString strValue;
	if (FindChildElem(name))
	{
		strValue = GetChildData();
	}

	if( strValue.IsEmpty())
	{
		return fDefault;
	}

	return static_cast <float> (_tstof(strValue));
}

// get double value
double CUIMarkup::GetChildElemValue(LPCTSTR name, double dDefault )
{
	CString strValue;
	if (FindChildElem(name))
	{
		strValue = GetChildData();
	}

	if( strValue.IsEmpty() )
	{
		return dDefault;
	}

	return _tstof(strValue);
}

// get DWORD value
DWORD CUIMarkup::GetChildElemValue(LPCTSTR name, DWORD dwDefault )
{
	CString strValue;
	if (FindChildElem(name))
	{
		strValue = GetChildData();
	}

	if( strValue.IsEmpty() )
	{
		return dwDefault;
	}

	return _tcstoul(strValue, NULL, 10);
}