// PowerDrawArc.cpp: implementation of the CPowerDrawArc class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerDrawArc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CPowerDrawArc,CPowerDrawBaseClass)

CPowerDrawArc::CPowerDrawArc()
{
	pt1=pt2=pt3=CPoint(0,0);

	fCenterX=fCenterY=0;
	fBeginAngle=fEndAngle=0;
	m_iDrawModal= POWERADVANCE_UNIT_DRAW_MODE_NORMAL;

}
CPowerDrawArc::CPowerDrawArc(CString strClass):CPowerDrawBaseClass(strClass)
{
	
}
CPowerDrawArc::~CPowerDrawArc()
{

}
BOOL CPowerDrawArc::SetArcPoints(CPoint p1,CPoint p2,CPoint p3)
{

	return 1;
}
BOOL CPowerDrawArc::SetArcValues(CPowerPointValue	ppv1,CPowerPointValue	ppv2,CPowerPointValue	ppv3)
{
	double ddM=0.001;
	double an1=0,an2=0,an3=0;
	double x1,y1,x2,y2,x3,y3,xx1,xx2,yy1,yy2,xx,yy,rr;
	double k1=0,k2=0;
	x1=(double)ppv1.dX;x2=(double)ppv2.dX;x3=(double)ppv3.dX;
	y1=(double)ppv1.dY;y2=(double)ppv2.dY;y3=(double)ppv3.dY;
	if(x1==x2&&y1==y2||x1==x3&&y1==y3||x2==x3&&y2==y3)
	{

		//return 0;
	}
	xx1=(x1+x2)/2 ;		yy1=(y1+y2)/2;
	xx2=(x2+x3)/2;		yy2=(y2+y3)/2;

	if(fabs(y2-y1)>ddM)
		k1=-(x2-x1)/(y2-y1);
	else
	{
		if(y2-y1>0)
			k1=-(x2-x1) / ddM;
		else k1=(x2-x1) / ddM;
	}
	if(fabs(y3-y2)>ddM)	
		k2=-(x3-x2)/(y3-y2);
	else
	{
		if(y3-y2>0)
			k2=-(x3-x2) / ddM;
		else k2=(x3-x2) / ddM;
	}
	if(k1==k2 && k1==0.0)	return 0;
	if(fabs(y2-y1)<ddM)
	{
		xx=xx1;
		if(fabs(y3-y2)<ddM)
		{
			yy=y2+10000;
			rr=10000;
		}
		else
		{
			yy=yy2+k2*(xx2-xx);
			//rr=yy-y2;
			rr=sqrt((yy-y2)*(yy-y2) + (xx-x2)*(xx-x2));
			if(rr<0)rr=-rr;
		}
	}
	else if(fabs(y2-y3)<ddM)
	{
		xx=xx2;
		yy=yy1+k1*(xx1-xx);
		rr=sqrt((yy-y2)*(yy-y2) + (xx-x2)*(xx-x2));
		if(rr<0)rr=-rr;
	}
	else
	{
		if(k1==k2)
		{
			xx=x2+(double)(10000/(sqrt(1+k1*k1)));
			yy=y2+(double)(10000/sqrt((1+k1*k1)/(k1*k1)));
			rr=10000;
		}
		else
		{
			xx=(yy2-yy1+k1*xx1-k2*xx2)/(k1-k2);
			yy=yy1+k1*(xx-xx1);
			rr=(double)sqrt((xx-x1)*(xx-x1)+(yy-y1)*(yy-y1));
		}
	}
	fCenterX=xx;
	fCenterY=yy;
	fRadius=rr;
//////////////////////////////////////////////////////////////////////////////////
	double pi=3.1415926536;
	an1=(double)GetTheAngle(x1,xx,rr);
	if(y1-yy<0)
		an1=(double)(pi*2-an1);
	/////////////////////////////////////////////////
	an2=(double)GetTheAngle(x2,xx,rr);;
	if(y2-yy<0)
		an2=(double)(pi*2-an2);
	/////////////////////////////////////////////////

	an3=(double)GetTheAngle(x3,xx,rr);;
	if(y3-yy<0)
		an3=(double)(pi*2-an3);

	if(an1<an3)
	{
		if(an1<an2 && an2<an3)
		{
			m_ppvBegin=ppv1;m_ppvEnd=ppv3;
			fBeginAngle=an1;fEndAngle=an3;
		}
		else
		{
			fBeginAngle=an3;fEndAngle=an1;
			m_ppvBegin=ppv3;m_ppvEnd=ppv1;
		}
	}
	else
	{
		if(an3<an2 && an2<an1)
		{
			m_ppvBegin=ppv3;m_ppvEnd=ppv1;
			fBeginAngle=an3;fEndAngle=an1;
		}
		else
		{
			m_ppvBegin=ppv1;m_ppvEnd=ppv3;
			fBeginAngle=an1;fEndAngle=an3;
		}
	}
	return 1;
	///////////////////modify in 2001.8.8
}
double CPowerDrawArc::GetTheAngle(double f1,double f2,double fr)
{
	double ft=0;
	int iFlag=1;
	ft=f1-f2;
	if(fabs(ft)>fr)
	{
		if(f1>=f2)iFlag=1;
		else iFlag=-1;
		ft=iFlag*fr;
	}
	else
		ft=f1-f2;
	double an=acos(ft/fr);
	return an;

}
void CPowerDrawArc::Draw(CDC *pDC,int m_DrawMode,int m_DrawMode1,unsigned long ululBKColor)
{
}

