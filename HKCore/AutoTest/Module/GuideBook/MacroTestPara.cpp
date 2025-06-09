#include "stdafx.h"
#include "MacroTestPara.h"
#include "Script/GbScriptFunctions.h"
#include "../../../Module/Expression/EpExpression.h"
#include "GuideBook.h"
#include "../../../Module/TestMacro/TestMacroInterface.h"
#include "Device.h"
#include "../../../Module/TestMacro/MtDataTypeMngr.h"
#include "../../../Module/TestMacro/TestMacroInterface.h"
#include "MacroTest.h"
#include "../XLanguageResourceAts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CMacroTestPara::CMacroTestPara()
{
	m_pFaultParaDatasUser = NULL;
	m_pFaultParaDatas = NULL;
	m_pScript = NULL;
	m_pValuesForCal = NULL;//new CValues();

	m_strMacroID = _T("");
	m_strTestMode = _T("auto-test");
}

void CMacroTestPara::InitMacroID()
{
	CTestMacros *pMacros = Gb_GetMacrosPtr(this);
	CTestMacro  *pMacro = (CTestMacro*)pMacros->GetHead();

	if (pMacro != NULL)
	{
		SetMacroID(pMacro->m_strID);
	}
}

void CMacroTestPara::SetMacroID(const CString &strID)
{ 
	if (m_strMacroID == strID)
	{
		return;
	}
	else
	{
		FreeTestParas();
	}
	
	m_strMacroID = strID;
	InitTestParaDatas();
}

CMacroTestPara::~CMacroTestPara()
{
	delete m_pValuesForCal;
}

void CMacroTestPara::ClearItemInDbState()
{
// 	if (m_pScript != NULL)
// 	{
// 		m_pScript->ClearItemInDbState();
// 	}
// 
// 	if (m_pFaultParaDatas != NULL)
// 	{
// 		m_pFaultParaDatas->DeleteAll();
// 	}
// 
// 	if (m_pFaultParaDatasUser != NULL)
// 	{
// 		m_pFaultParaDatasUser->DeleteAll();
// 	}
}

void CMacroTestPara::CreateScript()
{
	if (m_pScript != NULL)
	{
		m_pScript = new CScriptText();
		AddNewChild(m_pScript);
	}
}

void CMacroTestPara::CreateFaultParaDatas()
{
	if (m_pFaultParaDatas == NULL)
	{
		m_pFaultParaDatas = new CMacroTestParaDatas;
		AddNewChild(m_pFaultParaDatas);
	}

}

void CMacroTestPara::CreateFaultParaDatasUser()
{
	if (m_pFaultParaDatasUser == NULL)
	{
		m_pFaultParaDatasUser = new CMacroTestParaDatasUser;
		AddNewChild(m_pFaultParaDatasUser);
	}
}

long CMacroTestPara::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strMacroIDKey,oNode,m_strMacroID);
	xml_GetAttibuteValue(CGbXMLKeys::g_pGbXMLKeys->m_strTestModeKey,oNode,m_strTestMode);

	return 0;
}

long CMacroTestPara::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strMacroIDKey,oElement,m_strMacroID);
	xml_SetAttributeValue(CGbXMLKeys::g_pGbXMLKeys->m_strTestModeKey,oElement,m_strTestMode);

	return 0;
}

long CMacroTestPara::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if (oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestMode);
	}
	else if (oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
		BinarySerializeRead(oBinaryBuffer, m_strTestMode);
	}
	else if (oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
		BinarySerializeWrite(oBinaryBuffer, m_strTestMode);
	}

	return 0;
}

void CMacroTestPara::InitTestParaDatas(BOOL bInitByMacro)
{
	if (m_pValuesForCal == NULL )
	{
		m_pValuesForCal = new CValues();
	}
	else
	{
		m_pValuesForCal->DeleteAll();
	}


	if (!bInitByMacro)
	{
		return;
	}

	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook == NULL)
	{
		return;
	}

	ASSERT (pGuideBook != NULL);
	ASSERT (pGuideBook->m_pTestMacros != NULL);

	//测试功能数据接口
	CTestMacros *pMacros = pGuideBook->m_pTestMacros;
	ASSERT (pMacros != NULL);

	if (pMacros != NULL)
	{
		//获取测试功能数据接口定义
		TM_GetTestMacroParasValues(pMacros, m_strMacroID, m_pValuesForCal);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_WARNING, _T("ITestMacros is null"));
	}
}

