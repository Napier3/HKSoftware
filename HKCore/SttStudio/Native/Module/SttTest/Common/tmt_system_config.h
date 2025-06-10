#pragma once

#include"../../SttTestBase/SttXmlSerialize.h"
#include "tmt_adjust_sys_parameter.h"

//CurrentModulePower
#define STT_CurrentMODULE_POWER_LOW     0  //低功率
#define STT_CurrentMODULE_POWER_MIDDLE  1  //中功率
#define STT_CurrentMODULE_POWER_HIGH    2  //高功率
#define STT_CurrentMODULE_POWER_OTHER   3  //其他功率(自定义)
#define STT_CurrentMODULE_POWER_PNS330_6x10A_3x20A   4  //其他功率(自定义)

#define STT_FiberType_0G8M  0xff //0千兆 8百兆
#define STT_FiberType_2G6M  0xfc //2千兆 6百兆
#define STT_FiberType_4G4M  0xf0 //4千兆 4百兆

#define MAX_DIGITAL_GROUP_NUM     6
#define MAX_WEEK_GROUP_NUM        8
#define MAX_FT3_FiberPort_NUM     12
#define MAX_SV_FiberPort_NUM      8

#define STT_IEC_FORMAT_61850_92          0
#define STT_IEC_FORMAT_60044_8           1
#define STT_IEC_FORMAT_60044_8DC         2 //柔直FT3

#define STT_LARGE_CURRENT_MERGE_NOT_SUPPORT      -1    //不支持合并输出
#define STT_LARGE_CURRENT_MERGE_NOT_MERGE         0    //不合并输出
#define STT_LARGE_CURRENT_MERGE_ONE_CH            1    //合并为1个通道输出
#define STT_LARGE_CURRENT_MERGE_THREE_CH          3    //合并为3个通道输出


#define STT_LARGE_CUR_OUT_NULL           0   //不包含大电流输出端子选择
#define STT_LARGE_CUR_OUT_TERM_A         1   //大电流从A相端子输出
#define STT_LARGE_CUR_OUT_TERM_B         2   //大电流从B相端子输出
#define STT_LARGE_CUR_OUT_TERM_C         3   //大电流从C相端子输出

// typedef struct
// {
// 	int   m_nIPowerMode;//电流功率模式(默认所有电流模块采用统一的功率模式)
// 	float   m_nChMax;//用户加量的通道最大值(A)
// 	float m_fVoltSet;//用户设置端口电压(V)
//
// 	void init()
// 	{
// 		m_nIPowerMode=STT_CurrentMODULE_POWER_LOW;
// 		m_nChMax=0;
// 		m_fVoltSet=0;//自定义功率情况下必填
// 	}
// }tmt_CurrentPower;

typedef struct
{
    long m_nIPowerMode;//档位
    float m_fVoltSet;//端口电压
    long m_nMergeCurTerminal;//合并电流端子
    long m_nLargeCurOutTerm;//大电流输出端子
    long m_nModulePos;//模块位置
    long m_nModuleType;//模块类型,zhouhj 20210901  因为增加了电压电流混合输出的模块,故增加此参数

    void init()
    {
        m_nIPowerMode = STT_CurrentMODULE_POWER_LOW;
        m_fVoltSet = 0; //自定义功率情况下必填
        m_nMergeCurTerminal = STT_LARGE_CURRENT_MERGE_NOT_SUPPORT;
        m_nLargeCurOutTerm = STT_LARGE_CUR_OUT_NULL;
        m_nModulePos = -1;
        m_nModuleType = STT_MODULE_TYPE_CURRENT;
    }

} tmt_CurModuleGear;

