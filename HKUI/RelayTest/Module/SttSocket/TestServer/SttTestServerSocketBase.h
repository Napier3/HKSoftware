#pragma once

#include "../SttServerSocketDataBase.h"

class CSttTestServerSocketBase : public CSttServerSocketDataBase
{
public:
	CSttTestServerSocketBase();
	virtual ~CSttTestServerSocketBase();


public:
	virtual BOOL CreateServer(const char *pszIP, int nPort){return FALSE;}
	
};