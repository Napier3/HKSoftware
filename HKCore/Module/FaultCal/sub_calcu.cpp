// sub_calcu.cpp: implementation of the Csub_calcu class.
//
//2010-5-12: 取消单相功率计算, 修改为三相功率计算(可兼容单相功率计算)
//2010-5-13: 为了提高计算精度, 修改计算函数中的中间变量为 double 型
//2012-5-4: 定阻抗(Zs)计算模型时, 如果短路电流太大(超过10A), 
//          则自动调整故障后的系统侧电源电压 Es;
//          (即认为故障后系统侧不再是无穷大恒定电压源);
//2013-7-19: 修改工频变化量短路计算模型, 增加 nCalcuMode, 兼容
//           南瑞继保和许继两个厂家的计算公式; 
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sub_calcu.h"
#include <math.h>
#include <stdlib.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#ifdef PI
	#undef PI
#endif
#define PI 3.14159265358979323846
#define MAX_IF 10.0f	//定 Zs 时的最大允许电流
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Csub_calcu::Csub_calcu()
{

}

Csub_calcu::~Csub_calcu()
{

}

//---------------------------------------------------------------------------
//越限定限
float Csub_calcu::CheckLimit(float theValue, float theMax, float theMin)
{
	int i=(int)theMax;
	int j=(int)theMin;

	if(i==360 && j==-360)
	{
		theValue=(float)fmod(theValue,360.0f);
	}
	else
	{
		if(theValue>theMax) theValue=theMax;
		if(theValue<theMin) theValue=theMin;
	}

	return theValue;
}
//---------------------------------------------------------------------------
//根据 ABC 计算线(电压电流)分量: uab,ubc,uca
void Csub_calcu::calcu_ABCtoPP(float mag1,float mag2,float mag3,float ang1,float ang2,float ang3,float* thePPMag,float* thePPAng)
{
	int i;
	float Mag[3],Ang[3];
	int nIndex1,nIndex2;
	float theMag,theAng;

	Mag[0]=mag1;
	Mag[1]=mag2;
	Mag[2]=mag3;
	Ang[0]=ang1;
	Ang[1]=ang2;
	Ang[2]=ang3;
	for(i=0;i<3;i++)
	{
		//AB,BC,CA
		nIndex1=i;
		nIndex2=i+1;
		if(nIndex2==3) nIndex2=0;
		comp_Sub(Mag[nIndex1],Ang[nIndex1],Mag[nIndex2],Ang[nIndex2],
				&theMag,&theAng);
		thePPMag[i]=theMag;
		thePPAng[i]=theAng;
	}
}

//根据线(电压电流)分量: uab,ubc,uca, 计算 ABC
//此处, 直接假定 Uab+Ubc+Uca=0
void Csub_calcu::calcu_PPtoABC(float mag1,float mag2,float mag3,float ang1,float ang2,float ang3,float* theABCMag,float* theABCAng)
{
	//由 Uab=Ua-Ub, Ubc=Ub-Uc, Uca=Uc-Ua,
	//结合 Uab+Ubc+Uca=0
	//得:  Ub=(Ubc-Uab)/3
	//     Ua=Ub+Uab;
	//     Uc=Ub-Ubc;
	float theMag,theAng;
	float Uab_Mag,Uab_Ang;
	float Ubc_Mag,Ubc_Ang;

	Uab_Mag=mag1;
	Uab_Ang=ang1;
	Ubc_Mag=mag2;
	Ubc_Ang=ang2;
	comp_Sub(Ubc_Mag,Ubc_Ang,Uab_Mag,Uab_Ang,&theMag,&theAng);
	theMag/=3.0f;
	theABCMag[1]=theMag;	//Ub
	theABCAng[1]=theAng;
	comp_Add(theMag,theAng,Uab_Mag,Uab_Ang,&theMag,&theAng);
	theABCMag[0]=theMag;	//Ua
	theABCAng[0]=theAng;
	//
	theMag=theABCMag[1];
	theAng=theABCAng[1];
	comp_Sub(theMag,theAng,Ubc_Mag,Ubc_Ang,&theMag,&theAng);
	theABCMag[2]=theMag;	//Uc
	theABCAng[2]=theAng;
}

//---------------------------------------------------------------------------
//根据 ABC 计算序(电压电流)分量: u1,u2,3u0
void Csub_calcu::calcu_ABCto120(float mag1,float mag2,float mag3,float ang1,float ang2,float ang3,float* the120Mag,float* the120Ang)
{
	float vax,vbx,vcx;
	float vay,vby,vcy;
	double va1x,va2x,va0x;
	double va1y,va2y,va0y;
	double temp;
	float tempMag,tempAng;

	//计算各相量的直角坐标分量
	po_to_xy(mag1,ang1,&vax,&vay);
	po_to_xy(mag2,ang2,&vbx,&vby);
	po_to_xy(mag3,ang3,&vcx,&vcy);
	//计算序分量
	temp=sqrt(3.0)/2.0;
	va1x=(vax-vbx/2.0-vcx/2.0-vby*temp+vcy*temp)/3.0;
	va1y=(vay-vby/2.0-vcy/2.0+vbx*temp-vcx*temp)/3.0;
	va2x=(vax-vbx/2.0-vcx/2.0+vby*temp-vcy*temp)/3.0;
	va2y=(vay-vby/2.0-vcy/2.0-vbx*temp+vcx*temp)/3.0;
	va0x=(double)vax+vbx+vcx;	//3U0
	va0y=(double)vay+vby+vcy;	//3U0
	//转换为极坐标形式
	xy_to_po((float)va1x,(float)va1y,&tempMag,&tempAng);
	the120Mag[0]=tempMag;
	the120Ang[0]=tempAng;
	xy_to_po((float)va2x,(float)va2y,&tempMag,&tempAng);
	the120Mag[1]=tempMag;
	the120Ang[1]=tempAng;
	xy_to_po((float)va0x,(float)va0y,&tempMag,&tempAng);
	the120Mag[2]=tempMag;
	the120Ang[2]=tempAng;
}

//根据序(电压电流)分量: u1,u2,3u0, 计算 ABC
void Csub_calcu::calcu_120toABC(float mag1,float mag2,float mag0,float ang1,float ang2,float ang0,float* theABCMag,float* theABCAng)
{
	float tempMag,tempAng;

	mag0/=3.0f;
	//ua=u1+u2+u0
	comp_Add(mag1,ang1,mag2,ang2,&tempMag,&tempAng);
	comp_Add(tempMag,tempAng,mag0,ang0,&tempMag,&tempAng);
	theABCMag[0]=tempMag;
	theABCAng[0]=tempAng;

	//ub=u1*∠-120 + u2*∠120 + u0
	comp_Add(mag1,ang1-120.0f,mag2,ang2+120.0f,&tempMag,&tempAng);
	comp_Add(tempMag,tempAng,mag0,ang0,&tempMag,&tempAng);
	theABCMag[1]=tempMag;
	theABCAng[1]=tempAng;

	//uc=u1*∠120 + u2*∠-120 + u0
	comp_Add(mag1,ang1+120.0f,mag2,ang2-120.0f,&tempMag,&tempAng);
	comp_Add(tempMag,tempAng,mag0,ang0,&tempMag,&tempAng);
	theABCMag[2]=tempMag;
	theABCAng[2]=tempAng;
}

