#pragma  once

#include "../SttSocketDataBase.h"

class CSttServerClientSocketBase : public CSttSocketDataBase
{
public:
	CSttServerClientSocketBase();
	virtual ~CSttServerClientSocketBase();

public:
	virtual void OnSocketClose(int nErrorCode, BOOL bDeleteSocket = TRUE);
};
