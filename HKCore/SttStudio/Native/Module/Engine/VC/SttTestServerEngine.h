#pragma once

#include "../SttTestServerBase.h"

class CSttTestServerEngine : public  CSttTestServerBase
{
public:
    static CSttTestServerEngine* Create(char *pszIP, int nPort);
    static void Release();

private:
	CSttTestServerEngine();
	virtual ~CSttTestServerEngine();

public:
	virtual long Process_Cmd_Ajust_ReadDeviceParameter(CSttSocketDataBase *pClientSocket, CSttAdjustCmd &oAdjustCmd,CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Test_SetParameter(CSttXmlSerializeTool &oSttXmlSerializeTool);
	virtual long Process_Cmd_Test_StartTest(CSttXmlSerializeTool &oSttXmlSerializeTool);

};

//extern CSttServerTestCtrlCntr  *g_pTestCtrlEngine;
