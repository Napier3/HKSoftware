#include "stdafx.h"
#include "GbOptimizeTool.h"
#include "..\XLanguageResourceAts.h"
#define GBOPTIMIZE_ITEM_GROUP_FLAG  0X00F0F0F0
//////////////////////////////////////////////////////////////////////////
CGbOptimizeTool::CGbOptimizeTool()
{
	m_pParentWnd = NULL;
	m_pOptimizeThread = NULL;
	
	m_bOptmizeDeviceAll    = TRUE;
	m_bOptimizeCommCmd     = TRUE;
	m_bOptimizeSysParaEdit = TRUE;
	m_bOptimizeIecConfig   = TRUE;

}

void CGbOptimizeTool::SetParentWnd(CWnd *pWnd)
{	
	m_pParentWnd = pWnd;
	CGbOptimizeThread *pThread = CGbOptimizeThread::CreateTestCtrlThread(m_pParentWnd);
	m_pThreadProgress = pThread;
	m_pOptimizeThread = pThread;
}


CGbOptimizeTool::~CGbOptimizeTool()
{
	m_pOptimizeThread->PostThreadMessage(WM_QUIT, 0, 0);
	m_listAftItems.RemoveAll();
	m_listBftItems.RemoveAll();
	m_listIecConfig.RemoveAll();
	m_listSysParaEdit.RemoveAll();
}

void CGbOptimizeTool::Optimize(CExBaseList *pItems)
{
	long nBack = g_nCloneReportMapInCopy;
	g_nCloneReportMapInCopy = 1;

	CExBaseList oListItems;
	GetAllLevel1Items(pItems, oListItems);
	POS pos = oListItems.GetHeadPosition();
	CExBaseList *pCurrItems = NULL;
	long nCount = oListItems.GetCount();
	long nIndex = 1;

	while (pos != NULL)
	{
		pCurrItems = (CExBaseList *)oListItems.GetNext(pos);
		Optimize_Level(pCurrItems, nCount, nIndex);
		nIndex++;
	}

	g_nCloneReportMapInCopy = nBack;
	oListItems.RemoveAll();
}

void CGbOptimizeTool::Optimize_Level(CExBaseList *pItems, long nCount, long nIndex)
{
	m_listAftItems.RemoveAll();
	m_listBftItems.RemoveAll();
	m_listIecConfig.RemoveAll();
	m_listSysParaEdit.RemoveAll();
	m_listBftGroup.DeleteAll();
	m_listAftGroup.DeleteAll();
	m_listIecCfgGroup.DeleteAll();
	m_listSysParaEditGroup.DeleteAll();

	CString strTitle;
	CString strName = pItems->GetNamePathEx(GBCLASSID_DEVICE);
	strTitle.Format(_T("��%d - %d��%s"), nCount, nIndex, strName);
	m_pThreadProgress->SetTitle(strTitle);

	m_pThreadProgress->SetMaxRange(7);
	m_pThreadProgress->ShowMsg(/*_T("7-1����ʼ���Ż���Ŀ����............")*/g_sLangTxt_InitOptimizeList);
	
	
	if (m_bOptimizeCommCmd)
	{
		GetAllBftAftItems(pItems);
	}

	if (m_bOptimizeIecConfig)
	{
		GetAllIecItems(pItems);
	}

	if (m_bOptimizeSysParaEdit)
	{
		GetAllSysParaEditItems(pItems);
	}

	if (m_bOptimizeCommCmd)
	{
		m_pThreadProgress->ShowMsg(/*_T("7-2����ʼ������ǰ����׼����Ŀ����............")*/g_sLangTxt_InitPreTestList);
		BuildGroup(m_listBftItems, m_listBftGroup);
		m_pThreadProgress->ShowMsg(/*_T("7-3����ʼ������ָ���Ŀ����............")*/g_sLangTxt_InitTestRecoverList);
		BuildGroup(m_listAftItems, m_listAftGroup);

		m_pThreadProgress->ShowMsg(/*_T("7-4���Ż�����ǰ����׼����Ŀ............")*/g_sLangTxt_OptimizePreTestItem);
		OptimizeBfT();
		m_pThreadProgress->ShowMsg(/*_T("7-5���Ż�����ָ���Ŀ............")*/g_sLangTxt_OptimizeTestRecoverItem);
		OptimizeAfT();
	}

	if (m_bOptimizeIecConfig)
	{
		//�Ż�IEC61850����
		m_pThreadProgress->ShowMsg(/*_T("7-6���Ż�IEC61850��������............")*/g_sLangTxt_OptimizeIecCfgDownload);
		BuildIecGroup();
		OptimizeIECConfig();
	}

	//�Ż�IEC61850����
	if (m_bOptimizeSysParaEdit)
	{
		m_pThreadProgress->ShowMsg(/*_T("7-7���Ż�ϵͳ�����༭��Ŀ............")*/g_sLangTxt_OptimizeSysParaEditItem);
		BuildSysParaEditGroup();
		OptimizeSysParaEdit();
	}
}

void CGbOptimizeTool::GetAllLevel1Items(CExBaseList *pItems, CExBaseList &oListItems)
{
	if (pItems->GetClassID() != GBCLASSID_DEVICE)
	{
		oListItems.AddTail(pItems);
		return;
	}

	if (m_bOptmizeDeviceAll)
	{
		oListItems.AddTail(pItems);
		return;
	}

	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_ITEMS)
		{
			if (IsItemsHasItems((CExBaseList*)p))
			{
				oListItems.AddTail(p);
			}
		}
	}
}

