//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDataBase.cpp  CIecCfgDataBase


#include "stdafx.h"
#include "IecCfgDataBase.h"
#include "IecCfgDatasBase.h"
#include "../../Module/XLanguageResourceIec.h"
#include"../../../Module/API/GlobalConfigApi.h"

CIecCfgDataBase::CIecCfgDataBase()
{
	//初始化属性
	m_nUseFlag = 0;
	m_nChannelNum = 0;
	m_nFiberIndex = 0;
	m_nFiber2Index = 0;

	//初始化成员变量
	m_pCfgChs = NULL;
	m_nCfgDataViewState = 0;
	m_pSclRef = NULL;
#ifdef IECFG_USE_KEYDB
	m_pMatchList = NULL;
#endif
}


CIecCfgDataBase::~CIecCfgDataBase()
{
#ifdef IECFG_USE_KEYDB

	if (m_pMatchList != NULL)
	{
		delete m_pMatchList;
		m_pMatchList = NULL;
	}
#endif
}

#ifdef IECFG_USE_KEYDB
void CIecCfgDataBase::InitMatchList(CXKeyDB *pKeyDB)
{
	if (m_pMatchList == NULL)
	{
		m_pMatchList = new CXMatchList;
	}

	m_pMatchList->DeleteAll();
	m_pMatchList->Init(m_pCfgChs,pKeyDB);
}
#endif

long CIecCfgDataBase::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strUseFlagKey, oNode, m_nUseFlag);
	xml_GetAttibuteValue(pXmlKeys->m_strChannelNumKey, oNode, m_nChannelNum);
	xml_GetAttibuteValue(pXmlKeys->m_strFiberIndexKey, oNode, m_nFiberIndex);
	xml_GetAttibuteValue(pXmlKeys->m_strFiber2IndexKey, oNode, m_nFiber2Index);
	xml_GetAttibuteValue(pXmlKeys->m_strCtrlRefKey, oNode, m_strIedRefDesc);
	xml_GetAttibuteValue(pXmlKeys->m_strCfgDataViewStateKey, oNode, m_nCfgDataViewState);

	return 0;
}

long CIecCfgDataBase::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	//CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strUseFlagKey, oElement, m_nUseFlag);
	xml_SetAttributeValue(pXmlKeys->m_strChannelNumKey, oElement, m_nChannelNum);
	xml_SetAttributeValue(pXmlKeys->m_strFiberIndexKey, oElement, m_nFiberIndex);
	xml_SetAttributeValue(pXmlKeys->m_strFiber2IndexKey, oElement, m_nFiber2Index);
	xml_SetAttributeValue(pXmlKeys->m_strCtrlRefKey, oElement, m_strIedRefDesc);
	xml_SetAttributeValue(pXmlKeys->m_strCfgDataViewStateKey, oElement, m_nCfgDataViewState);

	return 0;
}

BOOL CIecCfgDataBase::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgDataBase *p = (CIecCfgDataBase*)pObj;

	if(m_nUseFlag != p->m_nUseFlag)
	{
		return FALSE;
	}

	if(m_nChannelNum != p->m_nChannelNum)
	{
		return FALSE;
	}

	if(m_nFiberIndex != p->m_nFiberIndex)
	{
		return FALSE;
	}

	if(m_nFiber2Index != p->m_nFiber2Index)
	{
		return FALSE;
	}

	if(m_strIedRefDesc != p->m_strIedRefDesc)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDataBase::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgDataBase *p = (CIecCfgDataBase*)pDest;

	p->m_nUseFlag = m_nUseFlag;
	p->m_nChannelNum = m_nChannelNum;
	p->m_nFiberIndex = m_nFiberIndex;
	p->m_nFiber2Index = m_nFiber2Index;
	p->m_strIedRefDesc = m_strIedRefDesc;
	p->m_pSclRef = m_pSclRef;

	return TRUE;
}

void CIecCfgDataBase::GetCfgDefaultConfigFile(CString &strFile)
{
	CString strTemp = GetCfgDefaultConfigFile();
	strFile = _P_GetConfigPath();
	strFile += strTemp;
}

BOOL CIecCfgDataBase::OpenCfgDefaultConfigFile()
{
	CString strFile;
	GetCfgDefaultConfigFile(strFile);

	BOOL b = OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	if (!b)
	{
#ifdef NOT_USE_XLANGUAGE
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("iec config file[%s] is not exist"), strFile.GetString());
#else
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_DefaultConfigFileNone.GetString() /*_T("缺省配置文件【%s】不存在")*/, strFile.GetString());
#endif
		InitAfterRead();
		SetChannelNum(12);
		//SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	}

	return b;
}



