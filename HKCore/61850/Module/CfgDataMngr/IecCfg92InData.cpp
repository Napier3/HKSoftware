//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData92.cpp  CIecCfgData92


#include "stdafx.h"
#include "IecCfg92InData.h"
#include "IecCfg92ChsIn.h"
#include "IecCfg92ChIn.h"

#ifndef _PSX_IDE_QT_
#include "../IecCfgTool/IecCfgTool.h"
#endif

#ifdef _USE_IN_AT02D_MODE_
#include "../../../Module/SmartCap/XSttRcdInitChDvmData.h"
#endif

CIecCfg92InData::CIecCfg92InData()
{
	m_nInitUseFlag = 1;
}

CIecCfg92InData::~CIecCfg92InData()
{
}

long CIecCfg92InData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg92Data::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CIecCfg92InData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfg92Data::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

BOOL CIecCfg92InData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfg92Data::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg92InData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfg92Data::CopyOwn(pDest);
	return TRUE;
}

CBaseObject* CIecCfg92InData::Clone()
{
	CIecCfg92Data *p = new CIecCfg92InData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg92InData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChs92InKey)
	{
		pNew = new CIecCfg92ChsIn();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	return CIecCfgSmvDataBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg92InData::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHS92IN);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg92ChsIn();
		AddNewChild(m_pCfgChs);
	}

	CIecCfgSmvDataBase::InitAfterRead();
}

void CIecCfg92InData::GetQualityList(CIecCfg92ChQualityList *pList)
{
	ASSERT (pList != NULL);
	ASSERT (m_pCfgChs != NULL);

	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfg92ChIn *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg92ChIn *)m_pCfgChs->GetNext(pos);

		if (pCh->GetClassID() == CFGCLASSID_CIECCFG92CHIN)
		{
			CIecCfg92ChQuality *pNew = new CIecCfg92ChQuality();
			pNew->SetQualityRef(&pCh->m_nQuality);
			pList->AddTail(pNew);
		}
	}

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg92ChsIn();
		AddNewChild(m_pCfgChs);
	}

}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfg92InData::AddAT02D_Dataset(CDvmDataset *pCurDataset,BOOL bHasHarm,BOOL bhasMUTestParas)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

		CIecCfg92ChsIn *pIecCfg92Chs = (CIecCfg92ChsIn*)m_pCfgChs;
		CExBaseObject *pCurObj = NULL;
		CIecCfg92ChIn *pIecCfg92Ch = NULL;
		CDvmData *pDvmData = NULL;
		CDvmValue *pDvmValue = NULL;

		POS pos = pIecCfg92Chs->GetHeadPosition();

		while(pos)
		{
			pCurObj = pIecCfg92Chs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CHIN)
			{
				pIecCfg92Ch = (CIecCfg92ChIn*)pCurObj;

// 				if ((pIecCfg92Ch->m_strChType != iecfg_SmvChDataType_Val_Curr)&&(pIecCfg92Ch->m_strChType != iecfg_SmvChDataType_Val_Vol))
// 				{
// 					continue;
// 				} //zhouhj 20220605 将通道延时放入数据集一起考虑

				pDvmData = new CDvmData;
				pDvmData->m_strDataType = pIecCfg92Ch->m_strChType;
				pDvmData->m_strName = pIecCfg92Ch->m_strName;
				pDvmData->m_strID = pIecCfg92Ch->m_strID;
				pCurDataset->AddNewChild(pDvmData);

				if (pIecCfg92Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
				{
					pDvmData->m_strUnit = _T("V");
				}
				else if (pIecCfg92Ch->m_strChType == iecfg_SmvChDataType_Val_UTCTime)
				{
				}
				else
				{
					pDvmData->m_strUnit = _T("A");
				}

				if (bHasHarm)
				{
					XSttRcdInitChDvmData(pDvmData, g_nXSttRcdInitChDvmData_Harm, bhasMUTestParas);
				}
				else
				{
					XSttRcdInitChDvmData(pDvmData, 0, bhasMUTestParas);
				}
			}
	}
}

void CIecCfg92InData::AT02D_MapChannelID(CIecCfg92Data *pIecCfg92Data)
{
	if ((m_pCfgChs != NULL)&&(pIecCfg92Data->m_pCfgChs != NULL))
	{
		CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pCfgChs;
		CIecCfg92Chs *pNewIecCfg92Chs = (CIecCfg92Chs*)pIecCfg92Data->m_pCfgChs;
		CExBaseObject *pCurObj = NULL;
		CIecCfg92Ch *pIecCfg92Ch = NULL;
		CExBaseObject *pNewCurObj = NULL;
		long nChannelIndex = 0;

		POS pos = pIecCfg92Chs->GetHeadPosition();

		while(pos)
		{
			pCurObj = pIecCfg92Chs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CHIN)
			{
				pIecCfg92Ch = (CIecCfg92Ch*)pCurObj;
				pNewCurObj = pNewIecCfg92Chs->GetAtIndex(nChannelIndex);

				if ((pNewCurObj!=NULL)&&(pNewCurObj->GetClassID() == CFGCLASSID_CIECCFG92CHIN))
				{
//					((CIecCfg92Ch*)pNewCurObj)->m_strAppChID = pIecCfg92Ch->m_strAppChID;
					pNewCurObj->m_strID = pIecCfg92Ch->m_strID;
				}
			}

			nChannelIndex++;
		}
	}
}

BOOL CIecCfg92InData::HasCurAndVolChannelType()
{
	if (m_pCfgChs == NULL)
	{
		return FALSE;
	}

	CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Ch *pIecCfg92Ch = NULL;
	POS pos = pIecCfg92Chs->GetHeadPosition();
	BOOL bHasCur = FALSE;
	BOOL bHasVol = FALSE;

	while(pos)
	{
		pCurObj = pIecCfg92Chs->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CHIN)
		{
			pIecCfg92Ch = (CIecCfg92Ch*)pCurObj;

			if (pIecCfg92Ch->m_strChType == _T("Curr"))
			{
				bHasCur = TRUE;
			}
			else if (pIecCfg92Ch->m_strChType == _T("Vol"))
			{
				bHasVol = TRUE;
			}

			if (bHasCur&&bHasVol)
			{
				break;
			}
		}
	}

	return (bHasCur&&bHasVol);
}
#endif