CRect CPowerDrawArc::GetBox()
{
	CRect rectBox;
	rectBox.left=(int)(m_ptCenter.x-m_iRadiusX) - POWERADVANCE_PICK_RADIUS;
	rectBox.right=(int)(m_ptCenter.x+m_iRadiusX) + POWERADVANCE_PICK_RADIUS;
	rectBox.top=(int)(m_ptCenter.y-m_iRadiusY) - POWERADVANCE_PICK_RADIUS;
	rectBox.bottom=(int)(m_ptCenter.y+m_iRadiusY) + POWERADVANCE_PICK_RADIUS;
	MakeRectCorrect(&rectBox);
	return rectBox;
}

BOOL CPowerDrawArc::PickArc(CPoint point)
{
	CRect rectBox=GetBox();
	if(!rectBox.PtInRect(point)) return FALSE;

	double dAngle=GetPickPointAngle(point);

	double ddx=0,ddy=0,ddf=0;
	ddx=cos(dAngle)/m_iRadiusX;ddy=sin(dAngle)/m_iRadiusY;
	ddf=ddx*ddx+ddy*ddy;
	ddf=1/ddf;		ddf=sqrt(ddf);

	double dDis=sqrt((point.x-m_ptCenter.x)*(point.x-m_ptCenter.x)+(point.y-m_ptCenter.y)*(point.y-m_ptCenter.y));
	if(fabs(dDis-ddf)>POWERADVANCE_PICK_RADIUS) return FALSE;

	if(fBeginAngle<fEndAngle)
	{
		if(dAngle>fBeginAngle && dAngle < fEndAngle ) return TRUE;
	}
	else
	{
		double dPI=acos(-1);
		if(dAngle>fBeginAngle&&dAngle<2*dPI || dAngle < fEndAngle) return TRUE;
	}
	return FALSE;
}
double CPowerDrawArc::GetPickPointAngle(CPoint pt)
{
	double dAngle=0;
	double dl=sqrt((pt.x-m_ptCenter.x)*(pt.x-m_ptCenter.x)+(pt.y-m_ptCenter.y)*(pt.y-m_ptCenter.y));
	if(dl<0.0001) return 0;
	dAngle=acos((pt.x-m_ptCenter.x)/dl);
	if(pt.y-m_ptCenter.y>0.001) dAngle=3.1415927*2-dAngle;
	return dAngle;
}
void CPowerDrawArc::SetPicked(BOOL bPicked)
{
	if(bPicked)m_iDrawModal=POWERADVANCE_UNIT_DRAW_MODE_PICKED;
	else m_iDrawModal=POWERADVANCE_UNIT_DRAW_MODE_NORMAL;
}
BOOL CPowerDrawArc::InitOwnDataByString(CString strOwnData)
{
	int iBegin=0;
	int iEnd=0;
	CString strData="";
	CString strsp="=";
	CString strsp2=",";
	iBegin=strOwnData.Find(strsp);
	if(iBegin==-1)return FALSE;
	iBegin++;
	double x1=0,x2=0,y1=0,y2=0,x3=0,y3=0;
	
	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	x1=atof(strData);
	iBegin=iEnd+1;

	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	y1=atof(strData);
	iBegin=iEnd+1;


	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	x2=atof(strData);
	iBegin=iEnd+1;

	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	y2=atof(strData);
	iBegin=iEnd+1;


	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	x3=atof(strData);

	iBegin=iEnd+1;
	strData=strOwnData.Mid(iBegin,strOwnData.GetLength()-iBegin);
	y3=atof(strData);
	iBegin=iEnd+1;

	m_ppv1.dX=x1;m_ppv1.dY=y1;
	m_ppv2.dX=x2;m_ppv2.dY=y2;
	m_ppv3.dX=x3;m_ppv3.dY=y3;
	SetArcValues(m_ppv1,m_ppv2,m_ppv3);
	return TRUE;
}
BOOL CPowerDrawArc::ContinueInitIt(CAxisReference *axisReference)
{
	LogicPointToDevicePoint(&m_ptCenter,fCenterX,fCenterY,axisReference);
	CPoint ptTopLeft;
	LogicPointToDevicePoint(&ptTopLeft,fCenterX-fRadius,fCenterY-fRadius,axisReference);
	m_iRadiusX=m_ptCenter.x-ptTopLeft.x;
	m_iRadiusY=m_ptCenter.y-ptTopLeft.y;

	LogicPointToDevicePoint(&m_ptBegin,m_ppvBegin.dX,m_ppvBegin.dY,axisReference);
	LogicPointToDevicePoint(&m_ptEnd,m_ppvEnd.dX,m_ppvEnd.dY,axisReference);
	return TRUE;
}
CString CPowerDrawArc::GetExportTextString(void)
{
	return "";
}
CString  CPowerDrawArc::GetDisplayDataString(void)
{
	CString strData="";
	CString strTemp="";
//	m_ppv1.dX=x1;m_ppv1.dY=y1;
//	m_ppv2.dX=x2;m_ppv2.dY=y2;
//	m_ppv3.dX=x3;m_ppv3.dY=y3;
	
	strData="ARC=";
	strTemp.Format("%.3f,",m_ppv1.dX);  strData+=strTemp;
	strTemp.Format("%.3f,",m_ppv1.dY);  strData+=strTemp;
	strTemp.Format("%.3f,",m_ppv2.dX);  strData+=strTemp;
	strTemp.Format("%.3f,",m_ppv2.dY);  strData+=strTemp;
	strTemp.Format("%.3f,",m_ppv3.dX);  strData+=strTemp;
	strTemp.Format("%.3f;",m_ppv3.dY);  strData+=strTemp;
	CString strNewLine="00";	strNewLine.SetAt(0,13);	strNewLine.SetAt(1,10);	
	strData+=strNewLine;
	CString strTab="					";
	strData=strTab+strData;
	return strData;
}