BOOL CGbOptimizeTool::IsItemsHasItems(CExBaseList *pItems)
{
	if (pItems->GetClassID() != GBCLASSID_ITEMS)
	{
		return FALSE;
	}

	BOOL bHas = FALSE;
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)pItems->GetNext(pos);

		if (p->GetClassID() == GBCLASSID_ITEMS)
		{
			bHas = TRUE;
			break;
		}
	}

	return bHas;
}

void CGbOptimizeTool::GetAllBftAftItems(CExBaseList *pItems)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pTemp = NULL;

	while (pos != NULL)
	{
		pTemp = (CExBaseObject *)pItems->GetNext(pos);

		if (pTemp->GetClassID() == GBCLASSID_ITEMS )
		{
			if (pTemp->m_strID.Find(GBID_BeforeTest_) >= 0)
			{
				m_listBftItems.AddTail(pTemp);
			}
			else if (pTemp->m_strID.Find(GBID_AfterTest_) >= 0)
			{
				m_listAftItems.AddTail(pTemp);
			}
			else
			{
				GetAllBftAftItems((CExBaseList*)pTemp);
			}
		}
	}
}

BOOL CGbOptimizeTool::CanBuildGroup(CExBaseObject *pItem)
{
	//�Ѿ���ƥ��
	if (pItem->m_dwReserved == GBOPTIMIZE_ITEM_GROUP_FLAG)
	{
		return FALSE;
	}

	//ͨѶ����
	if (pItem->GetClassID() == GBCLASSID_COMMCMD )
	{
		CString strID = pItem->m_strID;
		strID.MakeLower();

		//��λ�������
		if (strID == g_strReset)
		{
			return FALSE;
		}

		return TRUE;
	}

	//���Թ���
// 	if (pItem->GetClassID() == GBCLASSID_MACROTEST)
// 	{
// 		CMacroTest *pMacroTest = (CMacroTest*)pItem;
// 
// 		if (pMacroTest->GetMacroTestPara()->GetMacroID() == _T("IECConfig"))
// 		{
// 			return TRUE;
// 		}
// 
// 		return FALSE;
// 	}

	return FALSE;
}

//oListItems��BfT/AfT��Ŀ�����б�
//oListGroup�����������������ɹ���ͨѶ����
//����oListItems�����з��飬������̣���ǰ��Ŀ����֮�����Ŀ�Ƚϣ��ҵ���ͬ�ģ���ӷ���
//		����һ����Ŀ���࣬û����ͬ�ģ���ǰ��Ŀ��������
void CGbOptimizeTool::BuildGroup(CExBaseList &oListItems, CExBaseList &oListGroup)
{
	m_pThreadProgress->SetMaxRange(oListItems.GetCount());
	POS pos = oListItems.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = oListItems.GetNext(pos);
		BuildGroup(oListItems, pos, (CExBaseList*)p, oListGroup);
		m_pThreadProgress->StepIt();
	}
}

//oListItems��BfT/AfT��Ŀ�����б�
//posItemsFrom����ʲôλ�ÿ�ʼ�жϽ��з���
//pCurrItems����ǰ����Ŀ����
//oListGroup�����������������ɹ���ͨѶ����
//���̣�������ǰ��Ŀ�����µ�ÿһ����Ŀ���Ӻ�������Ŀ�����в�����ͬ��Cmd���з���
void CGbOptimizeTool::BuildGroup(CExBaseList &oListItems, POS posItemsFrom, CExBaseList *pCurrItems, CExBaseList &oListGroup)
{
	if (posItemsFrom == NULL)
	{
		return;
	}

	POS pos = pCurrItems->GetHeadPosition();
	CExBaseObject *pCmd = NULL;

	while (pos != NULL)
	{
		pCmd = (CExBaseObject *)pCurrItems->GetNext(pos);

		if (pCmd->GetClassID() == GBCLASSID_COMMCMD && pCmd->m_dwReserved != GBOPTIMIZE_ITEM_GROUP_FLAG)
		{
			BuildGroup(oListItems, posItemsFrom, pCmd, oListGroup);
		}
	}
}

//oListItems��BfT/AfT��Ŀ�����б�
//posItemsFrom����ʲôλ�ÿ�ʼ�жϽ��з���
//pCurrCmd����ǰ��ͨѶ������Ŀ
//oListGroup�����������������ɹ���ͨѶ����
//���̣���posItemsFrom��ʼ����oListItems����Ŀ���࣬���з���
void CGbOptimizeTool::BuildGroup(CExBaseList &oListItems, POS posItemsFrom, CExBaseObject *pCurrCmd, CExBaseList &oListGroup)
{
	if (posItemsFrom == NULL)
	{
		return;
	}

	CExBaseList *pDestItems = NULL;
	long nCount = 0;
	CExBaseList oListCmd;

	do
	{
		pDestItems = (CExBaseList*)oListItems.GetAt(posItemsFrom);
		nCount = BuildGroup(pDestItems, pCurrCmd, oListCmd);

		if (nCount == 0)
		{//���ĳһ����Ŀ��������û��һ����ͬ��ͨѶ�����������
			break;
		}

		oListItems.GetNext(posItemsFrom);
	}while (posItemsFrom != NULL);

	//���oListCmd�е���Ŀ��������0���򴴽�����
	if (oListCmd.GetCount() > 0)
	{
		CGbOptmItemGroup *pNewGroup = new CGbOptmItemGroup();
		oListGroup.AddTail(pNewGroup);
		pNewGroup->AddTail(pCurrCmd);
		pCurrCmd->m_dwReserved = GBOPTIMIZE_ITEM_GROUP_FLAG;
		pNewGroup->Append(oListCmd);
	}

	oListCmd.RemoveAll();
}

