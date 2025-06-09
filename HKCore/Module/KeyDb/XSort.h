#pragma once
#include "XMatchList.h"

// CXSort

class CXSort 
{
public:
	CXSort();
	virtual ~CXSort();

	void Sort(CXMatchList *pMatchList);
	int NumOfKeys(CExBaseList *pList);
	DWORD *m_pdwSortBuffer;
	long  m_nSortCount;

};


