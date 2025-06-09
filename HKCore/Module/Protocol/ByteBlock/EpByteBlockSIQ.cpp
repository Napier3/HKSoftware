#include "StdAfx.h"
#include "EpByteBlockSIQ.h"

#include "..\101\EpGlobalDefine_101.h"

CEpByteBlockSIQ::CEpByteBlockSIQ(BYTE byteSIQ)
{
	Ep101_GetSIQValue(byteSIQ, m_nSPI, m_nBL, m_nSB, m_nNT, m_nIV);

	AddBbInfor(g_strEpAsduSPI, m_nSPI, 0);
	AddBbInfor(g_strEpQDS_BL, m_nBL, 4);
	AddBbInfor(g_strEpQDS_SB, m_nSB, 5);
	AddBbInfor(g_strEpQDS_NT, m_nNT, 6);
	AddBbInfor(g_strEpQDS_IV, m_nIV, 7);

}


CEpByteBlockSIQ::~CEpByteBlockSIQ(void)
{
	
}
