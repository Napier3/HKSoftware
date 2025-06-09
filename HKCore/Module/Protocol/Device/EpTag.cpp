#include "stdafx.h"
#include "EpTag.h"


CEpTag::CEpTag()
{

}

CEpTag::~CEpTag()
{

}


CEpTag::CEpTag(unsigned char *val)
{
	(*this) = val;
}

CEpTag::CEpTag(short *val)
{
	(*this) = val;
}

CEpTag::CEpTag(long *val)
{
	(*this) = val;
}

CEpTag::CEpTag(float *val)
{
	(*this) = val;
}

CEpTag::CEpTag(double *val)
{
	(*this) = val;
}

CEpTag::CEpTag(int *val)
{
	(*this) = val;
}

CEpTag::CEpTag(CString *val)
{
	(*this) = val;
}

CEpTag::CEpTag(const CEpTag &val)
{
	(*this) = val;
}

void CEpTag::operator= (unsigned char *val)
{
	vt = EPDT_UNSIGNEDCHAR;
	bVal = val;
}

void CEpTag::operator= (short *val)
{
	vt = EPDT_SHORT;
	nVal = val;
}

void CEpTag::operator= (long *val)
{
	vt = EPDT_LONG;
	lVal = val;
}

void CEpTag::operator= (float *val)
{
	vt = EPDT_FLOAT;
	fltVal = val;
}

void CEpTag::operator= (double *val)
{
	vt = EPDT_DOUBLE;
	dblVal = val; 
}

void CEpTag::operator= (int *val)
{
	vt = EPDT_INT;
	intVal = val;
}

void CEpTag::operator= (CString *val)
{
	vt = EPDT_STRING;
	pszString = val;
}

void CEpTag::operator= (const CEpTag &val)
{
	switch(val.vt) 
	{
	case EPDT_UNSIGNEDCHAR://1
		(*this) = val.bVal;
		break;
	case EPDT_SHORT://2
		(*this) = val.nVal;
		break;
	case EPDT_LONG://3
		(*this) = val.lVal;
		break;
	case EPDT_FLOAT://4
		(*this) = val.fltVal;
		break;
	case EPDT_DOUBLE://5
		(*this) = val.dblVal;
		break;
	case EPDT_INT://6
		(*this) = val.intVal;
		break;
	case EPDT_STRING://7
		(*this) = val.pszString;
		break;
	default:
		break;
	}
}