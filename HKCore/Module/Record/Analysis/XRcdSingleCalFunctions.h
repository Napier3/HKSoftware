// XRcdSingleCalFunctions.h: interface for the CXRcdSingleCalFunctions class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XRcdSingleCalFunctions_H__)
#define _XRcdSingleCalFunctions_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../RtMemBuffer/MemBufferDef.h"

//计算总有效值和相位
void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, unsigned short *pDataBuffer
							   , double dEffecValue, double &dEffecPhase
							   , DWORD *pdwFreqZeroPosition=NULL, UINT  *pnFreqZeroPosCount=NULL
							   , DWORD *pdwRefFreqZeroPosition=NULL, UINT  *pnRefFreqZeroPosCount=NULL
							   , double dRefFrequency=0, double dFrequency=0, long dwSampleRate=0);

void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, short *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition=NULL, UINT  *pnFreqZeroPosCount=NULL
							 , DWORD *pdwRefFreqZeroPosition=NULL, UINT  *pnRefFreqZeroPosCount=NULL
							 , double dRefFrequency=0, double dFrequency=0, long dwSampleRate=0);


void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, long *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition=NULL, UINT  *pnFreqZeroPosCount=NULL
							 , DWORD *pdwRefFreqZeroPosition=NULL, UINT  *pnRefFreqZeroPosCount=NULL
							 , double dRefFrequency=0, double dFrequency=0, long dwSampleRate=0);

void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, float *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition=NULL, UINT  *pnFreqZeroPosCount=NULL
							 , DWORD *pdwRefFreqZeroPosition=NULL, UINT  *pnRefFreqZeroPosCount=NULL
							 , double dRefFrequency=0, double dFrequency=0, long dwSampleRate=0);

void rt_CalEffecValue_Single(PRT_MEM_BUFFER_DATA_POS pDataPos, double *pDataBuffer
							 , double dEffecValue, double &dEffecPhase
							 , DWORD *pdwFreqZeroPosition=NULL, UINT  *pnFreqZeroPosCount=NULL
							 , DWORD *pdwRefFreqZeroPosition=NULL, UINT  *pnRefFreqZeroPosCount=NULL
							 , double dRefFrequency=0, double dFrequency=0, long dwSampleRate=0);


void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, unsigned short *pDataBuffer, double dEffecValue);
void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, short *pDataBuffer, double dEffecValue);
void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, long *pDataBuffer, double dEffecValue);
void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, float *pDataBuffer, double dEffecValue);
void rt_CalEffecValue_Quick(PRT_MEM_BUFFER_DATA_POS pDataPos, double *pDataBuffer, double dEffecValue);

#endif // !defined(_XRcdSingleCalFunctions_H__)