typedef struct tmt_gear_set_cur_modules
{
    long m_nCurModuleNum;//电流模块数量
    tmt_CurModuleGear m_oCurModuleGear[ADJUST_MAX_MODULE_COUNT];//电流模块档位设置

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

    BOOL MergeCurrHasChanged(tmt_gear_set_cur_modules *pDes)//判断当前合并电流输出是否改变,如果改变了,需要重新进行通道映射
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
    long m_bBle;//低功耗设备默认上电启动
    long m_bNetWifi;
    long m_bNetRj45;//默认上电启动100M网口
    long m_nLcdTimes;//0-长时间，N-N分钟
	long m_nLcdLight;//屏幕亮度,1-5

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

typedef struct tmt_system_paras		// PSU 状态内递变参数
{
    float	m_fVNom;			//额定线电压正常100V
    float	m_fINom;            //额定电流正常1A
	float	m_fFNom;           //频率
	float   m_fU0_Std;      //零序电压额定值(配网弱信号使用) zhouhj 2023.7.28
	float   m_fI0_Std;     //零序电流额定值(配网弱信号使用) zhouhj 2023.7.28
    float 	m_fStabTime;		//防抖时间
    float  m_fOverLoadDelay;    //开始过载延时(s)

    float m_fCurValue_AbsError;//电流动作值绝对误差
    float m_fCurValue_RelError;//电流动作值相对误差
    float m_fVolValue_AbsError;//电压动作值绝对误差
    float m_fVolValue_RelError;//电压动作值相对误差
    float m_fImpValue_AbsError;//阻抗动作值绝对误差
    float m_fImpValue_RelError;//阻抗动作值相对误差
    float m_fAngValue_AbsError;//相位值绝对误差
//	float m_fAngValue_RelError;//相位值相对误差
    float m_fFreValue_AbsError;//频率值绝对误差
//	float m_fFreValue_RelError;//频率值相对误差
    float m_fTimeValue_AbsError;//动作时间值绝对误差
    float m_fTimeValue_RelError;//动作时间值相对误差
    float m_fdvdtValue_AbsError;//电压滑差值绝对误差
//	float m_fdvdtValue_RelError;//电压滑差值相对误差
    float m_fdfdtValue_AbsError;//频率滑差值绝对误差
//	float m_fdfdtValue_RelError;//频率滑差值相对误差
    float m_fDiffRateCoef_AbsError;//差动比率制动系数绝对误差
    float m_fDiffRateCoef_RelError;//差动比率制动系数相对误差
    float m_fDiffHarmCoef_AbsError;//差动谐波制动系数绝对误差
    float m_fDiffHarmCoef_RelError;//差动谐波制动系数相对误差


    float   m_fAuxDC_Vol;//辅助直流电压值
    float   m_fAuxDC_Cur;//辅助直流电流值
    float	m_fVPrimary[MAX_DIGITAL_GROUP_NUM];		//PT变比
    float	m_fVSecondary[MAX_DIGITAL_GROUP_NUM];
    float	m_fIPrimary[MAX_DIGITAL_GROUP_NUM];		//CT变比
    float	m_fISecondary[MAX_DIGITAL_GROUP_NUM];

// 	float	m_fVPrimary_Weak[MAX_WEEK_GROUP_NUM];		//弱信号PT变比
// 	float	m_fVSecondary_Weak[MAX_WEEK_GROUP_NUM];
// 	float	m_fIPrimary_Weak[MAX_WEEK_GROUP_NUM];		//CT变比
// 	float	m_fISecondary_Weak[MAX_WEEK_GROUP_NUM];

	float	m_fVRate[MAX_DIGITAL_GROUP_NUM];//电压比例因子
	float	m_fIRate[MAX_DIGITAL_GROUP_NUM];//电流比例因子

    int	m_nIecFormat;		//报文输出格式   0-IEC61850-9-2，1-IEC60044-8(FT3)  不考虑9-1情况
    int	m_n588Syn;			//IEC61588同步机制 0-延时请求-响应 1-对等延时
    int	m_nParaMode;		//参数设置选择 0-一次值 1-二次值
    int	m_nPkgOutMode;		//报文输出选择 0-一次值 1-二次值
    int	m_nBCodeMode;		//B码逻辑 0-正逻辑 1-负逻辑
    int	m_nLoopMode;			//光纤连接方式 0-双回 1-单回

    tmt_GearSetCurModules m_oGearSetCurModules;//所有电流模块的档位设置
    tmt_Peripheral m_oPeripheral;//4G 蓝牙 液晶背光时长 wifi 100M以太网

    long m_nHasAnalog;//需要模拟输出
    long m_nHasDigital;//需要数字输出
    long m_nHasWeek;//需要小信号输出
    BOOL m_bSyncSecond;//秒同步
    BOOL m_bKeepSendIecPkt;//保持数字报文发送
    int m_nFiberType;//光口带宽配置
    BOOL m_bCheckHeartOverTime;//配置是否检测测试客户端心跳

    int m_nUseAnalogMeas;//使用模拟量采集//20220806 zhouhj 增加用于采集
    int m_nUseDigitalMeas;//使用数字量采集
    int m_nUseWeekMeas;//使用小信号采集
    int	m_nIecFormatMeas;		//报文接收格式   0-IEC61850-9-2，1-IEC60044-8(FT3)  不考虑9-1情况
    int	m_nBCodeModeMeas;		//采集B码逻辑 0-正逻辑 1-负逻辑

    int m_nRprtUseBinExCnt;
    int m_nTimeZone;//底层上报数据的时区设置，默认+8区
    BOOL m_bGtoB_UseUserTz;//GPS转B码时使用用户设置时区
    int m_nWindSpeed;//1-正常风速 0-静音风速
	int m_nBinBoutMode;//用于高级实验时，0-默认主板开入1～8开出1～8，1-同时映射到扩展开入1～8开出1～8

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
        m_nRprtUseBinExCnt = 0;//自动关联开关量扩展模块
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
        m_nParaMode = 1;//zhouhj 20210626  参数设置选择 0-一次值 1-二次值,缺省采用二次值
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

    BOOL IsDigitalOutput(long nIecFormat)//判断是否为当前设置的数字量输出类型
    {
        if(!m_nHasDigital)
        {
            return FALSE;
        }

        return (m_nIecFormat == nIecFormat);
    }

    BOOL IsDigitalOutputFT3()//判断是否为当前设置的数字量输出类型
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

    BOOL HasDigitalInOrOut()//支持数字输出或采集
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

        if(m_nParaMode && (!m_nPkgOutMode)) //参数设置为二次值，报文输出为一次值
        {
            fPTRate = 1000 * m_fVPrimary[nGroup] / m_fVSecondary[nGroup];
        }
        else if((!m_nParaMode) && m_nPkgOutMode) //参数设置为一次值，报文输出为二次值
        {
            fPTRate = m_fVSecondary[nGroup] / (1000 * m_fVPrimary[nGroup]);
        }

        return fPTRate;
    }

    float PkgModeCTRate(int nGroup)
    {
        float fCTRate = 1;

        if(m_nParaMode && (!m_nPkgOutMode)) //参数设置为二次值，报文输出为一次值
        {
            fCTRate = m_fIPrimary[nGroup] / m_fISecondary[nGroup];
        }
        else if((!m_nParaMode) && m_nPkgOutMode) //参数设置为一次值，报文输出为二次值
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
void stt_xml_serialize_AuxDC(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //zhouhj 20211016 单独用于辅助直流设置
void stt_xml_serialize_AppConfig(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //zhouhj 20221207 增加用于设置变比

void stt_xml_serialize_ModulesGearSwitch(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //单独用于档位切换
void stt_xml_serialize_SystemParas(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //单独用于系统参数设置
void stt_xml_serialize_ModulesGearSwitch(tmt_GearSetCurModules *pGearSetCurModules, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PeripheralCtrl(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize); //单独用于外设切换
void stt_xml_serialize_Peripheral(tmt_Peripheral *pPeripheral, CSttXmlSerializeBase *pXmlSierialize, BOOL bUseChildGroup = TRUE); //20220625 zhouhj 参数3为是否查找指定的子节点Group

void stt_xml_serialize_ErrorValues(PTT_SystemParas pSystemParas, CSttXmlSerializeBase *pXmlSierialize);
