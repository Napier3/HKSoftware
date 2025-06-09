//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbBaseList.cpp  CSmDbBaseList


#include "stdafx.h"
#include "SmDbBaseList.h"

CSmDbBaseList::CSmDbBaseList()
{
	//初始化属性

	//初始化成员变量
}

CSmDbBaseList::~CSmDbBaseList()
{
}

long CSmDbBaseList::SmReadChildren(CShareMemClientEx &oSm)
{
	CSmDbBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nClassID = 0;
	long nCount = 0;
	long nIndex = 0;
	oSm >> nCount;
		
	for (nIndex=0;nIndex<nCount;nIndex++)
	{
		oSm >> nClassID;
		pObj = (CSmDbBaseObject*)CreateNewChild(nClassID);
		ASSERT (pObj != NULL);
		pObj->SetParent(this);
		pObj->SmRead(oSm);
		AddTail(pObj);
	}
	
	return 0;
}

long CSmDbBaseList::SmWriteChildren(CShareMemClientEx &oSm)
{
	CSmDbBaseObject *pObj = NULL;
	POS pos = GetHeadPosition();
	long nClassID = 0;
	long nCount = 0;
	long nIndex = 0;
	nCount = GetCount();
	
	oSm << nCount;
	
	while (pos)
	{
		pObj = (CSmDbBaseObject*)GetNext(pos);
		nClassID = pObj->GetClassID();
		oSm << nClassID;
		pObj->SmWrite(oSm);
	}

	return 0;
}
