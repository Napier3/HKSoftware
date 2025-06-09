// IVtag.cpp : 实现文件
//

#include "stdafx.h"
#include "61850ClientGlobal.h"
#include "EnumType.h"
//#include "MmsApi.h"
#include "..\..\..\Module\MemBuffer\BufferBase.h"
#include "ClientStructDatasDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CString g_strFuncIDame[FUNCID_MAX_COUNT+1] = 
{	"联机","与设备断开连接","写数据","读数据","启动报告","停止报告",
"获取当前运行区","设置当前运行区","枚举装置目录", "切换编辑定值区", "固化编辑定值区", _T("")};

UINT g_nMmsDvmReports_Format_Type = 0;  
CMmsValueKeyMngr g_oMmsValueKeyMngr;
long g_nDvmNameIsStd = 0;
long g_bResetOnlyClearReport = 0; 
CDvmLogicDevice g_oDescDefDatasets;

ST_CHAR* FindVarID(ST_CHAR *pMmsName)
{
	return g_oMmsValueKeyMngr.FindVarID(pMmsName);
}

CMmsValueKeyMngr::CMmsValueKeyMngr()
{
}

CMmsValueKeyMngr::~CMmsValueKeyMngr()
{

}

void CMmsValueKeyMngr::InitMmsValueKeyMngr(const CString &strFile)
{
	InitValueKeyMngr(strFile);
}

BOOL mms_IsSettingsDS(LD_NODE *pLD_Node)
{
	if (pLD_Node == NULL)
	{
		return FALSE;
	}

	LD_DATASET_INFO *pLdDatasetInfor = NULL;
	CString strTmp;

	for (int nIndex = 0;nIndex<pLD_Node->numDaSet;nIndex++)
	{
		pLdDatasetInfor = &pLD_Node->DataInfo[nIndex];
		strTmp = pLdDatasetInfor->DataSetID;
		strTmp.MakeLower();

		if (strTmp.Find("dssetting") >=0)
		{
			return TRUE;
		}
	}

	return FALSE;
}

tagDA* mms_FindData(tagDA *pDatas, long nCount, const CString &strDataAttrID, const CString &strDataAttrValue)
{
	if (strDataAttrID == _T("name"))
	{
		return mms_FindDataByName(pDatas, nCount, strDataAttrValue);
	}

	if (strDataAttrID == _T("id"))
	{
		return mms_FindDataByID(pDatas, nCount, strDataAttrValue);
	}

	return NULL;
}

ST_INT mms_is_da_struct(tagDA*pSrc)
{
	if (pSrc->DataType[0] == 'S')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

ST_INT mms_is_da_array(tagDA*pSrc)
{
	if (pSrc->DataType[0] == 'A')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

ST_INT mms_is_da_basic(tagDA*pSrc)
{
	if (mms_is_da_array(pSrc))
	{
		return 0;
	}

	if (mms_is_da_struct(pSrc))
	{
		return 0;
	}

	return 1;
}

tagDA* mms_FindDataByName(tagDA *pDatas, long nCount, const CString &strDataAttrValue)
{
	tagDA *pFind = NULL;
	tagDA *p = pDatas;
	tagDA *pEnd = pDatas + nCount;
	CString strName, str;

	while (p < pEnd)
	{
		//strName = mms_UTF8ToUnicode(p->DADescri.Value.name, strlen(p->DADescri.Value.name));
		strName = mms_GetDADesc(p);
		//strName = mms_UTF8ToUnicode(str, str.GetLength());

		if (strcmp(strName,strDataAttrValue) == 0)
		{
			pFind = p;
			break;
		}
		
		p++;
	}
	
	return pFind;
}

tagDA* mms_FindDataByID(tagDA *pDatas, long nCount, const CString &strDataAttrValue)
{
	tagDA *pFind = NULL;
	tagDA *p = pDatas;
	tagDA *pEnd = pDatas + nCount;

	CString strText;

	while (p < pEnd)
	{
#ifdef _use_mms_string
		strText = mms_string(&p->DAValue.mmsName);
#else
		strText = p->DAValue.mmsName;
#endif

		if (strcmp(strText,strDataAttrValue) == 0)
		{
			pFind = p;
			break;
		}

		p++;
	}

	return pFind;
}


void mms_GetShortDatasFromTagDA(tagDA *pDatas, long nCount, CShortDatas *pShotDatas)
{
	long nIndex = 0;
	CShortData *pShotData = NULL;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		pShotData = new CShortData();
		mms_GetShortDataFromTagDA(&pDatas[nIndex], pShotData);
		pShotDatas->AddTail(pShotData);
	}
}

void mms_GetShortDataFromTagDA(tagDA *pData, CShortData *pShotData)
{
	if (strcmp(pData->DataType ,"STRUCT") == 0)
	{
		mms_GetDASubValue(pData->pSubDA,pData->nSubDANum, /*"stVal",*/ pShotData->m_strValue);
	}
	else
	{
		pShotData->m_strValue = mms_GetValue(&pData->DAValue, pData->DataType);
	}

	pShotData->m_strName = mms_GetDADesc(pData);//mms_UTF8ToUnicode(pData->DADescri.Value.name, strlen(pData->DADescri.Value.name));
	//pShotData->m_strName = pData->DADescri.mmsName;
#ifdef _use_mms_string
	pShotData->m_strID = mms_string(&pData->DAValue.mmsName);
#else
	pShotData->m_strID = pData->DAValue.mmsName;
#endif
	pShotData->m_strID.Replace(_T("$"), _T("_"));
	pShotData->m_strUnit = mms_ParseUnit(pData->DAUnite.Value.i);
	pShotData->m_strDataTypeID = pData->DataType;
}

void mms_SetShortDatasToTagDA(CShortDatas *pShotDatas, tagDA *pDatas, long nCount)
{
	long nIndex = 0;
	CShortData *pShotData = NULL;
	POS pos = pShotDatas->GetHeadPosition();
	tagDA *pData = NULL;

	while (pos != NULL)
	{
		pShotData = (CShortData*)pShotDatas->GetNext(pos);
		pData = mms_FindDataByName(pDatas, nCount, pShotData->m_strName);

		if (pData != NULL)
		{
			mms_SetShortDataToTagDA(pShotData, pData);
			continue;
		}

		pData = mms_FindDataByID(pDatas, nCount, pShotData->m_strID);

		if (pData != NULL)
		{
			mms_SetShortDataToTagDA(pShotData, pData);
			continue;
		}

	}
}

void mms_SetShortDataToTagDA(CShortData *pShotData, tagDA *pData)
{
	pData->bModify = TRUE;

	if (strcmp(pData->DataType ,"STRUCT") == 0)
	{
		mms_SetDASubValue(pData->pSubDA, /*"stVal",*/ pShotData->m_strValue);
	}
	else
	{
		mms_SetValue(&pData->DAValue, pShotData->m_strValue, pData->DataType);
	}
}

void mms_GetDvmDataset(LD_DATASET_INFO *pDataset, CDvmDataset *pDvmDataset)
{
	pDvmDataset->m_strName = pDataset->DaSetDesc;
	pDvmDataset->m_strID = pDataset->DataSetID;

	long nIndex = 0;
	
	for (nIndex=0; nIndex<pDataset->numData; nIndex++)
	{
		CDvmData *pDvmData = new CDvmData();
		pDvmDataset->AddNewChild(pDvmData);
		mms_GetDvmData(&pDataset->DataSet[nIndex], pDvmData);
	}
}

void mms_GetDvmLogs(MMS_ADDR_VECTOR *pJournalDatas, CDvmLogs *pDvmLogs)//zhouhj 日志读取的函数
{
	long nIndex = 0;
	LD_JOURNAL_DATA *pJournalData = NULL;

	for (nIndex=0;nIndex<pJournalDatas->numOfData;nIndex++)
	{
		CDvmLog *pDvmLog = new CDvmLog();
		pDvmLogs->AddNewChild(pDvmLog);
		pJournalData = (LD_JOURNAL_DATA*)pJournalDatas->Datas[nIndex];
		mms_GetDvmLog(pJournalData,pDvmLog);
	}
}

void mms_GetDvmLdName(ACSI_NODE *pACSI_NODE, long nLdIndex, CString &strPath)
{
	if (nLdIndex >= pACSI_NODE->numLD)
	{
		return;
	}

	strPath = pACSI_NODE->LD[nLdIndex].LDName;
}

void mms_GetDvmDsName(ACSI_NODE *pACSI_NODE, long nLdIndex, long nDsIndex, CString &strPath)
{
	if (nLdIndex >= pACSI_NODE->numLD)
	{
		return;
	}

	strPath = pACSI_NODE->LD[nLdIndex].DataInfo[nDsIndex].DataSetID;
}

void mms_TransFromMap(ACSI_NODE *pACSI_NODE, long ldIndex, long dsIndex,CDvmData *pDvmData, CDvmDeviceMap *pDeviceMap)
{
	if (pDeviceMap == NULL)
	{
		return;
	}

	if (ldIndex >= pACSI_NODE->numLD)
	{
		return;
	}

	CString strLdName, strDsName;
	LD_NODE *pLd = &pACSI_NODE->LD[ldIndex];

	if (dsIndex >= pLd->numDaSet)
	{
		return;
	}

	strLdName = pLd->LDName;
	strDsName = pLd->DataInfo[dsIndex].DataSetID;
	pDeviceMap->TransFromMap(strLdName, strDsName, pDvmData);
}

void mms_GetDvmDatasetReports(ACSI_NODE *pACSI_NODE, long nBeginIndex, long nEndIndex,CDvmDataset *pDvmDataset, CDvmDeviceMap *pDeviceMap)
{
	tagRpt *pRrpts = pACSI_NODE->Reports;
	long nIndex = 0;

	for (nIndex=nBeginIndex; nIndex<nEndIndex; nIndex++)
	{
		CDvmData *pDvmData = new CDvmData();
		pDvmDataset->AddNewChild(pDvmData);
		mms_GetDvmDataRpt(&pRrpts[nIndex], pDvmData);
		pDvmData->m_dTime = pRrpts[nIndex].tmRcv;
		CDvmValue *pTmRcvValue = new CDvmValue;
		pDvmData->AddNewChild(pTmRcvValue);
		pTmRcvValue->m_strID = _T("tm_rcv");
		SYSTEMTIME tmSys;
		CTime tm = pDvmData->m_dTime;
		tm.GetAsSystemTime(tmSys);
		pTmRcvValue->m_strValue.Format(_T("%d-%d-%d %d:%d:%d %d"), tmSys.wYear, tmSys.wMonth, tmSys.wDay, tmSys.wHour
			, tmSys.wMinute, tmSys.wSecond, pRrpts[nIndex].nTmRcvMs);

		pDvmData->m_nIndex = ((pRrpts[nIndex].dvIndex) << 16) + pRrpts[nIndex].dsIndex;

		if (g_nMmsDvmReports_Format_Type == 0)
		{
			mms_GetDvmLdName(pACSI_NODE,pRrpts[nIndex].ldIndex , pDvmData->m_strFormat);
		}
		else
		{
			mms_GetDvmDsName(pACSI_NODE,pRrpts[nIndex].ldIndex ,pRrpts[nIndex].dsIndex, pDvmData->m_strFormat);
		}
		
		//时间差
		if (pRrpts[nIndex].nTimeGapMs >= 0)
		{
			pDvmData->m_strStep.Format(_T("%d"), pRrpts[nIndex].nTimeGapMs);
		}

	}
}

void mms_GetFileDir(XMMS_FILE_SYS_OBJ *pFileDir, CDvmDataset *pDvmDataset)
{
// 	long nIndex = 0;
// 	long nCount = pFileDir->subFiles.numOfData;
// 	XMMS_FILE_SYS_OBJ *pSubDir = NULL;
// 	CDvmData *pDvmData = NULL;
// 	long nTmp = 0;
// 	CString strTmp;
// 
// 	for (nIndex=nCount-1; nIndex>=0; nIndex--)//保证最新的文件放在最前面
// 	{
// 		pSubDir = (XMMS_FILE_SYS_OBJ*)(pFileDir->subFiles.Datas[nIndex]);
// 
// 		if (pSubDir->nType)
// 		{
// 			mms_GetFileDir(pSubDir,pDvmDataset);
// 		} 
// 		else if (pSubDir->bIsNew)
// 	{
// 			pDvmData = new CDvmData();
// 			pDvmDataset->AddNewChild(pDvmData);	
// 			pDvmData->m_strName = get_all_filedir_path(pSubDir); //mms_string(&pSubDir->filedir.filename);
// 		pDvmData->m_strID = pDvmData->m_strName;
// 
// 			if (pSubDir->filedir.fsize < 1024)
// 			{
// 				pDvmData->m_strValue.Format(_T("%d B"), pSubDir->filedir.fsize);
// 			}
// 			else if (pSubDir->filedir.fsize < 1048576)
// 			{
// 				pDvmData->m_strValue.Format(_T("%.2f KB"), pSubDir->filedir.fsize / 1024.0);
// 			}
// 			else
// 			{
// 				pDvmData->m_strValue.Format(_T("%.2f MB"), pSubDir->filedir.fsize / 1048576.0);
// 			}
// 
// 			pDvmData->m_dTime = pSubDir->filedir.mtime;
// 		}
// 	}
}

long mms_GetDvmDatasetReports(ACSI_NODE *pACSI_NODE, CDvmDataset *pDvmDataset, CDvmDeviceMap *pDeviceMap)
{
	pDvmDataset->m_strName = dsID_Report;
	pDvmDataset->m_strID = dsID_Report;
	long nBeginIndex = pACSI_NODE->nReportBeginIndex;
	long nEndIndex = pACSI_NODE->nCurrReportIndex;
	long nCount = pACSI_NODE->nCurrReportCount;

	if (nEndIndex == nBeginIndex)
	{
		return nEndIndex;
	}

	if (nEndIndex > nBeginIndex)
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("mms_GetDvmDatasetReports:(%d - %d)"), nBeginIndex, nEndIndex);
		mms_GetDvmDatasetReports(pACSI_NODE/*->Reports*/, nBeginIndex, nEndIndex, pDvmDataset, pDeviceMap);
	}
	else
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("mms_GetDvmDatasetReports:(%d - %d)+(0 - %d)"), nBeginIndex,MAX_REPORT_COUNT, nEndIndex);
		mms_GetDvmDatasetReports(pACSI_NODE/*->Reports*/, nBeginIndex, MAX_REPORT_COUNT , pDvmDataset, pDeviceMap);
		mms_GetDvmDatasetReports(pACSI_NODE/*->Reports*/, 0, nEndIndex, pDvmDataset, pDeviceMap);
	}

	return nEndIndex;
}

