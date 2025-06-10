#pragma once

#include "tmt_impedance_test.h"
#include "../tmt_common_def.h"

#define STT_CB_OPERATE_PROC_CTRL_TRIP              0
#define STT_CB_OPERATE_PROC_CTRL_TIME              1
// #define MAX_NAME_LEN  32

typedef struct tmt_cb_operate_paras :public tmt_ImpedanceParas
{
	float	m_fTAfterAccTrig;	//���Ϻ���ʱ
	int		m_nTestProcCtrlMode;	// ������̿��Ʒ�ʽ 0-���Ͽ��� 1-ʱ�����
	int   m_nRecloseMode;// �غϷ�ʽ��0-���أ�����+���أ� 1-���� 2-���غ�
	float   m_fUnom;//���ѹ(Ϊ�����ϰ�ӿڳ�������)
	

	long    m_nTtripCheck;     //����ʱ������ж�
	long    m_nTtripDCheck;    //�غ�բ����ʱ������ж�
	long    m_nTtripAccCheck;  //����ٶ���ʱ������ж�

	float   m_fTtripAbsErr;    //����ʱ��������
	float   m_fTtripRelErr;    //����ʱ��������
	float   m_fTSetting;       //����ʱ������ֵ

	float   m_fTtripDAbsErr;     //�غ�բ����ʱ��������
	float   m_fTtripDRelErr;     //�غ�բ����ʱ��������
	float   m_fDTSetting;        //�غ�բ����ʱ������ֵ

	float   m_fTtripAccAbsErr;   //����پ������
	float   m_fTtripAccRelErr;   //�����������
	float   m_fAccTSetting;      //���������ֵ

	long   m_nTtripErrorLogic;     //����ʱ������߼��ж�
	long   m_nTtripDErrorLogic;   //�غ�բ����ʱ������߼��ж�
	long   m_nTtripAccErrorLogic; //����ٶ���ʱ������߼��ж�

	void CalRX_CB_Angle()//����
	{
		float fAngle = m_fImpAngle[0] * pi / 180;
		m_fR = m_fImpedance[0] * cos(fAngle);
		m_fX = m_fImpedance[0] * sin(fAngle);
	}


public:
	virtual void init()
	{
		tmt_ImpedanceParas::init();
		m_fUnom = 57.74f;
		m_fTAfterAccTrig = 0.0f;
		m_nTestProcCtrlMode = STT_CB_OPERATE_PROC_CTRL_TRIP;
		m_nRecloseMode = 0;

		m_fTtripAbsErr = 0.04f;    //����ʱ��������
		m_fTtripRelErr = 0.04f;    //����ʱ��������
		m_fTSetting = 0.1f;       //����ʱ������ֵ

		m_fTtripDAbsErr = 0.04f;     //�غ�բ����ʱ��������
		m_fTtripDRelErr = 0.04f;     //�غ�բ����ʱ��������
		m_fDTSetting = 1.0f;        //�غ�բ����ʱ������ֵ

		m_fTtripAccAbsErr = 0.04f;   //����پ������
	    m_fTtripAccRelErr = 0.04f;   //�����������
		m_fAccTSetting = 0.04f;      //���������ֵ

		m_nTtripCheck = 1;     //����ʱ������ж�
		m_nTtripDCheck = 0;    //�غ�բ����ʱ������ж�
		m_nTtripAccCheck = 0;  //����ٶ���ʱ������ж�

		m_nTtripErrorLogic = 0;     //����ʱ������߼��ж�
		m_nTtripDErrorLogic = 0;   //�غ�բ����ʱ������߼��ж�
		m_nTtripAccErrorLogic = 0; //����ٶ���ʱ������߼��ж�
	} 


	tmt_cb_operate_paras &operator = (const tmt_cb_operate_paras &paras)
	{
		m_fSetting[0]   = paras.m_fSetting[0] ;
		m_fSetting[1]  = paras.m_fSetting[1] ;
		m_fRate[0] = paras.m_fRate[0] ;
		m_fRate[1] = paras.m_fRate[1] ;
		m_fImpedance[0] = paras.m_fImpedance[0] ;		//��·�迹
		m_fImpedance[1] = paras.m_fImpedance[1] ;	
		m_fImpAngle[0] = paras.m_fImpAngle[0] ;			//�迹�� m_fPhi
		m_fImpAngle[1] = paras.m_fImpAngle[1] ;
		m_fSCCurrent[0]  = paras.m_fSCCurrent[0] ;		//��·���� ԭm_fItest  m_fItestdev
		m_fSCCurrent[1] = paras.m_fSCCurrent[1] ;
		m_fSCVoltage[0]  = paras.m_fSCVoltage[0] ;		//��·��ѹ ԭm_fVtest  m_fVtestdev
		m_fSCVoltage[1]  = paras.m_fSCVoltage[1] ;
		m_nFaultDir[0] = paras.m_nFaultDir[0] ;				//���Ϸ��� ԭm_bFaultDirFirst m_bFaultDirSecond
		m_nFaultDir[1] = paras.m_nFaultDir[1] ;
		m_nCTPoint = paras.m_nCTPoint ;			//TA������  S1=ָ��ĸ��,S2=ָ����·  m_bCTPoint
		m_nPTPoint  = paras.m_nPTPoint ;			//TV��װλ��  S1=ĸ�߲�,S2=��·��  m_bPTPoint
		m_nFaultType[0] = paras.m_nFaultType[0] ;			//�������� 
		m_nFaultType[1] = paras.m_nFaultType[1] ;
		m_nCalMode = paras.m_nCalMode ;			//���㷽ʽ��ԭm_nTestMode ��ԶΪ0
//		m_fPrepareTime = paras.m_fPrepareTime ;		//��̬ʱ��
		m_fPreFaultTime = paras.m_fPreFaultTime ;		//����ǰʱ��
		m_fMaxFaultTime = paras.m_fMaxFaultTime;
		m_fMarginTime = paras.m_fMarginTime ;			//����ʱ��ԣ��
		m_bImitatePT  = paras.m_bImitatePT ;		//�Ƿ�ģ��PT����
		m_nImitPTPhase = paras.m_nImitPTPhase ;			//ģ��A��
		m_bCBSimulation = paras.m_bCBSimulation ;		//��·��ģ��  S1=��ģ��,S2=ģ�� 0
		m_fCBTripTime  = paras.m_fCBTripTime ;		//��բʱ��	200ms
		m_fCBCloseTime  = paras.m_fCBCloseTime ;		//��բʱ��	100ms
		m_fFaultAngle = paras.m_fFaultAngle ;		//���Ͻ� ��ԶΪ0
		m_fFaultAng_0 = paras.m_fFaultAng_0 ;
		m_nFaultIncMode = paras.m_nFaultIncMode ;		//���Ͽ�ʼ��ʽ ��ԶΪ0
		m_nFaultTrigMode = paras.m_nFaultTrigMode ;					//���ϴ�����ʽ S1=ʱ��,S2=����,S3=��������H������,S4=GPS 0
		m_nFaultProperty = paras.m_nFaultProperty ;		//�������ʣ�0-˲ʱ 1-���� m_bLastFault
		m_bTransFault = paras.m_bTransFault ;		//�Ƿ�ת���Թ��� 0
		// m_nTransMode = 0;
		m_fTransTime = paras.m_fTransTime ;		//����ת��ʱ��  0.1
		m_fPostFaultTime = paras.m_fPostFaultTime ;		//�������������ʱ��  2.000f
		//ͨ�ò���
		m_nVzDefine = paras.m_nVzDefine ;			//Uz������� S1=0,S2=��3��3Vo,S3=-��3��3Vo,S4=3Vo,S5=-3Vo,S6=��ȡ��ѹ
		//m_nVzPhDefine = 0;		//Uz�ο��ඨ��
		m_nK0CalMode = paras.m_nK0CalMode ;			//���򲹳�ϵ�����㷽ʽ 1  S1=|K0|,,Phi(K0),S2=RERL,,XEXL,S3=|Z0/Z1|,,Phi(Z0/Z1)
		m_fK0Amp = paras.m_fK0Amp ;				//|Ko|��Re(Ko) m_fRMRL
		m_fK0Angle = paras.m_fK0Angle ;			//Phi(Ko)��Im(Ko) m_fXMXL
		//��������
		m_fIfh = paras.m_fIfh ;				//��֪��ʲô��������ԶΪ0
		m_fPowerAngle = paras.m_fPowerAngle ;		//��֪��ʲô��������λ����ԶΪ20
		m_fZs = paras.m_fZs ;				//ϵͳ�迹����ԶΪ1.0 ϵͳ�迹����ʱ��Ч
		m_fPhis = paras.m_fPhis ;				//ϵͳ�迹�ǣ���ԶΪ90  ϵͳ�迹����ʱ��Ч
		m_fK0s = paras.m_fK0s ;				//��֪��ʲôϵ������ԶΪ0
		m_fK0sPh = paras.m_fK0sPh  ;				//��֪��ʲôϵ������ԶΪ0
		m_nRXSelect = paras.m_nRXSelect ;
		m_tGps  = paras.m_tGps;//paras.m_tGps.init();
		m_bIPlusDC  = paras.m_bIPlusDC;
		//m_fTao = 0.1f;
		m_nBinSelect  = paras.m_nBinSelect;

		m_fRecloseTime  = paras.m_fRecloseTime ;
		m_fAfterAcceTime  = paras.m_fAfterAcceTime ;

		m_fUxInput_Mag = paras.m_fUxInput_Mag ;
		m_fUxInput_Ang  = paras.m_fUxInput_Ang ;
		m_fUxHigh  = paras.m_fUxHigh ;
		m_fUxLow  = paras.m_fUxLow ;
		m_fUxInput_Ang  = paras.m_fUxInput_Ang ;
		m_fBoutTimeTrig  = paras.m_fBoutTimeTrig ;
		m_fBoutHoldTime  = paras.m_fBoutHoldTime ;
        /////////////////////////////////////////////////////////////////////////////////
        m_fTAfterAccTrig  = paras.m_fTAfterAccTrig;
        m_nTestProcCtrlMode = paras.m_nTestProcCtrlMode;
		m_nRecloseMode = paras.m_nRecloseMode;
		m_fUnom = paras.m_fUnom;

		m_fTtripAbsErr = paras.m_fTtripAbsErr;    //����ʱ��������
		m_fTtripRelErr = paras.m_fTtripRelErr;    //����ʱ��������
		m_fTSetting = paras.m_fTSetting;       //����ʱ������ֵ

		m_fTtripDAbsErr = paras.m_fTtripDAbsErr;     //�غ�բ����ʱ��������
		m_fTtripDRelErr = paras.m_fTtripDRelErr;     //�غ�բ����ʱ��������
		m_fDTSetting = paras.m_fDTSetting;       //�غ�բ����ʱ������ֵ

		m_fTtripAccAbsErr = paras.m_fTtripAccAbsErr;   //����پ������
		m_fTtripAccRelErr = paras.m_fTtripAccRelErr;   //�����������
		m_fAccTSetting = paras.m_fAccTSetting;      //���������ֵ

		m_nTtripCheck = paras.m_nTtripCheck;     //����ʱ������ж�
		m_nTtripDCheck = paras.m_nTtripDCheck;     //�غ�բ����ʱ������ж�
		m_nTtripAccCheck = paras.m_nTtripAccCheck;  //����ٶ���ʱ������ж�
 

		m_nTtripErrorLogic = paras.m_nTtripErrorLogic;     //����ʱ������߼��ж�
		m_nTtripDErrorLogic = paras.m_nTtripDErrorLogic;  //�غ�բ����ʱ������߼��ж�
		m_nTtripAccErrorLogic = paras.m_nTtripAccErrorLogic; //����ٶ���ʱ������߼��ж�
 		return *this;
 	}

}tmt_CBOperateParas;

