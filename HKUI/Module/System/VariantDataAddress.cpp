// VariantDataAddress.cpp: implementation of the CVariantDataAddress class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VariantDataAddress.h"
//#include "../api/StringApi.h"
#include "../API/StringApi.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVariantDataAddress::CVariantDataAddress()
{
	vt = VDOT_NULL;
	dblVal = NULL;
}

CVariantDataAddress::~CVariantDataAddress()
{

}

CVariantDataAddress::CVariantDataAddress(unsigned char *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(short *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(long *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(unsigned int *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(float *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(double *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(int *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(volatile __int64 *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(char *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(const char *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(CString *val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(VAR_DOUBLE_LIST *val)
{
    (*this) = val;
}

CVariantDataAddress::CVariantDataAddress(VAR_FLOAT_LIST *val)
{
    (*this) = val;
}

CVariantDataAddress::CVariantDataAddress(VAR_INT_LIST *val)
{
    (*this) = val;
}

CVariantDataAddress::CVariantDataAddress(const CVariantDataAddress &val)
{
	(*this) = val;
}

CVariantDataAddress::CVariantDataAddress(bool *val)
{
	(*this) = val;
}


void CVariantDataAddress::operator= (unsigned char *val)
{
	vt = VDOT_UNSIGNEDCHAR;
	bVal = val;
}

void CVariantDataAddress::operator= (short *val)
{
	vt = VDOT_SHORT;
	nVal = val;
}

void CVariantDataAddress::operator= (long *val)
{
	vt = VDOT_LONG;
	lVal = val;
}

void CVariantDataAddress::operator= (unsigned int *val)
{
	vt = VDOT_LONG;
	dwVal = val;
}

void CVariantDataAddress::operator= (float *val)
{
	vt = VDOT_FLOAT;
	fltVal = val;
}

void CVariantDataAddress::operator= (double *val)
{
	vt = VDOT_DOUBLE;
	dblVal = val; 
}

void CVariantDataAddress::operator= (int *val)
{
	vt = VDOT_INT;
	intVal = val;
}

void CVariantDataAddress::operator= (volatile __int64 *val)
{
	vt = VDOT_N64;
	n64Val = val;
}

void CVariantDataAddress::operator= (char *val)
{
	vt = VDOT_CHARSTR;
	pszVal = (char*)val;
}

void CVariantDataAddress::operator= (VAR_DOUBLE_LIST *val)
{
    vt = VDOT_DOUBLE_LIST;
    pDoubleList = val;
}

void CVariantDataAddress::operator= (VAR_FLOAT_LIST *val)
{
    vt = VDOT_FLOAT_LIST;
    pFloatList = val;
}

void CVariantDataAddress::operator= (VAR_INT_LIST *val)
{
    vt = VDOT_INT_LIST;
    pIntList = val;
}

void CVariantDataAddress::operator= (const char *val)
{
	vt = VDOT_CHARSTR;
	pszVal = (char*)val;
}

void CVariantDataAddress::operator= (CString *val)
{
	vt = VDOT_CSTRING;
	pString = val;
}
void CVariantDataAddress::operator= (bool *val)
{
	vt = VDOT_BOOL;
	boolVal = val;
}


void CVariantDataAddress::operator= (const CVariantDataAddress &val)
{
	switch(val.vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		(*this) = val.bVal;
		break;
	case VDOT_SHORT://2
		(*this) = val.nVal;
		break;
	case VDOT_LONG://3
		(*this) = val.lVal;
		break;
	case VDOT_FLOAT://4
		(*this) = val.fltVal;
		break;
	case VDOT_DOUBLE://5
		(*this) = val.dblVal;
		break;
	case VDOT_INT://6
		(*this) = val.intVal;
		break;
	case VDOT_N64://6
		(*this) = val.n64Val;
		break;
	case VDOT_CHARSTR://7
		(*this) = val.pszVal;
		break;
	case VDOT_CSTRING://7
		(*this) = val.pString;
		break;
	case VDOT_DWORD://7
		(*this) = val.dwVal;
		break;
    case VDOT_DOUBLE_LIST://7
        (*this) = val.pDoubleList;
        break;
    case VDOT_FLOAT_LIST://7
        (*this) = val.pFloatList;
        break;
    case VDOT_INT_LIST://7
        (*this) = val.pIntList;
        break;
    default:
		break;
	}
}

int CVariantDataAddress::operator== (unsigned char val)
{
	if (vt != VDOT_UNSIGNEDCHAR)
	{
		throw(-1);
	}
	
	return (*bVal == val);
}

int CVariantDataAddress::operator== (short val)
{
	if (vt != VDOT_SHORT)
	{
		throw(-1);
	}
	
	return (*nVal == val);
}

int CVariantDataAddress::operator== (long val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}
	
	return (*lVal == val);
}

int CVariantDataAddress::operator== (unsigned int val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}

	return (*dwVal == val);
}

int CVariantDataAddress::operator== (float val)
{
	if (vt != VDOT_FLOAT)
	{
		throw(-1);
	}
	
	return (*fltVal == val);
}

int CVariantDataAddress::operator== (double val)
{
	if (vt != VDOT_DOUBLE)
	{
		throw(-1);
	}
	
	return (*dblVal == val);
}

int CVariantDataAddress::operator== (int val)
{
	if (vt != VDOT_INT)
	{
		throw(-1);
	}
	
	return (*intVal == val);
}

int CVariantDataAddress::operator== (volatile __int64 val)
{
	if (vt != VDOT_N64)
	{
		throw(-1);
	}

	return (*n64Val == val);
}

int CVariantDataAddress::operator== (char *val)
{
	if (vt != VDOT_CHARSTR)
	{
		throw(-1);
	}
	
	return (strcmp(pszVal,val));
}

int CVariantDataAddress::operator == (const VAR_DOUBLE_LIST *val)
{
    if (vt != VDOT_DOUBLE_LIST)
	{
		throw(-1);
	}

    return FALSE;
}

int CVariantDataAddress::operator== (const VAR_FLOAT_LIST *val)
{
    if (vt != VDOT_FLOAT_LIST)
    {
        throw(-1);
    }

    return FALSE;
}


int CVariantDataAddress::operator== (const VAR_INT_LIST *val)
{
    if (vt != VDOT_INT_LIST)
    {
        throw(-1);
    }

    return FALSE;
}

int CVariantDataAddress::operator== (const CString &val)
{
    if (vt != VDOT_CSTRING)
    {
        throw(-1);
    }

    return _P_CompareString(*pString ,val);// (*pString == val);
}
int CVariantDataAddress::operator== (bool val)
{
	if (vt != VDOT_BOOL)
	{
		throw(-1);
	}

	return (*boolVal == val);
}

int CVariantDataAddress::operator== (const CVariantDataAddress &val)
{
	if (vt != val.vt)
	{
		throw(-1);
	}

	int bTrue = FALSE;
	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		bTrue = ((*this) == *(val.bVal));
		break;
	case VDOT_SHORT://2
		bTrue = ((*this) == *(val.nVal));
		break;
	case VDOT_LONG://3
		bTrue = ((*this) == *(val.lVal));
		break;
	case VDOT_FLOAT://4
		bTrue = ((*this) == *(val.fltVal));
		break;
	case VDOT_DOUBLE://5
		bTrue = ((*this) == *(val.dblVal));
		break;
	case VDOT_INT://6
		bTrue = ((*this) == *(val.intVal));
		break;
	case VDOT_CHARSTR://7
		bTrue = ((*this) == *(val.pszVal));
		break;
	case VDOT_CSTRING://7
		bTrue = ((*this) == *val.pString);
		break;
	case VDOT_N64://7
		bTrue = ((*this) == *(val.n64Val));
		break;
	case VDOT_DWORD://7
		bTrue = ((*this) == *(val.dwVal));
		break;
	default:
		break;
	}
	return bTrue;
}

long CVariantDataAddress::Compare(unsigned char val)
{
	if (vt != VDOT_UNSIGNEDCHAR)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (*bVal > val)
	{
		lCompare = 1;
	}
	else if (*bVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}

	return lCompare;
}

long CVariantDataAddress::Compare(short val)
{
	if (vt != VDOT_SHORT)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (*nVal > val)
	{
		lCompare = 1;
	}
	else if (*nVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantDataAddress::Compare(long val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (*lVal > val)
	{
		lCompare = 1;
	}
	else if (*lVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantDataAddress::Compare(unsigned int val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (*dwVal > val)
	{
		lCompare = 1;
	}
	else if (*dwVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}

	return lCompare;
}

long CVariantDataAddress::Compare(float val)
{
	if (vt != VDOT_FLOAT)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (*fltVal > val)
	{
		lCompare = 1;
	}
	else if (*fltVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantDataAddress::Compare(double val)
{
	if (vt != VDOT_DOUBLE)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (*dblVal > val)
	{
		lCompare = 1;
	}
	else if (*dblVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantDataAddress::Compare(int val)
{
	throw(-1);
	
	return 0;
}
long CVariantDataAddress::Compare(volatile __int64 val)
{
	throw(-1);

	return 0;
}

long CVariantDataAddress::Compare(char *val)
{
	if (vt != VDOT_CHARSTR)
	{
		throw(-1);
	}
	long lCompare = strcmp(pszVal,val);
	
	return lCompare;
}

long CVariantDataAddress::Compare(VAR_DOUBLE_LIST *val)
{
    if (vt != VDOT_DOUBLE_LIST)
    {
        return false;
    }

    if (pDoubleList->nCount != val->nCount)
    {
        return false;
    }

    return memcmp(pDoubleList->pfBuffer, val->pfBuffer, pDoubleList->nCount * sizeof(double));
}


long CVariantDataAddress::Compare(VAR_FLOAT_LIST *val)
{
    if (vt != VDOT_FLOAT_LIST)
    {
        return false;
    }

    if (pDoubleList->nCount != val->nCount)
    {
        return false;
    }

    return memcmp(pFloatList->pfBuffer, val->pfBuffer, pFloatList->nCount * sizeof(float));
}


long CVariantDataAddress::Compare(VAR_INT_LIST *val)
{
    if (vt != VDOT_INT_LIST)
    {
        return false;
    }

    if (pDoubleList->nCount != val->nCount)
    {
        return false;
    }

    return memcmp(pIntList->pnBuffer, val->pnBuffer, pIntList->nCount * sizeof(int));
}

long CVariantDataAddress::Compare(const CString &val)
{
	if (vt != VDOT_CSTRING)
	{
		throw(-1);
	}

	long lCompare = (*pString == val);

	return lCompare;
}
long CVariantDataAddress::Compare(bool val)
{
	if (vt != VDOT_BOOL)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (*boolVal != val)
	{
		lCompare = 1;
	}
	else
	{
		lCompare = 0;
	}

	return lCompare;
}
long CVariantDataAddress::Compare(const CVariantDataAddress &val)
{
	if (vt != val.vt)
	{
		throw(-1);
	}
	
	long lCompare = 0;
	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		lCompare = Compare(val.bVal);
		break;
	case VDOT_SHORT://2
		lCompare = Compare(val.nVal);
		break;
	case VDOT_LONG://3
		lCompare = Compare(val.lVal);
		break;
	case VDOT_FLOAT://4
		lCompare = Compare(val.fltVal);
		break;
	case VDOT_DOUBLE://5
		lCompare = Compare(val.dblVal);
		break;
	case VDOT_INT://6
		lCompare = Compare(val.intVal);
		break;
	case VDOT_CHARSTR://7
		lCompare = Compare(*(val.pszVal));
		break;
	case VDOT_N64://7
		lCompare = Compare(*(val.n64Val));
		break;
	case VDOT_DWORD://7
		lCompare = Compare(*(val.dwVal));
		break;

    case VDOT_DOUBLE_LIST:
        lCompare = Compare(val.pDoubleList);
        break;

    case VDOT_FLOAT_LIST:
        lCompare = Compare(val.pFloatList);
        break;

    case VDOT_INT_LIST:
        lCompare = Compare(val.pIntList);
        break;

    default:
		break;
	}
	return lCompare;	
}

#include "../MemBuffer/ExpandMemBuf.h"
void CVariantDataAddress::ToString(VAR_DOUBLE_LIST *val, CString &strVal)
{
    if (val->nCount == 0)
    {
        strVal.Format(_T("%d$"), val->nCount);
        return;
    }

    long nBufferLen = val->nCount * 30;
    CExpandMemBuf oBuff;
    oBuff.SetBufferLength(nBufferLen);
    oBuff.ZeroBuffer();

   oBuff.AddData(val->nCount, '$');

    long k = 0;

    for (k=0; k<val->nCount; k++)
    {
        oBuff.AddData(val->pfBuffer[k], '$');
    }

    strVal = (char*)oBuff.GetBuffer();
}

void CVariantDataAddress::ToString(VAR_FLOAT_LIST *val, CString &strVal)
{
    if (val->nCount == 0)
    {
        strVal.Format(_T("%d$"), val->nCount);
        return;
    }

    long nBufferLen = val->nCount * 30;
    CExpandMemBuf oBuff;
    oBuff.SetBufferLength(nBufferLen);
    oBuff.ZeroBuffer();

   oBuff.AddData(val->nCount, '$');

    long k = 0;

    for (k=0; k<val->nCount; k++)
    {
        oBuff.AddData(val->pfBuffer[k], '$');
    }

    strVal = (char*)oBuff.GetBuffer();
}

void CVariantDataAddress::ToString(VAR_INT_LIST *val, CString &strVal)
{
    if (val->nCount == 0)
    {
        strVal.Format(_T("%d$"), val->nCount);
        return;
    }

    long nBufferLen = val->nCount * 30;
    CExpandMemBuf oBuff;
    oBuff.SetBufferLength(nBufferLen);
    oBuff.ZeroBuffer();

   oBuff.AddData(val->nCount, '$');

    long k = 0;

    for (k=0; k<val->nCount; k++)
    {
        oBuff.AddData(val->pnBuffer[k], '$');
    }

    strVal = (char*)oBuff.GetBuffer();
}


CString CVariantDataAddress::ToString()
{
	CString strValue;

	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		strValue.Format(_T("%d"),*bVal);
		break;
	case VDOT_SHORT://2
		strValue.Format(_T("%d"), *nVal);
		break;
	case VDOT_LONG://3
		strValue.Format(_T("%d"), *lVal);
		break;
	case VDOT_DWORD:
		strValue.Format(_T("%d"), *dwVal);
		break;
	case VDOT_FLOAT://4
		strValue.Format(_T("%.4f"), *fltVal);
		break;
	case VDOT_DOUBLE://5
		strValue.Format(_T("%.4f"), *dblVal);
		break;
	case VDOT_INT://6
		strValue.Format(_T("%d"), *intVal);
		break;
	case VDOT_CHARSTR://7
		strValue = pszVal;
		break;
	case VDOT_N64://7
		strValue.Format(_T("%I64d"), *n64Val);
		break;
	case VDOT_CSTRING://7
		strValue = *pString;
		break;

    case VDOT_DOUBLE_LIST:
        ToString(pDoubleList, strValue);
        break;

    case VDOT_FLOAT_LIST:
        ToString(pFloatList, strValue);
        break;

    case VDOT_INT_LIST:
        ToString(pIntList, strValue);
        break;

    default:
		strValue = "";
		break;
	}

	return strValue;
}

CString CVariantDataAddress::ToString(const CString &strFormat)
{
	CString strValue;
	long nLen = strFormat.GetLength();

	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		strValue.Format(strFormat,*bVal);
		break;
	case VDOT_SHORT://2
		strValue.Format(strFormat, *nVal);
		break;
	case VDOT_LONG://3
		strValue.Format(strFormat, *lVal);
		break;
	case VDOT_DWORD:
		strValue.Format(strFormat, *dwVal);
		break;
	case VDOT_FLOAT://4
		strValue.Format(strFormat, *fltVal);
		break;
	case VDOT_DOUBLE://5
		strValue.Format(strFormat, *dblVal);
		break;
	case VDOT_INT://6
		strValue.Format(strFormat, *intVal);
		break;
	case VDOT_CHARSTR://7
		strValue.Format(strFormat, pszVal);
		break;
	case VDOT_N64://7
		strValue.Format(strFormat, *n64Val);
		break;
	case VDOT_CSTRING://7
		strValue = *pString;
		break;

    case VDOT_DOUBLE_LIST:
        ToString(pDoubleList, strValue);
        break;

    case VDOT_FLOAT_LIST:
        ToString(pFloatList, strValue);
        break;

    case VDOT_INT_LIST:
        ToString(pIntList, strValue);
        break;

    default:
		strValue = "";
		break;
	}

	return strValue;
}

unsigned int CVariantDataAddress::str_to_dword(const char *pstrValue)
{
	if (strlen(pstrValue) > 3)
	{
		if (pstrValue[0] == '0' && (pstrValue[1] == 'x' || pstrValue[1] == 'X') )
		{
			char *pEnd = NULL;
			return strtoul(pstrValue, &pEnd, 16);
		}
		else
		{
			return atol(pstrValue);
		}

	}
	else
	{
		return atol(pstrValue);
	}
}

void CVariantDataAddress::FromString(char *pszValue)
{
	ASSERT (pszValue != NULL);
	if (pszValue == NULL)
	{
		return;
	}
	
	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		*bVal = *pszValue;
		break;
	case VDOT_SHORT://2
		*nVal = (short)str_to_dword(pszValue);
		break;
	case VDOT_LONG://3
		*lVal = str_to_dword(pszValue);
		break;
	case VDOT_DWORD://3
		*dwVal = str_to_dword(pszValue);
		break;
	case VDOT_FLOAT://4
		*fltVal = (float)atof(pszValue);
		break;
	case VDOT_DOUBLE://5
		*dblVal = atof(pszValue);
		break;
	case VDOT_INT://6
		*intVal = str_to_dword(pszValue);
		break;
	case VDOT_CHARSTR://7
		strcpy(pszVal,pszValue);
		break;
	default:
		break;
	}	
}

#include "../MemBuffer/BufferBase.h"
void CVariantDataAddress::FromString(char *pszValue, VAR_DOUBLE_LIST *val)
{
    CBufferBase oBuffer;
    oBuffer.InitBuffer(pszValue);
    oBuffer.FormatBuffer('$');

    val->nCount = atof(oBuffer.GetString());
    val->pfBuffer = new double[val->nCount];
    memset(val->pfBuffer, 0, val->nCount * sizeof(double));
    long k = 0;

    for (k=0;k<val->nCount; k++)
    {
        if (! oBuffer.IsPoiterInBuffer())
        {
            break;
        }

        oBuffer.NextString();
        val->pfBuffer[k] = atof(oBuffer.GetString());
    }
}

void CVariantDataAddress::FromString(char *pszValue, VAR_FLOAT_LIST *val)
{
    CBufferBase oBuffer;
    oBuffer.InitBuffer(pszValue);
    oBuffer.FormatBuffer('$');

    val->nCount = atof(oBuffer.GetString());
    val->pfBuffer = new float[val->nCount];
    memset(val->pfBuffer, 0, val->nCount * sizeof(float));
    long k = 0;

    for (k=0;k<val->nCount; k++)
    {
        if (! oBuffer.IsPoiterInBuffer())
        {
            break;
        }

        oBuffer.NextString();
        val->pfBuffer[k] = (float)atof(oBuffer.GetString());
    }
}

void CVariantDataAddress::FromString(char *pszValue, VAR_INT_LIST *val)
{
    CBufferBase oBuffer;
    oBuffer.InitBuffer(pszValue);
    oBuffer.FormatBuffer('$');

    val->nCount = atof(oBuffer.GetString());
    val->pnBuffer = new int[val->nCount];
    memset(val->pnBuffer, 0, val->nCount * sizeof(int));
    long k = 0;

    for (k=0;k<val->nCount; k++)
    {
        if (! oBuffer.IsPoiterInBuffer())
        {
            break;
        }

        oBuffer.NextString();
        val->pnBuffer[k] = atoi(oBuffer.GetString());
    }
}



bool CVariantDataAddress::CompareValAddr(void* pValAddr)
{
	return (pValAddr == lVal);
}

void CVariantDataAddress::UpdateDefaultValue()
{
//	_n64Val = *n64Val;
}

bool CVariantDataAddress::IsValueChange()
{
/*	switch(vt)
    {
    case VDOT_UNSIGNEDCHAR://1
        return (*bVal != _bVal);
        break;
    case VDOT_SHORT://2
        return (*nVal != _nVal);
        break;
    case VDOT_LONG://3
        return (*lVal != _lVal);
        break;
    case VDOT_DWORD://3
        return (*dwVal != _dwVal);
        break;
    case VDOT_FLOAT://4
        return fabs(*fltVal - _fltVal) >= 0.00001;
        return (*fltVal != _fltVal);
        break;
    case VDOT_DOUBLE://5
        return (*dblVal != _dblVal);
        break;
    case VDOT_INT://6
        return (*intVal != _intVal);
        break;
    default:
        break;
    }
*/
    return TRUE;
}

void CVariantDataAddress::InitByDefault()
{
    //*n64Val = _n64Val;
}

float CVariantDataAddress::get_float()
{
    switch(vt)
    {
    case VDOT_UNSIGNEDCHAR://1
            return atof((char*)bVal);

    case VDOT_SHORT://2
            return *nVal;

    case VDOT_LONG://3
            return *lVal;

    case VDOT_DWORD://3
            return *dwVal;

    case VDOT_FLOAT://4
            return *fltVal;

    case VDOT_DOUBLE://5
            return *dblVal;

    case VDOT_INT://6
            return *intVal;

    case VDOT_CHARSTR://7
            atof(pszVal);

    default:
            return 0;

    }
}

