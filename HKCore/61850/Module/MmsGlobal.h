
#pragma once

#include "../../Module/DataMngr/DvmDevice.h"
#include "MmsRecordApi.h"
#include "../../Module/DataMngr/DvmCmp/DvmDeviceMap.h"
#include "XLanguageResourcePp_Mms.h"
#include "../../Module/DataMngr/ShortDatasMngr.h"

#include "../../Protocol/Module/PxiEngine/PxiEngineGlobal.h"
#include "sharemem.h"

//2022-12-12  lijunqing
#ifdef _PSX_QT_LINUX_
#define CStringA CString
#endif

//李俊庆 2019-4-7  将所有的和Data数值子对象的Key，统一到CDvmValue文件的CDvmValueKeyMngr中
//此处的修改，兼容之前的版本功能

// #define VarID_max    7//6 金智增加
// static ST_CHAR g_pszVarID[VarID_max][15] = {"$setMag$f", "$mag$f", "$mag$i","$setVal","$general", "$stVal","$setCharact"};//zhouhj 解决金智读模型描述为空问题

ST_CHAR* FindVarID(ST_CHAR *pMmsName);

// inline ST_CHAR* FindVarID(ST_CHAR *pMmsName)
// {
// 	ST_INT i;
// 	ST_CHAR *p = NULL;
// 
// 	for (i=0; i<VarID_max; i++)
// 	{
// 		p = strstr(pMmsName,g_pszVarID[i]);
// 
// 		if (p != NULL)
// 		{
// 			break;
// 		}
// 	}
// 
// 	return p;
// }

class CMmsValueKeyMngr : public CDvmValueKeyMngr
{
public:
	CMmsValueKeyMngr();
	virtual ~CMmsValueKeyMngr();

	void InitMmsValueKeyMngr(const CString &strFile);
	ST_BOOLEAN IsMmsValueID(const CString &mmsID)
	{
		return IsValueID(mmsID);
// 		ST_CHAR *pszMmsID = NULL;
// 		CString_to_char(mmsID, &pszMmsID);
// 		ST_BOOLEAN bTrue = IsMmsValueID(pszMmsID);
// 		delete pszMmsID;
// 		return bTrue;
	}

	ST_BOOLEAN IsMmsValueID(ST_CHAR *mmsID)
	{
		return IsValueID(mmsID);
// 		for (long nIndex=0; nIndex<m_nKeyCount; nIndex++)
// 		{
// 			if (strstr(mmsID, m_pszMmsValueKey[nIndex]) != NULL)
// 			{
// 				return TRUE;
// 			}
// 		}
// 
// 		return FALSE;
	}

// private:
// 	long m_nKeyCount;
// 	ST_CHAR m_pszMmsValueKey[20][20];
// 
// public:
// 	CStringArray m_astrLdIDKey;
};

extern CMmsValueKeyMngr g_oMmsValueKeyMngr;
extern long g_bMmsReadUseReport; 
extern long g_bResetOnlyClearReport; 

#define WM_MMS_NODE_SELCHANGED (WM_USER + 1127)
#define WM_MMS_REPORT          (WM_USER + 1128)
#define WM_MMS_REPORT_DEBUG          (WM_USER + 1129)
#define WM_MMS_SEND_RCDFILES_DEBUG          (WM_USER + 1130)
#define WM_MMS_CONNECTALLDEVICE_DEBUG          (WM_USER + 1131)

//定义的Tag
static const CString g_bstrPpEngineTag_Name = _T("name");
static const CString g_bstrPpEngineTag_Value = _T("value");
static const CString g_bstrPpEngineTag_ItemIndex = _T("item-index");
static const CString g_bstrPpEngineTag_ID = _T("id");
static const CString g_bstrPpEngineTag_Type = _T("type");

#define		dsID_TripInfo          "TripInfo"					//  0.  报告触发
#define		dsID_Parameter			"Parameter"					//	1.	装置参数  fc="SP"
#define		dsID_Setting			"Setting"					//  2.	保护定值  fc="SG"，fc="SP"
#define		dsID_TripInfo			"TripInfo"					//	7.	保护事件 fc="ST"
#define		dsID_Alarm				"Alarm"						//	8.	运行故障信号 fc="ST"
#define		dsID_Warning			"Warning"					//	9.	运行告警信号 fc="ST"
#define		dsID_SV					"SV"						//	11.	采样值  fc="MX"
#define		dsID_GOOSE				"GOOSE"						//	12.	GOOSE fc="ST"，fc="MX"   
#define		dsID_Ena				"Ena"						//	12.	压板
#define		dsID_Ain				"Ain"						//	13.	遥测
#define		dsID_Din				"Din"						//	14.	遥信(双点遥信)
#define		dsID_Rec				"Rec"						//	15.	录波
#define		dsID_Soe				"Soe"						//	15.	遥信

#define     dsID_Report             _T("report")
#define     dsID_Record             _T("record")
#define     dsID_File             _T("file")
#define     dsID_LogList            _T("loglist")
#define     dsID_MmsDvmAttr         _T("dsmmsdvmattr")


