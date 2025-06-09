#ifndef _algorithm_api_h__
#define _algorithm_api_h__

#define USE_LAGRANGE_MAX_POINT_NUM                    5



double LagrangeAlg(double *pdPointX,double *pdPointY,int nPointNum,double dCurPointX);
double linearAlg(double *pdPointX,double *pdPointY,int nPointNum,double dCurPointX);
unsigned short DoubleToUShortPointValue(double dPointValue);
long DoubleToLongPointValue(double dPointValue);

#endif