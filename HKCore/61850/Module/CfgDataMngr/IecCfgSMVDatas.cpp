//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasSMV.cpp  CIecCfgDatasSMV


#include "stdafx.h"
#include "IecCfgSMVDatas.h"

// static const CString g_strSmvType91		= _T("9-1");
// static const CString g_strSmvType92		= _T("9-2");
// static const CString g_strSmvType6044	= _T("6044-8");

CIecCfgDatasSMV::CIecCfgDatasSMV()
{
	//初始化属性
 	m_strSmvType = g_strSmvType92;
// 	m_strSmvType = g_strSmvType6044;
//	m_strSmvType = g_strSmvType91;

	m_pIecCfgSmvRates = NULL;
	m_nFT3CRCType = 0;

	//初始化成员变量
	m_oIecCfgDataSmvCommon.SetParent(this);
}

CIecCfgDatasSMV::~CIecCfgDatasSMV()
{
}

long CIecCfgDatasSMV::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strSmvTypeKey, oNode, m_strSmvType);
	xml_GetAttibuteValue(pXmlKeys->m_strFT3_ProtocolIDKey, oNode, m_strFT3_ProtocolID);
	xml_GetAttibuteValue(pXmlKeys->m_strFT3_CRCTypeKey, oNode, m_nFT3CRCType);
	return 0;
}

long CIecCfgDatasSMV::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDatasBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strSmvTypeKey, oElement, m_strSmvType);
	xml_SetAttributeValue(pXmlKeys->m_strFT3_ProtocolIDKey, oElement, m_strFT3_ProtocolID);
	xml_SetAttributeValue(pXmlKeys->m_strFT3_CRCTypeKey, oElement, m_nFT3CRCType);
	return 0;
}

BOOL CIecCfgDatasSMV::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDatasBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDatasSMV *p = (CIecCfgDatasSMV*)pObj;

	if(m_strSmvType != p->m_strSmvType)
	{
		return FALSE;
	}

	if(m_strFT3_ProtocolID != p->m_strFT3_ProtocolID)
	{
		return FALSE;
	}
	if(m_nFT3CRCType != p->m_nFT3CRCType)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CIecCfgDatasSMV::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDatasBase::CopyOwn(pDest);

	CIecCfgDatasSMV *p = (CIecCfgDatasSMV*)pDest;

	p->m_strSmvType = m_strSmvType;
	p->m_strFT3_ProtocolID = m_strFT3_ProtocolID;
	p->m_nFT3CRCType = m_nFT3CRCType;
	return TRUE;
}

CBaseObject* CIecCfgDatasSMV::Clone()
{
	CIecCfgDatasSMV *p = new CIecCfgDatasSMV();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgDatasSMV::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgData91Key)
	{
		pNew = new CIecCfg91Data();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgData92Key)
	{
		pNew = new CIecCfg92Data();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgData6044Key)
	{
		pNew = new CIecCfg6044Data();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgData6044CommonKey)
	{
		pNew = new CIecCfg6044CommonData();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgData2MKey)
	{
		pNew = new CIecCfg2MData();
	}	
	else if (strClassID == pXmlKeys->m_strCIecCfgSmvRatesKey)
	{
		pNew = new CIecCfgSmvRates();
	}

	return pNew;
}


CIecCfgDataBase* CIecCfgDatasSMV::CreateIecCfgData()
{
	long nSmvType = iecfg_GetSmvTypeByString(m_strSmvType);

	CIecCfgSmvDataBase *pNew = NULL;

	switch (nSmvType)
	{
	case SMVTYPE_91:
		pNew = new CIecCfg91Data();
		break;

	case SMVTYPE_92:
		pNew = new CIecCfg92Data();
		break;

	case SMVTYPE_6044:
		pNew = new CIecCfg6044Data();
		break;

	case SMVTYPE_6044_COMMON:
		pNew = new CIecCfg6044CommonData();
		break;
	case SMVTYPE_2M:
		pNew = new CIecCfg2MData();
		break;
	default:
		pNew = new CIecCfg92Data();
		break;
	}

	pNew->InitByCommData(&m_oIecCfgDataSmvCommon);
//	pNew->SetChannelNum(STSMV_CHANNEL_NUM);

	return pNew;
}


