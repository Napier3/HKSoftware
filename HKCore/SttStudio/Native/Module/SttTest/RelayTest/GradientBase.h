#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include "tmt_common_def.h"
#include "../../SttDevice/RelayTest/drv_define.h"

#ifdef _PSX_IDE_QT_
#include "../../SttDevice/RelayTest/SttDevice.h"
#endif



class CGradientBase : public CSttTestBase, public tmt_GradientCommon
{
public:
	CGradientBase();
	virtual ~CGradientBase();
	virtual void Stop();

#ifdef _PSX_IDE_QT_
	QVector<int> ChannelVolts,ChannelCurrs;
#endif

public:
    void CalStepValue_Gradient(float fSatrt, float fEnd, float fStep, tmt_channel *uData, tmt_channel *iData, int nHarmIndex=1);
    virtual void CalStepValue(float fCurValue){}
    void SetUIParaToStepUI(tmt_channel *uData, tmt_channel *iData, tmt_StepUI *pUIStepData, int nHarmIndex=1);
	void SetChannelSelect(int nRampChannel,int nRampType);
} ;


