#pragma once

#include "../../../Module/BaseClass/ComplexNumber.h"
#include "../../../Module/API/MathApi.h"

void Complex_Add(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3, long nMode=COMPLEX_MODE_DEGREE);
void Complex_Sub(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3,  long nMode=COMPLEX_MODE_DEGREE);
void Complex_Mul(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3,  long nMode=COMPLEX_MODE_DEGREE);
void Complex_Div(double dMag1, double dAng1, double dMag2, double dAng2, double &dMag3, double &dAng3,  long nMode=COMPLEX_MODE_DEGREE);

double Complex_Len(double dMag1, double dAng1, double dMag2, double dAng2, long nMode=COMPLEX_MODE_DEGREE);
