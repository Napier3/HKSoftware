#include "stdafx.h"
#include "XSmartTest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXSmartTest *CXSmartTest::g_pXSmartTest=NULL;
long CXSmartTest::g_nXSmartTestRef = 0;

CXSmartTest* CXSmartTest::Create()
{
    g_nXSmartTestRef++;

    if (g_nXSmartTestRef == 1)
    {
        g_pXSmartTest=new CXSmartTest;
    }

    return g_pXSmartTest;
}

void CXSmartTest::Release()
{
    g_nXSmartTestRef--;

    if(g_nXSmartTestRef == 0)
	{
        delete g_pXSmartTest;
        g_pXSmartTest=NULL;
	}
}

CXSmartTest::CXSmartTest()
{
  
}

CXSmartTest::~CXSmartTest()
{

}
