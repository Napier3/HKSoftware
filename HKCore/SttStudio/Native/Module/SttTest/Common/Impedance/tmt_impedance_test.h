#pragma once

#include "../tmt_common_def.h"
#include "../tmt_state_test.h"
#include"../../../SttTestBase/SttXmlSerialize.h"
#include <math.h>

#define STT_FaultProperty_Transient                  0           
#define STT_FaultProperty_Permanent                  1   



#define MAX_NAME_LEN  32
typedef struct tmt_impedance_paras
{
public:
	virtual void init()
	{
		m_fSetting[0] = 2.85f;
		m_fSetting[1] = 0.5f;
		m_fRate[0] = 1.0f;
		m_fRate[1] = 1.0f;
		m_fImpedance[0] = 2.85f;		//��·�迹
		m_fImpedance[1] = 0.5;	
		m_fImpAngle[0] = 90;			//�迹�� m_fPhi
		m_fImpAngle[1] = 90;
		m_fSCCurrent[0] = 5.000f;		//��·���� ԭm_fItest  m_fItestdev
		m_fSCCurrent[1] = 5.000f;
		m_fSCVoltage[0] = 50.000f;		//��·��ѹ ԭm_fVtest  m_fVtestdev
		m_fSCVoltage[1] = 0.000f;
		m_nFaultDir[0] = 1;				//���Ϸ��� ԭm_bFaultDirFirst m_bFaultDirSecond
		m_nFaultDir[1] = 1;
		m_nCTPoint = 1;			//TA������  S1=ָ��ĸ��,S2=ָ����·  m_bCTPoint
		m_nPTPoint = 0;			//TV��װλ��  S1=ĸ�߲�,S2=��·��  m_bPTPoint
		m_nFaultType[0] = 0;			//�������� 
		m_nFaultType[1] = 0;
		m_nCalMode = 0;			//���㷽ʽ��ԭm_nTestMode ��ԶΪ0
		m_fPrepareTime = 5.000;		//��̬ʱ��
		m_fPreFaultTime = 2.000f;		//����ǰʱ��
		m_fMaxFaultTime = 0.200f;			//����ʱ��
		m_fMarginTime = 0.2f;//
		m_bImitatePT = FALSE;		//�Ƿ�ģ��PT����
		m_nImitPTPhase = STT_PT_IMIT_PHASE_A;			//ģ��A��
		m_bCBSimulation = 0;		//��·��ģ��  S1=��ģ��,S2=ģ�� 0
		m_fCBTripTime = 0.200f;		//��բʱ��	200ms
		m_fCBCloseTime = 0.100f;		//��բʱ��	100ms
		m_fFaultAngle = 0;		//���Ͻ� ��ԶΪ0
		m_fFaultAng_0 = 0;
		m_nFaultIncMode = 0;		//���Ͽ�ʼ��ʽ ��ԶΪ0
		m_nFaultTrigMode = 0;					//���ϴ�����ʽ S1=ʱ��,S2=����,S3=��������H������,S4=GPS 0
		m_nFaultProperty = STT_FaultProperty_Transient;		//�������ʣ�0-˲ʱ 1-���� m_bLastFault
		m_bTransFault = 0;		//�Ƿ�ת���Թ��� 0
// 		m_nTransMode = 0;
 		m_fTransTime = 0.1f;		//����ת��ʱ��  0.1
		m_fPostFaultTime = 2.000f;		//�������������ʱ��  2.000f
		//ͨ�ò���
		m_nVzDefine = 0;			//Uz������� S1=0,S2=��3��3Vo,S3=-��3��3Vo,S4=3Vo,S5=-3Vo,S6=��ȡ��ѹ
//		m_nVzPhDefine = 0;		//Uz�ο��ඨ��
		m_nK0CalMode = 1;			//���򲹳�ϵ�����㷽ʽ 1  S1=|K0|,,Phi(K0),S2=RERL,,XEXL,S3=|Z0/Z1|,,Phi(Z0/Z1)
		m_fK0Amp = 0.670f;				//|Ko|��Re(Ko) m_fRMRL
		m_fK0Angle = 0.670f;			//Phi(Ko)��Im(Ko) m_fXMXL
		//��������
		m_fIfh = 0;				//��֪��ʲô��������ԶΪ0
		m_fPowerAngle = 20;		//��֪��ʲô��������λ����ԶΪ20
		m_fZs = 1.0;				//ϵͳ�迹����ԶΪ1.0 ϵͳ�迹����ʱ��Ч
		m_fPhis = 90.0f;				//ϵͳ�迹�ǣ���ԶΪ90  ϵͳ�迹����ʱ��Ч
		m_fK0s = 0;				//��֪��ʲôϵ������ԶΪ0
		m_fK0sPh = 0;				//��֪��ʲôϵ������ԶΪ0
		m_nRXSelect = 0;
		m_tGps.init();
		m_bIPlusDC = 0;
//		m_fTao = 0.1f;
		m_nBinSelect = 0;

		m_fRecloseTime = 0.7f;
		m_fAfterAcceTime = 0.5f;

		m_nVzPhDefine = 0;
		m_fUxInput_Mag = 0.0f;
		m_fUxInput_Ang = 0.0f;
		m_fUxHigh = 40.0f;
		m_fUxLow = 0.0f;
		m_fUxInput_Ang = 0.0f;
		m_fBoutTimeTrig = 0.0f;
		m_fBoutHoldTime = 0.0f;
		m_nOutputSwitchMode = 0;

		for (int nIndex = 0;  nIndex  <  MAX_BINARYIN_COUNT;  nIndex++)
		{
			m_nDInputState[nIndex] = STT_IMPEDANCE_BIN_STATE_SINGLE;
			m_nStateBOut[nIndex] = 0;
		}
	}

	void CopyOwn(tmt_impedance_paras* pDest)
	{
		for (int nIndex = 0;nIndex<2;nIndex++)
		{
			pDest->m_fSetting[nIndex] = m_fSetting[nIndex];
			pDest->m_fRate[nIndex] = m_fRate[nIndex];
			pDest->m_fImpedance[nIndex] = m_fImpedance[nIndex];
			pDest->m_fImpAngle[nIndex] = m_fImpAngle[nIndex];
			pDest->m_fSCCurrent[nIndex] = m_fSCCurrent[nIndex];
			pDest->m_fSCVoltage[nIndex] = m_fSCVoltage[nIndex];
			pDest->m_nFaultType[nIndex] = m_nFaultType[nIndex];
			pDest->m_nFaultDir[nIndex] = m_nFaultDir[nIndex];
		}

		pDest->m_nCTPoint = m_nCTPoint;
		pDest->m_nPTPoint = m_nPTPoint;
		pDest->m_nCalMode = m_nCalMode;
		pDest->m_fPrepareTime = m_fPrepareTime;
		pDest->m_fPreFaultTime = m_fPreFaultTime;
		pDest->m_fMaxFaultTime = m_fMaxFaultTime;
		pDest->m_fMarginTime = m_fMarginTime;
		pDest->m_bImitatePT = m_bImitatePT;
		pDest->m_nImitPTPhase = m_nImitPTPhase;

		pDest->m_bCBSimulation = m_bCBSimulation;
		pDest->m_fCBTripTime = m_fCBTripTime;
		pDest->m_fCBCloseTime = m_fCBCloseTime;
		pDest->m_nFaultIncMode = m_nFaultIncMode;
		pDest->m_fFaultAngle = m_fFaultAngle;
		pDest->m_fFaultAng_0 = m_fFaultAng_0;
		pDest->m_nFaultTrigMode = m_nFaultTrigMode;
		pDest->m_nFaultProperty = m_nFaultProperty;
		pDest->m_bTransFault = m_bTransFault;
		pDest->m_fTransTime = m_fTransTime;
		pDest->m_fPostFaultTime = m_fPostFaultTime;
		pDest->m_nVzDefine = m_nVzDefine;
		pDest->m_nVzPhDefine = m_nVzPhDefine;
		pDest->m_nK0CalMode = m_nK0CalMode;
		pDest->m_fK0Amp = m_fK0Amp;
		pDest->m_fK0Angle = m_fK0Angle;

		pDest->m_fIfh = m_fIfh;
		pDest->m_fPowerAngle = m_fPowerAngle;
		pDest->m_fZs = m_fZs;
		pDest->m_fPhis = m_fPhis;
		pDest->m_fK0s = m_fK0s;
		pDest->m_fK0sPh = m_fK0sPh;
		pDest->m_nRXSelect = m_nRXSelect;
		pDest->m_fUxInput_Mag = m_fUxInput_Mag;
		pDest->m_fUxInput_Ang = m_fUxInput_Ang;
		pDest->m_fUxHigh = m_fUxHigh;
		pDest->m_fUxLow = m_fUxLow;
		pDest->m_nOutputSwitchMode = m_nOutputSwitchMode;
		pDest->m_fBoutTimeTrig = m_fBoutTimeTrig;

		pDest->m_fBoutHoldTime = m_fBoutHoldTime;
		pDest->m_fRecloseTime = m_fRecloseTime;
		pDest->m_fAfterAcceTime = m_fAfterAcceTime;
		pDest->m_tGps = m_tGps;
		pDest->m_bIPlusDC = m_bIPlusDC;
		pDest->m_nBinSelect = m_nBinSelect;
		pDest->m_nOutputSwitchMode = m_nOutputSwitchMode;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_nDInputState[nIndex] = m_nDInputState[nIndex];
			pDest->m_nStateBOut[nIndex] = m_nStateBOut[nIndex];
		}
	}

	int GetSttTrigMode()
	{
		int nSttTrigMode = TMT_MDSTATE_TIMETRIGGER;

		switch (m_nFaultTrigMode)
		{
		case 0:		// ʱ��
			nSttTrigMode = TMT_MDSTATE_TIMETRIGGER; 
			break;
		case 1:		// ����
			nSttTrigMode = TMT_MDSTATE_MEARSURETRIGGER; 
			break;
		case 2:		// ����ӵ�
			nSttTrigMode = TMT_MDSTATE_BINTRIGGER; 
			break;
		case 3:		// GPS
			nSttTrigMode = TMT_MDSTATE_GPSBTRIGGER; 
			break;
		default:
			break;
		}

		return nSttTrigMode;
	}

	tmt_impedance_paras()	{	}
	virtual ~tmt_impedance_paras(){}

