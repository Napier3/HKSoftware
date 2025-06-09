#pragma once

#include "../Impedance/tmt_impedance_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_DCVOLTAGE_SETTING_NUM     4
#define TMT_DCVOLTAGE_TESTNAME_LEN	  64
#define TMT_DCVOLTAGE_GROUPID_LEN	  32

typedef struct tmt_dc_voltage_paras
{
public:
    double m_fUSetting;           //整定动作电压
	int m_nFaultChannel;        //故障通道
	int m_nCurrentChannel;      //电流通道
	double m_fCurrent;          //电流(A)
	float m_fRate;              //倍数
	float m_fMaxFaultTime;      //最大故障时间
	float m_fPreFaultTime;		//故障前时间
	float m_fMarginTime;        //故障时间裕度
	float m_fPostFaultTime;		//保护动作后持续时间  2.000f
	int   m_nFaultTrigMode;		//故障触发方式 S1=时间,S2=按键,S3=开入量“H”触发,S4=GPS 0(0:时间触发,1:按键触发,2:开入接点翻转触发,3:GPS触发)
    tmt_time m_tGps;
	BOOL  m_bCBSimulation;		//断路器模拟  S1=不模拟,S2=模拟 0(0:不模拟,1:模拟)
	float m_fCBTripTime;		//分闸时间	200ms（模拟断路器时的分闸时间）
	float m_fCBCloseTime;		//合闸时间	100ms（模拟断路器时的合闸时间）
	double m_fPreFaultVol;      //故障前电压
	double m_fPreFaultCur;      //故障前电流

	float   m_fSettingOverVol[TMT_DCVOLTAGE_SETTING_NUM];//电压保护动作值
	float   m_fSettingTime[TMT_DCVOLTAGE_SETTING_NUM];//电压保护动作时间
	tmt_BinaryIn m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int m_nBinLogic; //0 1逻辑与或
	BOOL m_nVolType; //0 过电压 1低电压



	float  m_fVolAmp[8];//常态及故障态电压幅值Ua\Ub\Uc\Uz
	float  m_fVolAng[8];//常态及故障态电压相位Ua\Ub\Uc\Uz

	//2022.5.23 caoxc 增加项目名称
	char m_pszTestName[TMT_DCVOLTAGE_TESTNAME_LEN];
	//2022.5.26 caoxc 增加分组id
	char m_pszGroupID[TMT_DCVOLTAGE_GROUPID_LEN];

	double m_fR, m_fX;  //阻抗平面的阻抗值，用于绘图
	float m_fImpAngle[2];		//阻抗角(第一次故障阻抗、第二次故障阻抗) m_fPhi



public:
	virtual void init()
	{
		m_fUSetting = 2.85f;
		m_nFaultChannel = 0;
		m_nCurrentChannel = 0;
		m_fCurrent = 0.000f;
		m_fRate = 1.0f;
		m_fMaxFaultTime = 0.200f;
		m_fPreFaultTime = 2.000f;		//故障前时间
		m_fMarginTime = 0.2f;
		m_fPostFaultTime = 2.000f;		//保护动作后持续时间  2.000f
		m_nFaultTrigMode = 0;					//故障触发方式 S1=时间,S2=按键,S3=开入量“H”触发,S4=GPS 0
		m_bCBSimulation = 0;		//断路器模拟  S1=不模拟,S2=模拟 0
		m_fCBTripTime = 0.200f;		//分闸时间	200ms
		m_fCBCloseTime = 0.100f;		//合闸时间	100ms
		m_fPreFaultVol = 57.74f;
		m_fPreFaultCur = 0.00f;
		m_nBinLogic = 1;
		m_nVolType = 0;


		m_fSettingOverVol[0] = 8.0f;
		m_fSettingOverVol[1] = 7.0f;
		m_fSettingOverVol[2] = 6.0f;
		m_fSettingOverVol[3] = 5.0f;
		m_fSettingTime[0] = 0.0f;
		m_fSettingTime[1] = 0.5f;
		m_fSettingTime[2] = 1.0f;
		m_fSettingTime[3] = 1.5f;

		m_fImpAngle[0] = 90;			//阻抗角 m_fPhi
		m_fImpAngle[1] = 90;
		//2022.5.23 caoxc
		memset(m_pszTestName, 0, TMT_DCVOLTAGE_TESTNAME_LEN);
		//2022.5.26 caoxc
		memset(m_pszGroupID, 0, TMT_DCVOLTAGE_GROUPID_LEN);
		for (int nIndex = 0;nIndex<8;nIndex++)
		{
			m_fVolAmp[nIndex] = 57.74f;
			m_fVolAng[nIndex] = 0.0f;
		}


		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

		for (int i = 0; i < g_nBinExCount; i++)
		{
			m_binInEx[i].init();
		}

		for (int i = 0; i < g_nBinExCount; i++)
		{
			m_binOutEx[i].init();
		}

		m_fVolAng[1] = -120.0f;
		m_fVolAng[2] = 120.0f;

		m_fVolAng[5] = -120.0f;
		m_fVolAng[6] = 120.0f;
	}
	void CopyOwn(tmt_dc_voltage_paras* pDest)
	{
		pDest->m_fUSetting = m_fUSetting;
		pDest->m_nFaultChannel = m_nFaultChannel;
		pDest->m_nCurrentChannel = m_nCurrentChannel;
		pDest->m_fCurrent = m_fCurrent;
		pDest->m_fRate = m_fRate;
		pDest->m_fMaxFaultTime = m_fMaxFaultTime;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_fPostFaultTime = m_fPostFaultTime;
		pDest->m_nFaultTrigMode = m_nFaultTrigMode;
		pDest->m_bCBSimulation = m_bCBSimulation;
		pDest->m_fCBTripTime = m_fCBTripTime;
		pDest->m_fCBCloseTime = m_fCBCloseTime;
		pDest->m_fPreFaultVol = m_fPreFaultVol;
		pDest->m_fPreFaultCur = m_fPreFaultCur;
		pDest->m_nVolType = m_nVolType;

		for(int nIndex = 0; nIndex < TMT_DCVOLTAGE_SETTING_NUM; nIndex++)
		{
			pDest->m_fSettingOverVol[nIndex] = m_fSettingOverVol[nIndex];
			pDest->m_fSettingTime[nIndex] = m_fSettingTime[nIndex];
		}

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_binIn[nIndex] = m_binIn[nIndex];
			pDest->m_binOut[nIndex] = m_binOut[nIndex];
			pDest->m_binInEx[nIndex] = m_binInEx[nIndex];
			pDest->m_binOutEx[nIndex] = m_binOutEx[nIndex];
		}
		
		for (int nIndex = 0; nIndex < 8; nIndex++)
		{
			pDest->m_fVolAmp[nIndex] = m_fVolAmp[nIndex];
			pDest->m_fVolAng[nIndex] = m_fVolAng[nIndex];
		}

		for (int nIndex = 0; nIndex < 2; nIndex++)
		{
			pDest->m_fImpAngle[nIndex] = m_fImpAngle[nIndex];
		}
		pDest->m_fVolAng[1] = m_fVolAng[1];
		pDest->m_fVolAng[2] = m_fVolAng[2];

		pDest->m_fVolAng[5] = m_fVolAng[5];
		pDest->m_fVolAng[6] = m_fVolAng[6];
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


}tmt_DcVoltageParas;

