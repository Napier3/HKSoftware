//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsGbWizrdGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define AtsGbWizrdCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00020000)
#define AtsGbWizrdCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00020000)

#define ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIRS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000000)
#define ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIR       (AtsGbWizrdCLASSID_BASECLASS + 0X00000001)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICETYPES       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000002)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICETYPE       (AtsGbWizrdCLASSID_BASECLASS + 0X00000003)
#define ATSGBWIZRDCLASSID_CATS_WZD_FACTORYDEVICETYPE       (AtsGbWizrdCLASSID_BASECLASS + 0X00000004)
#define ATSGBWIZRDCLASSID_CATS_WZD_FACTORYDEVICETYPES       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000005)
#define ATSGBWIZRDCLASSID_CATS_WZD_FACTORY       (AtsGbWizrdCLASSID_BASECLASS + 0X00000006)
#define ATSGBWIZRDCLASSID_CATS_WZD_FACTORYS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000007)
#define ATSGBWIZRDCLASSID_CATS_WZD_ULEVEL       (AtsGbWizrdCLASSID_BASECLASS + 0X00000008)
#define ATSGBWIZRDCLASSID_CATS_WZD_ULEVELS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000009)
#define ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X0000000A)
#define ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDERS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X0000000B)
#define ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNIT       (AtsGbWizrdCLASSID_BASECLASS + 0X0000000C)
#define ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATEUNITS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X0000000D)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICEMODEL       (AtsGbWizrdCLASSID_BASECLASS + 0X0000000E)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICEMODELS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X0000000F)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICEVERSION       (AtsGbWizrdCLASSID_BASECLASS + 0X00000010)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICEVERSIONS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000011)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICECHECKCODE       (AtsGbWizrdCLASSID_BASECLASS + 0X00000012)
#define ATSGBWIZRDCLASSID_CATS_WZD_DEVICECHECKCODES       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000013)
#define ATSGBWIZRDCLASSID_CATS_WZD_OPERMAINTAINCOP       (AtsGbWizrdCLASSID_BASECLASS + 0X00000014)
#define ATSGBWIZRDCLASSID_CATS_WZD_OPERMAINTAINCOPS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000015)
#define ATSGBWIZRDCLASSID_CATS_WZD_TRANSSTATION       (AtsGbWizrdCLASSID_BASECLASS + 0X00000016)
#define ATSGBWIZRDCLASSID_CATS_WZD_TRANSSTATIONS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000017)
#define ATSGBWIZRDCLASSID_CATS_WZD_INTERVAL       (AtsGbWizrdCLASSID_BASECLASS + 0X00000018)
#define ATSGBWIZRDCLASSID_CATS_WZD_INTERVALS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X00000019)
#define ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATE       (AtsGbWizrdCLASSID_BASECLASS + 0X0000001A)
#define ATSGBWIZRDCLASSID_CATS_WZD_TEMPLATES       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X0000001B)
#define ATSGBWIZRDCLASSID_CATS_WZD_DVMMAP       (AtsGbWizrdCLASSID_BASECLASS + 0X0000001C)
#define ATSGBWIZRDCLASSID_CATS_WZD_DVMMAPS       (AtsGbWizrdCLASSID_EXLISTCLASS + 0X0000001D)

