//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfg6044Ch.cpp  CIecCfg6044Ch


#include "stdafx.h"
#include "IecCfg6044CommonCh.h"

CIecCfg6044CommonCh::CIecCfg6044CommonCh()
{
	//初始化属性

	//初始化成员变量
	m_strChType = g_strChTypeDT_prot;
	m_strAppChID = g_strAppChID_None;
	m_nChLenth = 3;
	m_nValue = 0;
}

CIecCfg6044CommonCh::~CIecCfg6044CommonCh()
{
}

long CIecCfg6044CommonCh::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataSmvChBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strChLenth, oNode, m_nChLenth);
	xml_GetAttibuteValue(pXmlKeys->m_strCValueKey, oNode, m_nValue);


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

long CIecCfg6044CommonCh::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataSmvChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strChLenth, oElement, m_nChLenth);
	xml_SetAttributeValue(pXmlKeys->m_strCValueKey, oElement, m_nValue);

	return 0;
}

BOOL CIecCfg6044CommonCh::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataSmvChBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg6044CommonCh *p = (CIecCfg6044CommonCh*)pObj;

	if(m_nChLenth != p->m_nChLenth)
	{
		return FALSE;
	}

	if(m_nValue != p->m_nValue)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg6044CommonCh::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataSmvChBase::CopyOwn(pDest);

	CIecCfg6044CommonCh *p = (CIecCfg6044CommonCh*)pDest;
	p->m_nChLenth = m_nChLenth;
	p->m_nValue = m_nValue;

	return TRUE;
}

CBaseObject* CIecCfg6044CommonCh::Clone()
{
	CIecCfg6044CommonCh *p = new CIecCfg6044CommonCh();
	Copy(p);
	return p;
}


// void CIecCfg6044Ch::GetChFlagHcn(long &nFlag, long &nHcn)
// {
// 	CIecCfgDataSmvChBase::GetChFlagHcn(nFlag, nHcn);
// }

/*
60044-8 精度算法：
S=SCM、SCP、SV;
VR=100V,110V；IR=1A,5A;
Vi’：瞬时值，Vh’=十六进制瞬时值;
Vi’=Vi;
Vh’=( S/VR)*Vi= (S/VR)*( Vmax/32767)*Vh;
Vmag= Vh’/ Vh=(S/VR)*( Vmax/32767);
=(S/VR)*( (V_MAX/214)/32767);
Imag=(S/VR)*( (I_MAX/216)/32767);
Voffset=Ioffset=0x8000-offset.

对测量值的数据通道分配，可根据合并单元采样发送数据集中的内容灵活配置。
保护三相电流参考值为额定相电流，比例因子为SCP。
中性点电流参考值为额定中性点电流，比例因子为SCP。
测量三相电流参考值为额定相电流，比例因子为SCM。
电压参考值为额定相电压，比例因子为SV。

								测量用ECT（比例因子SCM）	保护用ECT（比例因子SCP）	EVT（比例因子SV）
额定值(range-flag=0)			2D41 H（十进制11585）		01CF H（十进制463）			2D41 H（十进制11585）
额定值量程标志(range-flag=1)	2D41 H（十进制11585）		00E7 H（十进制231）			2D41 H（十进制11585）
*/
// 
// DWORD CIecCfg6044Ch::CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// {
// 	pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_6044;
// 
// 	DWORD dwS = 0;
// 	CIecCfgDatasMngr *pDatasMngr = (CIecCfgDatasMngr*)GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
// 	CIecCfgData6044 *pData6044 = (CIecCfgData6044 *)GetAncestor(CFGCLASSID_CIECCFG6044DATA);
// 	CStSmvChDataType *pSmvDataType = CIecGlobalDataMngr::GetSmvDataType();
// 
// 	ASSERT (pSmvDataType != NULL);
// 	CIecCfgDatasSMV *pSmv = (CIecCfgDatasSMV*)GetAncestor(CFGCLASSID_CIECCFGDATASSMV);
// 	ASSERT (pSmv != NULL);
// 	DWORD dwRangeFlag = ((pData6044->m_dwStateWord & 0x00002000) == 0x00002000) ? 1 : 0;
// 
// 	if (pArtAmpDigData->Is_U())
// 	{
// 		dwS = 0x2D41;
// #ifdef _P_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = pData6044->m_fUNom * 1000;
// 		pArtAmpDigData->m_dSecValue = pData6044->m_fUNom2;
// #endif
// 	}
// 	else
// 	{
// #ifdef _P_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = pData6044->m_fINom;
// 		pArtAmpDigData->m_dSecValue = pData6044->m_fINom2;
// #endif
// 
// 		if (m_strChType == g_strChTypeDT_measure)
// 		{
// 			if (dwRangeFlag == 0)
// 			{
// 				dwS = 0x2D41;
// 			}
// 			else
// 			{
// 				dwS = 0x2D41;
// 			}
// 		}
// 		else// if (m_strChType == g_strChTypeDT_Prot)
// 		{
// 			if (dwRangeFlag == 0)
// 			{
// 				dwS = 0x01CF;
// 			}
// 			else
// 			{
// 				dwS = 0x00E7;
// 			}
// 		}
// 	}
// 
// 	if (pArtAmpDigData->Is_U())
// 	{//电压
// 		//Vmax=0x7FFF/比例因子* Vrtg=0x7FFF/比例因子*额定线电压（VAB /√3）
// 		double Vmax = 0x7FFF;
// 		Vmax /= dwS;
// 		Vmax *= pData6044->m_fUNom / sqrt(3.0);
// 		Vmax *= 1000;
// 		double mag = m_fCoef;
// 		dwMag = mag;
// 		dwOffset = 0x8000 - pArtAmpDigData->m_nOffset;
// 		pArtAmpDigData->m_fDigMaxOut = Vmax;
// 		pArtAmpDigData->m_fDigOffset = pArtAmpDigData->m_nOffset;
// 	}
// 	else if (pArtAmpDigData->Is_I())
// 	{//电流
// 		//Imax=0x7FFF/比例因子*额定电流
// 		double Imax = 0x7FFF;
// 		Imax /= dwS;
// 		Imax *= pData6044->m_fINom;
// 		double mag = m_fCoef;
// 		dwMag = mag;
// 		dwOffset = 0x8000 - pArtAmpDigData->m_nOffset;
// 		pArtAmpDigData->m_fDigMaxOut = Imax;
// 		pArtAmpDigData->m_fDigOffset =  pArtAmpDigData->m_nOffset;
// 	}
// 	else
// 	{
// 	}
// 
// 	return 0;
// }


void CIecCfg6044CommonCh::InitForSclRead(long &nUChIndex, long &nIChIndex)
{
// 	m_strAppChID = InitForSclRead_AppID(nUChIndex, nIChIndex);
// 	m_strChType = InitForSclRead_ChType();
}

void CIecCfg6044CommonCh::InitAfterRead()
{
}

long CIecCfg6044CommonCh::GetChAngType()
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

void CIecCfg6044CommonCh::SetChTypeID(const CString &strLnClass)
{
	CString strClass = strLnClass;
	strClass.MakeUpper();

	if (strClass.Find(_T("TVTR")) >= 0)
	{
		m_strChType = g_strChTypeDT_Voltage;
		return;
	}

	if (strClass.Find(_T("TCTR")) >= 0)
	{
		m_strChType = g_strChTypeDT_prot;
		return;
	}

	if (strClass.Find(_T("TRTG")) >= 0)
	{
		m_strChType = g_strChTypeDT_prot;
		return;
	}

	m_strChType = g_strChTypeDT_Voltage;
//		GGIO
//		CSWI
//		CILO
}

