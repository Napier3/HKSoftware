#pragma once

#include "SttSmartTest.h"

class CXSmartTestEntry : public CSttSmartTest
{
public:
    CXSmartTestEntry();
    virtual ~CXSmartTestEntry();

	static long g_nXSttSmartTestEntryRef;
	static CXSmartTestEntry* g_pXSttSmartTestEntry;
	static CXSmartTestEntry* Create();
	static void Release();

	//virtual CString ValidFileName(const CString &strPath, const CString &strFileName, const CString &strProfix);
};