//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgData6044.cpp  CIecCfgData6044


#include "stdafx.h"
#include "IecCfg6044CommonData.h"

CIecCfg6044CommonData::CIecCfg6044CommonData()
{
	//初始化属性

	//初始化成员变量
	m_strID = _T("IEC60044-8-Common(FT3)");

	m_nDelayTime= 0;
	m_nSmpCntType= 1;
	m_nSmpDataLen= 3;
	m_nBlockType= 1;
	m_nSCP= 1000;
	m_nSCM= 1000;
	m_nSV= 100;
	m_nBaudRate= 0;
	m_dInomProt= 1000;
	m_dInomMeas= 1000;
	m_nDcVol= 100;
	m_nDcCur= 1000;
	m_nDcNeuatralVol = 100;
	m_dDcVolPrim= 1000;
	m_dDcCurPrim= 100;
	m_dDcNeutralPrim = 1000;
	m_strProtocolID = _T("");
// 	m_nFT3CrcType = 0;
}

CIecCfg6044CommonData::~CIecCfg6044CommonData()
{
}

long CIecCfg6044CommonData::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strUNomKey, oNode, m_fUNom);
 	xml_GetAttibuteValue(pXmlKeys->m_strSampleRateKey, oNode, m_nSampleRate);
 	xml_GetAttibuteValue(pXmlKeys->m_strAsduNumKey, oNode, m_nAsduNum);
	xml_GetAttibuteValue(pXmlKeys->m_strDelayTimeKey, oNode, m_nDelayTime);

	xml_GetAttibuteValue(pXmlKeys->m_strSmpCntType, oNode, m_nSmpCntType);
	xml_GetAttibuteValue(pXmlKeys->m_strSampleDataLen, oNode, m_nSmpDataLen);
	xml_GetAttibuteValue(pXmlKeys->m_strBlockType, oNode, m_nBlockType);
	xml_GetAttibuteValue(pXmlKeys->m_strSCP, oNode, m_nSCP);
	xml_GetAttibuteValue(pXmlKeys->m_strSCM, oNode, m_nSCM);
	xml_GetAttibuteValue(pXmlKeys->m_strSV, oNode, m_nSV);
	xml_GetAttibuteValue(pXmlKeys->m_strBaudRate, oNode, m_nBaudRate);
	xml_GetAttibuteValue(pXmlKeys->m_strInomProt, oNode, m_dInomProt);
	xml_GetAttibuteValue(pXmlKeys->m_strInomMeas, oNode, m_dInomMeas);
	xml_GetAttibuteValue(pXmlKeys->m_strDcVol, oNode, m_nDcVol);
	xml_GetAttibuteValue(pXmlKeys->m_strDcCur, oNode, m_nDcCur);
	xml_GetAttibuteValue(pXmlKeys->m_strDcNeutralVol, oNode, m_nDcNeuatralVol);
	xml_GetAttibuteValue(pXmlKeys->m_strDcVolPrim, oNode, m_dDcVolPrim);
	xml_GetAttibuteValue(pXmlKeys->m_strDcCurPrim, oNode, m_dDcCurPrim);
	xml_GetAttibuteValue(pXmlKeys->m_strDcNeutralVolPrim, oNode, m_dDcNeutralPrim);
	xml_GetAttibuteValue(pXmlKeys->m_strProtocolIDKey, oNode, m_strProtocolID);
	return 0;
}

long CIecCfg6044CommonData::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strUNomKey, oElement, m_fUNom);
	xml_SetAttributeValue(pXmlKeys->m_strSampleRateKey, oElement, m_nSampleRate);
	xml_SetAttributeValue(pXmlKeys->m_strAsduNumKey, oElement, m_nAsduNum);
	xml_SetAttributeValue(pXmlKeys->m_strDelayTimeKey, oElement, m_nDelayTime);

	xml_SetAttributeValue(pXmlKeys->m_strSmpCntType, oElement, m_nSmpCntType);
	xml_SetAttributeValue(pXmlKeys->m_strSampleDataLen, oElement, m_nSmpDataLen);
	xml_SetAttributeValue(pXmlKeys->m_strBlockType, oElement, m_nBlockType);
	xml_SetAttributeValue(pXmlKeys->m_strSCP, oElement, m_nSCP);
	xml_SetAttributeValue(pXmlKeys->m_strSCM, oElement, m_nSCM);
	xml_SetAttributeValue(pXmlKeys->m_strSV, oElement, m_nSV);
	xml_SetAttributeValue(pXmlKeys->m_strBaudRate, oElement, m_nBaudRate);
	xml_SetAttributeValue(pXmlKeys->m_strInomProt, oElement, m_dInomProt);
	xml_SetAttributeValue(pXmlKeys->m_strInomMeas, oElement, m_dInomMeas);
	xml_SetAttributeValue(pXmlKeys->m_strDcVol, oElement, m_nDcVol);
	xml_SetAttributeValue(pXmlKeys->m_strDcCur, oElement, m_nDcCur);
	xml_SetAttributeValue(pXmlKeys->m_strDcNeutralVol, oElement, m_nDcNeuatralVol);
	xml_SetAttributeValue(pXmlKeys->m_strDcVolPrim, oElement, m_dDcVolPrim);
	xml_SetAttributeValue(pXmlKeys->m_strDcCurPrim, oElement, m_dDcCurPrim);
	xml_SetAttributeValue(pXmlKeys->m_strDcNeutralVolPrim, oElement, m_dDcNeutralPrim);
	xml_SetAttributeValue(pXmlKeys->m_strProtocolIDKey, oElement, m_strProtocolID);

	return 0;
}

