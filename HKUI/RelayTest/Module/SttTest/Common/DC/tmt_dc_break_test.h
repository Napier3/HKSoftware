#pragma once

#include "../Impedance/tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_DCBREAK_SETTING_NUM       2

typedef struct tmt_dc_break_paras
{
public:
	double m_fISetting;           //整定动作电流
	int m_nFaultChannel;        //故障通道(电流通道)
	float m_fRate;              //倍数
	float m_fTSetting;      //整定动作时间
	float m_fPreFaultTime;		//故障前时间
	float m_fMarginTime;        //故障时间裕度
	float m_fPostFaultTime;		//保护动作后持续时间  2.000f
	int   m_nFaultTrigMode;		//故障触发方式 S1=时间,S2=按键,S3=开入量“H”触发,S4=GPS 0(0:时间触发,1:按键触发,2:开入接点翻转触发,3:GPS触发)
	tmt_time m_tGps;
	BOOL  m_bCBSimulation;		//断路器模拟  S1=不模拟,S2=模拟 0(0:不模拟,1:模拟)
	float m_fCBTripTime;		//分闸时间	200ms（模拟断路器时的分闸时间）
	float m_fCBCloseTime;		//合闸时间	100ms（模拟断路器时的合闸时间）

	float   m_fSettingBreak[TMT_DCBREAK_SETTING_NUM];//开关保护动作值
	float   m_fSettingTime[TMT_DCBREAK_SETTING_NUM];//开关保护动作时间
	tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn m_binInEx[MAX_ExBINARY_COUNT];
    long m_nStateBOut[MAX_BINARYOUT_COUNT];//用二进制标识各个开出状态
	long m_nOutputSwitchMode;//翻转触发方式 0-时间触发 1-开入量触发
	float	m_fBoutTimeTrig;	//反转时间，0为不翻转
	float	m_fBoutHoldTime;	//翻转保持时间

	int m_nBinLogic; //0 1逻辑与或
	double m_fR, m_fX;  //用于绘图，传入横纵坐标

public:
	virtual void init()
	{
		m_fISetting = 2.85f;
		m_nFaultChannel = 0;
		m_fRate = 1.0f;
		m_fTSetting = 0.200f;
		m_fPreFaultTime = 2.000f;		//故障前时间
		m_fMarginTime = 0.2f;
		m_fPostFaultTime = 2.000f;		//保护动作后持续时间  2.000f
		m_nFaultTrigMode = 0;					//故障触发方式 S1=时间,S2=按键,S3=开入量“H”触发,S4=GPS 0
		m_bCBSimulation = 0;		//断路器模拟  S1=不模拟,S2=模拟 0
		m_fCBTripTime = 0.200f;		//分闸时间	200ms
		m_fCBCloseTime = 0.100f;		//合闸时间	100ms
		m_nBinLogic = 1;
		m_nOutputSwitchMode = 0;
		m_fBoutTimeTrig = 0.0f;
		m_fBoutHoldTime = 0.0f;


		m_fSettingBreak[0] = 8.0f;
		m_fSettingBreak[1] = 7.0f;
		m_fSettingTime[0] = 0.0f;
		m_fSettingTime[1] = 0.5f;

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_binIn[i].init();
		}

		for (int i = 0; i < g_nBinExCount; i++)
		{
			m_binInEx[i].init();
		}

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_nStateBOut[i] = 0;
		}
	}
	void CopyOwn(tmt_dc_break_paras* pDest)
	{
		pDest->m_fISetting = m_fISetting;
		pDest->m_nFaultChannel = m_nFaultChannel;
		pDest->m_fRate = m_fRate;
		pDest->m_fTSetting = m_fTSetting;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_fPostFaultTime = m_fPostFaultTime;
		pDest->m_nFaultTrigMode = m_nFaultTrigMode;
		pDest->m_bCBSimulation = m_bCBSimulation;
		pDest->m_fCBTripTime = m_fCBTripTime;
		pDest->m_fCBCloseTime = m_fCBCloseTime;
		pDest->m_fBoutTimeTrig = m_fBoutTimeTrig;
		pDest->m_fBoutHoldTime = m_fBoutHoldTime;
		pDest->m_nOutputSwitchMode = m_nOutputSwitchMode;

		for(int nIndex = 0; nIndex < TMT_DCBREAK_SETTING_NUM; nIndex++)
		{
			pDest->m_fSettingBreak[nIndex] = m_fSettingBreak[nIndex];
			pDest->m_fSettingTime[nIndex] = m_fSettingTime[nIndex];
		}

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_binIn[nIndex] = m_binIn[nIndex];
			pDest->m_binInEx[nIndex] = m_binInEx[nIndex];
			pDest->m_nStateBOut[nIndex] = m_nStateBOut[nIndex];
		}
	}
	int GetSttTrigMode()
	{
		int nSttTrigMode = TMT_MDSTATE_TIMETRIGGER;

		switch (m_nFaultTrigMode)
		{
		case 0:		// 时间
			nSttTrigMode = TMT_MDSTATE_TIMETRIGGER; 
			break;
		case 1:		// 按键
			nSttTrigMode = TMT_MDSTATE_MEARSURETRIGGER; 
			break;
		case 2:		// 开入接点
			nSttTrigMode = TMT_MDSTATE_BINTRIGGER; 
			break;
		case 3:		// GPS
			nSttTrigMode = TMT_MDSTATE_GPSBTRIGGER; 
			break;
		default:
			break;
		}

		return nSttTrigMode;
	}


}tmt_DcBreakParas;

