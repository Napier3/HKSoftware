#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

//��������
#define ERR_A_JD       0
#define ERR_B_JD       1
#define ERR_C_JD       2
#define ERR_AB_DL      3
#define ERR_BC_DL      4
#define ERR_CA_DL      5
#define ERR_AB_JDDL    6
#define ERR_BC_JDDL    7
#define ERR_CA_JDDL    8
#define ERR_ABC_DL     9
#define ERR_SINGLE_ZK  10

//KoMode ���򲹳�ϵ�����㷽ʽ
#define MODE_K0    0
#define MODE_RERL  1
#define MODE_Z0    2

typedef struct
{
    float m_fUNom; //��ߵ�ѹ
    float m_fINom; //�dianliu
    float m_fFreqNom; //�Ƶ��
}tmt_CommonPara;

typedef struct tmt_shake_paras
{
public:
    float  m_fPowerAngStart;//����ʼֵ
    float  m_fPowerAngEnd;//������ֵ
    float  m_fCycle;//������
    int      m_nShakeNum;//�񵴴���
    float  m_fRate;//em/en
    UINT m_nTripPt;//��բ�ӵ�
    UINT m_nTripSpeedupPt;//�����źŽӵ�
    UINT m_nTripSpeedDnPt;//�����źŽӵ�
    float  m_fFreq;//Ƶ��
    BOOL m_bExtraFault;//�����ٹ���
    BOOL m_bReciprocating;//������
    BOOL m_bDzDt;//�Ƿ�DZDT
    float   m_fDzDt;//DZDT
    BOOL m_bAccelerate;//������

    int       m_nFaultType;//��������
    float   m_fImpedance;//��·�迹
    float   m_fFaultCur;//���ϵ���
    float   m_fFaultTime;//���Ϸ���ʱ��
    int       m_nK0Mode;//��﷽ʽ
    float   m_fAmp;//
    float   m_fAngle;//
    float m_fKoOrRe;  //���򲹳�����ϵ��
    float m_fPhiOrIm; //������λ����ϵ��

    float   m_fActTime;//

    float m_fPreFaultTime;//
    UINT m_nCTPoint;//
    float m_fZS;//
    float m_fPhisS;//
    float m_fZT;//
    float m_fPhisT;//
    float m_fXD;//

    tmt_CommonPara oCommonPara;//
     tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];//
     void display()
     {

     }

    void init()
    {
        m_fPowerAngStart = 0.0f;
        m_fPowerAngEnd = 200.0f;
        m_fCycle = 0.02f;
        m_nShakeNum = 1;
        m_fRate = 1.25f;
        m_nTripPt = 0;
        m_nTripSpeedupPt = 0;
        m_nTripSpeedDnPt = 0;
        m_fFreq = 50.0f;
        m_bExtraFault = false;
        m_bReciprocating = false;
        m_bDzDt = false;
        m_bDzDt = 0.0f;
        m_bAccelerate = false;

        m_nFaultType = 0;
        m_fImpedance = 1.0f;
        m_fFaultCur = 5.0f;
        m_fFaultTime = 0.0f;
        m_nK0Mode = 0;
        m_fAmp = 0.0f;
        m_fAngle = 0.0f;
        m_fActTime = 5.0f;
        m_fPreFaultTime = 5.0f;
        m_nCTPoint = 0;
        m_fZS = 25.0f;
        m_fPhisS = 90.0f;
        m_fZT = 15.0f;
        m_fPhisT = 78.0f;
        m_fXD = 1.0f;
        m_fKoOrRe = 0.0f;
        m_fPhiOrIm = 0.0f;
        oCommonPara.m_fFreqNom = 50.0f;
        oCommonPara.m_fUNom = 100.0f;
        oCommonPara.m_fINom = 5.0f;
    }

    tmt_shake_paras(){}
    virtual ~tmt_shake_paras(){}
}tmt_ShakeParas;

typedef struct tmt_shake_results
{
public:

    void init()
    {
    }

    tmt_shake_results(){}
    virtual ~tmt_shake_results(){}
}tmt_ShakeResults;

typedef struct tmt_shake_test
{
public:
    tmt_ShakeParas       m_oShakeParas;
    tmt_ShakeResults   m_oShakeResults;

    void init()
    {
        m_oShakeParas.init();
        m_oShakeResults.init();
    }

    tmt_shake_test()	{}
    virtual ~tmt_shake_test(){}
}tmt_ShakeTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
void stt_xml_serialize_write_ShakeTest();//
void stt_init_paras(tmt_ShakeParas *pParas);//
void stt_init_results(tmt_ShakeResults *pResults);//
void stt_xml_serialize(tmt_ShakeParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ShakeResults *pResults, CSttXmlSerializeBase *pXmlSierialize);


