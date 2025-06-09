#pragma once
#include "tmt_state_test.h"

#ifdef _PSX_IDE_QT_
#include "IEC61850CfgMngr.h"
#endif


enum tmt_smv_abnormal_type
{
    TYPE_SMV_NORMAL = 0,
    TYPE_SMV_LOST   = 1,
    TYPE_SMV_JITTE  = 2,
    TYPE_SMV_FLYPOINT = 3,
    TYPE_SMV_ERRCMPT  = 4,
    TYPE_SMV_DELAYOFFSET = 5,
    TYPE_SMV_DELAYMODEFY = 6,
    TYPE_SMV_INDEXERR = 7,
    TYPE_SMV_QUALITYERR = 8
};//0 ������1 ��֡��2 ������3 �ɵ㣻4 ����5 ��ʱƫ�6 ��ʱ�仯��7 ���ƫ���8 Ʒ�ʴ���

enum tmt_SyncMode
{
	NO_SYNC_MODE = 0,
	LOCAL_SYNC_MODE = 1,
	GLOBAL_SYNC_MODE = 2
};//��ͬ��������ͬ����ȫ��ͬ��

enum tmt_abnormal_type
{
    TYPE_NORMAL = 0,
    TYPE_SMV_ABNORMAL = 1,
    TYPE_GOOSE_ABNORMAL = 2
};//��ͬ��������ͬ����ȫ��ͬ��


//typedef struct tmt_61850_9_2_setting
//{
//    CString strSrcMac;//Դmac
//    CString strDestMac;//Ŀ��mac
//    int           nVlanID;//VLANID
//    int           nVlanPriority;//VLAN���ȼ�
//    int           nNetFlag;//�����ʶ
//    int           nAppID;//appid
//    tmt_SyncMode nSyncMode;//ͬ����ʽ
//    int     nVerNo;//�汾��
//    int     nSamplingDelayTime;//������ʱ
//    CString strDataSet;//���ݼ�
//    CString strSVID;//SVID
//    BOOL    bRefrTm;//δ֪
//}tmt_Iec61850_9_2Setting;

enum tmt_SendType
{
	TYPE_CIRCLE = 0,
	TYPE_SECOND = 1
};//�ܲ����ͣ����뷢��

typedef struct tmt_SvQlty_Set
{
    int nValid;//bit0-1: 00-��, 01-��Ч, 10-������ 11-����
    BOOL bOverflow;//�����   ���
    BOOL bOutRange;//����   ��ֵ��
    BOOL bBadBmVal;//���� ����׼ֵ
    BOOL bJitter;//�޶���    ����
    BOOL bFault;//�޹���   ����
    BOOL bOldDataOT;//�޳�ʱ   ���ݳ�ʱ
    BOOL bInconformity;//һ��  ��һ��
    BOOL bImprecise;//��ȷ    ����ȷ
    BOOL bSrc;//����    ��ȡ��
    BOOL bTest;//����    ����
    BOOL bOprLock;//����Ա����

    void init()
    {
        nValid = 0;
        bOverflow = false;
        bOutRange = false;
        bBadBmVal = false;
        bJitter = false;
        bFault = false;
        bOldDataOT = false;
        bInconformity = false;
        bImprecise = false;
        bSrc = false;
        bTest = false;
        bOprLock = false;
    }
    tmt_SvQlty_Set()	{}
    virtual ~tmt_SvQlty_Set(){}
}tmt_SvQltySet;

