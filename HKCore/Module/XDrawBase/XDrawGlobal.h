//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XDrawGlobal.h

#pragma once

#include "../BaseClass/ExBaseList.h"

#define DWCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define DWCLASSID_LISTCLASS       (CLASSID_LISTCLASS + 0X00010000)

#define DWCLASSID_CXDRAWBASE           (DWCLASSID_BASECLASS + 0X00000000)
#define DWCLASSID_CXDRAWPOINT          (DWCLASSID_BASECLASS + 0X00000001)
#define DWCLASSID_CXDRAWLINE           (DWCLASSID_BASECLASS + 0X00000002)
#define DWCLASSID_CXDRAWCIRCLE         (DWCLASSID_BASECLASS + 0X00000003)
#define DWCLASSID_CXDRAWARC            (DWCLASSID_BASECLASS + 0X00000004)
#define DWCLASSID_CXDRAWLIST           (DWCLASSID_LISTCLASS + 0X00000005)
#define DWCLASSID_CXDRAWMNGR           (DWCLASSID_LISTCLASS + 0X00000006)
#define DWCLASSID_CXDRAWMNGRDESCARTES  (DWCLASSID_LISTCLASS + 0X00000007)
#define DWCLASSID_CXDRAWGROUP          (DWCLASSID_LISTCLASS + 0X00000008)
#define DWCLASSID_CXDRAWLINER          (DWCLASSID_BASECLASS + 0X00000009)
#define DWCLASSID_CXDRAWMNGRLOGARITHM          (DWCLASSID_LISTCLASS + 0X0000000A)
#define DWCLASSID_CXDRAWPOLYLINE           (DWCLASSID_BASECLASS + 0X0000000B)
#define DWCLASSID_CXDRAWPOINT_EX          (DWCLASSID_BASECLASS + 0X0000000C)
#define DWCLASSID_CXDRAWLINE_EX          (DWCLASSID_BASECLASS + 0X0000000D)

//2021-1-16  lijunqing
#define DWCLASSID_CXDRAWTEXT           (DWCLASSID_BASECLASS + 0X0000000E)

// #define AXIS_TYPE_ID_CARTES     _T("cartes")
// #define AXIS_TYPE_ID_POLAR      _T("polar")
// #define AXIS_TYPE_ID_LOGARITHM  _T("logarithm")
// #define AXIS_TYPE_INDEX_CARTES     0
// #define AXIS_TYPE_INDEX_POLAR      1
// #define AXIS_TYPE_INDEX_LOGARITHM  2


