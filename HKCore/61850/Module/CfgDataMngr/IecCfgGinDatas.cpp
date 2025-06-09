//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasGin.cpp  CIecCfgDatasGin


#include "stdafx.h"
#include "IecCfgGinDatas.h"

CIecCfgGinDatas::CIecCfgGinDatas()
{
	//初始化属性

	//初始化成员变量

	m_oIecCfgGinAppChMaps.SetParent(this);
}

CIecCfgGinDatas::~CIecCfgGinDatas()
{
}

long CIecCfgGinDatas::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgGinDatas::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	return 0;
}

BOOL CIecCfgGinDatas::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDatasBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgGinDatas *p = (CIecCfgGinDatas*)pObj;

	return TRUE;
}

BOOL CIecCfgGinDatas::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDatasBase::CopyOwn(pDest);

	CIecCfgGinDatas *p = (CIecCfgGinDatas*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgGinDatas::Clone()
{
	CIecCfgGinDatas *p = new CIecCfgGinDatas();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgGinDatas::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgDataGinKey)
	{
		pNew = new CIecCfgGinData();
	}

	return pNew;
}

void CIecCfgGinDatas::InitAfterRead()
{
	m_oIecCfgGinAppChMaps.InitDataTypes();
	InitGinAppChMaps();
}

void CIecCfgGinDatas::InitGinAppChMaps()
{
	m_oIecCfgGinAppChMaps.ReleaseMaps();
	m_oIecCfgGinAppChMaps.InitMaps(this);
}

CIecCfgDataBase* CIecCfgGinDatas::CreateIecCfgData()
{
	CIecCfgDataBase *pNew = new CIecCfgGinData();
	return pNew;
}

UINT CIecCfgGinDatas::GetIecCfgDataClassID()
{
	return CFGCLASSID_CIECCFGGINDATA;
}


BOOL CIecCfgGinDatas::ValidateFiberIndex(CIecCfgDataBase *pData)
{
	CExBaseList oListUseDatas;
	GetUseDatas(oListUseDatas);
	POS pos = NULL;
	CIecCfgDataBase *pCurr = NULL;
	BOOL bTrue = TRUE;

	long nIndex = oListUseDatas.FindIndex(pData);

	if (nIndex >= 8)
	{
		oListUseDatas.RemoveAll();
		return TRUE;
	}

	//只判断前8个
	while (oListUseDatas.GetCount() > 8)
	{
		pos = oListUseDatas.GetTailPosition();
		oListUseDatas.RemoveAt(pos);
	}

	pos = oListUseDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pCurr = (CIecCfgDataBase *)oListUseDatas.GetNext(pos);

		if (pCurr != pData)
		{
			if ((pCurr->m_nFiberIndex == pData->m_nFiberIndex)&&(((CIecCfgGinData*)pCurr)->m_dwAppID == ((CIecCfgGinData*)pData)->m_dwAppID))
			{
#ifdef NOT_USE_XLANGUAGE
                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【%s】与【%s】输出光口冲突"), pData->GetCfgDataShortName().GetString()
                                           , pCurr->GetCfgDataShortName().GetString());
#else
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_PortConflict.GetString()/*_T("【%s】与【%s】输出光口冲突")*/, pData->GetCfgDataShortName().GetString(), pCurr->GetCfgDataShortName().GetString());
#endif
				bTrue = FALSE;
				break;
			}
		}
	}

	oListUseDatas.RemoveAll();

	return TRUE;
}


BOOL CIecCfgGinDatas::ValidateFiberIndex()
{
	//前8个不能相同

	//后9~13个必须相同???

	return TRUE;
}

