//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TmFaultParasEx.cpp  CTmFaultParasEx


#include "stdafx.h"
#include "TmFaultParasEx.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTmFaultParasEx::CTmFaultParasEx()
{
	//初始化属性

	//初始化成员变量
}

CTmFaultParasEx::~CTmFaultParasEx()
{
}

// long CTmFaultParasEx::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CDataGroup::XmlReadOwn(oNode, pXmlRWKeys);
// 	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;
// 
// 	return 0;
// }
// 
// long CTmFaultParasEx::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CDataGroup::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
// 	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;
// 
// 	return 0;
// }
// 
// long CTmFaultParasEx::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	CDataGroup::SerializeOwn(oBinaryBuffer);
// 	if(oBinaryBuffer.IsCalSizeMode())
// 	{
// 	}
// 	else if(oBinaryBuffer.IsReadMode())
// 	{
// 	}
// 	else if(oBinaryBuffer.IsWriteMode())
// 	{
// 	}
// 	return 0;
// }
// 
// void CTmFaultParasEx::InitAfterRead()
// {
// }
// 
// BOOL CTmFaultParasEx::IsEqualOwn(CBaseObject* pObj)
// {
// 	if(this == pObj)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (!CDataGroup::IsEqualOwn(pObj))
// 	{
// 		return FALSE;
// 	}
// 
// 	CTmFaultParasEx *p = (CTmFaultParasEx*)pObj;
// 
// 	return TRUE;
// }
// 
// BOOL CTmFaultParasEx::CopyOwn(CBaseObject* pDest)
// {
// 	if(this == pDest)
// 	{
// 		return TRUE;
// 	}
// 
// 	CDataGroup::CopyOwn(pDest);
// 
// 	CTmFaultParasEx *p = (CTmFaultParasEx*)pDest;
// 
// 	return TRUE;
// }

CBaseObject* CTmFaultParasEx::Clone()
{
	CTmFaultParasEx *p = new CTmFaultParasEx();
	Copy(p);
	return p;
}
// 
// CExBaseObject* CTmFaultParasEx::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
// {
// 	CExBaseObject *pNew  = NULL;
// 	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;
// 
// 
// 
// 	return pNew;
// }
// 
// CExBaseObject* CTmFaultParasEx::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	CExBaseObject *pNew  = NULL;
// 
// 
// 
// 	return pNew;
// }
// 
// void CTmFaultParasEx::OnSetParaValue(CShortData *pData, CExBaseList &listNew, CExBaseList &listDelete)
// {
// 	if (pData->m_strFormat.GetLength() == 0)
// 	{
// 		return;
// 	}
// 
// 	CExBaseList listGroup;
// 	SelectAllGroups(listGroup, pData);
// 	long nCurrCount = listGroup.GetCount();
// 
// 	if (nCurrCount == 0)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("不存在参数类型为【%s】的组"), pData->m_strFormat);
// 		return;
// 	}
// 
// #ifdef _UNICODE
// 	long nNewCount = _wtoi(pData->m_strValue);
// #else
// 	long nNewCount = atol(pData->m_strValue);
// #endif
// 
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
// }
// 
// void CTmFaultParasEx::SelectAllGroups(CExBaseList &listDataGroup, CShortData *pData)
// {
// 	CDataGroup *pGroup = (CDataGroup*)pData->GetParent();
// 
// 	if (pGroup == NULL)
// 	{
// 		return;
// 	}
// 
// 	POS pos = pGroup->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pGroup->GetNext(pos);
// 
// 		if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
// 		{
// 			if ( ((CDataGroup*)p)->m_strDataType == pData->m_strFormat)
// 			{
// 				listDataGroup.AddTail(p);
// 			}
// 		}
// 	}
// }
// 
// void CTmFaultParasEx::ResetParas()
// {
// 	ResetParas(this);
// }
// 
// void CTmFaultParasEx::ResetParas(CDataGroup *pGroup)
// {
// 	POS pos = pGroup->GetHeadPosition();
// 	CExBaseObject *p = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		p = pGroup->GetNext(pos);
// 
// 		if (p->m_dwReserved == 1)
// 		{
// 			Delete(p);
// 		}
// 		else
// 		{
// 			if (p->GetClassID() == DTMCLASSID_CDATAGROUP)
// 			{
// 				ResetParas((CDataGroup*)p);
// 			}
// 		}
// 	}
// }
// 
// 
// BOOL CTmFaultParasEx::SetPara(const CString &strIDPath, const CString &strValue, CExBaseList &listNew, CExBaseList &listDelete)
// {
// 	CShortData *pData = FindDataByIDPath(strIDPath);
// 	
// 	if (pData == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	pData->m_strValue = strValue;
// 	OnSetParaValue(pData, listNew, listDelete);
// 
// 	return TRUE;
// }
// 
// CShortData* CTmFaultParasEx::FindDataByIDPath(const CString &strIDPath)
// {
// 	CExBaseList listData;
// 	CString strTemp;
// 	strTemp = strIDPath;
// 	Select(strTemp, listData, '$');
// 
// 	if (listData.GetCount() == 0)
// 	{
// 		return NULL;
// 	}
// 
// 	CShortData *pData = (CShortData*)listData.GetHead();
// 	listData.RemoveAll();
// 	
// 	return pData;
// }
// 
