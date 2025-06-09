//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacro.cpp  CTestMacro


#include "stdafx.h"
#include "TestMacro.h"
#include "TmFaultParasEx.h"

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguage/XLanguageResource.h"
#endif

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern long g_nResetDatas;

CTestMacro::CTestMacro()
{
	//初始化属性

	//初始化成员变量
	m_pFaultParas = NULL;
	m_pSysParas = NULL;
	m_pResults = NULL;
	m_pFaultParasEx = NULL;
	m_pResultsEx = NULL;
	m_pSearchResults = NULL;

	m_pFaultParas_Dvm = NULL;
	m_pResults_Dvm = NULL;
}

CTestMacro::~CTestMacro()
{
	FreeParasGroup(&m_listFaultParasGroup);
	FreeParasGroup(&m_listSysParasGroup);
	m_list_FaultParasEx.RemoveAll();
	m_list_ResultParasEx.RemoveAll();

	if (m_pFaultParas_Dvm != NULL)
	{
		delete m_pFaultParas_Dvm;
		delete m_pResults_Dvm;
	}
}

long CTestMacro::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_strVersion);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_strType);
	xml_GetAttibuteValue(pXmlKeys->m_strRemarkKey, oNode, m_strRemark);
	return 0;
}

long CTestMacro::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_strVersion);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_strType);
	xml_SetAttributeValue(pXmlKeys->m_strRemarkKey, oElement, m_strRemark);
	return 0;
}

long CTestMacro::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strVersion);
		BinarySerializeCalLen(oBinaryBuffer, m_strType);
		BinarySerializeCalLen(oBinaryBuffer, m_strRemark);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strVersion);
		BinarySerializeRead(oBinaryBuffer, m_strType);
		BinarySerializeRead(oBinaryBuffer, m_strRemark);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strVersion);
		BinarySerializeWrite(oBinaryBuffer, m_strType);
		BinarySerializeWrite(oBinaryBuffer, m_strRemark);
	}
	return 0;
}

void CTestMacro::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == TMCLASSID_CTMFAULTPARAS)
		{
			m_pFaultParas = (CTmFaultParas*)p;
		}
		else if (nClassID == TMCLASSID_CTMSYSPARAS)
		{
			m_pSysParas = (CTmSysParas*)p;
		}
		else if (nClassID == TMCLASSID_CTMRESULTPARAS)
		{
			m_pResults = (CTmResultParas*)p;
		}
		else if (nClassID == TMCLASSID_CTMSEARCHRESULTPARAS)
		{
			m_pSearchResults = (CTmSearchResultParas*)p;
		}
		else if (nClassID == TMCLASSID_CTMFAULTPARASEX)
		{
			m_pFaultParasEx = (CTmFaultParasEx*)p;
		}
		else if (nClassID == TMCLASSID_CTMRESULTPARASEX)
		{
			m_pResultsEx = (CTmResultParasEx*)p;
		}
	}

	if (m_pFaultParas == NULL)
	{
		m_pFaultParas = (CTmFaultParas*)AddNewChild(new CTmFaultParas());
	}
	else
	{
		//充电桩项目中，解析状态序列文件时，不需要进行参数重置，因此增加一个全局变量，进行兼容
		//shaolei 2022-1-12
		if (g_nResetDatas == 1)
		{
			m_pFaultParas->ResetDatas();
		}
	}

	if (m_pSysParas == NULL)
	{
		m_pSysParas = (CTmSysParas*)AddNewChild(new CTmSysParas());
	}
	else
	{
		if (g_nResetDatas == 1)
		{
			m_pSysParas->ResetDatas();
		}
	}

	if (m_pResults == NULL)
	{
		m_pResults = (CTmResultParas*)AddNewChild(new CTmResultParas());
	}

	if (m_pFaultParasEx != NULL)
	{
		if (g_nResetDatas == 1)
		{
			m_pFaultParasEx->ResetParas();
		}
	}

	//shaolei 2023-1-6
	InitFaultParasEx();
	InitResultParasEx();
}

BOOL CTestMacro::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTestMacro *p = (CTestMacro*)pObj;

	if(m_strVersion != p->m_strVersion)
	{
		return FALSE;
	}

	if(m_strType != p->m_strType)
	{
		return FALSE;
	}

	if(m_strRemark != p->m_strRemark)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTestMacro::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTestMacro *p = (CTestMacro*)pDest;

	p->m_strVersion = m_strVersion;
	p->m_strType = m_strType;
	p->m_strRemark = m_strRemark;
	return TRUE;
}

