//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XrioCfgMngrGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"

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

#define XRIOCLASSID_DEVICE			    (XRIOCLASSID_BASECLASS + 0X0000000E)

#define XRIOCLASSID_NAMEPLATE			(XRIOCLASSID_BASECLASS + 0X0000000F)
#define XRIOCLASSID_LOCATION			(XRIOCLASSID_BASECLASS + 0X00000010)
#define XRIOCLASSID_NOMINALVALUES	    (XRIOCLASSID_BASECLASS + 0X00000011)
#define XRIOCLASSID_RESIDUALFACTORS	    (XRIOCLASSID_BASECLASS + 0X00000012)
#define XRIOCLASSID_LIMITS	            (XRIOCLASSID_BASECLASS + 0X00000013)
#define XRIOCLASSID_MISC	            (XRIOCLASSID_BASECLASS + 0X00000014)

#define XRIOCLASSID_DEVICE_MODEL	    (XRIOCLASSID_BASECLASS + 0X00000015)
#define XRIOCLASSID_MANUFACTURER	    (XRIOCLASSID_BASECLASS + 0X00000016)
#define XRIOCLASSID_DEVICE_TYPE	        (XRIOCLASSID_BASECLASS + 0X00000017)
#define XRIOCLASSID_SERIALNR	        (XRIOCLASSID_BASECLASS + 0X00000018)
#define XRIOCLASSID_ADDITIONAL_INFO2	(XRIOCLASSID_BASECLASS + 0X00000019)

#define XRIOCLASSID_DEVICE_ADDRESS	    (XRIOCLASSID_BASECLASS + 0X0000001A)
#define XRIOCLASSID_SUBSTATION	        (XRIOCLASSID_BASECLASS + 0X0000001B)
#define XRIOCLASSID_SUBSTATION_ADDRESS	(XRIOCLASSID_BASECLASS + 0X0000001C)
#define XRIOCLASSID_BAY	                (XRIOCLASSID_BASECLASS + 0X0000001D)
#define XRIOCLASSID_BAY_ADDRESS	        (XRIOCLASSID_BASECLASS + 0X0000001E)
#define XRIOCLASSID_PROTECTED_OBJECT_NAME (XRIOCLASSID_BASECLASS + 0X0000001F)

#define XRIOCLASSID_PHASES              (XRIOCLASSID_BASECLASS + 0X00000020)
#define XRIOCLASSID_FNOM                (XRIOCLASSID_BASECLASS + 0X00000021)
#define XRIOCLASSID_VNOM                (XRIOCLASSID_BASECLASS + 0X00000022)
#define XRIOCLASSID_VPRIM_LL            (XRIOCLASSID_BASECLASS + 0X00000023)
#define XRIOCLASSID_INOM                (XRIOCLASSID_BASECLASS + 0X00000024)
#define XRIOCLASSID_IPRIM               (XRIOCLASSID_BASECLASS + 0X00000025)

#define XRIOCLASSID_VLNVN               (XRIOCLASSID_BASECLASS + 0X00000026)
#define XRIOCLASSID_ININOM              (XRIOCLASSID_BASECLASS + 0X00000027)

#define XRIOCLASSID_VMAX_LL              (XRIOCLASSID_BASECLASS + 0X00000028)
#define XRIOCLASSID_IMAX                 (XRIOCLASSID_BASECLASS + 0X00000029)

#define XRIOCLASSID_DEBOUNCETIME                 (XRIOCLASSID_BASECLASS + 0X0000002A)
#define XRIOCLASSID_DEGLITCHTIME                 (XRIOCLASSID_BASECLASS + 0X0000002B)
#define XRIOCLASSID_OVERLOADSUPTIME              (XRIOCLASSID_BASECLASS + 0X0000002C)


#define XRIOCLASSID_RIO_DATA			(XRIOCLASSID_EXLISTCLASS + 0X0000002D)
#define XRIOCLASSID_RIO_GROUP			(XRIOCLASSID_EXLISTCLASS + 0X0000002E)
#define XRIOCLASSID_RIO_TEXTFILE		(XRIOCLASSID_EXLISTCLASS + 0X0000002F)

#define XRIOCLASSID_CBCONFIGURATION		(XRIOCLASSID_EXLISTCLASS + 0X00000030)
#define XRIOCLASSID_TRIPTIME		    (XRIOCLASSID_EXLISTCLASS + 0X00000031)
#define XRIOCLASSID_CLOSETIME		    (XRIOCLASSID_EXLISTCLASS + 0X00000032)
#define XRIOCLASSID_P52AB		        (XRIOCLASSID_EXLISTCLASS + 0X00000033)

