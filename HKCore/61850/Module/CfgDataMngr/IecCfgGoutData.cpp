//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataGout.cpp  CIecCfgDataGout


#include "stdafx.h"
#include "IecCfgGoutData.h"
#include "IecCfgGinData.h"

CIecCfgGoutData::CIecCfgGoutData()
{
	//初始化属性
	m_nEntrust = 0;

	//初始化成员变量
	m_strID = _T("GOOSEOUT");
}

CIecCfgGoutData::~CIecCfgGoutData()
{
}

long CIecCfgGoutData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgGooseDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strEntrustKey, oNode, m_nEntrust);
	return 0;
}

long CIecCfgGoutData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgGooseDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strEntrustKey, oElement, m_nEntrust);
	return 0;
}

BOOL CIecCfgGoutData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgGooseDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgGoutData *p = (CIecCfgGoutData*)pObj;

	if(m_nEntrust != p->m_nEntrust)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgGoutData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgGooseDataBase::CopyOwn(pDest);

	CIecCfgGoutData *p = (CIecCfgGoutData*)pDest;

	p->m_nEntrust = m_nEntrust;
	return TRUE;
}

CBaseObject* CIecCfgGoutData::Clone()
{
	CIecCfgGoutData *p = new CIecCfgGoutData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgGoutData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChsGoutKey)
	{
		pNew = new CIecCfgGoutChs();
	}

	return pNew;
}


void CIecCfgGoutData::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHSGOUT);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfgGoutChs();
		AddNewChild(m_pCfgChs);
	}

	m_nChannelNum = m_pCfgChs->GetCount();
}

void CIecCfgGoutData::GenerateGout_GroupDatas(CDataGroup *pGoutChs)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

	CDataGroup *pGout = new CDataGroup;
	pGoutChs->AddNewChild(pGout);
	pGout->m_strName.Format(_T("GOOSEPub%ld"),pGoutChs->GetCount());
	pGout->m_strID = pGout->m_strName;
	pGout->m_strDataType = _T("GOOSEPub");
	CDvmData *pDvmData = new CDvmData;

	pGout->AddNewChild(pDvmData);
	pDvmData->m_strID = _T("CheckStatus");
	pDvmData->m_strName = _T("检修状态");
	pDvmData->m_strDataType = _T("number");
//	pDvmData->m_strValue = pIecCfgGoutCh->m_strDefaultValue;
	CIecCfgGoutData *pGoutData = (CIecCfgGoutData*)GetAncestor(CFGCLASSID_CIECCFGGOUTDATA);
	ASSERT(pGoutData);
	pDvmData->m_strValue.Format(_T("%ld"),pGoutData->m_bTest);

	CIecCfgGoutChs *pIecCfgGoutChs = (CIecCfgGoutChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	long nCurIndex = 1;
	POS pos = pIecCfgGoutChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGoutChs->GetNext(pos);

		pIecCfgGoutCh = (CIecCfgGoutCh*)pCurObj;

		if ((pIecCfgGoutCh->m_strDataType != _T("Timestamp"))&&(pIecCfgGoutCh->m_strAppChID.Find(_T("bout")) == -1))
		{
			pDvmData = new CDvmData;
			pGout->AddNewChild(pDvmData);
			pDvmData->m_strID.Format(_T("GooseChannel%ld"),nCurIndex);
			pDvmData->m_strName = pIecCfgGoutCh->m_strName;
			pDvmData->m_strFormat = pIecCfgGoutCh->m_strID;
			pDvmData->m_strDataType = pIecCfgGoutCh->m_strDataType;
			pDvmData->m_strValue = pIecCfgGoutCh->m_strDefaultValue;
		}

		nCurIndex++;
	}
}

BOOL CIecCfgGoutData::OpenCfgDefaultConfigFile()
{
	BOOL bRet = CIecCfgGooseDataBase::OpenCfgDefaultConfigFile();

	//打开缺省配置文件后,对外部描述等进行初始化,防止影响正常显示
	if (m_pCfgChs != NULL)
	{
		CIecCfgGoutCh *pIecCfgGoutCh = NULL;
		CExBaseObject *pCurObj = NULL;
		POS pos = m_pCfgChs->GetHeadPosition();

		while(pos)
		{
			pCurObj = m_pCfgChs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
			{
				pIecCfgGoutCh = (CIecCfgGoutCh*)pCurObj;
				pIecCfgGoutCh->m_strDescExternal = _T("");
				pIecCfgGoutCh->m_strAddrExternal = _T("");
				pIecCfgGoutCh->m_nIndexExternal = -1;
			}
		}
	}

	return bRet;
}