long CIecCfgDataBase::GetChannelNum()
{
	ASSERT (m_pCfgChs != NULL);

	if (m_pCfgChs != NULL)
	{
		return m_pCfgChs->GetCount();
	}
	else
	{
		return 0;
	}
}

BOOL CIecCfgDataBase::SaveCfgDefaultConfigFile()
{
	CString strFile;
	GetCfgDefaultConfigFile(strFile);

	return SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CIecCfgDataBase::SaveCfgDataTempFile()
{
	CString strFile = iecfg_GetCfgCapFileCfgData();

	return SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CIecCfgDataBase::OpenCfgDataTempFile()
{
	CString strFile = iecfg_GetCfgCapFileCfgData();

	return OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

void CIecCfgDataBase::RemoveTailCh(long nCountRemove, CExBaseList &oListRemove)
{
	ASSERT (m_pCfgChs != NULL);

	if (m_pCfgChs != NULL)
	{
		m_pCfgChs->RemoveTailCh(nCountRemove, oListRemove);
	}
}

BOOL CIecCfgDataBase::SetChannelNum(long nChannelNum)
{
	ASSERT (m_pCfgChs != NULL);

	if (m_pCfgChs != NULL)
	{
		BOOL bRet = m_pCfgChs->SetChannelNum(nChannelNum);

		if (bRet)
		{
			m_nChannelNum = nChannelNum;
		}
		
		return bRet;
	}
	else
	{
		return 0;
	}
}

long CIecCfgDataBase::GetChannels(CExBaseList &oListCh)
{
	ASSERT (m_pCfgChs != NULL);

	if (m_pCfgChs != NULL)
	{
		oListCh.Append(m_pCfgChs);
	}

	return oListCh.GetCount();
}

void CIecCfgDataBase::InitChs(UINT nClassID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == nClassID)
		{
			m_pCfgChs = (CIecCfgChsBase *)p;
		}
	}
}

long CIecCfgDataBase::GetCfgDataIndex()
{
	CIecCfgDatasBase *pCfgDatas = (CIecCfgDatasBase*)GetParent();
	CExBaseList oList;
	pCfgDatas->GetIecCfgDatas(oList);
	long nIndex = oList.FindIndex(this);
	oList.RemoveAll();
	return nIndex;
}
// 
// void CIecCfgDataBase::CalArtAmpDigdatas(CArtAmpDigdatas *pArtAmpDigdatas, long &nHdCnIndex)
// {
// 	POS pos = m_pCfgChs->GetHeadPosition();
// 	CIecCfgDataChBase *pCh = NULL;
// 	CArtAmpDigdata *pData = NULL;
// 	static long arrnHdIndex[] = {0x07,0x05,0x03,0x09,0x0A,0x0B,0x06,0x04,0x02,0x08,0x00,0x01};
// 
// 	while (pos != NULL)
// 	{
// 		pCh = (CIecCfgDataChBase *)m_pCfgChs->GetNext(pos);
// 
// 		if (pCh->IsAppCh())
// 		{
// 			pData = (CArtAmpDigdata *)pArtAmpDigdatas->FindByName(pCh->m_strAppChID);
// 
// 			if (pData == NULL)
// 			{
// 				pData = pArtAmpDigdatas->AddArtAmpDigdata(pCh->m_strAppChID);
// 
// 				if (pData == NULL)
// 				{
// 					break;
// 				}
// 
// 				pData->m_nDigFlag = 1;
// 				pData->m_dwHcnCal = arrnHdIndex[nHdCnIndex];
// 				pCh->InitArtAmpDigdata(pData);
// 				pCh->CalMagAndOffset(pData);
// 
// 				nHdCnIndex++;
// 			}
// 
// 			pCh->SetArtAmpDigdata(pData);
// 		}
// 		else
// 		{
// 			pCh->SetArtAmpDigdata(NULL);
// 		}
// 	}
// }


void CIecCfgDataBase::InitForSclRead()
{
	ASSERT (m_pCfgChs != NULL);

	POS pos = m_pCfgChs->GetHeadPosition();
	CIecCfgDataChBase *pCh = NULL;

	long nUChIndex = 0;
	long nIChIndex = 0;

	while (pos != NULL)
	{
		pCh = (CIecCfgDataChBase *)m_pCfgChs->GetNext(pos);
		pCh->InitForSclRead(nUChIndex, nIChIndex);
	}
}

CString CIecCfgDataBase::GetCfgDataName()
{
	long nIndex = GetCfgDataIndex();
	return GetCfgDataName(nIndex);
}

CString CIecCfgDataBase::GetCfgDataShortName()
{
	long nIndex = GetCfgDataIndex();
	return GetCfgDataShortName(nIndex);
}

//yyj
CIecCfgDataChBase* CIecCfgDataBase::GetCfgDataCh(int nIndex)
{
	if (m_pCfgChs == NULL)
	{
		return NULL;
	}

	CIecCfgDataChBase* pCfgDataCh = NULL;

	POS pos = m_pCfgChs->GetHeadPosition();

	while(pos)
	{
		pCfgDataCh = (CIecCfgDataChBase*)m_pCfgChs->GetNext(pos);
		if (pCfgDataCh->m_nIndex == nIndex)
		{
			return pCfgDataCh;
		}
	}

	return NULL;
}

#ifdef _PSX_IDE_QT_
BOOL CIecCfgDataBase::SetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
//		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue;
		m_nFiberIndex %= GetAppFiberCount();
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgDataBase::SetCfgDataValues(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
//		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue;
		//m_nFiberIndex %= GetAppFiberCount();//20240612 suyang 注销 多个插件 光口数显示不对，取余又从0开始，应顺序显示
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgDataBase::GetCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
//		vValue.vt = VT_I4;
		vValue = m_nFiberIndex;
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgDataBase::IsEqualCfgDataValue(long nDataID, unsigned long long &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
//		ASSERT (vValue.vt == VT_I4);
		return (vValue == m_nFiberIndex);
	}

	return FALSE;
}
#else
BOOL CIecCfgDataBase::SetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
		ASSERT (vValue.vt == VT_I4);
		m_nFiberIndex = vValue.lVal;
		m_nFiberIndex %= GetAppFiberCount();
		return TRUE;
	}

	return FALSE;
}


