//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmDatasetGroup.cpp  CDvmDatasetGroup


#include "stdafx.h"
#include "DvmDatasetGroup.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CDvmDatasetGroup::CDvmDatasetGroup()
{
    m_strName = /*g_sLangTxt_DataSets*/_T("Dataset");
	m_strID = _T("dataset");

	//初始化属性
	m_nIndex = 0;
	m_nWriteMode = 0;

	//初始化成员变量
	m_pDvmBrcb = NULL;
}

CDvmDatasetGroup::~CDvmDatasetGroup()
{
	if (m_pDvmBrcb != NULL)
	{
		delete m_pDvmBrcb;
		m_pDvmBrcb = NULL;
	}
}

long CDvmDatasetGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlReadOwn(oNode, pXmlRWKeys);


	return 0;
}

long CDvmDatasetGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDvmDataset::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);


	return 0;
}

long CDvmDatasetGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CDvmDataset::SerializeOwn(oBinaryBuffer);

	return 0;
}

BOOL CDvmDatasetGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CDvmDataset::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDvmDatasetGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDataset::CopyOwn(pDest);

	CDvmDatasetGroup *p = (CDvmDatasetGroup*)pDest;

	return TRUE;
}

void CDvmDatasetGroup::CopyChildrenWithDwData(CExBaseList* pSrc, CExBaseList* pDest)
{
	for (int i = 0; i < pSrc->GetCount(); i++)
	{
		CExBaseList* pSrcChild = (CExBaseList*)pSrc->GetAt(i);
		CExBaseList* pDestChild = (CExBaseList*)pDest->GetAt(i);
		pDestChild->m_dwItemData = pSrcChild->m_dwItemData;
		pDestChild->m_dwReserved = pSrcChild->m_dwReserved;
		if(pSrcChild->GetCount())
		{
			CopyChildrenWithDwData(pSrcChild, pDestChild);
		}
	}
}

BOOL CDvmDatasetGroup::CopyChildren(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDvmDataset::CopyChildren(pDest);

	//将dwReserved和dwItemData都进行复制
	CopyChildrenWithDwData(this, (CExBaseList*)pDest);

	return TRUE;
}

CBaseObject* CDvmDatasetGroup::Clone()
{
	CDvmDatasetGroup *p = new CDvmDatasetGroup();
	Copy(p);
	return p;
}

CBaseObject* CDvmDatasetGroup::CloneEx(BOOL bCopyOwn,BOOL bCopyChildren)
{
	CDvmDatasetGroup *pNew = new CDvmDatasetGroup();
	if(bCopyOwn)
	{
		CopyOwn(pNew);
	}
	if(bCopyChildren)
	{
		CopyChildren(pNew);
	}	
	return pNew;
}

CExBaseObject* CDvmDatasetGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCDvmDatasetGroupKey)
	{
		pNew = new CDvmDatasetGroup();
	}
	else
	{
		pNew = CDvmDataset::CreateNewChild(strClassID, bAddToTail, pXmlRWKeys);
	}

	return pNew;
}

CExBaseObject* CDvmDatasetGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;

	if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
	{
		pNew = new CDvmDatasetGroup();
	}
	else
	{
		pNew = CDvmDataset::CreateNewChild(nClassID);
	}

	return pNew;
}

BOOL CDvmDatasetGroup::CanPaste(UINT nClassID)
{
	if (nClassID == DVMCLASSID_CDVMDATA 
		|| nClassID == DVMCLASSID_CDVMDATASETGROUP)
	{
		return TRUE;
	}

	return FALSE;
}

void CDvmDatasetGroup::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	POS posBrcb = NULL;

	while (pos != NULL)
	{
		posBrcb = pos;
		p = GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMBRCB)
		{
			m_pDvmBrcb = (CDvmBrcb *)p;
			break;
		}
	}

	if (m_pDvmBrcb != NULL)
	{
		delete m_pDvmBrcb;
		m_pDvmBrcb = NULL;
		RemoveAt(posBrcb);
	}
}

