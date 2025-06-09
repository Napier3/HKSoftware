#ifndef IEC61850CFGMNGR_H
#define IEC61850CFGMNGR_H

#include "QMap"
#include "QtCore"
#include "QObject"
#include "IEC/IECGooseMngr.h"
#include "IEC/IEC6044Mngr.h"
#include "IEC/IEC6044ComMngr.h"
#include "IEC/IEC6044MngrBase.h"
#include "IEC/IEC92Mngr.h"
#include "IEC/IEC2MComMngr.h"
#include "../../SttDeviceBase.h"

class CIEC61850CfgMngr: public QObject
{
public:
	explicit CIEC61850CfgMngr(QObject *parent = 0);
	~CIEC61850CfgMngr();

public:
	CIecCfgDatasMngr m_oIecCfgDatasMngr;
	DrvGseChgParas	 *m_pGseChgParas;	
	CIECGooseMngr m_oGooseMngr;
	CIEC92Mngr m_o92Mngr;
	CIEC6044MngrBase *m_p6044MngrBase;
	CIEC6044ComMngr m_o6044ComMngr;//ÈáÖ±FT3
	CIEC6044Mngr m_o6044Mngr;//ÆÕÍ¨FT3
	CIECStable2MComMngr m_oStable2MMngr;
	long m_nUseSmv92;
	Drv_IECConfig *m_pIECConfig;
	Drv_IECConfigFt3 *m_pIECConfigFt3;
	Drv_IECConfig_2M *m_pIECConfig_2M;
	unsigned int m_nSysParasFT3baud;

	void SetGseOutMap();
	void SetGooseSub();
	void SetRecordIecIn();
	void SetFT3SubMap();
	int GetGseSubCnt()
	{
		if(gsesub == NULL)
		{
			return 0;
		}

		return gsesub->ncount;
	}
	void InitDigitalModulesInfo();
	BOOL DealSmvAbnPacket(StructComAbn *pSvItems, tmt_StateAbnormalSMV oTmtAbnPara, tmt_sv_92 &oTMtSmvAbn, unsigned int nQuality[50]);
	void DealSmvAbnConfig(SendConfSV *pSVCfg, unsigned int nGroup, unsigned int nSmvAbnType, unsigned int nSmvAbnValue, BOOL bIsDefault = FALSE);
	BOOL DealGseAbnConfig(StructComAbn *pGSItem, tmt_StatePara  *pTmt_paraState, tmt_StatePara  *pTmt_paraPreState);
public:
	virtual void InitIEC61850Para();
private:
	FiberConf *fiber;
	Ft3SubDatas *ft3subs;
	IecRecvCfg *gsesub;
	SendConfSV *confsv;
	SendConfGSE *confgse;
	SendConfFT3 *confFt3;
	Drv_GSOutMap *stMaps;
	SvConfigTotal m_oSvCfgTotal;

	void FiberClose();
	void FiberOpen();
	void InitIECConfig();
	void AfterInitIEC61850();
	void GetSysParas();
};

#endif
