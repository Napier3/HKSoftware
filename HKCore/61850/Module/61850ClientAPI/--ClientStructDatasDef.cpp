#include "StdAfx.h"
#include "ClientStructDatasDef.h"
long g_nMaxReportCount = MAX_REPORT_COUNT;
//long  g_nCanWriteActiveSG = 1;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void rpt_quit_value(tagRptValue *pValue)
{
	if (pValue == NULL)
	{
		return;
	}

	if (pValue->bString)
	{
		mms_str_quit(&pValue->Value.string);
		pValue->bString = FALSE;
	}
}

void rpt_quit(tagRpt *pRpt)
{
	ST_INT nIndex;
	nIndex = 0;

	for (nIndex=0; nIndex < pRpt->capacity; nIndex++)
	{
		rpt_quit_value(pRpt->Value+nIndex);
	}

	free (pRpt->Value);
	pRpt->Value = NULL;
	pRpt->size = 0;
	pRpt->capacity = 0;
}

ST_VOID mms_Free_Data_Node(MMS_DATA_NODE *p_mms_data_node)
{
	MMS_DATA_NODE *pCurr = p_mms_data_node;
	MMS_DATA_NODE *pNext = NULL;

	if (p_mms_data_node == NULL)
	{
		return;
	}

	pNext = pCurr->pNext;

	do 
	{
		mms_Free_Data_Node(pCurr->pFirstChild);
		pNext = pCurr->pNext;
#ifdef _use_mms_string
		mms_str_quit(&pCurr->name);
#endif

		free(pCurr);
		pCurr = pNext;
	}
	while (pCurr != NULL);
}

ST_VOID mms_ReleaseValue(tagDAValue *pValue, BOOL bValString)
{
	mms_str_quit(&pValue->mmsName);

	if (bValString)
	{
		mms_str_quit(&pValue->Value.string);
	}
}

ST_VOID mms_ReleaseData(tagDA*pData)
{
	ST_INT i=0;

	if (pData == NULL)
	{
		return;
	}

	if (pData != NULL)
	{
		for (i=0;i<pData->nSubDANum;i++)
		{
			mms_ReleaseData(&pData->pSubDA[i]);
		}

		pData->nSubDANum = 0;
		free(pData->pSubDA);
		pData->pSubDA = NULL;
	}

	if (strstr(pData->DataType, "_STR") != NULL)
	{
		mms_ReleaseValue(&pData->DAValue, TRUE);
	}
	else
	{
		mms_ReleaseValue(&pData->DAValue, FALSE);
	}

	mms_ReleaseValue(&pData->DADescri, TRUE);
	mms_ReleaseValue(&pData->DAUnite, FALSE);
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	mms_ReleaseValue(&pData->MaxVal, FALSE);
	mms_ReleaseValue(&pData->MinVal, FALSE);
	mms_ReleaseValue(&pData->StepSize, FALSE);
#endif
}

ST_VOID mms_Free_tagDA(tagDA*pData)
{
	mms_ReleaseData(pData);
	//	ST_INT i=0;
	// 	mms_str_quit(&pData->DAValue.mmsName);
	// 	mms_str_quit(&pData->DADescri.mmsName);
	// 	mms_str_quit(&pData->DAUnite.mmsName);
	// 	mms_str_quit(&pData->MaxVal.mmsName);
	// 	mms_str_quit(&pData->MinVal.mmsName);
	// 	mms_str_quit(&pData->StepSize.mmsName);
	// 
	// 	if (pData != NULL)
	// 	{
	// 		for (i=0;i<pData->nSubDANum;i++)
	// 		{
	// 			if (pData->pSubDA[i].pSubDA!=NULL)
	// 				mms_ReleaseData(&pData->pSubDA[i]);
	// 		}
	// 
	// 		free(pData->pSubDA);
	// 		pData->pSubDA = NULL;
	// 	}
}

void mms_Free_tagDAs(tagDA *pTagDAs, ST_INT nCount)
{
	ST_INT nIndex=0;

	if (pTagDAs == NULL)
	{
		return;
	}

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		mms_Free_tagDA(&pTagDAs[nIndex]);
	}
}

void mms_Free_LD_DATASET_INFO(LD_DATASET_INFO *pDataSet)
{
	if (pDataSet == NULL)
	{
		return;
	}

	mms_Free_tagDAs(pDataSet->DataSet, pDataSet->numData);

	if (pDataSet->DataSet != NULL)
	{
		free(pDataSet->DataSet);
		pDataSet->DataSet = NULL;
	}
}

