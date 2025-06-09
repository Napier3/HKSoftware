#include "StdAfx.h"
#include "EpByteBlockQDS.h"

CEpByteBlockQDS::CEpByteBlockQDS(BYTE byteQDS, BOOL bAddDetail)
{
	m_byteOV = (byteQDS & 0x01)==0?0:1;
	m_byteBL = (byteQDS & 0x10)==0?0:1;
	m_byteSB = (byteQDS & 0x20)==0?0:1;
	m_byteNT = (byteQDS & 0x40)==0?0:1;
	m_byteIV = (byteQDS & 0x80)==0?0:1;

	if (bAddDetail)
	{
		AddBbInfor(g_strEpQDS_OV, m_byteOV, 0);
		AddBbInfor(g_strEpQDS_BL, m_byteBL, 4);
		AddBbInfor(g_strEpQDS_SB, m_byteSB, 5);
		AddBbInfor(g_strEpQDS_NT, m_byteNT, 6);
		AddBbInfor(g_strEpQDS_IV, m_byteIV, 7);
	}
}


CEpByteBlockQDS::~CEpByteBlockQDS()
{
	
}