void mms_GetDvmData(tagDA *pDA, CDvmData *pDvmData)
{
	pDvmData->m_strName = mms_GetDADesc(pDA);

	CDvmMapObject *pMapObj = (CDvmMapObject*)pDA->dwDsMapObj;
	
	if (pMapObj != NULL)
	{
		pDvmData->m_strName = pMapObj->m_strName;
		pDvmData->m_strID   = pMapObj->m_strID;
	}
	else
	{
		if (pDvmData->m_strName.GetLength() < 1)
		{
#ifdef _use_mms_string
			pDvmData->m_strName = mms_string(&pDA->DADescri.Value.string);
#else
			pDvmData->m_strName = pDA->DADescri.Value.string;
#endif
			pDvmData->m_strName.TrimRight();
		}

#ifdef _use_mms_string
		pDvmData->m_strID = mms_string(&pDA->DAValue.mmsName);
#else
		pDvmData->m_strID = pDA->DAValue.mmsName;
#endif
	}

	pDvmData->m_strDataType = pDA->DataType;
	mms_ParseUnit(pDA->DAUnite.Value.i, pDvmData->m_strUnit);
	mms_GetDAValue(pDA, pDvmData->m_strValue);
	mms_GetMaxValue(pDA, pDvmData->m_strMax);
	mms_GetMinValue(pDA, pDvmData->m_strMin);
	
	for (long nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
	{
		CDvmValue *pValue = new CDvmValue();
		pDvmData->AddNewChild(pValue);
		mms_GetDvmDataValue(&pDA->pSubDA[nIndex], pValue);
	}
}

void mms_GetDvmLog(LD_JOURNAL_DATA *pJournalData,CDvmLog *pDvmLog)
{
// 	CString strTmp;
// 	tagEVENTTIME tmEvent;
// 	MMS_UTC_TIME tmUtc;
// 	pDvmLog->m_strID = "0x";
// 
// 	for (int nLenth = 0;nLenth<8;nLenth++)//EntryID
// 	{
// 		strTmp.Format("%02X",(ST_UCHAR)pJournalData->EntryID[nLenth]);
// 		pDvmLog->m_strID += strTmp;
// 	}
// 
// 	pDvmLog->m_strName = pDvmLog->m_strID;
// 	pDvmLog->m_strLogCtrl = mms_string(&pJournalData->LogCtrl);
// 	pDvmLog->m_strDataset = mms_string(&pJournalData->DataSetName);
// 
// 	asn1_convert_btod_to_utc(&pJournalData->occur_time, &tmUtc);
// 	Convert_UTC_To_BCD(&tmEvent, tmUtc);//先将其转成tagEVENTTIME 
// 
// 	SYSTEMTIME tmSys;
// 	ZeroMemory(&tmSys, sizeof(tmSys));
// 	tmSys.wYear = tmEvent.year;
// 	tmSys.wMonth = tmEvent.month;
// 	tmSys.wDay = tmEvent.day;
// 	tmSys.wHour = tmEvent.hour;
// 	tmSys.wMinute = tmEvent.minute;
// 	tmSys.wSecond = tmEvent.second;
// 	tmSys.wMilliseconds = tmEvent.ms;//赋值给SYSTEMTIME
// 
// 	CTime tm2(tmSys);//转换为CTime
// 	pDvmLog->m_dCurrTime = (double)tm2.GetTime();
// 
// 	for (int nIndex=0; nIndex<pJournalData->numData; nIndex++)
// 	{
// 		CDvmData *pDvmData = new CDvmData();
// 		pDvmLog->AddNewChild(pDvmData);
// 		mms_GetDvmData(&pJournalData->DAValue[nIndex], pDvmData);
// 	}
}

#ifdef _tagRpt_use_DA_ref

// 
// BOOL mms_GetDASubValueRpt(tagDA *pSubDA,long nCount, /*const CString &strValueID,*/ CString &strValue, tagRptValue *pRptValue)
// {
// 	//CString strTemp;
// 	//long nLen = strValueID.GetLength();
// 	BOOL bFind = FALSE;
// 
// 	if (nCount == 1)
// 	{
// 		bFind = TRUE;
// 		mms_GetValue(pRptValue->Value, pSubDA->DataType, strValue);
// 	}
// 	else
// 	{
// 		for (long nIndex=0; nIndex<nCount; nIndex++)
// 		{
// 			if (strcmp(pSubDA->DataType, "STRUCT") == 0)
// 			{
// 				if (mms_GetDASubValueRpt(pSubDA->pSubDA, pSubDA->nSubDANum, strValue, pRptValue))
// 				{
// 					bFind = TRUE;
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				if (mms_Is_SubDA_Value(pSubDA))
// 				{
// 					bFind = TRUE;
// 					strValue = mms_GetValue(&pSubDA->DAValue, pSubDA->DataType);
// 					break;
// 				}
// 			}
// 
// 			pSubDA++;
// 		}
// 	}
// 
// 	return bFind;
// }
void mms_GetDAValueRpt(tagDA *pDA, CString &strText, tagRptValue *pRptValue)
{
	if (pDA == NULL)
	{
		strText.Empty();
	}

	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		mms_GetDASubValueRpt(pDA->pSubDA,pDA->nSubDANum, /*_T("stVal"),*/ strText, pRptValue);
	}
	else
	{
		mms_GetValue(&pRptValue->Value,pDA->DataType, strText);
	}
}


