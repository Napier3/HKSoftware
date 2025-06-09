// EpProtocol104.cpp: implementation of the CEpProtocol104 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpProtocol104.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpProtocol104::CEpProtocol104()
{ 
	AddParseFrame(new CEp104Frame_68_S());
	AddParseFrame(new CEp104Frame_68_U());
	AddFrameGroup(new CEp104Frame_Group_68());

	m_nYxAddr  = 1;
	m_nYcAddr  = 1793;
	m_nYtAddr  = 25089;
	m_nODDRLen = 3;

// 	m_pYcDataNode = NULL;
// 	m_pYxDataNode = NULL;
// 	m_pYkDataNode = NULL;
// 	m_pYtDataNode = NULL;
	m_dwPrototcol = EPPROTOCOL_104;
	m_strName = _T("104");
	m_strID = m_strName;
}

CEpProtocol104::~CEpProtocol104()
{

}


void CEpProtocol104::InitDeviceNodes()
{
	CEpDevice101 *pDevice = (CEpDevice101*)m_pDevice;

// 	m_pYcDataNode = pDevice->GetYc();
// 	m_pYxDataNode = pDevice->GetYx();
// 	m_pYkDataNode = pDevice->GetYk();
// 	m_pYtDataNode = pDevice->GetYt();

	
}

