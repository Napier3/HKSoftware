//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DvmMatchTool.cpp  CDvmMatchTool


#include "stdafx.h"
#include "DvmMatchTool.h"

//////////////////////////////////////////////////////////////////////////
//CDvmMatchEqualObject
CDvmMatchEqualObject::CDvmMatchEqualObject()
{

}

CDvmMatchEqualObject::~CDvmMatchEqualObject()
{

}

BOOL CDvmMatchEqualObject::IsMatchTextSame(const CString &strSrcText, const CString &strDestText)
{
	if ( (m_strSrcKeysText == strSrcText) && (m_strDestKeysText == strDestText) )
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CDvmMatchEqualObject::InitMatchKey(CXKeyDB *pKeyDb, const CString &strSrcText, const CString &strDestText)
{
	m_strSrcKeysText = strSrcText;
	m_strDestKeysText = strDestText;

	m_listSrcMatchXKeys.DeleteAll();
	m_listDestMatchXKeys.DeleteAll();

	pKeyDb->QueryKeys(strSrcText, &m_listSrcMatchXKeys);
	pKeyDb->QueryKeys(strDestText, &m_listDestMatchXKeys);

	long nCountSrc = m_listSrcMatchXKeys.GetCount();
	long nCountDest = m_listDestMatchXKeys.GetCount();

	if (nCountDest == nCountSrc && nCountSrc > 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


//////////////////////////////////////////////////////////////////////////
//CDvmMatchData
CDvmMatchData::CDvmMatchData()
{

}

CDvmMatchData::CDvmMatchData(CExBaseObject *pRefObj, CXKeyDB *pKeyDb)
	: CXMatchObject(pRefObj, pKeyDb)
{

}

CDvmMatchData::~CDvmMatchData()
{

}

void CDvmMatchData::ReplaceKeys(CDvmMatchEqualObject *pXMatchEqual)
{
	POS pos = m_listMatchXKeys.GetHeadPosition();
	CXKeyMatchRef *pKey = NULL;
	CXKeyMatchRef *pKeyReplace = NULL;
	long nIndex = 0;
	POS posCurr = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		pKey = m_listMatchXKeys.GetNext(pos);
		nIndex = pXMatchEqual->m_listSrcMatchXKeys.XFindIndex(pKey);

		if (nIndex >= 0)
		{
			delete pKey;
			pKey = pXMatchEqual->m_listDestMatchXKeys.GetAtIndex(nIndex);
			m_listMatchXKeys.SetAt(posCurr, pKey->Clone());
		}
	}
}

void CDvmMatchData::RestoreKeys(CDvmMatchEqualObject *pXMatchEqual)
{
	POS pos = m_listMatchXKeys.GetHeadPosition();
	CXKeyMatchRef *pKey = NULL;
	CXKeyMatchRef *pKeyReplace = NULL;
	long nIndex = 0;
	POS posCurr = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		pKey = m_listMatchXKeys.GetNext(pos);
		nIndex = pXMatchEqual->m_listDestMatchXKeys.XFindIndex(pKey);

		if (nIndex >= 0)
		{
			delete pKey;
			pKey = pXMatchEqual->m_listSrcMatchXKeys.GetAtIndex(nIndex);
			m_listMatchXKeys.SetAt(posCurr, pKey->Clone());
		}
	}
}

void CDvmMatchData::GetAllMaps(CExBaseList &listVarMaps)
{
	CExBaseObject *pMatch = GetMatchRef();

	if (pMatch == NULL)
	{
		return;
	}

	if (m_pRefObject->m_strID == pMatch->m_strID)
	{
		return;
	}

	CString strDest;
	CDvmMapObject *pNew = NULL;

	strDest = m_pRefObject->m_strID;
	strDest.Replace(_T("$"), _T("_"));

	if (strDest != m_pRefObject->m_strID)
	{
		pNew = new CDvmMapObject();
		listVarMaps.AddTail(pNew);
		pNew->m_strID = m_pRefObject->m_strID;
		pNew->m_strMapID = strDest;
	}

	pNew = new CDvmMapObject();
	listVarMaps.AddTail(pNew);
	pNew->m_strID = strDest;
	pNew->m_strMapID = pMatch->m_strID;
}

//////////////////////////////////////////////////////////////////////////
//CDvmMatchDataset
CDvmMatchDataset::CDvmMatchDataset()
{
	m_pThreadProgress = NULL;
	m_nMatchRatio = 80;
}

CDvmMatchDataset::~CDvmMatchDataset()
{
	m_listSrcDataset.RemoveAll();   //源数据集列表
	m_listDestDataset.RemoveAll();   //目标数据集列表
	m_listSrcDatas.RemoveAll();     //源数据集的所有数据对象
	m_listDestDatas.RemoveAll();     //目标数据集的所有数据对象
}

CXMatchObject* CDvmMatchDataset::CreateMatchObject(CExBaseObject *pRefObj, CXKeyDB *pKeyDb)
{
	return new CDvmMatchData(pRefObj, pKeyDb);
}

BOOL CDvmMatchDataset::IsMatchInclude(CExBaseList *pSrc, CExBaseList *pDest)
{
	if (m_listSrcDataset.Find(pSrc) != NULL)
	{
		return TRUE;
	}

	if (m_listDestDataset.Find(pDest) != NULL)
	{
		return TRUE;
	}

	return FALSE;
}

void CDvmMatchDataset::AddMatchDataset(CExBaseList *pSrc, CExBaseList *pDest)
{
	if (m_listSrcDataset.Find(pSrc) == NULL)
	{
		m_listSrcDataset.AddTail(pSrc);
		m_listSrcDatas.Append(pSrc);
	}

	if (m_listDestDataset.Find(pDest) == NULL)
	{
		m_listDestDataset.AddTail(pDest);
		m_listDestDatas.Append(pDest);
	}
}

void CDvmMatchDataset::XMatch(CXKeyDB *pXKeyDB)
{
	Init(&m_listSrcDatas, pXKeyDB, m_pThreadProgress);
	m_oDestXMatchList.Init(&m_listDestDatas, pXKeyDB, m_pThreadProgress);
	Match(&m_oDestXMatchList, m_nMatchRatio, m_pThreadProgress, FALSE);
}

void CDvmMatchDataset::ReXMatch()
{
	FreeMatch();
	Match(&m_oDestXMatchList, m_nMatchRatio, m_pThreadProgress, FALSE);
}

CXMatchObject* CDvmMatchDataset::FindXMatchObjBySrc(CExBaseObject *pDvmDataObj)
{
	POS pos = GetHeadPosition();
	CXMatchObject *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)GetNext(pos);

		if (p->m_pRefObject == pDvmDataObj)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CDvmMatchDataset::ReplaceKeys(CDvmMatchEqualObject *pXMatchEqual)
{
	POS pos = GetHeadPosition();
	CDvmMatchData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMatchData *)GetNext(pos);
		p->ReplaceKeys(pXMatchEqual);
	}
}