void CMacroTestPara::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);
		UINT nClassID = p->GetClassID();

		switch (nClassID)
		{
		case  GBCLASSID_SCRIPTTEXT:
			m_pScript = (CScriptText*)p;
			break;
		case GBCLASSID_FAULTPARAS:
			m_pFaultParaDatas = (CMacroTestParaDatas*)p;
			break;
		case GBCLASSID_FAULTPARASUSER:
			m_pFaultParaDatasUser = (CMacroTestParaDatasUser*)p;
			break;
		default:
			break;
		}
	}

	CreateFaultParaDatas();
	CreateFaultParaDatasUser();
#ifndef guidebook_report_dev_mode
	//InitTestParaDatas();
#endif
	if (m_pScript == NULL)
	{
		m_pScript = new CScriptText();
		AddNewChild(m_pScript);
	}
}

BSTR CMacroTestPara::GetXmlElementKey()
{
	return CGbXMLKeys::g_pGbXMLKeys->m_strParaKey;
}

CExBaseObject* CMacroTestPara::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	if(strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strScriptKey)
	{
		return new CScriptText();
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaKey)
	{
		return new CMacroTestParaDatas();
	}
	else if (strClassID == CGbXMLKeys::g_pGbXMLKeys->m_strFaultParaUserKey)
	{
		return new CMacroTestParaDatasUser();
	}

	return NULL;
}

CExBaseObject* CMacroTestPara::CreateNewChild(long nClassID)
{
	if(nClassID == GBCLASSID_SCRIPTTEXT)
	{	
		return new CScriptText();
	}
	else if (nClassID == GBCLASSID_FAULTPARAS)
	{
		return new CMacroTestParaDatas();
	}
	else if (nClassID == GBCLASSID_FAULTPARASUSER)
	{
		return new CMacroTestParaDatasUser();
	}

	return NULL;
}

BOOL CMacroTestPara::IsEqual(CBaseObject* pObj)
{
	return FALSE;
}

BOOL CMacroTestPara::CopyOwn(CBaseObject* pDesObj)
{
	ASSERT(pDesObj != NULL);
	if(pDesObj == this)
	{
		return TRUE;
	}

	CMacroTestPara* pMacroTestPara = (CMacroTestPara*)pDesObj;
	pMacroTestPara->m_strMacroID = m_strMacroID;
	pMacroTestPara->m_strTestMode = m_strTestMode;

	return TRUE;
}

CBaseObject* CMacroTestPara::Clone()
{
	CMacroTestPara* pMacroTestPara = new CMacroTestPara();
	Copy(pMacroTestPara);

	return pMacroTestPara;
}

void CMacroTestPara::CalFaultParaDatasUser()
{
	CalFaultParaDatas( m_pFaultParaDatasUser);
}

void CMacroTestPara::CalFaultParaDatas()
{
	CalFaultParaDatas( m_pFaultParaDatas);
}

void CMacroTestPara::CalFaultParaDatas(CMacroTestParaDatas *pParaDaras)
{
	POS pos = pParaDaras->GetHeadPosition();

	if (pos == NULL)
	{
		return;
	}

	CMacroTestParaData *pData = NULL;
	CExBaseObject *p = NULL;
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject*)pParaDaras->GetNext(pos);   //shaolei  20201015 原m_pFaultParaDatas

		if (p->GetClassID() == GBCLASSID_FAULTPARAS_PARA)
		{
			pData = (CMacroTestParaData*)p;
			pValue = (CValue*)m_pValuesForCal->FindByID(pData->m_strID);

			if (pValue == NULL)
			{
				if (pData->m_strID.Find(_T("$")) >= 0)
				{
					pValue = m_pValuesForCal->AddValue(pData->m_strID, _T("0"));
				}
			}

			CalFaultParaData(pData->m_strExpression, pValue);
		}
	}
}

