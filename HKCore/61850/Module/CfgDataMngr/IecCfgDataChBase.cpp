//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataChBase.cpp  CIecCfgDataChBase


#include "stdafx.h"
#include "IecCfgDataChBase.h"
#include "../../Module/XLanguageResourceIec.h"

CIecCfgDataChBase::CIecCfgDataChBase()
{
	//初始化属性
	m_nUseFlag = 0;
	m_nIndex = 0;

	//初始化成员变量
// 	m_pArtAmpDigdata = NULL;
	m_pScdObjRef = NULL;
}

CIecCfgDataChBase::~CIecCfgDataChBase()
{
}

long CIecCfgDataChBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseFlagKey, oNode, m_nUseFlag);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexKey, oNode, m_nIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strAppChIDKey, oNode, m_strAppChID);
	xml_GetAttibuteValue(pXmlKeys->m_strDevChIDKey, oNode, m_strDevChID);
	xml_GetAttibuteValue(pXmlKeys->m_strMapDataIDKey, oNode, m_strMapDataID);
	return 0;
}

long CIecCfgDataChBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

// 	if (pXmlKeys->m_nXmlOnlyWrite_Id_Value >= 1)// 20230422 zhouhj IEC配置内需要显示通道名称
// 	{
// 		xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strID);
// 		xml_SetAttributeValue(pXmlKeys->m_strDevChIDKey, oElement, m_strDevChID);//FT3订阅时,使用该属性
// 	}
// 	else
	{
		CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
		xml_SetAttributeValue(pXmlKeys->m_strDevChIDKey, oElement, m_strDevChID);
	}

	xml_SetAttributeValue(pXmlKeys->m_strUseFlagKey, oElement, m_nUseFlag);
	xml_SetAttributeValue(pXmlKeys->m_strIndexKey, oElement, m_nIndex);
	xml_SetAttributeValue(pXmlKeys->m_strAppChIDKey, oElement, m_strAppChID);

	return 0;
}

BOOL CIecCfgDataChBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDataChBase *p = (CIecCfgDataChBase*)pObj;

	if(m_nUseFlag != p->m_nUseFlag)
	{
		return FALSE;
	}

	if(m_nIndex != p->m_nIndex)
	{
		return FALSE;
	}

	if(m_strAppChID != p->m_strAppChID)
	{
		return FALSE;
	}

	if(m_strDevChID != p->m_strDevChID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDataChBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgDataChBase *p = (CIecCfgDataChBase*)pDest;

	p->m_nUseFlag = m_nUseFlag;
	p->m_nIndex = m_nIndex;
	p->m_strAppChID = m_strAppChID;
	p->m_strDevChID = m_strDevChID;
	return TRUE;
}

CBaseObject* CIecCfgDataChBase::Clone()
{
	CIecCfgDataChBase *p = new CIecCfgDataChBase();
	Copy(p);
	return p;
}

void CIecCfgDataChBase::InitCh()	
{
	if (m_strName.GetLength() == 0)
	{
#ifdef NOT_USE_XLANGUAGE
        m_strName.Format(_T("通道%d"), m_nIndex+1);
#else
		m_strName.Format(g_sLangTxt_Channel.GetString()/*_T("通道%d")*/, m_nIndex+1);
#endif
		m_strID.Format(_T("Ch%d"), m_nIndex+1);//zhouhj 20211012 通道ID不包含中文
	}
}


BOOL CIecCfgDataChBase::IsChUse()
{
	return (m_strAppChID != g_strAppChID_None);
}

BOOL CIecCfgDataChBase::IsTimeCh()
{
	return (m_strAppChID == g_strAppChID_UTCTime);
}

BOOL CIecCfgDataChBase::IsZeroCh()
{
	return (m_strAppChID == g_strAppChID_Zero);
}


