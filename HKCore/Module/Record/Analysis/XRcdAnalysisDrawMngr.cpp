// XRcdAnalysisDrawMngr.cpp: implementation of the CXRcdAnalysisDrawMngr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XRcdAnalysisDrawMngr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
//CXRcdAnalysisDrawMngr
CXRcdAnalysisDrawMngr::CXRcdAnalysisDrawMngr()
{
	

}

CXRcdAnalysisDrawMngr::~CXRcdAnalysisDrawMngr()
{
	
}


CExBaseObject* CXRcdAnalysisDrawMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CXDrawXmlRWKeys *pXmlKeys = (CXDrawXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCXDrawListKey)
	{
		return new CXDrawList();
	}

	return CXDrawMngr::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}

CExBaseObject* CXRcdAnalysisDrawMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DWCLASSID_CXDRAWLIST)
	{
		return new CXDrawList();
	}

	return NULL;
	//return CXDrawMngr::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);;
}

void CXRcdAnalysisDrawMngr::InitAxis()
{

}

void CXRcdAnalysisDrawMngr::AdjustAxis(BOOL bUseMngrAxisRange)
{

}

void CXRcdAnalysisDrawMngr::ResetAxis()
{

}

void CXRcdAnalysisDrawMngr::SetAxisRange(double &dXMin, double &dYMin, double &dXMax, double &dYMax)
{

}

void CXRcdAnalysisDrawMngr::GetAxisInterface(CAxisInterface **ppAxisInterface)
{

}


void CXRcdAnalysisDrawMngr::DevicePointToLogicPoint(const CPoint &point, double &dX, double &dY)
{

}

void CXRcdAnalysisDrawMngr::DevicePointToLogicPoint(const CPoint &point, double *dX, double *dY)
{

}

void CXRcdAnalysisDrawMngr::DrawAxis(CDC *pDC)
{

}

