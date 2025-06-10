#pragma once

//2020-10-22  lijunqing
typedef struct stt_cycle_buffer_head_def
{
	long m_nLockFlag; //访问的时候，加锁的标记
	long m_nMaxCount;
	long m_nCurrIndex;
	long m_nCurrCount;

	long m_nCurrReadIndex;  //当前写入数据库的位置



}STT_CYCLE_BUFFER_HEAD_DEF, *PSTT_CYCLE_BUFFER_HEAD_DEF;

void stt_cycle_buffer_increase_curr_index(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf);

void stt_get_cycle_range_index(long nMaxCount, long nCurrCount, long nCurrIndex
							   , long nIndex
							   , long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);

void stt_get_read_index_range(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf, long &nBegin1, long &nEnd1, long &nBegin2, long &nEnd2);
long stt_cycle_buffer_get_count(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf, long nIndexFrom);
long stt_cycle_buffer_get_read_count(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf);
void stt_cycle_buffer_set_read_index(PSTT_CYCLE_BUFFER_HEAD_DEF pCycleBuf, long nIndex);