inline CString mms_GetDADescRpt(tagDA *pDA)
{
	CString strText;

#ifdef _use_mms_string
	strText.Format("%s", mms_string(&pDA->DADescri.Value.string));
#else
	strText.Format("%s", pDA->DADescri.Value.string);
#endif

	return strText;
}

void mms_GetDvmDataValueRpt(tagDA *pDA, CDvmValue *pDvmValue, tagRptValue **ppRptValue)
{
	CDvmMapObject *pMapObj = (CDvmMapObject*)pDA->dwDsMapObj;

	if ((pMapObj != NULL)&&(!g_nDvmNameIsStd))//zhouhj 20200210
	{
		pDvmValue->m_strID   = pMapObj->m_strID;
	}
	else
	{
#ifdef _use_mms_string
		pDvmValue->m_strID = mms_string(&pDA->DAValue.mmsName);
#else
		pDvmValue->m_strID = pDA->DAValue.mmsName;
#endif
	}

	pDvmValue->m_strDataType = pDA->DataType;

#ifdef _tagRpt_use_DA_ref
	tagRptValue *pRptValue = *ppRptValue;
	mms_GetValue(&pRptValue->Value, pDA->DataType, pDvmValue->m_strValue);

	if (mms_is_da_basic(pDA))
	{
		*ppRptValue = *ppRptValue + 1;
	}
#else
	mms_GetValue(&pDA->DAValue, pDA->DataType, pDvmValue->m_strValue);
#endif

	CDvmValue *pNew = NULL;

	if (pDA->nSubDANum == 0)
	{
		return;
	}

	for (long nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
	{
		pNew = new CDvmValue();
		pDvmValue->AddNewChild(pNew);
		mms_GetDvmDataValueRpt(pDA->pSubDA+nIndex, pNew, ppRptValue);
	}
}


void mms_GetDvmDataRpt(tagDA *pDA, tagRptValue *pRptValue, CDvmData *pDvmData)
{
	pDvmData->m_strName = mms_GetDADescRpt(pDA);

	CDvmMapObject *pMapObj = (CDvmMapObject*)pDA->dwDsMapObj;

	if ((pMapObj != NULL)&&(!g_nDvmNameIsStd))
	{
		pDvmData->m_strName = pMapObj->m_strName;
		pDvmData->m_strID   = pMapObj->m_strID;
	}
	else
	{
		if (pDvmData->m_strName.GetLength() < 1)
		{
#ifdef _use_mms_string
			pDvmData->m_strName = mms_string(&pDA->DADescri.Value.string);
#else
			pDvmData->m_strName = pDA->DADescri.Value.string;
#endif
			pDvmData->m_strName.TrimRight();
		}

#ifdef _use_mms_string
		pDvmData->m_strID = mms_string(&pDA->DAValue.mmsName);
#else
		pDvmData->m_strID = pDA->DAValue.mmsName;
#endif
	}

	pDvmData->m_strDataType = pDA->DataType;
	mms_ParseUnit(pDA->DAUnite.Value.i, pDvmData->m_strUnit);

#ifdef _tagRpt_use_DA_ref
	mms_GetDAValueRpt(pDA, pDvmData->m_strValue, pRptValue);

	if (mms_is_da_basic(pDA))
	{
		pRptValue = pRptValue + 1;
	}
#else
	mms_GetDAValue(pDA, pDvmData->m_strValue);
#endif

	mms_GetMaxValue(pDA, pDvmData->m_strMax);
	mms_GetMinValue(pDA, pDvmData->m_strMin);//zhouhj 20181018

	for (long nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
	{
		CDvmValue *pValue = new CDvmValue();
		pDvmData->AddNewChild(pValue);
		mms_GetDvmDataValueRpt(&pDA->pSubDA[nIndex], pValue, &pRptValue);
	}
}

void mms_EntryID_To_i64(BYTE *pEntryID, __int64 &n64EntryID)
{
	int nIndex = 0;

	for (nIndex=0; nIndex<8; nIndex++)
	{
		n64EntryID = n64EntryID << 8;
		n64EntryID += *pEntryID;
		pEntryID++;
	}
}

void mms_GetDvmDataRpt(tagRpt *pRpt, CDvmData *pDvmData)
{
	mms_GetDvmDataRpt(pRpt->pDaRef, pRpt->Value, pDvmData);
}
#endif

void mms_GetDvmDataValue(tagDA *pDA, CDvmValue *pDvmValue)
{
	CDvmMapObject *pMapObj = (CDvmMapObject*)pDA->dwDsMapObj;

	if (pMapObj != NULL)
	{
		pDvmValue->m_strID   = pMapObj->m_strID;
	}
	else
	{
#ifdef _use_mms_string
		pDvmValue->m_strID = mms_string(&pDA->DAValue.mmsName);
#else
		pDvmValue->m_strID = pDA->DAValue.mmsName;
#endif
	}

	pDvmValue->m_strDataType = pDA->DataType;
	mms_GetValue(&pDA->DAValue, pDA->DataType, pDvmValue->m_strValue);
	//pDvmValue->m_strValue = mms_GetValue(&pDA->DAValue, pDA->DataType);
	CDvmValue *pNew = NULL;

	if (pDA->nSubDANum == 0)
	{
		return;
	}

	for (long nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
	{
		pNew = new CDvmValue();
		pDvmValue->AddNewChild(pNew);
		mms_GetDvmDataValue(pDA->pSubDA+nIndex, pNew);
	}
}

long mms_SetByDvmDataset(const CDvmDataset *pDvmDataset, LD_DATASET_INFO *pDataset, BOOL bUseName, BOOL bUseID)
{
	if (!bUseID && !bUseName)
	{
		bUseID = TRUE;
	}

	long nDataCount = 0; //2018-10-8  lijq
	CDvmData *pDvmData = NULL;
	POS pos = pDvmDataset->GetHeadPosition();
	tagDA *pData = NULL;
	tagDA *pDatas = pDataset->DataSet;
	long nCount= pDataset->numData;
	CString strMsg;

	while (pos != NULL)
	{
		pData = NULL;
		pDvmData = (CDvmData *)pDvmDataset->GetNext(pos);

		if (bUseID)
		{
			pData = mms_FindDataByID(pDatas, nCount, pDvmData->m_strID);
		}

		if (pData != NULL)
		{
			pDvmData->m_dwReserved = 1;
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("修改数据【%s】【%s】"), pDvmData->m_strName, pDvmData->m_strValue);
			mms_SetByDvmData(pDvmData, pData);
			nDataCount++; //2018-10-8  lijq
			continue;
		}

		if (bUseName)
		{
			pData = mms_FindDataByName(pDatas, nCount, pDvmData->m_strName);
		}

		if (pData != NULL)
		{
			pDvmData->m_dwReserved = 1;
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("修改数据【%s】【%s】【%s】"), pDvmData->m_strName, pDvmData->m_strID, pDvmData->m_strValue);
			mms_SetByDvmData(pDvmData, pData);
			nDataCount++; //2018-10-8  lijq
			continue;
		}
	}

	return nDataCount; //2018-10-8  lijq
}

void mms_ViewDvmDataset(CDvmDataset *pDvmDataset)
{
	CDvmData *pDvmData = NULL;
	POS pos = pDvmDataset->GetHeadPosition();

	while (pos != NULL)
	{
		pDvmData = (CDvmData *)pDvmDataset->GetNext(pos);
		
		if (pDvmData->m_dwReserved != 1)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("数据【%s】【%s】不存在"), pDvmData->m_strName, pDvmData->m_strID);//_T("数据【%s】【%s】不存在")
		}
	}
}
void mms_SetByDvmData(CDvmData *pDvmData, tagDA *pData)
{
	if (pData == NULL)
	{
		return;
	}

	pData->bModify = TRUE;

	if (strcmp(pData->DataType ,"STRUCT") == 0)
	{
		int nIndex=0;

		for (nIndex=0; nIndex<pData->nSubDANum; nIndex++)
		{
			if (mms_SetDASubValue(pData->pSubDA + nIndex, /*"stVal",*/ pDvmData->m_strValue))
			{
				break;
			}
		}
	}
	else
	{
		mms_SetValue(&pData->DAValue, pDvmData->m_strValue, pData->DataType);
	}
}

void mms_SetValue(tagDA *pData, long nValue)
{
	if (strcmp(pData->DataType ,"STRUCT") == 0)
	{
		int nIndex=0;

		for (nIndex=0; nIndex<pData->nSubDANum; nIndex++)
		{
			if (mms_SetDASubValue(pData->pSubDA + nIndex, /*"stVal",*/ nValue))
			{
				break;
			}
		}
	}
	else
	{
		mms_SetValue(&pData->DAValue, nValue, pData->DataType);
	}
}

tagDAValue* mms_FindValue(tagDA *pData, const CString &strTagID)
{
	if (strTagID == g_bstrPpEngineTag_Name)
	{
		return &pData->DADescri;
	}

	if (strTagID == g_bstrPpEngineTag_ID)
	{
		return &pData->DADescri;
	}

	if (strTagID == g_bstrPpEngineTag_Value)
	{
		return &pData->DADescri;
	}

	if (pData->pSubDA != NULL)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex<pData->nSubDANum; nIndex++)
		{
#ifdef _use_mms_string
			if (strstr(mms_string(&pData->pSubDA[nIndex].DAValue.mmsName), strTagID) != NULL)
#else
			if (strstr(pData->pSubDA[nIndex].DAValue.mmsName, strTagID) != NULL)
#endif
			{
				return &pData->pSubDA[nIndex].DAValue;
			}
		}
	}

	return NULL;
}

void mms_SetValue(tagDA *pData, const CString &strTagID, const CString &strValue)
{
	tagDAValue *pValue = mms_FindValue(pData, strTagID);

	if (pValue != NULL)
	{
		mms_SetValue(pValue, strValue, pData->DataType);
	}
}

