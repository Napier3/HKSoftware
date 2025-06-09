//TempFuncGlobal.cpp
//ÉÛÀ×

#include "stdafx.h"
#include "TempFuncGlobal.h"

//CTempFuncXmlRWFuncs

CTempFuncXmlRWFuncs* CTempFuncXmlRWFuncs::g_pXmlFuncs = NULL;
long CTempFuncXmlRWFuncs::g_nTempFuncRef = 0;

CTempFuncXmlRWFuncs::CTempFuncXmlRWFuncs()
{
	m_strCXTempFuncsTempF = L"Templates-Functions";
	m_strCXTempFuncsFunc = L"Function";
	m_strCXTempFuncsKeys = L"keys";
	m_strCXTempFuncsKey = L"key";
	m_strCXTempFuncsTemp = L"Template";
	m_strCXTempFuncsScene = L"Test-Scene";
	m_strCXTempFuncsFolder = L"Folder";

	m_strCXTempFuncsArray = L"array";

}

CTempFuncXmlRWFuncs::~CTempFuncXmlRWFuncs()
{
}

CTempFuncXmlRWFuncs* CTempFuncXmlRWFuncs::Create(CXKeyDB *pXKeyDB)
{
	g_nTempFuncRef++;

	if (g_nTempFuncRef == 1)
	{
		g_pXmlFuncs = new CTempFuncXmlRWFuncs();
		g_pXmlFuncs->m_pXKeyDB = pXKeyDB;
	}

	return g_pXmlFuncs;
}

void CTempFuncXmlRWFuncs::Release()
{
	g_nTempFuncRef--;

	if (g_nTempFuncRef == 0)
	{
		delete g_pXmlFuncs;
		g_pXmlFuncs = NULL;
	}
}

CXKeyDB* CTempFuncXmlRWFuncs::GetXKeyDB()
{
	ASSERT(g_pXmlFuncs != NULL);
	return g_pXmlFuncs->m_pXKeyDB;
}