CShortData* CMacroTestPara::GetMacroTestData(const CString &strID)
{
	CGuideBook *pGuideBook = (CGuideBook*)GetAncestor(GBCLASSID_GUIDEBOOK);

	if (pGuideBook == NULL)
	{
		return NULL;
	}

// 	if (!pGuideBook->Is61850Protocol())
// 	{
// 		return FALSE;
// 	}

	//测试功能数据接口
	CTestMacros *pMacros = pGuideBook->m_pTestMacros;
	ASSERT (pMacros != NULL);

	if (pMacros == NULL)
	{
		return NULL;
	}

	CTestMacro *pTestMacro = (CTestMacro*)pMacros->FindByID(m_strMacroID);

	if (pTestMacro == NULL)
	{
		return NULL;
	}

	CShortData *pData = pTestMacro->FindDataByID(strID);

	return pData;
}

BOOL CMacroTestPara::IsOwnMacroTestData(const CString &strID)
{
	CShortData *pData = GetMacroTestData(strID);

	return (pData != NULL);
}

BOOL CMacroTestPara::IsValueTimeNeedTransFrom_ms_s(const CString &strID)
{
	CShortData *pData = GetMacroTestData(strID);

	if (pData == NULL)
	{
		return FALSE;
	}

	CString strUnit = pData->m_strUnit;
	strUnit.MakeLower();

	if (strUnit == _T("s"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CMacroTestPara::CalFaultParaData(const CString &strExpress, CValue* pValue, BOOL bLogError)
{
	if (pValue == NULL)
	{
		return FALSE;
	}


	pValue->m_dwReserved = 1;
	CShortData *pData = GetMacroTestData(pValue->m_strID);

	if (pData != NULL)
	{
		if (pData->m_strDataTypeID == CMtDataTypeMngr::g_strMtDataType_IECConfig)
		{
			CString strIecfgFile = Gb_GetMacroTestPara_Iec61850Config(this, strExpress);
			pValue->PutValue(strIecfgFile);
			return TRUE;
		}

		if (pData->m_strDataTypeID == CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
		{
			pValue->PutValue(strExpress);
			return TRUE;
		}
	}

	if (strExpress.Left(1) == _T("\"") || strExpress.Right(1) == _T("\""))
	{
		pValue->PutValue(strExpress);
		return TRUE;
	}

    if (IsStringNumber(strExpress.GetString()))
	{
		pValue->PutValue(strExpress);
		return TRUE;
	}

	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	double dValue = 0;

	if (!Gb_CalParaExpression(strExpress, pDevice, dValue, bLogError))
	{
		if (pData->m_strDataTypeID == "string")
		{
			pValue->PutValue(strExpress);
		}

		return FALSE;
	}
// 	CEpExpression oEpExp;
// 	
// 	if (oEpExp.ChangeEpExpression(strExpress) == -1)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("表达式【%s】 错误"), strExpress);
// 		return FALSE;
// 	}
// 
// 
// 	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
//  	CString strValue;
// 	POS pos = oEpExp.GetHeadPosition();
// 	CEpExpVariable *pExpVar = NULL;
// 	BOOL bTrue = TRUE;
// 
// 	while (pos != NULL)
// 	{
// 		pExpVar = oEpExp.GetNext(pos);
// 
// 		if (pDevice->GetVariableValue(pExpVar->m_strVarID, strValue))
// 		{
// 			pExpVar->m_dValue = _wtof(strValue);
// 		}
// 		else
// 		{
// 			if (bLogError)
// 			{
// 				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("表达式变量【%s】 错误"), pExpVar->m_strVarID);
// 				bTrue = FALSE;
// 			}
// 		}
// 	}
// 
// 	oEpExp.Value(dValue);

	//对于61850规约，所有经过计算的时间单位都要转换成ms
	if (pDevice->m_nIsTimeSetsUnit_ms)
	{
		if (IsValueTimeNeedTransFrom_ms_s(pValue->m_strID))
		{
			dValue /= 1000;
		}
	}

	CString strValue;
	strValue.Format(_T("%f"), dValue);
	pValue->PutValue(strValue);

	return TRUE;
}

void CMacroTestPara::FreeTestParas()
{
	if (m_pValuesForCal != NULL)
	{
		delete m_pValuesForCal;
		m_pValuesForCal = NULL;
	}
}

CString CMacroTestPara::GetParaDatas()
{
	InitTestParaDatas();

	CString strParaDatas;

#ifndef guidebook_report_dev_mode

	if (m_pValuesForCal == NULL)
	{
		return strParaDatas;
	}

	POS pos = m_pValuesForCal->GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)m_pValuesForCal->GetNext(pos);
		pValue->m_dwReserved = 0;
	}

	//计算表达式
	CalFaultParaDatas();

	//执行扩展脚本
	CString strSyntax;
	BOOL bTrue = TRUE;
	
#ifndef NOT_USE_GB_SCRIPT
	//执行脚本
	if(m_pScript != NULL)
	{
		bTrue = Gb_RunScript(m_pScript, strSyntax);
	}
#endif

	//CalFaultParaDatasUser();

	//strParaDatas = m_pValues->GetDatasString();

	//POS pos = m_pFaultParaDatas->GetHeadPosition();
	pos = m_pValuesForCal->GetHeadPosition();

	while (pos != NULL)
	{
		pValue = (CValue *)m_pValuesForCal->GetNext(pos);

		if (pValue->m_dwReserved > 0)
		{
            strParaDatas.AppendFormat(_T("%s=%s;"), pValue->m_strID.GetString(), pValue->m_strValue.GetString());
		}
	}

    //add by  shaolei 20220215  begin
    CMacroTest *pMacroTest = (CMacroTest *)GetAncestor(GBCLASSID_MACROTEST);
    CTestMacroUiParas *pUiParas = pMacroTest->GetTestMacroUiParas();

    if(pUiParas != NULL)
    {
//         CString strParas = pUiParas->GetParaText();
//         strParaDatas.AppendFormat(_T("%s"), strParas.GetString());
		strParaDatas += pUiParas->m_strParaText;
    }
      //add by  shaolei 20220215  end

	//CExBaseObject *p = NULL;


// 	while (pos != NULL)
// 	{
// 		p = (CExBaseObject*)m_pFaultParaDatas->GetNext(pos);
// 
// 		if (p->GetClassID() == GBCLASSID_FAULTPARAS_PARA)
// 		{
// 			CValue *pValue = (CValue*)m_pValuesForCal->FindByID(p->m_strID);
// 			//CalFaultParaData(pData->m_strExpression, pValue);
// 
// 			if (pValue != NULL)
// 			{
// 				strParaDatas.AppendFormat(_T("%s=%s;"), pValue->m_strID, pValue->m_strValue);
// 			}
// 			else
// 			{
// 				CMacroTestParaData *pData = (CMacroTestParaData*)p;
// 				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("异常：【%s】=【%s】"), p->m_strID, pData->m_strExpression);
// 			}
// 		}
// 	}
#endif

	return strParaDatas;
}

CString CMacroTestPara::GetParaDatas_UIParas()
{
	CString strParas;
	CMacroTest *pMacroTest = (CMacroTest *)GetAncestor(GBCLASSID_MACROTEST);
	CTestMacroUiParas *pUiParas = pMacroTest->GetTestMacroUiParas();
	ASSERT(pUiParas != NULL);
	long nLen = pUiParas->m_strParaText.GetLength();
	ASSERT(nLen > 0);

	if(pUiParas == NULL || nLen <= 0)
	{
		return strParas;
	}

	if(nLen > 6)
	{
		CString strLeft = pUiParas->m_strParaText.Left(6);

		if(strLeft != _T("<group"))
		{
			//IEC配置，系统参数配置，硬件通道配置。不是group。需过滤
			return pUiParas->m_strParaText;
		}
	}

	CDataGroup oGrp;
	BSTR bstrText = pUiParas->m_strParaText.AllocSysString();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = oGrp.SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;

#ifdef _PSX_IDE_QT_
	delete bstrText;
#else
	SysFreeString(bstrText);
#endif

	CDevice *pDevice = (CDevice*)GetAncestor(GBCLASSID_DEVICE);
	double dValue = 0;
	CDvmData *pData = NULL;
	CExBaseList oListUiParas;
	oGrp.SelectAllDatas(oListUiParas);
	POS pos = oListUiParas.GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CDvmData *)oListUiParas.GetNext(pos);

		//界面参数绑定数据，是绑定在format属性上
		if (pData->m_strFormat.GetLength() == 0)
		{
			//没有表达式绑定
			continue;
		}

		dValue = 0;

		if (!Gb_CalParaExpression(pData->m_strFormat, pDevice, dValue, FALSE))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("电气量项目执行，计算故障参数->表达式计算错误 [%s] ，参数值设置为0.000……"), pData->m_strFormat.GetString());
		}

		pData->m_strValue.Format(_T("%.3f"),dValue);
	}

	oListUiParas.RemoveAll();
	++CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	CDataMngrXmlRWKeys::IncXmlOnlyWrite_Id_Value();

	strParas = oGrp.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys);

	--CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData;
	CDataMngrXmlRWKeys::DecXmlOnlyWrite_Id_Value();

	return strParas;
}

