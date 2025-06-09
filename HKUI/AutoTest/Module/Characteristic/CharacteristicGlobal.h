//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharacteristicGlobal.h

#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../../Module/DataMngr/DataMngrGlobal.h"
#include "../../../Module/DataMngr/DvmData.h"
#include "../../../Module/DataMngr/DataType.h"

#define CHARCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00040000)
#define CHARCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00040000)

#define CHARCLASSID_CCHARELEMENTARCP       (CHARCLASSID_EXLISTCLASS + 0X00000000)
#define CHARCLASSID_CCHARELEMENTARC       (CHARCLASSID_EXLISTCLASS + 0X00000001)
#define CHARCLASSID_CCHARELEMENTLINER       (CHARCLASSID_EXLISTCLASS + 0X00000002)
#define CHARCLASSID_CCHARELEMENTLINE       (CHARCLASSID_EXLISTCLASS + 0X00000003)
#define CHARCLASSID_CCHARELEMENTLENS       (CHARCLASSID_EXLISTCLASS + 0X00000004)
#define CHARCLASSID_CCHARELEMENTMHO       (CHARCLASSID_EXLISTCLASS + 0X00000005)
#define CHARCLASSID_CCHARACTERISTIC       (CHARCLASSID_EXLISTCLASS + 0X00000006)
#define CHARCLASSID_CCHARACTERISTICS       (CHARCLASSID_EXLISTCLASS + 0X00000007)
#define CHARCLASSID_CCHARELEMENT       (CHARCLASSID_EXLISTCLASS + 0X00000008)
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
#define CHARCLASSID_CCHARFOLDER       (CHARCLASSID_EXLISTCLASS + 0X00000015)
#define CHARCLASSID_CCHARTESTLINE       (CHARCLASSID_BASECLASS + 0X000000016)
#define CHARCLASSID_CCHARTESTPOINT       (CHARCLASSID_BASECLASS + 0X000000017)

//反时限
#define CHARCLASSID_CCHARELEMENTI2T       (CHARCLASSID_EXLISTCLASS + 0X000000017)
#define CHARCLASSID_CCHARELEMENTIAC       (CHARCLASSID_EXLISTCLASS + 0X000000018)
#define CHARCLASSID_CCHARELEMENTIEC       (CHARCLASSID_EXLISTCLASS + 0X000000019)
#define CHARCLASSID_CCHARELEMENTIEEE       (CHARCLASSID_EXLISTCLASS + 0X00000001A)
#define CHARCLASSID_CCHARELEMENTINVOWNDEF       (CHARCLASSID_EXLISTCLASS + 0X00000001B)

#define CHARCLASSID_CCHARELEMENTLINEP       (CHARCLASSID_EXLISTCLASS + 0X0000001C)

#define CHARCLASSID_CCHARELEMENTUIVP       (CHARCLASSID_EXLISTCLASS + 0X00000001D)//sf 20211213 低压反时限

#define CHARCLASSID_CCHARTESTOBJECTS       (CHARCLASSID_EXLISTCLASS + 0X0000001E)
#define CHARCLASSID_CCharElementPointS       (CHARCLASSID_BASECLASS + 0X0000001F)
#define CHARCLASSID_CCharElementPoint       (CHARCLASSID_BASECLASS + 0X00000021)//luozibing 20240902 测试点

#define CHARCLASSID_CCHARELEMENTIUF           (CHARCLASSID_BASECLASS + 0X00000020)//zhouhj 20230415 过励磁

#define CHARCLASSID_CCHARDRAWVIEW       (CHARCLASSID_EXLISTCLASS + 0X00000080)

#define CHARCLASSID_CCHARELEMENTDCOVERLOAD  (CHARCLASSID_EXLISTCLASS + 0X00000021) //cl20230912过负荷(直流)

#define CHARCLASSID_CCHARELEMENTRXIDG  (CHARCLASSID_EXLISTCLASS + 0X00000022) //zhangyq 20240620
#define CHARCLASSID_CCHARELEMENTRICURVE  (CHARCLASSID_EXLISTCLASS + 0X00000023)
#define CHARCLASSID_CCHARELEMENTLABIECCURVE  (CHARCLASSID_EXLISTCLASS + 0X00000024)
#define CHARCLASSID_CCHARELEMENTIT  (CHARCLASSID_EXLISTCLASS + 0X00000025)
#define CHARCLASSID_CCHARELEMENTI2TEx  (CHARCLASSID_EXLISTCLASS + 0X00000026)

