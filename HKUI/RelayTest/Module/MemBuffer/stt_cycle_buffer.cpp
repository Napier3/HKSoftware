//#include "StdAfx.h"
#include "../../../Module/OSInterface/QT/stdafx.h"
#include "stt_cycle_buffer.h"


void stt_cycle_buffer_increase_curr_index(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf)
{
	pCycleBuf->m_nCurrIndex++;

	if (pCycleBuf->m_nCurrIndex >= pCycleBuf->m_nMaxCount)
	{
		pCycleBuf->m_nCurrIndex = 0;
	}

	pCycleBuf->m_nCurrCount++;

	if (pCycleBuf->m_nCurrCount >= pCycleBuf->m_nMaxCount)
	{
		pCycleBuf->m_nCurrCount = pCycleBuf->m_nMaxCount;
	}
}

void stt_get_cycle_range_index(long nMaxCount, long nCurrCount, long nCurrIndex
							   , long nIndex
							   , long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	if (nCurrCount == nMaxCount)
	{
		if (nIndex <= nCurrIndex)
		{
			nBegin1 = nIndex;
			nEnd1 = nCurrIndex-1;
			nBegin2 = -1;
			nEnd2 = -1;
		}
		else
		{
			nBegin1 = nIndex;
			nEnd1 = nCurrCount-1;
			nBegin2 = 0;
			nEnd2 = nCurrIndex-1;
		}
	}
	else
	{
		nBegin1 = nIndex;
		nEnd1 = nCurrIndex-1;
		nBegin2 = -1;
		nEnd2 = -1;
	}
}

void stt_get_read_index_range(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf, long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2)
{
	long nCurrCount = pCycleBuf->m_nCurrCount;
	long nCurrIndex = pCycleBuf->m_nCurrIndex;
	long nCurrReadIndex = pCycleBuf->m_nCurrReadIndex;

	stt_get_cycle_range_index(pCycleBuf->m_nMaxCount, nCurrCount, nCurrIndex
		, nCurrReadIndex
		, nBegin1, nEnd1, nBegin2, nEnd2);
}

long stt_cycle_buffer_get_count(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf, long nIndexFrom)
{
	long nCurrCount = pCycleBuf->m_nCurrCount;
	long nCurrIndex = pCycleBuf->m_nCurrIndex;

	if (nCurrCount == pCycleBuf->m_nMaxCount)
	{
		if (nCurrIndex >= nIndexFrom)
		{
			return nCurrIndex - nIndexFrom;
		}
		else
		{
			return nCurrCount - nIndexFrom + nCurrIndex;
		}
	}
	else
	{
		if (nCurrIndex >= nIndexFrom)
		{
			return nCurrIndex - nIndexFrom;
		}
		else
		{
			return 0;
		}
	}
}

long stt_cycle_buffer_get_read_count(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf)
{
	return stt_cycle_buffer_get_count(pCycleBuf, pCycleBuf->m_nCurrReadIndex);
}

void stt_cycle_buffer_set_read_index(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf, long nIndex)	
{
	pCycleBuf->m_nCurrReadIndex = nIndex;	

	if (pCycleBuf->m_nCurrReadIndex >= pCycleBuf->m_nMaxCount) 
	{
		pCycleBuf->m_nCurrReadIndex = 0;
	}	
}

