//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicGlobal.h

#pragma once

#include "ExBaseList.h"

#define CHARCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define CHARCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define CHARCLASSID_CCHARELEMENTARCP       (CHARCLASSID_BASECLASS + 0X00000000)
#define CHARCLASSID_CCHARELEMENTARC       (CHARCLASSID_BASECLASS + 0X00000001)
#define CHARCLASSID_CCHARELEMENTLINEP       (CHARCLASSID_BASECLASS + 0X00000002)
#define CHARCLASSID_CCHARELEMENTLINE       (CHARCLASSID_BASECLASS + 0X00000003)
#define CHARCLASSID_CCHARELEMENTLENS       (CHARCLASSID_EXLISTCLASS + 0X00000004)
#define CHARCLASSID_CCHARELEMENTMHO       (CHARCLASSID_EXLISTCLASS + 0X00000005)
#define CHARCLASSID_CCHARELEMENT       (CHARCLASSID_EXLISTCLASS + 0X00000006)
#define CHARCLASSID_CCHARACTERISTIC       (CHARCLASSID_EXLISTCLASS + 0X00000007)
#define CHARCLASSID_CCHARACTERISTICS       (CHARCLASSID_EXLISTCLASS + 0X00000008)
#define CHARCLASSID_CCHARINTERFACE       (CHARCLASSID_EXLISTCLASS + 0X00000009)
#define CHARCLASSID_CCHARACTERISTICLIB       (CHARCLASSID_EXLISTCLASS + 0X0000000A)
#define CHARCLASSID_CCHARACTERISTICTMPLATE       (CHARCLASSID_EXLISTCLASS + 0X0000000B)
#define CHARCLASSID_CCHARELEMENTLINED       (CHARCLASSID_EXLISTCLASS + 0X0000000C)
#define CHARCLASSID_CCHARTESTLINEDEFINE       (CHARCLASSID_BASECLASS + 0X0000000D)
#define CHARCLASSID_CCHARELEMENTARCD       (CHARCLASSID_EXLISTCLASS + 0X0000000E)
#define CHARCLASSID_CCHARMACRODRAW       (CHARCLASSID_BASECLASS + 0X0000000F)
#define CHARCLASSID_CCHARMACRODRAWPOINT       (CHARCLASSID_BASECLASS + 0X00000010)
#define CHARCLASSID_CCHARMACRODRAWLINE       (CHARCLASSID_BASECLASS + 0X00000011)
#define CHARCLASSID_CCHARACTERAREA       (CHARCLASSID_EXLISTCLASS + 0X00000012)
#define CHARCLASSID_CCHARMACRODRAWS       (CHARCLASSID_EXLISTCLASS + 0X00000013)
#define CHARCLASSID_CCHARINTERFACEVARIABLE       (CHARCLASSID_BASECLASS + 0X00000014)

