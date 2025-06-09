//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataGin.cpp  CIecCfgDataGin


#include "stdafx.h"
#include "IecCfgGinData.h"
#include "IecCfgGoutData.h"

CIecCfgGinData::CIecCfgGinData()
{
	//初始化属性
	m_nUseMacSrcAddr = 0;
	m_nUseMacDestAddr = 0;
	m_nUseDataSet = 0;
	m_nUseAppID = 0;
	m_nUseGocbRef = 0;
	m_nUseGooseID = 0;

	//初始化成员变量
	m_strID = _T("GOOSEIN");
	m_nAnalyze = FALSE;

}

CIecCfgGinData::~CIecCfgGinData()
{
}

long CIecCfgGinData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgGooseDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseMacSrcAddrKey, oNode, m_nUseMacSrcAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strUseMacDestAddrKey, oNode, m_nUseMacDestAddr);
	xml_GetAttibuteValue(pXmlKeys->m_strUseDataSetKey, oNode, m_nUseDataSet);
	xml_GetAttibuteValue(pXmlKeys->m_strUseAppIDKey, oNode, m_nUseAppID);
	xml_GetAttibuteValue(pXmlKeys->m_strUseGocbRefKey, oNode, m_nUseGocbRef);
	xml_GetAttibuteValue(pXmlKeys->m_strUseGooseIDKey, oNode, m_nUseGooseID);

	if (xml_GetAttibuteValue(pXmlKeys->m_strAnalyzeKey, oNode, m_nAnalyze))
	{
		m_nUseAppID = m_nAnalyze;
		m_nUseGocbRef = m_nAnalyze;
		m_nUseGooseID = m_nAnalyze;
	}
	else
	{
		m_nAnalyze = m_nUseGooseID;
	}

	return 0;
}

long CIecCfgGinData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgGooseDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUseMacSrcAddrKey, oElement, m_nUseMacSrcAddr);
	xml_SetAttributeValue(pXmlKeys->m_strUseMacDestAddrKey, oElement, m_nUseMacDestAddr);
	xml_SetAttributeValue(pXmlKeys->m_strUseDataSetKey, oElement, m_nUseDataSet);
	xml_SetAttributeValue(pXmlKeys->m_strUseAppIDKey, oElement, m_nUseAppID);
	xml_SetAttributeValue(pXmlKeys->m_strUseGocbRefKey, oElement, m_nUseGocbRef);
	xml_SetAttributeValue(pXmlKeys->m_strUseGooseIDKey, oElement, m_nUseGooseID);
	//xml_SetAttributeValue(pXmlKeys->m_strAnalyzeKey, oElement, m_nAnalyze);

	return 0;
}

BOOL CIecCfgGinData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgGooseDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgGinData *p = (CIecCfgGinData*)pObj;

	if(m_nUseMacSrcAddr != p->m_nUseMacSrcAddr)
	{
		return FALSE;
	}

	if(m_nUseMacDestAddr != p->m_nUseMacDestAddr)
	{
		return FALSE;
	}

	if(m_nUseDataSet != p->m_nUseDataSet)
	{
		return FALSE;
	}

	if(m_nUseAppID != p->m_nUseAppID)
	{
		return FALSE;
	}

	if(m_nUseGocbRef != p->m_nUseGocbRef)
	{
		return FALSE;
	}

	if(m_nUseGooseID != p->m_nUseGooseID)
	{
		return FALSE;
	}

	if(m_nAnalyze != p->m_nAnalyze)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgGinData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgGooseDataBase::CopyOwn(pDest);

	CIecCfgGinData *p = (CIecCfgGinData*)pDest;

	p->m_nUseMacSrcAddr = m_nUseMacSrcAddr;
	p->m_nUseMacDestAddr = m_nUseMacDestAddr;
	p->m_nUseDataSet = m_nUseDataSet;
	p->m_nUseAppID = m_nUseAppID;
	p->m_nUseGocbRef = m_nUseGocbRef;
	p->m_nUseGooseID = m_nUseGooseID;
	p->m_nAnalyze = m_nAnalyze;
	return TRUE;
}

