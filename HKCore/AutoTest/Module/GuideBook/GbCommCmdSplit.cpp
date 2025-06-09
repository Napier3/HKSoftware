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
// 	//����ӳ������ݶ�Ӧ�����ݼ�
// 	GetListDatasetFromDatas(pDevice, pCommCmd, &oListDatasetFromData);
// 
// 	//ȥ����ͨѶ�����޹ص����ݼ�������WriteEna��ֻ��Ena���ݼ���ͨѶ�����йأ������Ķ��޹�
// 	CGuideBook *pGuideBook = (CGuideBook*)pCommCmd->GetAncestor(GBCLASSID_GUIDEBOOK);
// 	CGbCommCmdMms *pCmdMms = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);
// 
// 	if (pCmdMms == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("ͨѶ���%s������")*/g_sLangTxt_CommCmdError, pCommCmd->m_strCommCmdID);
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
// 	//������е����ݶ���һ�����ݼ���
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
// 	//���ͨѶ����
// 	long nAdd = nCount - 1;
// 	long nIndex = 0;
// 	CExBaseList *pItems = (CExBaseList*)pCommCmd->GetParent();
// 	CCommCmd *pNew = NULL;
// 	POS posAdd = NULL;
// 	posAdd = pItems->Find(pCommCmd);
// 	CExBaseList listCommCmd;   //ͨѶ�����б�
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
// 	//����ͨѶ�������������������ݼ�ID
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
// 		//ɾ�������ڵ�ǰ���ݼ�������
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
		//ʹ��ӳ������ݣ�����ͨѶ����Ĳ������Ҷ�Ӧ�����ݼ�
		//����ӳ������ݶ�Ӧ�����ݼ�
		GetListDatasetFromDatas(m_pDevice, pCommCmd, &oListDatasetFromData);

		//ȥ����ͨѶ�����޹ص����ݼ�������WriteEna��ֻ��Ena���ݼ���ͨѶ�����йأ������Ķ��޹�
		CGuideBook *pGuideBook = (CGuideBook*)pCommCmd->GetAncestor(GBCLASSID_GUIDEBOOK);
		CGbCommCmdMms *pCmdMms = (CGbCommCmdMms*)pGuideBook->m_oGbCommCmdConfig.FindByID(pCommCmd->m_strCommCmdID);

		if (pCmdMms == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("ͨѶ���%s������")*/g_sLangTxt_CommCmdError, pCommCmd->m_strCommCmdID);
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
		//��ʹ�����õ����ݣ���Ҫ����ӳ���ϵȥ���Ҷ�Ӧ�����ݼ�
		GetListDatasetFromMaps(m_pDevice, pCommCmd, &oListDatasetFromData);
	}

	nCount = oListDatasetFromData.GetCount();

	if (nCount == 0)
	{
		//for debug
		/*shaolei 20220427
		�˴�ֱ�ӷ��أ������������⣺
		oListDatasetFromData�е����ݼ����Ǹ���ͨѶ����Я���Ĳ��������豸����ģ���в��ҵ�
		����ͨѶ����Я���Ĳ������Ǵ�CommCmdConfig.xml�ļ������õģ����磺�źŸ���Ĳ���
		��oListDatasetFromData�����޷����ҵ���Ӧ�����ݼ��ġ�
		��ʱ��pCmd->m_strDatasetPath   Ҳ����Ҫ����ӳ���ϵ�����滻��
		*/
		//���Ҷ�Ӧ��ӳ�����ݼ�
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
		strDsPath = pDsCrossBreak->m_strDsID;   //��¼ԭʼģ���е�ͨѶ��������ݼ�ID
#else 
		pDvmDatasetMap = (CDvmDatasetMap *)pObj;
		strMapDsPath = pDvmDatasetMap->m_strLdviceMap + _T("$") + pDvmDatasetMap->m_strDsMapID;
		strDsPath = pDvmDatasetMap->m_strDsID;   //��¼ԭʼģ���е�ͨѶ��������ݼ�ID
#endif

		//if (pCmd->m_strDatasetPath == strMapDsPath )
		{
			//˵��pCommCmd�����ݼ�·�����Ѿ����滻���
			if (pCommCmd->m_strRwOptr == g_strDeviceModelOptr_Read)
			{
				//���ڶ�ָ����⴦��
				//��һ�Զ�ӳ��ʱ�����磺LLN0$dsRelayEnaӳ��LLN0$dsRelayEna1��ͬʱLLN0$dsRelayEnaӳ��LLN0$dsRelayEna2
				//Ӧ������ӳ�䣬�������ͨѶ������Ŀ
				CExBaseList oMapList;
				long nMapCount = SelectDatasetMaps(strDsPath, &oMapList);  //��һ�Զ�ӳ�������ӳ�������ҳ���

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
					CExBaseList oListCommCmd;   //����ӵ�ͨѶ��������
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

	//������е����ݶ���һ�����ݼ���
	if (nCount == 1)
	{
		pCommCmd->m_bWzdHasInitDataset = TRUE;
		pDataset = (CDataSet*)oListDatasetFromData.GetHead();
		pCmd->m_strDatasetPath = pDataset->GetIDPathEx(GBCLASSID_CPUS, FALSE);
		oListDatasetFromData.RemoveAll();
		ValidateCmdValues(m_pDevice, pCommCmd);
		return;
	}

	//���ͨѶ����
	CExBaseList listCommCmd;   //ͨѶ�����б�
	long nAdd = nCount - 1;
	AddCommCmd(nAdd, &listCommCmd, pCommCmd);

	CDataObj *pDataObj = NULL;
	//����ͨѶ�������������������ݼ�ID
	pos = listCommCmd.GetHeadPosition();
	nIndex = 0;
	CDataSet *pDatasetFind = NULL;

	while (pos != NULL)
	{
		pCurr = (CCommCmd *)listCommCmd.GetNext(pos);
		pDatasetFind = (CDataSet*)oListDatasetFromData.GetAtIndex(nIndex);
		pCmd = pCurr->GetCmd();
		pCmd->m_strDatasetPath = pDatasetFind->GetIDPathEx(GBCLASSID_CPUS, FALSE);

		//ɾ�������ڵ�ǰ���ݼ�������
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

	//����û�й��������ݶ���
	CValue *pValue = NULL;
	POS pos = pCmd->GetHeadPosition();
	CCpus *pCpus = GetCpus(pDevice);
	CExBaseObject *pDataset = NULL;
	CExBaseObject *pDataObj = NULL;
	CExBaseList listDatas;
	long nCount = 0;

	//����ӳ������ݶ�Ӧ�����ݼ�
	while (pos != NULL)
	{
		pValue = (CValue *)pCmd->GetNext(pos);
		//shaolei �˴�Ӧ�ø���pCommCmd��m_strDatasetPath�����й���   20220330
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
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("����·����%s����Ӧ�����ݲ�����")*/g_sLangTxt_DataPathNoData, pValue->m_strID);
			}
		}
	}

	CString strCommCmdID = pCommCmd->m_strCommCmdID;
	strCommCmdID.MakeLower();

// 	if (pDatasetList->GetCount() == 0 && strCommCmdID != g_strReset)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ͨѶ���%s��û�ж�Ӧ�����ݼ�"), pCommCmd->GetNamePathEx(GBCLASSID_DEVICE, FALSE));
// 	}
}

