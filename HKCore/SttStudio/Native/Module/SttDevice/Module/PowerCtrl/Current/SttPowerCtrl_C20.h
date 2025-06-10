#ifndef CSTTPOWERCTRLC20_H
#define CSTTPOWERCTRLC20_H
#include "../SttPowerCtrlBase.h"

class CSttPowerCtrlC20:public CSttPowerCtrlBase
{
public:
	CSttPowerCtrlC20();
	~CSttPowerCtrlC20();

public:
	//Current
	virtual void SetCurrentDA(float fIoutSum,float fIoutMax,int nModuleIndex,BOOL bIsDc=FALSE);
	virtual void SetCurrentDA_State(int nModuleIndex);
};
#endif // CSTTPOWERCTRLC20_H