#define XRIOCLASSID_DISTANCE		             (XRIOCLASSID_EXLISTCLASS + 0X00000034)
//#define XRIOCLASSID_PROTECTEDOBJECT		         (XRIOCLASSID_EXLISTCLASS + 0X00000035)
#define XRIOCLASSID_PROTECTIONDEVICE		     (XRIOCLASSID_EXLISTCLASS + 0X00000036)
#define XRIOCLASSID_ZONES                        (XRIOCLASSID_EXLISTCLASS + 0X00000037)
#define XRIOCLASSID_ZONE                         (XRIOCLASSID_EXLISTCLASS + 0X00000038)
#define XRIOCLASSID_GENERICSHAPE                 (XRIOCLASSID_EXLISTCLASS + 0X00000039)
#define XRIOCLASSID_LINE                         (XRIOCLASSID_EXLISTCLASS + 0X0000003A)
#define XRIOCLASSID_ARC                          (XRIOCLASSID_EXLISTCLASS + 0X0000003B)
#define XRIOCLASSID_REFPOINT_R                   (XRIOCLASSID_EXLISTCLASS + 0X0000003C)
#define XRIOCLASSID_REFPOINT_X                   (XRIOCLASSID_EXLISTCLASS + 0X0000003D)
#define XRIOCLASSID_ANGLE                        (XRIOCLASSID_EXLISTCLASS + 0X0000003E)
#define XRIOCLASSID_REFPOINT_MAG                 (XRIOCLASSID_EXLISTCLASS + 0X0000003F)
#define XRIOCLASSID_REFPOINT_ANGLE               (XRIOCLASSID_EXLISTCLASS + 0X00000040)
#define XRIOCLASSID_REFPOINT_RADIUS              (XRIOCLASSID_EXLISTCLASS + 0X00000041)
#define XRIOCLASSID_REFPOINT_STARTANGLE          (XRIOCLASSID_EXLISTCLASS + 0X00000042)
#define XRIOCLASSID_REFPOINT_ENDANGLE            (XRIOCLASSID_EXLISTCLASS + 0X00000043)
#define XRIOCLASSID_REFPOINT_DIR                 (XRIOCLASSID_EXLISTCLASS + 0X00000044)

#define XRIOCLASSID_DIFFERENTIAL                 (XRIOCLASSID_EXLISTCLASS + 0X00000045)
#define XRIOCLASSID_DIFFBIAS                     (XRIOCLASSID_EXLISTCLASS + 0X00000046)
#define XRIOCLASSID_TRIPCHAR                     (XRIOCLASSID_EXLISTCLASS + 0X00000047)
#define XRIOCLASSID_POINT                        (XRIOCLASSID_EXLISTCLASS + 0X00000048)
#define XRIOCLASSID_POINT_X                      (XRIOCLASSID_EXLISTCLASS + 0X00000049)
#define XRIOCLASSID_POINT_Y                      (XRIOCLASSID_EXLISTCLASS + 0X0000004A)

#define XRIOCLASSID_OVERCURRENT                  (XRIOCLASSID_EXLISTCLASS + 0X0000004B)
#define XRIOCLASSID_OVERCURRENTELEMENTS          (XRIOCLASSID_EXLISTCLASS + 0X0000004C)
#define XRIOCLASSID_TIMEDOVERCURRENTELEMENT      (XRIOCLASSID_EXLISTCLASS + 0X0000004D)
#define XRIOCLASSID_OPERATINGCURVES              (XRIOCLASSID_EXLISTCLASS + 0X0000004E)
#define XRIOCLASSID_INVERSEPARAMETERCURVE        (XRIOCLASSID_EXLISTCLASS + 0X0000004F)
#define XRIOCLASSID_PARAMETERA                   (XRIOCLASSID_EXLISTCLASS + 0X00000050)
#define XRIOCLASSID_PARAMETERB                   (XRIOCLASSID_EXLISTCLASS + 0X00000051)
#define XRIOCLASSID_PARAMETERC                   (XRIOCLASSID_EXLISTCLASS + 0X00000052)
#define XRIOCLASSID_PARAMETERD                   (XRIOCLASSID_EXLISTCLASS + 0X00000053)
#define XRIOCLASSID_ACTIVE                       (XRIOCLASSID_EXLISTCLASS + 0X00000054)
#define XRIOCLASSID_STANDARDCURVE                (XRIOCLASSID_EXLISTCLASS + 0X00000055)
#define XRIOCLASSID_STANDARDCURVE_NAME           (XRIOCLASSID_EXLISTCLASS + 0X00000056)
#define XRIOCLASSID_TIMEDOVERCURRENTELEMENT_NAME (XRIOCLASSID_EXLISTCLASS + 0X00000057)

