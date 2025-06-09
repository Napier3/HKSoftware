#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"

#define LOW_FREQ_VOL_GRADIENT_TYPE_LOW_VOL                 0
#define LOW_FREQ_VOL_GRADIENT_TYPE_U2                      1
#define LOW_FREQ_VOL_GRADIENT_TYPE_3U0                     2


typedef struct tmt_low_freq_paras 
{
public:
    //���ϲ���
    int		m_nTestType;	//�������� 0-Ƶ�ʶ���ֵ 1-����ʱ�� 2-�������ֵ 3-�͵�������ֵ 4-�͵�ѹ����ֵ
    float	m_fDfdt;		//Ƶ�ʻ���
    float	m_fFstart;		//Ƶ�ʱ仯ʼֵ
    float	m_fFend;		//Ƶ�ʱ仯��ֵ
    float	m_fFstep;		//Ƶ�ʱ仯����
    float	m_fHoldTime;	//����ʱ��
    float   m_fMarginTime;  //����ʱ��ԣ��

    float	m_fDfdtStart;	//����仯ʼֵ
    float	m_fDfdtEnd;		//����仯��ֵ
    float	m_fDfdtStep;	//����仯����
    int     m_nDfdtTiming;    //�����ʱ���ò���  0����ʼ����ݱ���Ϊ��ʱ��㣬1������ݱ䵽����ֵʱ��ʼ��ʱ  20240625Xuzt

    float	m_fIStart;		//�����仯ʼֵ
    float	m_fIEnd;		//�����仯��ֵ
    float	m_fIStep;		//�����仯����
    int		m_nIPhase;		//��������� 0:A��;1-B��;2-C��

    float	m_fUStart;		//��ѹ�仯ʼֵ
    float	m_fUEnd;		//��ѹ�仯��ֵ
    float	m_fUStep;		//��ѹ�仯����
    int		m_nUPhase;		//��ѹ�����

    float   m_fCurrSearchDfdt;//�м����,��ǰ�����Ļ���ֵ

    //ͨ�ò���
// 	float	m_fInom;	//�����
// 	float	m_fUnom;	//���ѹ
    float	m_fFnom;	//�Ƶ��
    float	m_fPreFaultTime;//����ǰʱ��
	int		m_nChangeMode;	//�仯ģʽ��0�����仯 1 ��ʱ��仯 
    float	m_fChangeTime;	//�仯ʱ�� ��ChangeMode==1ʱ��Ч

    //����ֵ
    float	m_fFAct;		//����Ƶ��
    float	m_fFActTime;	//����ʱ��
    float	m_fDfdtClose;	//�������ֵ
    float	m_fUlow;		//������ѹ
    float	m_fILow;		//��������
    int		m_nUSetMode;	//������ѹ����  0-���ѹ 1-�ߵ�ѹ VSetMode

    int		m_nBinLogic;	//�����߼�

    //Pvn����
    float   m_fUabc[6];//0-2����ǰ��3-5���Ϻ�
    float   m_fUabcPh[6];
    float   m_fIabc[6];
    float   m_fIabcPh[6];

    //������
    tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	//
    tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//

public:
    virtual void init()
    {
        m_nTestType = 0;
        m_fDfdt = 2.55f;
        m_fCurrSearchDfdt = 2.55f;
        m_fFstart = 48.65f;
        m_fFend = 48.35f;
        m_fFstep = 0.05f;
        m_fHoldTime = 1.2f;
        m_fMarginTime = 0;

        m_fDfdtStart = 3.3f;
        m_fDfdtEnd = 2.4f;
        m_fDfdtStep = 0.3f;
        m_nDfdtTiming = 0;

        m_fIStart = 0.8f;
        m_fIEnd = 1.2f;
        m_fIStep = 0.1f;
        m_nIPhase = 0;

        m_fUStart = 24;
        m_fUEnd = 36;
        m_fUStep = 1;
        m_nUPhase = 0;

        //ͨ�ò���
// 		m_fInom=0;
// 		m_fUnom=100;
        m_fFnom=50;
        m_fPreFaultTime = 5.0f;
        m_nChangeMode = 0;
        m_fChangeTime = 0.1f;

        //����ֵ
        m_fFAct = 48.5f;
        m_fFActTime = 1;
        m_fDfdtClose = 3;
        m_fUlow = 30;
        m_fILow = 1;
        m_nUSetMode = 1;
        m_nBinLogic = TMT_BINLOGIC_OR;

        float fAngle[3]={0,-120,120};
        for (int i=0;i<6;i++)
        {
            m_fUabc[i] = 57.74f;
            m_fIabc[i] = 0;
            m_fIabcPh[i] = m_fUabcPh[i] = fAngle[i%3];
        }

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

}tmt_LowFreqParas;

typedef struct tmt_low_freq_paras_ex :public tmt_LowFreqParas
{
public:
    char	m_pszDfdt[PARAS_RSLT_EXPR_LEN];		//Ƶ�ʻ���
    char	m_pszFstart[PARAS_RSLT_EXPR_LEN];		//Ƶ�ʱ仯ʼֵ
    char	m_pszFend[PARAS_RSLT_EXPR_LEN];		//Ƶ�ʱ仯��ֵ
    char	m_pszFstep[PARAS_RSLT_EXPR_LEN];		//Ƶ�ʱ仯����
    char	m_pszHoldTime[PARAS_RSLT_EXPR_LEN];	//����ʱ��

    char	m_pszDfdtStart[PARAS_RSLT_EXPR_LEN];	//����仯ʼֵ
    char	m_pszDfdtEnd[PARAS_RSLT_EXPR_LEN];		//����仯��ֵ
    char	m_pszDfdtStep[PARAS_RSLT_EXPR_LEN];	//����仯����

    char	m_pszIStart[PARAS_RSLT_EXPR_LEN];		//�����仯ʼֵ
    char	m_pszIEnd[PARAS_RSLT_EXPR_LEN];		//�����仯��ֵ
    char	m_pszIStep[PARAS_RSLT_EXPR_LEN];		//�����仯����

    char	m_pszUStart[PARAS_RSLT_EXPR_LEN];		//��ѹ�仯ʼֵ
    char	m_pszUEnd[PARAS_RSLT_EXPR_LEN];		//��ѹ�仯��ֵ
    char	m_pszUStep[PARAS_RSLT_EXPR_LEN];		//��ѹ�仯����


    virtual void init()
    {
        tmt_LowFreqParas::init();
		memset(m_pszDfdt,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFstart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFend,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszFstep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszHoldTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszHoldTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDfdtStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDfdtEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDfdtStep,0,PARAS_RSLT_EXPR_LEN);

		memset(m_pszIStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIStep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszUStep,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_LowFreqParasEx;

typedef struct tmt_low_freq_results
{
public:
    float	m_fLowFAct;
    float	m_fLowFActTime;
    float	m_fDfdtAct;
    float	m_fIAct;
    float	m_fUAct;
    long   m_nAct;//��������

public:
    virtual void init()
    {
        m_fLowFAct = 0.0f;
        m_fLowFActTime = 0.0f;
        m_fDfdtAct = 0.0f;
        m_fIAct = 0.0f;
        m_fUAct = 0.0f;
        m_nAct = 0.0f;
	} 

}tmt_LowFreqResults;

typedef struct tmt_low_freq_test : public TMT_PARAS_HEAD
{
public:
    tmt_LowFreqParasEx m_oLowFreqParas;
    tmt_LowFreqResults m_oLowFreqResults;
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqAct);
        m_nVersion = 0x00010001;
        m_nTestState = 0;
        memset(&m_oRsltExprMngr, 0, sizeof(TMT_PARAS_RSLT_EXPR_MNGR));

        m_oLowFreqParas.init();
        m_oLowFreqResults.init();
    }

	tmt_low_freq_test(){	init();}
	virtual void clear_result(){	m_oLowFreqResults.init();	}
	virtual ~tmt_low_freq_test(){}
}tmt_LowFreqTest;

typedef struct tmt_low_freq_time_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqTime);
    }

	tmt_low_freq_time_test(){	init();}
	virtual ~tmt_low_freq_time_test(){}
}tmt_LowFreqTimeTest;

