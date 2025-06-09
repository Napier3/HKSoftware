// PowerDrawCircle.cpp: implementation of the CPowerDrawCircle class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerDrawCircle.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CPowerDrawCircleValue::CPowerDrawCircleValue()
{
	dOffset=0;
	dAngle=0;
	dDiameter=0;
	dA=dB=0;
}
CPowerDrawCircleValue::~CPowerDrawCircleValue()
{

}
BOOL CPowerDrawCircleValue::IsThisATrueCircle()
{
	double d=dA+dB;
	if(fabs(d-dDiameter)<=0.0001)
		return TRUE;
	else
		return FALSE;
}

IMPLEMENT_DYNCREATE(CPowerDrawCircle,CPowerDrawBaseClass)

CPowerDrawCircle::CPowerDrawCircle()
{
	m_ptCenter=CPoint(0,0);
	m_dRadius=0;
	m_iDrawModal= POWERADVANCE_UNIT_DRAW_MODE_NORMAL;
	InitIt();
}
CPowerDrawCircle::CPowerDrawCircle(CString strClass):CPowerDrawBaseClass(strClass)
{
	Init();
}
void CPowerDrawCircle::InitIt()
{
//	pArcL=new CPowerDrawArc;
//	pArcR=new CPowerDrawArc;

}

void CPowerDrawCircle::EndIt()
{
//	if(pArcL)
//		delete pArcL;
//	pArcL=NULL;
//	if(pArcR)
//		delete pArcR;
//	pArcL=NULL;
}
CPowerDrawCircle::~CPowerDrawCircle()
{
//	EndIt();
}
CRect CPowerDrawCircle::GetMinRectBOX()
{
	CRect rect;
	rect.left	=m_ptCenter.x - (int)m_dRadius;
	rect.top	=m_ptCenter.y - (int)m_dRadius;
	rect.right	=m_ptCenter.x + (int)m_dRadius;
	rect.bottom	=m_ptCenter.y + (int)m_dRadius;
	return rect;
}
BOOL CPowerDrawCircle::PickCircle(CPoint curPoint)
{
	CRect rectBox=GetMinRectBOX();
	rectBox.left = rectBox.left - POWERADVANCE_PICK_RADIUS;
	rectBox.top = rectBox.top - POWERADVANCE_PICK_RADIUS;
	rectBox.right = rectBox.right + POWERADVANCE_PICK_RADIUS;
	rectBox.bottom = rectBox.bottom + POWERADVANCE_PICK_RADIUS;
	if(!rectBox.PtInRect(curPoint)) 
	{
		return 0;
	}
	CPoint pt=m_ptCenter-curPoint;
	double dLen=sqrt(pt.x*pt.x+pt.y*pt.y);

	BOOL bPicked=0;
	if(dLen<POWERADVANCE_PICK_RADIUS)
		bPicked= 1;
	else
		bPicked= 0;
	SetPicked(bPicked);
	return bPicked;
}

