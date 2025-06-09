#ifndef CSTTPOWERCTRLC12_5_H
#define CSTTPOWERCTRLC12_5_H
#include "../../SttPowerCtrlBase.h"

class CSttPowerCtrlC12_5:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlC12_5();
	~CSttPowerCtrlC12_5();

public:
	//Current
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);
	virtual void SetCurrentDA_State(int nModuleIndex);
};
#endif // CSTTPOWERCTRLC12_5_H
