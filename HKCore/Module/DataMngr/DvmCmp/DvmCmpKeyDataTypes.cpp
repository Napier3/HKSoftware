//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmCmpKeyDataTypes.cpp  CDvmCmpKeyDataTypes


#include "stdafx.h"
#include "DvmCmpKeyDataTypes.h"
#include "DvmMapObject.h"
#include "../../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////////
const CString CDvmCmpKeyDataTypes::g_strLdeviceDataTypeID = _T("ldevice-key");
const CString CDvmCmpKeyDataTypes::g_strDatasetDataTypeID = _T("dataset-key");
const CString CDvmCmpKeyDataTypes::g_strDvmCmpValueKeyDataTypeID = _T("value-key");
const CString CDvmCmpKeyDataTypes::g_strDvmCmpFullNameIdKeyTypeID = _T("full-name-id-key");

CDvmCmpKeyDataTypes::CDvmCmpKeyDataTypes()
{

}

CDvmCmpKeyDataTypes::~CDvmCmpKeyDataTypes()
{
	
}

//比较名称、ID
long CDvmCmpKeyDataTypes::CanCmpDvmObject(CExBaseObject *pStand, CExBaseObject *pDestCmpObj)
{
	//名称相同
	if ( (pStand->m_strName.GetLength() > 0) && (pStand->m_strName == pDestCmpObj->m_strName) )
	{
		return 100;
	}

	//shaolei 20220209 增加ID相同
	if ( (pStand->m_strID.GetLength() > 0) && (pStand->m_strID == pDestCmpObj->m_strID) )
	{
		return 100;
	}

	//名称包含
	if ((pStand->m_strName.Find(pDestCmpObj->m_strName) >= 0) && (pDestCmpObj->m_strName.GetLength() > 0))
	{
		return 80;
	}

	if ((pDestCmpObj->m_strName.Find(pStand->m_strName) >= 0) && (pStand->m_strName.GetLength() > 0))
	{
		return 80;
	}

	//ID包含   shaolei 20220209
	if ((pStand->m_strID.Find(pDestCmpObj->m_strID) >= 0) && (pDestCmpObj->m_strID.GetLength() > 0))
	{
		return 80;
	}

	if ((pDestCmpObj->m_strID.Find(pStand->m_strID) >= 0) && (pStand->m_strID.GetLength() > 0))
	{
		return 80;
	}

	return 0;
}

long CDvmCmpKeyDataTypes::CanCmpDvmObject_ID(CExBaseObject *pStand, CExBaseObject *pDestCmpObj)
{
	//ID相同
	if ((pStand->m_strID.GetLength() > 0) && (pStand->m_strID == pDestCmpObj->m_strID))
	{
		return 100;
	}

	//ID包含
	if ((pStand->m_strID.Find(pDestCmpObj->m_strID) >= 0) && (pDestCmpObj->m_strID.GetLength() > 0))
	{
		return 90;
	}

	if ((pDestCmpObj->m_strID.Find(pStand->m_strID) >= 0) && (pStand->m_strID.GetLength() > 0))
	{
		return 90;
	}

	//20231102 huangliang 分割ID后，匹配数量
	return CanCmpID(pStand->m_strID, pDestCmpObj->m_strID);
}
long CDvmCmpKeyDataTypes::CanCmpID(const CString &strSrcID1, const CString &strSrcID2)
{
	vector <CString> vecSID1 = SplitCString(strSrcID1, _T("$"));
	vector <CString> vecSID2 = SplitCString(strSrcID2, _T("$"));

	long lValue = 0;
	for(int i=0; i<vecSID1.size(); i++)
	{
		for(int j=0; j<vecSID2.size(); j++)
		{
			if(vecSID1[i] == vecSID2[j])
			{
				lValue++;
			}
		}
	}

	return lValue;
}
vector<CString> CDvmCmpKeyDataTypes::SplitCString(const CString &strSource, const CString &ch)
{
	vector <CString> vecString;
#ifndef _PSX_IDE_QT_
	int iPos = 0;
	CString strTmp;
	strTmp = strSource.Tokenize(ch,iPos);
	while(strTmp.Trim() != _T(""))
	{
		vecString.push_back(strTmp);
		strTmp = strSource.Tokenize(ch,iPos);
	}
#endif
	return vecString;
}

void CDvmCmpKeyDataTypes::OpenKeyDataTypesFile(const CString &strFile)
{
	CString strPath;

	strPath = _P_GetConfigPath();

	if (strFile.GetLength() == 0)
	{
		strPath += _T("DvmTestKeyDataTypes.xml");
	}
	else
	{
		strPath += strFile;
	}

	OpenXmlFile(strPath, CDataMngrXmlRWKeys::CDataTypesKey(), CDataMngrXmlRWKeys::g_pXmlKeys);

	m_pDatasetDataType = (CDataType*)FindByID(g_strDatasetDataTypeID);
	m_pLdeviceDataType = (CDataType*)FindByID(g_strLdeviceDataTypeID);
	m_pDvmCmpValueKeyDataType = (CDataType*)FindByID(g_strDvmCmpValueKeyDataTypeID);
	m_pDvmCmpFullNameIdKeyType = (CDataType*)FindByID(g_strDvmCmpFullNameIdKeyTypeID);
}


long CDvmCmpKeyDataTypes::GetLdeviceKey(const CString &strText)
{
	return GetKey(m_pLdeviceDataType, strText);
}

long CDvmCmpKeyDataTypes::GetDatasetKey(const CString &strText)
{
	return GetKey(m_pDatasetDataType, strText);
}