CBaseObject* CTestMacro::Clone()
{
	CTestMacro *p = new CTestMacro();
	Copy(p);
	return p;
}

//shaolei  20210708
CBaseObject* CTestMacro::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTestMacro *p = new CTestMacro();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

long CTestMacro::InitListCtrlColumns(CListCtrl *pListCtrl)
{
#ifdef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(0, _T("编号"));
#else
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
#endif

	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("Version"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("Type"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("Remark"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTestMacro::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strVersion);
	pListCtrl->SetItemText(lItemIndex, 4, m_strType);
	pListCtrl->SetItemText(lItemIndex, 5, m_strRemark);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

CExBaseObject* CTestMacro::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTmFaultParasKey)
	{
		pNew = new CTmFaultParas();
	}
	else if (strClassID == pXmlKeys->m_strCTmSysParasKey)
	{
		pNew = new CTmSysParas();
	}
	else if (strClassID == pXmlKeys->m_strCTmResultParasKey)
	{
		pNew = new CTmResultParas();
	}
	else if (strClassID == pXmlKeys->m_strCTmSearchResultParasKey)
	{
		pNew = new CTmSearchResultParas();
	}
	else if (strClassID == pXmlKeys->m_strCTmFaultParasExKey)
	{
		pNew = new CTmFaultParasEx();
	}
	else if (strClassID == pXmlKeys->m_strCTmResultParasExKey)
	{
		pNew = new CTmResultParasEx();
	}

	return pNew;
}

CExBaseObject* CTestMacro::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TMCLASSID_CTMFAULTPARAS)
	{
		pNew = new CTmFaultParas();
	}
	else if (nClassID == TMCLASSID_CTMSYSPARAS)
	{
		pNew = new CTmSysParas();
	}
	else if (nClassID == TMCLASSID_CTMRESULTPARAS)
	{
		pNew = new CTmResultParas();
	}
	else if (nClassID == TMCLASSID_CTMFAULTPARASEX)
	{
		pNew = new CTmFaultParasEx();
	}
	else if (nClassID == TMCLASSID_CTMRESULTPARASEX)
	{
		pNew = new CTmResultParasEx();
	}

	return pNew;
}


void CTestMacro::OnSetParaValue(CShortData *pData, CExBaseList &listNew, CExBaseList &listDelete)
{
	if (m_pFaultParasEx == NULL)
	{
		return;
	}

	if (pData->GetAncestor(TMCLASSID_CTMFAULTPARASEX) == NULL)
	{
		return;
	}

	if (pData->m_strFormat.GetLength() == 0)
	{
		return;
	}

	m_pFaultParasEx->OnSetParaValue(pData, listNew, listDelete);
	
	if (m_pResultsEx == NULL)
	{
		return;
	}

	CExBaseList listGroup;
	m_pResultsEx->SelectAllGroups(listGroup, pData->m_strFormat);

	if (listGroup.GetCount() == 0)
	{
		return;
	}

	CExBaseList list1, list2;
	listGroup.RemoveAll();

#ifdef _UNICODE
	long nNewCount = _wtoi(pData->m_strValue);
#else
    long nNewCount = atol(pData->m_strValue.GetString());
#endif

	m_pResultsEx->SetGroupCount(pData->m_strFormat, nNewCount, list1, list2);
	
	list2.DeleteAll();
	list1.RemoveAll();
}

void CTestMacro::OnSetParaValue(const CString &sttrIDPath, const CString &strValue, CExBaseList &listNew, CExBaseList &listDelete, CExBaseList &listChanged)
{
	if (m_pFaultParasEx == NULL)
	{
		return;
	}

	CExBaseObject *pFind = m_pFaultParasEx->FindDataByIDPath(sttrIDPath);

	if (pFind == NULL)
	{
		return;
	}

	if (pFind->GetClassID() != DTMCLASSID_CSHORTDATA)
	{
		return;
	}

	CShortData *pData = (CShortData*)pFind;

	listChanged.AddTail(pData);
	pData->m_strValue = strValue;
	OnSetParaValue(pData, listNew, listDelete);
}

