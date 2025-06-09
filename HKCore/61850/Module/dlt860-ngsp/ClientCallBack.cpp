#include "StdAfx.h"
#include "ClientCallBack.h"
#include "../61850ClientConfig/61850ClientConfig.h"
#include "../61850ClientAPI/61850ClientGlobal.h"

#include "conversions.h"

#include "dlt860_client.h"
#include <stdlib.h>
#include <stdio.h>

ST_INT g_nStopProtocolParseFlag = 0;

ST_RET My_Pare_DataSetEx(ST_INT nACSI, LD_NODE **pLD, ST_INT *nLdIndex, ST_INT *numDA, tagDA **pTagDA, ST_INT *nDsIndex, const char *dataSet)
{
	ST_INT i;
	ST_INT n;
	//	ST_INT l;

	// 查找数据
	ACSI_NODE *ptACSINode = Client61850_GetAcsiNode(nACSI);
	LD_DATASET_INFO*pLDInfo = NULL;
	LD_NODE *ptLD = NULL;

	*numDA = 0;
	for (n=0;n<ptACSINode->numLD;n++)
	{
		ptLD = &ptACSINode->LD[n];

		if (strstr(dataSet,ptLD->LDName) == NULL)
		{
			continue;
		}

		for (i=0;i<ptLD->numDaSet;i++)
		{
			pLDInfo = &ptLD->DataInfo[i];

			if (pLDInfo)
			{
				if (strstr(dataSet,pLDInfo->DataSetID))
				{
					*pLD = &ptACSINode->LD[n];
					*numDA = pLDInfo->numData;
					*pTagDA = pLDInfo->DataSet;
					*nDsIndex = i;
					*nLdIndex = n;

					return SD_SUCCESS;
				}
			}
		}
	}

	return (*numDA<=0) ? SD_FAILURE : SD_SUCCESS;
}

ST_RET My_Pare_RptID_LD(LD_NODE *ptLD, ST_INT *numDA, tagDA **pTagDA, ST_INT *nDsIndex, const char *pzfRptID)
{
	ST_INT i;
	ST_INT k;
	ST_CHAR *pTemp = NULL;
	CString strRptName,strRptID;

	for (i=0;i<ptLD->numDaSet;i++)
	{
		LD_DATASET_INFO *pLD_INFO = &ptLD->DataInfo[i];

		for (k=0; k<pLD_INFO->numRcb;k++)
		{
			strRptName = GlobalGetRptLogCBString_GSP(pLD_INFO->RCB[k].rcbName);

			if (strstr(pzfRptID, strRptName) || strstr(strRptName, pzfRptID))
			{
				*numDA = ptLD->DataInfo[i].numData;
				*pTagDA = ptLD->DataInfo[i].DataSet;
				*nDsIndex = i;
				return SD_SUCCESS;
			}

			strRptID = GlobalGetRptLogCBString_GSP(pLD_INFO->RCB[k].RptID);

			if (strcmp(pzfRptID, strRptID) == 0)
			{
				*numDA = ptLD->DataInfo[i].numData;
				*pTagDA = ptLD->DataInfo[i].DataSet;
				*nDsIndex = i;
				return SD_SUCCESS;
			}
		}
	}

	return SD_FAILURE;
}

ST_RET My_Pare_RptID(ST_INT nACSI, LD_NODE **pLD, ST_INT *numDA, tagDA **pTagDA, ST_INT *nDsIndex, ST_INT *nLdIndex, const char *pzfRptID)
{
	ST_INT n;

	// 查找数据
	ACSI_NODE *ptACSINode = Client61850_GetAcsiNode(nACSI);
	const char *pTemp = pzfRptID;
	ST_CHAR strDsName[NAMESIZE];
	ST_INT nLen;

	//RptID = 0x0a27fa7c "LDO/LLN0$BR$brcbDeviceState"
	while (*pTemp != '/' && *pTemp != '$')
	{
		pTemp++;

		if (pTemp - pzfRptID > NAMESIZE)
		{
			break;
		}
	}

	if (*pTemp == '/')
	{
		nLen = pTemp - pzfRptID;
		memcpy(strDsName, pzfRptID, nLen);
		strDsName[nLen] = 0;

		for (n=0;n<ptACSINode->numLD;n++)
		{
			LD_NODE *ptLD = &ptACSINode->LD[n];

			if (strstr(ptLD->LDName, strDsName) != NULL)
			{
				if (My_Pare_RptID_LD(ptLD, numDA, pTagDA, nDsIndex, pzfRptID) == SD_SUCCESS)
				{
					*nLdIndex = n;
					*pLD = ptLD;
					return SD_SUCCESS;
				}

			}

		}

		//return SD_FAILURE;
	}

	*numDA = 0;

	for (n=0;n<ptACSINode->numLD;n++)
	{
		LD_NODE *ptLD = &ptACSINode->LD[n];

		if (My_Pare_RptID_LD(ptLD, numDA, pTagDA, nDsIndex, pzfRptID) == SD_SUCCESS)
		{
			*pLD = ptLD;
			*nLdIndex = n;
			return SD_SUCCESS;
		}
	}

	return SD_FAILURE;
}

