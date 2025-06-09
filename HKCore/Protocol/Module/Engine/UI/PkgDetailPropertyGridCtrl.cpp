// PkgDetailPropertyGridCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PkgDetailPropertyGridCtrl.h"
#include "..\..\XLanguageResourcePp.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPkgDetailPropertyGridCtrl

IMPLEMENT_DYNAMIC(CPkgDetailPropertyGridCtrl, CMFCPropertyGridCtrl)

CPkgDetailPropertyGridCtrl::CPkgDetailPropertyGridCtrl()
{

}

CPkgDetailPropertyGridCtrl::~CPkgDetailPropertyGridCtrl()
{
}


BEGIN_MESSAGE_MAP(CPkgDetailPropertyGridCtrl, CMFCPropertyGridCtrl)
END_MESSAGE_MAP()



// CPkgDetailPropertyGridCtrl ��Ϣ�������


void CPkgDetailPropertyGridCtrl::ShowPkgDetail(CPpPackageDetail *pPkg)
{
	if (pPkg == NULL)
	{
		RemoveAll();
		Invalidate(TRUE);
		return;
	}

	POS pos = pPkg->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	PROPGRIDITEMPARENT oPropGridItemParent;
	InitPropGridItemParent(oPropGridItemParent);
	oPropGridItemParent.pGrid = this;
	ShowExBaseList(pPkg, &oPropGridItemParent, TRUE);
}

void CPkgDetailPropertyGridCtrl::OnChangeSelection(CMFCPropertyGridProperty* pNewSel, CMFCPropertyGridProperty* pOldSel)
{
	GetParent()->SendMessage(WM_PP_PROP_SELCHANGED, (WPARAM)pNewSel, (LPARAM)pOldSel);
	//TRACE(_T("CPkgDetailPropertyGridCtrl::OnChangeSelection"));
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowExBaseList(CExBaseList *pList, PPROPGRIDITEMPARENT pParent, BOOL bShowVariablesNode)
{
	CMFCPropertyGridProperty *pNew = NULL;

	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case PPCLASSID_BBVARIABLES:
			ShowVariables((CBbVariables*)p, pParent, bShowVariablesNode);
			break;
		case PPCLASSID_BBVARIABLE:
			ShowVariable((CBbVariable*)p, pParent);
			break;

// 		case PPCLASSID_RBBDATASETS:
// 			ShowDataSets((CRBbDataSets*)p, pParent);
// 			break;
// 		case PPCLASSID_RBBDATASET:
// 			ShowDataSet((CRBbDataSet*)p, pParent);
// 			break;

		case PPCLASSID_BYTEBLOCK:
			ShowByteBlock((CByteBlock*)p, pParent);
			break;
		case PPCLASSID_RBYTEBLOCK:
			ShowRByteBlock((CRByteBlock*)p, pParent);
			break;
		case PPCLASSID_WBYTEBLOCK:
			ShowWByteBlock((CWByteBlock*)p, pParent);
			break;

		case PPCLASSID_BBDATA:
			ShowData((CBbData*)p, pParent);
			break;
		case PPCLASSID_RBBDATA:
			ShowRData((CRBbData*)p, pParent);
			break;
		case PPCLASSID_WBBDATA:
			ShowWData((CWBbData*)p, pParent);
			break;

		case PPCLASSID_DATABYTEBLOCK:
			ShowDataBlock((CDataByteBlock*)p, pParent);
			break;
		case PPCLASSID_RDATABYTEBLOCK:
			ShowRDataBlock((CRDataByteBlock*)p, pParent);
			break;
		case PPCLASSID_WDATABYTEBLOCK:
			ShowWDataBlock((CWDataByteBlock*)p, pParent);
			break;

		default:
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("%s : %s : %d"), p->m_strName, p->m_strID, nClassID);
			break;
		}
	}

	return pNew;
}

//	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("��ά���"), (_variant_t) false, _T("ָ�����ڵ����岻ʹ�ô��壬���ҿؼ���ʹ����ά�߿�")));

//CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("�߿�"), _T("Dialog Frame"), _T("����֮һ: ��(None)��ϸ(Thin)���ɵ�����С(Resizable)���Ի������(Dialog Frame)"));
CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowRByteBlock(CRByteBlock *pByteBlock, PPROPGRIDITEMPARENT pParent)
{
	return ShowByteBlock(pByteBlock, pParent);
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowWByteBlock(CWByteBlock *pByteBlock, PPROPGRIDITEMPARENT pParent)
{
	return ShowByteBlock(pByteBlock, pParent);
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowByteBlock(CByteBlock *pByteBlock, PPROPGRIDITEMPARENT pParent)
{
	CString strMsg;
	CString strAttr;
	long nLength = pByteBlock->GetByteBlockLength2();
	BYTE *pBuffer = pByteBlock->m_pBuffer;
	
	strMsg.Format(/*_T("%s(%s): %s, %d�ֽ�")*/g_sLangTxt_Byte , pByteBlock->m_strName, pByteBlock->m_strID, pByteBlock->m_strDataType, pByteBlock->GetByteBlockLength2());
	CMFCPropertyGridProperty *pGroup = new CMFCPropertyGridProperty(pByteBlock->m_strName);

	CMFCPropertyGridProperty *pAttr = new CMFCPropertyGridProperty(/*_T("����")*/g_sLangTxt_Type, pByteBlock->m_strDataType);
	pGroup->AddSubItem(pAttr);
	pAttr->AllowEdit(FALSE);
	strAttr.Format(_T("%d"), nLength);
	pAttr = new CMFCPropertyGridProperty(/*_T("����")*/g_sLangTxt_Length, strAttr);
	pAttr->AllowEdit(FALSE);
	pGroup->AddSubItem(pAttr);

	strAttr.Empty();

	for (long nIndex=0; nIndex<nLength; nIndex++)
	{
		strAttr.AppendFormat(_T("%02X "), pBuffer[nIndex]);
	}

	pAttr = new CMFCPropertyGridProperty(/*_T("����")*/g_sLangTxt_Msg , strAttr);
	pAttr->AllowEdit(FALSE);
	pGroup->AddSubItem(pAttr);

	PROPGRIDITEMPARENT oParent;
	InitPropGridItemParent(oParent);
	oParent.pProperty = pGroup;
	ShowVariables(pByteBlock->m_pVariables, &oParent, TRUE);
	pGroup->Expand(FALSE);

	pGroup->SetData((DWORD)pByteBlock);
	AddItem(pParent, pGroup);
	
	return pGroup;
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowVariable(CBbVariable *pVariable, PPROPGRIDITEMPARENT pParent)
{
	CString strMsg;
	strMsg.Format(/*_T("%s(%s): ��������=%s   ��ֵ=%s")*/g_sLangTxt_DataTypeValue, pVariable->m_strName, pVariable->m_strID, pVariable->m_strType, pVariable->m_strValue);

	CMFCPropertyGridProperty *pNew = new CMFCPropertyGridProperty(pVariable->m_strName, pVariable->m_strValue, strMsg, (DWORD)pVariable);
	AddItem(pParent, pNew);

	return pNew;
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowVariables(CBbVariables *pVariables, PPROPGRIDITEMPARENT pParent, BOOL bNewNode)
{
	if (pVariables == NULL)
	{
		return NULL;
	}

	if (pVariables->GetCount() == 0)
	{
		return NULL;
	}

	PPROPGRIDITEMPARENT pItemVariabels = pParent;
	PROPGRIDITEMPARENT oItemVariables;

	if (bNewNode)
	{
		CMFCPropertyGridProperty *pNew = new CMFCPropertyGridProperty(/*_T("��������")*/g_sLangTxt_FrameVariDefin2 );
		pNew->SetData((DWORD)pVariables);
		AddItem(pParent, pNew);
		InitPropGridItemParent(oItemVariables);
		oItemVariables.pProperty = pNew;
		pItemVariabels = &oItemVariables;
	}

	POS pos = pVariables->GetHeadPosition();
	CBbVariable *pVariable = NULL;

	while (pos != NULL)
	{
		pVariable = (CBbVariable *)pVariables->GetNext(pos);
		ShowVariable(pVariable, pItemVariabels);
	}

	return NULL;
}

// CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowDataSets(CRBbDataSets *pDataSets, PPROPGRIDITEMPARENT pParent)
// {
// 	CMFCPropertyGridProperty *pNew = NULL;
// 	ASSERT (FALSE);
// 	return pNew;
// }
// 
// CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowDataSet(CRBbDataSet *pDataSet, PPROPGRIDITEMPARENT pParent)
// {
// 	CMFCPropertyGridProperty *pNew = NULL;
// 	ASSERT (FALSE);
// 	return pNew;
// }

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowData(CBbData *pData, PPROPGRIDITEMPARENT pParent)
{
	CMFCPropertyGridProperty *pDataGroup = new CMFCPropertyGridProperty(pData->m_strName);

	PROPGRIDITEMPARENT oParent;
	InitPropGridItemParent(oParent);
	oParent.pProperty = pDataGroup;
	
	ShowExBaseList(pData, &oParent, FALSE);
	
	pDataGroup->SetData((DWORD)pData);
	pDataGroup->Expand(TRUE);
	AddItem(pParent, pDataGroup);

	return pDataGroup;
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowRData(CRBbData *pData, PPROPGRIDITEMPARENT pParent)
{
	return ShowData(pData, pParent);
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowWData(CWBbData *pData, PPROPGRIDITEMPARENT pParent)
{
	return ShowData(pData, pParent);
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowDataBlock(CDataByteBlock *pDataBlock, PPROPGRIDITEMPARENT pParent)
{
	return ShowByteBlock(pDataBlock, pParent);
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowRDataBlock(CRDataByteBlock *pDataBlock, PPROPGRIDITEMPARENT pParent)
{
	return ShowDataBlock(pDataBlock, pParent);
}

CMFCPropertyGridProperty* CPkgDetailPropertyGridCtrl::ShowWDataBlock(CWDataByteBlock *pDataBlock, PPROPGRIDITEMPARENT pParent)
{
	return ShowDataBlock(pDataBlock, pParent);
}

//////////////////////////////////////////////////////////////////////////
//
CExBaseObject* Pp_GetRefPpData(CMFCPropertyGridProperty *pCurr)
{
	if (pCurr == NULL)
	{
		return NULL;
	}

	CMFCPropertyGridProperty *pPropParent = pCurr;
	CExBaseObject *pData = NULL;

	while (pPropParent != NULL)
	{
		pData = (CExBaseObject *)pPropParent->GetData();

		if (pData != NULL)
		{
			break;
		}

		pPropParent = pPropParent->GetParent();
	}
	
	return pData;
}

