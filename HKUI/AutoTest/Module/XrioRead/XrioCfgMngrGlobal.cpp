//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XrioCfgMngrGlobal.cpp

#include "stdafx.h"
#include "XrioCfgMngrGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CXrioCfgMngrXmlRWKeys

CXrioCfgMngrXmlRWKeys* CXrioCfgMngrXmlRWKeys::g_pXmlKeys = NULL;
long CXrioCfgMngrXmlRWKeys::g_nXrioRef = 0;


CXrioCfgMngrXmlRWKeys::CXrioCfgMngrXmlRWKeys()
{
	m_strCustomKey = L"CUSTOM";
	m_strXRioKey = L"XRio";
    m_strCustomBlockKey = L"Block";
	m_strCustomParameterKey = L"Parameter";
	m_strNameKey = L"Name";
	m_strDescriptionKey = L"Description";
	m_strForeignIdKey = L"ForeignId";
	m_strDataTypeKey = L"DataType";
	m_strEnumListKey = L"EnumList";
	m_strEnumValueKey = L"EnumValue";
	m_strEnabledFormulaKey = L"EnabledFormula";
	m_strEnabledRefListKey = L"EnabledRefList";
	m_strValueFormulaKey = L"ValueFormula";
	m_strValueRefListKey = L"ValueRefList";
	m_strRefParamKey = L"RefParam";
	m_strRefEnumKey = L"RefEnum";
	m_strValueKey = L"Value";
	m_strMinValueKey = L"MinValue";
	m_strMaxValueKey = L"MaxValue";
	m_strUnitKey = L"Unit";

	m_strIdKey = L"Id";
	m_strRefIdKey = L"RefId";
	m_strEnumIdKey = L"EnumId";
	m_strEnabledKey = L"Enabled";
    m_strUnitDecimalPlacesKey = L"DecimalPlaces";

    m_strRioKey = L"RIO";
    m_strTypeKey = L"Type";
    m_strBlockTypeKey = L"BlockType";
  //  m_strRioGroupKey = L"Device";//ceshi

    m_strRioDeviceKey = L"DEVICE";
    m_strNameplateKey = L"NAMEPLATE";
    m_strLocationKey = L"LOCATION";
    m_strNominalValuesKey = L"NOMINALVALUES";
    m_strResidualFactorsKey = L"RESIDUALFACTORS";
    m_strLimitsKey = L"LIMITS";
    m_strMiscKey = L"MISC";

    m_strDeviceModelKey = L"DEVICE_MODEL";
    m_strManufacturerKey = L"MANUFACTURER";
    m_strDeviceTypeKey = L"DEVICE_TYPE";
    m_strSerialnrKey = L"SERIALNR";
    m_strAdditionalINF02Key = L"ADDITIONAL_INFO2";

    m_strDeviceAddressKey = L"DEVICE_ADDRESS";
    m_strSubstationKey = L"SUBSTATION";
    m_strSubstatioAddressKey = L"SUBSTATION_ADDRESS";
    m_strBayKey = L"BAY";
    m_strBayAddressKey = L"BAY_ADDRESS";
    m_strProtectedObjectNameKey = L"PROTECTED_OBJECT_NAME";

    m_strPhasesKey = L"PHASES";
    m_strFNomKey = L"FNOM";
    m_strVNomKey = L"VNOM";
    m_strVPrimLLKey = L"VPRIM_LL";
    m_strINomKey = L"INOM";
    m_strIPrimKey = L"IPRIM";

    m_strVLNVNKey = L"VLNVN";
    m_strININOMKey = L"ININOM";

    m_strVMaxLLKey = L"VMAX_LL";
    m_strIMaxKey = L"IMAX";

    m_strDeBounceTimeKey = L"DEBOUNCETIME";
    m_strDeGlitchTimeKey = L"DEGLITCHTIME";
    m_strOverloadSupTimeKey = L"OVERLOADSUPTIME";



  //  m_strRioTypeKey = L"Type";
  //  m_strRioBlockTypeKey = L"BlockType";

    m_strRioCBKey = L"CBCONFIGURATION";
    m_strTripTimeKey = L"TRIPTIME";
    m_strCloseTimeKey = L"CLOSETIME";
    m_strP52ABKey = L"P52AB";

    m_strDistanceKey = L"DISTANCE";
//    m_strProtectedObjectKey = L"PROTECTEDOBJECT";
    m_strProtectionDeviceKey = L"PROTECTIONDEVICE";
    m_strZonesKey = L"ZONES";
    m_strZoneKey = L"ZONE";
    m_strGenricShapeKey = L"GENERICSHAPE";
    m_strMhoShapeKey = L"MHOSHAPE";
    m_strReachKey = L"REACH";
    m_strOffsetKey = L"OFFSET";
    m_strInsideKey = L"INSIDE";
    m_strLineKey = L"LINE";
    m_strArcKey = L"ARC";
    m_strRefPointRKey = L"REFPOINT_R";
    m_strRefPointXKey = L"REFPOINT_X";
    m_strAngleKey = L"ANGLE";
    m_strAutoCloseKey = L"AUTOCLOSE";
    m_strRefPointMagKey = L"REFPOINT_MAG";
    m_strRefPointAngleKey = L"REFPOINT_ANGLE";
    m_strRadiusKey = L"RADIUS";
    m_strStartAngleKey = L"STARTANGLE";
    m_strEndAngleKey = L"ENDANGLE";
    m_strDirKey = L"DIR";

    m_strDifferentialKey = L"DIFFERENTIAL";
    m_strDiffBiasKey = L"DIFFBIAS";
    m_strTripCharKey = L"TRIPCHAR";
    m_strPointKey = L"POINT";
    m_strPointXKey = L"X";
    m_strPointYKey = L"Y";

    m_strOverCurrentKey = L"OVERCURRENT";
    m_strOverCurrentGroupKey = L"GROUP";
    m_strOverCurrentUnitKey = L"UNIT";
    m_strOverCurrentTableKey = L"TABLE";
    m_strOverCurrentCharKey = L"CHAR";
    m_strOverCurrentCharI2TKey = L"CHARI2T";
    m_strOverCurrentCharAKey = L"A";
    m_strOverCurrentCharBKey = L"B";
    m_strOverCurrentCharPKey = L"P";
    m_strOverCurrentCharQKey = L"Q";
    m_strOverCurrentCharK1Key = L"K1";
    m_strOverCurrentCharK2Key = L"K2";
    m_strOverCurrentElementsKey = L"OVERCURRENTELEMENTS";
    m_strTimedOverCurrentElementKey = L"TIMEDOVERCURRENTELEMENT";
    m_strOperatingCurvesKey = L"OPERATINGCURVES";
    m_strInverseParameterCurveKey = L"INVERSEPARAMETERCURVE";
    m_strI2TParameterCurveKey = L"I2TPARAMETERCURVE";
    m_strIACParameterCurveKey = L"IACPARAMETERCURVE";
    m_strCustomCurveKey = L"CUSTOMCURVE";
    m_strCurvePointsKey = L"CURVEPOINTS";
    m_strCurvePointKey = L"CURVEPOINT";
    m_strTimeMultiplierKey = L"TIMEMULTIPLIER";
    m_strNomvalKey = L"NOMVAL";
    m_strParameterAKey = L"PARAMETERA";
    m_strParameterBKey = L"PARAMETERB";
    m_strParameterCKey = L"PARAMETERC";
    m_strParameterDKey = L"PARAMETERD";
    m_strParameterEKey = L"PARAMETERE";
    m_strParameterFKey = L"PARAMETERF";
    m_strActiveKey = L"ACTIVE";
    m_strStandardCurveKey = L"STANDARDCURVE";
    m_strStandardCurveNameKey = L"NAME";
    m_strInverseParameterCurveNameKey = L"NAME";

    m_strRioConverterKey = L"RioConverter";
    m_strScriptKey = L"Script";

    m_strIndexKey = L"INDEX";
    m_strFaultLoopKey = L"FAULTLOOP";
    m_strTolerancesKey = L"TOLERANCES";
    m_strTTPLValidKey = L"TTPL_VALID";
    m_strTTOLPlusKey = L"TTOLPLUS";
    m_strTTMIValidKey = L"TTMI_VALID";
    m_strTTOLMinusKey = L"TTOLMINUS";
    m_strTTRLValidKey = L"TTRL_VALID";
    m_strTTOLRelKey = L"TTOLREL";
    m_strZTRLValidKey = L"ZTRL_VALID";
    m_strZTOLRelKey = L"ZTOLREL";
    m_strZTABValidKey = L"ZTAB_VALID";
    m_strZTOLAbsKey = L"ZTOLABS";

    m_strTIndexKey = L"TINDEX";
//    m_strPtConnKey = L"PTCONN";
//    m_strCtStarPointKey = L"CTSTARPOINT";
//    m_strLineAngleKey = L"LINEANGLE";
//    m_strLineLengthKey = L"LINELENGTH";
//    m_strGrfModeKey = L"GRF_MODE";
//    m_strKLMagKey = L"KL_MAG";
//    m_strKLAngleKey = L"KL_ANGLE";
}

CXrioCfgMngrXmlRWKeys::~CXrioCfgMngrXmlRWKeys()
{
}

CXrioCfgMngrXmlRWKeys* CXrioCfgMngrXmlRWKeys::Create()
{
	g_nXrioRef++;

	if (g_nXrioRef == 1)
	{
		g_pXmlKeys = new CXrioCfgMngrXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CXrioCfgMngrXmlRWKeys::Release()
{
	g_nXrioRef--;

	if (g_nXrioRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
//CXrioCfgMngrConstGlobal

long CXrioCfgMngrConstGlobal::g_nGlobalRef = 0;
CXrioCfgMngrConstGlobal* CXrioCfgMngrConstGlobal::g_pGlobal = NULL;

CXrioCfgMngrConstGlobal::CXrioCfgMngrConstGlobal()
{

}

CXrioCfgMngrConstGlobal::~CXrioCfgMngrConstGlobal()
{
}

CXrioCfgMngrConstGlobal* CXrioCfgMngrConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CXrioCfgMngrConstGlobal();
	}

	return g_pGlobal;
}

void CXrioCfgMngrConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

