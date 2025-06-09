#include "StdAfx.h"
#include "RptEditInterface.h"
#include "ReportMap.h"
#include "RptItem.h"
#include "..\GuideBook.h"
#include "WordRptApi.h"

CRptEditInterface::CRptEditInterface(void):m_pGuideBook(NULL),m_bHasModified(FALSE),m_bSave(FALSE)
{
	m_pGuideBook = NULL;
	m_bModified = FALSE;

	m_dwMaxBkmkIndex = 0;
	m_pCurrBkmk = NULL;
	m_pGbItemsMap = new CRptItem();  //作业指导书的映射关系
	m_pBkmkForCopy = NULL;

	m_strSelectPath = _T("");
	m_iFindIndex = 0;	//20231010 huangliang 记录值初始为0
}

CRptEditInterface::~CRptEditInterface(void)
{
	if (m_pGuideBook != NULL)
	{
		delete m_pGuideBook;
		m_pGuideBook = NULL;
	}

	Free();
	delete m_pGbItemsMap;
	m_pGbItemsMap = NULL;
}

BOOL CRptEditInterface::IsAuthority()
{
	if (m_pGuideBook == NULL)
	{
		return FALSE;
	}

	return m_pGuideBook->IsAuthority();
}

//公共函数
BOOL CRptEditInterface::ChangeWordReportFile(const CString &strDocFile)
{
	BOOL bIsChange = FALSE; //表示报告模板文档是否改变

	if (strDocFile == m_strReportTemplateFile)
	{
		return FALSE;
	}

	//在打开模板的情况下，传入的文档为空，此时需要初始化数据类型相关的内容
	if (strDocFile.GetLength() > 0)
	{
		ExitWord(FALSE);
		bIsChange = TRUE;
		m_strReportTemplateFile = strDocFile;
	}

	//打开WPS文档
	if (!CreateWordApplication())
	{
		return FALSE;
	}

	InitAllBookmarks();
	InitAllRptBkmks();
	AttachBookmarksAndRptBkmks();
	InitBkmkMaxindex(TRUE);

	if (!bIsChange)
	{
		InitPrecisionDataType();
	}

	return TRUE;
}

void CRptEditInterface::InitAllRptBkmks()
{
	if (m_pGuideBook == NULL)
	{
		return;
	}

	m_listRptBkmks.RemoveAll();
	InitAllRptBkmks(m_pGuideBook);
}

void CRptEditInterface::AttachBookmarksAndRptBkmks()
{
	POS pos = m_listRptBkmks.GetHeadPosition();
	CRptBkmk *pRptBkmk = NULL;
	CWordBkmk *pBkmk = NULL;

	while (pos != NULL)
	{
		pRptBkmk = (CRptBkmk *)m_listRptBkmks.GetNext(pos);
		pBkmk = (CWordBkmk *)m_listWordBkmks.FindByID(pRptBkmk->m_strID);

		if (pBkmk != NULL)
		{
			pBkmk->m_pBkmk = pRptBkmk;
			pRptBkmk->m_pBkmk = pBkmk;
		}
	}
}

BOOL CRptEditInterface::FindFile(const CString& strFileName)
{
	//查找文件是否存在
	CFileFind find;
	BOOL bRet = find.FindFile(strFileName);
	find.Close();
	return bRet;
}

void CRptEditInterface::Free()
{	
	m_listRptBkmks.RemoveAll();
	m_listWordBkmks.DeleteAll();
	m_pGbItemsMap->DeleteAll();
}

//遍历RptMap查找最大Index；
void CRptEditInterface::InitBkmkMaxindex(BOOL bInitAs0)
{
	if (bInitAs0)
	{
		m_dwMaxBkmkIndex = 0;
	}

	InitMaxIndexInList();
}

void CRptEditInterface::SetMaxIndexInList(CExBaseList* pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
		{
			m_dwMaxBkmkIndex = max(m_dwMaxBkmkIndex, ((CRptBkmk*)p)->m_dwIndex);
		}
		else if (p->IsBaseList())
		{
			SetMaxIndexInList((CExBaseList*)p);
		}
	}
}

void CRptEditInterface::InitMaxIndexInList()
{
	POS pos = m_listWordBkmks.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = m_listWordBkmks.GetNext(pos);
		long nIndex = Bkmk_GetIndexFromID(p->m_strID);
		m_dwMaxBkmkIndex = max(m_dwMaxBkmkIndex, nIndex);
	}

	m_dwMaxBkmkIndex ++;
}