void CIecCfgGoutData::ReadGout_GroupDatas(CDataGroup *pGoutChs)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

	CDvmData *pCheckStatus = (CDvmData*)pGoutChs->FindByID(_T("CheckStatus"));

	if (pCheckStatus != NULL)
	{
		CIecCfgGoutData *pGoutData = (CIecCfgGoutData*)GetAncestor(CFGCLASSID_CIECCFGGOUTDATA);
		ASSERT(pGoutData);
		pGoutData->m_bTest = CString_To_long(pCheckStatus->m_strValue);
	}

	CDvmData *pDvmData = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	POS pos = pGoutChs->GetHeadPosition();
	CString strIndex;
	long nIndex = 0;

	while(pos)
	{
		pDvmData = (CDvmData *)pGoutChs->GetNext(pos);

		if (pDvmData->m_strID == _T("CheckStatus"))
		{
			continue;
		}

		strIndex = pDvmData->m_strID;
		strIndex.Replace(_T("GooseChannel"),_T(""));
		nIndex = CString_To_long(strIndex);
		pIecCfgGoutCh = (CIecCfgGoutCh*)m_pCfgChs->GetAtIndex(nIndex-1);//因为DvmData中通道从1开始编号,此处减去1

		if (pIecCfgGoutCh != NULL)
		{
			if (pIecCfgGoutCh->m_strDataType == pDvmData->m_strDataType)
			{
				pIecCfgGoutCh->m_strDefaultValue = pDvmData->m_strValue;
			}
		}
	}
}

BOOL CIecCfgGoutData::SetCfgDataGoutMap(const long &nFirstMapIndex,const long &nMapNum)
{
	if (m_pCfgChs == NULL)
	{
		return FALSE;
	}

	CIecCfgGoutChs *pIecCfgGoutChs = (CIecCfgGoutChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	long nCurIndex = 0;

	POS pos = pIecCfgGoutChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGoutChs->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
		{
			pIecCfgGoutCh = (CIecCfgGoutCh*)pCurObj;

			if ((pIecCfgGoutCh->m_strDataType == _T("BOOLEAN"))||(pIecCfgGoutCh->m_strDataType == _T("Dbpos")))
			{
				pIecCfgGoutCh->m_strAppChID.Format(_T("bout%ld"),(nFirstMapIndex+nCurIndex));
				nCurIndex++;
			}

			if (nCurIndex == nMapNum)
			{
				return TRUE;
			}
		}
	}

	CLogPrint::LogString(XLOGLEVEL_ERROR,_T("当前控制块中无\"BOOL\"或\"Dbpos\"数据类型."));
	return FALSE;
}


#ifdef _USE_IN_AT02D_MODE_
void CIecCfgGoutData::SetAT02D_ChannelID(CExBaseList *pGoutList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	if (m_pCfgChs != NULL)
	{
		((CIecCfgGoutChs*)m_pCfgChs)->SetAT02D_ChannelID(pGoutList,nCBIndex);
	}
}

void CIecCfgGoutData::AddAT02D_Dataset(CDvmDataset *pCurDataset)
{
	if (m_pCfgChs != NULL)
	{
		CIecCfgGoutChs *pIecCfgGoutChs = (CIecCfgGoutChs*)m_pCfgChs;
		CExBaseObject *pCurObj = NULL;
		CIecCfgGoutCh *pIecCfgGoutCh = NULL;
		POS pos = pIecCfgGoutChs->GetHeadPosition();

		while(pos)
		{
			pCurObj = pIecCfgGoutChs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
			{
				pIecCfgGoutCh = (CIecCfgGoutCh*)pCurObj;
				AT02D_AddChannelData(pCurDataset,pIecCfgGoutCh);
			}
		}
	}
}

