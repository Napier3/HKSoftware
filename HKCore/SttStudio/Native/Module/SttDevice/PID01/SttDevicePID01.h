#ifndef CSTTDEVICEPID01_H
#define CSTTDEVICEPID01_H

#include "../Module/Driver466/SttDeviceComm.h"
#include "stdafx.h"

class CSttDevicePID01 : public CSttDeviceComm,public CSttDeviceBase
{
private:
	explicit CSttDevicePID01();
	~CSttDevicePID01();
	static long g_nSttDeviceRef;

public:
	static void Create();
	static void Release();
	static CSttDevicePID01 *g_pSttDevicePID01;

	virtual int InitDevice(BOOL bHasAdjFile);

	//pid01
	virtual void ProPid01DrvResult();
	virtual void tmt_to_drv_pid01(void *pVoidTmt);
    virtual void tmt_to_drv_pid16(void *pVoidTmt);
	virtual BOOL OnTimer(BOOL bExec = FALSE){return FALSE;}
public:

};

#endif // CSTTDEVICEPN466_H
