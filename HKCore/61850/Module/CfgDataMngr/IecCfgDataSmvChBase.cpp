//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataSmvChBase.cpp  CIecCfgDataSmvChBase


#include "stdafx.h"
#include "IecCfgDataSmvChBase.h"

CIecCfgDataSmvChBase::CIecCfgDataSmvChBase()
{
	//初始化属性
	m_fCoef = 0;
	m_nUseException = 0;

	//初始化成员变量
}

CIecCfgDataSmvChBase::~CIecCfgDataSmvChBase()
{
}

long CIecCfgDataSmvChBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataChBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCoefKey, oNode, m_fCoef);
	xml_GetAttibuteValue(pXmlKeys->m_strUseExceptionKey, oNode, m_nUseException);
	xml_GetAttibuteValue(pXmlKeys->m_strChTypeKey, oNode, m_strChType);

	return 0;
}

long CIecCfgDataSmvChBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (pXmlKeys->m_nXmlOnlyWrite_Id_Value == 0)
	{
		xml_SetAttributeValue(pXmlKeys->m_strUseExceptionKey, oElement, m_nUseException);
	}

	xml_SetAttributeValue(pXmlKeys->m_strCoefKey, oElement, m_fCoef);
	xml_SetAttributeValue(pXmlKeys->m_strChTypeKey, oElement, m_strChType);

	return 0;
}

BOOL CIecCfgDataSmvChBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataChBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDataSmvChBase *p = (CIecCfgDataSmvChBase*)pObj;

	if(m_fCoef != p->m_fCoef)
	{
		return FALSE;
	}

	if(m_nUseException != p->m_nUseException)
	{
		return FALSE;
	}

	if(m_strChType != p->m_strChType)
	{
		return FALSE;
	}


	return TRUE;
}

BOOL CIecCfgDataSmvChBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataChBase::CopyOwn(pDest);

	CIecCfgDataSmvChBase *p = (CIecCfgDataSmvChBase*)pDest;

	p->m_fCoef = m_fCoef;
	p->m_nUseException = m_nUseException;
	p->m_strChType = m_strChType;

	return TRUE;
}

CBaseObject* CIecCfgDataSmvChBase::Clone()
{
	CIecCfgDataSmvChBase *p = new CIecCfgDataSmvChBase();
	Copy(p);
	return p;
}

// 
// BYTE CIecCfgDataSmvChBase::GetChFlagHcn(long &nFlag, long &nHcn)
// {
// 	if (IsAppCh())
// 	{
// 		CIecCfgDatasMngr *pDatasMngr = (CIecCfgDatasMngr*)GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
// 		CArtAmpDigdatas *pArtAmpDigdatas = pDatasMngr->GetArtAmpDigdatas();
// 		CArtAmpDigdata *pArtAmpDigdata = (CArtAmpDigdata*)pArtAmpDigdatas->FindByName(m_strAppChID);
// 
// 		if (pArtAmpDigdata != NULL)
// 		{
// 			nFlag = 0;
// 			nHcn = pArtAmpDigdata->m_dwHcnCal;
// 		}
// 		else
// 		{
// 			nFlag = 1;
// 			nHcn = 0x70;
// 		}
// 	}
// 	else if (IsTimeCh())
// 	{//0xF2, the channel data is set by user
// 		nFlag = 1;
// 		nHcn = 0x72;
// 	}
// 	else
// 	{
// 		nFlag = 1;
// 		nHcn = 0x70;
// 	}
// 
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
// // 			CIecCfgDatasMngr *pDatasMngr = (CIecCfgDatasMngr*)GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
// // 			CArtAmpDigdatas *pArtAmpDigdatas = pDatasMngr->GetArtAmpDigdatas();
// // 			CArtAmpDigdata *pArtAmpDigdata = (CArtAmpDigdata*)pArtAmpDigdatas->FindByName(m_strAppChID);
// // 			nFlag = 0;
// // 			nHcn = pArtAmpDigdata->m_dwHcnCal;
// // 		}
// // 		else
// // 		{//≥	0xF0, no hardware channel to be mapped to SAV
// // 			nFlag = 1;
// // 			nHcn = 0x7F;
// // 		}
// // 
// // 	}
// 
// 	BYTE byteValue = BYTE(nFlag & 0x01);
// 	byteValue = byteValue << 7;
// 	byteValue |= BYTE(nHcn & 0x7F);
// 	return byteValue;
// }