inline ST_BOOLEAN mms_IsSettingsDS(const CString &strDsName)
{
	CString strTemp = strDsName;
	strTemp.MakeLower();

	if ((strTemp.Find(_T("prot")) >= 0) || (strTemp.Find(_T("rcd")) >= 0)  || (strTemp.Find(_T("pqm")) >= 0) || (strTemp.Find(_T("pqld")) >= 0) //zhowTest20180111
		 || (strTemp.Find(_T("d32ld1")) >= 0) )//zhouhj 20211030 特殊厂家,临时增加
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline ST_BOOLEAN mms_IsSettingsDS(ST_CHAR *strDsName)
{
	CString strTemp = strDsName;
	return mms_IsSettingsDS(strTemp);
}

BOOL mms_IsSettingsDS(LD_NODE *pLD_Node);


void mms_CString_to_utc_time(const CString &strTime, MMS_UTC_TIME  &utctime);

CString mms_ParseUnit(long nValue);
void mms_ParseUnit(long nValue, CString &strText);

tagDA* mms_FindData(tagDA *pDatas, long nCount, const CString &strDataAttrID, const CString &strDataAttrValue);
tagDA* mms_FindDataByName(tagDA *pDatas, long nCount, const CString &strDataAttrValue);
tagDA* mms_FindDataByID(tagDA *pDatas, long nCount, const CString &strDataAttrValue);

void mms_GetShortDatasFromTagDA(tagDA *pDatas, long nCount, CShortDatas *pShotDatas);
void mms_GetShortDataFromTagDA(tagDA *pData, CShortData *pShotData);
void mms_SetShortDatasToTagDA(CShortDatas *pShotDatas, tagDA *pDatas, long nCount);
void mms_SetShortDataToTagDA(CShortData *pShotData, tagDA *pData);

void mms_GetDvmDataset(LD_DATASET_INFO *pDataset, CDvmDataset *pDvmDataset);
void mms_GetDvmLogs(MMS_ADDR_VECTOR *pJournalDatas, CDvmLogs *pDvmLogs);//zhouhj读取日志
long mms_GetDvmDatasetReports(ACSI_NODE *pACSI_NODE, CDvmDataset *pDvmDataset, CDvmDeviceMap *pDeviceMap);
long mms_GetDvmDatasetReportsByCycle(ACSI_NODE *pACSI_NODE, CDvmDataset *pDvmDataset, CDvmDeviceMap *pDeviceMap, long nBeginIndex, long nEndIndex);
void mms_GetFileDir(XMMS_FILE_SYS_OBJ *pFileDir, CDvmDataset *pDvmDataset);
void mms_GetDvmData(tagDA *pData, CDvmData *pDvmData);
void mms_GetDvmLog(LD_JOURNAL_DATA *pJournalData,CDvmLog *pDvmLog);//zhouhj读取日志

#ifdef _tagRpt_use_DA_ref
void mms_GetDvmDataRpt(tagDA *pData, tagRptValue *pRptValue, CDvmData *pDvmData);
void mms_GetDvmDataRpt(tagRpt *pRpt, CDvmData *pDvmData);
#endif

void mms_GetDvmDataValue(tagDA *pData, CDvmValue *pDvmValue);
long mms_SetByDvmDataset(const CDvmDataset *pDvmDataset, LD_DATASET_INFO *pDataset, ST_BOOLEAN bUseName=TRUE, ST_BOOLEAN bUseID=TRUE);
void mms_ViewDvmDataset(CDvmDataset *pDvmDataset);
void mms_SetByDvmData(CDvmData *pDvmData, tagDA *pData);
void mms_SetValue(tagDA *pData, long nValue);

ST_BOOLEAN mms_GetValueDataType(tagDA *pDA ,CString &strDataType);//zhouhj 20181217 增加用于查找对应值得数据类型，用于最大值最小值数据的格式化
CString mms_GetValueByDataType(tagValue *pTagValue ,const CString &strDataType);

tagDAValue* mms_FindValue(tagDA *pData, const CString &strTagID);
void mms_SetValue(tagDA *pData, const CString &strTagID, const CString &strValue);
CString mms_GetValue(tagDAValue *pDaValue, const CString &strDataType);
void mms_GetValue(tagValue *pValue, char *strDataType, CString &strValue);
void mms_GetValue(tagDAValue *pDaValue, char *strDataType, CString &strValue);
float    mms_GetValueFloat(tagDAValue *pDaValue, const CString &strDataType);
void mms_SetValue(tagDAValue *pDaValue, const CString &strValue, const CString &strDataType);
void mms_SetValue(tagDAValue *pDaValue, long nValue, const CString &strDataType);
CString mms_GetMinValue(tagDA *pDA);
void     mms_GetMinValue(tagDA *pDA, CString &strText);
CString mms_GetMaxValue(tagDA *pDA);
void     mms_GetMaxValue(tagDA *pDA, CString &strText);
void mms_SetMinValue(tagDA *pDA, const CString &strValue);
void mms_SetMaxValue(tagDA *pDA, const CString &strValue);
void mms_SetStepSizeValue(tagDA *pDA,const CString &strValue);

void mms_GetAllDataset(ACSI_NODE *pDevice, char *pszDsKey, long &nCount, LD_DATASET_INFO **ppDataSetInfo);
// char* mms_GetDatasetKey(char *pszDsID);
char* mms_GetDatasetKey(const CString &strDsID);

// CDeviceNode 命令目标
#define NODE_TYPE_LD_NONE       0
//逻辑设备(CPU)
#define NODE_TYPE_LD_NODE       1
//数据节点
#define NODE_TYPE_DATA_ARRAY    2

//61850设备分为两层
//ACSI_NODE - LD_NODE - DATAS

#define TAGDA_TYPE_NONE   0
#define TAGDA_TYPE_YC     1
#define TAGDA_TYPE_SETS   2
#define TAGDA_TYPE_YK     3
#define TAGDA_TYPE_YB     4
#define TAGDA_TYPE_REPORT 5

static ST_CHAR* g_pszTagDA_Type[] = {"none", "Ain", "Setting", "GOOSE", "Ena", "Soe"};


inline DWORD mms_GetNodeTagDAType(const CString &strID)
{
	if (strID == _T("YC"))
	{
		return  TAGDA_TYPE_YC;
	}
	else if (strID == _T("YK"))
	{
		return  TAGDA_TYPE_YK;
	}
	else if (strID == _T("sets"))
	{
		return  TAGDA_TYPE_SETS;
	}
	else if (strID == _T("softswitch"))
	{
		return  TAGDA_TYPE_YB;
	}

	return TAGDA_TYPE_NONE;
}


#define TREEITEM_TYPE_DEVICE   0X10000000
#define TREEITEM_TYPE_LDEVICE  0X20000000
#define TREEITEM_TYPE_TAGDA    0X30000000
#define TREEITEM_TYPE_FILEDIR  0X40000000
#define TREEITEM_TYPE_LOGLIST  0X50000000
#define TREEITEM_TYPE_NODES    0X60000000

// #define TREEITEM_TYPE_DEVICE   0X01000000
// #define TREEITEM_TYPE_LDEVICE  0X02000000
// #define TREEITEM_TYPE_TAGDA    0X04000000
// #define TREEITEM_TYPE_FILEDIR   0X08000000
// #define TREEITEM_TYPE_LOGLIST  0X10000000
// #define TREEITEM_TYPE_NODES    0X20000000

//////////////////////////////////////////////////////////////////////////

inline DWORD mms_MakeDWORD(DWORD dwDsType, long nDeviceIndex, long nLDIndex=255, long nDaType=255)
{
	return dwDsType | ( (/*(BYTE)*/nDeviceIndex ) << 16) | ( ((BYTE)nLDIndex) << 8) | ((BYTE)nDaType);
}

inline void mms_GetFromDWORD(DWORD dwParam, DWORD &dwDsType, long &nDeviceIndex, long &nLDIndex, long &nDsIndex)
{
	dwDsType = dwParam & 0xF0000000;
	nDeviceIndex = (dwParam & 0x0FFF0000) >> 16;
	nLDIndex = (dwParam & 0x0000FF00) >> 8;
	nDsIndex = dwParam & 0x000000FF;
}

#define FUNCID_MAX_COUNT   11
extern CString g_strFuncIDame[FUNCID_MAX_COUNT+1];// = 
// {	"联机","与设备断开连接","写数据","读数据","启动报告","停止报告",
// "获取当前运行区","设置当前运行区","枚举装置目录", "切换编辑定值区", "固化编辑定值区", _T("")};


inline ST_BOOLEAN mms_Is_SubDA_Value(tagDA *pDA)
{
#ifdef _use_mms_string
	return g_oMmsValueKeyMngr.IsMmsValueID(mms_string(&pDA->DAValue.mmsName));
#else
	return g_oMmsValueKeyMngr.IsMmsValueID(pDA->DAValue.mmsName);
#endif
}

// 2013-4-8  返回是否已枚举的标志
inline ST_BOOLEAN mms_HasEnumDataSet(long nDeviceIndex, long nLDIndex, long nDsIndex)
{
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
	
	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
		return FALSE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];

	return pLD_INFO->bHasEnum;
}

