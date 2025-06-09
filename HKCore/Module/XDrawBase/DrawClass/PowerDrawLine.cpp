// PowerDrawLine.cpp: implementation of the CPowerDrawLine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerDrawLine.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPowerPointValue::CPowerPointValue()
{
	dX=dY=0;
}
CPowerPointValue::~CPowerPointValue()
{

}

IMPLEMENT_DYNCREATE(CPowerDrawLine,CPowerDrawBaseClass)

CPowerDrawLine::CPowerDrawLine()
{
	Init();
}
CPowerDrawLine::CPowerDrawLine(CString strClass):CPowerDrawBaseClass(strClass)
{
	Init();
}
CPowerDrawLine::~CPowerDrawLine()
{
	
}
CPowerDrawLine::CPowerDrawLine(CPoint pointBegin,CPoint pointEnd)
{
	m_pointBegin	=pointBegin;
	m_pointEnd		=pointEnd;
	m_iOldDrawModal=POWERADVANCE_UNIT_DRAW_MODE_NORMAL;
}
void CPowerDrawLine::Init()
{
	m_pointBegin	=CPoint(0,0);
	m_pointEnd		=CPoint(0,0);
	m_iDrawModal	=POWERADVANCE_UNIT_DRAW_MODE_NORMAL;
}
void CPowerDrawLine::InitPowerLine(CPoint pointBegin,CPoint pointEnd)
{
	m_pointBegin	=pointBegin;
	m_pointEnd		=pointEnd;
}

////////////////////////////////pick...
CRect CPowerDrawLine::GetMinRectBOX()
{
	CRect rectBOX;
	if(m_pointBegin.x>m_pointEnd.x)
	{
		rectBOX.left=m_pointEnd.x;
		rectBOX.right=m_pointBegin.x;
	}
	else
	{
		rectBOX.left=m_pointBegin.x;
		rectBOX.right=m_pointEnd.x;
	}
	if(m_pointBegin.y>m_pointEnd.y)
	{
		rectBOX.top=m_pointEnd.y;
		rectBOX.bottom=m_pointBegin.y;
	}
	else
	{
		rectBOX.top=m_pointBegin.y;
		rectBOX.bottom=m_pointEnd.y;
	}
	return rectBOX;
}
double CPowerDrawLine::GetLineAngle()
{
	int iYLen=m_pointBegin.y-m_pointEnd.y;
	int iXLen=m_pointBegin.x-m_pointEnd.x;

	double dLen=sqrt(iYLen*iYLen+iXLen*iXLen);
	if(dLen==0) return 0;
	double dAngle=acos(iXLen/dLen);
	return dAngle;
}
double CPowerDrawLine::GetLineAngleVal()	//获得直线的倾角
{
	double iYLen=-m_pvBegin.dY+m_pvEnd.dY;
	double iXLen=-m_pvBegin.dX+m_pvEnd.dX;

	double dLen=(double)sqrt(iYLen*iYLen+iXLen*iXLen);
	if(dLen==0) return 0;
	double dAngle=(double)acos(iXLen/dLen);
	if(iYLen<0)dAngle=3.1415927*2-dAngle;
	return dAngle;
}
double CPowerDrawLine::GetLineLength()		//获得直线的长度		2001年11月11日
{
	double iYLen=m_pvBegin.dY-m_pvEnd.dY;
	double iXLen=m_pvBegin.dX-m_pvEnd.dX;

	double dLen=(double)sqrt(iYLen*iYLen+iXLen*iXLen);
	return dLen;
}
BOOL CPowerDrawLine::PickLine(CPoint curPoint)
{
	m_iDrawModal=POWERADVANCE_UNIT_DRAW_MODE_NORMAL;
	CPoint objPoint=curPoint;
	CRect rectBox=GetMinRectBOX();
	CRect rectMaxBox;
	rectMaxBox.left = rectBox.left - POWERADVANCE_PICK_RADIUS;
	rectMaxBox.right = rectBox.right + POWERADVANCE_PICK_RADIUS;
	rectMaxBox.top = rectBox.top - POWERADVANCE_PICK_RADIUS;
	rectMaxBox.bottom = rectBox.bottom + POWERADVANCE_PICK_RADIUS;
	if(!rectMaxBox.PtInRect(curPoint)) return 0;
	double dAngleLine=GetLineAngle();
	double	dLineLen=0;
	if(dAngleLine>3.141/2 && dAngleLine<3.142/2)	///90
	{
		dLineLen=abs(curPoint.x-m_pointEnd.x);
	}
	else if(dAngleLine<0.01 || dAngleLine > 3.141)
	{
		dLineLen=abs(curPoint.y-m_pointEnd.y);
	}
	else
	{
		double x1,y1,x2,y2,x3,y3;
		double x,y;
		x1=m_pointBegin.x;x2=m_pointEnd.x;x3=curPoint.x;
		y1=m_pointBegin.y;y2=m_pointEnd.y;y3=curPoint.y;
		double k1=(y2-y1)/(x2-x1);
		double k2=-1/k1;
		x=(y3-y1-k2*x3+k1*x1)/(k1-k2);
		y=k1*(x-x1)+y1;
		dLineLen=sqrt((x-x3)*(x-x3)+(y-y3)*(y-y3));
	}
	BOOL bPicked=0;
	//if(dst<POWERADVANCE_PICK_RADIUS)
	if(dLineLen<POWERADVANCE_PICK_RADIUS)
		bPicked= 1;
	else
		bPicked= 0;
	SetPicked(bPicked);
	return bPicked;
}
void CPowerDrawLine::SetPicked(BOOL bPicked)
{
	if(bPicked)m_iDrawModal=POWERADVANCE_UNIT_DRAW_MODE_PICKED;
	else m_iDrawModal=POWERADVANCE_UNIT_DRAW_MODE_NORMAL;
}
void CPowerDrawLine::Draw(CDC *pDC)
{
	switch(m_iDrawModal)
	{
	case POWERADVANCE_UNIT_DRAW_MODE_NORMAL:
		{
			CPen cp,*pOldPen;
			cp.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
			pOldPen=pDC->SelectObject(&cp);
			pDC->MoveTo(m_pointBegin);
			pDC->LineTo(m_pointEnd);
			pDC->SelectObject(pOldPen);
			cp.DeleteObject();		
			break;
		}
	case POWERADVANCE_UNIT_DRAW_MODE_PICKED:
		{
			CPen cp,*pOldPen;
			cp.CreatePen(m_uiPickLineStyle,m_iPickLineWidth,m_ulPickColor);
			pOldPen=pDC->SelectObject(&cp);
			pDC->MoveTo(m_pointBegin);
			pDC->LineTo(m_pointEnd);
			pDC->SelectObject(pOldPen);
			cp.DeleteObject();		
			break;
		}
	default:
		{
			break;
		}
	}
	m_iOldDrawModal=m_iDrawModal;

}

