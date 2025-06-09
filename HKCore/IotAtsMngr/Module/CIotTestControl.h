#pragma once

#include "IotTestControlBase.h"


class CIotTestControl : public CIotTestControlBase
{
public:
	CIotTestControl();
	virtual ~CIotTestControl();

	BOOL m_bCloseTest;
	CDataGroup m_oItemList;//测试项目列表
public:

};