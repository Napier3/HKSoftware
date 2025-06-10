#ifndef IEC6044COMMNGR_H
#define IEC6044COMMNGR_H


#include "IEC6044MngrBase.h"
//��ֱFT3

class CIEC6044ComMngr: public CIEC6044MngrBase
{
public:
	CIEC6044ComMngr();
	virtual ~CIEC6044ComMngr();

//	long m_nVoltDrvPos[12];//12U
//    long m_nCurrDrvPos[18];//18I
	virtual void InitFT3Rates(CIecCfgSmvRates *pIecSmvRates);//��ʼ��FT3��ֵ��Ӧ��ϵ
	virtual void InitChanelMap();
	virtual void InitFT3ChanelType();
	virtual QString GetFt3ChannelType(int nChannelType, int nFT3ChannelTypePos);
};

#endif