class CCharacteristicXmlRWKeys : public CXmlRWKeys
{
protected:
	CCharacteristicXmlRWKeys();
	virtual ~CCharacteristicXmlRWKeys();
	static long g_nCHARRef;

public:
	static CCharacteristicXmlRWKeys* g_pXmlKeys;
	static CCharacteristicXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCCharInterfaceVariableKey; //variable
	BSTR m_strCCharMacroDrawsKey; //macro-draws
	BSTR m_strCCharacterAreaKey; //character-area
	BSTR m_strCCharMacroDrawLineKey; //line
	BSTR m_strCCharMacroDrawPointKey; //point
	BSTR m_strCCharMacroDrawKey; //macro
	BSTR m_strCCharElementArcdKey; //arcd
	BSTR m_strCCharTestLineDefineKey; //test-line
	BSTR m_strCCharElementLinedKey; //lined
	BSTR m_strCCharacteristicTmplateKey; //characteristic-t
	BSTR m_strCCharacteristicLibKey; //characteristic-lib
	BSTR m_strCCharInterfaceKey; //char-interface
	BSTR m_strCCharacteristicsKey; //characteristics
	BSTR m_strCCharacteristicKey; //characteristic
	BSTR m_strCCharElementKey; //
	BSTR m_strCCharElementMhoKey; //mho
	BSTR m_strCCharElementLensKey; //lens
	BSTR m_strCCharElementLineKey; //line
	BSTR m_strCCharElementLinepKey; //linep
	BSTR m_strCCharElementArcKey; //arc
	BSTR m_strCCharElementArcpKey; //arcp
	BSTR m_strZKey; //z
	BSTR m_strPhKey; //ph
	BSTR m_strRadiusKey; //radius
	BSTR m_strStartAngleKey; //start-angle
	BSTR m_strEndAngleKey; //end-angle
	BSTR m_strDirKey; //dir
	BSTR m_strXKey; //x
	BSTR m_strYKey; //y
	BSTR m_strAngleKey; //angle
	BSTR m_strForwardReachKey; //forward-reach
	BSTR m_strOffsetKey; //offset
	BSTR m_strWidthKey; //width
	BSTR m_strAutoCloseKey; //auto-close
	BSTR m_strAxisKey; //axis
	BSTR m_strXMinKey; //xmin
	BSTR m_strXMaxKey; //xmax
	BSTR m_strYMinKey; //ymin
	BSTR m_strYMaxKey; //ymax
	BSTR m_strXbKey; //x-b
	BSTR m_strYbKey; //y-b
	BSTR m_strXeKey; //x-e
	BSTR m_strYeKey; //y-e
	BSTR m_strExprAngleKey; //angle
	BSTR m_strExprXKey; //x
	BSTR m_strExprYKey; //y
	BSTR m_strExprRKey; //r
	BSTR m_strXcKey; //x-c
	BSTR m_strYcKey; //y-c
	BSTR m_strAngleBKey; //angle-b
	BSTR m_strAngleEKey; //angle-e
	BSTR m_strMacroIDKey; //macroid
	BSTR m_strTypeKey; //type
	BSTR m_strColorKey; //color
	BSTR m_strValueKey; //value

public:
	static BSTR CCharInterfaceVariableKey()  {   return g_pXmlKeys->m_strCCharInterfaceVariableKey;  }
	static BSTR CCharMacroDrawsKey()  {   return g_pXmlKeys->m_strCCharMacroDrawsKey;  }
	static BSTR CCharacterAreaKey()  {   return g_pXmlKeys->m_strCCharacterAreaKey;  }
	static BSTR CCharMacroDrawLineKey()  {   return g_pXmlKeys->m_strCCharMacroDrawLineKey;  }
	static BSTR CCharMacroDrawPointKey()  {   return g_pXmlKeys->m_strCCharMacroDrawPointKey;  }
	static BSTR CCharMacroDrawKey()  {   return g_pXmlKeys->m_strCCharMacroDrawKey;  }
	static BSTR CCharElementArcdKey()  {   return g_pXmlKeys->m_strCCharElementArcdKey;  }
	static BSTR CCharTestLineDefineKey()  {   return g_pXmlKeys->m_strCCharTestLineDefineKey;  }
	static BSTR CCharElementLinedKey()  {   return g_pXmlKeys->m_strCCharElementLinedKey;  }
	static BSTR CCharacteristicTmplateKey()  {   return g_pXmlKeys->m_strCCharacteristicTmplateKey;  }
	static BSTR CCharacteristicLibKey()  {   return g_pXmlKeys->m_strCCharacteristicLibKey;  }
	static BSTR CCharInterfaceKey()  {   return g_pXmlKeys->m_strCCharInterfaceKey;  }
	static BSTR CCharacteristicsKey()  {   return g_pXmlKeys->m_strCCharacteristicsKey;  }
	static BSTR CCharacteristicKey()  {   return g_pXmlKeys->m_strCCharacteristicKey;  }
	static BSTR CCharElementKey()  {   return g_pXmlKeys->m_strCCharElementKey;  }
	static BSTR CCharElementMhoKey()  {   return g_pXmlKeys->m_strCCharElementMhoKey;  }
	static BSTR CCharElementLensKey()  {   return g_pXmlKeys->m_strCCharElementLensKey;  }
	static BSTR CCharElementLineKey()  {   return g_pXmlKeys->m_strCCharElementLineKey;  }
	static BSTR CCharElementLinepKey()  {   return g_pXmlKeys->m_strCCharElementLinepKey;  }
	static BSTR CCharElementArcKey()  {   return g_pXmlKeys->m_strCCharElementArcKey;  }
	static BSTR CCharElementArcpKey()  {   return g_pXmlKeys->m_strCCharElementArcpKey;  }
	static BSTR ZKey()  {   return g_pXmlKeys->m_strZKey;  }
	static BSTR PhKey()  {   return g_pXmlKeys->m_strPhKey;  }
	static BSTR RadiusKey()  {   return g_pXmlKeys->m_strRadiusKey;  }
	static BSTR StartAngleKey()  {   return g_pXmlKeys->m_strStartAngleKey;  }
	static BSTR EndAngleKey()  {   return g_pXmlKeys->m_strEndAngleKey;  }
	static BSTR DirKey()  {   return g_pXmlKeys->m_strDirKey;  }
	static BSTR XKey()  {   return g_pXmlKeys->m_strXKey;  }
	static BSTR YKey()  {   return g_pXmlKeys->m_strYKey;  }
	static BSTR AngleKey()  {   return g_pXmlKeys->m_strAngleKey;  }
	static BSTR ForwardReachKey()  {   return g_pXmlKeys->m_strForwardReachKey;  }
	static BSTR OffsetKey()  {   return g_pXmlKeys->m_strOffsetKey;  }
	static BSTR WidthKey()  {   return g_pXmlKeys->m_strWidthKey;  }
	static BSTR AutoCloseKey()  {   return g_pXmlKeys->m_strAutoCloseKey;  }
	static BSTR AxisKey()  {   return g_pXmlKeys->m_strAxisKey;  }
	static BSTR XMinKey()  {   return g_pXmlKeys->m_strXMinKey;  }
	static BSTR XMaxKey()  {   return g_pXmlKeys->m_strXMaxKey;  }
	static BSTR YMinKey()  {   return g_pXmlKeys->m_strYMinKey;  }
	static BSTR YMaxKey()  {   return g_pXmlKeys->m_strYMaxKey;  }
	static BSTR XbKey()  {   return g_pXmlKeys->m_strXbKey;  }
	static BSTR YbKey()  {   return g_pXmlKeys->m_strYbKey;  }
	static BSTR XeKey()  {   return g_pXmlKeys->m_strXeKey;  }
	static BSTR YeKey()  {   return g_pXmlKeys->m_strYeKey;  }
	static BSTR ExprAngleKey()  {   return g_pXmlKeys->m_strExprAngleKey;  }
	static BSTR ExprXKey()  {   return g_pXmlKeys->m_strExprXKey;  }
	static BSTR ExprYKey()  {   return g_pXmlKeys->m_strExprYKey;  }
	static BSTR ExprRKey()  {   return g_pXmlKeys->m_strExprRKey;  }
	static BSTR XcKey()  {   return g_pXmlKeys->m_strXcKey;  }
	static BSTR YcKey()  {   return g_pXmlKeys->m_strYcKey;  }
	static BSTR AngleBKey()  {   return g_pXmlKeys->m_strAngleBKey;  }
	static BSTR AngleEKey()  {   return g_pXmlKeys->m_strAngleEKey;  }
	static BSTR MacroIDKey()  {   return g_pXmlKeys->m_strMacroIDKey;  }
	static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
	static BSTR ColorKey()  {   return g_pXmlKeys->m_strColorKey;  }
	static BSTR ValueKey()  {   return g_pXmlKeys->m_strValueKey;  }
};



class CCharacteristicConstGlobal
{
private:
	CCharacteristicConstGlobal();
	virtual ~CCharacteristicConstGlobal();

public:
	static CCharacteristicConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CCharacteristicConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
