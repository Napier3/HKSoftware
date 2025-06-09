#pragma  once

#include "../SttSocketDataBase.h"

class CSttClientSocketBase : public CSttSocketDataBase
{
public:
	CSttClientSocketBase();
	virtual ~CSttClientSocketBase();

public:
	virtual void CloseSocket();
};