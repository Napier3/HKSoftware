#pragma once
#include "SttComplexp.h"

#define IMPEDANCE_FAULT_TYPE_AN                                                 0//阻抗类的故障类型定义
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

	float GetTimeAfterTrigger(float fCBTripTimeSecond,BOOL bCBSimulation);//统一改为s为单位,断路器模拟的时间单位都为s
	float CalImpPlusDC_Tao(float fImpedance,float fImpAngle);  //计算阻抗类 直流分量的衰减时间常数: 
	void CalPreFaultComplex(Complex *pComplex,float fAmplitude,float fStartAngle);//通过幅值及A相起始相位计算三相电流或电压矢量值
	void CalVzComplex(Complex *pUzComplex,Complex *pU_Complex,long nVzDefine);//计算Vz矢量值 nVzDefine定义如下
	////0:+3U0,1:-3U0,2:+√3×3Vo,3:-√3×3Vo,4:检同期A,5:检同期B,6:检同期C,7:检同期AB,8:检同期BC,9:检同期CA,
	//10:检线无压母有压,11:检线有压母无压,12:检线无压母无压,13:检线有压母有压,14:无输出

	void Cal_SimulatePT(int nPTPhase, Complex *cmpUI);//计算模拟PT断线时的值

	//参数1位合闸角定值,参数2为故障类型,参数3为计算后的电压合闸角,参数4为计算后的电流合闸角,参数5为需要设置合闸角的通道
	void CalculateCloseAngle(float fCloseAngel,long nFaultType,float fUaAngle,float fUbAngle,float fUcAngle,
		float fPowerAngle,
		float& fVolAngle,float& fCurAngle,int& nChanel);

	void Cal_VzAccordDefine(int nVzDefine, Complex *cmpUI,float fUxInput_Mag,float fUxInput_Ang, float fUxHigh, float fUxLow,BOOL bAfterTrip);	//zhouhj 20211005 最后一个参数标识是否为跳闸后状态
	// 通用，根据Ux输出方式计算Vz，cmpUI为包含至少四路电压的数组,fUxHigh-有压测试值 fUxLow-无压测试值 ,此处主要用于重合闸后加速方式(常规状态序列)
	void Cal_VzAccordDefine_ImpBase(int nVzDefine, Complex *cmpUI,int nVzPhDefine,float fUzAng);//nVzPhDefine为Uz参考相定义,fUzAng为相对参考相的相对相角


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

	//zhouhj 低周减载中计算低电压闭锁时,变化类型选择低电压;参数1为3相电压矢量值首指针;参数2为当前低电压值;参数3位电压模式(0相电压;1线电压)
	void CalVolVaues_LowVol(Complex *pComplexU,float fCurU_Amp,int nUSetMode);
	//zhouhj 低周减载中计算低电压闭锁时,变化类型选择负序电压;参数2位标准额定相电压幅值
	void CalVolVaues_U2(Complex *pComplexU,float fStdLN_Vol,float fCurU_Amp);
	//zhouhj 低周减载中计算低电压闭锁时,变化类型选择零序电压
	void CalVolVaues_3U0(Complex *pComplexU,float fStdLN_Vol,float fCurU_Amp);
};
