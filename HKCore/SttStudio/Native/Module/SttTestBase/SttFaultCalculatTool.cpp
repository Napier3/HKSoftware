#include "StdAfx.h"
#include "SttFaultCalculatTool.h"
#include "../../../Module/API/MathApi.h"

static float g_nCalculatAngle[11]    = {0,-120,120,30,-90,150,30,-90,150,0,120};


CSttFaultCalculatTool::CSttFaultCalculatTool(void)
{
}

CSttFaultCalculatTool::~CSttFaultCalculatTool(void)
{
}

float CSttFaultCalculatTool::GetTimeAfterTrigger(float fCBTripTimeSecond,BOOL bCBSimulation)
{
	if (!bCBSimulation)
	{
		return 0.0f;
	}

	return fCBTripTimeSecond;
}

float CSttFaultCalculatTool::CalImpPlusDC_Tao(float fImpedance,float fImpAngle)
{
	float fTao = 0;

	if (fabs(fImpedance*cos(fImpAngle*_PI/180.0))>0.0001f && fabs(fImpedance*sin(fImpAngle*_PI/180.0))>0.0001f)
	{
		fTao = (WORD)(fabs(fImpedance*cos(fImpAngle*_PI/180.0))*2*_PI/fabs(fImpedance*sin(fImpAngle*_PI/180.0)));
	}

	return fTao;
}

void CSttFaultCalculatTool::CalPreFaultComplex(Complex *pComplex,float fAmplitude,float fStartAngle)
{
	Complex p1;
	pComplex[0] = p1.polar(fAmplitude,fStartAngle + 0.0f);
	pComplex[1] = p1.polar(fAmplitude, fStartAngle -120.0f);
	pComplex[2] = p1.polar(fAmplitude, fStartAngle + 120.0f);
}

void CSttFaultCalculatTool::CalVzComplex(Complex *pUzComplex,Complex *pU_Complex,long nVzDefine)
{
	int nVzPhDefine = 0;

	if (nVzDefine>4 && nVzDefine<10)//检同期等等
	{
		nVzPhDefine = nVzDefine-4;
	}

	if (nVzPhDefine<3)		//如果抽取电压选择A、B、C相电压
	{
		*pUzComplex = pU_Complex[nVzPhDefine];
	}
	else 
	{
		switch (nVzPhDefine) 
		{
		case 3:
			*pUzComplex = pU_Complex[0]-pU_Complex[1];
			break;
		case 4:
			*pUzComplex = pU_Complex[1]-pU_Complex[2];
			break;
		case 5:
			*pUzComplex = pU_Complex[2]-pU_Complex[0];
			break;
		}
	}

	switch(nVzDefine)//对于无输出或者零序作为抽取电压的情况,故障前抽取电压为0
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 14:
		pUzComplex->SetParameter(0,0);
		break;

	default:
		break;
	}
}

void CSttFaultCalculatTool::Cal_SimulatePT(int nPTPhase, Complex *cmpUI)
{
	Complex p1;

	if (nPTPhase < 3)
	{
		cmpUI[nPTPhase] = p1.polar(0.0,0.0);
	}
	else
	{
		switch (nPTPhase)
		{
		case 3:
			cmpUI[0] = p1.polar(0.0,0.0);
			cmpUI[1] = p1.polar(0.0,-120.0);
			break;
		case 4:
			cmpUI[2] = p1.polar(0.0,120.0);
			cmpUI[1] = p1.polar(0.0,-120.0);
			break;
		case 5:
			cmpUI[0] = p1.polar(0.0,0.0);
			cmpUI[2] = p1.polar(0.0,120.0);
			break;
		case 6:
			cmpUI[0] = p1.polar(0.0,0.0);
			cmpUI[1] = p1.polar(0.0,-120.0);
			cmpUI[2] = p1.polar(0.0,120.0);
			break;
		}
	}
}