CIecCfgDataBase* CIecCfgGinDatas::FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	CIecCfgGinData* pCfgGinData = NULL;
	CString strDstMac,strSrcMac;

	POS pos = oList.GetHeadPosition();
	while (pos)
	{
		pCfgGinData = (CIecCfgGinData*)oList.GetNext(pos);

		if (pCfgGinData->GetClassID() != CFGCLASSID_CIECCFGGINDATA || nCMT != PROTOCOL_61850_TYPE_GOOSEIN)
		{
			continue;
		}

		strDstMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pDstMac[0], pDstMac[1], pDstMac[2], pDstMac[3], pDstMac[4], pDstMac[5]);
		strSrcMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pSrcMac[0], pSrcMac[1], pSrcMac[2], pSrcMac[3], pSrcMac[4], pSrcMac[5]);

		if (pCfgGinData->m_strDestAddress.CompareNoCase(strDstMac)==0 && pCfgGinData->m_strSrcAddress.CompareNoCase(strSrcMac)==0 
				&& pCfgGinData->m_dwAppID == nAPPID && pCfgGinData->m_nChannelNum == nChCount)
		{
			return pCfgGinData;
		}
	}

	return NULL;
}

BOOL CIecCfgGinDatas::SetCfgDataGinMap(const long nContrlBlockIndex,const long nFirstMapIndex,const long nMapNum)
{
	CIecCfgGinData *pIecCfgData = (CIecCfgGinData*)GetIecCfgData(nContrlBlockIndex);

	if (pIecCfgData == NULL)
	{
		return FALSE;
	}

	return pIecCfgData->SetCfgDataGinMap(nFirstMapIndex,nMapNum);
}

BOOL CIecCfgGinDatas::IsAppID_Repeat(DWORD dwAppID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfgGinData* pIecCfgGinData = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			pIecCfgGinData = (CIecCfgGinData*)p;

			if (pIecCfgGinData->m_dwAppID == dwAppID)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}
BOOL CIecCfgGinDatas::IsCfgData(CExBaseObject *pObj)
{
	return CIecCfgDatasBase::IsCfgData(pObj);
}
void CIecCfgGinDatas::GenerateGins_GroupDatas(CDataGroup *pGins)
{
	POS pos = GetHeadPosition();
	CIecCfgGinData *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgGinData *)GetNext(pos);

		if (IsCfgData(p))
		{
			if (p->m_nUseFlag == 1)
			{
				p->GenerateGin_GroupDatas(pGins);
			}
		}
	}
}
void CIecCfgGinDatas::ReadGins_GroupDatas(CDataGroup *pGins)
{
	POS pos = GetHeadPosition();
	CIecCfgGinData *p = NULL;
	long nIndex = 1;
	CString strGroupID;
	CDataGroup *pGinGroup = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgGinData *)GetNext(pos);

		if (IsCfgData(p))
		{
			if (p->m_nUseFlag == 1)
			{
				strGroupID.Format(_T("GOOSEGINPub%ld"),nIndex);
				pGinGroup = (CDataGroup*)pGins->FindByID(strGroupID);
				nIndex++;

				if (pGinGroup != NULL)
				{
					p->ReadGin_GroupDatas(pGinGroup);
				}
			}
		}
	}
}
CIecCfgDataBase* CIecCfgGinDatas::FindByAppIDFiber(DWORD dwAppID,long nFiberIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfgGinData* pIecCfgGinData = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			pIecCfgGinData = (CIecCfgGinData*)p;

			if ((pIecCfgGinData->m_dwAppID == dwAppID)&&(pIecCfgGinData->m_nFiberIndex == nFiberIndex))
			{
				return pIecCfgGinData;
			}
		}
	}

	return NULL;
}


#ifdef _USE_IN_AT02D_MODE_
void CIecCfgGinDatas::SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinData *pIecCfgGinData = NULL;
	CIecCfgGinData *pHistoryIecCfgGinData = NULL;
	POS pos = GetHeadPosition();
