#include "stdafx.h"
#include "GbCommCmdSplit.h"
#include "../XLanguageResourceAts.h"
#include "GbDvmReplaceTool.h"

#define use_CGbDvmReplaceDsMapCrossBreak

//////////////////////////////////////////////////////////////////////////
CGbCommCmdSplit::CGbCommCmdSplit()
{
	m_pDevice = NULL;
	m_pCpus = NULL;
	m_pDatasetMaps = NULL;
}

CGbCommCmdSplit::~CGbCommCmdSplit()
{

}

CCpus* CGbCommCmdSplit::GetCpus(CDevice *pDevice)
{
	if (m_pCpus != NULL)
	{
		return m_pCpus;
	}

	return pDevice->m_pCpus;
}

void CGbCommCmdSplit::InitCommCmdItemDatasetPath(CDevice *pDevice, CCommCmd *pCommCmd)
{
	m_pDevice = pDevice;
	m_pCpus = GetCpus(pDevice);
	InitCommCmdItemDatasetPath(pCommCmd);

// 	CCmd *pCmd = pCommCmd->GetCmd();
// 	CExBaseList oListDatasetFromData;
// 
// 	CValue *pValue = NULL;
// 	POS pos = pCmd->GetHeadPosition();
// 	CExBaseObject *pDataset = NULL;
// 
// 	//查找映射的数据对应的数据集
// 	GetListDatasetFromDatas(pDevice, pCommCmd, &oListDatasetFromData);
// 
// 	//去掉与通讯命令无关的数据集，比如WriteEna，只有Ena数据集与通讯命令有关，其他的都无关
// 	CGuideBook *pGuideBook = (CGuideBook*)pCommCmd->GetAncestor(GBCLASSID_GUIDEBOOK);
// 	CGbCommCmdMms *pCmdMms = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);
// 
// 	if (pCmdMms == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("通讯命令【%s】错误")*/g_sLangTxt_CommCmdError, pCommCmd->m_strCommCmdID);
// 		return;
// 	}
// 
// 	POS posDs = oListDatasetFromData.GetHeadPosition();
// 	CString strIdKey = Gb_GetDataSetKey(pCmdMms->m_strGbDataID);
// 
// 	while (posDs != NULL)
// 	{
// 		pDataset = oListDatasetFromData.GetNext(posDs);
// 
// 		if (pDataset->m_strID.Find(strIdKey) < 0)
// 		{
// 			oListDatasetFromData.Remove(pDataset);
// 		}
// 	}
// 
// 	long nCount = oListDatasetFromData.GetCount();
// 
// 	if (nCount == 0)
// 	{
// 		return;
// 	}
// 
// 	//如果所有的数据都在一个数据集中
// 	if (nCount == 1)
// 	{
// 		pCommCmd->m_bWzdHasInitDataset = TRUE;
// 		pDataset = (CDataSet*)oListDatasetFromData.GetHead();
// 		pCmd->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
// 		oListDatasetFromData.RemoveAll();
// 		ValidateCmdValues(pDevice, pCommCmd);
// 		return;
// 	}
// 
// 	//添加通讯命令
// 	long nAdd = nCount - 1;
// 	long nIndex = 0;
// 	CExBaseList *pItems = (CExBaseList*)pCommCmd->GetParent();
// 	CCommCmd *pNew = NULL;
// 	POS posAdd = NULL;
// 	posAdd = pItems->Find(pCommCmd);
// 	CExBaseList listCommCmd;   //通讯命令列表
// 	listCommCmd.AddTail(pCommCmd);
// 	CDataObj *pDataObj = NULL;
// 
// 	for (nIndex=0; nIndex<nAdd; nIndex++)
// 	{
// 		pNew = (CCommCmd*)pCommCmd->Clone();
// 		pNew->m_strName.AppendFormat(_T("%d"), nIndex+2);
// 		pNew->m_strID.AppendFormat(_T("%d"), nIndex+2);
// 		posAdd = pItems->InsertAfter(posAdd, pNew);
// 		pNew->SetParent(pItems);
// 		listCommCmd.AddTail(pNew);
// 	}
// 
// 	//遍历通讯命令链表，依次设置数据集ID
// 	pos = listCommCmd.GetHeadPosition();
// 	CCommCmd *pCurr = NULL;
// 	nIndex = 0;
// 	CDataSet *pDatasetFind = NULL;
// 
// 	while (pos != NULL)
// 	{
// 		pCurr = (CCommCmd *)listCommCmd.GetNext(pos);
// 		pDatasetFind = (CDataSet*)oListDatasetFromData.GetAtIndex(nIndex);
// 		pCmd = pCurr->GetCmd();
// 		pCmd->m_strDatasetPath = pDatasetFind->GetIDPathEx(GBCLASSID_CPUS, FALSE);
// 
// 		//删除不属于当前数据集的数据
// 		POS posValue = pCmd->GetHeadPosition();
// 		POS posDelete = posValue;
// 
// 		while (posValue != NULL)
// 		{
// 			pValue = (CValue *)pCmd->GetNext(posValue);
// 			pDataObj = pCpus->SelectDataObj(pValue->m_strID);
// 
// 			if (pDatasetFind->Find(pDataObj) == NULL)
// 			{
// 				pCmd->Delete(pValue);
// 			}
// 			else
// 			{
// 				pValue->m_strID = pDataObj->GetIDPathEx(GBCLASSID_CPUS, FALSE);
// 			}
// 		}
// 
// 		pCurr->m_bWzdHasInitDataset = TRUE;
// 		nIndex++;
// 		ValidateCmdValues(pDevice, pCurr);
// 	}
// 
// 	oListDatasetFromData.RemoveAll();
// 	listCommCmd.RemoveAll();
}

