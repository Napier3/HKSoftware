
#pragma once

#include "PoMmsDevice.h"
#include "MmsEngineAppBase.h"
// CPoMmsEngine ÃüÁîÄ¿±ê

class CPoMmsEngine : public CMmsEngineAppBase
{
protected:
	CPoMmsEngine();
	virtual ~CPoMmsEngine();

	static CPoMmsEngine *g_pMmsEngine;
	static long g_nPxiEngineRef;

	virtual void OnFinalRelease();

public:
	static CPoMmsEngine* Create();
	static void Release();
	static CPoMmsEngine* GetPxiEngine();

public:
	virtual CPoMmsDevice* CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);
	virtual CPoMmsDevice* GetItem(long nIndex);
	virtual long ConfigEngine(const CString &strDvmFile);

	CString GetVersion(void);
	long GetCount(void);
	long ShowSpyWnd(long nShow);
	long ReleaseDevice(const CString &strDeviceID);
	long ReleaseAllDevice(void);
	long CreateProject(const CString &strProjectFile);
	long SetProtocolParse(long nStopFlag);
	long AttatchLogWnd(long hLogWnd);
};



extern CPoMmsEngine *g_theMmsEngine;