void CIecCfgDatasSMV::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGSMVRATES)
		{
			m_pIecCfgSmvRates = (CIecCfgSmvRates *)p;
			break;
		}
	}

	if (m_pIecCfgSmvRates == NULL)
	{
		m_pIecCfgSmvRates = GetIecCfgSmvRates();
		m_pIecCfgSmvRates->OpenCfgDefaultConfigFile();
	}
}

UINT CIecCfgDatasSMV::GetIecCfgDataClassID()
{
	long nSmvType = iecfg_GetSmvTypeByString(m_strSmvType);

	switch (nSmvType)
	{
	case SMVTYPE_91:
		return CFGCLASSID_CIECCFG91DATA;
		break;

	case SMVTYPE_92:
		return CFGCLASSID_CIECCFG92DATA;
		break;

	case SMVTYPE_6044:
		return CFGCLASSID_CIECCFG6044DATA;
		break;

	case SMVTYPE_6044_COMMON:
		return CFGCLASSID_CIECCFG6044COMMONDATA;
		break;
	case SMVTYPE_2M:
		return CFGCLASSID_CIECCFG2MDATA;
		break;
	default:
		return CFGCLASSID_CIECCFG92DATA;
		break;
	}

	return CFGCLASSID_CIECCFG92DATA;
}


BOOL CIecCfgDatasSMV::IsSmvData(UINT nClassID)
{
	return (GetCurSmvTypeClassID() == nClassID);
}

long CIecCfgDatasSMV::GetCurSmvTypeClassID()
{
	//return ((nClassID == CFGCLASSID_CIECCFG91DATA) //zhouhj 20211015 修改用于适应在切换FT3与9-2不删除当前数据对象
	//	|| (nClassID == CFGCLASSID_CIECCFG92DATA)
	//	|| (nClassID == CFGCLASSID_CIECCFG6044DATA) 
	//	|| (nClassID == CFGCLASSID_CIECCFG6044COMMONDATA));

	long nSmvType = GetSmvType();

	if (nSmvType == SMVTYPE_91)
	{
		return CFGCLASSID_CIECCFG91DATA;
	}
	else if (nSmvType == SMVTYPE_92)
	{
		return CFGCLASSID_CIECCFG92DATA;
	}
	else if (nSmvType == SMVTYPE_6044)
	{
		return CFGCLASSID_CIECCFG6044DATA;
	}
	else if (nSmvType == SMVTYPE_6044_COMMON)
	{
		return CFGCLASSID_CIECCFG6044COMMONDATA;
	}
	else if (nSmvType == SMVTYPE_2M)
	{
		return CFGCLASSID_CIECCFG2MDATA;
	}
	return -1;
}


BOOL CIecCfgDatasSMV::IsSmvData(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();

	return IsSmvData(nClassID);
}

long CIecCfgDatasSMV::GetMaxCfgDataCount(UINT nClassID)
{
	if (nClassID == CFGCLASSID_CIECCFG91DATA)
	{
		return g_nIecCfgSmvOut_91_92MaxNum;
	}
	else if (nClassID == CFGCLASSID_CIECCFG92DATA)
	{
		return g_nIecCfgSmvOut_91_92MaxNum;
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044DATA)
	{
		return g_nIecCfgSmvOut_60044MaxNum;
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044COMMONDATA)
	{
		return g_nIecCfgSmvOut_60044MaxNum;
	}
	else if (nClassID == CFGCLASSID_CIECCFG2MDATA)
	{
		return g_nIecCfgSmvOut_60044MaxNum;
	}

	return g_nIecCfgSmvOut_91_92MaxNum;
}

BOOL CIecCfgDatasSMV::IsSmvData_AllSmvType(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	UINT nClassID = pObj->GetClassID();

	if (nClassID == CFGCLASSID_CIECCFG91DATA)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFG92DATA)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044DATA)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFG6044COMMONDATA)
	{
		return TRUE;
	}
	else if (nClassID == CFGCLASSID_CIECCFG2MDATA)
	{
		return TRUE;
	}

	return FALSE;
}