#define XRIOCLASSID_RioConverter                 (XRIOCLASSID_EXLISTCLASS + 0X00000058)
#define XRIOCLASSID_Script                       (XRIOCLASSID_EXLISTCLASS + 0X00000059)

#define XRIOCLASSID_MHOSHAPE                 (XRIOCLASSID_EXLISTCLASS + 0X0000005A)
#define XRIOCLASSID_REACH                    (XRIOCLASSID_EXLISTCLASS + 0X0000005B)
#define XRIOCLASSID_OFFSET                   (XRIOCLASSID_EXLISTCLASS + 0X0000005C)
#define XRIOCLASSID_INSIDE                   (XRIOCLASSID_EXLISTCLASS + 0X0000005D)
#define XRIOCLASSID_AUTOCLOSE                   (XRIOCLASSID_EXLISTCLASS + 0X0000005E)

#define XRIOCLASSID_I2TPARAMETERCURVE                   (XRIOCLASSID_EXLISTCLASS + 0X0000005F)
#define XRIOCLASSID_TIMEMULTIPLIER                   (XRIOCLASSID_EXLISTCLASS + 0X00000060)
#define XRIOCLASSID_TIMEMULTIPLIER_NOMVAL                   (XRIOCLASSID_EXLISTCLASS + 0X00000061)

#define XRIOCLASSID_OVERCURRENT_GROUP                   (XRIOCLASSID_EXLISTCLASS + 0X00000062)
#define XRIOCLASSID_OVERCURRENT_UNIT                   (XRIOCLASSID_EXLISTCLASS + 0X00000063)
#define XRIOCLASSID_OVERCURRENT_TABLE                   (XRIOCLASSID_EXLISTCLASS + 0X00000064)
#define XRIOCLASSID_OVERCURRENT_CHAR                   (XRIOCLASSID_EXLISTCLASS + 0X00000065)
#define XRIOCLASSID_OVERCURRENT_CHAR_A                   (XRIOCLASSID_EXLISTCLASS + 0X00000066)
#define XRIOCLASSID_OVERCURRENT_CHAR_B                   (XRIOCLASSID_EXLISTCLASS + 0X00000067)
#define XRIOCLASSID_OVERCURRENT_CHAR_P                   (XRIOCLASSID_EXLISTCLASS + 0X00000068)
#define XRIOCLASSID_OVERCURRENT_CHAR_Q                   (XRIOCLASSID_EXLISTCLASS + 0X00000069)
#define XRIOCLASSID_OVERCURRENT_CHAR_K1                   (XRIOCLASSID_EXLISTCLASS + 0X0000006A)
#define XRIOCLASSID_OVERCURRENT_CHAR_K2                   (XRIOCLASSID_EXLISTCLASS + 0X0000006B)
#define XRIOCLASSID_OVERCURRENT_CHARI2T                   (XRIOCLASSID_EXLISTCLASS + 0X0000006C)

#define XRIOCLASSID_CUSTOMCURVE                           (XRIOCLASSID_EXLISTCLASS + 0X0000006D)
#define XRIOCLASSID_CURVEPOINTS                           (XRIOCLASSID_EXLISTCLASS + 0X0000006E)
#define XRIOCLASSID_CURVEPOINT                           (XRIOCLASSID_EXLISTCLASS + 0X0000006F)
#define XRIOCLASSID_IACPARAMETERCURVE                           (XRIOCLASSID_EXLISTCLASS + 0X00000070)
#define XRIOCLASSID_PARAMETERE                  (XRIOCLASSID_EXLISTCLASS + 0X00000072)