void CIecCfgDataSmvChBase::InitAfterRead()
{
	if (! (iecfg_IsCurrSmvChType(m_strChType) || iecfg_IsVolSmvChType(m_strChType) || iecfg_IsUTCTimeSmvChType(m_strChType) ) )
	{
		m_strChType = iecfg_SmvChDataType_Val_Vol;
	}

	if (iecfg_IsCurrSmvChType(m_strChType))
	{
		if (!IsICh())
		{
			m_strAppChID = g_strAppChID_None;
		}
	}
	else if (iecfg_IsVolSmvChType(m_strChType))
	{
		if (!IsUCh())
		{
			m_strAppChID = g_strAppChID_None;
		}
	}
	else if (iecfg_IsUTCTimeSmvChType(m_strChType))
	{
// 		if (!IsStringNumber(m_strAppChID))
		if (!IsTCh())
		{
			m_strAppChID = g_strAppChID_TDelay;//g_strAppChID_None;
		}
		else if (m_strAppChID == g_strAppChID_None)
		{
			m_strAppChID = g_strAppChID_TDelay;//g_strAppChID_None;
		}
	}
	else if (iecfg_IsDCVolSmvChType(m_strChType))//zhouhj 20211012 待后期增加
	{
	}	
	else if (iecfg_IsDCCurSmvChType(m_strChType))//zhouhj 20211012 待后期增加
	{
	}	
	else if (iecfg_IsNeutralUSmvChType(m_strChType))//zhouhj 20211012 待后期增加
	{
	}	
	else if (iecfg_IsStateValueChType(m_strChType))//zhouhj 20211012 待后期增加
	{
//		m_strAppChID = 
	}
	else if (iecfg_IsOtherChType(m_strChType))//zhouhj 20211012 待后期增加
	{
//		m_strAppChID = 
	}	
	else
	{
		m_strAppChID = g_strAppChID_None;
	}
}


long CIecCfgDataSmvChBase::GetPhID(UINT nDefault)
{
	CString strDesc1,strDesc2;
	strDesc1 = _T("A相");
	strDesc2 = _T("a相");

	if ((m_strName.Find(strDesc1) >= 0) || (m_strName.Find(strDesc2) >= 0))
	{
		return UI_CH_INDEX_A;
	}

	strDesc1 = _T("B相");
	strDesc2 = _T("b相");

	if ((m_strName.Find(strDesc1) >= 0) || (m_strName.Find(strDesc2) >= 0))
	{
		return UI_CH_INDEX_B;
	}

	strDesc1 = _T("C相");
	strDesc2 = _T("c相");

	if ((m_strName.Find(strDesc1) >= 0) || (m_strName.Find(strDesc2) >= 0))
	{
		return UI_CH_INDEX_C;
	}

	strDesc1 = _T("零序");
	strDesc2 = _T("中性");

	if ((m_strName.Find(strDesc1) >= 0) || (m_strName.Find(strDesc2) >= 0))
	{
		return UI_CH_INDEX_0;
	}

	return nDefault;
}

void CIecCfgDataSmvChBase::InitCh()
{
	CIecCfgDataChBase::InitCh();
}