CPowerDrawBaseClass* CPowerDrawArc::DirectGetNewObject()
{
	CPowerDrawBaseClass*pa=new CPowerDrawArc;
	pa->strClassName=strClassName;
	return pa ;
}

void CPowerDrawArc::DrawIt(CDC *pDC,BOOL bSel,double fZoomRatio,CPoint ptOffset)
{
	CRect rect;
	CPen cp,*pOldPen;

	rect.left=m_ptCenter.x-m_iRadiusX;
	rect.top=m_ptCenter.y-m_iRadiusY;
	rect.right=m_ptCenter.x+m_iRadiusX;
	rect.bottom=m_ptCenter.y+m_iRadiusY;
	MakeRectCorrect(&rect);

//	rect.left = (int)(rect.left*fZoomRatio);
//	rect.right = (int)(rect.right*fZoomRatio);
//	rect.top = (int)(rect.top*fZoomRatio);
//	rect.bottom = (int)(rect.bottom*fZoomRatio);
	rect.OffsetRect(ptOffset);

	CPoint ptBegin = m_ptBegin;
//	ptBegin.x = (int)(ptBegin.x * fZoomRatio);
//	ptBegin.y = (int)(ptBegin.y * fZoomRatio);
	CPoint ptEnd = m_ptEnd;
//	ptEnd.x = (int)(ptEnd.x * fZoomRatio);
//	ptEnd.y = (int)(ptEnd.y * fZoomRatio);
	if(!bSel)
	{
		cp.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
		pOldPen=pDC->SelectObject(&cp);
		pDC->Arc(rect,ptBegin,ptEnd);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();	
		return;
	}

	cp.CreatePen(m_uiPickLineStyle,m_iPickLineWidth,m_ulPickColor);
	pOldPen=pDC->SelectObject(&cp);
	pDC->Arc(rect,ptBegin,ptEnd);
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();
}

BOOL CPowerDrawArc::PickIt(CPoint point)
{
	return PickArc(point);
}
int CPowerDrawArc::GetQuadrant(double fx,double fy)
{
	int iQuadrant=0;
	if(fx>=0)
	{
		if(fy>=0)iQuadrant=0;
		else iQuadrant=3;
	}
	else
	{
		if(fy>=0)iQuadrant=1;
		else	iQuadrant=2;
	}
	return iQuadrant;
}
/*				fbx=fCenterX+fabs(fRadius);
				fex=fCenterX-fabs(fRadius);
				fby=fCenterY+fabs(fRadius);
				fey=fCenterY-fabs(fRadius);
				if(fMaxX<fbx)
					fMaxX=fbx;
				if(fMinX>fex)
					fMinX=fex;
				if(fMaxY<fby)
					fMaxY=fby;
				if(fMinY>fey)
					fMinY=fey;

	return;
*/
void CPowerDrawArc::GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	int iBAQuadrant=0,iEAQuadrant=0;
	double fbx,fby,fex,fey;


	fbx=(double)(fRadius * cos(fBeginAngle) )+ fCenterX;

	fby=(double)(fRadius * sin(fBeginAngle) )+ fCenterY;
	fex=(double)(fRadius * cos(fEndAngle) )+ fCenterX;
	fey=(double)(fRadius * sin(fEndAngle) )+ fCenterY;

