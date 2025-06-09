// EpProtocolBas.cpp: implementation of the CEpProtocol101 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpProtocol101.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpProtocol101::CEpProtocol101()
{ 
	AddParseFrame(new CEp101Frame_E5());
	AddParseFrame(new CEp101Frame_10());
	AddFrameGroup(new CEp101Frame_Group_68());

	m_nYxAddr  = 33;
	m_nYcAddr  = 16385;
	m_nYtAddr  = 25089;
	m_nODDRLen = 2;

	m_dwPrototcol = EPPROTOCOL_101;
	m_strName = _T("101");
	m_strID = m_strName;
}

CEpProtocol101::~CEpProtocol101()
{

}


void CEpProtocol101::InitDeviceNodes()
{
	CEpDevice101 *pDevice = (CEpDevice101*)m_pDevice;

// 	m_pYcDataNode = pDevice->GetYc();
// 	m_pYxDataNode = pDevice->GetYx();
// 	m_pYkDataNode = pDevice->GetYk();
// 	m_pYtDataNode = pDevice->GetYt();

	
}

