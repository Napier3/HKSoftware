#include "StdAfx.h"
#include "EpByteBlockQOS.h"

CEpByteBlockQOS::CEpByteBlockQOS(BYTE byteQOS, BOOL bAddDetail)
{
	m_byteQL = byteQOS & 0x7F;
	m_byteSE = (byteQOS & 0x80)==0?0:1;

	if (bAddDetail)
	{
		AddBbInfor(g_strEpQOS_SE, m_byteSE, 7);
		AddBbInfor(g_strEpQOS_QL, m_byteQL, 0, 6);
	}
}


CEpByteBlockQOS::~CEpByteBlockQOS()
{
	
}
