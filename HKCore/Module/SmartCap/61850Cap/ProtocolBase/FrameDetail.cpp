// FrameDetail.cpp: implementation of the CFrameDetail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FrameDetail.h"
// #include "ProtocolBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFrameDetail::CFrameDetail()
{ 
	m_pBuffer = NULL;
	m_pCurrByteBlocks = NULL;
}

CFrameDetail::~CFrameDetail()
{

}
