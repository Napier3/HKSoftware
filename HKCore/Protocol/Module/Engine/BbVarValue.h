#pragma once

#include "../../../Module/OSInterface/OSInterface.h"

class CBbVarValue
{
public:
	CBbVarValue(void);
	virtual ~CBbVarValue(void);

public:
	unsigned short vt;

	union 
	{
        char cVal;
        unsigned char bVal;
        short iVal;
        unsigned short uiVal;
        int intVal;
        unsigned int uintVal;
        long lVal;
        unsigned long ulVal;
        float fltVal;
        double dblVal;
        wchar_t* bstrVal;

        char *pcVal;
        unsigned char *pbVal;
        short *piVal;
        unsigned short *puiVal;
        int *pintVal;
        unsigned int *puintVal;
        long *plVal;
        unsigned long *pulVal;
        float *pfltVal;
        double *pdblVal;
        wchar_t* *pbstrVal;
	};

	enum VARENUM
	{	
	VVT_EMPTY	= 0,
	VVT_NULL		= 1,
	VVT_I1			= 2,
	VVT_UI1		= 3,
	VVT_I2			= 4,
	VVT_UI2		= 5,
	VVT_INT		= 6,
	VVT_UINT		= 7,
	VVT_I4			= 8,
	VVT_UI4		= 9,
	VVT_R4			= 10,
	VVT_R8			= 11,
	VVT_BSTR		= 12,

	VVT_REF		= 0x1000,		/*指针对象，应用其他地方的值*/
	VVT_NEW		= 0x2000		/*指针对象，自身创建的值，即*/
	} ;

public:
	CBbVarValue(CHAR val)			{    vt = VVT_I1;			cVal = val;		}
	CBbVarValue(BYTE val)			{    vt = VVT_UI1;		bVal = val;		}
	CBbVarValue(SHORT val)		{    vt = VVT_I2;			iVal = val;		}
	CBbVarValue(USHORT val)		{    vt = VVT_UI2;		uiVal = val;		}
	CBbVarValue(INT val)			{    vt = VVT_INT;		intVal = val;		}
	CBbVarValue(UINT val)			{    vt = VVT_UINT;		uintVal = val;	}
	CBbVarValue(LONG val)			{    vt = VVT_I4;			lVal = val;		}
	CBbVarValue(ULONG val)		{    vt = VVT_UI4;		ulVal = val;		}
	CBbVarValue(FLOAT val)		{    vt = VVT_R4;			fltVal = val;		}
	CBbVarValue(DOUBLE val)		{    vt = VVT_R8;			dblVal = val;	}

	CBbVarValue(BSTR val)		{    vt = VVT_BSTR;		bstrVal = val;	}	//{    vt = VVT_REF | VVT_BSTR;		bstrVal = val;	}
	CBbVarValue(CHAR *val)		{    vt = VVT_REF | VVT_I1;			pcVal = val;		}
	CBbVarValue(BYTE *val)		{    vt = VVT_REF | VVT_UI1;		pbVal = val;		}
	CBbVarValue(SHORT *val)		{    vt = VVT_REF | VVT_I2;			piVal = val;		}
	CBbVarValue(USHORT *val)	{    vt = VVT_REF | VVT_UI2;		puiVal = val;	}
	CBbVarValue(INT *val)			{    vt = VVT_REF | VVT_INT;		pintVal = val;	}
	CBbVarValue(UINT *val)		{    vt = VVT_REF | VVT_UINT;		puintVal = val;	}
	CBbVarValue(LONG *val)		{    vt = VVT_REF | VVT_I4;			plVal = val;		}
	CBbVarValue(ULONG *val)		{    vt = VVT_REF | VVT_UI4;		pulVal = val;	}
	CBbVarValue(FLOAT *val)		{    vt = VVT_REF | VVT_R4;			pfltVal = val;	}
	CBbVarValue(DOUBLE *val)	{    vt = VVT_REF | VVT_R8;			pdblVal = val;	}
	CBbVarValue(BSTR *val)		{    vt = VVT_REF | VVT_BSTR;		pbstrVal = val;	}

// 	CBbVarValue(CHAR &val)		{    vt = VVT_REF | VVT_I1;			pcVal = &val;		}
// 	CBbVarValue(BYTE &val)		{    vt = VVT_REF | VVT_UI1;		pbVal = &val;		}
// 	CBbVarValue(SHORT &val)		{    vt = VVT_REF | VVT_I2;			piVal = &val;		}
// 	CBbVarValue(USHORT &val)	{    vt = VVT_REF | VVT_UI2;		puiVal = &val;		}
// 	CBbVarValue(INT &val)			{    vt = VVT_REF | VVT_INT;		pintVal = &val;		}
// 	CBbVarValue(UINT &val)		{    vt = VVT_REF | VVT_INT;		puintVal = &val;	}
// 	CBbVarValue(LONG &val)		{    vt = VVT_REF | VVT_I4;			plVal = &val;		}
// 	CBbVarValue(ULONG &val)		{    vt = VVT_REF | VVT_UI4;		pulVal = &val;		}
// 	CBbVarValue(FLOAT &val)		{    vt = VVT_REF | VVT_R4;			pfltVal = &val;		}
// 	CBbVarValue(DOUBLE &val)	{    vt = VVT_REF | VVT_R8;			pdblVal = &val;		}
// 	CBbVarValue(BSTR &val)		{    vt = VVT_REF | VVT_BSTR;		pbstrVal = &val;	}

