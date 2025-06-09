#include "StdAfx.h"
#include "ProtoPkgProcessInterface.h"
#include "ProtoPkgProcess_DNP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CProtoPkgProcessInterface* pp_CreateProtoPkgProcess(char *pszProtoPkgPrcssID)
{
	if (stricmp(pszProtoPkgPrcssID, "dnp") == 0)
	{
		return new CProtoPkgProcess_DNP();
	}
	
	return NULL;
}



