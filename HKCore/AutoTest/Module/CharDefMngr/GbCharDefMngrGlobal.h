//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbCharDefMngrGlobal.h

#pragma once

#include "ExBaseList.h"

#define CHRCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define CHRCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define CHRCLASSID_CGBCHARLINE       (CHRCLASSID_BASECLASS + 0X00000000)
#define CHRCLASSID_CGBCHARLINER       (CHRCLASSID_BASECLASS + 0X00000001)
#define CHRCLASSID_CGBCHARLINES       (CHRCLASSID_BASECLASS + 0X00000002)
#define CHRCLASSID_CGBCHARARC       (CHRCLASSID_BASECLASS + 0X00000003)
#define CHRCLASSID_CGBCHARPLINE       (CHRCLASSID_EXLISTCLASS + 0X00000004)
#define CHRCLASSID_CGBCHARPLINES       (CHRCLASSID_EXLISTCLASS + 0X00000005)
#define CHRCLASSID_CGBCHARPLINER       (CHRCLASSID_EXLISTCLASS + 0X00000006)
#define CHRCLASSID_CGBCHARPARC       (CHRCLASSID_EXLISTCLASS + 0X00000007)
#define CHRCLASSID_CGBCHARPOINTDRAW       (CHRCLASSID_BASECLASS + 0X00000008)
#define CHRCLASSID_CGBCHARLINEDRAW       (CHRCLASSID_BASECLASS + 0X00000009)
#define CHRCLASSID_CGBCHARAXIS       (CHRCLASSID_EXLISTCLASS + 0X0000000A)
#define CHRCLASSID_CGBCHARAXISES       (CHRCLASSID_EXLISTCLASS + 0X0000000B)
#define CHRCLASSID_CGBCHARSDEF       (CHRCLASSID_EXLISTCLASS + 0X0000000C)
#define CHRCLASSID_CGBCHARMHO       (CHRCLASSID_BASECLASS + 0X0000000D)
#define CHRCLASSID_CGBCHARLENTOMATO       (CHRCLASSID_BASECLASS + 0X0000000E)
#define CHRCLASSID_CGBCHAR_Y_F_X       (CHRCLASSID_BASECLASS + 0X0000000F)
#define CHRCLASSID_CGBCHARFUNC       (CHRCLASSID_EXLISTCLASS + 0X00000010)
#define CHRCLASSID_CGBCHARCURVE       (CHRCLASSID_EXLISTCLASS + 0X00000011)
#define CHRCLASSID_CGBCHARDEF       (CHRCLASSID_EXLISTCLASS + 0X00000012)

