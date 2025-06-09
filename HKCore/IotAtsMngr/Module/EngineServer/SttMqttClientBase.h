#pragma once
#include "MqttClientToPxEngine.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"
#include "../../../SttStudio/Module/SttCmd/SttSysState.h"
#include "../../../SttStudio/Module/SttCmd/SttAtsCmd.h"
#include "../../../SttStudio/Module/SttCmd/SttTestCmd.h"
#include "../../../SttStudio/Module/SttCmd/SttIotCmd.h"

class CSttMqttClientBase:public CMqttClientToPxEngine
{
public:
	CSttMqttClientBase();
	virtual ~CSttMqttClientBase();

	//通信接口
public:
	//连接成功后，订阅主题
	//virtual BOOL Connect(const char *pszIP,long nPort, const char *pszClientIDKey);

	virtual long Send(CExBaseObject *pCmdBase);

protected:
	virtual long Send_Stt(CExBaseObject *pCmdBase);
	//2021-7-19  lijunqing
	virtual CString GenerateTopic(CSttCmdBase *pCmdBase);
	virtual CString GenerateTopic(CSttAtsCmd *pAtsCmd);
	virtual CString GenerateTopic(CSttTestCmd *pTestCmd);
	virtual CString GenerateTopic(CSttSysState *pSysState);
	virtual CString GenerateTopic(CSttIotCmd *pIotCmd);

	//shaolei 20210805
	virtual CString GenerateTopic(const CString &strToSN, char *pszCmdType, char *pszCmdID, char *pszRetType, char *pszEventID);

};