BOOL CDvmDatasetGroup::UpdateDataValue(CDvmDataset *pSrcDataset, BOOL bIsNew)
{
	BOOL bRet = TRUE;
	POS pos = pSrcDataset->GetHeadPosition();
	CDvmData *pSrcData = NULL;
	CDvmData *pDstData = NULL;
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;
	CString strSrcID;

	while (pos != NULL)
	{
		pObj = pSrcDataset->GetNext(pos);
		strSrcID = pObj->m_strID;
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pSrcDatasetGroup = (CDvmDatasetGroup *)pObj;
			CDvmDatasetGroup *pDestObj = (CDvmDatasetGroup*)FindByID(strSrcID);

			if(!pDestObj)
			{
				if (bIsNew)
				{
					pDestObj = (CDvmDatasetGroup *)pSrcDatasetGroup->CloneEx(TRUE, TRUE);
					AddNewChild(pDestObj);
					continue;
				}
				else
				{
					bRet = FALSE;
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("数据集数据更新，数据【%s】未找到"), strSrcID.GetString());
					continue;
				}
			}

			if (pDestObj->GetClassID() != DVMCLASSID_CDVMDATASETGROUP)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("数据集更新，数据集不一致，更新失败！"));
				return FALSE;
			}

			bRet = pDestObj->UpdateDataValue(pSrcDatasetGroup, bIsNew);

			if (!bRet)
			{
				return bRet;
			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATA)
		{
			pSrcData = (CDvmData *)pObj;
			pDstData = (CDvmData *)FindByID(strSrcID);

			if (pDstData == NULL)
			{
				if (bIsNew)
				{
					pDstData = (CDvmData *)pSrcData->CloneEx(TRUE,TRUE);
					AddNewChild(pDstData);
					continue;
				}
				else
				{
					bRet = FALSE;
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("数据集数据更新，数据【%s】未找到"), strSrcID.GetString());
					continue;
				}
			}
			else
			{
				pDstData->m_strValue = pSrcData->m_strValue;
				bRet = pDstData->UpdateChildValue(pSrcData, bIsNew);
			}
		}	
	}

	return TRUE;
}

void CDvmDatasetGroup::FilterDataExEqualValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;

			if (pData->HasValueEx(strTagID, strValue))
			{
				oDestList.AddTail(pData);
				continue;
			}

			CDvmValue *pValue = pData->HasValueEx_Child(strTagID, strValue);

			if(pValue != NULL)
			{
				CDvmData *pNew = new CDvmData();
				pNew->m_strValue = pValue->m_strValue;
				pNew->m_strDataType = pValue->m_strDataType;
				pNew->m_strID = pValue->m_strID;
				pNew->m_strName = pValue->m_strName;
				oDestList.AddTail(pNew);
 			}
// 			else if (pData->HasValueEx_Child(strTagID, strValue))
// 			{
// 				oDestList.AddTail(pData);
// 			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterDataExEqualValueStr(oDestList, strTagID, strValue);
		}
	}
}

void CDvmDatasetGroup::FilterDataExHasValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;

			if (pData->HasValueHasStr(strTagID, strValue))
			{
				oDestList.AddTail(pData);
				continue;
			}

			CDvmValue *pValue = pData->HasValueHasStr_Child(strTagID, strValue);

			if(pValue != NULL)
			{
				CDvmData *pNew = new CDvmData();
				pNew->m_strValue = pValue->m_strValue;
				pNew->m_strDataType = pValue->m_strDataType;
				pNew->m_strID = pValue->m_strID;
				pNew->m_strName = pValue->m_strName;
				oDestList.AddTail(pNew);
			}
// 			else if (pData->HasValueHasStr_Child(strTagID, strValue))
// 			{
// 				oDestList.AddTail(pData);
// 			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterDataExHasValueStr(oDestList, strTagID, strValue);
		}
	}
}

void CDvmDatasetGroup::FilterDataExHasNoValueStr(CExBaseList &oDestList, const CString &strTagID, const CString &strValue)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;

			if (pData->HasValueHasNoStr(strTagID, strValue))
			{
				oDestList.AddTail(pData);
				continue;
			}

			CDvmValue *pValue = pData->HasValueHasNoStr_Child(strTagID, strValue);

			if(pValue != NULL)
			{
				CDvmData *pNew = new CDvmData();
				pNew->m_strValue = pValue->m_strValue;
				pNew->m_strDataType = pValue->m_strDataType;
				pNew->m_strID = pValue->m_strID;
				pNew->m_strName = pValue->m_strName;
				oDestList.AddTail(pNew);
			}
// 			else if (pData->HasValueHasStr_Child(strTagID, strValue))
// 			{
// 				oDestList.AddTail(pData);
// 			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterDataExHasNoValueStr(oDestList, strTagID, strValue);
		}
	}
}

void CDvmDatasetGroup::FilterCombineDataEx(CString &strValues, const CString &strTagID, CString &strSeparator)
{
	strSeparator.Trim();

	if (strSeparator.GetLength() == 0)
	{
		strSeparator = _T(";");
	}

	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pData = (CDvmData *)pObj;
			CString strDataValue;

			if (pData->GetValueByID(strTagID, strDataValue))
			{
				strValues.AppendFormat(_T("%s%s"), strDataValue.GetString(), strSeparator.GetString());
				continue;
			}

// 			CDvmValue *pValue = pData->HasValueEx_Child(strTagID, strDataValue);
// 
// 			if(pValue != NULL)
// 			{
// 				strValues.AppendFormat(_T("%s%s"), strDataValue.GetString(), strSeparator.GetString());
// 			}
		}
		else if (nClassID == DVMCLASSID_CDVMDATASETGROUP)
		{
			CDvmDatasetGroup *pDatasetGroup = (CDvmDatasetGroup*)pObj;
			pDatasetGroup->FilterCombineDataEx(strValues, strTagID, strSeparator);
		}
	}
}