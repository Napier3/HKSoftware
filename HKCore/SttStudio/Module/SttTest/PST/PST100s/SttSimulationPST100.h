#pragma once

#include "../../../SttTestBase/SttTestBase.h"
#include "../../../../StableControl/Module/RecordDataBuffer/PstRcdDataBufferMngr_Pst100.h"
#include "../SttSimulationBase.h"

class CSttSimulationPST100 : public CSttSimulationBase
{
public:
    CSttSimulationPST100();
    virtual ~CSttSimulationPST100(void);


public:
    virtual void Init();
    virtual void StartTest(long nStateIdx);
    virtual void Stop();
};

