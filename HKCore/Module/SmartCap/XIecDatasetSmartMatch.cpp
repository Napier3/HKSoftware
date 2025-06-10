#include "stdafx.h"
#include "XIecDatasetSmartMatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
算法描述：如下数据集
【
第一组保护电流A相-保护电流A相1
第一组保护电流A相-保护电流A相2
第一组保护电流B相-保护电流B相1
第一组保护电流B相-保护电流B相2
第一组保护电流C相-保护电流C相1
第一组保护电流C相-保护电流C相2
第二组保护电流A相-保护电流A相1
第二组保护电流A相-保护电流A相2
第二组保护电流B相-保护电流B相1
第二组保护电流B相-保护电流B相2
第二组保护电流C相-保护电流C相1
第二组保护电流C相-保护电流C相2
测量电流A相
测量电流B相
测量电流C相
保护电压A相-电压A相1
保护电压A相-电压A相2
保护电压B相-电压B相1
保护电压B相-电压B相2
保护电压C相-电压C相1
保护电压C相-电压C相2
测量电压A相
测量电压B相
测量电压C相
同期电压1-抽取电压1
同期电压1-抽取电压2
同期电压2-抽取电压1
同期电压2-抽取电压2
】

第一步：分析关键字
第二步：将通道按照电压、电流、A相、B相、C相进行分组
第三步：就第二步的基础上，对电压、电流进行三相分组组合，组名称为去掉电压、电流、相别关键字，剩下的关键字的组合（非关键字一考虑进来）
第四步：基于第三步，提取相同分类名称的电压、电流组，进行组合
*/
/*
矢量图：
	第五步：基于第四步，为每个电压电流组合创建矢量图对象

序分量：
	第四步：基于第三步，为每个电压、电流三相分组创建序分量对象

功率：
	第五步：基于第四步，为每个电压电流组合创建功率分析对象
*/

CDvmData* iec_match_get_dvmdata(CExBaseObject *pObj)
{
	if (pObj == NULL)
	{
		return NULL;
	}

	if (pObj->GetClassID() == KDBCLASSID_CXMATCHOBJECT)
	{
		return (CDvmData*) (((CXMatchObject*)pObj)->m_pRefObject);
	}
	else
	{
		return (CDvmData*)pObj;
	}
}

