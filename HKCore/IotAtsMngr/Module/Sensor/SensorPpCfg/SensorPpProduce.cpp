//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SensorPpProduce.cpp  CSensorPpProduce


#include "stdafx.h"
#include "SensorPpProduce.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSensorPpProduce::CSensorPpProduce()
{
	//初始化属性

	//初始化成员变量
}

CSensorPpProduce::~CSensorPpProduce()
{
}

CBaseObject* CSensorPpProduce::Clone()
{
	CSensorPpProduce *p = new CSensorPpProduce();
	Copy(p);
	return p;
}

CBaseObject* CSensorPpProduce::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSensorPpProduce *p = new CSensorPpProduce();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}