void mms_GetValue(tagValue *pValue, char *strDataType, CString &strValue)
{
	if (strcmp(strDataType, "BOOL") == 0)
	{
		strValue.Format("%d", pValue->u);
	}
	else if (strcmp(strDataType, "INT") == 0)
	{
		strValue.Format("%d", pValue->i);
	}
	else if (strcmp(strDataType, "UINT") == 0)
	{
		strValue.Format("%d", pValue->u);
	}
	else if (strcmp(strDataType, "FLOAT") == 0)
	{
		strValue.Format("%f", pValue->f);
	}
	else if (strcmp(strDataType, "BIT_STR") == 0)
	{
		//strValue = pValue->name;
#ifdef _use_mms_string
		strValue = mms_string(&pValue->string);
#else
		DWORD dwData = pValue->i;
		dwData >>= 6;
		strValue.Format(_T("%d"),dwData);
#endif
	}
	else if ((strcmp(strDataType, "V_STR") == 0)||((strcmp(strDataType ,"UTF8_STR")== 0)))
	{
		//strValue = pValue->name;
		strValue = mms_string(&pValue->string);
	}
	else if (strcmp(strDataType, "UTC_TIME") == 0)
	{
		tagEVENTTIME lpTimeBCD;
		Convert_UTC_To_BCD(&lpTimeBCD, pValue->utctime);

		strValue.Format("%d-%d-%d %d-%d-%d-%d",lpTimeBCD.year,lpTimeBCD.month,lpTimeBCD.day,
			lpTimeBCD.hour,lpTimeBCD.minute,lpTimeBCD.second,lpTimeBCD.ms);
	}
	else
	{
	}
}

void mms_GetValue(tagDAValue *pDaValue, char *strDataType, CString &strValue)
{
	mms_GetValue(&pDaValue->Value, strDataType, strValue);
}

CString mms_GetValue(tagDAValue *pDaValue, const CString &strDataType)
{
	CString strValue;
	
	if (strDataType==_T("BOOL"))
	{
		strValue.Format("%d", pDaValue->Value.u);
	}
	else if (strDataType==_T("INT"))
	{
		strValue.Format("%d", pDaValue->Value.i);
	}
	else if (strDataType==_T("UINT"))
	{
		strValue.Format("%d", pDaValue->Value.u);
	}
	else if (strDataType==_T("FLOAT"))
	{
		strValue.Format("%f", pDaValue->Value.f);//zhouhj 20191025  ("%.5f"
	}
	else if (strDataType == _T("OCT_STR"))//zhouhj 20180516 此种类型时pDaValue->Value.string 无值，也不为NULL
	{
		strValue = mms_string(&pDaValue->Value.string);
	}
	else if (strDataType.Find(_T("_STR")) > 0)
	{
#ifdef _use_mms_string
		strValue = mms_string(&pDaValue->Value.string);
#else
		DWORD dwData = pDaValue->Value.i;
		dwData >>= 6;
		strValue.Format(_T("%d"),dwData);
#endif
	}
	else if (strDataType == _T("UTC_TIME"))
	{
		tagEVENTTIME lpTimeBCD;
		Convert_UTC_To_BCD(&lpTimeBCD, pDaValue->Value.utctime);

		strValue.Format("%d-%d-%d %d-%d-%d-%d",lpTimeBCD.year,lpTimeBCD.month,lpTimeBCD.day,
			lpTimeBCD.hour,lpTimeBCD.minute,lpTimeBCD.second,lpTimeBCD.ms);
	}
	else
	{
	}

	return strValue;
}

float mms_GetValueFloat(tagDAValue *pDaValue, const CString &strDataType)
{
	if (strDataType==_T("BOOL"))
	{
		return (float)pDaValue->Value.u;
	}
	else if (strDataType==_T("INT"))
	{
		return (float)pDaValue->Value.i;
	}
	else if (strDataType==_T("UINT"))
	{
		return (float)pDaValue->Value.u;
	}
	else if (strDataType==_T("FLOAT"))
	{
		return pDaValue->Value.f;
	}
	else if (strDataType==_T("BIT_STR"))
	{
		return 0;
	}
	else if (strDataType == _T("UTC_TIME"))
	{
		return 0;
	}
	else
	{
	}

	return 0;
}


void mms_CString_to_utc_time(const CString &strTime, MMS_UTC_TIME  &utctime)
{
	SYSTEMTIME tmSys;
	MMS_BTIME6 bTm6;
	MMS_BTOD btod;

	ZeroMemory(&tmSys, sizeof(tmSys));
	StringToSystemTime(strTime, tmSys);
	CTime tm2(tmSys);
	asn1_convert_timet_to_btime6(tm2.GetTime(), &bTm6);
	btod.form = MMS_BTOD6;
	btod.day = bTm6.day;
	btod.ms = bTm6.ms;

	asn1_convert_btod_to_utc(&btod, &utctime);
}

void mms_u64Time_to_utc_time(uint64_t u64Time, MMS_UTC_TIME  &utctime)
{
	MMS_BTIME6 bTm6;
	MMS_BTOD btod;
	asn1_convert_timet_to_btime6(u64Time/1000, &bTm6);
	btod.form = MMS_BTOD6;
	btod.day = bTm6.day;
	btod.ms = bTm6.ms;
	btod.ms += u64Time%1000;

	asn1_convert_btod_to_utc(&btod, &utctime);
}

void mms_SetValue(tagDAValue *pDaValue, const CString &strValue, const CString &strDataType)
{
	if (strDataType==_T("BOOL"))
	{
		pDaValue->Value.u = atoi(strValue);
		return;
	}

	if (strDataType==_T("INT"))
	{
		pDaValue->Value.i = atoi(strValue);
		return;
	}

	if (strDataType==_T("UINT"))
	{
		pDaValue->Value.u = atoi(strValue);
		return;
	}

	if (strDataType==_T("FLOAT"))
	{
#ifdef _UNICODE
		pDaValue->Value.f = _wtof(strValue);
#else
		pDaValue->Value.f = atof(strValue);
#endif
		return;
	}

	if ((strDataType==_T("BIT_STR"))||(strDataType==_T("UTF8_STR")))
	{
#ifdef _use_mms_string
		mms_str_set(&pDaValue->Value.string, strValue);
#else
		strcpy(pDaValue->Value.string,strValue);
#endif
		return;
	}

	if (strDataType==_T("UTC_TIME"))
	{
		try
		{
			mms_CString_to_utc_time(strValue, pDaValue->Value.utctime);
		}
		catch (...)
		{
			CString strMmsName;
			strMmsName = mms_string (&pDaValue->mmsName);
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("%s:%s  错误"), strMmsName, strValue);
		}
	
	
		return;
	}
}

void mms_SetValue(tagDAValue *pDaValue, long nValue, const CString &strDataType)
{

	if (strDataType==_T("BOOL"))
	{
		pDaValue->Value.u = (unsigned char)nValue;
		return;
	}

	if (strDataType==_T("INT"))
	{
		pDaValue->Value.i = nValue;
		return;
	}

	if (strDataType==_T("UINT"))
	{
		pDaValue->Value.u = (unsigned char)nValue;
		return;
	}

	if (strDataType==_T("FLOAT"))
	{
		pDaValue->Value.f = nValue;
		return;
	}
}

void mms_GeLimitValue(tagDA *pDA, BOOL bMax, CString &strText)
{
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (strstr(pDA->DataType,"STRUCT"))
	{
		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];
#ifdef _use_mms_string
			char *mmsName = mms_string(&pSubDA->DAValue.mmsName);
#else
			char *mmsName = pSubDA->DAValue.mmsName;
#endif

			if (strstr(mmsName,"$mag$f")||
				strstr(mmsName,"stVal")||
				strstr(mmsName,"setMag")||
				strstr(mmsName,"setVal")||
				strstr(mmsName,"general"))
			{
				mms_GeLimitValue(pSubDA, bMax, strText);
				return;
			}
		}
	}	

	if (bMax)
	{
		mms_GetValue(&pDA->MaxVal, pDA->DataType, strText);
	}
	else
	{
		mms_GetValue(&pDA->MinVal, pDA->DataType, strText);
	}
#endif
}

BOOL mms_GetValueDataType(tagDA *pDA ,CString &strDataType)
{
	if (strstr(pDA->DataType,"STRUCT"))
	{
		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];
#ifdef _use_mms_string
			char *mmsName = mms_string(&pSubDA->DAValue.mmsName);
#else
			char *mmsName = pSubDA->DAValue.mmsName;
#endif

			if (strstr(mmsName,"$mag$f")||
				strstr(mmsName,"stVal")||
				strstr(mmsName,"setMag")||
				strstr(mmsName,"setVal")||
				strstr(mmsName,"general"))
			{
				return mms_GetValueDataType(pSubDA ,strDataType);
			}
		}
	}
	else
	{
		strDataType = pDA->DataType;
		return TRUE;
	}

	return FALSE;
}

CString mms_GetValueByDataType(tagValue *pTagValue ,const CString &strDataType)
{
	CString strValue = "";

	if (strDataType == "BOOL")
	{
		strValue.Format("%u" ,pTagValue->u);
	}
	else if (strDataType == "INT")
	{
		strValue.Format("%d" ,pTagValue->i);
	}
	else if (strDataType == "UINT")
	{
		strValue.Format("%u" ,pTagValue->u);
	}
	else if (strDataType == "FLOAT")
	{
		strValue.Format("%f" ,pTagValue->f);
	}
	else if (strDataType == "UTF8_STR")
	{
		strValue.Format("%s" ,mms_string(&pTagValue->string));
	}
	else if (strDataType == "V_STR")
	{
		strValue.Format("%s" ,mms_string(&pTagValue->string));
	}

	return strValue;
}

CString mms_GeLimitValue(tagDA *pDA, BOOL bMax)
{
	CString strText;
	mms_GeLimitValue(pDA, bMax, strText);
	return strText;
}

CString mms_GetMinValue(tagDA *pDA)
{
	return mms_GeLimitValue(pDA, FALSE);
}

