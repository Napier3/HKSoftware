#pragma once

#include "../../Module/OSInterface/OSInterface.h"
#ifdef _PSX_QT_LINUX_
    #include "tmt_adjust_sys_parameter.h"
#endif
#include "tmt_test_paras_head.h"

#ifndef NOT_USE_XLANGUAGE
#include "../../XLangResource_Native.h"
#endif

#define MAX_HARM_COUNT			81
#define MAX_HARM_COUNT_UI			51
#define MAX_BINARYIN_COUNT		20
#define MAX_BINARYOUT_COUNT		20
#define MAX_VOLTAGE_COUNT		48
#define MAX_CURRENT_COUNT		MAX_VOLTAGE_COUNT
//zhouhj 2023.9.15 ɾ���˺�,ͳһʹ������Ŀ���򿪳���Ӧ�ĺ�,Ŀǰʵ�����������10
//#define MAX_PARACOUNT_BINARY 	10//ͨ��10����������
#define MAX_MODULE_COUNT		12		//���ģ����
#define MAX_ExBINARY_COUNT		256//�����չ����������,�����Դ����256in,256out,���8����չģ��
#define BIBO_ACTCOUNT			64//���뿪���¼�ÿ��Ӳ�����Ӽ�¼��λ�ܴ���
//����Ӳ�����,16����Ϊһ��
#define MAX_GOOSE_CHANNEL_COUNT	256
#define MAX_MODULES_GOOSEPUB_COUNT 16 //16*4
//Ft3
#define MAX_FT3_CHANNEL_COUNT	100
#define MAX_MODULES_FT3PUB_COUNT 18 //12(DRT400) + 6(9-2/FT3)
//�ȿ�2Mͨ������
#define MAX_2M_CHANNEL_COUNT    16
#define MAX_2M_BLOCK_COUNT      8
#define MAX_2M_DATAIDX_COUNT    16
#define MAX_2M_DATAIDX_VALUE    22
#define MAX_2M_CMDIDX_COUNT     2
#define MAX_2M_MODULE_COUNT     2
#define MAX_2M_BLOCKS_COUNT     MAX_2M_BLOCK_COUNT * MAX_2M_MODULE_COUNT


//�첽ģ����������  ģ���������źš�������
#define ASYNC_MODULE_TYPE_COUNT		3
#define ASYNC_MODULE_TYPE_ANALOG		0
#define ASYNC_MODULE_TYPE_WEEK			1
#define ASYNC_MODULE_TYPE_DIGITAL		2


#define DC_CURRENT_COMMON_FAULT_TYPE_I1_1                                                    0
#define DC_CURRENT_COMMON_FAULT_TYPE_I1_2                                                    1
#define DC_CURRENT_COMMON_FAULT_TYPE_I1_3                                                    2
#define DC_CURRENT_COMMON_FAULT_TYPE_I2_1                                                    3
#define DC_CURRENT_COMMON_FAULT_TYPE_I2_2                                                    4
#define DC_CURRENT_COMMON_FAULT_TYPE_I2_3                                                    5
#define DC_CURRENT_COMMON_FAULT_TYPE_I3_1                                                    6
#define DC_CURRENT_COMMON_FAULT_TYPE_I3_2                                                    7
#define DC_CURRENT_COMMON_FAULT_TYPE_I3_3                                                    8
#define DC_CURRENT_COMMON_FAULT_TYPE_I4_1                                                    9
#define DC_CURRENT_COMMON_FAULT_TYPE_I4_2                                                    10
#define DC_CURRENT_COMMON_FAULT_TYPE_I4_3                                                    11


#define EPSINON 0.000001//float��֤���ȵ���Сֵ
#define pi 3.14159265357979823846

//�ݱ�������غ궨��
#define GRADIENT_MAX_COUNT	  20000//���ݱ䲽��
#define DGRESS_PARAM_MAX      74//ÿ���ݱ�����ֽ���
#define GRADIENT_AMP		   0//��ֵ
#define GRADIENT_ANG           1//��λ
#define GRADIENT_FRE           2//Ƶ��
#define GRADIENT_CHAN_COUNT    6//�ݱ�֧�����2��6·,6U6I

#define GRADIENT_TYPE_None	   0//�޵ݱ�
#define GRADIENT_TYPE_Linear   1//���Ա仯
#define GRADIENT_TYPE_Step	   2//���ݱ仯

#define STT_BOUT_REVERSAL_TRIG_MODE_TIME                          0   //������ת��ʽ:�����ο�ֵΪ��һ̬,ʱ�䴥��,��תʱ��Ϊ0����ת,��������ʱ�䷭ת;��ת����ʱ������Ϊ0�򲻻ᷭת
#define STT_BOUT_REVERSAL_TRIG_MODE_BIN                           1   //������ת��ʽ:����������
#define STT_BOUT_REVERSAL_TRIG_MODE_NOT                           2   //������ת��ʽ:����ת,������ֵ���,��һ��״̬�̶�Ϊ��ֵ
#define STT_BOUT_REVERSAL_TRIG_MODE_LAST_STATE                    3   //����ת������һ̬

#define STT_PT_IMIT_PHASE_A                          0  //PT������ģ��  A����� .����ģ�顢��������ֵ�����õ�
#define STT_PT_IMIT_PHASE_B                          1
#define STT_PT_IMIT_PHASE_C                          2
#define STT_PT_IMIT_PHASE_AB                         3
#define STT_PT_IMIT_PHASE_BC                         4
#define STT_PT_IMIT_PHASE_CA                         5
#define STT_PT_IMIT_PHASE_ABC                        6

#define  TMT_BINLOGIC_AND 1//������
#define  TMT_BINLOGIC_OR  0//�����

//״̬���У�ͬ���첽�����к�
#define  TMT_MDSTATE_TIMETRIGGER                       0	    //0--ʱ�䴥��
#define  TMT_MDSTATE_TIMEBINTRIGGER                1    	//1--ʱ��+����������
#define  TMT_MDSTATE_BINTRIGGER                          2		//2--����������
#define  TMT_MDSTATE_MEARSURETRIGGER          3      //3--�ֶ�����
#define  TMT_MDSTATE_GPSBTRIGGER                      4		//4--GPS/B�봥��
#define  TMT_MDSTATE_LOWVOLTRIGGER                 5     //5--�͵�ѹ����
#define  MAX_STATE_NAME			128  //zhouhj 20211208 ����GOOSE�쳣ģ���״̬���������г��ȿ��ܳ���32�ֽ� �����Ϊ128
#define  MAX_STATE_ID           7 
#define STT_SINGLE_STATE_MAX_REPORT_COUNT         6   //dingxy 20240606 ����״̬�����ز�ͬ����
#define STT_STATE_REPORT_MAX_REPEAT_COUNT        10
#define STT_STATE_REPORT_TOTAL_STATE_NUM          20		 //dingxy 20240607 ״̬��������ܸ���(ͳ�ƶ��ѭ������״̬��)




#define STT_MACRO_ID_SystemConfig           "SystemConfig"
#define STT_MACRO_ID_UartConfig             "UartConfig"
#define STT_MACRO_ID_AuxDCOutput            "AuxDCOutput"//�������ڸ���ֱ���������  zhouhj 20211016 �������ڶ������ø���ֱ��
#define STT_MACRO_ID_ModulesGearSwitch      "ModulesGearSwitch"//�������ڵ�λ�л�//�������ڶ����л���λ
#define STT_MACRO_ID_AppConfig              "AppConfig" //�����������ò����Ǳ��  ��IDΪ���ݾɰ�ӿ� zhouhj 20221207
#define STT_MACRO_ID_ModuleOutput           "ModuleOutput"
#define STT_MACRO_ID_BinaryOutput           "BinaryOutput"
#define STT_MACRO_ID_BinaryExOutput         "BinaryExOutput"
#define STT_MACRO_ID_RegisterTest           "RegisterTest"
#define STT_MACRO_ID_BinMeas				"BinMeas"//����ɼ�
#define STT_MACRO_ID_SystemDefaultOutput    "SystemDefaultOutput"
#define STT_MACRO_ID_Iec61850Config     	"Iec61850Config"
#define STT_MACRO_ID_ChMapsConfig      		"ChMapsConfig"
#define STT_MACRO_ID_GradientTest      		"GradientTest"
#define STT_MACRO_ID_GradientMaxAngleTest   "GradientMaxAngleTest"
#define STT_MACRO_ID_GradientU				"GradientU"
#define STT_MACRO_ID_GradientI				"GradientI"

#define STT_MACRO_ID_ManualTest             "ManualTest"
#define STT_MACRO_ID_StateTest              "StateTest"
#define STT_MACRO_ID_HarmTest               "HarmTest"
#define STT_MACRO_ID_SoeTest                "SoeTest"
#define STT_MACRO_ID_SmvAbnTest				"SmvAbnTest"
#define STT_MACRO_ID_GseAbnTest				"GseAbnTest"

#define STT_MACRO_ID_SequenceManuTest       "SequenceManuTest"
#define STT_MACRO_ID_PowerManuTest          "PowerManuTest"
#define STT_MACRO_ID_LineVolManuTest        "LineVolManuTest"
#define STT_MACRO_ID_BinaryStateTest        "BinaryStateTest"//20230130 zhouhj �������ڿ�����״̬����
#define STT_MACRO_ID_BinaryManuTest         "BinaryManuTest"//�������ֶ�����
#define STT_MACRO_ID_SequenceGradientTest    "SequenceGradientTest"
#define STT_MACRO_ID_ImpedManualTest             "ImpedManualTest"//2024.6.14 ������
#define STT_MACRO_ID_PnvSCActValue   "SCActValue"

