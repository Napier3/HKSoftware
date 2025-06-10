#pragma once

#include "tmt_common_def.h"
#include "../../SttTestBase/SttXmlSerialize.h"
#include "tmt_test_paras_head.h"
#include "Abnormal/tmt_abnormal_test.h"

#define STATE_INIT_COUNT	6

//////////////////////////////////////////////////////////////////////////
//�����첽ͬ��״̬���й�ͬʹ����ش�����ʽ�궨�壬��������tmt_common_def.h

// ״̬���в�����ز���
//#define  TMT_MDSTATE_TIMETRIGGER                       0	    //0--ʱ�䴥��
//#define  TMT_MDSTATE_TIMEBINTRIGGER                1    	//1--ʱ��+����������
//#define  TMT_MDSTATE_BINTRIGGER                          2		//2--����������
//#define  TMT_MDSTATE_MEARSURETRIGGER          3      //3--�ֶ�����
//#define  TMT_MDSTATE_GPSBTRIGGER                      4		//4--GPS/B�봥��
//#define  TMT_MDSTATE_LOWVOLTRIGGER                 5     //5--�͵�ѹ����


#define  STT_IMPEDANCE_BIN_STATE_SINGLE                                 0 //��������Ϊ������բ
#define  STT_IMPEDANCE_BIN_STATE_THREE                                  1//��������Ϊ������բ
#define  STT_IMPEDANCE_BIN_STATE_RECLOCE                                2//��������Ϊ�غ�բ

//#define  MAX_STATE_NAME			128  //zhouhj 20211208 ����GOOSE�쳣ģ���״̬���������г��ȿ��ܳ���32�ֽ� �����Ϊ128

//2024-3-27 xuzhantao  Pnv��ֲ�ж���UI����������Ϊһ���������ú�����
#define  STT_PNV_STATE_6U6I         0
#define  STT_PNV_STATE_4U3I         1


enum tmt_state_gradient_type
{
	TMT_STATE_GRADIENT_NONE=0,
	TMT_STATE_GRADIENT_DFDT=1,			//��Ƶ��
	TMT_STATE_GRADIENT_DVDT=2,			//����ѹ
	TMT_STATE_GRADIENT_DFDVDT=3,		//���Ƶ�ʡ���ѹ
	TMT_STATE_GRADIENT_COMMON=4,		//��ͨ
};

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
}tmt_StateGradient;

typedef struct tmt_state_close_angle		// ��բ�ǲ���  zhouhj 20211015 �����迹��߼�ģ��
{
	int   m_nFaultIncMode;		//��բ��ѡ�� 0-��� 1-��ֵ  //zhouhj 20211015 ���������迹��ĺ�բ������
	float m_fCurCloseAngle;//������բ��
	float m_fVolCloseAngle;//��ѹ��բ��
	float m_fRefCloseAngle;//�������õ��Զ����բ��
	int   m_nCloseChannel;//��բͨ��

	void init()
	{
		m_nFaultIncMode = 0;
		m_fCurCloseAngle = 0;
		m_fVolCloseAngle=0;
		m_fRefCloseAngle=0;
		m_nCloseChannel=0;
	}

	tmt_state_close_angle()
	{	
		init(); 
	}
}tmt_StateCloseAngle;