class CGbCharDefMngrXmlRWKeys : public CXmlRWKeys
{
protected:
	CGbCharDefMngrXmlRWKeys();
	virtual ~CGbCharDefMngrXmlRWKeys();
	static long g_nCHRRef;

public:
	static CGbCharDefMngrXmlRWKeys* g_pXmlKeys;
	static CGbCharDefMngrXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCGbCharDefKey; //char-def
	BSTR m_strCGbCharCurveKey; //curve
	BSTR m_strCGbCharFuncKey; //func
	BSTR m_strCGbChar_y_f_xKey; //y_f_x
	BSTR m_strCGbCharLenTomatoKey; //lens-tomato
	BSTR m_strCGbCharMhoKey; //mho
	BSTR m_strCGbCharsDefKey; //chars-def
	BSTR m_strCGbCharAxisesKey; //axises
	BSTR m_strCGbCharAxisKey; //axis
	BSTR m_strCGbCharLineDrawKey; //line-draw
	BSTR m_strCGbCharPointDrawKey; //point-draw
	BSTR m_strCGbCharPArcKey; //parc
	BSTR m_strCGbCharPLinerKey; //pliner
	BSTR m_strCGbCharPLinesKey; //plines
	BSTR m_strCGbCharPLineKey; //pline
	BSTR m_strCGbCharArcKey; //arc
	BSTR m_strCGbCharLinesKey; //lines
	BSTR m_strCGbCharLinerKey; //liner
	BSTR m_strCGbCharLineKey; //line
	BSTR m_strXbKey; //x-b
	BSTR m_strYbKey; //y-b
	BSTR m_strAngleKey; //angle
	BSTR m_strDirKey; //dir
	BSTR m_strXeKey; //x-e
	BSTR m_strYeKey; //y-e
	BSTR m_strXcKey; //x-c
	BSTR m_strYcKey; //y-c
	BSTR m_strRKey; //r
	BSTR m_strAngleBKey; //angle-b
	BSTR m_strAngleEKey; //angle-e
	BSTR m_strXidKey; //x-id
	BSTR m_strYidKey; //y-id
	BSTR m_strXbidKey; //x-b-id
	BSTR m_strYbidKey; //y-b-id
	BSTR m_strXeidKey; //x-e-id
	BSTR m_strYeidKey; //y-e-id
	BSTR m_strAxisKey; //axis
	BSTR m_strXNameKey; //x-name
	BSTR m_strYNameKey; //y-name
	BSTR m_strXMinKey; //x-min
	BSTR m_strYMinKey; //y-min
	BSTR m_strXMaxKey; //x-max
	BSTR m_strYMaxKey; //y-max
	BSTR m_strReachKey; //reach
	BSTR m_strOffsetKey; //offset
	BSTR m_strWidthKey; //width
	BSTR m_strABKey; //AB
	BSTR m_strMinKey; //min
	BSTR m_strMaxKey; //max
	BSTR m_strExpressionKey; //Expression

public:
	static BSTR CGbCharDefKey()  {   return g_pXmlKeys->m_strCGbCharDefKey;  }
	static BSTR CGbCharCurveKey()  {   return g_pXmlKeys->m_strCGbCharCurveKey;  }
	static BSTR CGbCharFuncKey()  {   return g_pXmlKeys->m_strCGbCharFuncKey;  }
	static BSTR CGbChar_y_f_xKey()  {   return g_pXmlKeys->m_strCGbChar_y_f_xKey;  }
	static BSTR CGbCharLenTomatoKey()  {   return g_pXmlKeys->m_strCGbCharLenTomatoKey;  }
	static BSTR CGbCharMhoKey()  {   return g_pXmlKeys->m_strCGbCharMhoKey;  }
	static BSTR CGbCharsDefKey()  {   return g_pXmlKeys->m_strCGbCharsDefKey;  }
	static BSTR CGbCharAxisesKey()  {   return g_pXmlKeys->m_strCGbCharAxisesKey;  }
	static BSTR CGbCharAxisKey()  {   return g_pXmlKeys->m_strCGbCharAxisKey;  }
	static BSTR CGbCharLineDrawKey()  {   return g_pXmlKeys->m_strCGbCharLineDrawKey;  }
	static BSTR CGbCharPointDrawKey()  {   return g_pXmlKeys->m_strCGbCharPointDrawKey;  }
	static BSTR CGbCharPArcKey()  {   return g_pXmlKeys->m_strCGbCharPArcKey;  }
	static BSTR CGbCharPLinerKey()  {   return g_pXmlKeys->m_strCGbCharPLinerKey;  }
	static BSTR CGbCharPLinesKey()  {   return g_pXmlKeys->m_strCGbCharPLinesKey;  }
	static BSTR CGbCharPLineKey()  {   return g_pXmlKeys->m_strCGbCharPLineKey;  }
	static BSTR CGbCharArcKey()  {   return g_pXmlKeys->m_strCGbCharArcKey;  }
	static BSTR CGbCharLinesKey()  {   return g_pXmlKeys->m_strCGbCharLinesKey;  }
	static BSTR CGbCharLinerKey()  {   return g_pXmlKeys->m_strCGbCharLinerKey;  }
	static BSTR CGbCharLineKey()  {   return g_pXmlKeys->m_strCGbCharLineKey;  }
	static BSTR XbKey()  {   return g_pXmlKeys->m_strXbKey;  }
	static BSTR YbKey()  {   return g_pXmlKeys->m_strYbKey;  }
	static BSTR AngleKey()  {   return g_pXmlKeys->m_strAngleKey;  }
	static BSTR DirKey()  {   return g_pXmlKeys->m_strDirKey;  }
	static BSTR XeKey()  {   return g_pXmlKeys->m_strXeKey;  }
	static BSTR YeKey()  {   return g_pXmlKeys->m_strYeKey;  }
	static BSTR XcKey()  {   return g_pXmlKeys->m_strXcKey;  }
	static BSTR YcKey()  {   return g_pXmlKeys->m_strYcKey;  }
	static BSTR RKey()  {   return g_pXmlKeys->m_strRKey;  }
	static BSTR AngleBKey()  {   return g_pXmlKeys->m_strAngleBKey;  }
	static BSTR AngleEKey()  {   return g_pXmlKeys->m_strAngleEKey;  }
	static BSTR XidKey()  {   return g_pXmlKeys->m_strXidKey;  }
	static BSTR YidKey()  {   return g_pXmlKeys->m_strYidKey;  }
	static BSTR XbidKey()  {   return g_pXmlKeys->m_strXbidKey;  }
	static BSTR YbidKey()  {   return g_pXmlKeys->m_strYbidKey;  }
	static BSTR XeidKey()  {   return g_pXmlKeys->m_strXeidKey;  }
	static BSTR YeidKey()  {   return g_pXmlKeys->m_strYeidKey;  }
	static BSTR AxisKey()  {   return g_pXmlKeys->m_strAxisKey;  }
	static BSTR XNameKey()  {   return g_pXmlKeys->m_strXNameKey;  }
	static BSTR YNameKey()  {   return g_pXmlKeys->m_strYNameKey;  }
	static BSTR XMinKey()  {   return g_pXmlKeys->m_strXMinKey;  }
	static BSTR YMinKey()  {   return g_pXmlKeys->m_strYMinKey;  }
	static BSTR XMaxKey()  {   return g_pXmlKeys->m_strXMaxKey;  }
	static BSTR YMaxKey()  {   return g_pXmlKeys->m_strYMaxKey;  }
	static BSTR ReachKey()  {   return g_pXmlKeys->m_strReachKey;  }
	static BSTR OffsetKey()  {   return g_pXmlKeys->m_strOffsetKey;  }
	static BSTR WidthKey()  {   return g_pXmlKeys->m_strWidthKey;  }
	static BSTR ABKey()  {   return g_pXmlKeys->m_strABKey;  }
	static BSTR MinKey()  {   return g_pXmlKeys->m_strMinKey;  }
	static BSTR MaxKey()  {   return g_pXmlKeys->m_strMaxKey;  }
	static BSTR ExpressionKey()  {   return g_pXmlKeys->m_strExpressionKey;  }
};



class CGbCharDefMngrConstGlobal
{
private:
	CGbCharDefMngrConstGlobal();
	virtual ~CGbCharDefMngrConstGlobal();

public:
	static CGbCharDefMngrConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CGbCharDefMngrConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