BOOL CPowerDrawLine::InitOwnDataByString(CString strOwnData)
{
	int iBegin=0;
	int iEnd=0;
	CString strData="";
	CString strsp="=";
	CString strsp2=",";
	iBegin=strOwnData.Find(strsp);
	if(iBegin==-1)return FALSE;
	iBegin++;
	double x1=0,x2=0,y1=0,y2=0;
	
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

	strData=strOwnData.Mid(iBegin,strOwnData.GetLength()-iBegin);
	y2=atof(strData);
	iBegin=iEnd+1;

	m_pvBegin.dX=x1;m_pvBegin.dY=y1;
	m_pvEnd.dX=x2;m_pvEnd.dY=y2;
	return TRUE;
}
BOOL CPowerDrawLine::ContinueInitIt(CAxisReference *axisReference)
{
	LogicPointToDevicePoint(&m_pointBegin,m_pvBegin.dX,m_pvBegin.dY,axisReference);
	LogicPointToDevicePoint(&m_pointEnd,m_pvEnd.dX,m_pvEnd.dY,axisReference);
	return TRUE;
}

CString CPowerDrawLine::GetExportTextString(void)
{
	return "";
}

CString  CPowerDrawLine::GetDisplayDataString(void)
{
	CString strData="";
	CString strTemp="";
	CString strNewLine="00";	strNewLine.SetAt(0,13);	strNewLine.SetAt(1,10);	
	strData="LINE=";
	strTemp.Format("%.3f,",m_pvBegin.dX);strData+=strTemp;
	strTemp.Format("%.3f,",m_pvBegin.dY);strData+=strTemp;
	strTemp.Format("%.3f,",m_pvEnd.dX);  strData+=strTemp;
	strTemp.Format("%.3f;",m_pvEnd.dY);  strData+=strTemp;
	strData+=strNewLine;
	CString strTab="					";
	strData=strTab+strData;
	return strData;
}

