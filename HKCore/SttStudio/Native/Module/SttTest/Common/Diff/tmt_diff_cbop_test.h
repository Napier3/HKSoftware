#pragma once

#include "../tmt_test_paras_head.h"
#include "../tmt_common_def.h"
#include "../SearchBase/tmt_search_base.h"

#define FAULTLOCATION_HIGH_IN  0
#define FAULTLOCATION_HIGH_OUT  1
#define FAULTLOCATION_LOW_IN  2
#define FAULTLOCATION_LOW_OUT  3

typedef struct tmt_diff_cbop_paras
{
	int	    m_nFaultType;		//��������
	int     m_nErrorType;       //�������
	int	    m_nFaultLocation;	//���ϵ�λ��
	float	m_fCurrent;			//����(A)
	float	m_fFreq;			//Ƶ��(Hz)

    float	m_fVg1;			//��һ���ѹ���ֵ
    float	m_fVg2;			//�ڶ����ѹ���ֵ

	//ϵͳ����
    int  m_nKcal;               //�Ƿ�����ƽ��ϵ��
    float	m_fSN;              //��ѹ�������
	float	m_fKph;				//��ѹ����ѹ��ƽ��ϵ��
	float	m_fUh;				//��ѹ����ѹ����ѹ
    float	m_fInh;             //��ѹ����ѹ������
    float	m_fCTh;             //��ѹ����ѹ��CT���
    float	m_fKpm;				//��ѹ����ѹ��ƽ��ϵ��
    float	m_fUm;				//��ѹ����ѹ����ѹ
    float	m_fInm;             //��ѹ����ѹ������
    float	m_fCTm;             //��ѹ����ѹ��CT���
    float	m_fKpl;				//��ѹ����ѹ��ƽ��ϵ��
    float	m_fUl;				//��ѹ����ѹ����ѹ
    float	m_fInl;             //��ѹ����ѹ������
    float	m_fCTl;             //��ѹ����ѹ��CT���

    float   m_fAbsErrSum;       //�������(S) +
    float   m_fAbsErrReduce;    //�������(S) -
    float	m_fRelErr;	        //������

	//ͨ�ò���
	float   m_fPrepareTime;         //׼��ʱ��
	float   m_fPreFaultTime;	    //����ǰʱ��
    float   m_fFaultTime;		    //����ʱ��
	float   m_fFaultTimeMargin;     //����ʱ��ԣ��
    float   m_fActionHoldTime;      //�����󱣳�ʱ��
    int		m_nWindH;		//��ѹ�����������ʽ 0-Y 1-�� 0	���Լ���KPH��KPL
    int		m_nWindM;		//��ѹ�����������ʽ 0-Y 1-�� 0	���Լ���KPH��KPL
    int		m_nWindL;		//��ѹ�����������ʽ 0-Y 1-�� 1 ���Լ���KPL
    int		m_nAngleMode;	//У��ѡ��	0-��У�� 1-����У�� 2-Y��У��  2	���Լ���KPH��KPL AngleMode
    int		m_nWindSide;	//��������	0-��-��  1-��-��    2-��-��    2	���Լ���KPH��KPL
    int	    m_nAroundClockNumHM;	//��-�������ӵ���//
	int	    m_nAroundClockNumHL;	//��-�������ӵ���
	int	    m_nBalanceTerms;		//ƽ��ϵ������
	BOOL	m_bCTStarPoint;		    //CT����0-����ָ���ѹ�� 1-һ��ָ���ѹ��  ƽ̨ģ�����û�У���Ϊ0
    int	    m_nIbiasCal;	        //�ƶ����� 0-Ir=(|I1-I2|)/K1��Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|s,|I2|)
    //,3-Ir=(|Id-|I1|-|I2||)/K1,4-Ir=|I2|,5-Sqrt(K1*I1*I2*Cos(��))
	float	m_fFactor1;				//K1
	float	m_fFactor2;				//K2
    int	    m_nComBineFeature;		//�������
    int	    m_nEarthing;			//�ӵ�
	BOOL    m_bCBSimulation;		//��·��ģ��  S1=��ģ��,S2=ģ�� 0(0:��ģ��,1:ģ��)
	float   m_fCBTripTime;			//��բʱ��
	float   m_fCBCloseTime;			//��բʱ��
	int	    m_nCoordinate;			//����
    int		m_nInSel;	//��׼����ѡ�� 0-�߲���ζ���� 1-�趨ֵ 2-������ζ����	ƽ̨ģ��û�У���Ϊ0 ���Լ���INOM
    float	m_fIbase;	//��׼�����趨ֵ

	//����������
    int  m_nBinLogic; //0 1�߼����
    int  m_binIn[MAX_BINARYIN_COUNT];
    int  m_binOut[2][MAX_BINARYOUT_COUNT];

public:
	virtual void init()
	{
        //tmt_SearchBase::InitSearch();

		m_nFaultType = 0;		//��������
		m_nFaultLocation = 0;	//���ϵ�λ�� 0-��ѹ�ࣨ���ڣ�1-��ѹ�ࣨ���⣩2-��ѹ�ࣨ���ڣ�3-��ѹ�ࣨ���⣩
		m_nErrorType = 0;      //�������
		m_fCurrent = 5.000f;			//����(A)
		m_fFreq = 50.000f;			//Ƶ��(Hz)
        m_fVg1=57.74f;
        m_fVg2=57.74f;

		//ϵͳ����
		m_fKph = 1.000f;				//��ѹ����ѹ��ƽ��ϵ��
		m_fUh = 110.000f;				//��ѹ����ѹ����ѹ
        m_fInh = 10.000f;               //��ѹ����ѹ������
        m_fCTl  = 300.000f;             //��ѹ����ѹ��CT���
		m_fKpm = 0.936f;				//��ѹ����ѹ��ƽ��ϵ��
		m_fUm = 38.500f;				//��ѹ����ѹ����ѹ
        m_fInm = 7.000f;                //��ѹ����ѹ������
        m_fCTm  = 800.000f;             //��ѹ����ѹ��CT���
		m_fKpl = 0.637f;				//��ѹ����ѹ��ƽ��ϵ��
		m_fUl = 10.500f;				//��ѹ����ѹ����ѹ
        m_fCTl  = 5.000f;               //��ѹ����ѹ������
        m_fCTl  = 800.000f;             //��ѹ����ѹ��CT���
        m_fSN = 31.500f;                //��ѹ�������

		m_fAbsErrSum   = 0.002f;		//�������(S) +
		m_fAbsErrReduce= 0.001f;		//�������(S) -
		m_fRelErr      = 0.02f;	        //������

		//ͨ�ò���
		m_fPrepareTime  = 0.000f;        //׼��ʱ��
		m_fPreFaultTime =0.500f;	     //����ǰʱ��
        m_fFaultTime =0.500f;
		m_fFaultTimeMargin = 0.500f;     //����ʱ��ԣ��
		m_fActionHoldTime = 0.500f;      //�����󱣳�ʱ��	 
        m_nWindH = 0;
        m_nWindM = 0;
        m_nWindL = 1;
        m_nAngleMode = 0;
        m_nWindSide = 0;
		m_nAroundClockNumHM = 1;	     //��-�������ӵ���
		m_nAroundClockNumHL = 1;	     //��-�������ӵ���
		m_nBalanceTerms = 1;		     //ƽ��ϵ������
		m_bCTStarPoint = 1;				 //CT����
		m_nIbiasCal = 1;				 //�ƶ����� 0-Ir=(|I1-I2|)/K1��Ir=(|I1+I2|)/K1,1-Ir=(|I1|+|I2|*K2)/K1,2-Ir=max(|I1|,,|I2|)
		m_fFactor1 = 2;					 //K1
		m_fFactor2 = 1;					 //K2
		m_nComBineFeature = 1;			 //�������
		m_nEarthing = 1;				 //�ӵ�
		m_bCBSimulation = 0;			 //��·��ģ��  S1=��ģ��,S2=ģ�� 0(0:��ģ��,1:ģ��)
		m_fCBTripTime  = 100.000f;		 //��բʱ��
		m_fCBCloseTime = 100.000f;		 //��բʱ��
		m_nCoordinate  = 0;				 //����
        m_nInSel = 0;
        m_fIbase = 5.000f;

		//����������
		m_nBinLogic = 0; //0 - �� 1 - ��

		for(int i = 0;i < MAX_BINARYOUT_COUNT; i++)
		{
			m_binIn[i] = 0;
			for (int j = 0;j < 2; j++)
			{
				m_binOut[i][j] = 0;
			}
		}
	}

}tmt_DiffCBOpParas;

