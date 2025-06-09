#include "StdAfx.h"
#include "EpByteBlockFloat.h"

CEpByteBlockFloat::CEpByteBlockFloat(float fValue, BOOL bAddDetail)
{
	m_fValue = fValue;

	if (bAddDetail)
	{
		AddBbInfor(g_strEpFloat, m_fValue, -1, -1);
	}
}


CEpByteBlockFloat::~CEpByteBlockFloat()
{
	
}
