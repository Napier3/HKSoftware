//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAtsSvrMqttImpBase.h  CSttAtsSvrMqttImpBase

#pragma once

#include "../../../../SttStudio/Module/SttCmd/SttAtsCmd.h"
#include "SttProtoAtsServiceMqttClient.h"
#include "../../EngineServer/SttMqttEngineBase.h"

class CAtsSvrMsgWnd;

/*
2021-7-21  lijunqing
为了赶进度，暂时就将功能集成到CSttAtsSvrMqttImpBase中，CSttAtsSvrMqttImpBase从CSttMqttEngineBase派生
后续考虑通用，在增加相关的接口，将自动测试服务的功能从CSttAtsSvrMqttImpBase剥离出去，兼容STT的调用
可以考虑采用工厂模式注册和创建相关的处理对象
*/

class CSttAtsSvrMqttImpBase : public CSttMqttEngineBase
{
public:
	CSttAtsSvrMqttImpBase();
	virtual ~CSttAtsSvrMqttImpBase();


//私有成员变量
private:

protected:
	CSttProtoAtsServiceMqttClient *m_pMqttClient;
	CAtsSvrMsgWnd *m_pServiceWnd;

//私有成员变量访问方法
public:
	BOOL CreateAtsServiceMqttClient(const CString &strMqttTopic);

public:
	virtual long OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType);

};

