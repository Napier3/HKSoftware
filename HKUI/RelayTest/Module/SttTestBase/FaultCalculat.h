// FaultCalculat.h: interface for the CFaultCalculat class.
//
//////////////////////////////////////////////////////////////////////
#define PI 3.1415926

#ifndef __FAULTCALCULAT_H
#define __FAULTCALCULAT_H
//#include "Complexp.h"
#include "SttComplexp.h"
//const double PI=3.1415926;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
函数  参数说明
void Calculat(double Rate,//此系数只有工频变化量距离用到，其他是1
			  bool bFaultDirection,//故障方向，0-反方向，1-正方向，默认为1
			  bool bCTDirection,//CT极性正方向: 0--指向线路, 1--指向母线，默认为0
			  int nCalMode,//计算模式，计算方式选择 如界面此设置不可选,择过流、零序为3，距离、阻抗边界搜索为0，工频变化量距离根据故障方向而不同，为4（正方向）或5（反方向），默认为0
			  int nFaultType, //故障类型，0-9分别为A相接地、B相接地、C相接地、AB短路、BC短路、CA短路、AB接地短路、BC接地短路、CA接地短路、三相短路
			  int nPhaseRef,//  int nPhaseRef[11]={1,2,0,2,0,1,2,0,1,0,0};固定值通过故障类型选择
			  double  RefAngle,//float nAngle[11] = {(float)m_fUI[0].arg(),(float)m_fUI[1].arg(),(float)m_fUI[2].arg(),(float)m_fUI[0].arg()+30.0f
					 ,(float)m_fUI[1].arg()+30.0f,(float)m_fUI[2].arg()+30.0f,(float)m_fUI[0].arg()+30.0f,(float)m_fUI[1].arg()+30.0f
					 ,(float)m_fUI[2].arg()+30.0f,(float)m_fUI[0].arg(),(float)m_fUI[2].arg()}; 固定值通过nPhaseRef选择
			  double  Umax, //最大电压
			  double  Unom,//额定电压
			  double  Imax,//最大电流
			  double *Ishort,//短路电流
			  double *Vshort,//短路电压
			  Complex Inom,//负荷电流与负荷功角
			  Complex  zl,//短路阻抗与短路阻抗角
			  Complex k0,
			  Complex zs, //转换后短路阻抗与短路阻抗角，一般不用
			  Complex k0s,//转换后零序补偿系数，一般不用
			  Complex *FVa,//传出参数
			  Complex *FVb,//传出参数
			  Complex *FVc,//传出参数
			  Complex *FIa,//传出参数
			  Complex *FIb,//传出参数
			  Complex *FIc);//传出参数
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
class CFaultCalculat
{
public:
	CFaultCalculat();
	//单项故障
	void F1njs(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	//多项故障
	void F11js(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	//三项故障
	void F3js(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	//多项接地
	void F11njs(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void FRWYjs(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void Calculat(double Rate,bool bFaultDirection,bool bCTDirection,int nCalMode,int nFaultType,int nPhaseRef,double  RefAngle,
		double  Umax,double  Unom,double  Imax,double *Ishort,double *Vshort,Complex Inom,
		Complex  zl,Complex k0,Complex zs,Complex k0s,Complex *FVa,Complex *FVb,Complex *FVc,
		Complex *FIa,Complex *FIb,Complex *FIc);
	Complex GroundFactor(int nK0CalMode,double fRMRL,double fXMXL,double fPh);

	static void  VI0Cal(float Vx1, float Phx1, float Vx2, float Phx2, float Vx3, float Phx3, float *Vx, float *Phx);
private:

};

#endif
