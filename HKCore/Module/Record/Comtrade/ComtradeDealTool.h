#pragma once

#include "ComtradeMngr.h"

class CComtradeDealTool
{
public:
	CComtradeDealTool(void);
	virtual ~CComtradeDealTool(void);

	CComtradeAnalogData* AddAnalogChannelI0(CRcdComtradeFile *pComtradeFile,long nChannelIndexIa,long nChannelIndexIb,long nChannelIndexIc);
	CComtradeAnalogData* AddAnalogChannelU0(CRcdComtradeFile *pComtradeFile,long nChannelIndexUa,long nChannelIndexUb,long nChannelIndexUc);
	void DeleteComtradeChannel(CRcdComtradeFile *pSrcRcdFile,CComtradeAnalogData *pComtradeChannel);
	void UpdateAllChannelIndexs(CRcdComtradeFile *pComtradeFile);

protected:
	void SetZeroValue(CComtradeAnalogData *pPhaseN,CComtradeAnalogData *pPhaseA,CComtradeAnalogData *pPhaseB,CComtradeAnalogData *pPhaseC,long nTotalPoints);
	void SetZeroValue_Short(CComtradeAnalogData *pPhaseN,CComtradeAnalogData *pPhaseA,CComtradeAnalogData *pPhaseB,CComtradeAnalogData *pPhaseC,long nTotalPoints);
	void SetZeroValue_Long(CComtradeAnalogData *pPhaseN,CComtradeAnalogData *pPhaseA,CComtradeAnalogData *pPhaseB,CComtradeAnalogData *pPhaseC,long nTotalPoints);
};
