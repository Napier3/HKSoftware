// DeflatePolygon.cpp: implementation of the CDeflatePolygon class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DeflatePolygon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDeflatePolygon::CDeflatePolygon()
{
	
}

CDeflatePolygon::~CDeflatePolygon()
{
	
}

void CDeflatePolygon::DeflatePolygon(POINT *pPoints, long nCount, long nX, long nY)
{
	POINT *p1 = NULL, *p2 = NULL, *p3 = NULL;
	
	for (long nIndex=0; nIndex < nCount; nIndex++)
	{
		p1 = &pPoints[nIndex];
		
		if (nIndex < nCount - 2)
		{
			p2 = &pPoints[nIndex+1];
			p3 = &pPoints[nIndex+2];
		}
		else if (nIndex == nCount-2)
		{
			p2 = &pPoints[nIndex+1];
			p3 = &pPoints[0];
		}
		else
		{
			p2 = &pPoints[0];
			p3 = &pPoints[1];
		}
		
		if (IsLeft(p1, p2, p3))
		{
			p1->x += nX;
			p2->x += nX;
		}
		else if (IsRight(p1, p2, p3))
		{
			p1->x -= nX;
			p2->x -= nX;
		}
		else if (IsTop(p1, p2, p3))
		{
			p1->y += nY;
			p2->y += nY;
		}
		else if (IsBottom(p1, p2, p3))
		{
			p1->y -= nY;
			p2->y -= nY;
		}
	}
}

//     ___________                                                         
//     |                                                         
//     |                                                         
//                                                              
BOOL CDeflatePolygon::IsLeft(POINT *p1, POINT *p2, POINT *p3)
{
	return ( (p1->x == p2->x) && (p2->y == p3->y) && (p2->x < p3->x) );
}

//     |                                                         
//     |                                                         
//  ___|                                                            
//                                                              
BOOL CDeflatePolygon::IsRight(POINT *p1, POINT *p2, POINT *p3)
{
	return ( (p1->x == p2->x) && (p2->y == p3->y) && (p2->x > p3->x) );
}

//   _________                                                       
//            |                                               
//            |                                                  
//                                                              
BOOL CDeflatePolygon::IsTop(POINT *p1, POINT *p2, POINT *p3)
{
	return ( (p1->y == p2->y) && (p2->x == p3->x) && (p1->x < p2->x) );
}

//     |                                                   
//     |                                                    
//     |___________________                                                     
//                                                              
BOOL CDeflatePolygon::IsBottom(POINT *p1, POINT *p2, POINT *p3)
{
	return ( (p1->y == p2->y) && (p2->x == p3->x) && (p1->x > p2->x) );
}