//	iBAQuadrant= GetQuadrant(fbx,fby);
//	iEAQuadrant= GetQuadrant(fex,fey);
	iBAQuadrant= abs(int(fBeginAngle * 2 / 3.14159265) );
	iEAQuadrant= abs(int(fEndAngle * 2 / 3.14159265) );

	switch(iBAQuadrant)
	{
	case 0:
		{
			if(iEAQuadrant==0)
			{
				if(fbx<fMinX) fMinX=fbx;	if(fbx>fMaxX) fMaxX=fbx;
				if(fex<fMinX) fMinX=fex;	if(fex>fMaxX) fMaxX=fex;

				if(fby<fMinY) fMinY=fby;	if(fby>fMaxY) fMaxY=fby;
				if(fey<fMinY) fMinY=fey;	if(fey>fMaxY) fMaxY=fey;
			}
			else if(iEAQuadrant==1)
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
				if(fMaxY<fCenterY+fRadius)fMaxY=fCenterY+fRadius;
			}
			else if(iEAQuadrant==2)
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
				if(fMaxY<fCenterY+fRadius)fMaxY=fCenterY+fRadius;
				if(fMinX>fCenterX-fRadius)fMinX=fCenterX-fRadius;
			}
			else
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
				if(fMaxY<fCenterY+fRadius)fMaxY=fCenterY+fRadius;
				if(fMinX>fCenterX-fRadius)fMinX=fCenterX-fRadius;
				if(fMinY>fCenterY-fRadius)fMinY=fCenterY-fRadius;
			}
		}
		break;
	case 1:
		{
			if(iEAQuadrant==1)
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
			}
			else if(iEAQuadrant==2)
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
				if(fMinX>fCenterX-fRadius)fMinX=fCenterX-fRadius;
			}
			else
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
				if(fMinX>fCenterX-fRadius)fMinX=fCenterX-fRadius;
				if(fMinY>fCenterY-fRadius)fMinY=fCenterY-fRadius;
			}
		}
		break;
	case 2:
		{
			if(iEAQuadrant==2)
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
			}
			else
			{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
				if(fMinY>fCenterY-fRadius)fMinY=fCenterY-fRadius;
			}
		}
		break;
	case 3:
		{
				if(fbx<fMinX) fMinX=fbx;if(fbx>fMaxX) fMaxX=fbx;
				if(fby<fMinY) fMinY=fby;if(fby>fMaxY) fMaxY=fby;
				if(fex<fMinX) fMinX=fex;if(fex>fMaxX) fMaxX=fex;
				if(fey<fMinY) fMinY=fey;if(fey>fMaxY) fMaxY=fey;
		}
		break;
	}
}