ST_INT IsEvent( ST_CHAR *lpmmsVarName )
{
	if( strstr( lpmmsVarName, "stVal" ) != NULL )
		return 2;
	if( strstr( lpmmsVarName, "general") != NULL )
		return 3;
	else
		return -1;
}

ST_INT DifEventFromVar_Ex(tagDA *pDA, ST_INT *daindex, ST_INT numVar, ST_INT nDANum)
{
	ST_INT  i;
	ST_INT  IsEventReport=0;
	ST_INT  nEventNum = 0;

	if (daindex == NULL)
		return -1;

	if (nDANum < numVar)
		return -1;

	if (numVar == nDANum)
	{
		for (i=0; i<numVar; i++ )
			pDA[i].ApplyType = 1;

		return 0;
	}

	for (i=0; i<nDANum; i++)
	{
		pDA[i].ApplyType = -1;

		if (daindex[i] == 1)
		{
			//if (strstr(pDA[i].DataType, "STRUCT") != 0)
			if (strcmp(pDA[i].DataType, "STRUCT") == 0)
			{
				if (pDA[i].ApplyType == -1)
					pDA[i].ApplyType = 1;

				continue;
			}	

#ifdef _use_mms_string
			IsEventReport = IsEvent(mms_string(&pDA[i].DAValue.mmsName) );
#else
			IsEventReport = IsEvent(pDA[i].DAValue.mmsName);
#endif
			if (IsEventReport > 0)
			{
				pDA[i].ApplyType = IsEventReport;
				nEventNum++;
			}

			if (IsEventReport < 0)
			{
				pDA[i].ApplyType = 0;
			}
		}
	}

	return nEventNum;
}

ST_INT mms_get_value_count(tagDA *pDA)
{
	int count = 0;
	int index = 0;

	//if (strcmp(pDA->DataType, "STRUCT") == 0)
	if (mms_is_da_struct(pDA) || mms_is_da_array(pDA))
	{
		for (index = 0; index < pDA->nSubDANum; index++)
		{
			count = count + mms_get_value_count(pDA->pSubDA+index);
		}
	}
	else
	{
		count = 1;
	}

	return count;
}

void rpt_init2(tagRpt *pRpt, ST_INT sz, ST_INT cap)
{
	ST_INT len;

	if (pRpt->capacity >= cap)
	{
		pRpt->size = sz;
	}
	else
	{
		rpt_quit(pRpt);
		len = sizeof(tagRptValue) * cap;
		pRpt->Value = (tagRptValue *) malloc (len);
		memset(pRpt->Value, 0, len);
		pRpt->capacity = cap;
		pRpt->size = sz;
	}
}

void rpt_init(tagRpt *pRpt, ST_INT sz)
{
	rpt_init2(pRpt, sz, sz);
}

void rpt_set_value(tagRptValue *pDest,  tagValue *Value, ST_INT bString)
{
	if (bString)
	{
		if (!pDest->bString)
		{
			memset(pDest, 0, sizeof(tagRptValue));
			memset(&pDest->Value, 0, sizeof(pDest->Value));
		}

		mms_str_copy(&pDest->Value.string, &Value->string);
	}
	else
	{
		if (pDest->bString)
		{
			mms_str_quit(&pDest->Value.string);
		}

		pDest->Value = *Value;
	}

	pDest->bString = bString;
}

ST_BOOLEAN mms_IsDataTypeString(ST_CHAR *pszDataType)
{
	return (strstr(pszDataType, "_STR") != NULL);
}

ST_BOOLEAN mms_IsDataString(tagDA *pDA)
{
	return mms_IsDataTypeString(pDA->DataType);
	//return (strstr(pDA->DataType, "_STR") != NULL);
}