class CAtsGbWizrdXmlRWKeys : public CXmlRWKeys
{
protected:
	CAtsGbWizrdXmlRWKeys();
	virtual ~CAtsGbWizrdXmlRWKeys();
	static long g_nAtsGbWizrdRef;

public:
	static CAtsGbWizrdXmlRWKeys* g_pXmlKeys;
	static CAtsGbWizrdXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCAts_Wzd_DvmMapsKey; //CAts_Wzd_DvmMaps
	BSTR m_strCAts_Wzd_DvmMapKey; //Ats_Wzd_DvmMap
	BSTR m_strCAts_Wzd_TemplatesKey; //Ats_Wzd_Templates
	BSTR m_strCAts_Wzd_TemplateKey; //Ats_Wzd_Template
	BSTR m_strCAts_Wzd_InterValsKey; //Ats_Wzd_InterVals
	BSTR m_strCAts_Wzd_InterValKey; //Ats_Wzd_InterVals
	BSTR m_strCAts_Wzd_TransStationsKey; //Ats_Wzd_TransStations
	BSTR m_strCAts_Wzd_TransStationKey; //Ats_Wzd_TransStation
	BSTR m_strCAts_Wzd_OperMaintainCopsKey; //Ats_Wzd_OperMaintainCops
	BSTR m_strCAts_Wzd_OperMaintainCopKey; //Ats_Wzd_OperMaintainCop
	BSTR m_strCAts_Wzd_DeviceCheckCodesKey; //Ats_Wzd_DeviceCheckCodes
	BSTR m_strCAts_Wzd_DeviceCheckCodeKey; //Ats_Wzd_DeviceCheckCode
	BSTR m_strCAts_Wzd_DeviceVersionsKey; //Ats_Wzd_DeviceVersions
	BSTR m_strCAts_Wzd_DeviceVersionKey; //Ats_Wzd_DeviceVersion
	BSTR m_strCAts_Wzd_DeviceModelsKey; //Ats_Wzd_DeviceModels
	BSTR m_strCAts_Wzd_DeviceModelKey; //Ats_Wzd_DeviceModel
	BSTR m_strCAts_Wzd_TemplateUnitsKey; //Ats_Wzd_TemplateUnits
	BSTR m_strCAts_Wzd_TemplateUnitKey; //Ats_Wzd_TemplateUnit
	BSTR m_strCAts_Wzd_TempFoldersKey; //Ats_Wzd_TempFolders
	BSTR m_strCAts_Wzd_TempFolderKey; //Ats_Wzd_TempFolder
	BSTR m_strCAts_Wzd_ULevelsKey; //Ats_Wzd_ULevels
	BSTR m_strCAts_Wzd_ULevelKey; //Ats_Wzd_ULevel
	BSTR m_strCAts_Wzd_FactorysKey; //Ats_Wzd_Factorys
	BSTR m_strCAts_Wzd_FactoryKey; //Ats_Wzd_Factory
	BSTR m_strCAts_Wzd_FactoryDeviceTypesKey; //Ats_Wzd_FactoryDeviceTypes
	BSTR m_strCAts_Wzd_FactoryDeviceTypeKey; //CAts_Wzd_FactoryDeviceType
	BSTR m_strCAts_Wzd_DeviceTypeKey; //Ats_Wzd_DeviceType
	BSTR m_strCAts_Wzd_DeviceTypesKey; //Ats_Wzd_DeviceTypes
	BSTR m_strCAts_Wzd_ProfessionalDirKey; //Ats_Wzd_ProfessionalDir
	BSTR m_strCAts_Wzd_ProfessionalDirsKey; //Ats_Wzd_ProfessionalDirs
	BSTR m_strHasULevelKey; //HasULevel
	BSTR m_strIndex_ProfessionKey; //Index_Profession
	BSTR m_strIndex_DeviceTypeKey; //Index_DeviceType
	BSTR m_strIndex_FacDevTypeKey; //Index_FacDevType
	BSTR m_strIndex_FactoryKey; //Index_Factory
	BSTR m_strIndex_ULevelKey; //Index_ULevel
	BSTR m_strIndex_FolderKey; //Index_Folder
	BSTR m_strIndex_ParentFolderKey; //Index_ParentFolder
	BSTR m_strIndex_TemplateUnitKey; //Index_TemplateUnit
	BSTR m_strTemplateFileNameKey; //TemplateFileName
	BSTR m_strDvmFileNameKey; //DvmFileName
	BSTR m_strFullPathKey; //FullPath
	BSTR m_strIndex_DeviceModelKey; //Index_DeviceModel
	BSTR m_strIndex_DeviceVersionKey; //Index_DeviceVersion
	BSTR m_strIndex_DeviceCheckCodeKey; //Index_DeviceCheckCode
	BSTR m_strIndex_CompanyKey; //Index_Company
	BSTR m_strIndex_StationKey; //Index_Station
	BSTR m_strIndex_InterValKey; //Index_InterVal
	BSTR m_strIndex_InterVallKey; //Index_InterVal
	BSTR m_strIndex_TemplateKey; //Index_Template
	BSTR m_strPortectSetSetKey; //PortectSet
	BSTR m_strIndex_DvmMapKey; //Index_DvmMap
	BSTR m_strStandDvmFileNameKey; //StandDvmFileName
	BSTR m_strDestDvmFileNameKey; //DestDvmFileName
	BSTR m_strMapFileNameKey; //MapFileName
	BSTR m_strFactoryNameKey; //FactoryName
	BSTR m_strFactoryIDKey; //FactoryID
	BSTR m_strDeviceCheckCodeIDKey; //DeviceCheckCodeID
	BSTR m_strDeviceModelIDKey; //DeviceModelID
	BSTR m_strDeviceTypeNameKey; //DeviceTypeName
	BSTR m_strDeviceTypeIDKey; //DeviceTypeID
	BSTR m_strDeviceVersionIDKey; //DeviceVersionID
	BSTR m_strInterValIDKey; //InterValID
	BSTR m_strCompanyNameKey; //CompanyName
	BSTR m_strCompanyIDKey; //CompanyID
	BSTR m_strProfessionNameKey; //ProfessionName
	BSTR m_strProfessionIDKey; //ProfessionID
	BSTR m_strStationIDKey; //StationID
	BSTR m_strULevelIDKey; //ULevelID

public:
	static BSTR CAts_Wzd_DvmMapsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DvmMapsKey;  }
	static BSTR CAts_Wzd_DvmMapKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DvmMapKey;  }
	static BSTR CAts_Wzd_TemplatesKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TemplatesKey;  }
	static BSTR CAts_Wzd_TemplateKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TemplateKey;  }
	static BSTR CAts_Wzd_InterValsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_InterValsKey;  }
	static BSTR CAts_Wzd_InterValKey()  {   return g_pXmlKeys->m_strCAts_Wzd_InterValKey;  }
	static BSTR CAts_Wzd_TransStationsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TransStationsKey;  }
	static BSTR CAts_Wzd_TransStationKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TransStationKey;  }
	static BSTR CAts_Wzd_OperMaintainCopsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_OperMaintainCopsKey;  }
	static BSTR CAts_Wzd_OperMaintainCopKey()  {   return g_pXmlKeys->m_strCAts_Wzd_OperMaintainCopKey;  }
	static BSTR CAts_Wzd_DeviceCheckCodesKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceCheckCodesKey;  }
	static BSTR CAts_Wzd_DeviceCheckCodeKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceCheckCodeKey;  }
	static BSTR CAts_Wzd_DeviceVersionsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceVersionsKey;  }
	static BSTR CAts_Wzd_DeviceVersionKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceVersionKey;  }
	static BSTR CAts_Wzd_DeviceModelsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceModelsKey;  }
	static BSTR CAts_Wzd_DeviceModelKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceModelKey;  }
	static BSTR CAts_Wzd_TemplateUnitsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TemplateUnitsKey;  }
	static BSTR CAts_Wzd_TemplateUnitKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TemplateUnitKey;  }
	static BSTR CAts_Wzd_TempFoldersKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TempFoldersKey;  }
	static BSTR CAts_Wzd_TempFolderKey()  {   return g_pXmlKeys->m_strCAts_Wzd_TempFolderKey;  }
	static BSTR CAts_Wzd_ULevelsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_ULevelsKey;  }
	static BSTR CAts_Wzd_ULevelKey()  {   return g_pXmlKeys->m_strCAts_Wzd_ULevelKey;  }
	static BSTR CAts_Wzd_FactorysKey()  {   return g_pXmlKeys->m_strCAts_Wzd_FactorysKey;  }
	static BSTR CAts_Wzd_FactoryKey()  {   return g_pXmlKeys->m_strCAts_Wzd_FactoryKey;  }
	static BSTR CAts_Wzd_FactoryDeviceTypesKey()  {   return g_pXmlKeys->m_strCAts_Wzd_FactoryDeviceTypesKey;  }
	static BSTR CAts_Wzd_FactoryDeviceTypeKey()  {   return g_pXmlKeys->m_strCAts_Wzd_FactoryDeviceTypeKey;  }
	static BSTR CAts_Wzd_DeviceTypeKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceTypeKey;  }
	static BSTR CAts_Wzd_DeviceTypesKey()  {   return g_pXmlKeys->m_strCAts_Wzd_DeviceTypesKey;  }
	static BSTR CAts_Wzd_ProfessionalDirKey()  {   return g_pXmlKeys->m_strCAts_Wzd_ProfessionalDirKey;  }
	static BSTR CAts_Wzd_ProfessionalDirsKey()  {   return g_pXmlKeys->m_strCAts_Wzd_ProfessionalDirsKey;  }
	static BSTR HasULevelKey()  {   return g_pXmlKeys->m_strHasULevelKey;  }
	static BSTR Index_ProfessionKey()  {   return g_pXmlKeys->m_strIndex_ProfessionKey;  }
	static BSTR Index_DeviceTypeKey()  {   return g_pXmlKeys->m_strIndex_DeviceTypeKey;  }
	static BSTR Index_FacDevTypeKey()  {   return g_pXmlKeys->m_strIndex_FacDevTypeKey;  }
	static BSTR Index_FactoryKey()  {   return g_pXmlKeys->m_strIndex_FactoryKey;  }
	static BSTR Index_ULevelKey()  {   return g_pXmlKeys->m_strIndex_ULevelKey;  }
	static BSTR Index_FolderKey()  {   return g_pXmlKeys->m_strIndex_FolderKey;  }
	static BSTR Index_ParentFolderKey()  {   return g_pXmlKeys->m_strIndex_ParentFolderKey;  }
	static BSTR Index_TemplateUnitKey()  {   return g_pXmlKeys->m_strIndex_TemplateUnitKey;  }
	static BSTR TemplateFileNameKey()  {   return g_pXmlKeys->m_strTemplateFileNameKey;  }
	static BSTR DvmFileNameKey()  {   return g_pXmlKeys->m_strDvmFileNameKey;  }
	static BSTR FullPathKey()  {   return g_pXmlKeys->m_strFullPathKey;  }
	static BSTR Index_DeviceModelKey()  {   return g_pXmlKeys->m_strIndex_DeviceModelKey;  }
	static BSTR Index_DeviceVersionKey()  {   return g_pXmlKeys->m_strIndex_DeviceVersionKey;  }
	static BSTR Index_DeviceCheckCodeKey()  {   return g_pXmlKeys->m_strIndex_DeviceCheckCodeKey;  }
	static BSTR Index_CompanyKey()  {   return g_pXmlKeys->m_strIndex_CompanyKey;  }
	static BSTR Index_StationKey()  {   return g_pXmlKeys->m_strIndex_StationKey;  }
	static BSTR Index_InterValKey()  {   return g_pXmlKeys->m_strIndex_InterValKey;  }
	static BSTR Index_InterVallKey()  {   return g_pXmlKeys->m_strIndex_InterVallKey;  }
	static BSTR Index_TemplateKey()  {   return g_pXmlKeys->m_strIndex_TemplateKey;  }
	static BSTR PortectSetSetKey()  {   return g_pXmlKeys->m_strPortectSetSetKey;  }
	static BSTR Index_DvmMapKey()  {   return g_pXmlKeys->m_strIndex_DvmMapKey;  }
	static BSTR StandDvmFileNameKey()  {   return g_pXmlKeys->m_strStandDvmFileNameKey;  }
	static BSTR DestDvmFileNameKey()  {   return g_pXmlKeys->m_strDestDvmFileNameKey;  }
	static BSTR MapFileNameKey()  {   return g_pXmlKeys->m_strMapFileNameKey;  }
};



class CAtsGbWizrdConstGlobal
{
private:
	CAtsGbWizrdConstGlobal();
	virtual ~CAtsGbWizrdConstGlobal();

public:
	static CAtsGbWizrdConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CAtsGbWizrdConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};