CBaseObject* CIecCfgGinData::Clone()
{
	CIecCfgGinData *p = new CIecCfgGinData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgGinData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChsGinKey)
	{
		pNew = new CIecCfgGinChs();
	}

	return pNew;
}


void CIecCfgGinData::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHSGIN);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfgGinChs();
		AddNewChild(m_pCfgChs);
	}

	m_nChannelNum = m_pCfgChs->GetCount();
}

BOOL CIecCfgGinData::SetChMap(const CString &strChDesc,long nChMapIndex)
{
	if (m_pCfgChs == NULL)
	{
		return FALSE;
	}

	CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	POS pos = pIecCfgGinChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGinChs->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH)
		{
			pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;

			if ((pIecCfgGinCh->m_strDataType != _T("BOOLEAN"))&&(pIecCfgGinCh->m_strDataType != _T("Dbpos")))
			{
				continue;
			}

			if (pIecCfgGinCh->m_strName.Find(strChDesc) != -1)
			{
				pIecCfgGinCh->m_strAppChID.Format(_T("bin%ld;"),nChMapIndex);
				return TRUE;
			}
		}
	}

	return FALSE;
}

void CIecCfgGinData::InitBinChMaps()
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

	CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	POS pos = pIecCfgGinChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGinChs->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH)
		{
			pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;
			pIecCfgGinCh->InitDataTypeName(TRUE);
		}
	}
}

void CIecCfgGinData::CopyToGoutData(CIecCfgGooseDataBase *pGoutData)
{
	CIecCfgGooseDataBase::CopyOwn(pGoutData);
	pGoutData->SetChannelNum(m_nChannelNum);

	if ((m_pCfgChs == NULL)||(pGoutData->m_pCfgChs == NULL))
	{
		return;
	}

	CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	CIecCfgDataGooseChBase *pIecCfgGoutCh = NULL;
	long nCurIndex = 0;
	POS pos = pIecCfgGinChs->GetHeadPosition();

	while(pos)
	{
		pIecCfgGinCh = (CIecCfgGinCh*)pIecCfgGinChs->GetNext(pos);
		pIecCfgGoutCh = (CIecCfgDataGooseChBase *)pGoutData->m_pCfgChs->GetAt(nCurIndex);

		if (pIecCfgGoutCh != NULL)
		{
			pIecCfgGinCh->CopyToGoutCh(pIecCfgGoutCh);
		}

		nCurIndex++;
	}
}

