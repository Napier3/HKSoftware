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
����  ����˵��
void Calculat(double Rate,//��ϵ��ֻ�й�Ƶ�仯�������õ���������1
			  bool bFaultDirection,//���Ϸ���0-������1-������Ĭ��Ϊ1
			  bool bCTDirection,//CT����������: 0--ָ����·, 1--ָ��ĸ�ߣ�Ĭ��Ϊ0
			  int nCalMode,//����ģʽ�����㷽ʽѡ�� ���������ò���ѡ,�����������Ϊ3�����롢�迹�߽�����Ϊ0����Ƶ�仯��������ݹ��Ϸ������ͬ��Ϊ4�������򣩻�5�������򣩣�Ĭ��Ϊ0
			  int nFaultType, //�������ͣ�0-9�ֱ�ΪA��ӵء�B��ӵء�C��ӵء�AB��·��BC��·��CA��·��AB�ӵض�·��BC�ӵض�·��CA�ӵض�·�������·
			  int nPhaseRef,//  int nPhaseRef[11]={1,2,0,2,0,1,2,0,1,0,0};�̶�ֵͨ����������ѡ��
			  double  RefAngle,//float nAngle[11] = {(float)m_fUI[0].arg(),(float)m_fUI[1].arg(),(float)m_fUI[2].arg(),(float)m_fUI[0].arg()+30.0f
					 ,(float)m_fUI[1].arg()+30.0f,(float)m_fUI[2].arg()+30.0f,(float)m_fUI[0].arg()+30.0f,(float)m_fUI[1].arg()+30.0f
					 ,(float)m_fUI[2].arg()+30.0f,(float)m_fUI[0].arg(),(float)m_fUI[2].arg()}; �̶�ֵͨ��nPhaseRefѡ��
			  double  Umax, //����ѹ
			  double  Unom,//���ѹ
			  double  Imax,//������
			  double *Ishort,//��·����
			  double *Vshort,//��·��ѹ
			  Complex Inom,//���ɵ����븺�ɹ���
			  Complex  zl,//��·�迹���·�迹��
			  Complex k0,
			  Complex zs, //ת�����·�迹���·�迹�ǣ�һ�㲻��
			  Complex k0s,//ת�������򲹳�ϵ����һ�㲻��
			  Complex *FVa,//��������
			  Complex *FVb,//��������
			  Complex *FVc,//��������
			  Complex *FIa,//��������
			  Complex *FIb,//��������
			  Complex *FIc);//��������
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
class CFaultCalculat
{
public:
	CFaultCalculat();
	//�������
	void F1njs(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	//�������
	void F11js(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	//�������
	void F3js(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	//����ӵ�
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
