#ifndef _Mosquitto_Process_h_
#define _Mosquitto_Process_h_

#ifdef __cplusplus
extern "C"{
#endif

#include "../../Module/mosquitto-1.4.8/lib/memory_mosq.h"
#include "../../Module/mosquitto-1.4.8/src/mosquitto_broker.h"

	extern void handle_sigint(int signal);
	extern int main(int argc, char *argv[]);

	bool ServerPocess(char **ppTopic,void **ppPayload,uint32_t *pPayloadLen);

#ifdef __cplusplus
};
#endif

int Mosquitto_Main(void);
void Mosquitto_Exit(void);
void Mosquitto_SetMsgWnd(const HWND& hWnd);



#endif