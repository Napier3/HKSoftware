// AtlBaseObject.h: interface for the CAtlBaseObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_ATLBASEOBJECT_H__)
#define _ATLBASEOBJECT_H__


class  CAtlBaseObject
{
public:
	CAtlBaseObject();
	virtual ~CAtlBaseObject();

	virtual CAtlBaseObject* GetNewObject(BOOL bCopy=FALSE);
	
	virtual BOOL operator==(CAtlBaseObject &odTemp) ;
	virtual BOOL operator!=(CAtlBaseObject &odTemp) ;
	virtual const CAtlBaseObject & operator =(CAtlBaseObject &odTemp);

};


#endif //_ATLBASEOBJECT_H__