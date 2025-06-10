#pragma once

#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_adjust_sys_parameter.h"

//CurrentModulePower
#define STT_CurrentMODULE_POWER_LOW     0  //�͹���
#define STT_CurrentMODULE_POWER_MIDDLE  1  //�й���
#define STT_CurrentMODULE_POWER_HIGH    2  //�߹���
#define STT_CurrentMODULE_POWER_OTHER   3  //��������(�Զ���)
#define STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A   4  //��������(�Զ���)

#define STT_FiberType_0G8M  0xff //0ǧ�� 8����
#define STT_FiberType_2G6M  0xfc //2ǧ�� 6����
#define STT_FiberType_4G4M  0xf0 //4ǧ�� 4����

#define MAX_DIGITAL_GROUP_NUM     6
#define MAX_WEEK_GROUP_NUM        8
#define MAX_FT3_FiberPort_NUM     12
#define MAX_SV_FiberPort_NUM      8

#define STT_IEC_FORMAT_61850_92          0
#define STT_IEC_FORMAT_60044_8           1
#define STT_IEC_FORMAT_60044_8DC         2 //��ֱFT3

#define STT_LARGE_CURRENT_MERGE_NOT_SUPPORT      -1    //��֧�ֺϲ����
#define STT_LARGE_CURRENT_MERGE_NOT_MERGE         0    //���ϲ����
#define STT_LARGE_CURRENT_MERGE_ONE_CH            1    //�ϲ�Ϊ1��ͨ�����
#define STT_LARGE_CURRENT_MERGE_THREE_CH          3    //�ϲ�Ϊ3��ͨ�����


#define STT_LARGE_CUR_OUT_NULL           0   //������������������ѡ��
#define STT_LARGE_CUR_OUT_TERM_A         1   //�������A��������
#define STT_LARGE_CUR_OUT_TERM_B         2   //�������B��������
#define STT_LARGE_CUR_OUT_TERM_C         3   //�������C��������

// typedef struct
// {
// 	int   m_nIPowerMode;//��������ģʽ(Ĭ�����е���ģ�����ͳһ�Ĺ���ģʽ)
// 	float   m_nChMax;//�û�������ͨ�����ֵ(A)
// 	float m_fVoltSet;//�û����ö˿ڵ�ѹ(V)
//
// 	void init()
// 	{
// 		m_nIPowerMode=STT_CurrentMODULE_POWER_LOW;
// 		m_nChMax=0;
// 		m_fVoltSet=0;//�Զ��幦������±���
// 	}
// }tmt_CurrentPower;

typedef struct
{
    long m_nIPowerMode;//��λ
    float m_fVoltSet;//�˿ڵ�ѹ
    long m_nMergeCurTerminal;//�ϲ���������
    long m_nLargeCurOutTerm;//������������
    long m_nModulePos;//ģ��λ��
    long m_nModuleType;//ģ������,zhouhj 20210901  ��Ϊ�����˵�ѹ������������ģ��,�����Ӵ˲���

    void init()
    {
        m_nIPowerMode = STT_CurrentMODULE_POWER_LOW;
        m_fVoltSet = 0; //�Զ��幦������±���
        m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;
        m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
        m_nModulePos = -1;
        m_nModuleType = STT_MODULE_TYPE_CURRENT;
    }

} tmt_CurModuleGear;

