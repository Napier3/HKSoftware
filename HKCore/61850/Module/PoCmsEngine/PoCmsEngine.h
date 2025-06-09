
#pragma once

#include "PoCmsDevice.h"
#include "DltEngineAppBase.h"
// CPoCmsEngine ÃüÁîÄ¿±ê

class CPoCmsEngine : public CDltEngineAppBase
{
protected:
	CPoCmsEngine();
	virtual ~CPoCmsEngine();

	static CPoCmsEngine *g_pCmsEngine;
	static long g_nCmsEngineRef;

public:
	static CPoCmsEngine* Create();
	static void Release();
	static CPoCmsEngine* GetPxiEngine();

public:
	virtual CPoCmsDevice* CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID);
	virtual CPoCmsDevice* GetItem(LONG nIndex);
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



extern CPoCmsEngine *g_theCmsEngine;
