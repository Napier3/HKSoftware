//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SCLCheckSettingMngrGlobal.h

#pragma once

#include "..\..\..\Module\BaseClass\ExBaseList.h"
#include "..\..\DataMngr\DataTypes.h"

#define MngrCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define MngrCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define MNGRCLASSID_CHECKPATHS       (MngrCLASSID_EXLISTCLASS + 0X00000000)
#define MNGRCLASSID_SINGLEPATH       (MngrCLASSID_BASECLASS + 0X00000001)
#define MNGRCLASSID_SCHEMACHECKS       (MngrCLASSID_EXLISTCLASS + 0X00000002)
#define MNGRCLASSID_SCHEMACHECK       (MngrCLASSID_BASECLASS + 0X00000003)
#define MNGRCLASSID_DLT860CHECKS       (MngrCLASSID_EXLISTCLASS + 0X00000004)
#define MNGRCLASSID_PROJAPPCHECKS       (MngrCLASSID_EXLISTCLASS + 0X00000005)
#define MNGRCLASSID_VIRLOOPCHECKS       (MngrCLASSID_EXLISTCLASS + 0X00000006)
#define MNGRCLASSID_MANNUALCHECK       (MngrCLASSID_BASECLASS + 0X00000007)
#define MNGRCLASSID_ALLCHECKS       (MngrCLASSID_EXLISTCLASS + 0X00000008)

class CSCLCheckSettingMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CSCLCheckSettingMngrXmlRWKeys();
	virtual ~CSCLCheckSettingMngrXmlRWKeys();
	static long g_nMngrRef;

public:
	static CSCLCheckSettingMngrXmlRWKeys* g_pXmlKeys;
	static CSCLCheckSettingMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strallchecksKey; //all-checks
	BSTR m_strMannualcheckKey; //check-object
	BSTR m_strVirloopchecksKey; //virloop-checks
	BSTR m_strProjAppchecksKey; //ProjAppModel-checks
	BSTR m_strDLT860checksKey; //DLT860Model-checks
	BSTR m_strSchemacheckKey; //schema-object
	BSTR m_strSchemachecksKey; //schema-checks
	BSTR m_strSinglePathKey; //single-path
	BSTR m_strcheckPathsKey; //check-paths
	BSTR m_strPathKey; //path
	BSTR m_strChoseKey; //chose
	BSTR m_strVertionKey; //vertion
	BSTR m_strMethodKey; //method
	BSTR m_strTypeKey; //type

public:
	static BSTR allchecksKey()  {   return g_pXmlKeys->m_strallchecksKey;  }
	static BSTR MannualcheckKey()  {   return g_pXmlKeys->m_strMannualcheckKey;  }
	static BSTR VirloopchecksKey()  {   return g_pXmlKeys->m_strVirloopchecksKey;  }
	static BSTR ProjAppchecksKey()  {   return g_pXmlKeys->m_strProjAppchecksKey;  }
	static BSTR DLT860checksKey()  {   return g_pXmlKeys->m_strDLT860checksKey;  }
	static BSTR SchemacheckKey()  {   return g_pXmlKeys->m_strSchemacheckKey;  }
	static BSTR SchemachecksKey()  {   return g_pXmlKeys->m_strSchemachecksKey;  }
	static BSTR SinglePathKey()  {   return g_pXmlKeys->m_strSinglePathKey;  }
	static BSTR checkPathsKey()  {   return g_pXmlKeys->m_strcheckPathsKey;  }
	static BSTR PathKey()  {   return g_pXmlKeys->m_strPathKey;  }
	static BSTR ChoseKey()  {   return g_pXmlKeys->m_strChoseKey;  }
	static BSTR VertionKey()  {   return g_pXmlKeys->m_strVertionKey;  }
	static BSTR MethodKey()  {   return g_pXmlKeys->m_strMethodKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
};



class CSCLCheckSettingMngrConstGlobal
{
private:
	CSCLCheckSettingMngrConstGlobal();
	virtual ~CSCLCheckSettingMngrConstGlobal();

public:
	static CSCLCheckSettingMngrConstGlobal* Create();
	static void Release();

	static CDataType* FindCheckSettingDataType(const  CString &strDataTypeID);

private:
	static long g_nGlobalRef;
	static CSCLCheckSettingMngrConstGlobal *g_pGlobal;

private:
	void InitGlobal();
	CDataTypes m_oIecRtdDataTypes;

public:
	void Init_checkObjectSetDataType();  //_T("checkObjectSetDataType");
	void Init_schemaCheckObjectSetDataType();  //_T("schemaCheckVertionType");
	void Init_schemaCheckMethodType();  //_T("schemaCheckMethodType");
};
