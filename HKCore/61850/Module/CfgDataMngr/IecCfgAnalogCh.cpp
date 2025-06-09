//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgAnalogCh.cpp  CIecCfgAnalogCh


#include "stdafx.h"
#include "IecCfgAnalogCh.h"
#include <math.h>

CIecCfgAnalogCh::CIecCfgAnalogCh()
{
	//初始化属性
	m_fPrimNom = 0;
	m_fSecNom = 0;
	m_fValue = 0;
	m_fCoef = 0;
	m_nOutput = 0;
	m_nOffset = 0;

	//初始化成员变量
}

CIecCfgAnalogCh::~CIecCfgAnalogCh()
{
}

long CIecCfgAnalogCh::XmlReadOwn(const MSXML2::IXMLDOMNodePtr &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strAppChID);
	xml_GetAttibuteValue(pXmlKeys->m_strPrimNomKey, oNode, m_fPrimNom);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_fValue);
	xml_GetAttibuteValue(pXmlKeys->m_strCoefKey, oNode, m_fCoef);
	xml_GetAttibuteValue(pXmlKeys->m_strOutputKey, oNode, m_nOutput);
	xml_GetAttibuteValue(pXmlKeys->m_strOffsetKey, oNode, m_nOffset);
	xml_GetAttibuteValue(pXmlKeys->m_strUnitKey, oNode, m_strUnit);

	if (m_strID.GetLength() == 0)
	{
		m_strID = m_strName;
	}

	if (m_strName.GetLength() == 0)
	{
		m_strName = m_strID;
	}

	xml_GetAttibuteValue(pXmlKeys->m_strSecNomKey, oNode, m_fSecNom);

	return 0;
}

long CIecCfgAnalogCh::XmlWriteOwn(const MSXML2::IXMLDOMDocumentPtr &oXMLDoc, const MSXML2::IXMLDOMElementPtr &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strAppChID);
	xml_SetAttributeValue(pXmlKeys->m_strPrimNomKey, oElement, m_fPrimNom);
	xml_SetAttributeValue(pXmlKeys->m_strSecNomKey, oElement, m_fSecNom);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_fValue);
	xml_SetAttributeValue(pXmlKeys->m_strCoefKey, oElement, m_fCoef);
	xml_SetAttributeValue(pXmlKeys->m_strOutputKey, oElement, m_nOutput);
	xml_SetAttributeValue(pXmlKeys->m_strOffsetKey, oElement, m_nOffset);
	xml_SetAttributeValue(pXmlKeys->m_strUnitKey, oElement, m_strUnit);
	return 0;
}

