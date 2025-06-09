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

//����
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
�������Կ��ǽ�CXObjectRefDriver����ģ���࣬������ʹ�õ�ʱ��Ͳ���Ҫ������ǿ����ת�������磺
����������ʹ�ã�
	CXObjectRefDriver oDriver(CSttAtsCmd::New);
	CSttAtsCmd  *pAtsCmd = (CSttAtsCmd*)oDriver.New();

��Ϊģ����֮�󣬾�����ʹ��
	CXObjectRefDriver<CSttAtsCmd> oDriver(CSttAtsCmd::New);
	CSttAtsCmd  *pAtsCmd = oDriver.New();

�������ף���ʱ�������޸�
*/

#endif // !defined(_XObjectRefBase_H__)
