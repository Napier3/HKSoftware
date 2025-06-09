#include "stdafx.h"
#include "SttSocketDataBase.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../Engine/SttTestEngineBase.h"
#include "../SttCmdToolMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttSocketDataBase::CSttSocketDataBase()
{
	m_nIDTester = 0;
	m_nSocketType = 0;

	m_pTestEngine = NULL;
	m_pUser = NULL;
	m_nSttCmdDataFormat = _PUGI_XML_TYPE_;
}

CSttSocketDataBase::~CSttSocketDataBase()
{
}

//////////////////////////////////////////////////////////////////////////