void CGbCommCmdSplit::InitCommCmdItemDatasetPath(CCommCmd *pCommCmd)
{
	CCmd *pCmd = pCommCmd->GetCmd();
	CExBaseList oListDatasetFromData;

	CValue *pValue = NULL;
	POS pos = pCmd->GetHeadPosition();
	CExBaseObject *pDataset = NULL;
	long nCount = 0;
	long nIndex = 0;
	CCommCmd *pCurr = NULL;

	if (pCmd->m_nUseCurrSetData == 1)
	{
		//使用映射的数据，根据通讯命令的参数查找对应的数据集
		//查找映射的数据对应的数据集
		GetListDatasetFromDatas(m_pDevice, pCommCmd, &oListDatasetFromData);

		//去掉与通讯命令无关的数据集，比如WriteEna，只有Ena数据集与通讯命令有关，其他的都无关
		CGuideBook *pGuideBook = (CGuideBook*)pCommCmd->GetAncestor(GBCLASSID_GUIDEBOOK);
		CGbCommCmdMms *pCmdMms = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);

		if (pCmdMms == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("通讯命令【%s】错误")*/g_sLangTxt_CommCmdError, pCommCmd->m_strCommCmdID);
			return;
		}

		POS posDs = oListDatasetFromData.GetHeadPosition();
		CString strIdKey;
		CStringArray astrKeys;
		nCount = Gb_GetDataSetKey(pCmdMms->m_strGbDataID, astrKeys);

		while (posDs != NULL)
		{
			pDataset = oListDatasetFromData.GetNext(posDs);

			for (nIndex=0; nIndex<nCount; nIndex++)
			{
				strIdKey = astrKeys.GetAt(nIndex);

				if (strIdKey != g_strDataSetIDKey[DSID_dsAll])
				{
					if (pDataset->m_strID.Find(strIdKey) < 0)
					{
						oListDatasetFromData.Remove(pDataset);
					}
				}
			}
		}
	}
	else
	{
		//不使用设置的数据，需要根据映射关系去查找对应的数据集
		GetListDatasetFromMaps(m_pDevice, pCommCmd, &oListDatasetFromData);
	}

	nCount = oListDatasetFromData.GetCount();

	if (nCount == 0)
	{
		//for debug
		/*shaolei 20220427
		此处直接返回，存在以下问题：
		oListDatasetFromData中的数据集，是根据通讯命令携带的参数，从设备数据模型中查找的
		若是通讯命令携带的参数，是从CommCmdConfig.xml文件中配置的，例如：信号复归的参数
		则oListDatasetFromData中是无法查找到对应的数据集的。
		此时，pCmd->m_strDatasetPath   也是需要根据映射关系进行替换的
		*/
		//查找对应的映射数据集
#ifdef use_CGbDvmReplaceDsMapCrossBreak
		CGbDvmReplaceDsMapCrossBreak *pDsCrossBreak = NULL;
#else
		CDvmDatasetMap *pDvmDatasetMap = NULL;
#endif

		CExBaseObject *pObj = SelectDatasetMap(pCmd->m_strDatasetPath);

		if (pObj == NULL)
		{
			return;
		}

		CString strMapDsPath, strDsPath;
#ifdef use_CGbDvmReplaceDsMapCrossBreak
		pDsCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)pObj;

		pCommCmd->m_bWzdHasInitDataset = TRUE;
		strMapDsPath = pDsCrossBreak->m_strLdviceMap + _T("$") + pDsCrossBreak->m_strDsMapID;
		strDsPath = pDsCrossBreak->m_strDsID;   //记录原始模板中的通讯命令的数据集ID