ST_VOID mms_Free_Journal(LD_LOG_INFO *Journal)
{
	MMS_TAGDA_LIST_NODE *pList = NULL;
	MMS_TAGDA_LIST_NODE *p = NULL;

	if (Journal == NULL)
	{
		return;
	}

#ifdef _use_mms_string
	mms_str_quit(&Journal->Name);
#endif

	mms_str_quit(&Journal->Dataset);
	mms_str_quit(&Journal->logRef);
}

ST_VOID mms_Free_LD_JOURNAL_CTRLS(LD_JOURNAL_CTRLS *pJournal)
{
	ST_INT nDataset;
	if (pJournal == NULL)
	{
		return;
	}

	if (pJournal->LogInfo != NULL)
	{
		for (nDataset= 0;nDataset<pJournal->numData;nDataset++)
			mms_Free_Journal(&pJournal->LogInfo[nDataset]);

		free(pJournal->LogInfo);
		pJournal->LogInfo = NULL;
	}

	pJournal->numData = 0;
}

ST_VOID mms_JournalDataOfVector_Free(unsigned long* pJournalDatas,ST_INT nNumOfData)
{
	ST_INT nTmp;
	LD_JOURNAL_DATA *pJournalData = NULL;
	for (nTmp = 0;nTmp<nNumOfData;nTmp++)
	{
		pJournalData = (LD_JOURNAL_DATA*)*(pJournalDatas + nTmp/**sizeof(unsigned long)*/);//??????zhouhj 指针加1 为什么就是4个字节了？？？？？
		if (pJournalData != NULL)
		{
			mms_Free_tagDAs(pJournalData->DAValue,pJournalData->numData);

			if (pJournalData->DAValue != NULL)
			{
				free(pJournalData->DAValue);
				pJournalData->DAValue = NULL;
			}

			mms_str_quit(&pJournalData->LogCtrl);
			mms_str_quit(&pJournalData->DataSetName);
			free(pJournalData);
		}
	}
}

ST_VOID mms_Free_LD_NODE(LD_NODE *pLdevice)
{
	ST_INT nDataset = 0;

	if (pLdevice == NULL)
	{
		return;
	}

	for (nDataset=0; nDataset<pLdevice->numDaSet; nDataset++)
	{
		mms_Free_LD_DATASET_INFO(pLdevice->DataInfo+nDataset);
	}

	mms_Free_LD_JOURNAL_CTRLS(&pLdevice->JournalCtrls);
	mms_JournalDataOfVector_Free(pLdevice->JournalDatas.Datas,pLdevice->JournalDatas.numOfData);
	vector_free(&pLdevice->JournalDatas);

	mms_Free_Data_Node(pLdevice->mms_data_node);

	if (pLdevice->DataInfo != NULL)
	{
		free(pLdevice->DataInfo);
		pLdevice->DataInfo = NULL;
	}
}

ST_VOID mms_file_sys_free(XMMS_FILE_SYS_OBJ *pMmsFileSysObj)
{
	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
	int nIndex = 0;
	mms_str_quit(&pMmsFileSysObj->filedir.filename);

	for(nIndex = 0;nIndex<pMmsFileSysObj->subFiles.numOfData;nIndex++)
	{
		pSubFileDir = (XMMS_FILE_SYS_OBJ *)*(pMmsFileSysObj->subFiles.Datas + nIndex);
		mms_file_sys_free(pSubFileDir);
		free(pSubFileDir);
	}

	vector_free(&pMmsFileSysObj->subFiles);
}

ST_VOID mms_rpc_methods_free(MMS_ADDR_VECTOR *pRpcMethods)
{
	XDLT_RPC_METHOD *pRpcMethod = NULL;
	int nIndex = 0;

	for(nIndex = 0;nIndex<pRpcMethods->numOfData;nIndex++)
	{
		pRpcMethod = (XDLT_RPC_METHOD *)*(pRpcMethods->Datas + nIndex);
		mms_str_quit(&pRpcMethod->paraFuncation);
		mms_str_quit(&pRpcMethod->paraCallName);
		mms_str_quit(&pRpcMethod->paraCallID);
		mms_Free_tagDA(&pRpcMethod->oDataModel);
	}

	vector_free(pRpcMethods);
}