long CDvmCmpKeyDataTypes::GetCmpFullNameIdKey(const CString &strText)
{
	if (m_pDvmCmpFullNameIdKeyType == NULL)
	{
		return -1;
	}

	CString strTemp = strText;
	strTemp.MakeLower();

	POS pos = m_pDvmCmpFullNameIdKeyType->GetHeadPosition();
	CDataTypeValue *pVal = NULL;
	long nIndex = 0, nIndexFind = -1;

	while (pos != NULL)
	{
		pVal = (CDataTypeValue *)m_pDvmCmpFullNameIdKeyType->GetNext(pos);

		if (strTemp.Find(pVal->m_strID) >= 0)
		{
#ifdef _UNICODE
			nIndexFind = _wtoi(pVal->m_strIndex);
#else
//			nIndexFind = atoi(pVal->m_strIndex);
			nIndexFind = CString_To_long(pVal->m_strIndex);
#endif
			break;
		}

		nIndex++;
	}

	return nIndexFind;
}

long CDvmCmpKeyDataTypes::GetKey(CDataType *pDataType, const CString &strText)
{
	if (pDataType == NULL)
	{
		return -1;
	}

	POS pos = pDataType->GetHeadPosition();
	CDataTypeValue *pVal = NULL;
	long nIndex = 0, nIndexFind = -1;

	while (pos != NULL)
	{
		pVal = (CDataTypeValue *)pDataType->GetNext(pos);

		if (strText.Find(pVal->m_strID) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}

		nIndex++;
	}

	return nIndexFind;
}


CString CDvmCmpKeyDataTypes::GetDvmValueKey(CDvmValue *pDvmValue)
{
	CDataTypeValue *pFind     = NULL;
	CString strKey;

	if (m_pDvmCmpValueKeyDataType != NULL)
	{
		POS pos = m_pDvmCmpValueKeyDataType->GetHeadPosition();
		CDataTypeValue *pDataTypeValue = NULL;

		while (pos != NULL)
		{
			pDataTypeValue = (CDataTypeValue *)m_pDvmCmpValueKeyDataType->GetNext(pos);

			if (pDvmValue->m_strID.Right(pDataTypeValue->m_strID.GetLength())  == pDataTypeValue->m_strID)
			{
				pFind = pDataTypeValue;
				break;
			}
		}
	}

	if (pFind != NULL)
	{
		strKey = pFind->m_strID;
	}
	else
	{
		long nPos = pDvmValue->m_strID.ReverseFind('$');
		strKey = pDvmValue->m_strID.Mid(nPos);
	}

	return strKey;
}

void CDvmCmpKeyDataTypes::DvmCmpLdevice(CExBaseList *pSrcDevice, CExBaseList *pDestDevice, CExBaseList &listMap)
{
#ifdef DVM_USE_MAP
	POS posSrc = pSrcDevice->GetHeadPosition();
	CExBaseObject *pSrcLd = NULL;
	CExBaseObject *pDestLd = NULL;
	long nKey = 0;
	CDvmMapObject *pMap = NULL;

	while (posSrc != NULL)
	{
		pSrcLd = (CExBaseObject *)pSrcDevice->GetNext(posSrc);
		nKey = GetLdeviceKey(pSrcLd->m_strID);
		pDestLd = FindLdevice (pDestDevice, nKey);

		if (pDestLd != NULL)
		{
			pMap = new CDvmMapObject();
			listMap.AddTail(pMap);
		}
	}
#endif
}

void CDvmCmpKeyDataTypes::DvmCmpDataset(CExBaseList *pSrcLdevice, CExBaseList *pDestLdevice, CExBaseList &listMap)
{
#ifdef DVM_USE_MAP
	POS posSrc = pSrcLdevice->GetHeadPosition();
	CExBaseObject *pSrcDs = NULL;
	CExBaseObject *pDestDs = NULL;
	long nKey = 0;
	CDvmMapObject *pMap = NULL;

	while (posSrc != NULL)
	{
		pSrcDs = (CExBaseObject *)pSrcLdevice->GetNext(posSrc);
		nKey = GetLdeviceKey(pSrcDs->m_strID);
		pDestDs = FindDataset(pDestLdevice, nKey);

		if (pDestDs != NULL)
		{
			pMap = new CDvmMapObject();
			listMap.AddTail(pMap);
		}
	}
#endif
}

CExBaseObject* CDvmCmpKeyDataTypes::FindLdevice(CExBaseList *pDevice, long nKey)
{
	POS posSrc = pDevice->GetHeadPosition();
	CExBaseObject *pLd = NULL;
	CExBaseObject *pLdFind = NULL;
	long nKeyCurr = 0;

	while (posSrc != NULL)
	{
		pLd = (CExBaseObject *)pDevice->GetNext(posSrc);
		nKeyCurr = GetLdeviceKey(pLd->m_strID);

		if (nKeyCurr == nKey)
		{
			pLdFind = pLd;
			break;
		}
	}

	return pLdFind;
}


CExBaseObject* CDvmCmpKeyDataTypes::FindDataset(CExBaseList *pLdevice, long nKey)
{
	POS posSrc = pLdevice->GetHeadPosition();
	CExBaseObject *pDataset = NULL;
	CExBaseObject *pDatasetFind = NULL;
	long nKeyCurr = 0;

	while (posSrc != NULL)
	{
		pDataset = (CExBaseObject *)pLdevice->GetNext(posSrc);
		nKeyCurr = GetLdeviceKey(pDataset->m_strID);

		if (nKeyCurr == nKey)
		{
			pDatasetFind = pDataset;
			break;
		}
	}

	return pDatasetFind;
}