ST_VOID mms_CopyDataRptValue(tagDA*pSrc, tagRptValue **ppRptValue)
{
	int index = 0;

	//if (strcmp(pDA->DataType, "STRUCT") == 0)
	if (mms_is_da_struct(pSrc) || mms_is_da_array(pSrc))
	{
		for (index = 0; index < pSrc->nSubDANum; index++)
		{
			mms_CopyDataRptValue(pSrc->pSubDA+index, ppRptValue);
		}
	}
	else
	{
		rpt_set_value(*ppRptValue, &pSrc->DAValue.Value, mms_IsDataString(pSrc));
		*ppRptValue = *ppRptValue + 1;
	}
}

ST_VOID mms_CopyDataRpt(tagDA*pSrc, tagRpt *pRpt)
{
	ST_INT i=0;
	ST_INT size = 0;
	tagRptValue *pRptValue ;

	if (pSrc==NULL)
		return;

	pRpt->pDaRef = pSrc;
	size = mms_get_value_count(pSrc);
	rpt_init(pRpt, size);
	pRptValue = pRpt->Value;
	mms_CopyDataRptValue(pSrc, &pRptValue);
}

void mms_Add_DA_To_Rpts(tagRpt *pReports, tagDA *pTagDA, long *pnCurrRptIndex
						, long nAcsi, long nLdIndex, long nDsIndex
						, long *pnRptCount, long nDaIndex, double dTime, int nTmMs)
{
	//mms_ReleaseDataRpt(&pReports[*pnCurrRptIndex].DA);

	pReports[*pnCurrRptIndex].dvIndex = nAcsi;	
	pReports[*pnCurrRptIndex].ldIndex = nLdIndex;	
	pReports[*pnCurrRptIndex].dsIndex = nDsIndex;	

	mms_CopyDataRpt(pTagDA, &pReports[*pnCurrRptIndex]);

	//2015-3-26发送消息
	mms_FireDataChangedMsg(nAcsi, nLdIndex, nDsIndex, nDaIndex);

	pReports[*pnCurrRptIndex].tmRcv = dTime;
	pReports[*pnCurrRptIndex].nTmRcvMs = nTmMs;

	*pnRptCount = *pnRptCount + 1;
	*pnCurrRptIndex = *pnCurrRptIndex + 1;

	if (*pnRptCount > g_nMaxReportCount)//MAX_REPORT_COUNT) //2018-9-30
	{
		*pnRptCount = g_nMaxReportCount;//MAX_REPORT_COUNT;
	}
	if (*pnCurrRptIndex >= g_nMaxReportCount)//MAX_REPORT_COUNT)
	{
		*pnCurrRptIndex = 0;
	}
}

ST_VOID GeCurrTime_double(double *pdTime,int *pnTmMs)
{
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	CTime tm(tmSys);
	*pdTime = (double)(tm.GetTime());
	*pnTmMs = tmSys.wMilliseconds;
}

BOOL GetMmsDataRef(const char *dataItemRefs,const char *fc,CString &strMmsDataRef)
{
	CString strTmp,strTmp2;
	strTmp = dataItemRefs;
	long nIndex = strTmp.Find('/');

	if (nIndex<=0)
	{
		return FALSE;
	}

	strTmp2 = strTmp.Mid(nIndex+1);

	nIndex = strTmp2.Find('.');

	if (nIndex<=0)
	{
		return FALSE;
	}

	strMmsDataRef.Format(_T("%s$%s$%s"),strTmp2.Left(nIndex),fc,strTmp2.Mid(nIndex+1));
	strMmsDataRef.Replace('.','$');
	return TRUE;
}

GspMmsValue *Gsp_GetActChildValue(GspMmsValue *pDataItem,char  *pzfDataType)
{
	if ((pDataItem->present != Data_PR_array) && (pDataItem->present != Data_PR_structure))
		return NULL;

	GspMmsValue *pChildValue = NULL;

	for (int nIndex = 0;nIndex<pDataItem->choice.structure.list.count;nIndex++)
	{
		pChildValue = pDataItem->choice.structure.list.array[nIndex];

		if ((strcmp(pzfDataType ,_T("BOOL")) == 0)&&(GspMmsValue_getType(pChildValue) == Data_PR_boolean))
		{
			return pChildValue;
		}
		else if ((strcmp(pzfDataType ,_T("INT")) == 0)&&((GspMmsValue_getType(pChildValue) == Data_PR_int8)||(GspMmsValue_getType(pChildValue) == Data_PR_int16)||(GspMmsValue_getType(pChildValue) == Data_PR_int32)))
		{
			return pChildValue;
		}
		else if ((strcmp(pzfDataType ,_T("UINT")) == 0)&&((GspMmsValue_getType(pChildValue) == Data_PR_int8u)||(GspMmsValue_getType(pChildValue) == Data_PR_int16u)||(GspMmsValue_getType(pChildValue) == Data_PR_int32u)))
		{
			return pChildValue;
		}
		else if ((strcmp(pzfDataType ,_T("FLOAT")) == 0)&&(GspMmsValue_getType(pChildValue) == Data_PR_float32))
		{
			return pChildValue;
		}
	}

	return NULL;
}

