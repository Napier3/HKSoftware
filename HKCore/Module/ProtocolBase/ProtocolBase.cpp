// ProtocolBase.cpp: implementation of the CProtocolBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ProtocolBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProtocolBase::CProtocolBase()
{ 
	memset(&m_bufPos, 0, sizeof(EPBUFFERPOS));
}

CProtocolBase::~CProtocolBase()
{
	Ep_ZeroEpBufferPos(&m_bufPos);
}
