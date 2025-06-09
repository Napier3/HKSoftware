#pragma once

#include "../Common/tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"

#define MAX_STATE_COUNT			20
#define MAX_GOOSEPUB_COUNT		16
#define MAX_GOOSE_CHANNEL_COUNT	256
#define MAX_STATETEST_COUNT		6

//////////////////////////////////////////////////////////////////////////
// ״̬���в�����ز���
#define  TMT_MDSTATE_TIMETRIGGER                   0	    //0--ʱ�䴥��
#define  TMT_MDSTATE_TIMEBINTRIGGER                1    	//1--ʱ��+����������
#define  TMT_MDSTATE_BINTRIGGER                    2		//2--����������
#define  TMT_MDSTATE_MEARSURETRIGGER			   3		//3--�ֶ�����
#define  TMT_MDSTATE_GPSBTRIGGER                   4		//4--GPS/B�봥��
#define  TMT_MDSTATE_LOWVOLTRIGGER                 5		//5--�͵�ѹ����

enum tmt_state_bin_reversal		// PSU ���뷭ת�ο�����:0��	1��	2��
{
	TMT_MDSTATE_BINRVS_SWITCH=0,	    //0--���뷭ת����
	TMT_MDSTATE_BINRVS_UP=1,			//1--���������ش���
	TMT_MDSTATE_BINRVS_DOWN=2,			//2--�����½��ش���
};

enum tmt_state_gradient_type
{
	TMT_STATE_GRADIENT_NONE=0,
	TMT_STATE_GRADIENT_DFDT=1,			//��Ƶ��
	TMT_STATE_GRADIENT_DVDT=2,			//����ѹ
	TMT_STATE_GRADIENT_DFDVDT=3,		//���Ƶ�ʡ���ѹ
	TMT_STATE_GRADIENT_COMMON=4,		//��ͨ
};

typedef struct tmt_state_gradient		//PSU ״̬�ڵݱ����
{
	int  iVar;			//�ݱ�ͨ��
	float fdfdt;        //df/dtֵ
	float fdvdt;        //dv/dtֵ
	float fTrigerV;		//������ѹ
	float fEndV;		//��ֹ��ѹ
	float fStartF;		//��ʼƵ��
	float fEndF;		//��ֹƵ��
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
        fStep=1;
        fStepTime=0.5;
		fEndV=0;
		fStartF=0;
		fEndF=0;
    }

    tmt_state_gradient()
	{	
		init(); 
	}
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

    tmt_goose_pub()
	{ 
		init(); 
	}
    virtual ~tmt_goose_pub(){}
}tmt_GoosePub;