typedef struct tmt_smv_abnormal
{
    int nAbnType;//ʲô��ʽ���쳣
//	int nLoseStep;//ʧ����
//Ʒ���쳣
	int nQualityInvalid;//Ʒ�ʣ�ÿbit�ĺ���
//	int nTestMode;//����
    BOOL bQltyInvChannel[50];//50��Ʒ��ͨ��
    tmt_SvQltySet QltySet;
	
	float fOffsetTime;//��ʱƫ�
//	float fModefyTime;//��ʱ�仯��
	float fDelayTime;//��ʱʱ��
	
	float fFlyPointVolt;//�ɵ��ѹֵ
	float fFlyPointCur;//�ɵ����ֵ
    BOOL bVolFly[MAX_VOLTAGE_COUNT];//�ɵ��ѹʹ��
    BOOL bCurFly[MAX_CURRENT_COUNT];//�ɵ����ʹ��
//	unsigned int nJitterDirection;//��������Ĭ�ϵ���
	unsigned int nJitter;//����ֵ
	int nErrCmpt;//����--����ֵ��
	int nErrIndex;//���ƫ��ֵ
	//��������
	BOOL bSVAbnSet[80];//80���쳣��ʹ��

#ifdef _PSX_IDE_QT_
	tmt_sv_92 oIec61850_9_2Msg;
#endif

	int nSvGroupSel;//����ѡ��
    tmt_SendType nInvDataSndTyp;//�쳣���ݷ��ͷ�ʽ0-���ܲ�����   1-���뷢��
	unsigned int nCircle;//�����ܲ���
	unsigned int nCirclePerSecond;//ÿ�뷢���ܲ���
	unsigned int nHoldTime;//����ʱ�䣬type���뷢��ʱ����Ч	

    void init()
    {
        QltySet.init();
        nAbnType = 0;
        fOffsetTime = 0.0f;
        fDelayTime = 0.0f;
        fFlyPointVolt = 0.0f;
        fFlyPointCur = 0.0f;
        for(int i = 0; i<MAX_VOLTAGE_COUNT; i++)
        {
            bVolFly[i] = false;
            bCurFly[i] = false;
        }
        nJitter = 0.0f;
        nErrCmpt = 0.0f;
        nErrIndex = 0.0f;
        nSvGroupSel = 0;
        nInvDataSndTyp = TYPE_CIRCLE;
        nCircle = 0;
        nCirclePerSecond = 0;
        nHoldTime = 0;

        for(int i=0; i<50; i++)
        {
            bQltyInvChannel[i] = false;
        }

        for(int i=0; i<80; i++)
        {
            bSVAbnSet[i] = false;
        }
    }
    tmt_smv_abnormal()	{init();}
    virtual ~tmt_smv_abnormal(){}
}tmt_SmvAbnormal;

typedef struct tmt_goose_abnormal
{
	CString strSrcMac;//Դmac
	CString strDestMac;//Ŀ��mac
	CString strGcRef;
	CString strGoID;
	CString strDataSet;
	int     nVerNo;//�汾��
	int     nSt;
	int     nSq;
	int     nTTL;
	int     nAppID;
	BOOL    bEntrust;//ί��
    BOOL    bTest;//null
	int     nVlanID;
    int     nNetFlag;//null
	int     nVlanPriority;
	int     nTimeQlty;

    tmt_goose_abnormal()	{}
    virtual ~tmt_goose_abnormal(){}
}tmt_GooseAbnormal;

//enum tmt_state_bin_reversal		// PSU ���뷭ת�ο�����:0��	1��	2��
//{
//	TMT_MDSTATE_BINRVS_SWITCH=0,	    //0--���뷭ת����
//	TMT_MDSTATE_BINRVS_UP=1,			//1--���������ش���
//	TMT_MDSTATE_BINRVS_DOWN=2,			//2--�����½��ش���
//};

