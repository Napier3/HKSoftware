#pragma once

#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlC12_5_PTU200L:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlC12_5_PTU200L();
	~CSttPowerCtrlC12_5_PTU200L();

public:
	//Current
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);
	virtual void SetCurrentDA_State(int nModuleIndex);
};
