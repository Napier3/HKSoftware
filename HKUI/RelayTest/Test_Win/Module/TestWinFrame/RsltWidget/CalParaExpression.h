#include "../../../../AutoTest/Module/GuideBook/Device.h"
#include "../../../../Module/Expression/ExprEditRslt.h"


// 
// 
// CDvmDataset  g_oDataset_SetValue;
// CDvmDataset  g_oDataset_SystemPara;
// CDvmDataset  g_oDataset_TestRst;

// CDvmDataset  g_oDataset_SetValue;
// CDvmDataset  g_oDataset_SystemPara;
// CDvmDataset  g_oDataset_TestRst;


/*
BOOL CDevice::GetVariableValue(const CString &strVariable, CString &strValue, BOOL bShowLog)
{
	CDataObj *pPara = (CDataObj*)m_pSysParas->FindByID(strVariable);

	if (pPara != NULL)
	{
		strValue = pPara->m_strValue;
		return TRUE;
	}

	CDataObj *pSet = FindDataObjByID(strVariable, -1);

	if (pSet != NULL)
	{
		strValue = pSet->m_strValue;
		return TRUE;
	}

	if (bShowLog)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Variable [%s] not exist!"), strVariable.GetString());
	}

	return FALSE;
}

BOOL CDevice::GetVariableValue(const CString &strVariable,  double &dValue,  BOOL bShowLog)
{
	CString strValue;

	if (GetVariableValue(strVariable,  strValue,  bShowLog))
	{
		dValue = CString_To_double(strValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
*/


BOOL  stt_GetVariableValue(const CString &strVariable, CString &strValue, BOOL bShowLog)
{

	return TRUE;
}

BOOL stt_GetVariableValue(const CString &strVariable, double &dValue, BOOL bShowLog)
{
	CString strValue;

	if (stt_GetVariableValue(strVariable, strValue, bShowLog))
	{
		dValue = CString_To_double(strValue);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL stt_CalParaExp_FindValue(CExBaseList *pDevice, CValues *pValues, const CString &strVarID, CString &strValue)
{
	if (pValues != NULL)
	{
		if (pValues->GetValue(strVarID, strValue))
		{
			return TRUE;
		}
	}

	return  stt_GetVariableValue(strVarID, strValue, TRUE);//pDevice->GetVariableValue(strVarID, strValue, TRUE);
}


BOOL stt_CalParaExpression(const CString &strExpress, CExBaseList *pTestGlobalDatas, double &dValue, BOOL bLogError, CExBaseList *pRptTestPoint)
{
	CEpExpression oEpExp;

	if (strExpress.GetLength() == 0)
	{
		return FALSE;
	}

	if (oEpExp.ChangeEpExpression(strExpress) == -1)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*CXLanguageResourceAtsBase::g_sLangTxt_ExpressionError.GetString()/ **/_T("表达式【%s】 错误"), strExpress.GetString());
		return FALSE;
	}

	CDevice *pDevice = (CDevice*)pTestGlobalDatas;
	CString strValue;
	POS pos = oEpExp.GetHeadPosition();
	CEpExpVariable *pExpVar = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pExpVar = oEpExp.GetNext(pos);

		if (stt_CalParaExp_FindValue(pTestGlobalDatas,  (CValues*)pRptTestPoint, pExpVar->m_strVarID, strValue))
		{
#ifdef _UNICODE
			pExpVar->m_dValue = _wtof(strValue);
#else
			pExpVar->m_dValue = atof(strValue.GetString());
#endif
		}
		else
		{
			if (bLogError)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*CXLanguageResourceAtsBase::g_sLangTxt_ExpressionVariable.GetString()*/_T("表达式变量【%s】 错误"), pExpVar->m_strVarID.GetString());
				bTrue = FALSE;
			}
		}
	}

	oEpExp.Value(dValue);

	return bTrue;
}