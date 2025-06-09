#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"

#define _STT_DC_INCREMENT_VOL_NUM                  4
#define _STT_DC_INCREMENT_CUR_NUM                  3
#define _STT_DC_INCREMENT_CURVE_MAX               20

#define _STT_DC_INCREMENT_GradientIndex_Ua           0
#define _STT_DC_INCREMENT_GradientIndex_Ub           1
#define _STT_DC_INCREMENT_GradientIndex_Uc           2
#define _STT_DC_INCREMENT_GradientIndex_Uz           3
#define _STT_DC_INCREMENT_GradientIndex_Ia           4
#define _STT_DC_INCREMENT_GradientIndex_Ib           5
#define _STT_DC_INCREMENT_GradientIndex_Ic           6

// #define _STT_DC_INCREMENT_GradientIndex_Ia           0
// #define _STT_DC_INCREMENT_GradientIndex_Ib           1
// #define _STT_DC_INCREMENT_GradientIndex_Ic           2
// #define _STT_DC_INCREMENT_GradientIndex_Iab          3
// #define _STT_DC_INCREMENT_GradientIndex_Ibc          4
// #define _STT_DC_INCREMENT_GradientIndex_Ica          5
// #define _STT_DC_INCREMENT_GradientIndex_Iabc         6


#define STT_DC_INCREMENT_GradType_Slope                 0
#define STT_DC_INCREMENT_GradType_RiseTime              1
#define STT_DC_INCREMENT_GradType_InitValue             2



typedef struct tmt_dc_increment_paras :public tmt_SearchBase
{
public:
    float m_fVolAmp[_STT_DC_INCREMENT_VOL_NUM];
    float m_fCurAmp[_STT_DC_INCREMENT_CUR_NUM];
    float m_fPrepTime;//׼��ʱ��
    long m_nCurveNum;//��������
    long m_nGradientChIndex;//�ݱ�ͨ�� Ia1��Ib1��Ic1��Iab1��Ibc1��Ica1��Iabc1  0~6
    long m_nTimingCurveIndex;//��ʱ������߱��  0Ϊ����1��1Ϊ����2

    long m_nGradSelected;//�ݱ�ѡ��,��ѡΪ�ݱ�ģʽ
    long m_nGradType;//�ݱ�����  0-б�� 1-����ʱ��   2-��ֵ
    long m_nGradCurveSel;//�ݱ�����ѡ�� 0Ϊ����1��1Ϊ����2
// 	float m_fGradStartValue;//�ݱ�ʼֵ
// 	float m_fGradEndValue;//�ݱ���ֵ
// 	float m_fGradStepValue;//�ݱ䲽��

    float m_fDaDt[_STT_DC_INCREMENT_CURVE_MAX];//�����ߵ�����б��
    float m_fOutputTime[_STT_DC_INCREMENT_CURVE_MAX];//�����ߵ����ʱ��

    int		m_nBinLogic;	//�����߼� //0-�� 1-��

    //������
    tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	//
    tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//

public:
    virtual void init()
    {
        tmt_SearchBase::InitSearch();
        SetLinerSearchMode();

		for (int nIndex = 0;nIndex<_STT_DC_INCREMENT_VOL_NUM;nIndex++)
        {
            m_fVolAmp[nIndex] = 0.0f;
        }

		for (int nIndex = 0;nIndex<_STT_DC_INCREMENT_CUR_NUM;nIndex++)
        {
            m_fCurAmp[nIndex] = 0.0f;
        }

        m_fPrepTime = 5.0f;
        m_nCurveNum = 1;
        m_nGradientChIndex = _STT_DC_INCREMENT_GradientIndex_Ia;
        m_nTimingCurveIndex = 0;
        m_nGradSelected = 0;
        m_nGradType = STT_DC_INCREMENT_GradType_Slope;
        m_nGradCurveSel = 0;
        m_fScanFrom/*m_fGradStartValue*/ = 10.0f;
        m_fScanTo/*m_fGradEndValue*/ = 50.0f;
        m_fStep/*m_fGradStepValue*/ = 1.0f;

		for (int nIndex = 0;nIndex<_STT_DC_INCREMENT_CURVE_MAX;nIndex++)
        {
            m_fDaDt[nIndex] = 10.0f;
            m_fOutputTime[nIndex] = 30.0f;
        }

        m_nBinLogic = TMT_BINLOGIC_OR;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            m_binIn[i].init();
            m_binOut[i].init();
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            m_binInEx[i].init();
        }

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            m_binOutEx[i].init();
        }
    }

    bool IsGradVolCh()
    {
		if (m_nGradientChIndex<=_STT_DC_INCREMENT_GradientIndex_Uz)
        {
            return true;
		} 

        return false;
    }

}tmt_DcIncrementParas;

typedef struct tmt_dc_increment_results
{
public:
    //�������
    float	m_fActTime;
    float	m_fActValue;
    long   m_nAct;//��������

public:
    virtual void init()
    {
        m_fActTime = 0.0f;
        m_fActValue = 0.00f;
        m_nAct = 0;
	} 

}tmt_DcIncrementResults;

typedef struct tmt_dc_increment_test : public TMT_PARAS_HEAD
{
public:
    tmt_DcIncrementParas m_oDcIncParas;
    tmt_DcIncrementResults m_oDcIncResults;
    virtual void init()
    {
        init_head();
        strcpy(m_pszMacroID, STT_MACRO_ID_DcIncrementTest);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oDcIncParas.init();
        m_oDcIncResults.init();
    }

	tmt_dc_increment_test(){	init();}
	virtual void clear_result(){	m_oDcIncResults.init();	}
	virtual ~tmt_dc_increment_test(){}
}tmt_DcIncrementTest;




void stt_init_paras(tmt_DcIncrementParas *pParas);
void stt_init_results(tmt_DcIncrementResults *pResults);

void stt_xml_serialize_DcIncrement(tmt_DcIncrementParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_DcIncrement(tmt_DcIncrementResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DcIncrementTest *pTests, CSttXmlSerializeBase *pXmlSerialize);



