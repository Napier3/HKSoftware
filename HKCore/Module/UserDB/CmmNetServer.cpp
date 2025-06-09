#include "StdAfx.h"
#include "CmmNetServer.h"

CCmmNetServer::CCmmNetServer(void)
{
	m_nPort = 0;
	m_nMulticastPort = 0;
}

CCmmNetServer::~CCmmNetServer(void)
{
	RemoveAll();
}

