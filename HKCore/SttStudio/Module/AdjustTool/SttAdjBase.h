//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//SttAdjBase.h  CSttAdjBase

#pragma once

#include "../../../Module/DataMngr/DataGroup.h"
///#include "..\..\..\oa\Module\OA_DB\PowerSky_OAGlobal.h"

#include "../../../Module/API/GlobalConfigApi.h"

//2021-5-4  lijunqing  ͳһ���嵽У׼ϵ���ļ��У��������
#include "../SttTest/Common/tmt_adjust_sys_para_module_def.h"
#include "../SttTest/Common/tmt_adjust_sys_para_trans.h"

//xxy:ƴcom�ӿڲ���
#define CommDBData_ID_Records	("Records")
#define CommDBData_ID_Record	("Record")

#define STT_MODEL_TYPE_Module	0
#define STT_MODEL_TYPE_Device	1

#define STT_ADJ_FILE_FILTER  _T("У׼�ļ�(*.xml)|*.xml||")


class CSttAdjBase : public CExBaseList
{
public:
	CSttAdjBase();
	virtual ~CSttAdjBase();

	CDataGroup *m_pSttAdjRef;
	
//���غ���
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
	CDataGroup *AddNewDeviceModelByVersionViewCfg(CDataGroup *pVersionViewCfgGroup);    //��ȡ�汾��Ϣ��װ�����Ժ�ģ������)
	void AddDeviceAttrsByVersionViewCfg(CDataGroup *pConfigFile,CDataGroup *pDeviceAttr);     //����config������id
	void AddAllModuleAttrsByVersionViewCfg(CDataGroup *pConfigFile,CDataGroup *pDevice);  //��ȡģ������
	void GetModuleAttrDataByConfig(CDataGroup *pModuleGroup_Cfg,CDataGroup *pCurrModuleAttrs,CDataGroup *pNewModuleAttrs);  //����config������id

public:
	CString m_strModel;
	CString m_strSN;
	CString m_strFactory;
	CString m_strDateFac;
	long m_nStateCount;//zhouhj 20220401 ��Ӳ����Ϣ�ļ��л�ȡ��״̬�������忪�뿪������
	long m_nBinCount;
	long m_nBoutCount;
	long m_nSTModeSet;//2023-11-28 suyang ��Ӳ����Ϣ�ļ��л�ȡST��ģʽʹ��
	long m_nUartCount; //2024.05.8chenling ��Ӳ����Ϣ�����ȡ���ڸ���
	long m_nBinVoltMeas;//2024-11-5 wuxinyi ���忪���ѹ�ɼ�(0-��֧�֣�1-֧��)
	long m_nMergeCurTerminal;//suyang  �ϲ��������ӣ�-1 ��֧�ֺϲ������0 ���ϲ������ 1  �ϲ�Ϊ1��ͨ�������3 �ϲ�Ϊ3��ͨ�������

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