//功率计算(单相): P,Q,cos
void Csub_calcu::calcu_PQ(float Umag,float Uang,float Imag,float Iang,float *theP,float *theQ,float *theCos)
{
	double tempAng;

	tempAng=(Uang-Iang)*PI/180.0;
	*theP=(float)(Umag*Imag*cos(tempAng));
	*theQ=(float)(Umag*Imag*sin(tempAng));
	*theCos=(float)cos(tempAng);
}

//功率计算(三相): P,Q,cos
void Csub_calcu::calcu_PQ(int nCalcuMode,
						  float U1mag,float U1ang,float U2mag,float U2ang,float U3mag,float U3ang,
						  float I1mag,float I1ang,float I2mag,float I2ang,float I3mag,float I3ang,
						  float *theP,float *theQ,float *theCos)
{
	double P,Q;
	float theU,theI,theAng;
	int i;
	struct_PhaseSet U[3];
	struct_PhaseSet I[3];

	U[0].Mag=U1mag;
	U[0].Ang=U1ang;
	U[1].Mag=U2mag;
	U[1].Ang=U2ang;
	U[2].Mag=U3mag;
	U[2].Ang=U3ang;
	I[0].Mag=I1mag;
	I[0].Ang=I1ang;
	I[1].Mag=I2mag;
	I[1].Ang=I2ang;
	I[2].Mag=I3mag;
	I[2].Ang=I3ang;

	P=0.0;
	Q=0.0;
	switch(nCalcuMode)
	{
	case 0:		//0--三表计法: S = ∑U*I(共轭)
		for(i=0;i<3;i++)
		{
			theU=U[i].Mag;
			theI=I[i].Mag;
			theAng=(float)((U[i].Ang-I[i].Ang)*PI/180.0);
			P+=theU*theI*cos(theAng);
			Q+=theU*theI*sin(theAng);
		}
		break;
	case 1:		//1--两表计法: S = Uab * Ic(共轭) + Ucb * Ia(共轭)
		comp_Sub(U[0].Mag,U[0].Ang,U[1].Mag,U[1].Ang,&theU,&theAng);
		theI=I[2].Mag;
		theAng=(float)((theAng-I[2].Ang)*PI/180.0);
		P+=theU*theI*cos(theAng);
		Q+=theU*theI*sin(theAng);
		//
		comp_Sub(U[2].Mag,U[2].Ang,U[1].Mag,U[1].Ang,&theU,&theAng);
		theI=I[0].Mag;
		theAng=(float)((theAng-I[0].Ang)*PI/180.0);
		P+=theU*theI*cos(theAng);
		Q+=theU*theI*sin(theAng);
		break;
	default:
		break;
	}
	theU=(float)sqrt(P*P+Q*Q);
	if(theU<0.00001)
		theAng=0.0;
	else
		theAng=(float)(P/theU);

	*theP=(float)P;
	*theQ=(float)Q;
	*theCos=theAng;
}

//--------------------------------------------------------------------
void Csub_calcu::comp_Add(float mag1,float ang1,float mag2,float ang2,float *mag,float *ang)
{
	float x1,y1;
	float x2,y2;
	double x,y;

	po_to_xy(mag1,ang1,&x1,&y1);
	po_to_xy(mag2,ang2,&x2,&y2);
	x=(double)x1+x2;
	y=(double)y1+y2;
	xy_to_po((float)x,(float)y,&x1,&y1);
	*mag=x1;
	*ang=y1;
}

void Csub_calcu::comp_Sub(float mag1,float ang1,float mag2,float ang2,float *mag,float *ang)
{
	float x1,y1;
	float x2,y2;
	double x,y;

	po_to_xy(mag1,ang1,&x1,&y1);
	po_to_xy(mag2,ang2,&x2,&y2);
	x=(double)x1-x2;
	y=(double)y1-y2;
	xy_to_po((float)x,(float)y,&x1,&y1);
	*mag=x1;
	*ang=y1;
}

void Csub_calcu::comp_Mult(float x1,float y1,float x2,float y2,float *x,float *y)
{
	*x=x1*x2-y1*y2;
	*y=x1*y2+x2*y1;
}

void Csub_calcu::comp_Divi(float x1,float y1,float x2,float y2,float *x,float *y)
{
	double temp=(double)(x2*x2+y2*y2);

	if(fabs(temp)<=0.00001f)
	{
		*x=100000.0f;
		*y=100000.0f;
	}
	else
	{
	    temp=1.0/temp;
		*x=(float)((x1*x2+y1*y2)*temp);
		*y=(float)((-x1*y2+x2*y1)*temp);
	}
}

void Csub_calcu::xy_to_po(float x,float y,float *mag,float *ang)
{
	double  angPerRad=180.0/PI;

	*mag=(float)sqrt(x*x+y*y);
	if(*mag<=0.00001f)
	    *ang=0.0f;
	else
	    *ang=(float)(asin(y/(*mag))*angPerRad);
	if(x<0.0f)
	{
		if(y>0.0f)
			*ang=180.0f-(*ang);
		else
			*ang=-180.0f-(*ang);
	}
}

void Csub_calcu::po_to_xy(float mag,float ang,float *x,float *y)
{
	double  radPerAng=PI/180.0f;

	ang=(float)(ang*radPerAng);
	*x=(float)(mag*cos(ang));
	*y=(float)(mag*sin(ang));
	if(fabs(*x)<=0.00001)
		*x=0.0f;
	if(fabs(*y)<=0.00001)
		*y=0.0f;
}

