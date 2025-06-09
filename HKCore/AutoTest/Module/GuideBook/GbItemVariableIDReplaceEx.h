#pragma once

#include "GbItemVariableIDReplace.h"


class CGbItemVariableIDReplaceEx : public CGbItemVariableIDReplace
{
public:
	CGbItemVariableIDReplaceEx();
	virtual ~CGbItemVariableIDReplaceEx();

// Ù–‘
protected:
	virtual void Replace(CCommCmd *pGbObj);
};

