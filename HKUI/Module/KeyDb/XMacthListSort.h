#pragma once
#include "XMatchList.h"

// CXSort

class CXMacthListSort 
{
public:
	CXMacthListSort();
	virtual ~CXMacthListSort();

	void Sort(CXMatchList *pMatchList);

private:
	void InitXMatchObjKeysLength();
    int GetKeysSumLength(CXKeyMatchRefList *pList);
	void Sort();
	DWORD *m_pdwSortBuffer;
	long  m_nSortCount;

	CXMatchList *m_pMatchList;
};


