// RtScript.cpp: implementation of the CRtScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RtScript.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtScript::CRtScript()
{
	m_strName = "RtScript";
	m_strID = m_strName;
}

CRtScript::~CRtScript()
{
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRtAttrScript::CRtAttrScript()
{
	m_strName = "RtAttrScript";
	m_strID = m_strName;
}

CRtAttrScript::~CRtAttrScript()
{
}