BOOL CIecCfgGinData::SetCfgDataGinMap(const long &nFirstMapIndex,const long &nMapNum)
{
	if (m_pCfgChs == NULL)
	{
		return FALSE;
	}

	CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	CDvmData *pDvmData = NULL;
	CDvmValue *pDvmValue = NULL;
	long nCurIndex = 0;


	POS pos = pIecCfgGinChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGinChs->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH)
		{
			pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;

			if ((pIecCfgGinCh->m_strDataType == _T("BOOLEAN"))||(pIecCfgGinCh->m_strDataType == _T("Dbpos")))
			{
				pIecCfgGinCh->m_strAppChID.Format(_T("bin%ld;"),(nFirstMapIndex+nCurIndex));
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

void CIecCfgGinData::GenerateGin_GroupDatas(CDataGroup *pGinChs)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

	CDataGroup *pGin = new CDataGroup;
	pGinChs->AddNewChild(pGin);
	pGin->m_strName.Format(_T("GOOSEGinPub%ld"),pGinChs->GetCount());
	pGin->m_strID = pGin->m_strName;
	pGin->m_strDataType = _T("GOOSEPub");
	CDvmData *pDvmData = new CDvmData;

	pGin->AddNewChild(pDvmData);
	pDvmData->m_strID = _T("CheckStatus");
	pDvmData->m_strName = _T("检修状态");
	pDvmData->m_strDataType = _T("number");
	//	pDvmData->m_strValue = pIecCfgGoutCh->m_strDefaultValue;
	CIecCfgGinData *pGinData = (CIecCfgGinData*)GetAncestor(CFGCLASSID_CIECCFGGINDATA);
	ASSERT(pGinData);
	pDvmData->m_strValue.Format(_T("%ld"),pGinData->m_bTest);

	CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	long nCurIndex = 1;
	POS pos = pIecCfgGinChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGinChs->GetNext(pos);

		pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;

		if ((pIecCfgGinCh->m_strDataType != _T("Timestamp"))&&(pIecCfgGinCh->m_strAppChID.Find(_T("bin")) == -1))
		{
			pDvmData = new CDvmData;
			pGin->AddNewChild(pDvmData);
			pDvmData->m_strID.Format(_T("GooseChannel%ld"),nCurIndex);
			pDvmData->m_strName = pIecCfgGinCh->m_strName;
			pDvmData->m_strFormat = pIecCfgGinCh->m_strID;
			pDvmData->m_strDataType = pIecCfgGinCh->m_strDataType;
			pDvmData->m_strValue = pIecCfgGinCh->m_strDefaultValue;
		}

		nCurIndex++;
	}
}
void CIecCfgGinData::ReadGin_GroupDatas(CDataGroup *pGinChs)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}
	CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
	CDvmData *pCheckStatus = (CDvmData*)pGinChs->FindByID(_T("CheckStatus"));

	if (pCheckStatus != NULL)
	{
		CIecCfgGinData *pGoutData = (CIecCfgGinData*)GetAncestor(CFGCLASSID_CIECCFGGINDATA);
		ASSERT(pGoutData);
		pGoutData->m_bTest = CString_To_long(pCheckStatus->m_strValue);
	}

	CDvmData *pDvmData = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	POS pos = pGinChs->GetHeadPosition();
	CString strIndex;
	long nIndex = 0;

	while(pos)
	{
		pDvmData = (CDvmData *)pGinChs->GetNext(pos);

		strIndex = pDvmData->m_strID;
		strIndex.Replace(_T("GooseChannel"),_T(""));
		nIndex = CString_To_long(strIndex);
		pIecCfgGinCh = (CIecCfgGinCh*)m_pCfgChs->GetAtIndex(nIndex-1);//因为DvmData中通道从1开始编号,此处减去1

		if (pIecCfgGinCh != NULL)
		{
			if (pIecCfgGinCh->m_strDataType == pDvmData->m_strDataType)
			{
				pIecCfgGinCh->m_strDefaultValue = pDvmData->m_strValue;
			}
		}
	}
}


#ifdef _USE_IN_AT02D_MODE_
void CIecCfgGinData::SetAT02D_ChannelID(CExBaseList *pGinList,long &nCBIndex)//周宏军 20200616  增加AT02配置
{
	if (m_pCfgChs != NULL)
	{
		((CIecCfgGinChs*)m_pCfgChs)->SetAT02D_ChannelID(pGinList,nCBIndex);
	}
}

void CIecCfgGinData::AddAT02D_Dataset(CDvmDataset *pCurDataset)
{
	if (m_pCfgChs != NULL)
	{
		CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
		CExBaseObject *pCurObj = NULL;
		CIecCfgGinCh *pIecCfgGinCh = NULL;
		CDvmData *pDvmData = NULL;
		CDvmValue *pDvmValue = NULL;

		POS pos = pIecCfgGinChs->GetHeadPosition();

		while(pos)
		{
			pCurObj = pIecCfgGinChs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH)
			{
				pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;
				AT02D_AddChannelData(pCurDataset,pIecCfgGinCh);
			}
		}
	}
}