//pDestItems����Ҫƥ�����Ŀ����
//pCurrCmd����ǰ��ͨѶ������Ŀ
//oListCmd������ƥ��ɹ���ͨѶ������Ŀ
//���̣�����pDestItems�µ�ÿһ����ĿCmd������ƥ��Ƚϣ��ɹ�����ӵ�oListCmd
long CGbOptimizeTool::BuildGroup(CExBaseList *pDestItems, CExBaseObject *pCurrCmd, CExBaseList &oListCmd)
{
	long nCount = 0;
	POS pos = pDestItems->GetHeadPosition();
	CExBaseObject *pDestCmd = NULL;

	while (pos != NULL)
	{
		pDestCmd = (CExBaseObject *)pDestItems->GetNext(pos);

		if (pDestCmd->GetClassID() == GBCLASSID_COMMCMD && pDestCmd->m_dwReserved != GBOPTIMIZE_ITEM_GROUP_FLAG)
		{
			nCount += BuildGroup((CCommCmd*)pDestCmd, (CCommCmd*)pCurrCmd, oListCmd);

			if (nCount > 0)
			{//������һ����Ŀ������������ͬ��ͨѶ�����������
				oListCmd.AddTail(pDestCmd);
				pDestCmd->m_dwReserved = GBOPTIMIZE_ITEM_GROUP_FLAG;
				break;
			}
		}
	}

	return nCount;
}

//pIemDest�����Ƚϵ���Ŀ
//pCurrCmd����ǰ��ͨѶ������Ŀ
//oListCmd������ƥ��ɹ���ͨѶ������Ŀ
//�Ƚ�pIemDest��pCurrCmd�Ƿ���ͬ
long CGbOptimizeTool::BuildGroup(CCommCmd *pIemDest, CCommCmd *pCurrCmd, CExBaseList &oListCmd)
{
	if (pCurrCmd->m_strCommCmdID != pIemDest->m_strCommCmdID)
	{
		return 0;
	}

	CCmd *pDest = pIemDest->GetCmd();
	CCmd *pSrc  = pCurrCmd->GetCmd();

	if (pDest->m_strDatasetPath != pSrc->m_strDatasetPath)
	{
		return 0;
	}

	if (pDest->GetCount() != pSrc->GetCount())
	{
		return 0;
	}

	POS pos = pDest->GetHeadPosition();
	CValue *pValue = NULL;
	CValue *pFind = NULL;

	while (pos != NULL)
	{
		pValue = (CValue *)pDest->GetNext(pos);
		pFind = (CValue *)pSrc->FindByID(pValue->m_strID);

		if (pFind == NULL)
		{
			return 0;
		}

		if (pFind->m_strValue != pValue->m_strValue)
		{
			return 0;
		}
	}

	return 1;
}

//�Ż�
CExBaseList* CGbOptimizeTool::GetGroupAncestor(CGbOptmItemGroup *pGroup)
{
	POS pos = NULL;
	CExBaseList *pAncestorFind = NULL;
	CExBaseObject *pAncestor = NULL;
	CExBaseObject *pTemp = NULL;
	long nDepth = 0;
	CExBaseObject *pItem = NULL;

	pItem = pGroup->GetHead();
	pAncestorFind = (CExBaseList*)pItem->GetAncestor(GBCLASSID_DEVICE);
	BOOL bTrue = TRUE;

	while (TRUE)
	{
		pos = pGroup->GetHeadPosition();
		pItem = pGroup->GetNext(pos);
		pAncestor = GetAncestorByDepth(pItem, nDepth);
		bTrue = TRUE;

		while (pos != NULL)
		{
			pItem = pGroup->GetNext(pos);
			pTemp = GetAncestorByDepth(pItem, nDepth);

			if (pTemp != pAncestor)
			{
				bTrue = FALSE;
				break;
			}
		}

		if (bTrue)
		{
			pAncestorFind = (CExBaseList*)pAncestor;
		}
		else
		{
			break;
		}

		nDepth++;
	}

	return pAncestorFind;
}

CExBaseList* CGbOptimizeTool::GetSecondAncestor(CExBaseObject *pItem, CExBaseObject *pFirstAncestor)
{
	CExBaseList oList;
	pItem->GetAllAncestor(&oList, GBCLASSID_DEVICE);
	POS pos = oList.Find(pFirstAncestor);
	oList.GetNext(pos);
	CExBaseList *pAncestor = NULL;

	if (pos == NULL)
	{
		pAncestor = (CExBaseList*)oList.GetHead();
	}
	else
	{
		pAncestor = (CExBaseList*)oList.GetAt(pos);
	}

	oList.RemoveAll();

	return pAncestor;
}

CExBaseList* CGbOptimizeTool::GetAncestorByDepth(CExBaseObject *pItem, long nIndex)
{
	CExBaseList oList;
	pItem->GetAllAncestor(&oList, GBCLASSID_DEVICE);
	CExBaseList *pAncestor = (CExBaseList*)oList.GetAt(nIndex);
	oList.RemoveAll();

	return pAncestor;
}

