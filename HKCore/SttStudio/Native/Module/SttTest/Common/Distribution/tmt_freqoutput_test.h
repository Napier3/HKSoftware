#pragma once

#include "../tmt_common_def.h"
#include"../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_test_paras_head.h"

#define FreqChange_Max_Count 60000

typedef struct tmt_freqoutput_channel : public tmt_channel//电压电流通道
{
public:
	 int m_nSelect;//使能
	 float m_fAmp;//幅值V/A
	 float m_fAngle;//相位

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

typedef struct tmt_freqoutput_newfile //新建文件
{
	int m_nSetType;//0=默认设置 1=电网频率递变 2=转速脉冲频率递变3=直流电流递变
	int m_nRowCount;        // 行数
	float m_fOutPutTime;        // 持续时长 (ms)
	float m_fFrequency;     // 频率 (Hz)
	float m_fDCCurrent;     // 直流电流 (mA)
	float m_fFreqPluse;//转速脉冲频率hz

	// 电网频率递变参数
	float m_fStartFreq;     // 频率起始值 (Hz)
	float m_fEndFreq;       // 频率终止值 (Hz)
	float m_fStepFreq;      // 频率步长 (mHz)
	int m_nFreqChangeMode;  // 变化方式 (0=始-终, 1=始-终-始)
	float m_fFreqOutPutTime;    // 持续时长 (ms)

	// 转速脉冲频率递变参数
	float m_fStartFreqPluse;     // 频率起始值 (Hz)
	float m_fEndFreqPluse;       // 频率终止值 (Hz)
	float m_fStepFreqPluse;      // 频率步长 (mHz)
	int m_nFreqChangeModePluse;  // 变化方式 (0=始-终, 1=始-终-始)
	float m_fFreqOutPutTimePluse;    // 持续时长 (ms)


	// 直流电流递变参数
	float m_fStartCurrent;  // 直流电流起始值 (mA)
	float m_fEndCurrent;    // 直流电流终止值 (mA)
	float m_fStepCurrent;   // 直流电流步长 (mA)
	int m_nCurrentChangeMode; // 变化方式 (0=始-终, 1=始-终-始)
	float m_fCurrentOutPutTime; // 持续时长 (ms)

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

typedef struct tmt_freqoutput_para //存放频率表格数据
{
	float m_fHoldTime;        // 持续时长 (ms)
	float m_fFrequency;     // 电网频率 (Hz)
	float m_fPluseFrequency;     // 转速脉冲频率 (Hz)
	float m_fDCCurrent;     // 直流电流 (mA)

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

	int m_nOutPutType;//0=电压电流 1=直流信号源 2=转速脉冲信号
	int	 m_nPulseType;//脉冲信号 0=正弦波 1=矩形波
    float m_fPulseWidth;// 脉冲宽度ms
    int	m_nPeakValueType;//峰峰值 
	int m_nIdc[2];////直流信号源 0 = Idc1,1=Idc2
	
	int m_nStateCount;//默认频率点数
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