inline ST_BOOLEAN mms_HasEnumDataSet(LD_NODE *pLD, long nDsIndex)
{
	ASSERT(pLD!=NULL);

	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
		return FALSE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];

	return pLD_INFO->bHasEnum;
}

extern void mms_UpdateDeviceState(long nDeviceIndex);
extern void mms_UpdateDeviceState(ACSI_NODE *pDevice);
extern void mms_UpdateDatasetState(long nDeviceIndex, long nLDIndex, long nDsIndex);
extern void mms_UpdateDatasetState(LD_DATASET_INFO *pLD_INFO);

inline long mms_GetReportFlag(ACSI_NODE *pDevice, long nLDIndex, long nDsIndex)
{
	LD_NODE *pLD = &(pDevice->LD[nLDIndex]);
	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return SD_FALSE;

	LD_DATASET_INFO* pLD_INFO = &pLD->DataInfo[nDsIndex];

	return pLD->DataInfo[nDsIndex].bReportFlag;
}

inline long mms_GetReportFlag(long nDeviceIndex, long nLDIndex, long nDsIndex)
{
	return mms_GetReportFlag(&pACSINode[nDeviceIndex],nLDIndex,nDsIndex);
// 	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
// 	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
// 		return SD_FALSE;
// 
// 	LD_DATASET_INFO* pLD_INFO = &pLD->DataInfo[nDsIndex];
// 
// 	return pLD->DataInfo[nDsIndex].bReportFlag;
}

inline void mms_SetReportFlag(ACSI_NODE *pDevice, long nLDIndex, long nDsIndex, ST_BOOLEAN bReportFlag)
{
	LD_NODE *pLD = &(pDevice->LD[nLDIndex]);

	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	pLD_INFO->bReportFlag = bReportFlag;
	//mms_UpdateDatasetState(pLD_INFO);
}

inline void mms_SetReportFlag(long nDeviceIndex, long nLDIndex, long nDsIndex, ST_BOOLEAN bReportFlag)
{
	return mms_SetReportFlag(&pACSINode[nDeviceIndex],nLDIndex,nDsIndex,bReportFlag);
// 	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
// 
// 	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
// 		return;
// 
// 	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
// 	pLD_INFO->bReportFlag = bReportFlag;
// 	//mms_UpdateDatasetState(pLD_INFO);
}

