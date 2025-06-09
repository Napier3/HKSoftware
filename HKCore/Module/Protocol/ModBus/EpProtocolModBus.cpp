// EpProtocolBas.cpp: implementation of the CEpProtocolModBus class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EpProtocolModBus.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEpProtocolModBus::CEpProtocolModBus()
{ 
	//AddParseFrame(new CEpModBusFrame_E5());
	
}

CEpProtocolModBus::~CEpProtocolModBus()
{

}


void CEpProtocolModBus::InitDeviceNodes()
{
	CEpDeviceModBus *pDevice = (CEpDeviceModBus*)m_pDevice;
	
}