BOOL CIecCfg6044CommonData::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgSmvDataBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg6044CommonData *p = (CIecCfg6044CommonData*)pObj;

	if(m_nDelayTime != p->m_nDelayTime)
	{
		return FALSE;
	}

	if(m_nSmpCntType != p->m_nSmpCntType)
	{
		return FALSE;
	}	

	if(m_nSmpDataLen != p->m_nSmpDataLen)
	{
		return FALSE;
	}	

	if(m_nBlockType != p->m_nBlockType)
	{
		return FALSE;
	}	

	if(m_nBaudRate != p->m_nBaudRate)
	{
		return FALSE;
	}

	if(m_nDcVol != p->m_nDcVol)
	{
		return FALSE;
	}

	if(m_nDcCur != p->m_nDcCur)
	{
		return FALSE;
	}

	if(m_nDcNeuatralVol != p->m_nDcNeuatralVol)
	{
		return FALSE;
	}

	if(m_dDcVolPrim != p->m_dDcVolPrim)
	{
		return FALSE;
	}

	if(m_dDcCurPrim != p->m_dDcCurPrim)
	{
		return FALSE;
	}

	if(m_dDcNeutralPrim != p->m_dDcNeutralPrim)
	{
		return FALSE;
	}

	if(m_strProtocolID != p->m_strProtocolID)
	{
		return FALSE;
	}

	if(m_nSCP != p->m_nSCP)
	{
		return FALSE;
	}

	if(m_nSCM != p->m_nSCM)
	{
		return FALSE;
	}

	if(m_nSV != p->m_nSV)
	{
		return FALSE;
	}

	if(m_dInomProt != p->m_dInomProt)
	{
		return FALSE;
	}

	if(m_dInomMeas != p->m_dInomMeas)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg6044CommonData::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgSmvDataBase::CopyOwn(pDest);

	CIecCfg6044CommonData *p = (CIecCfg6044CommonData*)pDest;
	p->m_nBaudRate = m_nBaudRate;
	p->m_nDelayTime = m_nDelayTime;
	p->m_nSmpCntType = m_nSmpCntType;
	p->m_nSmpDataLen = m_nSmpDataLen;
	p->m_nBlockType = m_nBlockType;
	p->m_nDcVol = m_nDcVol;
	p->m_nDcCur = m_nDcCur;
	p->m_nDcNeuatralVol = m_nDcNeuatralVol;
	p->m_dDcVolPrim = m_dDcVolPrim;
	p->m_dDcCurPrim = m_dDcCurPrim;
	p->m_dDcNeutralPrim = m_dDcNeutralPrim;
	p->m_strProtocolID = m_strProtocolID;
	p->m_nSCP = m_nSCP;
	p->m_nSCM = m_nSCM;
	p->m_nSV = m_nSV;
	p->m_dInomProt = m_dInomProt;
	p->m_dInomMeas = m_dInomMeas;
	return TRUE;
}

CBaseObject* CIecCfg6044CommonData::Clone()
{
	CIecCfg6044CommonData *p = new CIecCfg6044CommonData();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfg6044CommonData::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgChs6044Key)
	{
		pNew = new CIecCfg6044Chs();
	}

	if (pNew != NULL)
	{
		return pNew;
	}

	return CIecCfgSmvDataBase::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
}


void CIecCfg6044CommonData::InitAfterRead()
{
	InitChs(CFGCLASSID_CIECCFGCHS6044);

	if (m_pCfgChs == NULL)
	{
		m_pCfgChs = new CIecCfg6044Chs();
		AddNewChild(m_pCfgChs);
	}

	CIecCfgSmvDataBase::InitAfterRead();
}

