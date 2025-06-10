#include "stdafx.h"

#include "SmvFrameBase.h"

//////////////////////////////////////////////////////////////////////////
//
CSmvFrameBase::CSmvFrameBase()
{
	m_SampleRate = 0;
	m_LastSmpCnt = 0;
	m_LostPPS = 0;

}

CSmvFrameBase::~CSmvFrameBase()
{

}
