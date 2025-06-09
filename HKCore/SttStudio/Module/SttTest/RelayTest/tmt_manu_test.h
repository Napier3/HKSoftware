#pragma once

#include "tmt_common_def.h"
#include"../../SttTestBase/SttXmlSerialize.h"

// �ֶ�������ز���
typedef struct tmt_manu_gradient
{
    int		nMode;	// 0:ʼֵ-��ֵ  1:ʼֵ-��ֵ-ʼֵ
    float	fStart;
    float	fEnd;
    float	fStep;
    float	fStepTime;
    float	fTrigDelay;
    int		nHarmIndex;

    void init()
    {
        nMode = 0;
        fStart=0;
        fEnd=0;
        fTrigDelay=0;
        fStep=0;
        fStepTime=0;
        nHarmIndex=0;
    }

    tmt_manu_gradient(){}
    virtual ~tmt_manu_gradient(){}
}tmt_ManuGradient;

typedef struct tmt_manual_paras
{
public:
    BOOL	m_bAging;		//�Ƿ��ϻ�����
    BOOL	m_bAuto;
    BOOL	m_bDC;
    bool       m_bLockChanged;//lock mark
    float       m_fOutPutTime;	// ����ʱ��
    float	    m_fVolAux;		// ����ֱ����ѹ����ģ�⣩
    float	    m_fCurAux;		// ����ֱ����������ģ�⣩
    float       m_fOverloadDelaytime;	//������ʱ  ��λ�� ���ܣ��������ڿ�ʼ������趨ʱ��֮����⵽���ز��ж����
    tmt_channel m_uiVOL[MAX_VOLTAGE_COUNT];
    tmt_channel m_uiCUR[MAX_CURRENT_COUNT];
    //������
    int		m_nBinLogic;			//0-�� 1-��
    tmt_BinaryIn     m_binIn[MAX_BINARYIN_COUNT];
    tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
    int		 m_nGradientTpSelect;	// �ݱ�����ѡ��
    int		 m_nGradientChSelect;	// �ݱ�ͨ��ѡ��
    tmt_ManuGradient m_manuGradient;

public:
    void init()
    {
        float fAngle[3] = {0, -120.0, 120.0};
        m_bAging = false;
        m_bAuto = false;
        m_bDC = false;
        m_bLockChanged = false;
        m_fOutPutTime = 999;
        m_fVolAux = 0;
        m_fCurAux = 0;       
        m_fOverloadDelaytime = 10;
        m_nBinLogic = 0;                   
        m_nGradientChSelect = 0;
        m_nGradientTpSelect = 0;                
        m_manuGradient.init();
        for(int i=0; i<MAX_VOLTAGE_COUNT; i++)
        {
            m_uiVOL[i].Harm[1].fAmp = 57.74;
            m_uiCUR[i].Harm[1].fAmp = 0;
             m_uiVOL[i].Harm[1].fAngle = m_uiCUR[i].Harm[1].fAngle = fAngle[i%3];
        }
    }

    tmt_manual_paras()	{}
    virtual ~tmt_manual_paras() {}
}tmt_ManualParas;

typedef struct tmt_manual_result
{
public:
    unsigned  int m_nindex;		//���
    unsigned   int m_nsecondtime;		// ʱ����� ��
    unsigned   int m_nnsecondtime;	// ʱ����� ����
    unsigned   int m_noactivetype;	// ����
    unsigned   int m_nBinstate;		// ������
    unsigned   int m_nBinAllState;   // ����������״ֵ̬
    unsigned   int m_nOverLoad;		// ���غ�ֹͣ
    float        m_fuavalue;		// ��ѹʵ�����ֵ�����ڼ�����ѹУ��ϵ��
    float        m_fubvalue;
    float        m_fucvalue;
    float        m_fuzvalue;

    //�������
    float	m_frTestTime;							//ʵ������ʱ��
    float	m_frTimeBinAct[MAX_BINARYIN_COUNT][64];		//ÿһ�������¼64�α�λʱ��
    int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT];
    int		m_nTripFlag;
    float	m_fTripTime;
    float	m_fActValue;
    float	m_fReturnValue;
    float   m_fReturnTime;

public:
    void init()
    {
        m_nindex = 0;
        m_nsecondtime = 0;
        m_nsecondtime = 0;
        m_noactivetype = 0;
        m_nBinstate = 0;
        m_nBinAllState = 0;
        m_nOverLoad = 0;
        m_fuavalue = 0;
        m_fubvalue = 0;
        m_fucvalue = 0;
        m_fuzvalue = 0;
        m_frTestTime = 0;
        m_nTripFlag = 0;
        m_fTripTime = 0;
        m_fActValue = 0;
        m_fReturnValue = 0;
        m_fReturnTime = 0;

        for (int i=0;i<MAX_BINARYIN_COUNT;i++)
        {
            for (int j=0;j<64;j++)
            {
                m_frTimeBinAct[i][j] = 0;
 //            m_frFlagBinAct[i][j] = 0;
            }
            m_nrBinSwitchCount[i] = 0;
        }
    }

    tmt_manual_result()	{}
    virtual ~tmt_manual_result() {}
}tmt_ManualResult;

typedef struct tmt_manual_test
{
public:
    tmt_ManualResult m_oManuResult;
    tmt_ManualParas   m_oManuParas;

    void init()
    {
        m_oManuResult.init();
        m_oManuParas.init();
    }
    tmt_manual_test() {}
    virtual ~tmt_manual_test() {}
}tmt_ManualTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_ManuTest();
void stt_init_paras(tmt_ManualParas *pParas);
void stt_init_results(tmt_ManualParas *pResults);
void stt_xml_serialize(tmt_ManualParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_ManualResult *pResults, CSttXmlSerializeBase *pXmlSierialize);


