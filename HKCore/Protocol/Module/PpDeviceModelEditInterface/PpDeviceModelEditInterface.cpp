// PpDeviceModelEditInterface.cpp
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PpDeviceModelEditInterface.h"

PP_INSTALLLOG 								Pp_InstallLog = NULL;
PP_UNINSTALLLOG 							Pp_UnInstallLog = NULL;

#ifndef _PP_DVM_EDIT_ONLY_USE_CMMCONFIG_FILE_
PP_EDITDEVICEMODEL					Pp_EditDeviceModel = NULL;
PP_EDITDEVICE								Pp_EditDevice = NULL;
PP_EDITDEVICECMMCONFIG				Pp_EditDeviceCmmConfig = NULL;
#endif

PP_EDITDEVICECMMCONFIGFILE				Pp_EditDeviceCmmConfigFile = NULL;

HINSTANCE g_hPpDeviceModelEditLib;


BOOL LoadPpDeviceEditLib(const CString &strBinPath)
{
	ReleasePpDeviceEditLib();

	BOOL bSucc = TRUE;
	CString strLibPath;

	if (strBinPath.GetLength() < 3)
	{
		strLibPath = _P_GetBinPath();
	}
	else
	{
		strLibPath = strBinPath;
	}

	strLibPath += _T("PpDeviceModelEdit.dll");
	g_hPpDeviceModelEditLib = ::LoadLibrary(strLibPath);

	if(g_hPpDeviceModelEditLib != NULL)
	{
		Pp_InstallLog = (PP_INSTALLLOG)GetProcAddress(g_hPpDeviceModelEditLib, "Pp_InstallLog");
		Pp_UnInstallLog = (PP_UNINSTALLLOG)GetProcAddress(g_hPpDeviceModelEditLib, "Pp_UnInstallLog");

#ifndef _PP_DVM_EDIT_ONLY_USE_CMMCONFIG_FILE_
		Pp_EditDeviceModel = (PP_EDITDEVICEMODEL)GetProcAddress(g_hPpDeviceModelEditLib, "Pp_EditDeviceModel");
		Pp_EditDevice = (PP_EDITDEVICE)GetProcAddress(g_hPpDeviceModelEditLib, "Pp_EditDevice");
		Pp_EditDeviceCmmConfig = (PP_EDITDEVICECMMCONFIG)GetProcAddress(g_hPpDeviceModelEditLib, "Pp_EditDeviceCmmConfig");
#endif

		Pp_EditDeviceCmmConfigFile = (PP_EDITDEVICECMMCONFIGFILE)GetProcAddress(g_hPpDeviceModelEditLib, "Pp_EditDeviceCmmConfigFile");
	}
	else
	{
		bSucc = FALSE;
	}	

	return bSucc;
}

#include "../../../System/Module/XAtsSysSvrGlobalDef.h"
#include "../Engine/DeviceModel/DevcieModel.h"
BOOL ppcfg_PpEngine(const CString &strProgID, const CString &strDvmFile)
{
	if (g_hPpDeviceModelEditLib == NULL)
	{
		CString strPpBinPath = atssys_GetProtocolPath();
		strPpBinPath += _T("Bin\\");

		if (!LoadPpDeviceEditLib(strPpBinPath))
		{
			CLogPrint::LogString(XLOGLEVEL_ERROR, _T("Load Protocol Config DLL Failed!"));
			return TRUE;
		}
	}

	if (Pp_InstallLog != NULL)
	{
		Pp_InstallLog(CLogPrint::GetLog());
	}

	CString strCmmCfgFile = pp_GetDeviceCmmCfgFile(strDvmFile);
	char *pszFile = NULL;
	CString_to_char(strCmmCfgFile, &pszFile);
	LONG nRet = Pp_EditDeviceCmmConfigFile(pszFile, NULL, CRect (0, 0, 0, 0));
	delete pszFile;

	if (Pp_UnInstallLog != NULL)
	{
		Pp_UnInstallLog();
	}

	return TRUE;
}