BOOL iec_match_XmlWrite(CExBaseObject *pObj, CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	if (pObj == NULL)
	{
		return FALSE;
	}

	if (pObj->GetClassID() == KDBCLASSID_CXMATCHOBJECT)
	{
		((CXMatchObject*)pObj)->m_pRefObject->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}
	else
	{
		pObj->XmlWrite(oXMLDoc, oElement, pXmlRWKeys);
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//CXIecDs_UIGroup_ABC
CXIecDs_Group_U_or_I_ALL::CXIecDs_Group_U_or_I_ALL()
{

}

CXIecDs_Group_U_or_I_ALL::~CXIecDs_Group_U_or_I_ALL()
{
	RemoveAll();
}

long CXIecDs_Group_U_or_I_ALL::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	POS pos = GetHeadPosition();
	CExBaseObject *pObj = NULL;

	while (pos != NULL)
	{
		pObj = GetNext(pos);
		iec_match_XmlWrite(pObj, oXMLDoc, oElement, pXmlRWKeys);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////
//	//CXIecDs_Group_ABC
CXIecDs_Group_ABC::CXIecDs_Group_ABC()
{
	m_pA = NULL;
	m_pB = NULL;
	m_pC = NULL;
	m_nRelationIndex = 0;  //缺省值为0，表示
}

CXIecDs_Group_ABC::~CXIecDs_Group_ABC()
{

}

long CXIecDs_Group_ABC::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	iec_match_XmlWrite(m_pA, oXMLDoc, oElement, pXmlRWKeys);
	iec_match_XmlWrite(m_pB, oXMLDoc, oElement, pXmlRWKeys);
	iec_match_XmlWrite(m_pC, oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}

void CXIecDs_Group_ABC::InitXKeyMatchRefList(CXKeyMatchRefList &listMatchXKeys, CXKeyMatchRef *pKeyDel)
{
	CXKeyMatchRef *p = NULL;
	POS pos = listMatchXKeys.GetHeadPosition();

	while (pos != NULL)
	{
		p = listMatchXKeys.GetNext(pos);

		if (p->Match(pKeyDel))
		{
			continue;
		}

		m_listMatchXKeys.AddTail(p->Clone());
	}
}


//////////////////////////////////////////////////////////////////////////
//CXIecDs_UIGroup_UI
CXIecDs_Group_UI::CXIecDs_Group_UI()
{
	m_pU = NULL;
	m_pI = NULL;
}

CXIecDs_Group_UI::~CXIecDs_Group_UI()
{
	
}


long CXIecDs_Group_UI::XmlWriteChildren(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	iec_match_XmlWrite(m_pU, oXMLDoc, oElement, pXmlRWKeys);
	iec_match_XmlWrite(m_pI, oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}


//////////////////////////////////////////////////////////////////////////
//CXIecDs_Group_UI_ABC
CXIecDs_Group_UI_ABC::CXIecDs_Group_UI_ABC()
{
	m_pUI_A = new CXIecDs_Group_UI();
	m_pUI_B = new CXIecDs_Group_UI();
	m_pUI_C = new CXIecDs_Group_UI();

	m_pUI_A->m_strID = _T("A");
	m_pUI_B->m_strID = _T("B");
	m_pUI_C->m_strID = _T("C");

	AddNewChild(m_pUI_A);
	AddNewChild(m_pUI_B);
	AddNewChild(m_pUI_C);
}

CXIecDs_Group_UI_ABC::~CXIecDs_Group_UI_ABC()
{
	
}

void CXIecDs_Group_UI_ABC::InitUI(CXIecDs_Group_ABC *pU, CXIecDs_Group_ABC *pI)
{
	m_pUI_A->m_pU = pU->m_pA;
	m_pUI_A->m_pI = pI->m_pA;

	m_pUI_B->m_pU = pU->m_pB;
	m_pUI_B->m_pI = pI->m_pB;

	m_pUI_C->m_pU = pU->m_pC;
	m_pUI_C->m_pI = pI->m_pC;
}

//////////////////////////////////////////////////////////////////////////
//CXIecDatasetSmartMatch
CXIecDatasetSmartMatch::CXIecDatasetSmartMatch()
{
	//按照ABC三相对电压电流进行分组
	m_pGroupUa = new CXIecDs_Group_U_or_I_ALL();
	m_pGroupUb = new CXIecDs_Group_U_or_I_ALL();
	m_pGroupUc = new CXIecDs_Group_U_or_I_ALL();
	m_pGroupIa  = new CXIecDs_Group_U_or_I_ALL();
	m_pGroupIb  = new CXIecDs_Group_U_or_I_ALL();
	m_pGroupIc  = new CXIecDs_Group_U_or_I_ALL();
	m_pGroupUa->m_strID = _T("Ua_Mngr");
	m_pGroupUb->m_strID = _T("Ub_Mngr");
	m_pGroupUc->m_strID = _T("Uc_Mngr");
	m_pGroupIa->m_strID = _T("Ia_Mngr");
	m_pGroupIb->m_strID = _T("Ib_Mngr");
	m_pGroupIc->m_strID = _T("Ic_Mngr");
	AddNewChild(m_pGroupUa);
	AddNewChild(m_pGroupUb);
	AddNewChild(m_pGroupUc);
	AddNewChild(m_pGroupIa);
	AddNewChild(m_pGroupIb);
	AddNewChild(m_pGroupIc);

	//三相组  CXIecDs_Group_ABC，用于矢量图、序分量等电压、电流三相组合属性分析
	m_pGroup_ABC_U_List = new CDataGroup();
	m_pGroup_ABC_U_List->m_strID = _T("U_ABC");
	AddNewChild(m_pGroup_ABC_U_List);

	m_pGroup_ABC_I_List = new CDataGroup();
	m_pGroup_ABC_I_List->m_strID = _T("I_ABC");
	AddNewChild(m_pGroup_ABC_I_List);

	//三相组  CXIecDs_Group_UI_ABC，用于矢量图、序分量等电压、电流三相组合属性分析
	 m_pGroup_UI_ABC_List = new CDataGroup();
	 m_pGroup_UI_ABC_List->m_strID = _T("UI_ABC");
	 AddNewChild(m_pGroup_UI_ABC_List);

	 CXKeyDB::SetRemoveSubKeys(false);
	 CXMatchObject::g_bNumberKeyMatchRatioAdd = 1; //2022-5-10 提高数字的占比
}

CXIecDatasetSmartMatch::~CXIecDatasetSmartMatch()
{
	CXKeyDB::SetRemoveSubKeys(true);
	CXMatchObject::g_bNumberKeyMatchRatioAdd = 0;
}

void CXIecDatasetSmartMatch::IecDatasetSmartMatch(CDvmDataset *pDataset)
{
	m_oXMatchList.DeleteAll();
	m_oXMatchList.Init(pDataset, m_pKeyDB);

	Group_U_I_A_B_C();

	//对电压、电流，进行ABC三相分组
	GroupForABC(m_pGroup_ABC_U_List, _T("U"), m_pGroupUa, m_pGroupUb, m_pGroupUc);
	GroupForABC(m_pGroup_ABC_I_List, _T("I"), m_pGroupIa, m_pGroupIb, m_pGroupIc);

	//匹配规则：以最多的通道组去匹配最少的通道组
	if (m_pGroup_ABC_U_List->GetCount() >= m_pGroup_ABC_I_List->GetCount())
	{
		Group_U_I_ABC(m_pGroup_ABC_U_List, m_pGroup_ABC_I_List);
	}
	else
	{
		Group_I_U_ABC(m_pGroup_ABC_I_List, m_pGroup_ABC_U_List);
	}
}

void CXIecDatasetSmartMatch::Group_U_I_A_B_C()
{
	SelectByKey(_T("UA"), *m_pGroupUa);
	SelectByKey(_T("电压"), _T("A相"), *m_pGroupUa);
	SelectByKey(_T("UB"), *m_pGroupUb);
	SelectByKey(_T("电压"), _T("B相"), *m_pGroupUb);
	SelectByKey(_T("UC"), *m_pGroupUc);
	SelectByKey(_T("电压"), _T("C相"), *m_pGroupUc);

	SelectByKey(_T("IA"), *m_pGroupIa);
	SelectByKey(_T("电流"), _T("A相"), *m_pGroupIa);
	SelectByKey(_T("IB"), *m_pGroupIb);
	SelectByKey(_T("电流"), _T("B相"), *m_pGroupIb);
	SelectByKey(_T("IC"), *m_pGroupIc);
	SelectByKey(_T("电流"), _T("C相"), *m_pGroupIc);

	RemoveByKey(_T("同期"), *m_pGroupUa);
	RemoveByKey(_T("同期"), *m_pGroupUb);
	RemoveByKey(_T("同期"), *m_pGroupUc);

	RemoveKey(_T("UA"), *m_pGroupUa);
	RemoveKey(_T("电压"), *m_pGroupUa);
	RemoveKey(_T("UB"), *m_pGroupUb);
	RemoveKey(_T("电压"), *m_pGroupUb);
	RemoveKey(_T("UC"), *m_pGroupUc);
	RemoveKey(_T("电压"), *m_pGroupUc);

	RemoveKey(_T("IA"), *m_pGroupIa);
	RemoveKey(_T("电流"), *m_pGroupIa);
	RemoveKey(_T("IB"), *m_pGroupIb);
	RemoveKey(_T("电流"), *m_pGroupIb);
	RemoveKey(_T("IC"), *m_pGroupIc);
	RemoveKey(_T("电流"), *m_pGroupIc);
}

void iec_match_add_tail(CExBaseList &listDest, CXMatchObject *p)
{
	if (listDest.Find(p) != NULL)
	{
		return;
	}

	listDest.AddTail(p);
}

void CXIecDatasetSmartMatch::SelectByKey(const CString &strKey, CExBaseList &listDest)
{
	CXKeyMatchRef *pKeyRef = m_pKeyDB->CreateXKeyMatchRef(strKey, 0);

	if (pKeyRef == NULL)
	{
		return;
	}

	POS pos = m_oXMatchList.GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)m_oXMatchList.GetNext(pos);
		
		if (p->m_listMatchXKeys.Match(pKeyRef))
		{
			iec_match_add_tail(listDest, p);
		}
	}

	delete pKeyRef;
}

void CXIecDatasetSmartMatch::RemoveByKey(const CString &strKey, CExBaseList &listDest)
{
	CXKeyMatchRef *pKeyRef = m_pKeyDB->CreateXKeyMatchRef(strKey, 0);

	if (pKeyRef == NULL)
	{
		return;
	}

	POS pos = listDest.GetHeadPosition();
	CXMatchObject *p = NULL;
	POS posPrev = NULL;

	while (pos != NULL)
	{
		posPrev = pos;
		p = (CXMatchObject *)listDest.GetNext(pos);

		if (p->m_listMatchXKeys.Match(pKeyRef))
		{
			listDest.RemoveAt(posPrev);
		}
	}

	delete pKeyRef;
}

void CXIecDatasetSmartMatch::RemoveKey(const CString &strKey, CExBaseList &listDest)
{
	CXKeyMatchRef *pKeyRef = m_pKeyDB->CreateXKeyMatchRef(strKey, 0);

	if (pKeyRef == NULL)
	{
		return;
	}

	POS pos = listDest.GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)listDest.GetNext(pos);
		p->m_listMatchXKeys.RemoveKey(pKeyRef);
	}

	delete pKeyRef;
}

