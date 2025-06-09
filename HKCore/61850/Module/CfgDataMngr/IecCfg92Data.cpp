//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData92.cpp  CIecCfgData92


#include "stdafx.h"
#include "IecCfg92Data.h"

#ifndef _PSX_IDE_QT_
#include "../IecCfgTool/IecCfgTool.h"
#endif

#ifdef _USE_IN_AT02D_MODE_
#include "../../../Module/SmartCap/XSttRcdInitChDvmData.h"
#endif

CIecCfg92Data::CIecCfg92Data()
{
	//初始化属性
	m_nPriority = 4;
	m_nSyn = 1;
	m_nCTBit = 1;
	m_nPTBit = 10;
	m_nDelay = 0;
	m_nUseSampRate = 0;
	m_nUseDataSet = 0;
	m_nUseSampleTime = 0;
	m_nUseRefreshTime = 0;
	m_nUseEncrupt = 0;
	m_nVoltateRate = 0;
	m_nCurrRate = 0;

	m_dwAppID = 0;
// 	m_dwSVID = 0;
	m_dwVID = 0x101;
// 	m_dwDataSet = 0;
	m_nAsduNum = 1;
	m_dwVersion = 1;

	//初始化成员变量
	m_strSrcAddress = _T("00-FF-FF-FF-FF-FF");
	m_strDestAddress = _T("00-FF-FF-FF-FF-FF");
	m_strID = _T("9-2");

}

CIecCfg92Data::~CIecCfg92Data()
{
}

long CIecCfg92Data::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgSmvDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strDestAddressKey, oNode, m_strDestAddress);
	xml_GetAttibuteValue(pXmlKeys->m_strSrcAddressKey, oNode, m_strSrcAddress);
	xml_GetAttibuteValue(pXmlKeys->m_strAppIDKey, oNode, m_dwAppID);
	xml_GetAttibuteValue(pXmlKeys->m_strPriorityKey, oNode, m_nPriority);
	xml_GetAttibuteValue(pXmlKeys->m_strSVIDKey, oNode, m_strSVID);
// 	xml_GetAttibuteValue(pXmlKeys->m_strSVIDKey, oNode, m_dwSVID);
	xml_GetAttibuteValue(pXmlKeys->m_strVIDKey, oNode, m_dwVID);
	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_dwVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strDataSetKey, oNode, m_strDataSet);
// 	xml_GetAttibuteValue(pXmlKeys->m_strDataSetKey, oNode, m_dwDataSet);
	xml_GetAttibuteValue(pXmlKeys->m_strSynKey, oNode, m_nSyn);
	xml_GetAttibuteValue(pXmlKeys->m_strCTBitKey, oNode, m_nCTBit);
	xml_GetAttibuteValue(pXmlKeys->m_strPTBitKey, oNode, m_nPTBit);
	xml_GetAttibuteValue(pXmlKeys->m_strDelayKey, oNode, m_nDelay);
	xml_GetAttibuteValue(pXmlKeys->m_strUseSampRateKey, oNode, m_nUseSampRate);
	xml_GetAttibuteValue(pXmlKeys->m_strUseDataSetKey, oNode, m_nUseDataSet);
	xml_GetAttibuteValue(pXmlKeys->m_strUseSampleTimeKey, oNode, m_nUseSampleTime);
	xml_GetAttibuteValue(pXmlKeys->m_strUseRefreshTimeKey, oNode, m_nUseRefreshTime);
	xml_GetAttibuteValue(pXmlKeys->m_strUseEncruptKey, oNode, m_nUseEncrupt);
	xml_GetAttibuteValue(pXmlKeys->m_strVoltateRateKey, oNode, m_nVoltateRate);
	xml_GetAttibuteValue(pXmlKeys->m_strCurrRateKey, oNode, m_nCurrRate);

#ifndef _PSX_IDE_QT_
	iecfg_GetCfgDataValueMac(m_strDestAddress, m_byteDestAddress);
	iecfg_GetCfgDataValueMac(m_strSrcAddress, m_byteSrcAddresss);
#endif

	return 0;
}

