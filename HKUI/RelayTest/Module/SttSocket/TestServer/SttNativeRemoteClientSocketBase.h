#pragma  once

#include "../SttSocketDataBase.h"

class CSttNativeRemoteClientSocketBase : public CSttSocketDataBase
{
public:
	CSttNativeRemoteClientSocketBase();
	virtual ~CSttNativeRemoteClientSocketBase();

public:
	virtual void OnSocketClose(int nErrorCode);
};