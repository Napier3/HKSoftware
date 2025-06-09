#pragma once

#include "EpTag.h"

class CEpTags :public CExBaseList
{
public:
	CEpTags();
	virtual ~CEpTags();

public:
	//基本方法
	virtual UINT GetClassID(){return EPDCLASSID_CEPTAG;};

};

