#pragma once

#include "../../../../Module/Log/LogPrint.h"

class CListBoxLog : public CLogBase, public CListBox
{
public:
	CListBoxLog(void);
	~CListBoxLog(void);
public:
	virtual void LogString(long nLevel, const CString &strMsg);
};