public:
	float m_fSetting[2];//�迹��ֵ//������ֵ
	float m_fRate[2];// �迹ϵ��/����ϵ����ͨ���迹��ֵ��ϵ�������迹ֵ��
	float m_fImpedance[2];		//��·�迹��ֵ(��һ�ι����迹���ڶ��ι����迹)	m_fZ m_fZdev
	float m_fImpAngle[2];		//�迹��(��һ�ι����迹���ڶ��ι����迹) m_fPhi

	double m_fSCCurrent[2];		//��·���� ԭm_fItest  m_fItestdev
	double m_fSCVoltage[2];		//��·��ѹ ԭm_fVtest  m_fVtestdev
	int	  m_nFaultType[2];		//��������(0:A��ӵ�;1:B��ӵ�;2:C��ӵ�;3:AB��·;4:BC��·;5:CA��·;6:AB�ӵض�·;7:BC�ӵض�·;8:CA�ӵض�·;9:�����·;10:�����迹) 
	int   m_nFaultDir[2];		//���Ϸ��� ԭm_bFaultDirFirst m_bFaultDirSecond(0:������;1:������;)
	int   m_nCTPoint;			//TA������  S1=ָ��ĸ��,S2=ָ����·  m_bCTPoint(0:ָ��ĸ��;1:ָ����·;)
	int   m_nPTPoint;			//TV��װλ��  S1=ĸ�߲�,S2=��·��  m_bPTPoint(0:ĸ�߲�;1:��·��;)
	int   m_nCalMode;			//���㷽ʽ��ԭDis=0 Overcurrent=3 Search��ѡ(????�ò����е�����,�迹���ֵΪ0,�������ֵΪ3)(Add����ģ�ͣ�0-�������� 1-��ѹ���� 2-ϵͳ�迹����)
	//��Ƶ�仯��������ݹ��Ϸ������ͬ��Ϊ4�������򣩻�5��������
	float m_fPrepareTime;		//��̬ʱ��(�ò���Ϊ����ǰ����ʱ��,Ҳ�����仯ǰʱ��,���ݱ��෢���ݱ�ǰ�ĸ���ʱ��,���������迹�߽�,�����Ƕȵ�,һ���غ�բ����١����벻�øò���)
	float m_fPreFaultTime;		//����ǰʱ��(����ǰ����ʱ��,ÿ�ι���ǰ�Ĺ��ϸ���ʱ��)
	float m_fMaxFaultTime;			//����ʱ��
	float m_fMarginTime;//����ʱ��ԣ��
	BOOL	m_bImitatePT;		//�Ƿ�ģ��PT����
	int		m_nImitPTPhase;		//PT����ģ����  A B C AB BC CA ABC
	BOOL  m_bCBSimulation;		//��·��ģ��  S1=��ģ��,S2=ģ�� 0(0:��ģ��,1:ģ��)
	float m_fCBTripTime;		//��բʱ��	200ms��ģ���·��ʱ�ķ�բʱ�䣩
	float m_fCBCloseTime;		//��բʱ��	100ms��ģ���·��ʱ�ĺ�բʱ�䣩
	int   m_nFaultIncMode;		//��բ��ѡ�� 0-��� 1-��ֵ
	float m_fFaultAngle;		//��բ�� ��ԶΪ0
	float m_fFaultAng_0;		//��բ�ǵ���ʼֵ(���ݵ�1�ι��ϵĹ������ͼ���)
	int   m_nFaultTrigMode;		//���ϴ�����ʽ S1=ʱ��,S2=����,S3=��������H������,S4=GPS 0(0:ʱ�䴥��,1:��������,2:����ӵ㷭ת����,3:GPS����)
	BOOL  m_nFaultProperty;		//�������ʣ�0-˲ʱ 1-���� m_bLastFault
	BOOL  m_bTransFault;		//�Ƿ�ת���Թ��� (0:����ת���Թ���,1:��ת���Թ���)
