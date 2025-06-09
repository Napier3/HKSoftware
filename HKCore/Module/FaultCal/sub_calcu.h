// sub_calcu.h: interface for the Csub_calcu class.
// ����������: �ַ���ת��Ϊ����StringToData(...)
//             ֱ������ͼ�����ת��xyTopo(...),poToxy(...)
//             ��·����
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SUB_CALCU_H__21109615_7400_4065_B1FA_39CA313849C1__INCLUDED_)
#define AFX_SUB_CALCU_H__21109615_7400_4065_B1FA_39CA313849C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Csub_calcu  
{
public:
	//�߷�������
	void calcu_ABCtoPP(float mag1,float mag2,float mag3,float ang1,float ang2,float ang3,float* thePPMag,float* thePPAng);
	void calcu_PPtoABC(float mag1,float mag2,float mag3,float ang1,float ang2,float ang3,float* theABCMag,float* theABCAng);
	//���������(U1,U2, 3U0)
	void calcu_ABCto120(float mag1,float mag2,float mag3,float ang1,float ang2,float ang3,float* the120Mag,float* the120Ang);
	void calcu_120toABC(float mag1,float mag2,float mag0,float ang1,float ang2,float ang0,float* theABCMag,float* theABCAng);
	//���ʼ���(����,����)
	void calcu_PQ(float Umag,float Uang,float Imag,float Iang,float *theP,float *theQ,float *theCos);	
	void calcu_PQ(int nCalcuMode,
					float U1mag,float U1ang,float U2mag,float U2ang,float U3mag,float U3ang,
					float I1mag,float I1ang,float I2mag,float I2ang,float I3mag,float I3ang,
					float *theP,float *theQ,float *theCos);
	//----------------------------------------------------------------------
	//��������: �Ӽ��˳�,xy->������,������->xy
	void comp_Add(float mag1,float ang1,float mag2,float ang2,float *mag,float *ang);
	void comp_Sub(float mag1,float ang1,float mag2,float ang2,float *mag,float *ang);
	void comp_Mult(float x1,float y1,float x2,float y2,float *x,float *y);
	void comp_Divi(float x1,float y1,float x2,float y2,float *x,float *y);
	void xy_to_po(float x,float y,float *mag,float *ang);
	void po_to_xy(float mag,float ang,float *x,float *y);
	//-----------��·����: nFaultDirection=0:--�������; 1:--�������--------
	struct struct_PhaseSet
	{
		float Mag;	float Ang;
	};
	struct struct_PhaseSet m_Es[3];
	struct struct_PhaseSet m_Up[3];
	struct struct_PhaseSet m_Ip[3];
	//����ǰ--����״̬: Ue--������װ���Ķ��ѹ, ILoad_Mag,Ang--���ɵ���, ��λ(-,�ͺ��ڵ�ѹ; +,��ǰ�ڵ�ѹ)
	void calcu_LoadState(float Ue,float ILoad_Mag,float ILoad_Ang);
	//��·�����㶨(������װ���Ĺ���������㶨)
	void f1_If(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If, 
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	void f11_If(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If, 
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			   );
	void f2_If(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If, 
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	void f3_If(int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If,
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	//��·��ѹ�㶨(������װ���Ĺ������ѹ�㶨)
	void f1_Uf(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float Uf,
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	void f11_Uf(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float Uf, 
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			   );
	void f2_Uf(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float Uf, 
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	void f3_Uf(int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float Uf, 
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	//��Դ�迹�㶨(��Դ���ĵ�ѹ���迹�㶨)
	void f1_Zs(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	void f11_Zs(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang, 
				float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			   );
	void f2_Zs(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang, 
				float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	void f3_Zs(int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang, 
				float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
				float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
			  );
	//��Ƶ�仯���迹(ר��ģ��), 2009-4-9, 2013-7-19
	void f1_gp(int nCalcuMode,
				int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If, 
				float Zzd_Mag,float Zzd_Ang,float k,float m
			  );
	void f11_gp(int nCalcuMode,
				int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If, 
				float Zzd_Mag,float Zzd_Ang,float k,float m
			  );
	void f2_gp(int nCalcuMode,
				int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If, 
				float Zzd_Mag,float Zzd_Ang,float k,float m
			  );
	void f3_gp(int nCalcuMode,
				int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
				float If, 
				float Zzd_Mag,float Zzd_Ang,float k,float m
			  );


public:
	Csub_calcu();
	virtual ~Csub_calcu();

private:
	//Խ�޶���, �Ƕ������� -360 - 360
	float CheckLimit(float theValue,float theMax,float theMin);
};

#endif // !defined(AFX_SUB_CALCU_H__21109615_7400_4065_B1FA_39CA313849C1__INCLUDED_)
