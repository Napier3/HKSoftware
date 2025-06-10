#include "stdafx.h"
#include "tmt_adjust_sys_para_trans.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "tmt_adjust_sys_para_module_def.h"
#include "../../SttDevice/Module/PowerCtrl/SttPowerCtrlCom.h"

#ifdef NOT_USE_XLANGUAGE
#else
#include "../../XLangResource_Native.h"                              
#endif

CDataTypes *g_pSttAdjSysParaDataTypes = NULL;

// class CSttAdjSysParaDataTypes : public CDataTypes
// {
// public:
    CSttAdjSysParaDataTypes::CSttAdjSysParaDataTypes()
    {
        g_pSttAdjSysParaDataTypes = this;
 #ifdef NOT_USE_XLANGUAGE
        InitAdjSysParaDataTypes();
#endif
    }
    CSttAdjSysParaDataTypes::~CSttAdjSysParaDataTypes()
    {
    }

// public:
	void CSttAdjSysParaDataTypes::InitAdjSysParaDataType_ModuleType()
    {
        CDataType *pNew = AddNew2(STT_ADJ_ID_ModuleType,        STT_ADJ_ID_ModuleType);
#ifdef NOT_USE_XLANGUAGE
        pNew->AddNewValue(_T("������ѹ���"), STT_MODULE_TYPE_VOLT_ID,               STT_MODULE_TYPE_VOLT);
        pNew->AddNewValue(_T("�����������"), STT_MODULE_TYPE_CURRENT_ID,         STT_MODULE_TYPE_CURRENT);
        pNew->AddNewValue(_T("8�����׿����ְ�"), STT_MODULE_TYPE_DIGITAL_0G8M_ID,  STT_MODULE_TYPE_DIGITAL_0G8M);
        pNew->AddNewValue(_T("6�����׿�,2��ǧ�׿����ְ�"), STT_MODULE_TYPE_DIGITAL_2G6M_ID,  STT_MODULE_TYPE_DIGITAL_2G6M);
        pNew->AddNewValue(_T("4�����׿�,4��ǧ�׿����ְ�"), STT_MODULE_TYPE_DIGITAL_4G4M_ID,  STT_MODULE_TYPE_DIGITAL_4G4M);
        pNew->AddNewValue(_T("ֱ���������"), STT_MODULE_TYPE_DCCURRENT_ID,      STT_MODULE_TYPE_DCCURRENT);
        pNew->AddNewValue(_T("ֱ����ѹ���"), STT_MODULE_TYPE_DCVOLT_ID,            STT_MODULE_TYPE_DCVOLT);
        pNew->AddNewValue(_T("��������չ��"), STT_MODULE_TYPE_SWITCH_ID,            STT_MODULE_TYPE_SWITCH);
        pNew->AddNewValue(_T("С�ź�ģ����"), STT_MODULE_TYPE_WEEK_EX_ID,           STT_MODULE_TYPE_WEEK_EX);
//20231023 	STT_MODULE_TYPE_WEEK_MAIN �ϲ��� STT_MODULE_TYPE_WEEK_EX
//        pNew->AddNewValue(_T("����С�ź�"), STT_MODULE_TYPE_WEEK_MAIN_ID,       STT_MODULE_TYPE_WEEK_MAIN);
        pNew->AddNewValue(_T("��ֱFT3��"), STT_MODULE_TYPE_FT3_ID,                   STT_MODULE_TYPE_FT3);
        pNew->AddNewValue(_T("U��I��ϲ��"), STT_MODULE_TYPE_VOLT_CURRENT_ID,   STT_MODULE_TYPE_VOLT_CURRENT);
        pNew->AddNewValue(_T("��ѹ�ɼ����"), STT_MODULE_TYPE_MEAS_VOLT_ID,   STT_MODULE_TYPE_MEAS_VOLT);
        pNew->AddNewValue(_T("�����ɼ����"), STT_MODULE_TYPE_MEAS_CURRENT_ID,   STT_MODULE_TYPE_MEAS_CURRENT);
//		pNew->AddNewValue(_T("48·С�ź�ģ����"), STT_MODULE_TYPE_WEEK_EX48_ID,           STT_MODULE_TYPE_WEEK_EX_48);
        pNew->AddNewValue(_T("�ȿ�2MͨѶ���"), STT_MODULE_TYPE_Stable2M_ID,   STT_MODULE_TYPE_Stable2M);
		pNew->AddNewValue(_T("ADMU���"), STT_MODULE_TYPE_ADMU_ID,   STT_MODULE_TYPE_ADMU);
#else
        pNew->AddNewValue(/*_T("������ѹ���")*/g_sLangTxt_Native_ACVoltPlugin, STT_MODULE_TYPE_VOLT_ID,               STT_MODULE_TYPE_VOLT);
        pNew->AddNewValue(/*_T("�����������")*/g_sLangTxt_Native_ACCurrPlugin, STT_MODULE_TYPE_CURRENT_ID,         STT_MODULE_TYPE_CURRENT);
        pNew->AddNewValue(/*_T("8�����׿����ְ�")*/g_sLangTxt_Native_8x100MbpsDB, STT_MODULE_TYPE_DIGITAL_0G8M_ID,  STT_MODULE_TYPE_DIGITAL_0G8M);
        pNew->AddNewValue(/*_T("6�����׿�,2��ǧ�׿����ְ�")*/g_sLangTxt_Native_6x100M2x1000MDB, STT_MODULE_TYPE_DIGITAL_2G6M_ID,  STT_MODULE_TYPE_DIGITAL_2G6M);
        pNew->AddNewValue(/*_T("4�����׿�,4��ǧ�׿����ְ�")*/g_sLangTxt_Native_4x100M4x1000MDB, STT_MODULE_TYPE_DIGITAL_4G4M_ID,  STT_MODULE_TYPE_DIGITAL_4G4M);
        pNew->AddNewValue(/*_T("ֱ���������")*/g_sLangTxt_Native_DCCurrPlugin, STT_MODULE_TYPE_DCCURRENT_ID,      STT_MODULE_TYPE_DCCURRENT);
        pNew->AddNewValue(/*_T("ֱ����ѹ���")*/g_sLangTxt_Native_DCVoltPlugin, STT_MODULE_TYPE_DCVOLT_ID,            STT_MODULE_TYPE_DCVOLT);
        pNew->AddNewValue(/*_T("��������չ��")*/g_sLangTxt_Native_DI_O_ExpBoard, STT_MODULE_TYPE_SWITCH_ID,            STT_MODULE_TYPE_SWITCH);
        pNew->AddNewValue(/*_T("С�ź�ģ����")*/g_sLangTxt_Native_LSModPlugin, STT_MODULE_TYPE_WEEK_EX_ID,           STT_MODULE_TYPE_WEEK_EX);
//        pNew->AddNewValue(/*_T("����С�ź�")*/g_sLangTxt_Native_MBLowSignal, STT_MODULE_TYPE_WEEK_MAIN_ID,       STT_MODULE_TYPE_WEEK_MAIN);
        pNew->AddNewValue(/*_T("��ֱFT3��")*/g_sLangTxt_Native_FSFT3Board, STT_MODULE_TYPE_FT3_ID,                   STT_MODULE_TYPE_FT3);
        pNew->AddNewValue(/*_T("U��I��ϲ��")*/g_sLangTxt_Native_UIHybridPlugin, STT_MODULE_TYPE_VOLT_CURRENT_ID,   STT_MODULE_TYPE_VOLT_CURRENT);
        pNew->AddNewValue(/*_T("��ѹ�ɼ����")*/g_sLangTxt_Native_VoltAcqPlugin, STT_MODULE_TYPE_MEAS_VOLT_ID,   STT_MODULE_TYPE_MEAS_VOLT);
        pNew->AddNewValue(/*_T("�����ɼ����")*/g_sLangTxt_Native_CurrAcqPlugin, STT_MODULE_TYPE_MEAS_CURRENT_ID,   STT_MODULE_TYPE_MEAS_CURRENT);

//		pNew->AddNewValue(/*_T("48·С�ź�ģ����")*/, STT_MODULE_TYPE_WEEK_EX48_ID,           STT_MODULE_TYPE_WEEK_EX_48);

        pNew->AddNewValue(/*_T("�ȿ�2MͨѶ���")*/g_sLangTxt_Native_Stable2MCommPlugin, STT_MODULE_TYPE_Stable2M_ID,   STT_MODULE_TYPE_Stable2M);
		pNew->AddNewValue(_T("ADMU���"), STT_MODULE_TYPE_ADMU_ID,   STT_MODULE_TYPE_ADMU);
#endif
    }
	void CSttAdjSysParaDataTypes::InitAdjSysParaDataType_WorkMode()
    {
        CDataType *pNew = AddNew2(STT_ADJ_ID_WorkMode,        STT_ADJ_ID_WorkMode);
#ifdef NOT_USE_XLANGUAGE
        pNew->AddNewValue(_T("���"), STT_ADJ_ID_WorkMode_Output,               0);
        pNew->AddNewValue(_T("�ɼ�"), STT_ADJ_ID_WorkMode_MEAS,                1);
#else
		pNew->AddNewValue(/*_T("���")*/g_sLangTxt_Output, STT_ADJ_ID_WorkMode_Output,               0);
		pNew->AddNewValue(/*_T("�ɼ�")*/g_sLangTxt_Native_Acquisition, STT_ADJ_ID_WorkMode_MEAS,                1);
#endif
    }
	void CSttAdjSysParaDataTypes::InitAdjSysParaDataType_EeType()
    {
        CDataType *pNew = AddNew2(STT_ADJ_ID_EeType,        STT_ADJ_ID_EeType);
#ifdef NOT_USE_XLANGUAGE
        pNew->AddNewValue(_T("��ѹ"),    STT_ADJ_ID_EeType_Voltage,   STT_CH_EETYPE_VOLTAGE);
        pNew->AddNewValue(_T("����"),    STT_ADJ_ID_EeType_Current,   STT_CH_EETYPE_CURRENT);
        pNew->AddNewValue(_T("������"), STT_ADJ_ID_EeType_Binary,     STT_CH_EETYPE_BINARY);
#else
		pNew->AddNewValue(/*_T("��ѹ")*/g_sLangTxt_Native_Voltage,    STT_ADJ_ID_EeType_Voltage,   STT_CH_EETYPE_VOLTAGE);
		pNew->AddNewValue(/*_T("����")*/g_sLangTxt_Native_Current,    STT_ADJ_ID_EeType_Current,   STT_CH_EETYPE_CURRENT);
		pNew->AddNewValue(/*_T("������")*/g_sLangTxt_Native_SwitchVal, STT_ADJ_ID_EeType_Binary,     STT_CH_EETYPE_BINARY);
#endif
    }
    void CSttAdjSysParaDataTypes::InitAdjSysParaDataType_ModulePower()
    {
        CDataType *pNew = AddNew2(STT_ADJ_ID_ModulePower,        STT_ADJ_ID_ModulePower);
#ifdef NOT_USE_XLANGUAGE
        pNew->AddNewValue(_T("δ����"), STT_MODULE_POWER_UNKNOWN_ID,    STT_MODULE_POWER_UNKNOWN);
        pNew->AddNewValue(_T("130����ѹģ��"), STT_MODULE_VOLT_V130_130_ID,    STT_MODULE_VOLT_V130_130);
        pNew->AddNewValue(_T("248����ѹģ��"), STT_MODULE_VOLT_V248_248_ID,    STT_MODULE_VOLT_V248_248);
        pNew->AddNewValue(_T("270����ѹģ������ѹ"), STT_MODULE_VOLT_V270_270_ID,    STT_MODULE_VOLT_V270_270);
        pNew->AddNewValue(_T("270����ѹģ������ѹ"), STT_MODULE_VOLT_V270_380_ID,    STT_MODULE_VOLT_V270_380);
        pNew->AddNewValue(_T("300����ѹģ������ѹ"), STT_MODULE_VOLT_V300_300_ID,    STT_MODULE_VOLT_V300_300);
        pNew->AddNewValue(_T("300����ѹģ������ѹ"), STT_MODULE_VOLT_V300_440_ID,    STT_MODULE_VOLT_V300_440);
        pNew->AddNewValue(_T("12.5������ģ��"), STT_MODULE_CURRENT_C12_5_ID,    STT_MODULE_CURRENT_C12_5);
        pNew->AddNewValue(_T("20������ģ��"), STT_MODULE_CURRENT_C20_ID,    STT_MODULE_CURRENT_C20);
        pNew->AddNewValue(_T("32������ģ��"), STT_MODULE_CURRENT_C32_ID,    STT_MODULE_CURRENT_C32);
        pNew->AddNewValue(_T("130��20�����ģ��"), STT_MODULE_UI_V130_C20_ID,    STT_MODULE_UI_V130_C20);
        pNew->AddNewValue(_T("310��60�����ģ��"), STT_MODULE_UI_V310_C60_ID,    STT_MODULE_UI_V310_C60);
        pNew->AddNewValue(_T("PFC_6A ģ��"), STT_MODULE_UI_PFC6A_ID,    STT_MODULE_UI_PFC6A);
        pNew->AddNewValue(_T("PIA12DS ģ��"), STT_MODULE_WEEK_PIA12DS_ID,    STT_MODULE_WEEK_PIA12DS);
        pNew->AddNewValue(_T("PIA48S ģ��"), STT_MODULE_WEEK_PIA48S_ID,    STT_MODULE_WEEK_PIA48S);
        pNew->AddNewValue(_T("EVTECT ģ��"), STT_MODULE_WEEK_EVTECT_ID,    STT_MODULE_WEEK_EVTECT);
        pNew->AddNewValue(_T("ֱ����������ģ��"), STT_MODULE_WEEK_EVTECT_Ex1_ID,    STT_MODULE_WEEK_EVTECT_Ex1);
        pNew->AddNewValue(_T("6·10��ֱ��ģ��"), STT_MODULE_WEEK_DC6U10V_ID,    STT_MODULE_WEEK_DC6U10V);
        pNew->AddNewValue(_T("6·20����ֱ��ģ��"), STT_MODULE_WEEK_DC6I20mA_ID,    STT_MODULE_WEEK_DC6I20mA);
        pNew->AddNewValue(_T("PN6U6Iֱ��С�ź�ģ��"), STT_MODULE_WEEK_PN_DC6U6I_ID,    STT_MODULE_WEEK_PN_DC6U6I);
		pNew->AddNewValue(_T("PN��������С�ź�ģ��"), STT_MODULE_WEEK_PN_MAIN_ID,    STT_MODULE_WEEK_PN_MAIN);
		pNew->AddNewValue(_T("L336DС�ź�ģ��"), STT_MODULE_WEEK_L336D_ID,    STT_MODULE_WEEK_L336D);
		pNew->AddNewValue(_T("PIA0103 ģ��"), STT_MODULE_UI_PIA0103_ID,    STT_MODULE_UI_PIA0103);
		pNew->AddNewValue(_T("PNS330 ģ��(����ͬ�����10��)"), STT_MODULE_UI_PNS330_ID,    STT_MODULE_UI_PNS330);
		pNew->AddNewValue(_T("PNS330_H ģ��"), STT_MODULE_UI_PNS330_H_ID,    STT_MODULE_UI_PNS330_H);
		pNew->AddNewValue(_T("PNS331 ģ��"), STT_MODULE_UI_PNS331_ID,    STT_MODULE_UI_PNS331);
		pNew->AddNewValue(_T("PNS330 ģ��(����ͬ�����20��)"), STT_MODULE_UI_PNS330_ABC_20_ID,    STT_MODULE_UI_PNS330_ABC_20);
		pNew->AddNewValue(_T("PNS330_6 ģ��"), STT_MODULE_UI_PNS330_6_ID,    STT_MODULE_UI_PNS330_6);
#else
		pNew->AddNewValue(/*_T("δ����")*/g_sLangTxt_Native_Undefined, STT_MODULE_POWER_UNKNOWN_ID,    STT_MODULE_POWER_UNKNOWN);
		pNew->AddNewValue(/*_T("130����ѹģ��")*/g_sLangTxt_Native_130VVoltageModule, STT_MODULE_VOLT_V130_130_ID,    STT_MODULE_VOLT_V130_130);
		pNew->AddNewValue(/*_T("248����ѹģ��")*/g_sLangTxt_Native_248VVoltageModule, STT_MODULE_VOLT_V248_248_ID,    STT_MODULE_VOLT_V248_248);
		pNew->AddNewValue(/*_T("270����ѹģ������ѹ")*/g_sLangTxt_Native_270VVMNoBoost, STT_MODULE_VOLT_V270_270_ID,    STT_MODULE_VOLT_V270_270);
		pNew->AddNewValue(/*_T("270����ѹģ������ѹ")*/g_sLangTxt_Native_270VVModuleWBoost, STT_MODULE_VOLT_V270_380_ID,    STT_MODULE_VOLT_V270_380);
		pNew->AddNewValue(/*_T("300����ѹģ������ѹ")*/g_sLangTxt_Native_300VVMNoBoost, STT_MODULE_VOLT_V300_300_ID,    STT_MODULE_VOLT_V300_300);
		pNew->AddNewValue(/*_T("300����ѹģ������ѹ")*/g_sLangTxt_Native_300VVModuleWBoost, STT_MODULE_VOLT_V300_440_ID,    STT_MODULE_VOLT_V300_440);
		pNew->AddNewValue(/*_T("12.5������ģ��")*/g_sLangTxt_Native_125ACModule, STT_MODULE_CURRENT_C12_5_ID,    STT_MODULE_CURRENT_C12_5);
		pNew->AddNewValue(/*_T("20������ģ��")*/g_sLangTxt_Native_20ACModule, STT_MODULE_CURRENT_C20_ID,    STT_MODULE_CURRENT_C20);
		pNew->AddNewValue(/*_T("32������ģ��")*/g_sLangTxt_Native_32ACModule, STT_MODULE_CURRENT_C32_ID,    STT_MODULE_CURRENT_C32);
		pNew->AddNewValue(/*_T("130��20�����ģ��")*/g_sLangTxt_Native_125V20AHM, STT_MODULE_UI_V130_C20_ID,    STT_MODULE_UI_V130_C20);
		pNew->AddNewValue(/*_T("310��60�����ģ��")*/g_sLangTxt_Native_310V60AHM, STT_MODULE_UI_V310_C60_ID,    STT_MODULE_UI_V310_C60);
		pNew->AddNewValue(/*_T("PFC_6A ģ��")*/g_sLangTxt_Native_PFC6A, STT_MODULE_UI_PFC6A_ID,    STT_MODULE_UI_PFC6A);
		pNew->AddNewValue(/*_T("PIA12DS ģ��")*/g_sLangTxt_Native_P12DSM, STT_MODULE_WEEK_PIA12DS_ID,    STT_MODULE_WEEK_PIA12DS);
		pNew->AddNewValue(/*_T("PIA48S ģ��")*/g_sLangTxt_Native_P48SM, STT_MODULE_WEEK_PIA48S_ID,    STT_MODULE_WEEK_PIA48S);
		pNew->AddNewValue(/*_T("EVTECT ģ��")*/g_sLangTxt_Native_EVTM, STT_MODULE_WEEK_EVTECT_ID,    STT_MODULE_WEEK_EVTECT);
		pNew->AddNewValue(/*_T("ֱ����������ģ��")*/g_sLangTxt_Native_DCIPM, STT_MODULE_WEEK_EVTECT_Ex1_ID,    STT_MODULE_WEEK_EVTECT_Ex1);
		pNew->AddNewValue(/*_T("6·10��ֱ��ģ��")*/g_sLangTxt_Native_6C10VDCM, STT_MODULE_WEEK_DC6U10V_ID,    STT_MODULE_WEEK_DC6U10V);
		pNew->AddNewValue(/*_T("6·20����ֱ��ģ��")*/g_sLangTxt_Native_6C20mADC, STT_MODULE_WEEK_DC6I20mA_ID,    STT_MODULE_WEEK_DC6I20mA);
		pNew->AddNewValue(/*_T("PN6U6Iֱ��С�ź�ģ��")*/g_sLangTxt_Native_PN6U6IDCSSM, STT_MODULE_WEEK_PN_DC6U6I_ID,    STT_MODULE_WEEK_PN_DC6U6I);
#endif
    }
	void CSttAdjSysParaDataTypes::InitAdjSysParaDataType_CurrentModuleMerge()
    {
        CDataType *pNew = AddNew2(STT_ADJ_ID_ChMergeMode,        STT_ADJ_ID_ChMergeMode);
#ifdef NOT_USE_XLANGUAGE
		pNew->AddNewValue(_T("��֧������ϲ�"), _T("NoChMerge"),    STT_CURRENT_ChMergeMode_No);
		pNew->AddNewValue(_T("6·���Ժϲ�Ϊ1·"), _T("ChMerge_1Ch"),    STT_CURRENT_ChMergeMode_1Ch);
		pNew->AddNewValue(_T("6·���Ժϲ�Ϊ3·"), _T("ChMerge_3Ch"),    STT_CURRENT_ChMergeMode_3Ch);
		pNew->AddNewValue(_T("6·�̶��ϲ�Ϊ3·"), _T("ChMerge_3Ch_Fixed"),    STT_CURRENT_ChMergeMode_3Ch_Fixed);
		pNew->AddNewValue(_T("6·�̶��ϲ�Ϊ1·"), _T("ChMerge_1Ch_Fixed"),    STT_CURRENT_ChMergeMode_1Ch_Fixed);
#else
		pNew->AddNewValue(/*_T("��֧������ϲ�")*/g_sLangTxt_Native_OutputNotSupported, _T("NoChMerge"),    0);
		pNew->AddNewValue(/*_T("6·���Ժϲ�Ϊ1·")*/g_sLangTxt_Native_6to1MergePossible, _T("ChMerge_1Ch"),    1);
		pNew->AddNewValue(/*_T("6·���Ժϲ�Ϊ3·")*/g_sLangTxt_Native_6to3MergePossible, _T("ChMerge_3Ch"),    2);
		pNew->AddNewValue(/*_T("6·�̶��ϲ�Ϊ3·")*/g_sLangTxt_Native_6to3FixedMerge, _T("ChMerge_3Ch_Fixed"),    3);
#endif
    }

    void CSttAdjSysParaDataTypes::InitAdjSysParaDataTypes()
    {
		DeleteAll();
        InitAdjSysParaDataType_ModuleType();
        InitAdjSysParaDataType_WorkMode();
        InitAdjSysParaDataType_EeType();
        InitAdjSysParaDataType_ModulePower();
        InitAdjSysParaDataType_CurrentModuleMerge();
    }
