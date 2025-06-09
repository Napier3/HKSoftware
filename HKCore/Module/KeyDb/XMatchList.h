//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XMatchList.h  CXMatchList

#pragma once

#include "XMatchObject.h"



class CXMatchList : public CExBaseList
{
public:
	CXMatchList();
	virtual ~CXMatchList();

	virtual void FreeMatch();
	virtual void Match(CXMatchList *pMachList, long nMatchRatio, CThreadProgressInterface *pThradProgress, BOOL bUseFullMatchString);
	virtual void Init(CExBaseList *pListRefObj, CXKeyDB *pKeyDb, CThreadProgressInterface *pThradProgress=NULL);

	virtual void AddMatch(CXMatchList *pMachList, long nMatchRatio, CThreadProgressInterface *pThradProgress, BOOL bFreeMatchList, BOOL bUseFullMatchString);
	virtual void FilterMatch(CXMatchList *pMachList, long nMatchRatio);
//重载函数
public:
	virtual UINT GetClassID() {    return KDBCLASSID_CXMATCHLIST;   }

//私有成员变量
private:
	CExBaseList *m_pListRefObject;

//私有成员变量访问方法
public:
	CExBaseList* GetListRefObject()	{	return m_pListRefObject;	}
	virtual BOOL IsXMatchValid();
	virtual BOOL IsXMatchValid_LEqual_1();

protected:
	virtual void FilterMatch(long nMatchRatio);
	virtual void FilterMatch(CXMatchList *pList);
	
	virtual CXMatchObject* CreateMatchObject(CExBaseObject *pRefObj, CXKeyDB *pKeyDb);
};