void CDvmMatchDataset::RestoreKeys(CDvmMatchEqualObject *pXMatchEqual)
{
	POS pos = GetHeadPosition();
	CDvmMatchData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMatchData *)GetNext(pos);
		p->RestoreKeys(pXMatchEqual);
	}
}

void CDvmMatchDataset::SelFirstMatch()
{
	POS pos = GetHeadPosition();
	CDvmMatchData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMatchData *)GetNext(pos);
		p->SelFirstMatch();
	}
}


BOOL CDvmMatchDataset::ValidateMatch()
{
	POS pos = GetHeadPosition();
	CDvmMatchData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMatchData *)GetNext(pos);
		
		if (!p->ValidateMatch())
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CDvmMatchDataset::GetAllMaps(CExBaseList &listVarMaps)
{
	POS pos = GetHeadPosition();
	CDvmMatchData *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMatchData *)GetNext(pos);
		p->GetAllMaps(listVarMaps);
	}
}

//////////////////////////////////////////////////////////////////////////
//CDvmMatchTool
CDvmMatchTool::CDvmMatchTool()
{
	m_pSrcDvmDevice = NULL;
	m_pDestDvmDevice = NULL;

	m_nClassID_Device = -1;
	m_nClassID_Ldevice = -1;
	m_nClassID_Dataset = -1;
	m_nClassID_Data = -1;

	m_oDvmCmpKeyDataTypes.OpenKeyDataTypesFile(_T(""));
}

CDvmMatchTool::~CDvmMatchTool()
{
	m_listDestDvmDataset.RemoveAll();
}

CXMatchObject* CDvmMatchTool::FindXMatchObjBySrc(CExBaseObject *pDvmDataObj)
{
	CExBaseObject *pDataset = (CExBaseObject*)pDvmDataObj->GetParent();
	POS pos = GetHeadPosition();
	CDvmMatchDataset *pXMatchDs = NULL;

	while (pos != NULL)
	{
		pXMatchDs = (CDvmMatchDataset *)GetNext(pos);

		if (pXMatchDs->m_listSrcDataset.Find(pDataset) != NULL)
		{
			return pXMatchDs->FindXMatchObjBySrc(pDvmDataObj);
		}
	}

	return NULL;
}

