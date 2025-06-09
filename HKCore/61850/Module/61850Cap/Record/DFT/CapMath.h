#pragma once



void AfxCalcFFT(double* pSrcPoints, int nPoints, double SampleRate,
	double& Mag, double& Ang, double& Fre);

double AfxFormatAngle(double prvAng);
void AfxFormatAngle(double *dAng);
