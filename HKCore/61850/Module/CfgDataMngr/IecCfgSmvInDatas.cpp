//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasSMV.cpp  CIecCfgDatasSmvIn


#include "stdafx.h"
#include "IecCfgSmvInDatas.h"


CIecCfgDatasSmvIn::CIecCfgDatasSmvIn()
{
	m_strSmvType = g_strSmvType6044Common;
//	SetSmvType(SMVTYPE_6044_COMMON);
}

CIecCfgDatasSmvIn::~CIecCfgDatasSmvIn()
{
}

long CIecCfgDatasSmvIn::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasSMV::XmlReadOwn(oNode, pXmlRWKeys);
	return 0;
}

long CIecCfgDatasSmvIn::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasSMV::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	return 0;
}

BOOL CIecCfgDatasSmvIn::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDatasSMV::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDatasSmvIn::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDatasSMV::CopyOwn(pDest);
	return TRUE;
}

CBaseObject* CIecCfgDatasSmvIn::Clone()
{
	CIecCfgDatasSmvIn *p = new CIecCfgDatasSmvIn();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgDatasSmvIn::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


// 	if (strClassID == pXmlKeys->m_strCIecCfgData91Key)
// 	{
// 		pNew = new CIecCfg91Data();
// 	}
	/*else*/ if (strClassID == pXmlKeys->m_strCIecCfgData92InKey)
	{
		pNew = new CIecCfg92InData();
	}
// 	else if (strClassID == pXmlKeys->m_strCIecCfgData6044Key)
// 	{
// 		pNew = new CIecCfg6044Data();
// 	}
 	else if (strClassID == pXmlKeys->m_strCIecCfgData6044CommonInKey)
 	{
 		pNew = new CIecCfg6044CommonInData();
 	}
	else if (strClassID == pXmlKeys->m_strCIecCfgData2MInKey)
	{
		pNew = new CIecCfg2MInData();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgSmvRatesKey)
	{
		pNew = new CIecCfgSmvRates();
	}

	return pNew;
}


CIecCfgDataBase* CIecCfgDatasSmvIn::CreateIecCfgData()
{
	long nSmvType = iecfg_GetSmvTypeByString(m_strSmvType);

	CIecCfgSmvDataBase *pNew = NULL;

	switch (nSmvType)
	{
// 	case SMVTYPE_91:
// 		pNew = new CIecCfg91Data();
// 		break;

	case SMVTYPE_92:
		pNew = new CIecCfg92InData();
		break;

// 	case SMVTYPE_6044:
// 		pNew = new CIecCfg6044Data();
// 		break;
// 
 	case SMVTYPE_6044_COMMON:
 		pNew = new CIecCfg6044CommonInData();
 		break;
	case SMVTYPE_2M:
		pNew = new CIecCfg2MInData();
		break;

	default:
		pNew = new CIecCfg92InData();
		break;
	}

	pNew->InitByCommData(&m_oIecCfgDataSmvCommon);
//	pNew->SetChannelNum(STSMV_CHANNEL_NUM);

	return pNew;
}


void CIecCfgDatasSmvIn::InitAfterRead()
{
	CIecCfgDatasSMV::InitAfterRead();
}

UINT CIecCfgDatasSmvIn::GetIecCfgDataClassID()
{
	long nSmvType = iecfg_GetSmvTypeByString(m_strSmvType);

	switch (nSmvType)
	{
// 	case SMVTYPE_91:
// 		return CFGCLASSID_CIECCFG91DATA;
// 		break;

	case SMVTYPE_92:
		return CFGCLASSID_CIECCFG92INPUTDATA;
		break;

// 	case SMVTYPE_6044:
// 		return CFGCLASSID_CIECCFG6044DATA;
// 		break;
// 
 	case SMVTYPE_6044_COMMON:
		return CFGCLASSID_CIECCFG6044COMMONINDATA;
 		break;
	case SMVTYPE_2M:
		return CFGCLASSID_CIECCFG2MINDATA;
		break;

	default:
		return CFGCLASSID_CIECCFG92INPUTDATA;
		break;
	}

	return CFGCLASSID_CIECCFG92INPUTDATA;
}

