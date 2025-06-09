// VariantData.h: interface for the CVariantData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARIANTDATA_H__)
#define AFX_VARIANTDATA_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CVariantData  
{
public:
	enum eVDOT
	{
		VDOT_NULL = 0,
		VDOT_UNSIGNEDCHAR = 1,
		VDOT_SHORT = 2,
		VDOT_LONG = 3,
		VDOT_FLOAT = 4,
		VDOT_DOUBLE = 5,
		VDOT_INT = 6,
		VDOT_BOOL = 8,
		VDOT_N64 = 9,
		VDOT_CSTRING=10,
		VDOT_DWORD=11,
		VDOT_WORD=12
	};
public:
	eVDOT vt;
	union 
	{
		long	lVal; 
		DWORD	dwVal; 
		WORD	wVal; 
		float	fltVal;
		double	dblVal; 
		int	intVal;
		unsigned char	bVal;
		short	nVal;
		__int64 n64Val;
		CString *pString;
	};

private:
	void Free()
	{
		if (vt == VDOT_CSTRING)
		{
			delete pString;
			pString = NULL;
			vt = VDOT_NULL;
		}
	}

public:
	CVariantData();
	virtual ~CVariantData();

	CVariantData(unsigned char val);
	CVariantData(short val);
	CVariantData(long val);
	CVariantData(DWORD val);
	CVariantData(WORD val);
	CVariantData(float val);
	CVariantData(double val);
	CVariantData(int val);
	CVariantData(volatile __int64 val);
	CVariantData(const CString &val);
	CVariantData(const CVariantData &val);

	void operator= (unsigned char val);
	void operator= (short val);
	void operator= (long val);
	void operator= (DWORD val);
	void operator= (WORD val);
	void operator= (float val);
	void operator= (double val);
	void operator= (int val);
	void operator= (volatile __int64 val);
	void operator= (const CString &val);
	void operator= (const CVariantData &val);

	int operator== (unsigned char val);
	int operator== (short val);
	int operator== (long val);
	int operator== (DWORD val);
	int operator== (WORD val);
	int operator== (float val);
	int operator== (double val);
	int operator== (int val);
	int operator== (volatile __int64 val);
	int operator== (const CString &val);
	int operator== (const CVariantData &val);
	
	long Compare(unsigned char val);
	long Compare(short val);
	long Compare(long val);
	long Compare(DWORD val);
	long Compare(WORD val);
	long Compare(float val);
	long Compare(double val);
	long Compare(int val);
	long Compare(volatile __int64 val);
	long Compare(const CString &val);
	long Compare(const CVariantData &val);
	 
	CString ToString(const CString &strFormat);
	CString ToString();

	BOOL IsCString()	{	return (vt == VDOT_CSTRING);	}
};

#endif // !defined(AFX_VARIANTDATA_H__)