long CIecCfg92Data::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgSmvDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strDestAddressKey, oElement, m_strDestAddress);
	xml_SetAttributeValue(pXmlKeys->m_strSrcAddressKey, oElement, m_strSrcAddress);
	xml_SetAttributeValue(pXmlKeys->m_strAppIDKey, oElement, m_dwAppID);
	xml_SetAttributeValue(pXmlKeys->m_strPriorityKey, oElement, m_nPriority);
	xml_SetAttributeValue(pXmlKeys->m_strSVIDKey, oElement, m_strSVID);
// 	xml_SetAttributeValue(pXmlKeys->m_strSVIDKey, oElement, m_dwSVID);
	xml_SetAttributeValue(pXmlKeys->m_strVIDKey, oElement, m_dwVID);
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_dwVersion);
//	xml_SetAttributeValue(pXmlKeys->m_strDataSetKey, oElement, m_dwDataSet);
	xml_SetAttributeValue(pXmlKeys->m_strDataSetKey, oElement, m_strDataSet);
	xml_SetAttributeValue(pXmlKeys->m_strSynKey, oElement, m_nSyn);
	xml_SetAttributeValue(pXmlKeys->m_strCTBitKey, oElement, m_nCTBit);
	xml_SetAttributeValue(pXmlKeys->m_strPTBitKey, oElement, m_nPTBit);
	xml_SetAttributeValue(pXmlKeys->m_strDelayKey, oElement, m_nDelay);
	xml_SetAttributeValue(pXmlKeys->m_strUseSampRateKey, oElement, m_nUseSampRate);
	xml_SetAttributeValue(pXmlKeys->m_strUseDataSetKey, oElement, m_nUseDataSet);
	xml_SetAttributeValue(pXmlKeys->m_strUseSampleTimeKey, oElement, m_nUseSampleTime);
	xml_SetAttributeValue(pXmlKeys->m_strUseRefreshTimeKey, oElement, m_nUseRefreshTime);
	xml_SetAttributeValue(pXmlKeys->m_strUseEncruptKey, oElement, m_nUseEncrupt);
	xml_SetAttributeValue(pXmlKeys->m_strVoltateRateKey, oElement, m_nVoltateRate);
	xml_SetAttributeValue(pXmlKeys->m_strCurrRateKey, oElement, m_nCurrRate);

	return 0;
}

BOOL CIecCfg92Data::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgSmvDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg92Data *p = (CIecCfg92Data*)pObj;

	if(m_strDestAddress != p->m_strDestAddress)
	{
		return FALSE;
	}

	if(m_strSrcAddress != p->m_strSrcAddress)
	{
		return FALSE;
	}

	if(m_dwAppID != p->m_dwAppID)
	{
		return FALSE;
	}

	if(m_nPriority != p->m_nPriority)
	{
		return FALSE;
	}

	if(m_strSVID != p->m_strSVID)
	{
		return FALSE;
	}

// 	if(m_dwSVID != p->m_dwSVID)
// 	{
// 		return FALSE;
// 	}
// 
	if(m_dwVID != p->m_dwVID)
	{
		return FALSE;
	}

	if(m_dwVersion != p->m_dwVersion)
	{
		return FALSE;
	}

	if(m_strDataSet != p->m_strDataSet)
	{
		return FALSE;
	}
// 	if(m_dwDataSet != p->m_dwDataSet)
// 	{
// 		return FALSE;
// 	}
// 
	if(m_nSyn != p->m_nSyn)
	{
		return FALSE;
	}

	if(m_nCTBit != p->m_nCTBit)
	{
		return FALSE;
	}

	if(m_nPTBit != p->m_nPTBit)
	{
		return FALSE;
	}

	if(m_nDelay != p->m_nDelay)
	{
		return FALSE;
	}

	if(m_nUseSampRate != p->m_nUseSampRate)
	{
		return FALSE;
	}

	if(m_nUseDataSet != p->m_nUseDataSet)
	{
		return FALSE;
	}

	if(m_nUseSampleTime != p->m_nUseSampleTime)
	{
		return FALSE;
	}

	if(m_nUseRefreshTime != p->m_nUseRefreshTime)
	{
		return FALSE;
	}

	if(m_nUseEncrupt != p->m_nUseEncrupt)
	{
		return FALSE;
	}

	if(m_nVoltateRate != p->m_nVoltateRate)
	{
		return FALSE;
	}

	if(m_nCurrRate != p->m_nCurrRate)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg92Data::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgSmvDataBase::CopyOwn(pDest);

	CIecCfg92Data *p = (CIecCfg92Data*)pDest;

	p->m_strDestAddress = m_strDestAddress;
	p->m_strSrcAddress = m_strSrcAddress;
	p->m_dwAppID = m_dwAppID;
	p->m_nPriority = m_nPriority;
	p->m_strSVID = m_strSVID;