void mms_GetMinValue(tagDA *pDA, CString &strText)
{
	mms_GeLimitValue(pDA, FALSE, strText);
}
CString mms_GetMaxValue(tagDA *pDA)
{
	CString strText;
	mms_GeLimitValue(pDA, TRUE, strText);
	return strText;
}

void mms_GetMaxValue(tagDA *pDA, CString &strText)
{
	return mms_GeLimitValue(pDA, TRUE, strText);
}

void mms_SetLimitValue(tagDA *pDA,const CString &strValue, BOOL bMax)
{
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (strstr(pDA->DataType,"STRUCT"))
	{
		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];
#ifdef _use_mms_string
			char *mmsName = mms_string(&pSubDA->DAValue.mmsName);
#else
			char *mmsName = pSubDA->DAValue.mmsName;
#endif

			if (strstr(mmsName,"$mag$f")||
				strstr(mmsName,"stVal")||
				strstr(mmsName,"setMag")||
				strstr(mmsName,"setVal")||
				strstr(mmsName,"general"))
			{
				mms_SetLimitValue(pSubDA, strValue, bMax);
			}
		}
	}	

	if (bMax)
	{
		mms_SetValue(&pDA->MaxVal, strValue, pDA->DataType);
	}
	else
	{
		mms_SetValue(&pDA->MinVal, strValue, pDA->DataType);
	}
#endif
}

void mms_SetStepSizeValue(tagDA *pDA,const CString &strValue)
{
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (strValue.GetLength() == 0)
	{
		return;
	}

	if (strstr(pDA->DataType,"STRUCT"))
	{
		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];
#ifdef _use_mms_string
			char *mmsName = mms_string(&pSubDA->DAValue.mmsName);
#else
			char *mmsName = pSubDA->DAValue.mmsName;
#endif

			if (strstr(mmsName,"$mag$f")||
				strstr(mmsName,"stVal")||
				strstr(mmsName,"setMag")||
				strstr(mmsName,"setVal")||
				strstr(mmsName,"general"))
			{
				mms_SetStepSizeValue(pSubDA, strValue);
			}
		}
	}	
	else
	{
#ifdef _use_mms_string
		mms_str_set(&pDA->StepSize.mmsName, "stepSize");
#else
		strcpy(pDA->StepSize.mmsName, "stepSize");
#endif
		mms_SetValue(&pDA->StepSize, strValue, pDA->DataType);
	}

#endif
}

void mms_SetMinValue(tagDA *pDA, const CString &strValue)
{
	mms_SetLimitValue(pDA, strValue, FALSE);
}

void mms_SetMaxValue(tagDA *pDA, const CString &strValue)
{
	mms_SetLimitValue(pDA, strValue, TRUE);
}


void mms_GetAllDataset(ACSI_NODE *pDevice, char *pszDsKey, long &nCount, LD_DATASET_INFO **ppDataSetInfo)
{
	long nLdIndex = 0;
	long nDsIndex = 0;
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDs = NULL;
	nCount = 0;

	for (nLdIndex=0; nLdIndex<pDevice->numLD; nLdIndex++)
	{
		pLdevice = &pDevice->LD[nLdIndex];

		for (nDsIndex=0; nDsIndex<pLdevice->numDaSet; nDsIndex++)
		{
			pDs = &pLdevice->DataInfo[nDsIndex];
			
			if (strstr(pDs->DataSetID, pszDsKey) != NULL)
			{
				ppDataSetInfo[nCount] = pDs;
				nCount++;
			}
		}
	}
}

char* mms_GetDatasetKey(const CString &strDsID)
{
// 	char *pKey = theMmsApi->mms_GetDatasetKey(strDsID);
// 
// 	if (pKey != NULL)
// 	{
// 		if (strlen(pKey) > 0)
// 		{
// 			return pKey;
// 		}
// 	}
// 
// 	if (strDsID.Find( key_dsParameter) >= 0)
// 		return key_dsParameter;
// 	else if (strDsID.Find( key_dsSetting) >= 0)
// 		return key_dsSetting;
// 	else if (strDsID.Find( key_dsRelayEna) >= 0)
// 		return key_dsRelayEna;
// 	else if (strDsID.Find( key_dsRelayDin) >= 0)
// 		return key_dsRelayDin;
// 	else if (strDsID.Find( key_dsWarning) >= 0)
// 		return key_dsWarning;
// 	else if (strDsID.Find( key_dsTripInfo) >= 0)
// 		return key_dsTripInfo;
// 	else if (strDsID.Find( key_dsAlarm) >= 0)
// 		return key_dsAlarm;
// 	else if (strDsID.Find( key_dsParameter) >= 0)
// 		return key_dsParameter;
// 	else if (strDsID.Find( key_dsSetGrpNum) >= 0)
// 		return key_dsSetGrpNum;
// 	else if (strDsID.Find( key_dsSetGrpNum) >= 0)
// 		return key_dsSetGrpNum;
// 	else if (strDsID.Find( key_dsDeviceState) >= 0)
// 		return key_dsDeviceState;
// 	else if (strDsID.Find( key_dsCommState) >= 0)
// 		return key_dsCommState;
// 	else if (strDsID.Find( key_dsRelayBlk) >= 0)
// 		return key_dsRelayBlk;
// 	else if (strDsID.Find( key_dsRelayFunEn) >= 0)
// 		return key_dsRelayFunEn;
// 	else if (strDsID.Find( key_dsRelayState) >= 0)
// 		return key_dsRelayState;
// 	else
		return NULL;
}

//CSIUnit mmsg_SIUnit;
//CMultiplier mmg_Multiplier;

CString mms_ParseUnit(long nValue)
{
	CString strText;
	mms_ParseUnit(nValue, strText);
	return strText;
}

void mms_ParseUnit(long nValue, CString &strText)
{
// 	ST_CHAR*pValue = (ST_CHAR*)&nValue;
// 
// 	if (pValue)
// 	{
// 		CString strUnit = "";
// 		CString strMuti = "";
// 		int nIndex = *pValue;
// 		strUnit = mmsg_SIUnit.GetSIUnite(nIndex);
// 
// 		nIndex = *(++pValue);
// 		strMuti = mmg_Multiplier.GetMultiplierUnite(nIndex);
// 		strText.Format("%s%s",strMuti,strUnit);
// 	}
}

long mms_GetUnitIndex(CString strUnite)
{
	long lUnite=65535;
	CString strText;

	return lUnite;
}

long mms_FindDatasetByKey(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, LD_NODE** ppRetLdevice, long *pnLdIndex, LD_DATASET_INFO **parrDataset, long *pDatasetIndex)
{
// 	char pszDatasetKey[MAX_NAME_LEN];
// 	CString_to_char(strDatasetPath, pszDatasetKey);
// 	long nDsFindIndex = 0;
// 
// 	LD_NODE *pLdevice = NULL;
// 	long nLdIndex = 0;
// 	long nDsIndex = 0;
// 	LD_DATASET_INFO *p = NULL;
// 
// 	for (nLdIndex=0; nLdIndex<pACSI_NODE->numLD; nLdIndex++)
// 	{
// 		pLdevice = &pACSI_NODE->LD[nLdIndex];
// 
// 		for (nDsIndex=0; nDsIndex<pLdevice->numDaSet; nDsIndex++)
// 		{
// 			p = pLdevice->DataInfo+nDsIndex;
// 
// 			if (strstr(p->DataSetID, pszDatasetKey) != NULL)
// 			{
// 				parrDataset[nDsFindIndex] = p;
// 				pDatasetIndex[nDsFindIndex] = nDsIndex;
// 				nDsFindIndex++;
// 			}
// 		}
// 
// 		if (nDsFindIndex > 0)
// 		{
// 			*pnLdIndex = nLdIndex;
// 			*ppRetLdevice = pLdevice;
// 			break;
// 		}
// 	}
//
//	return nDsFindIndex;
	return 0;
}

