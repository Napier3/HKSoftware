#include "stdafx.h"
#include "ItemGenRsltExpr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CItemGenRsltExpr::CItemGenRsltExpr()
{

}


CItemGenRsltExpr::~CItemGenRsltExpr()
{
	
}

CBaseObject* CItemGenRsltExpr::Clone()
{
	CItemGenRsltExpr* pNew = new CItemGenRsltExpr();
	Copy(pNew);

	return pNew;
}