CString CMacroTestPara::GetParaDatasString()
{
	POS pos = m_pFaultParaDatas->GetHeadPosition();

	if (pos == NULL)
	{
		return _T("");
	}

	CMacroTestParaData *pData = NULL;
	CExBaseObject *p = NULL;
	CValue *pValue = NULL;
	CString strParas;
	CString strTemp;

	while (pos != NULL)
	{
		p = (CExBaseObject*)m_pFaultParaDatas->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_FAULTPARAS_PARA)
		{
			pData = (CMacroTestParaData*)p;
            strParas.AppendFormat(_T("%s=%s;"), pData->m_strID.GetString(), pData->m_strExpression.GetString());
		}
	}

	return strParas;
}

void CMacroTestPara::ValidateMacroTestParaData(const CShortData  *pData)
{		
	CMacroTestParaData *pPara = NULL;
	CString strTemp;
	CShortData *pTemp = (CShortData*)pData;

	if (pTemp->GetAncestor(TMCLASSID_CTMFAULTPARASEX) == NULL)
	{
		strTemp = pData->m_strID;
		pPara = (CMacroTestParaData*)m_pFaultParaDatas->FindByID(pData->m_strID);
	}
	else
	{
		strTemp = pTemp->GetIDPathEx(TMCLASSID_CTMFAULTPARASEX, FALSE);
		pPara = (CMacroTestParaData*)m_pFaultParaDatas->FindByID(strTemp);
	}

	if (pPara == NULL)
	{
		return;
	}

	CValue oValue;
	oValue.m_strName = pData->m_strName;
	oValue.m_strID = strTemp;

	if (CalFaultParaData(pPara->m_strExpression, &oValue, TRUE))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ShowResult.GetString()/*_T("表达式【%s】计算结果为【%s】")*/, pPara->m_strExpression.GetString(), oValue.m_strValue.GetString());
	}
}


