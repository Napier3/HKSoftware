#ifndef _SttRelayTestServerApp_h__
#define _SttRelayTestServerApp_h__

#include "../../SttTestServerBaseApp.h"

class CSttRelayTestServerApp : public CSttTestServerBaseApp
{
public:
    CSttRelayTestServerApp();
    virtual ~CSttRelayTestServerApp();

public:
	virtual void InitSttTestServerBaseApp();
	virtual void ExitSttTestServerBaseApp();
};

#endif // _SttRelayTestServerApp_h__
