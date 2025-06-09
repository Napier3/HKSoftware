#include "stdafx.h"
#include "GbDvmReplaceTool.h"

//////////////////////////////////////////////////////////////////////////
//GbDvmReplaceDsMapCrossBreak
CGbDvmReplaceDsMapCrossBreak::CGbDvmReplaceDsMapCrossBreak(CDvmDatasetMap *pDvmDsMap)
{
	//shaolei 20220218
	m_listDataMapTemp.AppendClone(pDvmDsMap);

	BuildDataMap();
}

CGbDvmReplaceDsMapCrossBreak::~CGbDvmReplaceDsMapCrossBreak()
{
	//shaolei 20220218  RemoveAll改为DeleteAll
	m_listDataMapTemp.DeleteAll();
	RemoveAll();
	FreeCrossList(&m_listCrossSingle);
	FreeCrossList(&m_listCrossLoop);
	m_listNewDataMap.DeleteAll();
}

void CGbDvmReplaceDsMapCrossBreak::ResetDataMap()
{
	POS pos = GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;

	while (pos != NULL)
	{
		pDataMap = (CDvmDataMap *)GetNext(pos);
		pDataMap->m_pStand = NULL;
		pDataMap->m_pMap = NULL;
	}
}

BOOL CGbDvmReplaceDsMapCrossBreak::HasValidMap()
{
	BOOL bValid = FALSE;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		CDvmDataMap *pDataMap = (CDvmDataMap *)GetNext(pos);

		if (pDataMap->m_strMapName.GetLength() > 0 || pDataMap->m_strMapID.GetLength())
		{
			bValid = TRUE;
			break;
		}
	}

	return bValid;
}
//以pDataMap为参考对象，构建交叉替换链表
void CGbDvmReplaceDsMapCrossBreak::BuildDataMap()
{
	//过滤相同的数据对象
	BuildDataMapFilterSame();

	//构建Cross条件对象
	BuildDataMapInitCross();
	
	//去掉不满足Cross条件对象
	BuildDataMapFilterCross();
	
	//检索、创建Cross
	BuildDataMapCreateCross_Single();
	BuildDataMapCreateCross_Loop();

	//构建替换
	BuildDataMapBreakCross_Single();
	BuildDataMapBreakCross_Loop();

}

void CGbDvmReplaceDsMapCrossBreak::BuildDataMapFilterSame()
{
	POS pos = m_listDataMapTemp.GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	POS posCurr = NULL;

	//过滤相同的数据对象
	while (pos != NULL)
	{
		posCurr = pos;
		pDataMap =  (CDvmDataMap*)m_listDataMapTemp.GetNext(pos);

		if (pDataMap->m_strID == pDataMap->m_strMapID)
		{
			//AddTail(pDataMap);
			m_listDataMapTemp.RemoveAt(posCurr);
		}
	}
}

/*
			m_strID[###]m_strMapID(m_pStand) -> (m_pMap)m_strID[###]m_strMapID(m_pStand) ->  (m_pMap)m_strID[###]m_strMapID(m_pStand)
*/

void CGbDvmReplaceDsMapCrossBreak::BuildDataMapInitCross()
{
	POS pos = m_listDataMapTemp.GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	CDvmDataMap *pFind = NULL;

	while (pos != NULL)
	{
		pDataMap =  (CDvmDataMap*)m_listDataMapTemp.GetNext(pos);

		//查找MapID为其他对象的CDvmDataMap
		pFind = (CDvmDataMap *)m_listDataMapTemp.FindByID(pDataMap->m_strMapID);

		if (pFind != NULL)
		{
			pDataMap->m_pStand = pFind;
			pFind->m_pMap = pDataMap;
		}
	}
}

void CGbDvmReplaceDsMapCrossBreak::BuildDataMapFilterCross()
{
	POS pos = m_listDataMapTemp.GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	POS posCurr = NULL;

	while (pos != NULL)
	{
		posCurr = pos;
		pDataMap =  (CDvmDataMap*)m_listDataMapTemp.GetNext(pos);
		
		//清除没有任何交叉引用替换的对象
		if (pDataMap->m_pStand == NULL && pDataMap->m_pMap == NULL)
		{
			AddTail(pDataMap);
			m_listDataMapTemp.RemoveAt(posCurr);
		}
	}
}