#define STT_MACRO_ID_FaultGradientTest    "FaultGradientTest" //2023-12-28 yuanting
#define STT_MACRO_ID_LineVolGradientTest     "LineVolGradientTest"
//�����ϰ�ӿڳ���,����MacroID  20221205 zhouhj
#define STT_MACRO_ID_State6U6I               "State6U6I"
#define STT_MACRO_ID_State4U3I               "State4U3I"
#define STT_MACRO_ID_UITest_12u12i            "UITest.12u12i"
#define STT_MACRO_ID_StateDiffCoef               "StateDiffCoef"
#define STT_MACRO_ID_PsuStateTest               "PsuStateTest"


#define STT_MACRO_ID_Distance               "Distance"//zhouhj 20210626 �ײ���Թ�������MacroID����λ���ṹ�干��MacroID
#define STT_MACRO_ID_Distance_I             "Distance_I"//
#define STT_MACRO_ID_DistanceSearch         "DistanceSearch"
#define STT_MACRO_ID_DistanceSearch_I         "DistanceSearch_I"
#define STT_MACRO_ID_RecloseAcc             "RecloseAcc"
#define STT_MACRO_ID_TURecloseAcc           "TURecloseAcc"//����ר���غ�բ�����ģ��
#define STT_MACRO_ID_StateRecloseAcc             "StateRecloseAcc"//Pnv����
#define STT_MACRO_ID_PsuCBOperate           "PsuCBOperate"
#define STT_MACRO_ID_StateOverCurrent       "StateOverCurrent"
#define STT_MACRO_ID_OverCurrent            "OverCurrent"
#define STT_MACRO_ID_VoltageTest            "VoltageTest"
#define STT_MACRO_ID_StateI0Current         "StateI0Current"
#define STT_MACRO_ID_ZeroCurrent            "ZeroCurrent"
#define STT_MACRO_ID_DiffCBOp				"DiffCBOp"  //����

#define STT_MACRO_ID_ULockOverCurrent       "ULockOverCurrent"
#define STT_MACRO_ID_PowerDirection         "PsuPowerDirection"
#define STT_MACRO_ID_PowerDirection_I         "PsuPowerDirection_I"
#define STT_MACRO_ID_PnvPowerDirection         "ActAngle"
#define STT_MACRO_ID_ActionTime             "ActionTime"
#define STT_MACRO_ID_CurrentInverseTime     "CurrentInverseTime"
#define STT_MACRO_ID_VoltageInverseTime     "VoltageInverseTime"
#define STT_MACRO_ID_VFInverseTime          "VFInverseTime"

#define STT_MACRO_ID_CurrentActValue        "CurrentActValue"
#define STT_MACRO_ID_VoltageActValue        "VoltageActValue"

#define STT_MACRO_ID_PnvCurrentActValue        "IActValue"
#define STT_MACRO_ID_PnvVoltageActValue        "UActValue"


#define STT_MACRO_ID_PsuLowFreqAct             "PsuLowFreqAct"
#define STT_MACRO_ID_PsuLowFreqTime            "PsuLowFreqTime"
#define STT_MACRO_ID_PsuLowFreqDfdt            "PsuLowFreqDfdt"
#define STT_MACRO_ID_PsuLowFreqILock           "PsuLowFreqILock"
#define STT_MACRO_ID_PsuLowFreqULock           "PsuLowFreqULock"

#define STT_MACRO_ID_PnvLowFreqTime            "LowFreqActTime"
#define STT_MACRO_ID_PnvLowFreqAct             "LowFreqActVal"
#define STT_MACRO_ID_PnvLowFreqDfdt            "LowFreqDfdt"

#define STT_MACRO_ID_PsuLowVolAct             "PsuLowVolAct"
#define STT_MACRO_ID_PsuLowVolTime            "PsuLowVolTime"
#define STT_MACRO_ID_PsuLowVolDvdt            "PsuLowVolDvdt"
#define STT_MACRO_ID_PsuLowVolILock              "PsuLowVolILock" 

#define STT_MACRO_ID_PnvLowVolAct             "LowVolActVal"
#define STT_MACRO_ID_PnvLowVolTime            "LowVolActTime"
#define STT_MACRO_ID_PnvLowVolDvdt            "LowVolDvdt"

#define STT_MACRO_ID_PsuPowerFreqDist          "PsuPowerFreqDist"//PsuVm�й�Ƶ�仯����ID
#define STT_MACRO_ID_LFPGP                     "LFPGP"//PonovoVm�й�Ƶ�仯����ID

#define STT_MACRO_ID_PsuSwing                "PsuSwingTest"

#define STT_MACRO_ID_SynActVoltageTest            "SynActVoltageTest"
#define STT_MACRO_ID_SynActFreqTest               "SynActFreqTest"
#define STT_MACRO_ID_SynLeadAngTest               "SynLeadAngTest"//��ǰ�Ǽ���ǰʱ�����
#define STT_MACRO_ID_SynAutoAdjTest               "SynAutoAdjTest"//���Ե�������  ���ô�
//#define STT_MACRO_ID_SynAdjCycleTest               "SynAdjCycleTest"//��ѹ���ڡ���Ƶ����,���ô˲���
#define STT_MACRO_ID_SynAdjVolTest                "SynAdjVolTest"
#define STT_MACRO_ID_SynAdjFreqTest               "SynAdjFreqTest"


#define STT_MACRO_ID_PsuDiffTCurrTest             "PsuDiffTCurrTest" //�������MacroID
#define STT_MACRO_ID_PsuDiffRateTest              "PsuDiffRateTest"
#define STT_MACRO_ID_PsuDiffQuickTest             "PsuDiffQCurrTest"
#define STT_MACRO_ID_PsuDiffHarmTest              "PsuDiffHarmTest"
#define STT_MACRO_ID_PsuDiffTimeTest              "PsuDiffTimeTest"

#define STT_MACRO_ID_Diff6IRateRestrainSearchTest             "Diff6IRateRestrainSearch" //�(6i)���MacroID
#define STT_MACRO_ID_Diff6IRateRestrainTest             "Diff6IRateRestrain"
#define STT_MACRO_ID_Diff6IHarmRestrainSearchTest             "Diff6IHarmRestrainSearch"

#define STT_MACRO_ID_PsuManuDiffTCurrTest             "PsuManuDiffTCurrTest" //�ֶ��ݱ�
#define STT_MACRO_ID_PsuManuDiffRateTest              "PsuManuDiffRateTest"
#define STT_MACRO_ID_PsuManuDiffQuickTest             "PsuManuDiffQCurrTest"
#define STT_MACRO_ID_PsuManuDiffHarmTest              "PsuManuDiffHarmTest"


#define STT_MACRO_ID_ElecRailwayDiffTest            "ElecRailwayDiffTest"//����ǣ�������MacroID
#define STT_MACRO_ID_ElecRailwayDiffRateTest        "ElecRailwayDiffRateTest"
#define STT_MACRO_ID_ElecRailwayDiffQuickTest       "ElecRailwayDiffQCurrTest"
#define STT_MACRO_ID_ElecRailwayDiffHarmTest        "ElecRailwayDiffHarmTest"
#define STT_MACRO_ID_ElecRailwayDiffTimeTest        "ElecRailwayDiffTimeTest"

#define STT_MACRO_ID_BP2DiffTCurrTest             "BP2DiffTCurrTest" //BP2����MacroID
#define STT_MACRO_ID_BP2DiffRateTest              "BP2DiffRateTest"
#define STT_MACRO_ID_BP2CBOperateTest             "BP2CBOperateTest"

#define STT_MACRO_ID_DcIncrementTest              "DcIncrementTest"

#define STT_MACRO_ID_ReplayTest                   "ReplayTest"
#define STT_MACRO_ID_DigReplayTest                "DigReplayTest"
#define STT_MACRO_ID_Pid01Test              "Pid01Test"
#define STT_MACRO_ID_Pid16Test              "Pid16Test"

#define STT_MACRO_ID_IecDetect              "IecDetect"
#define STT_MACRO_ID_IecRecord              "IecRecord"

#define STT_MACRO_ID_UpdateFPGA              "UpdateFPGA"
#define STT_MACRO_ID_LcPowerTest			 "LcPowerTest"

#define STT_MACRO_ID_DCOverLoadTest     "DCOverLoadTest"  //cl������(ֱ��)
#define STT_MACRO_ID_OverLoadTest       "OverLoadTest"  //������(����)
#define STT_MACRO_ID_DCVoltageTest      "DCVoltageTest"//��ѹ����(ֱ��)
#define STT_MACRO_ID_OverVoltageTest    "OverVoltageTest"//��ѹ����(����)
#define STT_MACRO_ID_DCOverCurrentTest  "DCOverCurrentTest"//��������(ֱ��)

#define STT_MACRO_ID_DCBreakTest              "DCBreakTest"//���ر�������(ֱ��)

#define STT_MACRO_ID_DCFailureProtTest               "DCFailTest"    //ʧ�鱣������(ֱ��) //lichunqing 2023-11-16
#define STT_MACRO_ID_FailureProtActValue             "DCFailActValueTest"      //ʧ�鱣��������/1�ζ���ֵ
#define STT_MACRO_ID_FailureProtActTime              "DCFailActTimeTest"       //ʧ�鱣��������/1�ζ���ʱ��
#define STT_MACRO_ID_FailureProtDidtActValue         "DCFailDidtActValueTest"  //ʧ�鱣��������/2�ζ���ֵ
#define STT_MACRO_ID_FailureProtDidtActTime          "DCFailDidtActTimeTest"   //ʧ�鱣��������/2�ζ���ʱ��

