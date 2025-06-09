//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//61850ClientCfgMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_C61850CLIENTCONFIG       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CREMOTEDEVS       (MngrCLASSID_EXLISTCLASS + 0X00000001)
#define MNGRCLASSID_CREMOTEDEV       (MngrCLASSID_BASECLASS + 0X00000002)

class C61850ClientCfgMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	C61850ClientCfgMngrXmlRWKeys();
	virtual ~C61850ClientCfgMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static C61850ClientCfgMngrXmlRWKeys* g_pXmlKeys;
	static C61850ClientCfgMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCRemoteDevKey; //remote-dev
	BSTR m_strCRemoteDevsKey; //remote-devs
	BSTR m_strC61850ClientConfigKey; //client-config
	BSTR m_strDebug_ModeKey; //debug-mode
	BSTR m_strUse_Map_FileKey; //use-map-file
	BSTR m_strEna_Write_Wait_After_SelKey; //ena-write-wait-after-sel
	BSTR m_strEna_Write_WaitKey; //ena-write-wait
	BSTR m_strRead_Ain_Use_ReportKey; //read-ain-use-report
	BSTR m_strAdd_Rpt_BufferKey; //add-rpt-buffer
	BSTR m_strCan_Write_Active_SgKey; //can-write-active-sg
	BSTR m_strProtocol_VersionKey; //protocol-version
	BSTR m_strUse_DsdoutKey; //use-dsdout
	BSTR m_strEna_Read_Before_WriteKey; //ena-read-before-write
	BSTR m_strWrite_Data_Wait_MsKey; //write-data-wait-ms
	BSTR m_strAuto_Gen_Model_DatasKey; //auto-gen-model-datas
	BSTR m_strUse_Gsp_LogKey; //use-gsp-log
	BSTR m_strSpecifi_DatasetKey; //specifi-dataset
	BSTR m_strIntg_PdKey; //intg-pd
	BSTR m_strOpt_Flds_BRKey; //opt-flds-BR
	BSTR m_strOpt_Flds_RPKey; //opt-flds-RP
	BSTR m_strTrg_Ops_UIKey; //trg-ops-UI
	BSTR m_strUse_Entryid_UpdateKey; //use-entryid-update
	BSTR m_strWriteCtrlTypeKey; //write-ctrl-type
	BSTR m_strCtrlTestKey; //ctrl-test
	BSTR m_strCtrlCheckKey; //ctrl-check
	BSTR m_strHasTimeActKey; //has-time-act
	BSTR m_strIpKey; //ip
	BSTR m_strLocal_IpKey; //local-ip
	BSTR m_strUse_Local_IpKey; //use-local-ip

public:
	static BSTR CRemoteDevKey()  {   return g_pXmlKeys->m_strCRemoteDevKey;  }
	static BSTR CRemoteDevsKey()  {   return g_pXmlKeys->m_strCRemoteDevsKey;  }
	static BSTR C61850ClientConfigKey()  {   return g_pXmlKeys->m_strC61850ClientConfigKey;  }
	static BSTR Debug_ModeKey()  {   return g_pXmlKeys->m_strDebug_ModeKey;  }
	static BSTR Use_Map_FileKey()  {   return g_pXmlKeys->m_strUse_Map_FileKey;  }
	static BSTR Ena_Write_Wait_After_SelKey()  {   return g_pXmlKeys->m_strEna_Write_Wait_After_SelKey;  }
	static BSTR Ena_Write_WaitKey()  {   return g_pXmlKeys->m_strEna_Write_WaitKey;  }
	static BSTR Read_Ain_Use_ReportKey()  {   return g_pXmlKeys->m_strRead_Ain_Use_ReportKey;  }
	static BSTR Add_Rpt_BufferKey()  {   return g_pXmlKeys->m_strAdd_Rpt_BufferKey;  }
	static BSTR Can_Write_Active_SgKey()  {   return g_pXmlKeys->m_strCan_Write_Active_SgKey;  }
	static BSTR Protocol_VersionKey()  {   return g_pXmlKeys->m_strProtocol_VersionKey;  }
	static BSTR Use_DsdoutKey()  {   return g_pXmlKeys->m_strUse_DsdoutKey;  }
	static BSTR Ena_Read_Before_WriteKey()  {   return g_pXmlKeys->m_strEna_Read_Before_WriteKey;  }
	static BSTR Write_Data_Wait_MsKey()  {   return g_pXmlKeys->m_strWrite_Data_Wait_MsKey;  }
	static BSTR Auto_Gen_Model_DatasKey()  {   return g_pXmlKeys->m_strAuto_Gen_Model_DatasKey;  }
	static BSTR Use_Gsp_LogKey()  {   return g_pXmlKeys->m_strUse_Gsp_LogKey;  }
	static BSTR Specifi_DatasetKey()  {   return g_pXmlKeys->m_strSpecifi_DatasetKey;  }
	static BSTR Intg_PdKey()  {   return g_pXmlKeys->m_strIntg_PdKey;  }
	static BSTR Opt_Flds_BRKey()  {   return g_pXmlKeys->m_strOpt_Flds_BRKey;  }
	static BSTR Opt_Flds_RPKey()  {   return g_pXmlKeys->m_strOpt_Flds_RPKey;  }
	static BSTR Trg_Ops_UIKey()  {   return g_pXmlKeys->m_strTrg_Ops_UIKey;  }
	static BSTR Use_Entryid_UpdateKey()  {   return g_pXmlKeys->m_strUse_Entryid_UpdateKey;  }
	static BSTR WriteCtrlTypeKey()  {   return g_pXmlKeys->m_strWriteCtrlTypeKey;  }
	static BSTR IpKey()  {   return g_pXmlKeys->m_strIpKey;  }
	static BSTR Local_IpKey()  {   return g_pXmlKeys->m_strLocal_IpKey;  }
	static BSTR Use_Local_IpKey()  {   return g_pXmlKeys->m_strUse_Local_IpKey;  }
};



class C61850ClientCfgMngrConstGlobal
{
private:
	C61850ClientCfgMngrConstGlobal();
	virtual ~C61850ClientCfgMngrConstGlobal();

public:
	static C61850ClientCfgMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static C61850ClientCfgMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};


#define  DLT_WRITE_CTRL_TYPE_DIRECT                            0
#define  DLT_WRITE_CTRL_TYPE_SWV                               1
#define  DLT_WRITE_CTRL_TYPE_SBO                               2

