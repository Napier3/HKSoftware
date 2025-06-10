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
typedef struct tmt_pic200d_DAValue
{
	bool ADStart;// 1�������Ҳ���0ֹͣ���Ҳ�
	unsigned int ADDCflag;//����DA���ֱ�����ǽ���bit0��bit1�ֱ��ʾda1��da2.1Ϊֱ����0Ϊ����
	float DA1_FZ;
	float DA1_Frequency;//da1Ƶ��
	float DA1_Phase;//da1��λ
	float DA1_ACrisetime;     //������������
	float DA1_ACdowntime;     //�����½�����
	float DA1_ACholdtime;     //�����½�����

	float DA2_FZ;
	float DA2_ACrisetime;     //��������ʱ��
	float DA2_ACdowntime;     //�����½�ʱ��
	float DA2_ACholdtime;     //�����½�ʱ��
	unsigned int DA_bit8;//4·8λ��DA�����
	bool AdjCloseLoopMode;//�趨��ģʽΪУ׼ģʽ�����������ջ�ģʽ

	void init()
	{
		ADStart = 1;
		ADDCflag |= BIT3;
		DA1_FZ = 500;
		DA1_Frequency = 200;
		DA1_Phase = 0;
		DA1_ACrisetime = 2;
		DA1_ACdowntime = 0.5;
		DA1_ACholdtime  = 30;

		DA2_FZ = 3.3;
		DA2_ACrisetime = 2;
		DA2_ACdowntime = 0.5;
		DA2_ACholdtime = 30;
		DA_bit8 = 0;
		AdjCloseLoopMode = 0;
	}
}tmt_pic200d_DA;

typedef struct tmt_pic200d_Setting
{
	float VoltageAlarmMin;
	float VoltageAlarmMax;
	float CurrentAlarmMin;
	float CurrentAlarmMax;
	unsigned int  PIC200DOUTStateFlag; //�����λ��־��0ΪС��0~40A��1Ϊ��40~250A
	unsigned int  LocalRemoteFlag; //�豸�Ƿ�ΪPC���ơ�1ΪPC���ƣ�0Ϊ�ѻ�����
	unsigned int  PIC200DGetStateAutoFlag;//�Զ��е���־λ��1�����Զ��е���0�ر��Զ��е���ֻ�йر��Զ��е�����ѡ��λ
	unsigned int  ADCurrentState;//�����ɼ���λѡ�� 0 250A/12.5A��λ��1  25A/1.25A��λ��2  25A/1.25A��λ
	unsigned int  ADVoltageState;//��ѹ�ɼ���λѡ�� 0 5V��λ��1 1V��λ��2  0.2V��λ
	void init()
	{
		VoltageAlarmMin = 0;
		VoltageAlarmMax= 5;
		CurrentAlarmMin= 0;
		CurrentAlarmMax= 250;
		PIC200DOUTStateFlag = 0;
		LocalRemoteFlag = 1; //�豸�Ƿ�ΪPC���ơ�1ΪPC���ƣ�0Ϊ�ѻ�����
		PIC200DGetStateAutoFlag = 1;
		ADCurrentState = 0;//�����ɼ���λѡ�� 0 0.5mA��λ��1  10mA��λ

		ADVoltageState = 0;//
	}
}tmt_pic200d_Setting;

typedef struct tmt_pic200d_para
{
public:
	tmt_pic200d_DA m_oDA;
	tmt_pic200d_Setting m_oSetting;
public:
	void init()
	{
		m_oDA.init();
		m_oSetting.init();
	}

	tmt_pic200d_para()	{}
}tmt_Pic200dPara;

typedef struct tmt_pic200d_result
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

	tmt_pic200d_result()	{}
}tmt_Pic200dResult;

typedef struct tmt_pic200d_test
{
public:
	tmt_Pic200dPara    m_oPic200dPara;
	tmt_Pic200dResult  m_oPic200dResult;

	void init()
	{
		m_oPic200dPara.init();
		m_oPic200dResult.init();
	}
	tmt_pic200d_test() {}
}tmt_Pic200dTest;

//typedef struct tmt_pic200dAux_DA
//{
//	int Pic200dAuxVdc2StartFlag;
//	int Pic200dAuxVdc1State;
//	float Pic200dAuxVdc2Value;

//	void init()
//	{
//		Pic200dAuxVdc2StartFlag = 0;
//		Pic200dAuxVdc1State= 5;
//		Pic200dAuxVdc2Value= 1000;
//	}
//}tmt_pic200dAux_DA;

//typedef struct tmt_pic200dAux_para
//{
//public:
//	tmt_pic200dAux_DA m_oAuxDA;

//	void init()
//	{
//		m_oAuxDA.init();
//	}

//	tmt_pic200dAux_para()	{}
//}tmt_Pic200dAuxPara;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_PtTest();
void stt_init_paras(tmt_Pic200dPara *pPara);
void stt_xml_serialize(tmt_Pic200dPara *pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_Pic200dResult *pResult, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serializeAux(tmt_pic200dAux_DA *pPara, CSttXmlSerializeBase *pXmlSierialize);