ST_VOID mms_Free_ACSI_NODE(ACSI_NODE *pDevice)
{
	ST_INT nLdIndex = 0;
	ST_INT nIndex=0;

	if (pDevice == NULL)
	{
		return;
	}

	for (nLdIndex=0; nLdIndex<pDevice->numLD; nLdIndex++)
	{
		mms_Free_LD_NODE(pDevice->LD+nLdIndex);
	}

	if (pDevice->LD != NULL)
	{
		free(pDevice->LD);
		pDevice->LD = NULL;
	}

	if (pDevice->nCurrReportCount > 0)
	{
		for (nIndex=0; nIndex<pDevice->nCurrReportCount; nIndex++)
		{
			rpt_quit(&pDevice->Reports[nIndex]);
		}
	}

	mms_file_sys_free(&pDevice->FileDir);
	mms_rpc_methods_free(&pDevice->oRpcMethods);
	mms_str_quit(&pDevice->RcdFilePath);
	mms_str_quit(&pDevice->IpAddr);
}

ACSI_NODE* mms_New_ACSI_NODE_numLD(ACSI_NODE *pDevice, ST_INT numLD, BOOL bDelete)
{
	ST_INT nSize = 0;
	ACSI_NODE *pBack = NULL;

	if (pDevice == NULL)
	{
		return NULL;
	}

	nSize = numLD * sizeof(LD_NODE);

	if (bDelete)
	{
		mms_Free_ACSI_NODE(pDevice);
	}
	else
	{
		pBack = (ACSI_NODE *)malloc(sizeof(ACSI_NODE));
		pBack->LD = pDevice->LD;
		pBack->numLD = pDevice->numLD;
		pDevice->numLD = 0;
		pDevice->LD = NULL;
	}

	pDevice->LD = (LD_NODE *)malloc(nSize);
	memset(pDevice->LD, 0, nSize);
	pDevice->numLD = numLD;

	return pBack;
}

MMS_DATA_NODE* mms_node_append_sibling(MMS_DATA_NODE *pParent, MMS_DATA_NODE** ppSiblingNode, const char *pName, enum NODE_TYPE type)
{
	MMS_DATA_NODE *pNew = mms_node_append_sibling2(pParent, ppSiblingNode);

#ifdef _use_mms_string
	mms_str_set(&pNew->name, pName);
#else
	strcpy(pNew->name, pName);
#endif

	pNew->type = type;

	return pNew;
}

MMS_DATA_NODE* mms_node_get_tail(MMS_DATA_NODE *pHead)
{
	MMS_DATA_NODE *p = pHead;

	while (p != NULL)
	{
		if (p->pNext == NULL)
		{
			break;
		}

		p = p->pNext;
	}

	return p;
}

MMS_DATA_NODE* mms_node_append_sibling2(MMS_DATA_NODE *pParent, MMS_DATA_NODE** ppSiblingNode)
{
	MMS_DATA_NODE *pNew = NULL;
	MMS_DATA_NODE *pHead = *ppSiblingNode;

	if (*ppSiblingNode == NULL)
	{
#ifdef _use_debug_malloc
		*ppSiblingNode = (MMS_DATA_NODE*)new char[sizeof(MMS_DATA_NODE)];
#else
		*ppSiblingNode = (MMS_DATA_NODE*)malloc(sizeof(MMS_DATA_NODE));
#endif

		memset(*ppSiblingNode, 0, sizeof(MMS_DATA_NODE));
		pNew = *ppSiblingNode;
		pNew->pNext = NULL;
		pNew->pPrevious = NULL;
	}
	else
	{
#ifdef _use_debug_malloc
		pNew = (MMS_DATA_NODE*)new char[sizeof(MMS_DATA_NODE)];
#else
		pNew = (MMS_DATA_NODE*)malloc(sizeof(MMS_DATA_NODE));
#endif

		memset(pNew, 0, sizeof(MMS_DATA_NODE));
		MMS_DATA_NODE *pTail = mms_node_get_tail(pHead);
		pNew->pNext = NULL;
		pNew->pPrevious = pTail;
		pTail->pNext = pNew;
	}

	pNew->pParent = pParent;

	return pNew;
}

void mms_New_LD_JOURNAL_CTRLS_numData(LD_JOURNAL_CTRLS *pJournal, ST_INT numData)
{
	if (pJournal == NULL)
	{
		return;
	}

	mms_Free_LD_JOURNAL_CTRLS(pJournal);

	if ( (pJournal != NULL) && (numData > 0) )
	{
		ST_INT nSize = sizeof(LD_LOG_INFO) * numData;
		pJournal->LogInfo = (LD_LOG_INFO *)malloc(nSize);
		ASSERT (pJournal->LogInfo != NULL);

		if (pJournal->LogInfo != NULL)
		{
			memset(pJournal->LogInfo, 0, nSize);
			pJournal->numData = numData;
		}
	}
}