//���ڡ���ʹ�����õ����ݡ���ͨѶ��������ݼ�ӳ���в������ݼ��б�   shaolei 20220530
void CGbCommCmdSplit::GetListDatasetFromMaps(CDevice *pDevice, CCommCmd *pCommCmd, CExBaseList *pDatasetList)
{
	CCmd *pCmd = pCommCmd->GetCmd();
	CString strDatasetPath = pCmd->m_strDatasetPath;  //strDsPath�Ѿ����滻������ݼ�·
	//���磺PL110TEMPLATEPROT$LLN0$dsRelayDin����һ��$����ߵ����߼��豸��ID��
	CExBaseObject *pObj = NULL;
	CString strDataset_ID;  //ӳ�����ݼ���ID

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

	//����ӳ������ݶ�Ӧ�����ݼ�
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
			//��for debug
			//�Ƿ���ɾ��pValue��
			//pCmd->Delete(pValue);
			if (bIsCommCmdParaDS)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, /*_T("����·����%s����Ӧ�����ݲ�����")*/g_sLangTxt_DataPathNoData, pValue->m_strID);
			}
		}
	}

	//����ӳ���滻
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

//���ݵ�ǰͨѶ��������ݼ�·�������Ҷ�Ӧ��ģ��ӳ��
//PL110TEMPLATEPROT$LLN0$dsRelayDin����һ��$����ߵ����߼��豸��ID
//����˺���ʱ��strDsPath�Ѿ����滻������ݼ�·��
//���ڿ��߼��豸ӳ�䣬strDsPath�м�¼���߼��豸�ǲ���ȷ��
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
			//�Ƿ�����Ч��ӳ�䣬�����ǿ�ӳ��
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
			//�Ƿ�����Ч��ӳ�䣬�����ǿ�ӳ��
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

//shaolei 2023-2-22  ����ԭʼ���ݼ�ID���������е�ģ��ӳ��
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

//���ͨѶ����
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