BOOL CIecCfgDataChBase::IsAppCh()
{
	if (!IsChUse())
	{
		return FALSE;
	}

	if (IsTimeCh())
	{
		return FALSE;
	}

	if (IsZeroCh())
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDataChBase::IsUCh()
{
	if (m_strAppChID.GetLength() == 0)
	{
		return FALSE;
	}

	return (m_strAppChID.Left(1) == _T("U"));
}

BOOL CIecCfgDataChBase::IsICh()
{
	if (m_strAppChID.GetLength() == 0)
	{
		return FALSE;
	}

	return (m_strAppChID.Left(1) == _T("I"));
}

BOOL CIecCfgDataChBase::IsTCh()
{
	if (m_strAppChID.GetLength() == 0)
	{
		return FALSE;
	}

	return (m_strAppChID.Left(1) == _T("t"));
}

CExBaseObject* CIecCfgDataChBase::GetAncestorIecCfgData()
{
	CExBaseObject* pIecCfgChs = (CExBaseObject*)GetParent();

	if (pIecCfgChs == NULL)
	{
		return NULL;
	}

	return (CExBaseObject*)pIecCfgChs->GetParent();
}

// 
// DWORD CIecCfgDataChBase::InitArtAmpDigdata(CArtAmpDigdata *pArtAmpDigdata)
// {
// 	pArtAmpDigdata->m_nDigWhich = ((CExBaseList*)m_pParent)->FindIndex(this);
// 
// 	return 0;
// }
// 
// DWORD CIecCfgDataChBase::CalMagAndOffset(CArtAmpDigdata *pArtAmpDigdata)
// {
// 	float dwMag = 0;
// 	float dwOffset = 0;
// 	
// 	CalMagAndOffsetVal(pArtAmpDigdata, dwMag, dwOffset);
// 	pArtAmpDigdata->m_dwOffsetCal = dwOffset;
// 	pArtAmpDigdata->m_dwMagCal = dwMag;
// 
// 	return 0;
// }
// 
// DWORD CIecCfgDataChBase::GetMagAndOffset(float &dwMag, float &dwOffset)
// {
// // 	if (m_pArtAmpDigdata == NULL)
// // 	{
// // 		dwMag = 0;
// // 		dwOffset = 0;
// // 	}
// // 	else
// // 	{
// // 		dwOffset = m_pArtAmpDigdata->m_dwOffsetCal;
// // 		dwMag = m_pArtAmpDigdata->m_dwMagCal;
// // 	}
// 
// 	//dwMag = 1;
// 	//dwOffset = 0;
// 
// 	return 0;
// }
// 
// DWORD CIecCfgDataChBase::CalMagAndOffset(float &dwMag, float &dwOffset)
// {
// 	if (!IsAppCh())
// 	{
// 		dwMag = 0;
// 		dwOffset = 0;
// 		return 0;
// 	}
// 
// 	dwMag = 10;
// 	dwOffset = 20;
// 
// 	CIecCfgDatasMngr *pDatasMngr = (CIecCfgDatasMngr*)GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
// 	CArtAmpDigdatas *pArtAmpDigdatas = pDatasMngr->GetArtAmpDigdatas();
// 	CArtAmpDigdata *pArtAmpDigdata = (CArtAmpDigdata*)pArtAmpDigdatas->AddArtAmpDigdata(m_strAppChID);
// 	ASSERT (pArtAmpDigdata != NULL);
// 
// 	if (pArtAmpDigdata == NULL)
// 	{
// 		dwMag = 0;
// 		dwOffset = 0;
// 		return 0;
// 	}
// 
// 	pArtAmpDigdata->m_nDigFlag = 1;
// 	m_pArtAmpDigdata = pArtAmpDigdata;
// 
// 	return CalMagAndOffsetVal(pArtAmpDigdata, dwMag, dwOffset);
// }

// DWORD CIecCfgDataChBase::CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// {
// 	return 0;
// }

void CIecCfgDataChBase::InitForSclRead(long &nUChIndex, long &nIChIndex)
{
	
}