//表达式Expr
#define CHARCLASSID_CCHARELEMENTEXPR  (CHARCLASSID_EXLISTCLASS + 0X00000027)


#define CHAR_ELEMENT_ID_LINED   _T("lined")
#define CHAR_ELEMENT_ID_MHO     _T("mho")
#define CHAR_ELEMENT_ID_LENS    _T("lens")
#define CHAR_ELEMENT_ID_LINE    _T("line")
#define CHAR_ELEMENT_ID_LINER   _T("liner")
#define CHAR_ELEMENT_ID_ARC     _T("arc")
#define CHAR_ELEMENT_ID_ARCP    _T("arcp")
#define CHAR_ELEMENT_ID_ARCD    _T("arcd")

#define CHAR_ELEMENT_ID_I2T    _T("I2T")
#define CHAR_ELEMENT_ID_IAC    _T("IAC")
#define CHAR_ELEMENT_ID_IEC    _T("IEC")
#define CHAR_ELEMENT_ID_IEEE    _T("IEEE")

#define CHAR_ELEMENT_ID_UIVP    _T("UIVP")//sf 20211213 低压反时限
#define CHAR_ELEMENT_ID_IUF    _T("IUF")//zhouhj 20230415 u/f反时限(过励磁)

#define CHAR_ELEMENT_ID_DCOVERLOAD    _T("DCOVERLOAD")//cl 20230912过负荷(直流)

#define CHAR_ELEMENT_ID_INVOWNDEF    _T("INVOWNDEF")

#define CHAR_ELEMENT_ID_RXIDG    _T("RXIDG") //zhangyq 20240620
#define CHAR_ELEMENT_ID_RICURVE    _T("RICURVE")
#define CHAR_ELEMENT_ID_LABIECCURVE    _T("LABIECCURVE")
#define CHAR_ELEMENT_ID_IT    _T("IT")
#define CHAR_ELEMENT_ID_I2TEx    _T("I2TEx")

#define CHAR_ELEMENT_ID_DIFF    _T("diff")

#define CHAR_TEST_LINE_TYPE_SYS  _T("sys")
#define CHAR_TEST_LINE_TYPE_USER _T("user")

#define CHAR_TESTLINE_MODE_ID_PLUMB  _T("plumb")
#define CHAR_TESTLINE_MODE_ID_VERT   _T("vert")
#define CHAR_TESTLINE_MODE_ID_HORZ   _T("horz")

#define CHAR_TESTLINE_MODE_INDEX_PLUMB  0
#define CHAR_TESTLINE_MODE_INDEX_VERT   1
#define CHAR_TESTLINE_MODE_INDEX_HORZ   2

#define CHAR_DISTANCE_FAULT_TYPE_LN           _T("LN")//距离保护故障类型-单相接地故障/单相阻抗
#define CHAR_DISTANCE_FAULT_TYPE_LL           _T("LL")//距离保护故障类型-相间故障
#define CHAR_DISTANCE_FAULT_TYPE_LLN          _T("LLN")//距离保护故障类型-相间接地故障
#define CHAR_DISTANCE_FAULT_TYPE_LLL          _T("LLL")//距离保护故障类型-三相故障
#define CHAR_DISTANCE_FAULT_TYPE_ALL          _T("ALL")//距离保护故障类型-全部

#define CHAR_TEST_OBJECT_STATE_SELECT		        	0x100//测试点选中状态
#define CHAR_TEST_OBJECT_STATE_NORMAL			            0//测试点初始状态
#define CHAR_TEST_OBJECT_STATE_ELIGIBLE	                	1//测试点合格状态
#define CHAR_TEST_OBJECT_STATE_INELIGIBLE	                2//测试点不合格状态
#define CHAR_TEST_OBJECT_STATE_FINISHED	                    3//测试点测试完成状态

////add wangtao 20240925新增宏定义区分特性曲线单独绘制测试线/点还是全部
#define	CHAR_TEST_OBJECT_DRAW_ALL						0//绘制测试线和测试点
#define	CHAR_TEST_OBJECT_DRAW_LINE						1//绘制测试线
#define	CHAR_TEST_OBJECT_DRAW_POINT						2//绘制测试点

//20241015 wanmj 计算阻抗搜索特性曲线误差带
#define CHAR_CURVEERR_PARAS_ID_ERRORLOGIC			"CurveErr_ErrorLogic"		//误差逻辑判断
#define CHAR_CURVEERR_PARAS_ID_RELERR			    "CurveErr_RelErr"	//相对误差
#define CHAR_CURVEERR_PARAS_ID_ABSERR		    	"CurveErr_AbsErr"	//绝对误差
	
