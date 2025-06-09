#include "stdafx.h"
#include "GuideBookWizardDefine.h"
#include "..\XLanguageResourceAts.h"

//////////////////////////////////////////////////////////////////////////
//CGbWzdToolXmlRWKeys

CGbWzdToolXmlRWKeys* CGbWzdToolXmlRWKeys::g_pGbWzdToolXmlKeys = NULL;
long CGbWzdToolXmlRWKeys::g_nKDBRef = 0;


CGbWzdToolXmlRWKeys::CGbWzdToolXmlRWKeys()
{
	m_strCGbtBatchItemRefKey = L"CGbtBatchItemRef";
	m_strCGbtBatchGbtDataRefKey = L"CGbtBatchGbtDataRef";
	m_strCGbtBatchItemGroupKey = L"CGbtBatchItemGroup";
	m_strCGbtBatchGbtDataGroupKey = L"CGbtBatchGbtDataGroup";
	m_strCGbtBatchItemGroupsKey = L"CGbtBatchItemGroups";
	m_strCGbtDataScriptMapKey = L"CGbtDataScriptMap";
	m_strCGbtDataInterfaceMapKey = L"CGbtDataInterfaceMap";
	m_strCGbInsertStxmlFileKey = L"CGbInsertStxmlFile";
	m_strCGbInsertStxmlFileMngrKey = L"CGbInsertStxmlFileMngr";
	m_strCGbInsertStxmlFileToolKey = L"CGbInsertStxmlFileTool";
	m_strCGbWzdDatasetRefKey = L"GbWzdDatasetRef";
	m_strCGbWzdDatasetRefsKey = L"GbWzdDatasetRefs";
	m_strCGbWzdCmdGbAttrKey = L"wizard-gb-attr";
	m_strCGbWzdCmdDeviceModelKey = L"wizard-device-model";
	m_strCGbWzdCmdSelectStxmlFileKey = L"wizard-select-stxml";
	m_strCGbWzdCmdInitGbByStxmlFileKey = L"wizard-init-stxml";
	m_strCGbWzdCmdEditGbtDataMapKey = L"wizard-data-map";
	m_strCGbWzdCmdSelectRootItemsKey = L"wizard-sel-root";
	m_strCGbWzdCmdSaveKey = L"wizard-save";
	m_strCGuideBookWizardKey = L"guidebook-wizard";
	
	
	m_strCBatchItemRefValueKey = L"CBatchItemRefValue";
	m_strValueKey = L"value";
	m_strDatasetPathKey = L"DatasetPath";
	m_strBatchVariableModeKey = L"BatchVariableMode";
	m_strBatchItemsModeKey = L"BatchItemsMode";
	m_strDataValueKey = L"DataValue";
	m_strRefObjNameKey = L"RefObjName";
	m_strRefObjPathKey = L"RefObjPath";
	m_strStxmlFileFilterKey = L"StxmlFileFilter";
	m_strStxmlFileKey = L"StxmlFile";
	m_strIec61850ConfigFileKey = L"Iec61850ConfigFile";
	m_strAddRptGroupTitleKey = L"AddRptGroupTitle";
	m_strInsertRootItemsKey = L"InsertRootItems";
	m_strRootItemsNameKey = L"RootItemsName";
	m_strRootItemsIDKey = L"RootItemsID";
	m_strUseKey = L"Use";
	m_strCGbWzdCmdKey = L"wizard-cmd";

	m_strCDinWzdFromSclGinChsKey = L"din-wzd-ch";
	m_strCDinWzdFromSclGinChKey = L"din-wzd-ch";
	m_strAppIDKey = L"app-id";
	m_strGsChIndexKey = L"ch-index";
	m_strItemPathKey = L"item-path";
}

CGbWzdToolXmlRWKeys::~CGbWzdToolXmlRWKeys()
{
}

CGbWzdToolXmlRWKeys* CGbWzdToolXmlRWKeys::Create()
{
	g_nKDBRef++;

	if (g_nKDBRef == 1)
	{
		g_pGbWzdToolXmlKeys = new CGbWzdToolXmlRWKeys();
	}

	return g_pGbWzdToolXmlKeys;
}

void CGbWzdToolXmlRWKeys::Release()
{
	g_nKDBRef--;

	if (g_nKDBRef == 0)
	{
		delete g_pGbWzdToolXmlKeys;
		g_pGbWzdToolXmlKeys = NULL;
	}
}


CString wzd_GetWzdFilePath()
{
	CString strPath;

	strPath = _P_GetLibraryPath();
	strPath += _T("GbWzdFiles\\");
	return strPath;
}

CString wzd_GetWzdFileDlgFilter()
{
	CString strFilter;
	strFilter.Format(_T("%s|(*.%s)||"), /*g_strGbWzdFileName*/g_sLangTxt_GuideWizardFile, g_strGbWzdFilePostFix);
	return strFilter;
}