/*////////////////////////////////////////////////////////////////////////////////
								+++直线与圆相交的方法+++
	★★★★★★如果iType==1
	则直线方程为	x=b
	(Ⅰ)x0-R <= b <=x0+R
			如果(x0-R==b) || (b==x0+R)	一个交点
				x=b		y=y0
			如果x0-R < b < x0+R
				x=b
				y=y0 ± sqrt( R*R - (b-x0)*(b-x0) )
	(Ⅱ)	如果	x0-R > b 或者 b > x0+R	没有交点

	★★★★★★如果iType==0
	设直线的方程为	y=k*x+b							①
	设圆方程为		(x-x0)*(x-x0)+(y-y0)*(y-y0)=R*R	②
	由①②得
	A=1+k*k		
	B=2*k*b-2*k*y0-2*x0
	C=x0*x0+(b-y0)*(b-y0)-R*R
	DELTA=B*B-4*A*C
	(Ⅰ)DELTA<0		无交点
	(Ⅱ)DELTA=0		一个交点
		x=-B / (2*A)
		y=k*x+b
	(Ⅲ)DELTA>0		两个交点
		x=(-B±sqrt(B*B-4*A*C)) / (2*A)
		y=k*x+b
*/////////////////////////////////////////////////////////////////////////////////
void CPowerDrawArc::GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal)
{
	iIntersetNum=0;
	double fX0,fY0;	//圆心坐标
	fX0=fCenterX;	fY0=fCenterY;//////////////获取圆心的坐标
	////////////////////////////////////////////////////////////////////////////
	//		解方程
	CPointValueObject *ppvo;
	double fintx=0,finty=0;
	double fintx1=0,finty1=0;
	double fAngle=0;////////////////////////此交点象对于圆心的偏移角度
	double fDeltaX=0,fDeltaY=0;
	if(pLF->iType==1) //★★★★★★如果iType==1
	{
		if(fX0>pLF->fConstB+fRadius || fX0<pLF->fConstB-fRadius )//如果	x0-R > b 或者 b > x0+R	没有交点
		{
			ppvo=NULL;iIntersetNum=0;
		}
		else//x0-R <= b <=x0+R
		{
			if(fX0==pLF->fConstB+fRadius || fX0==pLF->fConstB-fRadius)//如果(x0-R==b) || (b==x0+R)	一个交点
			{
				fintx=pLF->fConstB; //x=b		y=y0
				finty=fY0;
				if(IsPointTheJustPoint(pLF,fintx,finty))//正方向
				{
					if(IsIntersectPTOnArc(fintx,finty))
					{
						iIntersetNum=2;
						fAngle=GetIntPVAngle(fintx,finty);
						fDeltaX=(double)(fErrorVal*cos(fAngle));
						fDeltaY=(double)(fErrorVal*sin(fAngle));

						ppvo=new CPointValueObject;
						ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
						listIntersect.AddTail(ppvo);

						ppvo=new CPointValueObject;
						ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
						listIntersect.AddTail(ppvo);
					}
				}
				else{ppvo=NULL;iIntersetNum=0;}//反方向
			}
			else//如果x0-R < b < x0+R
			{	//x=b		y=y0 ± sqrt( R*R - (b-x0)*(b-x0) )
				double fx=fRadius*fRadius-(pLF->fConstB-fX0)*(pLF->fConstB-fX0);
				fx=(double)pow(fx,0.5);
				double fy=pLF->fConstB-fX0; 
				double fhypot=fx;
				fintx=pLF->fConstB;
				finty=fY0+fhypot;
				if(IsPointTheJustPoint(pLF,fintx,finty))iIntersetNum=1;
				finty=fY0-fhypot;
				if(IsPointTheJustPoint(pLF,fintx,finty))iIntersetNum+=1;
				if(iIntersetNum==0)
				{ppvo=NULL;}//反方向
				else if(iIntersetNum==2)	//两个点都在正方向
				{
					finty=fY0+fhypot;
					if(IsIntersectPTOnArc(fintx,finty))
					{
						fAngle=GetIntPVAngle(fintx,finty);
						fDeltaX=(double)(fErrorVal*cos(fAngle));
						fDeltaY=(double)(fErrorVal*sin(fAngle));

						ppvo=new CPointValueObject;
						ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
						listIntersect.AddTail(ppvo);
						ppvo=new CPointValueObject;
						ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
						listIntersect.AddTail(ppvo);
						
					}
					finty=fY0-fhypot;
					if(IsIntersectPTOnArc(fintx,finty))
					{
						fAngle=GetIntPVAngle(fintx,finty);
						fDeltaX=(double)(fErrorVal*cos(fAngle));
						fDeltaY=(double)(fErrorVal*sin(fAngle));
						ppvo=new CPointValueObject;
						ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
						listIntersect.AddTail(ppvo);
						ppvo=new CPointValueObject;
						ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
						listIntersect.AddTail(ppvo);
					}
				}
				else//(iIntersetNum==1)	一个点在正方向
				{
					finty=fY0+fhypot;
					if(IsPointTheJustPoint(pLF,fintx,finty))
					{
						if(IsIntersectPTOnArc(fintx,finty))
						{
							fAngle=GetIntPVAngle(fintx,finty);
							fDeltaX=(double)(fErrorVal*cos(fAngle));
							fDeltaY=(double)(fErrorVal*sin(fAngle));
							ppvo=new CPointValueObject;
							ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
							listIntersect.AddTail(ppvo);
							ppvo=new CPointValueObject;
							ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
							listIntersect.AddTail(ppvo);
						}
					}
					else
					{
						finty=fY0-fhypot;
						if(IsIntersectPTOnArc(fintx,finty))
						{
							fAngle=GetIntPVAngle(fintx,finty);
							fDeltaX=(double)(fErrorVal*cos(fAngle));
							fDeltaY=(double)(fErrorVal*sin(fAngle));
							ppvo=new CPointValueObject;
							ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
							listIntersect.AddTail(ppvo);
							ppvo=new CPointValueObject;
							ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
							listIntersect.AddTail(ppvo);
						}
					}
					
					//}
				}
			}////如果x0-R < b < x0+R
		}////x0-R <= b <=x0+R
	}//end of		[★★★★★★如果iType==1]
	else//★★★★★★如果iType==0
	{
		double fCoef_A,fCoef_B,fCoef_C;//二次方程的系数
		fCoef_A=1+pLF->fCoefK*pLF->fCoefK; //A=1+k*k	
		fCoef_B=pLF->fCoefK*pLF->fConstB - pLF->fCoefK*fY0 - fX0; //B=2*k*b-2*k*y0-2*x0
		fCoef_B=fCoef_B*2;
		fCoef_C=fX0*fX0 + (pLF->fConstB-fY0)*(pLF->fConstB-fY0)-fRadius*fRadius;//C=x0*x0+(b-y0)*(b-y0)-R*R
		double fDELTA=fCoef_B*fCoef_B-4*fCoef_A*fCoef_C;//B*B-4*A*C
		if(fDELTA<0)//无交点
		{ppvo=NULL;iIntersetNum=0;
		}
		else if(fDELTA==0)//一个交点
		{
			fintx=-fCoef_B*0.5f / fCoef_A;//x=-B / (2*A)
			finty=pLF->fCoefK*fintx+pLF->fConstB;
			if(IsPointTheJustPoint(pLF,fintx,finty))//正方向
			{
				if(IsIntersectPTOnArc(fintx,finty))
				{
					fAngle=GetIntPVAngle(fintx,finty);
					fDeltaX=(double)(fErrorVal*cos(fAngle));
					fDeltaY=(double)(fErrorVal*sin(fAngle));
					ppvo=new CPointValueObject;
					ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
					listIntersect.AddTail(ppvo);
				}
			}
			else{ppvo=NULL;iIntersetNum=0;}////反方向
		}
		else//两个交点
		{//x=(-B±sqrt(B*B-4*A*C)) / (2*A)	y=k*x+b
			fDELTA=(double)pow(fDELTA,0.5);
			fintx=(-fCoef_B+fDELTA)*0.5f/fCoef_A;
			finty=pLF->fCoefK*fintx+pLF->fConstB;
			fintx1=(-fCoef_B-fDELTA)*0.5f/fCoef_A;
			finty1=pLF->fCoefK*fintx1+pLF->fConstB;
			if(IsPointTheJustPoint(pLF,fintx,finty))iIntersetNum++;
			if(IsPointTheJustPoint(pLF,fintx1,finty1))iIntersetNum++;
			if(iIntersetNum==0)ppvo=NULL;
			else if(iIntersetNum==1)
			{
				if(IsPointTheJustPoint(pLF,fintx,finty))
				{
					if(IsIntersectPTOnArc(fintx,finty))
					{
						fAngle=GetIntPVAngle(fintx,finty);
						fDeltaX=(double)(fErrorVal*cos(fAngle));
						fDeltaY=(double)(fErrorVal*sin(fAngle));
						ppvo=new CPointValueObject;
						ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
						listIntersect.AddTail(ppvo);
						ppvo=new CPointValueObject;
						ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
						listIntersect.AddTail(ppvo);
					}
				}
				else
				{
					if(IsIntersectPTOnArc(fintx1,finty1))
					{
						fAngle=GetIntPVAngle(fintx1,finty1);
						fDeltaX=(double)(fErrorVal*cos(fAngle));
						fDeltaY=(double)(fErrorVal*sin(fAngle));
						ppvo=new CPointValueObject;
						ppvo->dX=fintx1-fDeltaX;ppvo->dY=finty1-fDeltaY;
						listIntersect.AddTail(ppvo);
						ppvo=new CPointValueObject;
						ppvo->dX=fintx1+fDeltaX;ppvo->dY=finty1+fDeltaY;
						listIntersect.AddTail(ppvo);
					}
				}
				
			}
			else
			{
				if(IsIntersectPTOnArc(fintx,finty))
				{
					fAngle=GetIntPVAngle(fintx,finty);
					fDeltaX=(double)(fErrorVal*cos(fAngle));
					fDeltaY=(double)(fErrorVal*sin(fAngle));
					ppvo=new CPointValueObject;
					ppvo->dX=fintx-fDeltaX;ppvo->dY=finty-fDeltaY;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx+fDeltaX;ppvo->dY=finty+fDeltaY;
					listIntersect.AddTail(ppvo);
				}
				if(IsIntersectPTOnArc(fintx1,finty1))
				{
					fAngle=GetIntPVAngle(fintx1,finty1);
					fDeltaX=(double)(fErrorVal*cos(fAngle));
					fDeltaY=(double)(fErrorVal*sin(fAngle));
					ppvo=new CPointValueObject;
					ppvo->dX=fintx1-fDeltaX;ppvo->dY=finty1-fDeltaY;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx1+fDeltaX;ppvo->dY=finty1+fDeltaY;
					listIntersect.AddTail(ppvo);
				}
			}
		}
	}
}
BOOL CPowerDrawArc::IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy)
{
	BOOL bJust=FALSE;
	if(pLF->fSlantAngle==0)//
	{
		if(fx > pLF->fbx)//正方向
			bJust=TRUE;
	}
	else if(pLF->fSlantAngle==180)
	{
		if(fx < pLF->fbx)//正方向
			bJust=TRUE;
	}
	else if(pLF->fSlantAngle<180)
	{
		if(fy > pLF->fby)//正方向
			bJust=TRUE;
	}
	else
	{
		if(fy < pLF->fby)//正方向
			bJust=TRUE;
	}
	return bJust;
}
double CPowerDrawArc::GetIntPVAngle(double fx,double fy)
{
	double dAngle=0;
	dAngle=GetTheAngle(fx,fCenterX,fRadius);
	if(fy<fCenterY)
	{
		dAngle=3.1415926536*2 - dAngle;
	}
	return dAngle;
}
BOOL CPowerDrawArc::IsIntersectPTOnArc(double fx,double fy)
{
	double dAngle=0;
	BOOL b=FALSE;
	dAngle=GetIntPVAngle(fx,fy);
	if(fBeginAngle>fEndAngle)
	{
		if(dAngle<=fBeginAngle && dAngle>=fEndAngle)
			b=FALSE;
		else
			b=TRUE;
	}
	else
	{
		if(dAngle>=fBeginAngle && dAngle<=fEndAngle)
			b=TRUE;
	}
	return b;
}
void CPowerDrawArc::OnColorChanged(COLORREF color)
{
	m_ulColor=color;
}