void CIecCfgGoutData::AT02D_MapChannelID(CIecCfgGoutData *pIecCfgGoutData)
{
	if ((m_pCfgChs != NULL)&&(pIecCfgGoutData->m_pCfgChs != NULL))
	{
		CIecCfgGoutChs *pIecCfgGoutChs = (CIecCfgGoutChs*)m_pCfgChs;
		CIecCfgGoutChs *pNewIecCfgGoutChs = (CIecCfgGoutChs*)pIecCfgGoutData->m_pCfgChs;
		CExBaseObject *pCurObj = NULL;
		CIecCfgGoutCh *pIecCfgGoutCh = NULL;
		CExBaseObject *pNewCurObj = NULL;
		long nChannelIndex = 0;

		POS pos = pIecCfgGoutChs->GetHeadPosition();

		while(pos)
		{
			pCurObj = pIecCfgGoutChs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
			{
				pIecCfgGoutCh = (CIecCfgGoutCh*)pCurObj;
				pNewCurObj = pNewIecCfgGoutChs->GetAtIndex(nChannelIndex);

				if ((pNewCurObj!=NULL)&&(pNewCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH))
				{
//					((CIecCfgGoutCh*)pNewCurObj)->m_strAppChID = pIecCfgGoutCh->m_strAppChID;
					pNewCurObj->m_strID = pIecCfgGoutCh->m_strID;
				}
			}

			nChannelIndex++;
		}
	}
}

long CIecCfgGoutData::GetAppChIDGin_Index(const CString &strAppID_Index)
{
	CString strTmp,strTmp1;
	long nIndex = strAppID_Index.Find(';');

	if (nIndex < 5)
	{
		return 0;
	}

	strTmp = strAppID_Index.Left(nIndex);

	if ((strTmp.GetAt(3)>='0')&&(strTmp.GetAt(3)<='9'))
	{
		strTmp1 = strTmp.Mid(3);
		nIndex = CString_To_long(strTmp1);
	}
	else if ((strTmp.GetAt(5)>='0')&&(strTmp.GetAt(5)<='9'))
	{
		strTmp1 = strTmp.Mid(5);
		nIndex = CString_To_long(strTmp1);
	}
	else
		nIndex = 0;

	return nIndex;
}

void CIecCfgGoutData::AT02D_AddChannelData(CDvmDataset *pCurDataset,CIecCfgGoutCh *pIecCfgGoutCh)
{
	CDvmData *pDvmData = new CDvmData; //20220610 zhouhj 所有通道都创建data对象,只有单点和双点对象结构保持genAT02D一致
	//pDvmData->m_strDataType = _T("STRUCT")/*pIecCfgGoutCh->m_strDataType*/;
	//shaolei 20220518
	pDvmData->InitDataTypeByGsData(pIecCfgGoutCh->m_strDataType);
	pDvmData->m_strName = pIecCfgGoutCh->m_strName;
	pDvmData->m_strID = pIecCfgGoutCh->m_strID;
	pDvmData->m_nIndex = pIecCfgGoutCh->m_nIndex;
	pCurDataset->AddNewChild(pDvmData);
	CDvmValue *pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("通道值");
	pDvmValue->m_strID.Format(_T("%s$stVal"),pDvmData->m_strID.GetString());
	pDvmData->AddNewChild(pDvmValue);

	if ((pIecCfgGoutCh->m_strDataType != _T("BOOLEAN"))&&(pIecCfgGoutCh->m_strDataType != _T("Dbpos")))
	{
		return;
	}

// 	CDvmValue *pDvmQValue = new CDvmValue; //20220610 zhouhj 暂时去除品质和时间,其为单独的通道
// 	pDvmQValue->m_strName = _T("品质");
// 	pDvmQValue->m_strID.Format(_T("%s$q"),pDvmData->m_strID.GetString());
// 	pDvmQValue->m_strValue = _T("0000000000000");
// 	pDvmQValue->m_strDataType = _T("BIT_STR");
// 	CDvmValue *pDvmTValue = new CDvmValue;
// 	pDvmTValue->m_strName = _T("时间");
// 	pDvmTValue->m_strID.Format(_T("%s$t"),pDvmData->m_strID.GetString());
// 	pDvmTValue->m_strValue = _T("1970-1-1 8-0-0-0");
// 	pDvmTValue->m_strDataType = _T("UTC_TIME");

	CDvmValue *pMapValue = new CDvmValue;
	pMapValue->m_strName = _T("测试仪通道映射");
	pMapValue->m_strID.Format(_T("%s$map"),pDvmData->m_strID.GetString());
	pMapValue->m_strValue = pIecCfgGoutCh->m_strAppChID;
	pMapValue->m_strDataType = _T("string");

	CDvmValue *pMapValueEx = new CDvmValue;
	pMapValueEx->m_strName = _T("装置通道映射");
	pMapValueEx->m_strID.Format(_T("%s$devmap"),pDvmData->m_strID.GetString());
	pMapValueEx->m_strValue = pIecCfgGoutCh->m_strDevChID;
	pMapValueEx->m_strDataType = _T("string");

// 	pDvmData->AddNewChild(pDvmQValue);
// 	pDvmData->AddNewChild(pDvmTValue);
	pDvmData->AddNewChild(pMapValue);
	pDvmData->AddNewChild(pMapValueEx);

	if (pIecCfgGoutCh->m_strDataType == _T("BOOLEAN"))
	{
		pDvmValue->m_strDataType = _T("BOOL");
		pDvmValue->m_strValue = _T("FALSE");
	}
	else if (pIecCfgGoutCh->m_strDataType == _T("Dbpos"))
	{
		pDvmValue->m_strDataType = _T("Dbpos");
		pDvmValue->m_strValue = _T("[01]");
	}
// 	else if ((pIecCfgGoutCh->m_strDataType == _T("INT32"))||(pIecCfgGoutCh->m_strDataType == _T("INT32U")))
// 	{
// 		pDvmData->m_strValue = _T("0");
// 	}
// 	else if (pIecCfgGoutCh->m_strDataType == _T("Quality"))
// 	{
// 		pDvmData->m_strValue = _T("[1000000000000]");
// 	}
// 	else if (pIecCfgGoutCh->m_strDataType == _T("FLOAT32"))
// 	{
// 		pDvmData->m_strValue = _T("0.00");
// 	}
}