void CIecCfgGinData::AT02D_AddChannelData(CDvmDataset *pCurDataset,CIecCfgGinCh *pIecCfgGinCh)
{
	CDvmData *pDvmData = new CDvmData;
	//pDvmData->m_strDataType = _T("STRUCT")/*pIecCfgGinCh->m_strDataType*/;
	//shaolei 20220518
	pDvmData->InitDataTypeByGsData(pIecCfgGinCh->m_strDataType);
	pDvmData->m_strName = pIecCfgGinCh->m_strName;
	pDvmData->m_strID = pIecCfgGinCh->m_strID;
	pDvmData->m_nIndex = pIecCfgGinCh->m_nIndex;
	pCurDataset->AddNewChild(pDvmData);

	if ((pIecCfgGinCh->m_strDataType != _T("BOOLEAN"))&&(pIecCfgGinCh->m_strDataType != _T("Dbpos")))//20220915 zhouhj 总通道数与实际通道数一致,值在BOOL和DBPOS模式与之前兼容
	{
		return;
	}

	CDvmValue *pDvmValue = new CDvmValue;
	pDvmValue->m_strName = _T("通道值");
	pDvmValue->m_strID.Format(_T("%s$stVal"),pDvmData->m_strID.GetString());

	CDvmValue *pDvmQValue = new CDvmValue;
	pDvmQValue->m_strName = _T("品质");
	pDvmQValue->m_strID.Format(_T("%s$q"),pDvmData->m_strID.GetString());
	pDvmQValue->m_strValue = _T("0000000000000");
	pDvmQValue->m_strDataType = _T("BIT_STR");

	CDvmValue *pDvmTValue = new CDvmValue;
	pDvmTValue->m_strName = _T("时间");
	pDvmTValue->m_strID.Format(_T("%s$t"),pDvmData->m_strID.GetString());
	pDvmTValue->m_strValue = _T("1970-1-1 8-0-0-0");
	pDvmTValue->m_strDataType = _T("UTC_TIME");

	CDvmValue *pMapValue = new CDvmValue;
	pMapValue->m_strName = _T("测试仪通道映射");
	pMapValue->m_strID.Format(_T("%s$map"),pDvmData->m_strID.GetString());
	pMapValue->m_strValue = pIecCfgGinCh->m_strAppChID;
	pMapValue->m_strDataType = _T("string");

	CDvmValue *pMapValueEx = new CDvmValue;
	pMapValueEx->m_strName = _T("装置通道映射");
	pMapValueEx->m_strID.Format(_T("%s$devmap"),pDvmData->m_strID.GetString());
	pMapValueEx->m_strValue = pIecCfgGinCh->m_strDevChID;
	pMapValueEx->m_strDataType = _T("string");

	pDvmData->AddNewChild(pDvmValue);
	pDvmData->AddNewChild(pDvmQValue);
	pDvmData->AddNewChild(pDvmTValue);
	pDvmData->AddNewChild(pMapValue);
	pDvmData->AddNewChild(pMapValueEx);

	if (pIecCfgGinCh->m_strDataType == _T("BOOLEAN"))
	{
		pDvmValue->m_strDataType = _T("BOOL");
		pDvmValue->m_strValue = _T("FALSE");
	}
	else if (pIecCfgGinCh->m_strDataType == _T("Dbpos"))
	{
		pDvmValue->m_strDataType = _T("Dbpos");
		pDvmValue->m_strValue = _T("[01]");
	}
}

void CIecCfgGinData::AT02D_MapChannelID(CIecCfgGinData *pIecCfgGinData)
{
	if ((m_pCfgChs != NULL)&&(pIecCfgGinData->m_pCfgChs != NULL))
	{
		CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
		CIecCfgGinChs *pNewIecCfgGinChs = (CIecCfgGinChs*)pIecCfgGinData->m_pCfgChs;
		CExBaseObject *pCurObj = NULL;
		CIecCfgGinCh *pIecCfgGinCh = NULL;
		CExBaseObject *pNewCurObj = NULL;
		long nChannelIndex = 0;

		POS pos = pIecCfgGinChs->GetHeadPosition();

		while(pos)
		{
			pCurObj = pIecCfgGinChs->GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH)
			{
				pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;
				pNewCurObj = pNewIecCfgGinChs->GetAtIndex(nChannelIndex);

				if ((pNewCurObj!=NULL)&&(pNewCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH))
				{
//					((CIecCfgGinCh*)pNewCurObj)->m_strAppChID = pIecCfgGinCh->m_strAppChID;
					pNewCurObj->m_strID = pIecCfgGinCh->m_strID;
				}
			}

			nChannelIndex++;
		}
	}
}

