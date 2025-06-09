#pragma once



void AfxCalcFFT(double* pSrcPoints, int nPoints, double SampleRate,double& Mag, double& Ang, double& Fre);
void AfxCalcFFT(double* pSrcPoints, int nPoints, double SampleRate,double *pArrMag, double *pArrAng, double *pArrFre, long nHarmCount);

double AfxFormatAngle(double prvAng);
void AfxFormatAngle(double *dAng);
