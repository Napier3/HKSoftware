//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttCmdDefineGlobal.cpp

#include "stdafx.h"
#include "SttCmtrdCfgDefineGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CSttCmtrdCfgDefineXmlRWKeys

CSttCmtrdCfgDefineXmlRWKeys* CSttCmtrdCfgDefineXmlRWKeys::g_pXmlKeys = NULL;
long CSttCmtrdCfgDefineXmlRWKeys::g_nMngrRef = 0;


CSttCmtrdCfgDefineXmlRWKeys::CSttCmtrdCfgDefineXmlRWKeys()
{
	m_strCSttCmtrdReplayCfgKey = L"cmtrd-replay-cfg";
	m_strCSttMapGroupKey = L"map-group";
}

CSttCmtrdCfgDefineXmlRWKeys::~CSttCmtrdCfgDefineXmlRWKeys()
{

}

CSttCmtrdCfgDefineXmlRWKeys* CSttCmtrdCfgDefineXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CSttCmtrdCfgDefineXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CSttCmtrdCfgDefineXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}