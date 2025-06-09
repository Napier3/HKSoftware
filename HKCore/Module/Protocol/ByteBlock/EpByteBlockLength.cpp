#include "StdAfx.h"
#include "EpByteBlockLength.h"

CEpByteBlockLength::CEpByteBlockLength(BYTE byteVSQ)
{
	m_byteVSQ = byteVSQ;
	m_nSQ = (m_byteVSQ & 0x80) >> 7;
	m_nCount = m_byteVSQ & 0x7F;
}


CEpByteBlockLength::~CEpByteBlockLength(void)
{
	
}
