#include "stdafx.h"
#include"SttSimulationPST100.h"


CSttSimulationPST100::CSttSimulationPST100()
{
    Init();
}

void CSttSimulationPST100::Init()
{
    CSttSimulationBase::Init();
}

CSttSimulationPST100::~CSttSimulationPST100(void)
{

}

void CSttSimulationPST100::Stop()
{
    CSttSimulationBase::Stop();
}

void CSttSimulationPST100::StartTest(long nStateIdx)
{
    CSttDeviceBase::g_pSttDeviceBase->SetTestStart(nStateIdx);
}
