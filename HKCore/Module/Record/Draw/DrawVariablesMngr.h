// DrawVariablesMngr.h: interface for the CDrawVariablesMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DRAWVARIABLESMNGR_H__)
#define _DRAWVARIABLESMNGR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DrawBaseList.h"

class CDrawVariablesMngr : public CDrawBaseList  
{
public:
	virtual UINT GetClassID() {	return DRAWCLASSID_VARIABLESMNGR;	}
public:
	CDrawVariablesMngr();
	virtual ~CDrawVariablesMngr();
};

#endif // !defined(_DRAWVARIABLESMNGR_H__)
