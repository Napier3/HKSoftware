// FaultCalculat.h: interface for the CFaultCalculat class.
//
//////////////////////////////////////////////////////////////////////
#pragma once

#ifndef __FAULTCALCULAT_H
#define __FAULTCALCULAT_H

#include "../../Module/SttTestBase/SttComplexp.h"
//const double PI=3.1415926;
class CFaultCalculat
{
public:
	CFaultCalculat();
	void F1njs(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void F11js(double Rate,bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void F3js(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void F11njs(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void FRWYjs(bool CTPoint,int CalMode,double *Ishort,double *Vshort,double  Vnom,double  Imax,Complex Ifh,Complex zl,Complex k0,
		Complex zs,Complex k0s,Complex *FakVa,Complex *FakVb,Complex *FakVc,Complex *FakIa,Complex *FakIb,Complex *FakIc);
	void Calculat(double Rate,bool bFaultDirection,bool bCTDirection,int nCalMode,int nFaultType,int nPhaseRef,double  RefAngle,
		double  Umax,double  Unom,double  Imax,double *Ishort,double *Vshort,Complex Inom,
		Complex  zl,Complex k0,Complex zs,Complex k0s,Complex *FVa,Complex *FVb,Complex *FVc,
		Complex *FIa,Complex *FIb,Complex *FIc);
	Complex GroundFactor(int nK0CalMode,double fRMRL,double fXMXL,double fPh);
private:

};

#endif