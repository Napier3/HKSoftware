#ifndef CPPSTTIOTMEASSERVER_H
#define CPPSTTIOTMEASSERVER_H
#include "PpSttIotEngineDeviceBase.h"
#include "../../../Engine/SttTestServerBase.h"

class CPpSttIotMeasServer : public CSttTestServerBase
{
private:
	CPpSttIotEngineDeviceBase* m_pMeasDevice;

public:
	CPpSttIotMeasServer();
	virtual ~CPpSttIotMeasServer();

public:
	static CPpSttIotMeasServer* Create(char *pszIP, int nPort);
	static void Release();

	virtual long Process_Cmd_Test(CSttSocketDataBase *pClientSocket, BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_Test_SetDataset(CSttTestCmd* pTestCmd, CSttSocketDataBase *pClientSocket);
	virtual long Process_Cmd_Test_GetDataset(CSttTestCmd* pTestCmd, CSttSocketDataBase *pClientSocket);
	virtual void OnSocketClose(CSttSocketDataBase *pSocket) {}
	virtual void InitMeasServer();
};


#endif//!CPPSTTIOTMEASSERVER_H