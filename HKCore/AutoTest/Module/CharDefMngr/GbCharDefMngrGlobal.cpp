//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharDefMngrGlobal.cpp

#include "stdafx.h"
#include "GbCharDefMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CGbCharDefMngrXmlRWKeys

CGbCharDefMngrXmlRWKeys* CGbCharDefMngrXmlRWKeys::g_pXmlKeys = NULL;
long CGbCharDefMngrXmlRWKeys::g_nCHRRef = 0;


CGbCharDefMngrXmlRWKeys::CGbCharDefMngrXmlRWKeys()
{
	m_strCGbCharDefKey = L"char-def";
	m_strCGbCharCurveKey = L"curve";
	m_strCGbCharFuncKey = L"func";
	m_strCGbChar_y_f_xKey = L"y_f_x";
	m_strCGbCharLenTomatoKey = L"lens-tomato";
	m_strCGbCharMhoKey = L"mho";
	m_strCGbCharsDefKey = L"chars-def";
	m_strCGbCharAxisesKey = L"axises";
	m_strCGbCharAxisKey = L"axis";
	m_strCGbCharLineDrawKey = L"line-draw";
	m_strCGbCharPointDrawKey = L"point-draw";
	m_strCGbCharPArcKey = L"parc";
	m_strCGbCharPLinerKey = L"pliner";
	m_strCGbCharPLinesKey = L"plines";
	m_strCGbCharPLineKey = L"pline";
	m_strCGbCharArcKey = L"arc";
	m_strCGbCharLinesKey = L"lines";
	m_strCGbCharLinerKey = L"liner";
	m_strCGbCharLineKey = L"line";
	m_strXbKey = L"x-b";
	m_strYbKey = L"y-b";
	m_strAngleKey = L"angle";
	m_strDirKey = L"dir";
	m_strXeKey = L"x-e";
	m_strYeKey = L"y-e";
	m_strXcKey = L"x-c";
	m_strYcKey = L"y-c";
	m_strRKey = L"r";
	m_strAngleBKey = L"angle-b";
	m_strAngleEKey = L"angle-e";
	m_strXidKey = L"x-id";
	m_strYidKey = L"y-id";
	m_strXbidKey = L"x-b-id";
	m_strYbidKey = L"y-b-id";
	m_strXeidKey = L"x-e-id";
	m_strYeidKey = L"y-e-id";
	m_strAxisKey = L"axis";
	m_strXNameKey = L"x-name";
	m_strYNameKey = L"y-name";
	m_strXMinKey = L"x-min";
	m_strYMinKey = L"y-min";
	m_strXMaxKey = L"x-max";
	m_strYMaxKey = L"y-max";
	m_strReachKey = L"reach";
	m_strOffsetKey = L"offset";
	m_strWidthKey = L"width";
	m_strABKey = L"AB";
	m_strMinKey = L"min";
	m_strMaxKey = L"max";
	m_strExpressionKey = L"Expression";
}

CGbCharDefMngrXmlRWKeys::~CGbCharDefMngrXmlRWKeys()
{
}

CGbCharDefMngrXmlRWKeys* CGbCharDefMngrXmlRWKeys::Create()
{
	g_nCHRRef++;

	if (g_nCHRRef == 1)
	{
		g_pXmlKeys = new CGbCharDefMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CGbCharDefMngrXmlRWKeys::Release()
{
	g_nCHRRef--;

	if (g_nCHRRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CGbCharDefMngrConstGlobal

long CGbCharDefMngrConstGlobal::g_nGlobalRef = 0;
CGbCharDefMngrConstGlobal* CGbCharDefMngrConstGlobal::g_pGlobal = NULL;


CGbCharDefMngrConstGlobal::CGbCharDefMngrConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CGbCharDefMngrConstGlobal::~CGbCharDefMngrConstGlobal()
{
}

CGbCharDefMngrConstGlobal* CGbCharDefMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CGbCharDefMngrConstGlobal();
	}

	return g_pGlobal;
}

void CGbCharDefMngrConstGlobal::Release()
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