typedef struct tmt_state_para
{
public:
	BOOL		 m_bSelected;			//״̬�Ƿ�ѡ
	BOOL	     m_bPlusDC;				//�Ƿ����ֱ������
	float				m_fTao;					//ֱ��������˥��ʱ�䳣��: ����UIͨ������
    int		            m_nTriggerCondition;
    int		            m_nTrigJumpStateIndex;	//PSU ��������ת��״̬���
    float	            m_fTimeState;
    float	            m_fTimeAfterTrigger;	//��������ʱ
    tmt_time	    m_tGps;
	char         m_strName[MAX_STATE_NAME];		//״̬���ƣ�Ĭ�����16������
	char         m_strID[MAX_STATE_ID];         //dingxy 202408 ״̬id��Ĭ�������State99,���ڱ������

	//������
	int		m_nBinLogic;			//0-�� 1-��
	int		m_nBinAndSelect;		// PSU	�����봥����Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0
    int		m_nBinOrSelect;			// PSU	����򴥷���Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0

	long	m_nBinaryOutType;//0-����+Gse,1-ֻ�п���,2-ֻ��Gse
    tmt_state_bin_reversal   m_eBinReversal;		//PSU ���뷭ת�ο�����:0�����뷭ת����	1�����������ش���	2�������½��ش���
	tmt_BinaryIn             m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut            m_binOut[MAX_BINARYOUT_COUNT];
	tmt_BinaryIn             m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut            m_binOutEx[MAX_ExBINARY_COUNT];

	//ͨ��
	tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
	tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    float	                m_fVolAux;		// ����ֱ����ѹ����ģ�⣩
//    float	                m_fCurAux;		// ����ֱ����������ģ�⣩
	float       m_fOutputHoldTime;	// ����������ʱ�䣨������תʱ�䣩
	BOOL	    m_bDC;			// �Ƿ�ֱ�����
    BOOL	            m_bTestMode;	// �Ƿ����ģʽ
    int		                m_nRampType;	// �ݱ�����
	int		                m_nRampTimeGrad;// �ݱ�ʱ��ֶȺ���
    tmt_StateGradient	m_sttGradient;

	tmt_StateCloseAngle   m_oCloseAngle;		//��բ��ѡ�� 0-��� 1-��ֵ  //zhouhj 20211015 ���������迹��ĺ�բ������

    //GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];
    //Ft3Pub
    tmt_Ft3Pub  m_oFt3Pub[MAX_MODULES_FT3PUB_COUNT];

	tmt_StateAbnormalSMV m_oAbnormalSMV;
	tmt_StateAbnormalGOOSE m_oAbnormalGOOSE;

    void init()
	{
		m_bSelected = true;
		m_bPlusDC = FALSE;
		m_fTao = 0;
        m_nTriggerCondition = TMT_MDSTATE_TIMETRIGGER;
		m_fTimeState = 5;
		m_fTimeAfterTrigger = 0;
		m_fOutputHoldTime = 0;
		m_nBinLogic = TMT_BINLOGIC_OR;
		m_nBinAndSelect = 0;
		m_nBinOrSelect = 0;
		m_nBinaryOutType = 0;
		m_bDC = 0;
      m_fVolAux = 0;
//		m_fCurAux = 0;
		m_bTestMode = false;
//		m_nRampType = TMT_STATE_GRADIENT_NONE;
		m_nRampTimeGrad = 0;
		memset(m_strName, 0, MAX_STATE_NAME);
		memset(m_strID, 0, MAX_STATE_ID);

		m_oCloseAngle.init();
		m_oAbnormalSMV.init();
		m_oAbnormalGOOSE.init();

        // �ݱ����
        m_nRampType = 0;
        m_sttGradient.init();

        float fAng[3] = {0,-120,120};

		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
        {
			for(int k=0;k<MAX_HARM_COUNT;k++)
			{
				m_uiVOL[j].Harm[k].m_bSelect=FALSE;
				m_uiVOL[j].Harm[k].fAmp = 0;
				m_uiVOL[j].Harm[k].fAngle =  fAng[j%3];
				m_uiVOL[j].Harm[k].fFreq =  50;

				m_uiCUR[j].Harm[k].m_bSelect=FALSE;
				m_uiCUR[j].Harm[k].fAmp = 0;
				m_uiCUR[j].Harm[k].fAngle = fAng[j%3];
				m_uiCUR[j].Harm[k].fFreq = 50;
			}

			for (int nRampIndex = 0;nRampIndex < 3;nRampIndex++)
			{
				m_uiVOL[j].Ramp[nRampIndex].init();
				m_uiCUR[j].Ramp[nRampIndex].init();
			}
        }

		for (int j=0;j<MAX_BINARYIN_COUNT;j++)
        {
			m_binIn[j].nSelect = 0;
			m_binIn[j].nTrigMode = 0;

#ifdef _STT_NOT_IN_TEST_SERVER_
            if(j<g_nBinCount)
            {
                m_binIn[j].nSelect = 1;
            }
#endif
		}

        for (int j=0;j<MAX_BINARYOUT_COUNT;j++)
        {
			m_binOut[j].init();
        }

        for(int j = 0; j < g_nBinExCount && j < MAX_ExBINARY_COUNT; j++)
        {
			m_binInEx[j].nSelect = 0;//Ĭ���������벻ѡ��
			m_binInEx[j].nTrigMode = 0;
		}

        for(int j = 0; j < g_nBoutExCount && j < MAX_ExBINARY_COUNT; j++)
		{
			m_binOutEx[j].init();//Ĭ����������ȫ�Ͽ�
		}

        m_nBinLogic = TMT_BINLOGIC_OR;

        // �ݱ����
        m_nRampType = 0;
        m_sttGradient.init();

		for(int nIndex=0;nIndex<MAX_MODULES_GOOSEPUB_COUNT;nIndex++)
			m_oGoosePub[nIndex].init();

        for(int nIndex=0;nIndex<MAX_MODULES_FT3PUB_COUNT;nIndex++)
            m_oFt3Pub[nIndex].init();
	}

    void setDC(bool bDC,bool bUpdateAngleFre = false)
	{
		float fAngle[3] = {0, -120.0, 120.0};
		m_bDC = bDC;

		for (int j=0;j<MAX_VOLTAGE_COUNT;j++)
		{
			m_uiVOL[j].Harm[1].bDC = bDC;

			if (bDC)
			{
				m_uiVOL[j].Harm[1].fAngle = 0;
				m_uiVOL[j].Harm[1].fFreq = 0;
			}

			if (bUpdateAngleFre)
			{
				if (!bDC)
				{
					m_uiVOL[j].Harm[1].fFreq = 50;
					m_uiVOL[j].Harm[1].fAngle = fAngle[j%3];
				}
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

			if (bUpdateAngleFre)
			{
				if (!bDC)
				{
					m_uiCUR[j].Harm[1].fFreq = 50;
					m_uiCUR[j].Harm[1].fAngle = fAngle[j%3];
				}
			}
		}
	}

	void SetFundFreq(float fFreqValue)//���û���Ƶ��
	{
		for (int nChIndex=0;nChIndex<MAX_VOLTAGE_COUNT;nChIndex++)
		{
			m_uiVOL[nChIndex].Harm[1].fFreq =  fFreqValue;
			m_uiCUR[nChIndex].Harm[1].fFreq = fFreqValue;
		}
	}

    tmt_state_para()
	{	
		init(); 
	}

}tmt_StatePara;

typedef struct tmt_state_result
{
public://������
    float	m_frTestTime;							//ʵ������ʱ��,����ǵݱ�����ڵݱ����һ����ʼ��ʱ��
	long    m_nCurStepIndex;//��ǰ�仯�Ĳ���
	int m_nAct;//zhouhj 20210724 �������ڱ�ʶ��״̬��ʵ�ʴ�����ʽ�Ƿ�Ϊ��������������(������Ҫ�����롢���ϵ,��������������)????����������ʵ�ʶ���ʱ��
	double	m_frInTime;		//״̬�������ʱ��
    float	m_frTimeStateBegin;//����״̬ʱ����Կ�ʼ����ʱ�̵����ʱ��

//    float	m_frFlagBinAct[MAX_BINARYIN_COUNT][64];		//ÿһ�������¼64�α�λʱ��
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];
    int    m_nBinFirstChgState[MAX_BINARYIN_COUNT];//״̬�ڵ�һ�α�λ�Ŀ���״ֵ̬(0:�Ͽ�;1:�պ�)
	float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//ÿһ�������¼64�α�λʱ��
	int     m_nRampIndex[MAX_BINARYIN_COUNT];//δ����Ϊ-1��0�����ʼֵ������;1����ݱ�1������

	int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT];
    int    m_nBinExFirstChgState[MAX_ExBINARY_COUNT];//״̬�ڵ�һ�α�λ�Ŀ���״ֵ̬(0:�Ͽ�;1:�պ�)
	float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][64];		//ÿһ�������¼64�α�λʱ��
	int     m_nRampIndexEx[MAX_ExBINARY_COUNT];//δ����Ϊ-1��0�����ʼֵ������;1����ݱ�1������
    void init()
    {
        m_frTestTime = 0;
		m_nCurStepIndex = 0;
        m_frInTime = 0;
        m_frTimeStateBegin = 0;
		m_nAct = 0;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinAct[i][j] = 0;
            }

            m_nBinFirstChgState[i] = 0;
            m_nrBinSwitchCount[i] = 0;
			m_nRampIndex[i] = -1;
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for (int j=0;j<64;j++)
			{
				m_frTimeBinExAct[i][j] = 0;
			}

            m_nBinExFirstChgState[i] = 0;
			m_nrBinExSwitchCount[i] = 0;
			m_nRampIndexEx[i] = -1;
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
    int		         m_nStateNumbers;