typedef struct tmt_cb_operate_results :public tmt_ImpedanceResults
{
public:
	long m_nActAcc;
public:
	virtual void init()
	{
		tmt_ImpedanceResults::init();
		m_nActAcc = 0;
		
	} 

	tmt_cb_operate_results &operator = (const tmt_cb_operate_results &paras)
	{
		m_fRealTestTime =  paras.m_fRealTestTime;			//ʵ������ʱ��
		m_nTripNumbers =  paras.m_nTripNumbers;			//��բ(�غ�)�ܴ���, ��������¼��բ 4 ��
		m_fImp = paras.m_fImp;
		m_fImpAngle = paras.m_fImpAngle;
		m_fOverCurrent = paras.m_fOverCurrent;
		m_fFaultCurrent =  paras.m_fFaultCurrent;
		m_fFaultVol =	paras.m_fFaultVol;

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			for (int j = 0; j < 2;j++)
			{
				m_fBinTripTime[i][j] = paras.m_fBinTripTime[i][j];
			}
		}
		
		for (int i = 0; i < 8; i++)
		{
			m_fFirstTripTime[i] = paras.m_fFirstTripTime[i];//float	m_fBinTripTime[MAX_BINARYIN_COUNT][2];//����ӵ�ÿ�ζ���(��բ,�غ�)ʱ��
		}

		m_fRecloseTime = paras.m_fRecloseTime;
		m_fSecondTripTime = paras.m_fSecondTripTime;

		for (int i = 0; i < 4; i++)
		{
			m_fRecordTime[i] = paras.m_fRecordTime[i];
		}

		for (int i = 0; i < 8; i++)
		{
			m_fReturnTime[i] = paras.m_fReturnTime[i];
		}
		m_fTripTime = paras.m_fTripTime;

		for (int i = 0; i < MAX_BINARYIN_COUNT; i++)
		{
			m_nActID[i] = paras.m_nActID[i];//��ԭ��m_nActA��B��C��ͳһΪ����
		}

		m_nActA =  paras.m_nActA;
		m_nActB = paras.m_nActB;
		m_nActC = paras.m_nActC;
		m_nActD = paras.m_nActD;
		m_nActAcc = paras.m_nActAcc;

		return *this;
	}


}tmt_CBOperateResults;