// };

CSttAdjSysParaDataTypes g_oSttAdjSysParaDataTypes;


void stt_tmt_adj_para_trans_to_string(long nSrcValue, const char *pszDataType, char *pszDestValue)
{
#ifndef NOT_USE_XLANGUAGE
	if (g_oSttAdjSysParaDataTypes.GetCount() == 0)
	{
		g_oSttAdjSysParaDataTypes.InitAdjSysParaDataTypes();
	}
#endif
    CDataType *pFind = (CDataType *)g_oSttAdjSysParaDataTypes.FindByID(pszDataType);

    if(pFind != NULL)
    {
        CDataTypeValue *pValue = pFind->FindByIndex(nSrcValue);

        if(pValue != NULL)
        {
            CString_to_char(pValue->m_strID, pszDestValue);
            return;
        }
    }

    sprintf(pszDestValue, "%d", nSrcValue);
}

void stt_tmt_adj_para_trans_to_long(const char *pszSrcValue, const char *pszDataType, long &nDestValue)
{
    if(*pszSrcValue == 0)
    {
        nDestValue = 0;
        return;
    }

    if('0' <= *pszSrcValue && *pszSrcValue <= '9')
    {
        nDestValue = atol(pszSrcValue);
        return;
    }
#ifndef NOT_USE_XLANGUAGE
	if (g_oSttAdjSysParaDataTypes.GetCount() == 0)
	{
		g_oSttAdjSysParaDataTypes.InitAdjSysParaDataTypes();
	}
#endif

    CDataType *pFind = (CDataType *)g_oSttAdjSysParaDataTypes.FindByID(pszDataType);

    if(pFind != NULL)
    {
        CDataTypeValue *pValue = (CDataTypeValue *)pFind->FindByID(pszSrcValue);

        if(pValue != NULL)
        {
            nDestValue = CString_To_long(pValue->m_strIndex);
            return;
        }
    }

    nDestValue = 0;
}



//2021-5-5  lijunqing  ����ط����ֻ�ȡ�ļ��Ĵ��룬����Υ����������ģ�黯˼·�������Ӵ˺���
CString stt_get_adj_sys_para_file_path()
{
    CString strFile;
    strFile = _P_GetConfigPath();
    strFile += STT_ADJ_SYS_FILE_NAME;
    return strFile;
}

