#include "StdAfx.h"
#include "GbDataTypeMngr.h"
#include "GbXMLKeys.h"
#include "../../../Module/XLanguage/XLanguageMngr.h"
#include "../XLanguageResourceAts.h"
#include "../../../Module/API/GlobalConfigApi.h"	//yyj

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


long CGbDataTypeMngr::g_nGbDataTypeMngrRef = 0;
CGbDataTypeMngr* CGbDataTypeMngr::g_pGbDataTypeMngr = NULL;

const CString CGbDataTypeMngr::g_strGbSafetyComboDataTypeFile = _T("SafetyComboDataType.xml");	//安全措施组合框的数据类型定义文件
const CString CGbDataTypeMngr::g_strGbSetsDataTypeFile             = _T("SetsDataType.xml");				//定值数据类型定义文件
const CString CGbDataTypeMngr::g_strGbDateTimeFormatFile         = _T("DateTimeFormat.xml");			//日期时间格式数据类型文件
//lijq 20200228  all data types are defined in test-macro-file, 
//const CString CGbDataTypeMngr::g_strGbMacroTestDataTyeFile         = _T("MacroTestDataType.xml");			//测试功能参数数据类型文件

CGbDataTypeMngr::CGbDataTypeMngr(void)
{
	m_bCall_In_e_Report = TRUE;
	CMtDataTypeMngr::Create();
		
}

void CGbDataTypeMngr::InitGbDataTypeMngr()
{
	InitSafetyDataTypes();
	//InitMacroTestDataTypes();//lijq 20200228  all data types are defined in test-macro-file, 
	CMtDataTypeMngr::InitMacroTestDataTypes(_T(""));

	InitDateTimeFormat();
	InitGbtDataObjDataType();
	InitDataFillModeDataType();
}

CGbDataTypeMngr::~CGbDataTypeMngr(void)
{
//lijq 20200228  all data types are defined in test-macro-file, 
// 	CDataTypes *pDataTypes = CMtDataTypeMngr::GetMacroTestDataTypes();
// 	POS pos = g_pGbDataTypeMngr->m_listDataTypes.Find(pDataTypes);
// 
// 	if (pos != NULL)
// 	{
// 		g_pGbDataTypeMngr->m_listDataTypes.RemoveAt(pos);
// 	}

	CMtDataTypeMngr::Release();
	
	g_pGbDataTypeMngr->m_listDataTypes.DeleteAll();
}


CGbDataTypeMngr* CGbDataTypeMngr::Create(BOOL bCall_In_e_Report)
{
	g_nGbDataTypeMngrRef++;

	if (g_nGbDataTypeMngrRef == 1)
	{
		g_pGbDataTypeMngr = new CGbDataTypeMngr();
		g_pGbDataTypeMngr->m_bCall_In_e_Report = bCall_In_e_Report;
		g_pGbDataTypeMngr->InitGbDataTypeMngr();
	}

	return g_pGbDataTypeMngr;
}

void CGbDataTypeMngr::Release()
{
	g_nGbDataTypeMngrRef--;

	if (g_nGbDataTypeMngrRef == 0)
	{
		delete g_pGbDataTypeMngr;
		g_pGbDataTypeMngr = NULL;
	}
}

void CGbDataTypeMngr::InitSafetyDataTypes()
{
	CDataType *pDataType = NULL;
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeNumberName, g_strGbDataTypeNumber);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeStringName, g_strGbDataTypeString);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeComboboxName, g_strGbDataTypeCombobox);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeMulticomboboxName, g_strGbDataTypeMulticombobox);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeDatetimeName, g_strGbDataTypeDatetime);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypePasswordName, g_strGbDataTypePassword);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeMacAddrName, g_strGbDataTypeMacAddr);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeIPAddrName, g_strGbDataTypeIPAddr);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeDvmDatasetName, g_strGbDataTypeDvmDataset);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeImageFileName, g_strGbDataTypeImageFile);
	pDataType = m_oSafetyDataTypes.AddNew2(g_strGbDataTypeComtradeFileName, g_strGbDataTypeComtradeFile);

