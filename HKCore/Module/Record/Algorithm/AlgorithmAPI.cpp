#include "stdafx.h"

#include "AlgorithmAPI.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//arrX[N],arrY[N]分别存放的是插值节点(Xi,Yi)中的Xi,Yi,参数n为插值节点的个数,而参数x为待求解的插值节点的X值
//函数返回值为求解出来的插值节点X对应的Y值
//注意整个过程涉及的变量，除了循环变量为int外，其他均为float

double LagrangeAlg(double *pdPointX,double *pdPointY,int nPointNum,double dCurPointX)
{
	double dCurPointY=0.0;
	double dLagValue[1000];
	long nIndexK,nIndexM;
	double dTmp1,dTmp2;

	for (nIndexK = 0;nIndexK<nPointNum; nIndexK++)
	{
		if (fabs(dCurPointX-pdPointX[nIndexK])<0.00000001)
		{
			return pdPointY[nIndexK];
		}
		else if (pdPointX[nIndexK]>dCurPointX)
		{
			break;
		}
	}

	for(nIndexK = 0;nIndexK<nPointNum; nIndexK++)
	{
		dTmp1=1.0;
		dTmp2=1.0;

		for(nIndexM = 0;nIndexM<nPointNum;nIndexM++)
		{
			if(nIndexM==nIndexK)
			{
				continue;
			}

			dTmp1 *= (dCurPointX-pdPointX[nIndexM]);
			dTmp2 *= (pdPointX[nIndexK]-pdPointX[nIndexM]);
		}

		dLagValue[nIndexK]=dTmp1/dTmp2;
	}

	for(int nIndex=0;nIndex<nPointNum;nIndex++)
	{
		dCurPointY += pdPointY[nIndex]*dLagValue[nIndex];
	}

	return dCurPointY;
}

double linearAlg(double *pdPointX,double *pdPointY,int nPointNum,double dCurPointX)
{
	double dCurPointY=0.0;
	dCurPointY = pdPointY[0]+(pdPointY[1]-pdPointY[0])*(dCurPointX-pdPointX[0])/(pdPointX[1]-pdPointX[0]);
	return dCurPointY;
}

unsigned short DoubleToUShortPointValue(double dPointValue)
{
	short nPointValue = dPointValue;

	if ((dPointValue - nPointValue) > 0.5) 
	{
		nPointValue++;
	}
	else if ((dPointValue - nPointValue) < -0.5)
	{
		nPointValue--;
	}

	return (unsigned short)nPointValue;
}

long DoubleToLongPointValue(double dPointValue)
{
	long nPointValue = dPointValue;

	if ((dPointValue - nPointValue) > 0.5) 
	{
		nPointValue++;
	}
	else if ((dPointValue - nPointValue) < -0.5)
	{
		nPointValue--;
	}

	return nPointValue;
}