//�Ż�����ǰ׼��
void CGbOptimizeTool::OptimizeBfT()
{
	m_pThreadProgress->SetMaxRange(m_listBftGroup.GetCount());

	POS pos = m_listBftGroup.GetHeadPosition();
	CGbOptmItemGroup *pGroup = NULL;
	long nIndex = 1;
	CString strIndex;

	while (pos != NULL)
	{
// 		if (nIndex == 35)
// 		{
// 			nIndex = 35;
// 		}
// 		strIndex.Format(_T("%d"), nIndex);
// 		m_pThreadProgress->ShowMsg(strIndex);
		pGroup = (CGbOptmItemGroup *)m_listBftGroup.GetNext(pos);
		OptimizeBfT(pGroup);
		m_pThreadProgress->StepIt();
		Sleep(10);
// 		nIndex++;
	}
}

void CGbOptimizeTool::OptimizeCombine(CGbOptmItemGroup *pGroup, CExBaseList *pNewItems)
{
	POS pos = pGroup->GetHeadPosition();
	CExBaseObject *pItem = pGroup->GetHead();
	CExBaseObject *pNew  = (CExBaseObject*)pItem->Clone();
	pNewItems->AddNewChild(pNew);
	pGroup->GetNext(pos);

	//�����Ŀ�ı���ӳ��
	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pGroup->GetNext(pos);
		OptimizeCombine((CCommCmd*)pNew, (CCommCmd*)pItem);
	}

	//ɾ��ԭ����ͨѶ������Ŀ
	pos = pGroup->GetHeadPosition();
	CExBaseList *pParent = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pGroup->GetNext(pos);
		pParent = (CExBaseList *)pItem->GetParent();
		pParent->Delete(pItem);
	}

	pGroup->RemoveAll();
}


void CGbOptimizeTool::OptimizeBfT(CGbOptmItemGroup *pGroup)
{
	CExBaseList *pAncestor = GetGroupAncestor(pGroup);
	CExBaseObject *pItem = pGroup->GetHead();
	CExBaseList *pSecondAncestor = GetSecondAncestor(pItem, pAncestor);

	ASSERT(pAncestor != NULL);
	ASSERT(pSecondAncestor != NULL);

	if (pAncestor == NULL || pSecondAncestor == NULL)
	{
		return;
	}
	
	//������Ϻ����Ŀ����
	CExBaseList *pNewItems = CreateBfTItems(pAncestor, pSecondAncestor);
	OptimizeCombine(pGroup, pNewItems);
}

void CGbOptimizeTool::OptimizeCombine(CCommCmd *pDestIem, CCommCmd *pSrcItem)
{
	CReportMap *pRptMapDest = pDestIem->GetReportMap();
	CReportMap *pRptMapSrc  = pSrcItem->GetReportMap();

	OptimizeCombineRptMap(pRptMapDest, pRptMapSrc);
	
}

void CGbOptimizeTool::OptimizeCombineRptMap(CExBaseList *pDestRptMap, CExBaseList *pSrcRptMap)
{
	POS pos = pSrcRptMap->GetHeadPosition();
	CExBaseObject *pTemp = NULL;


	while (pos != NULL)
	{
		pTemp = (CExBaseObject *)pSrcRptMap->GetNext(pos);

		if (pTemp->GetClassID() == RPTCLASSID_RPTDATA)
		{
			CRptData *pRptData = (CRptData*)pTemp;
			CRptData *pRptDataFind = (CRptData*)pDestRptMap->FindByID(pRptData->m_strID);

			if (pRptDataFind == NULL)
			{
				pRptDataFind = (CRptData*)pRptData->Clone();
				pDestRptMap->AddNewChild(pRptDataFind);
			}
			else
			{
				pRptDataFind->AppendCloneEx(*((CExBaseList*)pRptData));
			}
		}
		else if (pTemp->GetClassID() == RPTCLASSID_RPTMAPREPEAT)
		{
			CRptMapRepeat *pRepeat = (CRptMapRepeat*)pTemp;
			CRptMapRepeat *pRepeatFind = (CRptMapRepeat*)pDestRptMap->FindByID(pRepeat->m_strID);

			if (pRepeatFind == NULL)
			{
				pRepeatFind = (CRptMapRepeat*)pRepeat->Clone();
				pDestRptMap->AddNewChild(pRepeatFind);
			}
			else
			{
				OptimizeCombineRptMap(pRepeatFind, pRepeat);
			}
		}
	}
}

