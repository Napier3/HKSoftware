#pragma once

#include "SttSocketDataBase_File.h"

//2022-2-12  lijunqing 报文转发,例如：自动测试控制服务，收到的测试仪事件报文，通过自动测试控制通信通道转发给上位机软件
#include "../SttPkgDispatchInterface.h"

class CSttSocketDataBase : public CSttSocketDataBase_File
{
public:
	CSttSocketDataBase();
	virtual ~CSttSocketDataBase();
};


