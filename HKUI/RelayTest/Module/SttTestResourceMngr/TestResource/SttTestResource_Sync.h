#pragma once

#include "SttTestResourceBase.h"

#include "../RtDataMngr/SttMacroChannels.h"

class CSttTestResource_Sync :public CSttTestResourceBase
{
public:
	CSttTestResource_Sync(void);
	virtual ~CSttTestResource_Sync(void);

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_SYNC;}//获取当前软件资源类型
	virtual void CreateSoftResource();//创建软件资源
	virtual CString GetChMapsFilePostfix(){return _T("sync");}
};