#else 
		pDvmDatasetMap = (CDvmDatasetMap *)pObj;
		strMapDsPath = pDvmDatasetMap->m_strLdviceMap + _T("$") + pDvmDatasetMap->m_strDsMapID;
		strDsPath = pDvmDatasetMap->m_strDsID;   //记录原始模板中的通讯命令的数据集ID
#endif

		//if (pCmd->m_strDatasetPath == strMapDsPath )
		{
			//说明pCommCmd的数据集路径，已经是替换后的
			if (pCommCmd->m_strRwOptr == g_strDeviceModelOptr_Read)
			{
				//对于读指令，特殊处理
				//当一对多映射时，例如：LLN0$dsRelayEna映射LLN0$dsRelayEna1，同时LLN0$dsRelayEna映射LLN0$dsRelayEna2
				//应当根据映射，创建多个通讯命令项目
				CExBaseList oMapList;
				long nMapCount = SelectDatasetMaps(strDsPath, &oMapList);  //将一对多映射的所有映射结果都找出来

				if (nMapCount == 0)
				{
					return;
				}

				if (nMapCount == 1)
				{
					pCmd->m_strDatasetPath = strMapDsPath;
					ValidateCmdValues(m_pDevice, pCommCmd);
					oMapList.RemoveAll();
					return;
				}
				else 
				{
					long nNeedAdd = nMapCount - 1;
					CExBaseList oListCommCmd;   //需添加的通讯命令链表
					AddCommCmd(nNeedAdd, &oListCommCmd, pCommCmd);
					nIndex = 0;
					pos = oListCommCmd.GetHeadPosition();

					while (pos != NULL)
					{
						pCurr = (CCommCmd *)oListCommCmd.GetNext(pos);
						pCmd = pCurr->GetCmd();

#ifdef use_CGbDvmReplaceDsMapCrossBreak
						pDsCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)oMapList.GetAtIndex(nIndex);
						pCmd->m_strDatasetPath = pDsCrossBreak->m_strLdviceMap + _T("$") + pDsCrossBreak->m_strDsMapID;
#else 
						pDvmDatasetMap = (CDvmDatasetMap *)oMapList.GetAtIndex(nIndex);
						pCmd->m_strDatasetPath = strMapDsPath = pDvmDatasetMap->m_strLdviceMap + _T("$") + pDvmDatasetMap->m_strDsMapID;
#endif
						nIndex++;
					}

					oListCommCmd.RemoveAll();
					oMapList.RemoveAll();
				}
			}
		}
		
		return;
	}

	//如果所有的数据都在一个数据集中
	if (nCount == 1)
	{
		pCommCmd->m_bWzdHasInitDataset = TRUE;
		pDataset = (CDataSet*)oListDatasetFromData.GetHead();
		pCmd->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		oListDatasetFromData.RemoveAll();
		ValidateCmdValues(m_pDevice, pCommCmd);
		return;
	}

	//添加通讯命令
	CExBaseList listCommCmd;   //通讯命令列表
	long nAdd = nCount - 1;
	AddCommCmd(nAdd, &listCommCmd, pCommCmd);

	CDataObj *pDataObj = NULL;
	//遍历通讯命令链表，依次设置数据集ID
	pos = listCommCmd.GetHeadPosition();
	nIndex = 0;
	CDataSet *pDatasetFind = NULL;

	while (pos != NULL)
	{
		pCurr = (CCommCmd *)listCommCmd.GetNext(pos);
		pDatasetFind = (CDataSet*)oListDatasetFromData.GetAtIndex(nIndex);
		pCmd = pCurr->GetCmd();
		pCmd->m_strDatasetPath = pDatasetFind->GetIDPathEx(GBCLASSID_CPUS, FALSE);

		//删除不属于当前数据集的数据
		POS posValue = pCmd->GetHeadPosition();
		POS posDelete = posValue;

		while (posValue != NULL)
		{
			pValue = (CValue *)pCmd->GetNext(posValue);
			pDataObj = m_pCpus->SelectDataObj(pValue->m_strID);

			if (pDatasetFind->Find(pDataObj) == NULL)
			{
				pCmd->Delete(pValue);
			}
			else
			{
				pValue->m_strID = pDataObj->GetIDPathEx(GBCLASSID_CPUS, FALSE);
			}
		}

		pCurr->m_bWzdHasInitDataset = TRUE;
		nIndex++;
		ValidateCmdValues(m_pDevice, pCurr);
	}

	oListDatasetFromData.RemoveAll();
	listCommCmd.RemoveAll();
}

