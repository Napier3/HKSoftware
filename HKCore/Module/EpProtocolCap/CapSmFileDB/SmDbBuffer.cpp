//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SmDbBuffer.cpp  CSmDbBuffer


#include "stdafx.h"
#include "SmDbBuffer.h"

CSmDbBuffer::CSmDbBuffer()
{
	//初始化属性

	//初始化成员变量
}

CSmDbBuffer::~CSmDbBuffer()
{
}

BOOL CSmDbBuffer::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSmDbBuffer *p = (CSmDbBuffer*)pObj;

	return TRUE;
}

BOOL CSmDbBuffer::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSmDbBuffer *p = (CSmDbBuffer*)pDest;

	return TRUE;
}

CBaseObject* CSmDbBuffer::Clone()
{
	CSmDbBuffer *p = new CSmDbBuffer();
	Copy(p);
	return p;
}