class CXDrawXmlRWKeys : public CXmlRWKeys
{
protected:
	CXDrawXmlRWKeys();
	virtual ~CXDrawXmlRWKeys();
	static long g_nDWRef;

public:
	static CXDrawXmlRWKeys* g_pXmlKeys;
	static CXDrawXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCXDrawMngrKey; //draw-mngr
	BSTR m_strCXDrawListKey; //draw-list
	BSTR m_strCXDrawArcKey; //arc
	BSTR m_strCXDrawCircleKey; //circle
	BSTR m_strCXDrawLineKey; //line
	BSTR m_strCXDrawPolylineKey; //line
	BSTR m_strCXDrawLineRKey; //liner
	BSTR m_strCXDrawPointKey; //point
	BSTR m_strCXDrawTextKey; //text
	BSTR m_strColorKey; //color
	BSTR m_strForeColorKey; //color
	BSTR m_strBackColorKey; //color
	BSTR m_strEnableKey;
	BSTR m_strShowKey;
	BSTR m_strStateKey; //state
	BSTR m_strXKey; //x
	BSTR m_strYKey; //y
	BSTR m_strPixelKey; //pixel
	BSTR m_strDrawStyleKey; //style
	BSTR m_strBXKey; //b-x
	BSTR m_strBYKey; //b-y
	BSTR m_strEXKey; //e-x
	BSTR m_strEYKey; //e-y
	BSTR m_strStyleKey; //style
	BSTR m_strWidthKey; //width
	BSTR m_strWidth2Key; //w
	BSTR m_strHeightKey; //height
	BSTR m_strXCenterKey; //x-c
	BSTR m_strYCenterKey; //y-c
	BSTR m_strRadiusXKey; //r-x
	BSTR m_strRadiusYKey; //r-y
	BSTR m_strRadiusKey; //r
	BSTR m_strAngleBeginKey; //angle-b
	BSTR m_strAngleEndKey; //angle-e
	BSTR m_strAngleKey; //angle
	BSTR m_strAxisKey; //axis
	BSTR m_strXMaxKey; //x-max
	BSTR m_strYMaxKey; //y-max
	BSTR m_strXMinKey; //x-min
	BSTR m_strYMinKey; //y-min
	BSTR m_strPointsKey; //points

public:
	static BSTR CXDrawMngrKey()  {   return g_pXmlKeys->m_strCXDrawMngrKey;  }
	static BSTR CXDrawListKey()  {   return g_pXmlKeys->m_strCXDrawListKey;  }
	static BSTR CXDrawArcKey()  {   return g_pXmlKeys->m_strCXDrawArcKey;  }
	static BSTR CXDrawCircleKey()  {   return g_pXmlKeys->m_strCXDrawCircleKey;  }
	static BSTR CXDrawLineKey()  {   return g_pXmlKeys->m_strCXDrawLineKey;  }
	static BSTR CXDrawPolylineKey()  {   return g_pXmlKeys->m_strCXDrawPolylineKey;  }
	static BSTR CXDrawLineRKey()  {   return g_pXmlKeys->m_strCXDrawLineRKey;  }
	static BSTR CXDrawPointKey()  {   return g_pXmlKeys->m_strCXDrawPointKey;  }
	static BSTR CXDrawTextKey()  {   return g_pXmlKeys->m_strCXDrawTextKey;  }
	static BSTR ColorKey()  {   return g_pXmlKeys->m_strColorKey;  }
	static BSTR StateKey()  {   return g_pXmlKeys->m_strStateKey;  }
	static BSTR XKey()  {   return g_pXmlKeys->m_strXKey;  }
	static BSTR YKey()  {   return g_pXmlKeys->m_strYKey;  }
	static BSTR PixelKey()  {   return g_pXmlKeys->m_strPixelKey;  }
	static BSTR DrawStyleKey()  {   return g_pXmlKeys->m_strDrawStyleKey;  }
	static BSTR BXKey()  {   return g_pXmlKeys->m_strBXKey;  }
	static BSTR BYKey()  {   return g_pXmlKeys->m_strBYKey;  }
	static BSTR EXKey()  {   return g_pXmlKeys->m_strEXKey;  }
	static BSTR EYKey()  {   return g_pXmlKeys->m_strEYKey;  }
	static BSTR StyleKey()  {   return g_pXmlKeys->m_strStyleKey;  }
	static BSTR WidthKey()  {   return g_pXmlKeys->m_strWidthKey;  }
	static BSTR HeightKey()  {   return g_pXmlKeys->m_strHeightKey;  }
	static BSTR XCenterKey()  {   return g_pXmlKeys->m_strXCenterKey;  }
	static BSTR YCenterKey()  {   return g_pXmlKeys->m_strYCenterKey;  }
	static BSTR RadiusXKey()  {   return g_pXmlKeys->m_strRadiusXKey;  }
	static BSTR RadiusYKey()  {   return g_pXmlKeys->m_strRadiusYKey;  }
	static BSTR RadiusKey()  {   return g_pXmlKeys->m_strRadiusKey;  }
	static BSTR AngleBeginKey()  {   return g_pXmlKeys->m_strAngleBeginKey;  }
	static BSTR AngleEndKey()  {   return g_pXmlKeys->m_strAngleEndKey;  }
	static BSTR AxisKey()  {   return g_pXmlKeys->m_strAxisKey;  }
	static BSTR XMaxKey()  {   return g_pXmlKeys->m_strXMaxKey;  }
	static BSTR YMaxKey()  {   return g_pXmlKeys->m_strYMaxKey;  }
	static BSTR XMinKey()  {   return g_pXmlKeys->m_strXMinKey;  }
	static BSTR YMinKey()  {   return g_pXmlKeys->m_strYMinKey;  }
	static BSTR PointsKey()  {   return g_pXmlKeys->m_strPointsKey;  }
};



class CXDrawConstGlobal
{
private:
	CXDrawConstGlobal();
	virtual ~CXDrawConstGlobal();

public:
	static CXDrawConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CXDrawConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};

void xdraw_DrawPoint(CDC *pDC, CPoint &ptPoint, DWORD dwDrawStyle, COLORREF crForeColor, long nPixel,  double fZoomRatio,const CPoint &ptOffset);
void xdraw_DrawPointLine(CDC *pDC, CPoint *pPointBuffer, long nCount, DWORD dwDrawStyle, COLORREF crForeColor, long nPixel,  double fZoomRatio,const CPoint &ptOffset);