typedef struct tmt_low_freq_dfdt_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqDfdt);
    }

	tmt_low_freq_dfdt_test(){	init();}
	virtual ~tmt_low_freq_dfdt_test(){}
}tmt_LowFreqDfDtTest;

typedef struct tmt_low_freq_ilock_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqILock);
    }

	tmt_low_freq_ilock_test(){	init();}
	virtual ~tmt_low_freq_ilock_test(){}
}tmt_LowFreqILockTest;

typedef struct tmt_low_freq_ulock_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowFreqULock);
    }

	tmt_low_freq_ulock_test(){	init();}
	virtual ~tmt_low_freq_ulock_test(){}
}tmt_LowFreqULockTest;

typedef struct tmt_low_freq_time_pnv_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowFreqTime);
    }

    tmt_low_freq_time_pnv_test(){	init();}
    virtual ~tmt_low_freq_time_pnv_test(){}
}tmt_LowFreqTimePnvTest;

typedef struct tmt_low_freq_act_pnv_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowFreqAct);
    }

    tmt_low_freq_act_pnv_test(){	init();}
    virtual ~tmt_low_freq_act_pnv_test(){}
}tmt_LowFreqActPnvTest;

typedef struct tmt_low_freq_dfdt_pnv_test : public tmt_LowFreqTest
{
public:
    virtual void init()
    {
        tmt_LowFreqTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowFreqDfdt);
    }

    tmt_low_freq_dfdt_pnv_test(){	init();}
    virtual ~tmt_low_freq_dfdt_pnv_test(){}
}tmt_LowFreqDfdtPnvTest;

void stt_init_paras(tmt_LowFreqParas *pParas);
void stt_init_paras_ex(tmt_LowFreqParasEx *pParas);
void stt_init_results(tmt_LowFreqResults *pResults);

void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqParas *pParas, CSttXmlSerializeBase *pXmlSierialize);


void stt_xml_serialize_PsuLowFreqAct_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqTime_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqDfDt_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqILock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqULock_ex(tmt_LowFreqParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);


void stt_xml_serialize_PsuLowFreqAct(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqDfDt(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqILock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowFreqULock(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqTime(tmt_LowFreqResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqAct(tmt_LowFreqResults *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowFreqDfdt(tmt_LowFreqResults *pParas, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_LowFreq_search_results(tmt_LowFreqParas *pParas,tmt_LowFreqResults *pResults,CSttXmlSerializeBase *pXmlSerialize);

void stt_xml_serialize_ex(tmt_LowFreqTest *pTests, CSttXmlSerializeBase *pXmlSerialize, BOOL bResultOnly=FALSE);



