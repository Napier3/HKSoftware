#pragma once

#include "SttSocketDataBase.h"
#include "..\Engine\SttTestEngineBase.h"
#include "..\SttAuthority\SttModuleAuthorityMngr.h"

class CSttAuthoritySocketDataBase : public CSttSocketDataBase
{
public:
	CSttAuthoritySocketDataBase();
	virtual ~CSttAuthoritySocketDataBase();

public:
	CSttModuleAuthorityMngr  m_oModuleAuthorityMngr;
};