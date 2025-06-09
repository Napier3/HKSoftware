#pragma once

//例如PonovoIecDown.dll的绝对路径
BOOL LoadDownIecCfgFileLib(const CString &strLibName);
void ReleaseDownIecCfgFileLib();
BOOL HasLoadDownIecCfgFileLib();

long iecfg_DownCfgFile(char *pszIecCfgFile);
long iecfg_DownCfgFile(const CString &strIecCfgFile);

long GetWorkFolderFromReg();
BOOL GetDllPath(const CString &strLibName);