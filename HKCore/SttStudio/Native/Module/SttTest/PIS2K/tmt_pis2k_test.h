#pragma once
#include"../../SttTestBase/SttXmlSerialize.h"
#define BIT0  0x0001
#define BIT1  0x0002
#define BIT2  0x0004
#define BIT3  0x0008
#define BIT4  0x0010
#define BIT5  0X0020
#define BIT6  0X0040
#define BIT7  0X0080
#define BIT8  0X0100
#define BIT9  0X0200
#define BIT10  0X0400
#define BIT11  0X0800
typedef struct tmt_pis2k_DAValue
{
	bool ADStart;// 1启动正弦波，0停止正弦波
	unsigned int ACDCflag;//控制DA输出直流还是交流bit0，bit1分别表示da1，da2.1为直流。0为交流
	float DA1_FZ;
	float DA1_Frequency;//da1频率
	float DA1_Phase;//da1相位
	float DA1_ACrisetime;     //设置上升速率
	float DA1_ACdowntime;     //设置下降速率
	float DA1_ACmaxtime;     //设置下降速率

	float DA2_FZ;
	float DA2_ACrisetime;     //设置上升时间
	float DA2_ACdowntime;     //设置下降时间
	float DA2_ACmaxtime;     //设置下降时间
	unsigned int DA_bit8;//4路8位的DA输出。
	bool AdjCloseLoopMode;//设定此模式为校准模式，或者正常闭环模式

	void init()
	{
		ADStart = 1;
		ACDCflag = 1;
		DA1_FZ = 500;
		DA1_Frequency = 200;
		DA1_Phase = 0;
		DA1_ACrisetime = 2;
		DA1_ACdowntime = 0.5;
		DA1_ACmaxtime  = 30;

		DA2_FZ = 3.3;
		DA2_ACrisetime = 2;
		DA2_ACdowntime = 0.5;
		DA2_ACmaxtime = 30;
		DA_bit8 = 0;
		AdjCloseLoopMode = 0;
	}
}tmt_pis2k_DA;

typedef struct tmt_pis2k_Setting
{
	float VoltageAlarmMin;
	float VoltageAlarmMax;
	float CurrentAlarmMin;
	float CurrentAlarmMax;
	unsigned int  ADCurrentState;//电流采集档位选择 0 0.5mA档位，1  10mA档位
	unsigned int  LocalRemoteFlag; //设备是否为PC控制。1为PC控制，0为脱机控制
	unsigned int  WorkModeFlag; //设备实验类型。1为直流耐压试验，0为绝缘电阻试验
	unsigned int  AutoADChangeState;//
    unsigned int  CurrentMeasPos;//电流采集模块位置选择

	void init()
	{
		VoltageAlarmMin = 0;
		VoltageAlarmMax= 2500;
		CurrentAlarmMin= 0;
		CurrentAlarmMax= 10;
		ADCurrentState = 0;//电流采集档位选择 0 0.5mA档位，1  10mA档位
		LocalRemoteFlag = 1; //设备是否为PC控制。1为PC控制，0为脱机控制
		WorkModeFlag = 0; //设备实验类型。1为直流耐压试验，0为绝缘电阻试验
		AutoADChangeState = 1;//
        CurrentMeasPos = 1;//默认采用位置1采集系数，关联500V电压等级
	}
}tmt_pis2k_Setting;

typedef struct tmt_pis2k_para
{
public:
	tmt_pis2k_DA m_oDA;
	tmt_pis2k_Setting m_oSetting;
public:
	void init()
	{
		m_oDA.init();
		m_oSetting.init();
	}

	tmt_pis2k_para()	{}
}tmt_Pis2kPara;

typedef struct tmt_pis2k_result
{
public:
	float m_fMeasU;
	float m_fMeasI;
	float m_fMeasR;
	float m_fTemp1;
	float m_fTemp2;
	float m_fTemp3;
public:
	void init()
	{
		m_fMeasU=0.0f;
		m_fMeasI=0.0f;
		m_fMeasR=0.0f;
		m_fTemp1=0.0f;
		m_fTemp2=0.0f;
		m_fTemp3=0.0f;
	}

	tmt_pis2k_result()	{}
}tmt_Pis2kResult;

typedef struct tmt_pis2k_test
{
public:
	tmt_Pis2kPara    m_oPis2kPara;
	tmt_Pis2kResult  m_oPis2kResult;

	void init()
	{
		m_oPis2kPara.init();
		m_oPis2kResult.init();
	}
	tmt_pis2k_test() {}
}tmt_Pis2kTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_PtTest();
void stt_init_paras(tmt_Pis2kPara *pPara);
void stt_xml_serialize(tmt_Pis2kPara *pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_Pis2kResult *pResult, CSttXmlSerializeBase *pXmlSierialize);

