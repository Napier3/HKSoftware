//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CSchemaCheckSettingObjectGlobal.h

#pragma once

#include "..\..\..\Module\BaseClass\ExBaseList.h"
#include "..\..\DataMngr\DataTypes.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CSCHEMACHECKSETTINGS       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_CSCHEMACHECKSETTING       (MngrCLASSID_BASECLASS + 0X00000001)
#define MNGRCLASSID_CMANNUALCHECKSETTINGS       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_CMANNUALCHECKSETTING       (MngrCLASSID_BASECLASS + 0X00000003)

class CCSchemaCheckSettingObjectXmlRWKeys : public CXmlRWKeys
{
protected:
	CCSchemaCheckSettingObjectXmlRWKeys();
	virtual ~CCSchemaCheckSettingObjectXmlRWKeys();
	static long g_nMngrRef;

public:
	static CCSchemaCheckSettingObjectXmlRWKeys* g_pXmlKeys;
	static CCSchemaCheckSettingObjectXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCMannualCheckSettingKey; //mannualSetting
	BSTR m_strCMannualCheckSettingsKey; //mannualSettings
	BSTR m_strCSchemaCheckSettingKey; //SchemaSetting
	BSTR m_strCSchemaCheckSettingsKey; //SchemaSettings
	BSTR m_strBeSelectedKey; //beSelected
	BSTR m_strDescriptionKey; //description
	BSTR m_strVersionTypeKey; //versionType
	BSTR m_strXmlMethodKey; //xmlMethod
	BSTR m_strTokenTypeKey; //tokenType

public:
	static BSTR CMannualCheckSettingKey()  {   return g_pXmlKeys->m_strCMannualCheckSettingKey;  }
	static BSTR CMannualCheckSettingsKey()  {   return g_pXmlKeys->m_strCMannualCheckSettingsKey;  }
	static BSTR CSchemaCheckSettingKey()  {   return g_pXmlKeys->m_strCSchemaCheckSettingKey;  }
	static BSTR CSchemaCheckSettingsKey()  {   return g_pXmlKeys->m_strCSchemaCheckSettingsKey;  }
	static BSTR BeSelectedKey()  {   return g_pXmlKeys->m_strBeSelectedKey;  }
	static BSTR DescriptionKey()  {   return g_pXmlKeys->m_strDescriptionKey;  }
	static BSTR VersionTypeKey()  {   return g_pXmlKeys->m_strVersionTypeKey;  }
	static BSTR XmlMethodKey()  {   return g_pXmlKeys->m_strXmlMethodKey;  }
	static BSTR TokenTypeKey()  {   return g_pXmlKeys->m_strTokenTypeKey;  }
};



class CCSchemaCheckSettingObjectConstGlobal
{
private:
	CCSchemaCheckSettingObjectConstGlobal();
	virtual ~CCSchemaCheckSettingObjectConstGlobal();

public:
	static CCSchemaCheckSettingObjectConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CCSchemaCheckSettingObjectConstGlobal *g_pGlobal;

	void InitGlobal();
	CDataTypes m_oIecRtdDataTypes;

public:
	static CDataType* FindCheckSettingDataType(const  CString &strDataTypeID);
	void Init_checkObjectSetDataType();  //_T("checkObjectSetDataType");
	void Init_schemaCheckObjectSetDataType();  //_T("schemaCheckVertionType");
	void Init_schemaCheckMethodType();  //_T("schemaCheckMethodType");

};
