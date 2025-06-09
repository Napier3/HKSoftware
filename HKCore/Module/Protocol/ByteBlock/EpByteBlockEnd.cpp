#include "StdAfx.h"
#include "EpByteBlockEnd.h"

CEpByteBlockEnd::CEpByteBlockEnd(BYTE byteVSQ)
{
	m_byteVSQ = byteVSQ;
	m_nSQ = (m_byteVSQ & 0x80) >> 7;
	m_nCount = m_byteVSQ & 0x7F;
}


CEpByteBlockEnd::~CEpByteBlockEnd(void)
{
	
}