class CCharacteristicXmlRWKeys : public CDataMngrXmlRWKeys
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
	BSTR m_strCCharElementPointsKey; //points
	BSTR m_strCCharElementPointKey; //point
	BSTR m_strCCharTestObjectsKey; //tests
	BSTR m_strCCharTestLineKey; //test
	BSTR m_strCCharacterFolderKey; //folder
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
	BSTR m_strCCharElementLinerKey; //liner
	BSTR m_strCCharElementArcKey; //arc
	BSTR m_strCCharElementArcpKey; //arcp
	BSTR m_strCCharElementI2TKey; //I2T
	BSTR m_strCCharElementIACKey; //IAC
	BSTR m_strCCharElementIECKey; //IEC
	BSTR m_strCCharElementIEEEKey; //IEEE
	BSTR m_strCCharElementUIVPKey; //UIVP //sf 20211213 低压反时限
	BSTR m_strCCharElementIUFKey; //IUF //

	BSTR m_strCCharElementDCOverLoadKey;

	BSTR m_strCCharElementRXIDGKey; //RXIDG
	BSTR m_strCCharElementRICurveKey; //RICURVE
	BSTR m_strCCharElementLabIecCurveKey; //LABORELECCURVE
	BSTR m_strCCharElementITKey; //IT
	BSTR m_strCCharElementI2TExKey; //I2TEx

	BSTR m_strCCharElementInvOwnDefKey; //IEEE
    BSTR m_strCCharElementExprFuncKey;//Expr
	BSTR m_strZKey; //z
	BSTR m_strPhKey; //ph
	BSTR m_strRadiusKey; //radius
	BSTR m_strStartAngleKey; //start-angle
	BSTR m_strEndAngleKey; //end-angle
	BSTR m_strClockwiseKey; //clockwise
	BSTR m_strDirKey; //dir
	BSTR m_strTestPointsKey;
	BSTR m_strErrLengthKey;
	BSTR m_strErrorLengthTypeKey;
	BSTR m_strXKey; //x
	BSTR m_strYKey; //y
	BSTR m_strAngleKey; //angle
	BSTR m_strForwardReachKey; //forward-reach
	BSTR m_strOffsetKey; //offset
	BSTR m_strWidthKey; //width
	BSTR m_strAutoCloseKey; //auto-close
	BSTR m_strUseKey; //use
	BSTR m_strAxisKey; //axis
	BSTR m_strTestLineModeKey; //test-line-mode
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
	BSTR m_strPosKey; //pos
	BSTR m_strRotateAngleKey;
	BSTR m_strAngleDefKey;
	BSTR m_strLengthUseKey;

	BSTR m_strTmaxKey;
	BSTR m_strXmaxKey;
	BSTR m_strPointsKey;
	BSTR m_strUseStartUpKey;
	BSTR m_strStartUpKey;
	BSTR m_strTStartUpKey;
	BSTR m_strUseSection1Key;
	BSTR m_strUseSection2Key;
	BSTR m_strUseSection3Key;
	BSTR m_strValSection1Key;
	BSTR m_strValSection2Key;
	BSTR m_strValSection3Key;
	BSTR m_strTSection1Key;
	BSTR m_strTSection2Key;
	BSTR m_strTSection3Key;

	BSTR m_strTpKey;
	BSTR m_strAKey;
	BSTR m_strKKey;
	BSTR m_strVpKey;
	BSTR m_strUTypeKey;
	BSTR m_strPickupKey;
	BSTR m_strAlphaKey;
	BSTR m_strBKey;
	BSTR m_strCKey;
	BSTR m_strDKey;
	BSTR m_strEKey;
	BSTR m_strBetaKey;
	BSTR m_strPKey;
	BSTR m_strQKey;
	BSTR m_strK1Key;
	BSTR m_strK2Key;
	BSTR m_strFromKey;   //from
	BSTR m_strToKey;     //to
	BSTR m_strStepKey;   //step


	BSTR m_strIBKey;
	BSTR m_strConstantKey;
	
    BSTR m_strExprKey;

	BSTR m_strFaultTypeKey;//20240910 luozibing 新增故障类型、区段类型、测试点状态、测试点Key
	BSTR m_strZoneTypeKey;
	BSTR m_strTestStateKey;
	BSTR m_strCCharTestPointKey;//point

    BSTR m_strMaxSensAng;   //20241014 wanmj 新增最大灵敏角