#define STT_MACRO_ID_DCUnbalanceTest  "DCUnbalanceTest"//��ƽ�Ᵽ��(ֱ��)
#define STT_MACRO_ID_DCDifferCurrTest       "DCDifferCurrTest"     //�ݲ��(��������)
#define STT_MACRO_ID_DCDifferRateTest       "DCDifferRateTest"     //�ݲ��(�����ƶ�ϵ��)
#define STT_MACRO_ID_DCDifferTimeTest       "DCDifferTimeTest"     //�ݲ��(����ʱ��)

#define STT_MACRO_ID_ShortTimeOverTest		"ShortTimeOverTest"    //2023/11/30 wangjunsheng ��Ӷ�ʱ��������ģ��
#define STT_MACRO_ID_VolTimeTypeSecTest  "VolTimeTypeSecTest"    //20240112 xueyangfan ��ѹʱ���ͷֶ�ģʽ

#define STT_MACRO_ID_AnsyncStateTest  "AnsyncStateTest"			//�첽״̬����
#define STT_MACRO_ID_AnsyncManualTest	"AnsyncManualTest"		//�첽ͨ������


typedef struct tmt_step_UI
{
public:
    void init()
    {
        for(int i = 0; i < 6; i++)
        {
            fU[i][0] = fU[i][1] = fU[i][2] =  fI[i][0] = fI[i][1] = fI[i][2] = 0;
        }
    }

    tmt_step_UI()
    {
        init();
    }

    float fU[6][3];	//12*(��ֵ+��λ+fre)
    float fI[6][3];
} tmt_StepUI;

typedef struct tmt_binary_in
{
public:
    int		nSelect;
    int		nTrigMode;	//0-��ת���� 1-�����ش��� 2-�½��ش���

public:
    void init()
    {
        nSelect = 1;
        nTrigMode = 0;
#ifdef _PSX_QT_LINUX_
        nSelect = 0;
#endif
    }

    tmt_binary_in()
    {
        init();
    }
} tmt_BinaryIn;

typedef struct tmt_binary_out
{
public:
    int		nState;		//0-�Ͽ� 1-�պ� >1-��ƽ
    //zhouhj 20210616 ���� 2-ͬ��һ��״̬,���ھ���ȸ߼����鿪����ת����
    int		nMode;		//��ת������ʽ 0-ʱ�䴥�� 1-���������� 2-ͬ��һ��״̬
    float	fTimeTrig;	//��תʱ�䣬0Ϊ����ת
    float	fHoldTime;	//��ת����ʱ��

public:
    void init()
    {
        nState = 0;
        nMode = STT_BOUT_REVERSAL_TRIG_MODE_NOT;
        fTimeTrig = 0;
        fHoldTime = 0;
    }

    tmt_binary_out()
    {
        init();
    }
} tmt_BinaryOut;

typedef struct tmt_binary_config
{
    int				m_nBinLogic;			//0-�� 1-��
    tmt_BinaryIn    m_binIn[MAX_BINARYIN_COUNT];//���忪����
    tmt_BinaryOut	m_binOut[MAX_BINARYOUT_COUNT];//���忪����
    tmt_BinaryIn    m_binInEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������
    tmt_BinaryOut	m_binOutEx[MAX_ExBINARY_COUNT];//ϵͳ��չ������

    tmt_BinaryOut	m_binFaultOut[MAX_BINARYOUT_COUNT];//�������̬����
    tmt_BinaryOut	m_binFaultOutEx[MAX_ExBINARY_COUNT];//�������̬��չ����

    void init()
    {
        for(int j = 0; j < MAX_BINARYOUT_COUNT; j++)
        {
            m_binOut[j].nState = 0;
            m_binOut[j].nMode = 0;
            m_binOut[j].fTimeTrig = 0;
            m_binOut[j].fHoldTime = 0;
            m_binFaultOut[j].nState = 0;
            m_binFaultOut[j].nMode = 0;
            m_binFaultOut[j].fTimeTrig = 0;
            m_binFaultOut[j].fHoldTime = 0;
            m_binIn[j].nSelect = 0;
#ifndef _PSX_QT_LINUX_

            if(j < g_nBinCount)
            {
                m_binIn[j].nSelect = 1;
            }

#endif
            m_binIn[j].nTrigMode = 0;
        }

        for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_binInEx[j].nSelect = 0;//Ĭ���������벻ѡ��
            m_binInEx[j].nTrigMode = 0;
        }

        for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
        {
            m_binOutEx[j].nState = 0;//Ĭ����������ȫ�Ͽ�
            m_binOutEx[j].nMode = 0;
            m_binOutEx[j].fTimeTrig = 0;
            m_binOutEx[j].fHoldTime = 0;
            m_binFaultOutEx[j].nState = 0;//Ĭ����������ȫ�Ͽ�
            m_binFaultOutEx[j].nMode = 0;
            m_binFaultOutEx[j].fTimeTrig = 0;
            m_binFaultOutEx[j].fHoldTime = 0;
        }

        m_nBinLogic = 0;
    }

    tmt_binary_config()
    {
        init();
    }
} tmt_BinaryConfig;

typedef struct tmt_channel_harm
{
public:
    BOOL	m_bSelect;//�Ƿ�ʹ��  2024-03-25 wuxinyi ��λ��ʹ�õ��ñ�����bool�޷����ݹʴ��޸�
    int		nSelectIndex;//-1-��Ч 1-30����30��г������(zhouhj 2023.7.11 ��λ���ô˱�ǵ�ǰ��г���Ƿ��޸�,�ڸ��²���ʱ,ֻ�����޸ĵ�ͨ��)
    int		nIndex;
    float	fContent;//������
    float	fAmp;
    float	fAngle;
    float	fFreq;
    bool	bDC;

public:
    void init()
    {
        m_bSelect = FALSE;
        nIndex = 0;
        fContent = 0;
        fAmp = fAngle = fFreq = 0;
        bDC = FALSE;
        nSelectIndex = -1;
    }

    tmt_channel_harm()
    {
        init();
    }
} tmt_ChannelHarm;

typedef struct tmt_channel_ramp
{
public:
    int		nIndex;	//�ݱ�г����� -1-�޵ݱ� 0-�ݱ�ֱ�� 1-�ݱ���� 2~n-�ݱ�2~n��г��
    //	int		nType;	//�ݱ����ͣ�0-��ֵ 1-��λ 2-Ƶ��
    //	int		nMode;	//�ݱ�ģʽ��0-���ݵݱ�	1-����
    //	float	fBegin;
    float	fEnd;
    float	fStep;
    float	fStepTime;
	BOOL    bSecondChan;//˫�����ݱ�ͨ��

public:
    void init()
    {
        /*fBegin = */fEnd = fStep = fStepTime = 0;
        //		nMode = nType = 0;
        nIndex = -1;
		bSecondChan = FALSE;
    }

    tmt_channel_ramp()
    {
        init();
    }
} tmt_ChannelRamp;

typedef struct tmt_channel
{
public:
    tmt_ChannelHarm Harm[MAX_HARM_COUNT];
    tmt_ChannelHarm InterHarm;//��г��
    tmt_ChannelRamp Ramp[3];//zhouhj 20210724 �ֱ��Ӧ0-��ֵ��1-��λ��2-Ƶ�ʵĵݱ�

public:
    void init()
    {
        for(int j = 0; j < MAX_HARM_COUNT; j++)
        {
            Harm[j].init();
        }

        InterHarm.init();

        for(int nIndex = 0; nIndex < 3; nIndex++)
        {
            Ramp[nIndex].init();
        }
    }

    void setSel(bool bSel)
    {
        for(int i = 2; i < MAX_HARM_COUNT; i++)
        {
            Harm[i].m_bSelect = bSel;
        }
    }

    void setDC(bool bDC)
    {
        for(int j = 0; j < MAX_HARM_COUNT; j++)
        {
            Harm[j].bDC = bDC;

            if(bDC)
            {
                Harm[j].fAngle = 0;
                Harm[j].fFreq = 0;
            }
        }
    }

    void init(bool bSel, float fAmp, float fAngle, float fFreq = 0)
    {
        Harm[0].fAmp = 0;
        Harm[1].m_bSelect = true;
        Harm[1].nIndex = 1;
        Harm[1].fAngle = fAngle;
        Harm[1].fAmp = fAmp;
        Harm[1].fContent = 100;

        if(fFreq >= 1)
        {
            Harm[1].fFreq = fFreq;
        }

        for(int i = 2; i < MAX_HARM_COUNT; i++)
        {
            Harm[i].m_bSelect = bSel;
            Harm[i].nIndex = i;
            Harm[i].fAngle = fAngle;
            Harm[i].fAmp = 0;
            Harm[i].fContent = 0;

            if(fFreq >= 1)
            {
                Harm[i].fFreq = i * fFreq;
            }
        }
    }

    void setContent(int nHarmIndex, float fVal)
    {
        if((fVal >= 0) && (fVal <= 100))
        {
            Harm[nHarmIndex].fContent = fVal;
            Harm[nHarmIndex].fAmp = (float)(Harm[1].fAmp * 0.01 * fVal);
        }
    }

    void setAmp(int nHarmIndex, float fVal, BOOL bHasAna)
    {
        float fBaseAmp = Harm[1].fAmp;

        if((fBaseAmp > EPSINON)/* && (fVal <= fBaseAmp)*/)
        {
            if(bHasAna && fVal > fBaseAmp)
            {
                return;
            }

            if(fVal > EPSINON)
            {
                Harm[nHarmIndex].fAmp = fVal;
            }
            else
            {
                Harm[nHarmIndex].fAmp = 0;
            }

            //����Ӧ�������ƹ����ֵ��������fVal sf 20220221
            Harm[nHarmIndex].fContent = Harm[nHarmIndex].fAmp/*fVal*/ * 100 / fBaseAmp;
        }
    }

    float getTotalVal()
    {
        float fTotal = 0;

        for(int i = 0; i < MAX_HARM_COUNT; i++)
        {
            if(Harm[i].m_bSelect)
            {
                fTotal += Harm[i].fAmp;
            }
        }

        return fTotal;
    }

    float getCurHarmAmp(int nHarmIndex)
    {
        float fVal = 0;

        if(Harm[nHarmIndex].m_bSelect)
        {
            fVal = Harm[nHarmIndex].fAmp;
        }

        return fVal;
    }

    tmt_channel()
    {
        init();
    }
} tmt_Channel;

