//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttAdjBase.h  CSttAdjBase

#pragma once

#include "../../../Module/DataMngr/DataGroup.h"
///#include "..\..\..\oa\Module\OA_DB\PowerSky_OAGlobal.h"

#include "../../../Module/API/GlobalConfigApi.h"

//2021-5-4  lijunqing  统一定义到校准系数文件中，方便访问
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"
#include "../SttTest/Common/tmt_adjust_sys_para_trans.h"

//xxy:拼com接口参数
#define CommDBData_ID_Records	("Records")
#define CommDBData_ID_Record	("Record")

#define STT_MODEL_TYPE_Module	0
#define STT_MODEL_TYPE_Device	1

#define STT_ADJ_FILE_FILTER  _T("校准文件(*.xml)|*.xml||")


class CSttAdjBase : public CExBaseList
{
public:
	CSttAdjBase();
	virtual ~CSttAdjBase();

	CDataGroup *m_pSttAdjRef;
	
//重载函数
public:
	virtual void AttatchAdjRef(CDataGroup *pSttAdjRef, BOOL bSetParent=FALSE);
	virtual void DettachAdjRef(BOOL bDelete=TRUE);

	void AddLongDataVal(const CString &strID, long &nValue);
	BOOL GetCountDataVal(const CString &strID, long &nValue);
	BOOL SetCountDataVal(const CString &strID, long nVal);
	void IncreaseCountData(const CString &strID, long nValAdd=1);
	void DecreaseCountData(const CString &strID, long nValAdd=1);

	long GetGroupCount(const CString &strDataType);
	long GetGroupCount(CDataGroup *pDataGroup);
	long GetGroupIndex(CDataGroup *pDataGroup);
	CDataGroup* DeleteGroup(CDataGroup *pDataGroup);

	long GetDvmDataIndex(CDvmData *pData);
	CDvmData* DeleteDvmData(CDvmData *pDvmData);

	//zyq 20221209 
	CDataGroup *AddNewDeviceModelByVersionViewCfg(CDataGroup *pVersionViewCfgGroup);    //获取版本信息（装置属性和模块属性)
	void AddDeviceAttrsByVersionViewCfg(CDataGroup *pConfigFile,CDataGroup *pDeviceAttr);     //遍历config，查找id
	void AddAllModuleAttrsByVersionViewCfg(CDataGroup *pConfigFile,CDataGroup *pDevice);  //获取模块属性
	void GetModuleAttrDataByConfig(CDataGroup *pModuleGroup_Cfg,CDataGroup *pCurrModuleAttrs,CDataGroup *pNewModuleAttrs);  //遍历config，查找id

public:
	CString m_strModel;
	CString m_strSN;
	CString m_strFactory;
	CString m_strDateFac;
	long m_nStateCount;//zhouhj 20220401 从硬件信息文件中获取总状态数、主板开入开出数量
	long m_nBinCount;
	long m_nBoutCount;
	long m_nSTModeSet;//2023-11-28 suyang 从硬件信息文件中获取ST口模式使能
	long m_nUartCount; //2024.05.8chenling 从硬件信息里面获取串口个数

	virtual void GetAttrs(){};
	virtual long GetModelType(){return STT_MODEL_TYPE_Module;}
	virtual void GenerateDBCommAttrs(CDvmData *pRecord,BOOL bModel);
	virtual CDataGroup *GenerateDBCommAttrs(BOOL bModel);
};


void stt_adj_init_cmb_hdgear_type(CComboBox *pComboBox);
CString stt_adj_get_cur_hdgear_type(CComboBox *pComboBox);

void stt_adj_init_cmb_channel(CComboBox *pComboBox);
CString stt_adj_get_cur_channel(CComboBox *pComboBox);

void stt_adj_init_cmb_ch_wave(CComboBox *pComboBox, long nHarmCount);
CString stt_adj_get_cur_ch_wave(CComboBox *pComboBox);

void stt_AddLongDataVal(CDataGroup *pParent, const CString &strID, long &nValue);
BOOL stt_GetCountDataVal(CDataGroup *pParent, const CString &strID, long &nValue);
BOOL stt_SetCountDataVal(CDataGroup *pParent, const CString &strID, long nVal);
void stt_IncreaseCountData(CDataGroup *pParent, const CString &strID, long nValAdd=1);
void stt_DecreaseCountData(CDataGroup *pParent, const CString &strID, long nValAdd=1);
//BOOL stt_GetCountDataVal(CDataGroup *pParent, const CString &strID, long &nValue);

CString SttAdj_GetTabelName(BOOL bModel);
