#include "FaultCalculat.h"

CFaultCalculat::CFaultCalculat()
{

}

void CFaultCalculat::F1njs(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
						   Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	Complex p1,p2;
	switch(CalMode)
	{
	case 0:
		*FakIa=p1.polar(*Ishort,-p2.arg((k0+1)*zl))+Ifh;
		*FakVa=(k0+1)*zl*(*FakIa);
		*FakVa=p1.polar(p2.norm(*FakVa),0.0);
		if(p1.norm(*FakVa)>=Vnom)//while-->if，因为一旦计算后的FakVa还是>=Vnom，就陷入死循环
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
		if(p1.norm(*FakVa)>=Vnom)		//while-->if，因为一旦计算后的FakVa还是>=Vnom，就陷入死循环
		{
			(*FakVa)=(k0+1)*zl*(*FakIa)*0.9;
			*FakVa=p1.polar(p2.norm(*FakVa),0.0);
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
		if(p1.norm(*FakVa)>=Vnom)		//while-->if，因为一旦计算后的FakVa还是>=Vnom，就陷入死循环
		{
			*FakIa=(*FakIa)*0.9;
			(*FakVa)=(k0+1)*zl*(*FakIa);
			*FakVa=p1.polar(p2.norm(*FakVa),0.0);
		}
		*FakVa=p1.polar(p2.norm(*FakVa)+(1.0-1.05*Rate)*Vnom,0.0);

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
} 

void CFaultCalculat::F11js(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
						   Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	Complex p1,p2,p3;
	switch(CalMode)
	{
	case 0:
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIb=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl));
		*FakIb=*FakIb+Ifh*p1.aoperator(-120.0);
		if(p1.norm(zl*(*FakIb)*2.0)>=1.732*Vnom)
		{
			*FakIb=*FakIb*0.9;
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl)+180.0);
		if(p1.norm(zl*(*FakIc)*2.0)>=1.732*Vnom)
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
		else zl=p1.polar(0,p2.arg(zl));
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIb=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl));
		*FakIb=*FakIb+Ifh*p1.aoperator(-120.0);
		if(p1.norm(zl*(*FakIb)*2.0)>=1.732*Vnom)
		{
			*FakIb=*FakIb*0.9;
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl)+180.0);
		if(p1.norm(zl*(*FakIc)*2.0)>=1.732*Vnom)
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
		if(p1.norm(zl*(*FakIb)*2.0)>=1.732*Vnom)
		{
			*FakIb=*FakIb*0.9;
		}
		p3=p1.polar(Vnom,-120.0)-p2.polar(Vnom,120.0);
		*FakIc=p1.polar(*Ishort,p1.arg(p3)-p2.arg(zl)+180.0);
		if(p1.norm(zl*(*FakIc)*2.0)>=1.732*Vnom)
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
void CFaultCalculat::F3js(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
						  Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc)
{
	Complex p1,p2;
	switch(CalMode)
	{
	case 0:
		*FakIa=p1.polar(*Ishort,-p2.arg(zl))+Ifh;
		*FakVa=*FakIa*zl;
		if(p1.norm(*FakVa)>=Vnom)
		{
			*FakIa=*FakIa*0.9;
			*FakVa=*FakIa*zl;
		}
		*FakIb=p1.polar(*Ishort,-p2.arg(zl)-120.0)+Ifh*p1.aoperator(-120.0);
		*FakVb=*FakIb*zl;
		if(p1.norm(*FakVb)>=Vnom)
		{
			*FakIb=*FakIb*0.9;
			*FakVb=*FakIb*zl;
		}
		*FakIc=p1.polar(*Ishort,-p2.arg(zl)+120.0)+Ifh*p1.aoperator(120.0);
		*FakVc=*FakIc*zl;
		if(p1.norm(*FakVc)>=Vnom)
		{
			*FakIc=*FakIc*0.9;
			*FakVc=*FakIc*zl;
		}

		break;
	case 1:
		*FakIa=p1.polar(*Vshort,0.0)/zl+Ifh;
		if(p1.norm(*FakIa)>=Imax)
		{
			*FakIa=p1.polar(Imax,p2.arg(*FakIa));
		}
		*FakVa=*FakIa*zl;

		*FakIb=p1.polar(*Vshort,-120.0)/zl+Ifh*p2.aoperator(-120.0);
		if(p1.norm(*FakIb)>=Imax)
		{
			*FakIb=p1.polar(Imax,p2.arg(*FakIb));
		}
		*FakVb=*FakIb*zl;

		*FakIc=p1.polar(*Vshort,120.0)/zl+Ifh*p2.aoperator(120.0);
		if(p1.norm(*FakIc)>=Imax)
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
void CFaultCalculat::FRWYjs(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
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
void CFaultCalculat::F11njs(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
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
void CFaultCalculat::Calculat(double Rate,bool bFaultDirection,bool bCTDirection,int nCalMode,int nFaultType,int nPhaseRef,double  RefAngle,
							  double  Umax,double  Unom,double  Imax,double *Ishort,double *Vshort,Complex Inom,
							  Complex  zl,Complex k0,Complex zs,Complex k0s,Complex *FVa,Complex *FVb,Complex *FVc,
							  Complex *FIa,Complex *FIb,Complex *FIc)

{
	Complex p1,p2;
	if(Unom<0.0005)Unom=0.0005;
	if(nFaultType<=2)
	{
		if(bFaultDirection)
			F1njs(Rate,bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else
			F1njs(Rate,!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType<=5)
	{
		if(bFaultDirection)F11js(Rate,bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else F11js(Rate,!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType<=8)
	{
		if(bFaultDirection)F11njs(bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else F11njs(!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType==9)
	{
		if(bFaultDirection)F3js(bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
		else F3js(!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,
			FIa,FIb,FIc);
	}
	else if(nFaultType==10)
	{
		if(bFaultDirection)FRWYjs(bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,FIa,FIb,FIc);
		else FRWYjs(!bCTDirection,nCalMode,Ishort,Vshort,Unom,Imax,Inom,zl,k0,zs,k0s,FVa,FVb,FVc,FIa,FIb,FIc);
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
	Angle[0]=p1.arg(*FVa);Angle[1]=p1.arg(*FVb);Angle[2]=p1.arg(*FVc);
	Angle[3]=p1.arg(*FIa);Angle[4]=p1.arg(*FIb);Angle[5]=p1.arg(*FIc);
	for(int i=0;i<=2;i++)
	{
		if(i!=nPhaseRef)Angle[i]=Angle[i]-Angle[nPhaseRef]+RefAngle;
		Angle[i+3]=Angle[i+3]-Angle[nPhaseRef]+RefAngle;
	}
	Angle[nPhaseRef]=RefAngle;
	if(Angle[0]>180.0)Angle[0]-=360.0;
	else if(Angle[0]<-180.0)Angle[0]+=360.0;
	if(Angle[1]>180.0)Angle[1]-=360.0;
	else if(Angle[1]<-180.0)Angle[1]+=360.0;
	if(Angle[2]>180.0)Angle[2]-=360.0;
	else if(Angle[2]<-180.0)Angle[2]+=360.0;
	if(Angle[3]>180.0)Angle[3]-=360.0;
	else if(Angle[3]<-180.0)Angle[3]+=360.0;
	if(Angle[4]>180.0)Angle[4]-=360.0;
	else if(Angle[4]<-180.0)Angle[4]+=360.0;
	if(Angle[5]>180.0)Angle[5]-=360.0;
	else if(Angle[5]<-180.0)Angle[5]+=360.0;

	*FVa=p1.polar(p2.norm(*FVa),Angle[0]);
	*FVb=p1.polar(p2.norm(*FVb),Angle[1]);
	*FVc=p1.polar(p2.norm(*FVc),Angle[2]);
	*FIa=p1.polar(p2.norm(*FIa),Angle[3]);
	*FIb=p1.polar(p2.norm(*FIb),Angle[4]);
	*FIc=p1.polar(p2.norm(*FIc),Angle[5]);
} 

Complex CFaultCalculat::GroundFactor(int nK0CalMode,double fRMRL,double fXMXL,double fPh)
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
		fTempr=fRMRL*cos(fXMXL*3.1415926/180.0)-1.0;
		fTempx=fRMRL*sin(fXMXL*3.1415926/180.0);
		Comp1.SetParameter(fTempr,fTempx);
	}
	return Comp1;
} 