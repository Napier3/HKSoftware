#pragma once

#include "../tmt_common_def.h"
#include"../../../SttTestBase/SttXmlSerialize.h"
#include "../tmt_manu_test.h"

typedef struct tmt_prim_freq_manual_paras : public tmt_manual_paras
{
public:
	int 	m_nOutputType;	//���ģʽ 0-����� 1-ת������ 2-ֱ���ź�
	//����
	int  	m_nSpeedPulseType;     // �����ź�����  0-
	int  	m_nPulseWidth;       // �����ȣ���λ: us��
	int  	m_nPeakToPeakTypeIndex;    // ���ֵ������ѡ��
	float 	m_fPulseFreqHz;       // ����Ƶ�ʣ���λ: Hz��

	//ֱ��  
	float	m_frCurrentDc[2];//ֱ���ź�Դ
	int   	m_nDcOutputMode;      // ֱ���ź�Դģʽ (Ƶ��/ת��)
	float 	m_fDcOutputValue;     // ֱ���ź����ֵ
	float 	m_fGridFrequencyMinHz;  // ����Ƶ����Сֵ
	float 	m_fGridFrequencyMaxHz;  // ����Ƶ�����ֵ
	float 	m_fGenSpeedMinRpm;     // �����ת����Сֵ
	float 	m_fGenSpeedMaxRpm;     // �����ת�����ֵ
	float	 m_fDcCurrentMeasured;  // ֱ����������ֵ

public:
    void init()
    {
		tmt_manual_paras::init();
		m_nOutputType = 0;
		m_nSpeedPulseType = 0;    
		m_nPulseWidth = 0;      
		m_nPeakToPeakTypeIndex = 0;    
		m_fPulseFreqHz = 0.0f;       
		m_frCurrentDc[0] = 0.0f;
		m_frCurrentDc[1] = 0.0f;
		m_nDcOutputMode = 0;      
		m_fDcOutputValue= 0.0f;     
		m_fGridFrequencyMinHz= 0.0f;
		m_fGridFrequencyMaxHz= 0.0f;
		m_fGenSpeedMinRpm= 0.0f;    
		m_fGenSpeedMaxRpm= 0.0f;    
		m_fDcCurrentMeasured= 0.0f;

    }

	void CopyOwn(tmt_prim_freq_manual_paras *pDest)
	{
		tmt_manual_paras::CopyOwn(pDest);
		pDest->m_nOutputType = m_nOutputType;
		pDest->m_nSpeedPulseType = m_nSpeedPulseType;    
		pDest->m_nPulseWidth = m_nPulseWidth;      
		pDest->m_nPeakToPeakTypeIndex = m_nPeakToPeakTypeIndex;    
		pDest->m_fPulseFreqHz = m_fPulseFreqHz;       
		memcpy(pDest->m_frCurrentDc, m_frCurrentDc, sizeof(m_frCurrentDc));
		pDest->m_nDcOutputMode = m_nDcOutputMode;      
		pDest->m_fDcOutputValue= m_fDcOutputValue;     
		pDest->m_fGridFrequencyMinHz= m_fGridFrequencyMinHz;
		pDest->m_fGridFrequencyMaxHz= m_fGridFrequencyMaxHz;
		pDest->m_fGenSpeedMinRpm= m_fGenSpeedMinRpm;    
		pDest->m_fGenSpeedMaxRpm= m_fGenSpeedMaxRpm;    
		pDest->m_fDcCurrentMeasured= m_fDcCurrentMeasured;
	}

    tmt_prim_freq_manual_paras()
    {
        init();
    }

	virtual ~tmt_prim_freq_manual_paras()
	{

	}

}tmt_PrimFreqManualParas;

typedef struct tmt_prim_freq_manual_result : public tmt_manual_result
{

public:
    virtual void init()
    {
		tmt_manual_result::init();
    }

    void CopyOwn(tmt_prim_freq_manual_result *pDest)
    {
		tmt_manual_result::CopyOwn(pDest);
    }

    tmt_prim_freq_manual_result()
    {
        init();
    }
} tmt_PrimFreqManualResult;

typedef struct tmt_prim_freq_manual_test : public TMT_PARAS_HEAD
{
public:
    tmt_PrimFreqManualParas   m_oManuParas;
    tmt_PrimFreqManualResult  m_oManuResult;

    void init()
    {
        strcpy(m_pszMacroID, STT_MACRO_ID_PrimFreqManualTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oManuResult.init();
        m_oManuParas.init();
    }

    tmt_prim_freq_manual_test()
    {
        init();
    }
} tmt_PrimFreqManualTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void stt_xml_serialize_write_PrimFreqManuTest();
void stt_init_paras(tmt_PrimFreqManualParas *pParas);
void stt_init_results(tmt_PrimFreqManualResult *pResults);
void stt_xml_serialize(tmt_PrimFreqManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_PrimFreqManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);
void stt_xml_serialize_act_rcd(tmt_PrimFreqManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase *stt_xml_serialize(tmt_PrimFreqManualTest *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum, long nCurRsNum);