void CSttFaultCalculatTool::Cal_VzAccordDefine(int nVzDefine, Complex *cmpUI,float fUxInput_Mag,float fUxInput_Ang, float fUxHigh, float fUxLow,BOOL bAfterTrip)	// 通用，根据Ux数据方式计算Vz
{
	Complex p1;
	cmpUI[3] = p1.polar(0,0);

	if (!bAfterTrip)//如果不是跳闸后状态,检同期或检无压时,使用+3U0
	{
		if ((nVzDefine>=10)&&(nVzDefine<=13))//如果是检无压方式,取三相电压最小值
		{
			double dAmp = cmpUI[0].norm();

			if (dAmp>cmpUI[1].norm())
			{
				dAmp = cmpUI[1].norm();
			}

			if (dAmp>cmpUI[2].norm())
			{
				dAmp = cmpUI[2].norm();
			}

			cmpUI[3] = p1.polar(dAmp,cmpUI[3].arg());
			return;
		}
		else if ((nVzDefine == 4)||(nVzDefine == 5)||(nVzDefine == 6))
		{
			cmpUI[3] = cmpUI[nVzDefine-4];
			return;
		}
		else if (nVzDefine == 7)
		{
			cmpUI[3] = cmpUI[0]-cmpUI[1];
			return;
		}
		else if (nVzDefine == 8)
		{
			cmpUI[3] = cmpUI[1]-cmpUI[2];
			return;
		}
		else if (nVzDefine == 9)
		{
			cmpUI[3] = cmpUI[2]-cmpUI[0];
			return;
		}
	}

	switch (nVzDefine)
	{
	case IMPEDANCE_VZ_TYPE_Positive_3U0/*0*/:		//+3U0
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		break;
	case IMPEDANCE_VZ_TYPE_Negative_3U0/*1*/:		//-3U0
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		cmpUI[3] = p1.polar(cmpUI[3].norm(),cmpUI[3].arg()+180);//m_fVz*sqrt(3.0);
		break;
	case IMPEDANCE_VZ_TYPE_Positive_Squ3_3U0/*2*/:		//+√3×3Vo
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		cmpUI[3] = p1.polar(cmpUI[3].norm()*sqrt(3.0),cmpUI[3].arg());	//m_fVz*sqrt(3.0);
		break;
	case IMPEDANCE_VZ_TYPE_Negative_Squ3_3U0/*3*/:		//-√3×3Vo
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		cmpUI[3] = p1.polar(cmpUI[3].norm()*sqrt(3.0),cmpUI[3].arg());	//m_fVz*sqrt(3.0);
		cmpUI[3] = p1.polar(cmpUI[3].norm(),cmpUI[3].arg()+180);	//-m_fVz*sqrt(3.0);
		break;
	case IMPEDANCE_VZ_TYPE_Check_Syn_A/*4*/:		//检同期A
	case IMPEDANCE_VZ_TYPE_Check_Syn_B/*5*/:		//检同期B
	case IMPEDANCE_VZ_TYPE_Check_Syn_C/*6*/:		//检同期C
		cmpUI[3] = p1.polar(fUxInput_Mag,(cmpUI[nVzDefine-4].arg())+fUxInput_Ang);
		break;
	case IMPEDANCE_VZ_TYPE_Check_Syn_AB/*7*/:		//检同期AB
		cmpUI[3] = cmpUI[0]-cmpUI[1];
		cmpUI[3] = p1.polar(fUxInput_Mag,(cmpUI[3].arg())+fUxInput_Ang);
		break;
	case IMPEDANCE_VZ_TYPE_Check_Syn_BC/*8*/:		//检同期BC
		cmpUI[3] = cmpUI[1]-cmpUI[2];
		cmpUI[3] = p1.polar(fUxInput_Mag,(cmpUI[3].arg())+fUxInput_Ang);
		break;
	case IMPEDANCE_VZ_TYPE_Check_Syn_CA/*9*/:	//检同期CA
		cmpUI[3] = cmpUI[2]-cmpUI[0];
		cmpUI[3] = p1.polar(fUxInput_Mag,(cmpUI[3].arg())+fUxInput_Ang);
		break;
	case IMPEDANCE_VZ_TYPE_Check_LineNoBusHas/*10*/:	//检线无压母有压
		cmpUI[0] = p1.polar(1.05*fUxHigh,cmpUI[0].arg());//有压定值的1.05倍,无压定值的0.95倍
		cmpUI[1] = p1.polar(1.05*fUxHigh,cmpUI[1].arg());
		cmpUI[2] = p1.polar(1.05*fUxHigh,cmpUI[2].arg());
		cmpUI[3] = p1.polar(0.95*fUxLow,cmpUI[3].arg());
		break;
	case IMPEDANCE_VZ_TYPE_Check_LineHasBusNo/*11*/:	//检线有压母无压
		cmpUI[0] = p1.polar(0.95*fUxLow,cmpUI[0].arg());
		cmpUI[1] = p1.polar(0.95*fUxLow,cmpUI[1].arg());
		cmpUI[2] = p1.polar(0.95*fUxLow,cmpUI[2].arg());
		cmpUI[3] = p1.polar(1.05*fUxHigh,cmpUI[3].arg());
		break;
	case IMPEDANCE_VZ_TYPE_Check_LineNoBusNo/*12*/:	//检线无压母无压
		cmpUI[0] = p1.polar(0.95*fUxLow,cmpUI[0].arg());
		cmpUI[1] = p1.polar(0.95*fUxLow,cmpUI[1].arg());
		cmpUI[2] = p1.polar(0.95*fUxLow,cmpUI[2].arg());
		cmpUI[3] = p1.polar(0.95*fUxLow,cmpUI[3].arg());
		break;
	case IMPEDANCE_VZ_TYPE_Check_LineHasBusHas/*13*/:	//检线有压母有压
		cmpUI[0] = p1.polar(1.05*fUxHigh,cmpUI[0].arg());
		cmpUI[1] = p1.polar(1.05*fUxHigh,cmpUI[1].arg());
		cmpUI[2] = p1.polar(1.05*fUxHigh,cmpUI[2].arg());
		cmpUI[3] = p1.polar(1.05*fUxHigh,cmpUI[3].arg());
		break;
	default:
		break;
	}
}

void CSttFaultCalculatTool::Cal_VzAccordDefine_ImpBase(int nVzDefine, Complex *cmpUI,int nVzPhDefine,float fUzAng)
{
	Complex p1,p2;
	cmpUI[3] = p1.polar(0,0);

	switch (nVzDefine)
	{
	case 1:		//Ua
		cmpUI[3] = cmpUI[0];
		break;
	case 2:		//Ub
		cmpUI[3] = cmpUI[1];
		break;
	case 3:		//Uc
		cmpUI[3] = cmpUI[2];
		break;
	case 4:		//+√3×3Vo
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		cmpUI[3] = p1.polar(cmpUI[3].norm()*sqrt(3.0),cmpUI[3].arg());	//m_fVz*sqrt(3.0);
		break;
	case 5:		//-√3×3Vo
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		cmpUI[3] = p1.polar(cmpUI[3].norm()*sqrt(3.0),cmpUI[3].arg());	//m_fVz*sqrt(3.0);
		cmpUI[3] = p1.polar(cmpUI[3].norm(),cmpUI[3].arg()+180);	//-m_fVz*sqrt(3.0);
		break;
	case 6:		//+3U0
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		break;
	case 7:		//-3U0
		cmpUI[3] = cmpUI[0]+cmpUI[1]+cmpUI[2];
		cmpUI[3] = p1.polar(cmpUI[3].norm(),cmpUI[3].arg()+180);//m_fVz*sqrt(3.0);
		break;
	default:
		break;
	}

	if ((nVzDefine>=1)&&(nVzDefine<=3))//只有在1-3的情况下,需要设置参考相位
	{
		switch (nVzPhDefine)
		{
		case 0:		//Ua
			p2 = cmpUI[0];
			cmpUI[3] = p1.polar(cmpUI[3].norm(),p2.arg()+fUzAng);
			break;
		case 1:		//Ub
			p2 = cmpUI[1];
			cmpUI[3] = p1.polar(cmpUI[3].norm(),p2.arg()+fUzAng);
			break;
		case 2:		//Uc
			p2 = cmpUI[2];
			cmpUI[3] = p1.polar(cmpUI[3].norm(),p2.arg()+fUzAng);
			break;
		case 3:		//Uab
			p2 = cmpUI[0] - cmpUI[1];
			cmpUI[3] = p1.polar(cmpUI[3].norm(),p2.arg()+fUzAng);
			break;
		case 4:		//Ubc
			p2 = cmpUI[1] - cmpUI[2];
			cmpUI[3] = p1.polar(cmpUI[3].norm(),p2.arg()+fUzAng);
			break;
		case 5:		//Uca
			p2 = cmpUI[2] - cmpUI[0];
			cmpUI[3] = p1.polar(cmpUI[3].norm(),p2.arg()+fUzAng);
			break;

		default:
			break;
		}
	}
}

