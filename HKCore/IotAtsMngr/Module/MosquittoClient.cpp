#include "stdafx.h"
#include "MosquittoClient.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CMosquittoClient::CMosquittoClient()
{

}

CMosquittoClient::~CMosquittoClient()
{
	m_oTopics.DeleteChildren();
}