void CRptEditInterface::DeleteWordBkmk(CWordBkmk *pBkmk)
{
	DeleteBkmk(pBkmk->m_strID);
	m_listWordBkmks.Delete(pBkmk);
}

void CRptEditInterface::DeleteAllErrorBkmk()
{
	POS pos = m_listWordBkmks.GetHeadPosition();
	POS posPrev = NULL;
	CWordBkmk *pBkmk = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		pBkmk = (CWordBkmk*)m_listWordBkmks.GetNext(pos);

		if (pBkmk->m_pBkmk == NULL)
		{
			DeleteBkmk(pBkmk->m_strID);
			m_listWordBkmks.DeleteAt(posPrev);
		}
	}
}

CWordBkmk* CRptEditInterface::GetCopyWordBkmk()
{
	return m_pBkmkForCopy;
}

CWordBkmk* CRptEditInterface::CopyWordBkmk()
{
	if (m_pCurrBkmk == NULL)
	{
		return NULL;
	}

	m_pBkmkForCopy = m_pCurrBkmk;
	DeleteBkmk(m_pBkmkForCopy->m_strID);

	return m_pBkmkForCopy;
}

void CRptEditInterface::PasteWordBkmk()
{
	InsertBkmk(m_pBkmkForCopy->m_strID);
	m_pBkmkForCopy = NULL;
}

void CRptEditInterface::InitPrecisionDataType()
{
	m_oPrecisionDataType.DeleteAll();
	m_oPrecisionDataType.AddNewValue(_T("0"), _T("0"), _T("0"));
	m_oPrecisionDataType.AddNewValue(_T("1"), _T("1"), _T("1"));
	m_oPrecisionDataType.AddNewValue(_T("2"), _T("2"), _T("2"));
	m_oPrecisionDataType.AddNewValue(_T("3"), _T("3"), _T("3"));
	m_oPrecisionDataType.AddNewValue(_T("4"), _T("4"), _T("4"));
	m_oPrecisionDataType.AddNewValue(_T("5"), _T("5"), _T("5"));

	CDevice *pDevice = m_pGuideBook->GetDevice();

	if (pDevice == NULL)
	{
		return;
	}

	CDataSet *pSysPara = pDevice->GetSysParas();
	POS pos = pSysPara->GetHeadPosition();
	CDataObj *pDataObj = NULL;

	while (pos != NULL)
	{
		pDataObj = (CDataObj *)pSysPara->GetNext(pos);

		if (pDataObj->m_strUnit == _T("BIT"))
		{
			m_oPrecisionDataType.AddNewValue(pDataObj->m_strName, pDataObj->m_strID, pDataObj->m_strValue);
		}
	}
}

void CRptEditInterface::InitAllRptBkmks(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTBKMK)
		{
			m_listRptBkmks.AddTail(p);
		}
		else if (p->IsBaseList())
		{
			InitAllRptBkmks((CExBaseList*)p);
		}
	}
}

long CRptEditInterface::Open(const CString &strGuideBookFile)
{
	if (HasModified())
	{
		long nResult = AfxMessageBox(g_sLangTxt_ModifyAndSave/*L"文件已修改，是否保存？"*/, MB_YESNOCANCEL);

		if (nResult == IDNO  )
		{
			m_bSave = FALSE;
		}
		else if (nResult == IDYES)
		{
			m_bSave = TRUE;
		}
		else
		{
			return 0;
		}
	}

	ExitWord();
	Free();

	ASSERT (m_pGuideBook != NULL);
	m_pGuideBook->OpenXMLFile(strGuideBookFile);
	m_strGuideBookFile = strGuideBookFile;
	m_pGbItemsMap->InitGbItems(m_pGuideBook);
	m_pGbItemsMap->InitItemStateByBkmk();
	m_pGbItemsMap->InitExpandState();

	//2023-05-30 huangliang 区分各模板类型文件后缀
	CString strType = _T("doc");
	strType = GetReportSuffix();
	m_strReportTemplateFile = ChangeFilePostfix(strGuideBookFile, strType);	

	ChangeWordReportFile(_T(""));

	return TRUE;
}

long CRptEditInterface::LocateBkmk(CRptData *pData, LONG nIndex)
{
	CRptBkmk* pBkmk = (CRptBkmk*)pData->GetAt(nIndex);
	LocateBkmk(pBkmk->m_strID);
	return 0;
}