WORD CIecCfgDataSmvChBase::GetAppChIndex()
{
	//2016-5-14  为GuideBookDev增加装置配置
	ASSERT (FALSE);
// 	if (IsAppCh())
// 	{
// 		CIecSmvChDataType *pSmvDataType = CIecGlobalDataMngr::GetSmvDataType();
// 		ASSERT (pSmvDataType != NULL);
// 		WORD nHcn = pSmvDataType->FindIndexByID(m_strAppChID);
// 		nHcn -= 3;
// 
// 		if (nHcn == -1)
// 		{
// 			nHcn = 0;
// 		}
// 
// 		return nHcn;
// 	}
// 	else
	{
		return 0xFFFF;
	}
}
// 
// DWORD CIecCfgDataSmvChBase::InitArtAmpDigdata(CArtAmpDigdata *pData)
// {
// 	CStSmvChDataType *pSmvDataType = CIecGlobalDataMngr::GetSmvDataType();
// 	ASSERT (pSmvDataType != NULL);
// 	long nHcn = pSmvDataType->FindIndexByID(m_strAppChID);
// 	nHcn -= 3;
// 
// 	if (0 <= nHcn && nHcn <= 11)
// 	{//电压
// 		pData->m_nTypeFlag = 0;
// 		pData->m_nTypeFlagValue = nHcn;
// 	}
// 	else if (12 <= nHcn && nHcn <= 23)
// 	{//电流
// 		pData->m_nTypeFlag = 1;
// 		pData->m_nTypeFlagValue = nHcn-12;
// 	}
// 
// 	pData->m_nFiberFlag = 1; //一次
// 
// 	CIecCfgSmvDataBase *pCfgData = (CIecCfgSmvDataBase*)m_pParent->GetParent();
// 	pData->m_nChannelFlag = pCfgData->GetCfgDataIndex() + 1;
// 
// 	CIecCfgDataChBase::InitArtAmpDigdata(pData);
// 
// 	return 0;
// }

CString CIecCfgDataSmvChBase::InitForSclRead_AppID(long &nUChIndex, long &nIChIndex)
{
	if (m_strName.Find(_T("延时")) >= 0  || m_strName.Find(_T("延迟")) >= 0 || m_strID.Find(_T("DelayTRtg")) >= 0)
	{
		if (m_strAppChID == g_strAppChID_None)
		{
			return g_strAppChID_TDelay;
		}
		else
		{
			return g_strAppChID_TDelay;
		}
	}
	else
	{

		CString strUI = InitForSclRead_AppID_UI();
		CString strPhase = InitForSclRead_AppID_Ph();

		if (strUI.GetLength() == 0)
		{
			return g_strAppChID_None;
		}
		else
		{
			CString strIndex = InitForSclRead_AppID_Index(strUI == _T("U"), nUChIndex, nIChIndex, strPhase);
			return strUI + strPhase + strIndex;
		}
	}
}

CString CIecCfgDataSmvChBase::InitForSclRead_ChType()
{
	return InitForSclRead_ChType(m_strID);
}

CString CIecCfgDataSmvChBase::InitForSclRead_ChType(const CString &strName)
{
	if (strName.Find(_T("保护")) >= 0)
	{
		return g_strChTypeDT_prot;
	}

	if (strName.Find(_T("测量")) >= 0)
	{
		return g_strChTypeDT_measure;
	}

	if (strName.Find(_T("电压")) >= 0)
	{
		return g_strChTypeDT_Voltage;
	}

	return g_strChTypeDT_prot;
}

CString CIecCfgDataSmvChBase::InitForSclRead_AppID_Ph()
{
	CString strPhase = _T("a");
	CString strID = m_strID;
	strID.MakeUpper();

	if (strID.Find(_T("A相")) >= 0)
	{
		strPhase = _T("a");
	}
	else if (strID.Find(_T("B相")) >= 0)
	{
		strPhase = _T("b");
	}
	else if (strID.Find(_T("C相")) >= 0)
	{
		strPhase = _T("c");
	}
	else if (strID.Find(_T("A")) >= 0)
	{
		strPhase = _T("a");
	}
	else if (strID.Find(_T("B")) >= 0)
	{
		strPhase = _T("b");
	}
	else if (strID.Find(_T("C")) >= 0)
	{
		strPhase = _T("c");
	}
	else
	{
		strPhase = _T("");
	}

	return strPhase;
}

CString CIecCfgDataSmvChBase::InitForSclRead_AppID_UI()
{
	if (m_strID.Find(_T("电压")) >= 0 || m_strID.Find(_T("TVTR")) >= 0)
	{
		return _T("U");
	}
	else if (m_strID.Find(_T("电流")) >= 0 || m_strID.Find(_T("TCTR")) >= 0)
	{
		return _T("I");
	}
	else
	{
		return _T("");
	}
}