GspMmsValue* Global_GetGspMmsValue(char *pzfDataType,GspMmsValue *pParentItem,const long &nFindIndex,long &nCurIndex)
{

	if ((pParentItem->present != Data_PR_array) && (pParentItem->present != Data_PR_structure))
		return NULL;

	GspMmsValue* pChildDataItem = NULL;

	for (int nIndex = 0;nIndex<pParentItem->choice.structure.list.count;nIndex++)
	{
		pChildDataItem = pParentItem->choice.structure.list.array[nIndex];

		if ((pChildDataItem->present == Data_PR_array)||(pChildDataItem->present == Data_PR_structure))//如果当前数据类型为结构体或者数组,则在其中查找
		{
			pChildDataItem = Global_GetGspMmsValue(pzfDataType,pChildDataItem,nFindIndex,nCurIndex);

			if (pChildDataItem == NULL)//如果查找失败,继续下一个子节点
			{
				continue;
			}

			return pChildDataItem;
		}
		
		if ((pChildDataItem->present == Data_PR_boolean)&&(strcmp(pzfDataType ,_T("BOOL")) == 0))//对于非结构图数据类型,在以下几种情况代码查找成功
		{
		}
		else if (((pChildDataItem->present == Data_PR_int8)||(pChildDataItem->present == Data_PR_int16)||(pChildDataItem->present == Data_PR_int32))&&(strcmp(pzfDataType ,_T("INT")) == 0))
		{
		}
		else if (((pChildDataItem->present == Data_PR_int8u)||(pChildDataItem->present == Data_PR_int16u)||(pChildDataItem->present == Data_PR_int32u))&&(strcmp(pzfDataType ,_T("UINT")) == 0))
		{
		}
		else if (((pChildDataItem->present == Data_PR_float32)||(pChildDataItem->present == Data_PR_float64))&&(strcmp(pzfDataType ,_T("FLOAT")) == 0))
		{
		}
		else if (((pChildDataItem->present == Data_PR_bit_string)||(pChildDataItem->present == Data_PR_quality)||(pChildDataItem->present == Data_PR_dbpos))&&(strcmp(pzfDataType ,_T("BIT_STR")) == 0))
		{	
		}
		else if ((pChildDataItem->present == Data_PR_utc_time)&&(strcmp(pzfDataType ,_T("UTC_TIME")) == 0))//对于时间的找到就算
		{	
			return pChildDataItem;
		}
		else
			continue;

		if (nFindIndex == nCurIndex)//查找成功且index一致,则直接返回
		{
			return pChildDataItem;
		}

		nCurIndex++;
	}

	return NULL;
}

