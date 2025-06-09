//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//YunConfigGlobal.cpp

#include "stdafx.h"
#include "YunConfigGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CYunConfigXmlRWKeys

CYunConfigXmlRWKeys* CYunConfigXmlRWKeys::g_pXmlKeys = NULL;
long CYunConfigXmlRWKeys::g_nYUNRef = 0;


CYunConfigXmlRWKeys::CYunConfigXmlRWKeys()
{
	m_strCYunConfigKey = L"yun-config";
	m_strProgIDKey = L"progid";
}

CYunConfigXmlRWKeys::~CYunConfigXmlRWKeys()
{
}

CYunConfigXmlRWKeys* CYunConfigXmlRWKeys::Create()
{
	g_nYUNRef++;

	if (g_nYUNRef == 1)
	{
		g_pXmlKeys = new CYunConfigXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CYunConfigXmlRWKeys::Release()
{
	g_nYUNRef--;

	if (g_nYUNRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}