//    BOOL	     m_bRepeat;				//�Ƿ�ѭ�����
	int		         m_nRepeatNumbers;		//״̬���е��ظ����� 0:��ѭ��
    int		         m_nBinTripRef;			//���뷭ת�ο�״̬ 0-��һ��״̬ 1-��һ��״̬
	int				 m_nPlusDC;				//�Ƿ����ֱ������ 0-������ 1-���� 2-��״̬����
    float	         m_fTao;					//ֱ��������˥��ʱ�䳣��: ����UIͨ������
    BOOL    	m_bSequence;			//�Ƿ�Ϊ˳��״̬����
	BOOL             m_bSearchNext;//���ڲ�ĺ�������

	//����
	struct
	{
		BOOL		m_bUseError;//ʹ������
		char		m_strTtripBegin_State[MAX_STATE_NAME];//��ʱ���_״̬
		char		m_strTtripEnd_State[MAX_STATE_NAME];//��ʱ�յ�_״̬
		char		m_strTtripBegin_Bin[MAX_STATE_NAME];//��ʱ���_����
		char		m_strTtripEnd_Bin[MAX_STATE_NAME];//��ʱ�յ�_����
		float		m_fActT_AbsErr;//���������
		float		m_fActT_RelErr;//��������
		float		m_fTset;//����ֵ
		long		m_nErrorLogic;//�ж��߼�
	}m_paraEstimates[10];

    tmt_StatePara*       m_paraState;
	int m_nStateCount;

	void initCommon()
	{
//		m_bRepeat = FALSE;
		m_nRepeatNumbers = 0;
		m_nBinTripRef = 1;
		m_nPlusDC = 0;
		m_fTao = 0;
		m_bSequence = TRUE;
		m_bSearchNext = FALSE;
		for (int i = 0; i < 10; i++)
		{
			memset(m_paraEstimates[i].m_strTtripBegin_State, 0, MAX_STATE_NAME);
			memset(m_paraEstimates[i].m_strTtripEnd_State, 0, MAX_STATE_NAME);
			memset(m_paraEstimates[i].m_strTtripBegin_Bin, 0, MAX_STATE_NAME);
			memset(m_paraEstimates[i].m_strTtripEnd_Bin, 0, MAX_STATE_NAME);
			m_paraEstimates[i].m_fActT_AbsErr = 0;
			m_paraEstimates[i].m_fActT_RelErr = 0;
			m_paraEstimates[i].m_fTset = 0;
			m_paraEstimates[i].m_nErrorLogic = 0;
			m_paraEstimates[i].m_bUseError = FALSE;
		}
	}

    void init(long nStateNumbers)
    {

		if (g_nStateCount > m_nStateCount)
		{
			if (m_paraState != NULL)
			{
				delete []m_paraState;
				m_paraState = NULL;
			}	
		}


        if(m_paraState == NULL)
        {
            m_paraState = new tmt_StatePara[g_nStateCount];
        }

        for (int i=0;i<nStateNumbers&&i<g_nStateCount;i++)
        {
            m_paraState[i].init();
        }

		m_nStateCount = g_nStateCount;
    }

	void SetSelect(int nIndex,bool bSel)
	{
        if (nIndex >= 0 && nIndex < g_nStateCount)
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

	void SetFundFreq(float fFreqValue)
	{
		if (m_paraState == NULL)
		{
			return;
		}

		for (int i=0; i < m_nStateNumbers; i++)
		{
			m_paraState[i].SetFundFreq(fFreqValue);
		}
	}

    tmt_state_paras(){
		m_paraState = NULL;
		m_nStateCount = 0;
		initCommon();
	}

	virtual ~tmt_state_paras()
	{
		if (m_paraState != NULL)
		{
            delete[] m_paraState;
			m_paraState = NULL;
		}
	}
}tmt_StateParas;