ST_VOID mms_New_LD_NODE_numDataset(LD_NODE *pLdevice, ST_INT numDataset)
{
	ST_INT nSize;
	mms_Free_LD_NODE(pLdevice);

	nSize = numDataset * sizeof(LD_DATASET_INFO);

	if (nSize > 0)
	{
		pLdevice->DataInfo = (LD_DATASET_INFO*)malloc(nSize);
		memset(pLdevice->DataInfo, 0, nSize);
	}

	pLdevice->numDaSet = numDataset;
}

//2018.1.17zhouhj
ST_VOID mms_New_LD_NODE_numJournal(LD_NODE *pLdevice, ST_INT numJournal)
{
	ST_INT nSize;

	if (pLdevice == NULL)
	{
		return;
	}

	if (pLdevice->JournalCtrls.LogInfo != NULL)
	{
		for (nSize= 0;nSize<pLdevice->JournalCtrls.numData;nSize++)
		{
			mms_Free_Journal(&pLdevice->JournalCtrls.LogInfo[nSize]);
		}

		pLdevice->JournalCtrls.numData = 0;
	}

	nSize = numJournal * sizeof(LD_LOG_INFO);

	if (nSize > 0)
	{
		pLdevice->JournalCtrls.LogInfo = (LD_LOG_INFO*)malloc(nSize);
		memset(pLdevice->JournalCtrls.LogInfo, 0, nSize);
	}

	pLdevice->JournalCtrls.numData = numJournal;
}

void mms_New_LD_DATASET_INFO_numData(LD_DATASET_INFO *pDataSet, ST_INT numData)
{
	if (pDataSet == NULL)
	{
		return;
	}

	mms_Free_LD_DATASET_INFO(pDataSet);

	if ( (pDataSet != NULL) && (numData > 0) )
	{
		ST_INT nSize = sizeof(tagDA) * numData;
		pDataSet->DataSet = (tagDA *)malloc(nSize);
		ASSERT (pDataSet->DataSet != NULL);

		if (pDataSet->DataSet != NULL)
		{
			memset(pDataSet->DataSet, 0, nSize);
			pDataSet->numData = numData;
			mms_InitDatas(pDataSet->DataSet, numData);
		}
	}
}

ST_VOID mms_CopyValue(tagDAValue*pDst, tagDAValue*pSrc, BOOL bString)
{
#ifdef _use_mms_string
	mms_str_copy(&pDst->mmsName, &pSrc->mmsName);

	if (bString)
	{
		mms_str_copy(&pDst->Value.string, &pSrc->Value.string);
	}
	else
	{
		pDst->Value.utctime = pSrc->Value.utctime;
	}
#endif
}

void mms_InitData(tagDA*pDA)
{
#ifdef _use_mms_string
	mms_str_init(&pDA->DAValue.mmsName);
	mms_str_init(&pDA->DADescri.mmsName);
	mms_str_init(&pDA->DAUnite.mmsName);
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	mms_str_init(&pDA->MaxVal.mmsName);
	mms_str_init(&pDA->MinVal.mmsName);
	mms_str_init(&pDA->StepSize.mmsName);
#endif

	mms_InitDatas(pDA->pSubDA, pDA->nSubDANum);
#endif
}

ST_RET CompareData(tagDA*pSrc, tagDA*pDst)
{
	ST_RET nRet = SD_FALSE;
	ST_INT i;

	if (strstr(pSrc->DataType,pDst->DataType))
	{
		if (strstr(pDst->DataType,"BOOL"))
		{
			if (pSrc->DAValue.Value.u == pDst->DAValue.Value.u)
				nRet = SD_TRUE;
		}
		else if (strstr(pDst->DataType,"INT"))
		{
			if (pSrc->DAValue.Value.l == pDst->DAValue.Value.l)
				nRet = SD_TRUE;
		}
		else if (strstr(pDst->DataType,"UINT"))
		{
			if (pSrc->DAValue.Value.u == pDst->DAValue.Value.u)
				nRet = SD_TRUE;
		}
		else if (strstr(pDst->DataType,"FLOAT"))
		{
			if (pSrc->DAValue.Value.f - pDst->DAValue.Value.f<0.001)
				nRet = SD_TRUE;
		}
		else if (strstr(pDst->DataType,"BIT_STR"))//比较全部的时候,对于品质位和时间都比较,会出现不一致的情况
		{
			CString strTmp;

			strTmp = mms_string(&pSrc->DAValue.mmsName);

			if (strTmp.Find("$q",strTmp.GetLength()-2) != -1)
			{
				nRet = SD_TRUE;
			}
			else if (mms_str_cmp(/*mms_string*/(&pSrc->DAValue.Value.string), /*mms_string*/(&pDst->DAValue.Value.string)) == 0) //(.)
				nRet = SD_TRUE;
		}
// 		else if (strstr(pDst->DataType,"UTC_TIME"))
// 		{
// 			//if (pSrc->DAValue.Value.f - pDst->DAValue.Value.f<0.001)
// 			nRet = SD_TRUE;
// 		}
		else if (strstr(pDst->DataType,"STRUCT"))
		{
			for (i=0; i<pDst->nSubDANum;i++)
			{
				nRet = CompareData(&pSrc->pSubDA[i], &pDst->pSubDA[i]);
				if (nRet!=SD_TRUE)
					break;
			}
		}
		else
			nRet = SD_TRUE;
	}

	return nRet;
}

