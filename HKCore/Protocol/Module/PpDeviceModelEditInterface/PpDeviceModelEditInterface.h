#pragma once

class CLogBase;

#ifndef _PP_DVM_EDIT_ONLY_USE_CMMCONFIG_FILE_
class CDevcieModel;
class CDvmDevice;
class CDeviceCmmConfig;
class CPpDvmDevice;
#endif

typedef LONG (__cdecl *PP_INSTALLLOG)(CLogBase *pLog);
typedef LONG (__cdecl *PP_UNINSTALLLOG)() ;

#ifndef _PP_DVM_EDIT_ONLY_USE_CMMCONFIG_FILE_
typedef LONG (__cdecl *PP_EDITDEVICEMODEL)(CDevcieModel *pDeviceModel, const CWnd *pParent, const CRect &rcPos) ;
typedef LONG (__cdecl *PP_EDITDEVICE)(CPpDvmDevice *pDevice, const CWnd *pParent, const CRect &rcPos) ;
typedef LONG (__cdecl *PP_EDITDEVICECMMCONFIG)(CDeviceCmmConfig *pDeviceCmmConfig, const CWnd *pParent, const CRect &rcPos) ;
#endif

typedef LONG (__cdecl *PP_EDITDEVICECMMCONFIGFILE)(const char *strFile, const CWnd *pParent, const CRect &rcPos) ;


extern PP_INSTALLLOG 								Pp_InstallLog;
extern PP_UNINSTALLLOG 							Pp_UnInstallLog;

#ifndef _PP_DVM_EDIT_ONLY_USE_CMMCONFIG_FILE_
extern PP_EDITDEVICEMODEL						Pp_EditDeviceModel;
extern PP_EDITDEVICE								Pp_EditDevice;
extern PP_EDITDEVICECMMCONFIG				Pp_EditDeviceCmmConfig;
#endif

extern PP_EDITDEVICECMMCONFIGFILE				Pp_EditDeviceCmmConfigFile;

extern HINSTANCE g_hPpDeviceModelEditLib;

inline BOOL HasLoadPpDeviceEditLib()
{
	return (g_hPpDeviceModelEditLib != NULL);
}

inline void ReleasePpDeviceEditLib()
{
	if (g_hPpDeviceModelEditLib != NULL)
	{
		FreeLibrary(g_hPpDeviceModelEditLib);
		g_hPpDeviceModelEditLib = NULL;
	}
}

//2020-12-22  lijunqing  SmartTest  增加通信配置功能
BOOL LoadPpDeviceEditLib(const CString &strBinPath=_T(""));

//2023-3-26  lijunqing
BOOL ppcfg_PpEngine(const CString &strProgID, const CString &strDvmFile);

