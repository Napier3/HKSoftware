#include "StdAfx.h"
#include "EpByteBlockTime.h"

CEpByteBlockTime::CEpByteBlockTime(EPTIME64 &tm, BOOL bAddDetail)
{
	m_tm = tm;
	
	if (bAddDetail)
	{
		AddBbInfor(g_strEpAsduTime, tm, -1, -1);
	}
}


CEpByteBlockTime::~CEpByteBlockTime(void)
{
	
}
