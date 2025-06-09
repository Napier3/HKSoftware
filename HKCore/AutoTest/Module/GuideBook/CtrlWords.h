#pragma once
#include "Sets.h"
#include "GuideBookDefine.h"

class CCtrlWords :public CSets
{
public:
	CCtrlWords(void);
	virtual ~CCtrlWords(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()		{		return GBCLASSID_CTRLWORDS;	}
	virtual BSTR GetXmlElementKey();
	virtual CBaseObject* Clone();
protected:

private:

};