//	int   m_nTransMode;			//����ת��ģʽ��1����������������ת����2�����غ�����ת��
	float m_fTransTime;			//����ת��ʱ��  0.1
	float m_fPostFaultTime;		//�������������ʱ��  2.000f
	//ͨ�ò���
	int   m_nVzDefine;			//Uz������� S1=0,S2=��3��3Vo,S3=-��3��3Vo,S4=3Vo,S5=-3Vo,S6=��ȡ��ѹ
	//0:+3U0,1:-3U0,2:+��3��3Vo,3:-��3��3Vo,4:��ͬ��A,5:��ͬ��B,6:��ͬ��C,7:��ͬ��AB,8:��ͬ��BC,9:��ͬ��CA,10:������ѹĸ��ѹ,11:������ѹĸ��ѹ,12:������ѹĸ��ѹ,13:������ѹĸ��ѹ,14:�����
	int	  m_nVzPhDefine;		//Uz�ο��ඨ��  S1=Va��λ,S2=Vb��λ,S3=Vc��λ,S4=Vab��λ,S5=Vbc��λ,S6=Vca��λ
	int   m_nK0CalMode;			//���򲹳�ϵ�����㷽ʽ 3  S1=|K0|,,Phi(K0),S2=RERL,,XEXL,S3=|Z0/Z1|,,Phi(Z0/Z1)
	float m_fK0Amp;				//|Ko|��Re(Ko) m_fRMRL
	float m_fK0Angle;			//Phi(Ko)��Im(Ko) m_fXMXL
	//��������
	float m_fIfh;				//���ɵ�������Search��Ϊ0
	float m_fPowerAngle;		//���ɹ��ǣ���Search��Ϊ20
	float m_fZs;				//��֪��ʲô�迹����ԶΪ1.0(ϵͳ�迹��ֵ)
	float m_fPhis;				//��֪��ʲô�迹����λ����ԶΪ90��ϵͳ�迹��λ��
	float m_fK0s;				//��֪��ʲôϵ������ԶΪ0
	float m_fK0sPh;				//��֪��ʲôϵ������ԶΪ0
	int	  m_nRXSelect;			//�迹��ʾ��ʽ 0-Z-Phi 1-RX  ģ����û�У���Ϊ0(�迹��﷽ʽ) zhouhj˵ �ײ��ò��������������Ϊ0��mym 2021-8-5