typedef struct tmt_time
{
public:
    int		nYear;
    int		nMonth;
    int		nDay;
    int		nHour;
    int		nMinutes;
    int		nSeconds;
    int		nMilliSeconds;

public:
    void init()
    {
        nYear = 0;
        nMonth = 0;
        nDay = 0;
        nHour = 0;
        nMinutes = 0;
        nSeconds = 0;
        nMilliSeconds = 0;
    }

    tmt_time()
    {
        init();
    }
} tmt_Time;

typedef struct
{
public:
    BOOL    m_bUChange[6][3];//mag   ph   fre
    BOOL    m_bIChange[6][3];
    tmt_StepUI m_uiStepData[GRADIENT_MAX_COUNT];	//�ݱ�����
    int     m_nDiretionMode;//0-m_uiStepData[0]Ϊʼֵ  1-m_uiStepData[m_nStepCount-1]Ϊʼֵ
    int     m_nStepCount;
} tmt_GradientProcess;

typedef struct tmt_gradient_common
{
public:
    tmt_GradientProcess m_oGradientProcess;
public:
    tmt_gradient_common()
    {
        m_oGradientProcess.m_nStepCount = 0;
    }
} tmt_GradientCommon;

typedef struct tmt_system_default_output_paras
{
public:
    BOOL	m_bUseSysOutput;
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];

    void init()
    {
        m_bUseSysOutput = 0;
        float fAngle[3] = {0, -120.0, 120.0};

        for(int j = 0; j < MAX_HARM_COUNT; j++)
        {
            for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
            {
                m_uiVOL[i].Harm[j].fAmp = 0;
                m_uiVOL[i].Harm[1].fAngle = fAngle[i % 3];
                m_uiVOL[i].Harm[j].fFreq = 50;
            }

            for(int i = 0; i < MAX_CURRENT_COUNT; i++)
            {
                m_uiCUR[i].Harm[j].fAmp = 0;
                m_uiCUR[i].Harm[j].fAngle = fAngle[i % 3];
                m_uiCUR[i].Harm[j].fFreq = 50;
            }
        }

        for(int i = 0; i < MAX_BINARYOUT_COUNT; i++)
        {
            m_binOut[i].nState = 0;
        }
    }

    tmt_system_default_output_paras()
    {
        init();
    }
} TMT_SYSTEM_DEFAULT_OUTPUT_PARAS, *PTMT_SYSTEM_DEFAULT_OUTPUT_PARAS;

typedef struct tmt_goose_pub
{
    BOOL m_bUseFlag;//�Ƿ��б�λ
    BOOL m_bHasTest;//�Ƿ��м���λ
    int m_nTest;// �Ƿ��ü���(0���ü���,1�ü���)
    CString m_strChannel[MAX_GOOSE_CHANNEL_COUNT];

    void init()
    {
        m_bUseFlag = FALSE;
        m_bHasTest = FALSE;
        m_nTest = 0;

        for(int nIndex = 0; nIndex < MAX_GOOSE_CHANNEL_COUNT; nIndex++)
        {
            m_strChannel[nIndex] = "";
        }
    }

    void CopyOwn(tmt_goose_pub *pDest)
    {
        pDest->m_bUseFlag = m_bUseFlag;
        pDest->m_bHasTest = m_bHasTest;
        pDest->m_nTest = m_nTest;

        for(int nIndex = 0; nIndex < MAX_GOOSE_CHANNEL_COUNT; nIndex++)
        {
            pDest->m_strChannel[nIndex] = m_strChannel[nIndex];
        }
    }

    tmt_goose_pub()
    {
        init();
    }
} tmt_GoosePub;

typedef struct tmt_goose_pubs
{
    tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
    void init()
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            m_oGoosePub[nIndex].init();
        }
    }

    tmt_goose_pubs()
    {
        init();
    }
} tmt_GoosePubs;

typedef struct tmt_ft3_pub
{
    BOOL m_bUseFlag;//�Ƿ��б�λ
    CString m_strChannel[MAX_FT3_CHANNEL_COUNT];

    void init()
    {
        m_bUseFlag = FALSE;

        for(int nIndex = 0; nIndex < MAX_FT3_CHANNEL_COUNT; nIndex++)
        {
            m_strChannel[nIndex] = "";
        }
    }

    void CopyOwn(tmt_ft3_pub *pDest)
    {
        pDest->m_bUseFlag = m_bUseFlag;

        for(int nIndex = 0; nIndex < MAX_FT3_CHANNEL_COUNT; nIndex++)
        {
            pDest->m_strChannel[nIndex] = m_strChannel[nIndex];
        }
    }

    tmt_ft3_pub()
    {
        init();
    }
} tmt_Ft3Pub;

typedef struct tmt_ft3_pubs
{
    tmt_Ft3Pub m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];
    void init()
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_FT3PUB_COUNT; nIndex++)
        {
            m_oFt3Pub[nIndex].init();
        }
    }

    tmt_ft3_pubs()
    {
        init();
    }
} tmt_Ft3Pubs;

typedef struct tmt_stable2m_pub
{
    BOOL m_bBlockUseFlag;//�Ƿ��б�λ
    BOOL m_bChanUseFlag[MAX_2M_CHANNEL_COUNT];
    long m_nChanValue[MAX_2M_CHANNEL_COUNT];

    void init()
    {
        m_bBlockUseFlag = FALSE;

        for(int nIndex = 0; nIndex < MAX_2M_CHANNEL_COUNT; nIndex++)
        {
            m_bChanUseFlag[nIndex] = FALSE;
            m_nChanValue[nIndex] = 0;
        }
    }

    void CopyOwn(tmt_stable2m_pub *pDest)
    {
        pDest->m_bBlockUseFlag = m_bBlockUseFlag;

        for(int nIndex = 0; nIndex < MAX_2M_CHANNEL_COUNT; nIndex++)
        {
            pDest->m_nChanValue[nIndex] = m_nChanValue[nIndex];
        }
    }

    tmt_stable2m_pub()
    {
        init();
    }
} tmt_Stable2MPub;

typedef struct tmt_2m_OnePort_pub
{
    tmt_Stable2MPub m_oStable2M_DataPub[MAX_2M_DATAIDX_VALUE];
    tmt_Stable2MPub m_oStable2M_CmdPub[MAX_2M_CMDIDX_COUNT];
    void init()
    {
        for(int nIndex = 0; nIndex < MAX_2M_DATAIDX_VALUE; nIndex++)
        {
            m_oStable2M_DataPub[nIndex].init();
        }

        for(int nIndex = 0; nIndex < MAX_2M_CMDIDX_COUNT; nIndex++)
        {
            m_oStable2M_CmdPub[nIndex].init();
        }
    }

    tmt_2m_OnePort_pub()
    {
        init();
    }
} tmt_2MOnePortPub;

/**************�첽ģ��**************/
typedef struct tmt_async_channel
{
public:
	tmt_ChannelHarm			m_oHarm;	//������ѡ�񡢷�ֵ����λ��Ƶ��
	tmt_ChannelRamp			m_oRamp;	//
	float m_fChACMax;					//ͨ���������ֵ
	float m_fChDCMax;					//ͨ��ֱ�����ֵ

	void init()
	{
		m_oHarm.init();
		m_oRamp.init();
		m_fChACMax = m_fChDCMax = 0;
	}

	tmt_async_channel()
	{
		init();
	}

	void CopyOwn(tmt_async_channel &pChannel)
	{
		m_oHarm.m_bSelect = pChannel.m_oHarm.m_bSelect;
		m_oHarm.fAmp = pChannel.m_oHarm.fAmp;
		m_oHarm.fAngle = pChannel.m_oHarm.fAngle;
		m_oHarm.fFreq = pChannel.m_oHarm.fFreq;

		m_fChACMax = pChannel.m_fChACMax;
		m_fChDCMax = pChannel.m_fChDCMax;

	}

}tmt_AsyncChannel;

typedef struct tmt_async_module
{
public:
	long 					m_nModulePos;			//ģ����� 
	long  					m_nCurrChCount;			//����ͨ������
	long  					m_nVolChCount;			//��ѹͨ������
	tmt_AsyncChannel 		* m_pCurrChannel;			//ͨ����Ϣ����
	tmt_AsyncChannel 		* m_pVolChannel;			//ͨ����Ϣ����

	void init()
	{
		m_nModulePos = 0;
		m_nCurrChCount = 0;
		m_nVolChCount = 0;
		m_pCurrChannel = NULL;
		m_pVolChannel = NULL;
	}

	void initChannel(long nCurrChNumbers, long nVolChNumbers)
	{
		if(m_nCurrChCount != nCurrChNumbers)
		{
			if(m_pCurrChannel != NULL)
			{
				delete []m_pCurrChannel;
				m_pCurrChannel = NULL;
			}
		}

		if(m_nVolChCount != nVolChNumbers)
		{
			if(m_pVolChannel != NULL)
			{
				delete []m_pVolChannel;
				m_pVolChannel = NULL;
			}
		}

		if (m_pCurrChannel == NULL && nCurrChNumbers > 0)
		{
			m_pCurrChannel = new tmt_AsyncChannel[nCurrChNumbers];
		}
		if(m_pVolChannel == NULL && nVolChNumbers > 0)
		{
			m_pVolChannel = new tmt_AsyncChannel[nVolChNumbers];
		}

		m_nCurrChCount = nCurrChNumbers;
		m_nVolChCount = nVolChNumbers;
	}

	tmt_async_module()
	{
		init();
	}

	void CopyOwn(tmt_async_module &pSrcModule)
	{
		m_nModulePos = pSrcModule.m_nModulePos;
		m_nCurrChCount = pSrcModule.m_nCurrChCount;
		m_nVolChCount = pSrcModule.m_nVolChCount;

		initChannel(m_nCurrChCount,m_nVolChCount);

		for(int i = 0;i<m_nCurrChCount;i++)
		{
			m_pCurrChannel[i].CopyOwn(pSrcModule.m_pCurrChannel[i]);
		}
		for(int i = 0;i<m_nVolChCount;i++)
		{
			m_pVolChannel[i].CopyOwn(pSrcModule.m_pVolChannel[i]);
		}

	}

}tmt_AsyncModule;