LD_DATASET_INFO* mms_FindDatasetEx(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, LD_NODE** ppRetLdevice, CString *pStrRetDatasetPath)
{
	LD_NODE *pLdevice = NULL;
	CString strTemp;
	long nLdIndex = 0;
	long nDsIndex = 0;
	LD_DATASET_INFO *pFind = NULL;
	LD_DATASET_INFO *p = NULL;
	long nLen = 0;
	CString strPath;

	for (nLdIndex=0; nLdIndex<pACSI_NODE->numLD; nLdIndex++)
	{
		pLdevice = &pACSI_NODE->LD[nLdIndex];

		for (nDsIndex=0; nDsIndex<pLdevice->numDaSet; nDsIndex++)
		{
			strTemp = pLdevice->LDName;
			strTemp += _T("$");
			p = &pLdevice->DataInfo[nDsIndex];
			strTemp += p->DataSetID;

			if (strTemp == strDatasetPath)
			{
				pFind = p;
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	if (pFind != NULL)
	{
		if (pStrRetDatasetPath != NULL)
		{
			*pStrRetDatasetPath = strTemp;
		}

		if (ppRetLdevice != NULL)
		{
			*ppRetLdevice = pLdevice;
		}
	}

	return pFind;
}


LD_DATASET_INFO* mms_FindDataset(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, CString *pStrRetDatasetPath)
{
	LD_NODE *pLdevice = NULL;
	return mms_FindDatasetEx(pACSI_NODE, strDatasetPath, &pLdevice, pStrRetDatasetPath);
}

LD_DATASET_INFO* mms_FindDataset(LD_NODE *pLdevice, const CString &strDatasetPath)
{
	LD_DATASET_INFO *pFind = NULL;
	LD_DATASET_INFO *p = NULL;
	CString strTemp;
	long nIndex = 0;
	long nLen = 0;

	for (nIndex=0; nIndex<pLdevice->numDaSet; nIndex++)
	{
		p = &pLdevice->DataInfo[nIndex];
		strTemp = p->DataSetID;
		strTemp += _T("$");
		nLen = strTemp.GetLength();

		if (strDatasetPath == strTemp)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL mms_FindDatasetIndex(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, long &nRetLdIndex, long &nRetDatasetIndex)
{
	LD_NODE *pLdevice = NULL;
	CString strTemp;
	long nLdIndex = 0;
	long nDsIndex = 0;
	LD_DATASET_INFO *pFind = NULL;
	LD_DATASET_INFO *p = NULL;
	long nLen = 0;
	CString strPath;

	for (nLdIndex=0; nLdIndex<pACSI_NODE->numLD; nLdIndex++)
	{
		pLdevice = &pACSI_NODE->LD[nLdIndex];

		for (nDsIndex=0; nDsIndex<pLdevice->numDaSet; nDsIndex++)
		{
			strTemp = pLdevice->LDName;
			strTemp += _T("$");
			p = &pLdevice->DataInfo[nDsIndex];
			strTemp += p->DataSetID;
			if (strTemp == strDatasetPath)
			{
				pFind = p;
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	if (pFind != NULL)
	{
		nRetLdIndex = nLdIndex;
		nRetDatasetIndex = nDsIndex;
	}

	return (pFind != NULL);
}


tagDA* mms_FindData(ACSI_NODE *pACSI_NODE, const CString &strDataPath)
{
	CString strRetDatasetPath;
	LD_DATASET_INFO *pDataset = NULL;
	LD_NODE *pLdevice = NULL;

	return mms_FindData(pACSI_NODE, &pLdevice, &pDataset, strDataPath);
}

tagDA* mms_FindData(ACSI_NODE *pACSI_NODE, LD_NODE** ppRetLdevice, LD_DATASET_INFO** ppRetDataset,const CString &strDataPath)
{
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	CString strRetDatasetPath;

	pDataset = mms_FindDatasetEx(pACSI_NODE, strDataPath, &pLdevice, &strRetDatasetPath);

	if (pDataset == NULL)
	{
		return NULL;
	}

	long nLen = strRetDatasetPath.GetLength() + 1;
	CString strDataID = strDataPath.Mid(nLen);

	if (strDataID.GetLength() == 0)
	{
		return NULL;
	}

	tagDA *p = NULL;
	tagDA *pFind = NULL;
	long nIndex = 0;
	tagDA *pDatas = pDataset->DataSet;

	for (nIndex=0; nIndex<pDataset->numData; nIndex++)
	{
#ifdef _use_mms_string
		if (strDataID == mms_string(&pDatas[nIndex].DAValue.mmsName))
#else
		if (strDataID == pDatas[nIndex].DAValue.mmsName)
#endif
		{
			pFind = p;
			break;
		}
	}

	if (ppRetLdevice != NULL)
	{
		*ppRetLdevice = pLdevice;
	}

	if (ppRetDataset != NULL)
	{
		*ppRetDataset = pDataset;
	}

	return pFind;
}

tagDA* mms_FindDataByID(ACSI_NODE *pDevice, const CString &strDataID)
{
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	tagDA *pDA = NULL;
	tagDA *pFind = NULL;

	long nLd = 0, nDs = 0, nData = 0;

	for (nLd=0; nLd <pDevice->numLD; nLd++)
	{
		pLdevice = &pDevice->LD[nLd];

		for (nDs=0; nDs < pLdevice->numDaSet; nDs++)
		{
			pDataset = pLdevice->DataInfo + nDs;

			for (nData=0; nData<pDataset->numData; nData++)
			{
				pDA = pDataset->DataSet + nData;
				
#ifdef _use_mms_string
				if (strDataID == mms_string(&pDA->DAValue.mmsName) )
#else
				if (strDataID == pDA->DAValue.mmsName)
#endif
				{
					pFind = pDA;
					break;
				}
			}

			if (pFind != NULL)
			{
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	return pFind;
}

BOOL mms_FindDataByID(ACSI_NODE *pDevice, const CString &strDataID, long &nLdFind, long &nDsFind, long &nDaFind,BOOL bFilterLogDs)
{
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	tagDA *pDA = NULL;
	tagDA *pFind = NULL;

	long nLd = 0, nDs = 0, nData = 0;

	for (nLd=0; nLd <pDevice->numLD; nLd++)
	{
		pLdevice = &pDevice->LD[nLd];

		for (nDs=0; nDs < pLdevice->numDaSet; nDs++)
		{
			pDataset = pLdevice->DataInfo + nDs;

			if (bFilterLogDs)
			{
				if (strstr(pDataset->DataSetID,"LLN0$dsLog") != NULL)
				{
					continue;
				}
			}

			for (nData=0; nData<pDataset->numData; nData++)
			{
				pDA = pDataset->DataSet + nData;

#ifdef _use_mms_string
				if (strDataID == mms_string(&pDA->DAValue.mmsName) )
#else
				if (strDataID == pDA->DAValue.mmsName)
#endif
				{
					pFind = pDA;
					break;
				}
			}

			if (pFind != NULL)
			{
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	if (pFind != NULL)
	{
		nLdFind = nLd;
		nDsFind = nDs;
		nDaFind = nData;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL mms_FindDataByID(const char *strDsKey, ACSI_NODE *pDevice, const CString &strDataID, long &nLdFind, long &nDsFind, long &nDaFind)
{
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	tagDA *pDA = NULL;
	tagDA *pFind = NULL;

	long nLd = 0, nDs = 0, nData = 0;

	for (nLd=0; nLd <pDevice->numLD; nLd++)
	{
		pLdevice = &pDevice->LD[nLd];

		for (nDs=0; nDs < pLdevice->numDaSet; nDs++)
		{
			pDataset = pLdevice->DataInfo + nDs;

			if (strstr(pDataset->DataSetID, strDsKey) ==NULL)
			{
				continue;
			}

			for (nData=0; nData<pDataset->numData; nData++)
			{
				pDA = pDataset->DataSet + nData;

#ifdef _use_mms_string
				if (strDataID == mms_string(&pDA->DAValue.mmsName) )
#else
				if (strDataID == pDA->DAValue.mmsName)
#endif
				{
					pFind = pDA;
					break;
				}
			}

			if (pFind != NULL)
			{
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	if (pFind != NULL)
	{
		nLdFind = nLd;
		nDsFind = nDs;
		nDaFind = nData;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL mms_FindDataByID(ACSI_NODE *pDevice, const CString &strLdId, const CString &strDsId, const CString &strDataID
					  , long &nLdFind, long &nDsFind, long &nDaFind)
{
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDataset = NULL;
	tagDA *pDA = NULL;
	tagDA *pFind = NULL;

	long nLd = 0, nDs = 0, nData = 0;

	for (nLd=0; nLd <pDevice->numLD; nLd++)
	{
		pLdevice = &pDevice->LD[nLd];

		if (strLdId != pLdevice->LDName)
		{
			continue;
		}

		for (nDs=0; nDs < pLdevice->numDaSet; nDs++)
		{
			pDataset = pLdevice->DataInfo + nDs;

			if (strDsId != pDataset->DataSetID)
			{
				continue;
			}

			for (nData=0; nData<pDataset->numData; nData++)
			{
				pDA = pDataset->DataSet + nData;

#ifdef _use_mms_string
				if (strDataID == mms_string(&pDA->DAValue.mmsName) )
#else
				if (strDataID == pDA->DAValue.mmsName)
#endif
				{
					pFind = pDA;
					break;
				}
			}

			if (pFind != NULL)
			{
				break;
			}
		}

		if (pFind != NULL)
		{
			break;
		}
	}

	if (pFind != NULL)
	{
		nLdFind = nLd;
		nDsFind = nDs;
		nDaFind = nData;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

tagDA* mms_FindData(LD_NODE *pLdevice, const CString &strDataPath)
{
	LD_DATASET_INFO *pDataset = NULL;
	return mms_FindData(pLdevice, &pDataset, strDataPath);
}

tagDA* mms_FindData(LD_NODE *pLdevice, LD_DATASET_INFO** ppRetDataset,const CString &strDataPath)
{
	CString strRetDatasetPath;
	LD_DATASET_INFO *pDataset = mms_FindDataset(pLdevice, strDataPath);

	if (pDataset == NULL)
	{
		return NULL;
	}

	CString strTemp = pDataset->DataSetID;
	strTemp += _T("$");
	long nLen = strTemp.GetLength();
	strTemp = strDataPath.Mid(nLen);
	long nIndex = 0;
	tagDA *pDA = NULL;
	tagDA *pFind = NULL;

	for (nIndex=0; nIndex<pDataset->numData; nIndex++)
	{
		pDA = &(pDataset->DataSet[nIndex]);

#ifdef _use_mms_string
		if (strTemp == mms_string(&pDA->DAValue.mmsName) )
#else
		if (strTemp == pDA->DAValue.mmsName)
#endif
		{
			pFind = pDA;
			break;
		}
	}

	return pFind;
}

//BOOL g_nSetRunSGIndexState = 1;   //是否在设置当前运行区的状态中

BOOL mms_HasDatasetDataChanged(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
	ACSI_NODE *pDevice = Client61850_GetAcsiNode(nDeviceIndex);

	if (pDevice == NULL)
	{
		return FALSE;
	}

	if (pDevice->numLD <= nLDIndex)
	{
		return FALSE;
	}

	LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];

	if (pLD_NODE->numDaSet <= nDsIndex)
	{
		return FALSE;
	}

	LD_DATASET_INFO *pDatasetd = &pLD_NODE->DataInfo[nDsIndex];
	BOOL bChanged = FALSE;
	long nIndex=0;
	tagDA *pDA = NULL;

	for (nIndex=0; nIndex<pDatasetd->numData; nIndex++)
	{
		pDA = &pDatasetd->DataSet[nIndex];

		if (pDA->bModify)
		{
			bChanged = TRUE;
			break;
		}
	}

	return bChanged;
}


BOOL mms_Init_tagDataChangeDef_cmd(tagDataChangeDef *pDef, const CString &strPath, ULONG nHwnd, ULONG nMsgID, ULONG nCmdState, ULONG wParam, ULONG lParam)
{
	return TRUE;


}

void mms_RegisterDataChangedMsg(tagDataChangeDef  *ptagDataChangeDef, ACSI_NODE *pDevice, const CString &strPath, ULONG nHwnd, ULONG nMsgID)
{
	//2019-1-5  报文事件：增加报文名称判断
	if (strPath.Find('$') >= 0)
	{//如果是路径，则根据路径提取对象
		ptagDataChangeDef->pRefDA = mms_FindData(pDevice, strPath);

		if (ptagDataChangeDef->pRefDA == NULL)
		{
			ptagDataChangeDef->pRefDA = mms_FindDataByID(pDevice, strPath);
		}

		if (ptagDataChangeDef->pRefDA == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RegisterDataChangedMsg(%s)失败"), strPath);//_T("RegisterDataChangedMsg(%s)失败")
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RegisterDataChangedMsg(%s)成功"), strPath);//_T("RegisterDataChangedMsg(%s)成功")
		}
	}
	else
	{
		ptagDataChangeDef->pRefDA = NULL;
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RegisterDataChangedMsg(%s)成功"), strPath);//_T("RegisterDataChangedMsg(%s)成功")
	}

	CString_to_char(strPath, ptagDataChangeDef->PathName);
	ptagDataChangeDef->hMsgWnd = nHwnd;
	ptagDataChangeDef->nMsg = nMsgID;
	ptagDataChangeDef->nCmdState = 0;
	ptagDataChangeDef->wParam = 0;
	ptagDataChangeDef->lParam = 0;
}

BOOL mms_RegisterDataChangedMsg(ACSI_NODE *pDevice, const CString &strPath, ULONG nHwnd, ULONG nMsgID)
{
	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;

	if (pDataChangeMsg->Count > MAX_ITEMCOUNT_FOR_DATACHANGEMSG)
	{
		return FALSE;
	}

	tagDataChangeDef  *ptagDataChangeDef = pDataChangeMsg->DataChangeDef;
	tagDataChangeDef  *ptagDataChangeDefEnd = ptagDataChangeDef + MAX_ITEMCOUNT_FOR_DATACHANGEMSG;

	while (ptagDataChangeDef < ptagDataChangeDefEnd)
	{
		if (ptagDataChangeDef->PathName[0] == 0)
		{
			mms_RegisterDataChangedMsg(ptagDataChangeDef, pDevice, strPath, nHwnd, nMsgID);
			pDataChangeMsg->Count++;

			break;
		}

		ptagDataChangeDef++;
	}

	return TRUE;
}

BOOL mms_RegisterCmdMsg(ACSI_NODE *pDevice, const CString &strPath, ULONG nHwnd, ULONG nMsgID, ULONG nCmdID, ULONG nCmdState, ULONG wParam, ULONG lParam)
{
	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;

	if (pDataChangeMsg->Count > MAX_ITEMCOUNT_FOR_DATACHANGEMSG)
	{
		return FALSE;
	}

	tagDataChangeDef  *ptagDataChangeDef = pDataChangeMsg->DataChangeDef;
	tagDataChangeDef  *ptagDataChangeDefEnd = ptagDataChangeDef + MAX_ITEMCOUNT_FOR_DATACHANGEMSG;

	while (ptagDataChangeDef < ptagDataChangeDefEnd)
	{
		if (ptagDataChangeDef->PathName[0] != 0)
		{
			if (ptagDataChangeDef->PathName == strPath
				&& ptagDataChangeDef->nMsg == nMsgID
				&& ptagDataChangeDef->nCmdState == nCmdState)
			{
				break;
			}
		}
		else //if (ptagDataChangeDef->PathName[0] == 0)
		{
			CString_to_char(strPath, ptagDataChangeDef->PathName);
			ptagDataChangeDef->hMsgWnd = nHwnd;
			ptagDataChangeDef->nMsg = nMsgID;
			ptagDataChangeDef->nCmdID = nCmdID;
			ptagDataChangeDef->nCmdState = nCmdState;
			ptagDataChangeDef->wParam = wParam;
			ptagDataChangeDef->lParam = lParam;
			pDataChangeMsg->Count++;

			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("RegisterCmdMsg(%s)成功"), strPath);

			break;
		}

		ptagDataChangeDef++;
	}

	return TRUE;
}

BOOL mms_UnRegisterDataChangedMsg(ACSI_NODE *pDevice, const CString &strPath)
{
	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;
	tagDataChangeDef  *ptagDataChangeDef = pDataChangeMsg->DataChangeDef;
	tagDataChangeDef  *ptagDataChangeDefEnd = ptagDataChangeDef + MAX_ITEMCOUNT_FOR_DATACHANGEMSG;
	BOOL bFind = FALSE;

	while (ptagDataChangeDef < ptagDataChangeDefEnd)
	{
		if (ptagDataChangeDef->PathName[0] != 0)
		{
			if(strPath == ptagDataChangeDef->PathName)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "UnRegisterDataChangedMsg(%s)成功", strPath);
				ptagDataChangeDef->PathName[0] = 0;
				ptagDataChangeDef++;
				bFind = TRUE;
				break;
			}
		}

		ptagDataChangeDef++;
	}

	if (!bFind)
	{
		return FALSE;
	}

	while (ptagDataChangeDef < ptagDataChangeDefEnd)
	{
		if (ptagDataChangeDef->PathName[0] != 0)
		{
			strcpy(ptagDataChangeDef->PathName, (ptagDataChangeDef+1)->PathName);
			ptagDataChangeDef++;
		}
		else
		{
			break;
		}
	}

	pDataChangeMsg->Count--;

	return TRUE;
}

BOOL mms_NeedFireDataChangedMsg(ACSI_NODE *pDevice)
{
	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;
	long nIndex = 0;

	if (pDataChangeMsg->Count == 0)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

//2019-1-5  报文事件：增加报文名称判断
BOOL mms_FireDataChangedMsg(tagDataChangeDef  *ptagDataChangeDef, tagDA *pDA)
{
	if (!::IsWindow((HWND)ptagDataChangeDef->hMsgWnd))
	{
		return FALSE;
	}

	BOOL bNeedFire = FALSE;

	if (ptagDataChangeDef->pRefDA != NULL)
	{
#ifdef _use_mms_string
		if (mms_str_cmp(&ptagDataChangeDef->pRefDA->DAValue.mmsName, &pDA->DAValue.mmsName) == 0)
#else
		if (strcmp(ptagDataChangeDef->pRefDA->DAValue.mmsName, pDA->DAValue.mmsName) == 0)
#endif
		{
			bNeedFire = TRUE;
		}
	}
	else
	{//使用名称进行判断
#ifdef _use_mms_string
		if (strcmp(ptagDataChangeDef->PathName, mms_string(&pDA->DADescri.Value.string) ) == 0)
#else
		if (strcmp(ptagDataChangeDef->PathName, pDA->DADescri.mmsName) == 0)
#endif
		{
			bNeedFire = TRUE;
		}
	}

	if (bNeedFire)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("FireDataChangedMsg(%x, %x,  %s)"), ptagDataChangeDef->hMsgWnd, ptagDataChangeDef->nMsg, CString(ptagDataChangeDef->PathName));
		PostMessage((HWND)ptagDataChangeDef->hMsgWnd, ptagDataChangeDef->nMsg, (WPARAM)0, (LPARAM)0);
	}

	return bNeedFire;
}

BOOL mms_FireDataChangedMsg(ACSI_NODE *pDevice, tagDA *pDA)
{
	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;
	long nIndex = 0;

	if (pDataChangeMsg->Count == 0)
	{
		return FALSE;
	}

	tagDataChangeDef  *ptagDataChangeDef = pDataChangeMsg->DataChangeDef;
	tagDataChangeDef  *ptagDataChangeDefEnd = ptagDataChangeDef + MAX_ITEMCOUNT_FOR_DATACHANGEMSG;

	while (ptagDataChangeDef < ptagDataChangeDefEnd)
	{
		if (ptagDataChangeDef->PathName[0] == 0)
		{
			break;
		}

		mms_FireDataChangedMsg(ptagDataChangeDef, pDA);
		
		ptagDataChangeDef++;
	}

	return TRUE;
}


BOOL mms_FireDataChangedMsg(ST_INT nAcsi, ST_INT nLdIndex, ST_INT nDsIndex, ST_INT nDataIndex)
{
	ACSI_NODE *pDevice = Client61850_GetAcsiNode(nAcsi);

	if (pDevice == NULL)
	{
		return FALSE;
	}

	if (!mms_NeedFireDataChangedMsg(pDevice))
	{
		return FALSE;
	}

	tagDA *pDA = mms_GetDA(nAcsi, nLdIndex, nDsIndex, nDataIndex);
	
	if (pDA == NULL)
	{
		return FALSE;
	}

	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;

	if (pDataChangeMsg->Count == 0)
	{
		return FALSE;
	}

	mms_FireDataChangedMsg(pDevice, pDA);

	return FALSE;
}


BOOL mms_FireCmdMsg(ACSI_NODE *pDevice, ST_INT nCmdID, ST_INT nCmdIndex)
{
	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;
	long nIndex = 0;

	if (pDataChangeMsg->Count == 0)
	{
		return FALSE;
	}

	tagDataChangeDef  *ptagDataChangeDef = pDataChangeMsg->DataChangeDef;
	tagDataChangeDef  *ptagDataChangeDefEnd = ptagDataChangeDef + MAX_ITEMCOUNT_FOR_DATACHANGEMSG;

	while (ptagDataChangeDef < ptagDataChangeDefEnd)
	{
		if (ptagDataChangeDef->PathName[0] == 0)
		{
			break;
		}

		if (ptagDataChangeDef->nCmdID == nCmdID && ptagDataChangeDef->nCmdState== nCmdIndex)
		{
			if (!::IsWindow((HWND)ptagDataChangeDef->hMsgWnd))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("mms_FireCmdMsg(%x, %x,  %s, %d, %d)失败：目标窗口不存在") //_T("mms_FireCmdMsg(%x, %x,  %s, %d, %d)失败：目标窗口不存在")
					, ptagDataChangeDef->hMsgWnd, ptagDataChangeDef->nMsg, CString(ptagDataChangeDef->PathName)
					, ptagDataChangeDef->wParam, ptagDataChangeDef->lParam);

				continue;
			}

			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("mms_FireCmdMsg(%x, %x,  %s, %d, %d)")
				, ptagDataChangeDef->hMsgWnd, ptagDataChangeDef->nMsg, CString(ptagDataChangeDef->PathName)
				, ptagDataChangeDef->wParam, ptagDataChangeDef->lParam);

			PostMessage((HWND)ptagDataChangeDef->hMsgWnd, ptagDataChangeDef->nMsg
				, (WPARAM)ptagDataChangeDef->wParam, (LPARAM)ptagDataChangeDef->lParam);
		}

		ptagDataChangeDef++;
	}

	return TRUE;
}

BOOL mms_FireCmdMsg(ST_INT nAcsi, ST_INT nLdIndex, ST_INT nDsIndex, ST_INT nDataIndex, ST_INT nCmdID, ST_INT nCmdIndex)
{
	ACSI_NODE *pDevice = Client61850_GetAcsiNode(nAcsi);

	if (pDevice == NULL)
	{
		return FALSE;
	}

	ptagDataChangeMsg pDataChangeMsg = &pDevice->DataChangeMsg;

	if (pDataChangeMsg->Count == 0)
	{
		return FALSE;
	}

	mms_FireCmdMsg(pDevice, nCmdID, nCmdIndex);

	return TRUE;
}



long mms_Get_LdID_DsPath(const CString &strPath, CString &strLdID, CString &strDsPath)
{
	long nPos = 0;
	long nIndex = 0;
	long nCount = g_oMmsValueKeyMngr.m_astrLdIDKey.GetSize();
	CString strKey;
	long nPosFind = -1;

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		strKey = g_oMmsValueKeyMngr.m_astrLdIDKey.GetAt(nIndex);
		nPos = strPath.Find(strKey);

		if (nPos >= 0)
		{
			nPosFind = nPos + strKey.GetLength() - 1;
			strLdID = strPath.Left(nPosFind);
			strDsPath = strPath.Mid(nPosFind+1);
			break;
		}
	}

	return nPosFind;
}

void mms_ResetRptIndex(ACSI_NODE *pDevice)
{
	LD_NODE *pLD = NULL;
	LD_DATASET_INFO *pDS = NULL;
	long nLd=0, nDs=0;

	for (nLd=0; nLd<pDevice->numLD; nLd++)
	{
		pLD = &pDevice->LD[nLd];

		for (nDs=0; nDs<pLD->numDaSet; nDs++)
		{
			pLD->DataInfo[nDs].curRcbIndex = 0;
		}
	}
}


BOOL mms_IsDeviceEnumDatas(ACSI_NODE *pDevice)
{
	if (pDevice->numLD == 0)
	{
		return FALSE;
	}

	BOOL bHasEnum = TRUE;

	long nLdIndex=0, nDsIndex = 0;

	for (nLdIndex=0; nLdIndex<pDevice->numLD; nLdIndex++)
	{
		for (nDsIndex=0; nDsIndex<pDevice->LD[nLdIndex].numDaSet; nDsIndex++)
		{
			if (!pDevice->LD[nLdIndex].DataInfo[nDsIndex].bHasEnum)
			{
				bHasEnum = FALSE;
				break;
			}
		}

		if (!bHasEnum)
		{
			break;
		}
	}

	return bHasEnum;
}


MMS_DATA_NODE* mms_find_data_node_child(MMS_DATA_NODE *pParentNode, const char *pName)
{
	MMS_DATA_NODE *pHead = pParentNode->pFirstChild;
	MMS_DATA_NODE *pCurr = pHead;
	MMS_DATA_NODE *pFind = NULL;

	do 
	{
		if (pCurr == NULL)
		{
			break;
		}

#ifdef _use_mms_string
		if (strcmp(mms_string(&pCurr->name), pName) == 0)
#else
		if (strcmp(pCurr->name, pName) == 0)
#endif
		{
			pFind = pCurr;
			break;
		}

		pCurr = pCurr->pNext;

	} while (pCurr != pHead);

	return pFind;
}

MMS_DATA_NODE* mms_node_append_child(MMS_DATA_NODE* pParentNode, const char *pName, enum NODE_TYPE type)
{
	MMS_DATA_NODE *pNew = mms_node_append_child2(pParentNode);

#ifdef _use_mms_string
	mms_str_set(&pNew->name, pName);
#else
	strcpy(pNew->name, pName);
#endif
	pNew->type = type;

	return pNew;
}


MMS_DATA_NODE* mms_node_append_child2(MMS_DATA_NODE* pParentNode)
{
	MMS_DATA_NODE *pNew = NULL;

	pNew = mms_node_append_sibling2(pParentNode, &pParentNode->pFirstChild);

	return pNew;
}

void InitGlobalDatasets_DescDef()
{
	CString strPath;
	strPath = _P_GetConfigPath();
	strPath += _T("DatasetsDescDef.xml");
	g_oDescDefDatasets.DeleteAll();

	if (IsFileExist(strPath))
	{
		if (g_oDescDefDatasets.OpenXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys))
		{
			return;
		}
	}
	g_oDescDefDatasets.AddNewDataset(_T("遥测"),_T("LLN0$dsAin"));
	g_oDescDefDatasets.AddNewDataset(_T("遥信"),_T("LLN0$dsDin"));
	g_oDescDefDatasets.AddNewDataset(_T("联锁状态"),_T("LLN0$dsInterLock"));

	g_oDescDefDatasets.AddNewDataset(_T("保护事件"),_T("LLN0$dsTripInfo"));
	g_oDescDefDatasets.AddNewDataset(_T("保护遥信"),_T("LLN0$dsRelayDin"));
	g_oDescDefDatasets.AddNewDataset(_T("保护压板"),_T("LLN0$dsRelayEna"));
	g_oDescDefDatasets.AddNewDataset(_T("保护录波"),_T("LLN0$dsRelayRec"));
	g_oDescDefDatasets.AddNewDataset(_T("保护遥测"),_T("LLN0$dsRelayAin"));
	g_oDescDefDatasets.AddNewDataset(_T("故障信号"),_T("LLN0$dsAlarm"));
	g_oDescDefDatasets.AddNewDataset(_T("告警信号"),_T("LLN0$dsWarning"));
	g_oDescDefDatasets.AddNewDataset(_T("通信工况"),_T("LLN0$dsCommState"));
	g_oDescDefDatasets.AddNewDataset(_T("装置参数"),_T("LLN0$dsParameter"));
	g_oDescDefDatasets.AddNewDataset(_T("定值"),_T("LLN0$dsSetting"));
	g_oDescDefDatasets.AddNewDataset(_T("GOOSE输出信号"),_T("LLN0$dsGOOSE"));
	g_oDescDefDatasets.AddNewDataset(_T("采样输出值"),_T("LLN0$dsSV"));

	g_oDescDefDatasets.AddNewDataset(_T("日志"),_T("LLN0$dsLog"));
	g_oDescDefDatasets.AddNewDataset(_T("装置运行状态"),_T("LLN0$dsDeviceState"));
	g_oDescDefDatasets.AddNewDataset(_T("定值区号"),_T("LLN0$dsSetGrpNum"));
	g_oDescDefDatasets.AddNewDataset(_T("远方操作保护功能投退"),_T("LLN0$dsRelayFunEn"));
	g_oDescDefDatasets.AddNewDataset(_T("保护功能状态"),_T("LLN0$dsRelayState"));
	g_oDescDefDatasets.AddNewDataset(_T("保护功能闭锁"),_T("LLN0$dsRelayBlk"));
	g_oDescDefDatasets.AddNewDataset(_T("装置标准信息"),_T("LLN0$dsDevStdMsg"));
	g_oDescDefDatasets.AddNewDataset(_T("控制操作信号"),_T("LLN0$dsDout"));
	g_oDescDefDatasets.SaveXmlFile(strPath,CDataMngrXmlRWKeys::g_pXmlKeys);
}

BOOL GlobalSetDatasetName(char *pzfDataSetID,char *pzfDaSetDesc)
{
	CString strID;
	strID = pzfDataSetID;
	POS pos = g_oDescDefDatasets.GetHeadPosition();
	CExBaseObject *pCurObj = NULL,*pFind = NULL;

	while(pos)
	{
		pCurObj = g_oDescDefDatasets.GetNext(pos);

		if (strID.Find(pCurObj->m_strID) == 0)
		{
			pFind = pCurObj;
			break;
		}
	}

	if (pFind == NULL)
	{
		return FALSE;
	}

	CString_to_char(pFind->m_strName,pzfDaSetDesc);
	return TRUE;
}

void InitGlobalDatasetsDesc_ACSI_NODE(ACSI_NODE *pACSI_NODE)
{
	if (pACSI_NODE == NULL)
	{
		return;
	}

	LD_NODE *pCurLd = NULL;
	LD_DATASET_INFO *pCurDataset = NULL;

	for (int nLdIndex = 0;nLdIndex<pACSI_NODE->numLD;nLdIndex++)
	{
		pCurLd = &pACSI_NODE->LD[nLdIndex];

		for (int nDsIndex = 0;nDsIndex<pCurLd->numDaSet;nDsIndex++)
		{
			pCurDataset = &pCurLd->DataInfo[nDsIndex];
			GlobalSetDatasetName(pCurDataset->DataSetID,pCurDataset->DaSetDesc);
		}
	}
}

CString GlobalGetRptLogCBString_GSP(char *pzfRptLogCBString)
{
	if (pzfRptLogCBString == NULL)
	{
		return _T("");
	}

	CString strRptLogCBString;
	strRptLogCBString = pzfRptLogCBString;
	strRptLogCBString.Replace(_T("$RP$"),_T("."));
	strRptLogCBString.Replace(_T("$BR$"),_T("."));
	strRptLogCBString.Replace(_T("$LG$"),_T("."));
	strRptLogCBString.Replace(_T("$"),_T("."));
	return strRptLogCBString;
}