#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"

typedef struct tmt_low_vol_paras 
{
public:
	//���ϲ���
	int		m_nTestType;	//�������� 0-��ѹ���ض���ֵ 1-����ʱ�� 2-��ѹ�����ֵ 3-�͵�������ֵ
	float	m_fDvdt;		//��ѹ����
	float	m_fVstart;		//��ѹ�仯ʼֵ
	float	m_fVend;		//��ѹ�仯��ֵ
	float	m_fVstep;		//��ѹ�仯����
	float	m_fHoldTime;	//����ʱ��
	int		m_nFaultType;	//��������

	float	m_fDvdtStart;	//����仯ʼֵ
	float	m_fDvdtEnd;		//����仯��ֵ
	float	m_fDvdtStep;	//����仯����
    int     m_nDvdtTiming;    //�����ʱ���ò���  0����ʼ����ݱ���Ϊ��ʱ��㣬1������ݱ䵽����ֵʱ��ʼ��ʱ

	float   m_fCurrSearchDvdt;//�м����,��ǰ�����Ļ���ֵ

	float	m_fIStart;		//�����仯ʼֵ
	float	m_fIEnd;		//�����仯��ֵ
	float	m_fIStep;		//�����仯����
	int		m_nIPhase;		//��������� 0:A��;1-B��;2-C��

	//ͨ�ò���
// 	float	m_fInom;	//�����
// 	float	m_fVnom;	//���ѹ
// 	float	m_fFnom;	//�Ƶ��
	float	m_fPreFaultTime;//����ǰʱ��
	int		m_nChangeMode;	//�仯ģʽ��0�����仯 1 ��ʱ��仯 
	float	m_fChangeTime;	//�仯ʱ�� ��ChangeMode==1ʱ��Ч

	//����ֵ
	float	m_fUAct;		//��ѹ����ֵ
	float	m_fUActTime;	//����ʱ��
	float	m_fDvdtClose;	//��ѹ�仯�ʱ���ֵ
	int		m_nUSetMode;	//������ѹ����  0-���ѹ 1-�ߵ�ѹ VSetMode
	float	m_fIAct;		//����

	int		m_nBinLogic;	//�����߼�

	//������
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	//
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];//

    //Pnv
    tmt_channel m_uiVOL[2][3];	//(����ǰ+����)*����ѹ��3
    tmt_channel m_uiCUR[2][3];
public:
	virtual void init()
	{
		m_fDvdt=68;
		m_fCurrSearchDvdt = 68;
		m_fVstart=49.5f;
		m_fVend=22.5f;
		m_fVstep=0.9f;
		m_fHoldTime=4.8f;
		m_nFaultType = 0;
		m_fDvdtStart = 88;
		m_fDvdtEnd = 68;
		m_fDvdtStep = 1.6f;
        m_nDvdtTiming = 0;

// 		m_fInom=0;
// 		m_fVnom=100;	//Ĭ��Ϊ�ߵ�ѹ
// 		m_fFnom=50;
		m_fPreFaultTime = 5.0f;
		m_nChangeMode = 0;
		m_fChangeTime = 0.1f;

		m_fUAct=45;
		m_fUActTime=4;
		m_fDvdtClose=80;
		m_nUSetMode=1;
		m_fIAct=1;

		m_fIStart = 0.8f;
		m_fIEnd = 1.2f;
		m_fIStep = 0.1f;
		m_nIPhase = 0;

		m_nBinLogic = TMT_BINLOGIC_OR;
        float fAngle[3]={0,-120,120};
        for(int i=0; i<2; i++)
        {
            for(int j=0; j<3; j++)
            {
                m_uiVOL[i][j].Harm[1].fAmp = 0;
                m_uiVOL[i][j].Harm[1].fAngle = fAngle[j];
                m_uiVOL[i][j].Harm[1].fFreq = 50;
                m_uiCUR[i][j].Harm[1].fAmp = 0;
                m_uiCUR[i][j].Harm[1].fAngle = fAngle[j];
                m_uiCUR[i][j].Harm[1].fFreq = 50;
            }
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

}tmt_LowVolParas;

typedef struct tmt_low_vol_paras_ex :public tmt_LowVolParas
{
public:
	char	m_pszDvdt[PARAS_RSLT_EXPR_LEN];		//��ѹ����
	char	m_pszVstart[PARAS_RSLT_EXPR_LEN];		//��ѹ�仯ʼֵ
	char	m_pszVend[PARAS_RSLT_EXPR_LEN];		//��ѹ�仯��ֵ
	char	m_pszVstep[PARAS_RSLT_EXPR_LEN];		//��ѹ�仯����
	char	m_pszHoldTime[PARAS_RSLT_EXPR_LEN];	//����ʱ��
	char	m_pszDvdtStart[PARAS_RSLT_EXPR_LEN];	//����仯ʼֵ
	char	m_pszDvdtEnd[PARAS_RSLT_EXPR_LEN];		//����仯��ֵ
	char	m_pszDvdtStep[PARAS_RSLT_EXPR_LEN];	//����仯����

	char	m_pszIStart[PARAS_RSLT_EXPR_LEN];		//�����仯ʼֵ
	char	m_pszIEnd[PARAS_RSLT_EXPR_LEN];		//�����仯��ֵ
	char	m_pszIStep[PARAS_RSLT_EXPR_LEN];		//�����仯����

	virtual void init()
	{
		tmt_LowVolParas::init();
		memset(m_pszDvdt,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszVstart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszVend,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszVstep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszHoldTime,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDvdtStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDvdtEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszDvdtStep,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIStart,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIEnd,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIStep,0,PARAS_RSLT_EXPR_LEN);
	} 
}tmt_LowVolParasEx;

typedef struct tmt_low_vol_results
{
public:
	//�������
	float	m_fLowUAct;
	float	m_fLowUActTime;
	float	m_fDvdtAct;
	float	m_fIAct;

	long   m_nAct;//��������


public:
	virtual void init()
	{
		m_fLowUAct = 0.0f;
		m_fLowUActTime = 0.00f;
		m_fDvdtAct = 0.0f;
		m_fIAct = 0.0f;
		m_nAct = 0;
	} 

}tmt_LowVolResults;

typedef struct tmt_low_vol_test : public TMT_PARAS_HEAD
{
public:
	tmt_LowVolParasEx m_oLowVolParas;
	tmt_LowVolResults m_oLowVolResults;
	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolAct);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oLowVolParas.init();
		m_oLowVolResults.init();
	}

	tmt_low_vol_test(){	init();}
	virtual void clear_result(){	m_oLowVolResults.init();	}
	virtual ~tmt_low_vol_test(){}
}tmt_LowVolTest;

