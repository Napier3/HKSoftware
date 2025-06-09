#include "StdAfx.h"
#include "Protocol.h"

CProtocol::CProtocol(int m_iHead,int m_iLength)
{
	m_headStartPos  =  m_iHead;
	m_DataPackLength  = m_iLength;
	m_AbnormalType  =  0;
}

CProtocol::~CProtocol(void)
{

}

void CProtocol::SetAbronamlType(int m_Type)
{
	if (m_AbnormalType != 0)
	{
		return;
	}

	m_AbnormalType = m_Type;
}