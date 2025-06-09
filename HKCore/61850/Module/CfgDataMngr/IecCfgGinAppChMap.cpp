//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgGinAppChMap.cpp  CIecCfgGinAppChMap


#include "stdafx.h"
#include "IecCfgGinAppChMap.h"
#include "../../../Module/System/StringTokenizer.h"

CIecCfgGinAppChMap::CIecCfgGinAppChMap()
{
	m_pIecCfgGinCh = NULL;
}

CIecCfgGinAppChMap::~CIecCfgGinAppChMap()
{
}

void CIecCfgGinAppChMap::InitByDataTypeValue(CDataTypeValue *pValue)
{
	m_strName = pValue->m_strName;
	m_strID   = pValue->m_strID;
}

