#ifndef IEC6044MNGRBASE_H
#define IEC6044MNGRBASE_H

#include "QMap"
#include "QtCore"
#include "QObject"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonData.h"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonInData.h"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonCh.h"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfg6044CommonChIn.h"
#include "../../../../../../61850/Module/CfgDataMngr/IecCfgSmvRates.h"
#include "../IEC_GlobalDefine.h"

typedef struct
{
	double fRatio;
	int nSampleLen;
} FT3MapPointer;

typedef struct
{
	int nACDataPos;//
	int nACDataLen;//字节交流通道长度
	int nSmpcntPos ;//2字节计数器位置
	int nSmpcntType; //1 samplecount0-SMP_CNT 2:0-255 3:0-65535
	int nACDataEnd;
} FT3BlockInfo;

class CIEC6044MngrBase: public QObject
{
public:
	CIEC6044MngrBase();
	virtual ~CIEC6044MngrBase();

public:
	QVector<tmt_ft3_6044> data_6044;
	QVector<tmt_ft3_6044> data_6044Sub;

	void Init();
	long GetSample()
	{
		return m_nSample;
	}
	long GetBaudRate()
	{
		return m_nBaudRate;
	}

	virtual void Create6044ComTmtStruct(CIecCfg6044CommonData *pIecData);
	virtual void Create6044ComSubTmtStruct(CIecCfg6044CommonInData *pIecData);
	virtual void Create6044ComByteArray(tmt_ft3_6044 otmt6044, QByteArray &m_oPackage);	
	QMap<QString, FT3MapPointer> m_Ft3ChannelType;
	long m_nVoltDrvPos[36];
	long m_nCurrDrvPos[36];
	long m_nVoltDrvCnt;
	long m_nCurrDrvCnt;
	long m_nBaudRate;
	long m_nSample;
	BOOL m_bFindDataPos;
	BOOL m_bACDataBegin;
	QMap<QString, int> m_ChanMapID;
	FT3BlockInfo m_oEncoderInfo;
	QList<QString> m_ChanMapList;

	virtual void EnCoderHeader(tmt_ft3_6044 otmt_6044, QByteArray &m_oPackage);
	virtual void InitFT3Rates(CIecCfgSmvRates *pIecSmvRates) {} //初始化FT3码值对应关系
	virtual void InitChanelMap() {}
	virtual void InitFT3ChanelType() {}
	virtual QString GetFt3ChannelType(int nChannelType, int nFT3ChannelTypePos){}
	virtual void InitSampleLen(long nSampleDataLen);//目前控制块只支持一个采样长度，所以电气量也同理
};

#endif
