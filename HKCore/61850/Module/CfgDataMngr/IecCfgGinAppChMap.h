//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	void InitByDataTypeValue(CDataTypeValue *pValue);
};