void CIecCfgDatasSMV::ChangePosition(long nIndex1, long nIndex2)
{
	POS posPrev = NULL;
	POS pos = GetHeadPosition();
	CExBaseObject *pCurObj = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		pCurObj = GetNext(pos);

		if ((pCurObj->GetClassID() == CFGCLASSID_CIECCFGSMVRATES)&&(pos != NULL))//zhouhj20210220 找到采样率对象，判断其不在最后，则将其链表移除，并添加到最后
		{
			RemoveAt(posPrev);
			AddTail(pCurObj);
			break;
		}
	}

	CTLinkList::ChangePosition(nIndex1, nIndex2);
}

void CIecCfgDatasSMV::FreeCfgDatas()
{
	POS pos = GetHeadPosition();
	POS posPrev = NULL;
	CIecCfgDatasBase *p = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CIecCfgDatasBase *)GetNext(pos);

		if (IsSmvData(p))
		{
			RemoveAt(posPrev);
			delete p;
		}
	}
}

BOOL CIecCfgDatasSMV::SetSmvType(long nSmvType)
{
	long nOldSmvType = GetSmvType();

	if (nSmvType == nOldSmvType)
	{
		return FALSE;
	}

	m_strSmvType = iecfg_GetSmvTypeByID(nSmvType);
	long nCount = GetCfgDataCount();

	if (nCount == 0)
	{
		CIecCfgDataBase *pData = CreateIecCfgData();
		pData->OpenCfgDefaultConfigFile();
		AddNewChild(pData);
	}

	InitCommonFromCfgDatas();

// 	long nCount = GetCfgDataCount();  //zhouhj 20211015 修改以适应在切换FT3和9-2时,不用重新创建相关配置
// 	m_strSmvType = iecfg_GetSmvTypeByID(nSmvType);
// 	FreeCfgDatas();
// 
// 	SetCount(nCount);
// 	InitCommonFromCfgDatas();
	return TRUE;
}

void CIecCfgDatasSMV::InitCfgDatasByCommon()
{
	POS pos = GetHeadPosition();
	CIecCfgSmvDataBase *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgSmvDataBase *)GetNext(pos);

		if (IsSmvData_AllSmvType(p))
		{
			p->InitByCommData(&m_oIecCfgDataSmvCommon);
		}
	}
}

void CIecCfgDatasSMV::InitCommonFromCfgDatas()
{
	POS pos = GetHeadPosition();
	CIecCfgSmvDataBase *p = NULL;
	BOOL bHasInitCommData = FALSE,bHasInitSampleRate = FALSE,bHasInitBaudRate = FALSE;

	while (pos != NULL)
	{
		p = (CIecCfgSmvDataBase *)GetNext(pos);

		if (bHasInitCommData && bHasInitSampleRate && bHasInitBaudRate)
		{
			break;
		}

		if (IsSmvData_AllSmvType(p))
		{
			//zhouhj 2023.10.18 9-2与FT3对应的采样率需要分别配置,此处进行分开处理
			if ((p->GetClassID() == CFGCLASSID_CIECCFG92DATA)||(p->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA)
				||(p->GetClassID() == CFGCLASSID_CIECCFG91DATA))
			{
				m_oIecCfgDataSmvCommon.m_nSampleRate = p->m_nSampleRate; 
				bHasInitSampleRate = TRUE;
			}
			else if ((p->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)||(p->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA))
			{
				CIecCfg6044CommonData *pIecCfg6044CommonData = (CIecCfg6044CommonData*)p;
				m_oIecCfgDataSmvCommon.m_nBaudRate = pIecCfg6044CommonData->m_nBaudRate; 
				m_oIecCfgDataSmvCommon.m_nSampleRate_FT3 = pIecCfg6044CommonData->m_nSampleRate; //cl 20231026
				bHasInitBaudRate = TRUE;
			}
			else if (!bHasInitCommData)
			{
				p->GetCommData(&m_oIecCfgDataSmvCommon);
				bHasInitCommData = TRUE;
			}
		}
	}
}

