//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

#include "stdafx.h"
#include "IecCfg92ChIn.h"
#include "IecCfgSMVDatas.h"
#include <math.h>

CIecCfg92ChIn::CIecCfg92ChIn()
{
	m_strCfg92DoDesc = _T("");
	m_strCfg92dUVal = _T("");
	m_nFiberIndex = 0;
	m_nFiber2Index = 0;
	m_nAccuratyLevel = 0;
	m_nUseFlag = 1;
}

CIecCfg92ChIn::~CIecCfg92ChIn()
{
}

long CIecCfg92ChIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg92Ch::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCIecCfg92DoDescKey, oNode, m_strCfg92DoDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strCIecCfg92dUValKey, oNode, m_strCfg92dUVal);
	xml_GetAttibuteValue(pXmlKeys->m_strFiberIndexKey, oNode, m_nFiberIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strFiber2IndexKey, oNode, m_nFiber2Index);
	xml_GetAttibuteValue(pXmlKeys->m_strCIecCfgAccuracyLevelKey, oNode, m_nAccuratyLevel);

	return 0;
}

long CIecCfg92ChIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg92Ch::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCIecCfg92DoDescKey, oElement, m_strCfg92DoDesc);
	xml_SetAttributeValue(pXmlKeys->m_strCIecCfg92dUValKey, oElement, m_strCfg92dUVal);
	xml_SetAttributeValue(pXmlKeys->m_strFiberIndexKey, oElement, m_nFiberIndex);
	xml_SetAttributeValue(pXmlKeys->m_strFiber2IndexKey, oElement, m_nFiber2Index);
	xml_SetAttributeValue(pXmlKeys->m_strCIecCfgAccuracyLevelKey, oElement, m_nAccuratyLevel);
	return 0;
}

BOOL CIecCfg92ChIn::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfg92Ch::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg92ChIn *p = (CIecCfg92ChIn*)pObj;

	if(m_strCfg92DoDesc != p->m_strCfg92DoDesc)
	{
		return FALSE;
	}

	if(m_nAccuratyLevel != p->m_nAccuratyLevel)
	{
		return FALSE;
	}

	if(m_strCfg92dUVal != p->m_strCfg92dUVal)
	{
		return FALSE;
	}

	if(m_nFiberIndex != p->m_nFiberIndex)
	{
		return FALSE;
	}

	if(m_nFiber2Index != p->m_nFiber2Index)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg92ChIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg92Ch::CopyOwn(pDest);

	CIecCfg92ChIn *p = (CIecCfg92ChIn*)pDest;

	p->m_strCfg92DoDesc = m_strCfg92DoDesc;
	p->m_nAccuratyLevel = m_nAccuratyLevel;
	p->m_strCfg92dUVal = m_strCfg92dUVal;
	p->m_nFiberIndex = m_nFiberIndex;
	p->m_nFiber2Index = m_nFiber2Index;
	return TRUE;
}

CBaseObject* CIecCfg92ChIn::Clone()
{
	CIecCfg92ChIn *p = new CIecCfg92ChIn();
	Copy(p);
	return p;
}

void CIecCfg92ChIn::InitCh()
{
	CIecCfgDataChBase::InitCh();
	CIecCfg92InData *pIecCfg92InData = (CIecCfg92InData*)GetAncestor(CFGCLASSID_CIECCFG92INPUTDATA);

	if (pIecCfg92InData == NULL)
	{
		m_nUseFlag = 1;
		m_nAccuratyLevel = 0;
		InitAccLevelByName();
//		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("pIecCfg92InData == NULL == %ld."),m_nUseFlag);
	}
	else if (pIecCfg92InData->m_nInitUseFlag)
	{
		m_nUseFlag = 1;
		m_nAccuratyLevel = 0;
		InitAccLevelByName();
//		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("pIecCfg92InData->m_nInitUseFlag=%ld; m_nUseFlag == %ld."),pIecCfg92InData->m_nInitUseFlag,m_nUseFlag);
	}
// 	else
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_RESULT,_T("pIecCfg92InData->m_nInitUseFlag == %ld."),pIecCfg92InData->m_nInitUseFlag);
// 	}
	
}

void CIecCfg92ChIn::InitAccLevelByName()
{
	if (iecfg_SmvChDataType_Val_Curr == m_strChType)
	{
		if (m_strName.Find(_T("测量"))>=0)
		{
			m_nAccuratyLevel = IECCFG_CURRCH_AccLevel_Meas0_2;
		}
		else
		{
			m_nAccuratyLevel = IECCFG_CURRCH_AccLevel_Prot5P30;
		}
	}
	else if (iecfg_SmvChDataType_Val_Curr == m_strChType)
	{
// 		if (m_strName.Find(_T("测量"))>=0)
// 		{
// 			m_nAccuratyLevel = IECCFG_VOLCH_AccLevel_Meas1;
// 		}
// 		else
		{
			m_nAccuratyLevel = IECCFG_VOLCH_AccLevel_Prot3P;
		}
	}
}