BOOL Gsp_SetRptValue(tagDA *pTagDA,GspMmsValue *dataItem)
{
	if (strcmp(pTagDA->DataType ,_T("STRUCT")) == 0)
	{
		tagDA *pSubTagDA = NULL;
		GspMmsValue* pChildDataItem = NULL;
		long nFindIndex_Float = 0,nFindIndex_Int = 0,nFindIndex_Uint = 0,nFindIndex_Bool = 0,nFindIndex_BitString = 0 ,nCurIndex = 0;

		for (int nIndex = 0;nIndex<pTagDA->nSubDANum;nIndex++)
		{
			pSubTagDA = &pTagDA->pSubDA[nIndex];
			nCurIndex = 0;

			if (strcmp(pSubTagDA->DataType ,_T("FLOAT")) == 0)
			{
				pChildDataItem = Global_GetGspMmsValue(pSubTagDA->DataType,dataItem,nFindIndex_Float,nCurIndex);
				nFindIndex_Float++;
			}
			else if (strcmp(pSubTagDA->DataType ,_T("INT")) == 0)
			{
				pChildDataItem = Global_GetGspMmsValue(pSubTagDA->DataType,dataItem,nFindIndex_Int,nCurIndex);
				nFindIndex_Int++;
			}
			else if (strcmp(pSubTagDA->DataType ,_T("UINT")) == 0)
			{
				pChildDataItem = Global_GetGspMmsValue(pSubTagDA->DataType,dataItem,nFindIndex_Uint,nCurIndex);
				nFindIndex_Uint++;
			}
			else if (strcmp(pSubTagDA->DataType ,_T("BOOL")) == 0)
			{
				pChildDataItem = Global_GetGspMmsValue(pSubTagDA->DataType,dataItem,nFindIndex_Bool,nCurIndex);
				nFindIndex_Bool++;
			}
			else if (strcmp(pSubTagDA->DataType ,_T("BIT_STR")) == 0)
			{
				pChildDataItem = Global_GetGspMmsValue(pSubTagDA->DataType,dataItem,nFindIndex_BitString,nCurIndex);
				nFindIndex_BitString++;
			}
			else
			{
				pChildDataItem = Global_GetGspMmsValue(pSubTagDA->DataType,dataItem,0,nCurIndex);
			}

//			pChildDataItem = GspMmsValue_getElement(dataItem, nIndex);

			if (pChildDataItem == NULL)
			{
				continue;
			}

			Gsp_SetRptValue(pSubTagDA,pChildDataItem);
		}

		return TRUE;
	}

	GspMmsValue* pActDataItem = dataItem;//实际的子对象,GspMmsValue中的数据值是完全按照模型中的数据值结构层层包裹,但实际设备数据模型会出现跳跃,如SPVT1$MX$Vol1$mag$f,最后两个节点合为一个,故此处需要单独处理

	if (GspMmsValue_getType(dataItem) == Data_PR_structure)
	{
		pActDataItem = Gsp_GetActChildValue(dataItem,pTagDA->DataType);
	}

	if (pActDataItem == NULL)
	{
		return FALSE;
	}

	if (strcmp(pTagDA->DataType ,_T("BOOL")) == 0)
	{
		ASSERT(GspMmsValue_getType(pActDataItem) == Data_PR_boolean);
		pTagDA->DAValue.Value.i = pActDataItem->choice.boolean;
	}
	else if (strcmp(pTagDA->DataType ,_T("INT")) == 0)
	{
//		ASSERT(GspMmsValue_getType(pActDataItem) == Data_PR_int32);
		pTagDA->DAValue.Value.i = pActDataItem->choice.int32;
	}
	else if (strcmp(pTagDA->DataType ,_T("UINT")) == 0)
	{
//		ASSERT(GspMmsValue_getType(pActDataItem) == Data_PR_int32u);
		pTagDA->DAValue.Value.u = pActDataItem->choice.int32u;
	}
	else if (strcmp(pTagDA->DataType ,_T("FLOAT")) == 0)
	{
		pTagDA->DAValue.Value.f = GspMmsValue_toFloat(pActDataItem);
	}
	else if (strcmp(pTagDA->DataType ,_T("UTC_TIME")) == 0)
	{
		ASSERT(GspMmsValue_getType(pActDataItem) == Data_PR_utc_time);
		uint64_t u64Time = convertUtcTimeToMs(pActDataItem->choice.utc_time);
		mms_u64Time_to_utc_time(u64Time,pTagDA->DAValue.Value.utctime);
	}
	else if (strcmp(pTagDA->DataType ,_T("BIT_STR")) == 0)
	{
		CString strTmp;
		GspMmsValue_getBitStringAsCString(pActDataItem,strTmp);
		mms_str_set(&pTagDA->DAValue.Value.string, strTmp);
	}

	return TRUE;
}