void CPowerDrawCircle::Draw(CDC *pDC)
{
	CRect rectBox=GetMinRectBOX();
	CPen pen,*pPen;
	pen.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
	pPen=pDC->SelectObject(&pen);
	CGdiObject *pObj=pDC->SelectStockObject(NULL_BRUSH);
	pDC->Ellipse(rectBox);
	pDC->SelectObject(pObj);
	pDC->SelectObject(pPen);
	pen.DeleteObject();	
}
void CPowerDrawCircle::Draw(CDC *pDC,CRect rectBox)
{

	
	switch(m_iDrawModal)
	{
	case POWERADVANCE_UNIT_DRAW_MODE_NORMAL:
		{
			CPen cp,*pOldPen;
			CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);
			cp.CreatePen(m_uiLineStyle,m_iLineWidth,m_ulColor);
			pOldPen=pDC->SelectObject(&cp);
			pDC->Ellipse(rectBox);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pObj);
			cp.DeleteObject();	
			//pDC->SetROP2(dWord);
			break;
		}
	case POWERADVANCE_UNIT_DRAW_MODE_PICKED:
		{
			//DWORD dWord=pDC->SetROP2(R2_XORPEN);
			CPen cp,*pOldPen;
			CGdiObject * pObj=pDC->SelectStockObject(NULL_BRUSH);
			cp.CreatePen(m_uiPickLineStyle,m_iPickLineWidth,m_ulPickColor);
			pOldPen=pDC->SelectObject(&cp);
			pDC->Ellipse(rectBox);
			pDC->SelectObject(pOldPen);
			pDC->SelectObject(pObj);
			cp.DeleteObject();
			//pDC->SetROP2(dWord);
			break;
		}
	}
}
void CPowerDrawCircle::SetPicked(BOOL bPicked)
{
	if(bPicked)m_iDrawModal=POWERADVANCE_UNIT_DRAW_MODE_PICKED;
	else m_iDrawModal=POWERADVANCE_UNIT_DRAW_MODE_NORMAL;
}
BOOL CPowerDrawCircle::InitCircleByOnePoint(double fx,double fy)
{
	double dx,dy;
	///偏移点坐标数值
	dx=m_pdcv.dOffset * cos(m_pdcv.dAngle);
	dy=m_pdcv.dOffset * sin(m_pdcv.dAngle);
	//////////点于X轴的夹角
	double dap=0;		///点与X轴的夹角
	double dLenPt=sqrt(fx*fx+fy*fy);
	if(dLenPt<=0.0001) dap=0;
	else	dap=fabs(acos(fx/dLenPt));

	double cosdap=0;
	cosdap=cos(dap);
	if(cosdap<=0.00001) cosdap=0.00001;

	double dTwoLine=fabs(dap-m_pdcv.dAngle);	//2直线的夹角	
//	if(dTwoLine<=0.0001 || dTwoLine >=3.1415) m_dRadius=dl;
	//else	m_dRadius=dl/cos(dTwoLine);
	double dl=sqrt((fx-dx)*(fx-dx)+(fy-dy)*(fy-dy));////点到OFSSET点的距离
	m_dRadius=dl/cos(dTwoLine);		

	if(m_dRadius>=100)m_dRadius=100;

	m_pdcv.dDiameter=m_dRadius;
	m_dRadius=m_dRadius/2;

	m_pdcv.dA=-dx+m_dRadius*cos(m_pdcv.dAngle);
	m_pdcv.dB=-dy+m_dRadius*sin(m_pdcv.dAngle);
	return 1;
}

