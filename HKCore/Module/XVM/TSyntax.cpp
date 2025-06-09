#include "stdafx.h"
#include "TSyntax.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CTSyntax::CTSyntax(const char* pszError, int nLineIndex, long nType)
{
	strcpy(m_pszError, pszError);
	int iLen = strlen(m_pszError);
	m_nLineIndex = nLineIndex;
	m_pszFuncName[0] = 0;
	m_nType = nType;

	char *p = m_pszError;

	while (*p != 0)
	{
		if (*p == '\t')
		{
			*p = ' ';
		}
		p++;
	}
}
