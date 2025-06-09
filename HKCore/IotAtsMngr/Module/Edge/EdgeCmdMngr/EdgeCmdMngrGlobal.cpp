//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//EdgeCmdMngrGlobal.cpp

#include "stdafx.h"
#include "EdgeCmdMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CEdgeCmdMngrXmlRWKeys

CEdgeCmdMngrXmlRWKeys* CEdgeCmdMngrXmlRWKeys::g_pXmlKeys = NULL;
long CEdgeCmdMngrXmlRWKeys::g_nMngrRef = 0;


CEdgeCmdMngrXmlRWKeys::CEdgeCmdMngrXmlRWKeys()
{
	m_strCEdgeDatasKey = L"datas";
	m_strCEdgeCmdKey = L"edgecmd";
	m_strCEdgeDeviceInfosKey = L"deviceInfos";
	m_strCEdgeRepPeriodKey = L"repPeriod";
	m_strCEdgeTemperatureKey = L"temperature";
	m_strCEdgeMemUsedKey = L"memUsed";
	m_strCEdgeLinkStateKey = L"linkState";
	m_strCEdgeSignKey = L"sign";
	m_strCEdgeFileKey = L"file";
	m_strCEdgeDiskLmtKey = L"disklmt";
	m_strCEdgeMemLmtKey = L"memlmt";
	m_strCEdgeCpuLmtKey = L"cpulmt";
	m_strCEdgeOSKey = L"os";
	m_strCEdgeLinkKey = L"link";
	m_strCEdgeLinksKey = L"links";
	m_strCEdgeDiskKey = L"disk";
	m_strCEdgeMemKey = L"mem";
	m_strCEdgeCpuKey = L"cpu";
	m_strCEdgeDevKey = L"dev";
	m_strCEdgeParasKey = L"paras";
	m_strCEdgeParamKey = L"param";
	m_strCEdgeDataKey = L"data";
	m_strCEdgeGroupKey = L"group";
	m_strDataTypeKey = L"data-type";
	m_strValueKey = L"value";
}

CEdgeCmdMngrXmlRWKeys::~CEdgeCmdMngrXmlRWKeys()
{
}

CEdgeCmdMngrXmlRWKeys* CEdgeCmdMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new CEdgeCmdMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CEdgeCmdMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CEdgeCmdMngrConstGlobal

long CEdgeCmdMngrConstGlobal::g_nGlobalRef = 0;
CEdgeCmdMngrConstGlobal* CEdgeCmdMngrConstGlobal::g_pGlobal = NULL;


CEdgeCmdMngrConstGlobal::CEdgeCmdMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CEdgeCmdMngrConstGlobal::~CEdgeCmdMngrConstGlobal()
{
}

CEdgeCmdMngrConstGlobal* CEdgeCmdMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CEdgeCmdMngrConstGlobal();
	}

	return g_pGlobal;
}

void CEdgeCmdMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