typedef struct tmt_gear_set_cur_modules
{
    long m_nCurModuleNum;//����ģ������
    tmt_CurModuleGear m_oCurModuleGear[ADJUST_MAX_MODULE_COUNT];//����ģ�鵵λ����

public:
    void init()
    {
        m_nCurModuleNum = 0;

        for(int nIndex = 0; nIndex < ADJUST_MAX_MODULE_COUNT; nIndex++)
        {
            m_oCurModuleGear[nIndex].init();
        }
    }

    void CopyOwn(tmt_gear_set_cur_modules *pDes)
    {
        pDes->m_nCurModuleNum = m_nCurModuleNum;

        for(int nIndex = 0; nIndex < ADJUST_MAX_MODULE_COUNT; nIndex++)
        {
            pDes->m_oCurModuleGear[nIndex].m_nIPowerMode = m_oCurModuleGear[nIndex].m_nIPowerMode;
            pDes->m_oCurModuleGear[nIndex].m_fVoltSet = m_oCurModuleGear[nIndex].m_fVoltSet;
            pDes->m_oCurModuleGear[nIndex].m_nMergeCurTerminal = m_oCurModuleGear[nIndex].m_nMergeCurTerminal;
            pDes->m_oCurModuleGear[nIndex].m_nLargeCurOutTerm = m_oCurModuleGear[nIndex].m_nLargeCurOutTerm;
        }
    }

    BOOL MergeCurrHasChanged(tmt_gear_set_cur_modules *pDes)//�жϵ�ǰ�ϲ���������Ƿ�ı�,����ı���,��Ҫ���½���ͨ��ӳ��
    {
        for(int nIndex = 0; nIndex < ADJUST_MAX_MODULE_COUNT; nIndex++)
        {
            if(pDes->m_oCurModuleGear[nIndex].m_nMergeCurTerminal != m_oCurModuleGear[nIndex].m_nMergeCurTerminal)
            {
                return TRUE;
            }
        }

        return FALSE;
    }
} tmt_GearSetCurModules;

typedef struct
{
    long m_b4G;
    long m_bBle;//�͹����豸Ĭ���ϵ�����
    long m_bNetWifi;
    long m_bNetRj45;//Ĭ���ϵ�����100M����
    long m_nLcdTimes;//0-��ʱ�䣬N-N����
	long m_nLcdLight;//��Ļ����,1-5

    void init()
    {
        m_b4G = 0;
        m_bBle = 1;
        m_bNetWifi = 0;
        m_bNetRj45 = 1;
        m_nLcdTimes = 0;
		m_nLcdLight = 5;
    }

} tmt_Peripheral;