CPowerDrawBaseClass* CPowerDrawLine::DirectGetNewObject()
{
	CPowerDrawBaseClass*pl=new CPowerDrawLine;
	pl->strClassName=strClassName;
	return pl;
}

void CPowerDrawLine::DrawIt(CDC *pDC,BOOL bSel,double fZoomRatio,CPoint ptOffset)
{
	CPoint ptBegin = m_pointBegin;
	CPoint ptEnd = m_pointEnd;

	ptBegin.Offset(ptOffset);
	ptEnd.Offset(ptOffset);

	int iLineWidth = (int)(m_iLineWidth * fZoomRatio);
	if(iLineWidth <= 0)
		iLineWidth = 1;
	CPen cp,*pOldPen;
	if(!bSel)
	{
		cp.CreatePen(m_uiLineStyle,iLineWidth,m_ulColor);
		pOldPen=pDC->SelectObject(&cp);
		pDC->MoveTo(ptBegin);
		pDC->LineTo(ptEnd);
		pDC->SelectObject(pOldPen);
		cp.DeleteObject();	
		return;
	}
	cp.CreatePen(m_uiPickLineStyle,iLineWidth,m_ulPickColor);
	pOldPen=pDC->SelectObject(&cp);
	pDC->MoveTo(ptBegin);
	pDC->LineTo(ptEnd);
	pDC->SelectObject(pOldPen);
	cp.DeleteObject();	
}


BOOL CPowerDrawLine::PickIt(CPoint point)
{
	return PickLine(point);
}