void CGbDvmReplaceDsMapCrossBreak::BuildDataMapCreateCross_Single()
{
	POS pos = m_listDataMapTemp.GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	CDvmDataMap *pHead = NULL;
	POS posCurr = NULL;
	CExBaseList *pCross = NULL;

	while (pos != NULL)
	{
		pHead = (CDvmDataMap*)m_listDataMapTemp.GetNext(pos);

		//单向
		if (pHead->m_pMap == NULL)
		{
			pCross = new CExBaseList();
			m_listCrossSingle.AddTail(pCross);
			pDataMap = pHead;

			while (pDataMap != NULL)
			{
				pCross->AddTail(pDataMap);
				pDataMap = (CDvmDataMap*)pDataMap->m_pStand;
			}
		}
	}

	POS posCross  = m_listCrossSingle.GetHeadPosition();

	while (posCross != NULL)
	{
		pCross = (CExBaseList *)m_listCrossSingle.GetNext(posCross);
		pos = pCross->GetHeadPosition();

		while (pos != NULL)
		{
			pDataMap = (CDvmDataMap *)pCross->GetNext(pos);
			m_listDataMapTemp.Remove(pDataMap);
		}
	}
}

void CGbDvmReplaceDsMapCrossBreak::BuildDataMapCreateCross_Loop()
{
	POS pos = m_listDataMapTemp.GetHeadPosition();
	CDvmDataMap *pDataMap = NULL;
	CDvmDataMap *pHead = NULL;
	POS posCurr = NULL;
	CExBaseList *pCross = NULL;

	while (TRUE)
	{
		pHead = (CDvmDataMap*)m_listDataMapTemp.GetHead();

		if (pHead == NULL)
		{
			break;
		}

		pCross = new CExBaseList();
		m_listCrossLoop.AddTail(pCross);
		pDataMap = pHead;

		while (pDataMap != NULL)
		{
			pCross->AddTail(pDataMap);
			pDataMap = (CDvmDataMap *)pDataMap->m_pStand;
			ASSERT (pDataMap != NULL);

			if (pDataMap == pHead)
			{
				break;
			}
		}

		pos = pCross->GetHeadPosition();

		while (pos != NULL)
		{
			pDataMap = (CDvmDataMap *)pCross->GetNext(pos);
			m_listDataMapTemp.Remove(pDataMap);
		}
	}
}

void CGbDvmReplaceDsMapCrossBreak::BuildDataMapBreakCross_Single()
{
	POS posCross = m_listCrossSingle.GetHeadPosition();
	CExBaseList *pCross = NULL;

	while (posCross != NULL)
	{
		pCross = (CExBaseList*)m_listCrossSingle.GetNext(posCross);
		POS pos = pCross->GetTailPosition();
		CExBaseObject *p = NULL;

		while (pos != NULL)
		{
			p = pCross->GetPrev(pos);
			AddTail(p);
		}
	}
}

void CGbDvmReplaceDsMapCrossBreak::BuildDataMapBreakCross_Loop()
{
	POS posCross = m_listCrossLoop.GetHeadPosition();
	CExBaseList *pCross = NULL;
	long nIndex = 0;
	CString strMapID;
	CString strID;

	while (posCross != NULL)
	{
		pCross = (CExBaseList*)m_listCrossLoop.GetNext(posCross);
	
		POS pos = pCross->GetTailPosition();
		CDvmDataMap *pDataMap = NULL;
		strMapID.Format(_T("Dvm%dTemp"), nIndex++);
		pDataMap = (CDvmDataMap *)pCross->GetAt(pos);

		strID = pDataMap->m_strMapID;
		pDataMap->m_strMapID = strMapID;

		AddTail(pDataMap);
		pCross->GetPrev(pos);

		while (pos != NULL)
		{
			pDataMap = (CDvmDataMap *)pCross->GetPrev(pos);
			AddTail(pDataMap);
		}

		CDvmDataMap *pNew = new CDvmDataMap();
		pNew->m_strID = strMapID;
		pNew->m_strMapID = strID;
		AddTail(pNew);

		m_listNewDataMap.AddTail(pNew);
	}
}