CString CIecCfgDataSmvChBase::InitForSclRead_AppID_Index(BOOL bIsUCh, long &nUChIndex, long &nIChIndex, CString &strPhase)
{
	CString strIndex;
	long nPhIndex = -1;
	long nIndex = -1;

	if (m_strID.Find(_T("1")) > 0)
	{
		strIndex = _T("1");
	}
	else if (m_strID.Find(_T("2")) > 0)
	{
		strIndex = _T("1");//strIndex = _T("2");
	}
	else if (m_strID.Find(_T("3")) > 0)
	{
		strIndex = _T("1");//strIndex = _T("3");
	}
	else
	{
		if (bIsUCh)
		{
			nUChIndex++;
			nIndex = nUChIndex;
		}
		else
		{
			nIChIndex++;
			nIndex = nIChIndex;
		}

		if (1 <= nIndex && nIndex <= 3)
		{
			nPhIndex = nIndex;
			nIndex = 1;
		}
		else if (4 <= nIndex && nIndex <= 6)
		{
			nPhIndex = nIndex - 3;
			nIndex = 2;
		}
		else if (7 <= nIndex && nIndex <= 9)
		{
			nPhIndex = nIndex - 6;
			nIndex = 3;
		}
		else
		{
			nPhIndex = 1;
			nIndex = 1;
		}

		nIndex = 1;//固定为1
		strIndex.Format(_T("%d"), nIndex);
	}

	if (strPhase.GetLength() == 0)
	{
		if (nPhIndex == 1)
		{
			strPhase = _T("a");
		}
		else if (nPhIndex == 2)
		{
			strPhase = _T("b");
		}
		else if (nPhIndex == 3)
		{
			strPhase = _T("c");
		}
		else
		{
			strPhase = _T("a");
		}
	}

	return strIndex;
}

void CIecCfgDataSmvChBase::SetAppChIndex(long nIndex)
{
	if (!IsAppCh())
	{
		return;
	}

	long nLen = m_strAppChID.GetLength();

	if (nLen <= 2)
	{
		return;
	}
	
	CHAR ch = m_strAppChID.GetAt(nLen-1);

	if ('1' <= ch && ch <= '3')
	{
		if (CHAR(nIndex) != ch)
		{
			m_strAppChID = m_strAppChID.Left(nLen-1);
			m_strAppChID.AppendFormat(_T("%d"), nIndex);
		}
	}
}

void CIecCfgDataSmvChBase::InitChTypeID_Name(const CString &strName)
{
	if (strName.GetLength() == 0)
	{
		m_strChType = InitForSclRead_ChType();
	}
	else
	{
		m_strChType = InitForSclRead_ChType(strName);
	}
}

void CIecCfgDataSmvChBase::SetAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent)
{
	if (iecfg_IsUTCTimeSmvChType(m_strChType))
	{
		return;
	}

	if (iecfg_IsCurrSmvChType(m_strChType) && bSetI)
	{
		SetAppCh(astrIChs);
	}
	else if (iecfg_IsVolSmvChType(m_strChType) && bSetU)
	{
		SetAppCh(astrUChs);
	}
	//2023/10/23 wjs 添加ChType是交流的电压/电流
	else if(iecfg_Is6CurrSmvChType(m_strChType)&&bSetI)
	{
		SetAppCh(astrIChs);
	}
	else if(iecfg_Is6VolSmvChType(m_strChType)&&bSetU)
	{
		SetAppCh(astrUChs);
	}

}

void CIecCfgDataSmvChBase::SetDcAppCh(BOOL bSetU, BOOL bSetI, CStringArray &astrUChs, const CStringArray &astrIChs, BOOL bIntelligent)
{
	if (iecfg_IsUTCTimeSmvChType(m_strChType))
	{
		return;
	}

	if(iecfg_IsDCCurSmvChType(m_strChType)&&bSetI)
	{
		SetAppCh(astrIChs);
	}
	else if(iecfg_IsDCVolSmvChType(m_strChType)&&bSetU)
	{
		SetAppCh(astrUChs);
	}
}

