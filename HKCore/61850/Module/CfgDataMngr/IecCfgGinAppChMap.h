//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgGinAppChMap.h  CIecCfgGinAppChMap

#pragma once

#include "IecCfgDataMngrGlobal.h"

#include "IecCfgGinChs.h"


class CIecCfgGinAppChMap : public CExBaseObject
{
public:
	CIecCfgGinAppChMap();
	virtual ~CIecCfgGinAppChMap();

	CIecCfgGinCh *m_pIecCfgGinCh;

//重载函数
public:
	void InitByDataTypeValue(CDataTypeValue *pValue);
};

