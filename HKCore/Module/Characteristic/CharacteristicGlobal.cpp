//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicGlobal.cpp

#include "stdafx.h"
#include "CharacteristicGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CCharacteristicXmlRWKeys

CCharacteristicXmlRWKeys* CCharacteristicXmlRWKeys::g_pXmlKeys = NULL;
long CCharacteristicXmlRWKeys::g_nCHARRef = 0;


CCharacteristicXmlRWKeys::CCharacteristicXmlRWKeys()
{
	m_strCCharInterfaceVariableKey = L"variable";
	m_strCCharMacroDrawsKey = L"macro-draws";
	m_strCCharacterAreaKey = L"character-area";
	m_strCCharMacroDrawLineKey = L"line";
	m_strCCharMacroDrawPointKey = L"point";
	m_strCCharMacroDrawKey = L"macro";
	m_strCCharElementArcdKey = L"arcd";
	m_strCCharTestLineDefineKey = L"test-line";
	m_strCCharElementLinedKey = L"";
	m_strCCharacteristicTmplateKey = L"characteristic-t";
	m_strCCharacteristicLibKey = L"characteristic-lib";
	m_strCCharInterfaceKey = L"char-interface";
	m_strCCharacteristicsKey = L"characteristics";
	m_strCCharacteristicKey = L"characteristic";
	m_strCCharElementKey = L"";
	m_strCCharElementMhoKey = L"mho";
	m_strCCharElementLensKey = L"lens";
	m_strCCharElementLineKey = L"line";
	m_strCCharElementLinepKey = L"linep";
	m_strCCharElementArcKey = L"arc";
	m_strCCharElementArcpKey = L"arcp";
	m_strZKey = L"z";
	m_strPhKey = L"ph";
	m_strRadiusKey = L"radius";
	m_strStartAngleKey = L"start-angle";
	m_strEndAngleKey = L"end-angle";
	m_strDirKey = L"dir";
	m_strXKey = L"x";
	m_strYKey = L"y";
	m_strAngleKey = L"angle";
	m_strForwardReachKey = L"forward-reach";
	m_strOffsetKey = L"offset";
	m_strWidthKey = L"width";
	m_strAutoCloseKey = L"auto-close";
	m_strAxisKey = L"axis";
	m_strXMinKey = L"xmin";
	m_strXMaxKey = L"xmax";
	m_strYMinKey = L"ymin";
	m_strYMaxKey = L"ymax";
	m_strXbKey = L"x-b";
	m_strYbKey = L"y-b";
	m_strXeKey = L"x-e";
	m_strYeKey = L"y-e";
	m_strExprAngleKey = L"angle";
	m_strExprXKey = L"x";
	m_strExprYKey = L"y";
	m_strExprRKey = L"r";
	m_strXcKey = L"x-c";
	m_strYcKey = L"y-c";
	m_strAngleBKey = L"angle-b";
	m_strAngleEKey = L"angle-e";
	m_strMacroIDKey = L"macroid";
	m_strTypeKey = L"type";
	m_strColorKey = L"color";
	m_strValueKey = L"value";
}

CCharacteristicXmlRWKeys::~CCharacteristicXmlRWKeys()
{
}

CCharacteristicXmlRWKeys* CCharacteristicXmlRWKeys::Create()
{
	g_nCHARRef++;

	if (g_nCHARRef == 1)
	{
		g_pXmlKeys = new CCharacteristicXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CCharacteristicXmlRWKeys::Release()
{
	g_nCHARRef--;

	if (g_nCHARRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CCharacteristicConstGlobal

long CCharacteristicConstGlobal::g_nGlobalRef = 0;
CCharacteristicConstGlobal* CCharacteristicConstGlobal::g_pGlobal = NULL;


CCharacteristicConstGlobal::CCharacteristicConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CCharacteristicConstGlobal::~CCharacteristicConstGlobal()
{
}

CCharacteristicConstGlobal* CCharacteristicConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CCharacteristicConstGlobal();
	}

	return g_pGlobal;
}

void CCharacteristicConstGlobal::Release()
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