void CIecCfgDataSmvChBase::SetAppCh_U(const CStringArray &astrUChs, long &nChIndex, long nMaxChs, BOOL bIntelligent)
{
	m_strChType = iecfg_SmvChDataType_Val_Vol;
	
	//long nPhID = GetPhID(UI_CH_INDEX_NONE);
	long nPhID = UI_CH_INDEX_NONE;

	if (bIntelligent)
	{
		nPhID = GetPhID(UI_CH_INDEX_NONE);
	}

	if (nPhID == UI_CH_INDEX_NONE)
	{
		nPhID = nChIndex % nMaxChs;
	}
	
	m_strAppChID = astrUChs.GetAt(nPhID);
	nChIndex++;
}

void CIecCfgDataSmvChBase::SetAppCh_I(const CStringArray &astrIChs, long &nChIndex, long nMaxChs, BOOL bIntelligent)
{
	m_strChType = iecfg_SmvChDataType_Val_Curr;
	long nPhID = UI_CH_INDEX_NONE;
	
	if (bIntelligent)
	{
		nPhID = GetPhID(UI_CH_INDEX_NONE);
	}

	if (nPhID == UI_CH_INDEX_NONE)
	{
		nPhID = nChIndex % nMaxChs;
	}

	m_strAppChID = astrIChs.GetAt(nPhID);
	nChIndex++;
}


void CIecCfgDataSmvChBase::SetAppCh(const CStringArray &astrChs)
{
	long nChIndex = GetPhID();
	m_strAppChID = astrChs.GetAt(nChIndex);
}	

void CIecCfgDataSmvChBase::SetAppCh_0(BOOL bSetU, BOOL bSetI)
{
	if (iecfg_IsUTCTimeSmvChType(m_strChType)||iecfg_IsStateValueChType(m_strChType)||iecfg_IsOtherChType(m_strChType))
	{
		return;
	}

	if (iecfg_IsCurrSmvChType(m_strChType) && bSetI)
	{
		m_strAppChID = g_strAppChID_Zero;
	}
	else if (iecfg_IsVolSmvChType(m_strChType) && bSetU)
	{
		m_strAppChID = g_strAppChID_Zero;
	}
}

void CIecCfgDataSmvChBase::SwitchChMap(long nGroupIndex,BOOL bSetU, BOOL bSetI,BOOL bDC_FT3)
{
	if (iecfg_IsUTCTimeSmvChType(m_strChType))
	{
		return;
	}

	if ((iecfg_IsCurrSmvChType(m_strChType)&&bSetI)||(iecfg_IsVolSmvChType(m_strChType)&&(bSetU))
		||(iecfg_Is6CurrSmvChType(m_strChType)&&bSetI)||(iecfg_Is6VolSmvChType(m_strChType)&&bSetU))
	{
		if (bDC_FT3)
		{
			return;
		}

		if (m_strAppChID.GetLength() != 3)//排除其他类型通道映射
		{
			return;
		}

		if (m_strAppChID.GetAt(0) == '3')//排除3U0 3I0
		{
			return;
		}

		CString strNewAppChID;
		strNewAppChID = m_strAppChID.Left(2);
		strNewAppChID.AppendFormat("%ld",nGroupIndex+1);
		m_strAppChID = strNewAppChID;
	}
	else if ((iecfg_IsDCVolSmvChType(m_strChType)&&bSetU)||(iecfg_IsDCCurSmvChType(m_strChType)&&bSetI))
	{
		if (m_strAppChID.GetLength() != 4)//排除其他类型通道映射
		{
			return;
		}

		if (!bDC_FT3)
		{
			return;
		}

		CString strNewAppChID;
		strNewAppChID = m_strAppChID.Left(1);
		strNewAppChID.AppendFormat("%ld",nGroupIndex+1);
		strNewAppChID += m_strAppChID.Mid(2);
		m_strAppChID = strNewAppChID;
	}
}