ST_VOID mms_CopyData(tagDA*pSrc, tagDA*pDst, BOOL bRpt)
{
	ST_INT i=0;
	ST_INT size = 0;
	// 	mms_ReleaseData(pDst);

	if (pSrc==NULL)
		return;

#ifdef _use_mms_string
	pDst->ReasonCode = pSrc->ReasonCode;
	pDst->Type_id = pSrc->Type_id;
	strcpy(pDst->DataType, pSrc->DataType);	//INT, BOOL 等
	pDst->ApplyType = pSrc->ApplyType;
	pDst->EventNum = pSrc->EventNum;
	pDst->bWrite = pSrc->bWrite;		//0-不可写 1-可写
	pDst->bModify = pSrc->bModify;		//0-未修改 1-已修改
	pDst->nSubDANum = pSrc->nSubDANum;
	pDst->dwDsMapObj = pSrc->dwDsMapObj;
	pDst->nDataType = pSrc->nDataType;//zhouhj20180130

	if (strstr(pDst->DataType, "_STR") != NULL)
	{
		mms_CopyValue(&pDst->DAValue, &pSrc->DAValue, TRUE);		//数值
	}
	else
	{
		mms_CopyValue(&pDst->DAValue, &pSrc->DAValue, FALSE);		//数值
	}

	mms_CopyValue(&pDst->DADescri, &pSrc->DADescri, TRUE);	//描述
	mms_CopyValue(&pDst->DAUnite, &pSrc->DAUnite, FALSE);		//单位

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	mms_CopyValue(&pDst->MaxVal, &pSrc->MaxVal, FALSE);		//最大值
	mms_CopyValue(&pDst->MinVal, &pSrc->MinVal, FALSE);		//最小值
	mms_CopyValue(&pDst->StepSize, &pSrc->StepSize, FALSE);		//stepsize
#endif

#else
	*pDst = *pSrc;
#endif

	if (pSrc->pSubDA != NULL)
	{
		size = pSrc->nSubDANum*sizeof(tagDA);
		pDst->pSubDA = (tagDA*)malloc(size);
		ZeroMemory(pDst->pSubDA, size);

		for (i=0; i<pSrc->nSubDANum; i++)
		{
			mms_InitData(&pDst->pSubDA[i]);
			mms_CopyData(&pSrc->pSubDA[i], &pDst->pSubDA[i], bRpt);
		}
	}
}

ST_VOID mms_InitDatas(tagDA*pDA, long nCount)
{
	ST_INT nIndex;

	if (pDA == NULL || nCount == 0)
	{
		return;
	}

	for (nIndex=0; nIndex<nCount; nIndex++)
	{
		mms_InitData(pDA+nIndex);
	}
}