typedef struct tmt_async_modules
{
	long 	m_nAnalogCount;		//ģ������ģ������
	long 	m_nWeekCount;		//���ź���ģ������

	tmt_AsyncModule  m_oAnalogModules[MAX_MODULE_COUNT];		//ģ����ģ��
	tmt_AsyncModule  m_oWeekModules[MAX_MODULE_COUNT];		//���ź�ģ��
	tmt_AsyncModule  m_oDigitalModules;						//������ģ��
	int m_nDc[ASYNC_MODULE_TYPE_COUNT];		//��Ӧֱ����ѡ״̬

	void init()
	{
		m_nAnalogCount = 0;
		m_nWeekCount = 0;
		m_oDigitalModules.init();

		for(int nIndex = 0; nIndex < ASYNC_MODULE_TYPE_COUNT ; nIndex++)
		{
			m_nDc[nIndex] = 0;
		}
		
		for(int nIndex = 0; nIndex < MAX_MODULE_COUNT ; nIndex++)
		{
			m_oAnalogModules[nIndex].init(); // ��ʼ������Ԫ��
			m_oWeekModules[nIndex].init(); // ��ʼ������Ԫ��
		}
	}


	tmt_async_modules()
	{
		init();
	}

	void CopyOwn(tmt_async_modules &pSrcModule)
	{
		m_nAnalogCount = pSrcModule.m_nAnalogCount;
		m_nWeekCount= pSrcModule.m_nWeekCount;

		for(int i = 0; i < ASYNC_MODULE_TYPE_COUNT; i++)
		{
			m_nDc[i] = pSrcModule.m_nDc[i];
		}

		for(int i = 0;i<m_nAnalogCount;i++)
		{
			m_oAnalogModules[i].CopyOwn(pSrcModule.m_oAnalogModules[i]);
		}
		for(int i = 0;i<m_nWeekCount;i++)
		{
			m_oWeekModules[i].CopyOwn(pSrcModule.m_oWeekModules[i]);

		}
		m_oDigitalModules.CopyOwn(pSrcModule.m_oDigitalModules);


	}

}tmt_AsyncModules;

/**************���ϻط�**************/

/**************LtReplay**************/
#define COMTRADE_REPLAY_PKG_POINTS					600
#define LT_REPLAY_FRAME_PKG_CNT						3600 //600*6
//������� ѭ�� A B �����С
#define LT_REPLAY_MAX_LOOP_PKG_CNT                  12
#define LT_REPLAY_MAX_A_PKG_CNT                     120
#define LT_REPLAY_MAX_B_PKG_CNT                     LT_REPLAY_MAX_A_PKG_CNT

typedef struct
{
    unsigned int 	module;
    unsigned int	title;
    unsigned int	length;
    unsigned int	cmd;
    long			data[LT_REPLAY_FRAME_PKG_CNT];
} Drv_BlockPkg;

typedef struct
{
    Drv_BlockPkg bufferLoop[LT_REPLAY_MAX_LOOP_PKG_CNT];
    Drv_BlockPkg bufferA[LT_REPLAY_MAX_A_PKG_CNT];
    Drv_BlockPkg bufferB[LT_REPLAY_MAX_B_PKG_CNT];
} Drv_LtReplayBuffer;

/**************ComReplay**************/
typedef struct
{
    unsigned int lenth;
    long dat[2560000];//�ο�COMTRADE_ABBUF_SIZE 10240000/4
} DrvComReplayData;

typedef struct
{
    unsigned int module;
    unsigned int pkglen;
    DrvComReplayData oData;
} Drv_ComReplayBuffer;

typedef struct ReplayCoefItem
{
    float fCoef;//��ֵϵ��
    float fZero;//������Ư
    float fTmtCoef;//С�źű��
    float fMaxValue; // ֱ�����ֵ ��Чֵ*1.414
    int   nCh;
    float fReverse;// +1 -1
	int   nSampleLen;//FT3��������
    ReplayCoefItem()
    {
        fCoef = 1.0;
        fZero = 0;
        fTmtCoef = 1.0;//һ����120:7.07,��С1:1���ж�ʱ������0.5����Ч
        fMaxValue = 100;
        nCh = 0;
        fReverse = 1.0;
		nSampleLen = 2;
    }
} Drv_ReplayCoefItem;

typedef struct ReplayCoefItems
{
    int nChCnt;//�ط�ģ���FPGAͨ���ź�������6��12
    int nCode;//�ֱ��ʣ�16λ��32λ 2^(32-1)-1
    ReplayCoefItem Item[48];//20220511 zhoulei ֧��48·С�źŻط�
} Drv_ReplayCoefItems;

typedef struct ReplayCoef
{
    ReplayCoefItems Items[16];//0-11��Ӧλ��1-12��15��Ӧ����С�źŻ�330
} Drv_ReplayCoef;


//2022-8-25  lijunqing
typedef struct _Replay_HdCh_RcdData_Map_
{
    int   nHdCh;   //Ӳ��ͨ�����

    //��Ӧ��¼�����ݵ�λ��   2022-8-24 lijunqing
    //���ϻط�ʱ:��Ӧ�Ĳ������ݵı�ţ�û�����ã���Ϊ-1
    //ģʽ1:���ͨ��û�����ã�����Ҫ���ز������ݣ�
    //ģʽ2:ͨ��û�����ã���Ȼ����ͨ�����ݣ���ʱ����Ϊ0
    int  nRcdDataIndex;
    double fCoef;

    void init()
    {
        nHdCh = 0;
        nRcdDataIndex = -1;
        fCoef = 1.0f;
    }
} REPLAY_HDCH_RCDDATA_MAP;

typedef struct _Replay_HdCh_RcdData_Maps_
{
    int nModuleIndex;   //ӳ��ģ����
    int nMapCount;  //ӳ��ͨ������
    REPLAY_HDCH_RCDDATA_MAP oHdChRcdDataMaps[48];  //�Ƿ���Ϊ�궨��

    void init()
    {
        nModuleIndex = -1;
        nMapCount = 0;

        for(int k = 0; k < 48; k++)
        {
            oHdChRcdDataMaps[k].init();
        }
    }
} REPLAY_HDCH_RCDDATA_MAPS;

typedef struct _Replay_HdCh_RcdData_Maps_Mngr_
{
    int nModuleCount;
    REPLAY_HDCH_RCDDATA_MAPS oModules [16];  //�Ƿ���Ϊ�궨��

    void init()
    {
        nModuleCount = 0;

        for(int k = 0; k < 16; k++)
        {
            oModules[k].init();
        }
    }
} REPLAY_HDCH_RCDDATA_MAPS_MNGR;

inline int get_xml_serialize_binary_count(CSttXmlSerializeBase *pXmlSierialize)
{
    int nCnt = 0;

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        nCnt = MAX_BINARYIN_COUNT;
    }
    else
    {
        nCnt = g_nBinCount;

        if(nCnt > MAX_BINARYIN_COUNT)
        {
            nCnt = MAX_BINARYIN_COUNT;
        }
        else
        {
            if(nCnt < 8)
            {
                nCnt = 8;//GOOSE����ӳ��D1-D8
            }
        }
    }

    return nCnt;
}

inline int get_xml_serialize_binary_out_count(CSttXmlSerializeBase *pXmlSierialize)
{
    int nCnt = 0;

    if(stt_xml_serialize_is_read(pXmlSierialize))
    {
        nCnt = MAX_BINARYOUT_COUNT;
    }
    else
    {
        nCnt = g_nBoutCount;

        if(nCnt > MAX_BINARYOUT_COUNT)
        {
            nCnt = MAX_BINARYOUT_COUNT;
        }
        else
        {
            if(nCnt < 8)
            {
                nCnt = 8;//GOOSE����ӳ��D1-D8
            }
        }
    }

    return nCnt;
}

