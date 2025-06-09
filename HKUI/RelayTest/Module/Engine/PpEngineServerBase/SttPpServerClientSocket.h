#ifndef _CSttPpServerClientSocket_H
#define _CSttPpServerClientSocket_H

#include "../../SttSocket/TestServer/VC/SttServerClientSocket.h"
#include "../../../../IotAtsMngr/Module/PxEngineServer/IotPxEngineInterface.h"

class CSttPpServerClientSocket : public CSttServerClientSocket, public CIotPxCommChannelInterface
{
public:
	CSttPpServerClientSocket();
    virtual ~CSttPpServerClientSocket();
	
//////////////////////////////////////////////////////////////////////////
//CIotPxCommChannelInterface
public:
	virtual long PxSendBuffer(BYTE *pBuf, long nLen) ;
	virtual long PxSendSysState(CSttSysState *pSysState);
	virtual UINT GetClassID()	{	return _PxCommChannelInterface_CLASSID_SOCKET_;	}

public:
	virtual BOOL ProcessRecvPacket(BYTE *pBuf,long nLen);
	virtual long OnTestMsg(BYTE *pBuf, long nLen);

	virtual long Process_Cmd_System(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);
	virtual long Process_Cmd_IOT(BYTE *pBuf, long nLen, char *pszCmdID, char *pszTestor);

	virtual void OnSocketClose(int nErrorCode, BOOL bDeleteSocket = TRUE);

protected:
	char *m_pszXmlBuffer;
	long m_nXmlBufferLen;

	void SetXmlBufferLen(long nLen);
};

#endif // _CSttPpServerClientSocket_H
