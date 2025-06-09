#pragma once
#include "Sets.h"
#include "GuideBookDefine.h"

class CSoftSwitchs :public CSets
{
public:
	CSoftSwitchs(void);
	virtual ~CSoftSwitchs(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()			{		return GBCLASSID_SOFTSWITCHS;			}
	virtual BSTR GetXmlElementKey() ;
	virtual CBaseObject* Clone();
protected:

private:

};