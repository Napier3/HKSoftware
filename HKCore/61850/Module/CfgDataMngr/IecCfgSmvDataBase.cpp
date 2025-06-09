//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgSmvDataBase.cpp  CIecCfgSmvDataBase


#include "stdafx.h"
#include "IecCfgSmvDataBase.h"
#include "IecCfgDatasMngr.h"

#define SETAPPCH_UI_MODE_ABC0ABC0   0
#define SETAPPCH_UI_MODE_AABBCC00   1

long g_nSetAppCh_UI_Mode = SETAPPCH_UI_MODE_ABC0ABC0;

CIecCfgSmvDataBase::CIecCfgSmvDataBase()
{
	//初始化属性
	m_fUNom = 0;
	m_fINom = 0;
	m_fUNom2 = 0;
	m_fINom2 = 0;
	m_fFNom = 0;
	m_fICenter = 0;
	m_nSampleRate = 4000;
	m_nAsduNum = 0;
	m_bNoQuality = FALSE;

	//初始化成员变量
	m_pException = NULL;
}

CIecCfgSmvDataBase::~CIecCfgSmvDataBase()
{
}

long CIecCfgSmvDataBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUNomKey, oNode, m_fUNom);
	xml_GetAttibuteValue(pXmlKeys->m_strINomKey, oNode, m_fINom);
	xml_GetAttibuteValue(pXmlKeys->m_strFNomKey, oNode, m_fFNom);
	xml_GetAttibuteValue(pXmlKeys->m_strICenterKey, oNode, m_fICenter);
	xml_GetAttibuteValue(pXmlKeys->m_strSampleRateKey, oNode, m_nSampleRate);
	xml_GetAttibuteValue(pXmlKeys->m_strAsduNumKey, oNode, m_nAsduNum);
	xml_GetAttibuteValue(pXmlKeys->m_strNoQualityKey, oNode, m_bNoQuality);
	xml_GetAttibuteValue(pXmlKeys->m_strUNom2Key, oNode, m_fUNom2);
	xml_GetAttibuteValue(pXmlKeys->m_strINom2Key, oNode, m_fINom2);
	return 0;
}

long CIecCfgSmvDataBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUNomKey, oElement, m_fUNom);
	xml_SetAttributeValue(pXmlKeys->m_strINomKey, oElement, m_fINom);
	xml_SetAttributeValue(pXmlKeys->m_strFNomKey, oElement, m_fFNom);
	xml_SetAttributeValue(pXmlKeys->m_strICenterKey, oElement, m_fICenter);
	xml_SetAttributeValue(pXmlKeys->m_strSampleRateKey, oElement, m_nSampleRate);
	xml_SetAttributeValue(pXmlKeys->m_strNoQualityKey, oElement, m_bNoQuality);
	xml_SetAttributeValue(pXmlKeys->m_strAsduNumKey, oElement, m_nAsduNum);
	xml_SetAttributeValue(pXmlKeys->m_strUNom2Key, oElement, m_fUNom2);
	xml_SetAttributeValue(pXmlKeys->m_strINom2Key, oElement, m_fINom2);
	return 0;
}


CExBaseObject* CIecCfgSmvDataBase::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgAdvanceExceptionKey)
	{
		m_pException = new CIecCfgAdvanceException();
		pNew = m_pException;
	}

	return pNew;
}