inline void stt_xml_serialize_binary_in(tmt_BinaryIn *pbin, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("����Aѡ��", "_BinSelectA", "", "BOOL", pbin[0].nSelect);
    pXmlSierialize->xml_serialize("����Bѡ��", "_BinSelectB", "", "BOOL", pbin[1].nSelect);
    pXmlSierialize->xml_serialize("����Cѡ��", "_BinSelectC", "", "BOOL", pbin[2].nSelect);
    pXmlSierialize->xml_serialize("����Rѡ��", "_BinSelectR", "", "BOOL", pbin[3].nSelect);
    pXmlSierialize->xml_serialize("����aѡ��", "_BinSelecta", "", "BOOL", pbin[4].nSelect);
    pXmlSierialize->xml_serialize("����bѡ��", "_BinSelectb", "", "BOOL", pbin[5].nSelect);
    pXmlSierialize->xml_serialize("����cѡ��", "_BinSelectc", "", "BOOL", pbin[6].nSelect);
    pXmlSierialize->xml_serialize("����rѡ��", "_BinSelectr", "", "BOOL", pbin[7].nSelect);
    pXmlSierialize->xml_serialize("����Iѡ��", "_BinSelectI", "", "BOOL", pbin[8].nSelect);
    pXmlSierialize->xml_serialize("����Jѡ��", "_BinSelectJ", "", "BOOL", pbin[9].nSelect);
    pXmlSierialize->xml_serialize("����Kѡ��", "_BinSelectK", "", "BOOL", pbin[10].nSelect);
    pXmlSierialize->xml_serialize("����Lѡ��", "_BinSelectL", "", "BOOL", pbin[11].nSelect);
    pXmlSierialize->xml_serialize("����Mѡ��", "_BinSelectM", "", "BOOL", pbin[12].nSelect);
    pXmlSierialize->xml_serialize("����Nѡ��", "_BinSelectN", "", "BOOL", pbin[13].nSelect);
    pXmlSierialize->xml_serialize("����Oѡ��", "_BinSelectO", "", "BOOL", pbin[14].nSelect);
    pXmlSierialize->xml_serialize("����Pѡ��", "_BinSelectP", "", "BOOL", pbin[15].nSelect);
}

inline void stt_xml_serialize_Exbinary_in(tmt_BinaryIn *pbinEx, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strName, strID, strTemp;
    CString str1 = _T("��չ����");
    CString str2 = _T("ѡ��");
    CSttXmlSerializeBase *pExBinSerialize = NULL;

    if(stt_xml_serialize_is_write(pXmlSierialize))	//�·�
    {
        if(g_nBinExCount <= 0)
        {
            return;
        }

        pExBinSerialize = pXmlSierialize->xml_serialize("��չ����", "BinEx", "BinEx", stt_ParaGroupKey());

        if(pExBinSerialize == NULL)
        {
            return;
        }

        for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
            strTemp.Format(_T("%d"), nIndex + 1);
            strName = str1 + strTemp + str2;
            strID.Format("BinEx%dSelect", (nIndex + 1));
            pExBinSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "BOOL", pbinEx[nIndex].nSelect);
        }

        return;
    }

    pExBinSerialize = pXmlSierialize->xml_serialize("��չ����", "BinEx", "BinEx", stt_ParaGroupKey());

    if(pExBinSerialize == NULL)
    {
        if(stt_xml_serialize_is_read(pXmlSierialize))
        {
            //20220426 �����ȿ�STT�ӿڵ���
            pExBinSerialize = pXmlSierialize;
        }
        else
        {
            return;
        }
    }

    for(int nIndex = 0; nIndex < g_nBinExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("BinEx%dSelect", (nIndex + 1));
        pExBinSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "BOOL", pbinEx[nIndex].nSelect);
    }
}

inline void stt_xml_serialize_binary_out(tmt_BinaryOut *pbOut, CSttXmlSerializeBase *pXmlSierialize)
{
//    pXmlSierialize->xml_serialize("����1״̬", "_Bout1", "", "DOutputState", pbOut[0].nState);
//    pXmlSierialize->xml_serialize("����2״̬", "_Bout2", "", "DOutputState", pbOut[1].nState);
//    pXmlSierialize->xml_serialize("����3״̬", "_Bout3", "", "DOutputState", pbOut[2].nState);
//    pXmlSierialize->xml_serialize("����4״̬", "_Bout4", "", "DOutputState", pbOut[3].nState);
//    pXmlSierialize->xml_serialize("����5״̬", "_Bout5", "", "DOutputState", pbOut[4].nState);
//    pXmlSierialize->xml_serialize("����6״̬", "_Bout6", "", "DOutputState", pbOut[5].nState);
//    pXmlSierialize->xml_serialize("����7״̬", "_Bout7", "", "DOutputState", pbOut[6].nState);
//    pXmlSierialize->xml_serialize("����8״̬", "_Bout8", "", "DOutputState", pbOut[7].nState);
    CString strName, strID, strTemp;
    CString str1 = _T("����");
    CString str2 = _T("״̬");
    long nBoSize = get_xml_serialize_binary_out_count(pXmlSierialize);

    for(int nIndex = 0; nIndex < nBoSize; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("_Bout%d", nIndex + 1);
        pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOut[nIndex].nState);
    }
}

inline void stt_xml_serialize_Exbinary_out(tmt_BinaryOut *pbOutEx, CSttXmlSerializeBase *pXmlSierialize)
{
    CString strName, strID, strTemp;
    CString str1 = _T("��չ����");
    CString str2 = _T("״̬");
    CSttXmlSerializeBase *pExBoutSerialize = NULL;

    if(stt_xml_serialize_is_write(pXmlSierialize))	//�·�
    {
        if(g_nBoutExCount <= 0)
        {
            return;
        }

        pExBoutSerialize = pXmlSierialize->xml_serialize("��չ����", "BoutEx", "BoutEx", stt_ParaGroupKey());

        if(pExBoutSerialize == NULL)
        {
            return;
        }

        for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
        {
            strTemp.Format(_T("%d"), nIndex + 1);
            strName = str1 + strTemp + str2;
            strID.Format("BoutEx%dState", nIndex + 1);
            pExBoutSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOutEx[nIndex].nState);
        }

        return;
    }

    pExBoutSerialize = pXmlSierialize->xml_serialize("��չ����", "BoutEx", "BoutEx", stt_ParaGroupKey());

    if(pExBoutSerialize == NULL)
    {
        if(stt_xml_serialize_is_read(pXmlSierialize))
        {
            //20220426 �����ȿ�STT�ӿڵ���
            pExBoutSerialize = pXmlSierialize;
        }
        else
        {
            return;
        }
    }

    for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("BoutEx%dState", nIndex + 1);
        pExBoutSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOutEx[nIndex].nState);
    }
}

inline void stt_xml_serialize(tmt_GoosePub *pGoosePub, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pGOOSEPubXml = pXmlSierialize->xml_serialize("", "GOOSEPubs", "GOOSEPubs", stt_ParaGroupKey());

    if(pGOOSEPubXml != NULL)
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_GOOSEPUB_COUNT; nIndex++)
        {
            CSttXmlSerializeBase *pGooseSerialize = pGOOSEPubXml->xml_serialize("GOOSE�������ƿ�", "GOOSEPub", nIndex + 1, "GOOSEPub", stt_ParaGroupKey());

            if(pGooseSerialize)
            {
                pGoosePub[nIndex].m_bUseFlag = TRUE;
                BOOL bRet;
                bRet = pGooseSerialize->xml_serialize("����", "CheckStatus", "", "number", pGoosePub[nIndex].m_nTest);

                if(bRet)
                {
                    pGoosePub[nIndex].m_bHasTest = TRUE;
                }

                CString strVal = _T("GooseChannel");
                CString strChannelID;

                for(int nChanIndex = 0; nChanIndex < MAX_GOOSE_CHANNEL_COUNT; nChanIndex++)
                {
                    strChannelID.Format(_T("%d"), nChanIndex + 1);
                    strChannelID = strVal + strChannelID;
                    pGooseSerialize->xml_serialize("GOOSEͨ��", strChannelID.GetString(), " ", "string", pGoosePub[nIndex].m_strChannel[nChanIndex]);
                }
            }
        }
    }
}

inline void stt_xml_serialize(tmt_Ft3Pub *pFt3Pub, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pFt3PubsXml = pXmlSierialize->xml_serialize("", "FT3Pubs", "FT3Pubs", stt_ParaGroupKey());

    if(pFt3PubsXml != NULL)
    {
        for(int nIndex = 0; nIndex < MAX_MODULES_FT3PUB_COUNT; nIndex++)
        {
            CSttXmlSerializeBase *pFt3PubXml = pFt3PubsXml->xml_serialize("FT3�������ƿ�", "FT3Pub", nIndex + 1, "FT3Pub", stt_ParaGroupKey());

            if(pFt3PubXml)
            {
                pFt3Pub[nIndex].m_bUseFlag = TRUE;
                CString strVal = _T("FT3Channel");
                CString strChannelID;

                for(int nChanIndex = 0; nChanIndex < MAX_FT3_CHANNEL_COUNT; nChanIndex++)
                {
                    strChannelID.Format(_T("%d"), nChanIndex + 1);
                    strChannelID = strVal + strChannelID;
                    pFt3PubXml->xml_serialize("FT3ͨ��", strChannelID.GetString(), " ", "string", pFt3Pub[nIndex].m_strChannel[nChanIndex]);
                }
            }
        }
    }
}