void CIecCfg6044CommonData::GenerateCommon_GroupDatas(CDataGroup *pCommonChs)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

	CDataGroup *pCommonData = new CDataGroup;
	pCommonChs->AddNewChild(pCommonData);
	pCommonData->m_strName.Format(_T("FT3Pub%ld"),pCommonChs->GetCount());
	pCommonData->m_strID = pCommonData->m_strName;
	pCommonData->m_strDataType = _T("FT3Pub");

	CIecCfg6044Chs *pIecCfg6044Chs=(CIecCfg6044Chs*)m_pCfgChs;
	CIecCfg6044CommonCh *pIecCfg6044CommonCh=NULL;
	long nIndex = 1;
	CDvmData *pDvmData = NULL;
	POS pos=pIecCfg6044Chs->GetHeadPosition();

	while(pos)
	{
		pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)pIecCfg6044Chs->GetNext(pos);
		pDvmData = new CDvmData;
		pCommonData->AddNewChild(pDvmData);
		pDvmData->m_strID.Format(_T("FT3Channel%ld"),nIndex);
		pDvmData->m_strName = pIecCfg6044CommonCh->m_strName;
		pDvmData->m_strFormat = pIecCfg6044CommonCh->m_strID;
		pDvmData->m_strDataType = pIecCfg6044CommonCh->m_strChType;
		pDvmData->m_strValue.Format(_T("%d"),pIecCfg6044CommonCh->m_nValue);
		nIndex++;
	}
}

void CIecCfg6044CommonData::ReadCommon_GroupDatas(CDataGroup *pCommonChs)
{
	if (m_pCfgChs == NULL)
	{
		return;
	}

	CDvmData *pDvmData = NULL;
	CIecCfg6044CommonCh *pIecCfg6044CommonCh=NULL;
	POS pos = pCommonChs->GetHeadPosition();
	CString strIndex;
	long nIndex = 0;

	while(pos)
	{
		pDvmData=(CDvmData*)pCommonChs->GetNext(pos);
		strIndex = pDvmData->m_strID;
		strIndex.Replace(_T("FT3Channel"),_T(""));
		nIndex = CString_To_long(strIndex);
		pIecCfg6044CommonCh = (CIecCfg6044CommonCh*)m_pCfgChs->GetAtIndex(nIndex-1);

		if (pIecCfg6044CommonCh != NULL)
		{
			if (pIecCfg6044CommonCh->m_strChType == pDvmData->m_strDataType)
			{
				pIecCfg6044CommonCh->m_nValue = CString_To_long(pDvmData->m_strValue);
			}
		}
	}
}

