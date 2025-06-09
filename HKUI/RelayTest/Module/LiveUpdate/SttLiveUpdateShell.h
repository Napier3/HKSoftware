
// SttLiveUpdateShell.h 
//
#pragma once

#include "SttUpdateCfg.h"
#include "SttLiveUpdateDef.h"

class CSttLiveUpdateShell
{
public:
	CSttLiveUpdateShell();
 	~CSttLiveUpdateShell();

	void Init();
	void Exit();

	//检查更新
	void GetShellParas(int nLiveUpdateType,CString &strParas);
	BOOL GetLiveUpdatePath(CString &strPath);

	//版本更新
	void LocalUpdate();
	void TestAppUpdate();
	bool IsProcessExist();//20220629 zhouhj 判断进程是否存在
#ifdef _PSX_QT_LINUX_
	void TestAppUpdate_OffLine(const CString &strArgv);//20231223 dxy 使用U盘离线升级
#endif
};

extern CSttLiveUpdateShell theLiveUpdate;