void CGbDvmReplaceDsMapCrossBreak::FreeCrossList(CExBaseList *pCrossList)
{
	POS pos = pCrossList->GetHeadPosition();
	CExBaseList *pCross = NULL;

	while (pos != NULL)
	{
		pCross = (CExBaseList *)pCrossList->GetNext(pos);
		pCross->RemoveAll();
	}

	pCrossList->DeleteAll();
}

//////////////////////////////////////////////////////////////////////////
//CGbItemDvmReplace
#define use_CGbDvmReplaceDsMapCrossBreak

CGbDvmReplaceTool::CGbDvmReplaceTool()
{
	m_pTrheadPrgsInterface = NULL;
	m_bStopGbDvmReplaceThread = FALSE;
	m_pGbDvmReplaceThread = NULL;
	m_nCurrRepalceIndex = 0;
	m_nTotalRepalceCount = 0;
	m_pCpus = NULL;

	m_pGbDvmReplaceEvent = NULL;   //2023-4-19  lijunqing
}

CGbDvmReplaceTool::~CGbDvmReplaceTool()
{
#ifdef use_CGbDvmReplaceDsMapCrossBreak

#else
	RemoveAll();
#endif
}

void CGbDvmReplaceTool::BuildRepalce(CExBaseList *pGbItems, CCpus *pCpus)
{
	m_pCpus = pCpus;
	m_oGbItemDvmVarReplace.BuildRepalce(pGbItems);
}


//添加数据集映射
void CGbDvmReplaceTool::AddDatasetMap(CDvmDatasetMap *pDvmDatasetMap)
{
#ifdef  use_CGbDvmReplaceDsMapCrossBreak

	CGbDvmReplaceDsMapCrossBreak *pNew = new CGbDvmReplaceDsMapCrossBreak(pDvmDatasetMap);
	AddTail(pNew);
	pNew->m_strDsID = pDvmDatasetMap->m_strID;
	pNew->m_strDsMapID = pDvmDatasetMap->m_strMapID;
	pNew->m_strLdviceMap = pDvmDatasetMap->m_strLdviceMap;
	pNew->m_strLdvice = pDvmDatasetMap->m_strLdvice;
	m_nTotalRepalceCount += pNew->GetCount();

#else

	AddTail(pDvmDatasetMap);

	//数据对象替换
	m_nTotalRepalceCount += pDvmDatasetMap->GetCount();

#endif

	//数据集替换
	m_nTotalRepalceCount++;

	CDvmMapObject *pFind = m_oLdeviceMap.FindMapObj(pDvmDatasetMap->m_strLdvice, pDvmDatasetMap->m_strLdviceMap);

	if (pFind == NULL)
	{
		//逻辑设备替换
		pFind = new CDvmMapObject();
		pFind->m_strID = pDvmDatasetMap->m_strLdvice;
		pFind->m_strMapID = pDvmDatasetMap->m_strLdviceMap;
		m_oLdeviceMap.AddTail(pFind);
		m_nTotalRepalceCount++;
	}
}


//创建Replace线程，开始替换
void CGbDvmReplaceTool::CreateGbDvmReplaceThread(CThreadProgressInterface *pTrheadPrgsInterface)
{
	m_pTrheadPrgsInterface = pTrheadPrgsInterface;

	m_pGbDvmReplaceThread = ::AfxBeginThread(GbDvmReplaceThread, this);
	m_pGbDvmReplaceThread->m_bAutoDelete = TRUE;
}

void CGbDvmReplaceTool::CreateGbDvmQueryThread(CThreadProgressInterface *pTrheadPrgsInterface)
{
	m_pTrheadPrgsInterface = pTrheadPrgsInterface;

	m_pGbDvmReplaceThread = ::AfxBeginThread(GbDvmQueryThread, this);
	m_pGbDvmReplaceThread->m_bAutoDelete = TRUE;
}

void CGbDvmReplaceTool::CreateGbDvmStxmlReplaceThread(CThreadProgressInterface *pTrheadPrgsInterface, CGbtDatas *pGbtDatas)
{
	m_pTrheadPrgsInterface = pTrheadPrgsInterface;
	m_pGbtDatas = pGbtDatas;

	m_pGbDvmReplaceThread = ::AfxBeginThread(GbDvmStxmlReplaceThread, this);
	m_pGbDvmReplaceThread->m_bAutoDelete = TRUE;
}