typedef struct tmt_low_vol_time_test : public tmt_LowVolTest
{
public:
	virtual void init()
	{
		tmt_LowVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolTime);
	}

	tmt_low_vol_time_test(){	init();}
	virtual ~tmt_low_vol_time_test(){}
}tmt_LowVolTimeTest;

typedef struct tmt_low_vol_dvdt_test : public tmt_LowVolTest
{
public:
	virtual void init()
	{
		tmt_LowVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolDvdt);
	}

	tmt_low_vol_dvdt_test(){	init();}
	virtual ~tmt_low_vol_dvdt_test(){}
}tmt_LowVolDvDtTest;

typedef struct tmt_low_vol_pnv_test : public TMT_PARAS_HEAD
{
public:
    tmt_LowVolParas m_oLowVolParas;
    tmt_LowVolResults m_oLowVolResults;
    virtual void init()
    {
        init_head(); //20210918 zhouhj
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowVolAct);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oLowVolParas.init();
        m_oLowVolResults.init();
    }

    tmt_low_vol_pnv_test(){	init();}
    virtual void clear_result(){	m_oLowVolResults.init();	}
    virtual ~tmt_low_vol_pnv_test(){}
}tmt_PnvLowVolTest;

typedef struct tmt_low_vol_ilock_test : public tmt_LowVolTest
{
public:
	virtual void init()
	{
		tmt_LowVolTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuLowVolILock);
	}

	tmt_low_vol_ilock_test(){	init();}
	virtual ~tmt_low_vol_ilock_test(){}
}tmt_LowVolILockTest;

typedef struct tmt_low_vol_time_pnv_test : public tmt_PnvLowVolTest
{
public:
    virtual void init()
    {
        tmt_PnvLowVolTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowVolTime);
    }

    tmt_low_vol_time_pnv_test(){	init();}
    virtual ~tmt_low_vol_time_pnv_test(){}
}tmt_LowVolTimePnvTest;

typedef struct tmt_low_vol_dvdt_pnv_test : public tmt_PnvLowVolTest
{
public:
    virtual void init()
    {
        tmt_PnvLowVolTest::init();
        strcpy(m_pszMacroID, STT_MACRO_ID_PnvLowVolDvdt);
    }

    tmt_low_vol_dvdt_pnv_test(){	init();}
    virtual ~tmt_low_vol_dvdt_pnv_test(){}
}tmt_LowVolDvDtPnvTest;
void stt_init_paras(tmt_LowVolParas *pParas);
void stt_init_paras_ex(tmt_LowVolParasEx *pParas);
void stt_init_results(tmt_LowVolResults *pResults);

void stt_xml_serialize_PsuLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolILock(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_PnvLowVolAct(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolTime(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolParas *pParas, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_PsuLowVolAct_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolTime_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolDvDt_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolILock_ex(tmt_LowVolParasEx *pParas, CSttXmlSerializeBase *pXmlSierialize);


void stt_xml_serialize_PsuLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PsuLowVolILock(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_PnvLowVolAct(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolTime(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_PnvLowVolDvDt(tmt_LowVolResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_LowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_PnvLowVolTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_LowVol_search_results(tmt_LowVolParas *pParas,tmt_LowVolResults *pResults,CSttXmlSerializeBase *pXmlSerialize);



