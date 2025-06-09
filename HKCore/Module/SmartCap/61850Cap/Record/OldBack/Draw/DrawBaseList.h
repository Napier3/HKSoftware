// DrawBaseList.h: interface for the CDrawBaseList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWBASELIST_H__9124124E_6A54_4A1F_A94D_18AD09611199__INCLUDED_)
#define AFX_DRAWBASELIST_H__9124124E_6A54_4A1F_A94D_18AD09611199__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBase.h"
#include "..\..\..\..\..\Module\BaseClass\TLinkList.h"


class CDrawBaseList  : public CDrawBase , public CTLinkList<CDrawBase> 
{
public:
	CDrawBaseList();
	virtual ~CDrawBaseList();

//·½·¨
public:
	virtual void Append(CDrawBaseList &oListSrc);
	virtual void Append(CDrawBaseList *pListSrc)			{	Append(*pListSrc);			}

public:
	virtual CDrawBase* GetNextByObj(CDrawBase* pData);
	virtual CDrawBase* GetPrevByObj(CDrawBase* pData);
	
};

#endif // !defined(AFX_DRAWBASELIST_H__9124124E_6A54_4A1F_A94D_18AD09611199__INCLUDED_)
