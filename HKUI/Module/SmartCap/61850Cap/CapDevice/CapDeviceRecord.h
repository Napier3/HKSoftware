#pragma once

#include "CapDeviceGlobal.h"
#include "CapDeviceBase.h"
#include "CapDeviceSmvBase.h"
#include "../../Module/SttTest/Common/tmt_adjust_sys_parameter.h"
//Xuzt 2024/8/5
class CCapDeviceRecord : public CCapDeviceSmvBase
{
public:
	CCapDeviceRecord();
	virtual ~CCapDeviceRecord();
	int m_nChannelNum;//采集通道总数量N（最大64）
	int m_nModulePos;//取值：0~12，当前0：主板开入
	long m_nChannelData[BINARY_CHANNEL_MAX];
	long m_nUseFlag;

//重载函数
public:
	virtual UINT GetClassID(){return CPDCLASSID_DEVICERECORD;};

	virtual void InitDevice(CIecCfgDataBase *pIecCfgData);
	virtual void ClearAnalysisResultErrors();
	virtual void AnalysisData(PEPCAPPARSEDATAS pDatas,BYTE* pBuferHead = NULL,long nBufferLenth = 0);

	long GetByteChValue(BYTE* pBuferHead,long &nCurrPos,long &nHasCrcLenth,long nChLenth);
    virtual void GetOriginalDatas(EPCAPPARSEDATAS* pParseDatas)
    {
#ifdef _PSX_IDE_QT_
        (void)pParseDatas;
#endif
    };
protected:
	virtual CCapDeviceChBase* CreateChannel(){return NULL;};
};


