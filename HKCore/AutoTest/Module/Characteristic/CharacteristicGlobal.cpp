//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicGlobal.cpp

#include "stdafx.h"
#include "CharacteristicGlobal.h"

#include "../../../Module/XDrawBase/XDrawDataDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//CCharacteristicXmlRWKeys

CCharacteristicXmlRWKeys* CCharacteristicXmlRWKeys::g_pXmlKeys = NULL;
long CCharacteristicXmlRWKeys::g_nCHARRef = 0;


CCharacteristicXmlRWKeys::CCharacteristicXmlRWKeys()
{
	m_strCCharElementTestPointsKey = L"points"; //points
	m_strCCharElementTestLinesKey = L"tests"; //tests
	m_strCCharElementTestLineKey = L"test";
	m_strCCharacterFolderKey = L"folder";
	m_strCCharInterfaceVariableKey = L"variable";
	m_strCCharMacroDrawsKey = L"macro-draws";
	m_strCCharacterAreaKey = L"character-area";
	m_strCCharMacroDrawLineKey = L"line";
	m_strCCharMacroDrawPointKey = L"point";
	m_strCCharMacroDrawKey = L"macro";
	m_strCCharElementArcdKey = L"arcd";
	m_strCCharTestLineDefineKey = L"test-line";
	m_strCCharElementLinedKey = L"lined";
	m_strCCharacteristicTmplateKey = L"characteristic-t";
	m_strCCharacteristicLibKey = L"characteristic-lib";
	m_strCCharInterfaceKey = L"char-interface";
	m_strCCharacteristicsKey = L"characteristics";
	m_strCCharacteristicKey = L"characteristic";
	m_strCCharElementKey = L"element";
	m_strCCharElementMhoKey = L"mho";
	m_strCCharElementLensKey = L"lens";
	m_strCCharElementLineKey = L"line";
	m_strCCharElementLinepKey = L"linep";
	m_strCCharElementLinerKey = L"liner";
	m_strCCharElementArcKey = L"arc";
	m_strCCharElementArcpKey = L"arcp";

	m_strCCharElementI2TKey = L"I2T"; //I2T
	m_strCCharElementIACKey = L"IAC"; //IAC
	m_strCCharElementIECKey = L"IEC"; //IEC
	m_strCCharElementIEEEKey = L"IEEE"; //IEC

	m_strCCharElementUIVPKey = L"UIVP"; //UIVP //sf 20211213 低压反时限
	m_strCCharElementIUFKey = L"IUF"; //
	m_strCCharElementInvOwnDefKey = L"IOWNDEF"; //

	m_strCCharElementDCOverLoadKey = L"DCOVERLOAD";

	m_strZKey = L"z";
	m_strPhKey = L"ph";
	m_strRadiusKey = L"radius";
	m_strStartAngleKey = L"start-angle";
	m_strEndAngleKey = L"end-angle";
	m_strClockwiseKey = L"clockwise";
	m_strTestPointsKey = L"test-points";
	m_strErrLengthKey = L"err-len";
	m_strErrorLengthTypeKey = L"err-len-type";
	m_strDirKey = L"dir";
	m_strXKey = L"x";
	m_strYKey = L"y";
	m_strAngleKey = L"angle";
	m_strForwardReachKey = L"forward-reach";
	m_strOffsetKey = L"offset";
	m_strWidthKey = L"width";
	m_strAutoCloseKey = L"auto-close";
	m_strAxisKey = L"axis";
	m_strTestLineModeKey = L"test-line-mode";
	m_strXMinKey = L"x-min";
	m_strXMaxKey = L"x-max";
	m_strYMinKey = L"y-min";
	m_strYMaxKey = L"y-max";
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
	m_strPosKey = L"pos";
	m_strRotateAngleKey = L"rotate-angle";
	m_strAngleDefKey = L"angle-def";
	m_strLengthUseKey = L"len-use";

	m_strTmaxKey = L"t-max";
	m_strXmaxKey = L"x-max";
	m_strPointsKey = L"points";
	m_strUseStartUpKey = L"use-start";
	m_strStartUpKey = L"start";
	m_strTStartUpKey = L"t-start";
	m_strUseSection1Key = L"use-Section1";
	m_strUseSection2Key = L"use-Section2";
	m_strUseSection3Key = L"use-Section3";
	m_strValSection1Key = L"Set1";
	m_strValSection2Key = L"Set2";
	m_strValSection3Key = L"Set3";
	m_strTSection1Key = L"Tset1";
	m_strTSection2Key = L"Tset2";
	m_strTSection3Key = L"Tset3";

	m_strTpKey = L"Tp";
	m_strAKey = L"A";
	m_strKKey = L"K";
	m_strVpKey = L"Vp";
	m_strPickupKey = L"Pickup";
	m_strAlphaKey = L"Alpha";

	m_strBKey = L"B";
	m_strCKey = L"C";
	m_strDKey = L"D";
	m_strEKey = L"E";
	m_strBetaKey = L"Beta";

	m_strPKey = L"P";
	m_strQKey = L"Q";
	m_strK1Key = L"K1";
	m_strK2Key = L"K2";
	m_strFromKey = L"from";   //from
	m_strToKey = L"to";     //to
	m_strStepKey = L"step";   //step

	m_strIBKey = L"Ib";
	m_strConstantKey = L"Constant";
}