//��һ����Ŀ��SeceondAncestor�������������_BeforeTest_��Ŀ����ʱ�������������
CExBaseList* CGbOptimizeTool::CreateBfTItems(CExBaseList *pFirstAncestor, CExBaseList *pSecondAncestor)
{
	POS pos = pFirstAncestor->Find(pSecondAncestor);
	POS posCurr = pos;
	ASSERT (pos != NULL);

	//���ң�pSecondAncestor֮ǰ�Ƿ��С�����ǰ׼������Ŀ
	CExBaseList *pFind = NULL;
	CExBaseObject *p = NULL;
	pFirstAncestor->GetPrev(pos);

	while (pos != NULL)
	{
		p = pFirstAncestor->GetAt(pos);

		if (p->m_strID.Find(GBID_BeforeTest_) >= 0)
		{
			pFind = (CExBaseList*)p;
			break;
		}

		//֮ǰ�Ķ���ֻҪ����Ŀ�����˳�
		if (Gb_IsItemBaseClassID(p->GetClassID()))
		{
			break;
		}

		pFirstAncestor->GetPrev(pos);
	}

	if (pFind != NULL)
	{
		return pFind;
	}

	//��������ǰ׼����Ŀ
	pFind = new CItems();
	long nIndex = 1;
	pFind->m_strName = GBNAME_BeforeTest_;
	pFind->m_strID = GBID_BeforeTest_;
	
	while (TRUE)
	{
		if (pFirstAncestor->FindByName(pFind->m_strName) == NULL)
		{
			break;
		}

		pFind->m_strName.Format(_T("%s%d"), GBNAME_BeforeTest_, nIndex);
		nIndex++;
	}

	nIndex = 1;

	while (TRUE)
	{
		if (pFirstAncestor->FindByID(pFind->m_strID) == NULL)
		{
			break;
		}

		pFind->m_strID.Format(_T("%s%d"), GBID_BeforeTest_, nIndex);
		nIndex++;
	}

	pFind->SetParent(pFirstAncestor);
	pFirstAncestor->InsertBefore(posCurr, pFind);

	return pFind;
}



void CGbOptimizeTool::OptimizeAfT()
{
	m_pThreadProgress->SetMaxRange(m_listAftGroup.GetCount());
	POS pos = m_listAftGroup.GetHeadPosition();
	CGbOptmItemGroup *pGroup = NULL;
	long nIndex = 1;
	CString strIndex;

	while (pos != NULL)
	{
// 		if (nIndex == 54)
// 		{
// 			nIndex = 54;
// 		}
// 		strIndex.Format(_T("%d"), nIndex);
// 		m_pThreadProgress->ShowMsg(strIndex);
// 
		pGroup = (CGbOptmItemGroup *)m_listAftGroup.GetNext(pos);
		OptimizeAfT(pGroup);
		m_pThreadProgress->StepIt();
		Sleep(10);
// 		nIndex++;
	}
}

void CGbOptimizeTool::OptimizeAfT(CGbOptmItemGroup *pGroup)
{
	CExBaseList *pAncestor = GetGroupAncestor(pGroup);
	CExBaseObject *pItem = pGroup->GetTail();
	CExBaseList *pSecondAncestor = GetSecondAncestor(pItem, pAncestor);


	ASSERT(pAncestor != NULL);
	ASSERT(pSecondAncestor != NULL);

	if (pAncestor == NULL || pSecondAncestor == NULL)
	{
		return;
	}

	//������Ϻ����Ŀ����
	CExBaseList *pNewItems = CreateAfTItems(pAncestor, pSecondAncestor);
	OptimizeCombine(pGroup, pNewItems);
}

//���һ����Ŀ��SeceondAncestor�������������_AfterTest_��Ŀ����ʱ�������������
CExBaseList* CGbOptimizeTool::CreateAfTItems(CExBaseList *pFirstAncestor, CExBaseList *pSecondAncestor)
{
	POS pos = pFirstAncestor->Find(pSecondAncestor);
	POS posCurr = pos;
	ASSERT (pos != NULL);

	//���ң�pSecondAncestor֮ǰ�Ƿ��С�����ǰ׼������Ŀ
	CExBaseList *pFind = NULL;
	CExBaseObject *p = NULL;
	pFirstAncestor->GetNext(pos);

	while (pos != NULL)
	{
		p = pFirstAncestor->GetAt(pos);

		if (p->m_strID.Find(GBID_AfterTest_) >= 0)
		{
			pFind = (CExBaseList*)p;
			break;
		}

		//֮ǰ�Ķ���ֻҪ����Ŀ�����˳�
		if (Gb_IsItemBaseClassID(p->GetClassID()))
		{
			break;
		}

		pFirstAncestor->GetNext(pos);
	}

	if (pFind != NULL)
	{
		return pFind;
	}

	//��������ǰ׼����Ŀ
	pFind = new CItems();
	long nIndex = 1;
	pFind->m_strName = GBNAME_AfterTest_;
	pFind->m_strID = GBID_AfterTest_;

	while (TRUE)
	{
		if (pFirstAncestor->FindByName(pFind->m_strName) == NULL)
		{
			break;
		}

		pFind->m_strName.Format(_T("%s%d"), GBNAME_AfterTest_, nIndex);
		nIndex++;
	}

	nIndex = 1;

	while (TRUE)
	{
		if (pFirstAncestor->FindByID(pFind->m_strID) == NULL)
		{
			break;
		}

		pFind->m_strID.Format(_T("%s%d"), GBID_AfterTest_, nIndex);
		nIndex++;
	}

	pFind->SetParent(pFirstAncestor);
	pFirstAncestor->InsertAfter(posCurr, pFind);

	return pFind;
}

//////////////////////////////////////////////////////////////////////////
///IEC61850���õ��Ż�
void CGbOptimizeTool::OptimizeIECConfig()
{
	m_pThreadProgress->SetMaxRange(m_listIecCfgGroup.GetCount());
	POS pos = m_listIecCfgGroup.GetHeadPosition();
	CGbOptmItemGroup *pGroup = NULL;
	long nIndex = 1;
	CString strIndex;

	while (pos != NULL)
	{
		pGroup = (CGbOptmItemGroup *)m_listIecCfgGroup.GetNext(pos);
		OptimizeItemByGroup(pGroup);
		m_pThreadProgress->StepIt();
		Sleep(10);
	}
}