inline void mms_SetReportRet(ACSI_NODE *pDevice, long nLDIndex, long nDsIndex, ST_BOOLEAN bReportRet)
{
	LD_NODE *pLD = &(pDevice->LD[nLDIndex]);

	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	pLD_INFO->bReportRet = bReportRet;
}

inline void mms_SetReportRet(long nDeviceIndex, long nLDIndex, long nDsIndex, ST_BOOLEAN bReportRet)
{
	return mms_SetReportRet(&pACSINode[nDeviceIndex],nLDIndex,nDsIndex,bReportRet);
// 	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
// 
// 	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
// 		return;
// 
// 	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
// 	pLD_INFO->bReportRet = bReportRet;
}

inline ST_INT mms_GetReportRet(long nDeviceIndex, long nLDIndex, long nDsIndex)
{
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return SD_FALSE;

	return pLD->DataInfo[nDsIndex].bReportRet;
}

inline long mms_GetDsDaDatasNum(ACSI_NODE *pNode, long nLDIndex, long nDsIndex)
{
	LD_NODE *pLD = &(pNode->LD[nLDIndex]);
	if (nDsIndex<0 || nDsIndex>MAX_DASET_NUM)
		return 0;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	return pLD_INFO->numData;
}

inline long mms_GetDsDaDatasNum(long nDeviceIndex, long nLDIndex, long nDsIndex)
{
	return mms_GetDsDaDatasNum(&pACSINode[nDeviceIndex],nLDIndex,nDsIndex);
// 	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
// 	if (nDsIndex<0 || nDsIndex>MAX_DASET_NUM)
// 		return 0;
// 
// 	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
// 	return pLD_INFO->numData;
}



inline tagDA* mms_GetDsDaDatas(LD_NODE *pLD, long &nCount, long nDsIndex)
{
	ASSERT(pLD!=NULL);

	if (nDsIndex < 0 || nDsIndex >= MAX_DASET_NUM)
		return NULL;

	nCount = pLD->DataInfo[nDsIndex].numData;

	return pLD->DataInfo[nDsIndex].DataSet;
}

inline tagDA* mms_GetDsDaDatas(LD_NODE *pLD, long &nCount, const CString &strDsDaDataType)
{
	ASSERT(pLD!=NULL);

	for (int i=0; i<pLD->numDaSet; i++)
	{
		LD_DATASET_INFO* pLD_INFO = &pLD->DataInfo[i];
		CStringA strName(pLD_INFO->DataSetID);

		nCount = pLD_INFO->numData;
		if (strDsDaDataType == _T("YC"))
		{
			if (strName.Find("Param")!=-1)
				return pLD_INFO->DataSet;
		}
		else if (strDsDaDataType == _T("sets"))
		{
			if (strName.Find("Setting")!=-1)
				return pLD_INFO->DataSet;
		}
		else if (strDsDaDataType == _T("YB"))
		{
			if (strName.Find("RelayEna")!=-1||
				strName.Find("Ena")!=-1)
				return pLD_INFO->DataSet;
		}
		else if (strDsDaDataType == _T("TRIP"))
		{
			if (strName.Find("TripInfo")!=-1)
				return pLD_INFO->DataSet;
		}
		else if (strDsDaDataType == _T("warning"))
		{
			if (strName.Find("Warning")!=-1)
				return pLD_INFO->DataSet;
		}
		else if (strDsDaDataType == _T("YX"))
		{
			if (strName.Find("RelayDin")!=-1||
				strName.Find("Din")!=-1)
				return pLD_INFO->DataSet;
		}
	}

	nCount = 0;
	return NULL;
}

 inline tagDA* mms_GetDA(long nDeviceIndex, long nLDIndex, long nDsIndex, long nDaDataIndex)
 {
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
	if (!pLD) 
		return NULL;
		
	if (nDaDataIndex<0 || nDaDataIndex>=MAX_DA_NUM)
		return NULL;

	return &pLD->DataInfo[nDsIndex].DataSet[nDaDataIndex];
 }