void CXIecDatasetSmartMatch::SelectByKey(const CString &strKey1, const CString &strKey2, CExBaseList &listDest)
{
	CXKeyMatchRef oKey1, oKey2;
	BOOL bKey1, bKey2;

	bKey1 = m_pKeyDB->CreateXKeyMatchRef(strKey1, 0, oKey1);
	bKey2 = m_pKeyDB->CreateXKeyMatchRef(strKey2, 0, oKey2);

	if (!bKey1 || !bKey2)
	{
		return;
	}

	POS pos = m_oXMatchList.GetHeadPosition();
	CXMatchObject *p = NULL;

	while (pos != NULL)
	{
		p = (CXMatchObject *)m_oXMatchList.GetNext(pos);

		if (p->m_listMatchXKeys.Match(&oKey1) && p->m_listMatchXKeys.Match(&oKey2))
		{
			iec_match_add_tail(listDest, p);
		}
	}
}

void CXIecDatasetSmartMatch::GroupForABC(CDataGroup *pGroup_ABC, const CString &strType, CDataGroup *pGroupA, CDataGroup *pGroupB, CDataGroup *pGroupC)
{
	POS pos = pGroupA->GetHeadPosition();
	CXMatchObject *pA = NULL;
	CXMatchObject *pB = NULL;
	CXMatchObject *pC = NULL;

	CString strType_A, strType_B, strType_C;
// 	strType_A = strType + _T("A");
// 	strType_B = strType + _T("B");
// 	strType_C = strType + _T("C");
	strType_A = _T("A相");
	strType_B = _T("B相");
	strType_C = _T("C相");

	CXKeyMatchRef oKeyRefA, oKeyRefB, oKeyRefC;
	BOOL bKeyRefA = m_pKeyDB->CreateXKeyMatchRef(strType_A, 0, oKeyRefA);
	BOOL bKeyRefB = m_pKeyDB->CreateXKeyMatchRef(strType_B, 0, oKeyRefB);
	BOOL bKeyRefC = m_pKeyDB->CreateXKeyMatchRef(strType_C, 0, oKeyRefC);

	if ((!bKeyRefA) || (!bKeyRefB) || (!bKeyRefC))
	{
		return;
	}

	while (pos != NULL)
	{
		pA = (CXMatchObject*)pGroupA->GetNext(pos);
		pB = GroupForABC_Find(pA, pGroupB, &oKeyRefA, &oKeyRefB);
		pC = GroupForABC_Find(pA, pGroupC, &oKeyRefA, &oKeyRefC);

		if (pB != NULL && pC != NULL)
		{
			CXIecDs_Group_ABC *pNew = new CXIecDs_Group_ABC();
			pNew->m_pA = pA;
			pNew->m_pB = pB;
			pNew->m_pC = pC;
			pNew->m_strDataType = strType;
			pNew->m_strName = pA->m_pRefObject->m_strName;
			pNew->m_strID = pA->m_pRefObject->m_strID;
			pNew->InitXKeyMatchRefList(pA->m_listMatchXKeys, &oKeyRefA);
			pGroup_ABC->AddNewChild(pNew);
		}
	}
}

