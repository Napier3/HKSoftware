#ifndef IEC6044MNGR_H
#define IEC6044MNGR_H

#include "IEC6044MngrBase.h"

//配网FT3
class CIEC6044Mngr: public CIEC6044MngrBase
{
public:
	CIEC6044Mngr();
	virtual ~CIEC6044Mngr();

public:
//	long m_nVoltDrvPos[12];//12U
//	long m_nCurrDrvPos[24];//24I 保护+测量

	virtual void InitFT3Rates(CIecCfgSmvRates *pIecSmvRates);//初始化FT3码值对应关系
	virtual void InitChanelMap();
	virtual void InitFT3ChanelType();
	virtual QString GetFt3ChannelType(int nChannelType, int nFT3ChannelTypePos);

	virtual int GetFT3DelayTime(int nGroupIndex)
	{
		if(nGroupIndex < MAX_DIGITAL_GROUP_NUM)
		{
			return m_nDelayTime[nGroupIndex];
		}
		else
		{
			return 0;
		}
	}

public:
	virtual void Create6044ComSubTmtStruct(CIecCfg6044CommonInData *pIecData);
	virtual void Create6044ComByteArray(tmt_ft3_6044 otmt6044, QByteArray &m_oPackage);
private:
	void InsertCRCFlag_GDW60044_STD12Ch(QByteArray &oPackage);
};

#endif