long CRptEditInterface::DeleteBkmk(CExBaseObject *pObj, CTreeCtrl *pTree, BOOL bDeleteBkmk)
{
	CAutoSimpleLock oLock(m_oWordCriticSection);

	CExBaseList *pParent = NULL;
	CExBaseList *pList = NULL;
	UINT nClassID = pObj->GetClassID();

	if (nClassID == RPTCLASSID_RPTBKMK)
	{
		pParent = (CExBaseList*)pObj->GetParent();
		pTree->DeleteItem((HTREEITEM)pObj->m_dwItemData);

		CRptBkmk *pRptBkmk = (CRptBkmk*)pObj;
		CWordBkmk *pWordBkmk = pRptBkmk->m_pBkmk;
		if (pWordBkmk != NULL)
		{
			pWordBkmk->m_pBkmk = NULL;
		}

		if (bDeleteBkmk)
		{
			DeleteBkmk(pObj->m_strID);
		}

		m_pCurrBkmk = NULL;
		m_listWordBkmks.Delete(pWordBkmk);
		pParent->Delete(pObj);
		return 0;
	}

	if (!pObj->IsBaseList())
	{
		return 0;
	}

	pList = (CExBaseList*)pObj;
	POS pos = pList->GetHeadPosition();
	CExBaseObject* p = NULL;

	while(pos !=NULL)
	{
		p = pList->GetNext(pos);
		DeleteBkmk(p, pTree, bDeleteBkmk);
	}

	nClassID = pList->GetClassID();

	if (nClassID == RPTCLASSID_RPTAREA || nClassID == RPTCLASSID_RPTDATA)
	{
		CExBaseList* pParent = (CExBaseList*)pList->GetParent();
		pTree->DeleteItem((HTREEITEM)pList->m_dwItemData);
		pParent->Delete(pList);
	}

	return 1;
}

CExBaseObject* CRptEditInterface::BindBkmk(CRptData *pData, const CString &strAttrID, const CString &strDataProcess, const CString &strFillMode, const CString &strBkmk)
{
	if(!IsValidDoc())
	{
		return FALSE;
	}

	if (pData->FindByID(strBkmk) != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("书签【%s】在数据报告中【%s】已经存在")*/g_sLangTxt_BookMarkExist, strBkmk, pData->m_strID);
		return NULL;
	}

	CAutoSimpleLock oLock(m_oWordCriticSection);

	CRptBkmk* pBkmk = NULL;

	pBkmk = (CRptBkmk*)pData->AddNew2(strBkmk);
	pBkmk->m_strDataAttrID = strAttrID;
	pBkmk->m_strProcess = strDataProcess;
	pBkmk->m_strFillMode = strFillMode;

// 	CWordBkmk *pNew = new CWordBkmk();
// 	pNew->m_strID = strBkmk;
// 	pNew->m_pBkmk = pBkmk;
// 	m_listWordBkmks.AddTail(pNew);
	CWordBkmk *pNew = (	CWordBkmk *)m_listWordBkmks.FindByID(strBkmk);//20230906 luozibing 获取当前标签信信息
	CExBaseList* pParent = (CExBaseList*)pNew->m_pBkmk->GetParent();
	pParent->DeleteByID(pNew->m_strID);									//删除其旧gbxml信息
	pNew->m_pBkmk = pBkmk;												//当前选择的信息与标签绑定
	pBkmk->m_pBkmk = pNew;


	SetRptItemBkmkState(pBkmk);

	SetMidified(TRUE);

	return pBkmk;
}

CExBaseObject* CRptEditInterface::MapBkmk(CRptData *pData, CWordBkmk *pBkmk)
{
	if (pData == NULL || pBkmk == NULL)
	{
		return NULL;
	}

	if (pData->FindByID(pBkmk->m_strID) != NULL)
	{
		return NULL;
	}

	CRptBkmk *pRptBkmk = (CRptBkmk*)pData->AddNew2(pBkmk->m_strID);
	pRptBkmk->m_pBkmk = pBkmk;
	pBkmk->m_pBkmk = pRptBkmk;

	return pRptBkmk;
}

CExBaseObject* CRptEditInterface::InsertBkmk(CRptBkmk *pBkmk)
{
	if(!IsValidDoc())
	{
		return FALSE;
	}

	CWordBkmk *pNew = NULL;

	try
	{
		InsertBkmk(pBkmk->m_strID);

		pNew = new CWordBkmk();
		pNew->m_strID = pBkmk->m_strID;
		pNew->m_strName = pBkmk->m_strID;
		m_listWordBkmks.AddTail(pNew);
		pBkmk->m_pBkmk = pNew;
		pNew->m_pBkmk = pBkmk;

		SetRptItemBkmkState(pBkmk);
	}
	catch (...)
	{
	}

	SetMidified(TRUE);
	return pNew;
}