typedef struct tmt_system_paras		// PSU ״̬�ڵݱ����
{
    float	m_fVNom;			//��ߵ�ѹ����100V
    float	m_fINom;            //���������1A
	float	m_fFNom;           //Ƶ��
	float   m_fU0_Std;      //�����ѹ�ֵ(�������ź�ʹ��) zhouhj 2023.7.28
	float   m_fI0_Std;     //��������ֵ(�������ź�ʹ��) zhouhj 2023.7.28
    float 	m_fStabTime;		//����ʱ��
    float  m_fOverLoadDelay;    //��ʼ������ʱ(s)

    float m_fCurValue_AbsError;//��������ֵ�������
    float m_fCurValue_RelError;//��������ֵ������
    float m_fVolValue_AbsError;//��ѹ����ֵ�������
    float m_fVolValue_RelError;//��ѹ����ֵ������
    float m_fImpValue_AbsError;//�迹����ֵ�������
    float m_fImpValue_RelError;//�迹����ֵ������
    float m_fAngValue_AbsError;//��λֵ�������
//	float m_fAngValue_RelError;//��λֵ������
    float m_fFreValue_AbsError;//Ƶ��ֵ�������
//	float m_fFreValue_RelError;//Ƶ��ֵ������
    float m_fTimeValue_AbsError;//����ʱ��ֵ�������
    float m_fTimeValue_RelError;//����ʱ��ֵ������
    float m_fdvdtValue_AbsError;//��ѹ����ֵ�������
//	float m_fdvdtValue_RelError;//��ѹ����ֵ������
    float m_fdfdtValue_AbsError;//Ƶ�ʻ���ֵ�������
//	float m_fdfdtValue_RelError;//Ƶ�ʻ���ֵ������
    float m_fDiffRateCoef_AbsError;//������ƶ�ϵ���������
    float m_fDiffRateCoef_RelError;//������ƶ�ϵ��������
    float m_fDiffHarmCoef_AbsError;//�г���ƶ�ϵ���������
    float m_fDiffHarmCoef_RelError;//�г���ƶ�ϵ��������


    float   m_fAuxDC_Vol;//����ֱ����ѹֵ
    float   m_fAuxDC_Cur;//����ֱ������ֵ
    float	m_fVPrimary[MAX_DIGITAL_GROUP_NUM];		//PT���
    float	m_fVSecondary[MAX_DIGITAL_GROUP_NUM];
    float	m_fIPrimary[MAX_DIGITAL_GROUP_NUM];		//CT���
    float	m_fISecondary[MAX_DIGITAL_GROUP_NUM];

// 	float	m_fVPrimary_Weak[MAX_WEEK_GROUP_NUM];		//���ź�PT���
// 	float	m_fVSecondary_Weak[MAX_WEEK_GROUP_NUM];
// 	float	m_fIPrimary_Weak[MAX_WEEK_GROUP_NUM];		//CT���
// 	float	m_fISecondary_Weak[MAX_WEEK_GROUP_NUM];

	float	m_fVRate[MAX_DIGITAL_GROUP_NUM];//��ѹ��������
	float	m_fIRate[MAX_DIGITAL_GROUP_NUM];//������������

    int	m_nIecFormat;		//���������ʽ   0-IEC61850-9-2��1-IEC60044-8(FT3)  ������9-1���
    int	m_n588Syn;			//IEC61588ͬ������ 0-��ʱ����-��Ӧ 1-�Ե���ʱ
    int	m_nParaMode;		//��������ѡ�� 0-һ��ֵ 1-����ֵ
    int	m_nPkgOutMode;		//�������ѡ�� 0-һ��ֵ 1-����ֵ
    int	m_nBCodeMode;		//B���߼� 0-���߼� 1-���߼�
    int	m_nLoopMode;			//�������ӷ�ʽ 0-˫�� 1-����

    tmt_GearSetCurModules m_oGearSetCurModules;//���е���ģ��ĵ�λ����
    tmt_Peripheral m_oPeripheral;//4G ���� Һ������ʱ�� wifi 100M��̫��

    long m_nHasAnalog;//��Ҫģ�����
    long m_nHasDigital;//��Ҫ�������
    long m_nHasWeek;//��ҪС�ź����
    BOOL m_bSyncSecond;//��ͬ��
    BOOL m_bKeepSendIecPkt;//�������ֱ��ķ���
    int m_nFiberType;//��ڴ�������
    BOOL m_bCheckHeartOverTime;//�����Ƿ�����Կͻ�������

    int m_nUseAnalogMeas;//ʹ��ģ�����ɼ�//20220806 zhouhj �������ڲɼ�
    int m_nUseDigitalMeas;//ʹ���������ɼ�
    int m_nUseWeekMeas;//ʹ��С�źŲɼ�
    int	m_nIecFormatMeas;		//���Ľ��ո�ʽ   0-IEC61850-9-2��1-IEC60044-8(FT3)  ������9-1���
    int	m_nBCodeModeMeas;		//�ɼ�B���߼� 0-���߼� 1-���߼�

    int m_nRprtUseBinExCnt;
    int m_nTimeZone;//�ײ��ϱ����ݵ�ʱ�����ã�Ĭ��+8��
    BOOL m_bGtoB_UseUserTz;//GPSתB��ʱʹ���û�����ʱ��
    int m_nWindSpeed;//1-�������� 0-��������
	int m_nBinBoutMode;//���ڸ߼�ʵ��ʱ��0-Ĭ�����忪��1��8����1��8��1-ͬʱӳ�䵽��չ����1��8����1��8

    void init()
    {
		m_nBinBoutMode = 0;
        m_nWindSpeed = 0;
#ifndef _STT_NOT_IN_TEST_SERVER_
		if(g_theDeviceSystemParameter != NULL)
		{
			m_nWindSpeed = g_theDeviceSystemParameter->m_oDeviceAttrs.m_nWindSpeed;
		}
#endif
        m_bGtoB_UseUserTz = FALSE;
        m_nTimeZone = 8;
        m_nRprtUseBinExCnt = 0;//�Զ�������������չģ��
        m_bCheckHeartOverTime = TRUE;
        m_nFiberType = STT_FiberType_0G8M;
        m_bKeepSendIecPkt = FALSE;
        m_bSyncSecond = TRUE;
        m_nHasAnalog = 1;
        m_nHasDigital = 0;
        m_nHasWeek = 0;
        m_fVNom = 100.0f;
        m_fINom = 1;
		m_fU0_Std = 2.166f;
		m_fI0_Std = 0.2f;
        m_fFNom = 50.0f;
        m_fStabTime = 0;
        m_fOverLoadDelay = 0.0f;        
        m_nIecFormat = STT_IEC_FORMAT_61850_92;
        m_n588Syn = 0;
        m_nParaMode = 1;//zhouhj 20210626  ��������ѡ�� 0-һ��ֵ 1-����ֵ,ȱʡ���ö���ֵ
        m_nPkgOutMode = 0;
        m_nBCodeMode = 0;
        m_nLoopMode = 0;
        m_fAuxDC_Vol = 0;
        m_fAuxDC_Cur = 0;
        m_nUseAnalogMeas = 0;
        m_nUseDigitalMeas = 1;
        m_nUseWeekMeas = 0;
        m_nIecFormatMeas = STT_IEC_FORMAT_61850_92;
        m_nBCodeModeMeas = 0;
        m_fCurValue_AbsError = 0.02f;
        m_fCurValue_RelError = 0.05f;
        m_fVolValue_AbsError = 0.2f;
        m_fVolValue_RelError = 0.05f;
        m_fImpValue_AbsError = 0.02f;
        m_fImpValue_RelError = 0.05f;
        m_fAngValue_AbsError = 3.0f;
        m_fAngValue_AbsError = 0.001f;
        m_fTimeValue_AbsError = 0.04f;
        m_fTimeValue_RelError = 0.01f;
        m_fdvdtValue_AbsError = 0.1f;
        m_fdfdtValue_AbsError = 0.1f;
        m_fDiffHarmCoef_AbsError = 0.1f;
        m_fDiffRateCoef_AbsError = 0.1f;
        m_fDiffHarmCoef_RelError = 0.05f;
        m_fDiffRateCoef_RelError = 0.05f;

        for(int nIndex = 0; nIndex < MAX_DIGITAL_GROUP_NUM; nIndex++)
        {
            m_fVPrimary[nIndex] = 110.0f;
            m_fVSecondary[nIndex] = 100.0f;
            m_fIPrimary[nIndex] = 1000.0f;
            m_fISecondary[nIndex] = 1.0f;

			m_fVRate[nIndex] = 0.01f;
			m_fIRate[nIndex] = 0.001f;
        }

        m_oGearSetCurModules.init();
        m_oPeripheral.init();
// 		for(int nIndex = 0;nIndex<MAX_WEEK_GROUP_NUM;nIndex++)
// 		{
// 			m_fVPrimary_Weak[nIndex] = 120.0f;
// 			m_fVSecondary_Weak[nIndex] = 7.07f;
// 			m_fIPrimary_Weak[nIndex] = 30.0f;
// 			m_fISecondary_Weak[nIndex] = 7.07f;
// 		}
    }

    BOOL IsDigitalOutput(long nIecFormat)//�ж��Ƿ�Ϊ��ǰ���õ��������������
    {
        if(!m_nHasDigital)
        {
            return FALSE;
        }

        return (m_nIecFormat == nIecFormat);
    }

    BOOL IsDigitalOutputFT3()//�ж��Ƿ�Ϊ��ǰ���õ��������������
    {
        if(!m_nHasDigital)
        {
            return FALSE;
        }

        if(m_nIecFormat == STT_IEC_FORMAT_60044_8)
        {
            return TRUE;
        }

        if(m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
        {
            return TRUE;
        }

        return FALSE;
    }

    BOOL OutputTypeHasChanged(tmt_system_paras *pDes)
    {
        if(pDes->m_nHasAnalog != m_nHasAnalog)
        {
            return TRUE;
        }

        if(pDes->m_nHasDigital != m_nHasDigital)
        {
            return TRUE;
        }

        if(pDes->m_nHasWeek != m_nHasWeek)
        {
            return TRUE;
        }

        if(pDes->m_nIecFormat != m_nIecFormat)
        {
            return TRUE;
        }

        return FALSE;
    }

	BOOL GlobalParamSetHasChanged(tmt_system_paras *pDes)
	{
		if (pDes->m_fVNom != m_fVNom)
		{
			return TRUE;
		}

		if (pDes->m_fINom != m_fINom)
		{
			return TRUE;
		}

		if (pDes->m_fFNom != m_fFNom)
		{
			return TRUE;
		}

		if (pDes->m_fStabTime != m_fStabTime)
		{
			return TRUE;
		}

		return FALSE;
	}

    BOOL HasDigitalInOrOut()//֧�����������ɼ�
    {
        if(m_nHasDigital)
        {
            return TRUE;
        }

        if(m_nUseDigitalMeas)
        {
            return TRUE;
        }

        return FALSE;
    }

    void CopyOwn(tmt_system_paras *pDes)
    {
		pDes->m_nWindSpeed = m_nWindSpeed;
        pDes->m_nFiberType = m_nFiberType;
        pDes->m_bKeepSendIecPkt = m_bKeepSendIecPkt;
        pDes->m_bSyncSecond = m_bSyncSecond;
        pDes->m_nHasAnalog = m_nHasAnalog;
        pDes->m_nHasDigital = m_nHasDigital;
        pDes->m_nHasWeek = m_nHasWeek;
        pDes->m_fVNom = m_fVNom;
        pDes->m_fINom = m_fINom;
        pDes->m_fFNom = m_fFNom;
		pDes->m_fU0_Std = m_fU0_Std;
		pDes->m_fI0_Std = m_fI0_Std;
        pDes->m_fStabTime = m_fStabTime;
        pDes->m_fOverLoadDelay = m_fOverLoadDelay;
        pDes->m_fAuxDC_Cur = m_fAuxDC_Cur;
        pDes->m_fAuxDC_Vol = m_fAuxDC_Vol;
        pDes->m_nIecFormat = m_nIecFormat;
        pDes->m_n588Syn = m_n588Syn;
        pDes->m_nParaMode = m_nParaMode;
        pDes->m_nPkgOutMode = m_nPkgOutMode;
        pDes->m_nBCodeMode = m_nBCodeMode;
        pDes->m_nLoopMode = m_nLoopMode;
        pDes->m_nUseAnalogMeas = m_nUseAnalogMeas;
        pDes->m_nUseDigitalMeas = m_nUseDigitalMeas;
        pDes->m_nUseWeekMeas = m_nUseWeekMeas;
        pDes->m_nIecFormatMeas = m_nIecFormatMeas;
        pDes->m_nBCodeModeMeas = m_nBCodeModeMeas;
        pDes->m_fCurValue_AbsError = m_fCurValue_AbsError;
        pDes->m_fCurValue_RelError = m_fCurValue_RelError;
        pDes->m_fVolValue_AbsError = m_fVolValue_AbsError;
        pDes->m_fVolValue_RelError = m_fVolValue_RelError;
        pDes->m_fImpValue_AbsError = m_fImpValue_AbsError;
        pDes->m_fImpValue_RelError = m_fImpValue_RelError;
        pDes->m_fAngValue_AbsError = m_fAngValue_AbsError;
//		pDes->m_fAngValue_RelError = m_fAngValue_RelError;
        pDes->m_fFreValue_AbsError = m_fFreValue_AbsError;
//		pDes->m_fFreValue_RelError = m_fFreValue_RelError;
        pDes->m_fTimeValue_AbsError = m_fTimeValue_AbsError;
        pDes->m_fTimeValue_RelError = m_fTimeValue_RelError;
        pDes->m_fdvdtValue_AbsError = m_fdvdtValue_AbsError;
//		pDes->m_fdvdtValue_RelError = m_fdvdtValue_RelError;
        pDes->m_fdfdtValue_AbsError = m_fdfdtValue_AbsError;
//		pDes->m_fdfdtValue_RelError = m_fdfdtValue_RelError;
        pDes->m_fDiffHarmCoef_AbsError = m_fDiffHarmCoef_AbsError;
        pDes->m_fDiffHarmCoef_RelError = m_fDiffHarmCoef_RelError;
        pDes->m_fDiffRateCoef_AbsError = m_fDiffRateCoef_AbsError;
        pDes->m_fDiffRateCoef_RelError = m_fDiffRateCoef_RelError;
        m_oGearSetCurModules.CopyOwn(&pDes->m_oGearSetCurModules);

        for(int nIndex = 0; nIndex < MAX_DIGITAL_GROUP_NUM; nIndex++)
        {
            pDes->m_fVPrimary[nIndex] = m_fVPrimary[nIndex];
            pDes->m_fVSecondary[nIndex] = m_fVSecondary[nIndex];
            pDes->m_fIPrimary[nIndex] = m_fIPrimary[nIndex];
            pDes->m_fISecondary[nIndex] = m_fISecondary[nIndex];
        }

// 		for(int nIndex = 0;nIndex<MAX_WEEK_GROUP_NUM;nIndex++)
// 		{
// 			pDes->m_fVPrimary_Weak[nIndex] = m_fVPrimary_Weak[nIndex];
// 			pDes->m_fVSecondary_Weak[nIndex] = m_fVSecondary_Weak[nIndex];
// 			pDes->m_fIPrimary_Weak[nIndex] = m_fIPrimary_Weak[nIndex];
// 			pDes->m_fISecondary_Weak[nIndex] = m_fISecondary_Weak[nIndex];
// 		}
    }

    tmt_system_paras()
    {
        init();
    }

    float PkgModePTRate(int nGroup)
    {
        float fPTRate = 1;

        if(m_nParaMode && (!m_nPkgOutMode)) //��������Ϊ����ֵ���������Ϊһ��ֵ
        {
            fPTRate = 1000 * m_fVPrimary[nGroup] / m_fVSecondary[nGroup];
        }
        else if((!m_nParaMode) && m_nPkgOutMode) //��������Ϊһ��ֵ���������Ϊ����ֵ
        {
            fPTRate = m_fVSecondary[nGroup] / (1000 * m_fVPrimary[nGroup]);
        }

        return fPTRate;
    }

    float PkgModeCTRate(int nGroup)
    {
        float fCTRate = 1;

        if(m_nParaMode && (!m_nPkgOutMode)) //��������Ϊ����ֵ���������Ϊһ��ֵ
        {
            fCTRate = m_fIPrimary[nGroup] / m_fISecondary[nGroup];
        }
        else if((!m_nParaMode) && m_nPkgOutMode) //��������Ϊһ��ֵ���������Ϊ����ֵ
        {
            fCTRate = m_fISecondary[nGroup] / m_fIPrimary[nGroup];
        }

        return fCTRate;
    }
} STT_SystemParas, *PTT_SystemParas;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_SystemConfig();
void stt_xml_serialize(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_AuxDC(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //zhouhj 20211016 �������ڸ���ֱ������
void stt_xml_serialize_AppConfig(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //zhouhj 20221207 �����������ñ��

void stt_xml_serialize_ModulesGearSwitch(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //�������ڵ�λ�л�
void stt_xml_serialize_SystemParas(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //��������ϵͳ��������
void stt_xml_serialize_ModulesGearSwitch(tmt_GearSetCurModules *pGearSetCurModules, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PeripheralCtrl(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //�������������л�
void stt_xml_serialize_Peripheral(tmt_Peripheral *pPeripheral, CSttXmlSerializeBase *pXmlSierialize, BOOL bUseChildGroup = TRUE); //20220625 zhouhj ����3Ϊ�Ƿ����ָ�����ӽڵ�Group

void stt_xml_serialize_ErrorValues(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize);