BOOL CPowerDrawCircle::InitOwnDataByString(CString strOwnData)
{
	int iBegin=0;
	int iEnd=0;
	CString strData="";
	CString strsp="=";
	CString strsp2=",";
	iBegin=strOwnData.Find(strsp);
	if(iBegin==-1)return FALSE;
	iBegin++;
	double cx=0,cy=0,cr=0;
	
	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	m_pdcv.dOffset=atof(strData);
	iBegin=iEnd+1;


	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	m_pdcv.dDiameter=atof(strData);
	iBegin=iEnd+1;

	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	m_pdcv.dAngle=atof(strData);
	iBegin=iEnd+1;

	iEnd=strOwnData.Find(strsp2,iBegin);
	if(iEnd==-1)return FALSE;
	strData=strOwnData.Mid(iBegin,iEnd-iBegin);
	m_pdcv.dA=atof(strData);
	iBegin=iEnd+1;
	
	strData=strOwnData.Mid(iBegin,strOwnData.GetLength()-iBegin);
	m_pdcv.dB=atof(strData);

	return TRUE;
}
BOOL CPowerDrawCircle::ContinueInitIt(CAxisReference *axisReference)
{
	//CPoint	m_ptCenter;	///实际的圆心坐标
	//int     m_iRadius;
//	pArcL=NULL;pArcR=NULL;
//	TRACE("CPowerDrawCircle::ContinueInitIt(CAxisReference *axisReference)\n");

	double dAngleA=0,dAngleB=0;
	double dA=m_pdcv.dA;
	double dB=m_pdcv.dB;
	double dOffset=m_pdcv.dOffset;
	double dZd=m_pdcv.dDiameter;

	double dR=(dOffset+dZd)/2;
	///////////计算张角A
	if(fabs(dA)<=0.001)dA=0.001;
	dAngleA=atan(dR/dA)*2*180/3.141593;
	////////////计算张角B
	if(fabs(dB)<=0.001)dB=0.001;
	dAngleB=atan(dR/dB)*2*180/3.141593;

	dR=(dZd-dOffset)/2;
	double dPI=3.141593/2;
	double dxc,dyc,dTheta,dxa,dxb,dya,dyb;
	double dxOff,dyOff,dxZd,dyZd;
	dTheta=m_pdcv.dAngle*3.14159/180;
	dxc=dR*cos(dTheta);				dyc=dR*sin(dTheta);
	dxa=dxc-dA*cos(dPI-dTheta);		dya=dyc+dA*sin(dPI-dTheta);
	dxb=dxc+dB*cos(dPI-dTheta);		dyb=dyc-dB*sin(dPI-dTheta);
	dxOff=-dOffset*cos(dTheta);		dyOff=-dOffset*sin(dTheta);
	dxZd=dZd*cos(dTheta);			dyZd=dZd*sin(dTheta);


	CPowerPointValue	ppvA,ppvB,ppvOff,ppvZd;
	ppvA.dX=dxa;ppvA.dY=dya;
	ppvB.dX=dxb;ppvB.dY=dyb;
	ppvOff.dX=dxOff;ppvOff.dY=dyOff;
	ppvZd.dX=dxZd;ppvZd.dY=dyZd;
//	pArcL->SetArcValues(ppvZd,ppvA,ppvOff);
//	pArcR->SetArcValues(ppvOff,ppvB,ppvZd);
//	pArcL->ContinueInitIt(axisReference);
//	pArcR->ContinueInitIt(axisReference);
	pArcL.SetArcValues(ppvZd,ppvA,ppvOff);
	pArcR.SetArcValues(ppvOff,ppvB,ppvZd);
	pArcL.ContinueInitIt(axisReference);
	pArcR.ContinueInitIt(axisReference);

	return TRUE;
}
CString CPowerDrawCircle::GetExportTextString(void)
{
	return "";
}
CString  CPowerDrawCircle::GetDisplayDataString(void)
{
	CString strData="";
	CString strTemp="";
	CString strNewLine="00";	strNewLine.SetAt(0,13);	strNewLine.SetAt(1,10);	
	strData="CIRCLE=";
	strTemp.Format("%.3f,",m_pdcv.dOffset);		strData+=strTemp;
	strTemp.Format("%.3f,",m_pdcv.dDiameter);		strData+=strTemp;
	strTemp.Format("%.3f,",m_pdcv.dAngle);		strData+=strTemp;
	strTemp.Format("%.3f,",m_pdcv.dA);			strData+=strTemp;
	strTemp.Format("%.3f;",m_pdcv.dB);			strData+=strTemp;

	CString strTab="					";
	strData=strTab+strData;
	strData+=strNewLine;
	return strData;
}

CPowerDrawBaseClass* CPowerDrawCircle::DirectGetNewObject()
{
	CPowerDrawBaseClass*pc=new CPowerDrawCircle;
	pc->strClassName=strClassName;
	return pc;
}
void CPowerDrawCircle::DrawIt(CDC *pDC,BOOL bSel,double fZoomRatio,CPoint ptOffset)
{
//	TRACE("CPowerDrawCircle::DrawIt(CDC *pDC)\n\n");
//	pArcL->DrawIt(pDC,bSel);
//	pArcR->DrawIt(pDC,bSel);
	pArcL.DrawIt(pDC,bSel,fZoomRatio,ptOffset);
	pArcR.DrawIt(pDC,bSel,fZoomRatio,ptOffset);
//	EndIt();
}

BOOL CPowerDrawCircle::PickIt(CPoint point)
{
	return TRUE;
}

