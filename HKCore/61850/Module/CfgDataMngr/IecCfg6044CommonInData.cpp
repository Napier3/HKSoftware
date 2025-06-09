//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData6044.cpp  CIecCfgData6044


#include "stdafx.h"
#include "IecCfg6044CommonInData.h"
#include "IecCfg6044CommonChIn.h"

CIecCfg6044CommonInData::CIecCfg6044CommonInData()
{
	//初始化属性

	//初始化成员变量
	m_strID = _T("IEC60044-8-CommonIn(FT3)");
}

CIecCfg6044CommonInData::~CIecCfg6044CommonInData()
{
}

long CIecCfg6044CommonInData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg6044CommonData::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	return 0;
}

long CIecCfg6044CommonInData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg6044CommonData::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfg6044CommonInData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfg6044CommonData::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg6044CommonInData *p = (CIecCfg6044CommonInData*)pObj;


	return TRUE;
}

BOOL CIecCfg6044CommonInData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg6044CommonData::CopyOwn(pDest);
	CIecCfg6044CommonInData *p = (CIecCfg6044CommonInData*)pDest;
	return TRUE;
}

CBaseObject* CIecCfg6044CommonInData::Clone()
{
	CIecCfg6044CommonInData *p = new CIecCfg6044CommonInData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg6044CommonInData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChs6044Key)
	{
		pNew = new CIecCfg6044Chs();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	return CIecCfg6044CommonData::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg6044CommonInData::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHS6044);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg6044Chs();
		AddNewChild(m_pCfgChs);
	}

	CIecCfgSmvDataBase::InitAfterRead();
}

long CIecCfg6044CommonInData::GetPkgLength()
{
	long nPkgLength = 0;
	CIecCfg6044Chs *pIecCfg6044Chs = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pIecCfg6044Chs=(CIecCfg6044Chs*)GetNext(pos);

		if (pIecCfg6044Chs->GetClassID() == CFGCLASSID_CIECCFGCHS6044)
		{
			POS posChs = pIecCfg6044Chs->GetHeadPosition();
			CExBaseObject *pCurObj = NULL;
			CIecCfg6044CommonChIn *pIecCfg6044CommonChIn=NULL;
			while(posChs)
			{
				pCurObj=pIecCfg6044Chs->GetNext(posChs);
				pIecCfg6044CommonChIn=(CIecCfg6044CommonChIn*)pCurObj;
				nPkgLength += pIecCfg6044CommonChIn->m_nChLenth;
			}	
			
		}


	}

	return nPkgLength;
}