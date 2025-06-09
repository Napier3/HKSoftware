//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLineBase.cpp  CCharElementLineBase


#include "stdafx.h"
#include "CharElementLineBase.h"
#include "CharacteristicTmplate.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceAts.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCharElementLineBase::CCharElementLineBase()
{

}

CCharElementLineBase::~CCharElementLineBase()
{
}

void CCharElementLineBase::GetLine(double &xb, double &yb, double &xe, double &ye)
{
	if (m_pDataRef != NULL)
	{
		CXDrawLine *pLine = (CXDrawLine*)m_pDataRef;
		xb = pLine->m_fXb;
		yb = pLine->m_fYb;
		xe = pLine->m_fXe;
		ye = pLine->m_fYe;
	}
	else
	{
		xb = m_fXb;
		yb = m_fYb;
		xe = m_fXe;
		ye = m_fYe;
	}
}

void CCharElementLineBase::CalTestLines_Plumb()
{
	if (m_pDataRef == NULL)
	{
		return;
	}

	CalTestLines_Plumb_Line((CXDrawLine*)m_pDataRef);
}

double line_cal_y(double xb, double yb, double xe, double ye, double x)
{
	double y = 0;

	if ( fabs(xb - xe) <= 0.00000001)
	{
		y = (yb + ye) / 2;
	}
	else
	{
		double k = (ye - yb) / (xe - xb);
		y = k * (x - xb) + yb;
	}

	return y;
}

void CCharElementLineBase::CalTestLines_Vert()
{
	double  fXb, fYb,fXe ,fYe;
	GetLine(fXb, fYb, fXe, fYe);

	double dX = fXe - fXb;
	double dY = fYe - fYb;

	double dErrorLen = GetErrorLength();
	//dErrorLen /= 2;

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);

		if (pTestLine->IsTestLineUserDef())
		{
			dX = pTestLine->m_fPos;
			dY = line_cal_y(fXb, fYb, fXe, fYe, pTestLine->m_fPos);
		}
		else
		{
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;
		}

		pTestLine->m_fXset = dX;
		pTestLine->m_fYset = dY;

		pTestLine->m_fXb = dX ;
		pTestLine->m_fYb = dY + dErrorLen;

		pTestLine->m_fXe = dX;
		pTestLine->m_fYe = dY - dErrorLen;
	}
}

void CCharElementLineBase::CalTestLines_Horz()
{
	double  fXb, fYb,fXe ,fYe;
	GetLine(fXb, fYb, fXe, fYe);

	double dX = fXe - fXb;
	double dY = fYe - fYb;

	double dErrorLen = GetErrorLength();
	//dErrorLen /= 2;

	POS pos = GetHeadPosition();
	CCharElementTestLine *pTestLine = NULL;
	double dXg = dX / (m_nTestPoints + 1);
	double dYg = dY / (m_nTestPoints + 1);

	while (pos != NULL)
	{
		pTestLine = (CCharElementTestLine *)GetNext(pos);

		if (pTestLine->IsTestLineUserDef())
		{
			dX = fXb + (pTestLine->m_fPos - fYb) * dXg;
			dY =pTestLine->m_fPos;
		}
		else
		{
			dX = fXb + pTestLine->m_fPos * dXg;
			dY = fYb + pTestLine->m_fPos * dYg;
		}

		pTestLine->m_fXset = dX;
		pTestLine->m_fYset = dY;

		pTestLine->m_fXb = dX + dErrorLen ;
		pTestLine->m_fYb = dY;

		pTestLine->m_fXe = dX - dErrorLen;
		pTestLine->m_fYe = dY;
	}
}

CXDrawDataBase* CCharElementLineBase::GetCXDrawDataBase()
{
	return this;
}


CXDrawBase* CCharElementLineBase::CreateDrawElement()
{	
// 	if (m_pDataRef != NULL)
// 	{
// 		return (CXDrawBase*)m_pDataRef;
// 	}

	CXDrawLine *pNew = new CXDrawLine();
	CXDrawData_Line::DataCopy(pNew);
	m_pDataRef = pNew;	

	return (CXDrawBase*)m_pDataRef;
}