inline void stt_xml_serialize(tmt_2MOnePortPub *p2MOnePortPub, CSttXmlSerializeBase *pXmlSierialize)
{
    CSttXmlSerializeBase *pStable2MSerialize;
    CSttXmlSerializeBase *pStable2MCmd;
    CSttXmlSerializeBase *pStable2MData;
    tmt_Stable2MPub *pStable2MPub;
    CString strVal = _T("Channel");
    CString strChannelID;
    BOOL bRet;

    for(int nIndex = 0; nIndex < MAX_2M_BLOCKS_COUNT; nIndex++)
    {
        pStable2MSerialize = pXmlSierialize->xml_serialize("�ȿ�2M����", "Stable2MPubPort", nIndex + 1, "Stable2MPubPort", stt_ParaGroupKey());

        if(pStable2MSerialize != NULL)
        {
            for(int nCmdIndex = 0; nCmdIndex < MAX_2M_CMDIDX_COUNT; nCmdIndex++)
            {
                p2MOnePortPub[nIndex].m_oStable2M_CmdPub[nCmdIndex].m_bBlockUseFlag = 0;
                pStable2MCmd = pStable2MSerialize->xml_serialize("�����", "CmdIdx", nCmdIndex, "CmdPacket", stt_ParaGroupKey());

                if(pStable2MCmd != NULL)
                {
                    pStable2MPub = &p2MOnePortPub[nIndex].m_oStable2M_CmdPub[nCmdIndex];

                    for(int nChanIndex = 0; nChanIndex < MAX_2M_CHANNEL_COUNT; nChanIndex++)
                    {
                        strChannelID.Format(_T("%d"), nChanIndex + 1);
                        strChannelID = strVal + strChannelID;
                        bRet = pStable2MCmd->xml_serialize("�ȿ�2Mͨ��", strChannelID.GetString(), " ", "long", pStable2MPub->m_nChanValue[nChanIndex]);

                        if(bRet)
                        {
                            pStable2MPub->m_bBlockUseFlag = 1;
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = TRUE;
                        }
                        else
                        {
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = FALSE;
                        }
                    }
                }
            }

            for(int nDataIndex = 0; nDataIndex < MAX_2M_DATAIDX_VALUE; nDataIndex++)
            {
                p2MOnePortPub[nIndex].m_oStable2M_DataPub[nDataIndex].m_bBlockUseFlag = 0;
                pStable2MData = pStable2MSerialize->xml_serialize("���ݱ���", "DataIdx", nDataIndex, "DataPacket", stt_ParaGroupKey());

                if(pStable2MData != NULL)
                {
                    pStable2MPub = &p2MOnePortPub[nIndex].m_oStable2M_DataPub[nDataIndex];

                    for(int nChanIndex = 0; nChanIndex < MAX_2M_CHANNEL_COUNT; nChanIndex++)
                    {
                        strChannelID.Format(_T("%d"), nChanIndex + 1);
                        strChannelID = strVal + strChannelID;
                        bRet = pStable2MData->xml_serialize("�ȿ�2Mͨ��", strChannelID.GetString(), " ", "long", pStable2MPub->m_nChanValue[nChanIndex]);

                        if(bRet)
                        {
                            pStable2MPub->m_bBlockUseFlag = 1;
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = TRUE;
                        }
                        else
                        {
                            pStable2MPub->m_bChanUseFlag[nChanIndex] = FALSE;
                        }
                    }
                }
            }
        }
    }
}

inline void stt_xml_serialize(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pParas, CSttXmlSerializeBase *pXmlSierialize)
{
    pXmlSierialize->xml_serialize("�Ƿ񱣳����", "_bUseSysOutput", "", "BOOL", pParas->m_bUseSysOutput);
    pXmlSierialize->xml_serialize("Ua��ֵ", "Ua", "V", "number", pParas->m_uiVOL[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ua��λ", "UaPh", "��", "number", pParas->m_uiVOL[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("UaƵ��", "UaFre", "Hz", "number", pParas->m_uiVOL[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ub��ֵ", "Ub", "V", "number", pParas->m_uiVOL[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ub��λ", "UbPh", "��", "number", pParas->m_uiVOL[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("UbƵ��", "UbFre", "Hz", "number", pParas->m_uiVOL[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uc��ֵ", "Uc", "V", "number", pParas->m_uiVOL[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uc��λ", "UcPh", "��", "number", pParas->m_uiVOL[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("UcƵ��", "UcFre", "Hz", "number", pParas->m_uiVOL[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Uap��ֵ", "Uap", "V", "number", pParas->m_uiVOL[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Uap��λ", "UapPh", "��", "number", pParas->m_uiVOL[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("UapƵ��", "UapFre", "Hz", "number", pParas->m_uiVOL[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ubp��ֵ", "Ubp", "V", "number", pParas->m_uiVOL[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ubp��λ", "UbpPh", "��", "number", pParas->m_uiVOL[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("UbpƵ��", "UbpFre", "Hz", "number", pParas->m_uiVOL[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ucp��ֵ", "Ucp", "V", "number", pParas->m_uiVOL[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ucp��λ", "UcpPh", "��", "number", pParas->m_uiVOL[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("UcpƵ��", "UcpFre", "Hz", "number", pParas->m_uiVOL[5].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ia��ֵ", "Ia", "A", "number", pParas->m_uiCUR[0].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ia��λ", "IaPh", "��", "number", pParas->m_uiCUR[0].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("IaƵ��", "IaFre", "Hz", "number", pParas->m_uiCUR[0].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ib��ֵ", "Ib", "A", "number", pParas->m_uiCUR[1].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ib��λ", "IbPh", "��", "number", pParas->m_uiCUR[1].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("IbƵ��", "IbFre", "Hz", "number", pParas->m_uiCUR[1].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ic��ֵ", "Ic", "A", "number", pParas->m_uiCUR[2].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ic��λ", "IcPh", "��", "number", pParas->m_uiCUR[2].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("IcƵ��", "IcFre", "Hz", "number", pParas->m_uiCUR[2].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Iap��ֵ", "Iap", "A", "number", pParas->m_uiCUR[3].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Iap��λ", "IapPh", "��", "number", pParas->m_uiCUR[3].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("IapƵ��", "IapFre", "Hz", "number", pParas->m_uiCUR[3].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Ibp��ֵ", "Ibp", "A", "number", pParas->m_uiCUR[4].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Ibp��λ", "IbpPh", "��", "number", pParas->m_uiCUR[4].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("IbpƵ��", "IbpFre", "Hz", "number", pParas->m_uiCUR[4].Harm[1].fFreq);
    pXmlSierialize->xml_serialize("Icp��ֵ", "Icp", "A", "number", pParas->m_uiCUR[5].Harm[1].fAmp);
    pXmlSierialize->xml_serialize("Icp��λ", "IcpPh", "��", "number", pParas->m_uiCUR[5].Harm[1].fAngle);
    pXmlSierialize->xml_serialize("IcpƵ��", "IcpFre", "Hz", "number", pParas->m_uiCUR[5].Harm[1].fFreq);
    stt_xml_serialize_binary_out(pParas->m_binOut, pXmlSierialize);
}

inline void stt_xml_serialize_Gradient_Exbinary_out(tmt_BinaryOut *pbOutEx, CSttXmlSerializeBase *pXmlSierialize, BOOL bIsFault)
{
    CString strName, strID, strTemp;
    CString str1 = _T("��չ����");
    CString str2 = _T("״̬");
    CString str3;

    if(bIsFault)
    {
        str3 = _T("����̬");
        strID = _T("Fault");
    }
    else
    {
        str3 = _T("��̬");
        strID = _T("PreFault");
    }

    strName = str3 + str1;
    strID += _T("BoutEx");
    CSttXmlSerializeBase *pExBoutSerialize = pXmlSierialize->xml_serialize(strName.GetString(), strID.GetString(), "BoutEx", stt_ParaGroupKey());

    if(pExBoutSerialize == NULL)
    {
        return;
    }

    for(int nIndex = 0; nIndex < g_nBoutExCount && nIndex < MAX_ExBINARY_COUNT; nIndex++)
    {
        strTemp.Format(_T("%d"), nIndex + 1);
        strName = str1 + strTemp + str2;
        strID.Format("BoutEx%dState", nIndex + 1);
        pExBoutSerialize->xml_serialize(strName.GetString(), strID.GetString(), "", "DOutputState", pbOutEx[nIndex].nState);
    }
}

inline void stt_xml_serialize_Channel(tmt_async_channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize)
{
	CSttXmlSerializeBase *pChannelXmlSerializeBase =pXmlSierialize->xml_serialize(pszID, pszID, "channel", stt_ParaGroupKey());
	if (pChannelXmlSerializeBase == NULL)
	{
		return;
	}

#ifdef NOT_USE_XLANGUAGE
	pChannelXmlSerializeBase->xml_serialize("ѡ��", "bSelect", "", "BOOL", pChannel->m_oHarm.m_bSelect);
	pChannelXmlSerializeBase->xml_serialize("��ֵ", "mag", "", "float", pChannel->m_oHarm.fAmp);
	pChannelXmlSerializeBase->xml_serialize("��λ", "ang", "", "float", pChannel->m_oHarm.fAngle);
	pChannelXmlSerializeBase->xml_serialize("Ƶ��", "freq", "", "float", pChannel->m_oHarm.fFreq);

	pChannelXmlSerializeBase->xml_serialize( "ͨ���������ֵ", "ChACMax", "", "float", pChannel->m_fChACMax);
	pChannelXmlSerializeBase->xml_serialize( "ͨ��ֱ�����ֵ" , "ChDCMax", "", "float", pChannel->m_fChDCMax);
#else
	pChannelXmlSerializeBase->xml_serialize("ѡ��", "bSelect", "", "BOOL", pChannel->m_oHarm.m_bSelect);
	pChannelXmlSerializeBase->xml_serialize(/* "��ֵ" */ g_sLangTxt_Native_Amplitude.GetString(), "mag", "", "float", pChannel->m_oHarm.fAmp);
	pChannelXmlSerializeBase->xml_serialize(/* "��λ" */ g_sLangTxt_Native_Phase.GetString(), "ang", "", "float", pChannel->m_oHarm.fAngle);
	pChannelXmlSerializeBase->xml_serialize(/* "Ƶ��" */ g_sLangTxt_Native_Freq.GetString(), "freq", "", "float", pChannel->m_oHarm.fFreq);

	pChannelXmlSerializeBase->xml_serialize( "ͨ���������ֵ", "ChACMax", "", "float", pChannel->m_fChACMax);
	pChannelXmlSerializeBase->xml_serialize( "ͨ��ֱ�����ֵ" , "ChDCMax", "", "float", pChannel->m_fChDCMax);
#endif
}

inline void stt_xml_serialize_Analog(tmt_async_module *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];

	sprintf(chName, "ģ����ģ��%d", nIndex+1);
	sprintf(chID, "AnalogModule%d", nIndex+1);

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("ģ�����","ModulePos","","number",pModule->m_nModulePos);
	pSerialize->xml_serialize("����ͨ������","CurrChCount","","number",pModule->m_nCurrChCount);
	pSerialize->xml_serialize("��ѹͨ������","VolChCount","","number",pModule->m_nVolChCount);
	CString strID;

	if(pModule->m_nCurrChCount != 0)
	{
		CSttXmlSerializeBase *pCurrSerialize =pSerialize->xml_serialize("����ͨ����Ϣ", "CurrChannel", "CurrChannel", stt_ParaGroupKey());
		if(pCurrSerialize)
		{

			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}

			for(int nIndex = 0; nIndex < pModule->m_nCurrChCount; nIndex++)
			{
				strID.Format(_T("I%d"),nIndex+1);
				if(!pModule->m_pCurrChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pCurrSerialize) && !pModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pCurrChannel[nIndex], strID.GetString(), pCurrSerialize);
			}
		}
	}

	if(pModule->m_nVolChCount != 0)
	{
		CSttXmlSerializeBase *pVolSerialize =pSerialize->xml_serialize("��ѹͨ����Ϣ", "VolChannel", "VolChannel", stt_ParaGroupKey());
		if(pVolSerialize)
		{
			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}
			for(int nIndex = 0; nIndex < pModule->m_nVolChCount; nIndex++)
			{
				strID.Format(_T("U%d"),nIndex+1);
				if(!pModule->m_pVolChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pVolSerialize) && !pModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pVolChannel[nIndex], strID.GetString(), pVolSerialize);
			}
		}
	}
}

inline void stt_xml_serialize_Week(tmt_async_module *pModule, int nIndex, CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];

	sprintf(chName, "���ź�ģ��%d", nIndex+1);
	sprintf(chID, "WeekModule%d", nIndex+1);

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("ģ�����","ModulePos","","number",pModule->m_nModulePos);
	pSerialize->xml_serialize("����ͨ������","CurrChCount","","number",pModule->m_nCurrChCount);
	pSerialize->xml_serialize("��ѹͨ������","VolChCount","","number",pModule->m_nVolChCount);
	CString strID;

	if(pModule->m_nCurrChCount != 0)
	{
		CSttXmlSerializeBase *pCurrSerialize =pSerialize->xml_serialize("����ͨ����Ϣ", "CurrChannel", "CurrChannel", stt_ParaGroupKey());
		if(pCurrSerialize)
		{

			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}

			for(int nIndex = 0; nIndex < pModule->m_nCurrChCount; nIndex++)
			{
				strID.Format(_T("I%d"),nIndex+1);
				if(!pModule->m_pCurrChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pCurrSerialize) && !pModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pCurrChannel[nIndex], strID.GetString(), pCurrSerialize);
			}
		}
	}

	if(pModule->m_nVolChCount != 0)
	{
		CSttXmlSerializeBase *pVolSerialize =pSerialize->xml_serialize("��ѹͨ����Ϣ", "VolChannel", "VolChannel", stt_ParaGroupKey());
		if(pVolSerialize)
		{
			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}
			for(int nIndex = 0; nIndex < pModule->m_nVolChCount; nIndex++)
			{
				strID.Format(_T("U%d"),nIndex+1);
				if(!pModule->m_pVolChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pVolSerialize) && !pModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pVolChannel[nIndex], strID.GetString(), pVolSerialize);
			}
		}
	}
}

