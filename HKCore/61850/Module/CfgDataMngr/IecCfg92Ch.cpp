//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg92Ch.cpp  CIecCfg92Ch


#include "stdafx.h"
#include "IecCfg92Ch.h"
#include "IecCfgSMVDatas.h"
#include <math.h>

CIecCfg92Ch::CIecCfg92Ch()
{
	//初始化属性
	m_strChType = iecfg_SmvChDataType_Val_Curr;
	m_nQuality = 0;
	m_nData = 0;

	//初始化成员变量
// 	m_strChType = g_strChTypeDT_prot;
	m_strAppChID = g_strAppChID_None;
	m_nIndexExternal = 65535;
}

CIecCfg92Ch::~CIecCfg92Ch()
{
}

long CIecCfg92Ch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataSmvChBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strAddrExternalKey, oNode, m_strAddrExternal);
	xml_GetAttibuteValue(pXmlKeys->m_strDescExternalKey, oNode, m_strDescExternal);
	xml_GetAttibuteValue(pXmlKeys->m_strIndexExternalKey, oNode, m_nIndexExternal);
	xml_GetAttibuteValue(pXmlKeys->m_strQualityKey, oNode, m_nQuality);
	xml_GetAttibuteValue(pXmlKeys->m_strDataKey, oNode, m_nData);

	if (m_strID.GetLength() == 0)
	{
		m_strID = m_strName;
	}

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	return 0;
}

long CIecCfg92Ch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataSmvChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (pXmlKeys->m_nXmlOnlyWrite_Id_Value == 0)
	{
		xml_SetAttributeValue(pXmlKeys->m_strAddrExternalKey, oElement, m_strAddrExternal);
		xml_SetAttributeValue(pXmlKeys->m_strDescExternalKey, oElement, m_strDescExternal);
		xml_SetAttributeValue(pXmlKeys->m_strIndexExternalKey, oElement, m_nIndexExternal);
	}

	xml_SetAttributeValue(pXmlKeys->m_strQualityKey, oElement, m_nQuality);
	xml_SetAttributeValue(pXmlKeys->m_strDataKey, oElement, m_nData);
	return 0;
}

BOOL CIecCfg92Ch::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataSmvChBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg92Ch *p = (CIecCfg92Ch*)pObj;

	if(m_strAddrExternal != p->m_strAddrExternal)
	{
		return FALSE;
	}

	if(m_strDescExternal != p->m_strDescExternal)
	{
		return FALSE;
	}

	if(m_nQuality != p->m_nQuality)
	{
		return FALSE;
	}

	if(m_nData != p->m_nData)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg92Ch::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataSmvChBase::CopyOwn(pDest);

	CIecCfg92Ch *p = (CIecCfg92Ch*)pDest;

	p->m_strAddrExternal = m_strAddrExternal;
	p->m_strDescExternal = m_strDescExternal;
	p->m_nIndexExternal = m_nIndexExternal;
	p->m_nQuality = m_nQuality;
	p->m_nData = m_nData;

	return TRUE;
}

CBaseObject* CIecCfg92Ch::Clone()
{
	CIecCfg92Ch *p = new CIecCfg92Ch();
	Copy(p);
	return p;
}

// void CIecCfg92Ch::GetChFlagHcn(long &nFlag, long &nHcn)
// {
// 	CIecCfgDataSmvChBase::GetChFlagHcn(nFlag, nHcn);
// // 	if (!IsChUse())
// // 	{//≥	0xF0, no hardware channel to be mapped to SAV
// // 		nFlag = 1;
// // 		nHcn = 0x7F;
// // 	}
// // 	else
// // 	{
// // 		if (IsTimeCh())
// // 		{//0xF2, the channel data is set by user
// // 			nFlag = 1;
// // 			nHcn = 0x72;
// // 		}
// // 		else if (IsZeroCh())
// // 		{//0xF0, the channel data will be set to 0
// // 			nFlag = 1;
// // 			nHcn = 0x70;
// // 		}
// // 		else if (IsAppCh())
// // 		{
// // 			CStSmvChDataType *pSmvDataType = CIecGlobalDataMngr::GetSmvDataType();
// // 			ASSERT (pSmvDataType != NULL);
// // 			nFlag = 0;
// // 			nHcn = pSmvDataType->FindIndexByID(m_strAppChID);
// // 			nHcn -= 3;
// // 
// // 			if (nHcn == -1)
// // 			{
// // 				nHcn = 0;
// // 			}	
// // 		}
// // 		else
// // 		{//≥	0xF0, no hardware channel to be mapped to SAV
// // 			nFlag = 1;
// // 			nHcn = 0x7F;
// // 		}
// // 
// // 	}
// }