BOOL CIecCfgDataBase::GetCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
		vValue.vt = VT_I4;
		vValue.lVal = m_nFiberIndex;
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgDataBase::IsEqualCfgDataValue(long nDataID, VARIANT &vValue)
{
	if (nDataID == CFGDATAID_FIBER)
	{
		ASSERT (vValue.vt == VT_I4);
		return (vValue.lVal == m_nFiberIndex);
	}

	return FALSE;
}
#endif



BOOL CIecCfgDataBase::ValidateFiberIndex()
{
	CIecCfgDatasBase *pDatas = (CIecCfgDatasBase*)GetParent();

	return pDatas->ValidateFiberIndex(this);
}

long CIecCfgDataBase::GetAppFiberCount()
{
	return 8;
}

void iecfg_GetCfgDataValueMac(const CString  &strMac, BYTE *pbyteMac)
{
	char *pszMac = NULL;

#ifdef UNICODE
	CString_to_char(strMac, &pszMac);
#else
	pszMac = (char*)strMac.GetString();
#endif

	HexToValue(pszMac, pbyteMac, '-');

#ifdef UNICODE
	delete pszMac;
#endif
}

#ifdef _PSX_IDE_QT_

void iecfg_GetCfgDataValueMac(const CString  &strMac, unsigned long long &vValue)
{
	char pszMac[40];
	CString_to_char(strMac, pszMac, 40);
	BYTE pDest[20];
	long nLen = HexToValue(pszMac, pDest, '-');
//	vValue.vt = VT_UI8;
	vValue = 0;

	for (long nIndex = 0; nIndex< nLen; nIndex++)
	{
		vValue <<= 8;
		vValue += pDest[nIndex];
	}

}

void iecfg_SetCfgDataValueMac(CString  &strMac, unsigned long long &vValue)
{
	ASSERT (vValue.vt == VT_UI8);
	strMac = _T("");
	BYTE byte;

	for (long nIndex=5; nIndex>=0; nIndex--)
	{
		byte = (vValue >> (nIndex*8)) & 0xFF;
		strMac.AppendFormat(_T("%02X-"), byte);
	}

	strMac = strMac.Left(strMac.GetLength()-1);
}

#else

void iecfg_GetCfgDataValueMac(const CString  &strMac, VARIANT &vValue)
{
	char pszMac[40];
	CString_to_char(strMac, pszMac, 40);
	BYTE pDest[20];
	long nLen = HexToValue(pszMac, pDest, '-');
	vValue.vt = VT_UI8;
	vValue.ullVal = 0;

	for (long nIndex = 0; nIndex< nLen; nIndex++)
	{
		vValue.ullVal <<= 8;
		vValue.ullVal += pDest[nIndex];
	}

}

void iecfg_SetCfgDataValueMac(CString  &strMac, VARIANT &vValue)
{
	ASSERT (vValue.vt == VT_UI8);
	strMac = _T("");
	BYTE byte;

	for (long nIndex=5; nIndex>=0; nIndex--)
	{
		byte = (vValue.ullVal >> (nIndex*8)) & 0xFF;
		strMac.AppendFormat(_T("%02X-"), byte);
	}

	strMac = strMac.Left(strMac.GetLength()-1);
}
#endif


