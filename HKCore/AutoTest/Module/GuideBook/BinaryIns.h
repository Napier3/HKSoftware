#pragma once
#include "Binarys.h"
#include "GuideBookDefine.h"

class CBinaryIns :public CBinarys
{
public:
	CBinaryIns(void);
	virtual ~CBinaryIns(void);

public:
	//Serialize mathods
	virtual UINT GetClassID()			{		return GBCLASSID_BINARYINS;		}
	virtual BSTR GetXmlElementKey()  ;
	virtual CBaseObject* Clone();

protected:

private:

};