#include "stdafx.h"
#include "SttXftpServerSocketBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BOOL CSttXftpServerSocketBase::g_bUseRelRootPath = TRUE;

CSttXftpServerSocketBase::CSttXftpServerSocketBase()
{
	strcpy(DEFAULT_HOME_DIR, "C:\\Temp");

}

CSttXftpServerSocketBase::~CSttXftpServerSocketBase()
{

}