//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IeCXBinaryDrawGlobal.cpp

#include "stdafx.h"
#include "XBINARYDrawGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CXBinaryDrawXmlRWKeys

CXBinaryDrawXmlRWKeys* CXBinaryDrawXmlRWKeys::g_pXmlKeys = NULL;
long CXBinaryDrawXmlRWKeys::g_nCFGRef = 0;

CXBinaryDrawXmlRWKeys::CXBinaryDrawXmlRWKeys()
{
	

}

CXBinaryDrawXmlRWKeys::~CXBinaryDrawXmlRWKeys()
{
}

CXBinaryDrawXmlRWKeys* CXBinaryDrawXmlRWKeys::Create()
{
	g_nCFGRef++;

	if (g_nCFGRef == 1)
	{
		g_pXmlKeys = new CXBinaryDrawXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CXBinaryDrawXmlRWKeys::Release()
{
	g_nCFGRef--;

	if (g_nCFGRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CXBinaryDrawConstGlobal

long CXBinaryDrawConstGlobal::g_nGlobalRef = 0;
CXBinaryDrawConstGlobal* CXBinaryDrawConstGlobal::g_pGlobal = NULL;

CXBinaryDrawConstGlobal::CXBinaryDrawConstGlobal()
{

	//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()
	InitGlobal();
}

CXBinaryDrawConstGlobal::~CXBinaryDrawConstGlobal()
{
}

CXBinaryDrawConstGlobal* CXBinaryDrawConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CXBinaryDrawConstGlobal();
	}

	return g_pGlobal;
}

void CXBinaryDrawConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

void CXBinaryDrawConstGlobal::InitGlobal()
{

}
//定义全局常量管理对象初始化函数，

//定义全局常量，例如

long g_nBinaryDrawColsCalUseHex_16 = 1;

long binary_draw_cal_cols(long nWidth, long nBinaryWidth)
{
	long nCols = nWidth / nBinaryWidth;

	if (g_nBinaryDrawColsCalUseHex_16 == 1)
	{
		long nCountOf_8 = nCols / 8;
		nCols = nCountOf_8 * 8;
	}

	return nCols;
}

long binary_draw_cal_cols_rows(long nButtons, long nWidth, long nBinaryWidth, long &nCols, long &nRows)
{
	nCols = nWidth / nBinaryWidth;

	if (g_nBinaryDrawColsCalUseHex_16 == 1)
	{
		long nCountOf_8 = nCols / 8;
		nCols = nCountOf_8 * 8;
	}

	nRows = nButtons / nCols;

	if (nRows * nCols < nButtons)
	{
		nRows++;
	}

	return nCols * nCols;
}

