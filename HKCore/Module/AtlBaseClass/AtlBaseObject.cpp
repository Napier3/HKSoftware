// CAtlBaseObject.cpp: implementation of the CAtlBaseObject class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "AtlBaseObject.h"

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAtlBaseObject::CAtlBaseObject()
{
}

CAtlBaseObject::~CAtlBaseObject()
{ 
	   
}

BOOL CAtlBaseObject::operator!=(CAtlBaseObject &odTemp)
{
	if ((operator ==(odTemp))==FALSE) 
		return TRUE;
	else 
		return FALSE;
}

BOOL CAtlBaseObject::operator==(CAtlBaseObject &odTemp) 
{
	if (&odTemp==this) 
		return TRUE;
		
	return TRUE;
}
const CAtlBaseObject & CAtlBaseObject::operator =(CAtlBaseObject &odTemp)
{
	return *this;
}

CAtlBaseObject* CAtlBaseObject::GetNewObject(BOOL bCopy)
{
	CAtlBaseObject *pObj = new CAtlBaseObject();
	
	if (bCopy)
	{
		*pObj =(*this);
	}
	return pObj;
}