// 	CXLanguage oXLanguage;
// 	oXLanguage.xlang_Buid(&m_oSafetyDataTypes);
// 	xlang_TranslateByResourceFile(&m_oSafetyDataTypes, _T("SafetyDataTypes.xml"));
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(&m_oSafetyDataTypes, _T("SafetyDataTypes.xml"));
#endif

	CString strFile;
    strFile = GetConfigPath();
    strFile += g_strGbSafetyComboDataTypeFile;
	m_oSafetyComboDataTypes.Open(strFile, CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);

	//xlang_TranslateByResourceFile(&m_oSafetyComboDataTypes, g_strGbSafetyComboDataTypeFile);
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(&m_oSafetyComboDataTypes, g_strGbSafetyComboDataTypeFile);
#endif
}

void CGbDataTypeMngr::InitDateTimeFormat()
{
	CString strFile;
    strFile = GetConfigPath();
    strFile += g_strGbDateTimeFormatFile;
	m_oDateTimeFormat.Open(strFile, CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys);
	//xlang_TranslateByResourceFile(&m_oDateTimeFormat, g_strGbDateTimeFormatFile);
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(&m_oDateTimeFormat, g_strGbDateTimeFormatFile);
#endif
}

//lijq 20200228  all data types are defined in test-macro-file, 
// void CGbDataTypeMngr::InitMacroTestDataTypes()
// {
// 	CMtDataTypeMngr::InitMacroTestDataTypes(g_strGbMacroTestDataTyeFile);
// }

void CGbDataTypeMngr::InitGbtDataObjDataType()
{
	m_oGbtDataObjDataType.AddNewValue(g_strGbtDataObjTypeName_Script, g_strGbtDataObjTypeID_Script, _T("0"));
	m_oGbtDataObjDataType.AddNewValue(g_strGbtDataObjTypeName_Batch, g_strGbtDataObjTypeID_Batch, _T("1"));

	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(&m_oGbtDataObjDataType, _T("GbtDataObjDataType.xml"));
#endif
}

void CGbDataTypeMngr::InitDataFillModeDataType()
{
	static const CString g_strDataFillModeTypeName_Cell			= _T("单一数据填写模式");
	static const CString g_strDataFillModeTypeID_Cell			= _T("cell");
	static const CString g_strDataFillModeTypeName_Row			= _T("表格行填写模式");
	static const CString g_strDataFillModeTypeID_Row			= _T("row");
	static const CString g_strDataFillModeTypeName_Col 			= _T("表格列填写模式");
	static const CString g_strDataFillModeTypeID_Col			= _T("col");

	m_oDataFillModeDataType.AddNewValue(g_sLangTxt_SingDataMode/*g_strDataFillModeTypeName_Cell*/, g_strDataFillModeTypeID_Cell, _T("0"));
	m_oDataFillModeDataType.AddNewValue(g_sLangTxt_ExcelDataMode/*g_strDataFillModeTypeName_Row*/, g_strDataFillModeTypeID_Row, _T("1"));
	m_oDataFillModeDataType.AddNewValue(g_sLangTxt_ExcelDataMode2/*g_strDataFillModeTypeName_Col*/, g_strDataFillModeTypeID_Col, _T("2"));

	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
    xlang_TranslateByResourceFileEx(&m_oDataFillModeDataType, _T("DataFillModeDataType.xml"));
#endif
}

CString CGbDataTypeMngr::GetConfigPath()
{
	CString strConfigPath;

	if (g_pGbDataTypeMngr->m_bCall_In_e_Report)
	{
		strConfigPath = _P_GetConfigPath();
	}
	else
	{
		strConfigPath = _P_GetInstallPath();
		strConfigPath += _T("e-Report/Config/");
	}

	return strConfigPath;
}

void CGbDataTypeMngr::FindComboDataTypeNameByID(CString strID,CString& strName)
{
	CDataType *pType =  (CDataType*)m_oSafetyComboDataTypes.FindByID(strID);

	if (pType != NULL)
	{
		strName = pType->m_strName;
	}
}