public:	
	static BSTR CCharTestObjectsKey()  {   return g_pXmlKeys->m_strCCharTestObjectsKey;  }
	static BSTR CCharElementPointKey()  { return g_pXmlKeys->m_strCCharElementPointKey; }
	static BSTR CCharElementPointsKey()  {   return g_pXmlKeys->m_strCCharElementPointsKey;  }
	static BSTR CCharTestLineKey()  {   return g_pXmlKeys->m_strCCharTestLineKey;  }
	static BSTR CCharTestPointKey()  { return g_pXmlKeys->m_strCCharTestPointKey; }
	static BSTR CCharacterFolderKey()  {   return g_pXmlKeys->m_strCCharacterFolderKey;  }
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
	static BSTR CCharElementLinerKey()  {   return g_pXmlKeys->m_strCCharElementLinerKey;  }
	static BSTR CCharElementArcKey()  {   return g_pXmlKeys->m_strCCharElementArcKey;  }
	static BSTR CCharElementArcpKey()  {   return g_pXmlKeys->m_strCCharElementArcpKey;  }
	static BSTR CCharElementI2TKey()  {   return g_pXmlKeys->m_strCCharElementI2TKey;  }
	static BSTR CCharElementIACKey()  {   return g_pXmlKeys->m_strCCharElementIACKey;  }
	static BSTR CCharElementIECKey()  {   return g_pXmlKeys->m_strCCharElementIECKey;  }
	static BSTR CCharElementIEEEKey()  {   return g_pXmlKeys->m_strCCharElementIEEEKey;  }

	static BSTR CCharElementUIVPKey()  {   return g_pXmlKeys->m_strCCharElementUIVPKey;  }//sf 20211213 低压反时限
	static BSTR CCharElementIUFKey()  {   return g_pXmlKeys->m_strCCharElementIUFKey;  }//zhouhj 20230415 U/F反时限

	static BSTR CCharElementDCOverLoadKey()  {   return g_pXmlKeys->m_strCCharElementDCOverLoadKey;  }//cl20230912过负荷(直流)

	static BSTR CCharElementRXIDGKey()  {   return g_pXmlKeys->m_strCCharElementRXIDGKey;  }
	static BSTR CCharElementRICurveKey()  {   return g_pXmlKeys->m_strCCharElementRICurveKey;  }
	static BSTR CCharElementLabIecCurveKey()  {   return g_pXmlKeys->m_strCCharElementLabIecCurveKey;  }
	static BSTR CCharElementITKey()  {   return g_pXmlKeys->m_strCCharElementITKey;  }
	static BSTR CCharElementI2TExKey()  {   return g_pXmlKeys->m_strCCharElementI2TExKey;  }

	static BSTR CCharElementInvOwnDefKey()  {   return g_pXmlKeys->m_strCCharElementInvOwnDefKey;  }
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
	static BSTR UseKey()  { return g_pXmlKeys->m_strUseKey; }
	static BSTR AxisKey()  {   return g_pXmlKeys->m_strAxisKey;  }
	static BSTR TestLineModeKey()  {   return g_pXmlKeys->m_strTestLineModeKey;  }
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
	static BSTR LengthUseKey()  {   return g_pXmlKeys->m_strLengthUseKey;  }

    static BSTR CCharElementExprFuncKey() {   return g_pXmlKeys->m_strCCharElementExprFuncKey;  }
    static BSTR ExprKey()  {   return g_pXmlKeys->m_strExprKey;  }

	static BSTR ExprFaultTypeKey()  { return g_pXmlKeys->m_strFaultTypeKey; }
	static BSTR ExprZoneTypeKey()  { return g_pXmlKeys->m_strZoneTypeKey; }
	static BSTR ExprTestStateKey()  { return g_pXmlKeys->m_strTestStateKey; }

    static BSTR MaxSensAngKey()  { return g_pXmlKeys->m_strMaxSensAng; }
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
	CDataType m_oDirDataType;
	CDataType m_oClockwiseDataType;

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;
	static CDataType* DirDataType();
	static CDataType* ClockwiseDataType();
};


void char_dev_SetModifiedFlag(CExBaseObject *pObj, BOOL bFlag);
BOOL char_dev_GetModifiedFlag(CExBaseObject *pObj);

UINT char_GetTestLineModeIndex(const CString &strID);
CString char_GetTestLineModeID(UINT nIndex);

UINT char_Cllockwise_To_UINT(const CString &strClockwise);
CString char_Cllockwise_To_String(UINT nClockwise);


#define COLOR_ERR_BAND_LINE  (RGB(255, 0, 0))