void CGbDvmReplaceTool::CreateDvmMatchReplaceThread(CThreadProgressInterface *pTrheadPrgsInterface, CExBaseList *pListMatchMaps)
{
	m_pTrheadPrgsInterface = pTrheadPrgsInterface;
	m_pListMatchMaps = pListMatchMaps;

	m_pGbDvmReplaceThread = ::AfxBeginThread(DvmMatchReplaceThread, this);
	m_pGbDvmReplaceThread->m_bAutoDelete = TRUE;
}

void CGbDvmReplaceTool::ResetDataMap()
{
	POS pos = GetHeadPosition();
	CGbDvmReplaceDsMapCrossBreak *pCrossBreak = NULL;

	while (pos != NULL)
	{
		pCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)GetNext(pos);
		pCrossBreak->ResetDataMap();
	}
}

//停止线程
void CGbDvmReplaceTool::StopGbDvmReplaceThread()
{
	m_bStopGbDvmReplaceThread = TRUE;
}

//////////////////////////////////////////////////////////////////////////
//
UINT CGbDvmReplaceTool::GbDvmReplaceThread(LPVOID pParameter)
{
	CGbDvmReplaceTool *pTool = (CGbDvmReplaceTool*)pParameter;

	pTool->GbDvmReplaceThread();
	pTool->m_pGbDvmReplaceThread = NULL;

	if (pTool->m_pGbDvmReplaceEvent != NULL)
	{
		pTool->m_pGbDvmReplaceEvent->ReplaceFinished();
	}

	return 0;
}


void CGbDvmReplaceTool::GbDvmReplaceThread()
{
	m_pTrheadPrgsInterface->SetMaxRange(m_nTotalRepalceCount);
	m_nCurrRepalceIndex = 1;

	//遍历数据集映射
	POS posDs = GetHeadPosition();

#ifdef use_CGbDvmReplaceDsMapCrossBreak
	CGbDvmReplaceDsMapCrossBreak *pDsCrossBreak = NULL;
#else
	CDvmDatasetMap *pDvmDatasetMap = NULL;
#endif

	CDvmDataMap *pDataMap = NULL;
	POS posData = NULL;
	CDataObj *pDataObj = NULL;
	CString strMsg;

	while (posDs != NULL)
	{
#ifdef use_CGbDvmReplaceDsMapCrossBreak
		pDsCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)GetNext(posDs);
		posData = pDsCrossBreak->GetHeadPosition();
#else
		pDvmDatasetMap = (CDvmDatasetMap *)GetNext(posDs);
		posData = pDvmDatasetMap->GetHeadPosition();
#endif

		while (posData != NULL)
		{
#ifdef use_CGbDvmReplaceDsMapCrossBreak
			pDataMap = (CDvmDataMap *)pDsCrossBreak->GetNext(posData);
#else
			pDataMap = (CDvmDataMap *)pDvmDatasetMap->GetNext(posData);
#endif

// 			if (pDataMap->m_strMapID.IsEmpty() && pDataMap->m_strMapName.IsEmpty())
// 			{
// 				continue;
// 			}

			if (pDataMap->m_strMapID != pDataMap->m_strID)
			{
#ifdef use_CGbDvmReplaceDsMapCrossBreak
				pDataObj = m_pCpus->FindDataObjByID(pDsCrossBreak->m_strLdviceMap, pDsCrossBreak->m_strDsMapID, pDataMap->m_strMapID);
#else
				pDataObj = m_pCpus->FindDataObjByID(pDvmDatasetMap->m_strLdviceMap, pDvmDatasetMap->m_strMapID, pDataMap->m_strMapID);
#endif
				//20231106 huangliang 父级ID为空时，直接去子级查找试试
				if(pDataMap->m_strMapID == "")
				{
					ReplaceChild(pDsCrossBreak->m_strLdviceMap, pDsCrossBreak->m_strDsMapID, pDataMap);
				}
				Replace(pDataObj, pDataMap->m_strID, pDataMap->m_strMapID);
			}

			m_nCurrRepalceIndex++;
		}

#ifdef use_CGbDvmReplaceDsMapCrossBreak
		if (pDsCrossBreak->m_strDsID != pDsCrossBreak->m_strDsMapID)
		{
			Replace(NULL, pDsCrossBreak->m_strDsID, pDsCrossBreak->m_strDsMapID);
		}
#else
		if (pDvmDatasetMap->m_strID != pDvmDatasetMap->m_strMapID)
		{
			Replace(NULL, pDvmDatasetMap->m_strID, pDvmDatasetMap->m_strMapID);
		}
#endif

		m_nCurrRepalceIndex++;
	}
	
	/*shaolei  20220427  for debug
		此处逻辑设备替换可能存在问题：
		若存在同一个逻辑设备下，有数据集跨逻辑设备映射的，有可能存在第二个替换不成功的问题。
		例如：PROT 映射 PROT，  PROT  映射 LD0（保护遥信数据集）
	*/
	//逻辑设备替换
	posDs = m_oLdeviceMap.GetHeadPosition();
	CDvmMapObject *pMap = NULL;

	while (posDs != NULL)
	{
		pMap = (CDvmMapObject *)m_oLdeviceMap.GetNext(posDs);

		if (pMap->m_strID != pMap->m_strMapID)
		{
			Replace(NULL, pMap->m_strID, pMap->m_strMapID);
		}

		m_nCurrRepalceIndex++;
	}

	m_oGbItemDvmVarReplace.FinishReplace();

	//替换完成，执行通讯命令的切分
	m_pTrheadPrgsInterface->ShowMsg(_T("替换完成，处理通讯命令...."));

	//2019-07-30   四方模型，各数据及下面模型是一致的，导致出问题，暂时屏蔽
	//2022-2-7  山东继电保护测试项目，放开此处
	CGbCommCmdSplitTool oGbCommCmdSplitTool;
	oGbCommCmdSplitTool.AttatchDatasetMaps(this);
	oGbCommCmdSplitTool.GbCommCmdSplit(m_pCpus);

	//恢复数据集映射用临时变量
	ResetDataMap();

	m_pTrheadPrgsInterface->Finish();
}
//20231106 huangliang 添加子级中查找
void CGbDvmReplaceTool::ReplaceChild(const CString &strCpuID, const CString &strDsID, CDvmDataMap *pDataMap)
{
	POS posDs = pDataMap->GetHeadPosition();
	CDvmValueMap *pMap = NULL;
	CDataSet *pDataSet = NULL;

	while (posDs != NULL)
	{
		pMap = (CDvmValueMap *)pDataMap->GetNext(posDs);

		if (pMap->m_strID != pMap->m_strMapID)
		{
			pDataSet = m_pCpus->FindDataObjByID(strCpuID, strDsID);
			Replace(pDataSet, pMap->m_strID, pMap->m_strMapID);
		}

		m_nCurrRepalceIndex++;
	}
}

