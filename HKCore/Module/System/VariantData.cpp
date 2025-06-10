// VariantData.cpp: implementation of the CVariantData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VariantData.h"
#include "../API/StringApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVariantData::CVariantData()
{
	vt = VDOT_NULL;
	dblVal = NULL;
}

CVariantData::~CVariantData()
{
	Free();
}

CVariantData::CVariantData(unsigned char val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(short val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(long val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(DWORD val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(WORD val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(float val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(double val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(int val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(volatile __int64 val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(const CString &val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

CVariantData::CVariantData(const CVariantData &val)
{
	vt = VDOT_NULL;
	(*this) = val;
}

void CVariantData::operator= (unsigned char val)
{
	Free();
	vt = VDOT_UNSIGNEDCHAR;
	bVal = val;
}

void CVariantData::operator= (short val)
{
	Free();
	vt = VDOT_SHORT;
	nVal = val;
}

void CVariantData::operator= (long val)
{
	Free();
	vt = VDOT_LONG;
	lVal = val;
}

void CVariantData::operator= (DWORD val)
{
	Free();
	vt = VDOT_LONG;
	dwVal = val;
}

void CVariantData::operator= (WORD val)
{
	Free();
	vt = VDOT_LONG;
	dwVal = val;
}

void CVariantData::operator= (float val)
{
	Free();
	vt = VDOT_FLOAT;
	fltVal = val;
}

void CVariantData::operator= (double val)
{
	Free();
	vt = VDOT_DOUBLE;
	dblVal = val; 
}

void CVariantData::operator= (int val)
{
	Free();
	vt = VDOT_INT;
	intVal = val;
}

void CVariantData::operator= (volatile __int64 val)
{
	Free();
	vt = VDOT_N64;
	n64Val = val;
}

void CVariantData::operator= (const CString &val)
{
	Free();
	vt = VDOT_CSTRING;
	pString = new CString;
	*pString = val;
}

void CVariantData::operator= (const CVariantData &val)
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
	case VDOT_CSTRING://7
		(*this) = *val.pString;
		break;
	case VDOT_DWORD://7
		(*this) = val.dwVal;
		break;
	case VDOT_WORD://7
		(*this) = val.wVal;
		break;
	default:
		break;
	}
}

int CVariantData::operator== (unsigned char val)
{
	if (vt != VDOT_UNSIGNEDCHAR)
	{
		throw(-1);
	}
	
	return (bVal == val);
}

int CVariantData::operator== (short val)
{
	if (vt != VDOT_SHORT)
	{
		throw(-1);
	}
	
	return (nVal == val);
}

int CVariantData::operator== (long val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}
	
	return (lVal == val);
}

int CVariantData::operator== (DWORD val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}

	return (dwVal == val);
}

int CVariantData::operator== (WORD val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}

	return (wVal == val);
}

int CVariantData::operator== (float val)
{
	if (vt != VDOT_FLOAT)
	{
		throw(-1);
	}
	
	return (fltVal == val);
}

int CVariantData::operator== (double val)
{
	if (vt != VDOT_DOUBLE)
	{
		throw(-1);
	}
	
	return (dblVal == val);
}

int CVariantData::operator== (int val)
{
	if (vt != VDOT_INT)
	{
		throw(-1);
	}
	
	return (intVal == val);
}

int CVariantData::operator== (volatile __int64 val)
{
	if (vt != VDOT_N64)
	{
		throw(-1);
	}

	return (n64Val == val);
}

int CVariantData::operator== (const CString &val)
{
	if (vt != VDOT_CSTRING)
	{
		throw(-1);
	}

	return (*pString == val);
}

int CVariantData::operator== (const CVariantData &val)
{
	if (vt != val.vt)
	{
		throw(-1);
	}

	int bTrue = FALSE;
	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		bTrue = ((*this) == val.bVal);
		break;
	case VDOT_SHORT://2
		bTrue = ((*this) == val.nVal);
		break;
	case VDOT_LONG://3
		bTrue = ((*this) == val.lVal);
		break;
	case VDOT_FLOAT://4
		bTrue = ((*this) == val.fltVal);
		break;
	case VDOT_DOUBLE://5
		bTrue = ((*this) == val.dblVal);
		break;
	case VDOT_INT://6
		bTrue = ((*this) == val.intVal);
		break;
	case VDOT_CSTRING://7
		bTrue = ((*this) == *val.pString);
		break;
	case VDOT_N64://7
		bTrue = ((*this) == val.n64Val);
		break;
	case VDOT_DWORD://7
		bTrue = ((*this) == val.dwVal);
		break;
	case VDOT_WORD://7
		bTrue = ((*this) == val.wVal);
		break;
	default:
		break;
	}
	return bTrue;
}

long CVariantData::Compare(unsigned char val)
{
	if (vt != VDOT_UNSIGNEDCHAR)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (bVal > val)
	{
		lCompare = 1;
	}
	else if (bVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}

	return lCompare;
}

long CVariantData::Compare(short val)
{
	if (vt != VDOT_SHORT)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (nVal > val)
	{
		lCompare = 1;
	}
	else if (nVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantData::Compare(long val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (lVal > val)
	{
		lCompare = 1;
	}
	else if (lVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantData::Compare(DWORD val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (dwVal > val)
	{
		lCompare = 1;
	}
	else if (dwVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}

	return lCompare;
}

long CVariantData::Compare(WORD val)
{
	if (vt != VDOT_LONG)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (wVal > val)
	{
		lCompare = 1;
	}
	else if (wVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}

	return lCompare;
}

long CVariantData::Compare(float val)
{
	if (vt != VDOT_FLOAT)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (fltVal > val)
	{
		lCompare = 1;
	}
	else if (fltVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantData::Compare(double val)
{
	if (vt != VDOT_DOUBLE)
	{
		throw(-1);
	}
	long lCompare = 0;
	if (dblVal > val)
	{
		lCompare = 1;
	}
	else if (dblVal < val)
	{
		lCompare = -1;
	}
	else
	{
		lCompare = 0;
	}
	
	return lCompare;
}

long CVariantData::Compare(int val)
{
	throw(-1);
	
	return 0;
}
long CVariantData::Compare(volatile __int64 val)
{
	throw(-1);

	return 0;
}

long CVariantData::Compare(const CString &val)
{
	if (vt != VDOT_CSTRING)
	{
		throw(-1);
	}

	long lCompare = _P_CompareString(*pString ,val); //(*pString == val);

	return lCompare;
}

long CVariantData::Compare(const CVariantData &val)
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
	case VDOT_N64://7
		lCompare = Compare((val.n64Val));
		break;
	case VDOT_DWORD://7
		lCompare = Compare((val.dwVal));
		break;
	case VDOT_WORD://7
		lCompare = Compare((val.wVal));
		break;
	default:
		break;
	}
	return lCompare;	
}

CString CVariantData::ToString()
{
	CString strValue;

	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		strValue.Format(_T("%d"),bVal);
		break;
	case VDOT_SHORT://2
		strValue.Format(_T("%d"),nVal);
		break;
	case VDOT_LONG://3
		strValue.Format(_T("%d"),lVal);
		break;
	case VDOT_DWORD:
		strValue.Format(_T("%d"),dwVal);
		break;
	case VDOT_WORD:
		strValue.Format(_T("%d"),wVal);
		break;
	case VDOT_FLOAT://4
		strValue.Format(_T("%.4f"),fltVal);
		break;
	case VDOT_DOUBLE://5
		strValue.Format(_T("%.4f"),dblVal);
		break;
	case VDOT_INT://6
		strValue.Format(_T("%d"),intVal);
		break;
	case VDOT_N64://7
		strValue.Format(_T("%I64d"),n64Val);
		break;
	case VDOT_CSTRING://7
		strValue = *pString;
		break;
	default:
		strValue = "";
		break;
	}

	return strValue;
}

CString CVariantData::ToString(const CString &strFormat)
{
	CString strValue;
	long nLen = strFormat.GetLength();

	switch(vt) 
	{
	case VDOT_UNSIGNEDCHAR://1
		strValue.Format(strFormat,bVal);
		break;
	case VDOT_SHORT://2
		strValue.Format(strFormat,nVal);
		break;
	case VDOT_LONG://3
		strValue.Format(strFormat,lVal);
		break;
	case VDOT_DWORD:
		strValue.Format(strFormat,dwVal);
		break;
	case VDOT_WORD:
		strValue.Format(strFormat,wVal);
		break;
	case VDOT_FLOAT://4
		strValue.Format(strFormat,fltVal);
		break;
	case VDOT_DOUBLE://5
		strValue.Format(strFormat,dblVal);
		break;
	case VDOT_INT://6
		strValue.Format(strFormat,intVal);
		break;
	case VDOT_N64://7
		strValue.Format(strFormat,n64Val);
		break;
	case VDOT_CSTRING://7
		strValue = *pString;
		break;
	default:
		strValue = "";
		break;
	}

	return strValue;
}