void CDvmMatchTool::DvmMatch_Device(CExBaseList *pSrc, CExBaseList *pDest)
{
	ASSERT (m_nClassID_Device != -1);
	ASSERT (pSrc != NULL && pDest != NULL);

	ASSERT( m_nClassID_Device == pSrc->GetClassID() && m_nClassID_Device == pDest->GetClassID());
	
	DvmMatch_BuildMatch(pSrc, pDest);
	DvmMatch_XMatch();
	InitDestDvmDataset();
}


void CDvmMatchTool::DvmMatch_BuildMatch(CExBaseList *pSrc, CExBaseList *pDest)
{
	POS pos = pSrc->GetHeadPosition();
	CExBaseList *pSrcLdevice = NULL;
	CExBaseList *pDestLdevice = NULL;
	long nCount = 0;
	CExBaseList listLdevice;

	while (pos != NULL)
	{
		pSrcLdevice = (CExBaseList *)pSrc->GetNext(pos);

		if (m_nClassID_Ldevice != pSrcLdevice->GetClassID())
		{
			continue;
		}

		nCount = DvmMatch_FindDestLdevice(pSrcLdevice, pDest, listLdevice);

		if (nCount > 0)
		{
			DvmMatch_Ldevice_List(pSrcLdevice, listLdevice);
		}

		listLdevice.RemoveAll();
	}
}

void CDvmMatchTool::InitDestDvmDataset()
{
	POS pos = GetHeadPosition();
	CDvmMatchDataset *p = NULL;

	while (pos != NULL)
	{
		p = (CDvmMatchDataset *)GetNext(pos);
		m_listDestDvmDataset.Append(p->m_listDestDataset);
	}
}

void CDvmMatchTool::DvmMatch_XMatch()
{
	POS pos = GetHeadPosition();
	CDvmMatchDataset *pDvmDsMatch = NULL;

	while (pos != NULL)
	{
		pDvmDsMatch = (CDvmMatchDataset *)GetNext(pos);
		pDvmDsMatch->XMatch(m_pXKeyDB);
	}
}

void CDvmMatchTool::ReXMatch()
{
	POS pos = GetHeadPosition();
	CDvmMatchDataset *pDvmDsMatch = NULL;

	while (pos != NULL)
	{
		pDvmDsMatch = (CDvmMatchDataset *)GetNext(pos);
		pDvmDsMatch->ReXMatch();
	}
}

long CDvmMatchTool::DvmMatch_FindDestLdevice(CExBaseList *pSrcLdevice, CExBaseList *pDestDevice, CExBaseList &listLdevice)
{
	//比较逻辑设备的关键字
	long nKeySrc = m_oDvmCmpKeyDataTypes.GetLdeviceKey(pSrcLdevice->m_strID);
	long nKeyDest = 0;

	POS pos = pDestDevice->GetHeadPosition();
	CExBaseList *pDestLdevice = NULL;
	CExBaseList *pFind = NULL;

	while (pos != NULL)
	{
		pDestLdevice = (CExBaseList *)pDestDevice->GetNext(pos);
		nKeyDest = m_oDvmCmpKeyDataTypes.GetLdeviceKey(pDestLdevice->m_strID);

		if (nKeySrc == nKeyDest)
		{
			listLdevice.AddTail(pDestLdevice);
		}
	}

	return listLdevice.GetCount();
}

void CDvmMatchTool::DvmMatch_Ldevice_List(CExBaseList *pSrcLdevice, CExBaseList &listLdevice)
{
	POS pos = listLdevice.GetHeadPosition();
	CExBaseList *pDestLdevice = NULL;

	while (pos != NULL)
	{
		pDestLdevice = (CExBaseList *)listLdevice.GetNext(pos);
		DvmMatch_Ldevice(pSrcLdevice, pDestLdevice);
	}
}

void CDvmMatchTool::DvmMatch_Ldevice(CExBaseList *pSrc, CExBaseList *pDest)
{
	ASSERT (m_nClassID_Ldevice != -1);
	ASSERT (pSrc != NULL && pDest != NULL);
	
	AddDvmMap(pSrc, pDest);
	
	POS pos = pSrc->GetHeadPosition();
	CExBaseList *pSrcDataset = NULL;
	CExBaseList listDataset;
	long nCount = 0;

	while (pos != NULL)
	{
		pSrcDataset = (CExBaseList *)pSrc->GetNext(pos);

		if (m_nClassID_Dataset != pSrcDataset->GetClassID())
		{
			continue;
		}

		nCount = DvmMatch_FindDestDataset(pSrcDataset, pDest, listDataset);

		if (nCount > 0)
		{
			DvmMatch_Dataset_List(pSrcDataset, listDataset);
		}

		listDataset.RemoveAll();
	}
}