void CGbOptimizeTool::GetAllIecItems(CExBaseList *pItems)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pTemp = NULL;

	while (pos != NULL)
	{
		pTemp = (CExBaseObject *)pItems->GetNext(pos);

		if (pTemp->GetClassID() == GBCLASSID_MACROTEST )
		{
			CMacroTest *pMacroTest = (CMacroTest*)pTemp;

			if (pMacroTest->GetMacroTestPara()->GetMacroID() == CMtDataTypeMngr::g_strTestMacroID_IECConfig)
			{
				m_listIecConfig.AddTail(pTemp);
			}
		}
		else if (pTemp->GetClassID() == GBCLASSID_ITEMS)
		{
			GetAllIecItems((CExBaseList*)pTemp);
		}
	}
}

void CGbOptimizeTool::BuildIecGroup()
{
	m_pThreadProgress->SetMaxRange(m_listIecConfig.GetCount());
	POS pos = m_listIecConfig.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = m_listIecConfig.GetNext(pos);

		if (p->m_dwReserved == GBOPTIMIZE_ITEM_GROUP_FLAG)
		{
			continue;
		}

		BuildIecGroup(pos, (CExBaseList*)p);
		m_pThreadProgress->StepIt();
	}
}

void CGbOptimizeTool::BuildIecGroup(POS posItemsFrom, CExBaseObject *pCurrItem)
{
	if (posItemsFrom == NULL)
	{
		return;
	}

	CExBaseList *pDestItems = NULL;
	long nCount = 0;
	CExBaseList oListMacroTest;

	do
	{
		pDestItems = (CExBaseList*)m_listIecConfig.GetAt(posItemsFrom);
		nCount = BuildIecGroup((CMacroTest*)pDestItems, (CMacroTest*)pCurrItem, oListMacroTest);

		if (nCount == 0)
		{//���ĳһ����Ŀ��������û��һ����ͬ��ͨѶ�����������
			break;
		}

		m_listIecConfig.GetNext(posItemsFrom);
	}while (posItemsFrom != NULL);

	//���oListCmd�е���Ŀ��������0���򴴽�����
	if (oListMacroTest.GetCount() > 0)
	{
		CGbOptmItemGroup *pNewGroup = new CGbOptmItemGroup();
		m_listIecCfgGroup.AddTail(pNewGroup);
		pNewGroup->AddTail(pCurrItem);
		pCurrItem->m_dwReserved = GBOPTIMIZE_ITEM_GROUP_FLAG;
		pNewGroup->Append(oListMacroTest);
	}

	oListMacroTest.RemoveAll();
}

long CGbOptimizeTool::BuildIecGroup(CMacroTest *pIemDest, CMacroTest *pCurrItem, CExBaseList &oListMacroTest)
{
	CMacroTestPara *pParaDest = pIemDest->GetMacroTestPara();
	CMacroTestPara *pParaSrc  = pCurrItem->GetMacroTestPara();

	CMacroTestParaDatas *pFaultParaDest = pParaDest->GetFaultParaDatas();
	CMacroTestParaDatas *pFaultParaSrc  = pParaSrc->GetFaultParaDatas();

	if (pFaultParaSrc->GetCount() != pFaultParaDest->GetCount())
	{
		return 0;
	}

	CMacroTestParaData *pDataDest = NULL;
	CMacroTestParaData *pDataSrc  = NULL;
	POS pos = pFaultParaDest->GetHeadPosition();

	while (pos != NULL)
	{
		pDataDest = (CMacroTestParaData *)pFaultParaDest->GetNext(pos);
		pDataSrc = (CMacroTestParaData *)pFaultParaSrc->FindByID(pDataDest->m_strID);

		if (pDataSrc == NULL)
		{
			return 0;
		}

		if (pDataSrc->m_strExpression != pDataDest->m_strExpression)
		{
			return 0;
		}
	}

	oListMacroTest.AddTail(pIemDest);
 	pIemDest->m_dwReserved = GBOPTIMIZE_ITEM_GROUP_FLAG;

	return 1;
}


void CGbOptimizeTool::OptimizeItemByGroup(CGbOptmItemGroup *pGroup)
{
	CExBaseList *pFirstAncestor = GetGroupAncestor(pGroup);
	CExBaseObject *pItem = pGroup->GetHead();
	CExBaseList *pSecondAncestor = GetSecondAncestor(pItem, pFirstAncestor);


	ASSERT(pFirstAncestor != NULL);
	ASSERT(pSecondAncestor != NULL);

	if (pFirstAncestor == NULL || pSecondAncestor == NULL)
	{
		return;
	}

	//�µ���Ŀ
	POS pos = pFirstAncestor->Find(pSecondAncestor);
	POS posCurr = pos;

	//��������ǰ׼����Ŀ
	CGbItemBase *pNew = (CGbItemBase*)pItem->Clone();
	long nIndex = 1;
	CString strName = pNew->m_strName;
	CString strID   = pNew->m_strID;

	while (TRUE)
	{
		if (pFirstAncestor->FindByName(pNew->m_strName) == NULL)
		{
			break;
		}

		pNew->m_strName.Format(_T("%s%d"), strName, nIndex);
		nIndex++;
	}

	nIndex = 1;

	while (TRUE)
	{
		if (pFirstAncestor->FindByID(pNew->m_strID) == NULL)
		{
			break;
		}

		pNew->m_strID.Format(_T("%s%d"), strID, nIndex);
		nIndex++;
	}

	pNew->SetParent(pFirstAncestor);
	pFirstAncestor->InsertBefore(posCurr, pNew);

	//ɾ��ԭ������Ŀ
	pos = pGroup->GetHeadPosition();
	CExBaseList *pParent = NULL;

	while (pos != NULL)
	{
		pItem = (CExBaseObject *)pGroup->GetNext(pos);
		pParent = (CExBaseList *)pItem->GetParent();
		pParent->Delete(pItem);
	}

	pGroup->RemoveAll();
}