/////////////////////////////////////////������ȡ����///////////////////////////////////////////////////////////////////////////////
	float m_fUxInput_Mag;	//ͬ�ڵ�ѹ(��ͬ�ڷ�ʽ��Ч)
	float m_fUxInput_Ang;
	float	m_fUxHigh;			//��ѹ����ֵ
	float	m_fUxLow;			//��ѹ����ֵ
	long m_nOutputSwitchMode;//��ת������ʽ 0-ʱ�䴥�� 1-����������
	float	m_fBoutTimeTrig;	//��תʱ�䣬0Ϊ����ת
	float	m_fBoutHoldTime;	//��ת����ʱ��

	float  m_fRecloseTime;    //�غ�բʱ��
	float  m_fAfterAcceTime;    //�����ʱ��
	tmt_time	    m_tGps;
	long m_bIPlusDC;//�Ƿ���ӷ����ڷ���
//	float m_fTao;//˥��ʱ�䳣��

	long m_nDInputState[MAX_BINARYIN_COUNT];//������״̬  0:����;1������;2���غ�
	long m_nStateBOut[MAX_BINARYIN_COUNT];//�ö����Ʊ�ʶ��������״̬
	long m_nBinSelect;//������ѡ��ڼ���   0-ABCD 1-EFGH 0

	//2021-9-7  lijunqing
	double m_fR, m_fX;  //�迹ƽ����迹ֵ�����ڻ�ͼ

	void CalRX()
	{
		float fAngle = m_fImpAngle[0] * pi / 180;
		m_fR = m_fSetting[0] * cos(fAngle);
		m_fX = m_fSetting[0] * sin(fAngle);
	}
}tmt_ImpedanceParas;