inline ST_BOOLEAN mms_SetDASubValue(tagDA *pSubDA, /*const CString &strValueID,*/ const CString &strValue)
{
	//CString strTemp;
	//long nLen = strValueID.GetLength();
	//strTemp = pSubDA->DAValue.mmsName;
	//strTemp = strTemp.Right(nLen);

	//if (strTemp.Find(strValueID) != -1)
	if (mms_Is_SubDA_Value(pSubDA))
	{
		mms_SetValue(&pSubDA->DAValue, strValue, pSubDA->DataType);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline ST_BOOLEAN mms_SetDASubValue(tagDA *pSubDA, long nDaNum, const CString &strValue)
{
	long nIndex = 0;

	for (nIndex=0; nIndex<nDaNum; nIndex++)
	{
		tagDA *pDA = &pSubDA[nIndex];

		if (strcmp(pDA->DataType, "STRUCT") == 0)
		{
			if (mms_SetDASubValue(pDA->pSubDA, pDA->nSubDANum, strValue))
			{
				return TRUE;
			}
		}
		else
		{
			if (mms_Is_SubDA_Value(pDA))
			{
				mms_SetValue(&pDA->DAValue, strValue, pDA->DataType);
				return TRUE;
			}
		}
	}

	return FALSE;
}

inline ST_BOOLEAN mms_SetDASubValue(tagDA *pSubDA, /*const CString &strValueID,*/ long nValue)
{
	if (mms_Is_SubDA_Value(pSubDA))
	{
		mms_SetValue(&pSubDA->DAValue, nValue, pSubDA->DataType);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline void mms_SetDASubValue(long nDeviceIndex, long nLDIndex, long nDaDataIndex, long nDsDaDataType, /*const CString &strValueID,*/ const CString &strValue)
{
	tagDA *pDA = mms_GetDA(nDeviceIndex, nLDIndex, nDsDaDataType, nDaDataIndex);
	ASSERT( pDA != NULL );

	if (pDA == NULL)
	{
		return;
	}

	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
	tagDA *pSubDA = NULL;
	for (int i=0; i<pDA->nSubDANum; i++)
	{
		pSubDA = &pDA->pSubDA[i];
		
		if (pSubDA != NULL)
		{
			if (mms_SetDASubValue(pSubDA, /*strValueID,*/ strValue))
			{
				break;
			}
		}
	}
}


inline ST_BOOLEAN mms_GetDASubValue(tagDA *pSubDA,long nCount, /*const CString &strValueID,*/ CString &strValue)
{
	//CString strTemp;
	//long nLen = strValueID.GetLength();
	ST_BOOLEAN bFind = FALSE;


	if (nCount == 1)
	{
		bFind = TRUE;
		strValue = mms_GetValue(&pSubDA->DAValue, pSubDA->DataType);
	}
	else
	{
		for (long nIndex=0; nIndex<nCount; nIndex++)
		{
			//strTemp = pSubDA->DAValue.mmsName;
			//strTemp = strTemp.Right(nLen);

			//if (strTemp.Find(strValueID) != -1)
			if (strcmp(pSubDA->DataType, "STRUCT") == 0)
			{
				if (mms_GetDASubValue(pSubDA->pSubDA, pSubDA->nSubDANum, strValue))
				{
					bFind = TRUE;
					break;
				}
			}
			else
			{
				if (mms_Is_SubDA_Value(pSubDA))
				{
					bFind = TRUE;
					strValue = mms_GetValue(&pSubDA->DAValue, pSubDA->DataType);
					break;
				}
			}

			pSubDA++;
		}
	}
	
	return bFind;
}

inline ST_BOOLEAN mms_GetDASubValueRpt(tagDA *pSubDA,long nCount, /*const CString &strValueID,*/ CString &strValue, tagRptValue *pRptValue)
{
	ST_BOOLEAN bFind = FALSE;

	if (nCount == 1)
	{
		bFind = TRUE;
		//strValue = mms_GetValue(&pSubDA->DAValue, pSubDA->DataType);	
		mms_GetValue(&pRptValue->Value, pSubDA->DataType, strValue);
	}
	else
	{
		for (long nIndex=0; nIndex<nCount; nIndex++)
		{
			//strTemp = pSubDA->DAValue.mmsName;
			//strTemp = strTemp.Right(nLen);

			//if (strTemp.Find(strValueID) != -1)
			if (strcmp(pSubDA->DataType, "STRUCT") == 0)
			{
				if (mms_GetDASubValueRpt(pSubDA->pSubDA, pSubDA->nSubDANum, strValue, pRptValue))
				{
					bFind = TRUE;
					break;
				}
			}
			else
			{
				if (mms_Is_SubDA_Value(pSubDA))
				{
					bFind = TRUE;
					mms_GetValue(&pRptValue->Value, pSubDA->DataType, strValue);
					break;
				}
			}

			pSubDA++;
			pRptValue++;
		}
	}
	
	return bFind;
}

inline ST_BOOLEAN mms_view_GetDASubValue(tagDA *pDA, /*const CString &strValueID,*/ CString &strValue, ST_BOOLEAN bAll)
{
	CString strTemp;
	ST_BOOLEAN bFind = TRUE;

	tagDA *pSubDA = pDA->pSubDA;
	long nCount = pDA->nSubDANum;
#ifdef _use_mms_string
	long nLen = mms_str_length(&pDA->DAValue.mmsName)+1;
#else
	long nLen = strlen(pDA->DAValue.mmsName)+1;
#endif

	if (nCount == 1)
	{
		//strValue = mms_GetValue(&pSubDA->DAValue, pSubDA->DataType);
	}
	else
	{
		for (long nIndex=0; nIndex<nCount; nIndex++)
		{
			if (!bAll)
			{
				if (mms_Is_SubDA_Value(pSubDA))
				{
					pSubDA++;
					continue;
				}
			}
			//if (strcmp(pSubDA->DataType, "UTC_TIME") != 0)
			{
#ifdef _use_mms_string
				CString strTemp;
				strTemp = mms_string(&pSubDA->DAValue.mmsName);
#else
				CString strTemp = pSubDA->DAValue.mmsName;
#endif
				strTemp=strTemp.Mid(nLen);

				if (strTemp.GetLength() > 0)
				{
					strTemp = strTemp + _T("=");
					strTemp = strTemp + mms_GetValue(&pSubDA->DAValue, pSubDA->DataType);
					strTemp = strTemp + _T("; ");
					strValue += strTemp;
				}
			}

			pSubDA++;
		}
	}
	
	return bFind;
}

inline CString mms_GetDASubValue(long nDeviceIndex, long nLDIndex, long nDaDataIndex, long nDsDaDataType, CString &strValue)
{
	tagDA *pDA = mms_GetDA(nDeviceIndex, nLDIndex, nDsDaDataType, nDaDataIndex);
	ASSERT( pDA != NULL );
// 	CString strValue;

	if (pDA == NULL)
	{
		//return strValue;
		strValue.Empty();
	}

	mms_GetDASubValue(pDA->pSubDA,pDA->nSubDANum, /*strValueID,*/ strValue);
}


inline void mms_GetIDFromPath(CString &strID)
{
	long nPos = strID.ReverseFind('$');

	if (nPos >= 0)
	{
		strID = strID.Mid(nPos+1);
	}
}

inline long mms_GetDeviceNodeIndex(ACSI_NODE *pDevice)
{
	long nIndex = 0;
	long nIndexFind = 0;

	for (nIndex=0; nIndex<MAX_DEVICE; nIndex++)
	{
		if (pDevice == &pACSINode[nIndex])
		{
			nIndexFind = nIndex;
			break;
		}
	}

	return nIndexFind;
}

inline void mms_PostDeviceSysMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam)
{
	if (pDevice->bTestLinkState)
	{
		wParam = engineConnectDeviceSuccessful;//engineConnectDeviceSuccessful;    zhouhj  20200703 原来为1  改为宏定义
		lParam = engineConnectDeviceSuccessful;//engineConnectDeviceSuccessful;zhouhj  20200703 原来为1  改为宏定义
	}

	HWND hWnd = (HWND)pDevice->hSysMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		return;
	}

	wParam = mms_GetDeviceNodeIndex(pDevice);
	::PostMessage(hWnd, pDevice->nSysMsg, wParam, lParam);
}


inline void mms_PostDeviceSysMessage2(long nDeviceIndex, WPARAM wParam, LPARAM lParam)
{
	ACSI_NODE *pACSI_NODE = &pACSINode[nDeviceIndex];
	mms_PostDeviceSysMessage(pACSI_NODE, wParam, lParam);
}

inline void mms_PostDeviceCommCmdMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)pDevice->hMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, g_sLangTxt_SendOverMesNotWin, pDevice->hMsgWnd);//_T("发送测试完成消息 【%08x】 不是窗口")
		return;
	}

	wParam = mms_GetDeviceNodeIndex(pDevice);
	//CLogPrint::LogFormatString(XLOGLEVEL_INFOR, g_sLangTxt_SendOverMes, (DWORD)hWnd, pDevice->nMsg);//_T("发送测试完成消息 WND=【%08x】 MSG=【%08x】")
	::PostMessage(hWnd, pDevice->nMsg, wParam, lParam);
}


