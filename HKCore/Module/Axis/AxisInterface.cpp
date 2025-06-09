// AxisInterface.cpp: implementation of the AxisInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AxisInterface.h"
#include "../API/GlobalApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void CAxisInterface::SetAxisName(const CString &strXAxisName, const CString &strYAxisName, const CString &strAxisTitle){};//zhouhj 20210130 增加用于设置坐标轴名称等
void CAxisInterface::SetAxisMinMax(double dXMin, double dYMin, double dXMax, double dYMax){};


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

void CAxisScaleData::FillIt(double dVal, CPoint &point)
{
	m_dAxisScaleVal = dVal;
	m_ptAxisScale = point;
}

void CAxisScaleData::FillIt(double dVal, const CPoint &point)
{
    m_dAxisScaleVal = dVal;
    m_ptAxisScale = point;
}

void CAxisScaleData::FillIt(double dVal, long x, long y)
{
    m_dAxisScaleVal = dVal;
    m_ptAxisScale.x = x;
    m_ptAxisScale.y = y;
}

long FloatValToInt(double dVal, bool bCarry)
{
	long nVal = (long)dVal;
	double dTemp = dVal - nVal;

	if (dTemp > 0.999)
	{
		nVal = nVal + 1;
	}
	else
	{
		if (bCarry)
		{
			if (dTemp > 0.5)
			{
				nVal = nVal + 1;
			}
		}
	}

	return nVal;
}


// BOOL _ChopIsStringFloat(char* pszFloatString, long &nDotPos)
// {
// 	BOOL bIsReal = TRUE;
// 	long nDotCount = 0;
// 	long nSignalCount = 0;
// 	long nIndex = 0;
// 	
// 	nDotPos = -1;
// 	ASSERT(pszFloatString != NULL);
// 	long nLen = strlen(pszFloatString);
// 	
// 	for(nIndex=0; nIndex < nLen; ++nIndex)
// 	{
// 		if( !( (pszFloatString[nIndex] >= '0') && (pszFloatString[nIndex] <= '9') ) )
// 		{
// 			if( (nIndex == 0) && (pszFloatString[nIndex] == '-' || pszFloatString[nIndex] == '+') )
// 			{
// 				nSignalCount++;
// 			}
// 			else if (pszFloatString[nIndex] == '.')
// 			{
// 				nDotCount++;
// 				nDotPos = nIndex;
// 			}
// 			else
// 			{
// 				bIsReal = FALSE;
// 			}
// 		}
// 	}
// 	
// 	if (nSignalCount > 1 || nDotCount > 1 )
// 	{//有多个符号或者小数点不是一个
// 		bIsReal = FALSE;
// 	}
// 	
// 	return bIsReal;
// }
// 
// LPSTR _ChopFloatString(char* pszFloatString, long nDecimal)
// {
// 	BOOL bIsReal = TRUE;
// 	long nSignalCount = 0;
// 	long nIndex = 0;
// 	long nDotPos = -1;
// 	long nBeginPos = 0;
// 
// 	ASSERT(pszFloatString != NULL);
// 	long nLen = strlen(pszFloatString);
// 
// 	bIsReal = _ChopIsStringFloat(pszFloatString, nDotPos);
// 
// 	if (bIsReal)
// 	{
// 		if (nDotPos == -1)
// 		{
// 			if (nDecimal > 0)
// 			{
// 				nDotPos = nLen;
// 				pszFloatString[nDotPos] = '.';
// 
// 				for (nIndex=1; nIndex<=nDecimal; nIndex++)
// 				{
// 					pszFloatString[nDotPos+nIndex] = '0';
// 				}
// 				
// 				pszFloatString[nDotPos+nIndex] = 0;
// 			}
// 		}
// 		else
// 		{
// 			//补充小数点位数
// 			if (nDecimal >= 0)
// 			{
// 				nLen = strlen(pszFloatString);
// 
// 				if(nDecimal+nDotPos > nLen)
// 				{
// 					for (nIndex=nLen-1; nIndex<nDecimal+nDotPos; nIndex++)
// 					{
// 						pszFloatString[nIndex] = '0';
// 					}
// 
// 					pszFloatString[nIndex+1] = '\0';
// 					nLen = nDecimal+nDotPos;
// 				}
// 
// 				nIndex = nDotPos + nDecimal;
// 
// 				if (pszFloatString[nIndex+1] >= '5')
// 				{
// 					for (; nIndex>=0; nIndex--)
// 					{
// 						if (pszFloatString[nIndex] == '.')
// 						{
// 							nIndex--;
// 
// 							if (nIndex == -1)
// 							{
// 								break;
// 							}
// 						}
// 						
// 						if (pszFloatString[nIndex] >= '9')
// 						{
// 							pszFloatString[nIndex] = '0';
// 						}
// 						else
// 						{
// 							pszFloatString[nIndex]++;
// 							break;
// 						}
// 					}
// 
// 					if (nIndex == -1)
// 					{
// 						char *pTemp = pszFloatString + nLen;
// 						*(pTemp + 1) = 0;
// 						*(pTemp + 2) = 0;
// 						while (pTemp >= pszFloatString)
// 						{
// 							*(pTemp+1) = *pTemp;
// 							pTemp--;
// 						}
// 
// 						pszFloatString[0] = '1';
// 						pszFloatString[nDotPos+nDecimal+2] = 0;
// 					}
// 					else
// 					{
// 						pszFloatString[nDotPos+nDecimal+1] = 0;
// 					}
// 				}
// 				else
// 				{
// 					pszFloatString[nDotPos+nDecimal+1] = 0;
// 				}
// 			}
// 			else
// 			{
// 				for (nIndex=nLen-1; nIndex>nDotPos; nIndex--)
// 				{//格式化0
// 					if(pszFloatString[nIndex] !='0') 
// 						break;
// 					
// 					if( (pszFloatString[nIndex]=='0') && (pszFloatString[nIndex-1] != '0') )
// 					{
// 						if(pszFloatString[nIndex-1]=='.')
// 						{
// 							if (nDecimal == -1)
// 							{
// 								pszFloatString[nIndex-1] = 0;
// 							}
// 						}
// 						else 
// 						{
// 							pszFloatString[nIndex]=0;
// 						}
// 						
// 						break;
// 					}
// 					else
// 					{
// 						pszFloatString[nIndex]=0;
// 					}
// 				}
// 			}	
// 		}
// 	}
// 	
// 	return pszFloatString;
// }
// 

