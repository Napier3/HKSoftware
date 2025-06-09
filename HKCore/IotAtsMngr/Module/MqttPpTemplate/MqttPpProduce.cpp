//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//MqttPpProduce.cpp  CMqttPpProduce


#include "stdafx.h"
#include "MqttPpProduce.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMqttPpProduce::CMqttPpProduce()
{
	//初始化属性

	//初始化成员变量
}

CMqttPpProduce::~CMqttPpProduce()
{
}


BOOL CMqttPpProduce::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CMqttPpPrase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CMqttPpProduce *p = (CMqttPpProduce*)pObj;

	return TRUE;
}

BOOL CMqttPpProduce::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CMqttPpPrase::CopyOwn(pDest);

	CMqttPpProduce *p = (CMqttPpProduce*)pDest;

	return TRUE;
}

CBaseObject* CMqttPpProduce::Clone()
{
	CMqttPpProduce *p = new CMqttPpProduce();
	Copy(p);
	return p;
}

CBaseObject* CMqttPpProduce::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CMqttPpProduce *p = new CMqttPpProduce();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CMqttPpProduce::CanPaste(UINT nClassID)
{
	return FALSE;
}