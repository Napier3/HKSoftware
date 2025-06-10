#pragma once

#include "tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "../../SttDevice/RelayTest/drv_define.h"


#define MAX_STATE_COUNT		20
#define MAX_BINARYIN_COUNT	20//xupf 20190620 �޸�����Ϊ256��ԭ64���ڴ�Խ�紦��
#define MAX_BINARYOUT_COUNT	20//xupf 20190620 �޸�����Ϊ256��ԭ64���ڴ�Խ�紦��
#define MAX_VOLTAGE_COUNT	32
#define MAX_CURRENT_COUNT	32
#define MAX_GOOSEPUB_COUNT	16
#define MAX_GOOSE_CHANNEL_COUNT	256

#define MAX_PARACOUNT_BINARY 8
#define MAX_STATETEST_COUNT	6

#define pi 3.1415926536

//////////////////////////////////////////////////////////////////////////
// ״̬���в�����ز���
#define  TMT_MDSTATE_TIMETRIGGER                       0	    //0--ʱ�䴥��
#define  TMT_MDSTATE_TIMEBINTRIGGER                1    	//1--ʱ��+����������
#define  TMT_MDSTATE_BINTRIGGER                          2		//2--����������
#define  TMT_MDSTATE_MEARSURETRIGGER          3      //3--�ֶ�����
#define  TMT_MDSTATE_GPSBTRIGGER                      4		//4--GPS/B�봥��
#define  TMT_MDSTATE_LOWVOLTRIGGER                 5     //5--�͵�ѹ����


enum tmt_state_bin_reversal		// PSU ���뷭ת�ο�����:0��	1��	2��
{
	TMT_MDSTATE_BINRVS_SWITCH=0,	    //0--���뷭ת����
	TMT_MDSTATE_BINRVS_UP=1,			//1--���������ش���
	TMT_MDSTATE_BINRVS_DOWN=2,			//2--�����½��ش���
};

typedef struct tmt_state_gradient		// PSU ״̬�ڵݱ����
{
	int  iVar;			//�ݱ�ͨ��
	float fdfdt;        //df/dtֵ
	float fdvdt;        //dv/dtֵ
	float fTrigerV;		//������ѹ
	float fStep;        //�仯����
	float fStepTime;    //����ʱ��
	float fEnd;         //�仯��ֵ
	float fStart;       //��ͨ�ݱ�ʼֵ   

    void init()
    {
        iVar = 0;
       fdfdt=0;
        fdvdt=0;
        fStart=0;
        fEnd=0;
        fTrigerV=0;
        fStep=0;
        fStepTime=0;
    }

    tmt_state_gradient(){}
    virtual ~tmt_state_gradient(){}
}tmt_StateGradient;

typedef struct tmt_goose_pub
{
    BOOL m_bTest;// �Ƿ��ü���(0���ü���,1�ü���)
    CString m_strChannel[MAX_GOOSE_CHANNEL_COUNT];

    void init()
    {
        m_bTest=0;

        for(int nIndex=0;nIndex<MAX_GOOSE_CHANNEL_COUNT;nIndex++)
        {
            m_strChannel[nIndex] = "";
        }
    }

    tmt_goose_pub(){}
    virtual ~tmt_goose_pub(){}
}tmt_GoosePub;