void CGbDataTypeMngr::FindComboDataTypeValueNameByID(CString strDataType,CString strID,CString& strName)
{
	CDataType *pType =  (CDataType*)m_oSafetyComboDataTypes.FindByID(strDataType);

	if (pType == NULL)
	{
		strName = strID;
		return;
	}

	CDataTypeValue * oTypeValue = (CDataTypeValue*)pType->FindByID(strID);

	if (oTypeValue == NULL)
	{
		oTypeValue = (CDataTypeValue*)pType->GetAtIndex(0);
	}

	strName = oTypeValue->m_strName;
}
// 
// CDataTypeValue* CGbDataTypeMngr::FindComboDataTypeValueByID(const CString &strDataType,const CString &strID)
// {
// 	CDataType *pType =  (CDataType*)m_oSafetyComboDataTypes.FindByID(strDataType);
// 
// 	if (pType == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CDataTypeValue * oTypeValue = (CDataTypeValue*)pType->FindByID(strID);
// 
// 	return oTypeValue;
// }
// 
// CDataTypeValue* CGbDataTypeMngr::FindComboDataTypeValueByName(const CString &strDataType,const CString &strName)
// {
// 	CDataType *pType =  (CDataType*)m_oSafetyComboDataTypes.FindByName(strDataType);
// 
// 	if (pType == NULL)
// 	{
// 		return NULL;
// 	}
// 
// 	CDataTypeValue * oTypeValue = (CDataTypeValue*)pType->FindByName(strName);
// 
// 	return oTypeValue;
// }


void CGbDataTypeMngr::FindComboDataTypeIDByName(CString& strID,CString strName)
{
	CDataType *pType =  (CDataType*)m_oSafetyComboDataTypes.FindByName(strName);

	if (pType != NULL)
	{
		strID = pType->m_strID;
	}
}

void CGbDataTypeMngr::FindComboDataTypeValueIDByName(CString strDataType,CString& strID,CString strName)
{
	CDataType *pType = (CDataType*) m_oSafetyComboDataTypes.FindByID(strDataType);

	if (pType == NULL)
	{
		return;
	}

	CDataTypeValue * oTypeValue = (CDataTypeValue*)pType->FindByName(strName);

	if (oTypeValue == NULL)
	{
		oTypeValue = (CDataTypeValue*)pType->GetAtIndex(0);
	}

	strID = oTypeValue->m_strID;
}

//lijq 20200228  all data types are defined in test-macro-file, 
// CDataTypes* CGbDataTypeMngr::GetMacroTestDataTypes()			
// {
// 	return g_pGbDataTypeMngr->GetDataTypes(g_strGbMacroTestDataTyeFile);		
// }
//lijq 20200228  all data types are defined in test-macro-file, s
// CDataType* CGbDataTypeMngr::GetMacroTestDataType(const CString &strID)
// {
// 	CDataTypes *pDataTypes = GetMacroTestDataTypes();
// 	CDataType *pFind = NULL;
// 
// 	if (pDataTypes != NULL)
// 	{
// 		pFind = (CDataType*)pDataTypes->FindByID(strID);
// 	}
// 
// 	if (pFind == NULL)
// 	{
// 		pFind = CMtDataTypeMngr::FindDataType(strID);
// 	}
// 
// 	return pFind;//(CDataType*)pDataTypes->FindByID(strID);
// }

void CGbDataTypeMngr::FindDataTypeNameByID(CString strID,CString& strName)
{
	CDataType *pType =  (CDataType*)m_oSafetyDataTypes.FindByID(strID);

	if (pType != NULL)
	{
		strName = pType->m_strName;
	}
}

void CGbDataTypeMngr::FindDataTypeIDByName(CString& strID,CString strName)
{
	CDataType *pType =  (CDataType*)m_oSafetyDataTypes.FindByName(strName);

	if (pType != NULL)
	{
		strID = pType->m_strID;
	}
}

//2011.8.28  根据数据类型文件名获取数据类型对象
CDataTypes* CGbDataTypeMngr::GetDataTypes(const CString &strDataTypeFile)
{
	if (g_pGbDataTypeMngr == NULL)
	{
		return NULL;
	}

	CDataTypes *pDataTypes = (CDataTypes*)g_pGbDataTypeMngr->m_listDataTypes.FindByID(strDataTypeFile);

	if (pDataTypes != NULL)
	{
		return pDataTypes;
	}

	pDataTypes  = new CDataTypes();
	CString strFile;
    strFile = GetConfigPath();
    strFile += strDataTypeFile;

	if (!pDataTypes->Open(strFile, CGbXMLKeys::g_pGbXMLKeys->m_pReportValueKeys))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DataTypeUnExist2.GetString()/*_T("数据类型文件 [%s] 不存在")*/, strFile.GetString());
		delete pDataTypes;
		pDataTypes = NULL;
	}
	else
	{
		pDataTypes->m_strID = strDataTypeFile;
		pDataTypes->m_strName = strDataTypeFile;
		g_pGbDataTypeMngr->m_listDataTypes.AddNewChild(pDataTypes);
	}

	return pDataTypes;
}