inline CString mms_GetDAValue(tagDA *pDA)
{
	if (pDA == NULL)
	{
		return _T("");
	}

	CString strText;

	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		mms_GetDASubValue(pDA->pSubDA,pDA->nSubDANum, /*_T("stVal"),*/ strText);
	}
	else
	{
		strText = mms_GetValue(&pDA->DAValue,pDA->DataType);
	}

	return strText;
}

inline void mms_GetDAValue(tagDA *pDA, CString &strText)
{
	if (pDA == NULL)
	{
		strText.Empty();
	}

	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		mms_GetDASubValue(pDA->pSubDA,pDA->nSubDANum, /*_T("stVal"),*/ strText);
	}
	else
	{
		mms_GetValue(&pDA->DAValue,pDA->DataType, strText);
	}
}

inline CString mms_view_GetDAValue(tagDA *pDA, ST_BOOLEAN bAll)
{
	CString strText;

	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		mms_view_GetDASubValue(pDA, /*_T("stVal"),*/ strText, bAll);
	}
	else
	{
		strText = mms_GetValue(&pDA->DAValue,pDA->DataType);
	}

	return strText;
}

inline CString GetDaStepSizeType(tagDA *pDA)
{
	CString strType;

	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
		{
#ifdef _use_mms_string
			if (FindVarID(mms_string(&pDA->pSubDA[nIndex].DAValue.mmsName)) != NULL)
#else
			if (FindVarID(pDA->pSubDA[nIndex].DAValue.mmsName) != NULL)
#endif
			{
				strType = pDA->pSubDA[nIndex].DataType;
			}
		}
	}
	else
	{
		strType = pDA->DataType;
	}

	return strType;
}

inline ST_BOOLEAN mms_GetDAStepSizeValue(tagDA *pDA, CString &strText)
{
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		long nIndex = 0;

		for (nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
		{
			if (mms_GetDAStepSizeValue(&pDA->pSubDA[nIndex], strText))
			{
				return TRUE;
			}
		}
	}
	else
	{
#ifdef _use_mms_string
		if (mms_str_length(&pDA->StepSize.mmsName) > 0)
#else
		if (pDA->StepSize.mmsName[0] != 0)
#endif
		{
			strText = mms_GetValue(&pDA->StepSize, pDA->DataType);
			return TRUE;
		}
	}

#endif
	return FALSE;
}

inline CString mms_GetDADesc(tagDA *pDA)
{
	CString strText;

	if (strcmp(pDA->DataType ,"STRUCT") == 0)
	{
		strText.Format("%s",mms_string(&pDA->DADescri.Value.string) );

		if (strText.GetLength() == 0)
		{
			for (int i=0; i<pDA->nSubDANum;i++)
			{
				tagDA*pSubDA = &pDA->pSubDA[i];
#ifdef _use_mms_string
				char *mmsName = mms_string(&pSubDA->DAValue.mmsName);
				if (strstr(mmsName,"stVal")||
					strstr(mmsName,"setMag")||
					strstr(mmsName,"setVal")||
					strstr(mmsName,"$mag$f")||
					strstr(mmsName,"general"))
#else
				if (strstr(pSubDA->DAValue.mmsName,"stVal")||
					strstr(pSubDA->DAValue.mmsName,"setMag")||
					strstr(pSubDA->DAValue.mmsName,"setVal")||
					strstr(pSubDA->DAValue.mmsName,"$mag$f")||
					strstr(pSubDA->DAValue.mmsName,"general"))
#endif
				{
					strText = mms_GetDADesc(pSubDA);
					break;
				}
			}
		}
	}
	else
	{
		//strText = mms_UTF8ToUnicode(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name));
#ifdef _use_mms_string
		strText.Format("%s", mms_string(&pDA->DADescri.Value.string));
#else
		strText.Format("%s", pDA->DADescri.Value.string);
#endif
	}

	return strText;
}