BOOL CIecCfgSmvDataBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgSmvDataBase *p = (CIecCfgSmvDataBase*)pObj;

	if(m_fUNom != p->m_fUNom)
	{
		return FALSE;
	}

	if(m_fINom != p->m_fINom)
	{
		return FALSE;
	}

	if(m_fUNom2 != p->m_fUNom2)
	{
		return FALSE;
	}

	if(m_fINom2 != p->m_fINom2)
	{
		return FALSE;
	}

	if(m_fFNom != p->m_fFNom)
	{
		return FALSE;
	}

	if(m_fICenter != p->m_fICenter)
	{
		return FALSE;
	}

	if(m_nSampleRate != p->m_nSampleRate)
	{
		return FALSE;
	}

	if(m_bNoQuality != p->m_bNoQuality)
	{
		return FALSE;
	}

	if(m_nAsduNum != p->m_nAsduNum)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgSmvDataBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataBase::CopyOwn(pDest);

	CIecCfgSmvDataBase *p = (CIecCfgSmvDataBase*)pDest;

	p->m_fUNom = m_fUNom;
	p->m_fINom = m_fINom;
	p->m_fUNom2 = m_fUNom2;
	p->m_fINom2 = m_fINom2;
	p->m_fFNom = m_fFNom;
	p->m_fICenter = m_fICenter;
	p->m_nSampleRate = m_nSampleRate;
	p->m_nAsduNum = m_nAsduNum;
	p->m_bNoQuality = m_bNoQuality;
	return TRUE;
}

void CIecCfgSmvDataBase::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGADVANCEEXCEPTION)
		{
			m_pException = (CIecCfgAdvanceException *)p;
			break;
		}
	}

	GetAdvanceException();

	if (m_pCfgChs != NULL)
	{
		m_nChannelNum = m_pCfgChs->GetCount();
	}
}

CIecCfgAdvanceException* CIecCfgSmvDataBase::GetAdvanceException()
{
	if (m_pException == NULL)
	{
		m_pException = new CIecCfgAdvanceException();
		AddTail(m_pException);
	}

	return m_pException;
}

void CIecCfgSmvDataBase::GetCommData(CIecCfgDataSmvCommon *pCommon)
{
	ASSERT (pCommon != NULL);
 	pCommon->m_fUNom = m_fUNom;
// 	pCommon->m_fINom = m_fINom;
	pCommon->m_fFNom = (long)m_fFNom;
// 	pCommon->m_fICenter = m_fICenter;

	if ((GetClassID() == CFGCLASSID_CIECCFG92DATA)||(GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
		||(GetClassID() == CFGCLASSID_CIECCFG91DATA))
	{
		pCommon->m_nSampleRate = m_nSampleRate;
	}
	else
	{
		pCommon->m_nSampleRate_FT3 = m_nSampleRate;
	}

	pCommon->m_nAsduNum = m_nAsduNum;
	pCommon->m_bNoQuality = m_bNoQuality;
}

void CIecCfgSmvDataBase::InitByCommData(CIecCfgDataSmvCommon *pCommon)
{
 	m_fUNom = pCommon->m_fUNom;
// 	m_fINom = pCommon->m_fINom;
	m_fFNom = (float)pCommon->m_fFNom;
// 	m_fICenter = pCommon->m_fICenter;
//	m_nSampleRate = pCommon->m_nSampleRate;
	m_nAsduNum = pCommon->m_nAsduNum;
	m_bNoQuality = pCommon->m_bNoQuality;

	if ((GetClassID() == CFGCLASSID_CIECCFG92DATA)||(GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
		||(GetClassID() == CFGCLASSID_CIECCFG91DATA))
	{
		m_nSampleRate = pCommon->m_nSampleRate;
	}
	else
	{
		m_nSampleRate = pCommon->m_nSampleRate_FT3;
	}
}

BOOL CIecCfgSmvDataBase::OpenCfgDefaultConfigFile()
{
	return CIecCfgDataBase::OpenCfgDefaultConfigFile();
}

void CIecCfgSmvDataBase::EmptyChsName()
{
	CIecCfgDataSmvChBase *pCh = NULL;
	POS pos = m_pCfgChs->GetHeadPosition();

	while (pos != NULL)
	{
		pCh = (CIecCfgDataSmvChBase *)m_pCfgChs->GetNext(pos);
		pCh->m_strID = _T("");
		pCh->m_strName = _T("");
		pCh->m_strAppChID = g_strAppChID_None;
	}
}


// void CIecCfgSmvDataBase::SetCfgDataValue(long nDataID, float dValue)
// {
// 	switch (nDataID)
// 	{
// 	case CFGDATAID_INOM2:
// 		m_fINom2 = dValue;
// 		break;
// 	case CFGDATAID_UNOM2:
// 		m_fUNom2 = dValue;
// 		break;
// 	}
// }


#ifdef _PSX_IDE_QT_
BOOL CIecCfgSmvDataBase::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_INOM2)
	{
		m_fINom2 = vValue;
		return TRUE;
	}

	if (nDataID == CFGDATAID_UNOM2)
	{
		m_fUNom2 = vValue;
		return TRUE;
	}

	return CIecCfgDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfgSmvDataBase::GetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_INOM2)
	{
		vValue = m_fINom2;
		return TRUE;
	}

	if (nDataID == CFGDATAID_UNOM2)
	{
		vValue = m_fUNom2;
		return TRUE;
	}

	return CIecCfgDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfgSmvDataBase::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_INOM2)
	{
		return (vValue == m_fINom2);
	}

	if (nDataID == CFGDATAID_UNOM2)
	{
		return (vValue == m_fUNom2);
	}

	return CIecCfgDataBase::IsEqualCfgDataValue(nDataID, vValue);
}