typedef struct tmt_dc_voltage_paras_ex :public tmt_DcVoltageParas
{
public:
	char m_pszSetting[PARAS_RSLT_EXPR_LEN];//整定动作电压
	char m_maxTSetting[PARAS_RSLT_EXPR_LEN];//最大故障时间

	virtual void init()
	{
		tmt_DcVoltageParas::init();
		memset(m_pszSetting,0,PARAS_RSLT_EXPR_LEN);
		memset(m_maxTSetting,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_DcVoltageParasEx;

typedef struct tmt_dc_voltage_results :public tmt_ImpedanceResults
{
public:
	float    m_fZshort;    //短路阻抗
	float    m_fIShortAngle;   //短路电流相位角 
	float	 m_fFirstTripTime[8];//开入动作时间
	float	 m_fRecloseTime;
	float	 m_fTripTime;   //动作时间
	long m_nActA,m_nActB,m_nActC,m_nActD;
	int		m_nActID[MAX_BINARYIN_COUNT];//将原来m_nActA、B、C等统一为数组
	float		m_fSecondTripTime;//后加速动作
	long    m_nActAcc;//后加速动作描述
	float m_fFaultCurrent,m_fFaultVol;	//故障电流、电压
	float m_fDcVoltage;
	float m_fImpAngle;


public:
	virtual void init()
	{
		m_fZshort = 0.0f;
		m_fIShortAngle = 90.0f;
		m_fRecloseTime = 0;
		m_fTripTime = 0;
		m_fSecondTripTime = 0;
		m_nActA = m_nActB = m_nActC = 0;
		m_nActAcc = 0;
		m_fDcVoltage = m_fFaultVol = m_fFaultCurrent = 0;
		m_fImpAngle = 0;


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

	void CopyOwn(tmt_dc_voltage_results* pDest)
	{
		pDest->m_fZshort = m_fZshort;
		pDest->m_fIShortAngle = m_fIShortAngle;
		pDest->m_fRecloseTime = m_fRecloseTime;
		pDest->m_fTripTime = m_fTripTime;
		pDest->m_nActA = m_nActA;
		pDest->m_nActB = m_nActB;
		pDest->m_nActC = m_nActC;
		pDest->m_nActD = m_nActD;
		pDest->m_nActAcc = m_nActAcc;
		pDest->m_fFaultCurrent = m_fFaultCurrent;
		pDest->m_fFaultVol = m_fFaultVol;
		pDest->m_fDcVoltage = m_fDcVoltage;
		pDest->m_fImpAngle = m_fImpAngle;
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

}tmt_DcVoltageResults;

typedef struct tmt_dc_voltage_test : public TMT_PARAS_HEAD
{
public:
	tmt_DcVoltageParasEx m_oDcVoltageParas;
	tmt_DcVoltageResults m_oDcVoltageResults;
	char m_szName[MAX_NAME_LEN];

	virtual void init()
	{
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_DCVoltageTest);//DCVoltageTest
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		memset(m_szName, 0, MAX_NAME_LEN);
		memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

		m_oDcVoltageParas.init();
		m_oDcVoltageResults.init();
	}

    tmt_dc_voltage_test()
    {
        init();
    }
    virtual void clear_result()
    {
        m_oDcVoltageResults.init();
    }
	virtual ~tmt_dc_voltage_test(){}

}tmt_DcVoltageTest;


void stt_init_paras(tmt_DcVoltageParas *pParas);
void stt_init_paras_ex(tmt_DcVoltageParasEx *pParas);
void stt_init_results(tmt_DcVoltageResults *pResults);

void stt_xml_serialize_DcVoltage(tmt_DcVoltageParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_DcVoltage_ex(tmt_DcVoltageParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_DcVoltageResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DcVoltageTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_write_DcVoltageTest();