void CGbCommCmdSplit::GetListDatasetFromDatas(CDevice *pDevice, CCommCmd *pCommCmd, CExBaseList *pDatasetList)
{
	BOOL bIsCommCmdParaDS = pCommCmd->IsCommCmdParaDS();
	CCmd *pCmd = pCommCmd->GetCmd();

	//处理没有关联的数据对象
	CValue *pValue = NULL;
	POS pos = pCmd->GetHeadPosition();
	CCpus *pCpus = GetCpus(pDevice);
	CExBaseObject *pDataset = NULL;
	CExBaseObject *pDataObj = NULL;
	CExBaseList listDatas;
	long nCount = 0;

	//查找映射的数据对应的数据集
	while (pos != NULL)
	{
		pValue = (CValue *)pCmd->GetNext(pos);
		//shaolei 此处应该根据pCommCmd的m_strDatasetPath，进行过滤   20220330
		nCount = pCpus->SelectDataObj(pCmd->m_strDatasetPath, pValue->m_strID, listDatas);

		if (nCount > 0)
		{
			POS posData = listDatas.GetHeadPosition();

			while (posData != NULL)
			{
				pDataObj = listDatas.GetNext(posData);

				pDataset = (CExBaseObject*)pDataObj->GetParent();

				if (pDatasetList->Find(pDataset) == NULL)
				{
					pDatasetList->AddTail(pDataset);
				}
			}

			listDatas.RemoveAll();
		}
		else
		{
			if (bIsCommCmdParaDS)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("数据路径【%s】对应的数据不存在")*/g_sLangTxt_DataPathNoData, pValue->m_strID);
			}
		}
	}

	CString strCommCmdID = pCommCmd->m_strCommCmdID;
	strCommCmdID.MakeLower();

// 	if (pDatasetList->GetCount() == 0 && strCommCmdID != g_strReset)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("通讯命令【%s】没有对应的数据集"), pCommCmd->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
// 	}
}

//对于“不使用设置的数据”的通讯命令，从数据集映射中查找数据集列表   shaolei 20220530
void CGbCommCmdSplit::GetListDatasetFromMaps(CDevice *pDevice, CCommCmd *pCommCmd, CExBaseList *pDatasetList)
{
	CCmd *pCmd = pCommCmd->GetCmd();
	CString strDatasetPath = pCmd->m_strDatasetPath;  //strDsPath已经是替换后的数据集路
	//例如：PL110TEMPLATEPROT$LLN0$dsRelayDin：第一个$符左边的是逻辑设备的ID径
	CExBaseObject *pObj = NULL;
	CString strDataset_ID;  //映射数据集的ID

	pObj = SelectDatasetMap(pCmd->m_strDatasetPath);

	if (pObj == NULL)
	{
		return;
	}

#ifdef use_CGbDvmReplaceDsMapCrossBreak
	CGbDvmReplaceDsMapCrossBreak *pDsCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)pObj;
	strDataset_ID = pDsCrossBreak->m_strDsID;
#else 
	CDvmDatasetMap *pDvmDatasetMap = (CDvmDatasetMap *)pObj;
	strDataset_ID = pDvmDatasetMap->m_strID;
#endif

	GetListDatasetFromMaps(pDevice, strDataset_ID, pDatasetList);
}