// Load: 负荷状态:  -------------------------------------------------------
void Csub_calcu::calcu_LoadState(float Ue,float ILoad_Mag,float ILoad_Ang)
{
	int i;

	m_Up[0].Ang=0.0f;
	m_Up[1].Ang=-120.0f;
	m_Up[2].Ang=120.0f;
	for(i=0;i<3;i++)
	{
		m_Up[i].Mag=Ue;
		m_Ip[i].Mag=ILoad_Mag;
		if(m_Ip[i].Mag==0.0f)
			m_Ip[i].Ang=0.0f;
		else
			m_Ip[i].Ang=CheckLimit(m_Up[i].Ang+ILoad_Ang,360.0f,-360.0f);
		if(m_Ip[i].Ang>180.0f) m_Ip[i].Ang=m_Ip[i].Ang-360.0f;
		if(m_Ip[i].Ang<-180.0f) m_Ip[i].Ang=m_Ip[i].Ang+360.0f;
	}
	for(i=0;i<3;i++)
	{
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

// f1: 单相接地---------------------------------------------------------
void Csub_calcu::f1_If(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float If, 
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	int i;
	float  Zl_x,Zl_y,kZl_x,kZl_y;
	float  Zm_x,Zm_y,Zm_Mag,Zm_Ang;
	int nIndex;

	//近似以 Es 代替保护安装处的稳态运行电压 Vs
	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);
	Zm_x=Zl_x+kZl_x;
	Zm_y=Zl_y+kZl_y;
	xy_to_po(Zm_x,Zm_y,&Zm_Mag,&Zm_Ang);
	if(Zm_Mag<=0.0001f)
		Zm_Ang=Zl_Ang;

	//1. 计算短路点处的电流 If
	nIndex=phaseNo;
	for(i=0;i<3;i++)
	{
		if(i==nIndex)
		{
			m_Ip[i].Mag=If;
			m_Ip[i].Ang=m_Es[i].Ang-Zm_Ang;
		}
		else
		{
			m_Ip[i].Mag=0.0f;
			m_Ip[i].Ang=0.0f;
		}
	}
	//2. 计算保护安装处的电压: 
	for(i=0;i<3;i++)
	{
		if(i==nIndex)
		{
			//短路电流 If 导致的电压
			m_Up[i].Mag=m_Ip[i].Mag*Zm_Mag;
			m_Up[i].Ang=m_Ip[i].Ang+Zm_Ang;;
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else
		{
			m_Up[i].Mag=m_Es[i].Mag;
			m_Up[i].Ang=m_Es[i].Ang;
		}
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang+=180.0f;
			else
				m_Ip[i].Ang-=180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f1_Uf(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float Uf,
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	float  Zl_x,Zl_y,kZl_x,kZl_y;
	float  Zm_x,Zm_y,Zm_Mag,Zm_Ang;
	float  If;

	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);
	Zm_x=Zl_x+kZl_x;
	Zm_y=Zl_y+kZl_y;
	xy_to_po(Zm_x,Zm_y,&Zm_Mag,&Zm_Ang);

	if(Zm_Mag<=0.0001f)
		If=10000.0f;
	else
		If=Uf/Zm_Mag;
	f1_If(phaseNo,nFaultDirection,Us,ILoad_Mag,ILoad_Ang,If,Zl_Mag,Zl_Ang,Kl_Re,Kl_Im);
}

void Csub_calcu::f1_Zs(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang, 
					   float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	int i;
	float  ex,ey;
	float  ix,iy;
	float  Zs_x,Zs_y,kZs_x,kZs_y;
	float  Zl_x,Zl_y,kZl_x,kZl_y;
	float  Zf_x,Zf_y;
	float  du_x,du_y;
	float  temp_x,temp_y;
	int nIndex;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zs_Mag,Zs_Ang,&Zs_x,&Zs_y);
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Ks_Re,Ks_Im,Zs_x,Zs_y,&kZs_x,&kZs_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);
	Zf_x=Zs_x+kZs_x+Zl_x+kZl_x;
	Zf_y=Zs_y+kZs_y+Zl_y+kZl_y;

	//1. 计算短路点处的电流 If
	//1-1: 检查 If 是否越限, 越限则自动调整 Es
	{
		nIndex=phaseNo;
		i=nIndex;
		po_to_xy(m_Es[i].Mag,m_Es[i].Ang,&ex,&ey);
		comp_Divi(ex,ey,Zf_x,Zf_y,&ix,&iy);
		xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		if(m_Ip[i].Mag>MAX_IF)
		{
			m_Ip[i].Mag=MAX_IF;
			//修正系统侧电源电压 Es: Es = If * Zf
			float Zf_Mag,Zf_Ang;
			xy_to_po(Zf_x,Zf_y,&Zf_Mag,&Zf_Ang);
			m_Es[i].Mag=m_Ip[i].Mag*Zf_Mag;
			for(int j=0;j<3;j++)
			{
				if(j!=i)
				{
					m_Es[j].Mag=m_Es[i].Mag;
				}
			}
		}
	}
	//1-2: 计算短路电流
	nIndex=phaseNo;
	for(i=0;i<3;i++)
	{
		if(i==nIndex)
		{
			po_to_xy(m_Es[i].Mag,m_Es[i].Ang,&ex,&ey);
			comp_Divi(ex,ey,Zf_x,Zf_y,&ix,&iy);
			xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		}
		else
		{
			m_Ip[i].Mag=0.0f;
			m_Ip[i].Ang=0.0f;
		}
	}

	//2. 计算保护安装处的电压
	for(i=0;i<3;i++)
	{
		if(i==nIndex)
		{
			//短路电流 If 导致的电压
			po_to_xy(m_Ip[i].Mag,m_Ip[i].Ang,&ix,&iy);
			comp_Mult(ix,iy,(Zl_x+kZl_x),(Zl_y+kZl_y),&temp_x,&temp_y);
			xy_to_po(temp_x,temp_y,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else
		{
			po_to_xy(m_Ip[nIndex].Mag,m_Ip[nIndex].Ang,&ix,&iy);
			comp_Mult(ix,iy,kZs_x,kZs_y,&du_x,&du_y);
			po_to_xy(m_Es[i].Mag,m_Es[i].Ang,&temp_x,&temp_y);
			temp_x=temp_x-du_x;
			temp_y=temp_y-du_y;
			xy_to_po(temp_x,temp_y,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang+=180.0f;
			else
				m_Ip[i].Ang-=180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

// f2: 两相相间--------------------------------------------------------
void Csub_calcu::f2_If(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float If, 
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	int i;
	float  ex,ey,e_Mag,e_Ang;
	float  ix,iy;
	float  Zl_x,Zl_y,kZl_x,kZl_y;
	float  du_x,du_y;
	float  temp_x,temp_y;
	int nIndex1,nIndex2;

	//近似以 Es 代替保护安装处的稳态运行电压 Vs
	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);

	switch(phaseNo)
	{
	case 0:  // AB相间 
		nIndex1=0;
		nIndex2=1;
		break;
	case 1:  // BC相间 
		nIndex1=1;
		nIndex2=2;
		break;
	case 2:  // CA相间 
		nIndex1=2;
		nIndex2=0;
		break;
	}
	//1. 计算短路点处的电流 If
	po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
	po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&temp_x,&temp_y);
	xy_to_po((ex-temp_x)/2.0f,(ey-temp_y)/2.0f,&e_Mag,&e_Ang);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			m_Ip[i].Mag=If;
			m_Ip[i].Ang=e_Ang-Zl_Ang;
		}
		else if(i==nIndex2)
		{
			m_Ip[i].Mag=If;
			m_Ip[i].Ang=e_Ang-Zl_Ang-180.0f;
		}
		else
		{
			m_Ip[i].Mag=0.0f;
			m_Ip[i].Ang=0.0f;
		}
	}
	//2. 计算保护安装处的电压: 
	po_to_xy(m_Ip[nIndex1].Mag,m_Ip[nIndex1].Ang,&ix,&iy);
	po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
	po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&temp_x,&temp_y);
	ex=(ex+temp_x)/2.0f;
	ey=(ey+temp_y)/2.0f;
	comp_Mult(ix,iy,Zl_x,Zl_y,&du_x,&du_y);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			//短路电流 If 导致的电压
			temp_x=ex+du_x;
			temp_y=ey+du_y;
			xy_to_po(temp_x,temp_y,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else if(i==nIndex2)
		{
			//短路电流 If 导致的电压
			temp_x=ex-du_x;
			temp_y=ey-du_y;
			xy_to_po(temp_x,temp_y,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else
		{
			m_Up[i].Mag=m_Es[i].Mag;
			m_Up[i].Ang=m_Es[i].Ang;
		}
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang=m_Ip[i].Ang+180.0f;
			else
				m_Ip[i].Ang=m_Ip[i].Ang-180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f2_Uf(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float Uf, 
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	float If;

	if(Zl_Mag<=0.0001f)
		If=10000.0f;
	else
		If=Uf/(2.0f*Zl_Mag);
	f2_If(phaseNo,nFaultDirection,Us,ILoad_Mag,ILoad_Ang,If,Zl_Mag,Zl_Ang,Kl_Re,Kl_Im);
}

void Csub_calcu::f2_Zs(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	int i;
	float  ex,ey;
	float  ix,iy;
	float  Zs_x,Zs_y,kZs_x,kZs_y;
	float  Zl_x,Zl_y,kZl_x,kZl_y;
	float  Zf_x,Zf_y;
	float  du_x,du_y;
	float  temp_x,temp_y;
	int nIndex1,nIndex2;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zs_Mag,Zs_Ang,&Zs_x,&Zs_y);
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Ks_Re,Ks_Im,Zs_x,Zs_y,&kZs_x,&kZs_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);
	Zf_x=Zs_x+Zl_x;
	Zf_y=Zs_y+Zl_y;

	switch(phaseNo)
	{
	case 0:  // AB相间 
		nIndex1=0;
		nIndex2=1;
		break;
	case 1:  // BC相间 
		nIndex1=1;
		nIndex2=2;
		break;
	case 2:  // CA相间 
		nIndex1=2;
		nIndex2=0;
		break;
	}
	//1. 计算短路点处的电流 If
	//1-1: 检查 If 是否越限, 越限则自动调整 Es
	{
		po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
		po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&temp_x,&temp_y);
		ex=(ex-temp_x)/2.0f;
		ey=(ey-temp_y)/2.0f;
		comp_Divi(ex,ey,Zf_x,Zf_y,&ix,&iy);
		i=nIndex1;
		xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		if(m_Ip[i].Mag>MAX_IF)
		{
			m_Ip[i].Mag=MAX_IF;
			//修正系统侧电源电压 Es: Es = If * Zf * 2 /sqrt(3)
			float Zf_Mag,Zf_Ang;
			xy_to_po(Zf_x,Zf_y,&Zf_Mag,&Zf_Ang);
			m_Es[i].Mag=m_Ip[i].Mag*Zf_Mag*2.0f/(float)sqrt(3.0);
			for(int j=0;j<3;j++)
			{
				if(j!=i)
				{
					m_Es[j].Mag=m_Es[i].Mag;
				}
			}
		}
	}
	//1-2: 计算短路电流
	po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
	po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&temp_x,&temp_y);
	ex=(ex-temp_x)/2.0f;
	ey=(ey-temp_y)/2.0f;
	comp_Divi(ex,ey,Zf_x,Zf_y,&ix,&iy);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		}
		else if(i==nIndex2)
		{
			xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
			m_Ip[i].Ang-=180.0f;
		}
		else
		{
			m_Ip[i].Mag=0.0f;
			m_Ip[i].Ang=0.0f;
		}
	}
	//2. 计算保护安装处的电压
	po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
	po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&temp_x,&temp_y);
	ex=(ex+temp_x)/2.0f;
	ey=(ey+temp_y)/2.0f;
	comp_Mult(ix,iy,Zl_x,Zl_y,&du_x,&du_y);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			//短路电流 If 导致的电压
			temp_x=ex+du_x;
			temp_y=ey+du_y;
			xy_to_po(temp_x,temp_y,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else if(i==nIndex2)
		{
			//短路电流 If 导致的电压
			temp_x=ex-du_x;
			temp_y=ey-du_y;
			xy_to_po(temp_x,temp_y,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else
		{
			m_Up[i].Mag=m_Es[i].Mag;
			m_Up[i].Ang=m_Es[i].Ang;
		}
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang=m_Ip[i].Ang+180.0f;
			else
				m_Ip[i].Ang=m_Ip[i].Ang-180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

// f3: 三相短路---------------------------------------------------------
void Csub_calcu::f3_If(int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float If, 
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	int i;
	float Zl_x,Zl_y,kZl_x,kZl_y;

	//近似以 Es 代替保护安装处的稳态运行电压 Vs
	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);

	//1. 计算短路点处的电流 If
	for(i=0;i<3;i++)
	{
		m_Ip[i].Mag=If;
		m_Ip[i].Ang=m_Es[i].Ang-Zl_Ang;
	}
	//2. 计算保护安装处的电压: 
	for(i=0;i<3;i++)
	{
		//短路电流 If 导致的电压
		m_Up[i].Mag=m_Ip[i].Mag*Zl_Mag;
		m_Up[i].Ang=m_Ip[i].Ang+Zl_Ang;
		//负荷电流 ILoad 导致的正序电压
		comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang=m_Ip[i].Ang+180.0f;
			else
				m_Ip[i].Ang=m_Ip[i].Ang-180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f3_Uf(int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float Uf, 
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	float  If;

	if(Zl_Mag<=0.0001)
		If=10000.0f;
	else
		If=Uf/Zl_Mag;
	f3_If(nFaultDirection,Us,ILoad_Mag,ILoad_Ang,If,Zl_Mag,Zl_Ang,Kl_Re,Kl_Im);
}

void Csub_calcu::f3_Zs(int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang, 
					   float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
					   float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
					   )
{
	int i;
	float  Zs_x,Zs_y,kZs_x,kZs_y;
	float  Zl_x,Zl_y,kZl_x,kZl_y;
	float  Zf_x,Zf_y;
	float  temp_x,temp_y;
	float  ex,ey;
	float  ix,iy;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zs_Mag,Zs_Ang,&Zs_x,&Zs_y);
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Ks_Re,Ks_Im,Zs_x,Zs_y,&kZs_x,&kZs_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);
	Zf_x=Zs_x+Zl_x;
	Zf_y=Zs_y+Zl_y;

	//1-1: 检查 If 是否越限, 越限则自动调整 Es
	{
		i=0;
		po_to_xy(m_Es[i].Mag,m_Es[i].Ang,&ex,&ey);
		comp_Divi(ex,ey,Zf_x,Zf_y,&ix,&iy);
		xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		if(m_Ip[i].Mag>MAX_IF)
		{
			m_Ip[i].Mag=MAX_IF;
			//修正系统侧电源电压 Es: Es = If * Zf
			float Zf_Mag,Zf_Ang;
			xy_to_po(Zf_x,Zf_y,&Zf_Mag,&Zf_Ang);
			m_Es[i].Mag=m_Ip[i].Mag*Zf_Mag;
			for(int j=0;j<3;j++)
			{
				if(j!=i)
				{
					m_Es[j].Mag=m_Es[i].Mag;
				}
			}
		}
	}
	//1-2: 计算短路电流
	for(i=0;i<3;i++)  
	{
		//1. 计算短路点处的短路电流 If
		po_to_xy(m_Es[i].Mag,m_Es[i].Ang,&ex,&ey);
		comp_Divi(ex,ey,Zf_x,Zf_y,&ix,&iy);
		xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		//2. 计算保护安装处的电压
		//   短路电流 If 导致的电压
		comp_Mult(ix,iy,Zl_x,Zl_y,&temp_x,&temp_y);
		xy_to_po(temp_x,temp_y,&m_Up[i].Mag,&m_Up[i].Ang);
		//   负荷电流 ILoad 导致的正序电压
		comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang=m_Ip[i].Ang+180.0f;
			else
				m_Ip[i].Ang=m_Ip[i].Ang-180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

//f11: 两相接地短路 --------------------------------------
// 假定: Ks=0; Zs角度 = Zl角度; 且 K0=Kl 
void Csub_calcu::f11_If(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
						float If, 
						float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
						)
{
	int i;
	float  ex,ey,e_Mag,e_Ang;
	float  ex2,ey2;
	float  ix,iy;
	float  ix2,iy2;
	float  Zl_x,Zl_y;
	float  kZl_x,kZl_y;
	float  du_x,du_y;
	float  temp_x,temp_y;
	int nIndex1,nIndex2;

	//近似以 Es 代替保护安装处的稳态运行电压 Vs
	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);

	switch(phaseNo)
	{
	case 0:  // AB两相接地
		nIndex1=0;
		nIndex2=1;
		break;
	case 1:  // BC两相接地
		nIndex1=1;
		nIndex2=2;
		break;
	case 2:  // CA两相接地
		nIndex1=2;
		nIndex2=0;
		break;
	}
	//1. 计算短路点处的电流 If
	po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
	po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&ex2,&ey2);
	comp_Mult(Kl_Re,Kl_Im,(ex-ex2),(ey-ey2),&du_x,&du_y);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			comp_Divi((ex+du_x),(ey+du_y),(1.0f+2.0f*Kl_Re),(2.0f*Kl_Im),&temp_x,&temp_y);
			xy_to_po(temp_x,temp_y,&e_Mag,&e_Ang);
			m_Ip[i].Mag=If;
			m_Ip[i].Ang=e_Ang-Zl_Ang;
		}
		else if(i==nIndex2)
		{
			comp_Divi((ex2-du_x),(ey2-du_y),(1.0f+2.0f*Kl_Re),(2.0f*Kl_Im),&temp_x,&temp_y);
			xy_to_po(temp_x,temp_y,&e_Mag,&e_Ang);
			m_Ip[i].Mag=If;
			m_Ip[i].Ang=e_Ang-Zl_Ang;
		}
		else
		{
			m_Ip[i].Mag=0.0f;
			m_Ip[i].Ang=0.0f;
		}
	}
	//2. 计算保护安装处的电压
	po_to_xy(m_Ip[nIndex1].Mag,m_Ip[nIndex1].Ang,&ix,&iy);
	po_to_xy(m_Ip[nIndex2].Mag,m_Ip[nIndex2].Ang,&ix2,&iy2);
	comp_Mult(kZl_x,kZl_y,(ix+ix2),(iy+iy2),&du_x,&du_y);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			//短路电流 If 导致的电压
			comp_Mult(Zl_x,Zl_y,ix,iy,&temp_x,&temp_y);
			ex=temp_x+du_x;
			ey=temp_y+du_y;
			xy_to_po(ex,ey,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else if(i==nIndex2)
		{
			//短路电流 If 导致的电压
			comp_Mult(Zl_x,Zl_y,ix2,iy2,&temp_x,&temp_y);
			ex=temp_x+du_x;
			ey=temp_y+du_y;
			xy_to_po(ex,ey,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else
		{		
			m_Up[i].Mag=m_Es[i].Mag;
			m_Up[i].Ang=m_Es[i].Ang;
		}
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang=m_Ip[i].Ang+180.0f;
			else
				m_Ip[i].Ang=m_Ip[i].Ang-180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f11_Uf(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
						float Uf, 
						float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
						)
{
	int i;
	float  ex,ey,e_Mag,e_Ang;
	float  ex2,ey2;
	float  ix,iy;
	float  ix2,iy2;
	float  Zl_x,Zl_y;
	float  kZl_x,kZl_y;
	float  du_x,du_y;
	float  temp_x,temp_y;
	int nIndex1,nIndex2;

	//近似以 Es 代替保护安装处的稳态运行电压 Vs
	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);

	switch(phaseNo)
	{
	case 0:  // AB两相接地
		nIndex1=0;
		nIndex2=1;
		break;
	case 1:  // BC两相接地
		nIndex1=1;
		nIndex2=2;
		break;
	case 2:  // CA两相接地
		nIndex1=2;
		nIndex2=0;
		break;
	}
	//2. 计算保护安装处的电压
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			m_Up[i].Mag=Uf;
			m_Up[i].Ang=m_Es[i].Ang;
		}
		else if(i==nIndex2)
		{
			m_Up[i].Mag=Uf;
			m_Up[i].Ang=m_Es[i].Ang;
		}
		else
		{
			m_Up[i].Mag=m_Es[i].Mag;
			m_Up[i].Ang=m_Es[i].Ang;
		}
	}
	//1. 计算短路点处的电流 If
	//计算 Ia+Ib
	po_to_xy(m_Up[nIndex1].Mag,m_Up[nIndex1].Ang,&ex,&ey);
	po_to_xy(m_Up[nIndex2].Mag,m_Up[nIndex2].Ang,&ex2,&ey2);
	comp_Divi((ex+ex2),(ey+ey2),(Zl_x+2.0f*kZl_x),(Zl_y+2.0f*kZl_y),&temp_x,&temp_y);
	comp_Mult(kZl_x,kZl_y,temp_x,temp_y,&temp_x,&temp_y);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			//计算 Ia
			comp_Divi((ex-temp_x),(ey-temp_y),Zl_x,Zl_y,&e_Mag,&e_Ang);
			xy_to_po(e_Mag,e_Ang,&e_Mag,&e_Ang);
			m_Ip[i].Mag=e_Mag;
			m_Ip[i].Ang=e_Ang;
		}
		else if(i==nIndex2)
		{
			//计算 Ib
			comp_Divi((ex2-temp_x),(ey2-temp_y),Zl_x,Zl_y,&e_Mag,&e_Ang);
			xy_to_po(e_Mag,e_Ang,&e_Mag,&e_Ang);
			m_Ip[i].Mag=e_Mag;
			m_Ip[i].Ang=e_Ang;
		}
		else
		{
			m_Ip[i].Mag=0.0f;
			m_Ip[i].Ang=0.0f;
		}
	}
	//2. 计算保护安装处的电压
	po_to_xy(m_Ip[nIndex1].Mag,m_Ip[nIndex1].Ang,&ix,&iy);
	po_to_xy(m_Ip[nIndex2].Mag,m_Ip[nIndex2].Ang,&ix2,&iy2);
	comp_Mult(kZl_x,kZl_y,(ix+ix2),(iy+iy2),&du_x,&du_y);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			//短路电流 If 导致的电压
			comp_Mult(Zl_x,Zl_y,ix,iy,&temp_x,&temp_y);
			ex=temp_x+du_x;
			ey=temp_y+du_y;
			xy_to_po(ex,ey,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else if(i==nIndex2)
		{
			//短路电流 If 导致的电压
			comp_Mult(Zl_x,Zl_y,ix2,iy2,&temp_x,&temp_y);
			ex=temp_x+du_x;
			ey=temp_y+du_y;
			xy_to_po(ex,ey,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else
		{		
			m_Up[i].Mag=m_Es[i].Mag;
			m_Up[i].Ang=m_Es[i].Ang;
		}
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang=m_Ip[i].Ang+180.0f;
			else
				m_Ip[i].Ang=m_Ip[i].Ang-180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f11_Zs(int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang, 
						float Zs_Mag,float Zs_Ang,float Ks_Re,float Ks_Im,
						float Zl_Mag,float Zl_Ang,float Kl_Re,float Kl_Im
						)
{
	int i;
	float  Zs_x,Zs_y,kZs_x,kZs_y;
	float  Zl_x,Zl_y,kZl_x,kZl_y;
	float  Zf_x,Zf_y;
	float  K0_Re,K0_Im;
	float  ex,ey;
	float  ix,iy;
	float  ix2,iy2;
	float  du_x,du_y;
	float  temp_x,temp_y;
	int nIndex1,nIndex2;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;
	po_to_xy(Zs_Mag,Zs_Ang,&Zs_x,&Zs_y);
	po_to_xy(Zl_Mag,Zl_Ang,&Zl_x,&Zl_y);
	comp_Mult(Ks_Re,Ks_Im,Zs_x,Zs_y,&kZs_x,&kZs_y);
	comp_Mult(Kl_Re,Kl_Im,Zl_x,Zl_y,&kZl_x,&kZl_y);
	Zf_x=0.0f;
	Zf_y=0.0f;
	comp_Mult((1.0f+2.0f*Ks_Re),(2.0f*Ks_Im),Zs_x,Zs_y,&temp_x,&temp_y);
	Zf_x=Zf_x+temp_x;
	Zf_y=Zf_y+temp_y;
	comp_Mult((1.0f+2.0f*Kl_Re),(2.0f*Kl_Im),Zl_x,Zl_y,&temp_x,&temp_y);
	Zf_x=Zf_x+temp_x;
	Zf_y=Zf_y+temp_y;
	comp_Divi((kZs_x+kZl_x),(kZs_y+kZl_y),(Zs_x+Zl_x),(Zs_y+Zl_y),&K0_Re,&K0_Im);

	switch(phaseNo)
	{
	case 0:  // AB两相接地
		nIndex1=0;
		nIndex2=1;
		break;
	case 1:  // BC两相接地
		nIndex1=1;
		nIndex2=2;
		break;
	case 2:  // CA两相接地
		nIndex1=2;
		nIndex2=0;
		break;
	}
	//1. 计算短路点处的电流 If
	//1-1: 检查 If 是否越限, 越限则自动调整 Es
	{
		po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
		po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&temp_x,&temp_y);
		comp_Mult(K0_Re,K0_Im,(ex-temp_x),(ey-temp_y),&du_x,&du_y);
		comp_Divi((ex+du_x),(ey+du_y),Zf_x,Zf_y,&ix,&iy);
		comp_Divi((temp_x-du_x),(temp_y-du_y),Zf_x,Zf_y,&ix2,&iy2);
		i=nIndex1;
		xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		if(m_Ip[i].Mag>MAX_IF)
		{
			m_Ip[i].Mag=MAX_IF;
			//修正系统侧电源电压 Es: Es = If * Zf / (1 + K0*sqrt(3)∠30)
			float Zf_Mag,Zf_Ang;
			xy_to_po(Zf_x,Zf_y,&Zf_Mag,&Zf_Ang);
			//
			xy_to_po(K0_Re,Kl_Im,&temp_x,&temp_y);
			temp_x*=(float)sqrt(3.0);
			temp_y+=30.0f;
			comp_Add(1.0f,0.0,temp_x,temp_y,&temp_x,&temp_y);
			//
			m_Es[i].Mag=m_Ip[i].Mag*Zf_Mag/temp_x;
			for(int j=0;j<3;j++)
			{
				if(j!=i)
				{
					m_Es[j].Mag=m_Es[i].Mag;
				}
			}
		}
	}
	//1-2: 计算短路电流
	po_to_xy(m_Es[nIndex1].Mag,m_Es[nIndex1].Ang,&ex,&ey);
	po_to_xy(m_Es[nIndex2].Mag,m_Es[nIndex2].Ang,&temp_x,&temp_y);
	comp_Mult(K0_Re,K0_Im,(ex-temp_x),(ey-temp_y),&du_x,&du_y);
	comp_Divi((ex+du_x),(ey+du_y),Zf_x,Zf_y,&ix,&iy);
	comp_Divi((temp_x-du_x),(temp_y-du_y),Zf_x,Zf_y,&ix2,&iy2);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			xy_to_po(ix,iy,&m_Ip[i].Mag,&m_Ip[i].Ang);
		}
		else if(i==nIndex2)
		{
			xy_to_po(ix2,iy2,&m_Ip[i].Mag,&m_Ip[i].Ang);
		}
		else
		{
			m_Ip[i].Mag=0.0f;
			m_Ip[i].Ang=0.0f;
		}
	}
	//2. 计算保护安装处的电压
	comp_Mult(kZl_x,kZl_y,(ix+ix2),(iy+iy2),&du_x,&du_y);
	for(i=0;i<3;i++)
	{
		if(i==nIndex1)
		{
			//短路电流 If 导致的电压
			comp_Mult(Zl_x,Zl_y,ix,iy,&temp_x,&temp_y);
			ex=temp_x+du_x;
			ey=temp_y+du_y;
			xy_to_po(ex,ey,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else if(i==nIndex2)
		{
			//短路电流 If 导致的电压
			comp_Mult(Zl_x,Zl_y,ix2,iy2,&temp_x,&temp_y);
			ex=temp_x+du_x;
			ey=temp_y+du_y;
			xy_to_po(ex,ey,&m_Up[i].Mag,&m_Up[i].Ang);
			//负荷电流导致的正序电压
			comp_Add(m_Up[i].Mag,m_Up[i].Ang,ILoad_Mag*Zl_Mag,m_Es[i].Ang+ILoad_Ang+Zl_Ang,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		else
		{
			po_to_xy(m_Es[i].Mag,m_Es[i].Ang,&ex,&ey);
			comp_Mult(kZs_x,kZs_y,(ix+ix2),(iy+iy2),&temp_x,&temp_y);
			ex=ex-temp_x;
			ey=ey-temp_y;
			xy_to_po(ex,ey,&m_Up[i].Mag,&m_Up[i].Ang);
		}
		m_Up[i].Ang=CheckLimit(m_Up[i].Ang,360.0f,-360.0f);
	}
	//3. 计算流过保护安装处的电流
	//3-1. 反方向修正
	if(nFaultDirection==1)
	{
		for(i=0;i<3;i++)
		{
			if(m_Ip[i].Ang<=0.0f)
				m_Ip[i].Ang=m_Ip[i].Ang+180.0f;
			else
				m_Ip[i].Ang=m_Ip[i].Ang-180.0f;
		}
	}
	//3-2. 叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

//工频变化量阻抗(专用模型), 2009-4-9, 2013-7-19
void Csub_calcu::f1_gp(int nCalcuMode,
					   int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float If, 
					   float Zzd_Mag,float Zzd_Ang,float k,float m
					   )
{
	int i;
	float Uz,Uf;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;

	//初始化故障电压电流 = 空载状态
	for(i=0;i<3;i++)
	{
		m_Up[i].Mag=m_Es[i].Mag;
		m_Up[i].Ang=m_Es[i].Ang;
		//
		m_Ip[i].Mag=0.0f;
		m_Ip[i].Ang=0.0f;
	}

	//计算浮动门槛 Uz = Uop,0 = U - I * Zzd
	//tempMag1=ILoad_Mag*Zzd_Mag;
	//tempAng1=ILoad_Ang+Zzd_Ang;
	//comp_Sub(Us,0.0,tempMag1,tempAng1,&tempMag1,&tempAng1);
	//Uz=tempMag1;
	Uz=Us;
	if(nFaultDirection==0)
	{
		//正方向单相接地: Uf=(1+k)*If*Zzd+(1-1.05m)*Un;
		switch(nCalcuMode)
		{
		case 0:		//0--南瑞继保
			Uf=(1.0f+k)*If*Zzd_Mag+(1.0f-1.05f*m)*Uz;
			break;
		case 1:		//1--许继
			Uf=(1.0f+k)*If*Zzd_Mag+(1.0f-1.4f*m)*Uz;
			break;
		default:
			Uf=0.0f;
			break;
		}
	}
	else
	{
		//反方向出口短路:
		Uf=0.0f;
	}
	m_Up[phaseNo].Mag=Uf;
	m_Ip[phaseNo].Mag=If;
	m_Ip[phaseNo].Ang=m_Up[phaseNo].Ang-Zzd_Ang;
	if(nFaultDirection==1)	//反方向故障
		m_Ip[phaseNo].Ang+=180.0f;

	//叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f11_gp(int nCalcuMode,
						int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
						float If, 
						float Zzd_Mag,float Zzd_Ang,float k,float m
						)
{
	int i;
	float Uz,Uf;
	int nIndex1,nIndex2;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;

	//初始化故障电压电流 = 空载状态
	for(i=0;i<3;i++)
	{
		m_Up[i].Mag=m_Es[i].Mag;
		m_Up[i].Ang=m_Es[i].Ang;
		//
		m_Ip[i].Mag=0.0f;
		m_Ip[i].Ang=0.0f;
	}

	//计算浮动门槛 Uz = Uop,0 = U - I * Zzd
	//tempMag1=ILoad_Mag*Zzd_Mag;
	//tempAng1=ILoad_Ang+Zzd_Ang;
	//comp_Sub(Us,0.0,tempMag1,tempAng1,&tempMag1,&tempAng1);
	//Uz=tempMag1;
	Uz=Us;
	if(nFaultDirection==0)
	{
		//正方向单相接地: Uf=(1+k)*If*Zzd+(1-1.05m)*Un;
		switch(nCalcuMode)
		{
		case 0:		//0--南瑞继保
			Uf=(1.0f+k)*If*Zzd_Mag+(1.0f-1.05f*m)*Uz;
			break;
		case 1:		//1--许继
			Uf=(1.0f+k)*If*Zzd_Mag+(1.0f-1.4f*m)*Uz;
			break;
		default:
			Uf=0.0f;
			break;
		}
	}
	else
	{
		//反方向出口短路:
		Uf=0.0f;
	}
	switch(phaseNo)
	{
	case 0:	//AB
		nIndex1=0;
		nIndex2=1;
		break;
	case 1:	//BC
		nIndex1=1;
		nIndex2=2;
		break;
	case 2:	//CA
		nIndex1=2;
		nIndex2=0;
		break;
	}
	m_Up[nIndex1].Mag=Uf;
	m_Up[nIndex2].Mag=Uf;
	m_Ip[nIndex1].Mag=If;
	m_Ip[nIndex1].Ang=m_Up[nIndex1].Ang-Zzd_Ang;
	m_Ip[nIndex2].Mag=If;
	m_Ip[nIndex2].Ang=m_Up[nIndex2].Ang-Zzd_Ang;
	if(nFaultDirection==1)	//反方向故障
	{
		m_Ip[nIndex1].Ang+=180.0f;
		m_Ip[nIndex2].Ang+=180.0f;
	}

	//叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f2_gp(int nCalcuMode,
					   int phaseNo,int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float If, 
					   float Zzd_Mag,float Zzd_Ang,float k,float m
					   )
{
	int i;
	float Mag1,Ang1,Mag2,Ang2;
	float tempMag1,tempAng1,tempMag2,tempAng2;
	float Uz,Uf;
	int nIndex1,nIndex2;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;

	//初始化故障电压电流 = 空载状态
	for(i=0;i<3;i++)
	{
		m_Up[i].Mag=m_Es[i].Mag;
		m_Up[i].Ang=m_Es[i].Ang;
		//
		m_Ip[i].Mag=0.0f;
		m_Ip[i].Ang=0.0f;
	}

	//计算浮动门槛 Uz = Uop,0 = U - I * Zzd
	//tempMag1=ILoad_Mag*Zzd_Mag;
	//tempAng1=ILoad_Ang+Zzd_Ang;
	//comp_Sub(Us,0.0,tempMag1,tempAng1,&tempMag1,&tempAng1);
	//Uz=tempMag1;
	Uz=Us;
	if(nFaultDirection==0)
	{
		//正方向相间故障: Uff=Iff*Zzd+(1-1.05m)*1.732*Un
		//                   =2*If*Zzd+(1-1.05m)*1.732*Un
		switch(nCalcuMode)
		{
		case 0:		//0--南瑞继保
			Uf=2.0f*If*Zzd_Mag+(1.0f-1.05f*m)*Uz*(float)sqrt(3.0);
			break;
		case 1:		//1--许继
			Uf=2.0f*If*Zzd_Mag+(1.0f-1.3f*m)*Uz*(float)sqrt(3.0);
			break;
		default:
			Uf=0.0f;
			break;
		}
	}
	else
	{
		//反方向出口短路:
		Uf=0.0f;
	}
	switch(phaseNo)
	{
	case 0:	//AB
		Mag1=m_Up[2].Mag;
		Ang1=m_Up[2].Ang;
		break;
	case 1:	//BC
		Mag1=m_Up[0].Mag;
		Ang1=m_Up[0].Ang;
		break;
	case 2:	//CA
		Mag1=m_Up[1].Mag;
		Ang1=m_Up[1].Ang;
		break;
	}
	Mag2=Uf;
	Ang2=Ang1-90.0f;
	comp_Add(-Mag1,Ang1,Mag2,Ang2,&tempMag1,&tempAng1);
	comp_Add(-Mag1,Ang1,-Mag2,Ang2,&tempMag2,&tempAng2);
	tempMag1/=2.0f;
	tempMag2/=2.0f;
	switch(phaseNo)
	{
	case 0:	//AB
		nIndex1=0;
		nIndex2=1;
		break;
	case 1:	//BC
		nIndex1=1;
		nIndex2=2;
		break;
	case 2:	//CA
		nIndex1=2;
		nIndex2=0;
		break;
	}
	m_Up[nIndex1].Mag=tempMag1;
	m_Up[nIndex1].Ang=tempAng1;
	m_Up[nIndex2].Mag=tempMag2;
	m_Up[nIndex2].Ang=tempAng2;
	//
	m_Ip[nIndex1].Mag=If;
	m_Ip[nIndex1].Ang=Ang2-Zzd_Ang;
	m_Ip[nIndex2].Mag=If;
	m_Ip[nIndex2].Ang=Ang2-Zzd_Ang-180.0f;
	if(nFaultDirection==1)	//反方向故障
	{
		m_Ip[nIndex1].Ang+=180.0f;
		m_Ip[nIndex2].Ang+=180.0f;
	}

	//叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

void Csub_calcu::f3_gp(int nCalcuMode,
					   int nFaultDirection,float Us,float ILoad_Mag,float ILoad_Ang,
					   float If, 
					   float Zzd_Mag,float Zzd_Ang,float k,float m
					   )
{
	int i;
	float Uz,Uf;

	m_Es[0].Mag=Us;
	m_Es[0].Ang=0.0f;
	m_Es[1].Mag=Us;
	m_Es[1].Ang=-120.0f;
	m_Es[2].Mag=Us;
	m_Es[2].Ang=120.0f;

	//初始化故障电压电流 = 空载状态
	for(i=0;i<3;i++)
	{
		m_Up[i].Mag=m_Es[i].Mag;
		m_Up[i].Ang=m_Es[i].Ang;
		//
		m_Ip[i].Mag=0.0f;
		m_Ip[i].Ang=0.0f;
	}

	//计算浮动门槛 Uz = Uop,0 = U - I * Zzd
	//tempMag1=ILoad_Mag*Zzd_Mag;
	//tempAng1=ILoad_Ang+Zzd_Ang;
	//comp_Sub(Us,0.0,tempMag1,tempAng1,&tempMag1,&tempAng1);
	//Uz=tempMag1;
	Uz=Us;
	if(nFaultDirection==0)
	{
		//正方向相间故障: Uff=Iff*Zzd+(1-1.05m)*1.732*Un
		//                   =1.732*If*Zzd+(1-1.05m)*1.732*Un
		switch(nCalcuMode)
		{
		case 0:		//0--南瑞继保
			Uf=(float)sqrt(3.0)*If*Zzd_Mag+(1.0f-1.05f*m)*Uz*(float)sqrt(3.0);
			break;
		case 1:		//1--许继
			Uf=(float)sqrt(3.0)*If*Zzd_Mag+(1.0f-1.3f*m)*Uz*(float)sqrt(3.0);
			break;
		default:
			Uf=0.0f;
			break;
		}
	}
	else
	{
		//反方向出口短路:
		Uf=0.0f;
	}
	for(i=0;i<3;i++)
	{
		m_Up[i].Mag=Uf/(float)sqrt(3.0);
		m_Ip[i].Mag=If;
		m_Ip[i].Ang=m_Up[i].Ang-Zzd_Ang;
		if(nFaultDirection==1)	//反方向故障
		{
			m_Ip[i].Ang+=180.0f;
		}
	}

	//叠加负荷电流
	for(i=0;i<3;i++)
	{
		comp_Add(m_Ip[i].Mag,m_Ip[i].Ang,ILoad_Mag,m_Es[i].Ang+ILoad_Ang,&m_Ip[i].Mag,&m_Ip[i].Ang);
		m_Ip[i].Ang=CheckLimit(m_Ip[i].Ang,360.0f,-360.0f);
	}
}

