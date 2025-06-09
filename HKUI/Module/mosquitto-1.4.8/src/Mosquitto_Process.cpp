//#include "stdafx.h"
#include "Mosquitto_Process.h"
#include <shlwapi.h>
#include <io.h>

extern HWND g_hMosquittoMsgWnd;

#ifdef __cplusplus
extern "C"{
#endif

bool ServerPocess(char **ppTopic,void **ppPayload,uint32_t *pPayloadLen)
{
	return 0;
//	return g_oMosquittoServerMngr.ServerPocess(ppTopic,ppPayload,pPayloadLen);
}

#ifdef __cplusplus
};
#endif

int Mosquitto_Main(void)
{
	char **argv;
	int argc = 1;
	int nRet = 0;

	char strExePath[MAX_PATH];
	if(!GetModuleFileName(NULL, strExePath, MAX_PATH))
		return nRet;
	PathRemoveFileSpec(strExePath);
	strcat(strExePath, "\\..\\Config\\mosquitto.conf");

	if (_access(strExePath, 0) != -1)
	{
		//yzj 启用conf配置文件，且配置文件中启用port设置
		argv = (char **)_mosquitto_malloc(sizeof(char *)*3);
		argv[0] = "mosquitto";
		argv[1] = "-c";
		argv[2] = strExePath;
		argc = 3;
	}
	else
	{
		argv = (char **)_mosquitto_malloc(sizeof(char *)*2);
		argv[0] = "mosquitto";
		argc = 1;
	}

	nRet = main(argc,argv);
	_mosquitto_free(argv);

	return nRet;
}

void Mosquitto_Exit(void)
{
	handle_sigint(0);
}

void Mosquitto_SetMsgWnd(const HWND& hWnd)
{
	g_hMosquittoMsgWnd = hWnd;
}