void CPowerDrawLine::GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	double fx=(double)m_pvBegin.dX;
	double fy=(double)m_pvBegin.dY;
	if(fx<fMinX) fMinX=fx;
	if(fx>fMaxX) fMaxX=fx;
	if(fy<fMinY) fMinY=fy;
	if(fy>fMaxY) fMaxY=fy;
	fx=(double)m_pvEnd.dX;
	fy=(double)m_pvEnd.dY;
	if(fx<fMinX) fMinX=fx;
	if(fx>fMaxX) fMaxX=fx;
	if(fy<fMinY) fMinY=fy;
	if(fy>fMaxY) fMaxY=fy;
}
/*////////////////////////////////////////////////////////////////////////////////
								+++直线与直线相交的方法+++
	★★★★★★如果iType==1
	则直线方程为	x=b
	△x1=x-x1
	△x2=x-x2
	(Ⅰ)	△x1*△x2==0
			如果△x1==0		△x2!=0		则第一点为交点(x1,y1)
			如果△x2==0		△x1!=0		则第二点为交点(x2,y2)
			如果△x2==0		△x1==0		此种情况不存在
	(Ⅱ)	△x1*△x2>0		两个直线没有交点
	(Ⅲ)	△x1*△x2<0
			●x=b												
			●y=( y2*|△x1| + y1*|△x2| ) / (|△x1|+|△x2|)	
	★★★★★★如果iType==0
	设直线的方程为y=k*x+b	①
	另一直线段的两个端点坐标分别为(x1,y1)、(x2,y2)，将此两点分别代入①

	y1'=k*x1+b				②
	y2'=k*x2+b				③

	△y1=y1'-y1				④
	△y2=y2'-y2				⑤

	下面分情况讨论：
	(Ⅰ)	△y1 * △y2 =0
			如果	△y1==0 但 △y2!=0		则第一点为交点(x1,y1)
			如果	△y2==0 但 △y1!=0		则第二点为交点(x2,y2)
			如果	△y1==0 但 △y2==0		则两直线重合
	(Ⅱ)	△y1 * △y2 >0		两个直线没有交点
	(Ⅲ)	△y1 * △y2 <0		两个直线又一个交点
			利用相似三角形的原理，可得交点的坐标为
			●x=( x2*|△y1| + x1*|△y2| ) / (|△y1|+|△y2|)	⑥
			●y=( y2*|△y1| + y1*|△y2| ) / (|△y1|+|△y2|)	⑦

	判断交点是否在直线的正方向：求取点(fbx,fby)的方向
		由于直线的起始点为(fbx,fby),倾斜角为fSlantAngle,
		if(fSlantAngle == 180 || fSlantAngle == 0 )
			if(fSlantAngle==0)
				if(x>fbx)	正方向
				else		反方向
			else
				if(x>fbx)	反方向
				else		正方向				
		if(fSlantAngle < 180)
			if(y>fby)	正方向
			else		反方向
		else
			if(y>fby)	反方向
			else		正方向
		
*/////////////////////////////////////////////////////////////////////////////////
void CPowerDrawLine::GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal)
{
	double fx1,fy1,fx2,fy2;
	/////直线段数据(x1,y1)、(x2,y2)
	fx1=m_pvBegin.dX;	fy1=m_pvBegin.dY;
	fx2=m_pvEnd.dX;		fy2=m_pvEnd.dY;
	CPointValueObject *ppv;//=new CPowerPointValue;
	double fErrorx1=0,fErrory1=0,fErrorx2=0,fErrory2=0;
	double fAngle=GetLineAngleVal();
	fErrorx1=(double)(fErrorVal*sin(fAngle));
	fErrory1=(double)(fErrorVal*cos(fAngle));
	fErrorx2=-(double)(-fErrorVal*sin(-fAngle));
	fErrory2=(double)(-fErrorVal*cos(-fAngle));


	if(pLF->iType==1)//★★★★★★如果iType==1
	{
		double fDLTX1=pLF->fConstB-fx1;
		double fDLTX2=pLF->fConstB-fx2;
		double fMR=fDLTX1*fDLTX2;
		if(fMR>0)//△x1*△x2>0		两个直线没有交点
		{
			iIntersetNum=0;
			ppv = NULL;
		}
		else if(fMR==0)//△x1*△x2==0
		{
			if(fDLTX1==0 )//如果△x1==0		△x2!=0		则第一点为交点(x1,y1)
			{
				if(IsPointTheJustPoint(pLF,fx1,fy1))
				{
					iIntersetNum=2;
					ppv=new CPointValueObject;
					ppv->dX=fx1+fErrorx1;		ppv->dY=fy1-fErrory1;
					listIntersect.AddTail(ppv);
					ppv=new CPointValueObject;
					ppv->dX=fx1+fErrorx2;		ppv->dY=fy1-fErrory2;
					listIntersect.AddTail(ppv);
				}
				else{	iIntersetNum=0;ppv=NULL;}
			}
			else//如果△x2==0		△x1!=0		则第二点为交点(x2,y2)
			{
				if(IsPointTheJustPoint(pLF,fx2,fy2))
				{
					ppv=new CPointValueObject;
					ppv->dX=fx2+fErrorx1;		ppv->dY=fy2-fErrory1;
					listIntersect.AddTail(ppv);
					ppv=new CPointValueObject;
					ppv->dX=fx2+fErrorx2;		ppv->dY=fy2-fErrory2;
					listIntersect.AddTail(ppv);
					iIntersetNum=1;
				}
				else
				{	iIntersetNum=0;ppv=NULL;}
			}
		}
		else//△x1*△x2<0
		{
			fDLTX1=fabs(fDLTX1);	fDLTX2=fabs(fDLTX2);
			fx1=pLF->fConstB;
			fy1=(fy2*fDLTX1 + fy1*fDLTX2) / (fDLTX1+fDLTX2);
			if(IsPointTheJustPoint(pLF,fx1,fy1))
			{
				ppv=new CPointValueObject;
				ppv->dX=fx1+fErrorx1;		ppv->dY=fy1-fErrory1;
				listIntersect.AddTail(ppv);
				ppv=new CPointValueObject;
				ppv->dX=fx1+fErrorx2;		ppv->dY=fy1-fErrory2;
				listIntersect.AddTail(ppv);
				iIntersetNum=1;
			}
			else
			{	iIntersetNum=0;ppv=NULL;}
		}
	}
	else//★★★★★★如果iType==0
	{
		double fy11=pLF->fCoefK * fx1 + pLF->fConstB;//y1'=k*x1+b	②
		double fy21=pLF->fCoefK * fx2 + pLF->fConstB;//y2'=k*x2+b	③
		double fDLTy1=fy11 - fy1;//△y1=y1'-y1		④
		double fDLTy2=fy21 - fy2;//△y1=y2'-y2		⑤
		double fMR=fDLTy1*fDLTy2;
		if(fMR==0)//△y1 * △y2 =0
		{
			if(fDLTy1== 0 && fDLTy2!=0)//如果△y1==0 但 △y2!=0	则第一点为交点(x1,y1)
			{
				if(IsPointTheJustPoint(pLF,fx1,fy1))
				{
					ppv=new CPointValueObject;
					ppv->dX=fx1+fErrorx1;		ppv->dY=fy1-fErrory1;
					listIntersect.AddTail(ppv);
					ppv=new CPointValueObject;
					ppv->dX=fx1+fErrorx2;		ppv->dY=fy1-fErrory2;
					listIntersect.AddTail(ppv);
					iIntersetNum=1;
				}
				else
				{
				}
			}
			else if(fDLTy2== 0 && fDLTy1!=0)//如果△y2==0 但 △y1!=0 则第二点为交点(x2,y2)
			{
				if(IsPointTheJustPoint(pLF,fx2,fy2))
				{
					ppv=new CPointValueObject;
					ppv->dX=fx2+fErrorx1;		ppv->dY=fy2-fErrory1;
					listIntersect.AddTail(ppv);
					ppv=new CPointValueObject;
					ppv->dX=fx2+fErrorx2;		ppv->dY=fy2-fErrory2;
					listIntersect.AddTail(ppv);
					iIntersetNum=1;
				}
				else
				{
				}
			}
			else//如果△y1==0 但 △y2==0 则两直线重合
			{
				ppv=NULL;iIntersetNum=0;
			}
		}
		else if(fMR>0)//△y1 * △y2 >0		两个直线没有交点
		{
			ppv=NULL;iIntersetNum=0;
		}
		else//△y1 * △y2 <0		两个直线又一个交点
		{
			fDLTy1=fabs(fDLTy1);fDLTy2=fabs(fDLTy2);
			//ppv=new CPowerPointValue;
			//iIntersetNum=1;
			double fIntsX,fIntsY;
			//●x=( x2*|△y1| + x1*|△y2| ) / (|△y1|+|△y2|)	⑥
			fIntsX=(fx2*fDLTy1 + fx1*fDLTy2) / (fDLTy1+fDLTy2);
			//●y=( y2*|△y1| + y1*|△y2| ) / (|△y1|+|△y2|)	⑦
			fIntsY=(fy2*fDLTy1 + fy1*fDLTy2) / (fDLTy1+fDLTy2);
			//判断交点是否在直线的正方向：求取点(fIntsX,fIntsY)的方向
			if(IsPointTheJustPoint(pLF,fIntsX,fIntsY))
			{
					ppv=new CPointValueObject;
					ppv->dX=fIntsX+fErrorx1;		ppv->dY=fIntsY-fErrory1;
					listIntersect.AddTail(ppv);
					ppv=new CPointValueObject;
					ppv->dX=fIntsX+fErrorx2;		ppv->dY=fIntsY-fErrory2;
					listIntersect.AddTail(ppv);
			}
			else
			{
				iIntersetNum=0;
				ppv=NULL;
			}			
		}
	}
	if(iIntersetNum)
	{
		
	}
	//return ppv;
}
void CPowerDrawLine::GetIntersectPV2(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect)
{
	double fx,fy;
	/////直线段数据(x1,y1)、(x2,y2)
	CPointValueObject *ppv;
	CLineFunction*pLineFun;//=new CLineFunction;
	pLineFun=GetLineFunction();
	if( fabs(pLineFun->fCoefK - pLF->fCoefK)<0.001  )//两个直线没有交点
	{
		iIntersetNum=0;
		ppv = NULL;
	}	
	else
	{
		if(pLineFun->iType==1)	//当前直线为垂直线
		{
			fx=pLineFun->fConstB;
			fy=pLF->fCoefK*fx+pLF->fConstB;
			iIntersetNum=1;
		}
		else if(pLF->iType==1)	//前直线为垂直线
		{
			fx=pLF->fConstB;
			fy=pLineFun->fCoefK*fx+pLineFun->fConstB;
			iIntersetNum=1;
		}
		else
		{
			fx=(pLineFun->fConstB-pLF->fConstB)/(pLF->fCoefK-pLineFun->fCoefK);
			fy=pLineFun->fCoefK*fx + pLineFun->fConstB;
			if(IsPointTheJustPoint(pLF,fx,fy))
			{
				iIntersetNum=1;
			}
			else
			{	iIntersetNum=0;ppv=NULL;}
		}
	}	
	if(iIntersetNum)
	{
		ppv=new CPointValueObject;
		ppv->dX=fx;	//●x=b	
		ppv->dY=fy;			
		listIntersect.AddTail(ppv);
	}
	delete pLineFun;
	//return ppv;
}
BOOL CPowerDrawLine::IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy)
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

