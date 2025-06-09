//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasGout.cpp  CIecCfgDatasGout


#include "stdafx.h"
#include "IecCfgGoutDatas.h"

CIecCfgGoutDatas::CIecCfgGoutDatas()
{
	//初始化属性

	//初始化成员变量
}

CIecCfgGoutDatas::~CIecCfgGoutDatas()
{
}

long CIecCfgGoutDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgGoutDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfgGoutDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDatasBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgGoutDatas *p = (CIecCfgGoutDatas*)pObj;

	return TRUE;
}

BOOL CIecCfgGoutDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDatasBase::CopyOwn(pDest);

	CIecCfgGoutDatas *p = (CIecCfgGoutDatas*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgGoutDatas::Clone()
{
	CIecCfgGoutDatas *p = new CIecCfgGoutDatas();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgGoutDatas::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CExBaseObject *pNew = new CIecCfgGoutDatas();
	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}
	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	
	return pNew;
}

CExBaseObject* CIecCfgGoutDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgDataGoutKey)
	{
		pNew = new CIecCfgGoutData();
	}

	return pNew;
}


CIecCfgDataBase* CIecCfgGoutDatas::CreateIecCfgData()
{
	CIecCfgDataBase *pNew = new CIecCfgGoutData();
	return pNew;
}


UINT CIecCfgGoutDatas::GetIecCfgDataClassID()
{
	return CFGCLASSID_CIECCFGGOUTDATA;
}

BOOL CIecCfgGoutDatas::ValidateFiberIndex(CIecCfgDataBase *pData)
{
	return TRUE;
}


BOOL CIecCfgGoutDatas::ValidateFiberIndex()
{
	return TRUE;
}

CIecCfgDataBase* CIecCfgGoutDatas::FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	CIecCfgGoutData* pCfgGoutData = NULL;
	CString strDstMac,strSrcMac;

	POS pos = oList.GetHeadPosition();
	while (pos)
	{
		pCfgGoutData = (CIecCfgGoutData*)oList.GetNext(pos);

		if (pCfgGoutData->GetClassID() != CFGCLASSID_CIECCFGGOUTDATA || nCMT != PROTOCOL_61850_TYPE_GOOSEOUT)
		{
			continue;
		}

		strDstMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pDstMac[0], pDstMac[1], pDstMac[2], pDstMac[3], pDstMac[4], pDstMac[5]);
		strSrcMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pSrcMac[0], pSrcMac[1], pSrcMac[2], pSrcMac[3], pSrcMac[4], pSrcMac[5]);

		if (pCfgGoutData->m_strDestAddress.CompareNoCase(strDstMac)==0 && pCfgGoutData->m_strSrcAddress.CompareNoCase(strSrcMac)==0 
			&& pCfgGoutData->m_dwAppID == nAPPID && pCfgGoutData->m_nChannelNum == nChCount)
		{
			return pCfgGoutData;
		}
	}

	return NULL;
}

BOOL CIecCfgGoutDatas::SetCfgDataGoutMap(const long nContrlBlockIndex,const long nFirstMapIndex,const long nMapNum)
{
	CIecCfgGoutData *pIecCfgData = (CIecCfgGoutData*)GetIecCfgData(nContrlBlockIndex);

	if (pIecCfgData == NULL)
	{
		return FALSE;
	}

	return pIecCfgData->SetCfgDataGoutMap(nFirstMapIndex,nMapNum);
}

BOOL CIecCfgGoutDatas::IsCfgData(CExBaseObject *pObj)
{
	return CIecCfgDatasBase::IsCfgData(pObj);
}

void CIecCfgGoutDatas::GenerateGouts_GroupDatas(CDataGroup *pGouts)
{
	POS pos = GetHeadPosition();
	CIecCfgGoutData *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgGoutData *)GetNext(pos);

		if (IsCfgData(p))
		{
			if (p->m_nUseFlag == 1)
			{
				p->GenerateGout_GroupDatas(pGouts);
			}
		}
	}
}

void CIecCfgGoutDatas::ReadGouts_GroupDatas(CDataGroup *pGouts)
{
	POS pos = GetHeadPosition();
	CIecCfgGoutData *p = NULL;
	long nIndex = 1;
	CString strGroupID;
	CDataGroup *pGoutGroup = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgGoutData *)GetNext(pos);

		if (IsCfgData(p))
		{
			if (p->m_nUseFlag == 1)
			{
				strGroupID.Format(_T("GOOSEPub%ld"),nIndex);
				pGoutGroup = (CDataGroup*)pGouts->FindByID(strGroupID);
				nIndex++;

				if (pGoutGroup != NULL)
				{
					p->ReadGout_GroupDatas(pGoutGroup);
				}
			}
		}
	}
}

CIecCfgDataBase* CIecCfgGoutDatas::FindByAppIDFiber(DWORD dwAppID,long nFiberIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfgGoutData* pIecCfgGoutData = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			pIecCfgGoutData = (CIecCfgGoutData*)p;

			if ((pIecCfgGoutData->m_dwAppID == dwAppID)&&(pIecCfgGoutData->m_nFiberIndex == nFiberIndex))
			{
				return pIecCfgGoutData;
			}
		}
	}

	return NULL;
}

