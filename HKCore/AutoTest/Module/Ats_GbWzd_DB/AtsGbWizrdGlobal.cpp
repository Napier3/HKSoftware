//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsGbWizrdGlobal.cpp

#include "stdafx.h"
#include "AtsGbWizrdGlobal.h"
#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CAtsGbWizrdXmlRWKeys

CAtsGbWizrdXmlRWKeys* CAtsGbWizrdXmlRWKeys::g_pXmlKeys = NULL;
long CAtsGbWizrdXmlRWKeys::g_nAtsGbWizrdRef = 0;


CAtsGbWizrdXmlRWKeys::CAtsGbWizrdXmlRWKeys()
{
	m_strCAts_Wzd_DvmMapsKey = L"Ats_Wzd_DvmMaps";
	m_strCAts_Wzd_DvmMapKey = L"Ats_Wzd_DvmMap";
	m_strCAts_Wzd_TemplatesKey = L"Ats_Wzd_Templates";
	m_strCAts_Wzd_TemplateKey = L"Ats_Wzd_Template";
	m_strCAts_Wzd_InterValsKey = L"Ats_Wzd_InterVals";
	m_strCAts_Wzd_InterValKey = L"Ats_Wzd_InterVal";
	m_strCAts_Wzd_TransStationsKey = L"Ats_Wzd_TransStations";
	m_strCAts_Wzd_TransStationKey = L"Ats_Wzd_TransStation";
	m_strCAts_Wzd_OperMaintainCopsKey = L"Ats_Wzd_OperMaintainCops";
	m_strCAts_Wzd_OperMaintainCopKey = L"Ats_Wzd_OperMaintainCop";
	m_strCAts_Wzd_DeviceCheckCodesKey = L"Ats_Wzd_DeviceCheckCodes";
	m_strCAts_Wzd_DeviceCheckCodeKey = L"Ats_Wzd_DeviceCheckCode";
	m_strCAts_Wzd_DeviceVersionsKey = L"Ats_Wzd_DeviceVersions";
	m_strCAts_Wzd_DeviceVersionKey = L"Ats_Wzd_DeviceVersion";
	m_strCAts_Wzd_DeviceModelsKey = L"Ats_Wzd_DeviceModels";
	m_strCAts_Wzd_DeviceModelKey = L"Ats_Wzd_DeviceModel";
	m_strCAts_Wzd_TemplateUnitsKey = L"Ats_Wzd_TemplateUnits";
	m_strCAts_Wzd_TemplateUnitKey = L"Ats_Wzd_TemplateUnit";
	m_strCAts_Wzd_TempFoldersKey = L"Ats_Wzd_TempFolders";
	m_strCAts_Wzd_TempFolderKey = L"Ats_Wzd_TempFolder";
	m_strCAts_Wzd_ULevelsKey = L"Ats_Wzd_ULevels";
	m_strCAts_Wzd_ULevelKey = L"Ats_Wzd_ULevel";
	m_strCAts_Wzd_FactorysKey = L"Ats_Wzd_Factorys";
	m_strCAts_Wzd_FactoryKey = L"Ats_Wzd_Factory";
	m_strCAts_Wzd_FactoryDeviceTypesKey = L"Ats_Wzd_FactoryDeviceTypes";
	m_strCAts_Wzd_FactoryDeviceTypeKey = L"CAts_Wzd_FactoryDeviceType";
	m_strCAts_Wzd_DeviceTypeKey = L"Ats_Wzd_DeviceType";
	m_strCAts_Wzd_DeviceTypesKey = L"Ats_Wzd_DeviceTypes";
	m_strCAts_Wzd_ProfessionalDirKey = L"Ats_Wzd_ProfessionalDir";
	m_strCAts_Wzd_ProfessionalDirsKey = L"Ats_Wzd_ProfessionalDirs";
	m_strHasULevelKey = L"HasULevel";
	m_strIndex_ProfessionKey = L"Index_Profession";
	m_strIndex_DeviceTypeKey = L"Index_DeviceType";
	m_strIndex_FacDevTypeKey = L"Index_FacDevType";
	m_strIndex_FactoryKey = L"Index_Factory";
	m_strIndex_ULevelKey = L"Index_ULevel";
	m_strIndex_FolderKey = L"Index_Folder";
	m_strIndex_ParentFolderKey = L"Index_ParentFolder";
	m_strIndex_TemplateUnitKey = L"Index_TemplateUnit";
	m_strTemplateFileNameKey = L"TemplateFileName";
	m_strDvmFileNameKey = L"DvmFileName";
	m_strFullPathKey = L"FullPath";
	m_strIndex_DeviceModelKey = L"Index_DeviceModel";
	m_strIndex_DeviceVersionKey = L"Index_DeviceVersion";
	m_strIndex_DeviceCheckCodeKey = L"Index_DeviceCheckCode";
	m_strIndex_CompanyKey = L"Index_Company";
	m_strIndex_StationKey = L"Index_Station";
	m_strIndex_InterValKey = L"Index_InterVal";
	m_strIndex_InterVallKey = L"Index_InterVal";
	m_strIndex_TemplateKey = L"Index_Template";
	m_strPortectSetSetKey = L"PortectSet";
	m_strIndex_DvmMapKey = L"Index_DvmMap";
	m_strStandDvmFileNameKey = L"StandDvmFileName";
	m_strDestDvmFileNameKey = L"DestDvmFileName";
	m_strMapFileNameKey = L"MapFileName";
	m_strFactoryNameKey = L"FactoryName";
	m_strFactoryIDKey = L"FactoryID";
	m_strDeviceCheckCodeIDKey = L"DeviceCheckCodeID";
	m_strDeviceModelIDKey = L"DeviceModelID";
	m_strDeviceTypeNameKey = L"DeviceTypeName";
	m_strDeviceTypeIDKey = L"DeviceTypeID";
	m_strDeviceVersionIDKey = L"DeviceVersionID";
	m_strInterValIDKey = L"InterValID";
	m_strCompanyNameKey = L"CompanyName";
	m_strCompanyIDKey = L"CompanyID";
	m_strProfessionNameKey = L"ProfessionName";
	m_strProfessionIDKey = L"ProfessionID";
	m_strStationIDKey = L"StationID";
	m_strULevelIDKey = L"ULevelID";
}

CAtsGbWizrdXmlRWKeys::~CAtsGbWizrdXmlRWKeys()
{
}

CAtsGbWizrdXmlRWKeys* CAtsGbWizrdXmlRWKeys::Create()
{
	g_nAtsGbWizrdRef++;

	if (g_nAtsGbWizrdRef == 1)
	{
		g_pXmlKeys = new CAtsGbWizrdXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CAtsGbWizrdXmlRWKeys::Release()
{
	g_nAtsGbWizrdRef--;

	if (g_nAtsGbWizrdRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CAtsGbWizrdConstGlobal

long CAtsGbWizrdConstGlobal::g_nGlobalRef = 0;
CAtsGbWizrdConstGlobal* CAtsGbWizrdConstGlobal::g_pGlobal = NULL;


CAtsGbWizrdConstGlobal::CAtsGbWizrdConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CAtsGbWizrdConstGlobal::~CAtsGbWizrdConstGlobal()
{
}

CAtsGbWizrdConstGlobal* CAtsGbWizrdConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CAtsGbWizrdConstGlobal();
	}

	return g_pGlobal;
}

void CAtsGbWizrdConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;