long CIecCfgDatasSmvIn::GetCurSmvTypeClassID()
{
	//return ((nClassID == CFGCLASSID_CIECCFG91DATA) //zhouhj 20211015 修改用于适应在切换FT3与9-2不删除当前数据对象
	//	|| (nClassID == CFGCLASSID_CIECCFG92DATA)
	//	|| (nClassID == CFGCLASSID_CIECCFG6044DATA) 
	//	|| (nClassID == CFGCLASSID_CIECCFG6044COMMONDATA));

	long nSmvType = GetSmvType();

// 	if (nSmvType == SMVTYPE_91)
// 	{
// 		return CFGCLASSID_CIECCFG91DATA;
// 	}
	/*else*/ if (nSmvType == SMVTYPE_92)
	{
		return CFGCLASSID_CIECCFG92INPUTDATA;
	}
	else if (nSmvType == SMVTYPE_2M)
	{
		return CFGCLASSID_CIECCFG2MINDATA;
	}
// 	else if (nSmvType == SMVTYPE_6044)
// 	{
// 		return CFGCLASSID_CIECCFG6044DATA;
// 	}
 	else if (nSmvType == SMVTYPE_6044_COMMON)
 	{
 		return CFGCLASSID_CIECCFG6044COMMONINDATA;
 	}

	return -1;
}

long CIecCfgDatasSmvIn::GetMaxCfgDataCount(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFG92INPUTDATA)
	{
		return g_nIecCfgSmvOut_91_92MaxNum;
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044COMMONINDATA)
	{
		return g_nIecCfgSmvOut_60044MaxNum;
	}
	else if (nClassID == CFGCLASSID_CIECCFG2MINDATA)
	{
		return g_nIecCfgSmvOut_60044MaxNum;
	}

	return g_nIecCfgSmvOut_91_92MaxNum;
}

void CIecCfgDatasSmvIn::ChangePosition(long nIndex1, long nIndex2)
{
	CIecCfgDatasSMV::ChangePosition(nIndex1,nIndex2);
}

BOOL CIecCfgDatasSmvIn::ValidateFiberIndex(CIecCfgDataBase *pData)
{
	return CIecCfgDatasSMV::ValidateFiberIndex(pData);
}


BOOL CIecCfgDatasSmvIn::ValidateFiberIndex()
{
	return CIecCfgDatasSMV::ValidateFiberIndex();
}

CIecCfgDataBase* CIecCfgDatasSmvIn::FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount)
{
	return CIecCfgDatasSMV::FindIecCfgData(pDstMac,pSrcMac,nAPPID,nCMT,nChCount);
}

BOOL CIecCfgDatasSmvIn::IsAppID_Repeat(DWORD dwAppID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfg92Data* pCfg92Data = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
		{
			pCfg92Data = (CIecCfg92Data*)p;

			if (pCfg92Data->m_dwAppID == dwAppID)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

BOOL CIecCfgDatasSmvIn::IsSmvData_AllSmvType(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();

	if (nClassID == CFGCLASSID_CIECCFG92INPUTDATA)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044COMMONINDATA)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFG2MINDATA)
	{
		return TRUE;
	}

	return FALSE;
}

#ifdef _USE_IN_AT02D_MODE_
//#include "../IecCfgTool/IecCfgTool.h"

void CIecCfgDatasSmvIn::SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Data *pIecCfg92Data = NULL;
	CIecCfg92Data *pHistoryIecCfg92Data = NULL;
	POS pos = GetHeadPosition();
// 	long nDelayIndex = 1;
// 	long nCurChannelIndex = 1;
// 	long nVolChannelIndex = 1;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
		{
			pIecCfg92Data = (CIecCfg92Data *)pCurObj;

			if (!pIecCfg92Data->m_nUseFlag)
			{
				continue;
			}

			if (pIecCfg92Data->m_nUseFlag)
			{
				pIecCfg92Data->m_strName.Format(_T("0X%04X"),pIecCfg92Data->m_dwAppID);
				pHistoryIecCfg92Data = (CIecCfg92Data*)pSVList->FindByName(pIecCfg92Data->m_strName);

				if (pHistoryIecCfg92Data == NULL)
				{
					pIecCfg92Data->SetAT02D_ChannelID(pSVList,nCBIndex);
					pSVList->AddTail(pIecCfg92Data);
					nCBIndex++;
				} 
				else
				{
					pHistoryIecCfg92Data->AT02D_MapChannelID(pIecCfg92Data);
				}
			}
		}
	}
}