void CTestMacro::InitParasGroup()
{
	if (m_listFaultParasGroup.GetCount() > 0 || m_listSysParasGroup.GetCount() > 0)
	{
		return;
	}

	POS posFirst = NULL;
	AddParasToGroup(m_pFaultParas, &m_listFaultParasGroup, posFirst);

	posFirst = NULL;
	AddParasToGroup(m_pSysParas, &m_listSysParasGroup, posFirst);
}

void CTestMacro::ResetDatas(CExBaseList &listDatas)
{
	if (m_pFaultParasEx == NULL)
	{
		return;
	}

	m_pFaultParasEx->ResetDatas(listDatas);
}

void CTestMacro::ResetDatas()
{
	if (m_pFaultParas_Dvm == NULL)
	{
		return;
	}

	m_pFaultParas_Dvm->ResetDatas();
	m_pResults_Dvm->ResetDatas();
}

CShortData* CTestMacro::FindDataByID(const CString &strID)
{
	CShortData *pData = NULL;

	pData = (CShortData*)m_pFaultParas->FindByID(strID);

	if (pData != NULL)
	{
		return pData;
	}

	pData = (CShortData*)m_pSysParas->FindByID(strID);

	if (pData != NULL)
	{
		return pData;
	}

	pData = (CShortData*)m_pResults->FindByID(strID);

	if (pData != NULL)
	{
		return pData;
	}

	if (m_pFaultParasEx != NULL)
	{
		pData = (CShortData*)m_pFaultParasEx->FindDataByIDPath(strID);

		if (pData != NULL)
		{
			return pData;
		}
	}

	if (m_pResultsEx != NULL)
	{
		pData = (CShortData*)m_pResultsEx->FindDataByIDPath(strID);

		if (pData != NULL)
		{
			return pData;
		}
	}

	return NULL;
}

CShortDatas* CTestMacro::FindGroupByID(CExBaseList *pListGroup, const CString &strID)
{
	CShortDatas *pFind = NULL;
	POS pos = pListGroup->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pListGroup->GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CSHORTDATAS)
		{
			if (p->m_strID == strID)
			{
				pFind = (CShortDatas*)p;
				break;
			}
		}
	}

	return pFind;
}

CShortDatas* CTestMacro::AddGroupByID(CExBaseList *pListGroup, const CString &strID, POS &posFirst)
{
	CShortDatas *p = NULL;
	CShortDatas *pFind = FindGroupByID(pListGroup, strID);

	if (pFind == NULL)
	{
		pFind = new CShortDatas();
		pFind->m_strID = strID;
		pFind->m_strName = strID;
		pListGroup->AddTail(pFind);

		if (posFirst == NULL)
		{
			posFirst = pListGroup->GetTailPosition();
		}
	}

	return pFind;
}

void CTestMacro::AddParaToGroup(CShortData *pData, CExBaseList *pListGroup, POS &posFirst)
{
	if (pData->m_strRemark.GetLength() <= 0)
	{
// 		if (posFirst != NULL)
// 		{
// 			pListGroup->InsertBefore(posFirst, pData);
// 		}
// 		else
		{
			pListGroup->AddTail(pData);
		}
	}
	else
	{
		CShortDatas *pGroup = AddGroupByID(pListGroup, pData->m_strRemark, posFirst);
		pGroup->AddTail(pData);
	}
}

void CTestMacro::AddParasToGroup(CShortDatas *pDatas, CExBaseList *pListGroup, POS &posFirst)
{
	POS pos = pDatas->GetHeadPosition();
	CShortData *pData = NULL;

	while (pos != NULL)
	{
		pData = (CShortData*)pDatas->GetNext(pos);
		AddParaToGroup(pData, pListGroup, posFirst);
	}
}

void CTestMacro::FreeParasGroup(CExBaseList *pListGroup)
{
	CShortDatas *pFind = NULL;
	POS pos = pListGroup->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pListGroup->GetNext(pos);

		if (p->GetClassID() == DTMCLASSID_CSHORTDATAS)
		{
			( (CShortDatas*)p)->RemoveAll();
			delete p;
		}
	}

	pListGroup->RemoveAll();
}

void CTestMacro::GetParasValues(CValues *pValues)
{
	AppendValues(m_pFaultParas, pValues);
	AppendValues(m_pSysParas, pValues);
	AppendValues(m_pFaultParasEx, pValues);
}

void CTestMacro::AppendValues(CExBaseList *pList, CValues *pValues)
{
	if (pList == NULL)
	{
		return;
	}

	CShortData *pData = NULL;
	POS pos = pList->GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CShortData*)pList->GetNext(pos);

		if (pData->GetClassID() == DTMCLASSID_CSHORTDATA)
		{
			pValues->AddValue(pData->m_strID, pData->m_strValue);
		}
	}
}

void CTestMacro::GetTestMacroParas(CDataGroup *pParas, CDataGroup *pResults)
{
	InitParas_Dvm();
	
	pParas->AppendClone(m_pFaultParas_Dvm);
	pResults->AppendClone(m_pResults_Dvm);
}

void CTestMacro::GetTestMacroParas_Fault(CDataGroup *pParas)
{
	InitParas_Dvm();

	pParas->AppendClone(m_pFaultParas_Dvm);
}

void CTestMacro::GetTestMacroParas_Fault_CloneEx(CDataGroup *pParas)
{
	if (m_pFaultParas != NULL)
	{
		pParas->AppendCloneEx(*m_pFaultParas);
	}

	if (m_pFaultParasEx != NULL)
	{
		pParas->AppendCloneEx(*m_pFaultParasEx);
	}

	if (m_pSysParas != NULL)
	{
		pParas->AppendCloneEx(*m_pSysParas);
	}

	pParas->ShortData_to_DvmData();

}

void CTestMacro::GetTestMacroParas_Result_CloneEx(CDataGroup *pResults)
{
	if (m_pResults != NULL)
	{
		pResults->AppendCloneEx(*m_pResults);
	}

	if (m_pResultsEx != NULL)
	{
		pResults->AppendCloneEx(*m_pResultsEx);
	}

	pResults->ShortData_to_DvmData();
}

//以下四个函数，分别将扩展故障参数和扩展结果参数，整理成一个链表
void CTestMacro::InitFaultParasEx()
{
	if (m_pFaultParasEx == NULL)
	{
		return;
	}

	m_pFaultParasEx->SelectAllDatas(m_list_FaultParasEx);//这个链表中的参数暂时不带路径信息
}

void CTestMacro::InitResultParasEx()
{
	if (m_pResultsEx == NULL)
	{
		return;
	}

	m_pResultsEx->SelectAllDatas(m_list_ResultParasEx);//这个链表中的参数暂时不带路径信息
}

//以下两个函数，重新整理参数，使参数的ID，重新赋值为参数路径
//增加形参nStateCount。对状态序列进行特殊处理。删除多余状态的参数
void CTestMacro::InitFaultParasEx(CExBaseList &oList, long nStateCount)
{
	POS pos = m_list_FaultParasEx.GetHeadPosition();

	while (pos != NULL)
	{
		CShortData *pData = (CShortData *)m_list_FaultParasEx.GetNext(pos);
		CValue *pNew = new CValue();//(CShortData *)pData->Clone();
		pNew->m_strID = GetParaIDPath(pData);
		pNew->m_strValue = pData->m_strValue;

		if (nStateCount != -1)
		{
			long nStateNum = GetStateNum(pNew->m_strID);

			if (nStateNum > nStateCount)
			{
				delete pNew;
				return;  //按照顺序，后续所有的参数都是超过当前状态数的，因此直接return。
			}
		}

		oList.AddNewChild(pNew);
	}
}

//增加形参nStateCount。对状态序列进行特殊处理。删除多余状态的参数
void CTestMacro::InitResultParasEx(CExBaseList &oList, long nStateCount)
{
	POS pos = m_list_ResultParasEx.GetHeadPosition();

	while (pos != NULL)
	{
		CShortData *pData = (CShortData *)m_list_ResultParasEx.GetNext(pos);
		CValue *pNew = new CValue();//(CShortData *)pData->Clone();
		pNew->m_strID = GetParaIDPath(pData);
		pNew->m_strValue = pData->m_strValue;

		if (nStateCount != -1)
		{
			long nStateNum = GetStateNum(pNew->m_strID);

			if (nStateNum > nStateCount)
			{
				delete pNew;
				return;  //按照顺序，后续所有的参数都是超过当前状态数的，因此直接return。
			}
		}

		oList.AddNewChild(pNew);
	}
}

