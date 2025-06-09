#pragma once

#include "IotPxEngineInterface.h"


class CIotPxEngineFactoryBase : public CIotPxEngineInterface
{
public:
	CIotPxEngineFactoryBase();
	virtual ~CIotPxEngineFactoryBase();

	CString m_strEngineProgID;  //ÒýÇæµÄID
public:

};