inline long mms_FindDsSettingLDeviceIndex(ACSI_NODE *pDevice, long nCurrLdeIndex)
{
	CString strLDName;

	if (0 <= nCurrLdeIndex && nCurrLdeIndex < pDevice->numLD)
	{
		strLDName = pDevice->LD[nCurrLdeIndex].LDName;
		strLDName.MakeLower();

		if (mms_IsSettingsDS(strLDName))
		{
			return nCurrLdeIndex;
		}
	}

	long nIndex = 0;
	long nIndexFind = -1;
	LD_NODE *pFind = NULL;

	for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
	{
		strLDName = pDevice->LD[nIndex].LDName;
		strLDName.MakeLower();

		if (mms_IsSettingsDS(strLDName))
		{
			nIndexFind = nIndex;
			break;
		}
	}

	return nIndexFind;
}

inline long mms_FindLDeviceIndex(ACSI_NODE *pDevice, const CString &strID)
{
	long nIndex = 0;
	long nIndexFind = -1;
	LD_NODE *pFind = NULL;
	CString strLDName;
	CString strTemp;
	strTemp = strID;
	strTemp.MakeLower();

	for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
	{
		strLDName = pDevice->LD[nIndex].LDName;
		strLDName.MakeLower();

		if (strLDName.Find(strID) >= 0)
		{
			nIndexFind = nIndex;
			break;
		}
	}

	return nIndexFind;
}

inline long mms_FindLDeviceIndex(long nDeviceIndex, const CString &strID)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	return mms_FindLDeviceIndex(pDevice, strID);
}

long mms_FindDatasetByKey(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, LD_NODE** ppRetLdevice, long *pnLdIndex, LD_DATASET_INFO **parrDataset, long *pDatasetIndex);
LD_DATASET_INFO* mms_FindDatasetEx(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, LD_NODE** ppRetLdevice, CString *pStrRetDatasetPath=NULL);
LD_DATASET_INFO* mms_FindDataset(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, CString *pStrRetDatasetPath=NULL);
LD_DATASET_INFO* mms_FindDataset(LD_NODE *pLdevice, const CString &strDatasetPath);
ST_BOOLEAN mms_FindDatasetIndex(ACSI_NODE *pACSI_NODE, const CString &strDatasetPath, long &nLdIndex, long &nDatasetIndex);

tagDA* mms_FindData(ACSI_NODE *pACSI_NODE, const CString &strDataPath);
tagDA* mms_FindData(ACSI_NODE *pACSI_NODE, LD_NODE** ppRetLdevice, LD_DATASET_INFO** ppRetDataset,const CString &strDataPath);

tagDA* mms_FindData(LD_NODE *pLdevice, const CString &strDataPath);
tagDA* mms_FindData(LD_NODE *pLdevice, LD_DATASET_INFO** ppRetDataset,const CString &strDataPath);
tagDA* mms_FindDataByID(ACSI_NODE *pDevice, const CString &strDataID);
ST_BOOLEAN mms_FindDataByID(ACSI_NODE *pDevice, const CString &strDataID, long &nLdFind, long &nDsFind, long &nDaFind,ST_BOOLEAN bFilterLogDs = FALSE);
ST_BOOLEAN mms_FindDataByID(const char *strDsKey, ACSI_NODE *pDevice, const CString &strDataID, long &nLdFind, long &nDsFind, long &nDaFind);
ST_BOOLEAN mms_FindDataByID(ACSI_NODE *pDevice, const CString &strLdId, const CString &strDsId, const CString &strDataID
					  , long &nLdFind, long &nDsFind, long &nDaFind);

ST_BOOLEAN mms_IsDeviceEnumDatas(ACSI_NODE *pDevice);


//extern ST_BOOLEAN g_nSetRunSGIndexState;   //是否在设置当前运行区的状态中

//根据ID查找装置
ACSI_NODE* mms_Find_ACSI_NODE_ByID(const CString &strDeviceID);
ACSI_NODE* mms_Find_ACSI_NODE_UnConnect();



ST_BOOLEAN mms_HasDatasetDataChanged(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);
ST_BOOLEAN mms_HasDatasetDataChanged(ACSI_NODE *pDevice, ST_INT nLDIndex, ST_INT nDsIndex);


//2015-3-26
ST_BOOLEAN mms_RegisterDataChangedMsg(ACSI_NODE *pDevice, const CString &strPath, ULONG nHwnd, ULONG nMsgID);
ST_BOOLEAN mms_RegisterCmdMsg(ACSI_NODE *pDevice, const CString &strPath, ULONG nHwnd, ULONG nMsgID, ULONG nCmdID, ULONG nCmdState, ULONG wParam, ULONG lParam);
ST_BOOLEAN mms_UnRegisterDataChangedMsg(ACSI_NODE *pDevice, const CString &strPath);
ST_BOOLEAN mms_NeedFireDataChangedMsg(ACSI_NODE *pDevice);
ST_BOOLEAN mms_FireDataChangedMsg(ACSI_NODE *pDevice, tagDA *pDA);
ST_BOOLEAN mms_FireDataChangedMsg(ST_INT nAcsi, ST_INT nLdIndex, ST_INT nDsIndex, ST_INT nDataIndex);

void mms_ResetRptIndex(ACSI_NODE *pDevice);