//	long nGinChIndex = 1;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			pIecCfgGinData = (CIecCfgGinData *)pCurObj;

			if (pIecCfgGinData->m_nUseFlag)
			{
				pIecCfgGinData->m_strName.Format(_T("0X%04X"),pIecCfgGinData->m_dwAppID);
				pHistoryIecCfgGinData = (CIecCfgGinData*)pGinList->FindByName(pIecCfgGinData->m_strName);

				if (pHistoryIecCfgGinData == NULL)
				{
					pIecCfgGinData->SetAT02D_ChannelID(pGinList,nCBIndex);
					pGinList->AddTail(pIecCfgGinData);
					nCBIndex++;
				} 
				else
				{
					pHistoryIecCfgGinData->AT02D_MapChannelID(pIecCfgGinData);
				}

//				pIecCfgGinData->SetAT02D_ChannelID(pGinList,nGinChIndex);
			}
		}
	}
}

void CIecCfgGinDatas::AddAT02D_dsGin(CDvmLogicDevice *pLDevice,long &nDatasetIndex)
{
//	SetAT02D_ChannelID();
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinData *pIecCfgGinData = NULL;
	CDvmDataset *pCurDataset = NULL;
	POS pos = GetHeadPosition();
	CString strAppID;

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			pIecCfgGinData = (CIecCfgGinData *)pCurObj;

			if (!pIecCfgGinData->m_nUseFlag)
			{
				continue;
			}

			strAppID.Format(_T("0X%04X_dsGin"),pIecCfgGinData->m_dwAppID);

			if (!HasCfgDataset_AT02D_Model(pLDevice,strAppID))
			{
				pCurDataset = new CDvmDataset;
				//			pCurDataset->m_strName.Format(_T("Gin数据集%ld"),nDatasetIndex);
				pCurDataset->m_strID.Format(_T("dsGin%ld"),nDatasetIndex);
				pIecCfgGinData->m_strDvmDatasetID = pCurDataset->m_strID;
                pCurDataset->m_strName.Format(_T("0X%04X_%s"),pIecCfgGinData->m_dwAppID,pCurDataset->m_strID.GetString());
				pIecCfgGinData->AddAT02D_Dataset(pCurDataset);
				pLDevice->AddNewChild(pCurDataset);
				nDatasetIndex++;
			}
		}
	}
}

BOOL CIecCfgGinDatas::IsAT02D_Invalid()
{
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinData *pIecCfgGinData = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			pIecCfgGinData = (CIecCfgGinData *)pCurObj;

			CExBaseObject *pCurObjTmp = NULL;
			CIecCfgGinData *pIecCfgGinDataTmp = NULL;
			POS pos_tmp = GetHeadPosition();

			while(pos_tmp)
			{
				pCurObjTmp = GetNext(pos_tmp);

				if (pCurObjTmp->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
				{
					pIecCfgGinDataTmp = (CIecCfgGinData *)pCurObjTmp;

					if ((pIecCfgGinDataTmp->m_dwAppID == pIecCfgGinData->m_dwAppID)&&(pIecCfgGinDataTmp->m_strDestAddress != pIecCfgGinData->m_strDestAddress))
					{
#ifndef _PSX_IDE_QT_
						CString strMsg;
						strMsg.Format(_T("Gin配置中存在AppID(0x%04X)相同,目标MAC地址(%s!=%s)不一致的情况,请重新配置."),pIecCfgGinDataTmp->m_dwAppID,pIecCfgGinDataTmp->m_strDestAddress,pIecCfgGinData->m_strDestAddress);
						CLogPrint::LogString(XLOGLEVEL_ERROR,strMsg);
						AfxMessageBox(strMsg/*, _T("提示"), MB_OK*/);
#endif
						return TRUE;
					}

					if ((pIecCfgGinDataTmp->m_dwAppID != pIecCfgGinData->m_dwAppID)&&(pIecCfgGinDataTmp->m_strDestAddress == pIecCfgGinData->m_strDestAddress))
					{
#ifndef _PSX_IDE_QT_
						CString strMsg;
						strMsg.Format(_T("Gin配置中存在目标MAC地址(%s)相同,AppID(0x%04X != 0x%04X)不一致的情况,请重新配置."),pIecCfgGinData->m_strDestAddress,pIecCfgGinDataTmp->m_dwAppID,pIecCfgGinData->m_dwAppID);
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