typedef struct tmt_impedance_results
{
public:
	virtual void init()
	{
		m_fRealTestTime=0.0f;		//ʵ������ʱ��
		m_nTripNumbers=0;			//��բ(�غ�)�ܴ���, ��������¼��բ 4 ��
		m_fImp = m_fImpAngle = 0;
		m_fOverCurrent = m_fFaultVol = m_fFaultCurrent = 0;
		m_fRecloseTime = m_fSecondTripTime = m_fTripTime = 0;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			m_nActID[nIndex] = 0;
		}

		for(int i=0;i<2;i++)
		{
			for(int j=0;j<MAX_BINARYIN_COUNT;j++)
				m_fBinTripTime[j][i] = -1000.0f;
		}

		for(int i=0;i<4;i++)
		{
			m_fFirstTripTime[i] = m_fFirstTripTime[i+4] = 0;
			m_fRecordTime[i] = 0;
			m_fReturnTime[i] = m_fReturnTime[i+4] = 0;
		}

		m_nActA = m_nActB = m_nActC = 0;
		m_nActAcc = 0;
	}

	tmt_impedance_results()	
	{
//		init();
	}

	virtual ~tmt_impedance_results(){}

	void SetRecloseTime(float fValue)
	{
		if (fValue<=0)
		{
			return;
		}

		m_fRecloseTime = fValue;
	}

	void SetFault1TripTime(long nTripIndex,long nInputMapState,float fValue,bool bHasMapReclose)
	{
		if (fValue<=0)
		{
			return;
		}

		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_THREE)
		{
			m_fFirstTripTime[0] = fValue;
			m_fFirstTripTime[1] = fValue;
			m_fFirstTripTime[2] = fValue;
		}
		else if (nInputMapState == STT_IMPEDANCE_BIN_STATE_SINGLE)
		{
			m_fFirstTripTime[nTripIndex-bHasMapReclose] = fValue;
		}
	}

	void SetFaultTripTime(float *pfTripTime, long nTripIndex,long nInputMapState,float fValue,bool bHasMapReclose)
	{
		if (fValue<=0)
		{
			return;
		}

		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_THREE)
		{
			pfTripTime[0] = fValue;
			pfTripTime[1] = fValue;
			pfTripTime[2] = fValue;
		}
		else if (nInputMapState == STT_IMPEDANCE_BIN_STATE_SINGLE)
		{
			pfTripTime[nTripIndex-bHasMapReclose] = fValue;
		}
	}

	void SetFault2TripTime(long nTripIndex,long nInputMapState,float fValue)
	{
		if (nInputMapState == STT_IMPEDANCE_BIN_STATE_RECLOCE)
			return;

		if (fValue>=m_fSecondTripTime)
		{
			m_fSecondTripTime = fValue;
		}
	}

	float GetFirstTripTime()
	{
		float fValue = 0.0f;

		for (int nIndex = 0;nIndex<3;nIndex++)
		{
			if (fValue<m_fFirstTripTime[nIndex])
			{
				fValue = m_fFirstTripTime[nIndex];
			}
		}

		return fValue;
	}

	void CopyOwn(tmt_impedance_results* pDest)
	{
		pDest->m_fRealTestTime = m_fRealTestTime;
		pDest->m_nTripNumbers = m_nTripNumbers;
		pDest->m_fImp = m_fImp;
		pDest->m_fImpAngle = m_fImpAngle;
		pDest->m_fOverCurrent = m_fOverCurrent;
		pDest->m_fFaultCurrent = m_fFaultCurrent;
		pDest->m_fFaultVol = m_fFaultVol;
		pDest->m_fRecloseTime = m_fRecloseTime;
		pDest->m_fSecondTripTime = m_fSecondTripTime;
		pDest->m_fTripTime = m_fTripTime;

		pDest->m_nActA = m_nActA;
		pDest->m_nActB = m_nActB;
		pDest->m_nActC = m_nActC;
		pDest->m_nActD = m_nActD;
		pDest->m_nActAcc = m_nActAcc;

		for (int nIndex = 0;nIndex<MAX_BINARYIN_COUNT;nIndex++)
		{
			pDest->m_fBinTripTime[nIndex][0] = m_fBinTripTime[nIndex][0];
			pDest->m_fBinTripTime[nIndex][1] = m_fBinTripTime[nIndex][1];
			pDest->m_nActID[nIndex] = m_nActID[nIndex];
		}

		pDest->m_fTripTime = m_fTripTime;
	}