void CPowerDrawCircle::GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	double dA=m_pdcv.dA;
	double dB=m_pdcv.dB;
	double dOffset=m_pdcv.dOffset;
	double dZd=m_pdcv.dDiameter;

	double dR=dOffset+dZd;
	if(dA+dB==dR)
	{
		double frr=dR/2;
		dR=(dZd-dOffset)/2;
		double fcx,fcy;
		double dTheta=(double)(m_pdcv.dAngle*3.141592654/180.0f);
		fcx=dR*cos(dTheta);
		fcy=dR*sin(dTheta);
		if(fMinX>fcx-frr)fMinX=fcx-frr;
		if(fMaxX<fcx+frr)fMaxX=fcx+frr;
		if(fMinY>fcy-frr)fMinY=fcx-frr;
		if(fMaxY<fcy+frr)fMaxY=fcy+frr;
	}
	else
	{
		pArcL.GetMinOuterValue(fMinX,fMinY,fMaxX,fMaxY);
		pArcR.GetMinOuterValue(fMinX,fMinY,fMaxX,fMaxY);
	}
}
BOOL CPowerDrawCircle::IsPointTheJustPoint(CLineFunction*pLF,double fx,double fy)
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
void CPowerDrawCircle::GetCircleIntersetPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal)
{
	iIntersetNum=0;
	double dPI=3.141593f;

	double fX0,fY0;	//圆心坐标
	double fRadius;	//圆半径
	//double fK=pLF->fCoefK;
	double dR=(m_pdcv.dOffset+m_pdcv.dDiameter)/2;
	fRadius=dR;		//获取圆半径
	dR=(-m_pdcv.dOffset+m_pdcv.dDiameter)/2;
	double dTheta=m_pdcv.dAngle*dPI/180;
	fX0=dR*cos(dTheta);	fY0=dR*sin(dTheta);//////////////获取圆心的坐标
	////////////////////////////////////////////////////////////////////////////
	//		解方程
	CPointValueObject *ppvo;
	double fintx=0,finty=0;
	double fintx1=0,finty1=0;
	double fAngle=0;
	double fErrorx=0,fErrory=0;
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
					iIntersetNum=2;
					fAngle=GetPVAngle(fintx,finty);
					fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx+fErrorx;ppvo->dY=finty+fErrory;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx-fErrorx;ppvo->dY=finty-fErrory;
					listIntersect.AddTail(ppvo);
				}
				else{ppvo=NULL;iIntersetNum=0;}//反方向
			}
			else//如果x0-R < b < x0+R
			{	//x=b		y=y0 ± sqrt( R*R - (b-x0)*(b-x0) )
				double fx=fRadius;
				double fy=pLF->fConstB-fX0; 
				double fhypot=hypot(fx,fy);
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

					fAngle=GetPVAngle(fintx,finty);
					fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx+fErrorx;ppvo->dY=finty+fErrory;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx-fErrorx;ppvo->dY=finty-fErrory;
					listIntersect.AddTail(ppvo);
					////////////////////////////////////////////
					finty=fY0-fhypot;

					fAngle=GetPVAngle(fintx,finty);
					fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx+fErrorx;ppvo->dY=finty+fErrory;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx-fErrorx;ppvo->dY=finty-fErrory;
					listIntersect.AddTail(ppvo);
				}
				else//(iIntersetNum==1)	一个点都在正方向
				{
					finty=fY0+fhypot;
					if(IsPointTheJustPoint(pLF,fintx,finty)){}
					else{finty=fY0-fhypot;		}

					fAngle=GetPVAngle(fintx,finty);
					fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx+fErrorx;ppvo->dY=finty+fErrory;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx-fErrorx;ppvo->dY=finty-fErrory;
					listIntersect.AddTail(ppvo);
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
				iIntersetNum=1;
				fAngle=GetPVAngle(fintx,finty);
				fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
				ppvo=new CPointValueObject;
				ppvo->dX=fintx+fErrorx;ppvo->dY=finty+fErrory;
				listIntersect.AddTail(ppvo);
				ppvo=new CPointValueObject;
				ppvo->dX=fintx-fErrorx;ppvo->dY=finty-fErrory;
				listIntersect.AddTail(ppvo);
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
					fAngle=GetPVAngle(fintx,finty);
					fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx+fErrorx;ppvo->dY=finty+fErrory;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx-fErrorx;ppvo->dY=finty-fErrory;
					listIntersect.AddTail(ppvo);
				}
				else
				{
					fAngle=GetPVAngle(fintx1,finty1);
					fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx1+fErrorx;ppvo->dY=finty1+fErrory;
					listIntersect.AddTail(ppvo);
					ppvo=new CPointValueObject;
					ppvo->dX=fintx1-fErrorx;ppvo->dY=finty1-fErrory;
					listIntersect.AddTail(ppvo);
				}
			}
			else
			{
				fAngle=GetPVAngle(fintx,finty);
				fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
				ppvo=new CPointValueObject;
				ppvo->dX=fintx+fErrorx;ppvo->dY=finty+fErrory;
				listIntersect.AddTail(ppvo);
				ppvo=new CPointValueObject;
				ppvo->dX=fintx-fErrorx;ppvo->dY=finty-fErrory;
				listIntersect.AddTail(ppvo);

				fAngle=GetPVAngle(fintx1,finty1);
				fErrorx=fErrorVal*cos(fAngle);		fErrory=fErrorVal*sin(fAngle);
				ppvo=new CPointValueObject;
				ppvo->dX=fintx1+fErrorx;ppvo->dY=finty1+fErrory;
				listIntersect.AddTail(ppvo);
				ppvo=new CPointValueObject;
				ppvo->dX=fintx1-fErrorx;ppvo->dY=finty1-fErrory;
				listIntersect.AddTail(ppvo);
			}
		}
	}
}
void CPowerDrawCircle::GetArcIntersetPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal)
{
	pArcL.GetIntersectPV(pLF,iIntersetNum,listIntersect,fErrorVal);
	pArcR.GetIntersectPV(pLF,iIntersetNum,listIntersect,fErrorVal);
}
//获得圆上一点的角度
double CPowerDrawCircle::GetPVAngle(double fx,double fy)
{
	double dPI=3.141593f;
	double fX0,fY0;	//圆心坐标
	double dR=(m_pdcv.dOffset+m_pdcv.dDiameter)/2;
	dR=(-m_pdcv.dOffset+m_pdcv.dDiameter)/2;
	double dTheta=m_pdcv.dAngle*dPI/180;
	fX0=dR*cos(dTheta);	fY0=dR*sin(dTheta);//////////////获取圆心的坐标
	double fYLen=fy-fY0;
	double fXLen=fx-fX0;
	double dLen=sqrt(fYLen*fYLen+fXLen*fXLen);
	if(dLen==0) return 0;
	double dAngle=acos(fXLen/dLen);
	if(fYLen<0)dAngle=3.1415927*2-dAngle;
	return (double)dAngle;
}
void CPowerDrawCircle::GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal)
{
	double dA=m_pdcv.dA;
	double dB=m_pdcv.dB;
	double dOffset=m_pdcv.dOffset;
	double dZd=m_pdcv.dDiameter;

	double dR=dOffset+dZd;
	if(dA+dB==dR)
		GetCircleIntersetPV(pLF,iIntersetNum,listIntersect,fErrorVal);
	else
		GetArcIntersetPV(pLF,iIntersetNum,listIntersect,fErrorVal);
}
void CPowerDrawCircle::OnColorChanged(COLORREF color)
{
	pArcL.OnColorChanged(color);
	pArcR.OnColorChanged(color);
}