void CRptEditInterface::DelArea(CExBaseList *pRptArea)
{
	if(!IsValidDoc())
	{
		return;
	}

	CRptArea *pArea = (CRptArea*)pRptArea;

	try
	{
		DeleteWordBkmk(pArea->m_pBkmkBegin->m_pBkmk);
	}
	catch (...)
	{
	}

	try
	{
		DeleteWordBkmk(pArea->m_pBkmkEnd->m_pBkmk);
	}
	catch (...)
	{
	}

	pArea->DeleteAll();
	SetMidified(TRUE);
}

long CRptEditInterface::Close(BOOL bSave)
{
	if (bSave)//nSave 不为0退出保存
	{
		Save();
	}
	return 0;
}

void CRptEditInterface::ClearBkmksText()
{
	ClearBkmksText(m_pGuideBook);
}

void CRptEditInterface::ClearBkmksText(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTAREA)
		{
			continue;
		}

		if (p->IsBaseList())
		{
			ClearBkmksText((CExBaseList*)p);
		}
		else
		{
			if (p->GetClassID() == RPTCLASSID_RPTBKMK)
			{
				ClearBkmkText((CRptBkmk*)p);
			}
		}
	}
}

void CRptEditInterface::SetWordWndFocus()
{
	CWnd *pWnd = NULL;
	if (::IsWindow(m_hWordWnd))
	{
		pWnd = CWnd::FromHandle(m_hWordWnd);
		if (pWnd != NULL)
		{
			BOOL b = pWnd->SetForegroundWindow();
			pWnd->SetFocus();
		}
	}
}

CWordBkmk* CRptEditInterface::GetCurrBkmk()
{	
	CAutoSimpleLock oLock(m_oWordCriticSection);
	return m_pCurrBkmk;
}

BOOL CRptEditInterface::ReplaceBkmk(CRptBkmk *pRptBkmk, CWordBkmk *pBkmk)
{
	if (pRptBkmk == NULL || pBkmk == NULL)
	{
		return FALSE;
	}

	if (pRptBkmk->m_pBkmk != NULL || pBkmk->m_pBkmk != NULL)
	{
		return FALSE;
	}

	CRptData *pData = (CRptData*)pRptBkmk->GetParent();
	pRptBkmk->m_pBkmk = pBkmk;
	pBkmk->m_pBkmk = pRptBkmk;

	ReplaceBkmk(pBkmk->m_strID, pRptBkmk->m_strID);
	pBkmk->m_strID = pRptBkmk->m_strID;

	return TRUE;
}

CRptBkmk* CRptEditInterface::GetCurrPosRptBkmk()
{
	CString strBkmk = InitCurrBkmk();
	CWordBkmk *pBkmk = GetCurrBkmk();

	if (pBkmk == NULL)
	{
		return NULL;
	}
	else
	{
		return pBkmk->m_pBkmk;
	}
}

long CRptEditInterface::AdjustReport_DelArea(CGbItemBase *pItem)
{
	if (pItem->m_pRptMap == NULL)
	{
		return 0;
	}

	AdjustReport_DelArea(pItem->m_pRptMap->m_pArea);

	return 0;
}

void CRptEditInterface::SetRptItemBkmkState(CExBaseObject *pObj)
{
	CRptItem *pItem = Rpt_GetParentRptItem(pObj);

	if (pItem == NULL)
	{
		return ;
	}

	CRptItem *pParent = pItem;

	while (pParent != NULL)
	{
		if (pParent->m_pGbItemRef->GetClassID() == GBCLASSID_GUIDEBOOK)
		{
			break;
		}

		pParent->m_bHasBkmk = TRUE;
		pParent = (CRptItem *)pParent->GetParent();
	}
}

