#ifndef CSTTPOWERCTRLC32_H
#define CSTTPOWERCTRLC32_H
#include "../SttPowerCtrlBase.h"

class CSttPowerCtrlC32:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlC32();
	~CSttPowerCtrlC32();

public:
	//Current
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);
	virtual void SetCurrentDA_State(int nModuleIndex);
};
#endif // CSTTPOWERCTRLC32_H