//定义误差线的求取函数
CString	CPowerDrawCircle::GetErrorString(double fOffVal)
{
	CString strError="";
	if(fOffVal==0)
		return GetDisplayDataString();
	CPowerDrawArc parc1,parc2;
	double dA=m_pdcv.dA;
	double dB=m_pdcv.dB;
	double dOffset=m_pdcv.dOffset;
	double dZd=m_pdcv.dDiameter;
	if(dA<=fOffVal || dB<=fOffVal )
		if(fOffVal<0)			return "";
	double dR=dOffset+dZd;
	if(dA+dB==dR)
	{
		dA+=fOffVal;		dB+=fOffVal;
		dOffset+=fOffVal;		dZd+=fOffVal;
	}
	else
	{
		if(fOffVal>0)
		{
			dR/=2;
			double frr=m_pdcv.dA / 2 + dR*dR/2/m_pdcv.dA;
			dA+=fOffVal;			dB+=fOffVal;
			frr+=fOffVal;
			double fdr2=sqrt(frr*dA*2 - dA*dA);
			fdr2=fdr2-dR;
			dOffset+=fdr2;		dZd+=fdr2;
		}
		else
		{
			dR/=2;
			double frr=m_pdcv.dA / 2 + dR*dR/2/m_pdcv.dA;
			dA+=fOffVal;			dB+=fOffVal;
			frr+=fOffVal;
			double fdr2=sqrt(frr*dA*2 - dA*dA);
 			fdr2=dR-fdr2;
			dOffset-=fdr2;			dZd-=fdr2;
		}
	}
	CString strData="";
	CString strTemp="";
	strData="CIRCLE=";
	strTemp.Format("%.3f,",dOffset);		strData+=strTemp;
	strTemp.Format("%.3f,",dZd);		strData+=strTemp;
	strTemp.Format("%.3f,",m_pdcv.dAngle);		strData+=strTemp;
	strTemp.Format("%.3f,",dA);			strData+=strTemp;
	strTemp.Format("%.3f;",dB);			strData+=strTemp;
	return strData;
}


