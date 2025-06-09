#include "stdafx.h"
#include "MqttEdgePkgBase.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CMqttEdgePkgBase::CMqttEdgePkgBase()
{
	m_pBuffer = &m_oMqttData;
}

CMqttEdgePkgBase::~CMqttEdgePkgBase()
{

}