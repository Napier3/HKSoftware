#pragma once


#include "TestControlBase.h"

//×ÊÔ´ÇëÇó
class CTestItemExec_ResReq : public CBaseList
{
private:
	CTestItemExec_ResReq();
	virtual ~CTestItemExec_ResReq();

	static long g_nCTestItemExec_ResReq;
	static CTestItemExec_ResReq *g_pCTestItemExec_ResReq;

public:
	static void Create();
	static void Release();

	static void TestItem(CTestControlBase *pTestControl, CHdResReqest *pTestItem);

protected:
	CTestControlBase *m_pTestControl;
	CHdResReqest *m_pTestItem;


protected:
	

};