void CIecCfgGoutData::AT02D_CopyToGinData(CExBaseList *pGinData)
{
	if ((pGinData == NULL)||(pGinData->GetClassID() != CFGCLASSID_CIECCFGGINDATA) ||(m_pCfgChs == NULL))
	{
		return;
	}	
	
	CIecCfgGinData *pIecCfgGinData = (CIecCfgGinData*)pGinData;
	pIecCfgGinData->DeleteAll();
	pIecCfgGinData->m_pCfgChs = NULL;
	CIecCfgGooseDataBase::CopyOwn(pGinData);
	CIecCfgGinChs *pIecCfgGinChs = new CIecCfgGinChs;
	pIecCfgGinData->m_pCfgChs = pIecCfgGinChs;
	pIecCfgGinData->AddNewChild(pIecCfgGinChs);
	CIecCfgGoutChs *pIecCfgGoutChs = (CIecCfgGoutChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	CExBaseObject *pNewCurObj = NULL;

	POS pos = pIecCfgGoutChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGoutChs->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTCH)
		{
			pIecCfgGoutCh = (CIecCfgGoutCh*)pCurObj;
			pIecCfgGinCh = new CIecCfgGinCh;
			pIecCfgGinCh->m_strName = pIecCfgGoutCh->m_strName;
			pIecCfgGinCh->m_strID = pIecCfgGoutCh->m_strID;
			pIecCfgGinCh->m_nUseFlag = pIecCfgGoutCh->m_nUseFlag;
			pIecCfgGinCh->m_nIndex = pIecCfgGoutCh->m_nIndex;
			pIecCfgGinCh->m_strDataType = pIecCfgGoutCh->m_strDataType;

			if (pIecCfgGoutCh->m_strAppChID.Find("bout") != -1)
			{
				pIecCfgGinCh->m_strAppChID = pIecCfgGoutCh->m_strAppChID;
				pIecCfgGinCh->m_strAppChID.Replace("bout","bin");
				pIecCfgGinCh->m_strAppChID.AppendFormat(";");
			}
			else
				pIecCfgGinCh->m_strAppChID = _T("none");

			pIecCfgGinChs->AddNewChild(pIecCfgGinCh);
		}
	}
}
#endif