ST_VOID mms_InitDA_DataType(tagDA*pSrc)
{
	if (strcmp(pSrc->DataType, "BOOL") == 0)
		pSrc->nDataType = DA_DATATYE_BOOL;
	else if (strcmp(pSrc->DataType, "INT") == 0)
		pSrc->nDataType = DA_DATATYE_INT;
	else if (strcmp(pSrc->DataType, "UINT") == 0)
		pSrc->nDataType = DA_DATATYE_UINT;
	else if (strcmp(pSrc->DataType, "FLOAT") == 0)
		pSrc->nDataType = DA_DATATYE_FLOAT;
	else if (strcmp(pSrc->DataType, "UTC_TIME") == 0)
		pSrc->nDataType = DA_DATATYE_UTC_TIME;
	else if (strcmp(pSrc->DataType, "ARRAY") == 0)
		pSrc->nDataType = DA_DATATYE_ARRAY;
	else if (strcmp(pSrc->DataType, "STRUCT") == 0)
		pSrc->nDataType = DA_DATATYE_STRUCT;
	else if (strcmp(pSrc->DataType, "UTF8_STR") == 0)
		pSrc->nDataType = DA_DATATYE_UTF8_STR;
	else if (strcmp(pSrc->DataType, "BIT_STR") == 0)
		pSrc->nDataType = DA_DATATYE_BIT_STR;
	else if (strcmp(pSrc->DataType, "OCT_STR") == 0)//zhouhj 20180516 
		pSrc->nDataType = DA_DATATYE_OCTET_STR;
	else if (strcmp(pSrc->DataType, "V_STR") == 0)//zhouhj 20180516 
		pSrc->nDataType = DA_DATATYE_VISIBLE_STR;
	else if (strcmp(pSrc->DataType, "BYTE") == 0)
		pSrc->nDataType = DA_DATATYE_BYTE;
	else if (strcmp(pSrc->DataType, "UTCTIME") == 0)
		pSrc->nDataType = DA_DATATYE_UTC_TIME;
	else if (strcmp(pSrc->DataType, "UBYTE") == 0)
		pSrc->nDataType = DA_DATATYE_UBYTE;
	else if (strcmp(pSrc->DataType, "OVSTRING64") == 0)
		pSrc->nDataType = DA_DATATYE_OVSTRING64;
	else if (strcmp(pSrc->DataType, "BVSTRING2") == 0)
		pSrc->nDataType = DA_DATATYE_BVSTRING2;
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("mms_InitDA_DataType[%s]"), pSrc->DataType);
		pSrc->nDataType = DA_DATATYE_UINT;
	}
}

/************************************************************************/
/* Helpful Time-related defines						*/

#define SECONDS_PER_DAY		(60*60*24)
#define MILLISECONDS_PER_DAY	(1000 * SECONDS_PER_DAY) 
#define DAYS_FROM_1970_TO_1984	((11*365) + (3*366))	/*includes 3 leap years 1972, 1976, 1980*/
#define TIME_T_1984_JAN_1	(DAYS_FROM_1970_TO_1984 * SECONDS_PER_DAY)


ST_RET asn1_convert_btod_to_utc (MMS_BTOD *btod, MMS_UTC_TIME *utc)
{
	time_t tJan84 = TIME_T_1984_JAN_1;

	if (btod->form != MMS_BTOD6)
	{
		CLogPrint::LogString (XLOGLEVEL_ERROR,_T("convert_btod_to_utc: MMS_BTOD4 can't be converted to UTC time"));
		return (SD_FAILURE);
	}

	/* Now compute the MMS_UTC_TIME */
	utc->secs = tJan84 +
		(time_t) (btod->day * SECONDS_PER_DAY) + (time_t) (btod->ms / 1000);
	/* num of seconds since Jan 1, 1970	*/
	/* NOTE: use 0x01000000 (2**24) in fraction computations.	*/
	utc->fraction = (ST_UINT32) ((ST_DOUBLE)(btod->ms % 1000) / 1000.0 * (ST_DOUBLE)0x01000000);
	/* fraction of a second	on 24-bits */

	return (SD_SUCCESS);
}

/************************************************************************/
/*			asn1_convert_timet_to_btime6			*/
/* Convert time_t value to MMS_BTIME6.					*/
/* Input "time_t" value is always based on UTC (GMT). It is compared	*/
/* to the define TIME_T_1984_JAN_1 which is also based on UTC (GMT).	*/
/* The difference is used to compute the number of seconds elapsed	*/
/* since 1984. Then seconds is converted to days & milliseconds.	*/
/************************************************************************/
ST_RET asn1_convert_timet_to_btime6 (time_t tThis, MMS_BTIME6 *btime6)
{
	time_t tJan84 = TIME_T_1984_JAN_1;
	long elapsed;		/* elapsed time since 1984-Jan-1 (in seconds)	*/
	ldiv_t divResult;
	ST_RET retcode;

	/* Find the number of seconds since "1984-Jan-1" and convert to days & msec.*/
	/* NOTE: difftime returns "double" (don't know why), but ldiv needs "long".*/
	elapsed = (long) difftime (tThis, tJan84);

	if (elapsed < 0)
	{				/* "negative" elapsed time NOT ALLOWED	*/
		btime6->day = 0;		/* days since 1984-Jan-1		*/
		btime6->ms = 0;		/* milliseconds this day		*/
		retcode = SD_FAILURE;
	}
	else
	{
		divResult = ldiv (elapsed, SECONDS_PER_DAY);

		btime6->day = divResult.quot;		/* days since 1984		*/
		btime6->ms = (divResult.rem * 1000);	/* milliseconds this day	*/
		retcode = SD_SUCCESS;
	}

	return (retcode);
}

