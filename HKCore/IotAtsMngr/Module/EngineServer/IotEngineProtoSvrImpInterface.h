#pragma once

#include "../../../SttStudio/Module/SttCmd/SttIotCmd.h"

//Э��ת��ģ��ʵ�ֽӿڣ�IotEngineProtocolServer����

class CIotEngineProtoSvrImpInterface
{
public:
	CIotEngineProtoSvrImpInterface(){}
	virtual ~CIotEngineProtoSvrImpInterface(){}
public:
	virtual long RunProcedure(CSttIotCmd &oIotCmd) = 0;
	virtual long PkgPrase(CSttIotCmd &oIotCmd,CSttParas &oRetParas) = 0;
	virtual long PkgProduce(CSttIotCmd &oIotCmd,CSttParas &oRetParas) = 0;
	virtual long GetDataset(CSttIotCmd &oIotCmd,CSttParas &oRetParas) = 0;
	virtual long ConfigDevice(CSttIotCmd &oIotCmd) = 0;
	virtual long CloseDevice(CSttIotCmd &oIotCmd) = 0;
};