void CIecCfgDatasSmvIn::AddAT02D_dsSV(CDvmLogicDevice *pLDevice,long &nDatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas)
{
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Data *pIecCfg92Data = NULL;
	CDvmDataset *pCurDataset = NULL;
	POS pos = GetHeadPosition();
//	SetAT02D_ChannelID();
	CString strAppID;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
		{
			pIecCfg92Data = (CIecCfg92Data *)pCurObj;

			if (!pIecCfg92Data->m_nUseFlag)
			{
				continue;
			}

			strAppID.Format(_T("0X%04X_dsSV"),pIecCfg92Data->m_dwAppID);
			
			if (!HasCfgDataset_AT02D_Model(pLDevice,strAppID))
			{
				pCurDataset = new CDvmDataset;
				//			pCurDataset->m_strName.Format(_T("采样值数据集%ld"),nDatasetIndex);
				pCurDataset->m_strID.Format(_T("dsSV%ld"),nDatasetIndex);
				pIecCfg92Data->m_strDvmDatasetID = pCurDataset->m_strID;
				strAppID.Format(_T("0X%04X"),pIecCfg92Data->m_dwAppID);
				pCurDataset->m_strName.Format(_T("%s_%s"),strAppID.GetString(),pCurDataset->m_strID.GetString());
				pIecCfg92Data->AddAT02D_Dataset(pCurDataset,bHasHarm,bhasMUTestParas);
				pLDevice->AddNewChild(pCurDataset);
				nDatasetIndex++;
			}
		}
	}
}

BOOL CIecCfgDatasSmvIn::IsAT02D_Invalid()
{
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Data *pIecCfg92Data = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
		{
			pIecCfg92Data = (CIecCfg92Data *)pCurObj;

// 			if ((!pIecCfg92Data->HasCurAndVolChannelType())&&(CIecCfgTool::IsVerifyVolCurChannel()))
// 			{
// 				CString strMsg;
// 				strMsg.Format(_T("SMV配置中AppID(0x%04X),目标MAC地址(%s)对应控制块中只存在电压或电流通道,请重新配置."),pIecCfg92Data->m_dwAppID,pIecCfg92Data->m_strDestAddress);
// 				CLogPrint::LogString(XLOGLEVEL_ERROR,strMsg);
// 				AfxMessageBox(strMsg/*, _T("提示"), MB_OK*/);
// 				return TRUE;
// 			}

			CExBaseObject *pCurObjTmp = NULL;
			CIecCfg92Data *pIecCfg92DataTmp = NULL;
			POS pos_tmp = GetHeadPosition();

			while(pos_tmp)
			{
				pCurObjTmp = GetNext(pos_tmp);

				if (pCurObjTmp->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
				{
					pIecCfg92DataTmp = (CIecCfg92Data *)pCurObjTmp;

					if ((pIecCfg92DataTmp->m_dwAppID == pIecCfg92Data->m_dwAppID)&&(pIecCfg92DataTmp->m_strDestAddress != pIecCfg92Data->m_strDestAddress))
					{
#ifndef _PSX_IDE_QT_
						CString strMsg;
						strMsg.Format(_T("SMV配置中存在AppID(0x%04X)相同,目标MAC地址(%s!=%s)不一致的情况,请重新配置."),pIecCfg92DataTmp->m_dwAppID,pIecCfg92DataTmp->m_strDestAddress,pIecCfg92Data->m_strDestAddress);
						CLogPrint::LogString(XLOGLEVEL_ERROR,strMsg);
						AfxMessageBox(strMsg/*, _T("提示"), MB_OK*/);
#endif
						return TRUE;
					}

					if ((pIecCfg92DataTmp->m_dwAppID != pIecCfg92Data->m_dwAppID)&&(pIecCfg92DataTmp->m_strDestAddress == pIecCfg92Data->m_strDestAddress))
					{
#ifndef _PSX_IDE_QT_
						CString strMsg;
						strMsg.Format(_T("SMV配置中存在目标MAC地址(%s)相同,AppID(0x%04X != 0x%04X)不一致的情况,请重新配置."),pIecCfg92Data->m_strDestAddress,pIecCfg92DataTmp->m_dwAppID,pIecCfg92Data->m_dwAppID);
						CLogPrint::LogString(XLOGLEVEL_ERROR,strMsg);
						AfxMessageBox(strMsg/*, _T("提示"), MB_OK*/);
#endif
						return TRUE;
					}
				}
			}
		}
	}

	return FALSE;
}
#endif