void CPowerDrawArc::GetIntersectPV2(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,BOOL bIner,int iEndOrBegin)
{
	iIntersetNum=0;
	double fX0,fY0;	//圆心坐标
	fX0=fCenterX;	fY0=fCenterY;//////////////获取圆心的坐标
	////////////////////////////////////////////////////////////////////////////
	//		解方程
	CPointValueObject *ppvo;
	double fintx=0,finty=0;
	double fintx1=0,finty1=0;

	double fCoef_A,fCoef_B,fCoef_C;//二次方程的系数
	//直线为垂直X轴的直线
	if(pLF->iType==1) //★★★★★★如果iType==1
	{
		if(fX0>pLF->fConstB+fRadius || fX0<pLF->fConstB-fRadius )//如果	x0-R > b 或者 b > x0+R	没有交点
		{
			ppvo=NULL;iIntersetNum=0;
		}
		else//x0-R <= b <=x0+R	
		{
			if(fX0==pLF->fConstB+fRadius || fX0==pLF->fConstB-fRadius)//如果(x0-R==b) || (b==x0+R)	一个交点
			{	//一个交点
				fintx=pLF->fConstB; //x=b		y=y0
				finty=fY0;
				if(IsPointTheJustPoint(pLF,fintx,finty))//正方向
				{
					if(IsIntersectPTOnArc(fintx,finty))
					{
						iIntersetNum=1;
						ppvo=new CPointValueObject;
						ppvo->dX=fintx;ppvo->dY=finty;
						listIntersect.AddTail(ppvo);
					}
				}
				else{ppvo=NULL;iIntersetNum=0;}//反方向
			}
			else
			{//有两个交点
				double fx=fRadius*fRadius-(pLF->fConstB-fX0)*(pLF->fConstB-fX0);
				fx=(double)pow(fx,0.5);
				double fy=pLF->fConstB-fX0; 
				double fhypot=fx;
				fintx=pLF->fConstB;
				finty=fY0+fhypot;
				iIntersetNum=2;
				//if(iIntersetNum==2)	//两个点都在正方向
				{
					finty=fY0+fhypot;
					ppvo=new CPointValueObject;
					ppvo->dX=fintx;ppvo->dY=finty;
					listIntersect.AddTail(ppvo);
				}
				finty=fY0-fhypot;
				{
					finty=fY0+fhypot;
					ppvo=new CPointValueObject;
					ppvo->dX=fintx;ppvo->dY=finty;
					listIntersect.AddTail(ppvo);
				}
			}
		}
		return ;
	}
	fCoef_A=1+pLF->fCoefK*pLF->fCoefK; //A=1+k*k	
	fCoef_B=pLF->fCoefK*pLF->fConstB - pLF->fCoefK*fY0 - fX0; //B=2*k*b-2*k*y0-2*x0
	fCoef_B=fCoef_B*2;
	fCoef_C=fX0*fX0 + (pLF->fConstB-fY0)*(pLF->fConstB-fY0)-fRadius*fRadius;//C=x0*x0+(b-y0)*(b-y0)-R*R
	double fDELTA=fCoef_B*fCoef_B-4*fCoef_A*fCoef_C;//B*B-4*A*C
	if(fDELTA<0)//无交点
	{
		ppvo=NULL;iIntersetNum=0;
	}
	else if(fDELTA==0)//一个交点
	{
		fintx=-fCoef_B*0.5f / fCoef_A;//x=-B / (2*A)
		finty=pLF->fCoefK*fintx+pLF->fConstB;
		if(IsPointTheJustPoint(pLF,fintx,finty))//正方向
		{
			if(bIner)
			{
				if(IsIntersectPTOnArc(fintx,finty))
				{
					ppvo=new CPointValueObject;
					ppvo->dX=fintx;ppvo->dY=finty;
					iIntersetNum=1;
					listIntersect.AddTail(ppvo);
				}
			}
			else
			{
				ppvo=new CPointValueObject;
				ppvo->dX=fintx;ppvo->dY=finty;
				iIntersetNum=1;
				listIntersect.AddTail(ppvo);
			}
		}
		else{ppvo=NULL;iIntersetNum=0;}////反方向
	}
	else//两个交点
	{//x=(-B±sqrt(B*B-4*A*C)) / (2*A)	y=k*x+b
		fDELTA=(double)pow(fDELTA,0.5);
		fintx=(-fCoef_B+fDELTA)*0.5f/fCoef_A;
		finty=pLF->fCoefK*fintx+pLF->fConstB;
		fintx1=(-fCoef_B-fDELTA)*0.5f/fCoef_A;
		finty1=pLF->fCoefK*fintx1+pLF->fConstB;
		iIntersetNum=2;
	//	if(IsPointTheJustPoint(pLF,fintx,finty))iIntersetNum++;
	//	if(IsPointTheJustPoint(pLF,fintx1,finty1))iIntersetNum++;
		if(iIntersetNum==0)ppvo=NULL;
		else
		{
			if(bIner)
			{
				if(IsIntersectPTOnArc(fintx,finty))
				{
					ppvo=new CPointValueObject;
					ppvo->dX=fintx;ppvo->dY=finty;
					listIntersect.AddTail(ppvo);
				}
				if(IsIntersectPTOnArc(fintx1,finty1))
				{
					ppvo=new CPointValueObject;
					ppvo->dX=fintx1;ppvo->dY=finty1;
					listIntersect.AddTail(ppvo);
				}
			}
			else
			{
				ppvo=new CPointValueObject;
				double fx=0,fy=0;
				if(iEndOrBegin==1)	//begin point
				{
					fx=m_ppv1.dX;fy=m_ppv1.dY;
				}
				else
				{
					fx=m_ppv3.dX;fy=m_ppv3.dY;
				}
				double fLen1=hypot(fintx-fx,finty-fy);
				double fLen2=hypot(fintx1-fx,finty1-fy);
				if(fLen1<fLen2)
				{
					ppvo->dX=fintx;ppvo->dY=finty;
				}
				else
				{
					ppvo->dX=fintx1;ppvo->dY=finty1;
				}
				listIntersect.AddTail(ppvo);
			}
		}
	}
}