void CIecCfgDatasSMV::GenerateSmv_GroupDatas(CDataGroup *pSmv)
{
	POS pos=GetHeadPosition();
	CIecCfgSmvDataBase *p = NULL;
	CIecCfg6044CommonData *p6044CommonData = NULL;
	CExBaseObject *pCurrObj = NULL;

	while (pos != NULL)
	{
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() != CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			continue;
		}

		p=(CIecCfgSmvDataBase*)pCurrObj;
		//zhouhj 2023.10.18 此处无需再判别是否SMV
//		if (IsSmvData(p))
		{
			if (p->m_nUseFlag==1)
			{
				p6044CommonData = (CIecCfg6044CommonData *)p;
				p6044CommonData->GenerateCommon_GroupDatas(pSmv);
			}
		}
	}
}

void CIecCfgDatasSMV::ReadSmv_GroupDatas(CDataGroup *pSmv)
{
	POS pos = GetHeadPosition();
	CIecCfg6044CommonData *p = NULL;
	long nIndex = 1;
	CString strGroupID;
	CDataGroup *pSmvGroup = NULL;
	CExBaseObject *pCurrObj = NULL;

	while (pos != NULL)
	{
		pCurrObj = GetNext(pos);

		if (pCurrObj->GetClassID() != CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			continue;
		}

		p = (CIecCfg6044CommonData *)pCurrObj;

		if (p->m_nUseFlag == 1)
		{
			strGroupID.Format(_T("FT3Pub%ld"),nIndex);
			pSmvGroup = (CDataGroup*)pSmv->FindByID(strGroupID);
			nIndex++;

			if (pSmvGroup != NULL)
			{
				p->ReadCommon_GroupDatas(pSmvGroup);
			}
		}
	}
}

BOOL CIecCfgDatasSMV::ValidateFiberIndex(CIecCfgDataBase *pData)
{
	CExBaseList oListUseDatas;
	GetUseDatas(oListUseDatas);
	POS pos = NULL;
	CIecCfgDataBase *pCurr = NULL;
	BOOL bTrue = TRUE;

	pos = oListUseDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pCurr = (CIecCfgDataBase *)oListUseDatas.GetNext(pos);

		if (pCurr != pData)
		{
			if ((pCurr->m_nFiberIndex == pData->m_nFiberIndex))
			{
				if ((pCurr->GetClassID() == CFGCLASSID_CIECCFG2MDATA)||(pCurr->GetClassID() == CFGCLASSID_CIECCFG2MINDATA))
				{
					continue;
				}

				if ((pCurr->GetClassID() == CFGCLASSID_CIECCFG92DATA)||(pCurr->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA))
				{
					if (((CIecCfg92Data*)pCurr)->m_dwAppID != ((CIecCfg92Data*)pData)->m_dwAppID)
					{
						continue;
					}
				}

                CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【%s】与【%s】输出光口冲突"), pData->GetCfgDataShortName().GetString()
                                           , pCurr->GetCfgDataShortName().GetString());
				bTrue = FALSE;
				break;
			}
		}
	}

	oListUseDatas.RemoveAll();

	//只进行提示，不返回错误
	return TRUE;
}


BOOL CIecCfgDatasSMV::ValidateFiberIndex()
{
	CExBaseList oListUseDatas;
	GetUseDatas(oListUseDatas);
	POS pos = NULL;
	CIecCfgDataBase *pData = NULL;
	BOOL bTrue = TRUE;
	pos = oListUseDatas.GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CIecCfgDataBase *)oListUseDatas.GetNext(pos);

		if (!ValidateFiberIndex(pData))
		{
			bTrue = FALSE;
			break;
		}
	}

	oListUseDatas.RemoveAll();

	return bTrue;
}

CIecCfgSmvRates* CIecCfgDatasSMV::GetIecCfgSmvRates()
{
	if (m_pIecCfgSmvRates == NULL)
	{
		m_pIecCfgSmvRates = new CIecCfgSmvRates();
		AddNewChild(m_pIecCfgSmvRates);
	}

	return m_pIecCfgSmvRates;
}

