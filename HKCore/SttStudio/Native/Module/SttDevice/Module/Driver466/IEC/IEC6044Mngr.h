#ifndef IEC6044MNGR_H
#define IEC6044MNGR_H

#include "IEC6044MngrBase.h".h"

//配网FT3
class CIEC6044Mngr: public CIEC6044MngrBase
{
public:
	CIEC6044Mngr();
	virtual ~CIEC6044Mngr();

public:
//	long m_nVoltDrvPos[18];//18U
//	long m_nCurrDrvPos[18];//18I

	virtual void InitFT3Rates(CIecCfgSmvRates *pIecSmvRates);//初始化FT3码值对应关系
	virtual void InitChanelMap();
	virtual void InitFT3ChanelType();
	virtual QString GetFt3ChannelType(int nChannelType, int nFT3ChannelTypePos);
};

#endif