#define ITEM_CNT  5



typedef struct tmt_cb_operate_test  : public TMT_PARAS_HEAD
{
public:
	tmt_CBOperateParas       m_oCBOperateParas;
	tmt_CBOperateResults   m_oCBOperateResults;
	char m_szName[MAX_NAME_LEN];
	
	float m_fR;
	float m_fX;

	void init()
	{
		init_head(); //2021-9-13  lijunqing
		strcpy(m_pszMacroID, STT_MACRO_ID_PsuCBOperate);
		strcpy(m_szName, "Z = 1.900��, A-E, ˲ʱ");
		m_nVersion = 0x00010001;
		m_nTestState = 0;
		m_nSelected = 1;
		m_fR = 0.0f;
		m_fX = 0.0f;

		m_oCBOperateParas.init();
		m_oCBOperateResults.init();
		
	}


	tmt_cb_operate_test &operator = (const tmt_cb_operate_test &paras)
	{
		m_oCBOperateParas = paras.m_oCBOperateParas ;
		m_oCBOperateResults = paras.m_oCBOperateResults ;
		m_fR = paras.m_fR;
		m_fX = paras.m_fX;
		m_nSelected = paras.m_nSelected;

		for (int i = 0; i < MAX_NAME_LEN;i++)
			m_szName[i] = paras.m_szName[i];

		return *this;
	}

	tmt_cb_operate_test()	{init();}
	virtual void clear_result(){	m_oCBOperateResults.init();	}
	virtual ~tmt_cb_operate_test(){}

}tmt_CBOperateTest;

void stt_init_paras(tmt_CBOperateParas *pParas);
void stt_init_results(tmt_CBOperateResults *pResults);

void stt_xml_serialize(tmt_CBOperateParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_CBOperateResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
CSttXmlSerializeBase* stt_xml_serialize(tmt_CBOperateTest *pTests, CSttXmlSerializeBase *pXmlSerialize, long nVolRsNum, long nCurRsNum);