BOOL CSttFaultCalculatTool::F1njs(double Rate,BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
						   Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	Complex p1,p2;
	long nCurrCalIndex = 0;
	BOOL bRet = TRUE;
	double dTmpValue = 0.0f;

	switch(CalMode)
	{
	case 0:
		*FakIa=p1.polar(*Ishort,-p2.arg((k0+1)*zl))+Ifh;
		*FakVa=(k0+1)*zl*(*FakIa);
		*FakVa=p1.polar(p2.norm(*FakVa),0.0);
		while(p1.norm(*FakVa)>=Vnom)
		{
			*Ishort=*Ishort*0.9;
			*FakIa=p1.polar(*Ishort,-p2.arg((k0+1)*zl))+Ifh;
			(*FakVa)=(k0+1)*zl*(*FakIa);
			*FakVa=p1.polar(p2.norm(*FakVa),0.0);
		}
		*FakIb=Ifh*p1.aoperator(-120.0);
		*FakIc=Ifh*p1.aoperator(120.0);
		*FakVb=p1.polar(Vnom,-120.0);
		*FakVc=p1.polar(Vnom,120.0);
		break;
	case 1:
		*FakIa=p1.polar(*Vshort,0.0)/(k0+1)/zl;
		*FakIa=*FakIa+Ifh;
		if(p1.norm(*FakIa)>Imax)
			*FakIa=p1.polar(Imax,p2.arg(*FakIa));
		*FakVa=*FakIa*(k0+1)*zl;
		*FakVa=p1.polar(p2.norm(*FakVa),0);
		*FakVb=p1.polar(Vnom,-120.0);
		*FakVc=p1.polar(Vnom,120.0);
		*FakIb=Ifh*p1.aoperator(-120.0);
		*FakIc=Ifh*p1.aoperator(120.0);
		break;
	case 2:
		*FakIa=p1.polar(Vnom,0.0)/((k0+1)*zl+(k0s+1)*zs);


		*FakIa=*FakIa+Ifh;
		if(p1.norm(*FakIa)>Imax/4.0)
			*FakIa=p1.polar(Imax/4.0,p2.arg(*FakIa));
		Vnom=p1.norm(*FakIa*((k0+1)*zl+(k0s+1)*zs));
		*FakIb=Ifh*p1.aoperator(-120.0);
		*FakIc=Ifh*p1.aoperator(120.0);
		*FakVa=(*FakIa)*(k0+1)*zl;
		*FakVb=p1.polar(Vnom,-120.0)-(*FakIa)*k0s*zs;	
		*FakVc=p1.polar(Vnom,120.0)-(*FakIa)*k0s*zs;
		break;
	case 3:
		*FakIa=p1.polar(*Ishort,-p2.arg((k0+1)*zl))+Ifh;
		*FakVa=p1.polar(*Vshort,0.0);
		nCurrCalIndex = 0;

		while(p1.norm(*FakVa)>=Vnom)		//while-->if，因为一旦计算后的FakVa还是>=Vnom，就陷入死循环
		{
			nCurrCalIndex++;
			(*FakVa)=(k0+1)*zl*(*FakIa)*0.9;
			*FakVa=p1.polar(p2.norm(*FakVa),0.0);

			if (nCurrCalIndex>100)//zhouhj 20220729 增加保护,最大循环100次
			{
				break;
			}
		}
		*FakIb=Ifh*p1.aoperator(-120.0);
		*FakIc=Ifh*p1.aoperator(120.0);
		*FakVb=p1.polar(Vnom,-120.0);
		*FakVc=p1.polar(Vnom,120.0);
		break;
	case 4:
		*FakIa=p1.polar(*Ishort,-p2.arg((k0+1)*zl))+Ifh;
		*FakVa=(k0+1)*zl*(*FakIa);
		*FakVa=p1.polar(p2.norm(*FakVa),0.0);
		nCurrCalIndex = 0;

		while(p1.norm(*FakVa)>=Vnom)		//while-->if，因为一旦计算后的FakVa还是>=Vnom，就陷入死循环
		{
			nCurrCalIndex++;
			*FakIa=(*FakIa)*0.9;
			(*FakVa)=(k0+1)*zl*(*FakIa);
			*FakVa=p1.polar(p2.norm(*FakVa),0.0);

			if (nCurrCalIndex>100)//zhouhj 20220729 增加保护,最大循环100次
			{
				break;
			}
		}

		dTmpValue = p2.norm(*FakVa)+(1.0-1.05*Rate)*Vnom;

		if (dTmpValue<0)
		{
			bRet = FALSE;
		}

		*FakVa=p1.polar(dTmpValue,0.0);

		*FakIb=Ifh*p1.aoperator(-120.0);
		*FakIc=Ifh*p1.aoperator(120.0);
		*FakVb=p1.polar(Vnom,-120.0);
		*FakVc=p1.polar(Vnom,120.0);

		break;
	case 5:
		*FakIa=p1.polar(*Ishort,-p2.arg((k0+1)*zl))+Ifh;
		*FakVa=p1.polar(0,0);//(k0+1)*zl*(*FakIa);

		*FakIb=Ifh*p1.aoperator(-120.0);
		*FakIc=Ifh*p1.aoperator(120.0);
		*FakVb=p1.polar(Vnom,-120.0);
		*FakVc=p1.polar(Vnom,120.0);

		break;
	}
	if(!CTPoint)
	{
		*FakIa=(*FakIa)*p1.aoperator(180.0);
		*FakIb=(*FakIb)*p1.aoperator(180.0);
		*FakIc=(*FakIc)*p1.aoperator(180.0);
	}

	return bRet;
} 