//2022-11-18  lijunqing  PpEngine、MmsEngine、CmsEngine都有相关内的定义，统一定义
#include "../../IotProtoServer/Module/SttPxCommCmdDef.h"
/*
#define  ParaID_setzone      _T("Set_Zone_Index")
#define  ParaID_path      _T("Path")
#define  ParaID_tmStart           _T("tmStart")
#define  ParaID_tmEnd            _T("tmEnd")
#define  ParaID_NewFNum      _T("NewFNum")
#define  ParaID_DsID      _T("DsID")

#define  ParaID_CmdState  _T("CmdState")
#define  ParaID_wParam    _T("wParam")
#define  ParaID_lParam    _T("lParam")

#define  ParaID_TrgOps_1    _T("TrgOps_1")
#define  ParaID_TrgOps_4    _T("TrgOps_4")
#define  ParaID_IntgPd    _T("IntgPd")

//日志相关的函数
#define  ParaID_Log_bStart             _T("bStart")
#define  ParaID_Log_EntryIDStart    _T("EntryIDStart")
#define  ParaID_Log_bEnd              _T("bEnd")
#define  ParaID_Log_EntryIDEnd     _T("EntryIDEnd")
#define  ParaID_Log_EntryNum     _T("EntryNum")
#define  ParaID_File                      _T("File")
#define  ParaID_Dir                       _T("Dir")
#define  ParaID_Mode                   _T("Mode")

//枚举模型相关参数
#define  ParaID_FileName                   _T("FileName")
#define  ParaID_EnumSetting                _T("EnumSetting")
#define  ParaID_EnumRelayEna               _T("EnumRelayEna")
#define  ParaID_EnumParameter              _T("EnumParameter")
#define  ParaID_EnumRelayAin               _T("EnumRelayAin")
#define  ParaID_EnumRelayDin               _T("EnumRelayDin")
#define  ParaID_EnumTripInfo               _T("EnumTripInfo")
#define  ParaID_EnumAlarm_Warning          _T("EnumAlarm_Warning")
#define  ParaID_EnumRelayBlk               _T("EnumRelayBlk")
#define  ParaID_EnumRelayState             _T("EnumRelayState")
#define  ParaID_EnumRelayFunEn             _T("EnumRelayFunEn")
#define  ParaID_EnumLog                    _T("EnumLog")
#define  ParaID_DevStdMsg                  _T("DevStdMsg")

//针对readdataset命令，是否发送读数据命令
#define  ParaID_UseRead    _T("UseRead")

#define  CMDID_writeenaone  _T("writeenaone")
#define  CMDID_changesetzone  _T("changesetzone")
#define  CMDID_readain  _T("readain")
#define  CMDID_readsetting  _T("readsetting")
#define  CMDID_writesetting  _T("writesetting")
#define  CMDID_readena       _T("readena")
#define  CMDID_writeena       _T("writeena")
#define  CMDID_writedout       _T("writedout")
#define  CMDID_readparameter       _T("readparameter")
#define  CMDID_writeparameter       _T("writeparameter")
#define  CMDID_readsoe       _T("readsoe")
#define  CMDID_readsoeds       _T("readsoeds")
#define  CMDID_reset       _T("reset")
#define  CMDID_registerreport       _T("registerreport")
#define  CMDID_unregisterreport       _T("unregisterreport")
#define  CMDID_readzone        _T("readzone")
#define  CMDID_readdataset        _T("readdataset")
#define  CMDID_read_dir        _T("readdir")
#define  CMDID_read_file        _T("readfile")
#define  CMDID_ReadMmsAttr        _T("readmmsattr")
#define  CMDID_WriteMmsAttr        _T("writemmsattr")

#define  CMDID_connect        _T("connect")
#define  CMDID_disconnect     _T("disconnect")
#define  CMDID_logmmserr      _T("logmmserr")
#define  CMDID_ReadDataOne       _T("readone")
#define  CMDID_SetDataRef       _T("setdaref")

//StartRecord兼容传统规约的StartRecord，主要是为了设置录波文件的路径
#define  CMDID_StartRecord       _T("startrecord")
#define  CMDID_ReadLogCount       _T("readlogcount")
#define  CMDID_ReadLog       _T("readlog")
#define  CMDID_uploadfile       _T("uploadfile")
#define  CMDID_dvmenum         _T("dvmenum")
*/

long mms_Get_LdID_DsPath(const CString &strPath, CString &strLdID, CString &strDsPath);

extern UINT g_nMmsDvmReports_Format_Type; 
extern long g_nDvmNameIsStd;
extern ST_INT g_nCurErrorCode;
extern ST_INT g_nCurErrorClass;
extern ST_INT g_nCurErrorInforRpt;


void InitGlobalDatasetsDesc_ACSI_NODE(ACSI_NODE *pACSI_NODE);
MMS_DATA_NODE* mms_find_data_node_child(MMS_DATA_NODE *pParentNode, const char *pName);
BOOL GlobalSetDatasetName(char *pzfDataSetID,char *pzfDaSetDesc);

///2022-12-30 lijunqing for cms
extern ST_INT	g_nCfgMaxDevNum;//从配置文件中读取到的最大装置数量
extern CDvmLogicDevice *g_pDescDefDatasets;//zhouhj 全部数据集名称的描述

void InitGlobalDatasets_DescDef();
void ReleaseGlobalDatasets_DescDef();


CString GlobalGetRptLogCBString_GSP(char *pzfRptLogCBString);//获取Gps路径,即去除FC及将$改为.
BOOL GlobalHasSpecifiedDataset(char *pDataSetID);//20221122 判断当前数据集的ID是否存在