long CTestMacro::GetStateNum(const CString &strDataID)
{
	//举例：strDataID = state0$EndMode
	long nPos = strDataID.Find(_T("state"));
	CString strID;

	if (nPos < 0)
	{
		return -1;
	}

	strID = strDataID.Mid(nPos + 5);
	nPos = strID.Find(_T("$"));

	if (nPos < 0)
	{
		return CString_To_long(strID) + 1;
	}

	strID = strID.Left(nPos);
	return CString_To_long(strID) + 1;
}

void CTestMacro::GetParaIDPath(CString &strPath, CShortData *pPara)
{
	strPath.Empty();
	CExBaseObject *pParent = pPara;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == TMCLASSID_CTMFAULTPARASEX
			|| pParent->GetClassID() == TMCLASSID_CTMRESULTPARASEX)
		{
			break;
		}

		strTemp.Format(_T("%s$"), pParent->m_strID.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}
}

CString CTestMacro::GetParaIDPath(CShortData *pPara)
{
	CString strPath;
	GetParaIDPath(strPath, pPara);
	return strPath;
}

void CTestMacro::GetParaNamePath(CString &strPath, CShortData *pPara)
{
	strPath.Empty();
	CExBaseObject *pParent = pPara;
	CString strTemp;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == TMCLASSID_CTMFAULTPARASEX
			|| pParent->GetClassID() == TMCLASSID_CTMRESULTPARASEX
			|| pParent->GetClassID() == TMCLASSID_CTMFAULTPARAS
			|| pParent->GetClassID() == TMCLASSID_CTMRESULTPARAS)
		{
			break;
		}

		strTemp.Format(_T("%s$"), pParent->m_strName.GetString());
		strPath = strTemp + strPath;
		pParent = (CExBaseObject*)pParent->GetParent();
	}

	long nLen = strPath.GetLength();

	if (nLen > 0)
	{
		nLen = nLen - 1;
		strPath = strPath.Left(nLen);
	}
}

CString CTestMacro::GetParaNamePath(CShortData *pPara)
{
	CString strPath;
	GetParaNamePath(strPath, pPara);
	return strPath;
}

void CTestMacro::GetTestMacroParas_Result(CDataGroup *pResults)
{
	InitParas_Dvm();

	pResults->AppendClone(m_pResults_Dvm);
}

void CTestMacro::InitParas_Dvm()
{
	if (m_pFaultParas_Dvm != NULL)
	{
		return;
	}

	m_pFaultParas_Dvm = new CDataGroup();
	m_pResults_Dvm = new CDataGroup();

	if (m_pFaultParas != NULL)
	{
		m_pFaultParas_Dvm->AppendClone(m_pFaultParas);
		m_pFaultParas->DeleteAll();
	}

	if (m_pFaultParasEx != NULL)
	{
		m_pFaultParas_Dvm->AppendClone(m_pFaultParasEx);
		m_pFaultParasEx->DeleteAll();
	}

	if (m_pSysParas != NULL)
	{
		m_pFaultParas_Dvm->AppendClone(m_pSysParas);
		m_pSysParas->DeleteAll();
	}

	if (m_pResults != NULL)
	{
		m_pResults_Dvm->AppendClone(m_pResults);
		m_pResults->DeleteAll();
	}

	if (m_pResultsEx != NULL)
	{
		m_pResults_Dvm->AppendClone(m_pResultsEx);
		m_pResultsEx->DeleteAll();
	}


	m_pFaultParas_Dvm->ShortData_to_DvmData();
	m_pResults_Dvm->ShortData_to_DvmData();

}

BOOL CTestMacro::SaveFile()
{
	return SaveXmlFile(m_strFile, CTestMacroXmlRWKeys::g_pXmlKeys);
}void CTestMacro::SetParasToDefault()
{
	SetParasToDefault((CShortDatas *)m_pFaultParas);
	SetParasToDefault((CShortDatas *)m_pSysParas);
	SetParasToDefault((CShortDatas *)m_pFaultParasEx);
}

void CTestMacro::SetParasToDefault(CShortDatas *pDatas)
{
	if ((pDatas == NULL))
	{
		return;
	}

	CShortData* pData = NULL;
	POS pos = pDatas->GetHeadPosition();

	while (pos != NULL)
	{
		pData = (CShortData*)pDatas->GetNext(pos);
		pData->m_strValue = pData->m_strDefaultValue;
	}
}
