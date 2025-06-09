// XObjectRefBase.h: interface for the CXObjectRefBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_XObjectRefBase_H__)
#define _XObjectRefBase_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////////////////////////////////////
//CXObjectRefBase
class CXObjectRefBase  
{
public:
	CXObjectRefBase();
	virtual ~CXObjectRefBase();

protected:
	long m_nObjectRefCount;

//方法
public:
	virtual void AddRef();
	virtual void Release();
	long GetRefCount();
};

//2021-7-17  lijunqing
typedef CXObjectRefBase* (P_FUNC_CREATE_XOBJECT)();

//////////////////////////////////////////////////////////////////////////
//CXObjectRefDriver
class CXObjectRefDriver
{
// Constructors
public:
	CXObjectRefDriver();
	CXObjectRefDriver(P_FUNC_CREATE_XOBJECT *pFuncCreate);
	CXObjectRefDriver(CXObjectRefBase* lpXObject, BOOL bAutoRelease = TRUE);
	CXObjectRefDriver(const CXObjectRefDriver& oXobjRefSrc);

// Attributes
protected:
	CXObjectRefBase* m_lpXObject;
	BOOL m_bAutoRelease;

public:
	CXObjectRefBase* GetXObjectRef()	{	return m_lpXObject;	}
	void AttachXObject(CXObjectRefBase* lpXObject, BOOL bAutoRelease = TRUE);
	CXObjectRefBase* DetachXObject();
	
	// detach and get ownership of m_lpXObject
	void ReleaseXObject();

	// special operators
	const CXObjectRefDriver& operator=(const CXObjectRefDriver& oXobjRefSrc);

	// Implementation
public:
	virtual ~CXObjectRefDriver();

//2021-7-17  lijunqing
protected:
	P_FUNC_CREATE_XOBJECT *m_pFuncCreate;

public:
	CXObjectRefBase* New();
	virtual void AddRef();
	virtual void Release();

	//2022-10-19 lijunqing
	virtual CXObjectRefDriver* Clone();
};

//2021-7-21  lijunqing
/*
后续可以考虑将CXObjectRefDriver做成模板类，这样在使用的时候就不需要做类型强制性转换，例如：
现在是这样使用：
	CXObjectRefDriver oDriver(CSttAtsCmd::New);
	CSttAtsCmd  *pAtsCmd = (CSttAtsCmd*)oDriver.New();

改为模板类之后，就这样使用
	CXObjectRefDriver<CSttAtsCmd> oDriver(CSttAtsCmd::New);
	CSttAtsCmd  *pAtsCmd = oDriver.New();

各有利弊，暂时不考虑修改
*/

#endif // !defined(_XObjectRefBase_H__)