public:
	float m_fRealTestTime;			//ʵ������ʱ��
	int   m_nTripNumbers;			//��բ(�غ�)�ܴ���, ��������¼��բ 4 ��
	float m_fImp,m_fImpAngle;
	float m_fOverCurrent;
	float m_fFaultCurrent,m_fFaultVol;	//���ϵ�������ѹ
	float	m_fBinTripTime[MAX_BINARYIN_COUNT][2];//����ӵ�ÿ�ζ���(��բ,�غ�)ʱ��
	float		m_fFirstTripTime[8];
	float		m_fRecloseTime;
	float		m_fSecondTripTime;
	float		m_fRecordTime[4];
	float		m_fReturnTime[8];
	float		m_fTripTime;
	int		m_nActID[MAX_BINARYIN_COUNT];//��ԭ��m_nActA��B��C��ͳһΪ����

	long m_nActA,m_nActB,m_nActC,m_nActD;
	long m_nActAcc;

}tmt_ImpedanceResults;

//����2�����Ƿ�ʹ��ImpBase��Ϊ����,ֻ���غ�բ����ٲ��ǲ���ImpBase��Ϊ����,�غ�բ�����ʹ��״̬������Ϊ����
void stt_xml_serialize_impedance_paras(tmt_ImpedanceParas *pParas, CSttXmlSerializeBase *pXmlSierialize,BOOL bImpBase);
void stt_xml_serialize_impedance_results(tmt_ImpedanceResults *pResults, CSttXmlSerializeBase *pXmlSierialize);