UINT CGbDvmReplaceTool::GbDvmQueryThread(LPVOID pParameter)
{
	CGbDvmReplaceTool *pTool = (CGbDvmReplaceTool*)pParameter;

	pTool->GbDvmQueryThread();
	pTool->m_pGbDvmReplaceThread = NULL;

	return 0;
}

UINT CGbDvmReplaceTool::GbDvmStxmlReplaceThread(LPVOID pParameter)
{
	CGbDvmReplaceTool *pTool = (CGbDvmReplaceTool*)pParameter;

	pTool->GbDvmStxmlReplaceThread();
	pTool->m_pGbDvmReplaceThread = NULL;

	return 0;
}


UINT CGbDvmReplaceTool::DvmMatchReplaceThread(LPVOID pParameter)
{
	CGbDvmReplaceTool *pTool = (CGbDvmReplaceTool*)pParameter;

	pTool->DvmMatchReplaceThread();
	pTool->m_pGbDvmReplaceThread = NULL;

	return 0;
}

void CGbDvmReplaceTool::GbDvmQueryThread()
{
	m_nTotalRepalceCount = 0;

	POS posCpu = NULL, posDs = NULL, posData = NULL;
	CCpu *pCpu = NULL;
	CDataSet *pDataset = NULL;
	CDataObj *pData = NULL;

	posCpu = m_pCpus->GetHeadPosition();

	while (posCpu != NULL)
	{
		pCpu = (CCpu *)m_pCpus->GetNext(posCpu);
		posDs = pCpu->GetHeadPosition();

		while (posDs != NULL)
		{
			pDataset = (CDataSet *)pCpu->GetNext(posDs);
			m_nTotalRepalceCount += pDataset->GetCount();
		}
	}

	m_pTrheadPrgsInterface->SetMaxRange(m_nTotalRepalceCount);
	m_nCurrRepalceIndex = 1;

	posCpu = m_pCpus->GetHeadPosition();

	while (posCpu != NULL)
	{
		pCpu = (CCpu *)m_pCpus->GetNext(posCpu);
		posDs = pCpu->GetHeadPosition();

		while (posDs != NULL)
		{
			pDataset = (CDataSet *)pCpu->GetNext(posDs);

			if (pDataset->m_strID.Find(_T("Log")) >= 0)
			{
				continue;
			}

			posData = pDataset->GetHeadPosition();

			while (posData != NULL)
			{
				pData = (CDataObj *)pDataset->GetNext(posData);

				if (HasReplace(NULL, pData->m_strID))
				{
					if (Find(pData) == NULL)
					{
						AddTail(pData);
					}
				}
			}
		}
	}

	m_pTrheadPrgsInterface->Finish(0);
}

