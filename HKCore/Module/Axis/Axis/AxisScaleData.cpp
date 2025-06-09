#include "stdafx.h"
#include "AxisScaleData.h"

/////////////////////////////////////////////////////
//             坐标轴数据类的定义
/////////////////////////////////////////////////////
CAxisScaleData::CAxisScaleData()
{
	m_dAxisScaleVal = 0;
	m_ptAxisScale.x=0;
	m_ptAxisScale.y=0;
}

CAxisScaleData::~CAxisScaleData()
{

}

void CAxisScaleData::FillIt(double dVal,CPoint point)
{
	m_dAxisScaleVal = dVal;
	m_ptAxisScale = point;
}

int FloatValToInt(double f,BOOL bCaryy)
{
	int iVal = 0;
	char pszBuff[40];
	sprintf(pszBuff,"%f",f);
	char *pTemp = pszBuff;
	while (*pTemp != 0)
	{
		if (*pTemp == '.')
			break;
		pTemp++;
	}
	if(*pTemp != '.')
		return atoi(pszBuff);
	*pTemp = 0;
	pTemp++;
	iVal = atoi(pszBuff);
	if(*pTemp >= '5' && bCaryy )
	{
		iVal++;
	}
	return iVal;
}

LPSTR chop(LPSTR cStr)
{
	if(strchr(cStr,'.')==NULL)  return cStr;
	int iLen=lstrlen(cStr);
	for (int i=iLen-1;i>=1;i--)
	{
		if(cStr[i]!='0') break;
		if((cStr[i]=='0')&&(cStr[i-1]!='0'))
		{
			if(cStr[i-1]=='.')cStr[i-1]=0;
			else cStr[i]=0;
			break;
		}
	}
	return cStr;
}

long GetIntVal(double fVal)
{
	int iTempVal1=((int)fVal)*10;
	int iTempVal2=(int)(fVal*10);
	int iTempVal=(int)fVal;
	if(iTempVal2-iTempVal1>=5) iTempVal++;
	return iTempVal;
}

void CAxisScaleData::FillIt2(float lV,float fV,int iK,CPoint cP)
{
	lVal=lV;
	fVal=fV;
	iKind=iK;
	cPt=cP;
}