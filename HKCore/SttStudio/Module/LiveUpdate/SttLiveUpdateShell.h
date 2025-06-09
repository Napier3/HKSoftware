
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

	//������
	void GetShellParas(int nLiveUpdateType,CString &strParas);
	BOOL GetLiveUpdatePath(CString &strPath);

	//�汾����
	void LocalUpdate();
	void TestAppUpdate();
	bool IsProcessExist();//20220629 zhouhj �жϽ����Ƿ����
#ifdef _PSX_QT_LINUX_
	void TestAppUpdate_OffLine(const CString &strArgv);//20231223 dxy ʹ��U����������
#endif
};

extern CSttLiveUpdateShell theLiveUpdate;