void CSttFaultCalculatTool::F11js(double Rate,BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
						   Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	Complex p1,p2,p3;
	switch(CalMode)
	{
	case 0:
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIb=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl));
		*FakIb=*FakIb+Ifh*p1.aoperator(-120.0);
		while(p1.norm(zl*(*FakIb)*2.0)>=1.732*Vnom)
		{
			*FakIb=*FakIb*0.9;
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl)+180.0);
		*FakIc=*FakIc+Ifh*p1.aoperator(120.0);
		while(p1.norm(zl*(*FakIc)*2.0)>=1.732*Vnom)
		{
			*FakIc=*FakIc*0.9;
		}
		*FakIa=Ifh;
		*FakVa=p1.polar(Vnom,0.0);
		p3=p1.polar(Vnom,-120.0)+p2.polar(Vnom,120.0);
		*FakVb=p3*0.5+(*FakIb)*zl;
		*FakVc=p3*0.5+(*FakIc)*zl;
		break;
	case 1:
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIb=p1.polar(*Vshort/2.0/p2.norm(zl),p1.arg(p3)-p1.arg(zl));
		*FakIb=*FakIb+Ifh*p1.aoperator(-120.0);
		if(p1.norm(*FakIb)>Imax)
		{
			*FakIb=p1.polar(Imax,p2.arg(*FakIb));
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(*Vshort/2.0/p2.norm(zl),p1.arg(p3)-p1.arg(zl)+180.0);
		*FakIc=*FakIc+Ifh*p1.aoperator(120.0);
		if(p1.norm(*FakIc)>Imax)
		{
			*FakIc=p1.polar(Imax,p2.arg(*FakIc));
		}
		*FakIa=Ifh;
		p3=p1.polar(Vnom,-120.0)+p2.polar(Vnom,120.0);
		*FakVb=p1.polar(p2.norm(p3)/2.0,p2.arg(p3))+(*FakIb)*zl;
		*FakVc=p1.polar(p2.norm(p3)/2.0,p2.arg(p3))+(*FakIc)*zl;
		*FakVa=p1.polar(Vnom,0.0);
		break;
	case 2:
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIb=p1.polar(p2.norm(p3/(zl+zs))/2.0,p2.arg(p3/(zl+zs)));
		*FakIb=*FakIb+Ifh*p1.aoperator(-120.0);
		*FakIa=Ifh;
		if(p1.norm(*FakIb)>Imax/4.0)
		{
			*FakIb=p1.polar(Imax/4.0,p2.arg(*FakIb));
			Vnom=Imax/4.0*p1.norm(zl+zs)*2.0/1.732;
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(p2.norm(p3/(zl+zs))/2.0,p2.arg(p3/(zl+zs))+180.0);
		*FakIc=*FakIc+Ifh*p1.aoperator(120.0);
		p3=p1.polar(Vnom,-120.0)+p2.polar(Vnom,120.0);
		p1=*FakIb*zl;
		*FakVb=p3*0.5+p1;

		p1=*FakIc*zl;
		*FakVc=p3*0.5+p1;
		*FakVa=p1.polar(Vnom,0.0);	
		break;
	case 3:
		p2=p1.polar(*Vshort,-90.0);
		p3=p1.polar(Vnom,180.0);
		*FakVb=p2+p3;
		p3=p1.polar(2.0,0.0);
		*FakVb=*FakVb/p3;
		*FakVc=*FakVb-p2;
		*FakVa=p1.polar(Vnom,0.0);	
		*FakIb=p1.polar(*Ishort,-90.0-p1.arg(zl));
		*FakIc=p1.polar(*Ishort,-90.0-p1.arg(zl)-180.0);
		*FakIa=p1.polar(0.0,0.0);
		break;
	case 4:
		if((p2.norm(zl)+(1.0-1.05*Rate)*sqrt(3.0)*Vnom/2.0/(*Ishort))>0)
			zl=p1.polar(p2.norm(zl)+(1.0-1.05*Rate)*sqrt(3.0)*Vnom/2.0/(*Ishort),p3.arg(zl));
		else 
			zl=p1.polar(0,p2.arg(zl));

		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIb=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl));
		*FakIb=*FakIb+Ifh*p1.aoperator(-120.0);
		while(p1.norm(zl*(*FakIb)*2.0)>=1.732*Vnom)
		{
			*FakIb=*FakIb*0.9;
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl)+180.0);
		*FakIc=*FakIc+Ifh*p1.aoperator(120.0);
		while(p1.norm(zl*(*FakIc)*2.0)>=1.732*Vnom)
		{
			*FakIc=*FakIc*0.9;
		}
		*FakIa=Ifh;
		*FakVa=p1.polar(Vnom,0.0);
		p3=p1.polar(Vnom,-120.0)+p2.polar(Vnom,120.0);
		*FakVb=p3*0.5+(*FakIb)*zl;
		*FakVc=p3*0.5+(*FakIc)*zl;
		break;
	case 5:
		zl=p1.polar(0,0);
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIb=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl));
		*FakIb=*FakIb+Ifh*p1.aoperator(-120.0);
		while(p1.norm(zl*(*FakIb)*2.0)>=1.732*Vnom)
		{
			*FakIb=*FakIb*0.9;
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl)+180.0);
		*FakIc=*FakIc+Ifh*p1.aoperator(120.0);
		while(p1.norm(zl*(*FakIc)*2.0)>=1.732*Vnom)
		{
			*FakIc=*FakIc*0.9;
		}
		*FakIa=Ifh;
		*FakVa=p1.polar(Vnom,0.0);
		p3=p1.polar(Vnom,-120.0)+p2.polar(Vnom,120.0);
		*FakVb=p3*0.5+(*FakIb)*zl;
		*FakVc=p3*0.5+(*FakIc)*zl;
		break;
	}
	if(!CTPoint)
	{
		*FakIa=(*FakIa)*p1.aoperator(180.0);
		*FakIb=(*FakIb)*p1.aoperator(180.0);
		*FakIc=(*FakIc)*p1.aoperator(180.0);
	}
} 
void CSttFaultCalculatTool::F3js(BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
						  Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	Complex p1,p2;
	switch(CalMode)
	{
	case 0:
		*FakIa=p1.polar(*Ishort,-p2.arg(zl))+Ifh;
		*FakVa=*FakIa*zl;
		while(p1.norm(*FakVa)>=Vnom)
		{
			*FakIa=*FakIa*0.9;
			*FakVa=*FakIa*zl;
		}
		*FakIb=p1.polar(*Ishort,-p2.arg(zl)-120.0)+Ifh*p1.aoperator(-120.0);
		*FakVb=*FakIb*zl;
		while(p1.norm(*FakVb)>=Vnom)
		{
			*FakIb=*FakIb*0.9;
			*FakVb=*FakIb*zl;
		}
		*FakIc=p1.polar(*Ishort,-p2.arg(zl)+120.0)+Ifh*p1.aoperator(120.0);
		*FakVc=*FakIc*zl;
		while(p1.norm(*FakVc)>=Vnom)
		{
			*FakIc=*FakIc*0.9;
			*FakVc=*FakIc*zl;
		}

		break;
	case 1:
		*FakIa=p1.polar(*Vshort,0.0)/zl+Ifh;
		while(p1.norm(*FakIa)>=Imax)
		{
			*FakIa=p1.polar(Imax,p2.arg(*FakIa));
		}
		*FakVa=*FakIa*zl;

		*FakIb=p1.polar(*Vshort,-120.0)/zl+Ifh*p2.aoperator(-120.0);
		while(p1.norm(*FakIb)>=Imax)
		{
			*FakIb=p1.polar(Imax,p2.arg(*FakIb));
		}
		*FakVb=*FakIb*zl;

		*FakIc=p1.polar(*Vshort,120.0)/zl+Ifh*p2.aoperator(120.0);
		while(p1.norm(*FakIc)>=Imax)
		{
			*FakIc=p1.polar(Imax,p2.arg(*FakIc));
		}
		*FakVc=*FakIc*zl;
		break;
	case 2:
		*FakIa=p1.polar(Vnom,0.0)/(zl+zs)+Ifh;
		if(p1.norm(*FakIa)>Imax/4.0)
		{
			*FakIa=p1.polar(Imax/4.0,p2.arg(*FakIa));
			Vnom=p1.norm(*FakIa*(zl+zs));
		}
		*FakVa=*FakIa*zl;
		*FakIb=p1.polar(Vnom,-120.0)/(zl+zs)+Ifh*p2.aoperator(-120.0);
		if(p1.norm(*FakIb)>Imax/4.0)
		{
			*FakIb=p1.polar(Imax/4.0,p2.arg(*FakIb));
			if(p1.norm(*FakIb*(zl+zs))>Vnom)Vnom=p1.norm(*FakIb*(zl+zs));
		}
		*FakVb=*FakIb*zl;

		*FakIc=p1.polar(Vnom,120.0)/(zl+zs)+Ifh*p2.aoperator(120.0);
		if(p1.norm(*FakIc)>Imax/4.0)
		{
			*FakIc=p1.polar(Imax/4.0,p2.arg(*FakIc));
			if(p1.norm(*FakIc*(zl+zs))>Vnom)Vnom=p1.norm(*FakIc*(zl+zs));
		}
		*FakVc=*FakIc*zl;
		break;
	case 3:
		*FakIa=p1.polar(*Ishort,-p2.arg(zl))+Ifh;
		*FakIb=*FakIa*p1.aoperator(-120.0);
		*FakIc=*FakIa*p1.aoperator(120.0);
		*FakVa=*FakIa*zl;
		*FakVa=p1.polar(*Vshort,p2.arg(*FakVa));
		*FakVb=*FakVa*p1.aoperator(-120.0);
		*FakVc=*FakVa*p1.aoperator(120.0);
		break;
	}
	if(!CTPoint)
	{
		*FakIa=(*FakIa)*p1.aoperator(180.0);
		*FakIb=(*FakIb)*p1.aoperator(180.0);
		*FakIc=(*FakIc)*p1.aoperator(180.0);
	}
}
void CSttFaultCalculatTool::FRWYjs(BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
							Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	Complex p1,p2;
	if(p1.norm(zl)<0.001)zl=p1.polar(0.001,0.0);
	switch(CalMode)
	{
	case 0:
		*FakVa=p1.polar(p2.norm(zl)*(*Ishort),0.0);
		*FakIa=p1.polar(*Ishort,-p2.arg(zl));
		break;
	case 1:
		*FakIa=p1.polar(*Vshort,0.0)/zl;
		if(p1.norm(*FakIa)>Imax)
		{
			*FakIa=p1.polar(Imax,p2.arg(*FakIa));
		}
		*FakVa=p1.polar(p2.norm(zl*(*FakIa)),0.0);
		break;
	default:
		break;
	}
	*FakVb=p1.polar(0.0,0.0);
	*FakVc=p1.polar(0.0,0.0);
	*FakIb=p1.polar(0.0,0.0);
	*FakIc=p1.polar(0.0,0.0);
	if(!CTPoint)
	{
		*FakIa=(*FakIa)*p1.aoperator(180.0);
		*FakIb=(*FakIb)*p1.aoperator(180.0);
		*FakIc=(*FakIc)*p1.aoperator(180.0);
	}
}
void CSttFaultCalculatTool::F11njs(BOOL CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
							Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	//	double  Zsumr,Zsumi,Zsum,Zsumang,Tz,Ta,Tr,Ti;
	//	double Z0z,Z0a,Z0r,Z0i,Z1z,Z1a,Z1r,Z1i,Z0sz,Z0sa,Z0sr,Z0si,I0z,I0a,I0r,I0i;
	Complex p1,p2,p3,p4,p5,p6,ulim,ilimit,ua,ub,uc,ia,ib,ic,pA;
	double d1;
	switch(CalMode)
	{
	case 0:
		zs=((p1.aoperator(240)-p2.aoperator(120))*(k0*3+1)+p3.aoperator(240)-1)/(k0*6+3);
		d1=p1.arg(zs)-p2.arg(zl);
		zs=zs/(p1.polar(*Ishort,d1)-p2.polar(p3.norm(Ifh),p4.arg(Ifh)-120))*Vnom-zl;
		ulim=(k0*6+3)*(zl+zs)/((p1.aoperator(120+180)-p2.aoperator(240)+1)*(k0*3+1)+1)/zl*(p3.polar(p4.norm(Ifh),p5.arg(Ifh)-120+180)*zl+0.9*Vnom);
		ilimit=((p1.aoperator(240)-p2.aoperator(120))*(k0*3+1)+p3.aoperator(240)-1)/(k0*6+3)/(zl+zs)*ulim+p4.polar(p5.norm(Ifh),p5.arg(Ifh)-120);
		if(*Ishort>0.9*p1.norm(ilimit))
		{
			*Ishort=0.9*p1.norm(ilimit);
			zs=((p1.aoperator(240)-p2.aoperator(120))*(k0*3+1)+p3.aoperator(240)-1)/(k0*6+3);
			zs=zs/(p1.polar(*Ishort,d1)-p2.polar(p3.norm(Ifh),p4.arg(Ifh)-120))*Vnom-zl;
		}
		*FakIa=Ifh;
		*FakIb=((p1.aoperator(240)-p2.aoperator(120))*(k0*3+1)+p3.aoperator(240)-1)/(zl+zs)/(k0*6+3)*Vnom+p4.polar(p5.norm(Ifh),p5.arg(Ifh)+240);
		*FakIc=((p1.aoperator(120)-p2.aoperator(240))*(k0*3+1)+p3.aoperator(120)-1)/(zl+zs)/(k0*6+3)*Vnom+p4.polar(p5.norm(Ifh),p5.arg(Ifh)+120);
		*FakVa=((k0*2+1)*zl+(k0*3+1)*zs)/(k0*2+1)/(zl+zs)*Vnom+Ifh*zl;
		*FakVb=((p1.aoperator(120+180)-p2.aoperator(240)+1)*(k0*3+1)+1)/(k0*6+3)/(zl+zs)*zl*p4.aoperator(240)*Vnom+p3.polar(p4.norm(Ifh),p5.arg(Ifh)-120)*zl;
		*FakVc=((p1.aoperator(120+180)-p2.aoperator(240)+1)*(k0*3+1)+1)/(k0*6+3)/(zl+zs)*zl*p4.aoperator(120)*Vnom+p3.polar(p4.norm(Ifh),p5.arg(Ifh)+120)*zl;
		break;
	case 1:
		pA=(p2.aoperator(240)-p1.aoperator(120))*((p1.aoperator(120+180)-p2.aoperator(240)+1)*(k0*3+1)+1)/(k0*6+3);
		d1=p1.arg(pA);
		zs=pA*zl/(p1.polar(*Vshort,d1)+(p2.aoperator(120)-p3.aoperator(240))*Ifh*zl)*Vnom-zl;
		ulim=(p1.polar(Imax,d1)-Ifh*p2.polar(1.0,-120))*(zl+zs)*(k0*6+3)/((p3.aoperator(240)-p4.aoperator(120))*(k0*3+1)+p5.aoperator(240)-1);
		ulim=ulim*pA*zl/(zl+zs)+(p1.aoperator(240)-p2.aoperator(120))*Ifh*zl;			
		if(*Vshort>0.9*p1.norm(ulim))//p1.norm(ilimit))
		{
			*Vshort=0.9*p1.norm(ulim);
			zs=pA*zl/(p1.polar(*Vshort,d1)+(p2.aoperator(120)-p3.aoperator(240))*Ifh*zl)-zl;
		}
		*FakIa=Ifh;
		*FakIb=((p1.aoperator(240)-p2.aoperator(120))*(k0*3+1)+p3.aoperator(240)-1)/(zl+zs)/(k0*6+3)*Vnom+Ifh*p4.polar(1.0,240);
		*FakIc=((p1.aoperator(120)-p2.aoperator(240))*(k0*3+1)+p3.aoperator(120)-1)/(zl+zs)/(k0*6+3)*Vnom+Ifh*p4.polar(1.0,120);
		*FakVa=((k0*2+1)*zl+(k0*3+1)*zs)/(k0*2+1)/(zl+zs)*Vnom+Ifh*zl;
		*FakVb=((p1.aoperator(120+180)-p2.aoperator(240)+1)*(k0*3+1)+1)*Vnom*zl*p3.aoperator(240)/(k0*6+3)/(zl+zs)+Ifh*p4.polar(1.0,240)*zl;
		*FakVc=((p1.aoperator(120+180)-p2.aoperator(240)+1)*(k0*3+1)+1)*Vnom*zl*p3.aoperator(120)/(k0*6+3)/(zl+zs)+Ifh*p4.polar(1.0,120)*zl;
		break;
	case 2:
		*FakIa=Ifh;
		p1=p2.aoperator(240);
		*FakIb=((p1-p2.aoperator(120))*(k0*3+1)+p1-1)/(zl+zs)/(k0*6+3)*Vnom+p1*Ifh;
		p3=p1.aoperator(240);
		ulim=(p1.polar(0.7*Imax,p5.arg(*FakIb))-Ifh*p2.polar(1.0,240))*(k0*6+3)*(zl+zs)/((p3-p4.aoperator(120))*(k0*3+1)+p3-1);
		ib=((p1-p2.aoperator(120))*(k0*3+1)+p1-1)/(zl+zs)/(k0*6+3)*Vnom+p1*Ifh;
		if(p1.norm(ib)>Imax/4.0)
		{
			Vnom=0.9*p1.norm(ulim);
			p1=p2.aoperator(240);
			ib=((p1-p2.aoperator(120))*(k0*3+1)+p1-1)/(zl+zs)/(k0*6+3)*Vnom+p1*Ifh;
			*FakIb=p2.polar(p1.norm(ib),p3.arg(*FakIb));
		}

		p1=p2.aoperator(120);
		*FakIc=((p1-p2.aoperator(240))*(k0*3+1)+p1-1)/(zl+zs)/(k0*6+3)*Vnom+p1*Ifh;
		*FakVa=((k0*2+1)*zl+(k0*3+1)*zs)/(zl+zs)/(k0*2+1)*Vnom+Ifh*zl;
		*FakVb=p1.aoperator(240)*Vnom*zl*((p2.aoperator(120+180)-p1.aoperator(240)+1)*(k0*3+1)+1)/(zl+zs)/(k0*6+3)+Ifh*p3.polar(1.0,-120)*zl;
		p1=p2.aoperator(120);
		*FakVc=p1.aoperator(120)*Vnom*zl*((p2.aoperator(120+180)-p1.aoperator(240)+1)*(k0*3+1)+1)/(zl+zs)/(k0*6+3)+Ifh*p3.polar(1.0,120)*zl;
		break;
	}
	if(!CTPoint)
	{
		*FakIa=(*FakIa)*p1.polar(1.0,180.0);
		*FakIb=(*FakIb)*p1.polar(1.0,180.0);
		*FakIc=(*FakIc)*p1.polar(1.0,180.0);

	}
}  
BOOL CSttFaultCalculatTool::Calculat(double Rate,BOOL bFaultDirection,BOOL bCTDirection,int nCalMode,int nFaultType,int nPhaseRef,double  RefAngle,
							  double  Umax,double  Unom,double  Imax,double *Ishort,double *Vshort,Complex Inom,
							  Complex  zl,Complex k0,Complex zs,Complex k0s,Complex *FVa,Complex *FVb,Complex *FVc,
							  Complex *FIa,Complex *FIb,Complex *FIc)