/******************************************************************************/
/*Function Name: 		Convert_UTC_To_BCD( )								  */
/*Function Description:	Convert UTC time to BCD time						  */
/******************************************************************************/
ST_VOID Convert_UTC_To_BCD(tagEVENTTIME* lpTimeBCD, MMS_UTC_TIME UTCTime)
{
	ST_INT32  EvenYearSec=0, LeapYearSec=0, YearSec=0;
	ST_INT32  BigMonthSec=0, SmallMonthSec=0, FebruarySec=0;
	ST_INT	  wYear=0, wMinute=0, wSecond=0;
	ST_UCHAR  wMonth=0,wDay=0,wHour=0;
	ST_INT8   byLeapYear=0, YearLoop=0, byDaysMonth=0, i=0;
	ST_INT32  MonthSec[12];
	ST_INT32  IntergerSecond=0;
	ST_DOUBLE msBase=1,val=0;

	IntergerSecond = UTCTime.secs;

	/*Regard of the time-zone*/
	IntergerSecond += 8 * 60 * 60;

	/* Calculate the Year */
	EvenYearSec = 365 * 24 * 60 * 60;
	LeapYearSec = 366 * 24 * 60 * 60;

	YearLoop = (ST_INT8)( IntergerSecond / ( 3 * EvenYearSec + LeapYearSec ) );
	IntergerSecond %= ( 3 * EvenYearSec + LeapYearSec );
	wYear = 1970 + 4 * YearLoop;

	if( ( 3 * EvenYearSec + LeapYearSec ) > IntergerSecond )
	{
		if( ( 2 * EvenYearSec + LeapYearSec ) <= IntergerSecond )
		{
			wYear += 3; 
			IntergerSecond -= ( 2 * EvenYearSec + LeapYearSec );
		}
		if( ( 2 * EvenYearSec ) <= IntergerSecond )
		{
			wYear += 2;
			byLeapYear = 1;
			IntergerSecond -= ( 2 * EvenYearSec );
		}
		if( EvenYearSec <= IntergerSecond )
		{
			wYear += 1;
			IntergerSecond -= EvenYearSec;
		}
	}
	lpTimeBCD->year = wYear;

	/* Calculate the Month */
	BigMonthSec = 31 * 24 * 60 * 60;
	SmallMonthSec = 30 * 24 * 60 * 60;
	if( byLeapYear ){
		FebruarySec = 29 * 24 * 60 * 60;
		YearSec = LeapYearSec;
	}
	else{
		FebruarySec = 28 * 24 * 60 * 60;
		YearSec = EvenYearSec;
	}
	for(i=1; i<=12; i++)
	{
		if( i==2 )
		{
			MonthSec[i-1] = FebruarySec;
			continue;
		}
		else if( i==4 || i==6 || i==9 || i==11 )
		{
			MonthSec[i-1] = SmallMonthSec;
			continue;
		}
		else
		{
			MonthSec[i-1] = BigMonthSec;
			continue;
		}
	}
	for(i=0; i<12; i++)
	{
		IntergerSecond -= MonthSec[i]; 
		if( IntergerSecond < 0 )
		{
			IntergerSecond += MonthSec[i];
			wMonth = i + 1;
			break;
		}
	}
	lpTimeBCD->month = wMonth;

	/* Calculate the Day */
	for(i=1; i<=31; i++)
	{
		IntergerSecond -= 24 * 60 * 60;
		if( IntergerSecond < 0 )
		{
			IntergerSecond += 24 * 60 * 60;
			wDay = i;
			break;
		}
	}
	lpTimeBCD->day = wDay;

	/* Calculate the Hour */
	for(i=0; i<=24; i++)
	{
		IntergerSecond -= 60 * 60;
		if( IntergerSecond < 0 )
		{
			IntergerSecond += 60 * 60;
			wHour = i;
			break;
		}
	}
	lpTimeBCD->hour = wHour;

	/* Calculate the Minute */
	for(i=0; i<=60; i++)
	{
		IntergerSecond -= 60;
		if( IntergerSecond < 0 )
		{
			IntergerSecond += 60;
			wMinute = i;
			break;
		}
	}
	lpTimeBCD->minute = wMinute;

	/* Evaluate the Second */
	lpTimeBCD->second = IntergerSecond;

	/* Calculate the ms  ns -> ms */
	for( i=0; i<24; i++ )
	{
		msBase = msBase / 2;
	}
	val = UTCTime.fraction * msBase * 1000 ;
	lpTimeBCD->ms = (ST_INT)val;
	if( val > lpTimeBCD->ms + 0.5 )
		lpTimeBCD->ms += 1;
}


