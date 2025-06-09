#pragma once

#include "../tmt_common_def.h"
#include"../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_test_paras_head.h"

#define FreqChange_Max_Count 60000

typedef struct tmt_freqoutput_channel : public tmt_channel//��ѹ����ͨ��
{
public:
	 int m_nSelect;//ʹ��
	 float m_fAmp;//��ֵV/A
	 float m_fAngle;//��λ

public:
	void init()
	{
		 m_nSelect = 0;
		 m_fAmp = m_fAngle = 0;
	}

	tmt_freqoutput_channel()
	{
		init();
	}
}tmt_FreqOutputChannel;

typedef struct tmt_freqoutput_newfile //�½��ļ�
{
	int m_nSetType;//0=Ĭ������ 1=����Ƶ�ʵݱ� 2=ת������Ƶ�ʵݱ�3=ֱ�������ݱ�
	int m_nRowCount;        // ����
	float m_fOutPutTime;        // ����ʱ�� (ms)
	float m_fFrequency;     // Ƶ�� (Hz)
	float m_fDCCurrent;     // ֱ������ (mA)
	float m_fFreqPluse;//ת������Ƶ��hz

	// ����Ƶ�ʵݱ����
	float m_fStartFreq;     // Ƶ����ʼֵ (Hz)
	float m_fEndFreq;       // Ƶ����ֵֹ (Hz)
	float m_fStepFreq;      // Ƶ�ʲ��� (mHz)
	int m_nFreqChangeMode;  // �仯��ʽ (0=ʼ-��, 1=ʼ-��-ʼ)
	float m_fFreqOutPutTime;    // ����ʱ�� (ms)

	// ת������Ƶ�ʵݱ����
	float m_fStartFreqPluse;     // Ƶ����ʼֵ (Hz)
	float m_fEndFreqPluse;       // Ƶ����ֵֹ (Hz)
	float m_fStepFreqPluse;      // Ƶ�ʲ��� (mHz)
	int m_nFreqChangeModePluse;  // �仯��ʽ (0=ʼ-��, 1=ʼ-��-ʼ)
	float m_fFreqOutPutTimePluse;    // ����ʱ�� (ms)


	// ֱ�������ݱ����
	float m_fStartCurrent;  // ֱ��������ʼֵ (mA)
	float m_fEndCurrent;    // ֱ��������ֵֹ (mA)
	float m_fStepCurrent;   // ֱ���������� (mA)
	int m_nCurrentChangeMode; // �仯��ʽ (0=ʼ-��, 1=ʼ-��-ʼ)
	float m_fCurrentOutPutTime; // ����ʱ�� (ms)

	void init()
	{
		m_nSetType = 0;
		m_nRowCount = 10;        
		m_fOutPutTime = 20;       
		m_fFrequency = 50;    
		m_fFreqPluse = 3000;
		m_fDCCurrent = 12;     
		m_fStartFreq = 49;    
		m_fEndFreq = 50;       
		m_fStepFreq = 10;      
		m_nFreqChangeMode = 0;  
		m_fFreqOutPutTime = 20;    
		m_fStartFreqPluse = 49;    
		m_fEndFreqPluse = 50;       
		m_fStepFreqPluse = 10;      
		m_nFreqChangeModePluse = 0;  
		m_fFreqOutPutTimePluse = 20;  
		m_fStartCurrent = 4;  
		m_fEndCurrent = 20;    
		m_fStepCurrent = 1;   
		m_nCurrentChangeMode = 0; 
		m_fCurrentOutPutTime = 20; 
	}

	tmt_freqoutput_newfile()
	{	
		init(); 
	}
}tmt_FreqOutputNewFile;

typedef struct tmt_freqoutput_para //���Ƶ�ʱ������
{
	float m_fHoldTime;        // ����ʱ�� (ms)
	float m_fFrequency;     // ����Ƶ�� (Hz)
	float m_fPluseFrequency;     // ת������Ƶ�� (Hz)
	float m_fDCCurrent;     // ֱ������ (mA)

	void init()
	{
		m_fHoldTime = 20;       
		m_fFrequency = 50;    
		m_fPluseFrequency = 3000;
		m_fDCCurrent = 12;   
	}

	tmt_freqoutput_para()
	{	
		
	}
}tmt_FreqOutputPara;


typedef struct tmt_freqoutput_paras
{
public:
 	tmt_FreqOutputChannel m_uiVOL[MAX_VOLTAGE_COUNT];
 	tmt_FreqOutputChannel m_uiCUR[MAX_CURRENT_COUNT];

	int m_nOutPutType;//0=��ѹ���� 1=ֱ���ź�Դ 2=ת�������ź�
	int	 m_nPulseType;//�����ź� 0=���Ҳ� 1=���β�
    float m_fPulseWidth;// ������ms
    int	m_nPeakValueType;//���ֵ 
	int m_nIdc[2];////ֱ���ź�Դ 0 = Idc1,1=Idc2
	
	int m_nStateCount;//Ĭ��Ƶ�ʵ���
	tmt_FreqOutputPara m_oFreqOutputPara[FreqChange_Max_Count];
	
	tmt_FreqOutputNewFile m_oFreqOutputNewFile;

  
public:
	void init()
	{
		float fAngle[3] = {0, -120.0, 120.0};

		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			m_uiVOL[i].init();
			m_uiCUR[i].init();
			m_uiVOL[i].m_fAmp = m_uiCUR[i].m_fAmp = 0;
			m_uiVOL[i].m_fAngle = m_uiCUR[i].m_fAngle = fAngle[i % 3];
		}

		m_nOutPutType = 0;
		m_nPulseType = 0;
		m_fPulseWidth = 10;
		m_nPeakValueType = 0;
		m_nIdc[0]= 1;
		m_nIdc[1]= 1;
		m_nStateCount = 2;
		m_oFreqOutputNewFile.init();
	}

	void initFreqPonint(int nCount)
	{
		for(int i = 0; i < nCount && i<FreqChange_Max_Count ; i++)
		{
			m_oFreqOutputPara[i].init();
		}
	}


	tmt_freqoutput_paras()
	{
		init();
		initFreqPonint(m_nStateCount);
	}

	virtual ~tmt_freqoutput_paras() 
	{

	}

} tmt_FreqOutputParas;

typedef struct tmt_freqoutput_result
{
public:

	void init()
	{

	}
	tmt_freqoutput_result()	
	{ 
		init(); 
	}
	virtual ~tmt_freqoutput_result(){}
}tmt_FreqOutputResult;

typedef struct tmt_freqoutput_test : public TMT_PARAS_HEAD
{
public:
	tmt_FreqOutputParas m_oFreqOutputParas;
	tmt_FreqOutputResult m_oFreqOutputResult;

	void init()
	{
		strcpy(m_pszMacroID, STT_MACRO_ID_FreqOutputTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oFreqOutputParas.init();
		m_oFreqOutputResult.init();
	}

	tmt_freqoutput_test()
	{
		init();
	}
} tmt_FreqOutputTest;


void stt_xml_serialize_write_FreqOutputTest();
void stt_init_paras(tmt_FreqOutputParas *pParas);
void stt_xml_serialize(tmt_FreqOutputParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_FreqOutputParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);
void stt_state_paras_delete(tmt_FreqOutputParas *pParas, int nIndex);
void stt_xml_serialize_freqchangePoint(tmt_FreqOutputPara *pParas, const char *pszID, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_newfile(tmt_FreqOutputNewFile *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_channel(tmt_FreqOutputChannel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize);