//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DataGroup.cpp  CDataGroup


#include "stdafx.h"
#include "DataGroup.h"
#include "DataMngrTrans.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CDataGroup::CDataGroup()
{
	//初始化属性

	//初始化成员变量
}

CDataGroup::~CDataGroup()
{
}

long CDataGroup::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	//20220408  shaolei   只保存id和value
	if (pXmlKeys->m_nXmlOnlyWrite_Id_Value >= 1)
	{
		if (pXmlKeys->m_nXmlOnlyWrite_Id_Value > 0xFFFF)
		{//特殊处理：返回名称 2022-3-18
			xml_GetAttibuteValue(pXmlRWKeys->m_strNameKey, oNode, m_strName);
		}

		xml_GetAttibuteValue(pXmlRWKeys->m_strIDKey, oNode, m_strID);
		xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
		xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

		return 0;
	}

	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeKey, oNode, m_strDataType);
	xml_GetAttibuteValue(pXmlKeys->m_strValueKey, oNode, m_strValue);

	return 0;
}

long CDataGroup::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
    CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

    //2020-11-30  lijunqing
    if (pXmlKeys->m_nXmlOnlyWrite_Id_Value >= 1)
    {
		if (pXmlKeys->m_nXmlOnlyWrite_Id_Value > 0xFFFF)
		{//特殊处理：返回名称 2022-3-18
			xml_SetAttributeValue(pXmlRWKeys->m_strNameKey, oElement, m_strName);
		}

        xml_SetAttributeValue(pXmlRWKeys->m_strIDKey, oElement, m_strID);
        xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
        xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);
        return 0;
    }

	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	xml_SetAttributeValue(pXmlKeys->m_strDataTypeKey, oElement, m_strDataType);
	xml_SetAttributeValue(pXmlKeys->m_strValueKey, oElement, m_strValue);

	return 0;
}

long CDataGroup::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strDataType);
		BinarySerializeCalLen(oBinaryBuffer, m_strValue);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		if (oBinaryBuffer.m_dwVersionFind >= DATAMNGR_VERSION_1_7)
		{
			BinarySerializeRead(oBinaryBuffer, m_strDataType);
			BinarySerializeRead(oBinaryBuffer, m_strValue);
		}
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strDataType);
		BinarySerializeWrite(oBinaryBuffer, m_strValue);
	}
	
	return 0;
}

void CDataGroup::InitAfterRead()
{
}

BOOL CDataGroup::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDataGroup *p = (CDataGroup*)pObj;

	if (CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsEqualOwn_Id_Value >= 1)
	{
		if (p->m_strID != m_strID)
		{
			return FALSE;
		}

		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CDataGroup::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CDataGroup *p = (CDataGroup*)pDest;
	p->m_strDataType = m_strDataType;
	p->m_strValue = m_strValue;

	return TRUE;
}

CBaseObject* CDataGroup::Clone()
{
	CDataGroup *p = new CDataGroup();
	Copy(p);
	return p;
}

CBaseObject* CDataGroup::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CDataGroup *p = new CDataGroup();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CDataGroup::CanPaste(UINT nClassID)
{
	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		return TRUE;
	}

	if (nClassID == DTMCLASSID_CLONGDATAS)
	{
		return TRUE;
	}

	if (nClassID == DTMCLASSID_CSHORTDATAS)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDataGroup::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDataGroupKey)
	{
		pNew = new CDataGroup();
	}
	else if (strClassID == pXmlKeys->m_strCShortDatasKey)
	{
		pNew = new CShortDatas();
	}
	else if (strClassID == pXmlKeys->m_strCDvmDataKey)
	{
		if (pXmlKeys->m_nIsGroupUseDvmData > 0)
		{
			pNew = new CDvmData();
		}
		else
		{
			pNew = new CShortData();
		}
	}

	return pNew;
}

CExBaseObject* CDataGroup::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DTMCLASSID_CDATAGROUP)
	{
		pNew = new CDataGroup();
	}
	else if (nClassID == DTMCLASSID_CSHORTDATAS)
	{
		pNew = new CShortDatas();
	}
	else if (nClassID == DTMCLASSID_CSHORTDATA)
	{
		pNew = new CShortData();
	}
	else if (nClassID == DVMCLASSID_CDVMDATA)
	{
		pNew = new CDvmData();
	}

	return pNew;
}

//shaolei 2022-1-6  330项目，更新参数时，需要将不存在的参数补齐，因此重载
BOOL CDataGroup::UpdateChildren(CBaseObject* pDest)
{
	if (this == pDest)
	{
		return FALSE;
	}

	if (!pDest->IsBaseList())
	{
		return FALSE;
	}

	CDataGroup *pDestList = (CDataGroup*)pDest;
	CExBaseObject *pObj = NULL;
	CExBaseObject *pFind = NULL;
	POS pos = GetHeadPosition();
	CExBaseList listAppend;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		ASSERT(pObj != NULL);
		pFind = (CExBaseObject *)pDestList->FindSame(pObj);

		if (pFind != NULL)
		{
			pObj->Update(pFind);
		}
 		else
 		{
 			listAppend.AddTail(pObj);
 		}
	}

 	pDestList->AppendClone(listAppend);
 	listAppend.RemoveAll();

	return TRUE;
}

void CDataGroup::OnSetParaValue(CShortData *pData, CExBaseList &listNew, CExBaseList &listDelete)
{
	if (pData->m_strFormat.GetLength() == 0)
	{
		return;
	}

// 	CExBaseList listGroup;
// 	SelectAllGroups(listGroup, pData);
// 	long nCurrCount = listGroup.GetCount();
// 
// 	if (nCurrCount == 0)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("不存在参数类型为【%s】的组"), pData->m_strFormat);
// 		return;
// 	}

#ifdef _UNICODE
	long nNewCount = _wtoi(pData->m_strValue);
#else
    long nNewCount = atol(pData->m_strValue.GetString());
#endif

	CDataGroup *pParentGroup = (CDataGroup*)pData->GetParent();
	pParentGroup->SetGroupCount(pData->m_strFormat, nNewCount, listNew, listDelete);

// 	if (nCurrCount == nNewCount)
// 	{
// 		listGroup.RemoveAll();
// 		return;
// 	}
// 
// 	CDataGroup *pParentGroup = (CDataGroup*)pData->GetParent();
// 	long nIndex = 0;
// 	CDataGroup *pTemp = NULL;
// 
// 	if (nCurrCount > nNewCount)
// 	{
// 		for (nIndex=nNewCount; nIndex<nCurrCount; nIndex++)
// 		{
// 			pTemp = (CDataGroup *)listGroup.GetAtIndex(nIndex);
// 			pParentGroup->Remove(pTemp);
// 			listDelete.AddTail(pTemp);
// 		}		
// 	}
// 	else
// 	{
// 		CDataGroup *pHead = (CDataGroup*)listGroup.GetHead();
// 		CString strName = pHead->m_strName.Left(pHead->m_strName.GetLength() - 1);
// 
// 		for (nIndex=nCurrCount; nIndex<nNewCount; nIndex++)
// 		{
// 			pTemp = (CDataGroup*)pHead->Clone();
// 			pParentGroup->AddNewChild(pTemp);
// 			pTemp->m_dwReserved = 1;
// 			listNew.AddTail(pTemp);
// 			listGroup.AddTail(pTemp);
// 			pTemp->m_strName.Format(_T("%s%d"),strName, nIndex+1);
// 			pTemp->m_strID.Format(_T("%s%d"), pHead->m_strDataType, nIndex+1);
// 		}
// 	}
// 
// 	listGroup.RemoveAll();
}

void CDataGroup::SetGroupCount(const CString &strDataType, long nGroupCount, CExBaseList &listNew, CExBaseList &listDelete)
{
	if (nGroupCount == 0)
	{
//#ifdef NOT_USE_XLANGUAGE
//		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("参数类型【%s】组必须有一组"), strDataType);
//#else
//        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_ParaTypeGroup/*_T("参数类型【%s】组必须有一组")*/, strDataType.GetString());
//#endif
		return;
	}

	if (strDataType.GetLength() == 0)
	{
		return;
	}

	CExBaseList listGroup;
	SelectAllGroups(listGroup, strDataType);
	long nCurrCount = listGroup.GetCount();

	if (nCurrCount == 0)
	{
//#ifdef NOT_USE_XLANGUAGE
//		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("不存在参数类型为【%s】的组"), strDataType);
//#else
//        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NoParaTypeGroup /*_T("不存在参数类型为【%s】的组")*/, strDataType.GetString());
//#endif

		return;
	}

	long nNewCount =nGroupCount;

	if (nCurrCount == nNewCount)
	{
		listGroup.RemoveAll();
		return;
	}

	long nIndex = 0;
	CDataGroup *pTemp = NULL;

	if (nCurrCount > nNewCount)
	{
		for (nIndex=nNewCount; nIndex<nCurrCount; nIndex++)
		{
			pTemp = (CDataGroup *)listGroup.GetAtIndex(nIndex);
			Remove(pTemp);
			listDelete.AddTail(pTemp);
		}		
	}
	else
	{
		CDataGroup *pHead = (CDataGroup*)listGroup.GetHead();
		CString strName = pHead->m_strName.Left(pHead->m_strName.GetLength() - 1);

		for (nIndex=nCurrCount; nIndex<nNewCount; nIndex++)
		{
			pTemp = (CDataGroup*)pHead->Clone();
#ifndef exbase_not_use_m_dwReserved
			pTemp->m_dwReserved = 1;
#else
			pTemp->m_dwItemData = 1;
#endif
			pTemp->ResetParas();
			AddNewChild(pTemp);
			listNew.AddTail(pTemp);
			listGroup.AddTail(pTemp);
            pTemp->m_strName.Format(_T("%s%d"),strName.GetString(), nIndex+1);
            pTemp->m_strID.Format(_T("%s%d"), pHead->m_strDataType.GetString(), nIndex+1);
		}
	}

	listGroup.RemoveAll();
}

void CDataGroup::SelectAllGroups(CExBaseList &listDataGroup, CShortData *pData)
{
	if (pData->m_strFormat.GetLength() == 0)
	{
		return;
	}

	CDataGroup *pGroup = (CDataGroup*)pData->GetParent();

	if (pGroup == NULL)
	{
		return;
	}

	pGroup->SelectAllGroups(listDataGroup, pData->m_strFormat);
}

void CDataGroup::SelectAllDatas(CExBaseList &listDatas, BOOL bAddGroup, BOOL bValidID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			if (bAddGroup)
			{
				((CDataGroup*)p)->SelectAllDatas(listDatas, bAddGroup, bValidID);
			}
		}
		else
		{
			if (bValidID)
			{
				if (listDatas.FindByID(p->m_strID) == NULL)
				{
					listDatas.AddTail(p);
				}
			}
			else
			{
				listDatas.AddTail(p);
			}
		}
	}
}

void CDataGroup::SelectAllGroups(CExBaseList &listDataGroup, const CString &strDataType)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			if (strDataType.GetLength() == 0)
			{//2021-5-3  lijunqing  如果传入的参数为空字符串，表示所有的Group
				listDataGroup.AddTail(p);
				continue;
			}

			if ( ((CDataGroup*)p)->m_strDataType == strDataType)
			{
				listDataGroup.AddTail(p);
			}
		}
	}
}

void CDataGroup::ResetParas()
{
	ResetParas(this);
}

void CDataGroup::ResetParas(CDataGroup *pGroup)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pGroup->GetNext(pos);

#ifndef exbase_not_use_m_dwReserved
		if (p->m_dwReserved == 1)
#else
		if (p->m_dwItemData == 1)
#endif
		{
			Delete(p);
		}
		else
		{
			if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
			{
				ResetParas((CDataGroup*)p);
			}
			else if (p->GetClassID() == DTMCLASSID_CSHORTDATA)
			{
				( (CShortData*)p)->ResetData();
			}
			else if (p->GetClassID() == DVMCLASSID_CDVMDATA)
			{
				( (CDvmData*)p)->ResetData();
			}
		}
	}
}

void CDataGroup::ResetDatas(CExBaseList &listDatas)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)p)->ResetDatas(listDatas);
		}
		else
		{
			if (listDatas.Find(p) == NULL)
			{
				( (CShortData*)p)->ResetData();
			}
		}
	}
}

//2021-8-15  lijunqing
void CDataGroup::ResetDatas()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)p)->ResetDatas();
		}
		else if (p->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			( (CShortData*)p)->ResetData();
		}
		else if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			( (CDvmData*)p)->ResetData();
		}
	}
}

BOOL CDataGroup::SetPara(const CString &strIDPath, const CString &strValue, CExBaseList &listNew, CExBaseList &listDelete)
{
	CShortData *pData = FindDataByIDPath(strIDPath);

	if (pData == NULL)
	{
		return FALSE;
	}

	pData->m_strValue = strValue;
	OnSetParaValue(pData, listNew, listDelete);

	return TRUE;
}

CShortData* CDataGroup::FindDataByIDPath(const CString &strIDPath)
{
	CExBaseList listData;
	CString strTemp;
	strTemp = strIDPath;
	Select(strTemp, listData, '$');

	if (listData.GetCount() == 0)
	{
		return NULL;
	}

	CShortData *pData = (CShortData*)listData.GetHead();
	listData.RemoveAll();

	return pData;
}

BOOL CDataGroup::UpdateOwn(CBaseObject* pDest)
{
	if (GetClassID() != pDest->GetClassID())
	{
		return FALSE;
	}

	CDataGroup *pDesGroup = (CDataGroup*)pDest;
	pDesGroup->m_strValue = m_strValue;
	return TRUE;
}

CString CDataGroup::GetXLangID(CExBaseObject *pChildObj)
{
	CString strXLangID;
	GetXLangID(pChildObj, strXLangID);
	return strXLangID;
}

void CDataGroup::GetXLangID(CExBaseObject *pChildObj, CString &strXLangID)
{
	if (m_strDataType.GetLength() > 0)
	{
        strXLangID.Format(_T("#s%s_%s"), m_strDataType.GetString(), pChildObj->m_strID.GetString());
	}
	else
	{
        strXLangID.Format(_T("#s%s_%s"), m_strID.GetString(), pChildObj->m_strID.GetString());
	}
}


CString CDataGroup::GetDataIDPath(CExBaseObject *pPara)
{
	CString strPath;
	GetDataIDPath(strPath, pPara);
	return strPath;
}

void CDataGroup::GetDataIDPath(CString &strPath, CExBaseObject *pPara)
{
	strPath.Empty();
	CExBaseObject *pParent = pPara;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->m_strID.GetLength() == 0)
		{
			break;
		}

        strTemp.Format(_T("%s$"), pParent->m_strID.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();

		if (pParent == NULL)
		{
			break;
		}

		if (pParent->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			break;
		}
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}
}

void CDataGroup::StringSerialize(CStringSerializeBuffer &oBinaryBuffer)
{
	CExBaseObject* p = NULL;
	POS pos = GetHeadPosition();
	CString strValue;
	UINT nClassID = p->GetClassID();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)p)->StringSerialize(oBinaryBuffer);
		}
		else
		{
			if (nClassID == DTMCLASSID_CSHORTDATA)
			{
				CShortData *pData = (CShortData*)p;
				oBinaryBuffer << GetDataIDPath(p);
				oBinaryBuffer << _T("=");
				oBinaryBuffer << pData->m_strValue;
				oBinaryBuffer << _T(";");
			}
		}
	}
}


void CDataGroup::Parser(CEquationBuffer *pEquation)
{
	POS pos = GetHeadPosition();
	CString strValue;
	CExBaseObject *p = NULL;

	CString strPath;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			CShortData *pPara = (CShortData*)p;
			strValue = _T("");
			GetDataIDPath(strPath, pPara);
			pEquation->ParseString(strPath, strValue);

			if(strValue.GetLength() > 0)
			{
				pPara->m_strValue = strValue;
			}
		}
		else if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			CDvmData *pDvmData = (CDvmData*)p;
			strValue = _T("");
			GetDataIDPath(strPath, pDvmData);
			pEquation->ParseString(strPath, strValue);

			if(strValue.GetLength() > 0)
			{
				pDvmData->m_strValue = strValue;
			}
		}
	}

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)p)->Parser(pEquation);
		}
	}
}

CDvmData* CDataGroup::AddNewData(const CString &strName, const CString &strID, const CString &strDataType, const CString &strValue
					 , const CString &strUnit, const CString &strMin, const CString &strMax, const CString &strStep)
{
	CDvmData *pNew = new CDvmData();

	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_strDataType = strDataType;
	pNew->m_strUnit = strUnit;
	pNew->m_strMin = strMin;
	pNew->m_strMax = strMax;
	pNew->m_strStep = strStep;

#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
	wcscpy(pNew->m_strValue, strValue);
#else
	BSTR bstr = strValue.AllocSysString();
	wcscpy(pNew->m_strValue, bstr);
	::SysFreeString(bstr);
#endif
#else
	pNew->m_strValue = strValue;
#endif

	AddNewChild(pNew);

	return pNew;
}

CDvmData* CDataGroup::AddNewData(const CString &strID, const CString &strValue)
{
	return AddNewData(strID, strID, _T("string"), strValue);
}

//2021-9-5 lijunqing 简单新建Data函数
CDvmData* CDataGroup::AddNewData(const CString &strID,float fValue)
{
	CString strValue;
	strValue.Format(_T("%f"), fValue);
	CDvmData *pNew = AddNewData(strID, strValue);
	pNew->m_strDataType = DATAMNGR_DATATYPE_FLOAT;
	return pNew;
}

CDvmData* CDataGroup::AddNewData(const CString &strID,long nValue)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);
	CDvmData *pNew = AddNewData(strID, strValue);
	pNew->m_strDataType = DATAMNGR_DATATYPE_LONG;
	return pNew;
}

CDvmData* CDataGroup::AddNewData(const CString &strID,double fValue)
{
	CString strValue;
	strValue.Format(_T("%f"), fValue);
	CDvmData *pNew = AddNewData(strID, strValue);
	pNew->m_strDataType = DATAMNGR_DATATYPE_DOUBLE;
	return pNew;
}



//2020-10-03
CDataGroup* CDataGroup::FindByDataType(const CString &strDataType)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataGroup *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			if (((CDataGroup*)p)->m_strDataType == strDataType)
			{
				return (CDataGroup*)p;
			}
		}
	}

	return NULL;
}

CDataGroup* CDataGroup::FindByDataType(const CString &strDataType, long nFindIndex)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataGroup *pFind = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			if (((CDataGroup*)p)->m_strDataType == strDataType)
			{
				if (nIndex == nFindIndex)
				{
					return (CDataGroup*)p;
				}
				else
				{
					nIndex++;
				}
			}
		}
	}

	return NULL;
}

long CDataGroup::FindByDataType(const CString &strDataType, CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataGroup *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			if (((CDataGroup*)p)->m_strDataType == strDataType)
			{
				oList.AddTail(p);
			}
		}
	}

	return oList.GetCount();
}

//2020-11-23  add 
long CDataGroup::FindByDataType_Data(const CString &strDataType, CExBaseList &oList)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			if (((CDvmData*)p)->m_strDataType == strDataType)
			{
				oList.AddTail(p);
			}
		}
	}

	return oList.GetCount();
}


CDataGroup* CDataGroup::AddNewGroup(const CString &strName, const CString &strID, const CString &strDataType, BOOL bInitNameAndId)
{
	CDataGroup *pNew = (CDataGroup*)FindByID(strID);

	if (pNew == NULL)
	{
		pNew = new CDataGroup();
	}
	
	pNew->m_strName = strName;
	pNew->m_strID = strID;
	pNew->m_strDataType = strDataType;
	
	AddNewChild(pNew, bInitNameAndId);

	return pNew;
}

//2020-10-13 lijunqing
CDvmData* CDataGroup::FindDataByValue(const CString &strValue)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			if (strValue == ((CDvmData*)p)->m_strValue)
			{
				pFind = (CDvmData*)p;
				break;
			}
		}
	}

	return pFind;
}

void CDataGroup::ShortData_to_DvmData()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	POS posCurr = pos;

	while (pos != NULL)
	{
		posCurr = pos;
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)p)->ShortData_to_DvmData();
		}
		else if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			CShortData *pShortData = (CShortData*)p;
			CDvmData *pNew = new CDvmData();
			Copy_Data(pNew, pShortData);
			pNew->SetParent(this);
			SetAt(posCurr, pNew);
			delete pShortData;
		}
	}
}

// 获取当前节点子节点的数量 - data的数量 mym add 2020-10-8
//2021-5-3  lijunqing 修改名字
long CDataGroup::GetChildCount(const CString &strDataType)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	long nCount = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			if (((CDataGroup*)p)->m_strDataType == strDataType)
			{
				nCount++;
			}
		}
		else if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			if (((CDvmData*)p)->m_strDataType == strDataType)
			{
				nCount++;
			}
		}
	}

	return nCount;
}

long CDataGroup::GetChildCount(UINT nClassID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long  nNodeCnt = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == nClassID)
		{
			nNodeCnt++;
		}
	}

	return nNodeCnt;
}

//2024-3-13 lijunqing
CExBaseObject* CDataGroup::GetChildByIndex(long nIndex, UINT nClassID)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long  nIndexTemp = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);

		if (p->GetClassID() == nClassID)
		{
			if (nIndexTemp == nIndex)
			{
				return p;
			}

			nIndexTemp++;
		}
	}

	return NULL;
}

//2020-10-27  lijunqing
//shaolei 2022-1-18 增加类型判断
BOOL CDataGroup::GetDataValue(const CString &strID, CString &strValue, UINT nClassID)
{
	CExBaseObject *pFind = FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->GetClassID() != nClassID)
	{
		return FALSE;
	}

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		strValue = ((CDvmData*)pFind)->m_strValue;
	}
	else if (nClassID == DTMCLASSID_CSHORTDATA)
	{
		strValue = ((CShortData*)pFind)->m_strValue;
	}

	return TRUE;
}

BOOL CDataGroup::GetDataValue(const CString &strID, long &nValue, UINT nClassID)
{
	CString strVal = _T("");
	BOOL bRet = GetDataValue(strID,strVal, nClassID);
	if (!bRet)
	{
		return FALSE;
	}

	nValue = CString_To_long(strVal);
	return TRUE;
}

BOOL CDataGroup::GetDataValue(const CString &strID, double &dValue, UINT nClassID)
{
	CString strVal = _T("");
	BOOL bRet = GetDataValue(strID,strVal, nClassID);
	if (!bRet)
	{
		return FALSE;
	}

	dValue = CString_To_double(strVal);
	return TRUE;
}

BOOL CDataGroup::GetDataType( const CString &strID, CString &strDataType, UINT nClassID /*= DVMCLASSID_CDVMDATA*/ )
{
	CExBaseObject *pFind = FindByID(strID);

	if (pFind == NULL)
	{
		return FALSE;
	}

	if (pFind->GetClassID() != nClassID)
	{
		return FALSE;
	}

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		strDataType = ((CDvmData*)pFind)->m_strDataType;
	}
	else if (nClassID == DTMCLASSID_CSHORTDATA)
	{
		strDataType = ((CShortData*)pFind)->m_strDataTypeID;
	}

	return TRUE;
}

//2021-8-2  lijunqing
void CDataGroup::SetDataValue(const CString &strID, const CString &strValue, BOOL bAddNewNotExist, UINT nClassID)
{
	CExBaseObject *pFind = FindByID(strID);

	if (pFind == NULL)
	{
		if(bAddNewNotExist)
		{
			if (nClassID == DVMCLASSID_CDVMDATA)
			{
				pFind = new CDvmData();
			}
			else if (nClassID == DTMCLASSID_CSHORTDATA)
			{
				pFind = new CShortData();
			}
			
			AddNewChild(pFind);
			pFind->m_strID = strID;
			pFind->m_strName = strID;
		}
		else
		{
			return;
		}
	}

	if (pFind->GetClassID() != nClassID)
	{
		return;
	}

	if (nClassID == DVMCLASSID_CDVMDATA)
	{
		((CDvmData*)pFind)->m_strValue = strValue;
	}
	else if (nClassID == DTMCLASSID_CSHORTDATA)
	{
		((CShortData*)pFind)->m_strValue = strValue;
	}
}

void CDataGroup::SetDataValue(const CString &strID, long nValue, BOOL bAddNewNotExist, UINT nClassID)
{
	CString strValue;
	strValue.Format(_T("%d"), nValue);

	SetDataValue(strID, strValue, bAddNewNotExist, nClassID);
// 	CExBaseObject *pFind = FindByID(strID);
// 
// 	if (pFind == NULL)
// 	{
// 		if(bAddNewNotExist)
// 		{
// 			pFind = new CDvmData();
// 			AddNewChild(pFind);
// 			pFind->m_strID = strID;
// 			pFind->m_strName = strID;
// 		}
// 		else
// 		{
// 		return;
// 	}
// 	}
// 
// 	if (pFind->GetClassID() != DVMCLASSID_CDVMDATA)
// 	{
// 		return;
// 	}
// 
// 	((CDvmData*)pFind)->m_strValue.Format(_T("%d"), nValue);
}

void CDataGroup::SetDataValue(const CString &strID, double dValue, BOOL bAddNewNotExist, UINT nClassID)
{
	CString strValue;
	strValue.Format(_T("%lf"), dValue);

	SetDataValue(strID, strValue, bAddNewNotExist, nClassID);
}

void CDataGroup::InitNameByID(const CString &strName,const CString &strID)
{
	CExBaseObject *pCurrObj = FindByID(strID);

	if (pCurrObj != NULL)
	{
		pCurrObj->m_strName = strName;
	}
}

//2022-8-11 lijunqing 根据查询的条件对象，判断当前数据对象是否包含数据，默认使用CDvmData
BOOL CDataGroup::Match(CDataGroup *pQuery)
{
	POS pos = pQuery->GetHeadPosition();
	CDvmData *p = NULL;
	CDvmData *pFind = NULL;

	while (pos != NULL)
	{
		p = (CDvmData *)pQuery->GetNext(pos);
		pFind = (CDvmData *)FindByID(p->m_strID);

		if (pFind == NULL)
		{
			return FALSE;
		}

		if (pFind->GetClassID() == DVMCLASSID_CDVMDATA && p->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			if (p->m_strValue != pFind->m_strValue)
			{
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}

	return TRUE;
}


void CDataGroup::InitDataValues(CDataGroup *pSrc, BOOL bCloneWhenNotFind)
{
	if (pSrc == NULL)
	{
		return;
	}

    m_strValue = pSrc->m_strValue;

	POS pos = pSrc->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = /*(CExBaseObject *)*/pSrc->GetNext(pos);
		pFind = /*(CExBaseObject *)pSrc->*/FindByID(p->m_strID);
		nClassID = p->GetClassID();

		if (pFind == NULL)
		{
			if (bCloneWhenNotFind)
			{
				//AddTail((CExBaseObject*)pFind->Clone());
				AddNewChild((CExBaseObject*)p->Clone());
			}

			continue;
		}
		
		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)pFind)->InitDataValues((CDataGroup*)p, bCloneWhenNotFind);
		}
		else if (nClassID == DVMCLASSID_CDVMDATA)
		{
			((CDvmData*)pFind)->m_strValue = ((CDvmData*)p)->m_strValue;
		}
		else if (nClassID == DTMCLASSID_CSHORTDATA)
		{
			((CShortData*)pFind)->m_strValue = ((CShortData*)p)->m_strValue;
		}
	}
}

//只添加this中不包含的新的项
void CDataGroup::AddDataValuesNotExist(CDataGroup *pSrc)
{
	if (pSrc == NULL)
	{
		return;
	}

	POS pos = pSrc->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pSrc->GetNext(pos);
		pFind = FindByID(p->m_strID);
		nClassID = p->GetClassID();

		if (pFind == NULL)
		{
			AddNewChild((CExBaseObject*)p->Clone());
		}

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)pFind)->AddDataValuesNotExist((CDataGroup*)p);
		}
	}
}

BOOL CDataGroup::SetDvmDataXml(const CString &strXml)
{
	BSTR bstrText = strXml.AllocSysString();
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData++;
	BOOL bRet = SetXml(bstrText, CDataMngrXmlRWKeys::g_pXmlKeys);
	CDataMngrXmlRWKeys::g_pXmlKeys->m_nIsGroupUseDvmData--;
#ifdef _PSX_IDE_QT_
    delete bstrText;
#else
	SysFreeString(bstrText);// 用完释放
#endif

	return bRet;
}

//shaolei  2023-4-3 查找ID包含的数据。默认不递归
long CDataGroup::SelectDatas_IDHas(const CString &strIDHas, CExBaseList &oListDatas, BOOL bRecursive)
{
	POS pos = GetHeadPosition();
	UINT nClassID = 0;
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		nClassID = pObj->GetClassID();

		if (nClassID == DTMCLASSID_CDATAGROUP)
		{
			if (bRecursive)
			{
				CDataGroup *pChildGrp = (CDataGroup *)pObj;
				pChildGrp->SelectDatas_IDHas(strIDHas, oListDatas, bRecursive);
			}
			
			continue;
		}
		
		//除了嵌套的group子对象，剩余子对象不判断对象类型
		if (pObj->m_strID.Find(strIDHas) >= 0)
		{
			oListDatas.AddTail(pObj);
		}
	}

	return oListDatas.GetCount();
}


void  CDataGroup::AppendValues( CValues *pValues)
{
	CExBaseObject *pData = NULL;
	POS pos = GetHeadPosition();
	CValue *pValue = NULL;

	while (pos != NULL)
	{
		pData = GetNext(pos);

		if (pData->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			pValues->AddValue(pData->m_strID, ((CShortData*)pData)->m_strValue);
		}
		else if (pData->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			pValues->AddValue(pData->m_strID, ((CDvmData*)pData)->m_strValue);
		}
	}
}


//2024-3-10  lijunqing  基于自动测试Safety扩展数据分类，增加AddNew2兼容CShortDatas

CValues* CDataGroup::GetValues()
{
	CValues *pValues = new CValues();
	GetValues(pValues);
	return pValues;
}

CDataGroup* datagroup_GetRootGroup(CDataGroup *pDataGroup)
{
	CExBaseObject *pParent = (CExBaseObject*)pDataGroup->GetParent();

	if (pParent == NULL)
	{
		return pDataGroup;
	}

	if (pParent->GetClassID() != DTMCLASSID_CDATAGROUP)
	{
		return pDataGroup;
	}

	if (pParent->m_strID.GetLength() == 0)
	{
		return (CDataGroup*)pParent;
	}

	return datagroup_GetRootGroup((CDataGroup*)pParent);
}

void datagroup_AddToValues(CDataGroup *pDataGroup, CShortData *pData, CValues *pValues)
{
	CDataGroup *pRoot = datagroup_GetRootGroup(pDataGroup);
	CString strNamePath, strIDPath;
	CDataGroup *p = pDataGroup;

	while (p != pRoot)
	{
		strNamePath = p->m_strName + _T("$") + strNamePath;
		strIDPath = p->m_strID + _T("$") + strIDPath;
		p = (CDataGroup *)p->GetParent();
	}

	strNamePath += pData->m_strName;
	strIDPath += pData->m_strID;
	pValues->AddNew(strIDPath, strNamePath, pData->m_strValue);
}

void CDataGroup::GetValues(CValues *pValues)
{
	POS pos = GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData *)GetNext(pos);

		if (pData->GetClassID() == DTMCLASSID_CDATAGROUP)
		{
			((CDataGroup*)pData)->GetValues(pValues);
		}
		else
		{
			datagroup_AddToValues(this, pData, pValues);
		}
	}
}

CShortData* CDataGroup::AddNew2(const CString &strName,const CString &strID, const CString &strUnit, const CString &strDataTypeID
								 , const CString &strValue, LONG nReserved,const CString &strFormat,const CString &strRemark, BOOL bAddSame)
{
	CShortData *pData = NULL;

	if (bAddSame)
	{
		pData = new CShortData();
		AddNewChild(pData);
	}
	else
	{
		pData = (CShortData *)FindByID(strID);

		if (pData == NULL)
		{
			pData = new CShortData();
			AddNewChild(pData);
		}
	}

	pData->m_strName = strName;
	pData->m_strID = strID;
	pData->m_strUnit = strUnit;
	pData->m_strDataTypeID = strDataTypeID;
	pData->m_strValue = strValue;
	pData->m_strFormat = strFormat;
	pData->m_strRemark = strRemark;
	pData->m_nReserved = nReserved;
	return pData;
}


//lijunqing 2024-3-20
CString CDataGroup::GetAttrValue(const CString &strValueID)
{
	CString strValue = _T("");

	if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strNameKey)
	{
		strValue = m_strName;
	}
	else if (strValueID == CDataMngrXmlRWKeys::g_pXmlKeys->m_strIDKey)
	{
		strValue = m_strID;
	}
	else if (strValueID == CDataMngrXmlRWKeys::ValueKey())
	{
		strValue = m_strValue;
	}
	else if (strValueID == CDataMngrXmlRWKeys::DataTypeKey())
	{
		strValue = m_strDataType;
	}

	return strValue;
}

//////////////////////////////////////////////////////////////////////////
//2021-5-5  lijunqing 
CDataGroup* dvm_FindDataGroupByValue(CExBaseList &listGroup, const CString &strValue)
{
	POS pos = listGroup.GetHeadPosition();
	CExBaseObject *p = NULL;
	CDataGroup *pFind = NULL;

	while (pos != NULL)
	{
		p = listGroup.GetNext(pos);

		if (p->GetClassID() != DTMCLASSID_CDATAGROUP)
		{
			continue;
		}

		if ( ((CDataGroup*)p)->m_strValue == strValue)
		{
			pFind = (CDataGroup *)p;
			break;
		}
	}

	return pFind;
}

//2022-4-13  lijunqing 从SttParas移动到此处，更加方便使用

//////////////////////////////////////////////////////////////////////////
//
BOOL stt_GetDataValueByID(CExBaseList *pList, const char* strValueID, CString &strValue)
{
	CString strTemp;
	strTemp = strValueID;

	return stt_GetDataValueByID(pList, strTemp, strValue);
}

BOOL stt_GetDataValueByID(CExBaseList *pList, const char* strValueID, long &nValue)
{
	CString strTemp;
	strTemp = strValueID;

	return stt_GetDataValueByID(pList, strTemp, nValue);
}

long stt_GetDataValueByID2(CExBaseList *pList, const char* strValueID, long nDefaultValue)
{
	CString strTemp;
	strTemp = strValueID;

	return stt_GetDataValueByID2(pList, strTemp, nDefaultValue);
}

BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, CString &strValue)
{
	CExBaseObject *pData = pList->FindByID(strValueID);

	//2021-9-1  lijunqing
	//pList的子对象可能是CShortData， 有可能是CDvmData
	if (pData != NULL)
	{
		if (pData->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			strValue = ((CShortData*)pData)->m_strValue;
			return TRUE;
		}
		if (pData->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			strValue = ((CDvmData*)pData)->m_strValue;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, long &nValue)
{
	CString strValue;

	BOOL bRet = stt_GetDataValueByID(pList, strValueID, strValue);

	if (bRet)
	{
		nValue = CString_HEX_to_UINT(strValue);
	}

	return bRet;
}

long stt_GetDataValueByID2(CExBaseList *pList, const CString &strValueID, long nDefaultValue)
{
	ASSERT(pList != NULL);
	long nValue = nDefaultValue;

	if (pList != NULL)
	{
		stt_GetDataValueByID(pList, strValueID, nValue);
	}

	return nValue;
}

BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, double &dValue)
{
	CString strValue;

	BOOL bRet = stt_GetDataValueByID(pList, strValueID, strValue);

	if (bRet)
	{
		dValue = CString_To_double(strValue);
	}

	return bRet;
}

BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, float &fValue)
{
	CString strValue;

	BOOL bRet = stt_GetDataValueByID(pList, strValueID, strValue);

	if (bRet)
	{
		fValue = CString_To_double(strValue);
	}

	return bRet;
}

//2021-9-1  lijunqing
BOOL stt_GetDataValueByID(CExBaseList *pList, const CString &strValueID, short &nValue)
{
	CString strValue;

	BOOL bRet = stt_GetDataValueByID(pList, strValueID, strValue);

	if (bRet)
	{
		nValue = CString_To_long(strValue);
	}

	return bRet;
}

long stt_SetDataValueByID(CExBaseList *pList, const CString &strValueID, const CString &strValue)
{
	CDvmData *pData = (CDvmData *)pList->FindByID(strValueID);

	if (pData != NULL)
	{
		pData->m_strValue = strValue;
		return TRUE;
	}

	pData = new CDvmData();
	pData->m_strValue = strValue;
	pData->m_strID = strValueID;
	pList->AddNewChild(pData);

	return TRUE;
}

//2022-9-12  lijunqing
void dvm_SetDvmX_Value(CExBaseObject *pData, long nValue)
{
	switch (pData->GetClassID())
	{
	case DTMCLASSID_CDATAGROUP:
		((CDataGroup*)pData)->m_strValue.Format(_T("%d"), nValue);
		break;

	case DVMCLASSID_CDVMDATA:
		((CDvmData*)pData)->m_strValue.Format(_T("%d"), nValue);
		break;

	case DVMCLASSID_CDVMVALUE:
		((CDvmValue*)pData)->m_strValue.Format(_T("%d"), nValue);
		break;

	case DTMCLASSID_CSHORTDATA:
		((CShortData*)pData)->m_strValue.Format(_T("%d"), nValue);
		break;
	}
}

void dvm_SetDvmX_Value(CExBaseObject *pData, const CString &strValue)
{
	switch (pData->GetClassID())
	{
	case DTMCLASSID_CDATAGROUP:
		((CDataGroup*)pData)->m_strValue = strValue;
		break;

	case DVMCLASSID_CDVMDATA:
		((CDvmData*)pData)->m_strValue = strValue;
		break;

	case DVMCLASSID_CDVMVALUE:
		((CDvmValue*)pData)->m_strValue = strValue;
		break;

	case DTMCLASSID_CSHORTDATA:
		((CShortData*)pData)->m_strValue = strValue;
		break;
	}
}

void dvm_GetDvmX_Value(CExBaseObject *pData, long &nValue)
{
	switch (pData->GetClassID())
	{
	case DTMCLASSID_CDATAGROUP:
		nValue = CString_To_long( ((CDataGroup*)pData)->m_strValue);
		break;

	case DVMCLASSID_CDVMDATA:
		nValue = CString_To_long( ((CDvmData*)pData)->m_strValue);
		break;

	case DVMCLASSID_CDVMVALUE:
		nValue = CString_To_long( ((CDvmValue*)pData)->m_strValue);
		break;

	case DTMCLASSID_CSHORTDATA:
		nValue = CString_To_long( ((CShortData*)pData)->m_strValue);
		break;
	}
}

void dvm_GetDvmX_Value(CExBaseObject *pData, CString &strValue)
{
	switch (pData->GetClassID())
	{
	case DTMCLASSID_CDATAGROUP:
		strValue = ((CDataGroup*)pData)->m_strValue;
		break;

	case DVMCLASSID_CDVMDATA:
		strValue= ((CDvmData*)pData)->m_strValue;
		break;

	case DVMCLASSID_CDVMVALUE:
		strValue= ((CDvmValue*)pData)->m_strValue;
		break;

	case DTMCLASSID_CSHORTDATA:
		strValue= ((CShortData*)pData)->m_strValue;
		break;
	}
}

long dvm_GetDvmX_Value_long(CExBaseObject *pData)
{
	long nValue = 0;
	dvm_GetDvmX_Value(pData, nValue);
	return nValue;
}

CString dvm_GetDvmX_Value_string(CExBaseObject *pData)
{
	switch (pData->GetClassID())
	{
	case DTMCLASSID_CDATAGROUP:
		return  ((CDataGroup*)pData)->m_strValue;
		break;

	case DVMCLASSID_CDVMDATA:
		return ((CDvmData*)pData)->m_strValue;
		break;

	case DVMCLASSID_CDVMVALUE:
		return ((CDvmValue*)pData)->m_strValue;
		break;

	case DTMCLASSID_CSHORTDATA:
		return ((CShortData*)pData)->m_strValue;
		break;
	}

	return _T("");
}