typedef struct tmt_state_para
{
public:
	bool		 m_bSelected;			//״̬�Ƿ�ѡ
    int		     m_nTriggerCondition;
    int		     m_nTrigJumpStateIndex;	//PSU ��������ת��״̬���
    float	     m_fTimeState;
    float	     m_fTimeAfterTrigger;	//��������ʱ
    tmt_time	 m_tGps;

	//������
	int		m_nBinLogic;			//0-�� 1-��
	int		m_nBinAndSelect;		//PSU�����봥����Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0
    int		m_nBinOrSelect;			//PSU����򴥷���Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0

    tmt_state_bin_reversal   m_eBinReversal;//PSU ���뷭ת�ο�����:0�����뷭ת����	1�����������ش���	2�������½��ش���
    tmt_BinaryIn   m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut  m_binOut[MAX_BINARYOUT_COUNT];

	//ͨ��
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    float	    m_fVolAux;			// ����ֱ����ѹ����ģ�⣩
    float	    m_fCurAux;			// ����ֱ����������ģ�⣩
	float       m_fOutputHoldTime;	// ����������ʱ�䣨������תʱ�䣩
    BOOL	    m_bDC;				// �Ƿ�ֱ�����
    BOOL	    m_bTestMode;		// �Ƿ����ģʽ
    int		    m_nRampType;		// �ݱ�����
    int		    m_nRampTimeGrad;	// �ݱ�ʱ��ֶ�
    tmt_StateGradient	m_sttGradient;

    //GoosePub
    tmt_GoosePub m_oGoosePub[MAX_GOOSEPUB_COUNT];

    void init()
	{
		m_bSelected = true;
        m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_fTimeState = 5;
		m_fTimeAfterTrigger = 0;
		m_fOutputHoldTime = 0;
		m_nBinLogic = 0;       
		m_nBinAndSelect = 0;
		m_nBinOrSelect = 0;
		m_bDC = 0;
		m_fVolAux = 0;
		m_fCurAux = 0;
		m_bTestMode = false;
		m_nRampType = TMT_STATE_GRADIENT_NONE;
		m_nRampTimeGrad = 0;

        float fAng[3] = {0,-120,120};

		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
        {
            m_uiVOL[j].Harm[1].fAmp = 57.74f;
			m_uiVOL[j].Harm[1].fAngle = fAng[j%3];
			m_uiVOL[j].Harm[1].fFreq  = 50;
        }

		for (int j=0;j<MAX_CURRENT_COUNT;j++)
        {
            m_uiCUR[j].Harm[1].fAmp = 0;
			m_uiCUR[j].Harm[1].fAngle = fAng[j%3];
			m_uiCUR[j].Harm[1].fFreq = 50;
        }

		for (int j=0;j<MAX_BINARYIN_COUNT;j++)
		{
			m_binIn[j].nSelect = 0;
			m_binIn[j].nTrigMode = 0;
			
			if(j<MAX_PARACOUNT_BINARY)
			{
				m_binIn[j].nSelect = 1;
			}
			else
			{
				m_binIn[j].nSelect = 0;
			}
		}

        for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
        {
            m_binOut[j].nState = 0;
            m_binOut[j].nMode = 0;
            m_binOut[j].fTimeTrig = 0;
            m_binOut[j].fHoldTime = 0;
        }

        m_nBinLogic = 0;

        // �ݱ����
        m_nRampType = 0;
        m_sttGradient.init();

        for(int nIndex=0;nIndex<MAX_GOOSEPUB_COUNT;nIndex++)
            m_oGoosePub[nIndex].init();
	}

    void setDC(bool bDC)
	{
		m_bDC = bDC;
		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
		{
			m_uiVOL[j].Harm[1].bDC = bDC;
			if (bDC)
			{
				m_uiVOL[j].Harm[1].fAngle = 0;
				m_uiVOL[j].Harm[1].fFreq = 0;
			}
		}

		for (int j=0;j<MAX_CURRENT_COUNT;j++)
		{
			m_uiCUR[j].Harm[1].bDC = bDC;
			if (bDC)
			{
				m_uiCUR[j].Harm[1].fAngle = 0;
				m_uiCUR[j].Harm[1].fFreq = 0;
			}
		}
	}

    tmt_state_para()	
	{	
		init(); 
	}
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

    tmt_state_result()	
	{ 
		init(); 
	}
    virtual ~tmt_state_result(){}
}tmt_StateResult;

typedef struct tmt_state_paras
{
public:
    int		m_nStateNumbers;
    BOOL	m_bRepeat;				//�Ƿ�ѭ�����
    int		m_nRepeatNumbers;		//״̬���е��ظ�����
    int		m_nBinTripRef;			//���뷭ת�ο�״̬ 0-��һ��״̬ 1-��һ��״̬
    BOOL	m_bPlusDC;				//�Ƿ����ֱ������
    float	m_fTao;					//ֱ��������˥��ʱ�䳣��: ����UIͨ������
    BOOL    m_bSequence;			//�Ƿ�Ϊ˳��״̬����

    tmt_StatePara m_paraState[MAX_STATE_COUNT];

	void initCommon()
	{
		m_bRepeat = FALSE;
		m_nRepeatNumbers = 0;
		m_nBinTripRef = 1;
		m_bPlusDC = FALSE;
		m_fTao = 0;
		m_bSequence = TRUE;
	}

    void init(long nStateNumbers = MAX_STATE_COUNT)
    {
        m_nStateNumbers = nStateNumbers;

        for (int i=0;i<m_nStateNumbers;i++)
        {
            m_paraState[i].init();
        }
    }

	void SetSelect(int nIndex,bool bSel)
	{
		if (nIndex >= 0 && nIndex < MAX_STATE_COUNT)
		{
			m_paraState[nIndex].m_bSelected = bSel;
		}
	}

	int GetSelCount()
	{
		int nCnt = 0;
		for (int i=0; i < m_nStateNumbers; i++)
		{
			if (m_paraState[i].m_bSelected)
			{
				nCnt++;
			}
		}
		return nCnt;
	}

    tmt_state_paras(){
		initCommon();
	}

    virtual ~tmt_state_paras(){}
}tmt_StateParas;

typedef struct tmt_state_results
{
public:
    tmt_StateResult  m_resultState[MAX_STATE_COUNT];

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
    tmt_StateParas     m_oStateParas;
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

void stt_xml_serialize_ex(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,bool bSel);

tmt_StatePara* stt_state_paras_insert_after(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nAfter);
tmt_StatePara* stt_state_paras_insert_before(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nBefore);
void stt_state_paras_delete(tmt_StateParas *pParas, int nIndex);
void stt_xml_serialize_dc(tmt_ChannelHarm &oChannel, CSttXmlSerializeBase *pXmlSierialize);