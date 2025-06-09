#include "SwingTestCommon.h"

CString SwingTestValueCheck(CString strValue,float nMax,float nMin,int nAfterPoint)
{	
	bool bOk = false;
	float fValue = strValue.toFloat(&bOk);

	if(!bOk)
    {
        fValue = 0;
        strValue.setNum(fValue);
    }

	if (fValue < nMin)
	{
		strValue.setNum(nMin);
	}
	if(fValue > nMax)
	{
		strValue.setNum(nMax);
	}

	int num = 0;
	int nPoint = strValue.indexOf(".");
	if(nPoint == -1)
	{
		if (strValue == "")
		{
			strValue = "0";
		}
		if(nAfterPoint > 0)
			strValue += ".";
	}
	else
	{
		num = strValue.length()-nPoint-1;
		if (num > nAfterPoint)
		{
			if(nAfterPoint > 0)
				strValue = strValue.left(nPoint + 1 + nAfterPoint);
			else
				strValue = strValue.left(nPoint + nAfterPoint);

			num = nAfterPoint;
		}
	}

	for (int i=num;i < nAfterPoint;i++)
	{
		strValue+="0";
	}

	return strValue;
}