CString CRptEditInterface::GetUIDString()
{
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	CString strUid;
	tm.wYear %= 1000;
	strUid.Format(_T("%d%d%d%d%d%d%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	char pszUid[MAX_PATH];
	char pszDestUid[MAX_PATH];
	CString_to_char(strUid, pszUid);
	char *pTemp = pszUid;
	char *pDest = pszDestUid;
	char *pEnd = pszUid + strlen(pszUid);
	int nOffset = 0;
	long nGap = 0;

	while (pTemp < pEnd)
	{
		nOffset = rand();
		nOffset %= 3;
		nOffset += 1;
		nGap = pEnd - pTemp;

		if (nOffset > nGap)
		{
			nOffset = nGap;
		}

		if (nOffset <= 0)
		{
			break;
		}

		memcpy(pDest, pTemp, nOffset);
		pDest+=nOffset;
		pTemp+= nOffset;

		if (pTemp >= pEnd)
		{
			break;
		}

		*pDest = 'A' + nOffset  + *pTemp - '0';
		pDest++;
	}

	*pDest = 0;
	strUid = pszDestUid;
	return strUid;
}

CString CRptEditInterface::GetWordFileTitle()
{
	return wordrpt_GetWordFileTitle(m_strReportTemplateFile);
}

CRptBkmk* CRptEditInterface::InsertCellBkmk(CGbItemBase *pItem, CExBaseObject *pData, const CString &strAttrID, const CString &strPrecision, long nRepeatIndex, const CString &strDataProcess, const CString &strFillMode)
{
	CreatePathID(pItem, pData->m_strID);

	CRptData* pRptData = NULL;
	CRptBkmk* pObjBkmk = NULL;
	BOOL bIsAddDataset = FALSE;
	CExBaseObject *pParent = (CExBaseObject*)pData->GetParent();

	if (pParent != NULL)
	{
		if (pParent->GetClassID() == DVMCLASSID_CDVMDATASET)
		{
			CDvmDataset *pDataset = (CDvmDataset*)pParent;

			if (pDataset->m_strDataType == CGbXMLKeys::g_pGbXMLKeys->m_strDataSetKey)
			{
				bIsAddDataset = TRUE;
			}

			if (pItem->GetClassID() == DVMCLASSID_CDVMDATASET)
			{
				pItem = (CGbItemBase*)pItem->GetParent();
			}
		}
	}

	//如果是数据集定义对象，则添加数据集的ID作为CRptData对象，Data对象作为属性
	if (bIsAddDataset)
	{
		pRptData = (CRptData*)AddRptData(pItem, pParent, strPrecision, nRepeatIndex);
		pObjBkmk = (CRptBkmk*)AddBkmk(pRptData, pData->m_strID, strDataProcess, _T("row") );
	}
	else
	{
		pRptData = (CRptData*)AddRptData(pItem, pData, strPrecision, nRepeatIndex);
		pObjBkmk = (CRptBkmk*)AddBkmk(pRptData, strAttrID, strDataProcess, strFillMode);
	}

	if (pObjBkmk == NULL)
	{
		return NULL;
	}

	//20230615 luozibing 只更新表格
	UpdateToFaceGrid();
	return pObjBkmk;
}

CExBaseObject* CRptEditInterface::FindRptBkmk(const CString & strBkmk)
{
	return FindBkmk(m_pGuideBook, strBkmk);
}

CExBaseObject* CRptEditInterface::FindBkmk(CExBaseList *pList, const CString &strBkmk)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	CExBaseObject *pFind = NULL;
	CReportMap *pMap = NULL;
	
	while (pos != NULL)
	{
		p = pList->GetNext(pos);

		if (p->GetClassID() == RPTCLASSID_RPTREPORTMAP)
		{
			pMap = (CReportMap *)p;
			pFind = pMap->FindByID(strBkmk);

			if (pFind != NULL)
			{
				break;
			}

			if (pMap->m_pArea != NULL)
			{
				pFind = pMap->m_pArea->FindByID(strBkmk);

				if (pFind != NULL)
				{
					break;
				}
			}
		}
		else if (p->IsBaseList())
		{
			pFind = FindBkmk((CExBaseList*)p, strBkmk);

			if (pFind != NULL)
			{
				break;
			}
		}
	}

	return pFind;
}

CExBaseObject* CRptEditInterface::AddRptData(CGbItemBase *pItem, CShortData *pData,const CString &strPrecision, long nRepeatIndex)
{
	return AddRptData(pItem, pData->m_strName, pData->m_strID, strPrecision, nRepeatIndex);
}

CExBaseObject*  CRptEditInterface::AddRptData(CGbItemBase *pItem, CValue *oValue,const CString &strPrecision, long nRepeatIndex)
{
	CReportMap *pMap = pItem->m_pRptMap;
	CExBaseObject* pObj;
	pObj = pMap->FindRptData(oValue->m_strID, nRepeatIndex);

	if (pObj == NULL)
	{
		pObj = pMap->AddNewData(oValue->m_strName, oValue->m_strID, strPrecision, nRepeatIndex);
		m_pGuideBook->m_dwReserved = 1;
	}

	return pObj;
}

CExBaseObject*  CRptEditInterface::AddRptData(CGbItemBase* pItem,const CString &strName, const CString &strID, const CString &strPrecision, long nRepeatIndex)
{
	CReportMap *pMap = pItem->m_pRptMap;
	CExBaseObject* pObj;
	pObj = pMap->FindRptData(strID, nRepeatIndex);

	if (pObj == NULL)
	{
		pObj = pMap->AddNewData(strName, strID, strPrecision, nRepeatIndex);
		m_pGuideBook->m_dwReserved = 1;
	}

	return pObj;
}

CExBaseObject*  CRptEditInterface::AddRptData(CGbItemBase* pItem, const CString &strID, const CString &strPrecision, long nRepeatIndex)
{
	CReportMap *pMap = pItem->m_pRptMap;
	CExBaseObject* pObj;
	pObj = pMap->FindRptData(strID, nRepeatIndex);

	if (pObj == NULL)
	{
		pObj = pMap->AddNewData(_T(""), strID, strPrecision, nRepeatIndex);
		m_pGuideBook->m_dwReserved = 1;
	}

	return pObj;
}

CString CRptEditInterface::GetDataIdPath(CExBaseObject *pData)
{
	if (pData->GetAncestor(TMCLASSID_CTMFAULTPARASEX) != NULL)
	{
		return pData->GetIDPathEx(TMCLASSID_CTMFAULTPARASEX, FALSE);
	}

	if (pData->GetAncestor(TMCLASSID_CTMRESULTPARASEX) != NULL)
	{
		return pData->GetIDPathEx(TMCLASSID_CTMRESULTPARASEX, FALSE);
	}

	return pData->m_strID;
}

CExBaseObject* CRptEditInterface::AddRptData(CGbItemBase* pItem,CExBaseObject* pObj, const CString &strPrecision, long nRepeatIndex)
{
	CReportMap *pMap = pItem->m_pRptMap;
	CExBaseObject* pNew = NULL;
	CString strIdPath = GetDataIdPath(pObj);

	pNew = pMap->FindRptData(strIdPath, nRepeatIndex);

	if (pNew == NULL)
	{
		pNew = pMap->AddNewData(pObj->m_strName, strIdPath, strPrecision, nRepeatIndex);
		m_pGuideBook->m_dwReserved = 1;
	}
	else
	{
		((CRptData*)pNew)->SetPrecision(strPrecision);
	}

	return pNew;
}


void CRptEditInterface::InitRptEdit()
{
	if (m_pGuideBook == NULL)
	{
		m_pGuideBook = new CGuideBook();
	}
}

//2023-06-25 huangliang 在基类中统一标签创建规则
CString CRptEditInterface::CreateNewBkmk(CRptData *pData)
{
	CString strBkmk = "";
	strBkmk.Format(_T("Bmk%s_%x"),GetUIDString(), m_dwMaxBkmkIndex++);
	return strBkmk;
}

void CRptEditInterface::CreatePathID(CGbItemBase *pItem, const CString &strDataID)
{
	CString strItemPath = pItem->GetIDPathEx(GBCLASSID_GUIDEBOOK, false);
	m_strSelectPath.Format(_T("%s$%s"), strItemPath, strDataID);
}

//////////////////////////////////////////////////////////////////////////
CRptItem* Rpt_GetParentRptItem(CExBaseObject *pObj)
{
	CExBaseObject *pMap = Rpt_GetParentRptMap(pObj);

	if (pMap == NULL)
	{
		return NULL;
	}

	CGbItemBase *pGbItem = (CGbItemBase*)pMap->GetParent();

	return (CRptItem*)(pGbItem->m_pRptRef);
}

CReportMap* Rpt_GetParentRptMap(CExBaseObject *pObj)
{
	CExBaseObject *pParent = pObj;
	CExBaseObject *pMap = NULL;

	while (pParent != NULL)
	{
		if (pParent->GetClassID() == RPTCLASSID_RPTREPORTMAP)
		{
			pMap = pParent;
			break;
		}

		pParent = (CExBaseObject*)pParent->GetParent();
	}

	return (CReportMap*)pMap;
}