	void operator= (CHAR val)		{    vt = VVT_I1;			cVal = val;		}
	void operator= (BYTE val)		{    vt = VVT_UI1;		bVal = val;		}
	void operator= (SHORT val)   {    vt = VVT_I2;			iVal = val;		}
	void operator= (USHORT val)	{    vt = VVT_UI2;		uiVal = val;		}
	void operator= (INT val)		{    vt = VVT_INT;		intVal = val;		}
	void operator= (UINT val)		{    vt = VVT_INT;		uintVal = val;	}
	void operator= (LONG val)		{    vt = VVT_I4;			lVal = val;		}
	void operator= (ULONG val)	{    vt = VVT_UI4;		ulVal = val;		}
	void operator= (FLOAT val)	{    vt = VVT_R4;			fltVal = val;		}
	void operator= (DOUBLE val)	{    vt = VVT_R8;			dblVal = val;	}
	void operator= (BSTR val)		{    vt = VVT_BSTR;		bstrVal = val;	}

	void operator= (CHAR *val)		{    vt = VVT_REF | VVT_I1;			pcVal = val;		}
	void operator= (BYTE *val)		{    vt = VVT_REF | VVT_UI1;		pbVal = val;		}
	void operator= (SHORT *val)		{    vt = VVT_REF | VVT_I2;			piVal = val;		}
	void operator= (USHORT *val)	{    vt = VVT_REF | VVT_UI2;		puiVal = val;	}
	void operator= (INT *val)			{    vt = VVT_REF | VVT_INT;		pintVal = val;	}
	void operator= (UINT *val)		{    vt = VVT_REF | VVT_INT;		puintVal = val;	}
	void operator= (LONG *val)		{    vt = VVT_REF | VVT_I4;			plVal = val;		}
	void operator= (ULONG *val)		{    vt = VVT_REF | VVT_UI4;		pulVal = val;	}
	void operator= (FLOAT *val)		{    vt = VVT_REF | VVT_R4;			pfltVal = val;	}
	void operator= (DOUBLE *val)	{    vt = VVT_REF | VVT_R8;			pdblVal = val;	}
	void operator= (BSTR *val)		{    vt = VVT_REF | VVT_BSTR;		pbstrVal = val;	}

// 	void operator= (CHAR &val)		{    vt = VVT_REF | VVT_I1;			pcVal = &val;		}
// 	void operator= (BYTE &val)		{    vt = VVT_REF | VVT_UI1;		pbVal = &val;		}
// 	void operator= (SHORT &val)		{    vt = VVT_REF | VVT_I2;			piVal = &val;		}
// 	void operator= (USHORT &val)	{    vt = VVT_REF | VVT_UI2;		puiVal = &val;		}
// 	void operator= (INT &val)			{    vt = VVT_REF | VVT_INT;		pintVal = &val;		}
// 	void operator= (UINT &val)		{    vt = VVT_REF | VVT_INT;		puintVal = &val;	}
// 	void operator= (LONG &val)		{    vt = VVT_REF | VVT_I4;			plVal = &val;		}
// 	void operator= (ULONG &val)		{    vt = VVT_REF | VVT_UI4;		pulVal = &val;		}
// 	void operator= (FLOAT &val)		{    vt = VVT_REF | VVT_R4;			pfltVal = &val;		}
// 	void operator= (DOUBLE &val)	{    vt = VVT_REF | VVT_R8;			pdblVal = &val;		}
// 	void operator= (BSTR &val)		{    vt = VVT_REF | VVT_BSTR;		pbstrVal = &val;	}

	CString ToString();
	void ToString(CString &strVal);
	void FromString(const CString &strValue);
	void FromString(BSTR bstrValue);
	void FromString(char* pszValue);

public:
	BOOL IsEqual(CBbVarValue* pObj);
	BOOL Copy(CBbVarValue* pDest);
	CBbVarValue* Clone();
	BOOL Clear();
};
