//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XrioCfgMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

#define XRIOCLASSID_BASECLASS			(CLASSID_BASECLASS + 0X00040000)
#define XRIOCLASSID_EXLISTCLASS			(CLASSID_EXLISTCLASS + 0X00040000)

#define XRIOCLASSID_XRIO				(XRIOCLASSID_EXLISTCLASS + 0X00000001)
#define XRIOCLASSID_CUSTOM		      	(XRIOCLASSID_EXLISTCLASS + 0X00000002)
#define XRIOCLASSID_CUSTOMBLOCK     	(XRIOCLASSID_EXLISTCLASS + 0X00000003)
#define XRIOCLASSID_CUSTOMPARAMETER		(XRIOCLASSID_EXLISTCLASS + 0X00000004)

#define XRIOCLASSID_UNIT				(XRIOCLASSID_BASECLASS + 0X00000005)

#define XRIOCLASSID_ENUMLIST			(XRIOCLASSID_EXLISTCLASS + 0X00000006)
#define XRIOCLASSID_ENUMVALUE			(XRIOCLASSID_BASECLASS + 0X00000007)

#define XRIOCLASSID_ENABLEDREFLIST		(XRIOCLASSID_EXLISTCLASS + 0X00000008)

#define XRIOCLASSID_VALUEREFLIST		(XRIOCLASSID_EXLISTCLASS + 0X00000009)

#define XRIOCLASSID_REFPARAM			(XRIOCLASSID_BASECLASS + 0X0000000A)
#define XRIOCLASSID_REFENUM			    (XRIOCLASSID_BASECLASS + 0X0000000B)

#define XRIOCLASSID_RIO					(XRIOCLASSID_EXLISTCLASS + 0X0000000C)

#define XRIOCLASSID_RIO_ATTR			(XRIOCLASSID_BASECLASS + 0X0000000D)
#define XRIOCLASSID_RIO_DATA			(XRIOCLASSID_EXLISTCLASS + 0X0000000E)
#define XRIOCLASSID_RIO_GROUP			(XRIOCLASSID_EXLISTCLASS + 0X0000000F)
#define XRIOCLASSID_RIO_TEXTFILE				(XRIOCLASSID_EXLISTCLASS + 0X00000010)


#define WM_THREAD_XRIO_PARAMETERS_SHOW      (WM_USER + 1021)

class CXrioCfgMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CXrioCfgMngrXmlRWKeys();
	virtual ~CXrioCfgMngrXmlRWKeys();
	static long g_nXrioRef;

public:
	static CXrioCfgMngrXmlRWKeys* g_pXmlKeys;
	static CXrioCfgMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strXRioKey;		//Xrio
	BSTR m_strCustomKey;		//Custom
	BSTR m_strCustomBlockKey;	//Block
	BSTR m_strCustomParameterKey;	//Parameter
	BSTR m_strNameKey;		//Name
	BSTR m_strDescriptionKey;	//Description
	BSTR m_strForeignIdKey;        //ForeignId
	BSTR m_strDataTypeKey;		//DataType
	BSTR m_strEnumListKey;		//EnumList
	BSTR m_strEnumValueKey;		//EnumValue
	BSTR m_strEnabledFormulaKey;	//EnabledFormula
	BSTR m_strEnabledRefListKey;	//EnabledRefList
	BSTR m_strValueFormulaKey;	//ValueFormula
	BSTR m_strValueRefListKey;	//ValueRefList
	BSTR m_strRefParamKey;		//RefParam
	BSTR m_strRefEnumKey;		//RefEnum
	BSTR m_strValueKey;		//Value
	BSTR m_strMinValueKey;		//MinValue
	BSTR m_strMaxValueKey;		//MaxValue
	BSTR m_strUnitKey;		//Unit

	BSTR m_strIdKey;		//Id
	BSTR m_strRefIdKey;		//RefId
	BSTR m_strEnumIdKey;		//EnumId
	BSTR m_strEnabledKey;	//Enabled
	BSTR m_strUnitDecimalPlacesKey;	//DecimalPlaces
	
public:
	static BSTR XrioKey()  {   return g_pXmlKeys->m_strXRioKey;  }
	static BSTR CustomKey()  {   return g_pXmlKeys->m_strCustomKey;  }
	static BSTR CustomBlockKey()  {   return g_pXmlKeys->m_strCustomBlockKey;  }
	static BSTR CustomParameterKey()  {   return g_pXmlKeys->m_strCustomParameterKey;  }
	static BSTR NameKey()  {   return g_pXmlKeys->m_strNameKey;  }
	static BSTR DescriptionKey()  {   return g_pXmlKeys->m_strDescriptionKey;  }
	static BSTR ForeignIdKey()  {   return g_pXmlKeys->m_strForeignIdKey;  }
	static BSTR DataTypeKey()  {   return g_pXmlKeys->m_strDataTypeKey;  }

	static BSTR EnumListKey()  {   return g_pXmlKeys->m_strEnumListKey;  }
	static BSTR EnumValueKey()  {   return g_pXmlKeys->m_strEnumValueKey;  }
	static BSTR EnabledFormulaKey()  {   return g_pXmlKeys->m_strEnabledFormulaKey;  }
	static BSTR EnabledRefListKey()  {   return g_pXmlKeys->m_strEnabledRefListKey;  }

	static BSTR ValueFormulaKey()  {   return g_pXmlKeys->m_strValueFormulaKey;  }
	static BSTR ValueRefListKey()  {   return g_pXmlKeys->m_strValueRefListKey;  }
	static BSTR RefParamKey()  {   return g_pXmlKeys->m_strRefParamKey;  }
	static BSTR RefEnumKey()  {   return g_pXmlKeys->m_strRefEnumKey;  }

	static BSTR ValueKey()	{	return g_pXmlKeys->m_strValueKey;	}
	static BSTR MinValueKey()  {   return g_pXmlKeys->m_strMinValueKey;  }
	static BSTR MaxValueKey()  {   return g_pXmlKeys->m_strMaxValueKey;  }

	static BSTR UnitKey()  {   return g_pXmlKeys->m_strUnitKey;  }

	static BSTR IdKey()  {   return g_pXmlKeys->m_strIdKey;  }
	static BSTR RefIdWKey()	{	return g_pXmlKeys->m_strRefIdKey;	}
	static BSTR EnumIdKey()	{	return g_pXmlKeys->m_strEnumIdKey;	}

	static BSTR EnabledKey()  {   return g_pXmlKeys->m_strEnabledKey;  }
	static BSTR DecimalPlacesWKey()	{	return g_pXmlKeys->m_strUnitDecimalPlacesKey;	}
};

class CXrioCfgMngrConstGlobal
{
private:
	CXrioCfgMngrConstGlobal();
	virtual ~CXrioCfgMngrConstGlobal();

public:
	static CXrioCfgMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CXrioCfgMngrConstGlobal *g_pGlobal;

private:


public:

};