BOOL Gsp_SetRptValue(tagDA *pTagDA,long nNumDA,GspMmsValue *dataItem,const char *dataItemRefs,const char *fc,unsigned reasonCode,ST_INT &nDA_Index)
{
	BOOL bFind = FALSE;
	CString strMmsDataRef;
	GetMmsDataRef(dataItemRefs,fc,strMmsDataRef);

	for (int nIndex = 0;nIndex<nNumDA;nIndex++)
	{
		if (strcmp(mms_string(&pTagDA[nIndex].DAValue.mmsName),strMmsDataRef) == 0)
		{
			pTagDA[nIndex].ReasonCode = reasonCode;
			Gsp_SetRptValue(&pTagDA[nIndex],dataItem);
			nDA_Index = nIndex;
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}

void ClientCallBackHandler::ReportHandler_BRCB(void* parameter, void* reportPDU)
{
	if (g_nStopProtocolParseFlag)
	{
		return;
	}

//	printf("用户层面报告回调! 接收到底层报告: %s\n", (char*)parameter);

	if(reportPDU)
	{
		// dataset
		const char* DataSetName = Gsp_ClientReport_getDataSetName(reportPDU);

// 		if(dataSet)
// 		{
// 			printf("报告 dataset: %s \n", dataSet);
// 		}

		// 获取报告 RptID
		const char* rptID = Gsp_ClientReport_getRptId(reportPDU);

// 		if(rptID)
// 		{
// 			printf("报告 RptID: %s \n", rptID);
// 		}

		// 获取报告时间
		uint64_t reportTimeStamp = Gsp_ClientReport_getReportTime(reportPDU);

// 		if(reportTimeStamp)
// 		{
// 			printf("报告时间: %ld \n", reportTimeStamp);
// 		}

		// 获取报告数据
		void* reportDataList = Gsp_ClientReport_getDataSetValueList(reportPDU);

		// 获取报告尺寸
		uint32_t reportDataCount = Gsp_ClientReport_getDataSetValuesSize(reportDataList);

//		printf("报告中数据的条目个数: %d \n", reportDataCount);




		CRemoteDev *pRemoteDev = (CRemoteDev *)parameter;
		ASSERT(pRemoteDev);
		long nDevIndex = pRemoteDev->GetDeviceIndex();
		ACSI_NODE *ptACSINode = pRemoteDev->GetAcsiNode();

		ST_INT j;
		ST_UINT16 OptFldsData;		/* ptr to data part of OptFlds bvstring	*/
		ST_UINT8 InclusionData[1000];	/* ptr to Inclusion bstring		*/
//		ST_CHAR  rptID[NAMESIZE];
//		ST_CHAR  DataSetName[NAMESIZE];
		ST_CHAR *ar_ptr_end;
		ST_INT len;
		ST_INT offset;
		ST_INT numDsVar=0;
		ST_INT numDA=0;
		ST_UCHAR *cptr;
		ST_UCHAR **lpRptDT;
		ST_RET ret=SD_FAILURE;
		ST_INT startMember=0;
		ST_INT EventNum=0;
		tagDA *pTagDA = NULL;
		LD_NODE *pLD = NULL;
		ST_UCHAR EntryID[NAMESIZE];
		ST_INT nDA_Index = 0;
		long nRptCount = 0;
		long nCurrRptIndex = 0;
		ST_INT nDsIndex = -1;
		ST_INT nLdIndex = -1;
		ST_BOOLEAN bFind = SD_FALSE;

		WPARAM wParam = 0;//
		LPARAM lParam = 0;
		tagRpt *pReports = NULL;
		double dTime=0;
		int nTmMs = 0;
		CString strTmpRef;
//		ZeroMemory(rptID,NAMESIZE);
		memset(EntryID,0,NAMESIZE);
		memset(InclusionData,0,sizeof(ST_UINT8)*100);

		//关联数据集pTagDA
		if (My_Pare_RptID(nDevIndex, &pLD, &numDA, &pTagDA, &nDsIndex,&nLdIndex, rptID)!=SD_SUCCESS)//第一步根据rptID查找对应的设备、逻辑设备、数据集、报告等信息
		{
			bFind = SD_FALSE;
		}
		else
		{
			bFind = SD_TRUE;
		}

		if (strstr(rptID,"LEDRs$Oper"))//如果是复归信号，忽略
			return ;

		if (pTagDA == NULL)
		{
			if (My_Pare_DataSetEx(nDevIndex, &pLD, &nLdIndex, &numDA, &pTagDA, &nDsIndex, DataSetName) != SD_SUCCESS) //第二步如果rptID查找失败,根据数据集名称,查找对应的报告及数据集信息
			{
				return;
			}
		}

		pReports = ptACSINode->Reports;
		nCurrRptIndex = ptACSINode->nCurrReportIndex;

		/* 缓存报告记录 */
		nRptCount = ptACSINode->nCurrReportCount;

		if (g_o61850ClientConfig.m_nAddRptBuffer == 1)
		{
			GeCurrTime_double(&dTime,&nTmMs);
			// 获取报告数据
			for(int index=0; static_cast<unsigned int>(index) < reportDataCount; ++index)
			{

				// 获取报告ID
				uint16_t dataID = Gsp_ClientReport_getDataSetValueID(reportDataList, index);

// 				// 打印分割
// 				printf("********************** 报告条目 %d *****************************\n", dataID);

				// 获取报告数据的的refs
				strTmpRef = Gsp_ClientReport_getDataSetValueRefs(reportDataList, index);

				if (strTmpRef.Find(_T("$")) != -1)
				{
					strTmpRef.Replace(_T("$"),_T("."));
				}

				// 获取报告数据的功能约束
				const char* fc = Gsp_ClientReport_getDataSetValueFC(reportDataList, index);

				// 报告上送原因
				const char* reasonCodeStr = Gsp_ClientReport_getReasonCodeStr(reportDataList, index);
				unsigned reasonCode = Gsp_ClientReport_getReasonCode(reportDataList, index);
				printf(" %d 报告条目的报告上送原因: %s -> %d\n", dataID, reasonCodeStr, reasonCode);

				// 获取报告数据
				GspMmsValue* dataItem = Gsp_ClientReport_getDataSetValue(reportDataList, index);

				if (!Gsp_SetRptValue(pTagDA,numDA,dataItem,strTmpRef,fc,reasonCode,nDA_Index))
				{
					continue;
				}

				_snprintf(pReports[ptACSINode[nDevIndex].nCurrReportIndex].EntryID, 8, "%d", dataID);
				mms_Add_DA_To_Rpts(pReports, &pTagDA[nDA_Index], &nCurrRptIndex, nDevIndex
					, nLdIndex, nDsIndex, &nRptCount, nDA_Index, dTime,nTmMs);
				memcpy(pReports[nCurrRptIndex].EntryID,pReports[ptACSINode[nDevIndex].nCurrReportIndex].EntryID,8);
			}

			/* 创建报告结果通知事件 */
			wParam = nDevIndex + (numDsVar << 16);//
			lParam = ((unsigned short)ptACSINode->nCurrReportIndex) + (((unsigned short)nCurrRptIndex) << 16);
			ptACSINode->nCurrReportCount = nRptCount;	
			ptACSINode->nCurrReportIndex = nCurrRptIndex;	
		}
		else
		{
			wParam = nDevIndex + (numDsVar << 16);//
			lParam = 0;
		}

		PostMessageA((HWND)(ptACSINode->hRptMsgWnd), ptACSINode->nRptMsg, wParam, lParam);	
	}

	// 释放数据内存
	Gsp_Report_Destory(reportPDU);
}

void ClientCallBackHandler::ReportHandler_URCB(void* parameter, void* reportPDU)
{
	if (g_nStopProtocolParseFlag)
	{
		return;
	}

	printf("用户层面报告回调! 接受到底层报告: %s\n", (char*)parameter);

	if(reportPDU)
	{
		// dataset
		const char* DataSetName = Gsp_ClientReport_getDataSetName(reportPDU);

		// 获取报告 RptID
		const char* rptID = Gsp_ClientReport_getRptId(reportPDU);

		// 获取报告数据
		void* reportDataList = Gsp_ClientReport_getDataSetValueList(reportPDU);

		// 获取报告尺寸
		uint32_t reportDataCount = Gsp_ClientReport_getDataSetValuesSize(reportDataList);

		CRemoteDev *pRemoteDev = (CRemoteDev *)parameter;
		ASSERT(pRemoteDev);
		long nDevIndex = pRemoteDev->GetDeviceIndex();
		ACSI_NODE *ptACSINode = pRemoteDev->GetAcsiNode();

		ST_INT j;
		ST_UINT16 OptFldsData;		/* ptr to data part of OptFlds bvstring	*/
		ST_UINT8 InclusionData[1000];	/* ptr to Inclusion bstring		*/
		ST_CHAR *ar_ptr_end;
		ST_INT len;
		ST_INT offset;
		ST_INT numDsVar=0;
		ST_INT numDA=0;
		ST_UCHAR *cptr;
		ST_UCHAR **lpRptDT;
		ST_RET ret=SD_FAILURE;
		ST_INT startMember=0;
		ST_INT EventNum=0;
		tagDA *pTagDA = NULL;
		LD_NODE *pLD = NULL;
		ST_UCHAR EntryID[NAMESIZE];
		ST_INT nDA_Index = 0;// 数据集中数据编号,从0开始,便于添加到报告
		long nRptCount = 0;
		long nCurrRptIndex = 0;
		ST_INT nDsIndex = -1;
		ST_INT nLdIndex = -1;
		ST_BOOLEAN bFind = SD_FALSE;

		WPARAM wParam = 0;//
		LPARAM lParam = 0;
		tagRpt *pReports = NULL;
		double dTime=0;
		int nTmMs = 0;
		CString strTmpRef;
		memset(EntryID,0,NAMESIZE);
		memset(InclusionData,0,sizeof(ST_UINT8)*100);

		//关联数据集pTagDA
		if (My_Pare_RptID(nDevIndex, &pLD, &numDA, &pTagDA, &nDsIndex,&nLdIndex, rptID)!=SD_SUCCESS)//第一步根据rptID查找对应的设备、逻辑设备、数据集、报告等信息
		{
			bFind = SD_FALSE;
		}
		else
		{
			bFind = SD_TRUE;
		}

		if (strstr(rptID,"LEDRs$Oper"))//如果是复归信号，忽略
			return ;

		if (pTagDA == NULL)
		{
			if (My_Pare_DataSetEx(nDevIndex, &pLD, &nLdIndex, &numDA, &pTagDA, &nDsIndex, DataSetName) != SD_SUCCESS) //第二步如果rptID查找失败,根据数据集名称,查找对应的报告及数据集信息
			{
				return;
			}
		}

		pReports = ptACSINode->Reports;
		nCurrRptIndex = ptACSINode->nCurrReportIndex;

		/* 缓存报告记录 */
		nRptCount = ptACSINode->nCurrReportCount;

		if (g_o61850ClientConfig.m_nAddRptBuffer == 1)
		{
			GeCurrTime_double(&dTime,&nTmMs);
			// 获取报告数据
			for(int index=0; static_cast<unsigned int>(index) < reportDataCount; ++index)
			{

				// 获取报告ID
				uint16_t dataID = Gsp_ClientReport_getDataSetValueID(reportDataList, index);

				// 获取报告数据的的refs
				strTmpRef = Gsp_ClientReport_getDataSetValueRefs(reportDataList, index);

				if (strTmpRef.Find(_T("$")) != -1)
				{
					strTmpRef.Replace(_T("$"),_T("."));
				}

				// 获取报告数据的功能约束
				const char* fc = Gsp_ClientReport_getDataSetValueFC(reportDataList, index);

				// 报告上送原因
				const char* reasonCodeStr = Gsp_ClientReport_getReasonCodeStr(reportDataList, index);
				unsigned reasonCode = Gsp_ClientReport_getReasonCode(reportDataList, index);
				printf(" %d 报告条目的报告上送原因: %s -> %d\n", dataID, reasonCodeStr, reasonCode);

				// 获取报告数据
				GspMmsValue* dataItem = Gsp_ClientReport_getDataSetValue(reportDataList, index);

				if (!Gsp_SetRptValue(pTagDA,numDA,dataItem,strTmpRef,fc,reasonCode,nDA_Index))
				{
					continue;
				}

				_snprintf(pReports[ptACSINode[nDevIndex].nCurrReportIndex].EntryID, 8, "%d", dataID);
				mms_Add_DA_To_Rpts(pReports, &pTagDA[nDA_Index], &nCurrRptIndex, nDevIndex
					, nLdIndex, nDsIndex, &nRptCount, nDA_Index, dTime,nTmMs);
				memcpy(pReports[nCurrRptIndex].EntryID,pReports[ptACSINode[nDevIndex].nCurrReportIndex].EntryID,8);
			}

			/* 创建报告结果通知事件 */
			wParam = nDevIndex + (numDsVar << 16);//
			lParam = ((unsigned short)ptACSINode->nCurrReportIndex) + (((unsigned short)nCurrRptIndex) << 16);
			ptACSINode->nCurrReportCount = nRptCount;	
			ptACSINode->nCurrReportIndex = nCurrRptIndex;	
		}
		else
		{
			wParam = nDevIndex + (numDsVar << 16);//
			lParam = 0;
		}

		PostMessageA((HWND)(ptACSINode->hRptMsgWnd), ptACSINode->nRptMsg, wParam, lParam);
	}

	// 释放数据内存
	Gsp_Report_Destory(reportPDU);
}

bool /*ClientCallBackHandler::*/ClientCallBack_GetFileHandler(void* parameter,unsigned char* buffer,unsigned int bytesRead,bool endFlag)
{
	FILE* fp = (FILE*) parameter;
	printf("received %i bytes\n", bytesRead);
	if (fwrite(buffer, bytesRead, 1, fp) == 1){

		if(endFlag){
			// 关闭文件
			fclose(fp);
			printf("文件下载完毕, 保存操作\n");
		}

		return true;
	} else {
		printf("Failed to write local file!\n");

		// 关闭文件
		fclose(fp);

		return false;
	}
}


BOOL GspMmsValue_getBitStringAsCString(const GspMmsValue* self,CString &strValue)
{
	int bitPos;
	int bitSize = self->choice.bit_string.size * 8 - self->choice.bit_string.bits_unused;;
	strValue = _T("");

	if (bitSize <=0)////?????????????????????????????????????此处有问题，暂时做特殊处理
	{
		strValue = _T("00");
		return FALSE;
	}

	for (bitPos = 0; bitPos < bitSize; bitPos++) 
	{
		if (GspMmsValue_getBitStringBit(self, bitPos)) 
		{
			strValue += _T("1");
		}
		else
		{
			strValue += _T("0");
		}
	}

	if (strValue == _T("1"))////?????????????????????????????????????此处有问题，暂时做特殊处理
	{
		strValue = _T("10");
	}

	return TRUE;
}