BOOL CIecCfgAnalogCh::IsEqualOwn(CExBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgAnalogCh *p = (CIecCfgAnalogCh*)pObj;

	if(m_strAppChID != p->m_strAppChID)
	{
		return FALSE;
	}

	if(m_fPrimNom != p->m_fPrimNom)
	{
		return FALSE;
	}

	if(m_fSecNom != p->m_fSecNom)
	{
		return FALSE;
	}

	if(m_fValue != p->m_fValue)
	{
		return FALSE;
	}

	if(m_fCoef != p->m_fCoef)
	{
		return FALSE;
	}

	if(m_nOutput != p->m_nOutput)
	{
		return FALSE;
	}

	if(m_nOffset != p->m_nOffset)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgAnalogCh::CopyOwn(CExBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgAnalogCh *p = (CIecCfgAnalogCh*)pDest;

	p->m_strAppChID = m_strAppChID;
	p->m_fPrimNom = m_fPrimNom;
	p->m_fSecNom = m_fSecNom;
	p->m_fValue = m_fValue;
	p->m_fCoef = m_fCoef;
	p->m_nOutput = m_nOutput;
	p->m_nOffset = m_nOffset;
	p->m_strUnit = m_strUnit;
	return TRUE;
}

CExBaseObject* CIecCfgAnalogCh::Clone()
{
	CIecCfgAnalogCh *p = new CIecCfgAnalogCh();
	Copy(p);
	return p;
}
// 
// DWORD CIecCfgAnalogCh::CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// {
// 	pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_ANALOG;
// // 	CIecCfgDataAnalog *pDataAnalog = (CIecCfgDataAnalog*)GetAncestor(CFGCLASSID_CIECCFGANALOGDATA);
// // 	ASSERT (pDataAnalog != NULL);
// #ifdef _ST_VERSION_USE_ANALOG
// 	pArtAmpDigData->m_dAnaValue = m_fValue / 1000;
// #endif
// 
// 	double dK = 0;
// 	dK = pArtAmpDigData->m_nMaxOut;
// 
// 	if (pArtAmpDigData->m_dwHcnCal <= 5)
// 	{
// 		dK = dK * 2.0 / 50.0 / 16384.0;
// 	}
// 	else
// 	{
// 		dK = dK * 0.6 / 3.0 / 65536.0;
// 	}
// 
// 	if (Is_U_CH())
// 	{//电压
// #ifdef _ST_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = m_fPrimNom ;
// 		pArtAmpDigData->m_dSecValue = m_fSecNom;
// 
// 		//Vmax=0x7FFF/比例因子* Vrtg=0x7FFF/比例因子*额定线电压（VAB /√3）
// // 		double Vmax = pArtAmpDigData->m_nMaxOut;
// // 		Vmax /= 16384.0;
// // 		Vmax = Vmax / 25.0 * m_fCoef;
// // 		Vmax = Vmax * m_fPrimNom / sqrt(3.0);
// // 		Vmax = Vmax / m_fValue;
// // 		Vmax *= 1000;
// // 		double mag = m_fCoef;
// // 		dwMag = mag;
// // 		dwOffset = 0x8000 - pArtAmpDigData->m_nOffset;
// 		pArtAmpDigData->m_fDigMaxOut = dK * m_fCoef * m_fPrimNom / sqrt(3.0) / (m_fValue / 1000);
// #else
// 		pArtAmpDigData->m_fDigMaxOut = pArtAmpDigData->m_nMaxOut;
// #endif
// 		pArtAmpDigData->m_fDigOffset = pArtAmpDigData->m_nOffset;
// 
// 	}
// 	else if (Is_I_CH())
// 	{//电流
// #ifdef _ST_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = m_fPrimNom;
// 		pArtAmpDigData->m_dSecValue = m_fSecNom;
// 
// // 		double Imax = pArtAmpDigData->m_nMaxOut;
// // 		Imax /= 65536.0f;
// // 		Imax *= 0.2;   //*0.6 / 3
// // 		Imax = Imax * m_fCoef * m_fPrimNom / m_fValue * 1000;
// 		pArtAmpDigData->m_fDigMaxOut = dK * m_fCoef * m_fPrimNom / (m_fValue / 1000);
// #else
// 		pArtAmpDigData->m_fDigMaxOut = pArtAmpDigData->m_nMaxOut;
// #endif
// 
// 		pArtAmpDigData->m_fDigOffset = pArtAmpDigData->m_nOffset;
// 	}
// 	else
// 	{
// 	}
// 
// 	return 0;
// }

 void CIecCfgAnalogCh::InitForSclRead(long &nUChIndex, long &nIChIndex)
 {
// 	 m_strAppChID = InitForSclRead_AppID();
// 	 m_strChType = InitForSclRead_ChType();
 }


 DWORD CIecCfgAnalogCh::InitArtAmpDigdata(CArtAmpDigdata *pData)
 {
	 long nCh = 0;
	 long nPhase = 0;
	
	 if (m_strAppChID.Left(1) == _T("I"))
	 {
		 nCh = 1;
	 }

// 	CHAR ch = m_strAppChID.GetAt(1);
// 	if ('A'<= ch && ch <= 'C')
// 	{
// 		nPhase = 4 + ch - 'A';
// 	}
// 	else if ('a'<= ch && ch <= 'c')
// 	{
// 		nPhase = ch - 'a';
// 	}
// 	else
// 	{
// 		nPhase = 0;
// 	}

	 CStSmvChDataType *pSmvDataType = CStGlobalDataMngr::GetSmvDataType();
	 ASSERT (pSmvDataType != NULL);
	 long nHcn = pSmvDataType->FindIndexByID(m_strAppChID);
	 nHcn -= 3;

	 if (0 <= nHcn && nHcn <= 11)
	 {//电压
		 pData->m_nTypeFlag = 0;
		 pData->m_nTypeFlagValue = nHcn;
	 }
	 else if (12 <= nHcn && nHcn <= 23)
	 {//电流
		 pData->m_nTypeFlag = 1;
		 pData->m_nTypeFlagValue = nHcn-12;
	 }

// 	long nHcn = nCh * 6 + nPhase;
//
//	pData->m_nTypeFlag = nCh;
//	pData->m_nTypeFlagValue = nPhase;

// 	 if (0 <= nHcn && nHcn <= 5)
// 	 {//电压
// 	 }
// 	 else if (6 <= nHcn && nHcn <= 11)
// 	 {//电流
// 		 pData->m_nTypeFlag = 1;
// 		 pData->m_nTypeFlagValue = nPhase;
// 	 }
// 	 else
// 	 {
// 		 pData->m_nTypeFlag = 0;
// 		 pData->m_nTypeFlagValue = nPhase;
// 	 }
// 
	 pData->m_nFiberFlag = 1; //一次

	 CIecCfgSmvDataBase *pCfgData = (CIecCfgSmvDataBase*)m_pParent->GetParent();
	 pData->m_nChannelFlag = pCfgData->GetCfgDataIndex() + 1;

	 CIecCfgDataChBase::InitArtAmpDigdata(pData);

	 return 0;
 }