{
	BOOL bRet = TRUE;

	Complex p1,p2;
	if(Unom<0.0005)
		Unom=0.0005;
	if(nFaultType<=2)
	{
		if(bFaultDirection)
			bRet = F1njs(Rate,bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else
			bRet =  F1njs(Rate,!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType<=5)
	{
		if(bFaultDirection)
			F11js(Rate,bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else 
			F11js(Rate,!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType<=8)
	{
		if(bFaultDirection)
			F11njs(bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else 
			F11njs(!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType==9)
	{
		if(bFaultDirection)
			F3js(bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else 
			F3js(!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType==10)
	{
		if(bFaultDirection)
			FRWYjs(bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,FIa,FIb,FIc);
		else 
			FRWYjs(!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,FIa,FIb,FIc);
	}

	if(nFaultType==1||nFaultType==5||nFaultType==8)
	{
		Complex ii=*FVc;
		*FVc=*FVb;
		*FVb=*FVa;
		*FVa=ii;
		ii=*FIc;
		*FIc=*FIb;
		*FIb=*FIa;
		*FIa=ii;
	}
	else if(nFaultType==2||nFaultType==3||nFaultType==6)
	{
		Complex ii=*FVc;
		*FVc=*FVa;
		*FVa=*FVb;
		*FVb=ii;
		ii=*FIc;
		*FIc=*FIa;
		*FIa=*FIb;
		*FIb=ii;
	}

	double  Angle[6];
	Angle[0]=p1.arg(*FVa);
	Angle[1]=p1.arg(*FVb);
	Angle[2]=p1.arg(*FVc);
	Angle[3]=p1.arg(*FIa);
	Angle[4]=p1.arg(*FIb);
	Angle[5]=p1.arg(*FIc);

	for(int i=0;i<=2;i++)
	{
		if(i!=nPhaseRef)
			Angle[i]=Angle[i]-Angle[nPhaseRef]+RefAngle;
		Angle[i+3]=Angle[i+3]-Angle[nPhaseRef]+RefAngle;
	}

	Angle[nPhaseRef]=RefAngle;
	if(Angle[0]>180.0)
		Angle[0]-=360.0;
	else if(Angle[0]<-180.0)
		Angle[0]+=360.0;
	if(Angle[1]>180.0)
		Angle[1]-=360.0;
	else if(Angle[1]<-180.0)
		Angle[1]+=360.0;
	if(Angle[2]>180.0)
		Angle[2]-=360.0;
	else if(Angle[2]<-180.0)
		Angle[2]+=360.0;
	if(Angle[3]>180.0)
		Angle[3]-=360.0;
	else if(Angle[3]<-180.0)
		Angle[3]+=360.0;
	if(Angle[4]>180.0)
		Angle[4]-=360.0;
	else if(Angle[4]<-180.0)
		Angle[4]+=360.0;
	if(Angle[5]>180.0)
		Angle[5]-=360.0;
	else if(Angle[5]<-180.0)
		Angle[5]+=360.0;

	*FVa=p1.polar(p2.norm(*FVa),Angle[0]);
	*FVb=p1.polar(p2.norm(*FVb),Angle[1]);
	*FVc=p1.polar(p2.norm(*FVc),Angle[2]);
	*FIa=p1.polar(p2.norm(*FIa),Angle[3]);
	*FIb=p1.polar(p2.norm(*FIb),Angle[4]);
	*FIc=p1.polar(p2.norm(*FIc),Angle[5]);

	return bRet;
} 
Complex CSttFaultCalculatTool::GroundFactor(int nK0CalMode,double fRMRL,double fXMXL,double fPh)
{
	Complex Comp1;

	if(nK0CalMode==0)
	{
		double fTempx,fTempr;
		fTempr=fRMRL*cos(fXMXL*3.1415926/180.0);
		fTempx=fRMRL*sin(fXMXL*3.1415926/180.0);
		Comp1.SetParameter(fTempr,fTempx);
	}
	if(nK0CalMode==1)
	{
		double fTempx,fTempr;
		fTempr=(fRMRL*cos(fPh*3.1415926/180.0)*cos(fPh*3.1415926/180.0)+fXMXL*sin(fPh*3.1415926/180.0)*sin(fPh*3.1415926/180.0));
		fTempx=(fXMXL*cos(fPh*3.1415926/180.0)*sin(fPh*3.1415926/180.0)-fRMRL*sin(fPh*3.1415926/180.0)*cos(fPh*3.1415926/180.0));
		Comp1.SetParameter(fTempr,fTempx);
	}
	if(nK0CalMode==2)
	{
		double fTempx,fTempr;
		fTempr=fRMRL*cos(fXMXL*3.1415926/180.0)/3.0-1.0/3.0;//20220729 zhouhj 合并张萌代码
		fTempx=fRMRL*sin(fXMXL*3.1415926/180.0)/3.0;
		Comp1.SetParameter(fTempr,fTempx);
	}
	return Comp1;
} 

void CSttFaultCalculatTool::CalVolVaues_LowVol(Complex *pComplexU,float fCurU_Amp,int nUSetMode)
{
	Complex oComp1;

	if (nUSetMode == 0)//相电压模式
	{
		pComplexU[0].SetMag(fCurU_Amp);
		pComplexU[1].SetMag(fCurU_Amp);
		pComplexU[2].SetMag(fCurU_Amp);
	} 
	else
	{
		pComplexU[0].SetMag(fCurU_Amp/SQRT3);
		pComplexU[1].SetMag(fCurU_Amp/SQRT3);
		pComplexU[2].SetMag(fCurU_Amp/SQRT3);
	}
}

void CSttFaultCalculatTool::CalVolVaues_U2(Complex *pComplexU,float fStdLN_Vol,float fCurU_Amp)
{
	Complex oComp1,oComp2,oComp3;
	pComplexU[0] = oComp1.polar(fStdLN_Vol,120);
	pComplexU[1] = oComp1.polar(fStdLN_Vol-fCurU_Amp,240)+oComp2.polar(fCurU_Amp,120)+oComp3.polar(0,180);
	pComplexU[2] = oComp1.polar(fStdLN_Vol-fCurU_Amp,120)+oComp2.polar(fCurU_Amp,-120)+oComp3.polar(0,180);
}

void CSttFaultCalculatTool::CalVolVaues_3U0(Complex *pComplexU,float fStdLN_Vol,float fCurU_Amp)
{
	Complex oComp1,oComp2,oComp3;
	pComplexU[0] = oComp1.polar(fStdLN_Vol-fCurU_Amp,0)+oComp2.polar(fCurU_Amp,180)+oComp3.polar(fCurU_Amp,180);
	pComplexU[1] = oComp1.polar(fStdLN_Vol-fCurU_Amp,-120)+oComp2.polar(fCurU_Amp,-60)+oComp3.polar(fCurU_Amp,180);
	pComplexU[2] = oComp1.polar(fStdLN_Vol-fCurU_Amp,120)+oComp2.polar(fCurU_Amp,60)+oComp3.polar(fCurU_Amp,180);
}

void CSttFaultCalculatTool::CalculateCloseAngle(float fCloseAngel,long nFaultType,float fUaAngle,float fUbAngle,float fUcAngle,
												float fPowerAngle,
												float& fVolAngle,float& fCurAngle,int& nChanel)
{
	fCurAngle = 0;
	nChanel = 0;
	

	switch(nFaultType)
	{
	case IMPEDANCE_FAULT_TYPE_BC:
	case IMPEDANCE_FAULT_TYPE_AN:
		{
			fCloseAngel = fCloseAngel - fUaAngle + g_nCalculatAngle[0];
			fCurAngle = fCloseAngel - fUaAngle - fPowerAngle;
			nChanel = 0;
		}

		break;
	case IMPEDANCE_FAULT_TYPE_CA:
	case IMPEDANCE_FAULT_TYPE_BN:
		{
			fCloseAngel = fCloseAngel - fUbAngle + g_nCalculatAngle[1];
			fCurAngle = fCloseAngel - fUbAngle - 120 - fPowerAngle;
			nChanel = 1;
		}

		break;

	case IMPEDANCE_FAULT_TYPE_AB:
	case IMPEDANCE_FAULT_TYPE_CN:
		{
			fCloseAngel = fCloseAngel - fUcAngle + g_nCalculatAngle[2];
			fCurAngle = fCloseAngel - fUcAngle + 120 - fPowerAngle;
			nChanel = 2;
		}

		break;

	default:
		{
			fCloseAngel = fCloseAngel - fUaAngle + g_nCalculatAngle[0];
			fCurAngle = fCloseAngel - fUaAngle - fPowerAngle;
			nChanel = 0;
		}

		break;
	}

	fVolAngle = fCloseAngel;
}