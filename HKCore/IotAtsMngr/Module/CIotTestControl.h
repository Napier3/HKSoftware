#pragma once

#include "IotTestControlBase.h"


class CIotTestControl : public CIotTestControlBase
{
public:
	CIotTestControl();
	virtual ~CIotTestControl();

	BOOL m_bCloseTest;
	CDataGroup m_oItemList;//������Ŀ�б�
public:

};