void CGbCommCmdSplit::GetListDatasetFromMaps(CDevice *pDevice, const CString &strDatasetID, CExBaseList *pDatasetList)
{
	CCpus *pCpus = GetCpus(pDevice);
	POS pos = m_pDatasetMaps->GetHeadPosition();
	CString strLDeviceMap;

#ifdef use_CGbDvmReplaceDsMapCrossBreak
	CGbDvmReplaceDsMapCrossBreak *pDsCrossBreak = NULL;
#else
	CDvmDatasetMap *pDvmDatasetMap = NULL;
#endif

	while (pos != NULL)
	{
#ifdef use_CGbDvmReplaceDsMapCrossBreak
		pDsCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)m_pDatasetMaps->GetNext(pos);

		if (strDatasetID == pDsCrossBreak->m_strDsID)
		{
			strLDeviceMap = pDsCrossBreak->m_strLdviceMap;
			CCpu *pCpu = (CCpu *)pCpus->FindByID(strLDeviceMap);
			CExBaseObject *pDataset = pCpu->FindByID(pDsCrossBreak->m_strDsMapID);

			if (pDatasetList->Find(pDataset) == NULL)
			{
				pDatasetList->AddTail(pDataset);
			}
		}
#else
		pDvmDatasetMap = (CDvmDatasetMap *)m_pDatasetMaps->GetNext(pos);

		if (strDatasetID == pDvmDatasetMap->m_strID)
		{
			strLDeviceMap = pDvmDatasetMap->m_strLdviceMap;
			CCpu *pCpu = (CCpu *)pCpus->FindByID(strLDeviceMap);
			CExBaseObject *pDataset = pCpu->FindByID(pDvmDatasetMap->m_strMapID);

			if (pDatasetList->Find(pDataset) == NULL)
			{
				pDatasetList->AddTail(pDataset);
			}
		}
#endif
	}

}

void CGbCommCmdSplit::ValidateCmdValues(CDevice *pDevice, CCommCmd *pCommCmd)
{
	BOOL bIsCommCmdParaDS = pCommCmd->IsCommCmdParaDS();

	CCmd *pCmd = pCommCmd->GetCmd();
	CDataObj *pFind = NULL;
	CValue *pValue = NULL;
	POS pos = pCmd->GetHeadPosition();
	CCpus *pCpus = GetCpus(pDevice);
	CExBaseObject *pDataset = NULL;
	CExBaseObject *pDataObj = NULL;

	//查找映射的数据对应的数据集
	while (pos != NULL)
	{
		pValue = (CValue *)pCmd->GetNext(pos);
		pDataObj = pCpus->SelectDataObj(pValue->m_strID);

		if (pDataObj != NULL)
		{
			if (pDataObj->m_strID != pValue->m_strID)
			{
				pValue->m_strID = pDataObj->m_strID;
			}
		}
		else
		{
			//？for debug
			//是否考虑删除pValue？
			//pCmd->Delete(pValue);
			if (bIsCommCmdParaDS)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("数据路径【%s】对应的数据不存在")*/g_sLangTxt_DataPathNoData, pValue->m_strID);
			}
		}
	}

	//报告映射替换
	CReportMap *pRptMap = pCommCmd->GetReportMap();
	CExBaseObject *pObj = NULL;
	pos = pRptMap->GetHeadPosition();

	while (pos != NULL)
	{
		pObj = pRptMap->GetNext(pos);

		if (pObj->GetClassID() == RPTCLASSID_RPTDATA)
		{
			pDataObj = FindDataObjByRptDataPath(pObj->m_strID, pCpus);

			if (pDataObj != NULL)
			{
				pObj->m_strName = pDataObj->m_strName;
				pObj->m_strID   = pDataObj->GetIDPathEx(GBCLASSID_CPUS, FALSE);
			}
		}
	}
}

CExBaseObject* CGbCommCmdSplit::FindDataObjByRptDataPath(const CString &strPath, CCpus *pCpus)
{
	CString strTemp = strPath;
	long nPos = 0;
	CExBaseObject *pFind = NULL;
	
	while (TRUE)
	{
		pFind = pCpus->SelectDataObj(strTemp);

		if (pFind != NULL)
		{
			break;
		}

		nPos = strTemp.Find('$');

		if (nPos == -1)
		{
			break;
		}

		strTemp = strTemp.Mid(nPos+1);
	}

	return pFind;
}

