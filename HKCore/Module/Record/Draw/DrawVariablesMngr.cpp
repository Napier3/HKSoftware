// DrawVariablesMngr.cpp: implementation of the CDrawVariablesMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DrawVariablesMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDrawVariablesMngr::CDrawVariablesMngr()
{
}

CDrawVariablesMngr::~CDrawVariablesMngr()
{
	m_listChild.DeleteAll();
}