BOOL CIecCfgGoutDatas::IsAppID_Repeat(DWORD dwAppID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfgGoutData* pIecCfgGoutData = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			pIecCfgGoutData = (CIecCfgGoutData*)p;

			if (pIecCfgGoutData->m_dwAppID == dwAppID)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfgGoutDatas::SetAT02D_ChannelID(CExBaseList *pGoutList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutData *pIecCfgGoutData = NULL;
	CIecCfgGoutData *pHistoryIecCfgGoutData = NULL;
	POS pos = GetHeadPosition();
//	long nGoutChIndex = 1;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			pIecCfgGoutData = (CIecCfgGoutData *)pCurObj;

			if (pIecCfgGoutData->m_nUseFlag)
			{
				pIecCfgGoutData->m_strName.Format(_T("0X%04X"),pIecCfgGoutData->m_dwAppID);
				pHistoryIecCfgGoutData = (CIecCfgGoutData*)pGoutList->FindByName(pIecCfgGoutData->m_strName);

				if (pHistoryIecCfgGoutData == NULL)
				{
					pIecCfgGoutData->SetAT02D_ChannelID(pGoutList,nCBIndex);
					pGoutList->AddTail(pIecCfgGoutData);
					nCBIndex++;
				} 
				else
				{
					pHistoryIecCfgGoutData->AT02D_MapChannelID(pIecCfgGoutData);
				}


//				pIecCfgGoutData->SetAT02D_ChannelID(pGoutList,nGoutChIndex);
			}
		}
	}
}

void CIecCfgGoutDatas::AddAT02D_dsGout(CDvmLogicDevice *pLDevice,long &nDatasetIndex)
{
//	SetAT02D_ChannelID();
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutData *pIecCfgGoutData = NULL;
	CDvmDataset *pCurDataset = NULL;
	POS pos = GetHeadPosition();
	CString strAppID;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			pIecCfgGoutData = (CIecCfgGoutData *)pCurObj;

			if (!pIecCfgGoutData->m_nUseFlag)
			{
				continue;
			}

			strAppID.Format(_T("0X%04X_dsGout"),pIecCfgGoutData->m_dwAppID);

			if (!HasCfgDataset_AT02D_Model(pLDevice,strAppID))
			{
				pCurDataset = new CDvmDataset;
				//			pCurDataset->m_strName.Format(_T("Gout数据集%ld"),nDatasetIndex);
				pCurDataset->m_strID.Format(_T("dsGout%ld"),nDatasetIndex);
				pIecCfgGoutData->m_strDvmDatasetID = pCurDataset->m_strID;
				pCurDataset->m_strName.Format(_T("0X%04X_%s"),pIecCfgGoutData->m_dwAppID,pCurDataset->m_strID.GetString());
				pIecCfgGoutData->AddAT02D_Dataset(pCurDataset);
				pLDevice->AddNewChild(pCurDataset);
				nDatasetIndex++;
			}
		}
	}
}

BOOL CIecCfgGoutDatas::IsAT02D_Invalid()
{
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutData *pIecCfgGoutData = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			pIecCfgGoutData = (CIecCfgGoutData *)pCurObj;

			CExBaseObject *pCurObjTmp = NULL;
			CIecCfgGoutData *pIecCfgGoutDataTmp = NULL;
			POS pos_tmp = GetHeadPosition();

			while(pos_tmp)
			{
				pCurObjTmp = GetNext(pos_tmp);

				if (pCurObjTmp->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
				{
					pIecCfgGoutDataTmp = (CIecCfgGoutData *)pCurObjTmp;

					if ((pIecCfgGoutDataTmp->m_dwAppID == pIecCfgGoutData->m_dwAppID)&&(pIecCfgGoutDataTmp->m_strDestAddress != pIecCfgGoutData->m_strDestAddress))
					{
#ifndef _PSX_IDE_QT_
						CString strMsg;
						strMsg.Format(_T("Gout配置中存在AppID(0x%04X)相同,目标MAC地址(%s!=%s)不一致的情况,请重新配置."),pIecCfgGoutDataTmp->m_dwAppID,pIecCfgGoutDataTmp->m_strDestAddress,pIecCfgGoutData->m_strDestAddress);
						CLogPrint::LogString(XLOGLEVEL_ERROR,strMsg);
						AfxMessageBox(strMsg/*, _T("提示"), MB_OK*/);
#endif
						return TRUE;
					}

					if ((pIecCfgGoutDataTmp->m_dwAppID != pIecCfgGoutData->m_dwAppID)&&(pIecCfgGoutDataTmp->m_strDestAddress == pIecCfgGoutData->m_strDestAddress))
					{
#ifndef _PSX_IDE_QT_
						CString strMsg;
						strMsg.Format(_T("Gout配置中存在目标MAC地址(%s)相同,AppID(0x%04X != 0x%04X)不一致的情况,请重新配置."),pIecCfgGoutData->m_strDestAddress,pIecCfgGoutDataTmp->m_dwAppID,pIecCfgGoutData->m_dwAppID);
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