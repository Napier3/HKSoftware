#pragma once

#include "ExBaseList.h"

class CExBaseListUpdateToolBase
{
public:
	CExBaseListUpdateToolBase();
	virtual ~CExBaseListUpdateToolBase();

protected:
	virtual BOOL Update_Own(CExBaseObject *pSrc, CExBaseObject *pDest);

public:
	virtual BOOL Update_ByName(CExBaseObject *pSrc, CExBaseObject *pDest);
	virtual BOOL Update_ByName(CExBaseList *pSrc, CExBaseList *pDest);

	virtual BOOL Update_ByID(CExBaseObject *pSrc, CExBaseObject *pDest);
	virtual BOOL Update_ByID(CExBaseList *pSrc, CExBaseList *pDest);

	virtual BOOL Update_ByClassID(CExBaseObject *pSrc, CExBaseObject *pDest);
	virtual BOOL Update_ByClassID(CExBaseList *pSrc, CExBaseList *pDest);
};


