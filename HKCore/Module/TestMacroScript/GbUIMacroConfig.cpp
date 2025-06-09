//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//GbUIMacroConfig.cpp  CGbUIMacroConfig


#include "stdafx.h"
#include "GbUIMacroConfig.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CGbUIMacroConfig* CGbUIMacroConfig::g_pGbUIMacroConfig = NULL;
long CGbUIMacroConfig::g_nRef = 0;

CGbUIMacroConfig* CGbUIMacroConfig::Create()
{
	g_nRef++;

	if (g_nRef == 1)
	{
		g_pGbUIMacroConfig = new CGbUIMacroConfig();
	}

	return g_pGbUIMacroConfig;
}

void CGbUIMacroConfig::Release()
{
	if (g_nRef == 0)
	{
		return;
	}

	g_nRef--;

	if (g_nRef == 0)
	{
		delete g_pGbUIMacroConfig;
		g_pGbUIMacroConfig = NULL;
	}
}

CGbUIMacroConfig::CGbUIMacroConfig()
{
	//初始化属性

	//初始化成员变量
}

CGbUIMacroConfig::~CGbUIMacroConfig()
{
}

long CGbUIMacroConfig::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CGbUIMacroConfig::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CGbUIMacroConfig::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CGbUIMacroConfig *p = (CGbUIMacroConfig*)pObj;

	return TRUE;
}

BOOL CGbUIMacroConfig::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CGbUIMacroConfig *p = (CGbUIMacroConfig*)pDest;

	return TRUE;
}

CBaseObject* CGbUIMacroConfig::Clone()
{
	CGbUIMacroConfig *p = new CGbUIMacroConfig();
	Copy(p);
	return p;
}

CExBaseObject* CGbUIMacroConfig::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CMacroScriptMngrXmlRWKeys *pXmlKeys = (CMacroScriptMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCGbUIMacroKey)
	{
		pNew = new CGbUIMacro();
	}

	return pNew;
}

CExBaseObject* CGbUIMacroConfig::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TMSCLASSID_CGBUIMACRO)
	{
		pNew = new CGbUIMacro();
	}

	return pNew;
}