inline void stt_xml_serialize_Digital(tmt_async_module *pModule, CSttXmlSerializeBase *pXmlSierialize)
{
	char chName[MAX_PATH],chID[MAX_PATH];

	sprintf(chName, "������ģ��");
	sprintf(chID, "DigitalModule");

	CSttXmlSerializeBase *pSerialize =pXmlSierialize->xml_serialize(chName, chID, "Module", stt_ParaGroupKey());
	if (pSerialize == NULL)
	{
		return;
	}
	pSerialize->xml_serialize("ģ�����","ModulePos","","number",pModule->m_nModulePos);
	pSerialize->xml_serialize("����ͨ������","CurrChCount","","number",pModule->m_nCurrChCount);
	pSerialize->xml_serialize("��ѹͨ������","VolChCount","","number",pModule->m_nVolChCount);
	CString strID;

	if(pModule->m_nCurrChCount != 0)
	{
		CSttXmlSerializeBase *pCurrSerialize =pSerialize->xml_serialize("����ͨ����Ϣ", "CurrChannel", "CurrChannel", stt_ParaGroupKey());

		if(pCurrSerialize)
		{

			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}

			for(int nIndex = 0; nIndex < pModule->m_nCurrChCount; nIndex++)
			{
				strID.Format(_T("I%d"),nIndex+1);
				if(!pModule->m_pCurrChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pCurrSerialize) && !pModule->m_pCurrChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pCurrChannel[nIndex], strID.GetString(), pCurrSerialize);
			}
		}
	}

	if(pModule->m_nVolChCount != 0)
	{
		CSttXmlSerializeBase *pVolSerialize =pSerialize->xml_serialize("��ѹͨ����Ϣ", "VolChannel", "VolChannel", stt_ParaGroupKey());
		if(pVolSerialize)
		{
			if(stt_xml_serialize_is_read(pXmlSierialize))
			{
				pModule->initChannel(pModule->m_nCurrChCount,pModule->m_nVolChCount);
			}
			for(int nIndex = 0; nIndex < pModule->m_nVolChCount; nIndex++)
			{
				strID.Format(_T("U%d"),nIndex+1);
				if(!pModule->m_pVolChannel)
				{
					return;
				}
				if (stt_xml_serialize_is_write(pVolSerialize) && !pModule->m_pVolChannel[nIndex].m_oHarm.m_bSelect)
				{
					continue;
				}
				stt_xml_serialize_Channel(&pModule->m_pVolChannel[nIndex], strID.GetString(), pVolSerialize);			
			}
		}
	}
}

inline bool Global_CheckBinSelect(tmt_BinaryIn *pBinIn, int nMaxBinNum, bool bLogicAnd) //zhouhj 20220421 ��鿪������ѡ״̬,��֤���ٹ�ѡһ������
{
	if(bLogicAnd)
	{
		int nCount = 0;
		for(int nIndex = 0; nIndex < nMaxBinNum; nIndex++)
		{
			if(pBinIn[nIndex].nSelect)
			{
				nCount++;
				if(nCount == 2)
				{
					return true;
				}
			}
		}

		if(nCount == 1 && pBinIn[0].nSelect == 0)
		{
			pBinIn[0].nSelect = 1;
			return false;
		}
		else if(nCount == 1 && pBinIn[0].nSelect == 1)
		{
			pBinIn[1].nSelect = 1;
			return false;
		}
	}

	for(int nIndex = 0; nIndex < nMaxBinNum; nIndex++)
	{
		if(pBinIn[nIndex].nSelect)
		{
			return true;
		}
	}

	pBinIn[0].nSelect = 1;
	return false;
}

static short Leap_year[2][12] =
{
    { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
    { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};

inline void TransTimer_t(unsigned int ntime_t,
                         short &nYear, short &nMon, short &nDay, short &nHour, short &nMin, short &nSec)
{
    nYear = 1970;
    nMon = 1;
    nDay = 1;
    nHour = nMin = nSec = 0;

    while(TRUE)
    {
        int nIsLeap = 0;

        if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
        {
            nIsLeap = 1;
        }

        int nDiff = nIsLeap ? 366 : 365;

        if(ntime_t >= nDiff * 24 * 60 * 60)
        {
            nYear += 1;
            ntime_t -= nDiff * 24 * 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        int nIsLeap = 0;

        if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
        {
            nIsLeap = 1;
        }

        int nLastDay = Leap_year[nIsLeap][nMon - 1];

        if(ntime_t >= nLastDay * 24 * 60 * 60)
        {
            nMon += 1;
            ntime_t -= nLastDay * 24 * 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        if(ntime_t >= 24 * 60 * 60)
        {
            nDay += 1;
            ntime_t -= 24 * 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        if(ntime_t >= 60 * 60)
        {
            nHour += 1;
            ntime_t -= 60 * 60;
        }
        else
        {
            break;
        }
    }

    while(TRUE)
    {
        if(ntime_t >= 60)
        {
            nMin += 1;
            ntime_t -= 60;
        }
        else
        {
            break;
        }
    }

    nSec = ntime_t;
}

inline void TransTimer_To_t(unsigned int &ntime_t,
                            short nYear, short nMon, short nDay, short nHour, short nMin, short nSec)
{
    ntime_t = 0;
    int nYearRef = 1970;

    while(TRUE)
    {
        int nDiffYear = nYear - nYearRef;

        if(nDiffYear == 0)
        {
            break;
        }

        int nIsLeap = 0;

        if((nYearRef % 4 == 0 && nYearRef % 100 != 0) || nYearRef % 400 == 0)
        {
            nIsLeap = 1;
        }

        int nDays = nIsLeap ? 366 : 365;
        ntime_t += nDays * 24 * 60 * 60;
        nYearRef++;
    }

    int nIsLeap = 0;

    if((nYear % 4 == 0 && nYear % 100 != 0) || nYear % 400 == 0)
    {
        nIsLeap = 1;
    }

    int nMonRef = 1;

    while(TRUE)
    {
        int nDiffMon = nMon - nMonRef;

        if(nDiffMon == 0)
        {
            break;
        }

        int nLastDay = Leap_year[nIsLeap][nMonRef - 1];
        ntime_t += nLastDay * 24 * 60 * 60;
        nMonRef++;
    }

    ntime_t += (nDay - 1) * 24 * 60 * 60;
    ntime_t += nHour * 60 * 60;
    ntime_t += nMin * 60;
    ntime_t += nSec;
}
