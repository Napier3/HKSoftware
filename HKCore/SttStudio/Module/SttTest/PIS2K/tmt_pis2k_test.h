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
	bool ADStart;// 1�������Ҳ���0ֹͣ���Ҳ�
	unsigned int ACDCflag;//����DA���ֱ�����ǽ���bit0��bit1�ֱ��ʾda1��da2.1Ϊֱ����0Ϊ����
	float DA1_FZ;
	float DA1_Frequency;//da1Ƶ��
	float DA1_Phase;//da1��λ
	float DA1_ACrisetime;     //������������
	float DA1_ACdowntime;     //�����½�����
	float DA1_ACmaxtime;     //�����½�����

	float DA2_FZ;
	float DA2_ACrisetime;     //��������ʱ��
	float DA2_ACdowntime;     //�����½�ʱ��
	float DA2_ACmaxtime;     //�����½�ʱ��
	unsigned int DA_bit8;//4·8λ��DA�����
	bool AdjCloseLoopMode;//�趨��ģʽΪУ׼ģʽ�����������ջ�ģʽ

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
	unsigned int  ADCurrentState;//�����ɼ���λѡ�� 0 0.5mA��λ��1  10mA��λ
	unsigned int  LocalRemoteFlag; //�豸�Ƿ�ΪPC���ơ�1ΪPC���ƣ�0Ϊ�ѻ�����
	unsigned int  WorkModeFlag; //�豸ʵ�����͡�1Ϊֱ����ѹ���飬0Ϊ��Ե��������
	unsigned int  AutoADChangeState;//
    unsigned int  CurrentMeasPos;//�����ɼ�ģ��λ��ѡ��

	void init()
	{
		VoltageAlarmMin = 0;
		VoltageAlarmMax= 2500;
		CurrentAlarmMin= 0;
		CurrentAlarmMax= 10;
		ADCurrentState = 0;//�����ɼ���λѡ�� 0 0.5mA��λ��1  10mA��λ
		LocalRemoteFlag = 1; //�豸�Ƿ�ΪPC���ơ�1ΪPC���ƣ�0Ϊ�ѻ�����
		WorkModeFlag = 0; //�豸ʵ�����͡�1Ϊֱ����ѹ���飬0Ϊ��Ե��������
		AutoADChangeState = 1;//
        CurrentMeasPos = 1;//Ĭ�ϲ���λ��1�ɼ�ϵ��������500V��ѹ�ȼ�
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