CXMatchObject* CXIecDatasetSmartMatch::GroupForABC_Find(CXMatchObject *pA, CDataGroup *pGroupX, CXKeyMatchRef *pTypeA, CXKeyMatchRef *pTypeX)
{
	POS pos = pGroupX->GetHeadPosition();
	CXMatchObject *pX = NULL;
	CXMatchObject *pFind = NULL;

	while (pos != NULL)
	{
		pX = (CXMatchObject*)pGroupX->GetNext(pos);
		
		if (GroupForABC_Find_Match(pA, pX, pTypeA, pTypeX))
		{
			pFind = pX;
			break;
		}
	}

	return pFind;
}

BOOL CXIecDatasetSmartMatch::GroupForABC_Find_Match(CXMatchObject *pA, CXMatchObject *pX, CXKeyMatchRef *pTypeA, CXKeyMatchRef *pTypeX)
{
	CXKeyMatchRefList *pKeyRefA = &pA->m_listMatchXKeys;
	CXKeyMatchRefList *pKeyRefX = &pX->m_listMatchXKeys;

	if (pKeyRefA->GetCount() != pKeyRefX->GetCount())
	{//两个数据对象关键字不相同，表示不能正确匹配
		return FALSE;
	}

	POS pos = pKeyRefA->GetHeadPosition();
	CXKeyMatchRef *p = NULL;

	while (pos != NULL)
	{
		p = pKeyRefA->GetNext(pos);

		if (p->Match(pTypeA))
		{//A相关键字，忽略
			continue;
		}


		POS posx = pKeyRefX->GetHeadPosition();
		CXKeyMatchRef *pRefX = NULL;
		BOOL bMatch = FALSE;

		while (posx != NULL)
		{
			pRefX = pKeyRefX->GetNext(posx);

			if (pRefX->Match(pTypeX))
			{//其他相别关键字，忽略
				continue;
			}

			if (pRefX->Match(p))
			{//如果有相同的关键字，则表示匹配
				bMatch = TRUE;
			}
		}

		if (!bMatch)
		{
			return FALSE;
		}
	}

	return TRUE;
}

