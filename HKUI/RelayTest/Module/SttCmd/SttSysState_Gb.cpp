//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttSysState_Gb.cpp  CSttSysState_Gb


#include "stdafx.h"
#include "SttSysState_Gb.h"
#include "SttParas_Gb.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CSttSysState_Gb::CSttSysState_Gb()
{
	
}

CSttSysState_Gb::CSttSysState_Gb(const CString &strRetType)
	: CSttSysState(strRetType)
{
	
}

CSttSysState_Gb::~CSttSysState_Gb()
{
}

CBaseObject* CSttSysState_Gb::Clone()
{
	CSttSysState_Gb *p = new CSttSysState_Gb();
	Copy(p);
	return p;
}

CBaseObject* CSttSysState_Gb::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttSysState_Gb *p = new CSttSysState_Gb();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

//2023-9-9
CSttParas* CSttSysState_Gb::NewSttParas()
{
	return new CSttParas_Gb();
}

