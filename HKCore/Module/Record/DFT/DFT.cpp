// DFT.cpp: implementation of the CDFT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "DFT.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDFT* CDFT::g_pDft = NULL;
long CDFT::m_nDftRef = 0;

CDFT::CDFT()
{
	m_pCos=NULL;
	m_pSin=NULL;
	m_nCalPos = 0;
	m_nMaxDegree = 100;	
	m_nDataLength = 0;

	m_pdSin = NULL;
	m_pdCos = NULL;
	m_nDftCalGap = 1;
	InitSinCos();

	m_pDftShort = CDFT_Short::CreateDft(m_pdSin, m_pdCos);
	m_pDftLong = CDFT_Long::CreateDft(m_pdSin, m_pdCos);
}

CDFT::~CDFT()
{
	TermTriangle();
	ClearSinCos();

	CDFT_Short::ReleaseDFT();
	CDFT_Long::ReleaseDFT();
}

CDFT* CDFT::CreateDft()
{
	m_nDftRef++;

	if (m_nDftRef == 1)
	{
		ASSERT (g_pDft == NULL);
		g_pDft = new CDFT();
	}

	return g_pDft;
}

CDFT* CDFT::GetDft()
{
	//ASSERT( g_pDft != NULL );
	return g_pDft;
}

//只在程序退出时调用
void CDFT::ReleaseDFT()
{
	m_nDftRef--;

	if (m_nDftRef != 0)
	{
		return;
	}

	if (g_pDft != NULL)
	{
		g_pDft->TermTriangle();
		g_pDft->ClearSinCos();
		delete g_pDft;
		g_pDft = NULL;
	}
}
