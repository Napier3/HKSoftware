//MyCalc.c
#include "stdafx.h"
#include "MyCalc.h"

CMyCalc::CMyCalc()
{
}

CMyCalc::~CMyCalc()
{
}

//////////////////////////////////////////////////////////////////////////
void CMyCalc::Long_to_Byte(long lTemp1, BYTE *buf)
{
	unsigned int iTemp1,iTemp2;
	
	iTemp2 = lTemp1 & 0x0ffff;
	iTemp1 = (lTemp1>>16) & 0x0ffff;
	buf[1] = iTemp1 & 0x0ff;
	buf[0] = (iTemp1>>8) & 0x0ff;
	buf[3] = iTemp2 & 0x0ff;
	buf[2] = (iTemp2>>8) & 0x0ff;
}

long CMyCalc::Byte_to_Long(BYTE *buf)
{
	unsigned int iTemp1,iTemp2;
	long lTemp1;
	
	iTemp1 = buf[0]*256 + buf[1];
	iTemp2 = buf[2]*256 + buf[3];
	lTemp1 = (long)(iTemp1 *65536 + iTemp2);
	return lTemp1;
}