void CGbDvmReplaceTool::GbDvmStxmlReplaceThread()
{
	m_nTotalRepalceCount = GetCount();
	m_pTrheadPrgsInterface->SetMaxRange(m_nTotalRepalceCount);
	m_nCurrRepalceIndex = 1;

	//遍历数据集映射
	POS posDest = m_pGbtDatas->GetHeadPosition();
	CExBaseObject *pDest = NULL;
	POS posSrc = GetHeadPosition();
	CExBaseObject *pSrc = NULL;

	while (posDest != NULL && posSrc != NULL)
	{
		pSrc = (CExBaseObject *)GetNext(posSrc);
		pDest = (CExBaseObject *)m_pGbtDatas->GetNext(posDest);

		if (pSrc->m_strName == pDest->m_strName)
		{
			Replace(pDest, pSrc->m_strID, pDest->m_strID);
		}

		m_nCurrRepalceIndex++;
	}

	m_oGbItemDvmVarReplace.FinishReplace();
	m_pTrheadPrgsInterface->Finish(1);
}

void CGbDvmReplaceTool::DvmMatchReplaceThread()
{
	m_nTotalRepalceCount = m_pListMatchMaps->GetCount();
	m_pTrheadPrgsInterface->SetMaxRange(m_nTotalRepalceCount);
	m_nCurrRepalceIndex = 1;

	//遍历数据集映射
	POS pos = m_pListMatchMaps->GetHeadPosition();
	CDvmMapObject *pMap = NULL;

	while (pos != NULL)
	{
		pMap = (CDvmMapObject *)m_pListMatchMaps->GetNext(pos);

		if (pMap->m_strID != pMap->m_strMapID)
		{
			//2019-3-18  映射关系的目标数据对象
			//Replace(NULL, pMap->m_strID, pMap->m_strMapID);
			Replace(pMap->m_pMap, pMap->m_strID, pMap->m_strMapID);
		}

		m_nCurrRepalceIndex++;
	}

	m_oGbItemDvmVarReplace.FinishReplace();
	m_pTrheadPrgsInterface->Finish(2);
}

void CGbDvmReplaceTool::Replace(CExBaseObject *pDestObject, const CString &strSrcID, const CString &strDestID)
{
	if (strSrcID.GetLength() == 0 || strDestID.GetLength() == 0)
	{//无效的数据，直接返回  2023-4-19  lijunqing
		m_pTrheadPrgsInterface->StepIt();
		return;
	}

	CString strMsg;
	strMsg.Format(_T("%d / %d    \r\n%s ==>> %s"), m_nCurrRepalceIndex, m_nTotalRepalceCount
		,strSrcID, strDestID);
	m_pTrheadPrgsInterface->ShowMsg(strMsg);
	
	m_oGbItemDvmVarReplace.Replace(pDestObject, strSrcID, strDestID);
	m_pTrheadPrgsInterface->StepIt();
}

BOOL CGbDvmReplaceTool::HasReplace(CExBaseObject *pDestObject, const CString &strSrcID)
{
	//m_pTrheadPrgsInterface->ShowMsg(strSrcID);

	return m_oGbItemDvmVarReplace.HasReplace(pDestObject, strSrcID);
}