typedef struct tmt_dc_break_paras_ex :public tmt_DcBreakParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];//整定动作电压
	char m_pszTSetting[PARAS_RSLT_EXPR_LEN];//整定动作时间
	char m_pszGroupID[MAX_NAME_LEN];//增加分组id

	virtual void init()
	{
		tmt_DcBreakParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszTSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszGroupID, 0, MAX_NAME_LEN);
	} 
}tmt_DcBreakParasEx;

typedef struct tmt_dc_break_results :public tmt_ImpedanceResults
{
public:
	float	 m_fFirstTripTime[8];//开入动作时间
	float	 m_fRecloseTime;//重合闸
	float	 m_fTripTime;   //动作时间
	long m_nActA,m_nActB,m_nActC,m_nActD;//开入动作描述
	int		m_nActID[MAX_BINARYIN_COUNT];//将原来m_nActA、B、C等统一为数组
	float		m_fSecondTripTime;//后加速动作
	long    m_nActAcc;//后加速动作描述

public:
	virtual void init()
	{
		m_fRecloseTime = 0;
		m_fTripTime = 0;
		m_fSecondTripTime = 0;
		m_nActA = m_nActB = m_nActC = 0;
		m_nActAcc = 0;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			m_nActID[nIndex] = 0;
		}

		for(int i=0;i<4;i++)
		{
			m_fFirstTripTime[i] = m_fFirstTripTime[i+4] = 0;
			m_fRecordTime[i] = 0;
			m_fReturnTime[i] = m_fReturnTime[i+4] = 0;
		}

		tmt_ImpedanceResults::init();
	} 

	void CopyOwn(tmt_dc_break_results* pDest)
	{
		pDest->m_fRecloseTime = m_fRecloseTime;
		pDest->m_fTripTime = m_fTripTime;
		pDest->m_nActA = m_nActA;
		pDest->m_nActB = m_nActB;
		pDest->m_nActC = m_nActC;
		pDest->m_nActD = m_nActD;
		pDest->m_nActAcc = m_nActAcc;
	}
	void SetFault1TripTime(long nTripIndex,long nInputMapState,float fValue,bool bHasMapReclose)
	{
		if (fValue<=0)
		{
			return;
		}

		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_THREE)
		{
			m_fFirstTripTime[0] = fValue;
			m_fFirstTripTime[1] = fValue;
			m_fFirstTripTime[2] = fValue;
		}
		else if (nInputMapState == STT_IMPEDANCE_BIN_STATE_SINGLE)
		{
			m_fFirstTripTime[nTripIndex-bHasMapReclose] = fValue;
		}
	}

	void SetFault2TripTime(long nTripIndex,long nInputMapState,float fValue)
	{
		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_RECLOCE)
			return;

		if (fValue>=m_fSecondTripTime)
		{
			m_fSecondTripTime = fValue;
		}
	}

	float GetFirstTripTime()
	{
		float fValue = 0.0f;

		for (int nIndex = 0;nIndex<3;nIndex++)
		{
			if (fValue<m_fFirstTripTime[nIndex])
			{
				fValue = m_fFirstTripTime[nIndex];
			}
		}

		return fValue;
	}

}tmt_DcBreakResults;

typedef struct tmt_dc_break_test : public TMT_PARAS_HEAD
{
public:
	tmt_DcBreakParasEx m_oDcBreakParas;
	tmt_DcBreakResults m_oDcBreakResults;
	char m_szName[MAX_NAME_LEN];

	virtual void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_DCBreakTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		memset(m_szName, 0, MAX_NAME_LEN);
		memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

		m_oDcBreakParas.init();
		m_oDcBreakResults.init();
	}

	tmt_dc_break_test()
	{
		init();
	}
	virtual void clear_result()
	{
		m_oDcBreakResults.init();
	}
	virtual ~tmt_dc_break_test(){}

}tmt_DcBreakTest;


void stt_init_paras(tmt_DcBreakParas *pParas);
void stt_init_paras_ex(tmt_DcBreakParasEx *pParas);
void stt_init_results(tmt_DcBreakResults *pResults);

void stt_xml_serialize_DcBreak(tmt_DcBreakParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_DcBreak_ex(tmt_DcBreakParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DcBreakResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DcBreakTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_write_DcBreakTest();

