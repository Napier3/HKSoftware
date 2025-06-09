//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利


//IecFiberConfig.cpp  CIecFiberConfig


#include "stdafx.h"
#include "IecFiberConfig.h"


//CIecFiberCh
CIecFiberCh::CIecFiberCh()
{
	m_nState = 0;
	m_nUseCount = 0;
	m_nIndex = 0;
}

CIecFiberCh::~CIecFiberCh()
{
	
}

//CIecFiberConfig
CIecFiberConfig::CIecFiberConfig()
{
	//初始化属性

	//初始化成员变量
}

CIecFiberConfig::~CIecFiberConfig()
{
}


void CIecFiberConfig::InitFiberConfig(long nFiberCount)
{
	DeleteAll();
	long nIndex=0;
	CIecFiberCh *pNew = NULL;
	
	for (nIndex=0; nIndex<nFiberCount; nIndex++)
	{
		pNew = new CIecFiberCh();
		pNew->m_nIndex = nIndex;
		pNew->m_strName.Format(_T("Fiber %d"), nIndex+1);
		pNew->m_strID.Format(_T("Fiber%d"), nIndex+1);
		AddNewChild(pNew);
	}
}


void CIecFiberConfig::InitFt3Config(long nFiberCount)
{
	DeleteAll();
	long nIndex=0;
	CIecFiberCh *pNew = NULL;

	for (nIndex=0; nIndex<nFiberCount; nIndex++)
	{
		pNew = new CIecFiberCh();
		pNew->m_nIndex = nIndex;
		pNew->m_strName.Format(_T("CH%d"), nIndex+1);
		pNew->m_strID.Format(_T("Ft3%d"), nIndex+1);
		AddNewChild(pNew);
	}
}

void CIecFiberConfig::InitFiberConfig(long nAppType, long nAppVersion)
{
	
}