#else
BOOL CIecCfgSmvDataBase::SetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_INOM2)
	{
		m_fINom2 = vValue.fltVal;
		return TRUE;
	}

	if (nDataID == CFGDATAID_UNOM2)
	{
		m_fUNom2 = vValue.fltVal;
		return TRUE;
	}

	return CIecCfgDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfgSmvDataBase::GetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_INOM2)
	{
		vValue.fltVal = m_fINom2;
		return TRUE;
	}

	if (nDataID == CFGDATAID_UNOM2)
	{
		vValue.fltVal = m_fUNom2;
		return TRUE;
	}

	return CIecCfgDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfgSmvDataBase::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_INOM2)
	{
		return (vValue.fltVal == m_fINom2);
	}

	if (nDataID == CFGDATAID_UNOM2)
	{
		return (vValue.fltVal == m_fUNom2);
	}

	return CIecCfgDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#endif

void CIecCfgSmvDataBase::UpdateChsIndex()
{
	CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr*)GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
	ASSERT (pIecCfgDatasMngr != NULL);

	if (pIecCfgDatasMngr == NULL)
	{
		return;
	}

// 	CIecCfgSystemConfig* pSystemConfig = pIecCfgDatasMngr->GetIecCfgSystemConfig();
// 
// 	if (!pSystemConfig->GetAutoSetUIChIndex())
// 	{
// 		return;
// 	}

	if (m_pCfgChs == NULL)
	{
		return;
	}

	long nIndex = GetCfgDataIndex() + 1;
	
	if (nIndex > 3)
	{
		nIndex -= 3;
	}

	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfgDataSmvChBase *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfgDataSmvChBase*)m_pCfgChs->GetNext(pos);
		pCh->SetAppChIndex(nIndex);
	}
}

void iecfg_AddUICh(long nGroupIndex, const CString &strPhID, CStringArray &astrUChs, CStringArray &astrIChs)
{
	CString strID;
    strID.Format(_T("U%s%d"), strPhID.GetString(), nGroupIndex);
	astrUChs.Add(strID);
    strID.Format(_T("I%s%d"), strPhID.GetString(), nGroupIndex);
	astrIChs.Add(strID);
}

void iecfg_AddDcUICh(long nGroupIndex, const CString &strPhID, CStringArray &astrUChs, CStringArray &astrIChs)
{
	CString strID;
	strID.Format(_T("U%d-%s"), nGroupIndex, strPhID.GetString());
	astrUChs.Add(strID);
	strID.Format(_T("I%d-%s"), nGroupIndex, strPhID.GetString());
	astrIChs.Add(strID);
}

void CIecCfgSmvDataBase::GetUIChs(CStringArray &astrUChs, CStringArray &astrIChs, long nUIGroupIndex)
{
	iecfg_AddUICh(nUIGroupIndex, _T("a"), astrUChs, astrIChs);
	iecfg_AddUICh(nUIGroupIndex, _T("b"), astrUChs, astrIChs);
	iecfg_AddUICh(nUIGroupIndex, _T("c"), astrUChs, astrIChs);
	iecfg_AddUICh(nUIGroupIndex, _T("0"), astrUChs, astrIChs);
	iecfg_AddUICh(nUIGroupIndex, _T("z"), astrUChs, astrIChs);
}

