
#pragma once

#include "PxiDevice.h"
#include "../Engine/PpEngineBaseApp.h"
// CPxiEngine 

class CPxiEngine : public CPpEngineBaseApp
{
private:
	CPxiEngine();
	virtual ~CPxiEngine();

    static CPxiEngine *g_pPxiEngine;
    static long g_nPxiEngineRef;

protected:
	CTLinkListEx<CPxiDevice>  m_listDevice;

public:
    static CPxiEngine* Create();
    static void Release();
    static CPxiEngine* GetPxiEngine();

public:
	CString GetVersion(void);
	CPxiDevice* CreateDevice(const CString &strTemplateFile, const CString &strDeviceFile, const CString &strDeviceID, CExBaseObject *pPpEngineDevice);
	long GetCount(void);
	CPxiDevice* GetItem(long nIndex);
	long ShowSpyWnd(long nShow);
	long ReleaseDevice(const CString &strDeviceID);
	long ReleaseAllDevice(void);
	long CreateProject(const CString &strProjectFile);

    CPxiDevice* FindDevice(const CString &strDeviceID);
    CPxiDevice* GetDeviceByIndex(long nIndex);

    void UnloadDevice(CPxiDevice *pDevice);
public:
    virtual void SerializeTrigerScript(long &nScriptIndex, CExBaseList &listTrigerScript, const CString &strID);

    virtual void OnEngineDataDeleted(const CString &strDeviceID);
};

extern CPxiEngine *g_thePxiEngine;

//2020-11-09  lijunqing
extern CPxiDeviceCommCmdMessage *g_thePxiDeviceCommCmdMessage;