typedef struct tmt_diff_cbop_results
{
    float	m_fTripTime;		//����ʱ��
    int		m_nActFlag;			//������־
public:
	virtual void init()
	{
        m_fTripTime = 0.0f;
        m_nActFlag = 0;
    }
}tmt_DiffCBOpResults;


typedef struct tmt_diff_cbop_Test  : public TMT_PARAS_HEAD
{
public:
	tmt_DiffCBOpParas       m_oDiffProtectionParas;
	tmt_DiffCBOpResults     m_oDiffProtectionResults;

    virtual void init()
    {
        init_head();
        strcpy(m_pszMacroID, STT_MACRO_ID_DiffCBOp);
        m_nVersion = 0x00010001;
        m_nTestState = 0;

        m_oDiffProtectionParas.init();
        m_oDiffProtectionResults.init();
    }

    tmt_diff_cbop_Test()	{init();}
    virtual void clear_result(){	m_oDiffProtectionResults.init();	}
    virtual ~tmt_diff_cbop_Test(){}


}tmt_DiffCBOpTest;

void stt_init_paras(tmt_DiffCBOpParas *pParas);
void stt_init_results(tmt_DiffCBOpResults *pResults);

void stt_xml_serialize(tmt_DiffCBOpParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_write_DiffCBOp();
void stt_xml_serialize(tmt_DiffCBOpResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_diff_cbop_Test *pTests, CSttXmlSerializeBase *pXmlSerialize);