// 	p->m_dwSVID = m_dwSVID;
	p->m_dwVID = m_dwVID;
	p->m_dwVersion = m_dwVersion;
	p->m_strDataSet = m_strDataSet;
	p->m_nSyn = m_nSyn;
	p->m_nCTBit = m_nCTBit;
	p->m_nPTBit = m_nPTBit;
	p->m_nDelay = m_nDelay;
	p->m_nUseSampRate = m_nUseSampRate;
	p->m_nUseDataSet = m_nUseDataSet;
	p->m_nUseSampleTime = m_nUseSampleTime;
	p->m_nUseRefreshTime = m_nUseRefreshTime;
	p->m_nUseEncrupt = m_nUseEncrupt;
	p->m_nVoltateRate = m_nVoltateRate;
	p->m_nCurrRate = m_nCurrRate;

	return TRUE;
}

CBaseObject* CIecCfg92Data::Clone()
{
	CIecCfg92Data *p = new CIecCfg92Data();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg92Data::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChs92Key)
	{
		pNew = new CIecCfg92Chs();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	return CIecCfgSmvDataBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg92Data::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHS92);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg92Chs();
		AddNewChild(m_pCfgChs);
	}

	CIecCfgSmvDataBase::InitAfterRead();
}

BOOL CIecCfg92Data::OpenCfgDefaultConfigFile()
{
	BOOL bRet = CIecCfgSmvDataBase::OpenCfgDefaultConfigFile();

	//打开缺省配置文件后,对外部描述等进行初始化,防止影响正常显示
	if (m_pCfgChs != NULL)
	{
		CIecCfg92Ch *pIecCfg92Ch = NULL;
		CExBaseObject *pCurObj = NULL;
		POS pos = m_pCfgChs->GetHeadPosition();

		while(pos)
		{
			pCurObj = m_pCfgChs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CH)
			{
				pIecCfg92Ch = (CIecCfg92Ch*)pCurObj;
				pIecCfg92Ch->m_strDescExternal = _T("");
				pIecCfg92Ch->m_strAddrExternal = _T("");
				pIecCfg92Ch->m_nIndexExternal = -1;
			}
		}
	}

	m_nUseSampRate = 0;
	m_nUseDataSet = 0;
	m_nUseSampleTime = 0;
	m_nUseRefreshTime = 0;
	m_nUseEncrupt = 0;
	return bRet;
}

void CIecCfg92Data::GetQualityList(CIecCfg92ChQualityList *pList)
{
	ASSERT (pList != NULL);
	ASSERT (m_pCfgChs != NULL);

	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfg92Ch *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg92Ch *)m_pCfgChs->GetNext(pos);

		if (pCh->GetClassID() == CFGCLASSID_CIECCFG92CH)
		{
			CIecCfg92ChQuality *pNew = new CIecCfg92ChQuality();
			pNew->SetQualityRef(&pCh->m_nQuality);
			pList->AddTail(pNew);
		}
	}

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg92Chs();
		AddNewChild(m_pCfgChs);
	}

}

BOOL CIecCfg92Data::IsAllChSetTest()
{
	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfg92Ch *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg92Ch *)m_pCfgChs->GetNext(pos);

		if ((pCh->m_nQuality & 0x0800) == 0)
		{
			return FALSE;
		} 
	}

	return TRUE;
}

void CIecCfg92Data::SetChsQualityValue(DWORD dwQulity)
{
	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfg92Ch *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg92Ch *)m_pCfgChs->GetNext(pos);
		pCh->m_nQuality = dwQulity;
	}
}

