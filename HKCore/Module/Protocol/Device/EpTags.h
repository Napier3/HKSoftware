#pragma once

#include "EpTag.h"

class CEpTags :public CExBaseList
{
public:
	CEpTags();
	virtual ~CEpTags();

public:
	//��������
	virtual UINT GetClassID(){return EPDCLASSID_CEPTAG;};

};

