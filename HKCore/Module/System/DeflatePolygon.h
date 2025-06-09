// DeflatePolygon.h: interface for the CDeflatePolygon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(DEFLATEPOLYGON_H__)
#define DEFLATEPOLYGON_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDeflatePolygon  
{
public:
	CDeflatePolygon();
	virtual ~CDeflatePolygon();

	void DeflatePolygon(POINT *pPoints, long nCount, long nX, long nY);

private:
	BOOL IsLeft(POINT *p1, POINT *p2, POINT *p3);
	BOOL IsRight(POINT *p1, POINT *p2, POINT *p3);
	BOOL IsTop(POINT *p1, POINT *p2, POINT *p3);
	BOOL IsBottom(POINT *p1, POINT *p2, POINT *p3);
};

#endif // !defined(DEFLATEPOLYGON_H__)