void CIecCfgSmvDataBase::GetDcUIChs(CStringArray &astrUChs, CStringArray &astrIChs, long nUIGroupIndex)
{
	iecfg_AddDcUICh(nUIGroupIndex, _T("1"), astrUChs, astrIChs);
	iecfg_AddDcUICh(nUIGroupIndex, _T("2"), astrUChs, astrIChs);
	iecfg_AddDcUICh(nUIGroupIndex, _T("3"), astrUChs, astrIChs);
//	iecfg_AddDcUICh(nUIGroupIndex, _T("4"), astrUChs, astrIChs);
//	iecfg_AddDcUICh(nUIGroupIndex, _T("0"), astrUChs, astrIChs);
//	iecfg_AddDcUICh(nUIGroupIndex, _T("z"), astrUChs, astrIChs);
}

void CIecCfgSmvDataBase::SetAbc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 1);

	SetAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::SetPabc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 2);

	SetAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::SetSabc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 3);

	SetAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::SetTabc(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 4);

	SetAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::Setabc5(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 5);

	SetAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::Setabc6(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 6);

	SetAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::Set0(BOOL bSetU, BOOL bSetI)
{
	Set0(*m_pCfgChs, bSetU, bSetI);
}


void CIecCfgSmvDataBase::SetAbc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 1);

	SetAppCh(oListCh, bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::SetPabc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 2);

	SetAppCh(oListCh, bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::SetSabc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 3);

	SetAppCh(oListCh, bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::SetTabc(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 4);

	SetAppCh(oListCh, bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::Setabc5(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 5);

	SetAppCh(oListCh, bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::Setabc6(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetUIChs(astrUChs, astrIChs, 6);

	SetAppCh(oListCh, bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::Set0(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI)
{
	SetAppCh_0(oListCh, bSetU, bSetI);
}

void CIecCfgSmvDataBase::SetDcAbcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetDcUIChs(astrUChs, astrIChs, 1);

	SetDcAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}
void CIecCfgSmvDataBase::SetDcPabcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetDcUIChs(astrUChs, astrIChs, 2);

	SetDcAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}
void CIecCfgSmvDataBase::SetDcSabcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetDcUIChs(astrUChs, astrIChs, 3);

	SetDcAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}
void CIecCfgSmvDataBase::SetDcTabcz(BOOL bSetU, BOOL bSetI, BOOL bIntelligent)
{
	CStringArray astrUChs, astrIChs;
	GetDcUIChs(astrUChs, astrIChs, 4);

	SetDcAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
}

void CIecCfgSmvDataBase::SwitchChMap(long nGroupIndex,BOOL bSetU, BOOL bSetI,BOOL bDC_FT3)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfgDataSmvChBase *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfgDataSmvChBase *)m_pCfgChs->GetNext(pos);
		pCh->SwitchChMap(nGroupIndex,bSetU,bSetI,bDC_FT3);
	}
}

void CIecCfgSmvDataBase::SetAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent)
{
	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfgDataSmvChBase *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfgDataSmvChBase *)m_pCfgChs->GetNext(pos);
		pCh->SetAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
	}
}

void CIecCfgSmvDataBase::SetDcAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent)
{
	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfgDataSmvChBase *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfgDataSmvChBase *)m_pCfgChs->GetNext(pos);
		pCh->SetDcAppCh(bSetU, bSetI, astrUChs, astrIChs, bIntelligent);
	}
}

void CIecCfgSmvDataBase::SetAppCh(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent)
{
	if (bSetU)
	{
		SetAppCh_U(oListCh, astrUChs, bIntelligent);

		return;
	}

	if (bSetI)
	{
		SetAppCh_I(oListCh, astrIChs, bIntelligent);
		return;
	}
}

