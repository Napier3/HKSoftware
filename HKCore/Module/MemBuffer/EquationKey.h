// EquationKey.h: interface for the CEquationKey class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EQUATIONKEY_H__)
#define _EQUATIONKEY_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEquationBuffer;

#include "../BaseClass/BaseList.h"

class CEquationKey : public CBaseObject  
{
public:
	CEquationKey();
	CEquationKey(const char *pszKeyName,const char *pszValue);
	CEquationKey(const CString &strKeyName,const CString &strValue);
	CEquationKey(const char *pszKeyNameBegin,const char *pszKeyNameEnd
		,const char *pszValueBegin,const char *pszValueEnd);
	virtual ~CEquationKey();

private:
	CString m_pszKeyName;
	CString m_pszKeyValue;

public:
	BOOL IsLegal()
	{
		return (m_pszKeyName.GetLength() > 0);
	}
	BOOL CompareName(const char *pszName)
	{
		if ( !IsLegal())
			return FALSE;
		if (pszName == NULL)
			return FALSE;

		return (m_pszKeyName == pszName);
	}
	BOOL CompareName(const CString &strName)
	{
		if ( !IsLegal())
			return FALSE;
		
		return (m_pszKeyName == strName);
	}

	CString GetKeyName();
	CString GetKeyValue();
// 	const char* GetKeyName2();
// 	const char* GetKeyValue2();
	void GetKeyName(CString &strName);

	void GetKeyValue(CString &strValue);
	void GetKeyValue(int *pVal);
	void GetKeyValue(long *pVal);
	void GetKeyValue(float *pVal);
	void GetKeyValue(double *pVal);
	void SetKeyValue(const CString &strValue);
	void SetKeyValue(const char* strValue);
	void SetKeyValue(int nVal);
	void SetKeyValue(long nVal);
	void SetKeyValue(float fVal);
	void SetKeyValue(double dVal);

protected:
	virtual bool IsASeparateChar(char ch);

    friend class CEquationBuffer;
};

#endif // !defined(_EQUATIONKEY_H__)
