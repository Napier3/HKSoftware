//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//61850ClientCfgMngrGlobal.cpp

#include "stdafx.h"
#include "61850ClientCfgMngrGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//C61850ClientCfgMngrXmlRWKeys

C61850ClientCfgMngrXmlRWKeys* C61850ClientCfgMngrXmlRWKeys::g_pXmlKeys = NULL;
long C61850ClientCfgMngrXmlRWKeys::g_nMngrRef = 0;


C61850ClientCfgMngrXmlRWKeys::C61850ClientCfgMngrXmlRWKeys()
{
	m_strCRemoteDevKey = L"remote-dev";
	m_strCRemoteDevsKey = L"remote-devs";
	m_strC61850ClientConfigKey = L"client-config";
	m_strDebug_ModeKey = L"debug-mode";
	m_strUse_Map_FileKey = L"use-map-file";
	m_strEna_Write_Wait_After_SelKey = L"ena-write-wait-after-sel";
	m_strEna_Write_WaitKey = L"ena-write-wait";
	m_strRead_Ain_Use_ReportKey = L"read-ain-use-report";
	m_strAdd_Rpt_BufferKey = L"add-rpt-buffer";
	m_strCan_Write_Active_SgKey = L"can-write-active-sg";
	m_strProtocol_VersionKey = L"protocol-version";
	m_strUse_DsdoutKey = L"use-dsdout";
	m_strEna_Read_Before_WriteKey = L"ena-read-before-write";
	m_strWrite_Data_Wait_MsKey = L"write-data-wait-ms";
	m_strAuto_Gen_Model_DatasKey = L"auto-gen-model-datas";
	m_strUse_Gsp_LogKey = L"use-gsp-log";
	m_strSpecifi_DatasetKey = L"specifi-dataset";
	m_strIntg_PdKey = L"intg-pd";
	m_strOpt_Flds_BRKey = L"opt-flds-BR";
	m_strOpt_Flds_RPKey = L"opt-flds-RP";
	m_strTrg_Ops_UIKey = L"trg-ops-UI";
	m_strUse_Entryid_UpdateKey = L"use-entryid-update";
	m_strWriteCtrlTypeKey = L"write-ctrl-type";
	m_strCtrlTestKey = L"ctrl-test";
	m_strCtrlCheckKey = L"ctrl-check";
	m_strHasTimeActKey = L"has-time-act";
	m_strIpKey = L"ip";
	m_strLocal_IpKey = L"local-ip";
	m_strUse_Local_IpKey = L"use-local-ip";
}

C61850ClientCfgMngrXmlRWKeys::~C61850ClientCfgMngrXmlRWKeys()
{
}

C61850ClientCfgMngrXmlRWKeys* C61850ClientCfgMngrXmlRWKeys::Create()
{
	g_nMngrRef++;

	if (g_nMngrRef == 1)
	{
		g_pXmlKeys = new C61850ClientCfgMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void C61850ClientCfgMngrXmlRWKeys::Release()
{
	g_nMngrRef--;

	if (g_nMngrRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//C61850ClientCfgMngrConstGlobal

long C61850ClientCfgMngrConstGlobal::g_nGlobalRef = 0;
C61850ClientCfgMngrConstGlobal* C61850ClientCfgMngrConstGlobal::g_pGlobal = NULL;


C61850ClientCfgMngrConstGlobal::C61850ClientCfgMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

C61850ClientCfgMngrConstGlobal::~C61850ClientCfgMngrConstGlobal()
{
}

C61850ClientCfgMngrConstGlobal* C61850ClientCfgMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new C61850ClientCfgMngrConstGlobal();
	}

	return g_pGlobal;
}

void C61850ClientCfgMngrConstGlobal::Release()
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