void CIecCfgSmvDataBase::SetAppCh_U(CExBaseList &oListCh, const CStringArray &astrUChs, BOOL bIntelligent)
{
	POS pos = oListCh.GetHeadPosition();
	CIecCfgDataSmvChBase *pCh = NULL;

	long nChIndex = 0;
	long nCount = oListCh.GetCount();
	long nMaxChs = 3;
	long nAABBCC00 = 0;
	long nAABBCC00_Gap = 0;
	long nAABBCC00_Gap_Index = 0;

	if (nCount % 4 == 0)
	{
		nMaxChs = 4;
	}

	nAABBCC00_Gap = nCount / nMaxChs;

	if (g_nSetAppCh_UI_Mode == SETAPPCH_UI_MODE_ABC0ABC0)
	{
		while (pos != NULL)
		{
			pCh = (CIecCfgDataSmvChBase *)oListCh.GetNext(pos);
			pCh->SetAppCh_U(astrUChs, nChIndex, nMaxChs, bIntelligent);
		}

		g_nSetAppCh_UI_Mode = SETAPPCH_UI_MODE_AABBCC00;
	}
	else
	{
		nAABBCC00 = 0;
		nAABBCC00_Gap_Index = 0;

		while (pos != NULL)
		{
			nChIndex = nAABBCC00;
			pCh = (CIecCfgDataSmvChBase *)oListCh.GetNext(pos);
			pCh->SetAppCh_U(astrUChs, nChIndex, nMaxChs, bIntelligent);
			nAABBCC00_Gap_Index++;

			if (nAABBCC00_Gap_Index >= nAABBCC00_Gap)
			{
				nAABBCC00_Gap_Index = 0;
				nAABBCC00++;
			}
		}

		g_nSetAppCh_UI_Mode = SETAPPCH_UI_MODE_ABC0ABC0;
	}
}


void CIecCfgSmvDataBase::SetAppCh_I(CExBaseList &oListCh, const CStringArray &astrIChs, BOOL bIntelligent)
{
	POS pos = oListCh.GetHeadPosition();
	CIecCfgDataSmvChBase *pCh = NULL;

	long nChIndex = 0;
	long nCount = oListCh.GetCount();
	long nMaxChs = 3;
	long nAABBCC00 = 0;
	long nAABBCC00_Gap = 0;
	long nAABBCC00_Gap_Index = 0;

	if (nCount % 4 == 0)
	{
		nMaxChs = 4;
	}

	nAABBCC00_Gap = nCount / nMaxChs;

	if (g_nSetAppCh_UI_Mode == SETAPPCH_UI_MODE_ABC0ABC0)
	{
		while (pos != NULL)
		{
			pCh = (CIecCfgDataSmvChBase *)oListCh.GetNext(pos);
			pCh->SetAppCh_I(astrIChs, nChIndex, nMaxChs, bIntelligent);
		}

		g_nSetAppCh_UI_Mode = SETAPPCH_UI_MODE_AABBCC00;
	}
	else
	{
		nAABBCC00 = 0;
		nAABBCC00_Gap_Index = 0;

		while (pos != NULL)
		{
			nChIndex = nAABBCC00;
			pCh = (CIecCfgDataSmvChBase *)oListCh.GetNext(pos);
			pCh->SetAppCh_I(astrIChs, nChIndex, nMaxChs, bIntelligent);
			nAABBCC00_Gap_Index++;

			if (nAABBCC00_Gap_Index >= nAABBCC00_Gap)
			{
				nAABBCC00_Gap_Index = 0;
				nAABBCC00++;
			}
		}

		g_nSetAppCh_UI_Mode = SETAPPCH_UI_MODE_ABC0ABC0;
	}
}

void CIecCfgSmvDataBase::SetAppCh_0(CExBaseList &oListCh, BOOL bSetU, BOOL bSetI)
{
	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfgDataSmvChBase *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfgDataSmvChBase *)m_pCfgChs->GetNext(pos);
		pCh->SetAppCh_0(bSetU, bSetI);
	}
}