typedef struct tmt_abnstate_para
{
public:
    int                         m_nTriggerCondition;    //��������
    int                         m_nTrigJumpStateIndex;	//PSU ��������ת��״̬���
	tmt_state_bin_reversal   m_eBinReversal;//PSU ���뷭ת�ο�����:0�����뷭ת����	1�����������ش���	2�������½��ش���
    float                     m_fTimeState;//���ʱ��
    float                     m_fTimeAfterTrigger;	//��������ʱ
    tmt_time           m_tGps;
	//������
    int		          		   m_nBinLogic;			//0-�� 1-��
    int		   				   m_nBinAndSelect;		// PSU	�����봥����Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0
    int		   				   m_nBinOrSelect;		// PSU	����򴥷���Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0
    tmt_BinaryIn      m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut  m_binOut[MAX_BINARYOUT_COUNT];
	//ͨ��
	tmt_channel         m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel         m_uiCUR[MAX_CURRENT_COUNT];	


    int                                       m_nAbnormalType;//0 ���� ��SV�쳣��goose�쳣ģ��
    tmt_SmvAbnormal     m_smvAbnormalPara;

#ifdef _PSX_IDE_QT_
	tmt_goose m_gooseAbnormalPara;
#endif


    BOOL	            m_bDC;			// �Ƿ�ֱ�����
    void init()
	{
        m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_fTimeState = 5;
		m_fTimeAfterTrigger = 0;
		m_nBinLogic = 0;
        m_nAbnormalType = 0;
        m_bDC = false;
        float fAng[3] = {0,-120,120};
        for (int j=0;j<6;j++)
        {
            m_uiVOL[j].Harm[1].fAmp = 57.74f;
            m_uiCUR[j].Harm[1].fAmp = 0;
            m_uiVOL[j].Harm[1].fAngle = m_uiCUR[j].Harm[1].fAngle = fAng[j%3];
            m_uiVOL[j].Harm[1].fFreq = m_uiCUR[j].Harm[1].fFreq = 50;
        }

        for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
        {
            m_binOut[j].nState = 0;
            m_binOut[j].nMode = 0;
            m_binOut[j].fTimeTrig = 0;
            m_binOut[j].fHoldTime = 0;
            if(j<MAX_PARACOUNT_BINARY)
            {
                m_binIn[j].nSelect = 1;
            }
            else
            {
                m_binIn[j].nSelect = 0;
            }
            m_binIn[j].nTrigMode = 0;
        }
        m_nBinLogic = 0;
	}
    tmt_abnstate_para()	{}
    virtual ~tmt_abnstate_para(){}
}tmt_AbnStatePara;

typedef struct tmt_abnsimulation_paras
{
public:
    int         m_nStateNumbers;
    BOOL   m_bRepeat;				//�Ƿ�ѭ�����
    int		   m_nRepeatNumbers;		//״̬���е��ظ�����
    int		   m_nBinTripRef;			//���뷭ת�ο�״̬ 0-��һ��״̬ 1-��һ��״̬
    BOOL   m_bPlusDC;				//�Ƿ����ֱ������
    float	   m_fTao;			//ֱ��������˥��ʱ�䳣��: ����UIͨ������
    BOOL   m_bSequence;			//�Ƿ�Ϊ˳��״̬����

    tmt_AbnStatePara       m_AbnStatepara[MAX_STATE_COUNT];

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        m_nStateNumbers = nStateNumbers;
        m_bRepeat = FALSE;
        m_nRepeatNumbers = 0;
        m_nBinTripRef = 1;
        m_bPlusDC = FALSE;
        m_fTao = 0;
        m_bSequence = true;

        for (int i=0;i<m_nStateNumbers;i++)
        {
            m_AbnStatepara[i].init();
        }
    }

    tmt_abnsimulation_paras(){}
    virtual ~tmt_abnsimulation_paras(){}
}tmt_AbnsimulationParas;

typedef struct tmt_abnsimulation_test
{
public:
    tmt_AbnsimulationParas       m_oAbnSimulationParas;
    tmt_StateResults   m_oStateResults;

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        m_oAbnSimulationParas.init(nStateNumbers);
        m_oStateResults.init(nStateNumbers);
    }

    tmt_abnsimulation_test()	{}
    virtual ~tmt_abnsimulation_test(){}
}tmt_AbnSimulationTest;




/////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize_write_AbnStateTest();
void stt_init_paras(tmt_AbnsimulationParas *pParas);
//void stt_init_results(tmt_StateResults *pResults);
void stt_xml_serialize(tmt_AbnsimulationParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//void stt_xml_serialize(tmt_StateResults *pResults,int nStateNums, CSttXmlSerializeBase *pXmlSierialize);







