#include "StdAfx.h"
#include "Packet.h"

CPacket::CPacket(int nHead,  int nLength)
{
	m_nHeadStartPos  =    nHead;
	m_nDataPackLength  = nLength;
	m_nAbnormalType  =  0;
}

CPacket::~CPacket(void)
{

}

void CPacket::SetAbronamlType(int nType)
{
	if (m_nAbnormalType != 0)
	{
		return;
	}

	m_nAbnormalType = nType;
}

CPacket::CPacket(BYTE * pBuffer,  int nHead,  int nLength)
{
	m_pBuffer = pBuffer;
	m_nHeadStartPos  =    nHead;
	m_nDataPackLength  = nLength;
	m_nAbnormalType  =  0;
}
