//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//IecCfg91Ch.cpp  CIecCfg91Ch


#include "stdafx.h"
#include "IecCfg91Ch.h"

CIecCfg91Ch::CIecCfg91Ch()
{
	//��ʼ������
	m_dwStateWord = 0;

	//��ʼ����Ա����
	m_strChType = g_strChTypeDT_prot;
	m_strAppChID = g_strAppChID_None;
}

CIecCfg91Ch::~CIecCfg91Ch()
{
}

long CIecCfg91Ch::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataSmvChBase::XmlReadOwn(oNode, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strStateWordKey, oNode, m_dwStateWord);

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

long CIecCfg91Ch::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CIecCfgDataSmvChBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strStateWordKey, oElement, m_dwStateWord);

	return 0;
}

BOOL CIecCfg91Ch::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CIecCfgDataSmvChBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfg91Ch *p = (CIecCfg91Ch*)pObj;

	if(m_dwStateWord != p->m_dwStateWord)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfg91Ch::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDataSmvChBase::CopyOwn(pDest);

	CIecCfg91Ch *p = (CIecCfg91Ch*)pDest;

	p->m_dwStateWord = m_dwStateWord;

	return TRUE;
}

CBaseObject* CIecCfg91Ch::Clone()
{
	CIecCfg91Ch *p = new CIecCfg91Ch();
	Copy(p);
	return p;
}

// void CIecCfg91Ch::GetChFlagHcn(long &nFlag, long &nHcn)
// {
// 	return CIecCfgDataSmvChBase::GetChFlagHcn(nFlag, nHcn);
// }

// facotr= Vfactor��Ifactor
// Vfactor:����ϵ����0.01�����û����룬������
// 		Ifactor��ѹϵ����0.001�����û����룬������
// 		Vrtg������ѹ��K��������������ѹ����,Kc������У��ֵ��
// 		Vmax=K* Vrtg *��2
// 		mag=( K* Vrtg *��2)*Kc/(32767*factor)
// 		Voffset=Ioffset=0x8000-offset.
// 
// 		60044-8��
// 		mag=Kc;
// Voffset=Ioffset=0x8000-offset.
//�μ������ļ�SmvChDataType.xml
// DWORD CIecCfg91Ch::CalMagAndOffsetVal(CArtAmpDigdata *pArtAmpDigData, float &dwMag, float &dwOffset)
// {
// 	pArtAmpDigData->m_nProtocalFlag = PROTOCOL_61850_TYPE_91;
// 
// 	DWORD dwS = 0;
// 	CIecCfgDatasMngr *pDatasMngr = (CIecCfgDatasMngr*)GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
// 	CIecCfgData91 *pData91 = (CIecCfgData91 *)GetAncestor(CFGCLASSID_CIECCFG91DATA);
// 	CStSmvChDataType *pSmvDataType = CIecGlobalDataMngr::GetSmvDataType();
// 
// 	ASSERT (pSmvDataType != NULL);
// 	CIecCfgDatasSMV *pSmv = (CIecCfgDatasSMV*)GetAncestor(CFGCLASSID_CIECCFGDATASSMV);
// 	ASSERT (pSmv != NULL);
// 	DWORD dwRangeFlag = ((pData91->m_dwStateWord & 0x00002000) == 0x00002000) ? 1 : 0;
// 
// 	if (pArtAmpDigData->Is_U())
// 	{
// 		dwS = 0x2D41;
// #ifdef _P_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = pData91->m_fUNom * 1000;
// 		pArtAmpDigData->m_dSecValue = pData91->m_fUNom2;
// #endif
// 	}
// 	else
// 	{
// #ifdef _P_VERSION_USE_ANALOG
// 		pArtAmpDigData->m_dPriValue = pData91->m_fINom;
// 		pArtAmpDigData->m_dSecValue = pData91->m_fINom2;
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
// 	{//��ѹ
// 		//Vmax=0x7FFF/��������* Vrtg=0x7FFF/��������*��ߵ�ѹ��VAB /��3��
// 		double Vmax = 0x7FFF;
// 		Vmax /= dwS;
// 		Vmax *= pData91->m_fUNom / sqrt(3.0);
// 		Vmax *= 1000;
// 		double mag = m_fCoef;
// 		dwMag = mag;
// 		dwOffset = 0x8000 - pArtAmpDigData->m_nOffset;
// 		pArtAmpDigData->m_fDigMaxOut = Vmax;
// 		pArtAmpDigData->m_fDigOffset = pArtAmpDigData->m_nOffset;
// 	}
// 	else if (pArtAmpDigData->Is_I())
// 	{//����
// 		//Imax=0x7FFF/��������*�����
// 		double Imax = 0x7FFF;
// 		Imax /= dwS;
// 		Imax *= pData91->m_fINom;
// 		double mag = m_fCoef;
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

 void CIecCfg91Ch::InitForSclRead(long &nUChIndex, long &nIChIndex)
 {
	 m_strAppChID = InitForSclRead_AppID(nUChIndex, nIChIndex);
	 m_strChType = InitForSclRead_ChType();
 }


 void CIecCfg91Ch::SetChTypeID(const CString &strLnClass)
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

	 m_strChType = g_strChTypeDT_Voltage;
	 //		GGIO
	 //		CSWI
	 //		CILO
 }

