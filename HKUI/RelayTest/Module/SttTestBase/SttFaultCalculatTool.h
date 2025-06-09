#pragma once
#include "SttComplexp.h"

#define IMPEDANCE_FAULT_TYPE_AN                                                 0//�迹��Ĺ������Ͷ���
#define IMPEDANCE_FAULT_TYPE_BN                                                 1
#define IMPEDANCE_FAULT_TYPE_CN                                                 2
#define IMPEDANCE_FAULT_TYPE_AB                                                 3
#define IMPEDANCE_FAULT_TYPE_BC                                                 4
#define IMPEDANCE_FAULT_TYPE_CA                                                 5
#define IMPEDANCE_FAULT_TYPE_ABN                                                6
#define IMPEDANCE_FAULT_TYPE_BCN                                                7
#define IMPEDANCE_FAULT_TYPE_CAN                                                8
#define IMPEDANCE_FAULT_TYPE_ABC                                                9
#define IMPEDANCE_FAULT_TYPE_ONE                                                10

#define IMPEDANCE_VZ_TYPE_Positive_3U0                                          0//
#define IMPEDANCE_VZ_TYPE_Negative_3U0                                          1//
#define IMPEDANCE_VZ_TYPE_Positive_Squ3_3U0                                     2//
#define IMPEDANCE_VZ_TYPE_Negative_Squ3_3U0                                     3//
#define IMPEDANCE_VZ_TYPE_Check_Syn_A                                           4//
#define IMPEDANCE_VZ_TYPE_Check_Syn_B                                           5//
#define IMPEDANCE_VZ_TYPE_Check_Syn_C                                           6//
#define IMPEDANCE_VZ_TYPE_Check_Syn_AB                                          7//
#define IMPEDANCE_VZ_TYPE_Check_Syn_BC                                          8//
#define IMPEDANCE_VZ_TYPE_Check_Syn_CA                                          9//
#define IMPEDANCE_VZ_TYPE_Check_LineNoBusHas                                   10//
#define IMPEDANCE_VZ_TYPE_Check_LineHasBusNo                                   11//
#define IMPEDANCE_VZ_TYPE_Check_LineNoBusNo                                    12//
#define IMPEDANCE_VZ_TYPE_Check_LineHasBusHas                                  13//
#define IMPEDANCE_VZ_TYPE_NULL                                                 14//


class CSttFaultCalculatTool
{
public:
	CSttFaultCalculatTool(void);
	virtual ~CSttFaultCalculatTool(void);

	float GetTimeAfterTrigger(float fCBTripTimeSecond,BOOL bCBSimulation);//ͳһ��ΪsΪ��λ,��·��ģ���ʱ�䵥λ��Ϊs
	float CalImpPlusDC_Tao(float fImpedance,float fImpAngle);  //�����迹�� ֱ��������˥��ʱ�䳣��: 
	void CalPreFaultComplex(Complex *pComplex,float fAmplitude,float fStartAngle);//ͨ����ֵ��A����ʼ��λ��������������ѹʸ��ֵ
	void CalVzComplex(Complex *pUzComplex,Complex *pU_Complex,long nVzDefine);//����Vzʸ��ֵ nVzDefine��������
	////0:+3U0,1:-3U0,2:+��3��3Vo,3:-��3��3Vo,4:��ͬ��A,5:��ͬ��B,6:��ͬ��C,7:��ͬ��AB,8:��ͬ��BC,9:��ͬ��CA,
	//10:������ѹĸ��ѹ,11:������ѹĸ��ѹ,12:������ѹĸ��ѹ,13:������ѹĸ��ѹ,14:�����

	void Cal_SimulatePT(int nPTPhase, Complex *cmpUI);//����ģ��PT����ʱ��ֵ

	//����1λ��բ�Ƕ�ֵ,����2Ϊ��������,����3Ϊ�����ĵ�ѹ��բ��,����4Ϊ�����ĵ�����բ��,����5Ϊ��Ҫ���ú�բ�ǵ�ͨ��
	void CalculateCloseAngle(float fCloseAngel,long nFaultType,float fUaAngle,float fUbAngle,float fUcAngle,
		float fPowerAngle,
		float& fVolAngle,float& fCurAngle,int& nChanel);

	void Cal_VzAccordDefine(int nVzDefine, Complex *cmpUI,float fUxInput_Mag,float fUxInput_Ang, float fUxHigh, float fUxLow,BOOL bAfterTrip);	//zhouhj 20211005 ���һ��������ʶ�Ƿ�Ϊ��բ��״̬
	// ͨ�ã�����Ux�����ʽ����Vz��cmpUIΪ����������·��ѹ������,fUxHigh-��ѹ����ֵ fUxLow-��ѹ����ֵ ,�˴���Ҫ�����غ�բ����ٷ�ʽ(����״̬����)
	void Cal_VzAccordDefine_ImpBase(int nVzDefine, Complex *cmpUI,int nVzPhDefine,float fUzAng);//nVzPhDefineΪUz�ο��ඨ��,fUzAngΪ��Բο����������


	BOOL F1njs(double Rate,BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void F11js(double Rate,BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void F3js(BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void F11njs(BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void FRWYjs(BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	BOOL Calculat(double Rate,BOOL bFaultDirection,BOOL bCTDirection,int nCalMode,int nFaultType,int nPhaseRef,double  RefAngle,
		double  Umax,double  Unom,double  Imax,double *Ishort,double *Vshort,Complex Inom,
		Complex  zl,Complex k0,Complex zs,Complex k0s,Complex *FVa,Complex *FVb,Complex *FVc,
		Complex *FIa,Complex *FIb,Complex *FIc);
	Complex GroundFactor(int nK0CalMode,double fRMRL,double fXMXL,double fPh);

	//zhouhj ���ܼ����м���͵�ѹ����ʱ,�仯����ѡ��͵�ѹ;����1Ϊ3���ѹʸ��ֵ��ָ��;����2Ϊ��ǰ�͵�ѹֵ;����3λ��ѹģʽ(0���ѹ;1�ߵ�ѹ)
	void CalVolVaues_LowVol(Complex *pComplexU,float fCurU_Amp,int nUSetMode);
	//zhouhj ���ܼ����м���͵�ѹ����ʱ,�仯����ѡ�����ѹ;����2λ��׼����ѹ��ֵ
	void CalVolVaues_U2(Complex *pComplexU,float fStdLN_Vol,float fCurU_Amp);
	//zhouhj ���ܼ����м���͵�ѹ����ʱ,�仯����ѡ�������ѹ
	void CalVolVaues_3U0(Complex *pComplexU,float fStdLN_Vol,float fCurU_Amp);
};