//////////////////////////////////////////////////////////////////////////
///CSysParaEdit���õ��Ż�
void CGbOptimizeTool::OptimizeSysParaEdit()
{
	m_pThreadProgress->SetMaxRange(m_listSysParaEditGroup.GetCount());
	POS pos = m_listSysParaEditGroup.GetHeadPosition();
	CGbOptmItemGroup *pGroup = NULL;
	long nIndex = 1;
	CString strIndex;

	while (pos != NULL)
	{
		pGroup = (CGbOptmItemGroup *)m_listSysParaEditGroup.GetNext(pos);
		OptimizeItemByGroup(pGroup);
		m_pThreadProgress->StepIt();
		Sleep(10);
	}
}

void CGbOptimizeTool::GetAllSysParaEditItems(CExBaseList *pItems)
{
	POS pos = pItems->GetHeadPosition();
	CExBaseObject *pTemp = NULL;

	while (pos != NULL)
	{
		pTemp = (CExBaseObject *)pItems->GetNext(pos);

		if (pTemp->GetClassID() == GBCLASSID_SYSPARAEDIT )
		{
			CSysParaEdit *pSysParaEdit = (CSysParaEdit*)pTemp;

			if (pSysParaEdit->m_strDatasetPath == g_strDeviceModel_SysPara)
			{
				m_listSysParaEdit.AddTail(pTemp);
			}
		}
		else if (pTemp->GetClassID() == GBCLASSID_ITEMS)
		{
			GetAllSysParaEditItems((CExBaseList*)pTemp);
		}
	}
}

void CGbOptimizeTool::BuildSysParaEditGroup()
{
	m_pThreadProgress->SetMaxRange(m_listSysParaEdit.GetCount());
	POS pos = m_listSysParaEdit.GetHeadPosition();
	CExBaseObject *p = NULL;

	while (pos != NULL)
	{
		p = m_listSysParaEdit.GetNext(pos);

		if (p->m_dwReserved == GBOPTIMIZE_ITEM_GROUP_FLAG)
		{
			continue;
		}

		BuildSysParaEditGroup(pos, (CExBaseList*)p);
		m_pThreadProgress->StepIt();
	}
}

void CGbOptimizeTool::BuildSysParaEditGroup(POS posItemsFrom, CExBaseObject *pCurrItem)
{
	if (posItemsFrom == NULL)
	{
		return;
	}

	CExBaseList *pDestItems = NULL;
	long nCount = 0;
	CExBaseList oListSysParaEdit;

	do
	{
		pDestItems = (CExBaseList*)m_listSysParaEdit.GetAt(posItemsFrom);
		nCount = BuildSysParaEditGroup((CSysParaEdit*)pDestItems, (CSysParaEdit*)pCurrItem, oListSysParaEdit);

		if (nCount == 0)
		{//���ĳһ����Ŀ��������û��һ����ͬ��ϵͳ�����༭����������
			break;
		}

		m_listSysParaEdit.GetNext(posItemsFrom);
	}while (posItemsFrom != NULL);

	//���oListCmd�е���Ŀ��������0���򴴽�����
	if (oListSysParaEdit.GetCount() > 0)
	{
		CGbOptmItemGroup *pNewGroup = new CGbOptmItemGroup();
		m_listSysParaEditGroup.AddTail(pNewGroup);
		pNewGroup->AddTail(pCurrItem);
		pCurrItem->m_dwReserved = GBOPTIMIZE_ITEM_GROUP_FLAG;
		pNewGroup->Append(oListSysParaEdit);
	}

	oListSysParaEdit.RemoveAll();
}