long CDvmMatchTool::DvmMatch_FindDestDataset(CExBaseList *pSrcDataset, CExBaseList *pDestLdevice, CExBaseList &listDataset)
{
	//比较逻辑设备的关键字
	long nKeySrc = m_oDvmCmpKeyDataTypes.GetDatasetKey(pSrcDataset->m_strID);
	long nKeyDest = 0;

	POS pos = pDestLdevice->GetHeadPosition();
	CExBaseList *pDestDataset = NULL;
	CExBaseList *pFind = NULL;

	while (pos != NULL)
	{
		pDestDataset = (CExBaseList *)pDestLdevice->GetNext(pos);
		nKeyDest = m_oDvmCmpKeyDataTypes.GetDatasetKey(pDestDataset->m_strID);

		if (nKeySrc == nKeyDest)
		{
			listDataset.AddTail(pDestDataset);
		}
	}

	return listDataset.GetCount();
}

void CDvmMatchTool::DvmMatch_Dataset_List(CExBaseList *pSrcDataset, CExBaseList &listDataset)
{
	POS pos = listDataset.GetHeadPosition();
	CExBaseList *pDestDataset = NULL;

	while (pos != NULL)
	{
		pDestDataset = (CExBaseList *)listDataset.GetNext(pos);
		DvmMatch_Dataset(pSrcDataset, pDestDataset);
	}
}

void CDvmMatchTool::DvmMatch_Dataset(CExBaseList *pSrc, CExBaseList *pDest)
{
	ASSERT (m_nClassID_Device != -1);
	ASSERT (pSrc != NULL && pDest != NULL);

	AddDvmMap(pSrc, pDest);
	
	CDvmMatchDataset *p = FindDvmMatch_Dataset(pSrc, pDest);

	if (p == NULL)
	{
		p = new CDvmMatchDataset();
		AddNewChild(p);
	}

	p->AddMatchDataset(pSrc, pDest);
}


CDvmMatchDataset* CDvmMatchTool::FindDvmMatch_Dataset(CExBaseList *pSrc, CExBaseList *pDest)
{
	CDvmMatchDataset *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		 p = (CDvmMatchDataset*)GetNext(pos);

		 if (p->IsMatchInclude(pSrc, pDest))
		 {
			pFind = p;
			break;
		 }
	}

	return pFind;
}

CDvmMapObject* CDvmMatchTool::AddDvmMap(CExBaseList *pSrc, CExBaseList *pDest)
{
	CDvmMapObject *p = FindDvmMap(pSrc, pDest);

	if (p != NULL)
	{
		return p;
	}

	p = new CDvmMapObject();
	p->m_pStand = pSrc;
	p->m_pMap = pDest;
	m_listLdDsMap.AddTail(p);

	return p;
}

CDvmMapObject* CDvmMatchTool::FindDvmMap(CExBaseList *pSrc, CExBaseList *pDest)
{
	CDvmMapObject *p = NULL, *pFind = NULL;
	POS pos = m_listLdDsMap.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmMapObject*)m_listLdDsMap.GetNext(pos);

		if (p->m_pStand == pSrc && p->m_pMap == pDest)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CDvmMatchTool::ReplaceKeys(CDvmMatchEqualObject *pXMatchEqual)
{
	CDvmMatchDataset *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmMatchDataset*)GetNext(pos);
		p->ReplaceKeys(pXMatchEqual);
	}

	ReXMatch();
}

void CDvmMatchTool::RestoreKeys(CDvmMatchEqualObject *pXMatchEqual)
{
	CDvmMatchDataset *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmMatchDataset*)GetNext(pos);
		p->RestoreKeys(pXMatchEqual);
	}
}

void CDvmMatchTool::SelFirstMatch()
{
	CDvmMatchDataset *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmMatchDataset*)GetNext(pos);
		p->SelFirstMatch();
	}
}


BOOL CDvmMatchTool::ValidateMatch()
{
	CDvmMatchDataset *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmMatchDataset*)GetNext(pos);

		if (!p->ValidateMatch())
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CDvmMatchTool::GetAllMaps(CExBaseList &listVarMaps)
{
	CDvmMatchDataset *p = NULL, *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CDvmMatchDataset*)GetNext(pos);
		p->GetAllMaps(listVarMaps);
	}

	pos = m_listLdDsMap.GetHeadPosition();
	CDvmMapObject *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmMapObject *)m_listLdDsMap.GetNext(pos);

		if ((pMap->m_pStand == NULL) || (pMap->m_pMap == NULL))
		{
			continue;
		}

		if (pMap->m_pStand->m_strID != pMap->m_pMap->m_strID)
		{
			CDvmMapObject *pNew = new CDvmMapObject();
			pMap->CopyOwn(pNew);
			listVarMaps.AddTail(pNew);
		}
	}
}

