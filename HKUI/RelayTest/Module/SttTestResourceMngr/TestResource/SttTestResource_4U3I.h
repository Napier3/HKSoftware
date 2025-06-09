#pragma once

#include "SttTestResourceBase.h"

#include "../RtDataMngr/SttMacroChannels.h"

class CSttTestResource_4U3I :public CSttTestResourceBase
{
public:
	CSttTestResource_4U3I(void);
	virtual ~CSttTestResource_4U3I(void);

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_4U3I;}//获取当前软件资源类型
	virtual void CreateSoftResource();//创建软件资源
	virtual CString GetChMapsFilePostfix(){return _T("4u3i");}
	virtual void InitAfterCreated();//在创建完软件资源后,需要进行的初始化操作
};