void CIecCfg92Data::SetTestState(BOOL bTest)
{
	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfg92Ch *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg92Ch *)m_pCfgChs->GetNext(pos);

		if (bTest)
		{
			pCh->m_nQuality = (pCh->m_nQuality&0xF7FF);
			pCh->m_nQuality += 0x0800;
		}
		else
		{
			pCh->m_nQuality = (pCh->m_nQuality&0xF7FF);
		}
	}
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfg92Data::SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	if (m_pCfgChs != NULL)
	{
		((CIecCfg92Chs*)m_pCfgChs)->SetAT02D_ChannelID(pSVList,nCBIndex);
	}
}

void CIecCfg92Data::AddAT02D_Dataset(CDvmDataset *pCurDataset,BOOL bHasHarm,BOOL bhasMUTestParas)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

		CIecCfg92Chs *pIecCfg92Chs = (CIecCfg92Chs*)m_pCfgChs;
		CExBaseObject *pCurObj = NULL;
		CIecCfg92Ch *pIecCfg92Ch = NULL;
		CDvmData *pDvmData = NULL;
		CDvmValue *pDvmValue = NULL;

		POS pos = pIecCfg92Chs->GetHeadPosition();

		while(pos)
		{
			pCurObj = pIecCfg92Chs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CH)
			{
				pIecCfg92Ch = (CIecCfg92Ch*)pCurObj;

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

void CIecCfg92Data::AT02D_MapChannelID(CIecCfg92Data *pIecCfg92Data)
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

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CH)
			{
				pIecCfg92Ch = (CIecCfg92Ch*)pCurObj;
				pNewCurObj = pNewIecCfg92Chs->GetAtIndex(nChannelIndex);

				if ((pNewCurObj!=NULL)&&(pNewCurObj->GetClassID() == CFGCLASSID_CIECCFG92CH))
				{
//					((CIecCfg92Ch*)pNewCurObj)->m_strAppChID = pIecCfg92Ch->m_strAppChID;
					pNewCurObj->m_strID = pIecCfg92Ch->m_strID;
				}
			}

			nChannelIndex++;
		}
	}
}

BOOL CIecCfg92Data::HasCurAndVolChannelType()
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

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92CH)
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

#ifdef _PSX_IDE_QT_
BOOL CIecCfg92Data::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_SetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_SetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
		ASSERT (vValue.vt == VT_UI4);
		m_dwAppID = vValue;
		return TRUE;
	}

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfg92Data::GetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
//		vValue.vt = VT_UI4;
		vValue = m_dwAppID;
		return TRUE;
	}

	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg92Data::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
{
	unsigned long long vCurr;

	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vCurr);
		return (vCurr == vValue);
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vCurr);
		return (vCurr == vValue);
	}

	if (nDataID == CFGDATAID_APPID)
	{
//		ASSERT (vValue.vt == VT_UI4);
		return (vValue == m_dwAppID);
	}

	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#else
BOOL CIecCfg92Data::SetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_SetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_SetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
		ASSERT (vValue.vt == VT_UI4);
		m_dwAppID = vValue.ulVal;
		return TRUE;
	}

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfg92Data::GetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vValue);
		return TRUE;
	}

	if (nDataID == CFGDATAID_APPID)
	{
		vValue.vt = VT_UI4;
		vValue.ulVal = m_dwAppID;
		return TRUE;
	}

	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg92Data::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
{
	VARIANT vCurr;

	if (nDataID == CFGDATAID_SRCMAC)
	{
		iecfg_GetCfgDataValueMac(m_strSrcAddress, vCurr);
		return (vCurr.ullVal == vValue.ullVal);
	}

	if (nDataID == CFGDATAID_DESTMAC)
	{
		iecfg_GetCfgDataValueMac(m_strDestAddress, vCurr);
		return (vCurr.ullVal == vValue.ullVal);
	}

	if (nDataID == CFGDATAID_APPID)
	{
		ASSERT (vValue.vt == VT_UI4);
		return (vValue.ulVal == m_dwAppID);
	}

	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#endif