#define XRIOCLASSID_INDEX                                    (XRIOCLASSID_EXLISTCLASS + 0X00000073)
#define XRIOCLASSID_FAULTLOOP                                (XRIOCLASSID_EXLISTCLASS + 0X00000074)
#define XRIOCLASSID_TOLERANCES                                (XRIOCLASSID_EXLISTCLASS + 0X00000075)
#define XRIOCLASSID_TTPL_VALID                                (XRIOCLASSID_EXLISTCLASS + 0X00000076)
#define XRIOCLASSID_TTOLPLUS                                  (XRIOCLASSID_EXLISTCLASS + 0X00000077)
#define XRIOCLASSID_TTMI_VALID                                (XRIOCLASSID_EXLISTCLASS + 0X00000078)
#define XRIOCLASSID_TTOLMINUS                                 (XRIOCLASSID_EXLISTCLASS + 0X00000079)
#define XRIOCLASSID_TTRL_VALID                                 (XRIOCLASSID_EXLISTCLASS + 0X0000007A)
#define XRIOCLASSID_TTOLREL                                    (XRIOCLASSID_EXLISTCLASS + 0X0000007B)
#define XRIOCLASSID_ZTRL_VALID                                    (XRIOCLASSID_EXLISTCLASS + 0X0000007C)
#define XRIOCLASSID_ZTOLREL                                    (XRIOCLASSID_EXLISTCLASS + 0X0000007D)
#define XRIOCLASSID_ZTAB_VALID                                    (XRIOCLASSID_EXLISTCLASS + 0X0000007E)
#define XRIOCLASSID_ZTOLABS                                   (XRIOCLASSID_EXLISTCLASS + 0X0000007F)
#define XRIOCLASSID_PARAMETERF                                (XRIOCLASSID_EXLISTCLASS + 0X00000080)
#define XRIOCLASSID_TINDEX                                (XRIOCLASSID_EXLISTCLASS + 0X00000081)




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

    BSTR m_strRioKey;	//Rio
    BSTR m_strTypeKey;	//Type
    BSTR m_strBlockTypeKey;	//BlockTypeKey
    //   BSTR m_strRioGroupKey;	//Group?????device

    BSTR m_strRioDeviceKey;	//Device
    BSTR m_strNameplateKey;	//Nameplate
    BSTR m_strLocationKey;	//Location
    BSTR m_strNominalValuesKey;	//NominalValues
    BSTR m_strResidualFactorsKey;	//ResidualFactors
    BSTR m_strLimitsKey;	//Limits
    BSTR m_strMiscKey;	//Misc

    BSTR m_strDeviceModelKey;	//DeviceModel
    BSTR m_strManufacturerKey;	//Manufacturer
    BSTR m_strDeviceTypeKey;	//DeviceType
    BSTR m_strSerialnrKey;	//Serialnr
    BSTR m_strAdditionalINF02Key;	//AdditionalINF02

    BSTR m_strDeviceAddressKey;	//DeviceAddress
    BSTR m_strSubstationKey;	//Substation
    BSTR m_strSubstatioAddressKey;	//SubstatioAddress
    BSTR m_strBayKey;	//Bay
    BSTR m_strBayAddressKey;	//BayAddress
    BSTR m_strProtectedObjectNameKey;	//ProjectedObjectName

    BSTR m_strPhasesKey;	//Phases
    BSTR m_strFNomKey;	//FNom
    BSTR m_strVNomKey;	//VNom
    BSTR m_strVPrimLLKey;	//VPrimLL
    BSTR m_strINomKey;	//INom
    BSTR m_strIPrimKey;	//IPrim

    BSTR m_strVLNVNKey;	//VLNVN
    BSTR m_strININOMKey;	//ININOM

    BSTR m_strVMaxLLKey;	//VMaxLL
    BSTR m_strIMaxKey;	//IMax

    BSTR m_strDeBounceTimeKey;	//DeBounceTime
    BSTR m_strDeGlitchTimeKey;	//DeGlitchTime
    BSTR m_strOverloadSupTimeKey;	//OverloadSupTime



    BSTR m_strRioCBKey;	//CBCONFIGURATION
    BSTR m_strTripTimeKey;	//TripTime
    BSTR m_strCloseTimeKey;	//CloseTime
    BSTR m_strP52ABKey;	//P52AB

    BSTR m_strDistanceKey;	//Distance
    //    BSTR m_strProtectedObjectKey;	//ProtectedObject
    BSTR m_strProtectionDeviceKey;	//ProtectionDevice
    BSTR m_strZonesKey;	//Zones
    BSTR m_strZoneKey;	//Zone
    BSTR m_strGenricShapeKey;	//GenricShape
    BSTR m_strMhoShapeKey;	//MhoShape
    BSTR m_strReachKey;	//Reach
    BSTR m_strOffsetKey;	//offset
    BSTR m_strInsideKey;	//Inside
    BSTR m_strLineKey;	//Line
    BSTR m_strArcKey;	//Arc
    BSTR m_strRefPointRKey;	//RefPointR
    BSTR m_strRefPointXKey;	//RefPointX
    BSTR m_strAngleKey;	//Angle
    BSTR m_strAutoCloseKey;	//AutoClose
    BSTR m_strRefPointMagKey;	//RefPointMag
    BSTR m_strRefPointAngleKey;	//RefPointAngle
    BSTR m_strRadiusKey;	//Radius
    BSTR m_strStartAngleKey;	//StartAngle
    BSTR m_strEndAngleKey;	//EndAngle
    BSTR m_strDirKey;	//Dir

    BSTR m_strDifferentialKey;	//Differential
    BSTR m_strDiffBiasKey;	//DiffBias
    BSTR m_strTripCharKey;	//TripChar
    BSTR m_strPointKey;	//Point
    BSTR m_strPointXKey;	//PointX
    BSTR m_strPointYKey;	//PointY

    BSTR m_strOverCurrentKey;	//OverCurrent
    BSTR m_strOverCurrentGroupKey;	//OverCurrentGroup
    BSTR m_strOverCurrentUnitKey;	//OverCurrentUnit
    BSTR m_strOverCurrentTableKey;	//OverCurrentTAable
    BSTR m_strOverCurrentCharKey;	//OverCurrentChar
    BSTR m_strOverCurrentCharI2TKey;	//OverCurrentCharI2T
    BSTR m_strOverCurrentCharAKey;	//OverCurrentCharA
    BSTR m_strOverCurrentCharBKey;	//OverCurrentCharB
    BSTR m_strOverCurrentCharPKey;	//OverCurrentCharP
    BSTR m_strOverCurrentCharQKey;	//OverCurrentCharQ
    BSTR m_strOverCurrentCharK1Key;	//OverCurrentCharK1
    BSTR m_strOverCurrentCharK2Key;	//OverCurrentCharK2
    BSTR m_strOverCurrentElementsKey;	//OverCurrentElements
    BSTR m_strTimedOverCurrentElementKey;	//TimedOverCurrentElement
    BSTR m_strOperatingCurvesKey;	//OperatingCurves
    BSTR m_strInverseParameterCurveKey;	//InverseParameterCurve
    BSTR m_strI2TParameterCurveKey;	//I2TParameterCurve
    BSTR m_strIACParameterCurveKey;	//IACParameterCurve
    BSTR m_strCustomCurveKey;	//CustomCurve
    BSTR m_strCurvePointsKey;	//CurvePoints
    BSTR m_strCurvePointKey;	//CurvePoint
    BSTR m_strTimeMultiplierKey;	//TimeMultiplier
    BSTR m_strNomvalKey;	//Nomval
    BSTR m_strParameterAKey;	//ParameterA
    BSTR m_strParameterBKey;	//ParameterB
    BSTR m_strParameterCKey;	//ParameterC
    BSTR m_strParameterDKey;	//ParameterD
    BSTR m_strParameterEKey;	//ParameterE
    BSTR m_strParameterFKey;	//ParameterF
    BSTR m_strActiveKey;	//Active
    BSTR m_strStandardCurveKey;	//StandardCurve
    BSTR m_strStandardCurveNameKey;	//StandardCurveName
    BSTR m_strInverseParameterCurveNameKey;	//InverseParameterCurveName

    BSTR m_strRioConverterKey;	//RioConverter
    BSTR m_strScriptKey;	//Script

    BSTR m_strIndexKey;	//Index
    BSTR m_strFaultLoopKey;	//FaultLoop
    BSTR m_strTolerancesKey;	//Tolerances
    BSTR m_strTTPLValidKey;	//TTPLValid
    BSTR m_strTTOLPlusKey;	//TTOLPlus
    BSTR m_strTTMIValidKey;	//TTMIValid
    BSTR m_strTTOLMinusKey;	//TTOLMinus
    BSTR m_strTTRLValidKey;	//TTRLValid
    BSTR m_strTTOLRelKey;	//TTOLRel
    BSTR m_strZTRLValidKey;	//ZTRLValid
    BSTR m_strZTOLRelKey;	//ZTOLRel
    BSTR m_strZTABValidKey;	//ZTABValid
    BSTR m_strZTOLAbsKey;	//ZTOLAbs

    BSTR m_strTIndexKey;	//TIndex

    //    BSTR m_strPtConnKey;	//PtConnKey
    //    BSTR m_strCtStarPointKey;	//CtStarPoint




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

    static BSTR RioKey()  {   return g_pXmlKeys->m_strRioKey;  }
    static BSTR TypeKey()  {   return g_pXmlKeys->m_strTypeKey;  }
    static BSTR BlockTypeKey()  {   return g_pXmlKeys->m_strBlockTypeKey;  }
    // static BSTR RioGroupKey()  {   return g_pXmlKeys->m_strRioGroupKey;  }

    static BSTR DeviceKey()  {   return g_pXmlKeys->m_strRioDeviceKey;  }
    static BSTR NameplateKey()  {   return g_pXmlKeys->m_strNameplateKey;  }
    static BSTR LocationKey()  {   return g_pXmlKeys->m_strLocationKey;  }
    static BSTR NominalValuesKey()  {   return g_pXmlKeys->m_strNominalValuesKey;  }
    static BSTR ResidualFactorsKey()  {   return g_pXmlKeys->m_strResidualFactorsKey;  }
    static BSTR LimitsKey()  {   return g_pXmlKeys->m_strLimitsKey;  }
    static BSTR MiscKey()  {   return g_pXmlKeys->m_strMiscKey;  }

    static BSTR DeviceModelKey()  {   return g_pXmlKeys->m_strDeviceModelKey;  }
    static BSTR ManufacturerKey()  {   return g_pXmlKeys->m_strManufacturerKey;  }
    static BSTR DeviceTypeKey()  {   return g_pXmlKeys->m_strDeviceTypeKey;  }
    static BSTR SerialnrKey()  {   return g_pXmlKeys->m_strSerialnrKey;  }
    static BSTR AdditionalINF02Key()  {   return g_pXmlKeys->m_strAdditionalINF02Key;  }

    static BSTR DeviceAddressKey()  {   return g_pXmlKeys->m_strDeviceAddressKey;  }
    static BSTR SubstationKey()  {   return g_pXmlKeys->m_strSubstationKey;  }
    static BSTR SubstationAddressKey()  {   return g_pXmlKeys->m_strSubstatioAddressKey;  }
    static BSTR BayKey()  {   return g_pXmlKeys->m_strBayKey;  }
    static BSTR BayAddressKey()  {   return g_pXmlKeys->m_strBayAddressKey;  }
    static BSTR ProtectedObjectNameKey()  {   return g_pXmlKeys->m_strProtectedObjectNameKey;  }

    static BSTR PhasesKey()  {   return g_pXmlKeys->m_strPhasesKey;  }
    static BSTR FNomKey()  {   return g_pXmlKeys->m_strFNomKey;  }
    static BSTR VNomKey()  {   return g_pXmlKeys->m_strVNomKey;  }
    static BSTR VPrimLLKey()  {   return g_pXmlKeys->m_strVPrimLLKey;  }
    static BSTR INomKey()  {   return g_pXmlKeys->m_strINomKey;  }
    static BSTR IPrimKey()  {   return g_pXmlKeys->m_strIPrimKey;  }

    static BSTR VLNVNKey()  {   return g_pXmlKeys->m_strVLNVNKey;  }
    static BSTR ININOMKey()  {   return g_pXmlKeys->m_strININOMKey;  }

    static BSTR VMaxLLKey()  {   return g_pXmlKeys->m_strVMaxLLKey;  }
    static BSTR IMaxKey()  {   return g_pXmlKeys->m_strIMaxKey;  }

    static BSTR DeBounceTimeKey()  {   return g_pXmlKeys->m_strDeBounceTimeKey;  }
    static BSTR DeGlitchTimeKey()  {   return g_pXmlKeys->m_strDeGlitchTimeKey;  }
    static BSTR OverloadSupTimeKey()  {   return g_pXmlKeys->m_strOverloadSupTimeKey;  }

    static BSTR CBKey()  {   return g_pXmlKeys->m_strRioCBKey;  }
    static BSTR TripTimeKey()  {   return g_pXmlKeys->m_strTripTimeKey;  }
    static BSTR CloseTimeKey()  {   return g_pXmlKeys->m_strCloseTimeKey;  }
    static BSTR P52ABKey()  {   return g_pXmlKeys->m_strP52ABKey;  }

    static BSTR DistanceKey()  {   return g_pXmlKeys->m_strDistanceKey;  }
    //    static BSTR ProtectedObjectKey()  {   return g_pXmlKeys->m_strProtectedObjectKey;  }
    static BSTR ProtectionDeviceKey()  {   return g_pXmlKeys->m_strProtectionDeviceKey;  }
    static BSTR ZonesKey()  {   return g_pXmlKeys->m_strZonesKey;  }
    static BSTR ZoneKey()  {   return g_pXmlKeys->m_strZoneKey;  }
    static BSTR GenricShapeKey()  {   return g_pXmlKeys->m_strGenricShapeKey;  }
    static BSTR MhoShapeKey()  {   return g_pXmlKeys->m_strMhoShapeKey;  }
    static BSTR ReachKey()  {   return g_pXmlKeys->m_strReachKey;  }
    static BSTR OffsetKey()  {   return g_pXmlKeys->m_strOffsetKey;  }
    static BSTR InsideKey()  {   return g_pXmlKeys->m_strInsideKey;  }
    static BSTR LineKey()  {   return g_pXmlKeys->m_strLineKey;  }
    static BSTR ArcKey()  {   return g_pXmlKeys->m_strArcKey;  }
    static BSTR RefPointRKey()  {   return g_pXmlKeys->m_strRefPointRKey;  }
    static BSTR RefPointXKey()  {   return g_pXmlKeys->m_strRefPointXKey;  }
    static BSTR AutoCloseKey()  {   return g_pXmlKeys->m_strAutoCloseKey;  }
    static BSTR AngleKey()  {   return g_pXmlKeys->m_strAngleKey;  }
    static BSTR RefPointMagKey()  {   return g_pXmlKeys->m_strRefPointMagKey;  }
    static BSTR RefPointAngleKey()  {   return g_pXmlKeys->m_strRefPointAngleKey;  }
    static BSTR RadiusKey()  {   return g_pXmlKeys->m_strRadiusKey;  }
    static BSTR StartAngleKey()  {   return g_pXmlKeys->m_strStartAngleKey;  }
    static BSTR EndAngleKey()  {   return g_pXmlKeys->m_strEndAngleKey;  }
    static BSTR DirKey()  {   return g_pXmlKeys->m_strDirKey;  }

    static BSTR DifferentialKey()  {   return g_pXmlKeys->m_strDifferentialKey;  }
    static BSTR DiffBiasKey()  {   return g_pXmlKeys->m_strDiffBiasKey;  }
    static BSTR TripCharKey()  {   return g_pXmlKeys->m_strTripCharKey;  }
    static BSTR PointKey()  {   return g_pXmlKeys->m_strPointKey;  }
    static BSTR PointXKey()  {   return g_pXmlKeys->m_strPointXKey;  }
    static BSTR PointYKey()  {   return g_pXmlKeys->m_strPointYKey;  }

    static BSTR OverCurrentKey()  {   return g_pXmlKeys->m_strOverCurrentKey;  }
    static BSTR OverCurrentGroupKey()  {   return g_pXmlKeys->m_strOverCurrentGroupKey;  }
    static BSTR OverCurrentUnitKey()  {   return g_pXmlKeys->m_strOverCurrentUnitKey;  }
    static BSTR OverCurrentTableKey()  {   return g_pXmlKeys->m_strOverCurrentTableKey;  }
    static BSTR OverCurrentCharKey()  {   return g_pXmlKeys->m_strOverCurrentCharKey;  }
    static BSTR OverCurrentCharI2TKey()  {   return g_pXmlKeys->m_strOverCurrentCharI2TKey;  }
    static BSTR OverCurrentCharAKey()  {   return g_pXmlKeys->m_strOverCurrentCharAKey;  }
    static BSTR OverCurrentCharBKey()  {   return g_pXmlKeys->m_strOverCurrentCharBKey;  }
    static BSTR OverCurrentCharPKey()  {   return g_pXmlKeys->m_strOverCurrentCharPKey;  }
    static BSTR OverCurrentCharQKey()  {   return g_pXmlKeys->m_strOverCurrentCharQKey;  }
    static BSTR OverCurrentCharK1Key()  {   return g_pXmlKeys->m_strOverCurrentCharK1Key;  }
    static BSTR OverCurrentCharK2Key()  {   return g_pXmlKeys->m_strOverCurrentCharK2Key;  }
    static BSTR OverCurrentElementsKey()  {   return g_pXmlKeys->m_strOverCurrentElementsKey;  }
    static BSTR TimedOverCurrentElementKey()  {   return g_pXmlKeys->m_strTimedOverCurrentElementKey;  }
    static BSTR OperatingCurvesKey()  {   return g_pXmlKeys->m_strOperatingCurvesKey;  }
    static BSTR InverseParameterCurveKey()  {   return g_pXmlKeys->m_strInverseParameterCurveKey;  }
    static BSTR I2TParameterCurveKey()  {   return g_pXmlKeys->m_strI2TParameterCurveKey;  }
    static BSTR IACParameterCurveKey()  {   return g_pXmlKeys->m_strIACParameterCurveKey;  }
    static BSTR CustomCurveKey()  {   return g_pXmlKeys->m_strCustomCurveKey;  }
    static BSTR CurvePointsKey()  {   return g_pXmlKeys->m_strCurvePointsKey;  }
    static BSTR CurvePointKey()  {   return g_pXmlKeys->m_strCurvePointKey;  }
    static BSTR TimeMultiplierKey()  {   return g_pXmlKeys->m_strTimeMultiplierKey;  }
    static BSTR NomvalKey()  {   return g_pXmlKeys->m_strNomvalKey;  }
    static BSTR ParameterAKey()  {   return g_pXmlKeys->m_strParameterAKey;  }
    static BSTR ParameterBKey()  {   return g_pXmlKeys->m_strParameterBKey;  }
    static BSTR ParameterCKey()  {   return g_pXmlKeys->m_strParameterCKey;  }
    static BSTR ParameterDKey()  {   return g_pXmlKeys->m_strParameterDKey;  }
    static BSTR ParameterEKey()  {   return g_pXmlKeys->m_strParameterEKey;  }
    static BSTR ParameterFKey()  {   return g_pXmlKeys->m_strParameterFKey;  }
    static BSTR ActiveKey()  {   return g_pXmlKeys->m_strActiveKey;  }
    static BSTR StandardCurveKey()  {   return g_pXmlKeys->m_strStandardCurveKey;  }
    static BSTR StandardCurveNameKey()  {   return g_pXmlKeys->m_strStandardCurveNameKey;  }
    static BSTR InverseParameterCurveNameKey()  {   return g_pXmlKeys->m_strInverseParameterCurveNameKey;  }

    static BSTR RioConverterKey()  {   return g_pXmlKeys->m_strRioConverterKey;  }
    static BSTR ScriptKey()  {   return g_pXmlKeys->m_strScriptKey;  }

    static BSTR IndexKey()  {   return g_pXmlKeys->m_strIndexKey;  }
    static BSTR FaultLoopKey()  {   return g_pXmlKeys->m_strFaultLoopKey;  }
    static BSTR TolerancesKey()  {   return g_pXmlKeys->m_strTolerancesKey;  }
    static BSTR TTPLValidKey()  {   return g_pXmlKeys->m_strTTPLValidKey;  }
    static BSTR TTOLPlusKey()  {   return g_pXmlKeys->m_strTTOLPlusKey;  }
    static BSTR TTMIValidKey()  {   return g_pXmlKeys->m_strTTMIValidKey;  }
    static BSTR TTOLMinusKey()  {   return g_pXmlKeys->m_strTTOLMinusKey;  }
    static BSTR TTRLValidKey()  {   return g_pXmlKeys->m_strTTRLValidKey;  }
    static BSTR TTOLRelKey()  {   return g_pXmlKeys->m_strTTOLRelKey;  }
    static BSTR ZTRLValidKey()  {   return g_pXmlKeys->m_strZTRLValidKey;  }
    static BSTR ZTOLRelKey()  {   return g_pXmlKeys->m_strZTOLRelKey;  }
    static BSTR ZTABValidKey()  {   return g_pXmlKeys->m_strZTABValidKey;  }
    static BSTR ZTOLAbsKey()  {   return g_pXmlKeys->m_strZTOLAbsKey;  }

    static BSTR TIndexKey()  {   return g_pXmlKeys->m_strTIndexKey;  }

    //    static BSTR PtConnKey()  {   return g_pXmlKeys->m_strPtConnKey;  }
    //    static BSTR CtStarPointKey()  {   return g_pXmlKeys->m_strCtStarPointKey;  }
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
