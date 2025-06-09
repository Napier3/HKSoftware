#include "StdAfx.h"
#include "EpByteBlockDataSet.h"


CEpByteBlockDataSet::CEpByteBlockDataSet()
{
	m_pCurrData = NULL;
}

CEpByteBlockDataSet::~CEpByteBlockDataSet(void)
{
	
}

CEpByteBlockData* CEpByteBlockDataSet::AddNewData(long nIndex)
{
	m_pCurrData = new CEpByteBlockData(nIndex);
	AddTail(m_pCurrData);
	return m_pCurrData;
}

