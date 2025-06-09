// VariantDataAddress.h: interface for the CVariantDataAddress class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VARIANTDATAADDRESS_H__)
#define AFX_VARIANTDATAADDRESS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// #ifdef _PSX_IDE_QT_
// #include "../OSInterface/QT/CString_QT.h"
// #endif
// class CString;

#include "VarDataTypeEx.h"

class CVariantDataAddress  
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
		VDOT_CHARSTR = 7,
		VDOT_BOOL = 8,
		VDOT_N64 = 9,
		VDOT_CSTRING=10,
        VDOT_DWORD=11,
        VDOT_DOUBLE_LIST=12,
         VDOT_FLOAT_LIST=13,
         VDOT_INT_LIST=14
	};
public:
	eVDOT vt;
	union 
	{
		long	*lVal; 
        unsigned int	*dwVal;
		float	*fltVal;
		double	*dblVal; 
		int	*intVal;
		char *pszVal;
		unsigned char	*bVal;
		short	*nVal;
		volatile __int64 *n64Val;
		CString *pString;
        VAR_DOUBLE_LIST *pDoubleList;
        VAR_FLOAT_LIST *pFloatList;
        VAR_INT_LIST *pIntList;

		bool *boolVal;
	};


public:
	CVariantDataAddress();
	virtual ~CVariantDataAddress();

	CVariantDataAddress(unsigned char *val);
	CVariantDataAddress(short *val);
	CVariantDataAddress(long *val);
    CVariantDataAddress(unsigned int *val);
	CVariantDataAddress(float *val);
	CVariantDataAddress(double *val);
	CVariantDataAddress(int *val);
	CVariantDataAddress(volatile __int64 *val);
	CVariantDataAddress(char *val);
	CVariantDataAddress(const char *val);
	CVariantDataAddress(CString *val);
    CVariantDataAddress(VAR_DOUBLE_LIST *val);
    CVariantDataAddress(VAR_FLOAT_LIST *val);
    CVariantDataAddress(VAR_INT_LIST *val);
	CVariantDataAddress(const CVariantDataAddress &val);
	CVariantDataAddress(bool *val);		//20241022 huangliang 添加bool类型

	void operator= (unsigned char *val);
	void operator= (short *val);
	void operator= (long *val);
    void operator= (unsigned int *val);
	void operator= (float *val);
	void operator= (double *val);
	void operator= (int *val);
	void operator= (volatile __int64 *val);
	void operator= (char *val);
	void operator= (const char *val);
	void operator= (CString *val);
    void operator= (VAR_DOUBLE_LIST *val);
    void operator= (VAR_FLOAT_LIST *val);
    void operator= (VAR_INT_LIST *val);
    void operator= (const CVariantDataAddress &val);
	void operator= (bool *val);

	int operator== (unsigned char val);
	int operator== (short val);
	int operator== (long val);
    int operator== (unsigned int val);
	int operator== (float val);
	int operator== (double val);
	int operator== (int val);
	int operator== (volatile __int64 val);
    int operator== (char *val);
    int operator== (const CString &val);
    int operator== (const VAR_DOUBLE_LIST *val);
    int operator== (const VAR_FLOAT_LIST *val);
    int operator== (const VAR_INT_LIST *val);
    int operator== (const CVariantDataAddress &val);
	int operator== (bool val);
	
	long Compare(unsigned char val);
	long Compare(short val);
	long Compare(long val);
    long Compare(unsigned int val);
	long Compare(float val);
	long Compare(double val);
	long Compare(int val);
	long Compare(volatile __int64 val);
	long Compare(char *val);
    long Compare(VAR_DOUBLE_LIST *val);
    long Compare(VAR_FLOAT_LIST *val);
    long Compare(VAR_INT_LIST *val);
    long Compare(const CString &val);
	long Compare(const CVariantDataAddress &val);
	long Compare(bool val);
	 
    void ToString(VAR_DOUBLE_LIST *val, CString &strVal);
    void ToString(VAR_FLOAT_LIST *val, CString &strVal);
    void ToString(VAR_INT_LIST *val, CString &strVal);
	CString ToString(const CString &strFormat);
	CString ToString();

    void FromString(char *pszValue, VAR_DOUBLE_LIST *val);
    void FromString(char *pszValue, VAR_FLOAT_LIST *val);
    void FromString(char *pszValue, VAR_INT_LIST *val);
    void FromString(char *pszValue);

	void FromString(const char *pszValue)
	{
		FromString((char*)pszValue);
	}
    bool CompareValAddr(void* pValAddr);

    bool IsCString()	{	return (vt == VDOT_CSTRING);	}
    void UpdateDefaultValue();
    bool IsValueChange();
    void InitByDefault();

    unsigned int str_to_dword(const char *pstrValue);

    float get_float();

};

#endif // !defined(AFX_VARIANTDATAADDRESS_H__)