//////////////////////////////////////////////////////////////////////////
void InsertDataTypesToComboBox(CDataTypes *pDataTypes, CComboBox *pBox)
{
	pBox->ResetContent();

	pDataTypes->InsertChildreComboBox(pBox);
}

void InsertDataTypeToComboBox(CDataType *pDataType, CComboBox *pBox)
{
	//如果是测试仪的IEC61850配置功能，则更新配置文件信息
	if (pDataType->m_strID == CMtDataTypeMngr::g_strMtDataType_IECConfig)
	{
		CMtDataTypeMngr::UpdateIecConfigDataType();
	}

	if (pDataType->m_strID == CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
	{
		CMtDataTypeMngr::UpdateComtradeFileDataType();
	}

	pBox->ResetContent();
	pDataType->InsertChildreComboBox(pBox);
}

BOOL IsComboMacroTestDataType(const CString &bstrDataTypeID)
{
	if (CMtDataTypeMngr::IsDataTypeCombo(bstrDataTypeID))
	{
		return TRUE;
	}

	if (g_strGbDataTypeNumber == bstrDataTypeID)
	{
		return FALSE;
	}

	if (g_strGbDataTypeString == bstrDataTypeID)
	{
		return FALSE;
	}

	if (g_strGbDataTypeExpression == bstrDataTypeID)
	{
		return FALSE;
	}

	if (g_strGbDataTypeSet == bstrDataTypeID)
	{
		return FALSE;
	}


//lijq 20200228  all data types are defined in test-macro-file, 
// 	CDataTypes *pDataTypes = CGbDataTypeMngr::GetMacroTestDataTypes();
// 
// 	if (pDataTypes == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	CDataType *pDataType = (CDataType*)pDataTypes->FindByID(bstrDataTypeID);
// 
// 	if (pDataType == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	if (pDataType->GetCount() < 1)
// 	{
// 		return FALSE;
// 	}

	return TRUE;
}

BOOL GetDataTypeNameByValue(CDataTypes *pDataTypes, const CString &bstrDataTypeID, const CString &bstrValue, CString &strName)
{
	CDataType *pDataType = NULL;
	CDataTypeValue * pValue = NULL;

	//2022-06-04  lijunqing
	if (pDataTypes != NULL)
	{
		pDataType = (CDataType*)pDataTypes->FindByID(bstrDataTypeID);
	}

	BOOL bTrue = FALSE;

	if (pDataType == NULL)
	{
		strName = bstrValue;
	}
	else
	{
#ifdef _UNICODE
		long nIndex = _wtol(bstrValue);
#else
//		long nIndex = atol(bstrValue);
		long nIndex = CString_To_long(bstrValue); //yyj
#endif

		if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_IECConfig)
		{
			strName = bstrValue;
		}
		else if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
		{
			strName = bstrValue;
		}
		else
		{
			pValue = (CDataTypeValue*)pDataType->GetAtIndex(nIndex);

			if (pValue != NULL)
			{
				strName = pValue->m_strName;
				bTrue = TRUE;
			}
			else
			{
				strName = bstrValue;
			}
		}
	}

	return bTrue;
}


BOOL GetDataTypeValueByName(CDataTypes *pDataTypes, const CString &bstrDataTypeID, CString &bstrValue, const CString &strName)
{
	CDataType *pDataType = NULL;
	CDataTypeValue * pValue = NULL;
	pDataType = (CDataType*)pDataTypes->FindByID(bstrDataTypeID);
	BOOL bTrue = FALSE;

	if (pDataType == NULL)
	{
		bstrValue = strName;
	}
	else
	{
		if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_IECConfig)
		{
			bstrValue = strName;
		}
		else if (bstrDataTypeID == CMtDataTypeMngr::g_strMtDataType_ComtradeFile)
		{
			bstrValue = strName;
		}
		else
		{
			pValue = (CDataTypeValue*)pDataType->FindByName(strName);

			if (pValue != NULL)
			{
				bstrValue = pValue->m_strIndex;
				bTrue = TRUE;
			}
			else
			{
				bstrValue = strName;
			}
		}
	}

	return bTrue;
}

