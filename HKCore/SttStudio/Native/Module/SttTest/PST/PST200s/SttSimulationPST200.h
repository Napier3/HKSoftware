#pragma once

#include "../../../SttTestBase/SttTestBase.h"
#include "../../../../StableControl/Module/RecordDataBuffer/PstRcdDataBufferMngr_Pst200.h"
#include "../SttSimulationBase.h"

#define OutputType_WeekSwitch   0
#define OutputType_SmvGoose     1
#define OutputType_Ft3          2

class CSttSimulationPST200 : public CSttSimulationBase
{
public:
    CSttSimulationPST200();
    virtual ~CSttSimulationPST200(void);

    //2022-8-25  lijunqing
    REPLAY_HDCH_RCDDATA_MAPS_MNGR m_oHdChRcdDataMapsMngr;
    CPstRtdsFiberOutputMap* m_pOutputMap;
    virtual void SetRtdsFiberOutputMap(CPstRtdsFiberOutputMap* pOutputMap){ m_pOutputMap = pOutputMap;}
public:
    virtual void Init();
    virtual void StartTest(long nStateIdx);
    virtual void ReStart(long nStateIdx);
    virtual void OnRecordFinished();
    virtual void InitModuleCoef();
    virtual void Stop();
};