void CXIecDatasetSmartMatch::Group_U_I_ABC(CDataGroup *pGroup_ABC_U, CDataGroup *pGroup_ABC_I)
{
	CXIecDs_Group_ABC *pU = NULL, *pI = NULL;
	POS pos = pGroup_ABC_U->GetHeadPosition();
	CXIecDs_Group_UI_ABC *pNew = NULL;

	while (pos != NULL)
	{
		pU = (CXIecDs_Group_ABC *)pGroup_ABC_U->GetNext(pos);
		pI = Group_XX_ABC_Find(pU->m_listMatchXKeys, pGroup_ABC_I);
		
		if (pI != NULL)
		{
			pNew = new CXIecDs_Group_UI_ABC();
			pNew->InitUI(pU, pI);
			m_pGroup_UI_ABC_List->AddNewChild(pNew);
		}
	}
}

void CXIecDatasetSmartMatch::Group_I_U_ABC(CDataGroup *pGroup_ABC_I, CDataGroup *pGroup_ABC_U)
{
	CXIecDs_Group_ABC *pU = NULL, *pI = NULL;
	POS pos = pGroup_ABC_I->GetHeadPosition();
	CXIecDs_Group_UI_ABC *pNew = NULL;
	long nIndex = 1;

	while (pos != NULL)
	{
		pI = (CXIecDs_Group_ABC *)pGroup_ABC_I->GetNext(pos);
		pU = Group_XX_ABC_Find(pI->m_listMatchXKeys, pGroup_ABC_U);

		if (pU != NULL)
		{
			pU->m_nRelationIndex = nIndex;
			pI->m_nRelationIndex = nIndex;
			nIndex++;
			pNew = new CXIecDs_Group_UI_ABC();
			pNew->InitUI(pU, pI);
			m_pGroup_UI_ABC_List->AddNewChild(pNew);
		}
	}
}

CXIecDs_Group_ABC* CXIecDatasetSmartMatch::Group_XX_ABC_Find(CXKeyMatchRefList &oXMatchList, CDataGroup *pGroup_ABC_X)
{
	CXIecDs_Group_ABC *pMax = NULL;

	CXIecDs_Group_ABC *p = NULL;
	POS pos = pGroup_ABC_X->GetHeadPosition();
	CXMatchObject oXMatchObj;  //用到对象的匹配函数，没有实际用途的对象
	long nRatio = 0;

	while (pos != NULL)
	{
		p = (CXIecDs_Group_ABC *)pGroup_ABC_X->GetNext(pos);
		oXMatchObj.XMatch(&oXMatchList, &p->m_listMatchXKeys, nRatio);
		
		if (nRatio > 0)
		{
			oXMatchObj.XAddXMatchRatioObject(nRatio, p);
		}
	}

	oXMatchObj.FilterSortByRatio();
	CXMatchObjectRatio *pRatio = (CXMatchObjectRatio*)oXMatchObj.m_listMacthObjectRatio.GetHead();
	CXIecDs_Group_ABC *pRet = NULL;
	
	if (pRatio != NULL)
	{
		pRet = (CXIecDs_Group_ABC*)pRatio->m_pRefObject;
	}

	return pRet;
}

