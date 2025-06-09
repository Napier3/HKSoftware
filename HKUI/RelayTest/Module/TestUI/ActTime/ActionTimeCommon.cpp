#include "ActionTimeCommon.h"
#include "../../../../Module/TestMacro/TestMacro.h"
#include "../../../../Module/TestMacro/TestMacros.h"
#include "../../SttCmd/GuideBook/SttMacroTest.h"
#include "SttMultiMacroActionTimeParasDefine.h"

CString ActTimeValueCheck(CString strValue,float nMax,float nMin,int nAfterPoint)
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
		if(nAfterPoint>0)
			strValue += ".";
	}
	else
	{
		num = strValue.length()-nPoint-1;
		if (num > nAfterPoint)
		{
			if(nAfterPoint >0)
				strValue = strValue.left(nPoint + 1 + nAfterPoint);
			else
				strValue = strValue.left(nPoint + nAfterPoint);

			num = nAfterPoint;
		}
	}

	for (int i=num;i<nAfterPoint;i++)
	{
		strValue+="0";
	}

	return strValue;
}

void ActTimeCheckParaExist(CExBaseList *pParas,CString strID)
{
	if(pParas == NULL)
		return;

	CSttMacroTestParaData *pData = (CSttMacroTestParaData *)pParas->FindByID(strID);
	if(pData == NULL)
	{
		CSttMacroTestParaData *pNew = new CSttMacroTestParaData();
		pNew->m_strName = STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_DEFAULT;
		pNew->m_strID = strID;
		pNew->m_strValue = STT_MULTI_MACRO_ACTIONTIME_PARAS_ID_DEFAULT;
		pParas->AddNewChild(pNew);
	}
}