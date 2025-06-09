#pragma once

#include "../tmt_state_test.h"
#include "../tmt_test_paras_head.h"

#define TMT_OVERCURRENT_SETTING_NUM                     5
#define TMT_OVERCURRENT_TESTNAME_LEN	64
#define TMT_OVERCURRENT_GROUPID_LEN		32

typedef struct tmt_diff_coef_pnv_paras :public tmt_StateParas
{
public:
    float   m_fPreFaultTime;//����ǰʱ��

    int     m_nRampIndex;//�ݱ���ѡ��
    float   m_fBeginVal;//�仯ʼֵ
    float   m_fEndVal;//�仯��ֵ
    float   m_fStepVal;//�仯����
    float   m_fStepTime;//ÿ��ʱ��
    float   m_fFreq;//Ƶ��

    long    m_nBinLogic;//�����߼�
    long    m_nInputState[8];//������״̬
    int     m_nBout[2][8];//����
    int     m_nOutputSwitchMode;
    float   m_fHoldTime;

    float  m_fVolAmp[2][9];//��̬������̬��ѹ��ֵUa\Ub\Uc\Uap\Ubp\Ucp\Usa\Usb\Usc
    float  m_fVolAng[2][9];//��̬������̬��ѹ��λ
    float  m_fCurAmp[2][9];//��̬������̬������ֵIa\Ib\Ic\Iap\Ibp\Icp\Isa\Isb\Isc
    float  m_fCurAng[2][9];//��̬������̬������λ

public:
    virtual void init(int nStateNumbers)
	{
        tmt_StateParas::init(nStateNumbers);
        m_nRampIndex = 8;
        m_fBeginVal = 0.0f;
        m_fEndVal = 5.0f;
        m_fStepVal = 0.1f;
        m_fStepTime = 0.1f;
        m_fFreq = 50;
        m_nBinLogic = 0;
        m_nOutputSwitchMode =  0;
        m_fHoldTime = 0.0f;

        float fAngle[3] = {0, -120.0, 120.0};
        for (int i = 0;i<2;i++)
        {
            for (int nIndex = 0;nIndex<9;nIndex++)
            {
                m_fVolAmp[i][nIndex] = 57.74f;
                m_fCurAmp[i][nIndex] = 0.0f;
                m_fVolAng[i][nIndex] = fAngle[nIndex%3];
                m_fCurAng[i][nIndex] = fAngle[nIndex%3];
            }
        }
        for (int nIndex = 0;nIndex<8;nIndex++)
        {
            m_nInputState[nIndex] = 0;
            m_nBout[0][nIndex] = 0;
            m_nBout[1][nIndex] = 0;
        }

	}

}tmt_DiffCoefPnvParas;
typedef struct tmt_diff_coef_pnv_results :public tmt_StateResults
{
public:
    int m_nBinSwitchCount[3];
    float m_fTimeBinAct[3];
    void init()
    {
        for(int i = 0;i<3;i++)
        {
            m_nBinSwitchCount[i] = 0;
            m_fTimeBinAct[i] = 0.0f;
        }
    }
}tmt_DiffCoefPnvResults;
typedef struct tmt_diff_coef_pnv_test : public TMT_PARAS_HEAD
{
public:
    tmt_DiffCoefPnvParas m_oDiffCoefParas;
    tmt_DiffCoefPnvResults m_oDiffCoefResults;
    void init(long nStateNumbers)
    {
        init_head();
        strcpy(m_pszMacroID, STT_MACRO_ID_StateDiffCoef);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
        m_nVersion = 0x00010001;
        m_nTestState = 0;
#endif
        m_oDiffCoefParas.init(nStateNumbers);
        m_oDiffCoefResults.init();
    }

    tmt_diff_coef_pnv_test(){	init(2);}
    virtual ~tmt_diff_coef_pnv_test(){}

}tmt_DiffCoefPnvTest;

void stt_init_paras(tmt_DiffCoefPnvParas *pParas);
void stt_init_paras(tmt_DiffCoefPnvResults *pParas);

void stt_xml_serialize_DiffCoef_Pnv(tmt_DiffCoefPnvParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_DiffCoef_Pnv(tmt_DiffCoefPnvResults *pParas, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_DiffCoefPnvTest *pTests, CSttXmlSerializeBase *pXmlSerialize);