CTestMacros* Gb_GetMacrosPtr(CExBaseObject *pItem)
{
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	ASSERT (pGuideBook->m_pTestMacros != NULL);
	return pGuideBook->m_pTestMacros;
}

CTestMacro* Gb_GetMacroPtr(CExBaseObject *pItem)
{
	CMacroTestPara* pTestPara = NULL;

	if (pItem->GetClassID() == GBCLASSID_MACROPARA)
	{
		pTestPara = (CMacroTestPara*)pItem;
	}
	else
	{
		CMacroTest* pMacroTest = NULL;

		if (pItem->GetClassID() == GBCLASSID_MACROTEST)
		{
			pMacroTest = (CMacroTest*)pItem;
		}
		else
		{
			pMacroTest =  (CMacroTest*)(pItem->GetAncestor(GBCLASSID_MACROTEST));
		}

		if (pMacroTest != NULL)
		{
			pTestPara = pMacroTest->GetMacroTestPara();
		}
	}

	if (pTestPara == NULL)
	{
		return NULL;
	}

// 	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
// 	ASSERT (pGuideBook != NULL);
// 	ASSERT (pGuideBook->m_pTestMacros != NULL);
// 
// 	CString strMacroId = pTestPara->GetMacroID();
// 	CTestMacro* pTestMacro = (CTestMacro*)pGuideBook->m_pTestMacros->FindByID(strMacroId);

	return Gb_GetMacroPtr(pItem, pTestPara->GetMacroID());
}

CTestMacro* Gb_GetMacroPtr(CExBaseObject *pItem, const CString &strMacroID)
{
	CGuideBook *pGuideBook = (CGuideBook*)pItem->GetAncestor(GBCLASSID_GUIDEBOOK);
	ASSERT (pGuideBook != NULL);
	ASSERT (pGuideBook->m_pTestMacros != NULL);

	CTestMacro* pTestMacro = (CTestMacro*)pGuideBook->m_pTestMacros->FindByID(strMacroID);

	return pTestMacro;
}
