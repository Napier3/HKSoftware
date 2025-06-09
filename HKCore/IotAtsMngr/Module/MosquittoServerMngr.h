#pragma once

class CMosquittoServerMngr
{
public:
	CMosquittoServerMngr(){}
	virtual ~CMosquittoServerMngr(){}

	bool ServerPocess(char **ppTopic,void **ppPayload,unsigned int *pPayloadLen){return true;}
};

extern CMosquittoServerMngr g_oMosquittoServerMngr;