//根据当前通讯命令的数据集路径，查找对应的模型映射
//PL110TEMPLATEPROT$LLN0$dsRelayDin：第一个$符左边的是逻辑设备的ID
//进入此函数时，strDsPath已经是替换后的数据集路径
//对于跨逻辑设备映射，strDsPath中记录的逻辑设备是不正确的
CExBaseObject* CGbCommCmdSplit::SelectDatasetMap(const CString &strDsPath)
{
	CExBaseObject *pObj = NULL;
	CString strDataset;
	long nPos = strDsPath.Find(_T("$"));

	if (nPos < 0)
	{
		return NULL;
	}

	strDataset = strDsPath.Mid(nPos + 1);

#ifdef use_CGbDvmReplaceDsMapCrossBreak
	CGbDvmReplaceDsMapCrossBreak *pDsCrossBreak = NULL;
#else
	CDvmDatasetMap *pDvmDatasetMap = NULL;
#endif
	
	POS pos = m_pDatasetMaps->GetHeadPosition();

	while (pos != NULL)
	{
#ifdef use_CGbDvmReplaceDsMapCrossBreak
		pDsCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)m_pDatasetMaps->GetNext(pos);

		if (strDataset == pDsCrossBreak->m_strDsMapID)
		{
			//是否有有效的映射，即不是空映射
			//if (pDsCrossBreak->HasValidMap())
			{
				pObj = pDsCrossBreak;
				break;
			}
		}
#else
		pDvmDatasetMap = (CDvmDatasetMap *)m_pDatasetMaps->GetNext(pos);

		if (strDataset == pDvmDatasetMap->m_strMapID)
		{
			//是否有有效的映射，即不是空映射
			//if (pDvmDatasetMap->HasValidMap() > 0)
			{
				pObj = pDvmDatasetMap;
				break;
			}
		}
#endif
	}

	return pObj;
}

//shaolei 2023-2-22  根据原始数据集ID，查找所有的模型映射
long CGbCommCmdSplit::SelectDatasetMaps(const CString &strDsID, CExBaseList *pMapList)
{
	CExBaseObject *pObj = NULL;

#ifdef use_CGbDvmReplaceDsMapCrossBreak
	CGbDvmReplaceDsMapCrossBreak *pDsCrossBreak = NULL;
#else
	CDvmDatasetMap *pDvmDatasetMap = NULL;
#endif

	POS pos = m_pDatasetMaps->GetHeadPosition();

	while (pos != NULL)
	{
#ifdef use_CGbDvmReplaceDsMapCrossBreak
		pDsCrossBreak = (CGbDvmReplaceDsMapCrossBreak *)m_pDatasetMaps->GetNext(pos);

		if (strDsID == pDsCrossBreak->m_strDsID)
		{
			pMapList->AddTail(pDsCrossBreak);
		}
#else
		pDvmDatasetMap = (CDvmDatasetMap *)m_pDatasetMaps->GetNext(pos);

		if (strDsID == pDvmDatasetMap->m_strDsID)
		{
			pMapList->AddTail(pDvmDatasetMap);
		}
#endif
	}

	return pMapList->GetCount();
}

//添加通讯命令
long CGbCommCmdSplit::AddCommCmd(long nAdd, CExBaseList *pListCommcmd, CCommCmd *pCommCmd)
{
	CExBaseList *pItems = (CExBaseList*)pCommCmd->GetParent();
	CCommCmd *pNew = NULL;
	POS posAdd = NULL;
	posAdd = pItems->Find(pCommCmd);
	pListCommcmd->AddTail(pCommCmd);

	for (long nIndex=0; nIndex<nAdd; nIndex++)
	{
		pNew = (CCommCmd*)pCommCmd->Clone();
		pNew->m_strName.AppendFormat(_T("%d"), nIndex+2);
		pNew->m_strID.AppendFormat(_T("%d"), nIndex+2);
		posAdd = pItems->InsertAfter(posAdd, pNew);
		pNew->SetParent(pItems);
		pListCommcmd->AddTail(pNew);
	}

	return pListCommcmd->GetCount();
}

//////////////////////////////////////////////////////////////////////////
//CGbCommCmdSplitTool
CGbCommCmdSplitTool::CGbCommCmdSplitTool()
{

}

CGbCommCmdSplitTool::~CGbCommCmdSplitTool()
{

}


void CGbCommCmdSplitTool::GbCommCmdSplit(CCpus *pCpus)
{
	AttatchCpus(pCpus);

	CDevice *pDevice = (CDevice *)pCpus->GetParent();
	m_pDevice = pDevice;
	SplitCommCmd(pDevice);
}

void CGbCommCmdSplitTool::SplitCommCmd(CExBaseList *pList)
{
	POS pos = pList->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = pList->GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == GBCLASSID_COMMCMD)
		{
			InitCommCmdItemDatasetPath((CCommCmd*)p);
		}
		else if (nClassID == GBCLASSID_ITEMS)
		{
			SplitCommCmd((CExBaseList*)p);
		}
		else if (nClassID == GBCLASSID_MACROTEST)
		{
			SplitCommCmd((CExBaseList*)p);
		}
	}
}