typedef struct tmt_state_results
{
public:
    long m_nLoopIndex;
    int  m_nBinRefState[MAX_BINARYIN_COUNT];//�ݴ��һ̬��������ֵ
    int  m_nBinExRefState[MAX_ExBINARY_COUNT];//�ݴ��һ̬��������ֵ
    tmt_StateResult*  m_resultState;
	int m_nStateCount;//dxy 20240118 ��ǳ�ʼ��g_nStateCount����

	//����
	struct
	{
		float m_fTtrip; //�Զ��嶯��ʱ��
		float m_fTtrip_AbsErr;//�Զ��嶯��ʱ��������
		float m_fTtrip_RelErr;//�Զ��嶯��ʱ��������
	}m_resultEstimates[10];


    void init(long nStateNumbers)
    {
		for (int i = 0; i < 10; i++)
		{
			m_resultEstimates[i].m_fTtrip = 0;
			m_resultEstimates[i].m_fTtrip_AbsErr = 0;
			m_resultEstimates[i].m_fTtrip_RelErr = 0;
		}

		if (g_nStateCount > m_nStateCount)//dxy 20240118 ���жϷ�ֹg_nStateCount�����и��ģ�����Խ��
		{
			if (m_resultState != NULL)
			{
				delete []m_resultState;
				m_resultState = NULL;
			}	
		}

        if(m_resultState == NULL)
        {
            m_resultState = new tmt_StateResult[g_nStateCount];
        }

        m_nLoopIndex = 0;
        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            m_nBinRefState[i] = 0;
        }

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
        {
            m_nBinExRefState[i] = 0;
        }

        for(int i = 0; i < nStateNumbers && i < g_nStateCount; i++)
        {
            m_resultState[i].init();
        }
		m_nStateCount = g_nStateCount;
    }

    tmt_state_results()
	{
		m_resultState = NULL;
		m_nStateCount = 0;
	}
    virtual ~tmt_state_results()
	{
		if (m_resultState != NULL)
		{
            delete[] m_resultState;
			m_resultState = NULL;
		}
	}
}tmt_StateResults;

