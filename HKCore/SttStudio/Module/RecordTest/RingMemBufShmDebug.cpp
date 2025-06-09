#include "stdafx.h"
#include "RingMemBufShmDebug.h"


CRingMemBufShmDebug::CRingMemBufShmDebug()
{
	m_pMemBufShmDebug = new char [DEFAULT_CIRCLEBUF_LEN];
}

CRingMemBufShmDebug::~CRingMemBufShmDebug()
{
	delete m_pMemBufShmDebug;
}


void CRingMemBufShmDebug::ShmCreateServer()
{
	Attatch(m_pMemBufShmDebug, DEFAULT_CIRCLEBUF_LEN, TRUE);
}

void CRingMemBufShmDebug::ShmCreateClient()
{
	Attatch(m_pMemBufShmDebug, DEFAULT_CIRCLEBUF_LEN, FALSE);
}