long CGbOptimizeTool::BuildSysParaEditGroup(CSysParaEdit *pIemDest, CSysParaEdit *pCurrItem, CExBaseList &oListMacroTest)
{
	if (pIemDest->m_strDatasetPath != pCurrItem->m_strDatasetPath)
	{
		return 0;
	}

	CValues *pDestValues = pIemDest->GetParas();
	CValues *pCurrValues = pCurrItem->GetParas();

	if (pDestValues->GetCount() != pCurrValues->GetCount())
	{
		return 0;
	}

	POS pos = pDestValues->GetHeadPosition();

	while (pos != NULL)
	{
		CValue *pDataDest = (CValue *)pDestValues->GetNext(pos);
		CValue *pDataSrc  = (CValue *)pCurrValues->FindByID(pDataDest->m_strID);

		if (pDataSrc == NULL)
		{
			return 0;
		}

		if (pDataSrc->m_strValue != pDataDest->m_strValue)
		{
			return 0;
		}
	}

	oListMacroTest.AddTail(pIemDest);
	pIemDest->m_dwReserved = GBOPTIMIZE_ITEM_GROUP_FLAG;

	return 1;
}
// 
// 
// void CGbOptimizeTool::OptimizeSysParaEdit(CGbOptmItemGroup *pGroup)
// {
// 	CExBaseList *pFirstAncestor = GetGroupAncestor(pGroup);
// 	CExBaseObject *pItem = pGroup->GetHead();
// 	CExBaseList *pSecondAncestor = GetSecondAncestor(pItem, pFirstAncestor);
// 
// 
// 	ASSERT(pFirstAncestor != NULL);
// 	ASSERT(pSecondAncestor != NULL);
// 
// 	if (pFirstAncestor == NULL || pSecondAncestor == NULL)
// 	{
// 		return;
// 	}
// 
// 	//�µ���Ŀ
// 	POS pos = pFirstAncestor->Find(pSecondAncestor);
// 	POS posCurr = pos;
// 
// 	//��������ǰ׼����Ŀ
// 	CSysParaEdit *pNew = (CSysParaEdit*)pItem->Clone();
// 	long nIndex = 1;
// 	CString strName = pNew->m_strName;
// 	CString strID   = pNew->m_strID;
// 
// 	while (TRUE)
// 	{
// 		if (pFirstAncestor->FindByName(pNew->m_strName) == NULL)
// 		{
// 			break;
// 		}
// 
// 		pNew->m_strName.Format(_T("%s%d"), strName, nIndex);
// 		nIndex++;
// 	}
// 
// 	nIndex = 1;
// 
// 	while (TRUE)
// 	{
// 		if (pFirstAncestor->FindByID(pNew->m_strID) == NULL)
// 		{
// 			break;
// 		}
// 
// 		pNew->m_strID.Format(_T("%s%d"), strID, nIndex);
// 		nIndex++;
// 	}
// 
// 	pNew->SetParent(pFirstAncestor);
// 	pFirstAncestor->InsertBefore(posCurr, pNew);
// 
// 	//ɾ��ԭ������Ŀ
// 	pos = pGroup->GetHeadPosition();
// 	CExBaseList *pParent = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pItem = (CExBaseObject *)pGroup->GetNext(pos);
// 		pParent = (CExBaseList *)pItem->GetParent();
// 		pParent->Delete(pItem);
// 	}
// 
// 	pGroup->RemoveAll();
// }
// 

UINT CGbOptimizeTool::ExecOptimizeThread(LPVOID pParam)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////
//

IMPLEMENT_DYNCREATE(CGbOptimizeThread, CWinThread)

CGbOptimizeThread::CGbOptimizeThread()
{
	m_pProgressDlg = NULL;
	memset(m_pszMessage, 0, 4096);
	m_nMaxRange = 100;
	m_pParentWnd = NULL;
}


CGbOptimizeThread::~CGbOptimizeThread()
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->DestroyWindow();
		delete m_pProgressDlg;
		m_pProgressDlg = NULL;
	}
}


BOOL CGbOptimizeThread::InitInstance()
{
	CWnd *pWnd = CWnd::GetDesktopWindow();
	CThreadProgrssDlg *pProgressDlg = new CThreadProgrssDlg(pWnd);//pTool->m_pParentWnd);
	pProgressDlg->CreateThreadDlg(pWnd, _T(""));//pTool->m_pParentWnd, _T(""));
	pProgressDlg->SetMaxRange(m_nMaxRange);

	m_pProgressDlg = pProgressDlg;
	m_pProgressDlg->ShowWindow(SW_HIDE);

	return TRUE;
}

int CGbOptimizeThread::ExitInstance()
{
	int nReturn = CWinThread::ExitInstance();

	return nReturn;
}


BEGIN_MESSAGE_MAP(CGbOptimizeThread, CWinThread)
	//{{AFX_MSG_MAP(CGbOptimizeThread)
	ON_THREAD_MESSAGE(WM_USER + 2355, On2355)
	ON_THREAD_MESSAGE(WM_USER + 2356, On2356)
	ON_THREAD_MESSAGE(WM_USER + 2357, On2357)
	ON_THREAD_MESSAGE(WM_USER + 2358, On2358)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGbOptimizeThread message handlers

void CGbOptimizeThread::ShowProgressDlg()
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ShowWindow(SW_SHOW);
		CRect rc;
		m_pProgressDlg->GetWindowRect(&rc);
		m_pProgressDlg->SetWindowPos(&CWnd::wndTopMost, rc.left, rc.top, rc.Width(), rc.Height(), SWP_SHOWWINDOW);
	}
}

void CGbOptimizeThread::On2355(WPARAM wParam, LPARAM lParam)
{
	m_nMaxRange = wParam;

	ShowProgressDlg();

	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->SetMaxRange(wParam);
		m_pProgressDlg->ResetProcess();
	}
}

void CGbOptimizeThread::On2356(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		m_pProgressDlg->ResetProcess();
	}
}

void CGbOptimizeThread::On2357(WPARAM wParam, LPARAM lParam)
{
	if (m_pProgressDlg != NULL)
	{
		//m_pProgressDlg->StepIt();
		m_pProgressDlg->StepPos(m_nStepIndex);
	}
}

void CGbOptimizeThread::On2358(WPARAM wParam, LPARAM lParam)
{
	ShowProgressDlg();

	if (m_pProgressDlg != NULL)
	{
		CString strMsg ;
		strMsg = m_pszMessage;
		m_pProgressDlg->ShowMsg(strMsg);
	}
}
