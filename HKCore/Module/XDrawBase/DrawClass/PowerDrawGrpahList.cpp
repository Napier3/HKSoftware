// PowerDrawGrpahList.cpp: implementation of the CPowerDrawGrpahList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerDrawGrpahList.h"
#include "PDBaseApp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPowerDrawGrpahList::CPowerDrawGrpahList()
{
	odDrawGrpahList.EndIt();
}

CPowerDrawGrpahList::~CPowerDrawGrpahList()
{
	odDrawGrpahList.EndIt();
}
CString CPowerDrawGrpahList::GetOneDrawString(CString strDraw)
{
	strDraw.TrimLeft();
	strDraw.TrimRight();
	CString strFind="=";
	CString strClass="";
	int iBegin=strDraw.Find(strFind,0);
	if(iBegin>0)
		strClass=strDraw.Left(iBegin);
	return strClass;
}

void CPowerDrawGrpahList::InitDrawGraphData(CString strGraph)
{
	CString strSp1=";";
	::DeleteLpstr(&strGraph);
	int iBegin=0;
	int iEnd=0;
	CString strData="";
	while(1)
	{
		iEnd=strGraph.Find(strSp1,iBegin);
		if(iEnd==-1)	break;
			
		strData=strGraph.Mid(iBegin,iEnd-iBegin);
		CString strClass=GetOneDrawString(strData);//得到绘图的种类
		CPDBaseApp*pApp=(CPDBaseApp*)AfxGetApp();
		CPowerDrawBaseClass *odNew=pApp->GetDrawClassByClassName(strClass);
		if(!odNew)
		{	
			iBegin=iEnd+1;
			continue;
		}
		CPowerDrawBaseClass *odTemp=odNew->DirectGetNewObject();
		if(odTemp->InitOwnDataByString(strData))
		{
			odDrawGrpahList.AddTail(odTemp);
		}
		else
		{
			delete odTemp;odTemp=NULL;
		}
		iBegin=iEnd+1;
	}
}
/*
void CPowerDrawGrpahList::InitDrawGraphData2(CString strGraph)
{
	CString strSp1=")";
	::DeleteLpstr(&strGraph);
	int iBegin=0;
	int iEnd=0;
	CString strData="";
	while(1)
	{
		iEnd=strGraph.Find(strSp1,iBegin);
		if(iEnd==-1)	break;
			
		strData=strGraph.Mid(iBegin,iEnd-iBegin);
		CString strClass=GetOneDrawString(strData);//得到绘图的种类
		CPDBaseApp*pApp=(CPDBaseApp*)AfxGetApp();
		CPowerDrawBaseClass *odNew=pApp->GetDrawClassByClassName(strClass);
		if(!odNew)
		{	
			iBegin=iEnd+1;
			continue;
		}
		CPowerDrawBaseClass *odTemp=odNew->DirectGetNewObject();
		if(odTemp->InitOwnDataByString(strData))
		{
			odDrawGrpahList.AddTail(odTemp);
		}
		else
		{
			delete odTemp;odTemp=NULL;
		}
		iBegin=iEnd+1;
	}
}
*/
void CPowerDrawGrpahList::DrawIt(CDC *pDC,BOOL bSel,double fZoomRatio,CPoint ptOffset)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
			od->DrawIt(pDC,bSel,fZoomRatio,ptOffset);
	}
}

BOOL CPowerDrawGrpahList::ContinueInitIt(CAxisReference *axisReference)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
			od->ContinueInitIt(axisReference);
	}
	return TRUE;
}

CString CPowerDrawGrpahList::GetExportTextString(void)
{
	return "";
}
CString  CPowerDrawGrpahList::GetDisplayDataString(void)
{
	CString strData="";
	CString strTemp="";
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
		{
			strTemp=od->GetDisplayDataString();
			strData+=strTemp;
		}
	}
	return strData;
}
void  CPowerDrawGrpahList::BeforePrinting(double fMMValue)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
		{
			od->BeforePrinting(fMMValue);
		}
	}	
}

BOOL CPowerDrawGrpahList::PickIt(CPoint point)
{
	return TRUE;
}

CPowerDrawBaseClass*CPowerDrawGrpahList::PickIt(CPoint point,BOOL &bPicked)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	CPowerDrawBaseClass*pPickUnit=NULL;
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
		{
			if(od->PickIt(point))
			{
				bPicked=TRUE;
				pPickUnit=od;
				break;
			}
		}
	}	
	return pPickUnit;
}
CPowerDrawBaseClass*CPowerDrawGrpahList::PickIt(CPoint point,BOOL &bPicked,int &iPicIndex)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	CPowerDrawBaseClass*pPickUnit=NULL;
	iPicIndex=0;
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		iPicIndex++;
		if(od)
		{
			if(od->PickIt(point))
			{
				bPicked=TRUE;
				pPickUnit=od;
				break;
			}
		}
	}	
	return pPickUnit;
}
CPowerDrawBaseClass*CPowerDrawGrpahList::PickIt(int iIndex)
{
	POSITION pos;//=odDrawGrpahList.GetHeadPosition();
	int iCount=odDrawGrpahList.GetCount();
	if(iCount<=iIndex)
		return NULL;
	pos=odDrawGrpahList.FindIndex(iIndex);
	CPowerDrawBaseClass*pdbc=(CPowerDrawBaseClass*)odDrawGrpahList.GetAt(pos);
	return pdbc;
}

BOOL CPowerDrawGrpahList::RemoveUnit(int iIndex)
{
	if(iIndex<0)return FALSE;
	int iCount=odDrawGrpahList.GetCount();
	if(iCount<=iIndex)
		return FALSE;
	POSITION pos=odDrawGrpahList.FindIndex(iIndex);
	CPowerDrawBaseClass*pdbc=(CPowerDrawBaseClass*)odDrawGrpahList.GetAt(pos);
	odDrawGrpahList.RemoveAt(pos);
	delete pdbc;
	pdbc=NULL;
	return TRUE;
}

void CPowerDrawGrpahList::GetMinOuterValue(double &fMinX,double &fMinY,double &fMaxX,double &fMaxY)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
		{
			od->GetMinOuterValue(fMinX,fMinY,fMaxX,fMaxY);
		}
	}
}

BOOL CPowerDrawGrpahList::GetIntersectPV(CLineFunction*pLF,int &iIntersetNum,CPDBaseObjectList &listIntersect,double fErrorVal)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
		{
			od->GetIntersectPV(pLF,iIntersetNum,listIntersect,fErrorVal);	
		}
	}
	return TRUE;
}

void CPowerDrawGrpahList::OnColorChanged(COLORREF color)
{
	POSITION pos=odDrawGrpahList.GetHeadPosition();
	while(pos)
	{
		CPowerDrawBaseClass*od=(CPowerDrawBaseClass*)odDrawGrpahList.GetNext(pos);
		if(od)
		{
			od->OnColorChanged(color);
		}
	}
}