typedef struct tmt_state_test : public TMT_PARAS_HEAD
{
public:
    tmt_StateParas       m_oStateParas;
    tmt_StateResults   m_oStateResults;

    void init(long nStateNumbers)
    {
		init_head(); 
		strcpy(m_pszMacroID, STT_MACRO_ID_StateTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
        m_oStateParas.init(nStateNumbers);
        m_oStateResults.init(nStateNumbers);
    }

	tmt_state_test()	{init(0);}
}tmt_StateTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_StateTest();
void stt_init_paras(tmt_StateParas *pParas);
void stt_init_results(tmt_StateResults *pResults);
void stt_xml_serialize(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,long nHarmCount = MAX_HARM_COUNT);
void stt_xml_serialize(tmt_StateResults *pResults,tmt_StateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef);

//2024.5.17 Xuzt ����pszDataTypeID������ʾ����/��ѹͨ��
void stt_xml_serialize(tmt_Channel *pChannel, const char *pszID, CSttXmlSerializeBase *pXmlSierialize,const char *pszDataTypeID,int nHarmCount = MAX_HARM_COUNT);

//2024.5.17 Xuzt ����pszDataTypeID������ʾ����/��ѹͨ��
void stt_xml_serialize_statenUnI_pnv(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,int nMode,long nHarmCount = 1);
void stt_xml_serialize_statenUnI_pnv(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,int nMode,const char *pszDataTypeID,long nHarmCount = 1);
void stt_xml_serialize_statenUnI_pnv(tmt_StateResults *pResults,tmt_StateParas *pStateParas,int nStateNums, CSttXmlSerializeBase *pXmlSierialize,int nBinTripRef);

void stt_xml_serialize(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,int nHarmCount = MAX_HARM_COUNT);
void stt_xml_serialize_ex(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_ex(tmt_StatePara &oStatePara, long nIndex, CSttXmlSerializeBase *pXmlSierialize,bool bSmvAbnormal, bool bGooseAbnormal);

void stt_xml_serialize_ex(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize,bool bSel,long nHarmCount);
void stt_xml_serialize_ex2(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel,long nHarmCount,bool bSmvAbnormal, bool bGooseAbnormal);
void stt_xml_serialize_ex2(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,bool bSel,long nHarmCount);

tmt_StatePara* stt_state_paras_insert_after(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nAfter);
tmt_StatePara* stt_state_paras_insert_before(tmt_StateParas *pParas, tmt_StatePara *pSrc, int nBefore);
void stt_state_paras_delete(tmt_StateParas *pParas, int nIndex);
void stt_xml_serialize_dc(tmt_ChannelHarm &oChannel, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_act_rcd(tmt_StateResult *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_common(tmt_StateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_common(tmt_StateResults *pResults, BOOL *bUseErr, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,long nHarmCount);
CSttXmlSerializeBase* stt_xml_serialize(tmt_state_test *pParas, CSttXmlSerializeBase *pXmlSierialize, long nVolRsNum,long nCurRsNum,long nHarmCount, bool bSmvAbnormal, bool bGooseAbnormal);

void stt_xml_serialize_binary_in(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_binary_out(tmt_StatePara &oStatePara, CSttXmlSerializeBase *pXmlSierialize);