long CIecCfgGinData::GetAppChIDGin_Index(const CString &strAppID_Index)
{
	CString strTmp,strTmp1;
	long nIndex = strAppID_Index.Find(';');

	if (nIndex < 4)
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

void CIecCfgGinData::AT02D_CopyToGoutData(CExBaseList *pGoutData)
{
	if ((pGoutData == NULL)||(pGoutData->GetClassID() != CFGCLASSID_CIECCFGGOUTDATA) ||(m_pCfgChs == NULL))
	{
		return;
	}

	CIecCfgGoutData *pIecCfgGoutData = (CIecCfgGoutData*)pGoutData;
	pIecCfgGoutData->DeleteAll();
	pIecCfgGoutData->m_pCfgChs = NULL;

	CIecCfgGooseDataBase::CopyOwn(pIecCfgGoutData);
	CIecCfgGoutChs *pIecCfgGoutChs = new CIecCfgGoutChs;
	pIecCfgGoutData->m_pCfgChs = pIecCfgGoutChs;
	pIecCfgGoutData->AddNewChild(pIecCfgGoutChs);
	CIecCfgGinChs *pIecCfgGinChs = (CIecCfgGinChs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfgGoutCh *pIecCfgGoutCh = NULL;
	CIecCfgGinCh *pIecCfgGinCh = NULL;
	CExBaseObject *pNewCurObj = NULL;

	POS pos = pIecCfgGinChs->GetHeadPosition();

	while(pos)
	{
		pCurObj = pIecCfgGinChs->GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINCH)
		{
			pIecCfgGinCh = (CIecCfgGinCh*)pCurObj;
			pIecCfgGoutCh = new CIecCfgGoutCh;
			pIecCfgGoutCh->m_strName = pIecCfgGinCh->m_strName;
			pIecCfgGoutCh->m_strID = pIecCfgGinCh->m_strID;
			pIecCfgGoutCh->m_nUseFlag = pIecCfgGinCh->m_nUseFlag;
			pIecCfgGoutCh->m_nIndex = pIecCfgGinCh->m_nIndex;
			pIecCfgGoutCh->m_strDataType = pIecCfgGinCh->m_strDataType;

			if (pIecCfgGinCh->m_strAppChID.Find("bin") != -1)
			{
				pIecCfgGoutCh->m_strAppChID.Format(_T("bout%ld"),GetAppChIDGin_Index(pIecCfgGinCh->m_strAppChID));

				if (pIecCfgGinCh->m_strDataType == _T("BOOLEAN"))
				{
					pIecCfgGoutCh->m_strDefaultValue = _T("FALSE");
				}
				else if (pIecCfgGinCh->m_strDataType == _T("Dbpos"))
				{
					pIecCfgGoutCh->m_strDefaultValue = _T("[01]");
				}
			}
			else if (pIecCfgGinCh->m_strDataType == _T("BOOLEAN"))
			{
				pIecCfgGoutCh->m_strAppChID = _T("v0");
			}
			else if (pIecCfgGinCh->m_strDataType == _T("Dbpos"))
			{
				pIecCfgGoutCh->m_strAppChID = _T("v01");
			}
			else if (pIecCfgGinCh->m_strDataType == _T("Timestamp"))
			{
				pIecCfgGoutCh->m_strAppChID = _T("UTCTime");
			}
			else if (pIecCfgGinCh->m_strDataType == _T("FLOAT32"))
			{
				pIecCfgGoutCh->m_strAppChID = _T("0.0");
			}

			pIecCfgGoutChs->AddNewChild(pIecCfgGoutCh);
		}
	}
}
#endif