//定义误差计算函数
CString CPowerDrawArc::GetErrorArcString(CPointValueObject*ppvo1,CPointValueObject*ppvo2,BOOL bIner)
{
	double fa1=GetIntPVAngle(ppvo1->dX,ppvo1->dY);
	double fa2=GetIntPVAngle(ppvo2->dX,ppvo2->dY);
	double fa=(fa1+fa2)/2;
	fa=GetIntPVAngle(m_ppv2.dX,m_ppv2.dY);
	double frr=hypot(ppvo1->dX-fCenterX,ppvo1->dY-fCenterY);
	double fx=fCenterX+frr*cos(fa);
	double fy=fCenterY+frr*sin(fa);
	CString strData="";
	CString strTemp="";
//	m_ppv1.dX=x1;m_ppv1.dY=y1;
//	m_ppv2.dX=x2;m_ppv2.dY=y2;
//	m_ppv3.dX=x3;m_ppv3.dY=y3;
	
	strData="ARC=";
	strTemp.Format("%.3f,",ppvo1->dX);  strData+=strTemp;
	strTemp.Format("%.3f,",ppvo1->dY);  strData+=strTemp;
	strTemp.Format("%.3f,",fx);  strData+=strTemp;
	strTemp.Format("%.3f,",fy);  strData+=strTemp;
	strTemp.Format("%.3f,",ppvo2->dX);  strData+=strTemp;
	strTemp.Format("%.3f;",ppvo2->dY);  strData+=strTemp;
	return strData;
}
//获得偏移后的误差曲线
CPowerDrawArc*CPowerDrawArc::GetErrorArc(double fErrorVal)	
{
	fErrorVal=-fErrorVal;
	if(fErrorVal<0)
		if(fRadius+fErrorVal<=0.001)return NULL;
	CPowerDrawArc*pArc=new CPowerDrawArc;
	double frr=fRadius+fErrorVal;
	pArc->fRadius=frr;
	pArc->fCenterX=fCenterX;
	pArc->fCenterY=fCenterY;
	pArc->fBeginAngle=fBeginAngle;
	pArc->fEndAngle=fEndAngle;
	pArc->m_ppvBegin.dX=m_ppvBegin.dX+fErrorVal*cos(fBeginAngle);
	pArc->m_ppvBegin.dY=m_ppvBegin.dY+fErrorVal*sin(fBeginAngle);
	pArc->m_ppvEnd.dX=m_ppvEnd.dX+fErrorVal*cos(fEndAngle);
	pArc->m_ppvEnd.dY=m_ppvEnd.dY+fErrorVal*sin(fEndAngle);
	pArc->m_ppv1.dX=m_ppvBegin.dX+fErrorVal*cos(fBeginAngle);
	pArc->m_ppv1.dY=m_ppvBegin.dY+fErrorVal*sin(fBeginAngle);
	pArc->m_ppv3.dX=m_ppvEnd.dX+fErrorVal*cos(fEndAngle);
	pArc->m_ppv3.dY=m_ppvEnd.dY+fErrorVal*sin(fEndAngle);
	double fa=0;
	fa=GetIntPVAngle(m_ppv2.dX,m_ppv2.dY);
	pArc->m_ppv2.dX=fCenterX+frr*cos(fa);
	pArc->m_ppv2.dY=fCenterY+frr*sin(fa);
	return pArc;
}

