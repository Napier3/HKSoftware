#pragma once

//����PonovoIecDown.dll�ľ���·��
BOOL LoadDownIecCfgFileLib(const CString &strLibName);
void ReleaseDownIecCfgFileLib();
BOOL HasLoadDownIecCfgFileLib();

long iecfg_DownCfgFile(char *pszIecCfgFile);
long iecfg_DownCfgFile(const CString &strIecCfgFile);

long GetWorkFolderFromReg();
BOOL GetDllPath(const CString &strLibName);