long CIecCfg6044CommonData::GetPkgLenth()
{
	if (m_pCfgChs == NULL)
	{
		return 0;
	}

	CIecCfg6044Chs *pIecCfg6044Chs=(CIecCfg6044Chs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfg6044CommonCh *pIecCfg6044CommonCh=NULL;
	long nPkgLenth = 0;// 报文头长度
	POS pos=pIecCfg6044Chs->GetHeadPosition();

	while(pos)
	{
		pCurObj=pIecCfg6044Chs->GetNext(pos);
		pIecCfg6044CommonCh=(CIecCfg6044CommonCh*)pCurObj;
		nPkgLenth += pIecCfg6044CommonCh->m_nChLenth;
	}

	long nCrcLenth = 2*(nPkgLenth/16);//计算CRC长度(每16字节对应2字节CRC长度)

	if ((nPkgLenth%16)>0)//如果总长度不为16字节整数倍,则最后一段,单独增加CRC
	{
		nCrcLenth += 2;
	}

	nPkgLenth += nCrcLenth;
	nPkgLenth += 2;//加上报文头长度
	return nPkgLenth;
}

long CIecCfg6044CommonData::GetPkgLenth(long nFT3CrcType)
{
// 	m_nFT3CrcType = nFT3CrcType;

	if (m_pCfgChs == NULL)
	{
		return 0;
	}

	CIecCfg6044Chs *pIecCfg6044Chs=(CIecCfg6044Chs*)m_pCfgChs;
	CExBaseObject *pCurObj = NULL;
	CIecCfg6044CommonCh *pIecCfg6044CommonCh=NULL;
	long nPkgLenth = 0;// 报文头长度
	POS pos=pIecCfg6044Chs->GetHeadPosition();

	while(pos)
	{
		pCurObj=pIecCfg6044Chs->GetNext(pos);
		pIecCfg6044CommonCh=(CIecCfg6044CommonCh*)pCurObj;
		nPkgLenth += pIecCfg6044CommonCh->m_nChLenth;
	}

	if (nFT3CrcType == 2)
	{
		 
// 		long nCrcLenth = 2*(nPkgLenth/16);//计算CRC长度(每16字节对应2字节CRC长度)
// 
// 		if ((nPkgLenth%16)>0)//如果总长度不为16字节整数倍,则最后一段,单独增加CRC
// 		{
// 			nCrcLenth += 2;
// 		}

		
// 		nPkgLenth += nCrcLenth;

		nPkgLenth += 8; //末尾
		return nPkgLenth;
		
	}
	else if (nFT3CrcType == 1)
	{
		nPkgLenth += 4; //末尾
		return nPkgLenth;
	}
	else
	{

		long nCrcLenth = 2*(nPkgLenth/16);//计算CRC长度(每16字节对应2字节CRC长度)

		if ((nPkgLenth%16)>0)//如果总长度不为16字节整数倍,则最后一段,单独增加CRC
		{
			nCrcLenth += 2;
		}

		nPkgLenth += nCrcLenth;
		nPkgLenth += 2;//加上报文头长度
		return nPkgLenth;
	}


}

void CIecCfg6044CommonData::GetCommData(CIecCfgDataSmvCommon *pCommon)
{
	CIecCfgSmvDataBase::GetCommData(pCommon);
	pCommon->m_nBaudRate = m_nBaudRate;
	pCommon->m_nDcVol = m_nDcVol;
	pCommon->m_nDcCur = m_nDcCur;
	pCommon->m_nDcNeuatralVol = m_nDcNeuatralVol;
	pCommon->m_dDcVolPrim = m_dDcVolPrim;
	pCommon->m_dDcCurPrim = m_dDcCurPrim;
	pCommon->m_dDcNeutralPrim = m_dDcNeutralPrim;
	pCommon->m_nSCP = m_nSCP;
	pCommon->m_nSCM = m_nSCM;
	pCommon->m_nSV = m_nSV;
	pCommon->m_dInomProt = m_dInomProt;
	pCommon->m_dInomMeas = m_dInomMeas;
}

void CIecCfg6044CommonData::InitByCommData(CIecCfgDataSmvCommon *pCommon)
{
	CIecCfgSmvDataBase::InitByCommData(pCommon);
	m_nBaudRate = pCommon->m_nBaudRate;
	m_nDcVol = pCommon->m_nDcVol;
	m_nDcCur = pCommon->m_nDcCur;
	m_nDcNeuatralVol = pCommon->m_nDcNeuatralVol;
	m_dDcVolPrim = pCommon->m_dDcVolPrim;
	m_dDcCurPrim = pCommon->m_dDcCurPrim;
	m_dDcNeutralPrim = pCommon->m_dDcNeutralPrim;
	m_nSCP = pCommon->m_nSCP;
	m_nSCM = pCommon->m_nSCM;
	m_nSV = pCommon->m_nSV;
	m_dInomProt = pCommon->m_dInomProt;
	m_dInomMeas = pCommon->m_dInomMeas;
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfg6044CommonData::SetAT02D_ChannelID(CExBaseList *pSVList,long &nCBIndex)
{
	if (m_pCfgChs != NULL)
	{
		((CIecCfg6044Chs*)m_pCfgChs)->SetAT02D_ChannelID(pSVList,nCBIndex);
	}
}
#endif


#ifdef _PSX_IDE_QT_
BOOL CIecCfg6044CommonData::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
//		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue;
		m_nFiberIndex = m_nFiberIndex % GetAppFiberCount();

		return TRUE;
	}

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg6044CommonData::SetCfgDataValues(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
//		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue;
		//m_nFiberIndex = m_nFiberIndex % GetAppFiberCount();//20240612 suyang 注销 多个插件 光口数显示不对，取余又从0开始，应顺序显示

		return TRUE;
	}

	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg6044CommonData::GetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg6044CommonData::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
{
	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#else
BOOL CIecCfg6044CommonData::SetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue.ulVal;
		m_nFiberIndex = m_nFiberIndex % GetAppFiberCount();

		return TRUE;
	}


	return CIecCfgSmvDataBase::SetCfgDataValue(nDataID, vValue);
}


BOOL CIecCfg6044CommonData::GetCfgDataValue(long nDataID, VARIANT &vValue)
{
	return CIecCfgSmvDataBase::GetCfgDataValue(nDataID, vValue);
}

BOOL CIecCfg6044CommonData::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
{
	return CIecCfgSmvDataBase::IsEqualCfgDataValue(nDataID, vValue);
}
#endif
