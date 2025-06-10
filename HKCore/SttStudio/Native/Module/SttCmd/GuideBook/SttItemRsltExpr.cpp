#include "stdafx.h"
#include "SttItemRsltExpr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSttItemRsltExpr::CSttItemRsltExpr()
{

}


CSttItemRsltExpr::~CSttItemRsltExpr()
{
	
}

CBaseObject* CSttItemRsltExpr::Clone()
{
	CSttItemRsltExpr* pNew = new CSttItemRsltExpr();
	Copy(pNew);

	return pNew;
}
