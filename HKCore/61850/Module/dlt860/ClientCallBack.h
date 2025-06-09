#ifndef CLIENT_CALL_BACK_H
#define CLIENT_CALL_BACK_H

#include "../61850ClientConfig/RemoteDev.h"


class ClientCallBackHandler 
{
public:
	static void ReportHandler_BRCB(void* parameter,void* reportPDU);
	static void ReportHandler_URCB(void* parameter,void* reportPDU);
};

bool ClientCallBack_GetFileHandler(void* parameter,unsigned char* buffer,unsigned int bytesRead,bool endFlag);

BOOL GspMmsValue_getBitStringAsCString(const GspMmsValue* self,CString &strValue);

#endif // CLIENT_CALL_BACK_H
