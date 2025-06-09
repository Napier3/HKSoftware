#include "StdAfx.h"
#include "EpByteBlockVSQ.h"

CEpByteBlockVSQ::CEpByteBlockVSQ(BYTE byteVSQ)
{
	m_byteVSQ = byteVSQ;
	m_nSQ = (m_byteVSQ & 0x80) >> 7;
	m_nCount = m_byteVSQ & 0x7F;

	AddBbInfor(_T("SQ"), m_nSQ, 7);
	AddBbInfor(_T("Count"), m_nCount, 6, 0);
}


CEpByteBlockVSQ::~CEpByteBlockVSQ(void)
{
	
}