void CPowerDrawLine::OnColorChanged(COLORREF color)
{
	m_ulColor=color;
}

//////获得误差线直线数据
CString CPowerDrawLine::GetErrorLineString(CPointValueObject*ppvo1,CPointValueObject*ppvo2)
{
	CString strData="";
	CString strTemp="";
	strData="LINE=";
	strTemp.Format("%.3f,",ppvo1->dX);	strData+=strTemp;
	strTemp.Format("%.3f,",ppvo1->dY);	strData+=strTemp;
	strTemp.Format("%.3f,",ppvo2->dX);  strData+=strTemp;
	strTemp.Format("%.3f;",ppvo2->dY);  strData+=strTemp;
	return strData;	
}
//获得此直线的偏移直线
CPowerDrawLine*CPowerDrawLine::GetErrorLine(double fErrorVal)
{
	double fAngle=GetLineAngleVal();
	double faa=fAngle*180 / ((double)CONST_PI);
	if(fabs(fErrorVal)<=0.0001)return NULL;
	double foffx=(double)(fErrorVal*sin((fAngle+90)));
	double foffy=(double)(fErrorVal*cos((fAngle+90)));
	if(fErrorVal>0)
	{
		foffx=(double)(fErrorVal*sin((fAngle+0)));
		foffy=(double)(fErrorVal*cos((fAngle+0)));
	}
	else
	{
		foffx=-(double)(fErrorVal*sin((-fAngle)));
		foffy=(double)(fErrorVal*cos((-fAngle)));
	}
	CPowerDrawLine*pLine=new CPowerDrawLine;
//	if(fAngle<=(double)CONST_PI)
	{
		pLine->m_pvBegin.dX=m_pvBegin.dX+foffx;
		pLine->m_pvBegin.dY=m_pvBegin.dY-foffy;
		pLine->m_pvEnd.dX=m_pvEnd.dX+foffx;
		pLine->m_pvEnd.dY=m_pvEnd.dY-foffy;
	}
/*	else
	{
		pLine->m_pvBegin.dX=m_pvBegin.dX+foffx;
		pLine->m_pvBegin.dY=m_pvBegin.dY+foffy;
		pLine->m_pvEnd.dX=m_pvEnd.dX+foffx;
		pLine->m_pvEnd.dY=m_pvEnd.dY+foffy;
	}
*/	return pLine;
}
//获得此直线的方程
CLineFunction*CPowerDrawLine::GetLineFunction()
{
	CLineFunction *pLineFun=NULL;
	pLineFun=new CLineFunction;
	double fAngle=GetLineAngleVal();
	fAngle=(double)(fAngle * 180 / 3.1415927);
	pLineFun->fSlantAngle=fAngle;
	pLineFun->fbx=m_pvBegin.dX;//直线的起始点
	pLineFun->fby=m_pvBegin.dY;
	if((fAngle>=89.999 && fAngle<=90.001) || (fAngle>=269.999 && fAngle<=270.001) )
	{
		pLineFun->iType=1;	//
		pLineFun->fCoefK=99999.0f;
		pLineFun->fConstB=m_pvBegin.dX;
	}
	else
	{
		pLineFun->iType=0;
		pLineFun->fCoefK=(m_pvBegin.dY-m_pvEnd.dY)/(m_pvBegin.dX-m_pvEnd.dX);
		pLineFun->fConstB=m_pvBegin.dY - pLineFun->fCoefK*m_pvBegin.dX;
	}
	return pLineFun;
}
