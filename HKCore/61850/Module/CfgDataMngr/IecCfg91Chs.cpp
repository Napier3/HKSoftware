//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgChs91.cpp  CIecCfgChs91


#include "stdafx.h"
#include "IecCfg91Chs.h"

CIecCfg91Chs::CIecCfg91Chs()
{
	//初始化属性

	//初始化成员变量
}

CIecCfg91Chs::~CIecCfg91Chs()
{
}

long CIecCfg91Chs::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfg91Chs::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfg91Chs::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfg91Chs *p = (CIecCfg91Chs*)pObj;

	return TRUE;
}

BOOL CIecCfg91Chs::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg91Chs *p = (CIecCfg91Chs*)pDest;

	return TRUE;
}

CBaseObject* CIecCfg91Chs::Clone()
{
	CIecCfg91Chs *p = new CIecCfg91Chs();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg91Chs::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfg91ChKey)
	{
		pNew = new CIecCfg91Ch();
	}

	return pNew;
}

CExBaseObject* CIecCfg91Chs::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == CFGCLASSID_CIECCFG91CH)
	{
		pNew = new CIecCfg91Ch();
	}

	return pNew;
}


CIecCfgDataChBase* CIecCfg91Chs::CreateChannel()
{
	CIecCfgDataChBase *pNew = new CIecCfg91Ch();
	return pNew;
}

void CIecCfg91Chs::InitAfterRead()
{
	SetChannelNum(12);
}
