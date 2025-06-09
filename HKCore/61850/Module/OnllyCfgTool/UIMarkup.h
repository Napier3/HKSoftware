#pragma once
#include "markup.h"

class CUIMarkup :	public CMarkup
{
public:
	CUIMarkup(void);
	virtual ~CUIMarkup(void);
private:
	BOOL SetValue( LPCTSTR lpszValue );
	BOOL SetValue( bool bValue );
	BOOL SetValue( int nValue );
	BOOL SetValue( long lValue );
	BOOL SetValue( __int64 llValue );
	BOOL SetValue( float fValue );
	BOOL SetValue( double dValue );
	BOOL SetValue( DWORD dwValue );

public:
	BOOL AddElemSetData(LPCTSTR name, LPCTSTR lpszValue );
	BOOL AddElemSetData(LPCTSTR name, bool bValue );
	BOOL AddElemSetData(LPCTSTR name, int nValue );
	BOOL AddElemSetData(LPCTSTR name, long lValue );
	BOOL AddElemSetData(LPCTSTR name, __int64 llValue );
	BOOL AddElemSetData(LPCTSTR name, float fValue );
	BOOL AddElemSetData(LPCTSTR name, double dValue );
	BOOL AddElemSetData(LPCTSTR name, DWORD dwValue );

public:
	CString	GetChildElemValue(LPCTSTR name, LPCTSTR lpszDefault = NULL);
	bool	GetChildElemValue(LPCTSTR name, bool bDefault = 0);
	int		GetChildElemValue(LPCTSTR name, int nDefault = 0);
	long	GetChildElemValue(LPCTSTR name, long lDefault = 0);
	__int64	GetChildElemValue(LPCTSTR name, __int64 llDefault = 0);
	float	GetChildElemValue(LPCTSTR name, float fDefault = 0.0f);
	double	GetChildElemValue(LPCTSTR name, double dDefault = 0.0f)	;
	DWORD	GetChildElemValue(LPCTSTR name, DWORD dwDefault  = 0);
};