typedef struct tmt_state_para
{
public:
    int		            m_nTriggerCondition;
    int		            m_nTrigJumpStateIndex;	//PSU ��������ת��״̬���
    float	            m_fTimeState;
    float	            m_fTimeAfterTrigger;	//��������ʱ
    tmt_time	    m_tGps;

	//������
	int		m_nBinLogic;			//0-�� 1-��
	int		m_nBinAndSelect;		// PSU	�����봥����Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0
    int		m_nBinOrSelect;			// PSU	����򴥷���Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0

    tmt_state_bin_reversal   m_eBinReversal;		//PSU ���뷭ת�ο�����:0�����뷭ת����	1�����������ش���	2�������½��ش���
    tmt_BinaryIn                        m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut                    m_binOut[MAX_BINARYOUT_COUNT];

	//ͨ��
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    float	                m_fVolAux;		// ����ֱ����ѹ����ģ�⣩
    float	                m_fCurAux;		// ����ֱ����������ģ�⣩
    BOOL	            m_bDC;			// �Ƿ�ֱ�����
    BOOL	            m_bTestMode;	// �Ƿ����ģʽ
    int		                m_nRampType;	// �ݱ�����
    int		                m_nRampTimeGrad;// �ݱ�ʱ��ֶ�
    tmt_StateGradient	m_sttGradient;

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_GOOSEPUB_COUNT];

    void init()
	{
        m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_fTimeState = 5;
		m_fTimeAfterTrigger = 0;
		m_nBinLogic = 0;
        m_fVolAux = 15;
		m_fCurAux = 0;

        // �ݱ����
        m_nRampType = 0;
        m_sttGradient.init();

        float fAng[3] = {0,-120,120};

        for (int j=0;j<3;j++)
        {
            m_uiVOL[j].Harm[1].fAmp = 57.74f;
            m_uiCUR[j].Harm[1].fAmp = 0;
            m_uiVOL[j].Harm[1].fAngle = m_uiCUR[j].Harm[1].fAngle = fAng[j];
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

        // �ݱ����
        m_nRampType = 0;
        m_sttGradient.init();

        for(int nIndex=0;nIndex<MAX_GOOSEPUB_COUNT;nIndex++)
            m_oGoosePub[nIndex].init();
	}

    tmt_state_para()	{}
    virtual ~tmt_state_para(){}

}tmt_StatePara;

typedef struct tmt_state_result
{
public://������
    float	m_frTestTime;							//ʵ������ʱ��
    float	m_frInTime;		//״̬����ʱ��
    float	m_frTimeStateBegin;
    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//ÿһ�������¼64�α�λʱ��
    float	m_frFlagBinAct[MAX_BINARYIN_COUNT][64];		//ÿһ�������¼64�α�λʱ��
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];

    void init()
    {
        m_frTestTime = 0;
        m_frInTime = 0;
        m_frTimeStateBegin = 0;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinAct[i][j] = 0;
                m_frFlagBinAct[i][j] = 0;
            }

            m_nrBinSwitchCount[i] = 0;
        }
    }

    tmt_state_result()	{}
    virtual ~tmt_state_result(){}
}tmt_StateResult;

typedef struct tmt_state_paras
{
public:
    int		         m_nStateNumbers;
    BOOL	     m_bRepeat;				//�Ƿ�ѭ�����
    int		         m_nRepeatNumbers;		//״̬���е��ظ�����
    int		         m_nBinTripRef;			//���뷭ת�ο�״̬ 0-��һ��״̬ 1-��һ��״̬
    BOOL	     m_bPlusDC;				//�Ƿ����ֱ������
    float	         m_fTao;					//ֱ��������˥��ʱ�䳣��: ����UIͨ������
    BOOL    	m_bSequence;			//�Ƿ�Ϊ˳��״̬����

    tmt_StatePara       m_paraState[MAX_STATE_COUNT];

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
            m_paraState[i].init();
        }
    }

    tmt_state_paras(){}
    virtual ~tmt_state_paras(){}
}tmt_StateParas;

typedef struct tmt_state_results
{
public:
    tmt_StateResult       m_resultState[MAX_STATE_COUNT];

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        for (int i=0;i<nStateNumbers;i++)
        {
            m_resultState[i].init();
        }
    }

    tmt_state_results(){}
    virtual ~tmt_state_results(){}
}tmt_StateResults;


typedef struct tmt_state_test
{
public:
    tmt_StateParas       m_oStateParas;
    tmt_StateResults   m_oStateResults;

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        m_oStateParas.init(nStateNumbers);
        m_oStateResults.init(nStateNumbers);
    }

    tmt_state_test()	{}
    virtual ~tmt_state_test(){}
}tmt_StateTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_StateTest();
void stt_init_paras(tmt_StateParas *pParas);
void stt_init_results(tmt_StateResults *pResults);
void stt_xml_serialize(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_StateResults *pResults,int nStateNums, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ChannelHarm &oChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize);