BOOL convert_btod_to_timet(MMS_BTOD &btod, tagEVENTTIME &tmEvent)
{
	MMS_UTC_TIME tmUtc;

	asn1_convert_btod_to_utc(&btod, &tmUtc);
	Convert_UTC_To_BCD(&tmEvent, tmUtc);

	return TRUE;
}

long Global_GetSysObjFileNum_CurDir(XMMS_FILE_SYS_OBJ *pFileDir)
{
	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
	long nNum = 0;

	for(int nIndex = 0;nIndex<pFileDir->subFiles.numOfData;nIndex++)
	{
		pSubFileDir = (XMMS_FILE_SYS_OBJ *)*(pFileDir->subFiles.Datas + nIndex);

		if (pSubFileDir->nType == 0)
		{
			nNum++;
		}
	}

	return nNum;
}

CString Global_GetFileDirFullPath(XMMS_FILE_SYS_OBJ *pTagFileDir)
{
	if (pTagFileDir == NULL)
	{
		return NULL;
	}

	CString strPath = mms_string(&pTagFileDir->filedir.filename);
	XMMS_FILE_SYS_OBJ *pTagParent = pTagFileDir->parent;

	while(pTagParent != NULL)
	{
		if (!mms_str_is_null(&pTagParent->filedir.filename))
		{
			strPath = mms_string(&pTagParent->filedir.filename) + strPath;
		}

		pTagParent = pTagParent->parent;
	}

	strPath.Replace("//","/");

	return strPath;
}

BOOL Global_MarkOldFile(XMMS_FILE_SYS_OBJ *pFileDir)
{
	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
	ST_INT nIndex = 0;

	if (pFileDir == NULL)
	{
		return 0;
	}

	for(nIndex = 0;nIndex<pFileDir->subFiles.numOfData;nIndex++)
	{
		pSubFileDir = (XMMS_FILE_SYS_OBJ *)*(pFileDir->subFiles.Datas + nIndex);

		if (pSubFileDir->nType == 0)
		{
			pSubFileDir->bIsNew = FALSE;
		}
	}

	return 1;
}

XMMS_FILE_SYS_OBJ* Global_CheckRepeatOfSysobj(const char *pName, XMMS_FILE_SYS_OBJ *pFileDir)
{
	XMMS_FILE_SYS_OBJ *pFind = NULL;
	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
	int nIndex = 0;

	for(nIndex = 0;nIndex<pFileDir->subFiles.numOfData;nIndex++)
	{
		pSubFileDir = (XMMS_FILE_SYS_OBJ *)*(pFileDir->subFiles.Datas + nIndex);

		if (strcmp(mms_string(&pSubFileDir->filedir.filename),pName) == 0)
		{
			pFind = pSubFileDir;
			break;
		}
	}

	return pFind;
}

XDLT_RPC_METHOD* Global_FindRpcMethod(MMS_ADDR_VECTOR *pVector,const char *pParaFuncation)
{
	XDLT_RPC_METHOD* pCurObj = NULL;
	XDLT_RPC_METHOD* pFind = NULL;

	for(long nIndex = 0;nIndex<pVector->numOfData;nIndex++)
	{
		pCurObj = (XDLT_RPC_METHOD *)*(pVector->Datas + nIndex);

		if (strcmp(mms_string(&pCurObj->paraFuncation),pParaFuncation) == 0)
		{
			pFind = pCurObj;
			break;
		}
	}

	return pFind;
}

XDLT_RPC_METHOD* Global_RpcMethodAddNewMethod(MMS_ADDR_VECTOR *pVector,const char *pParaFuncation)
{
	XDLT_RPC_METHOD* pFind = Global_FindRpcMethod(pVector,pParaFuncation);

	if (pFind == NULL)
	{
		pFind = (XDLT_RPC_METHOD*)malloc(sizeof(XDLT_RPC_METHOD));
		memset(pFind,0,sizeof(XDLT_RPC_METHOD));
		vector_add_data(pVector,pFind);
	}

	mms_str_set(&pFind->paraFuncation,pParaFuncation);
	return pFind;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
