// PowerDrawBaseClass.cpp: implementation of the CPowerDrawBaseClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerDrawBaseClass.h"
#include "PDAPI.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAxisReference::CAxisReference()
{
	m_ptCenterLogInDv=CPoint(0,0);	
	m_fOneYGapValue=1;	
	m_fOneXGapValue=1;	

}
CAxisReference::~CAxisReference()
{

}
CPointValueObject::CPointValueObject()
{
	dX=dY=0;
	iIndex=0;
}
CPointValueObject::~CPointValueObject()
{
}
/////////////////////////////////定义直线函数方程数据类
CLineFunction::CLineFunction()
{
	InitIt();
}
void CLineFunction::InitIt()
{
	iType	=0;		//直线的种类
	fCoefK	=1;		//直线的斜率 k
	fSlantAngle=45;
	fConstB	=0;		//直线的常数 b
	fbx=0;fby=0;	//直线的起始点
	fex=0;fey=0;	//直线的终止点	
}
CLineFunction::~CLineFunction()
{

}
void CLineFunction::SetCoefKByAngle(double fAngle,double fx,double fy)
{
	fbx=fx;fby=fy;
	fSlantAngle=fAngle;
	if( (fAngle >89.999 && fAngle < 90.001) || (fAngle > 269.999 && fAngle < 270.001) )
	{
		iType=1;
	}
	else
	{
		iType=0;
		double f=fAngle * 3.141593f / 180;
		fCoefK=(double)tan(f);
		fConstB=fy-fx*fCoefK;
	}
}



IMPLEMENT_DYNCREATE(CPowerDrawBaseClass,CPDBaseObject)

CPowerDrawBaseClass::CPowerDrawBaseClass()
{
	Init();
}
CPowerDrawBaseClass::CPowerDrawBaseClass(CString strClass)
{
	strClassName=strClass;
	Init();
}
CPowerDrawBaseClass::~CPowerDrawBaseClass()
{

}
CPowerDrawBaseClass::CPowerDrawBaseClass(unsigned long color,UINT lineStyle,int iWidth)
{
	m_ulColor	=color;
	m_uiLineStyle	=lineStyle;
	m_iLineWidth	=iWidth;
}
void CPowerDrawBaseClass::Init()
{
	m_ulColor	=RGB(0,0,128);
	m_uiLineStyle	=PS_SOLID;
	m_iLineWidth	=1;
	m_ulPickColor		=RGB(0,0,255);
	m_uiPickLineStyle	=PS_SOLID   ;
	m_iPickLineWidth	=2;

}
void CPowerDrawBaseClass::LogicPointToDevicePoint(CPoint *ptDevice,double fx,double fy,CAxisReference *axisReference)// *pv)
{
	CPoint pointCenter=axisReference->m_ptCenterLogInDv;
	double fValYOneGap=axisReference->m_fOneYGapValue ;///Y轴实际坐标与实际值的比率
	double fValXOneGap=axisReference->m_fOneXGapValue ;//X轴实际坐标与实际值的比率
	/////坐标原点在屏幕上的位置
	/////// point  value
	double f=fx*fValXOneGap+pointCenter.x;
	ptDevice->x=FloatValToInt(f);
	f=-fy*fValYOneGap+pointCenter.y;
	ptDevice->y=FloatValToInt(f);
}

BOOL CPowerDrawBaseClass::InitOwnDataByString(CString strOwnData)
{
	return TRUE;
}

CPowerDrawBaseClass* CPowerDrawBaseClass::DirectGetNewObject()
{
	CPowerDrawBaseClass*pDB=new CPowerDrawBaseClass; 
	pDB->strClassName=strClassName;
	return pDB;
}

void CPowerDrawBaseClass::DrawIt(CDC *pDC,BOOL bSel,double fZoomRatio,CPoint ptOffset)
{

}

BOOL CPowerDrawBaseClass::ContinueInitIt(CAxisReference *axisReference)
{

	return TRUE;
}


CString CPowerDrawBaseClass::GetExportTextString(void)
{
	return "";
}

CString  CPowerDrawBaseClass::GetDisplayDataString(void)
{
	return "";
}

void  CPowerDrawBaseClass::BeforePrinting(double fMMValue)
{
	
}

BOOL CPowerDrawBaseClass::PickIt(CPoint point)
{
	return TRUE;
}
void CPowerDrawBaseClass::GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{

}

void CPowerDrawBaseClass::GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal)
{
	iIntersetNum=0;
}

void CPowerDrawBaseClass::OnColorChanged(COLORREF color)
{
	m_ulColor=color;
}