CIecCfgDataBase* CIecCfgDatasSMV::FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount)
{
	CExBaseList oList;
	GetIecCfgDatas(oList);

	CIecCfgSmvDataBase* pCfgSmvDataBase = NULL;
	CIecCfgSmvDataBase* pTemp = NULL;
	CIecCfg91Data* pCfg91Data = NULL;
	CIecCfg92Data* pCfg92Data = NULL;
	CString strDstMac,strSrcMac;

	POS pos = oList.GetHeadPosition();
	while (pos)
	{
		pTemp = (CIecCfgSmvDataBase*)oList.GetNext(pos);

		if (pTemp->GetClassID()==CFGCLASSID_CIECCFG91DATA && nCMT != PROTOCOL_61850_TYPE_91
			|| pTemp->GetClassID()==CFGCLASSID_CIECCFG92DATA && nCMT != PROTOCOL_61850_TYPE_92)
		{
			continue;
		}
		
		strDstMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pDstMac[0], pDstMac[1], pDstMac[2], pDstMac[3], pDstMac[4], pDstMac[5]);
		strSrcMac.Format(_T("%.2X-%.2X-%.2X-%.2X-%.2X-%.2X"), pSrcMac[0], pSrcMac[1], pSrcMac[2], pSrcMac[3], pSrcMac[4], pSrcMac[5]);

		if(nCMT == PROTOCOL_61850_TYPE_91)
		{
			pCfg91Data = (CIecCfg91Data*)pTemp;

			if (pCfg91Data->m_strDestAddress.CompareNoCase(strDstMac)==0 && pCfg91Data->m_strSrcAddress.CompareNoCase(strSrcMac)==0 
				&& pCfg91Data->m_dwAppID == nAPPID && pCfg91Data->m_nChannelNum == nChCount)
			{
				pCfgSmvDataBase = pCfg91Data;
				break;
			}
		}
		else if (nCMT == PROTOCOL_61850_TYPE_92)
		{
			pCfg92Data = (CIecCfg92Data*)pTemp;

			if (pCfg92Data->m_strDestAddress.CompareNoCase(strDstMac)==0 && pCfg92Data->m_strSrcAddress.CompareNoCase(strSrcMac)==0 
				&& pCfg92Data->m_dwAppID == nAPPID && pCfg92Data->m_nChannelNum == nChCount)
			{
				pCfgSmvDataBase = pCfg92Data;
				break;
			}
		}
	}

	oList.RemoveAll();
	return pCfgSmvDataBase;
}

BOOL CIecCfgDatasSMV::IsAppID_Repeat(DWORD dwAppID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfg92Data* pCfg92Data = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFG92DATA)
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

CIecCfg92Data* CIecCfgDatasSMV::FindByAppIDFiber(DWORD dwAppID,long nFiberIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfg92Data* pCfg92Data = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if ((p->GetClassID() == CFGCLASSID_CIECCFG92DATA)||(p->GetClassID() == CFGCLASSID_CIECCFG92INPUTDATA))
		{
			pCfg92Data = (CIecCfg92Data*)p;

			if (pCfg92Data->m_dwAppID != dwAppID)
			{
				continue;
			}

			if ((pCfg92Data->m_nFiberIndex == nFiberIndex) || (nFiberIndex < 0))
			{
				return pCfg92Data;
			}
		}
	}

	return NULL;
}

CIecCfgDataBase* CIecCfgDatasSMV::FindByFiber_60044Common(long nFiberIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfg6044CommonData* pCfg6044CommonData = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if ((p->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)||
			(p->GetClassID() == CFGCLASSID_CIECCFG6044COMMONINDATA))
		{
			pCfg6044CommonData = (CIecCfg6044CommonData*)p;

			if ((pCfg6044CommonData->m_nFiberIndex == nFiberIndex))
			{
				return pCfg6044CommonData;
			}
		}
	}

	return NULL;
}

#ifdef _USE_IN_AT02D_MODE_
//#include "../IecCfgTool/IecCfgTool.h"

void CIecCfgDatasSMV::SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex)//周宏军 20200616  增加AT02配置
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

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92DATA)
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

void CIecCfgDatasSMV::AddAT02D_dsSV(CDvmLogicDevice *pLDevice,long &nDatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas)
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

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92DATA)
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

BOOL CIecCfgDatasSMV::IsAT02D_Invalid()
{
	CExBaseObject *pCurObj = NULL;
	CIecCfg92Data *pIecCfg92Data = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pCurObj = GetNext(pos);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFG92DATA)
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

				if (pCurObjTmp->GetClassID() == CFGCLASSID_CIECCFG92DATA)
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