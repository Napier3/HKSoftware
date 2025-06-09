#include "StdAfx.h"
#include "EpCmmNetServer.h"

CEpCmmNetServer::CEpCmmNetServer(void)
{
	m_nPort = 0;
	m_nMulticastPort = 0;
}

CEpCmmNetServer::~CEpCmmNetServer(void)
{
	RemoveAll();
}