char* _ChopFloatString(char* pszBuffer, long nDecimal)
{
	return ChopFloatString(pszBuffer, nDecimal);
}

char* _ChopFloatString(double dValue, char* pszBuffer, long nDecimal)
{
	sprintf(pszBuffer, "%f", dValue);
	return ChopFloatString(pszBuffer, nDecimal);
}

void _ChopFloatString(CString &strBuffer, long nDecimal)
{
	char *pszBuffer = NULL;
	CString_to_char(strBuffer, &pszBuffer);
	_ChopFloatString(pszBuffer, nDecimal);
	strBuffer = pszBuffer;
	delete pszBuffer;
}

// #define _CHOP_FLOAT_STRING_MAX_LEN 40
// void _ChopFloatString(CString &strValue, long nDecimal)
// {
// 	
// 	char pszResultKeyBuff[_CHOP_FLOAT_STRING_MAX_LEN];
// 	//memset(pszFloatString, 0, _CHOP_FLOAT_STRING_MAX_LEN);
// 	strcpy(pszResultKeyBuff,strValue);
// 	_ChopFloatString(pszResultKeyBuff, nDecimal);
// 	strValue = pszResultKeyBuff;
// }



UINT axis_GetAxisIndex(const CString &strAxisID)
{
	if(strAxisID == AXIS_TYPE_ID_CARTES)
	{
		return AXIS_TYPE_INDEX_CARTES;
	}
	else if(strAxisID == AXIS_TYPE_ID_POLAR)
	{
		return AXIS_TYPE_INDEX_POLAR;
	}
	else if(strAxisID == AXIS_TYPE_ID_LOGARITHM)
	{
		return AXIS_TYPE_INDEX_LOGARITHM;
	}
	else
	{
		return AXIS_TYPE_INDEX_CARTES;
	}
}

CString axis_GetAxisID(UINT nAxisIndex)
{
	if(nAxisIndex == AXIS_TYPE_INDEX_CARTES)
	{
		return AXIS_TYPE_ID_CARTES;
	}
	else if(nAxisIndex == AXIS_TYPE_INDEX_POLAR)
	{
		return AXIS_TYPE_ID_POLAR;
	}
	else if(nAxisIndex == AXIS_TYPE_INDEX_LOGARITHM)
	{
		return AXIS_TYPE_ID_LOGARITHM;
	}
	else
	{
		return AXIS_TYPE_ID_CARTES;
	}
}