CCharacteristicXmlRWKeys::~CCharacteristicXmlRWKeys()
{
}

CCharacteristicXmlRWKeys* CCharacteristicXmlRWKeys::Create()
{
	CCharacteristicConstGlobal::Create();

	g_nCHARRef++;

	if (g_nCHARRef == 1)
	{
		g_pXmlKeys = new CCharacteristicXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CCharacteristicXmlRWKeys::Release()
{
	CCharacteristicConstGlobal::Release();

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
	m_oDirDataType.AddNewValue(_T("LEFT"), _T("LEFT"), _T("0"));
	m_oDirDataType.AddNewValue(_T("RIGHT"), _T("RIGHT"), _T("1"));

	m_oClockwiseDataType.AddNewValue(_T("顺时针"), _T("CW"), _T("0"));
	m_oClockwiseDataType.AddNewValue(_T("逆时针"), _T("CCW"), _T("1"));
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

CDataType* CCharacteristicConstGlobal::DirDataType()
{
	if (g_pGlobal == NULL)
	{
		return NULL;
	}

	return &g_pGlobal->m_oDirDataType;
}

CDataType* CCharacteristicConstGlobal::ClockwiseDataType()
{
	if (g_pGlobal == NULL)
	{
		return NULL;
	}

	return &g_pGlobal->m_oClockwiseDataType;
}


//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;




void char_dev_SetModifiedFlag(CExBaseObject *pObj, BOOL bFlag)
{
	if (pObj == NULL)
	{
		return;
	}

	CExBaseObject *pLib = (CExBaseObject*)pObj->GetAncestor(CHARCLASSID_CCHARACTERISTICLIB);

	if (pLib == NULL)
	{
		pLib = (CExBaseObject*)pObj->GetRoot();
	}

	pLib->m_dwReserved = bFlag;
}


BOOL char_dev_GetModifiedFlag(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	CExBaseObject *pLib = (CExBaseObject*)pObj->GetAncestor(CHARCLASSID_CCHARACTERISTICLIB);

	if (pLib == NULL)
	{
		pLib = (CExBaseObject*)pObj->GetRoot();
	}

	return (pLib->m_dwReserved != 0);
}

#define CHAR_TESTLINE_MODE_ID_PLUMB  _T("plumb")
#define CHAR_TESTLINE_MODE_ID_VERT   _T("vert")
#define CHAR_TESTLINE_MODE_ID_HORZ   _T("horz")

#define CHAR_TESTLINE_MODE_INDEX_PLUMB  0
#define CHAR_TESTLINE_MODE_INDEX_VERT   1
#define CHAR_TESTLINE_MODE_INDEX_HORZ   2

UINT char_GetTestLineModeIndex(const CString &strID)
{
	if (strID == CHAR_TESTLINE_MODE_ID_PLUMB)
	{
		return CHAR_TESTLINE_MODE_INDEX_PLUMB;
	}

	if (strID == CHAR_TESTLINE_MODE_ID_VERT)
	{
		return CHAR_TESTLINE_MODE_INDEX_VERT;
	}

    if (strID == CHAR_TESTLINE_MODE_ID_HORZ)
	{
		return CHAR_TESTLINE_MODE_INDEX_HORZ;
	}

	return CHAR_TESTLINE_MODE_INDEX_PLUMB;
}

CString char_GetTestLineModeID(UINT nIndex)
{
	if (nIndex == CHAR_TESTLINE_MODE_INDEX_PLUMB)
	{
		return CHAR_TESTLINE_MODE_ID_PLUMB;
	}

	if (nIndex == CHAR_TESTLINE_MODE_INDEX_VERT)
	{
		return CHAR_TESTLINE_MODE_ID_VERT;
	}

	if (nIndex == CHAR_TESTLINE_MODE_INDEX_HORZ)
	{
		return CHAR_TESTLINE_MODE_ID_HORZ;
	}

	return CHAR_TESTLINE_MODE_ID_PLUMB;
}

UINT char_Cllockwise_To_UINT(const CString &strClockwise)
{
	if (strClockwise == _T("CW"))
	{
		return ARC_CLOCKWISE_CW;
	}

	return ARC_CLOCKWISE_CCW;
}

CString char_Cllockwise_To_String(UINT nClockwise)
{
	if (nClockwise == ARC_CLOCKWISE_CW)
	{
		return _T("CW");
	}

	return _T("CCW");
}

