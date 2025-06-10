#pragma once

#include "SttTestResourceBase.h"

#include "../RtDataMngr/SttMacroChannelsAsync.h"

class CSttTestResource_Hd :public CSttTestResourceBase
{
public:
	CSttTestResource_Hd(void){}
	virtual ~CSttTestResource_Hd(void){}

};


class CSttTestResource_Async :public CSttTestResourceBase
{
public:
	CSttTestResource_Async(void);
	virtual ~CSttTestResource_Async(void);

	CSttTestResource_Hd m_oAnalog;
	CSttTestResource_Hd m_oDigital;
	CSttTestResource_Hd m_oWeak;

public:
	virtual long GetTestRsType(){return STT_TEST_RESOURCE_TYPE_ASYNC;}//获取当前软件资源类型
	virtual void CreateSoftResource();//创建软件资源
	virtual CString GetChMapsFilePostfix(){return _T("async");}
};