// facotr= Vfactor或Ifactor
// Vfactor:电流系数：0.01允许用户输入，不常用
// 		Ifactor电压系数：0.001允许用户输入，不常用
// 		Vrtg：额定相电压，K：电流倍数，电压倍数,Kc：精度校验值。
// 		Vmax=K* Vrtg *√2
// 		mag=( K* Vrtg *√2)*Kc/(32767*factor)
// 		Voffset=Ioffset=0x8000-offset.
// 
// 		60044-8：
// 		mag=Kc;
// Voffset=Ioffset=0x8000-offset.
//参见配置文件SmvChDataType.xml
// DWORD CIecCfg92Ch::CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// {
// 	pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_92;
// 
// 	CIecCfgDatasMngr *pDatasMngr = (CIecCfgDatasMngr*)GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
// 	CIecCfgData92 *pData92 = (CIecCfgData92 *)GetAncestor(CFGCLASSID_CIECCFG92DATA);
// 	CStSmvChDataType *pSmvDataType = CIecGlobalDataMngr::GetSmvDataType();
// 
// 	ASSERT (pSmvDataType != NULL);
// 	CIecCfgDatasSMV *pSmv = (CIecCfgDatasSMV*)GetAncestor(CFGCLASSID_CIECCFGDATASSMV);
// 	ASSERT (pSmv != NULL);
// 
// 	if (pArtAmpDigData->Is_U())
// 	{//电压
// #ifdef _P_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = pData92->m_fUNom * 1000;
// 		pArtAmpDigData->m_dSecValue = pData92->m_fUNom2;
// #endif
// 
// 		double Vmax = pData92->m_nVoltateRate;
// 		Vmax *= pData92->m_fUNom * sqrt(2.0);
// 		Vmax /= sqrt(3.0);
// 		Vmax *= 1000;
// 		double mag = Vmax * m_fCoef ;
// 		mag = mag / (32767.0 * pData92->m_nPTBit / 1000.0);
// 		dwMag = mag;
// 		dwOffset = 0x8000 - pArtAmpDigData->m_nOffset;
// 		pArtAmpDigData->m_fDigMaxOut = Vmax;
// 		pArtAmpDigData->m_fDigOffset = pArtAmpDigData->m_nOffset;
// 	}
// 	else if (pArtAmpDigData->Is_I())
// 	{//电流
// #ifdef _P_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = pData92->m_fINom;
// 		pArtAmpDigData->m_dSecValue = pData92->m_fINom2;
// #endif
// 
// 		double Imax = pData92->m_nCurrRate;
// 		Imax *= pData92->m_fINom * sqrt(2.0);
// 		double mag = Imax * m_fCoef /(32767.0 * pData92->m_nCTBit / 1000.0);
// 		dwMag = mag;
// 		dwOffset = 0x8000 - pArtAmpDigData->m_nOffset;
// 		pArtAmpDigData->m_fDigMaxOut = Imax;
// 		pArtAmpDigData->m_fDigOffset = pArtAmpDigData->m_nOffset;
// 	}
// 	else
// 	{
// 	}
// 	
// 	return 0;
// }
// 

void CIecCfg92Ch::InitForSclRead(long &nUChIndex, long &nIChIndex)
{
	m_strAppChID = InitForSclRead_AppID(nUChIndex, nIChIndex);
}

void CIecCfg92Ch::InitCh()
{
	CIecCfgDataChBase::InitCh();
}

void CIecCfg92Ch::SetChTypeID(const CString &strLnClass)
{
	if (iecfg_IsTimeCh(m_strID))//m_strID.Find(_T("延时")) >= 0 || m_strID.Find(_T("延迟")) >= 0)
	{
		OnChTypeIDChanged(iecfg_SmvChDataType_Val_UTCTime);
		return;
	}

	if (iecfg_IsTimeCh(strLnClass))
	{
		OnChTypeIDChanged(iecfg_SmvChDataType_Val_UTCTime);
		return;
	}

	if (strLnClass.Find(_T("TVTR")) >= 0)
	{
		OnChTypeIDChanged(iecfg_SmvChDataType_Val_Vol);
		return;
	}

	if (strLnClass.Find(_T("TCTR")) >= 0)
	{
		OnChTypeIDChanged(iecfg_SmvChDataType_Val_Curr);
		return;
	}

	OnChTypeIDChanged(iecfg_SmvChDataType_Val_Curr);
	//		GGIO
	//		CSWI
	//		CILO
}

void CIecCfg92Ch::OnChTypeIDChanged(const CString &strChTypeID)
{
	if (m_strChType == strChTypeID)
	{
		if ( m_strChType == iecfg_SmvChDataType_Val_UTCTime )
		{
			if (m_strAppChID != g_strAppChID_TDelay)//zhouhj 20211030  延时通道,如果没有设置为延时,则改为延时
			{
				m_strAppChID = g_strAppChID_TDelay;
			}
		}

		return;
	}

	if ((m_strChType != iecfg_SmvChDataType_Val_UTCTime) && (iecfg_SmvChDataType_Val_UTCTime == strChTypeID))
	{
		m_strAppChID = _T("50");
	}
	else
	{
		m_strAppChID = g_strAppChID_None;
	}

	m_strChType = strChTypeID;
}

long CIecCfg92Ch::GetChAngType()
{
	if (m_strAppChID.GetLength()<3)
	{
		return 0;
	}

	long nChAngType = 0, nAngIndex = 0,nGroupIndex = 0;

	if (m_strAppChID.GetAt(1) == 'a')
	{
		nAngIndex = 0;
	}
	else if (m_strAppChID.GetAt(1) == 'b')
	{
		nAngIndex = 1;
	}
	else if (m_strAppChID.GetAt(1) == 'c')
	{
		nAngIndex = 2;
	}
	else if (m_strAppChID.GetAt(1) == '0')
	{
		nAngIndex = 3;
	}

	if ((m_strAppChID.GetAt(2)>='1') && (m_strAppChID.GetAt(2)<='9'))
	{
		nGroupIndex = (m_strAppChID.GetAt(2) - '1');
	}

	nChAngType = nAngIndex + 4*nGroupIndex;
	return nChAngType;
}