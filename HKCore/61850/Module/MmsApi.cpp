// MmsApi.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MmsApi.h"
#include "EnumType.h"
#include "MmsGlobal.h"
#include "../../Module/System/TickCount32.h"
#include "../../Module/GpsPcTime/GpsPcTime.h"
#include "XLanguageResourcePp_Mms.h"
#include "../../../sm4.h"
#include "../../Module/API/FileApi.h"
#include "../../Module/API/GlobalConfigApi.h"
#include "../../Module/API/StringConvert/String_Utf8_To_Gbk.h"
#include "../../Module/API/StringConvert/String_Gbk_To_Utf8.h"
#include "MmsWriteXml.h"
#include "../../Module/OSInterface/QT/XGlobalDefine_QT.h"

#ifdef _PSX_QT_LINUX_
#include <pthread.h>
#endif

//extern CMmsEngineRpcMngr *g_theMmsEngineRpcMngr;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int ping(unsigned long IP);


/************************************************************************/
/* For debug version, use a static pointer to avoid duplication of 		*/
/* __FILE__ strings.													*/
/************************************************************************/

#ifdef DEBUG_SISCO
SD_CONST static ST_CHAR *SD_CONST thisFileName = __FILE__;
#endif


long OptFlds_BP[9] = {1,1,1,1,1,0,1,0,0};
long OptFlds_RP[9] = {1,1,1,1,1,0,0,0,1};
long TrgOps_UI[5] = {1,0,0,0,0};

CMmsApi *theMmsApi = NULL;
BOOL g_bMmsEngineDebugMode = FALSE; 
BOOL g_bMmsEnumLDAfterReadXml = FALSE; 
long g_nExitAppForException = 0; 
BOOL g_bUseDvmMapFile = TRUE; 
BOOL g_bMultDevModel = FALSE;
BOOL g_bExportModelAuto = TRUE; 
long g_nSetDeviceCheck = 0;
long g_nUseEntryIDUpdate = 1;
long g_nIntgPd = 3000;
BOOL g_bUseDsDout = FALSE; 
BOOL g_bAutoGenModelDatas = FALSE;  //自动添加装置唯一性识别码、装置型号等固定路径到装置参数数据集下


//////////////////////////////////////////////////////////////////////////


//void mmsi_Trace(LPCWSTR lpszFormat,...)
//{
// 	CStringW str;
// 	va_list argList;
// 	va_start( argList, lpszFormat );
// 	str.FormatV(lpszFormat, argList);
// 	va_end( argList );
// 	OutputDebugStringW(str);
//}
//
//void mmsi_Trace(LPCSTR lpszFormat,...)
//{
// 	CStringA str;
// 	va_list argList;
// 	va_start( argList, lpszFormat );
// 	str.FormatV(lpszFormat, argList);
// 	va_end( argList );
// 	OutputDebugStringA(str);
//}
//
//#define mmsi_TRACE  mmsi_Trace

//////////////////////////////////////////////////////////////////////////

ST_RET enter_u_mvl_rpt_CriticSection()
{
	return 0;//theApp.enter_u_mvl_rpt_CriticSection();
}

ST_RET free_u_mvl_rpt_CriticSection()
{
	return 0;//theApp.free_u_mvl_rpt_CriticSection();
}
//////////////////////////////////////////////////////////////////////////

void WriteDataAfterWait(CThreadProgressInterface *pThread, long nWaiteTime, const CString &strWriteTitle, const CString &strText)
{
	if (nWaiteTime == 0)
	{
		return;
	}

	if (pThread != NULL)
	{
		CString strWait;
        strWait.Format(g_sLangTxt_WriteDataAfterWait.GetString()/*_T("%s:%s:等待%d毫秒")*/
            ,strWriteTitle.GetString(), strText.GetString(), nWaiteTime);
		pThread->ShowMsg(strWait);
		pThread->StartTimer(nWaiteTime);
	}

	Sleep(nWaiteTime);

// 	CGpsPcTimeTickCount oTickCount;
// 
// 	while (oTickCount.GetTickCountLong(FALSE) <= nWaiteTime)
// 	{
// 		Sleep(50);
// 	}
}



CString mms_CONFIG_PATH()
{
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += _T("osicfg.xml");
	return strFile;
}

CString mms_VMD_PATH()
{
	CString strFile;
	strFile = _P_GetBinPath();
	strFile += _T("VMD.ini");
	return strFile;
}

// This is an example of an exported variable

//////////////////////////////////////////////////////////////////////////

// 数据处理线程
#ifdef _PSX_QT_LINUX_
void* MMSCallBackProc(void* lpParameter)
#else
static DWORD WINAPI MMSCallBackProc(void* lpParameter)
#endif
{
	CMmsApi*pMmsApi=(CMmsApi*)lpParameter;

	if (pMmsApi)
	{
		pMmsApi->MmsAcsiServerThread();
	}

	return(0);
}

#ifdef _PSX_QT_LINUX_
void* MMSCallBackProc_Data(void* lpParameter)
#else
static DWORD WINAPI MMSCallBackProc_Data(void* lpParameter)
#endif
{
	CFuncParamEx * pFuncParaEx =( CFuncParamEx *)lpParameter;
	theMmsApi->MmsAcsiServerThread_DataProc(pFuncParaEx);

	return(0);
}

// MMS 报告接收完成通知
// static DWORD WINAPI MMSRptRecvNotify(LPVOID lpParameter)
// {
// 	CMmsApi*pMMSApiObj=(CMmsApi*)lpParameter;
// 
// 	if (pMMSApiObj)
// 		pMMSApiObj->RecvRptNotify();
// 
// 	return(0);
// }

//////////////////////////////////////////////////////////////////////////
#define TIMEOUT_SET	10

ST_CHAR OSICFG_PATH[255];
ST_CHAR SECMANCFG_PATH[255];

BOOL bInit_ACSI = SD_FALSE;

void func_mms_log_error_infor_def()
{
	CLogPrint::LogString(XLOGLEVEL_ERROR, buff_mms_err_text);
}

ST_VOID mvl_log_err(ST_CHAR *pszError)
{
	CLogPrint::LogString(XLOGLEVEL_ERROR, pszError);
}

ST_VOID mvl_log_err_ex(ST_CHAR *pszError, ST_INT nExitMms)
{
	if (nExitMms == 1)
	{
		theMmsApi->ExitMmsApi();
	}
	else
	{
		mvl_log_err(pszError);
	}
}

/*
#define MVL_ERR_USR_TIMEOUT           0x6A01
#define MVL_ERR_REQ_CONTROL           0x6A02
#define MVL_ERR_UNKNOWN_PDU_TYPE      0x6A03
#define MVL_ERR_RUNTIME_TYPE_ID       0x6A04
#define MVL_ERR_ASN1_TO_RUNTIME       0x6A05
#define MVL_ERR_NOT_SYM_ADDR	      0x6A06
#define MVL_ERR_ARRAY_ELEMENT_CNT     0x6A07
#define MVL_ERR_LOCAL_ADDRESS	      0x6A08
#define MVL_ERR_BUFFER_SIZE  	      0x6A09
#define MVL_ERR_DOM_CONTROL   	      0x6A0A
#define MVL_ERR_AA_CONTROL   	      0x6A0B
#define MVL_ERR_AA_SPECIFIC   	      0x6A0C
#define MVL_ERR_NVL_NOT_FOUND  	      0x6A0D
#define MVL_ERR_ALT_ACCESS  	      0x6A0E
#define MVL_ERR_VA_NOT_FOUND  	      0x6A0F
#define MVL_ERR_VA_SPEC		      0x6A10
#define MVL_ERR_NO_REQ_CTRL 	      0x6A11
#define MVL_ERR_NO_CONN_CTRL	      0x6A12
#define MVL_ERR_ASSOC_REQ	      0x6A13
#define MVL_ERR_COMM_SERVE_ACTIVE     0x6A14
#define MVL_ERR_REQ_PEND_COUNT	      0x6A15
#define MVL_ERR_CNF_REJ_ERR           0x6A16
#define MVL_ERR_CNF_ERR_OK	      0x6A17
#define MVL_ERR_CNF_DISCONNECTED      0x6A18
#define MVL_ERR_BAD_TYPE	      0x6A19
#define MVL_ERR_RESOURCE_NOT_AVAIL    0x6A1A
*/
BOOL g_b_post_FuncID_TestProc_error = TRUE;
extern ST_INT g_n_MVL_ERR_USR_TIMEOUT_Count;

void func_mms_error_mvl_req_pend_def(MVL_REQ_PEND *req, ST_INT nACSI)
{
	if (!g_b_post_FuncID_TestProc_error)
	{
		return;
	}

	if (MVL_ERR_USR_TIMEOUT == req->result)
	{
		ACSI_NODE *pDevice = theMmsApi->get_DevACSI_NODEPtr(&theMmsApi->m_oFuncParamEx[nACSI]);

		if (pDevice != NULL)
		{
			if (!pDevice->bTestLinkState)
			{
				g_n_MVL_ERR_USR_TIMEOUT_Count++;

				if (g_n_MVL_ERR_USR_TIMEOUT_Count > 5)
				{
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DvRcvOverTime.GetString()/*_T("装置响应超时【第%d次】")*/
						, g_n_MVL_ERR_USR_TIMEOUT_Count);
				}
				else
				{
                    CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_DvRcvOverTime.GetString()/*_T("装置响应超时【第%d次】")*/
						, g_n_MVL_ERR_USR_TIMEOUT_Count);
				}
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////
//CMmsDvmDevice
CMmsDvmDevice::CMmsDvmDevice()
{

}

CMmsDvmDevice::~CMmsDvmDevice()
{

}

//////////////////////////////////////////////////////////////////////////
//
CMmsApi::CMmsApi()
{
	//2022-10-12  lijunqing
	m_pMmsMsgRcvWnd = NULL;

	m_bMMSConnected = SD_FALSE;
//	m_hThread_Notify = NULL;
	m_hThread_Proc = NULL;

#ifdef SERVER_USE_TWO_THREAD
//	m_hThread_Proc_Data = NULL;
#endif

	m_bOnlyReadValue = SD_FALSE;
// 	m_bEmnuRpt = /*FALSE*/TRUE;
	m_bEnumLN = FALSE;

	for (long nIndex = 0; nIndex<MAX_DEVICE;nIndex++)
	{
		m_oFuncParamEx[nIndex].set_FuncID(FuncID_TestProc);
		m_oFuncParamEx[nIndex].set_DevIndex(nIndex);
		LocalIp[nIndex] = 0;
	}

	CMmsEngineConfigXmlRWKeys::Create();

	mms_log_error_infor = 0;
	func_mms_log_error_infor    = func_mms_log_error_infor_def;
	func_mms_error_mvl_req_pend = func_mms_error_mvl_req_pend_def;
	m_bExitServeACSIServer = FALSE;
	m_bMmsDisConBfConnected = TRUE;

	m_bMaxMmsConnectedTimes = 1;
	ZeroMemory(m_pszMinValKey, 40);
	ZeroMemory(m_pszMaxValKey, 40);
	m_bIsAinMinMax = FALSE;
	m_bAutoSetIP = FALSE;


	//long nIndex = 0;
	//CMmsDvmDevice *pNew = NULL;

	//for (nIndex=0; nIndex<MAX_DEVICE; nIndex++)
	//{
	//	pNew = new CMmsDvmDevice();
	//	m_listDevice.AddTail(pNew);
	//}
}

CMmsApi::~CMmsApi()
{	
	//lijq 2015-1-17
	free_m_smem_ctxt();
//	slogDelBuf();

	//mmsi_ReleaseMMSData();
	CMmsEngineConfigXmlRWKeys::Release();
}

void CMmsApi::OnCreateDevice()	
{	
	if (m_nDeviceCount == 0)
	{
		m_nDeviceCount += 2;
	}
	else
	{
		m_nDeviceCount++;	
	}
}

void CMmsApi::OnReleaseDevice()	
{	
	// 	if (g_bMmsEngineSingleDeviceMode)
	// 	{
	// 		return;
	// 	}

	m_nDeviceCount--;	
}

CMmsDvmDevice* CMmsApi::GetDvmDevice(long nDvIndex)
{
	CMmsDvmDevice *pDvmDevice = (CMmsDvmDevice*)m_listDevice.GetAtIndex(nDvIndex);
	ASSERT (pDvmDevice != NULL);

	return pDvmDevice;
}

CDvmDataset* CMmsApi::GetDsJournal(long nDvIndex)
{
	CMmsDvmDevice *pDvmDevice = GetDvmDevice(nDvIndex);

	return &pDvmDevice->m_oDsJournal;
}

CDvmDataset* CMmsApi::GetDsReport(long nDvIndex)
{
	CMmsDvmDevice *pDvmDevice = GetDvmDevice(nDvIndex);

	return &pDvmDevice->m_oDsReport;
}

CDvmData* CMmsApi::AddJournal(long nDvIndex, tagDA *pDA)
{
	ASSERT (pDA != NULL);

	CDvmDataset *pDataset = GetDsJournal(nDvIndex);
	CDvmData *pNew = new CDvmData();
	mms_GetDvmData(pDA, pNew);
	pDataset->AddTail(pNew);

	return pNew;
}

void CMmsApi::ExitMmsApi()
{
	
}

ST_VOID CMmsApi::ReleaseMMSData()
{
	//////////////////////////////////////////////////////////////////////////
	// osicfgx
	if (spareMem != NULL)
	{
		free (spareMem);
		spareMem = NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	// InitACSIServerNet
	//for (int i=0;i<num_rem_dib_entries;i++)
	
	int i = 0;
	{
		ACSE_CONN *pacse_conn_table = &acse_conn_table[i];
		if (pacse_conn_table)
		{
			chk_free(pacse_conn_table);
			pacse_conn_table = NULL;
		}

		SOCK_INFO *psock_info_table = &sock_info_table[i];
		if (psock_info_table)
		{
			chk_free(psock_info_table);
			psock_info_table = NULL;
		}

#ifdef _not_use_PIPE_MSG
		if (g_pPipeMsgBuffs != NULL)
		{
			mms_free_pipe_msg_bufs_ex(g_pPipeMsgBuffs, num_rem_dib_entries);
			free(g_pPipeMsgBuffs);
			g_pPipeMsgBuffs = NULL;
		}
#endif

		MVL_REQ_PEND *preq_pend_table = &req_pend_table[i];
		if (preq_pend_table)
		{
			chk_free(preq_pend_table);
			preq_pend_table = NULL;
		}

		MVL_COMM_EVENT *pcommEvent_table = &commEvent_table[i];
		if (pcommEvent_table != NULL)
		{
			chk_free(pcommEvent_table);	 
			pcommEvent_table = NULL;
		}

		ST_UCHAR *precv_buf_table = &recv_buf_table[i];
		if (precv_buf_table != NULL)
		{
			chk_free(precv_buf_table);
			precv_buf_table = NULL;
		}
	}

	//if (loc_dib_table)
	//	chk_free(loc_dib_table);

	//if (rem_dib_table)
	//	chk_free(rem_dib_table);

	num_rem_dib_entries = 0;

	//////////////////////////////////////////////////////////////////////////
	// mvl_start_acse
	if (mvl_vmd.dom_tbl != NULL)
	{	
		chk_free(mvl_vmd.dom_tbl);
		mvl_vmd.dom_tbl = NULL;
	}

	if (mvl_vmd.nvlist_tbl != NULL)
	{	
		chk_free(mvl_vmd.nvlist_tbl);
		mvl_vmd.nvlist_tbl = NULL;
	}

	if (mvl_vmd.jou_tbl != NULL)
	{	
		chk_free(mvl_vmd.jou_tbl);
		mvl_vmd.jou_tbl = NULL;
	}

	if (mvl_vmd.var_assoc_tbl != NULL)
	{	
		chk_free(mvl_vmd.var_assoc_tbl);
		mvl_vmd.var_assoc_tbl = NULL;
	}

#ifndef _MVL_TYPE_CTRL_use_one_device_
	if (mvl_type_ctrl != NULL)
	{	
		chk_free(mvl_type_ctrl);
		mvl_type_ctrl = NULL;
	}
#endif

	if (mmsl_enc_buf != NULL)
	{
		chk_free(mmsl_enc_buf);
		mmsl_enc_buf = NULL;
	}

	if (_mms_dec_info != NULL)
	{
		chk_free(_mms_dec_info);
		_mms_dec_info = NULL;
	}

	if (mvl_cfg_info != NULL)
	{
		if (mvl_calling_conn_ctrl != NULL)
		{
			for (int i = 0; i < mvl_cfg_info->num_calling; ++i)
			{
				if (mvl_calling_conn_ctrl[i].aa_objs)
				{
					if (mvl_calling_conn_ctrl[i].aa_objs->var_assoc_tbl)
						chk_free(mvl_calling_conn_ctrl[i].aa_objs->var_assoc_tbl);
					if (mvl_calling_conn_ctrl[i].aa_objs->nvlist_tbl)
						chk_free(mvl_calling_conn_ctrl[i].aa_objs->nvlist_tbl);
					chk_free(mvl_calling_conn_ctrl[i].aa_objs);
				}
			}

			chk_free(mvl_calling_conn_ctrl);
			mvl_calling_conn_ctrl = NULL;
		}

		if (mvl_called_conn_ctrl != NULL)
		{
			for (int i = 0; i < mvl_cfg_info->num_called; ++i)
			{
				if (mvl_called_conn_ctrl[i].aa_objs)
				{
					if (mvl_called_conn_ctrl[i].aa_objs->var_assoc_tbl)
						chk_free(mvl_called_conn_ctrl[i].aa_objs->var_assoc_tbl);
					if (mvl_called_conn_ctrl[i].aa_objs->nvlist_tbl)
						chk_free(mvl_called_conn_ctrl[i].aa_objs->nvlist_tbl);
					chk_free(mvl_called_conn_ctrl[i].aa_objs);
				}
			}

			chk_free(mvl_called_conn_ctrl);
			mvl_called_conn_ctrl = NULL;
		}

		chk_free(mvl_cfg_info);
		mvl_cfg_info = NULL;
	}
}


ST_VOID CMmsApi::ReleaseObjData()
{
	for (int i=0; i<numDevice; i++)
	{
		ACSI_NODE *pDvNode = &pACSINode[i];
		if (!pDvNode)
			continue;

		ReleaseObjData(pDvNode);


#ifdef _MVL_TYPE_CTRL_use_one_device_
		chk_free(pDvNode->p_mvl_type_ctrl);
		pDvNode->p_mvl_type_ctrl = NULL;
#endif
	}

	ReleaseDeviceNode();

//	pACSINode = NULL;//zhouhj 20181009 解决析构之后的问题
}

ST_VOID CMmsApi::ReleaseObjData(ACSI_NODE *pDvNode)
{
#ifdef _use_dynamic_mem
	mms_Free_ACSI_NODE(pDvNode);
#else
	for (int j=0;j<pDvNode->numLD; j++)
	{
		LD_NODE*pLD = &pDvNode->LD[j];

		for (int k=0;k<pLD->numDaSet;k++)
			ReleaseTagDAAry(pLD->DataInfo[k].DataSet, &pLD->DataInfo[k].numData);
	}
#endif

	pDvNode->numLD = 0;
	pDvNode->nHasDeviceModel = 0;
	pDvNode->DeviceFilePath[0] = 0;
	pDvNode->devID[0] = 0;
	pDvNode->nReleaseWhenUnlink = 0;
	pDvNode->psw[0] = 0;
	pDvNode->key[0] = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 基本操作 */
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 2012-10-08  解析变量的单位 */
ST_VOID CMmsApi::My_PareVarUnite(int nValue, CString &strText)
{
	ST_CHAR*pValue = (ST_CHAR*)&nValue;

	CString strUnit = "";
	CString strMuti = "";

	if (pValue)
	{
		CSIUnit SIUnit;
		int nIndex = *pValue;
		strUnit = SIUnit.GetSIUnite(nIndex);

		CMultiplier Multiplier;
		nIndex = *(++pValue);
		strMuti = Multiplier.GetMultiplierUnite(nIndex);
	}

    strText = strMuti + strUnit;
}

tagDA* mms_new_tagda()
{
	tagDA* pNewDA = (tagDA*)malloc(sizeof(tagDA));//new tagDA();
	ZeroMemory(pNewDA, sizeof(tagDA));
	return pNewDA;
}

tagDA* mms_new_tagda(long nCount)
{
	int nSize = nCount * sizeof (tagDA);
	tagDA* pNewDA = (tagDA*)malloc(nSize);//new tagDA();
	ZeroMemory(pNewDA, nSize);
	return pNewDA;
}

ST_INT CMmsApi::My_PareVarType_Value(CTagDAList &listDA, RUNTIME_TYPE* rt_out, ST_CHAR *DAName)
{
	tagDA *pNewDA = NULL;

	if (rt_out->comp_name_ptr != NULL)
	{
		pNewDA = mms_new_tagda();//new tagDA();
		//ZeroMemory(pNewDA, sizeof(tagDA));
#ifdef _use_mms_string
		mms_str_set3(&pNewDA->DAValue.mmsName, DAName, 3);
		ST_CHAR *pMmsName = mms_string(&pNewDA->DAValue.mmsName);
#else
		ST_CHAR *pMmsName = pNewDA->DAValue.mmsName;
		strcpy(pMmsName, DAName);
#endif
		listDA.AddTail(pNewDA);


#ifdef _use_mms_string
		if (pMmsName[strlen(DAName)-1] != '$')
		{
			mms_str_cat( &pNewDA->DAValue.mmsName, "$");
		}

		mms_str_cat( &pNewDA->DAValue.mmsName, rt_out->comp_name_ptr);
		pMmsName = mms_string(&pNewDA->DAValue.mmsName);
#else
		if (pMmsName[strlen(DAName)-1] != '$')
		{
			strcat(pMmsName, "$");
		}
		strcat(pMmsName, rt_out->comp_name_ptr);
#endif
		set_FCDA_type(rt_out->el_tag, pNewDA->DataType);
		mms_InitDA_DataType(pNewDA);

		if (strstr(pMmsName,"$SV$")|| strstr(pMmsName,"$CF$")|| strstr(pMmsName,"$DC$")|| strstr(pMmsName,"$SE$")||
			strstr(pMmsName,"$BR$")|| strstr(pMmsName,"$RP$")|| strstr(pMmsName,"$LG$")|| strstr(pMmsName,"$GO$")||
			strstr(pMmsName,"$GS$")|| strstr(pMmsName,"$US$"))
		{
			pNewDA->bWrite = SD_TRUE;
		}
		else
		{
			pNewDA->bWrite = SD_FALSE;
		}

		return 1;
	}
	else
	{
		return 0;
	}
}

ST_VOID CMmsApi::My_PareVarType_Struct(CTagDAList &listDA, ST_CHAR *DAName, ST_INT num_rt_out, ST_INT &index, RUNTIME_TYPE* &rt_out)
{
	tagDA *pNewDA = NULL;
	ST_INT len = strlen(DAName);

	ST_CHAR ValueName[NAMESIZE];
	memset(ValueName, 0, NAMESIZE);
	strcpy(ValueName, DAName);
#ifdef _use_mms_string
	ST_CHAR	  mmsName[NAMESIZE];
#endif

	rt_out++;

	if (DAName[len-1] == '$')
	{
		DAName[len-1] = 0;
	}

	for (; index<num_rt_out; index++)
	{
		if (RT_STR_START == rt_out->el_tag)	/*struct start*/
		{		
			if (NULL != rt_out->comp_name_ptr)
			{
				_snprintf(ValueName,NAMESIZE,"%s$%s",DAName, rt_out->comp_name_ptr);
			}
			else
				_snprintf(ValueName,NAMESIZE,"%s",DAName);

			My_PareVarType_Struct(listDA, ValueName, num_rt_out, index, rt_out);
			continue;
		}
		else if (RT_STR_END == rt_out->el_tag)	/*struct end*/
		{
			rt_out++;
			index++;
			break;
		}
		else if (RT_ARR_START == rt_out->el_tag)
		{
			pNewDA = mms_new_tagda();//new tagDA();
			//ZeroMemory(pNewDA, sizeof(tagDA));
			listDA.AddTail(pNewDA);
			sprintf(pNewDA->DataType, "ARRAY");
			mms_InitDA_DataType(pNewDA);

#ifdef _use_mms_string
			if (NULL != rt_out->comp_name_ptr)
				_snprintf(mmsName,NAMESIZE,"%s$%s",DAName, rt_out->comp_name_ptr);
			else
				_snprintf(mmsName,NAMESIZE,"%s",DAName);

			mms_str_set(&pNewDA->DAValue.mmsName, mmsName);
#else
			if (NULL != rt_out->comp_name_ptr)
				_snprintf(mmsName,NAMESIZE,"%s$%s",DAName, rt_out->comp_name_ptr);
			else
				_snprintf(mmsName,NAMESIZE,"%s",DAName);
#endif

			My_PareVarType_Array(pNewDA, num_rt_out, index, rt_out);
			continue;
		}
		else if (RT_ARR_END == rt_out->el_tag )
		{
			ASSERT(FALSE);
		}
		else
		{
			//My_PareVarType_Value(listDA, rt_out, ValueName);//????????????????
			My_PareVarType_Value(listDA, rt_out, DAName/*ValueName*/);//zhouhj 20180201 替换因为发现与实际模型中路径相比 q、t 的路径多出了一位，实测发现修改后 各路径下的时间值都能正确读取了
		}

		rt_out++;
	}
}

ST_VOID CMmsApi::My_PareVarType_Array(tagDA *pDA, ST_INT num_rt_out, ST_INT &index, RUNTIME_TYPE* &rt_out)
{
	ST_INT k;
	ST_CHAR DAName[NAMESIZE];
	CTagDAList listDA;
	tagDA *pNewDA = NULL;
	tagDA *pSubFirst = NULL;
	tagDA *pTemp = NULL;
#ifdef _use_mms_string
	ST_CHAR	  mmsName[NAMESIZE];
#endif

	if (pDA == NULL)
		return;

	//创建数组
	sprintf(pDA->DataType, "ARRAY");
	mms_InitDA_DataType(pDA);
	pDA->nSubDANum = rt_out->u.arr.num_elmnts;
	pDA->pSubDA = mms_new_tagda(pDA->nSubDANum);//new struct tagDA[pDA->nSubDANum];
	pSubFirst = pDA->pSubDA;
	//ZeroMemory(pDA->pSubDA, sizeof(tagDA)*pDA->nSubDANum);
	mms_InitDatas(pDA->pSubDA, pDA->nSubDANum);

	rt_out++;
	memset(DAName, 0, NAMESIZE);
	strcpy(DAName,mms_string(&pDA->DAValue.mmsName));
	ST_INT len = strlen(DAName);

	if (DAName[len-1] == '$')
	{
		DAName[len - 1] = 0;
	}

	for (; index<num_rt_out; index++)
	{
// 		p = strrchr(DAName,'$');
// 		if (NULL != p)
// 			*p = 0;

		if (RT_STR_START == rt_out->el_tag)	/*struct start*/
		{		
			My_PareVarType_Struct(listDA, DAName, num_rt_out, index, rt_out);
			continue;
		}
		else if (RT_STR_END == rt_out->el_tag)	/*struct end*/
		{
			ASSERT(FALSE);
		}
		else if (RT_ARR_START == rt_out->el_tag)
		{
			pNewDA = mms_new_tagda();//new tagDA();
			//ZeroMemory(pNewDA, sizeof(tagDA));
			listDA.AddTail(pNewDA);

#ifdef _use_mms_string
			if (NULL != rt_out->comp_name_ptr)
				_snprintf(mmsName,NAMESIZE,"%s$%s",DAName, rt_out->comp_name_ptr);
			else
				_snprintf(mmsName,NAMESIZE,"%s",DAName);

			mms_str_set(&pNewDA->DAValue.mmsName, mmsName);
#else
			if (NULL != rt_out->comp_name_ptr)
				_snprintf(pNewDA->DAValue.mmsName,NAMESIZE,"%s$%s$",DAName, rt_out->comp_name_ptr);
			else
				_snprintf(pNewDA->DAValue.mmsName,NAMESIZE,"%s$",DAName);
#endif

			My_PareVarType_Array(pNewDA, num_rt_out, index, rt_out);
			continue;
		}
		else if (RT_ARR_END == rt_out->el_tag )
		{
			rt_out++;
			index++;
			break;
		}
		else
		{
			My_PareVarType_Value(listDA, rt_out, DAName);
		}

		rt_out++;
	}

	//数组的第一个数据对象
	pSubFirst->nSubDANum = listDA.GetCount();

	if (pSubFirst->nSubDANum == 1)
	{
		pTemp = listDA.GetAtIndex(0);
		mms_CopyData(pTemp, pSubFirst, FALSE);
		mms_ReleaseData(pTemp);
		free(pTemp);////delete pTemp;
	}
	else if (pSubFirst->nSubDANum > 1)
	{
		pSubFirst->pSubDA = mms_new_tagda(pSubFirst->nSubDANum);//new struct tagDA[pSubFirst->nSubDANum];
		strcpy(pSubFirst->DataType, "STRUCT");
		mms_InitDA_DataType(pSubFirst);
		//ZeroMemory(pSubFirst->pSubDA, sizeof(tagDA)*pSubFirst->nSubDANum);
		mms_InitDatas(pDA->pSubDA, pDA->nSubDANum);
	
		for (k=0; k<pSubFirst->nSubDANum; k++)
		{
			pTemp = listDA.GetAtIndex(k);
			mms_CopyData(pTemp, &pSubFirst->pSubDA[k], FALSE);
			mms_ReleaseData(pTemp);
			free(pTemp);//delete pTemp;
		}
	}

	//
	k = 0;

#ifdef _use_mms_string
	if (mms_str_length(&pDA->pSubDA[k].DAValue.mmsName) == 0)
#else
	if (pDA->pSubDA[k].DAValue.mmsName[0] == 0)
#endif
	{
		//My_CopyData(pSubFirst, &pDA->pSubDA[k]);
		if (mms_str_length(&pDA->DAValue.mmsName) == 0)
		{
			sprintf(DAName, "%d", k);
		}
		else
		{
			strcpy(DAName, mms_string(&pDA->DAValue.mmsName));
		}

		//2017-12-11
		//My_PareVarType_Array_MmsName(&pDA->pSubDA[k], DAName);
		My_PareVarType_Array_Set_Sub_MmsName(pDA, DAName);
		//strcat(pDA->pSubDA[k].DAValue.mmsName, DAName);
	}

	for (k=1; k<pDA->nSubDANum; k++)
	{
		mms_CopyData(pSubFirst, &pDA->pSubDA[k], FALSE);
		sprintf(DAName, "%d", k);
		//strcat(pDA->pSubDA[k].DAValue.mmsName, DAName);
		My_PareVarType_Array_MmsName(&pDA->pSubDA[k], DAName);
	}

	listDA.RemoveAll();
}

ST_VOID CMmsApi::My_PareVarType_Array_MmsName(tagDA *pDA, ST_CHAR *pArrayIndex)
{
	if (strcmp(pDA->DataType, "STRUCT") != 0)
	{
#ifdef _use_mms_string
		mms_str_append(&pDA->DAValue.mmsName, pArrayIndex);
#else
		strcat(pDA->DAValue.mmsName, pArrayIndex);
#endif
	}
	else
	{

	}

	if (pDA->nSubDANum == 0)
	{
		return;
	}

	long nIndex = 0;

	for (nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
	{
		My_PareVarType_Array_MmsName(&pDA->pSubDA[nIndex], pArrayIndex);
	}
}

ST_VOID CMmsApi::My_PareVarType_Array_Set_Sub_MmsName(tagDA *pDA, ST_CHAR *pValName)
{
	long nIndex = 0;

	for (nIndex=0; nIndex<pDA->nSubDANum; nIndex++)
	{
		mms_str_set(&pDA->pSubDA[nIndex].DAValue.mmsName, pValName);
	}
}

/* 2012-10-15  解析数据类型 */ 
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_VOID CMmsApi::My_PareVarType(ST_INT type_id, tagDA *pDA, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_VOID CMmsApi::My_PareVarType(ST_INT type_id, tagDA *pDA)
#endif
{
	ST_INT i;
	RUNTIME_TYPE *rt_out;
	ST_INT num_rt_out;
	ST_CHAR *p;
	ST_CHAR DAName[NAMESIZE];
	CTagDAList listDA;
	tagDA *pNewDA = NULL;
#ifdef _use_mms_string
	ST_CHAR mmsName[NAMESIZE];
#endif

	if (pDA == NULL)
		return;

	mms_ReleaseDataX(pDA);
	memset(DAName, 0, NAMESIZE);

#ifdef _use_mms_string
	mms_str_copy2(DAName, &pDA->DAValue.mmsName);
#else
	_snprintf(DAName,NAMESIZE,"%s",pDA->DAValue.mmsName);
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
	mvl_get_runtime(type_id, &rt_out, &num_rt_out, mvl_type_ctrl);
#else
	mvl_get_runtime(type_id, &rt_out, &num_rt_out);
#endif

	if (num_rt_out >= 3)
	{
		sprintf(pDA->DataType, "STRUCT");
		mms_InitDA_DataType(pDA);
	}
	else
	{
		pDA->Type_id = type_id;
		set_FCDA_type(rt_out->el_tag, pDA->DataType);
		mms_InitDA_DataType(pDA);
		return;
	}

	pDA->nSubDANum = 0;
	strcat(DAName,"$");

	for (i=0; i<num_rt_out; i++)
	{
		p = strrchr(DAName,'$');
		if (NULL != p)
			*p = 0;

		if (RT_STR_START == rt_out->el_tag)	/*struct start*/
		{		
			My_PareVarType_Struct(listDA, DAName, num_rt_out, i, rt_out);
			continue;
		}
		else if (RT_STR_END == rt_out->el_tag)	/*struct end*/
		{
			ASSERT(FALSE);
		}
		else if (RT_ARR_START == rt_out->el_tag)
		{
			pNewDA = mms_new_tagda();//new tagDA();
			//ZeroMemory(pNewDA, sizeof(tagDA));
			listDA.AddTail(pNewDA);
			sprintf(pNewDA->DataType, "ARRAY");
			mms_InitDA_DataType(pNewDA);

#ifdef _use_mms_string
			if (NULL != rt_out->comp_name_ptr)
				_snprintf(mmsName,NAMESIZE,"%s$%s$",DAName, rt_out->comp_name_ptr);
			else
				_snprintf(mmsName,NAMESIZE,"%s$",DAName);
			mms_str_set(&pNewDA->DAValue.mmsName, mmsName);
#else
			if (NULL != rt_out->comp_name_ptr)
				_snprintf(pNewDA->DAValue.mmsName,NAMESIZE,"%s$%s$",DAName, rt_out->comp_name_ptr);
			else
				_snprintf(pNewDA->DAValue.mmsName,NAMESIZE,"%s$",DAName);
#endif

			My_PareVarType_Array(pNewDA, num_rt_out, i, rt_out);
			continue;
		}
		else if (RT_ARR_END == rt_out->el_tag )
		{
			ASSERT (FALSE);
		}
		else
		{
			My_PareVarType_Value(listDA, rt_out, DAName);			
		}

		rt_out++;
	}

	pDA->nSubDANum = listDA.GetCount();

	if (pDA->nSubDANum > 0)
	{
		pDA->pSubDA = mms_new_tagda(pDA->nSubDANum);//new struct tagDA [pDA->nSubDANum];
		//ZeroMemory(pDA->pSubDA, sizeof(tagDA)*pDA->nSubDANum);
		mms_InitDatas(pDA->pSubDA, pDA->nSubDANum);
	}

	for (i=0; i<pDA->nSubDANum; i++)
	{
		pNewDA = listDA.GetAtIndex(i);
		mms_CopyData(pNewDA, &pDA->pSubDA[i], FALSE);
		mms_ReleaseData(pNewDA);
		free(pNewDA);//delete pNewDA;
	}

	listDA.RemoveAll();
// 	mms_ReleaseData(&tempDA);
}

/* 2012-11-09  解析出报告数据 */
ST_VOID CMmsApi::My_GetRptData(ST_INT nDsIndex, CString *strRpt)
{
	LD_NODE *pLD = get_DevLDPtr(&m_oFuncParamEx[0]);//zhouhj 20181002 目前此函数的函数源未被调用到，故默认采用第一台装置
	if (!pLD) return;

	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return;

	int nDASize = pLD->DataInfo[nDsIndex].numData;
	tagDA *pDA = pLD->DataInfo[nDsIndex].DataSet;

	CString strTemp = "";
	CString strText = "";
	for (int i=0; i<nDASize; i++)
	{
		if (pDA[i].bModify!=SD_TRUE)
			continue;

		if (strstr(pDA[i].DataType,"STRUCT"))
		{ 
#ifdef _use_mms_string
			strText = mms_string(&pDA[i].DADescri.Value.string);//mms_UTF8ToUnicode(pDA[i].DADescri.Value.name, strlen(pDA[i].DADescri.Value.name));
#else
			strText = pDA[i].DADescri.Value.string;//mms_UTF8ToUnicode(pDA[i].DADescri.Value.name, strlen(pDA[i].DADescri.Value.name));
#endif

			if (pDA[i].pSubDA==NULL)
				continue;

			for (int j=0; j<pDA[i].nSubDANum; j++)
			{
				strTemp = "";

				if (strstr(pDA[i].pSubDA[j].DataType,"BOOL"))
				{
					strTemp.Format("  状态值:%d <*>",pDA[i].pSubDA[j].DAValue.Value.u);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"BIT_STR"))
				{
					strTemp.Format("  状态值:%s <*>",pDA[i].pSubDA[j].DAValue.Value.string);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"INT"))
				{
					strTemp.Format("  状态值:%d <*>",pDA[i].pSubDA[j].DAValue.Value.i);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"UINT"))
				{
					strTemp.Format("  状态值:%d <*>",pDA[i].pSubDA[j].DAValue.Value.u);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"FLOAT"))
				{
					strTemp.Format("  状态值:%.6f <*>",pDA[i].pSubDA[j].DAValue.Value.f);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"OCT_STR"))
				{
					strTemp.Format("  状态值:%s <*>",pDA[i].pSubDA[j].DAValue.Value.string);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"V_STR"))
				{
					strTemp.Format("  状态值:%s <*>",pDA[i].pSubDA[j].DAValue.Value.string);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"B_TIME"))
				{

				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"BOOL[]"))
				{
					strTemp.Format("  状态值:%d <*>;",pDA[i].pSubDA[j].DAValue.Value.u);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"UTC_TIME"))
				{
					tagEVENTTIME lpTimeBCD;
					Convert_UTC_To_BCD(&lpTimeBCD, pDA[i].pSubDA[j].DAValue.Value.utctime);
					strTemp.Format("时间：%d-%d-%d-%d-%d-%d-%d\n\t",lpTimeBCD.year,lpTimeBCD.month,lpTimeBCD.day,
						lpTimeBCD.hour,lpTimeBCD.minute,lpTimeBCD.second,lpTimeBCD.ms);
				}
				else if (strstr(pDA[i].pSubDA[j].DataType,"UTF8_STR"))
				{

				}

				strText += strTemp;
			}
		}
		else
		{
			strTemp = "";

			if (strstr(pDA[i].DataType,"BOOL"))
			{
				strTemp.Format("  状态值:%d <*>",pDA[i].DAValue.Value.u);
			}
			else if (strstr(pDA[i].DataType,"BIT_STR"))
			{
				strTemp.Format("  状态值:%s <*>",pDA[i].DAValue.Value.string);
			}
			else if (strstr(pDA[i].DataType,"INT"))
			{
				strTemp.Format("  状态值:%d <*>",pDA[i].DAValue.Value.i);
			}
			else if (strstr(pDA[i].DataType,"UINT"))
			{
				strTemp.Format("  状态值:%d <*>",pDA[i].DAValue.Value.u);
			}
			else if (strstr(pDA[i].DataType,"FLOAT"))
			{
				strTemp.Format("  状态值:%.6f <*>",pDA[i].DAValue.Value.f);
			}
			else if (strstr(pDA[i].DataType,"OCT_STR"))
			{
				strTemp.Format("  状态值:%s <*>",pDA[i].DAValue.Value.string);
			}
			else if (strstr(pDA[i].DataType,"V_STR"))
			{
				strTemp.Format("  状态值:%s <*>",pDA[i].DAValue.Value.string);
			}
			else if (strstr(pDA[i].DataType,"BOOL[]"))
			{
				strTemp.Format("  状态值:%d <*>;",pDA[i].DAValue.Value.u);
			}
			else if (strstr(pDA[i].DataType,"UTC_TIME"))
			{
				tagEVENTTIME lpTimeBCD;
				Convert_UTC_To_BCD(&lpTimeBCD, pDA[i].DAValue.Value.utctime);
				strTemp.Format("时间：%d-%d-%d-%d-%d-%d-%d\n\t",lpTimeBCD.year,lpTimeBCD.month,lpTimeBCD.day,
					lpTimeBCD.hour,lpTimeBCD.minute,lpTimeBCD.second,lpTimeBCD.ms);
			}

			strText += strTemp;
		}
	}

	*strRpt = strText;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/* 2012-09-27  获取命名变量描述名 */ 
//lijq 2015-1-18
#define VAR_DESC_NAME_KIND_FULL           0
#define VAR_DESC_NAME_KIND_REMOVE_VALID     1

ST_VOID CMmsApi::get_varDesrName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind, ST_INT nLevel)
{
	ST_CHAR *p;

	strcpy(pDst,pSrc);

	switch (nAinKind )
	{
	case VAR_DESC_NAME_KIND_FULL:
		break;

	case VAR_DESC_NAME_KIND_REMOVE_VALID:
		p = FindVarID(pDst);

		if (p != NULL)
		{
			*p = 0;
		}

		break;

	default:
		break;
	}
	
	strcat(pDst,"$dU");
	p = pDst;

	while (*p != 0)
	{
		if (*p == '$')
		{
			if (*(p+3) == '$')
			{
				*(p+1) = 'D';
				*(p+2) = 'C';
				break;
			}
		}

		p++;
	}
}
ST_VOID CMmsApi::get_varUnitName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind, ST_INT nLevel)
{
	ST_CHAR *p;

	strcpy(pDst,pSrc);

	switch (nAinKind )
	{
	case VAR_DESC_NAME_KIND_FULL:
		break;

	case VAR_DESC_NAME_KIND_REMOVE_VALID:
		p = FindVarID(pDst);

		if (p != NULL)
		{
			*p = 0;
		}

		break;

	default:
		break;
	}

	strcat(pDst,"$units");
	p = pDst;

	while (*p != 0)
	{
		if (*p == '$')
		{
			if (*(p+3) == '$')
			{
				*(p+1) = 'C';
				*(p+2) = 'F';
				break;
			}
		}

		p++;
	}
}


ST_VOID CMmsApi::get_varLimitName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind, ST_INT nLevel, int nKind, int nHas_F)
{
	ST_CHAR *p;

	strcpy(pDst,pSrc);

	switch (nAinKind )
	{
	case VAR_DESC_NAME_KIND_FULL:
		break;

	case VAR_DESC_NAME_KIND_REMOVE_VALID:
		p = FindVarID(pDst);

		if (p != NULL)
		{
			*p = 0;
		}

		break;

	default:
		break;
	}

	if (m_bIsAinMinMax)
	{
		if (nHas_F == 1)
		{
			strcat(pDst, nKind==0 ? "$rangeC$min$f" : "$rangeC$max$f");
		}
		else
		{
			strcat(pDst, nKind==0 ? "$rangeC$min" : "$rangeC$max");
		}
	}
	else
	{
		if (nHas_F == 1)
		{
			strcat(pDst, nKind==0 ? "$minVal$f" : "$maxVal$f");
		}
		else
		{
			strcat(pDst, nKind==0 ? "$minVal" : "$maxVal");
		}
	}
	

	p = pDst;

	while (*p != 0)
	{
		if (*p == '$')
		{
			if (*(p+3) == '$')
			{
				*(p+1) = 'C';
				*(p+2) = 'F';
				break;
			}
		}

		p++;
	}
}

ST_VOID CMmsApi::get_varStepSizeName(ST_CHAR*pSrc, ST_CHAR*pDst, int nHas_F)
{
	ST_CHAR *p;

	strcpy(pDst,pSrc);
// 	switch (nAinKind )
// 	{
// 	case VAR_DESC_NAME_KIND_FULL:
// 		break;
// 
// 	case VAR_DESC_NAME_KIND_REMOVE_VALID:
// 		p = FindVarID(pDst);
// 
// 		if (p != NULL)
// 		{
// 			*p = 0;
// 		}
// 
// 		break;
// 
// 	default:
// 		break;
// 	}

	p = FindVarID(pDst);

	if (p != NULL)
	{
		*p = 0;
	}


	if (nHas_F == 1)
	{
		strcat(pDst, "$stepSize$f");
	}
	else
	{
		strcat(pDst, "$stepSize");
	}

	p = pDst;

	while (*p != 0)
	{
		if (*p == '$')
		{
			if (*(p+3) == '$')
			{
				*(p+1) = 'C';
				*(p+2) = 'F';
				break;
			}
		}

		p++;
	}
}
// 
// ST_VOID CMmsApi::get_varDesrName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind, ST_INT nLevel)
// {
// 	ST_INT i;
// 	ST_CHAR *p;
// 
// 	strcpy(pDst,pSrc);
// 
// 	// 第三类情况(1)
// 	if (nAinKind==0)
// 	{
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 	}
// 
// 	// 第三类情况(2)
// 	if (nAinKind==1)
// 	{
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 	}
// 
// 	if (nAinKind==-1)
// 	{
// 		if (strstr(pSrc,"$setMag$f"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$mag$f"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$mag$i"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$setVal"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$general"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 
// 		for (int i=0; i<nLevel; i++)
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 	}
// 
// 	if (nAinKind==2)
// 	{
// 		p = strrchr(pDst,'$');
// 		if (p) *p = 0;
// 	}
// 
// 	strcat(pDst,"$dU");
// 
// 	for (i=0; i<nSize; i++)
// 	{
// 		if (pDst[i]=='$')
// 		{
// 			if (i+1<nSize)
// 				pDst[i+1] = 'D';
// 			if (i+2<nSize)
// 				pDst[i+2] = 'C';
// 			break;
// 		}
// 	}
// }

/* 2012-09-27  获取命名变量单位名 */ 
// ST_VOID CMmsApi::get_varUnitName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind, ST_INT nLevel)
// {
// 	ST_INT i;
// 	ST_CHAR *p;
// 
// 	strcpy(pDst,pSrc);
// 
// 	// 第三类情况(1)
// 	if (nAinKind==0)
// 	{
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 	}
// 
// 	// 第三类情况(2)
// 	if (nAinKind==1)
// 	{
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 	}
// 
// 	if (nAinKind==-1)
// 	{
// 		if (strstr(pSrc,"$setMag$f"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$mag$f"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$setVal"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$general"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 
// 		for (int i=0; i<nLevel; i++)
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 	}
// 
// 	strcat(pDst,"$units");
// 
// 	for (i=0; i<nSize; i++)
// 	{
// 		if (pDst[i] == '$')
// 		{
// 			if (i+1<nSize)
// 				pDst[i+1] = 'C';
// 			if (i+2<nSize)
// 				pDst[i+2] = 'F';
// 			break;
// 		}
// 	}
// }
// 
// ST_VOID CMmsApi::get_varLimitName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind, ST_INT nLevel, int nKind, int nHas_F)
// {
// 	ST_INT i;
// 	ST_CHAR *p;
// 
// 	strcpy(pDst,pSrc);
// 
// 	// 第三类情况(1)
// 	if (nAinKind==0)
// 	{
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 	}
// 
// 	// 第三类情况(2)
// 	if (nAinKind==1)
// 	{
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 
// 		p = strrchr(pDst,'$');
// 		if (p != NULL)*p = 0;
// 	}
// 
// 	if (nAinKind==-1)
// 	{
// 		if (strstr(pSrc,"$setMag$f"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$mag$f"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$setVal"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p != NULL)*p = 0;
// 		}
// 
// 		if (strstr(pSrc,"$general"))
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 
// 		for (int i=0; i<nLevel; i++)
// 		{
// 			p = strrchr(pDst,'$');
// 			if (p) *p = 0;
// 		}
// 	}
// 
// 	if (nHas_F == 1)
// 	{
// 		strcat(pDst, nKind==0 ? "$minVal$f" : "$maxVal$f");
// 	}
// 	else
// 	{
// 		strcat(pDst, nKind==0 ? "$minVal" : "$maxVal");
// 	}
// 
// 	for (i=0; i<nSize; i++)
// 	{
// 		if (pDst[i] == '$')
// 		{
// 			if (i+1<nSize)
// 				pDst[i+1] = 'C';
// 			if (i+2<nSize)
// 				pDst[i+2] = 'F';
// 			break;
// 		}
// 	}
// }


/* 2012-10-23  获取装置的某个逻辑设备 */
LD_NODE* CMmsApi::get_DevLDPtr(CFuncParamEx *pFuncParaEx)
{
	ST_INT i;
	ST_INT j;

	i = pFuncParaEx->get_DevIndex();
	j = pFuncParaEx->get_LDvIndex();
	
	if ((i>=0&&i<MAX_DEVICE)&&(j>=0&&j<MAX_LD_VMD))
	{
		ACSI_NODE *pDvNode = &pACSINode[i];
		if (pDvNode)
			return &pDvNode->LD[j];
	}
	
	return NULL;
}

ACSI_NODE* CMmsApi::get_DevACSI_NODEPtr(CFuncParamEx *pFuncParaEx)
{
	return &pACSINode[pFuncParaEx->get_DevIndex()];
}

/* 2012-11-20  网络监控线程 */
ST_RET CMmsApi::CreateDataProcThread()
{
	if (m_hThread_Proc==NULL)
	{

#ifdef _PSX_QT_LINUX_
            int nRet = pthread_create(&m_hThread_Proc, 0, MMSCallBackProc, (void*)this);

            if (nRet != 0)
            {
                return SD_FAILURE;
            }
#else
                m_hThread_Proc = CreateThread(NULL,1024, MMSCallBackProc,this,0,NULL);

                if (m_hThread_Proc==NULL)
                {
                    return SD_FAILURE;
                }
                else
                {
                    SetThreadPriority(m_hThread_Proc, THREAD_PRIORITY_HIGHEST);
                }
#endif
	}

#ifdef SERVER_USE_TWO_THREAD

// 	if (m_hThread_Proc_Data==NULL)
// 	{
// 		m_hThread_Proc_Data = CreateThread(NULL,1024, MMSCallBackProc_Data,this,0,NULL);	
// 		if (m_hThread_Proc_Data==NULL)
// 			return SD_FAILURE;
// 	}
#endif

	return SD_SUCCESS;
}

//装置链接创建的时候调用此线程
ST_RET CMmsApi::CreateDataProcThread(CFuncParamEx *pFuncParaEx)
{
	if (pFuncParaEx->m_hThread_Proc_Data==NULL)
	{
#ifdef _PSX_QT_LINUX_
        pthread_create(&pFuncParaEx->m_hThread_Proc_Data, 0, MMSCallBackProc_Data, (void*)pFuncParaEx);
#else
        HANDLE h = CreateThread(NULL,1024, MMSCallBackProc_Data, pFuncParaEx, 0,NULL);
        pFuncParaEx->m_hThread_Proc_Data = h;
#endif

		if (pFuncParaEx->m_hThread_Proc_Data==NULL)
			return SD_FAILURE;
	}

	return SD_SUCCESS;
}

/* 2012-11-20  销毁网络监控线程 */
ST_RET CMmsApi::DestroyDataProcThread()
{
	m_bExitServeACSIServer = TRUE;

	// 停止监控线程
	if (m_hThread_Proc)
	{
// 		DWORD  ExitCode = 0;
// 		if (GetExitCodeThread(m_hThread_Proc,&ExitCode))
// 		{
// 			// 强制结束,失败
// 			if (!TerminateThread(m_hThread_Proc,ExitCode))
// 				return SD_FAILURE;
// 
// 			if (CloseHandle(m_hThread_Proc))
// 				m_hThread_Proc = NULL;
// 		}
#ifdef _PSX_QT_LINUX_
        //_endthread(m_hThread_Proc);
#else
        CloseHandle(m_hThread_Proc);
#endif

		m_hThread_Proc = NULL;
	}

#ifdef SERVER_USE_TWO_THREAD
// 	if (m_hThread_Proc_Data)
// 	{
// 		CloseHandle(m_hThread_Proc_Data);
// 		m_hThread_Proc_Data = NULL;
// 	}

	for (int nIndex = 0;nIndex<MAX_DEVICE;nIndex++)
	{
		if (m_oFuncParamEx[nIndex].m_hThread_Proc_Data)
		{
#ifndef _PSX_QT_LINUX_
			CloseHandle(m_oFuncParamEx[nIndex].m_hThread_Proc_Data);
#endif
			m_oFuncParamEx[nIndex].m_hThread_Proc_Data = NULL;
		}
	}
#endif

	return SD_SUCCESS;
}

/* 2012-11-01  创建接收线程 */
// ST_RET CMmsApi::CreateMMSRecvThread()
// {
// 	/* 2012-11-09  */
// 	if (m_hThread_Notify==NULL)
// 	{
// 		m_hThread_Notify = CreateThread(NULL,1024, MMSRptRecvNotify,this,0,NULL);	
// 		if (m_hThread_Notify==NULL)
// 			return SD_FAILURE;
// 	}
// 
// 	return SD_SUCCESS;
// }

/* 2012-11-01  销毁接收线程 */
// ST_RET CMmsApi::DestroyMMSRecvThread()
// {
// 	if (m_hThread_Notify)
// 	{
// 		DWORD  ExitCode = 0;
// 		if (GetExitCodeThread(m_hThread_Notify, &ExitCode))
// 		{
// 			//强制结束,失败
// 			if (!TerminateThread(m_hThread_Notify, ExitCode))
// 				return SD_FAILURE;
// 
// 			if (CloseHandle(m_hThread_Notify))
// 				m_hThread_Notify = NULL;
// 		}
// 	}
// 
// 	/* 2012-11-09  */
// 	if (hRptNotifyEvent)
// 	{
// 		CloseHandle(hRptNotifyEvent);
// 		hRptNotifyEvent = NULL; 
// 	}
// 
// 	return SD_SUCCESS;
// }

/* 2012-11-09  报告通知 */
// ST_VOID CMmsApi::RecvRptNotify()
// {
// 	hRptNotifyEvent = OpenEvent(EVENT_ALL_ACCESS,FALSE,"MMS-RPT-NOTIFY");
// 
// 	while (TRUE)
// 	{
// 		if (hRptNotifyEvent != NULL)
// 		{
// 			WaitForSingleObject(hRptNotifyEvent,INFINITE);
// 			mmsi_RecvRptData();
// 		}
// 		else
// 		{   // 如果没有其他进程创建这个事件，则重新创建，该事件为自动重置事件
// 			hRptNotifyEvent = CreateEvent(NULL,FALSE,FALSE,"MMS-RPT-NOTIFY");
// 		}
// 	}
// 
// 	// 关闭句柄
// 	CloseHandle(hRptNotifyEvent);
// }

#define  _MmsAcsiServerThread_use_Sleep

ST_VOID CMmsApi::MmsAcsiServerThread()
{
	ThreadCountAddRef();
	ST_INT  nServeACSI0 = 0;
	ST_INT  nServeACSI1 = 0;
	ST_INT  bServeACSI0 = 0;
	ST_INT  bServeACSI1 = 0;
	long nDeviceIndex = 0;

    S_LOCK_COMMON_RESOURCES ();
	S_LOCK_COMMON_RESOURCES ();
    S_UNLOCK_COMMON_RESOURCES ();
    S_UNLOCK_COMMON_RESOURCES ();



	while (TRUE)
	{ 
		if (m_bExitServeACSIServer)
		{
			break;
		}

        if (m_nDeviceCount == 0)
        {
            Sleep(10);
            continue;
        }
// 		nServeACSI0 = 0;
// 		nServeACSI1 = 0;

// #ifdef _use_pip_use_counter
// 		//mmsi_ResetSocketInfoTable();
// #endif

#ifdef _MmsAcsiServerThread_use_Sleep
		//nSelPipe = 0;
		nServeACSI0 = mvl_comm_serve (0);

		if (nServeACSI0 == 0)
		{
			Sleep(1);
		}

#ifndef _not_use_PIPE_MSG
		//nSelPipe = 1;
		mvl_comm_serve (1);
#endif

// 		//nSelPipe = 1;
// 		if(bServeACSI0 == 0 && bServeACSI1 == 0)
// 		{
// 			Sleep(1);
// 		}
#else
		while(mvl_comm_serve (0))
		{
			if(nServeACSI0++>MAX_PIPE0_RPT)
				break;
		}

		//nSelPipe = 1;
		while(mvl_comm_serve (1))
		{
			if(nServeACSI1++>MAX_PIPE1_RPT)
				break;
		}
#endif

#ifdef SERVER_USE_TWO_THREAD
#else
		MMS_DataOpeProc();

		Mms_TestNetsProc();

		if (g_bMmsEngineDebugMode)
		{
			if (m_bTestMms_handle_data)
			{
				Test_handle_data();
			}
		}
#endif
		//201611-14
		//SleepEx(20, TRUE); 
		//SleepEx(1, TRUE);
		//Sleep(1);
	}

	ThreadCountRelease();
}

ST_VOID CMmsApi::MmsAcsiServerThread_DataProc(CFuncParamEx *pFuncParaEx)
{
	ThreadCountAddRef();
	ST_INT  nServeACSI0 = 0;
	ST_INT  nServeACSI1 = 0;

	while (TRUE)
	{ 
		if (m_bExitServeACSIServer)
		{
			break;
		}

		MMS_DataOpeProc(pFuncParaEx);

// 		Mms_TestNetsProc();
// 
// 		if (g_bMmsEngineDebugMode)
// 		{
// 			if (m_bTestMms_handle_data)
// 			{
// 				Test_handle_data();
// 			}
// 		}
		pFuncParaEx->ClearExitFunc();

		Sleep(100);
	}

	ThreadCountRelease();
}

void CMmsApi::Test_handle_data()
{
// 	ST_CHAR spdu_ptr[9192];
// 	m_bTestMms_handle_data = FALSE;
// 	SOCK_INFO sock_info;
// 	TP0_CONN tp0_conn;
// 	ACSE_CONN acse_conn;
// 	ZeroMemory(&acse_conn, sizeof(ACSE_CONN));
// 	ZeroMemory(&tp0_conn, sizeof(TP0_CONN));
// 	ZeroMemory(&sock_info, sizeof(SOCK_INFO));
// 	tp0_conn.spdu_rx.spdu_ptr = spdu_ptr;
// 	tp0_conn.spdu_rx.spdu_len = 0;
// 	tp0_conn.sock_info = &sock_info;
// 	tp0_conn.user_conn_id = (DWORD)(&acse_conn);
// 	tp0_conn.state = TP_STATE_OPEN;
// 
// 	acse_conn.cosp_state = 713;
// 	acse_conn.copp_state = 3;//COPP_STATE_CONNECTED;
// 	acse_conn.user_conn_id = ;
// 
// 	sock_info.user_conn_id = (DWORD)(&tp0_conn);
	m_bTestMms_handle_data = FALSE;
	SOCK_INFO *sock_info = &sock_info_table[0];
	handle_data (sock_info, m_buf_handle_data, m_len_buf_handle_data);
}

void CMmsApi::Test_handle_data(BYTE *pBuffer, long nLen)
{
	memcpy(m_buf_handle_data, pBuffer, nLen);
	m_len_buf_handle_data = nLen;
	m_bTestMms_handle_data = TRUE;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* 2012-10-17  启动读装置报告 */
ST_RET CMmsApi::set_StartReadRpt(CFuncParamEx *pFuncParaEx,ST_BOOLEAN bGI,ST_BOOLEAN bUpdateEntryID)
{
	ST_INT ret;
	ST_BOOLEAN RptGI = 1;
	ST_CHAR rcbItem[NAMESIZE];
	ST_CHAR rcbGI[NAMESIZE];
	ST_INT nDsIndex, nRCB_Index, nStartCount;
	//
	BOOL OptFlds_Flag[9] = {1,1,1,1,1,0,1,0,0};
	*rcbItem = 0;
	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());

	if (!pFuncParaEx->Chck_DevIndex())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_StartRptFail);//_T("启动报告失败，请确认装置规约是否正确"));
		return SD_FAILURE;
	}

	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	if (!netInfo)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_StartRptFail);//_T("启动报告失败，请确认装置规约是否正确"));
		return SD_FAILURE;
	}

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_StartRptFail);//_T("启动报告失败，请确认装置规约是否正确"));
		return SD_FAILURE;
	}

	nDsIndex = pFuncParaEx->get_DSID();
	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_StartRptFail);//_T("启动报告失败，请确认装置规约是否正确"));
		return SD_FAILURE;
	}

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	if (pLD_INFO->numRcb <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_HasNoRptCtrl);//_T("启动报告：不存在报告控制块"));
		return SD_SUCCESS;
	}
	
	if (0 < pLD_INFO->curRcbIndex && pLD_INFO->curRcbIndex <= pLD_INFO->numRcb)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE 
            , g_sLangTxt_RptCtrlHasStart.GetString()/*_T("启动报告：报告控制块【%s】已经启动")*/
            , pLD_INFO->RCB[pLD_INFO->curRcbIndex-1].rcbName);
		return SD_SUCCESS;
	}

	pLD_INFO->curRcbIndex = 0;

	ST_BOOLEAN bStartRpt = SD_FALSE;
	//for (int i=0; i<pLD_INFO->numRcb; i++)
	int nBrcbIndex = pFuncParaEx->get_BrcbIndex();

	if ((nBrcbIndex<0)||(nBrcbIndex>=pLD_INFO->numRcb))
	{
		nBrcbIndex = pFuncParaEx->m_nConnDevIndex /*-1*/;
		if ((nBrcbIndex<0)||(nBrcbIndex>=pLD_INFO->numRcb))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("报告控制块号【%d】越限."),nBrcbIndex);//
			return SD_FAILURE;
		}
	}

	ST_BOOLEAN RptEna=SD_FALSE;

	for (int i=nBrcbIndex; i<pLD_INFO->numRcb; i++)
	{
		strcpy(rcbItem,pLD_INFO->RCB[i].rcbName);
		strcpy(rcbGI,rcbItem);
		strcat(rcbGI,"$GI");

		if (get_RptEnableState(netInfo, pLD->LDName, rcbItem, &RptEna)==SD_SUCCESS)//判断该报告号是否已经被启动过
		{
			if (!RptEna)
			{
				nRCB_Index = i;
				bStartRpt = SD_TRUE;
				break;
			}
		}

		Sleep(100);

		if (g_bMultDevModel)
		{
			break;
		}
	}

	// 启动报告
	if (bStartRpt==SD_TRUE)
	{
		ST_UCHAR OptFlds [2];	/* 10 bit bitstring but only allow write of 9 bits */
		ST_UCHAR TrgOps [1];	/* 8 bit bitstring */
		ST_BOOLEAN isBR = SD_TRUE;
		/* 缓存报告采用默认值“0x79” */
		/* Enable options we want to see in IEC-61850 report. */
		OptFlds [0] = 0;
		OptFlds [1] = 0;

		/* NOTE: these options ONLY available for IEC-61850 (not UCA)
		* SUBSEQNUM is only set by the server, so don't try to set it.
		* BUFOVFL valid for BRCB but meaningless for URCB, so don't set
		* BUFOVFL for URCB.
		*/	

		if (strstr(rcbItem,"BR"))
			memcpy(OptFlds_Flag, OptFlds_BP, sizeof(BOOL)*9);
		else if (strstr(rcbItem,"RP"))
			memcpy(OptFlds_Flag, OptFlds_RP, sizeof(BOOL)*9);

		for (int i=0; i<9; i++)
		{
			if (OptFlds_Flag[i])
				BSTR_BIT_SET_ON(OptFlds, i+1);
			else
				BSTR_BIT_SET_OFF(OptFlds, i+1);
		}

		TrgOps [0] = 0;	/* enable ALL triggers	*/
		for (int i=0; i<5; i++)
		{
			if (TrgOps_UI[i])
				BSTR_BIT_SET_ON(TrgOps, i+1);
			else
				BSTR_BIT_SET_OFF(TrgOps, i+1);
		}

		nStartCount = 0;

		while (TRUE)
		{
#ifdef _MVL_TYPE_CTRL_use_one_device_
			ret = set_RCBEnable(netInfo, pLD->LDName, rcbItem, OptFlds, TrgOps,bUpdateEntryID, pDevice->p_mvl_type_ctrl);
#else
			ret = set_RCBEnable(netInfo, pLD->LDName, rcbItem, OptFlds, TrgOps,bUpdateEntryID);
#endif

			if (bGI&&ret==SD_SUCCESS)
			{
				Sleep(100);
				ret = set_varvalue(netInfo, rcbGI, pLD->LDName, BOOLEAN_TYPEID, &RptGI);
			}

			if (ret == SD_SUCCESS)
			{
				pLD_INFO->curRcbIndex = nRCB_Index + 1;
				break;
			}

			if (nStartCount == 5)
			{
				break;
			}

			nStartCount++;
			Sleep(100);
		}
	}

	CString str_rcbItem;
	str_rcbItem = (char*)rcbItem;

	if (bStartRpt)
	{
		if (ret == SD_SUCCESS)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , g_sLangTxt_StartRptCtrlFinish.GetString()/*"启动报告[%s]完成"*/
                , str_rcbItem.GetString());
			mms_UpdateDatasetState(pLD_INFO);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , g_sLangTxt_StartRptCtrlFail.GetString()/*"启动报告[%s]失败"*/
                , str_rcbItem.GetString());
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE
            , g_sLangTxt_StartRptCtrlFail.GetString()/*"启动报告[%s]失败"*/
            , str_rcbItem.GetString());
	}

	return ret;
}

/* 2012-11-21   */
ST_VOID CMmsApi::get_MMStagDAObj(ST_INT nDsIndex, ST_INT index, LD_DATASET_INFO*pLD_INFO, tagDA **pDA)
{
	ASSERT(pLD_INFO!=NULL);

	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return;

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("----0x%08X"), (DWORD)&pLD_INFO->DataSet[index]);
	*pDA = &pLD_INFO->DataSet[index];
}

/* 2012-11-22  获取网络信息 */
MVL_NET_INFO *CMmsApi::get_NetInfo(CFuncParamEx *pFuncParaEx)
{
	if (!pFuncParaEx->Chck_DevIndex())
		return NULL;

	ST_INT nDvID = pFuncParaEx->get_DevIndex();
	MVL_NET_INFO *netInfo = (MVL_NET_INFO*)(acsi_ctrl_table[nDvID].pnet_info);
	if (netInfo==NULL)
	{
		//m_strMMSApiError ="网络连接未创建.";
	}

	return netInfo;
}

BOOL CMmsApi::HasUnit(char *pszDsId)
{
	if (strstr(pszDsId, dsParameter) != NULL)
	{
		return TRUE;
	}

	if (strstr(pszDsId, dsAin) != NULL)
	{
		return TRUE;
	}

	if (strstr(pszDsId, dsSetting) != NULL)
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CMmsApi::HasMinMax(char *pszDsId)
{
	m_bIsAinMinMax = FALSE;

	if (strstr(pszDsId, dsParameter) != NULL)
	{
		return TRUE;
	}

	if (strstr(pszDsId, dsSetting) != NULL)
	{
		return TRUE;
	}

	if (strstr(pszDsId, dsSetGrpNum) != NULL)
	{
		return TRUE;
	}

	if (strstr(pszDsId, dsRelayAin) != NULL)
	{
		m_bIsAinMinMax = TRUE;
		return TRUE;
	}

	if (strstr(pszDsId, dsAin) != NULL)
	{
		m_bIsAinMinMax = TRUE;
		return TRUE;
	}

	return FALSE;
}

BOOL CMmsApi::HasStepSize(char *pszDsId)
{
	if (strstr(pszDsId, dsParameter) != NULL)
	{
		return TRUE;
	}

	if (strstr(pszDsId, dsSetting) != NULL)
	{
		return TRUE;
	}

	if (strstr(pszDsId, dsSetGrpNum) != NULL)
	{
		return TRUE;
	}

	return FALSE;
}

/* 2012-11-12  释放分配的数据集 */ 
ST_VOID CMmsApi::ReleaseTagDAAry(tagDA*pDA, ST_INT *nSize)
{
	ST_INT i = 0;

	if (pDA == NULL)
		return;

	for (; i<*nSize; i++)
		mms_ReleaseData(&pDA[i]);

	*nSize = 0;
}

/* 2012-11-12  初始化设备数据集 */
ST_VOID CMmsApi::Init_DevDataSet(LD_NODE *pLD, ST_INT nDsIndex)
{
	ASSERT(pLD!=NULL);

	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];

	ReleaseTagDAAry(pLD_INFO->DataSet, &pLD_INFO->numData);
	ST_INT nSize = MAX_DA_NUM*sizeof(tagDA);
	memset(pLD_INFO->DataSet, 0, nSize);
}

/* 2012-10-24  读取报告的使能状态 */
ST_RET CMmsApi::get_RptEnableState(MVL_NET_INFO *netInfo, ST_CHAR *domName, ST_CHAR *rcbItem, ST_BOOLEAN *RptEna)
{
	ST_RET ret = SD_SUCCESS;
	ST_CHAR dstVar[NAMESIZE];

	ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
	sprintf(dstVar, "%s$RptEna", rcbItem);

	ret = get_varvalue(netInfo, dstVar, domName, BOOLEAN_TYPEID, RptEna, 1);
	
	return ret;
}

/* 2012-10-23  使能报告控制块 */
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::set_RCBEnable(MVL_NET_INFO *netInfo, ST_CHAR *domName,
							  ST_CHAR *rcbItem, ST_UCHAR *OptFlds, ST_UCHAR *TrgOps,ST_BOOLEAN bUpdateEntryID, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::set_RCBEnable(MVL_NET_INFO *netInfo, ST_CHAR *domName,
							  ST_CHAR *rcbItem, ST_UCHAR *OptFlds, ST_UCHAR *TrgOps,ST_BOOLEAN bUpdateEntryID)
#endif
{	
	ST_RET ret;
	ST_CHAR dstVar[NAMESIZE];
	ST_INT Type_id=0, ret2;
	ST_UINT8 vEntryID [10] = {0};
	ST_UINT32 IntgPd = 0;
	char *pChBrcb = strstr(rcbItem,_T("$brcb"));//判断是否为缓存报告控制块
	//EntryID

	if ((bUpdateEntryID)&&(pChBrcb != NULL))//zhouhj 20181015
	{
		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
		sprintf(dstVar, "%s$EntryID", rcbItem);

#ifdef _MVL_TYPE_CTRL_use_one_device_
		if (get_varType(netInfo, domName, &Type_id, dstVar, mvl_type_ctrl) == SD_SUCCESS)
#else
		if (get_varType(netInfo, domName, &Type_id, dstVar) == SD_SUCCESS)
#endif
		{
			ret2 = get_varvalue(netInfo, dstVar, domName, Type_id, vEntryID, 1);

			if (ret2 != SD_SUCCESS)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "write [%s][%s] failed", domName, dstVar);
			}
			else
			{
				ret = set_varvalue(netInfo, dstVar, domName, Type_id, vEntryID);
			}
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Read [%s][%s] type failed", domName, dstVar);
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif
	}

	if (TrgOps_UI[3] > 0)
	{
		//IntgPd
		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
		//sprintf(dstVar, "%s$OptFlds", rcbItem);
		sprintf(dstVar, "%s$IntgPd", rcbItem);
		//ret = set_varvalue(netInfo, dstVar, domName, RTYP_BSTR9_TYPEID, OptFlds);

		if (g_nIntgPd<0)
		{
			IntgPd -= g_nIntgPd;
			ret = set_varvalue(netInfo, dstVar, domName, INT16_TYPEID, &IntgPd);//zhouhj 为了兼容之前版本，当自动测试传进来的值为负数是，依旧使用整型的方式
		} 
		else
		{
			IntgPd = g_nIntgPd;
			ret = set_varvalue(netInfo, dstVar, domName, INT32U_TYPEID/*INT16U_TYPEID*//*INT16_TYPEID*/, &IntgPd);//zhouhj 将原来的整型改为无符号整型
		}

		if (ret!=SD_SUCCESS)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "write [%s][%s] failed", domName, dstVar);
		}
	}

	//OptFlds
	ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
	//sprintf(dstVar, "%s$OptFlds", rcbItem);
	sprintf(dstVar, "%s$%s", rcbItem, g_strOptFlds);
	//ret = set_varvalue(netInfo, dstVar, domName, RTYP_BSTR9_TYPEID, OptFlds);
	ret = set_varvalue(netInfo, dstVar, domName, BSTR10_TYPEID, OptFlds);

	if (ret!=SD_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "write [%s][%s] failed", domName, dstVar);
	}

	//TrgOps
	ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
	//sprintf(dstVar, "%s$TrgOps", rcbItem);
	sprintf(dstVar, "%s$%s", rcbItem, g_strTrgOps);
	if (ret==SD_SUCCESS)
	{
		ret = set_varvalue(netInfo, dstVar, domName, RTYP_BSTR6_TYPEID, TrgOps);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "write [%s][%s] failed", domName, dstVar);
	}	
 
	//RptEna
	ST_BOOLEAN RptEna = 1;
	ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
	sprintf(dstVar, "%s$RptEna", rcbItem);
	ret = set_varvalue(netInfo, dstVar, domName, BOOLEAN_TYPEID, &RptEna);

	if (ret!=SD_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "write [%s][%s] failed", domName, dstVar);
	}

	return ret;
}

/* 2012-10-23  停止使能报告控制块 */
ST_RET CMmsApi::set_RCBDisable(MVL_NET_INFO *netInfo, ST_CHAR *domName, ST_CHAR *rcbItem)
{
	ST_RET ret = SD_SUCCESS;
	ST_BOOLEAN RptEna = 0;
	ST_CHAR dstVar[NAMESIZE];

	ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
	sprintf(dstVar, "%s$RptEna", rcbItem);
	ret = set_varvalue(netInfo, dstVar, domName, BOOLEAN_TYPEID, &RptEna);

	return ret;
}

/* 2012-10-17  停止读报告数据 */
ST_RET CMmsApi::set_StopReadRpt(CFuncParamEx *pFuncParaEx,ST_INT nDsIndex)
{
	ST_INT ret;
	ST_CHAR rcbItem[NAMESIZE];

	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	if (!netInfo)
		return SD_FAILURE;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return SD_FAILURE;

	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
		return SD_FAILURE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	if (pLD_INFO->numRcb < 0)
		return SD_SUCCESS;

	ST_BOOLEAN bStartRpt = SD_FALSE;

	if (pLD_INFO->curRcbIndex <= pLD_INFO->numRcb && pLD_INFO->curRcbIndex > 0)
	{
		strcpy(rcbItem,pLD_INFO->RCB[pLD_INFO->curRcbIndex-1].rcbName);
	}
	else
	{
		pLD_INFO->curRcbIndex = 0;
		return SD_SUCCESS;
	}

	int nStartCount = 0;

	while (TRUE)
	{
		// 设置报告相关信息	
		ret = set_RCBDisable(netInfo, pLD->LDName, rcbItem);

		if(ret == SD_SUCCESS)
		{
			pLD_INFO->curRcbIndex = 0;
			break;
		}

		if (nStartCount == 10)
		{
			break;
		}

		nStartCount++;
		Sleep(100);
	}

	mms_UpdateDatasetState(pLD_INFO);

	return ret;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/* 外部使用接口 */
void CMmsApi::SaveMmsEngineConfig()
{
	m_oMmsEngineConfig.m_nDebugMode = g_bMmsEngineDebugMode;
	m_oMmsEngineConfig.m_nExitAppForException = g_nExitAppForException;
	m_oMmsEngineConfig.m_nEnumLDAfterReadXml = g_bMmsEnumLDAfterReadXml;
	m_oMmsEngineConfig.m_nMmsEnumLogCtrl = m_bEnumLN;
	m_oMmsEngineConfig.m_nUseDvmMapFile = g_bUseDvmMapFile;
	m_oMmsEngineConfig.m_bMultDevModel = g_bMultDevModel;
	m_oMmsEngineConfig.m_nExportModelAuto = g_bExportModelAuto;
	m_oMmsEngineConfig.m_nUseDsDout = g_bUseDsDout;
	m_oMmsEngineConfig.m_nAutoGenModelDatas = g_bAutoGenModelDatas;
	m_oMmsEngineConfig.SaveMmsEngineConfig();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CMmsApi::ReadMmsEngineConfig()
{
	CString strTemp;
	strTemp = mms_CONFIG_PATH();
	CGpsPcTimeTickCount oTick32;

	m_oMMS_STACK_CFG.OpenXmlFile(strTemp, CMMS_STACK_CFGXmlRWKeys::g_pXmlKeys);
	long nTmLong = oTick32.GetTickCountLong(FALSE);
	strTemp += _T("e");
	m_oMMS_STACK_CFG.SaveXmlFile(strTemp, CMMS_STACK_CFGXmlRWKeys::g_pXmlKeys);
	CMMS_STACK_CFGXmlRWKeys::Release();
	nTmLong = oTick32.GetTickCountLong(TRUE);

	m_oMmsEngineConfig.ReadMmsEngineConfig();

	nTmLong = oTick32.GetTickCountLong(TRUE);
	g_bMmsEngineDebugMode = m_oMmsEngineConfig.m_nDebugMode;
	g_bMmsEnumLDAfterReadXml = m_oMmsEngineConfig.m_nEnumLDAfterReadXml;
	m_bEnumLN = m_oMmsEngineConfig.m_nMmsEnumLogCtrl;
	g_nExitAppForException = m_oMmsEngineConfig.m_nExitAppForException;
	g_bUseDvmMapFile = m_oMmsEngineConfig.m_nUseDvmMapFile;
	g_bMultDevModel = m_oMmsEngineConfig.m_bMultDevModel;
	g_bExportModelAuto = m_oMmsEngineConfig.m_nExportModelAuto;
	g_bUseDsDout = m_oMmsEngineConfig.m_nUseDsDout;
	g_bAutoGenModelDatas = m_oMmsEngineConfig.m_nAutoGenModelDatas;
}

/* 2012-09-20  初始化 MMS 数据 */
ST_RET CMmsApi::mmsi_InitMMSData(ST_INT  nSelPipe, ST_BOOLEAN bInit)
{
	//g_strFuncIDame[FUNCID_MAX_COUNT];
	m_bExitServeACSIServer = FALSE;
	CString strTemp;
	strTemp = mms_CONFIG_PATH();

	CGpsPcTimeTickCount oTick32;
	long nTmLong = oTick32.GetTickCountLong(FALSE);

	ST_INT  nServeACSI0 = 0;
	ST_INT  nServeACSI1 = 0;
	ST_RET  ret;

    //mmsi_TRACE ("%s Version %s, Build #%d\n", MMSLITE_NAME, MMSLITE_VERSION, MMSLITE_BUILD_NUM);

#if defined(S_SEC_ENABLED)
    //mmsi_TRACE ("%s Version %s\n", S_SEC_LITESECURE_NAME, S_SEC_LITESECURE_VERSION_STR);
#endif

	if (!bInit_ACSI&&bInit)
	{
#ifdef S_MT_SUPPORT
		/* init glbsem explicitly to avoid auto-initialization calls from multiple threads */
		if ((ret = gs_init()) != SD_SUCCESS)
		{
            //mmsi_TRACE ("gs_init() failed");
			return SD_FAILURE;
		}
#endif
		/* init stime explicitly to avoid auto-initialization calls from multiple threads */
		if ((ret = stimeInit()) != SD_SUCCESS)
		{
            //mmsi_TRACE ("stimeInit() failed");
			return SD_FAILURE;
		}

		init_mem ();		/* Set up memory allocation tools 		*/
		init_mem_chk();

#if defined (DEBUG_SISCO)
		init_log_cfg();
#endif

		/* We want to know about connection activity				*/
		u_mvl_disc_ind_fun = disc_ind_fun;

		/* Read the configuration from a file */
		if (mvlCfg.bind_ctrl)
		{
			//chk_free(mvlCfg.bind_ctrl);
			ZeroMemory(&mvlCfg,sizeof(mvlCfg));
		}

		ret = osicfgx(OSICFG_PATH, &mvlCfg);	/* This fills in mvlCfg	*/

 		ret = mvl_start_acse(nSelPipe, &mvlCfg);	/* MAKE SURE mvlCfg is filled in */
  		
		if (ret != SD_SUCCESS)
  		{
            //mmsi_TRACE ("\n mvl_start_acse () failed, err = 0x%X. Check log file.\n", ret );
  			return SD_FAILURE;
  		}

 		InitDeviceNode();
		InitACSIServerNet();
		InitDeviceNode_mvl_type_ctrl();

		//PSW and KEY
		CStkCfg_RemoteAddressList *pRemoteAddressList = m_oMMS_STACK_CFG.GetRemoteAddressList();
		CStkCfg_RemoteAddress *pAddr = NULL;

		for (int i=0; i<MAX_DEVICE; i++)
		{
			pAddr = (CStkCfg_RemoteAddress*)pRemoteAddressList->GetAtIndex(i);

			if (pAddr == NULL)
			{
				break;
			}

			CString_to_char(pAddr->m_strPSW, pACSINode[i].psw);
			CString_to_char(pAddr->m_strKey, pACSINode[i].key);
		}

 		bInit_ACSI = SD_TRUE;
	}

	// 启动监控线程

	if (m_hThread_Proc == NULL)
	{
		CreateDataProcThread();
	}
	
	nTmLong = oTick32.GetTickCountLong(TRUE);

	

	return SD_SUCCESS;
}

/* 2012-09-20  释放 MMS 数据 */
ST_VOID CMmsApi::mmsi_DisConnectServer(ST_INT  nSelPipe)
{
	// 释放连接
	if (sock_info_table != NULL)
	{
		for (int i=0; i<numDevice; i++)
		{
			if (sock_info_table[i].net_error && sock_info_table[i].bSpawn)
				continue;

			if ((sock_info_table[i].nNet < 1) && sock_info_table[i].bSpawn)
				continue;

			if (NULL != acsi_ctrl_table[i].pnet_info)
			{
				//disconnectFromServer((MVL_NET_INFO *)acsi_ctrl_table[i].pnet_info);
				disconnectFromServerEx(i);
			}
		}
	}
}

#ifdef _use_pip_use_counter
ST_VOID CMmsApi::mmsi_ResetSocketInfoTable()
{
	if (sock_info_table == NULL)
	{
		return;
	}

	BOOL bCanReset = TRUE;
	SOCK_INFO *pSocketInfo = NULL;

	for (int i=0; i<numDevice; i++)
	{
		pSocketInfo = &sock_info_table[i];

		if (!pACSINode[i].bConnect)
		{
			pSocketInfo->pip_use_counter = 0;
			continue;;
		}

		if (pSocketInfo->pip_use_counter < PIP_USE_MAX_COUNT)
		{
			bCanReset = FALSE;
			break;
		}
	}

	if (!bCanReset)
	{
		return;
	}

	for (int i=0; i<numDevice; i++)
	{
		SOCK_INFO *pSocketInfo = &sock_info_table[i];

		if (pACSINode[i].bConnect)
		{
			pSocketInfo->pip_use_counter = 0;
			continue;;
		}
	}
}
#endif

ST_VOID CMmsApi::mmsi_ReleaseMMSData(ST_INT  nSelPipe)
{
	if (sock_info_table != NULL)
	{
		for (int i=0; i<numDevice; i++)
		{
			if (sock_info_table[i].net_error && sock_info_table[i].bSpawn)
				continue;

			if ((sock_info_table[i].nNet < 1) && sock_info_table[i].bSpawn)
				continue;

			if (NULL != acsi_ctrl_table[i].pnet_info)
			{
				ResetNetInfo(i);
			}
		}

		// 关闭会话
		if (bInit_ACSI)
		{
			dyn_mem_ptr_statistics(0);
			mvl_end_acse(nSelPipe);
			dyn_mem_ptr_status();	/* is everything freed up?	*/
		}
	}

	if (gs_already_inited)
	{
		gs_mutex_destroy (&gs_glb_mutex);

		gs_mutex_destroy (&gs_util_mutex);
		gs_mutex_destroy (&gs_sock_mutex);
		gs_mutex_destroy (&gs_ping_mutex);

		gs_mutex_destroy (&gs_soe_mutex);
		gs_mutex_destroy (&gs_rlysoe_mutex);

		gs_already_inited = SD_FALSE;
	}


// 	// 释放内存
// 	ReleaseMMSData();
//	ReleaseObjData();  zhouhj 20181009 单独释放
}

/* 2012-11-22  设置功能ID */
ST_RET CMmsApi::mmsi_FunctionCall(ST_INT nDeviceIndex, ST_INT nFuncID)
{	
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];
	pFuncParaEx->set_FuncID(nFuncID);

	ST_RET ret = SD_SUCCESS;
	if (!bInit_ACSI)
		ret = mmsi_InitMMSData(0, FALSE);

	return ret;
}

ST_RET CMmsApi::MMS_ReadDevice(CFuncParamEx *pFuncParaEx)
{
	ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
	ST_INT ret = SD_SUCCESS;
	ST_INT nDaNum = 0;
	ST_INT Type_id = 0;
	tagDA *pDA=NULL;

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("开始读取装置模型"));

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	long nLDIndex = 0;
	long nLdCount = pDevice->numLD;
	MVL_NET_INFO *netInfo = (MVL_NET_INFO*)(acsi_ctrl_table[nDeviceIndex].pnet_info);
	if (!netInfo)
		return SD_FAILURE;

	LD_DATASET_INFO *pLD_INFO = NULL;
	CString strTitle;
	BOOL bHasMinMax = FALSE;
	BOOL bNeedReadData = FALSE;

	for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
	{
		LD_NODE *pLD = &pACSINode[nDeviceIndex].LD[nLDIndex];

		for (int i=0;i<pLD->numDaSet;i++)
		{
			pLD_INFO = &pLD->DataInfo[i];
			bHasMinMax = HasMinMax(pLD_INFO->DataSetID);

			if ((strstr(pLD_INFO->DataSetID,_T("Setting"))!=NULL)
				||(strstr(pLD_INFO->DataSetID,_T("Ena"))!=NULL))//对于定值或压板数据集,去读取实际结果数据
			{
				bNeedReadData = TRUE;
			}
			else
			{
				bNeedReadData = FALSE;
			}

			nDaNum = pLD_INFO->numData;

			if ((pFuncParaEx != NULL)&&(!g_bMultDevModel))
			{
				strTitle.Format(_T("设备%d - 逻辑设备%d - %s - 第%d个数据集, 共%d个")
					,nDeviceIndex + 1, nLDIndex + 1, _T("读数据"),i+1,pLD->numDaSet);
				pFuncParaEx->SetTitle(strTitle);
				pFuncParaEx->SetMaxRange(nDaNum);
			}

			for (ST_INT k=0; k<nDaNum; k++)
			{
				Type_id = 0;

				if ((pFuncParaEx != NULL)&&(!g_bMultDevModel) && (pFuncParaEx->m_pProgressInterface != NULL) )
				{
					pFuncParaEx->StepIt();
					CString strMsg;
					strMsg.Format(g_sLangTxt_IndexAndTotal, k+1, nDaNum);//_T("第%d个  共%d个")
					pFuncParaEx->ShowMsg(strMsg);
				}

				get_MMStagDAObj(i, k, pLD_INFO, &pDA);

				if (pDA == NULL)
					continue;

				if (node_get_tagDAData(netInfo, pLD, pDA)!=SD_SUCCESS)
				{
					continue;
				}
				
#ifdef _MVL_TYPE_CTRL_use_one_device_
				node_get_DataDescInfo(netInfo, pLD->LDName, pDA, pDevice->p_mvl_type_ctrl);
#else
				node_get_DataDescInfo(netInfo, pLD->LDName, pDA);
#endif

				if (bNeedReadData)//对于定值或压板数据集,去读取实际结果数据
				{
#ifdef _MVL_TYPE_CTRL_use_one_device_
					if (get_tagDAData(netInfo, pLD->LDName, pDA, pDevice->p_mvl_type_ctrl)!=SD_SUCCESS)
#else
					if (get_tagDAData(netInfo, pLD->LDName, pDA)!=SD_SUCCESS)
#endif
					{
						continue;
					}
				}

				if (bHasMinMax)
				{
					node_get_DataLimitValInfoAll(netInfo, pLD->LDName, pDA);
				}
			}

#ifdef _MVL_TYPE_CTRL_use_one_device_
			node_get_rcbs_lcbs(netInfo,pLD, pDevice->p_mvl_type_ctrl);
#else
			node_get_rcbs_lcbs(netInfo,pLD);
#endif

			pLD_INFO->bHasEnum = TRUE;
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("结束读取装置模型"));

// 	for (long nLdIndex=0; nLdIndex<pDevice->numLD; nLdIndex++)
// 	{
// 		mms_Free_Data_Node(pDevice->LD[nLdIndex].mms_data_node);
// 		pDevice->LD[nLdIndex].mms_data_node = NULL;
// 	}

	return SD_SUCCESS;
}

ST_RET CMmsApi::MMS_DvmEnum(CFuncParamEx *pFuncParaEx)
{
	ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
	CString strFilePath;
	strFilePath = _P_GetInstallPath();
	CString strFileName;
	strFileName = pFuncParaEx->get_FileName();
	m_bOnlyReadValue = TRUE;

	if (strFileName.IsEmpty())
	{
		return SD_FAILURE;
	}

    strFilePath.AppendFormat(_T("e-Report\\Library\\%s.xml"),strFileName.GetString());
	mms_XmlWrite(strFilePath, &pACSINode[nDeviceIndex]);
	return SD_SUCCESS;
}

ST_RET CMmsApi::node_get_tagDAData(MVL_NET_INFO *net_info, LD_NODE *pLD, tagDA *pDA)
{
	MMS_DATA_NODE *pHead_LN_NODE = pLD->mms_data_node;
	MMS_DATA_NODE *pLN_NODE = pHead_LN_NODE;
	MMS_DATA_NODE *pNode_Data = NULL;
	ST_INT nLen;
	CString strTmp,strLNName,strFC;
	strTmp = mms_string(&pDA->DAValue.mmsName);
	nLen = strTmp.Find('$');

	if ((nLen == -1)||(pLN_NODE == NULL))
	{
		return SD_FAILURE;
	}

	strLNName = strTmp.Left(nLen);
	strTmp = strTmp.Mid(nLen+1);
	nLen = strTmp.Find('$');
	strFC = strTmp.Left(nLen);
	strTmp = strTmp.Mid(nLen+1);

	do 
	{
        if (strLNName == mms_string(&pLN_NODE->name) )
		{
			MMS_DATA_NODE *FC_node = pLN_NODE->pFirstChild;
			MMS_DATA_NODE *Head_FC_node = FC_node;

			if (FC_node == NULL)
			{
				return SD_FAILURE;
			}

			do 
			{
                if (strFC == mms_string(&FC_node->name) )
				{
					pNode_Data = find_node_by_name(FC_node,strTmp);

					if (pNode_Data == NULL)
						return SD_FAILURE;

					init_tagDA_datatype(pDA,pNode_Data);
					add_child_tagDA(pDA,pNode_Data);
					MMS_DATA_NODE *Find_node = node_find_child(pLN_NODE,_T("DC"));

					if (Find_node != NULL)
						node_get_desc_path(pDA,Find_node);

					Find_node = node_find_child(pLN_NODE,_T("CF"));

					if (Find_node != NULL)
					{
						node_get_LimitVal_path(pDA,Find_node);
					}

					return SD_SUCCESS;
				}

				FC_node = FC_node->pNext;
			} while((FC_node != Head_FC_node)&&(FC_node != NULL));
		}

		pLN_NODE = pLN_NODE->pNext;
	} while ((pLN_NODE != pHead_LN_NODE)&&(pLN_NODE != NULL));

	return SD_FAILURE;
}

void CMmsApi::node_get_desc_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE)
{
	CString strDescPath,strTmp;
	int nIndex = -1;
	strDescPath = mms_string(&pDA->DAValue.mmsName);
	nIndex = strDescPath.Find("$");
	strTmp = strDescPath.Left(nIndex);
    strTmp += "$DC$";
	strDescPath = strDescPath.Mid(nIndex+4);

//	if ((pDA->nDataType != DA_DATATYE_UTC_TIME)&&(pDA->nDataType != DA_DATATYE_BIT_STR)&&(pDA->nDataType != DA_DATATYE_ARRAY))
	{
		node_find_dU(pDA,pLN_NODE,strTmp,strDescPath);
	}
// 	else
// 		return;
// 
// 	tagDA *pSubDA = pDA->pSubDA;
// 	int nNum = pDA->nSubDANum;
//
// 	for (nIndex = 0;nIndex<nNum;nIndex++)
// 	{
// 		node_get_desc_path(&pSubDA[nIndex],pLN_NODE);
// 	}
}

void CMmsApi::node_get_LimitVal_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE)
{
	CString strDescPath,strPathHead,strPathTail,strTmp1,strTmp2;
	int nIndex = -1;
	strDescPath = mms_string(&pDA->DAValue.mmsName);
	nIndex = strDescPath.Find("$");
	strPathHead = strDescPath.Left(nIndex);
    strPathHead += ("$CF$");
	strPathTail = strDescPath.Mid(nIndex+4);
	strTmp1 = strPathHead;
	strTmp2 = strPathTail;

	node_find_MinMaxStepUnit(pDA,pLN_NODE,strPathHead,strPathTail,0);
	strPathHead = strTmp1;
	strPathTail = strTmp2;
	node_find_MinMaxStepUnit(pDA,pLN_NODE,strTmp1,strTmp2,1);
	strTmp1 = strPathHead;
	strTmp2 = strPathTail;
	node_find_MinMaxStepUnit(pDA,pLN_NODE,strPathHead,strPathTail,2);
	node_find_MinMaxStepUnit(pDA,pLN_NODE,strTmp1,strTmp2,3);
}

void CMmsApi::node_find_dU(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail)
{
	int nIndex = strPathTail.Find("$");
	CString strTmp1;
	MMS_DATA_NODE *Find_node = NULL;

	if (nIndex != -1)
	{
		strTmp1 = strPathTail.Left(nIndex);
		strPathTail = strPathTail.Mid(nIndex+1);
	} 
	else
		strTmp1 = strPathTail;

	Find_node = node_find_child(FC_node,strTmp1);

	if (Find_node != NULL)
	{
		MMS_DATA_NODE *FindChild_node = NULL;
		FindChild_node = node_find_child(Find_node,_T("dU"));
        strPathHead += (strTmp1);

		if (FindChild_node != NULL)
		{	
//			strPathHead.Append(_T("$dU"));
            mms_str_set(&pDA->DADescri.mmsName, strPathHead.GetString());
			mms_str_cat(&pDA->DADescri.mmsName, _T("$dU"));
		}

		if (nIndex != -1)
		{
            strPathHead += ("$");
			node_find_dU(pDA,Find_node,strPathHead,strPathTail);
		}
	}
}

void CMmsApi::node_find_MinMaxStepUnit(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail,ST_INT nLimitKind)                                                 
{                                                   //zhouhj nLimitKind=0代表最小值, nLimitKind=1代表最大值, nLimitKind=2代表步长, nLimitKind=3代表单位
	int nIndex = strPathTail.Find("$");
	CString strTmp1;
	MMS_DATA_NODE *Find_node = NULL;

	if (nIndex != -1)
	{
		strTmp1 = strPathTail.Left(nIndex);
		strPathTail = strPathTail.Mid(nIndex+1);
	} 
	else
		strTmp1 = strPathTail;

	Find_node = node_find_child(FC_node,strTmp1);

	if (Find_node != NULL)
	{
        strPathHead += (strTmp1);
		MMS_DATA_NODE *FindChild_node = NULL;

		if (nLimitKind == 0)
			FindChild_node = node_find_child(Find_node,_T("minVal"));
		else if (nLimitKind == 1)
			FindChild_node = node_find_child(Find_node,_T("maxVal"));
		else if (nLimitKind == 2)
			FindChild_node = node_find_child(Find_node,_T("stepSize"));
		else
			FindChild_node = node_find_child(Find_node,_T("units"));

		if (FindChild_node != NULL)
		{	
			CString strVal;
			strVal.Format("$%s",mms_string(&FindChild_node->name));
            strPathHead += (strVal);

			if (FindChild_node->pFirstChild!=NULL)
			{
				strVal.Format("$%s",mms_string(&FindChild_node->pFirstChild->name));
                strPathHead += (strVal);
			}

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
			if (nLimitKind == 0)
                mms_str_set(&pDA->MinVal.mmsName, strPathHead.GetString());
			else if (nLimitKind == 1)
                mms_str_set(&pDA->MaxVal.mmsName, strPathHead.GetString());
			else if (nLimitKind == 2)
                mms_str_set(&pDA->StepSize.mmsName, strPathHead.GetString());
			else
			{
				strPathHead.Replace("$SIUnit","");
				strPathHead.Replace("$multiplier","");
                mms_str_set(&pDA->DAUnite.mmsName, strPathHead.GetString());
			}
#endif
		}
		else if (nIndex != -1)
		{
            strPathHead += ("$");
			node_find_MinMaxStepUnit(pDA,Find_node,strPathHead,strPathTail,nLimitKind);
		}
	}
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
void CMmsApi::node_get_rcbs_lcbs( MVL_NET_INFO *netInfo,LD_NODE *pLD, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
void CMmsApi::node_get_rcbs_lcbs( MVL_NET_INFO *netInfo,LD_NODE *pLD)
#endif

{
	MMS_DATA_NODE *pHead_LN_NODE = pLD->mms_data_node;
	MMS_DATA_NODE *pLN_NODE = pHead_LN_NODE;
	MMS_DATA_NODE *FC_node = NULL;
	MMS_DATA_NODE *Head_FC_node = NULL;
	MMS_DATA_NODE *pNode_Data = NULL;
	char strRptPath[256];

	if (pHead_LN_NODE == NULL)
		return;

	for (int nIndex = 0;nIndex<pLD->numDaSet;nIndex++)
	{
		if (pLD->DataInfo[nIndex].numRcb>0)
			return;
	}

	do 
	{
		FC_node = pLN_NODE->pFirstChild;
		Head_FC_node = FC_node;

		if (Head_FC_node != NULL)
		{
			do 
			{
				if (stricmp(mms_string(&FC_node->name),_T("RP")) == 0)
				{
					sprintf(strRptPath, _T("%s$RP$"),mms_string(&pLN_NODE->name));
#ifdef _MVL_TYPE_CTRL_use_one_device_
					node_get_rpt_dataset(netInfo,pLD,FC_node,strRptPath, mvl_type_ctrl);
#else
					node_get_rpt_dataset(netInfo,pLD,FC_node,strRptPath);
#endif
				}
				else if (stricmp(mms_string(&FC_node->name),_T("BR")) == 0)
				{
					sprintf(strRptPath, _T("%s$BR$"),mms_string(&pLN_NODE->name));
#ifdef _MVL_TYPE_CTRL_use_one_device_
					node_get_rpt_dataset(netInfo,pLD,FC_node,strRptPath, mvl_type_ctrl);
#else
					node_get_rpt_dataset(netInfo,pLD,FC_node,strRptPath);
#endif
				}
				else if (stricmp(mms_string(&FC_node->name),_T("LG")) == 0)
				{
					sprintf(strRptPath, _T("%s$LG$"),mms_string(&pLN_NODE->name));
#ifdef _MVL_TYPE_CTRL_use_one_device_
					node_get_lcb_dataset(netInfo,pLD,FC_node,strRptPath, mvl_type_ctrl);
#else
					node_get_lcb_dataset(netInfo,pLD,FC_node,strRptPath);
#endif
				}

				FC_node = FC_node->pNext;
			} while((FC_node != Head_FC_node)&&(FC_node != NULL));
		}

		pLN_NODE = pLN_NODE->pNext;
	} while ((pLN_NODE != pHead_LN_NODE)&&(pLN_NODE != NULL));
}

LD_DATASET_INFO* mms_find_dataset_ld(LD_NODE *pLD, char *strRptID)
{
	LD_DATASET_INFO *pDatasetInfo = NULL;
	char *pTmp = NULL;

	for (int nIndex = 0;nIndex<pLD->numDaSet;nIndex++)
	{
		pDatasetInfo = &pLD->DataInfo[nIndex];
		pTmp = strstr(strRptID,pDatasetInfo->DataSetID);

		if (pTmp != NULL)
		{
			if (strcmp(pTmp,pDatasetInfo->DataSetID) == 0)
			{
				return pDatasetInfo;
			}
		}
	}

	return NULL;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
void CMmsApi::node_get_rpt_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node, char *strRptPath, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
void CMmsApi::node_get_rpt_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node, char *strRptPath)
#endif
{
	MMS_DATA_NODE *RptCtrl_node = FC_node->pFirstChild;
	MMS_DATA_NODE *Head_RptCtrl_node = FC_node->pFirstChild;
	LD_DATASET_INFO *pDatasetInfo = NULL;
	ST_RET ret;
	
	ST_CHAR rcbVar[NAMESIZE];

	if (RptCtrl_node == NULL)
		return;

	do 
	{
		ST_INT Type_id=-1;
		tagValueX xRptID;
        strcpy(rcbVar,strRptPath);
		strcat(rcbVar,mms_string(&RptCtrl_node->name));
		strcat(rcbVar,_T("$DatSet"));

#ifdef _MVL_TYPE_CTRL_use_one_device_
		if (get_varType(netInfo, pLD->LDName, &Type_id, rcbVar, mvl_type_ctrl) == SD_SUCCESS)
#else
		if (get_varType(netInfo, pLD->LDName, &Type_id, rcbVar) == SD_SUCCESS)
#endif
		{
			ret = get_varvalue(netInfo, rcbVar, pLD->LDName, Type_id, &xRptID, 1);

			if (ret == SD_SUCCESS)
			{
				pDatasetInfo = mms_find_dataset_ld(pLD, xRptID.string);

				if (pDatasetInfo != NULL)
				{
					strcpy(rcbVar,strRptPath);
					strcat(rcbVar,mms_string(&RptCtrl_node->name));
					strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].rcbName,rcbVar);
					strcat(rcbVar,_T("$RptID"));
					mvl_type_id_destroy(Type_id);

					if (get_varType(netInfo, pLD->LDName, &Type_id, rcbVar) == SD_SUCCESS)
					{
						ret = get_varvalue(netInfo, rcbVar, pLD->LDName, Type_id, &xRptID, 1);

						if (ret == SD_SUCCESS)
						{
							strcpy(pDatasetInfo->RCB[pDatasetInfo->numRcb].RptID,xRptID.string);
						}
					}

					pDatasetInfo->numRcb++;
				}
			}
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif

		RptCtrl_node = RptCtrl_node->pNext;
	} while((RptCtrl_node != Head_RptCtrl_node)&&(RptCtrl_node != NULL));
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
void CMmsApi::node_get_lcb_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node,const CString &strLogPath, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
void CMmsApi::node_get_lcb_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node
								   , char *strLogPath)
#endif
{
	MMS_DATA_NODE *LogCtrl_node = FC_node->pFirstChild;
	MMS_DATA_NODE *Head_RptCtrl_node = FC_node->pFirstChild;
	LD_LOG_INFO *pLogInfo = NULL;
	ST_RET ret;
	char *pTmp = NULL;

	ST_CHAR lcbVar[NAMESIZE];

	if (LogCtrl_node == NULL)
		return;

	do 
	{
		ST_INT Type_id=-1;
		tagValueX xLogID;

        strcpy(lcbVar,strLogPath);
		strcat(lcbVar,mms_string(&LogCtrl_node->name));
		strcat(lcbVar,_T("$DatSet"));

#ifdef _MVL_TYPE_CTRL_use_one_device_
		if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar, mvl_type_ctrl) == SD_SUCCESS)
#else
		if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar) == SD_SUCCESS)
#endif
		{
			ret = get_varvalue(netInfo, lcbVar, pLD->LDName, Type_id, &xLogID, 1);

			if (ret == SD_SUCCESS)
			{
				for (int nIndex = 0;nIndex<pLD->JournalCtrls.numData;nIndex++)
				{
					pLogInfo = &pLD->JournalCtrls.LogInfo[nIndex];
					pTmp = strstr(xLogID.string,mms_string(&pLogInfo->Dataset));

					if (pTmp != NULL)
					{
						if (strcmp(pTmp,mms_string(&pLogInfo->Dataset)) == 0)
						{
                            strcpy(lcbVar,strLogPath);
							strcat(lcbVar,mms_string(&LogCtrl_node->name));
							mms_str_set(&pLogInfo->Name,lcbVar);
							strcat(lcbVar,_T("$LogRef"));
#ifdef _MVL_TYPE_CTRL_use_one_device_
							mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
							mvl_type_id_destroy(Type_id);
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
							if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar, mvl_type_ctrl) == SD_SUCCESS)
#else
							if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar) == SD_SUCCESS)
#endif
							{
								ret = get_varvalue(netInfo, lcbVar, pLD->LDName, Type_id, &xLogID, 1);

								if (ret == SD_SUCCESS)
								{
									mms_str_set(&pLogInfo->logRef,xLogID.string);
								}
							}

#ifdef _MVL_TYPE_CTRL_use_one_device_
							mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
							mvl_type_id_destroy(Type_id);
#endif

							break;
						}
					}
				}

				mms_str_set(&pLogInfo->logRef,xLogID.string);
			}
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif

		LogCtrl_node = LogCtrl_node->pNext;
	} while((LogCtrl_node != Head_RptCtrl_node)&&(LogCtrl_node != NULL));
}

CString CMmsApi::remove_tail_digit(const CString &strRptName)
{
	long nAllLenth,nTailDigitLenth;
	nAllLenth = strRptName.GetLength();
	nTailDigitLenth = 0;

	for( int i=nAllLenth-1;i >= 0; i--)
	{
		if(strRptName.GetAt(i)>='0' &&  strRptName.GetAt(i)<='9')
			nTailDigitLenth++;
		else
			break;
	}

	CString strNewName;
	strNewName = strRptName.Left(nAllLenth-nTailDigitLenth);
	return strNewName;
}

MMS_DATA_NODE* CMmsApi::node_find_child(MMS_DATA_NODE *pLN_NODE,const CString &strTmp)
{
	MMS_DATA_NODE *Child_node = pLN_NODE->pFirstChild;
	MMS_DATA_NODE *Head_FC_node = pLN_NODE->pFirstChild;

	if (Child_node == NULL)
		return NULL;

	do 
	{
        if (strTmp == mms_string(&Child_node->name) )
		{

			return Child_node;
		}

		Child_node = Child_node->pNext;
	} while((Child_node != Head_FC_node)&&(Child_node != NULL));

	return NULL;
}

MMS_DATA_NODE* CMmsApi::find_node_by_name(MMS_DATA_NODE *FC_node,const CString&strDescPath)
{
	if ((FC_node == NULL)||(strDescPath.IsEmpty()))
		return NULL;

	if (FC_node->pFirstChild == NULL)
		return NULL;

	CString strNodeName,strTmp;
	ST_INT nLen = strDescPath.Find('$');

	if (nLen == -1)
		strNodeName = strDescPath;
	else
	{
		strNodeName = strDescPath.Left(nLen);
		strTmp = strDescPath.Mid(nLen+1);
	}

	MMS_DATA_NODE *pNode_Data = FC_node->pFirstChild;
	MMS_DATA_NODE *pHead_Node_Data = FC_node->pFirstChild;

	do 
	{
        if (strNodeName  == mms_string(&pNode_Data->name) )
		{
			if (strTmp.IsEmpty())
				return pNode_Data; 
			else
				return find_node_by_name(pNode_Data,strTmp);
		}

		pNode_Data = pNode_Data->pNext;
	} while((pNode_Data != pHead_Node_Data)&&(pNode_Data != NULL));

	return NULL;
}

void CMmsApi::add_child_tagDA(tagDA *pDA,MMS_DATA_NODE *pNode_Data)
{
	if (pNode_Data->pFirstChild == NULL)
	{
		pDA->nSubDANum = 0;
		pDA->pSubDA = NULL;
	} 
	else
	{
		ST_INT nSubNum = 0;
		get_node_numbers(pNode_Data,nSubNum);

		if (pDA->pSubDA != NULL)
		{
			for (int i=0;i<pDA->nSubDANum;i++)
			{
				mms_ReleaseData(&pDA->pSubDA[i]);
			}

			pDA->nSubDANum = 0;
			free(pDA->pSubDA);
			pDA->pSubDA = NULL;
		}

		pDA->nSubDANum = nSubNum;
		pDA->pSubDA = mms_new_tagda(pDA->nSubDANum);
		mms_InitDatas(pDA->pSubDA, pDA->nSubDANum);
		MMS_DATA_NODE *pNode_Child = pNode_Data->pFirstChild;
		MMS_DATA_NODE *pNode_Head_Child = pNode_Child;	
		tagDA *pNewDA = pDA->pSubDA;

		do 
		{
			init_tagDA_data(pNewDA,pNode_Child,mms_string(&pDA->DAValue.mmsName));
			get_node_tagDA(&pNewDA,pNode_Child);
			pNode_Child = pNode_Child->pNext;
		} while ((pNode_Child!=pNode_Head_Child)&&(pNode_Child != NULL));
	}
}

void CMmsApi::get_node_tagDA(tagDA **ppDA,MMS_DATA_NODE *pNode_Data)
{
	char szTmp[MAX_DSNAME] = {0};
	strcpy(szTmp,mms_string(&(*ppDA)->DAValue.mmsName));

	if (pNode_Data->pFirstChild == NULL)
	{
		(*ppDA)->nSubDANum = 0;
		(*ppDA)->pSubDA = NULL;
		(*ppDA)++;
	} 
	else if (strcmp((*ppDA)->DataType,_T("ARRAY")) == 0)
	{
		strcpy((*ppDA)->DataType,_T("STRUCT"));
		mms_InitDA_DataType(*ppDA);
		(*ppDA)->nSubDANum = 1;
		(*ppDA)->pSubDA = mms_new_tagda();
		mms_InitDatas((*ppDA)->pSubDA, 1);	
		tagDA *pNewDA = (*ppDA)->pSubDA;
		strcpy(pNewDA->DataType,_T("ARRAY"));
		mms_InitDA_DataType(pNewDA);
		mms_str_set(&pNewDA->DAValue.mmsName, szTmp);
		mms_str_cat(&pNewDA->DAValue.mmsName, "$");
		add_node_tagDA_ARRAY(pNewDA,pNode_Data);

		(*ppDA)++;
	}
	else
	{
		MMS_DATA_NODE *pNode_Child = pNode_Data->pFirstChild;
		MMS_DATA_NODE *pNode_Head_Child = pNode_Child;	

		do 
		{
			init_tagDA_data(*ppDA,pNode_Child,szTmp);
			get_node_tagDA(ppDA,pNode_Child);
			pNode_Child = pNode_Child->pNext;
			
		} while((pNode_Child!=pNode_Head_Child)&&(pNode_Child != NULL));
	}
}

void CMmsApi::add_node_tagDA_ARRAY(tagDA *pDA,MMS_DATA_NODE *pNode_Data)
{
	ST_INT nSubNum = 0,nArrNum = pNode_Data->data.valLong;

	pDA->nSubDANum = nArrNum;
	pDA->pSubDA = mms_new_tagda(nArrNum);
	mms_InitDatas(pDA->pSubDA, nArrNum);
	tagDA *pFirstSub = pDA->pSubDA;

	mms_str_set(&pFirstSub->DAValue.mmsName, mms_string(&pDA->DAValue.mmsName));
	get_node_numbers(pNode_Data,nSubNum);

	if (nSubNum == 1)
	{
		pFirstSub->nSubDANum = 0;
		pFirstSub->pSubDA = NULL;
		get_node_tagDA(&pFirstSub,pNode_Data);
		pFirstSub--;
	} 
	else if (nSubNum > 1)
	{
		strcpy(pFirstSub->DataType,_T("STRUCT"));
		mms_InitDA_DataType(pFirstSub);
		pFirstSub->nSubDANum = nSubNum;
		pFirstSub->pSubDA = mms_new_tagda(nSubNum);
		mms_InitDatas(pFirstSub->pSubDA, nSubNum);
		tagDA *pNewDA = pFirstSub->pSubDA;
		mms_str_set(&pNewDA->DAValue.mmsName, mms_string(&pDA->DAValue.mmsName));
		get_node_tagDA(&pNewDA,pNode_Data);
	}

	ST_CHAR DAName[NAMESIZE];
	memset(DAName, 0, NAMESIZE);

	for (int k=1; k<pDA->nSubDANum; k++)
	{
		mms_CopyData(pFirstSub, &pDA->pSubDA[k], FALSE);
		sprintf(DAName, "%d", k);
		My_PareVarType_Array_MmsName(&pDA->pSubDA[k], DAName);
	}
}

void CMmsApi::init_tagDA_data(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child,ST_CHAR *pValuePath)
{
	CString strNewPath;
	init_tagDA_datatype(pNewDA,pNode_Child);

	strNewPath.Format(_T("%s$%s"),pValuePath,mms_string(&pNode_Child->name));
	strNewPath.Replace("$$","$");
    mms_str_set(&pNewDA->DAValue.mmsName, strNewPath.GetString());
}

void CMmsApi::init_tagDA_datatype(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child)
{
	CString strDataType = pNode_Child->DataType;

	if (strDataType.IsEmpty())
		strcpy(pNewDA->DataType,_T("STRUCT"));
	else if(strDataType == _T("BVSTRING13"))
		strcpy(pNewDA->DataType,_T("BIT_STR"));
	else if(strDataType == _T("UTF8VSTRING255"))
		strcpy(pNewDA->DataType,_T("UTF8_STR"));
	else if(strDataType == _T("VSTRING255"))
		strcpy(pNewDA->DataType,_T("V_STR"));
	else if(strDataType == _T("BSTRING2"))
		strcpy(pNewDA->DataType,_T("BIT_STR"));
	else if(strDataType == _T("OVSTRING64"))
		strcpy(pNewDA->DataType,_T("OCT_STR"));
	else if(strDataType == _T("VSTRING65"))
		strcpy(pNewDA->DataType,_T("V_STR"));
	else if(strDataType == _T("BVSTRING2"))
		strcpy(pNewDA->DataType,_T("BIT_STR"));
	else if(strDataType == _T("UBYTE"))
		strcpy(pNewDA->DataType,_T("UINT"));
	else if(strDataType == _T("BVSTRING2"))
		strcpy(pNewDA->DataType,_T("BIT_STR"));
	else if(strDataType == _T("LONG"))
		strcpy(pNewDA->DataType,_T("INT"));
	else if(strDataType == _T("BYTE"))
		strcpy(pNewDA->DataType,_T("INT"));
	else if(strDataType == _T("UTCTIME"))
		strcpy(pNewDA->DataType,_T("UTC_TIME"));
	else
        strcpy(pNewDA->DataType,strDataType.GetString());

	mms_InitDA_DataType(pNewDA);
}

void CMmsApi::get_node_numbers(MMS_DATA_NODE *pNode_Data,ST_INT &nSubNum)
{
	if (pNode_Data->pFirstChild == NULL)
	{
		nSubNum++;
		return;
	}

	MMS_DATA_NODE *pNode_Child = pNode_Data->pFirstChild;

	do 
	{
		if (strcmp(pNode_Child->DataType,_T("ARRAY")) == 0)
			nSubNum++;
		else
			get_node_numbers(pNode_Child,nSubNum);

		pNode_Child = pNode_Child->pNext;
	}
	while((pNode_Child != pNode_Data->pFirstChild)&&(pNode_Child!=NULL));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static int EncryptPwd(const char *paramRawData,int rawDataLength, const char *paramKey, int keyLength, char* retEncryptData)
{
	sm4_context mContent;
	char rawData[32];
	char rawKey[32];
	char rawResult[32] = {0};
	time_t currentTime;
	int i = 0;
	// filter
	if(rawDataLength > 12){
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "raw data length error\n");
//		printf("raw data length error\n");
		return 1;
	}

	if(keyLength > 16) {
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "key length error\n");
//		printf("key length error\n");
		return 1;
	}

	// set data
	memset(rawData,0,sizeof(rawData));
	memset(rawKey,0,sizeof(rawKey));
	memset(retEncryptData,0,16);
	rawData[rawDataLength] = 0;
	rawKey[keyLength] = 0;

	currentTime = time(0);
	ULONG nTime = currentTime;
	nTime = htonl(nTime);
	memcpy(rawData,&nTime,4);
	//memcpy(rawData, "9876", 4);
	memcpy(rawData+4,paramRawData,12);
	memcpy(rawKey,paramKey,min(keyLength, 16));

	//encrypt data
	sm4_setkey_enc(&mContent,(unsigned char*)rawKey);
	sm4_crypt_ecb(&mContent,1,16,(unsigned char*)rawData,(unsigned char*)rawResult);

	for(i = 0; i < 16; ++i) 
	{
		sprintf(retEncryptData + i * 2, "%02X", (unsigned char)rawResult[i]);
//		printf("%s\n", retEncryptData);
	}
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "retEncryptData=%s;",retEncryptData);

	return 0;
}

/* 2012-10-17  装置联机 */
ST_RET CMmsApi::MMS_LinkDev(CFuncParamEx *pFuncParaEx)
{
	ST_INT iDvIndex;
	ST_RET ret = SD_FAILURE;
	ACSI_NODE *pDevice;
	char passwd[NAMESIZE];
	PIPE_MSG_BUFS *pMsgBuf = NULL;

	memset(passwd, 0, NAMESIZE);
	pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
	mms_ResetRptIndex(pDevice);

	if (!pFuncParaEx->Chck_DevIndex())
		return ret;

	iDvIndex = pFuncParaEx->get_DevIndex();
	pMsgBuf = &g_pPipeMsgBuffs[iDvIndex];

	if (sock_info_table==NULL)
		return ret;

	acsi_ctrl_table[iDvIndex].needConnect = SD_TRUE;

	if (acsi_ctrl_table[iDvIndex].CMD==CMD_CONNECT)
	{
		if (acsi_ctrl_table[iDvIndex].g_timeOut++ > 30)
		{
			acsi_ctrl_table[iDvIndex].g_timeOut = 0;
		}
	}

	CGpsPcTimeTickCount  oTickCount32;
	ST_INT nConnCount = 0;

	if (pDevice->psw[0] != 0 && pDevice->key[0] != 0)
	{
		EncryptPwd(pDevice->psw, strlen(pDevice->psw), pDevice->key, strlen(pDevice->key), passwd);
	}

	if (acsi_ctrl_table[iDvIndex].needConnect)
	{
		g_b_post_FuncID_TestProc_error = FALSE;
		
		if (NULL != acsi_ctrl_table[iDvIndex].pnet_info)
		{
			if (m_bMmsDisConBfConnected)
			{
#ifdef _use_bunlink_buse_critcle
				mms_set_bufs_parse(pMsgBuf);

				while (pMsgBuf->buse == 1)
				{
					Sleep(1);
				}
#endif
				//disconnectFromServer((MVL_NET_INFO *)acsi_ctrl_table[iDvIndex].pnet_info);
				disconnectFromServerEx(iDvIndex);

#ifdef _use_bunlink_buse_critcle
				//pMsgBuf->bunlink =	1;//  2018-10-17  lijq   不再处于断开连接状态
#endif

			}

			ResetNetInfo(iDvIndex);
			m_bMmsDisConBfConnected = TRUE;
		}

#ifdef _use_bunlink_buse_critcle
		pMsgBuf->bunlink = 0;//  2018-10-17  lijq   不再处于断开连接状态
		pMsgBuf->buse = 0;//  2018-10-17  lijq   不再处于断开连接状态
		//mms_set_bufs_parse(pMsgBuf);
#endif

		g_b_post_FuncID_TestProc_error = TRUE;

		while (nConnCount <m_bMaxMmsConnectedTimes)
		{
			ret = connect_proc(iDvIndex, SD_TRUE, passwd);

			if (ret==SD_SUCCESS)
			{
				pACSINode[iDvIndex].bConnect = SD_TRUE;
				break;
			}
			else
			{
				pACSINode[iDvIndex].bConnect = SD_FALSE;
			}
			nConnCount++;
		}

		pACSINode[iDvIndex].bCanReConnect = SD_FALSE;
		g_n_MVL_ERR_USR_TIMEOUT_Count = 0;

		if (m_bExitServeACSIServer)
		{
			mms_UpdateDeviceState(&pACSINode[iDvIndex]);
		}
	}

	pDevice->tmTotal += oTickCount32.GetTickCountLong();
	m_bMaxMmsConnectedTimes = 1;

	return ret;
}

/* 2012-10-17  装置断开链接 */
ST_RET CMmsApi::MMS_UnLinkDev(CFuncParamEx *pFuncParaEx)
{
	ST_INT iDeviceIndex;//, nMsgIndex;
	
	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	iDeviceIndex = pFuncParaEx->get_DevIndex();
	CGpsPcTimeTickCount  oTickCount32;
	ACSI_NODE *pDevice;
	pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;

	if (NULL != acsi_ctrl_table[iDeviceIndex].pnet_info)
	{
// 		SOCK_INFO *sock_info = &sock_info_table[pFuncParaEx->get_DevIndex()];//zhouhj 20181009
// 
// 		ST_INT ping_ret = ping(sock_info->ip_addr);  	

#ifdef _use_bunlink_buse_critcle
		PIPE_MSG_BUFS *pMsgBuf = &g_pPipeMsgBuffs[iDeviceIndex];
		mms_set_bufs_parse(pMsgBuf);

// 		while (pMsgBuf->buse == 1)
// 		{
// 			Sleep(1);
// 		}
#endif

		//李俊庆修改：如果网络断开，就无法ping通，就会无法关闭本地的socket，导致再次连接出问题
		//2018-10-18
		//if(1 == ping_ret)
		{
			//disconnectFromServer((MVL_NET_INFO *)acsi_ctrl_table[iDeviceIndex].pnet_info);
			disconnectFromServerEx(iDeviceIndex);
		}

#ifdef _use_bunlink_buse_critcle
		//Sleep(100);
		//pMsgBuf->bunlink = 1;  //断开连接之前，设置标志，让接收端不再接受报文 2018-10-17  lijq
#endif

		ResetNetInfo(iDeviceIndex);
		m_bMmsDisConBfConnected = TRUE;
	}

	pDevice->tmTotal += oTickCount32.GetTickCountLong();
	pDevice->bConnect = FALSE;
	mms_ResetRptIndex(pDevice);

	if (pDevice->nReleaseWhenUnlink)
	{
		ReleaseObjData(pDevice);
	}

	return SD_SUCCESS;
}

/* 2012-11-22  基本数据操作过程 */
long CMmsApi::MMS_DataOpeProc(CFuncParamEx *pFuncParaEx)
{
	ST_INT i;

	if (!pFuncParaEx->Chck_DevIndex())
	{//无效的设备
		return -1;
	}

	if (pFuncParaEx->m_bHasPostMsg)
	{//已经执行完毕，返回
		return -1;
	}

	i = pFuncParaEx->get_DevIndex();
	ST_INT nFuncID = pFuncParaEx->get_FuncID();
	ST_RET nRet = SD_SUCCESS;
	SOCK_INFO *sock_info = &sock_info_table[pFuncParaEx->get_DevIndex()];

	if (sock_info != NULL)
	{
		sock_info->send_error = 0;
	}

	switch(nFuncID)
	{
	case FuncID_Link:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_LinkDev(pFuncParaEx);
		break;
	case FuncID_UnLink:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_UnLinkDev(pFuncParaEx);
		break;
	case FuncID_EnumLD:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_EnumLDDir(pFuncParaEx);

		if (m_bEnumLN)
		{
			nRet = MMS_EnumLNDir(pFuncParaEx);
		}

		break;

	case FuncID_EnumLN:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_EnumLNDir(pFuncParaEx);
		break;

	case FuncID_Write:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_WriteData(pFuncParaEx);
		break;
	case FuncID_WriteSingle:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_WriteDataSingle(pFuncParaEx);
		break;
	case FuncID_Read:
		//mms_log_error_infor = 0;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadData(pFuncParaEx);
		break;
	case FuncID_ReadOne:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadOneData(pFuncParaEx);
		break;
	case FuncID_Read_SET:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadDataSetting(pFuncParaEx);
		break;

	case FuncID_ReadDir:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadDir(pFuncParaEx);
		break;

	case FuncID_ReadFile:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadFile(pFuncParaEx);
		break;

	case FuncID_StartRpt:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_StartDevRpt(pFuncParaEx);
		break;
	case FuncID_StopRpt:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_StopDevRpt(pFuncParaEx);
		break;
	case FuncID_SetSGNum:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_SetActiveSG(pFuncParaEx);
		break;
	case FuncID_GetSGNum:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		m_nLdIndexBack = pFuncParaEx->get_LDvIndex();

		while (TRUE)
		{
			nRet = MMS_GetActiveSG(pFuncParaEx);

			if (nRet == SD_SUCCESS)
			{
				break;
			}

			if (!MMS_GetNextLdZonePara(pFuncParaEx))
			{
				break;
			}
		}

		break;
	case FuncID_SetSENum:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_SetEditSG(pFuncParaEx,pFuncParaEx->get_SEID());
		break;
	case FuncID_CnfSetSE:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_CnfEditSG(pFuncParaEx);
		break;
	case FuncID_CtrlWrite:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_CtrlWrite(pFuncParaEx);
		break;
	case FuncID_CtrlWriteOne:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_CtrlWriteOne(pFuncParaEx);
		break;
	case FuncID_Reset:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ResetDev(pFuncParaEx);
		break;
	case FuncID_ReadJournalCount:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadJournalCount(pFuncParaEx);
		break;
	case FuncID_ReadJournal:
		//mms_log_error_infor = 1;
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadJournal(pFuncParaEx);
		break;
	case FuncID_TestProc:
		//mms_log_error_infor = 0;
		nRet = SD_SUCCESS;
		break;
	case FuncID_UploadFile:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_UploadFile(pFuncParaEx);
		break;
	case FuncID_ReadDevice:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_ReadDevice(pFuncParaEx);
		break;
	case FuncID_DvmEnum:
		acsi_ctrl_table[i].idleCount = 0;
		nRet = MMS_DvmEnum(pFuncParaEx);
		break;
		/*测试网络状态*/
// 		if (acsi_ctrl_table[i].idleCount++ > 400)
// 		{
// 			acsi_ctrl_table[i].idleCount = 0;
// 			nRet = MMS_TestNetProc();
// 
// 			if (nRet == SD_FAILURE)
// 			{
// 				ACSI_NODE *pDevice = get_DevACSI_NODEPtr();
// 
// 				if (pDevice != NULL)
// 				{
// 					pDevice->bConnect = SD_FALSE;
// 					pDevice->bCanReConnect = SD_TRUE;
// 				}
// 			}
// 
// 			m_FuncParam.MySendMessage(nFuncID,nRet);
// 		}
	default:
		break;
	}

	if (sock_info != NULL)
	{
		if (sock_info->send_error > 0)
		{
			nRet = SD_FAILURE;
		}
	}

	return nRet;
}

/* 2012-11-22  测试MMS网络过程 */
ST_RET CMmsApi::MMS_TestNetProc(CFuncParamEx *pFuncParaEx)
{
	MVL_NET_INFO *net_info;
	NAMELIST_REQ_INFO getnam_req;
	ST_RET	ret;
	MVL_REQ_PEND *reqCtrl;
	ST_INT nACSI;

	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	nACSI = pFuncParaEx->get_DevIndex();

	net_info = (MVL_NET_INFO*)(acsi_ctrl_table[nACSI].pnet_info);

	if (net_info == NULL)
	{
		return SD_FAILURE;
	}

	acsi_ctrl_table[nACSI].CMD = CMD_NULL;
	acsi_ctrl_table[nACSI].g_timeOut = 0;
	acsi_ctrl_table[nACSI].IsEnd = STAT_END;
	acsi_ctrl_table[nACSI].idleCount = 0;
	acsi_ctrl_table[nACSI].needTest = SD_FALSE;

	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = MMS_CLASS_DOM;   
	getnam_req.objscope = VMD_SPEC;
	getnam_req.cont_after_pres = SD_FALSE;
	req_pend_table[nACSI].done = SD_FALSE;
	net_info->numpend_req = 0;
	ret = mvla_getnam (net_info, &getnam_req, &reqCtrl);
	if (ret == SD_SUCCESS)
	{
		ret = waitReqDone (reqCtrl, g_timeOut, net_info->nACSI);
		if (ret != SD_SUCCESS)
		{
			//m_strMMSApiError = "test server timeout";
			ret = SD_FAILURE;
		}
		else
		{
			//m_strMMSApiError = "test server success";
			acsi_ctrl_table[nACSI].testCount = 0;
			acsi_ctrl_table[nACSI].CMD = CMD_NULL;
			acsi_ctrl_table[nACSI].g_timeOut = 0;
			acsi_ctrl_table[nACSI].IsEnd = STAT_END;
			acsi_ctrl_table[nACSI].idleCount = 0;
			ret = SD_SUCCESS;
		}
	}
	else
	{
		//m_strMMSApiError = "test server fail";
		ret = SD_FAILURE;
	}

	if (ret == SD_FAILURE)
	{
		if(acsi_ctrl_table[nACSI].testCount++ > 1)
		{
			sock_info_table[nACSI].net_error = SD_TRUE;
			acsi_ctrl_table[nACSI].testCount = 0;
			acsi_ctrl_table[nACSI].idleCount = 0;
			acsi_ctrl_table[nACSI].needConnect = SD_TRUE;
			acsi_ctrl_table[nACSI].needDirectory = SD_FALSE;
			acsi_ctrl_table[nACSI].CMD = CMD_NULL;
			acsi_ctrl_table[nACSI].IsEnd = STAT_END;
			Sleep(1000);
		}
	}

	mvl_free_req_ctrl (reqCtrl);

	return ret;
}

ST_VOID CMmsApi::Mms_TestNetsProc()
{
	return;
	long nIndex = 0;

	for (nIndex=0; nIndex<numDevice; nIndex++)
	{
		Mms_TestNetProc(nIndex);
	}
}

ST_RET CMmsApi::Mms_TestNetProc(ST_INT nACSI)
{
	MVL_NET_INFO *net_info;
	NAMELIST_REQ_INFO getnam_req;
	ST_RET	ret;
	MVL_REQ_PEND *reqCtrl;

	net_info = (MVL_NET_INFO*)(acsi_ctrl_table[nACSI].pnet_info);

	if (net_info == NULL)
	{
		return SD_FAILURE;
	}

	ACSI_NODE *pDevice = &pACSINode[nACSI];

	if (pDevice->bTestLinkState)
	{
		return SD_SUCCESS;
	}

	SOCK_INFO *sock_info;		/* new tracking struct for this conn.*/
	sock_info = &sock_info_table[nACSI];

	if (sock_info->ulTickCount == 0)
	{
		sock_info->ulTickCount = ::GetTickCount();
		return SD_FAILURE;
	}

	CTickCount32 oTickCount;

	//每30秒查询一次
	if (oTickCount.CalTickCountLong(sock_info->ulTickCount) < 30000)
	{
		return SD_FAILURE;
	}

	acsi_ctrl_table[nACSI].CMD = CMD_NULL;
	acsi_ctrl_table[nACSI].g_timeOut = 0;
	acsi_ctrl_table[nACSI].IsEnd = STAT_END;
	acsi_ctrl_table[nACSI].idleCount = 0;
	acsi_ctrl_table[nACSI].needTest = SD_FALSE;

	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = MMS_CLASS_DOM;//9;   
	getnam_req.objscope = VMD_SPEC;
	getnam_req.cont_after_pres = SD_FALSE;
	req_pend_table[nACSI].done = SD_FALSE;
	net_info->numpend_req = 0;
	ret = mvla_getnam (net_info, &getnam_req, &reqCtrl);

	if (ret == SD_SUCCESS)
	{
		ret = waitReqDone (reqCtrl, g_timeOut, net_info->nACSI);
	
		if (ret != SD_SUCCESS)
		{
			sock_info->net_error = 1;
			req_pend_table[nACSI].reconnect = TRUE;
			sock_info->state = SOCK_STATE_CONNECTING;
		}
		else
		{
			acsi_ctrl_table[nACSI].testCount = 0;
			acsi_ctrl_table[nACSI].CMD = CMD_NULL;
			acsi_ctrl_table[nACSI].g_timeOut = 0;
			acsi_ctrl_table[nACSI].IsEnd = STAT_END;
			acsi_ctrl_table[nACSI].idleCount = 0;
			ret = SD_SUCCESS;
		}
	}
	else
	{
		ret = SD_FAILURE;
	}

	if (ret == SD_FAILURE)
	{
		sock_info->net_error = 1;
		req_pend_table[nACSI].reconnect = TRUE;
		sock_info->state = SOCK_STATE_CONNECTING;
		sock_info_table[nACSI].net_error = SD_TRUE;
	}
	else
	{
	}

	mvl_free_req_ctrl (reqCtrl);

	if (ret != SD_SUCCESS)
	{
		m_oFuncParamEx[nACSI].set_DevIndex(nACSI);
		m_oFuncParamEx[nACSI].set_FuncID(FuncID_Link);
		ret = MMS_LinkDev(&m_oFuncParamEx[nACSI]);
	}

	sock_info->ulTickCount = ::GetTickCount();

	return ret;
}

/* 2012-10-10  枚举所有装置的逻辑节点目录 */
ST_RET CMmsApi::MMS_EnumLDDir(CFuncParamEx *pFuncParaEx)
{
	ST_INT ret;
	ST_INT i;
	ST_INT j;
	ST_INT k;

	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
	MVL_REQ_PEND *reqCtrl;
	NAMELIST_REQ_INFO getnam_req;
	NAMELIST_RESP_INFO *getnam_resp;
	ST_CHAR **nptr;
	MVL_NET_INFO *netInfo;
	ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
	i = nDeviceIndex;
	
	pFuncParaEx->SetTitle("Enum Logic Device Dir");

	//for (i=0; i<numDevice; i++)
	{
		netInfo = (MVL_NET_INFO*)(acsi_ctrl_table[i].pnet_info);
		acsi_ctrl_table[i].CMD = CMD_DIR;
		acsi_ctrl_table[i].needDirectory = SD_FALSE;
		acsi_ctrl_table[i].g_timeOut = 0;

		getnam_req.cs_objclass_pres = SD_FALSE;
		getnam_req.obj.mms_class = MMS_CLASS_DOM;//9; 
		getnam_req.objscope = VMD_SPEC;
		getnam_req.cont_after_pres = SD_FALSE;
		ret = mvla_getnam (netInfo, &getnam_req, &reqCtrl);
		if (ret == SD_SUCCESS)
			ret = waitReqDone (reqCtrl, g_timeOut, netInfo->nACSI);
		else
		{
			mvl_free_req_ctrl (reqCtrl);
			m_bMMSConnected = SD_FALSE;
			return SD_FAILURE;
		}

		if (ret != SD_SUCCESS)
		{
			m_bMMSConnected = SD_FALSE;
			return SD_FAILURE;
		}

		getnam_resp = (NAMELIST_RESP_INFO *) reqCtrl->u.ident.resp_info;

		// 初始化数据
		nptr = (ST_CHAR **) (getnam_resp + 1);

#ifdef _use_dynamic_mem
		if (pACSINode[i].nHasDeviceModel == 0)
		{//没有枚举模型
			mms_New_ACSI_NODE_numLD(&pACSINode[i], getnam_resp->num_names, TRUE);
		}
#else
		pACSINode[i].numLD = getnam_resp->num_names;
#endif

		pACSINode[i].numRCB = 0;
		acsi_ctrl_table[i].bShow = SD_FALSE;

		for (j=0; j<pACSINode[i].numLD; j++)
		{
			if (j >= getnam_resp->num_names)
			{//自动测试模式下，读取XML文件后，枚举目录
				break;
			}

			if (nptr[0]!=0)
			{
				_snprintf(pACSINode[i].LD[j].LDName, NAMESIZE-1, "%s", nptr[j]);
			}
		}

		acsi_ctrl_table[i].CMD = CMD_NULL;
		acsi_ctrl_table[i].g_timeOut = 0;
		acsi_ctrl_table[i].IsEnd = STAT_END;
		acsi_ctrl_table[i].bShow = SD_TRUE;

		mvl_free_req_ctrl (reqCtrl);

		//////////////////////////////////////////////////////////////////////////
		// 2013-4-8  枚举逻辑设备的数据集
		getnam_req.cs_objclass_pres = SD_FALSE;
		getnam_req.obj.mms_class = MMS_CLASS_VARLIST;//2; // Named Variable List
		getnam_req.objscope = DOM_SPEC;
		getnam_req.cont_after_pres = SD_FALSE;

		for (j=0; j<pACSINode[i].numLD; j++)
		{
			LD_NODE*pLD = &pACSINode[i].LD[j];

			if (pACSINode[i].nHasDeviceModel == 1)
			{//已经读取了XML模型文件，并且需要读取模型，则不处理数据集枚举
				break;
			}

			strcpy(getnam_req.dname, pLD->LDName);

			CString strLDName = pLD->LDName;
			strLDName.MakeUpper();

			if (g_bMultDevModel)
			{
				if (strLDName.Find("PROT") == -1)
				{
					continue;
				}
			}

			ret = mvla_getnam (netInfo, &getnam_req, &reqCtrl);
			if (ret == SD_SUCCESS)
				ret = waitReqDone (reqCtrl, g_timeOut, netInfo->nACSI);
			else
			{
				mvl_free_req_ctrl (reqCtrl);
				break;;
			}

			if (ret != SD_SUCCESS)
				break;

			getnam_resp = (NAMELIST_RESP_INFO *) reqCtrl->u.ident.resp_info;

			// 初始化数据
			nptr = (ST_CHAR **) (getnam_resp + 1);
			long nDatasetNum = getnam_resp->num_names;

			if ((g_bAutoGenModelDatas)&&(strLDName.Find("PROT") >= 0))//自动添加对应数据集
			{
				nDatasetNum++;
			}

			if (g_bUseDsDout)
			{
				nDatasetNum++;
			}


#ifdef _use_dynamic_mem
			mms_New_LD_NODE_numDataset(pLD, nDatasetNum);
			mms_New_LD_NODE_numJournal(pLD, nDatasetNum);
#else
			pLD->numDaSet = nDatasetNum;
			pLD->JournalCtrls.numData = nDatasetNum; 
#endif

			for (k=0; k<getnam_resp->num_names/*pLD->numDaSet-1*/; k++)
			{
				if (nptr[0]!=0)
				{
					ZeroMemory(pLD->DataInfo[k].DataSetID,NAMESIZE);
					strcpy(pLD->DataInfo[k].DataSetID, nptr[k]);
					mms_set_dataset_desc(&pLD->DataInfo[k]);
					mms_str_assign((&pLD->JournalCtrls.LogInfo[k].Dataset), nptr[k]);
				}
			}

			if ((g_bAutoGenModelDatas)&&(strLDName.Find("PROT") >= 0))//自动添加对应数据集
			{
				long nDsDevStdMsgIndex = k;
				strcpy(pLD->DataInfo[k].DataSetID, dsDevStdMsg);

				int nSize = 2;
				mms_New_LD_DATASET_INFO_numData(&pLD->DataInfo[nDsDevStdMsgIndex],nSize );
				mms_str_set(&pLD->DataInfo[nDsDevStdMsgIndex].DataSet[0].DAValue.mmsName,_T("LPHD1$DC$PhyNam$serNum"));
				mms_str_set(&pLD->DataInfo[nDsDevStdMsgIndex].DataSet[0].DADescri.Value.string,_T("装置识别代码"));
				strcpy(pLD->DataInfo[nDsDevStdMsgIndex].DataSet[0].DataType,_T("V_STR"));
				pLD->DataInfo[nDsDevStdMsgIndex].DataSet[0].Type_id = DA_DATATYE_VISIBLE_STR;

				mms_str_set(&pLD->DataInfo[nDsDevStdMsgIndex].DataSet[1].DAValue.mmsName,_T("LPHD1$DC$PhyNam$swRev"));
				mms_str_set(&pLD->DataInfo[nDsDevStdMsgIndex].DataSet[1].DADescri.Value.string,_T("装置程序版本"));
				strcpy(pLD->DataInfo[nDsDevStdMsgIndex].DataSet[1].DataType,_T("V_STR"));
				pLD->DataInfo[nDsDevStdMsgIndex].DataSet[1].Type_id = DA_DATATYE_VISIBLE_STR;
			}

			if (g_bUseDsDout)
			{
				strcpy(pLD->DataInfo[nDatasetNum-1].DataSetID, dsDout);
			}

			mvl_free_req_ctrl (reqCtrl);
		}

		if (pACSINode[i].nHasDeviceModel == 1)
		{//已经读取了XML模型文件，并且需要读取模型，则不处理数据集枚举
			return SD_SUCCESS;
		}

		//////////////////////////////////////////////////////////////////////////
		// 2012-11-29 枚举逻辑设备数据集数据的数目
		long nReadDatasetNum = 0;
		CString strLDName;

		for (j=0; j<pACSINode[i].numLD; j++)
		{
			LD_NODE *pLD = &pACSINode[i].LD[j];
			strLDName = pLD->LDName;
			strLDName.MakeUpper();

			if (g_bUseDsDout)
			{
				nReadDatasetNum = pLD->numDaSet-1;
			} 
			else
			{
				nReadDatasetNum = pLD->numDaSet;
			}

			if ((strLDName.Find(_T("PROT"))>=0)&&g_bAutoGenModelDatas)
			{
				nReadDatasetNum--;
			}

			for (k=0;k<nReadDatasetNum;k++)
			{
				get_varlistattri(netInfo, pLD, k);
			}
		}
	}

	return SD_SUCCESS;
}

void CMmsApi::mms_set_dataset_desc(LD_DATASET_INFO *pDatasetInfor)
{
	CMmsEngineDatasets *pDatasets = m_oMmsEngineConfig.GetMmsDatasetsCfg();

	if (pDatasets == NULL)
	{
		return;
	}

	CMmsEngineDsCfg *pCurDataset = NULL;
	POS pos = pDatasets->GetHeadPosition();
	CString strDatasetDesc;

	while(pos)
	{
		pCurDataset = (CMmsEngineDsCfg *)pDatasets->GetNext(pos);
		strDatasetDesc.Format(_T("%s"),pDatasetInfor->DataSetID);

		if (strDatasetDesc.Find(pCurDataset->m_strID) != -1)
		{
			strDatasetDesc.Replace(pCurDataset->m_strID,pCurDataset->m_strName);
			CString_to_char(strDatasetDesc,pDatasetInfor->DaSetDesc);
		}
	}
}

ST_RET CMmsApi::MMS_EnumLNDir(CFuncParamEx *pFuncParaEx)
{
	ST_INT j;

	NAMELIST_REQ_INFO getnam_req;
	MVL_NET_INFO *netInfo;
	ST_INT nDeviceIndex = pFuncParaEx->get_DevIndex();
	enum NODE_TYPE nTypeDepp_1 = DO_TYPE;

	netInfo = (MVL_NET_INFO*)(acsi_ctrl_table[nDeviceIndex].pnet_info);
	acsi_ctrl_table[nDeviceIndex].CMD = CMD_DIR;
	acsi_ctrl_table[nDeviceIndex].needDirectory = SD_FALSE;
	acsi_ctrl_table[nDeviceIndex].g_timeOut = 0;
	acsi_ctrl_table[nDeviceIndex].CMD = CMD_NULL;
	acsi_ctrl_table[nDeviceIndex].g_timeOut = 0;
	acsi_ctrl_table[nDeviceIndex].IsEnd = STAT_END;
	acsi_ctrl_table[nDeviceIndex].bShow = SD_TRUE;

	//////////////////////////////////////////////////////////////////////////
	// 2013-4-8 枚举逻辑设备的数据集
	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = MMS_CLASS_VARLIST; //2; // Named Variable List
	getnam_req.objscope = DOM_SPEC;
	getnam_req.cont_after_pres = SD_FALSE;

	pFuncParaEx->SetTitle("Enum Logic Node Dir");
	pFuncParaEx->SetMaxRange(pACSINode[nDeviceIndex].numLD);
	CString strMsg;

	for (j=0; j<pACSINode[nDeviceIndex].numLD; j++)
	{
		LD_NODE*pLD = &pACSINode[nDeviceIndex].LD[j];

		pFuncParaEx->SetTitle(pLD->LDName);
		strMsg.Format(g_sLangTxt_IndexAndTotal, j+1, pACSINode[nDeviceIndex].numLD);//_T("第%d个  共%d个")
		pFuncParaEx->ShowMsg(strMsg);
		pFuncParaEx->StepIt();

		GetLogicalNodeDirectory(nDeviceIndex, pLD);

		MMS_DATA_NODE *pHead_LN_NODE = pLD->mms_data_node;
		MMS_DATA_NODE *pLN_NODE = pHead_LN_NODE;

		do 
		{
			if (pLN_NODE == NULL)
			{
				break;
			}

			//获取LLN0的属性，因为LLN0对应的属性字符串过长，所以按照FC获取字符串，并解析获取的字符串并添加到树状模型中
#ifdef _use_mms_string
			if (strcmp(mms_string(&pLN_NODE->name),"LLN0")==0)
#else
			if (strcmp(pLN_NODE->name,"LLN0")==0)
#endif
			{
				nTypeDepp_1 = DO_TYPE;
			}
			else
			{
				nTypeDepp_1 = FC_TYPE;
			}

			MMS_DATA_NODE *FC_node = pLN_NODE->pFirstChild;
			MMS_DATA_NODE *Head_FC_node = pLN_NODE->pFirstChild;

			do 
			{
				if (FC_node == NULL)
				{
					break;
				}

				if(Get_LNX_Attributte(nDeviceIndex,pLD->LDName, FC_node, nTypeDepp_1)==SD_FAILURE)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "GetLogicalNodeAttributte failed! name is :%s", mms_string(&FC_node->name) );						
				}

				FC_node = FC_node->pNext;
			} while (FC_node != Head_FC_node);

			pLN_NODE = pLN_NODE->pNext;
		} while (pLN_NODE != pHead_LN_NODE);
	}

	if (!g_bMultDevModel)
	{
		Get_Nodes_Detail(nDeviceIndex);
	}

	//GetControlDirectory(nDevIndex);
	//mms_XmlWriteNode(_T("D:/Node.xml"), &pACSINode[pFuncParaEx->m_nConnDevIndex], false);

	CLogPrint::LogString(XLOGLEVEL_TRACE, "EnumLNDir  Finished");						

	return SD_SUCCESS;
}

/************************************************************************/
/* 遍历树状模型，获取遥控数据                                                                     */
/************************************************************************/
ST_INT CMmsApi::GeCount_DATA_NODE(MMS_DATA_NODE *pNode)
{
	long nCount = 0;
	MMS_DATA_NODE *p = pNode->pFirstChild;

	while (p != NULL)
	{
		nCount++;
		p = p->pNext;
	}

	return nCount;
}

MMS_DATA_NODE* CMmsApi::Get_DATA_NODE_Oper(MMS_DATA_NODE *pNode)
{
	MMS_DATA_NODE *p = NULL;
	MMS_DATA_NODE *pFind = NULL;

#ifdef _use_mms_string
	if (strcmp(mms_string(&pNode->name), "Oper") == 0)
#else
	if (strcmp(pNode->name, "Oper") == 0)
#endif
	{
		pFind = pNode;
		return pFind;
	}

	p = pNode->pFirstChild;

	while (p != NULL)
	{
		pFind = Get_DATA_NODE_Oper(p);

		if (pFind != NULL)
		{
			break;
		}

		p = p->pNext;
	}

	return pFind;
}

MMS_DATA_NODE* CMmsApi::Find_DATA_NODE(MMS_DATA_NODE *pParent, char *pName)
{
	MMS_DATA_NODE *p = NULL;
	MMS_DATA_NODE *pFind = NULL;

#ifdef _use_mms_string
	if (strcmp(mms_string(&pParent->name), pName) == 0)
#else
	if (strcmp(pParent->name, pName) == 0)
#endif
	{
		pFind = pParent;
		return pFind;
	}

	p = pParent->pFirstChild;

	while (p != NULL)
	{
		pFind = Find_DATA_NODE(p, pName);

		if (pFind != NULL)
		{
			break;
		}

		p = p->pNext;
	}

	return pFind;
}

ST_VOID CMmsApi::Init_tagDA_by_DATA_NODE(tagDA *pDA, MMS_DATA_NODE *pNode)
{
	MMS_DATA_NODE *pOper = Get_DATA_NODE_Oper(pNode);

	if (pOper == NULL)
	{
		strcpy(pDA->DataType, "BOOL");
		mms_InitDA_DataType(pDA);
	}
	else
	{
		Init_tagDA_by_DATA_NODE2(pDA, pOper);
		mms_InitDA_DataType(pDA);
	}
}

ST_VOID CMmsApi::Set_DATA_NODE_DataType(MMS_DATA_NODE *pNode, ST_CHAR *strDataType)
{
//	strcpy(pNode->DataType, strDataType);
//	CharUpperBuff(pNode->DataType, strlen(pNode->DataType));
    char *pEnd = strDataType + strlen(strDataType);
    char *p1 = strDataType;
    char *p2 = pNode->DataType;
    char chOffset = 'a' - 'A';  //'a' == 97  'A'=65

    while (p1 < pEnd)
    {
        if ('a' <= *p1 && *p1 <='z')
        {
            *p2 = *p1 - chOffset;
        }
        else
        {
            *p2 = *p1;
        }
        p1++;
        p2++;
    }

    *p2 = 0;
}

ST_VOID CMmsApi::Init_tagDA_by_DATA_NODE2(tagDA *pDA, MMS_DATA_NODE *pNode)
{
	if (pNode->pFirstChild == NULL)
	{
		strcpy(pDA->DataType, pNode->DataType);
		mms_InitDA_DataType(pDA);
	}
	else
	{
		strcpy(pDA->DataType, "STRUCT");
		mms_InitDA_DataType(pDA);
	}

#ifdef _use_mms_string
	mms_str_copy(&pDA->DAValue.mmsName, &pNode->name);
#else
	strcpy(pDA->DAValue.mmsName, pNode->name);
#endif

	long nCount = GeCount_DATA_NODE(pNode);

	if (nCount == 0)
	{
		return;
	}

	MMS_DATA_NODE *p = pNode->pFirstChild;
	pDA->pSubDA = (struct tagDA *)malloc(nCount*sizeof(tagDA));
	ZeroMemory(pDA->pSubDA, nCount*sizeof(tagDA));
	pDA->nSubDANum = nCount;
	long nIndex = 0;

	while (p != NULL)
	{
		Init_tagDA_by_DATA_NODE2(&pDA->pSubDA[nIndex], p);
		p = p->pNext;
		nIndex++;
	}
}

BOOL CMmsApi::mms_Is_CO_CtrlMode_1_4(ST_INT nDeviceIndex, char *pLdName, tagDA *pDaValue)
{
	MVL_NET_INFO *connectInfo=NULL;
	connectInfo = (MVL_NET_INFO*)(acsi_ctrl_table[nDeviceIndex].pnet_info);

	if (connectInfo == NULL)
	{
		return FALSE;
	}

	get_tagDADataValue2(connectInfo, pLdName, "INT", &pDaValue->DAValue, DA_DATATYE_INT);

	if (pDaValue->DAValue.Value.i == 1 || pDaValue->DAValue.Value.i == 4)
	{
		return TRUE;
	}

	return FALSE;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
void CMmsApi::mms_Init_desc_data_node(ST_INT nDeviceIndex, char *pLdName, tagDA *pDa, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
void CMmsApi::mms_Init_desc_data_node(ST_INT nDeviceIndex, char *pLdName, tagDA *pDa)
#endif
{
	MVL_NET_INFO *connectInfo=NULL;
	connectInfo = (MVL_NET_INFO*)(acsi_ctrl_table[nDeviceIndex].pnet_info);

	if (connectInfo == NULL)
	{
		return;
	}

	ST_INT Type_id=-1;
	ST_INT ret = 0;
//	tagValueX xValue;

#ifdef _use_mms_string
#ifdef _MVL_TYPE_CTRL_use_one_device_
	if (get_varType(connectInfo, pLdName, &Type_id, mms_string(&pDa->DADescri.mmsName), mvl_type_ctrl) == SD_SUCCESS)
#else
	if (get_varType(connectInfo, pLdName, &Type_id, mms_string(&pDa->DADescri.mmsName)) == SD_SUCCESS)
#endif
	{
		ret = get_varvalue_x(connectInfo, mms_string(&pDa->DADescri.mmsName), pLdName, Type_id, &pDa->DADescri.Value, 1, DA_DATATYE_UTF8_STR);
	}
#else
	if (get_varType(connectInfo, pLdName, &Type_id, pDa->DADescri.mmsName) == SD_SUCCESS)
	{
		ret = get_varvalue(connectInfo, pDa->DADescri.mmsName, pLdName, Type_id, &pDa->DADescri.Value, 1);

		if (ret != SD_FAILURE)
		{
			mms_UTF8ToUnicodeEx(pDa->DADescri.Value.string, strlen(pDa->DADescri.Value.string), pDa->DADescri.Value.string);
		}
	}
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
	mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
	mvl_type_id_destroy(Type_id);
#endif
}

// void mms_init_Journal(MMS_DATA_NODE *head_node, tagJOURNAL *pJournal)
// {
// 	MMS_DATA_NODE *da_node = head_node->pFirstChild;
// 	
// #ifdef _use_mms_string
// 	char mmsName[NAMESIZE];
// 	sprintf(mmsName, "LLN0$LG$%s", mms_string(&head_node->name));
// 	mms_str_set(&pJournal->Name, mmsName);
// #else
// 	sprintf(pJournal->Name, "LLN0$LG$%s", head_node->name);
// #endif
// 
// 	tagDAValueEx *pValueEx = NULL;
// 
// 	while (da_node != NULL)
// 	{
// 		pValueEx = NULL;
// 
// #ifdef _use_mms_string
// 		if (strcmp(mms_string(&da_node->name),"logref")==0)
// #else
// 		if (stricmp(da_node->name, _T("logref")) == 0)
// #endif
// 		{
// 			pValueEx = &pJournal->logRef;
// 		}
// #ifdef _use_mms_string
// 		if (strcmp(mms_string(&da_node->name),"dataset")==0)
// #else
// 		else if (stricmp(da_node->name, _T("dataset")) == 0)
// #endif
// 		{
// 			pValueEx = &pJournal->Dataset;
// 		}
// #ifdef _use_mms_string
// 		if (strcmp(mms_string(&da_node->name),"datset")==0)
// #else
// 		else if (stricmp(da_node->name, _T("datset")) == 0)
// #endif
// 		{
// 			pValueEx = &pJournal->Dataset;
// 		}
// #ifdef _use_mms_string
// 		if (strcmp(mms_string(&da_node->name),"logena")==0)
// #else
// 		else if (stricmp(da_node->name, _T("logena")) == 0)
// #endif
// 		{
// 			pValueEx = &pJournal->logEna;
// 		}
// 
// 		if (pValueEx != NULL)
// 		{
// #ifdef _use_mms_string
// 			sprintf(mmsName, "LLN0$LG$%s$%s", mms_string(&head_node->name), mms_string(&da_node->name) );
// 			mms_str_set(&pValueEx->mmsName, mmsName);
// 			mms_str_set(&pValueEx->DataType, da_node->DataType);
// #else
// 			sprintf(pValueEx->mmsName, "LLN0$LG$%s$%s", head_node->name, da_node->name);
// 			memcpy(pValueEx->DataType, da_node->DataType, 10);
// #endif
// 		}
// 
// 		da_node = da_node->pNext;
// 	}
// }

#ifdef _use_mms_string
void CMmsApi::MMS_CopyJournal(LD_LOG_INFO *pDest, LD_LOG_INFO *pSrc)
{
	mms_str_copy(&pDest->Name, &pSrc->Name);
//	mms_str_copy(&pDest->Descri, &pSrc->Descri);
	mms_str_copy(&pDest->Dataset, &pSrc->Dataset);
	pDest->intgPD = pSrc->intgPD;
	mms_str_copy(&pDest->logRef, &pSrc->logRef);
	pDest->logEna = pSrc->logEna;
	pDest->trgOps = pSrc->trgOps;
// 	MMS_MEM_STRING Name;
// 	tagDAValueEx Descri;	//描述
// 	tagDAValueEx Dataset;	
// 	tagDAValueEx intgPD;
// 	tagDAValueEx logRef;		//最大值
// 	tagDAValueEx logEna;		//最小值
// 	tagDAValueEx trgOps;		//stepsize
}
#endif

BOOL IsValidFC(const char *strFC)
{
	if (strcmp(strFC, ("ST") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("SG") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("CO") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("LG") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("RP") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("BR") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("SP") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("MX") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("DC") )== 0)
	{
		return TRUE;
	}
	else if (strcmp(strFC, ("CF") )== 0)
	{
		return TRUE;
	}

	return FALSE;
}

ST_RET CMmsApi::GetLogicalNodeDirectory(ST_INT _iNetInfo,LD_NODE *_LDNode)
{
	ST_INT ret;
	ST_INT k; //2023-2-1  lijunqing  i 改为 k，字符宽度大点，阅读性好
	ST_CHAR **nptr;
	NAMELIST_REQ_INFO getnam_req;
	MVL_REQ_PEND *reqCtrl;
	NAMELIST_RESP_INFO *getnam_resp;

	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = MMS_CLASS_VAR; //MMS_CLASS_VAR
	getnam_req.objscope = DOM_SPEC;
	getnam_req.cont_after_pres = SD_FALSE;
	strcpy(getnam_req.dname,_LDNode->LDName);

	MVL_NET_INFO *connectInfo=NULL;
	connectInfo = (MVL_NET_INFO*)(acsi_ctrl_table[_iNetInfo].pnet_info);

	if (connectInfo==NULL)
	{
		return SD_FAILURE;
	}

	//获取LLN0
	MMS_DATA_NODE *LLN0_node = NULL;
//	MMS_DATA_NODE *pFind;
	ST_BOOLEAN more_follows = false;
	ST_CHAR strFC[10]={0};

	LLN0_node = NULL;
	char *p = NULL, *pTemp = NULL;
	long nNodeLen = 0;

	do
	{
		ret = mvla_getnam(connectInfo,&getnam_req,&reqCtrl);
		if (ret ==SD_SUCCESS)
			ret = waitReqDone(reqCtrl,g_timeOut, _iNetInfo);

		if (ret!=SD_SUCCESS/*SD_FAILURE*/)//zhouhj 20180919 在响应超时时，此处如不退出软件会进入死循环
		{
			return SD_FAILURE;
		}

		getnam_resp = (NAMELIST_RESP_INFO *)(reqCtrl->u.ident.resp_info);

		if (getnam_resp->num_names == 0)
		{
			break;
		}

		nptr = (ST_CHAR **)(getnam_resp + 1);
	
		for (k = 0; k < getnam_resp->num_names; k++)
		{
			//LN节点的子节点
			if (LLN0_node != NULL)
			{
				pTemp = nptr[k] + nNodeLen;

				if (*pTemp == '$' && *(pTemp+3) == 0)
				{
					//memcpy(strFC, pTemp+1, 2);

					if (IsValidFC(/*strFC*/pTemp+1))//增加判断,是否为有效的功能约束  zhouhj 20210423
					{
						if (mms_find_data_node_child(LLN0_node, /*strFC*/pTemp+1) == NULL)
						{
							mms_node_append_child(LLN0_node, /*strFC*/pTemp+1, FC_TYPE);

// 							if (!g_bMultDevModel)
// 							{
// 								CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "**[%s] LN append:%s --- (%s)",_LDNode->LDName, nptr[k], strFC);
// 							}
						}
					}
				}
			}

			//筛选出LN节点
			if (strchr(nptr[k], '$') == NULL)  //没有找到字符'$'，表示LN节点
			{
				nNodeLen = strlen(nptr[k]);
				LLN0_node=mms_node_append_sibling(NULL, &_LDNode->mms_data_node, nptr[k], FC_TYPE);

// 				if (!g_bMultDevModel)
// 				{
// 					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "[%s] append LN:%s",_LDNode->LDName, nptr[k]);
// 				}
			}
		}

		getnam_req.cont_after_pres = SD_TRUE;
		strcpy(getnam_req.continue_after,nptr[(getnam_resp->num_names) - 1]);

		more_follows = getnam_resp->more_follows;
		mvl_free_req_ctrl(reqCtrl);

	}while(more_follows == SD_TRUE);

	if (!g_bMultDevModel)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "** LD [%s] ",_LDNode->LDName);
	}

//	mms_XmlWriteNode(_T("d:\\121.xml"), &pACSINode[_iNetInfo], FALSE);
	return SD_SUCCESS;
}
/************************************************************************/
/*获取LLN0的访问属性                                                                      */
/************************************************************************/
/**********************************************
* to convert a asn.1 type to local data type
*
**********************************************/

ST_RET asn_type_to_local(ST_INT asn1_len, ST_UCHAR *asn1, ST_CHAR* retOut)
{
	ST_CHAR *tdl;
	ST_CHAR *asn1Copy;

	asn1Copy = (ST_CHAR *) chk_malloc (asn1_len);
	memcpy (asn1Copy, asn1, asn1_len);
	tdl = ms_asn1_to_tdl ((ST_UCHAR *) asn1Copy, asn1_len, 256000);
	if (tdl)
	{
		if ((ST_INT) strlen (tdl))
		{
			//log_printf("Type Specification Follows in TDL: ");
			if(retOut )
			{
				strcpy(retOut,tdl);
			}
			//log_printf("  '%s'", tdl);
		}
		else
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, "Type Specification TDL too long to log ...");
			//log_printf((ST_INT) strlen (tdl), tdl);
			return SD_FALSE;
		}
		chk_free (tdl);
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, "  Could not convert following Type Specification to TDL: ");
		//log_printf (asn1_len, asn1);
		return SD_FALSE;
	}

	chk_free (asn1Copy);

	return SD_SUCCESS;
}

ST_RET CMmsApi::Get_LNX_Attributte(ST_INT _iNetInfo, ST_CHAR *pLDName,MMS_DATA_NODE* _FCNode, enum NODE_TYPE nTypeDepp_1)
{
	MMS_DATA_NODE *pParent = (MMS_DATA_NODE*)_FCNode->pParent;
	ST_RET ret;
	MVL_REQ_PEND *reqCtrl=NULL;
	GETVAR_REQ_INFO getvar_req={0};
	ST_CHAR tmpDataType[256000];
	ST_CHAR item_id[256]={0};

	getvar_req.req_tag = GETVAR_NAME;
	getvar_req.name.object_tag = DOM_SPEC;
	getvar_req.name.domain_id = pLDName;
	sprintf(item_id,"%s$%s", mms_string(&pParent->name) , mms_string(&_FCNode->name));
	getvar_req.name.obj_name.item_id=item_id;

	MVL_NET_INFO *connectInfo=NULL;
	connectInfo = (MVL_NET_INFO*)(acsi_ctrl_table[_iNetInfo].pnet_info);
	ret = mvla_getvar (connectInfo, &getvar_req, &reqCtrl);

	if (ret == SD_SUCCESS)
	{
		ret = waitReqDone (reqCtrl, g_timeOut, _iNetInfo);
	}

	if (ret != SD_SUCCESS)
	{
#ifdef _use_mms_string
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error getting type of variable '%s' in domain '%s'",(char*)mms_string(&_FCNode->name),pLDName);
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error getting type of variable '%s' in domain '%s'",(char*)_FCNode->name, pLDName);
#endif
	}
	else
	{
		ret = asn_type_to_local(reqCtrl->u.getvar.resp_info->type_spec.len, 
			reqCtrl->u.getvar.resp_info->type_spec.data, tmpDataType);

		//解析LNX属性结构
		if (ret == SD_SUCCESS)
		{
			Pharse_LNX_Attributte(connectInfo,tmpDataType,pLDName, _FCNode, nTypeDepp_1);
		}
		else
		{
#ifdef _use_mms_string
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error asn_type_to_local variable '%s' in domain '%s'[len=%d].",
				(char*)mms_string(&_FCNode->name),pLDName,reqCtrl->u.getvar.resp_info->type_spec.len);
#else
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error asn_type_to_local variable '%s' in domain '%s'[len=%d].",
				(char*)_FCNode->name, pLDName,reqCtrl->u.getvar.resp_info->type_spec.len);
#endif
		}
	}

	mvl_free_req_ctrl (reqCtrl);

	return SD_SUCCESS;
}


/************************************************************************/
/* 解析LNX节点的属性                                                                     */
/************************************************************************/
ST_RET CMmsApi::Pharse_LNX_Attributte(MVL_NET_INFO *connectInfo,ST_CHAR *_pStrLine, ST_CHAR *pLDName,MMS_DATA_NODE* _FCNode, enum NODE_TYPE nTypeDepp_1)
{
	ST_INT i,j,deeph,preDeep,iLeft,iRight,iArray;
	ST_CHAR ch;
	MMS_DATA_NODE* childNode;
	ST_CHAR strTemp[255];
	ST_INT nLineLen = strlen(_pStrLine);

	deeph=0;
	preDeep=0;

	for (i=0;i<nLineLen;i++)
	{
		ch=_pStrLine[i];

		switch(ch)
		{
		case '{':
			{
				iRight=-1;
				deeph++;
				break;
			}
		case '}':
			{
				//获取DA数据类型
				if (iRight!=-1)
				{
					memset(strTemp,0,sizeof(strTemp));
					memcpy(strTemp,_pStrLine+iRight+1,i-iRight-1);
					Set_DATA_NODE_DataType(childNode, strTemp);
					preDeep=deeph;
				}

				iRight=-1;
				deeph--;

				break;
			}
		case '(':
			{
				iLeft=i;
				break;
			}
		case ')':
			{
				if (preDeep==0)
				{
                    //childNode=_FCNode.AppendChild();
					childNode = mms_node_append_child2(_FCNode);
				}
				else
				{
					//当前深度大于前一个，说明时子节点
					if (deeph>preDeep)
					{
                        //childNode=childNode.AppendChild();
						childNode = mms_node_append_child2(childNode);
					}
					//当前深度大于前一个，说明是兄弟节点
					else if(deeph==preDeep)
					{
                        //childNode=childNode.Parent().AppendChild();
						childNode = mms_node_append_child2(childNode->pParent);
					}
					//当前深度小于前一个，说明时父辈节点的兄弟节点
					else
					{
						//获取父辈节点
						j=deeph;

						while(j<preDeep)
						{
							//pChildNode=pChildNode->pParent;
							childNode=childNode->pParent;
							j++;
						}

						//获取父辈节点的兄弟节点
                        //childNode=childNode.Parent().AppendChild();
						childNode = mms_node_append_child2(childNode->pParent);
					}
				}

				iRight=i;

				if (deeph==1)
				{
					childNode->type = nTypeDepp_1;
				}

				memset(strTemp,0,sizeof(strTemp));
				memcpy(strTemp,_pStrLine+iLeft+1,i-iLeft-1);

#ifdef _use_mms_string
				mms_str_set(&childNode->name, strTemp);
#else
				strcpy(childNode->name, strTemp);
#endif
				preDeep=deeph;
				iLeft=0;

				break;
			}
		case ',':
			{
				//获取数据类型
				if (iRight!=-1)
				{
					memset(strTemp,0,sizeof(strTemp));
					memcpy(strTemp,_pStrLine+iRight+1,i-iRight-1);
					Set_DATA_NODE_DataType(childNode, strTemp);
					preDeep=deeph;
				}

				iRight=-1;
				break;
			}
		case '[':
			{
				//获取数组
				iArray = i;
				break;
			}
		case ':':
			{
				//获取数组
				memset(strTemp,0,sizeof(strTemp));
				memcpy(strTemp,_pStrLine+iArray+1,i-iArray-1);
				Set_DATA_NODE_DataType(childNode, _T("ARRAY"));
				childNode->data.valLong = CString_To_long(strTemp);
				break;
			}
		}
	}

	return SD_SUCCESS;
}


ST_RET CMmsApi::Get_Nodes_Detail(ST_INT nDeviceIndex)
{
	int j = 0;

	//for (CDataNode LDNode=Root().FirstChild();LDNode;LDNode=LDNode.NextSibling())
	for (j=0; j<pACSINode[nDeviceIndex].numLD; j++)
	{
		LD_NODE*pLD = &pACSINode[nDeviceIndex].LD[j];
		MMS_DATA_NODE *head_ln_data_node = pLD->mms_data_node;
		MMS_DATA_NODE *ln_data_node = head_ln_data_node;
		CStringArray straDatas;
		CString strData;

		CString strLDName = pLD->LDName;
		strLDName.MakeUpper();

		//if (strLDName.Find("PROT") == -1)  //只提取PROT下的控制类信息
		//{
		//	continue;
		//}

		//for (CDataNode LNNode=LDNode.FirstChild();LNNode;LNNode=LNNode.NextSibling())
		do 
		{
			if (ln_data_node == NULL)
			{
				break;
			}

			MMS_DATA_NODE *head_co = ln_data_node->pFirstChild;
			MMS_DATA_NODE *co_node = head_co;

			//CDataNode CONode = LNNode.Child("CO");
			//for (CDataNode node=CONode.FirstChild();node;node=node.NextSibling())
			do 
			{
				if (co_node == NULL)
				{
					break;
				}

				if (g_bUseDsDout)//在添加控制类信号数据集的情况下,进行如下操作
				{
#ifdef _use_mms_string
					if (strcmp(mms_string(&co_node->name),"CO") == 0)
#else
					if (strcmp(co_node->name, "CO") == 0)
#endif
					{
						MMS_DATA_NODE *head_da = co_node->pFirstChild;
						MMS_DATA_NODE *da_node = head_da;

						//for (CDataNode node=CONode.FirstChild();node;node=node.NextSibling())
						do 
						{
							if (da_node == NULL)
							{
								break;
							}

							strData.Format("%s$ST$%s",mms_string(&ln_data_node->name),mms_string(&da_node->name));//zhouhj20190102设置dsDout数据集中的FC类型
							straDatas.Add(strData);

							da_node = da_node->pNext;
						} while (da_node != head_da);
					}
				}

#ifdef _use_mms_string
				if (strcmp(mms_string(&co_node->name),"LG")==0)
#else
				else if (strcmp(co_node->name, "LG") == 0)
#endif
				{
					MMS_DATA_NODE *head_da = co_node->pFirstChild;
					MMS_DATA_NODE *da_node = head_da;

					do 
					{
						if (da_node == NULL)
						{
							break;
						}

						da_node = da_node->pNext;
					} while (da_node != head_da);
				}

				co_node = co_node->pNext;
			} while (co_node != head_co);

			ln_data_node = ln_data_node->pNext;
		} while (ln_data_node != head_ln_data_node);

		if (g_bUseDsDout)
		{
			int nSize = straDatas.GetSize();
			long nDatasetIndex = pLD->numDaSet-1;
			mms_New_LD_DATASET_INFO_numData(&pLD->DataInfo[nDatasetIndex],nSize );

			for (int nCount = 0; nCount < nSize; ++nCount)
			{
				mms_str_set(&pLD->DataInfo[nDatasetIndex].DataSet[nCount].DAValue.mmsName,
                    straDatas.GetAt(nCount).GetString());
			}
		}

	}//for (j=0; j<pACSINode[nDeviceIndex].numLD; j++)

	// 	for (CDataNode LDNode=Root().FirstChild();LDNode;LDNode=LDNode.NextSibling())
	// 	{
	// 		for (CDataNode LNNode=LDNode.FirstChild();LNNode;LNNode=LNNode.NextSibling())
	// 		{
	// 			CDataNode CONode = LNNode.Child("CO");
	// 			for (CDataNode node=CONode.FirstChild();node;node=node.NextSibling())
	// 			{
	// 				Control_Data_Struct controlData;
	// 				controlData.CO = node;
	// 				controlData.iConnect = &m_pData->iNet;
	// 				controlData.value = LNNode.Child("ST").Child(node.Name());
	// 				controlData.ctlModel = LNNode.Child("CF").Child(node.Name()).Child("ctlModel");
	// 				ReadLeafNode(controlData.ctlModel);
	// 				sprintf(controlData.reference,"%s/%s$CO$%s",LDNode.Name(),LNNode.Name(),node.Name());
	// 				controlData.dU = LNNode.Child("DC").Child(node.Name()).Child("dU");
	// 				ReadLeafNode(controlData.dU);
	// 
	// 				m_pData->controlDataVec.push_back(controlData);
	// 			}
	// 		}
	// 	}

	return SD_SUCCESS;
}

ST_RET CMmsApi::Get_Node_Value(ST_INT nDeviceIndex, LD_NODE*pLD, ST_CHAR pszParentPath, MMS_DATA_NODE* _FCNode)
{
	MMS_DATA_NODE *head_da = _FCNode->pFirstChild;
	MMS_DATA_NODE *da_node = head_da;

	if (head_da == NULL)
	{

	}

	return 0;
}


ST_RET CMmsApi::GetLLN0Attributte(ST_INT _iNetInfo,ST_CHAR *_pLDName,MMS_DATA_NODE* _FCNode)
{
	ST_RET ret;
	MVL_REQ_PEND *reqCtrl=NULL;
	GETVAR_REQ_INFO getvar_req={0};
	ST_CHAR tmpDataType[256000];

	getvar_req.req_tag = GETVAR_NAME;
	getvar_req.name.object_tag = DOM_SPEC;
	getvar_req.name.domain_id=_pLDName;
	ST_CHAR item_id[256]={0};
	sprintf(item_id,"LLN0$%s", mms_string(&_FCNode->name) );
	getvar_req.name.obj_name.item_id=item_id;

	MVL_NET_INFO *connectInfo=NULL;
	connectInfo = (MVL_NET_INFO*)(acsi_ctrl_table[_iNetInfo].pnet_info);

	ret = mvla_getvar (connectInfo, &getvar_req, &reqCtrl);
	if (ret == SD_SUCCESS)
		ret = waitReqDone (reqCtrl, g_timeOut, _iNetInfo);

	if (ret != SD_SUCCESS)
	{
#ifdef _use_mms_string
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error getting type of variable '%s' in domain '%s'",(char*)mms_string(&_FCNode->name),_pLDName);
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error getting type of variable '%s' in domain '%s'",(char*)_FCNode->name,_pLDName);
#endif
	}
	else
	{
		ret = asn_type_to_local(reqCtrl->u.getvar.resp_info->type_spec.len, 
			reqCtrl->u.getvar.resp_info->type_spec.data, tmpDataType);

		//if (strcmp(_FCNode->name, "CO") == 0)
// 		{
// 			CString strFile;
// 			strFile = _P_GetBinPath();
// 			strFile.AppendFormat("%sLLN0$%s.txt",_pLDName, _FCNode->name);
// 			CFile file;
// 
// 			if (file.Open(strFile, CFile::modeCreate | CFile::modeWrite))
// 			{
// 				file.Write(tmpDataType, strlen(tmpDataType));
// 				file.Close();
// 			}
// 
// 		}


		//解析LLN0属性结构
		if (ret == SD_SUCCESS)
		{
			PharseLLN0Attributte(tmpDataType,_FCNode);
		}
	}

	mvl_free_req_ctrl (reqCtrl);

	return SD_SUCCESS;
}

/************************************************************************/
/* 解析LLN0节点的属性                                                                     */
/************************************************************************/
ST_RET CMmsApi::PharseLLN0Attributte(ST_CHAR *_pStrLine,MMS_DATA_NODE* _FCNode)
{
	ST_INT i,j,deeph,preDeep,iLeft,iRight;
	ST_CHAR ch;
	MMS_DATA_NODE* childNode;
	ST_CHAR strTemp[255];
	ST_INT nLineLen = strlen(_pStrLine);

	deeph=0;
	preDeep=0;

	for (i=0;i<nLineLen;i++)
	{
		ch=_pStrLine[i];
		switch(ch)
		{
		case '{':
			{
				iRight=-1;
				deeph++;
				break;
			}
		case '}':
			{
				//获取DA数据类型
				if (iRight!=-1)
				{
					memset(strTemp,0,sizeof(strTemp));
					memcpy(strTemp,_pStrLine+iRight+1,i-iRight-1);
					Set_DATA_NODE_DataType(childNode, strTemp);
					preDeep=deeph;
				}
				iRight=-1;

				deeph--;
				break;
			}
		case '(':
			{
				iLeft=i;
				break;
			}
		case ')':
			{
				if (preDeep==0)
				{
					childNode = mms_node_append_child2(_FCNode);
                    //childNode=_FCNode.AppendChild();
				}
				else
				{
					//当前深度大于前一个，说明时子节点
					if (deeph>preDeep)
					{
                        //childNode=childNode.AppendChild();
						childNode = mms_node_append_child2(childNode);
					}
					//当前深度大于前一个，说明是兄弟节点
					else if(deeph==preDeep)
					{
                        //childNode=childNode.Parent().AppendChild();
						childNode = mms_node_append_child2(childNode->pParent);
					}
					//当前深度小于前一个，说明时父辈节点的兄弟节点
					else
					{
						//获取父辈节点
						j=deeph;
						while(j<preDeep)
						{
							//pChildNode=pChildNode->pParent;
							childNode=childNode->pParent;
							j++;
						}
						//获取父辈节点的兄弟节点
                        //childNode=childNode.Parent().AppendChild();
						childNode = mms_node_append_child2(childNode->pParent);
					}
				}

				iRight=i;

				if (deeph==1)
				{
					childNode->type = DO_TYPE;
				}

				memset(strTemp,0,sizeof(strTemp));
				memcpy(strTemp,_pStrLine+iLeft+1,i-iLeft-1);
#ifdef _use_mms_string
				mms_str_set(&childNode->name, strTemp);
#else
				strcpy(childNode->name, strTemp);
#endif

				preDeep=deeph;

				iLeft=0;
				break;
			}
		case ',':
			{
				//获取数据类型
				if (iRight!=-1)
				{
					memset(strTemp,0,sizeof(strTemp));
					memcpy(strTemp,_pStrLine+iRight+1,i-iRight-1);
					//if(childNode->DataType, strTemp) == SD_FAILURE)
					//{
					//	SLOGALWAYS1("set the value type error,please add it!---%s",strTemp);
					//}
					Set_DATA_NODE_DataType(childNode, strTemp);
					preDeep=deeph;
				}
				iRight=-1;
				break;
			}
		}
	}

	return SD_SUCCESS;
}


/************************************************************************/
/*获取LN的访问属性                                                                      */
/************************************************************************/
ST_RET CMmsApi::GetLogicalNodeAttributte(ST_INT _iNetInfo,ST_CHAR *_pLDName,MMS_DATA_NODE* _LNNode, ST_INT nTypeDepp_1, ST_INT object_tag)
{
	ST_RET ret;
	MVL_REQ_PEND *reqCtrl=NULL;
	GETVAR_REQ_INFO getvar_req={0};
	ST_CHAR tmpDataType[100000];

	getvar_req.req_tag = GETVAR_NAME;
	getvar_req.name.object_tag = object_tag;//DOM_SPEC;
	getvar_req.name.domain_id=_pLDName;
	getvar_req.name.obj_name.item_id=mms_string(&_LNNode->name);

	MVL_NET_INFO *connectInfo=NULL;
	connectInfo = (MVL_NET_INFO*)(acsi_ctrl_table[_iNetInfo].pnet_info);

	ret = mvla_getvar (connectInfo, &getvar_req, &reqCtrl);
	if (ret == SD_SUCCESS)
		ret = waitReqDone (reqCtrl, g_timeOut, _iNetInfo);

	if (ret != SD_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "Error getting type of variable '%s' in domain '%s'",mms_string(&_LNNode->name), _pLDName);
	}
	else
	{
		ret = asn_type_to_local(reqCtrl->u.getvar.resp_info->type_spec.len, 
			reqCtrl->u.getvar.resp_info->type_spec.data, tmpDataType);

		//解析LN属性结构
		if (ret == SD_SUCCESS)
		{
			PharseLogicalNodeAttributte(tmpDataType,_LNNode);
		}
	}

	mvl_free_req_ctrl (reqCtrl);

	return SD_SUCCESS;
}

/************************************************************************/
/* 解析LN节点的属性                                                                     */
/************************************************************************/
ST_RET CMmsApi::PharseLogicalNodeAttributte(ST_CHAR *_pStrLine,MMS_DATA_NODE* _LNNode)
{
	ST_INT i,j,deeph,preDeep,iLeft,iRight;
	ST_CHAR ch;
	MMS_DATA_NODE* childNode;
	ST_CHAR strTemp[255];

	deeph=0;
	preDeep=0;

	for (i=0;i<strlen(_pStrLine);i++)
	{
		ch=_pStrLine[i];
		switch(ch)
		{
		case '{':
			{
				iRight=-1;
				deeph++;
				break;
			}
		case '}':
			{
				//获取DA数据类型
				if (iRight!=-1)
				{
					memset(strTemp,0,sizeof(strTemp));
					memcpy(strTemp,_pStrLine+iRight+1,i-iRight-1);
					Set_DATA_NODE_DataType(childNode, strTemp);
// 					if(childNode.SetValueType(strTemp) == SD_FAILURE)
// 					{
// 						SLOGALWAYS1("the value type error,please add it!---%s",strTemp);
// 					}

					preDeep=deeph;
				}
				iRight=-1;

				deeph--;
				break;
			}
		case '(':
			{
				iLeft=i;
				break;
			}
		case ')':
			{
				if (preDeep==0)
				{
					childNode = mms_node_append_child2(_LNNode);
                    //childNode=_LNNode.AppendChild();
				}
				else
				{
					//当前深度大于前一个，说明时子节点
					if (deeph>preDeep)
					{
                        //childNode=childNode.AppendChild();
						childNode = mms_node_append_child2(childNode);
					}
					//当前深度大于前一个，说明是兄弟节点
					else if(deeph==preDeep)
					{
                        //childNode=childNode.Parent().AppendChild();
						childNode = mms_node_append_child2(childNode->pParent);
					}
					//当前深度小于前一个，说明时父辈节点的兄弟节点
					else
					{
						//获取父辈节点
						j=deeph;
						while(j<preDeep)
						{
							childNode=childNode->pParent;
							//childNode=childNode.Parent();
							j++;
						}
						//获取父辈节点的兄弟节点
                        //childNode=childNode.Parent().AppendChild();
						childNode = mms_node_append_child2(childNode->pParent);
					}
				}

				iRight=i;
				if (deeph==1)
				{
					childNode->type = FC_TYPE;
				}

				memset(strTemp,0,sizeof(strTemp));
				memcpy(strTemp,_pStrLine+iLeft+1,i-iLeft-1);
				//childNode.SetName(strTemp);
#ifdef _use_mms_string
				mms_str_set(&childNode->name, strTemp);
#else
				strcpy(childNode->name, strTemp);
#endif

				preDeep=deeph;
				iLeft=0;

				break;
			}
		case ',':
			{
				//获取数据类型
				if (iRight!=-1)
				{
					memset(strTemp,0,sizeof(strTemp));
					memcpy(strTemp,_pStrLine+iRight+1,i-iRight-1);
					Set_DATA_NODE_DataType(childNode, strTemp);;
// 					if(childNode.SetValueType(strTemp) != SD_SUCCESS)
// 					{
// 						SLOGALWAYS1("set the value type error,please add it!---%s",strTemp);
// 					}
					preDeep=deeph;
				}
				iRight=-1;
				break;
			}
		}
	}

	return SD_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////

BOOL check_rptid_Ldname_rcbname(char *pszRptID, char *pszLdName, char *pszRcbName)
{
	char *pTemp = pszRptID;
	char strRcbTemp[NAMESIZE];
	char *pEnd = pszRptID + strlen(pszRptID);
	char *p = strRcbTemp;

	while (*pTemp != 0)
	{
		*p = *pTemp;

		if (*pTemp == '/')
		{
			*p = 0;
			pTemp++;
			break;
		}

		pTemp++;
		p++;
	}

	if (strstr(pszLdName, strRcbTemp) == NULL)
	{
		return FALSE;
	}

//	if (strstr(pszRptID, pszRcbName) == NULL)
	if (strstr(pszRcbName, pTemp) == NULL)//zhow20180109
	{//忽略最后的数字  2018-3-21
		return FALSE;
	}

	return TRUE;
}

// 2013-4-10  获取报告控制块
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::get_ReportCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class, ST_BOOLEAN bBR, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::get_ReportCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class, ST_BOOLEAN bBR)
#endif
{
	ST_RET ret;
	ST_RET ret2;
	MVL_NET_INFO *netInfo;
	NAMELIST_REQ_INFO getnam_req;
	NAMELIST_RESP_INFO *getnam_resp;
	MVL_REQ_PEND *reqCtrl;
	ST_CHAR **nptr;
	ST_INT i=0;
	ST_INT k=0;
	ST_INT j=0;
	ST_INT Type_id=-1;
	tagValueX xValue;
	tagValueX xRptID;
	ST_CHAR rcbVar[NAMESIZE];
	ST_CHAR ar_nptr[4096][NAMESIZE];
	ZeroMemory(ar_nptr, 4096*NAMESIZE*sizeof(ST_CHAR));
	ZeroMemory(&xRptID, sizeof(tagValue));


	/*可以获取LD下所有逻辑节点、数据、数据集的变量名*/
	netInfo = (MVL_NET_INFO *)acsi_ctrl_table[nACSI].pnet_info;
	acsi_ctrl_table[nACSI].CMD = CMD_DIR;
	acsi_ctrl_table[nACSI].needDirectory = SD_FALSE;
	acsi_ctrl_table[nACSI].g_timeOut = 0;

	strncpy(getnam_req.dname, pLD->LDName, NAMESIZE-1);

	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = mms_class; // Named Variable
	getnam_req.objscope = DOM_SPEC;
	getnam_req.cont_after_pres = SD_TRUE;//SD_FALSE;

	if (bBR)
		strcpy(getnam_req.continue_after,"LLN0$BR");
	else
		strcpy(getnam_req.continue_after,"LLN0$RP");

	do
	{
		ret = mvla_getnam (netInfo, &getnam_req, &reqCtrl);
		if( ret == SD_SUCCESS )
			ret = waitReqDone (reqCtrl, g_timeOut, netInfo->nACSI);
		else
		{
			mvl_free_req_ctrl (reqCtrl);
			break;
		}

		if (ret != SD_SUCCESS)
		{
			mvl_free_req_ctrl (reqCtrl);
			break;
		}
		else
		{
			getnam_resp = (NAMELIST_RESP_INFO *) reqCtrl->u.ident.resp_info;
			nptr = (ST_CHAR **) (getnam_resp + 1);
			ST_INT num = getnam_resp->num_names;

			for (i=0; i<num; i++)
			{
				if (i>=4096)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "%s (num=%d)>=4096", getnam_req.continue_after,num);
					break;
				}
				strcpy(ar_nptr[i], nptr[i]);
			}

			for (i=0; i<num; i++)
			{
				if (i>=4096)
				{
					break;
				}
				k = ClarifymmsVarName(ar_nptr[i]);

				if (k == 0) /*判LN*/
				{
				}
				else if(k == 1)
				{
				}
				else if(k == 2)
				{
					if (strstr(ar_nptr[i], "$BR$") || strstr(ar_nptr[i], "$RP$"))
					{
						if (ar_nptr[0]!=0)
						{
							ZeroMemory(rcbVar,NAMESIZE);
							_snprintf(rcbVar,NAMESIZE,"%s$DatSet",ar_nptr[i]); 
#ifdef _MVL_TYPE_CTRL_use_one_device_
							if (get_varType(netInfo, pLD->LDName, &Type_id, rcbVar, mvl_type_ctrl) == SD_SUCCESS)
#else
							if (get_varType(netInfo, pLD->LDName, &Type_id, rcbVar) == SD_SUCCESS)
#endif
								ret = get_varvalue(netInfo, rcbVar, pLD->LDName, Type_id, &xValue, 1);

#ifdef _MVL_TYPE_CTRL_use_one_device_
							mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
							mvl_type_id_destroy(Type_id);
#endif

							_snprintf(rcbVar,NAMESIZE,"%s$RptID",ar_nptr[i]); 
#ifdef _MVL_TYPE_CTRL_use_one_device_
							if (get_varType(netInfo, pLD->LDName, &Type_id, rcbVar, mvl_type_ctrl) == SD_SUCCESS)
#else
							if (get_varType(netInfo, pLD->LDName, &Type_id, rcbVar) == SD_SUCCESS)
#endif
								ret2 = get_varvalue(netInfo, rcbVar, pLD->LDName, Type_id, &xRptID, 1);

#ifdef _MVL_TYPE_CTRL_use_one_device_
							mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
							mvl_type_id_destroy(Type_id);
#endif

							if (ret2 != SD_SUCCESS)
							{
								xRptID.string[0] = 0;
							}

							if (ret==SD_SUCCESS)
							{
								CString strName(xValue.string);

								//TRACE("%s\r\n", strName);
								for (j=0; j<pLD->numDaSet; j++)
								{
									//if (strName.Find(pLD->DataInfo[j].DataSetID)!=-1)
									long nLen = strlen(pLD->DataInfo[j].DataSetID);
									if (strName.Right(nLen) == pLD->DataInfo[j].DataSetID 
										|| strName.Left(nLen) == pLD->DataInfo[j].DataSetID)
									{
										int index = pLD->DataInfo[j].numRcb;
									
										if (index<MAX_RCB_VMD && index>=0)
										{
											//CString strText(ar_nptr[i]);
											strcpy(pLD->DataInfo[j].RCB[index].rcbName, ar_nptr[i]); 

											if (ret2 == SD_SUCCESS)
											{
#ifdef _use_mms_string
												strcpy(pLD->DataInfo[j].RCB[index].RptID, xRptID.string); 
												if (! check_rptid_Ldname_rcbname(xRptID.string, pLD->LDName, ar_nptr[i]) )
#else
												strcpy(pLD->DataInfo[j].RCB[index].RptID, vRptID.string); 
												if (! check_rptid_Ldname_rcbname(vRptID.string,pLD->LDName, ar_nptr[i]) )
#endif
												{
													CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "RptID[%s]!=rcbName[%s]", xRptID.string, ar_nptr[i]);
												}
											}
											
											pLD->DataInfo[j].numRcb++;
											
											///TRACE("Find %s - %s %d \r\n", strText, pLD->DataInfo[j].DaSetName, pLD->DataInfo[j].numRcb);
										}
									}
								}
							}
						}
					}
				}  
			}

			if (getnam_resp->more_follows)
			{
				getnam_req.cont_after_pres = SD_TRUE;
				strcpy(getnam_req.continue_after,ar_nptr[i-1]);
			}

			mvl_free_req_ctrl (reqCtrl);
		}
	}while(getnam_resp->more_follows);

	return ret;
}

// 2018-1-17  获取日志控制块 zhouhj
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::get_LogCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::get_LogCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class)
#endif
{
	ST_RET ret;
	ST_RET ret2;
	MVL_NET_INFO *netInfo;
	NAMELIST_REQ_INFO getnam_req;
	NAMELIST_RESP_INFO *getnam_resp;
	MVL_REQ_PEND *reqCtrl;
	ST_CHAR **nptr;
	ST_INT i=0;
	ST_INT k=0;
	ST_INT j=0;
	ST_INT Type_id=-1;
	tagValueX xValue;
	tagValueX xLogName;
	ST_CHAR lcbVar[NAMESIZE];
	ST_CHAR ar_nptr[4096][NAMESIZE];
	ZeroMemory(ar_nptr, 4096*NAMESIZE*sizeof(ST_CHAR));
	ZeroMemory(&xLogName, sizeof(tagValue));


	/*可以获取LD下所有逻辑节点、数据、数据集的变量名*/
	netInfo = (MVL_NET_INFO *)acsi_ctrl_table[nACSI].pnet_info;
	acsi_ctrl_table[nACSI].CMD = CMD_DIR;
	acsi_ctrl_table[nACSI].needDirectory = SD_FALSE;
	acsi_ctrl_table[nACSI].g_timeOut = 0;

	strncpy(getnam_req.dname, pLD->LDName, NAMESIZE-1);
	strncpy(pLD->JournalCtrls.Desc, pLD->LDName, NAMESIZE-1);

	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = mms_class; // Named Variable
	getnam_req.objscope = DOM_SPEC;
	getnam_req.cont_after_pres = SD_TRUE;//SD_FALSE;

	strcpy(getnam_req.continue_after,"LLN0$LG");

	do
	{
		ret = mvla_getnam (netInfo, &getnam_req, &reqCtrl);
		if( ret == SD_SUCCESS )
			ret = waitReqDone (reqCtrl, g_timeOut, netInfo->nACSI);
		else
		{
			mvl_free_req_ctrl (reqCtrl);
			break;
		}

		if (ret != SD_SUCCESS)
		{
			mvl_free_req_ctrl (reqCtrl);
			break;
		}
		else
		{
			getnam_resp = (NAMELIST_RESP_INFO *) reqCtrl->u.ident.resp_info;
			nptr = (ST_CHAR **) (getnam_resp + 1);
			ST_INT num = getnam_resp->num_names;

			for (i=0; i<num; i++)
			{
				if (i>=4096)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "%s (num=%d)>=4096", getnam_req.continue_after,num);
					break;
				}
				strcpy(ar_nptr[i], nptr[i]);
			}

			for (i=0; i<num; i++)
			{
				if (i>=4096)
				{
					break;
				}
				k = ClarifymmsVarName(ar_nptr[i]);

				if (k == 0) /*判LN*/
				{
				}
				else if(k == 1)
				{
				}
				else if(k == 2)
				{
					if (strstr(ar_nptr[i], "$LG$"))
					{
						if (ar_nptr[0]!=0)
						{
							ZeroMemory(lcbVar,NAMESIZE);
							_snprintf(lcbVar,NAMESIZE,"%s$DatSet",ar_nptr[i]); 
#ifdef _MVL_TYPE_CTRL_use_one_device_
							if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar, mvl_type_ctrl) == SD_SUCCESS)
								ret = get_varvalue(netInfo, lcbVar, pLD->LDName, Type_id, &xValue, 1);
							mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
							if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar) == SD_SUCCESS)
								ret = get_varvalue(netInfo, lcbVar, pLD->LDName, Type_id, &xValue, 1);
							mvl_type_id_destroy(Type_id);
#endif

							_snprintf(lcbVar,NAMESIZE,"%s$LogRef",ar_nptr[i]); 

#ifdef _MVL_TYPE_CTRL_use_one_device_
							if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar, mvl_type_ctrl) == SD_SUCCESS)
								ret2 = get_varvalue(netInfo, lcbVar, pLD->LDName, Type_id, &xLogName, 1);
							mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
							if (get_varType(netInfo, pLD->LDName, &Type_id, lcbVar) == SD_SUCCESS)
								ret2 = get_varvalue(netInfo, lcbVar, pLD->LDName, Type_id, &xLogName, 1);
							mvl_type_id_destroy(Type_id);
#endif

							if (ret2 != SD_SUCCESS)
							{
								xLogName.string[0] = 0;
							}

							if (ret==SD_SUCCESS)
							{
								CString strName(xValue.string);

								//TRACE("%s\r\n", strName);
								for (j=0; j<pLD->numDaSet; j++)
								{
									//if (strName.Find(pLD->DataInfo[j].DataSetID)!=-1)
									long nLen = strlen(pLD->DataInfo[j].DataSetID);
									if (strName.Right(nLen) == pLD->DataInfo[j].DataSetID 
										|| strName.Left(nLen) == pLD->DataInfo[j].DataSetID)
									{
										if (pLD->JournalCtrls.LogInfo != NULL)
										{
											mms_str_assign(&pLD->JournalCtrls.LogInfo[j].Name, ar_nptr[i]); 
											
											if (ret2 == SD_SUCCESS)
											{
												mms_str_assign((&pLD->JournalCtrls.LogInfo[j].logRef) , xLogName.string);
											} 
										}
									}
								}
							}
						}
					}
				}  
			}

			if (getnam_resp->more_follows)
			{
				getnam_req.cont_after_pres = SD_TRUE;
				strcpy(getnam_req.continue_after,ar_nptr[i-1]);
			}

			mvl_free_req_ctrl (reqCtrl);
		}
	}while(getnam_resp->more_follows);

	return ret;
}
// 
// // 2013-4-10  获取报告控制块
// ST_RET CMmsApi::get_JournalCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class)
// {
// 	ST_RET ret;
// 	ST_RET ret2;
// 	MVL_NET_INFO *netInfo;
// // 	NAMELIST_REQ_INFO getnam_req;
// // 	NAMELIST_RESP_INFO *getnam_resp;
// 	MVL_REQ_PEND *reqCtrl;
// 	ST_CHAR **nptr;
// 	ST_INT i=0;
// 	ST_INT k=0;
// 	ST_INT j=0;
// 	ST_INT Type_id=-1;
// 	tagValue Value;
// 	tagValue vRptID;
// 	ST_CHAR rcbVar[NAMESIZE];
// 	ST_CHAR ar_nptr[4096][NAMESIZE];
// 	ZeroMemory(ar_nptr, 4096*NAMESIZE*sizeof(ST_CHAR));
// 	ZeroMemory(&vRptID, sizeof(tagValue));
// 
// 	READ_REQ_INFO read_req_info;
// 	READ_RESP_INFO *read_resp_info;
// 
// 
// 	/*可以获取LD下所有逻辑节点、数据、数据集的变量名*/
// 	netInfo = (MVL_NET_INFO *)acsi_ctrl_table[nACSI].pnet_info;
// 	acsi_ctrl_table[nACSI].CMD = CMD_DIR;
// 	acsi_ctrl_table[nACSI].needDirectory = SD_FALSE;
// 	acsi_ctrl_table[nACSI].timeOut = 0;
// 
// 	read_req_info.va_spec.vl_name.object_tag = DOM_SPEC;
// 	strncpy(read_req_info.va_spec.vl_name.domain_id, pLD->LDName, NAMESIZE-1);
// 	strncpy(read_req_info.va_spec.vl_name.obj_name.item_id, "LLN0$LG", NAMESIZE-1);
// 
// 	read_req_info.spec_in_result = SD_TRUE;
// 
// 	ret = mvl_read_variables (netInfo, &read_req_info, &reqCtrl);
// 	if( ret == SD_SUCCESS )
// 		ret = waitReqDone (reqCtrl, timeOut, netInfo->nACSI);
// 	else
// 	{
// 		mvl_free_req_ctrl (reqCtrl);
// 		return SD_FALSE;
// 	}
// 
// 	read_resp_info = (READ_RESP_INFO *) reqCtrl->u.ident.resp_info;
// 	nptr = (ST_CHAR **) (read_resp_info + 1);
// 	ST_INT num = read_resp_info->num_of_acc_result;
// 
// 	mvl_free_req_ctrl (reqCtrl);
// 
// 	return ret;
// }
// 


// 2013-4-10  获取日志控制块
ST_RET CMmsApi::get_JournalCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class)
{
	ST_RET ret;
//	ST_RET ret2;
	MVL_NET_INFO *netInfo;
	NAMELIST_REQ_INFO getnam_req;
	NAMELIST_RESP_INFO *getnam_resp;
	MVL_REQ_PEND *reqCtrl;
	ST_CHAR **nptr;
	ST_INT i=0;
	ST_INT k=0;
	ST_INT j=0;
	ST_INT Type_id=-1;
//	tagValue Value;
	tagValue vRptID;
//	ST_CHAR rcbVar[NAMESIZE];
	ST_CHAR ar_nptr[4096][NAMESIZE];
	ZeroMemory(ar_nptr, 4096*NAMESIZE*sizeof(ST_CHAR));
	ZeroMemory(&vRptID, sizeof(tagValue));


	/*可以获取LD下所有逻辑节点、数据、数据集的变量名*/
	netInfo = (MVL_NET_INFO *)acsi_ctrl_table[nACSI].pnet_info;
	acsi_ctrl_table[nACSI].CMD = CMD_DIR;
	acsi_ctrl_table[nACSI].needDirectory = SD_FALSE;
	acsi_ctrl_table[nACSI].g_timeOut = 0;

	strncpy(getnam_req.dname, pLD->LDName, NAMESIZE-1);

	getnam_req.cs_objclass_pres = SD_FALSE;
	getnam_req.obj.mms_class = MMS_CLASS_VARLIST; // Named Variable
	getnam_req.objscope = DOM_SPEC;
	getnam_req.cont_after_pres = SD_FALSE;//SD_TRUE;//SD_FALSE;

	strcpy(getnam_req.continue_after,"LLN0$LG");

	do
	{
		ret = mvla_getnam (netInfo, &getnam_req, &reqCtrl);
		if( ret == SD_SUCCESS )
			ret = waitReqDone (reqCtrl, g_timeOut, netInfo->nACSI);
		else
		{
			mvl_free_req_ctrl (reqCtrl);
			break;
		}

		if (ret != SD_SUCCESS)
		{
			mvl_free_req_ctrl (reqCtrl);
			break;
		}
		else
		{
			getnam_resp = (NAMELIST_RESP_INFO *) reqCtrl->u.ident.resp_info;
			nptr = (ST_CHAR **) (getnam_resp + 1);
			ST_INT num = getnam_resp->num_names;

			for (i=0; i<num; i++)
			{
				if (i>=4096)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, "%s (num=%d)>=4096", getnam_req.continue_after,num);
					break;
				}
				strcpy(ar_nptr[i], nptr[i]);
			}

			for (i=0; i<num; i++)
			{
				if (i>=4096)
				{
					break;
				}
				k = ClarifymmsVarName(ar_nptr[i]);

				if (k == 0) /*判LN*/
				{
				}
				else if(k == 1)
				{
				}
				else if(k == 2)
				{
					if (strstr(ar_nptr[i], "$LG$") )
					{
						if (ar_nptr[0]!=0)
						{
						}
					}
				}  
			}

			if (getnam_resp->more_follows)
			{
				getnam_req.cont_after_pres = SD_TRUE;
				strcpy(getnam_req.continue_after,ar_nptr[i-1]);
			}

			mvl_free_req_ctrl (reqCtrl);
		}
	}while(getnam_resp->more_follows);

	return ret;
}


ST_INT CMmsApi::ClarifymmsVarName(ST_CHAR *mmsVarName)
{
	ST_CHAR	*pstr;
	ST_INT count;
	count = 0;
	pstr = mmsVarName;

// 	for(;;)
// 	{
// 		pstr = strchr(pstr, '$');
// 		if(NULL == pstr)
// 			break;
// 		pstr++;
// 		count++;
// 	}

	while (*pstr != 0)
	{
		if (*pstr == '$')
		{
			count++;
		}

		pstr++;
	}

	return  count;
}

/* 2012-10-09  读取数据 */
ST_RET CMmsApi::MMS_ReadData(CFuncParamEx *pFuncParaEx)
{
	ST_INT ret;
	ST_INT k;
	ST_INT nDaNum = 0;
	ST_INT Type_id = 0;
	ST_INT nLen;
	ST_INT i = 0;
	tagDA *pDA=NULL;
	ST_INT nDsIndex;
	BOOL bHasUnit = FALSE;
	BOOL bHasMinMax = FALSE;
	BOOL bHasStepSize = FALSE;
	ACSI_NODE *pDevice = &pACSINode[pFuncParaEx->get_DevIndex()];

	nDsIndex = pFuncParaEx->get_DSID();

	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	if (!netInfo)
		return SD_FAILURE;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return SD_FAILURE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	nDaNum = pLD_INFO->numData;
	CStringA strText(pLD_INFO->DataSetID);

	if ((strText == dsDout)&&(!g_bUseDsDout))
	{
		return SD_SUCCESS;  //zhouhj20180606 解决dsDout中读取数据失败的问题
	}

	bHasUnit = HasUnit(pLD_INFO->DataSetID);
	bHasMinMax = HasMinMax(pLD_INFO->DataSetID);
	bHasStepSize = HasStepSize(pLD_INFO->DataSetID);

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->SetMaxRange(nDaNum);
	}

	for (k=0; k<nDaNum; k++)
	{
		if (pFuncParaEx->NeedExitFunc())
		{
			break;
		}

		Type_id = 0;

		if (pFuncParaEx != NULL)
		{
			pFuncParaEx->StepIt();
			CString strMsg;
			strMsg.Format(g_sLangTxt_IndexAndTotal, k+1, nDaNum);//_T("第%d个  共%d个")
			pFuncParaEx->ShowMsg(strMsg);
		}

		get_MMStagDAObj(nDsIndex, k, pLD_INFO, &pDA);
		if (pDA == NULL)
			continue;

		// 读取数值 2012-12-17  读取装置数据
		//////////////////////////////////////////////////////////////////////////
#ifdef _use_mms_string
		nLen = mms_str_length(&pDA->DAValue.mmsName);
#else
		nLen = strlen(pDA->DAValue.mmsName);
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
		if (get_tagDAData(netInfo, pLD->LDName, pDA, pDevice->p_mvl_type_ctrl)!=SD_SUCCESS)
#else
		if (get_tagDAData(netInfo, pLD->LDName, pDA)!=SD_SUCCESS)
#endif
		{
			continue;
		}

		if (m_bOnlyReadValue)
		{
			continue;
		}

		// 读取描述
		//////////////////////////////////////////////////////////////////////////
		if (!pLD_INFO->bHasEnum)//zhouhj 20210423 在没有枚举模型的情况下需要去读取描述
		{
			ret = SD_FAILURE;
#ifdef _MVL_TYPE_CTRL_use_one_device_
			ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl, VAR_DESC_NAME_KIND_FULL);
#else
			ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_FULL);
#endif

			if (ret!=SD_SUCCESS)
			{
#ifdef _MVL_TYPE_CTRL_use_one_device_
				ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl, VAR_DESC_NAME_KIND_REMOVE_VALID);
#else
				ret = get_DataDescInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_REMOVE_VALID);
#endif
			}
		}

		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("    3****0x%08X"), (DWORD)pDA);

		// 读取单位
		//////////////////////////////////////////////////////////////////////////	
		//if (pDA->bUnite==SD_FALSE)
		if (bHasUnit)
		{
			ret = SD_FAILURE;
#ifdef _MVL_TYPE_CTRL_use_one_device_
			ret = get_DataUniteInfo(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl, VAR_DESC_NAME_KIND_REMOVE_VALID);
#else
			ret = get_DataUniteInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_REMOVE_VALID);
#endif

			if (ret!=SD_SUCCESS)
			{
				ret = get_DataUniteInfo(netInfo, pLD->LDName, nLen, pDA, VAR_DESC_NAME_KIND_FULL);
			}
		}

		// 2013-4-16  读取最大值、最小值、步长
		//////////////////////////////////////////////////////////////////////////	
		if (bHasMinMax)
		{
#ifdef _MVL_TYPE_CTRL_use_one_device_
			ret = get_DataLimitValInfoAll(netInfo, pLD->LDName, nLen, pDA, pDevice->p_mvl_type_ctrl);
#else
			ret = get_DataLimitValInfoAll(netInfo, pLD->LDName, nLen, pDA);
#endif
		}

		if (bHasStepSize)
		{
			ret = get_DataStepSizeInfo(netInfo, pLD->LDName, nLen, pDA);
		}
	}	

	pLD_INFO->bHasEnum = SD_TRUE;

	return SD_SUCCESS;
}

ST_RET CMmsApi::MMS_ReadOneData(CFuncParamEx *pFuncParaEx)
{
	ST_INT ret;
	ST_INT k;
	ST_INT nDaNum = 0;
	ST_INT Type_id = 0;
	ST_INT nLen;
	ST_INT i = 0;
	tagDA *pDA=NULL;
	ST_INT nDsIndex;
	ST_INT nDataIndex;
	BOOL bHasUnit = FALSE;
	BOOL bHasMinMax = FALSE;
	BOOL bHasStepSize = FALSE;
	ACSI_NODE *pDevice = &pACSINode[pFuncParaEx->get_DevIndex()];

	nDsIndex = pFuncParaEx->get_DSID();
	nDataIndex = pFuncParaEx->get_DaIndex1();

	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	if (!netInfo)
		return SD_FAILURE;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return SD_FAILURE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	nDaNum = pLD_INFO->numData;
	CStringA strText(pLD_INFO->DataSetID);

	bHasUnit = HasUnit(pLD_INFO->DataSetID);
	bHasMinMax = HasMinMax(pLD_INFO->DataSetID);
	bHasStepSize = HasStepSize(pLD_INFO->DataSetID);

	nDaNum = 1;

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->SetMaxRange(nDaNum);
	}

	Type_id = 0;
	k = 0;

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->StepIt();
		CString strMsg;
		strMsg.Format(g_sLangTxt_IndexAndTotal, k+1, nDaNum);//_T("第%d个  共%d个")
		pFuncParaEx->ShowMsg(strMsg);
	}

	get_MMStagDAObj(nDsIndex, nDataIndex, pLD_INFO, &pDA);
	if (pDA == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadOneData:DV=%d  LD=%d DS=%d DA=%d  Error")
			, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex1());
		return SD_FAILURE;
	}

	// 读取数值 读取装置数据
#ifdef _use_mms_string
	nLen = mms_str_length(&pDA->DAValue.mmsName);
#else
	nLen = strlen(pDA->DAValue.mmsName);
#endif
	m_bOnlyReadValue = TRUE;

#ifdef _MVL_TYPE_CTRL_use_one_device_
	ret = get_tagDAData(netInfo, pLD->LDName, pDA, pDevice->p_mvl_type_ctrl);
#else
	ret = get_tagDAData(netInfo, pLD->LDName, pDA);
#endif

	if (ret != SD_SUCCESS )
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadOneData[%s]:DV=%d  LD=%d DS=%d DA=%d  Error")
			, pDA->DAValue.mmsName, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex1());
	}

	return ret;
}

ST_RET CMmsApi::MMS_ReadDataSetting(CFuncParamEx *pFuncParaEx)
{
	ST_INT ret;
	ST_INT k;
	ST_INT nDaNum = 0;
	ST_INT Type_id = 0;
	ST_INT i = 0;
	tagDA *pDA=NULL;
	ST_INT nDsIndex;
	ST_BOOLEAN bSE = FALSE;
	CGpsPcTimeTickCount  oTickCount32;
	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;

	nDsIndex = pFuncParaEx->get_DSID();

	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	if (!netInfo)
		return SD_FAILURE;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	
	if (!pLD)
		return SD_FAILURE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	nDaNum = pLD_INFO->numData;

	//不是定值数据集
	//if (_stricmp(dsSetting, pLD_INFO->DataSetID) != 0)
	if (strstr(pLD_INFO->DataSetID, dsSetting) == NULL)
		return SD_FAILURE;

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->SetMaxRange(nDaNum);
	}

	ST_INT nSG = pFuncParaEx->get_SGID();
	ST_INT nSE = pFuncParaEx->get_SEID();

// 	if (g_theMmsEngineRpcMngr == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MMS_ReadDataSetting:SG=%d  SE=%d"), nSG, nSE);
// 	}

	if (nSE == 0)
	{
		nSE = nSG;
	}

	if (nSG != nSE)
	{
		acsi_ctrl_table[i].idleCount = 0;
		ret = MMS_SetEditSG(pFuncParaEx,nSE);
	
		if (ret == SD_FAILURE)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , g_sLangTxt_SetEdtZnFail.GetString()/*_T("读定值区%d时，切换编辑区失败【运行区=%d】")*/
				, nSE, nSG);
		}
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , g_sLangTxt_SetEdtZnRd.GetString()/*_T("读定值区%d时，切换编辑区【运行区=%d】")*/
				, nSE, nSG);
			bSE = TRUE;
		}

		if (pFuncParaEx != NULL)
		{
			pFuncParaEx->ShowMsg(_T("Wait 1000 ms"));
			pFuncParaEx->StartTimer(1000);
		}
	
		Sleep(1000);
	}

// 	if (g_theMmsEngineRpcMngr == NULL)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("MMS_ReadDataSetting:SG=%d  SE=%d"), nSG, nSE);
// 	}

	for (k=0; k<nDaNum; k++)
	{
		if (pFuncParaEx->NeedExitFunc())
		{
			break;
		}

		Type_id = 0;

		if (pFuncParaEx != NULL)
		{
			pFuncParaEx->StepIt();
			CString strMsg;
			strMsg.Format(g_sLangTxt_IndexAndTotal/*_T("第%d个  共%d个")*/, k+1, nDaNum);
			pFuncParaEx->ShowMsg(strMsg);
		}

		get_MMStagDAObj(nDsIndex, k, pLD_INFO, &pDA);
		if (pDA == NULL)
			continue;

		oTickCount32.Enter();
		ret = get_tagDAData_Set(netInfo, pLD->LDName, pDA, bSE);
		ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
		pDevice->tmTotal += oTickCount32.GetTickCountLong(TRUE);

		if (ret != SD_SUCCESS)
		{
			break;
		}
	}	

	return ret;
}

void CMmsApi::get_all_subdir(ST_INT nDvIndex,XMMS_FILE_SYS_OBJ *pTagFileDir, CFuncParamEx *pFuncParaEx,BOOL bOnlyReadCfg)
{
	if (pTagFileDir == NULL)
		return;

	XMMS_FILE_SYS_OBJ *pSubFileDir = NULL;
	int nIndex = 0;
	CString strPath;
	char *pszPath = NULL;

	for(nIndex = 0;nIndex<pTagFileDir->subFiles.numOfData;nIndex++)
	{
		if (pFuncParaEx->NeedExitFunc())
		{
			break;
		}

		pSubFileDir = (XMMS_FILE_SYS_OBJ *)*(pTagFileDir->subFiles.Datas + nIndex);

		if (pSubFileDir->nType == 1)
		{
			strPath = get_all_filedir_path(pSubFileDir);
			CString_to_char(strPath,&pszPath);
			get_dir(nDvIndex, pszPath/*mms_string(&pSubFileDir->filedir.filename)*/,pSubFileDir,bOnlyReadCfg);
			get_all_subdir(nDvIndex,pSubFileDir, pFuncParaEx,bOnlyReadCfg);

			delete pszPath;
			pszPath = NULL;
		}
	}

}

CString CMmsApi::find_dataset_by_valuepath(LD_NODE *pLD,char *pLogValuePath)
{
	CString strDatasetName,strSourPath,strDestPath;
	if (pLD == NULL)
	{
		return strDatasetName;
	}

	LD_DATASET_INFO *pDatasetInfo = NULL;
	tagDA* pTagDA = NULL;
	int nIndex,nIndex2;
	strDestPath = pLogValuePath;
	nIndex = strDestPath.Find('/');
	if (nIndex != -1)
	{
		strDestPath = strDestPath.Mid(nIndex+1);
	}

	for (nIndex = 0;nIndex<pLD->numDaSet;nIndex++)
	{
		pDatasetInfo = &pLD->DataInfo[nIndex];

		for (nIndex2 = 0;nIndex2<pDatasetInfo->numData;nIndex2++)
		{
			pTagDA = &pDatasetInfo->DataSet[nIndex2];
			strSourPath = mms_string(&pTagDA->DAValue.mmsName);

			if (strSourPath.Find(strDestPath) != -1)
			{
				strDatasetName = pDatasetInfo->DataSetID;
				return strDatasetName;
			}
		}
	}

	return strDatasetName;
}

ST_RET CMmsApi::MMS_ReadDir(CFuncParamEx *pFuncParaEx)
{
	ST_INT nDvIndex;
	CGpsPcTimeTickCount  oTickCount32;

	oTickCount32.Enter();
	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
	XMMS_FILE_SYS_OBJ *pTagFileDir = &pDevice->FileDir;


	if (pTagFileDir->subFiles.numOfData > 0)
	{
		pTagFileDir->bFirstRead = FALSE;
	}

	CString strDir,strTmp;
	strDir = pFuncParaEx->get_Path();
	long nOnlyReadCfg = pFuncParaEx->get_DaIndex2();
	BOOL bMark = check_prefix_and_suffix(strDir,strTmp);//此函数检查路径中是否包含按时间段查找的前缀或按最新文件数查找的后缀，含有返回1，不包含返回0，将去除前缀、后缀后的文件路径返回给参数2
	strDir = strTmp;
	strTmp = mms_string(&pTagFileDir->filedir.filename);

	if ((strTmp != strDir)||(bMark))//文件查找路径变更后，清空源文件记录
	{
		mms_file_sys_free(&pDevice->FileDir);
		mms_str_init(&pTagFileDir->filedir.filename);
        mms_str_set(&pTagFileDir->filedir.filename,strDir.GetString());
	}

	pDevice->nRecordFileTotalNum = 0;//将文件总数改为020200812
	nDvIndex = pFuncParaEx->get_DevIndex();
	get_dir(nDvIndex, pFuncParaEx->get_Path()/*_T("")*/,pTagFileDir/*m_FuncParam.get_Path()*/,(nOnlyReadCfg == 1));
	get_all_subdir(nDvIndex,pTagFileDir, pFuncParaEx,(nOnlyReadCfg == 1));
//	XMMS_FILE_SYS_OBJ *pSubDir = NULL;
// 	CString strNewPath ,strTmp;
// 	ASSERT(pTagFileDir->subFiles.numOfData != 0);
//	int nIndex = pTagFileDir->subFiles.numOfData;
//	strTmp = m_FuncParam.get_Path();

// 	for(int nLenth = 0;nLenth < nIndex;nLenth++)
// 	{
// 		if (!strTmp.IsEmpty())
// 		{
// 			pSubDir = (PXMMS_FILE_SYS_OBJ)(*(pTagFileDir->subFiles.Datas + nLenth));
// 			if (strstr(strTmp,mms_string(&pSubDir->filedir.filename)) == NULL)
// 			{
// 				strNewPath = strTmp + mms_string(&pSubDir->filedir.filename)/*pTagFileDir->dir[nLenth].filename*/;
// 				strcpy(mms_string(&pSubDir->filedir.filename) ,strNewPath);
// 			}
// 		}
// 	}//zhow:20180109 部分装置的filename为全路径，部分厂家装置仅为文件或文件夹名称，为了兼容两者增加

	pDevice->tmTotal = oTickCount32.GetTickCountLong();
	pDevice->nRecordFileTotalNum = Global_GetSysObjFileNum_CurDir(pTagFileDir);

	return SD_SUCCESS;
}

ST_RET CMmsApi::MMS_ReadFile(CFuncParamEx *pFuncParaEx)
{
	ST_INT nDvIndex;
	CGpsPcTimeTickCount  oTickCount32;

	oTickCount32.Enter();
	nDvIndex = pFuncParaEx->get_DevIndex();
	//get_dir(nDvIndex, "/COMTRADE/", "d:\\Dir.txt");
	get_file(nDvIndex, pFuncParaEx->get_FileName(), pFuncParaEx->get_Path());
	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
	pDevice->tmTotal = oTickCount32.GetTickCountLong();

	return SD_SUCCESS;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::get_DataLimitValInfoAll(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl
										,ST_INT nAinKind, ST_INT nLevel, ST_INT nKind)
#else
ST_RET CMmsApi::get_DataLimitValInfoAll(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA
										,ST_INT nAinKind, ST_INT nLevel, ST_INT nKind)
#endif
{
	ST_RET ret = 0;

	//max value
#ifdef _MVL_TYPE_CTRL_use_one_device_
	ret = get_DataLimitValInfo(netInfo, pLDName, nLen, pDA, mvl_type_ctrl, VAR_DESC_NAME_KIND_REMOVE_VALID, 0, 0);
#else
	ret = get_DataLimitValInfo(netInfo, pLDName, nLen, pDA, VAR_DESC_NAME_KIND_REMOVE_VALID, 0, 0);
#endif

	if (ret!=SD_SUCCESS)
	{
		ret = get_DataLimitValInfo(netInfo, pLDName, nLen, pDA, VAR_DESC_NAME_KIND_FULL, 0, 0);
	}

	//min value
#ifdef _MVL_TYPE_CTRL_use_one_device_
	ret = get_DataLimitValInfo(netInfo, pLDName, nLen, pDA, mvl_type_ctrl, VAR_DESC_NAME_KIND_REMOVE_VALID, 0, 1);
#else
	ret = get_DataLimitValInfo(netInfo, pLDName, nLen, pDA, VAR_DESC_NAME_KIND_REMOVE_VALID, 0, 1);
#endif

	if (ret!=SD_SUCCESS)
	{
		ret = get_DataLimitValInfo(netInfo, pLDName, nLen, pDA, VAR_DESC_NAME_KIND_FULL, 0, 1);
	}

	return ret;
}

ST_RET CMmsApi::node_get_DataLimitValInfoAll(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, tagDA*pDA)
{
	ST_RET ret = 0;

	//min value
	ret = node_get_DataLimitValInfo(netInfo, pLDName, pDA, 0);

	//max value
	ret = node_get_DataLimitValInfo(netInfo, pLDName, pDA, 1);

	//stepsize value
	ret = node_get_DataLimitValInfo(netInfo, pLDName, pDA, 2);

	//unit value
	ret = node_get_DataLimitValInfo(netInfo, pLDName, pDA, 3);

	return ret;
}

// 2012-12-17  读取某项的数据
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::get_tagDAData(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::get_tagDAData(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA)
#endif
{
#ifdef _mms_api_rw_use_critic_section_
	CAutoSimpleLock oLock(m_oMmsRWCriticSection);
#endif

	ST_INT nLen;
	ST_INT Type_id;
	ST_INT nRet = 0;
	ST_INT i;
//	tagValueX xValue;

	// 读取数值
	//////////////////////////////////////////////////////////////////////////
	nLen = mms_str_length(&pDA->DAValue.mmsName);

#ifdef _MVL_TYPE_CTRL_use_one_device_
	if (get_varType(net_info, pLDName, &Type_id, mms_string(&pDA->DAValue.mmsName), mvl_type_ctrl) != SD_SUCCESS)
#else
	if (get_varType(net_info, pLDName, &Type_id, mms_string(&pDA->DAValue.mmsName)) != SD_SUCCESS)
#endif
		return SD_FAILURE;

	if (!m_bOnlyReadValue)
	{
#ifdef _MVL_TYPE_CTRL_use_one_device_
		My_PareVarType(Type_id, pDA, mvl_type_ctrl);
#else
		My_PareVarType(Type_id, pDA);
#endif
	}

	// 2012-11-29  如果数据类型是结构体, 读取结构体数据
	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA)
	{	
		for (i=0; i<pDA->nSubDANum;i++)
		{
			//递归调用测试
//			get_tagDAData(net_info, pLDName, &pDA->pSubDA[i]);
			int SubType_id = 0;
#ifdef _MVL_TYPE_CTRL_use_one_device_
			if (get_varType(net_info, pLDName, &SubType_id, mms_string(&pDA->pSubDA[i].DAValue.mmsName), mvl_type_ctrl) != SD_SUCCESS)
#else
			if (get_varType(net_info, pLDName, &SubType_id, mms_string(&pDA->pSubDA[i].DAValue.mmsName)) != SD_SUCCESS)
#endif
				continue;

			if (!m_bOnlyReadValue)
			{
#ifdef _MVL_TYPE_CTRL_use_one_device_
				My_PareVarType(SubType_id, &pDA->pSubDA[i], mvl_type_ctrl);
#else
				My_PareVarType(SubType_id, &pDA->pSubDA[i]);
#endif
			}

			if (!strstr(pDA->pSubDA[i].DataType,"STRUCT"))
			{
#ifdef _use_mms_string
				get_varvalue_x(net_info, mms_string(&pDA->pSubDA[i].DAValue.mmsName), pLDName, SubType_id, &pDA->pSubDA[i].DAValue.Value, 1, pDA->pSubDA[i].nDataType);
#else
				get_varvalue(net_info, pDA->pSubDA[i].DAValue.mmsName, pLDName, SubType_id, &pDA->pSubDA[i].DAValue.Value, 1);
#endif
			}

#ifdef _MVL_TYPE_CTRL_use_one_device_
			destroy_typeid(SubType_id, mvl_type_ctrl);
#else
			destroy_typeid(SubType_id);
#endif
		}
	}
	else
	{
		//数据读写部分-整体一次性读取   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
		tagValue  arrValue[1024];
		ZeroMemory(arrValue, 1024*sizeof(tagValue));
#ifdef _use_mms_string
		nRet = get_varvalue_x(net_info, mms_string(&pDA->DAValue.mmsName), pLDName, Type_id, &pDA->DAValue.Value, 1, pDA->nDataType);
#else
		nRet = get_varvalue(net_info, pDA->DAValue.mmsName, pLDName, Type_id, &pDA->DAValue.Value, 1);
#endif
		//nRet = get_varvalue(net_info, pDA->DAValue.mmsName, pLDName, Type_id, arrValue, 1);

// 		{
// 			RUNTIME_TYPE *rt_out;
// 			ST_INT num_rt_out;
// 
// 			mvl_get_runtime(Type_id, &rt_out, &num_rt_out);
// 			int i = 0;
// 		}


		if (nRet != SD_SUCCESS)
		{
#ifdef _MVL_TYPE_CTRL_use_one_device_
			destroy_typeid(Type_id, mvl_type_ctrl);
#else
			destroy_typeid(Type_id);
#endif
			return SD_FAILURE;
		}
	}

#ifdef _MVL_TYPE_CTRL_use_one_device_
	destroy_typeid(Type_id, mvl_type_ctrl);
#else
	destroy_typeid(Type_id);
#endif

	return nRet;
}

ST_RET CMmsApi::get_tagDADataValue(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA)
{
	ST_INT nLen;
	ST_INT Type_id;
	ST_INT nRet = 0;
	ST_INT i;
//	tagValueX xValue;

	// 读取数值
	//////////////////////////////////////////////////////////////////////////
#ifdef _use_mms_string
	nLen = mms_str_length(&pDA->DAValue.mmsName);
#else
	nLen = strlen(pDA->DAValue.mmsName);
#endif

	// 2012-11-29  如果数据类型是结构体, 读取结构体数据
	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA)
	{	
		for (i=0; i<pDA->nSubDANum;i++)
		{
			if (mms_Is_SubDA_Value(&pDA->pSubDA[i]))
			{
//				Type_id = get_Type_id(pDA->pSubDA[i].DataType);

#ifdef _MVL_TYPE_CTRL_use_one_device_
				if (get_varType(net_info, pLDName, &Type_id, mms_string(&pDA->pSubDA[i].DAValue.mmsName), mvl_type_ctrl) != SD_SUCCESS)
#else
				if (get_varType(net_info, pLDName, &Type_id, mms_string(&pDA->pSubDA[i].DAValue.mmsName)) != SD_SUCCESS)
#endif
					return SD_FAILURE;

#ifdef _MVL_TYPE_CTRL_use_one_device_
				My_PareVarType(Type_id, &pDA->pSubDA[i], mvl_type_ctrl);
#else
				My_PareVarType(Type_id, &pDA->pSubDA[i]);
#endif

				if (Type_id != -1)
				{
#ifdef _use_mms_string
					get_varvalue_x(net_info, mms_string(&pDA->pSubDA[i].DAValue.mmsName), pLDName, Type_id, &pDA->pSubDA[i].DAValue.Value, 1, pDA->pSubDA[i].nDataType);
#else
					get_varvalue(net_info, pDA->pSubDA[i].DAValue.mmsName, pLDName, Type_id, &pDA->pSubDA[i].DAValue.Value, 1);
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
					destroy_typeid(Type_id, mvl_type_ctrl);
#else
					destroy_typeid(Type_id);
#endif
				}
			}
		}
	}
	else
	{
		Type_id = get_Type_id(pDA->DataType);

		if (Type_id == -1)
		{
			return SD_FAILURE;
		}

#ifdef _use_mms_string
		nRet = get_varvalue(net_info, mms_string(&pDA->DAValue.mmsName), pLDName, Type_id, &pDA->DAValue.Value, 1);
#else
		nRet = get_varvalue(net_info, pDA->DAValue.mmsName, pLDName, Type_id, &pDA->DAValue.Value, 1);
#endif

		if (nRet != SD_SUCCESS)
		{
			return SD_FAILURE;
		}
	}

	return nRet;
}

ST_RET CMmsApi::get_tagDADataValue2(MVL_NET_INFO *net_info, ST_CHAR*pLDName, char *pDataType, tagDAValue *pDAValue, ST_INT nDataType)
{
	ST_INT nLen;
	ST_INT Type_id;
	ST_INT nRet = 0;
//	tagValueX xValue;
	//ST_INT i;

	// 读取数值
	//////////////////////////////////////////////////////////////////////////
#ifdef _use_mms_string
	nLen = mms_str_length(&pDAValue->mmsName);
#else
	nLen = strlen(pDAValue->mmsName);
#endif

	// 2012-11-29  如果数据类型是结构体, 读取结构体数据
	if (strstr(pDataType,"STRUCT"))
	{	
		return SD_FAILURE;
	}
	else
	{
		Type_id = get_Type_id(pDataType);

		if (Type_id == -1)
		{
			return SD_FAILURE;
		}

#ifdef _use_mms_string
		nRet = get_varvalue_x(net_info, mms_string(&pDAValue->mmsName), pLDName, Type_id, &pDAValue->Value, 1, nDataType);
#else
		nRet = get_varvalue(net_info, pDAValue->mmsName, pLDName, Type_id, &pDAValue->Value, 1);
#endif

		if (nRet != SD_SUCCESS)
		{
			return SD_FAILURE;
		}
	}

	return nRet;
}

ST_INT CMmsApi::get_Type_id(ST_CHAR *pDataType)
{
	if (pDataType == NULL)
	{
		return INT32U_TYPEID;
	}

	ST_INT type_id = -1;

	if(strstr(pDataType,"BOOL"))
	{
		type_id = BOOLEAN_TYPEID;
	}
	else if(strstr(pDataType,"INT"))
	{
		type_id = INT32_TYPEID;
	}
	else if(strstr(pDataType,"UINT"))
	{
		type_id = INT32U_TYPEID;
	}
	else if(strstr(pDataType,"FLOAT"))
	{
		type_id = FLOAT32_TYPEID;
	}
	else if(strstr(pDataType,"UTF8_STR"))
	{
		type_id = DA_DATATYE_UTF8_STR;
	}
	else if(strstr(pDataType,"V_STR"))
	{
		type_id = DA_DATATYE_VISIBLE_STR;
	}
	//else if(strstr(pDataType,"BIT_STR"))
	//{
	//	type_id = DA_DATATYE_BIT_STR;
	//}

	return type_id;
}

ST_VOID CMmsApi::set_mmsname_SE(ST_CHAR *mmsname)
{
	ST_CHAR *p = strstr(mmsname,"$SG$");

	if (p != NULL)
	{
		*(p+2) = 'E';
	}
}

ST_RET CMmsApi::get_tagDAData_Set(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA, ST_BOOLEAN bReadSE)
{
	ST_INT nLen;
	ST_INT Type_id;
	ST_INT nRet = 0;
	ST_INT i=0;
	ST_CHAR	  mmsName[NAMESIZE];
//	tagValueX xValue;

#ifdef _mms_api_rw_use_critic_section_
	CAutoSimpleLock oLock(m_oMmsRWCriticSection);
#endif

	// 读取数值
	//////////////////////////////////////////////////////////////////////////
#ifdef _use_mms_string
	nLen = mms_str_length(&pDA->DAValue.mmsName);
#else
	nLen = strlen(pDA->DAValue.mmsName);
#endif

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA)
	{	
		for (i=0; i<pDA->nSubDANum;i++)
		{
			Type_id = get_Type_id(pDA->pSubDA[i].DataType);

			if (Type_id != -1)
			{
#ifdef _use_mms_string
				strcpy(mmsName, mms_string(&pDA->pSubDA[i].DAValue.mmsName));
#else
				strcpy(mmsName, pDA->pSubDA[i].DAValue.mmsName);
#endif

				if (bReadSE)
				{
					set_mmsname_SE(mmsName);
				}

				nRet = get_varvalue_x(net_info, mmsName, pLDName, Type_id, &pDA->pSubDA[i].DAValue.Value, 1, pDA->pSubDA[i].nDataType);
			}
		}
	}
	else
	{
		Type_id = get_Type_id(pDA->DataType);

		if (Type_id != -1)
		{
#ifdef _use_mms_string
			strcpy(mmsName, mms_string(&pDA->DAValue.mmsName));
#else
			strcpy(mmsName, pDA->DAValue.mmsName);
#endif

			if (bReadSE)
			{
				set_mmsname_SE(mmsName);
			}

			//nRet = get_varvalue(net_info, mmsName, pLDName, Type_id, &pDA->DAValue.Value, 1);
			nRet = get_varvalue_x(net_info, mmsName, pLDName, Type_id, &pDA->DAValue.Value, 1, pDA->nDataType);
		}
	}

	return nRet;
}

// 2013-4-17  读取数据的描述
#ifdef _MVL_TYPE_CTRL_use_one_device_

ST_RET CMmsApi::get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen
								 , tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl,ST_INT nAinKind,ST_INT nLevel)
#else
ST_RET CMmsApi::get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA,ST_INT nAinKind,ST_INT nLevel)
#endif
{
	ST_INT ret = SD_FAILURE;
	ST_INT Type_id = -1;
	ST_CHAR dstVar[NAMESIZE];
#ifdef _use_mms_string
	ST_CHAR mmsName[NAMESIZE];
#endif

	ASSERT(netInfo!=NULL);
	ASSERT(pDA!=NULL);

// 	if (strstr(pDA->DAValue.mmsName,"$mag$f")||
// 		strstr(pDA->DAValue.mmsName,"$mag$i")||
// 		strstr(pDA->DAValue.mmsName,"stVal")||
// 		strstr(pDA->DAValue.mmsName,"setMag")||
// 		strstr(pDA->DAValue.mmsName,"setVal")||
// 		strstr(pDA->DAValue.mmsName,"general"))
// 	{
// 		
// 	}
// 	else
// 	{
// 		return SD_TRUE;
// 	}

	{
		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
#ifdef _use_mms_string
		get_varDesrName(mms_string(&pDA->DAValue.mmsName), dstVar, nLen,nAinKind,nLevel);
		_snprintf(mmsName, NAMESIZE-1, "%s", dstVar);
		mms_str_set(&pDA->DADescri.mmsName, mmsName);

#ifdef _MVL_TYPE_CTRL_use_one_device_
		if (get_varType(netInfo, pLDName, &Type_id, mms_string(&pDA->DADescri.mmsName), mvl_type_ctrl) == SD_SUCCESS)
#else
		if (get_varType(netInfo, pLDName, &Type_id, mms_string(&pDA->DADescri.mmsName)) == SD_SUCCESS)
#endif
		{
			//ret = get_varvalue(netInfo, mms_string(&pDA->DADescri.mmsName), pLDName, Type_id, &pDA->DADescri.Value, 1);
			ret = get_varvalue_x(netInfo, mms_string(&pDA->DADescri.mmsName), pLDName, Type_id, &pDA->DADescri.Value, 1, DA_DATATYE_UTF8_STR);
		}
#else
		get_varDesrName(pDA->DAValue.mmsName, dstVar, nLen,nAinKind,nLevel);
		_snprintf(pDA->DADescri.mmsName, NAMESIZE-1, "%s", dstVar);

		if (get_varType(netInfo, pLDName, &Type_id, pDA->DADescri.mmsName) == SD_SUCCESS)
		{
			ret = get_varvalue(netInfo, pDA->DADescri.mmsName, pLDName, Type_id, &pDA->DADescri.Value, 1);

			if (ret != SD_FAILURE)
			{
				mms_UTF8ToUnicodeEx(pDA->DADescri.Value.string, strlen(pDA->DADescri.Value.string), pDA->DADescri.Value.string);
			}
		}
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif
	}


	if (strstr(pDA->DataType,"STRUCT"))
	{
		nLevel++;
		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];

// 			if (strstr(pSubDA->DAValue.mmsName,"$mag$f")||
// 				strstr(pSubDA->DAValue.mmsName,"stVal")||
// 				strstr(pSubDA->DAValue.mmsName,"setMag")||
// 				strstr(pSubDA->DAValue.mmsName,"setVal")||
// 				strstr(pSubDA->DAValue.mmsName,"general"))
// 			{
// 				ret += get_DataDescInfo(netInfo, pLDName, nLen, pSubDA, nAinKind, nLevel);
// 			}
// 			else
// 			{
// 				ret = get_DataDescInfo(netInfo, pLDName, nLen, pSubDA, nAinKind, nLevel);
// 			}
#ifdef _MVL_TYPE_CTRL_use_one_device_
			ret = get_DataDescInfo(netInfo, pLDName, nLen, pSubDA, mvl_type_ctrl, nAinKind, nLevel);
#else
			ret = get_DataDescInfo(netInfo, pLDName, nLen, pSubDA, nAinKind, nLevel);
#endif
		}


// 		if (ret != SD_SUCCESS)
// 		{
// 			ret = SD_FAILURE;
// 		}

	}
	else
	{
// 		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
// 		get_varDesrName(pDA->DAValue.mmsName, dstVar, nLen,nAinKind,nLevel);
// 		_snprintf(pDA->DADescri.mmsName, NAMESIZE-1, "%s", dstVar);
// 
// 		if (get_varType(netInfo, pLDName, &Type_id, pDA->DADescri.mmsName) == SD_SUCCESS)
// 		{
// 			ret = get_varvalue(netInfo, pDA->DADescri.mmsName, pLDName, Type_id, &pDA->DADescri.Value, 1);
// 
// 			if (ret != SD_FAILURE)
// 			{
// 				mms_UTF8ToUnicodeEx(pDA->DADescri.Value.name, strlen(pDA->DADescri.Value.name), pDA->DADescri.Value.name);
// 			}
// 		}
// 
// 		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
	}

	return ret;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::node_get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::node_get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, tagDA*pDA)
#endif
{
	ST_INT ret = SD_FAILURE;
	ST_INT Type_id = -1;

	ASSERT(netInfo!=NULL);
	ASSERT(pDA!=NULL);


	if (mms_str_length(&pDA->DADescri.mmsName) > 0)
	{
#ifdef _MVL_TYPE_CTRL_use_one_device_
		if (get_varType(netInfo, pLDName, &Type_id, mms_string(&pDA->DADescri.mmsName), mvl_type_ctrl) == SD_SUCCESS)
#else
		if (get_varType(netInfo, pLDName, &Type_id, mms_string(&pDA->DADescri.mmsName)) == SD_SUCCESS)
#endif
		{
			ret = get_varvalue_x(netInfo, mms_string(&pDA->DADescri.mmsName), pLDName, Type_id, &pDA->DADescri.Value, 1, DA_DATATYE_UTF8_STR);
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif
	}

	return ret;
}


// 2013-4-17  读取数据的单位
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::get_DataUniteInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen
								  , tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl,ST_INT nAinKind, ST_INT nLevel)
#else
ST_RET CMmsApi::get_DataUniteInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA,ST_INT nAinKind, ST_INT nLevel)
#endif
{
	ST_INT ret = SD_SUCCESS;
	ST_INT Type_id = -1;
	ST_CHAR dstVar[NAMESIZE];

	ASSERT(netInfo!=NULL);
	ASSERT(pDA!=NULL);

	if (strstr(pDA->DataType,"STRUCT"))
	{
		nLevel++;
		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];

			//lijq   2015-1-18
#ifdef _MVL_TYPE_CTRL_use_one_device_
			ret += get_DataUniteInfo(netInfo, pLDName, nLen, pSubDA, mvl_type_ctrl, nAinKind);
#else
			ret += get_DataUniteInfo(netInfo, pLDName, nLen, pSubDA, nAinKind);
#endif
// 			if (strstr(pSubDA->DAValue.mmsName,"$mag$f")||
// 				strstr(pSubDA->DAValue.mmsName,"stVal")||
// 				strstr(pSubDA->DAValue.mmsName,"setMag")||
// 				strstr(pSubDA->DAValue.mmsName,"setVal")||
// 				strstr(pSubDA->DAValue.mmsName,"general"))
// 			{
// 				get_DataUniteInfo(netInfo, pLDName, nLen, pSubDA, nAinKind);
// 			}
		}
	
		if (ret != SD_SUCCESS)
		{
			ret = SD_FAILURE;
		}
	}	
	else
	{
		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
#ifdef _use_mms_string
		get_varUnitName(mms_string(&pDA->DAValue.mmsName), dstVar, nLen, nAinKind, nLevel);
#else
		get_varUnitName(pDA->DAValue.mmsName, dstVar, nLen, nAinKind, nLevel);
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
		if (get_varType(netInfo, pLDName, &Type_id, dstVar, mvl_type_ctrl) == SD_SUCCESS)
#else
		if (get_varType(netInfo, pLDName, &Type_id, dstVar) == SD_SUCCESS)
#endif
		{
			ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, &pDA->DAUnite.Value, 1, DA_DATATYE_FLOAT);
#ifdef _use_mms_string
			mms_str_set(&pDA->DAUnite.mmsName, dstVar);
#else
			strcpy(pDA->DAUnite.mmsName, dstVar);
#endif
		}
		else
		{
			//TRACE("%s\n", pDA->DAUnite.mmsName);
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif
	}

	return ret;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::get_DataLimitVal(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_CHAR* dstVar, tagDAValue *pDAValue, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::get_DataLimitVal(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_CHAR* dstVar, tagDAValue *pDAValue)
#endif
{
	ST_INT ret = SD_FAILURE;
	ST_INT Type_id = -1;

	ASSERT(netInfo!=NULL);
	ASSERT(pDAValue!=NULL);

#ifdef _MVL_TYPE_CTRL_use_one_device_
	if (get_varType(netInfo, pLDName, &Type_id, dstVar, mvl_type_ctrl) == SD_SUCCESS)
#else
	if (get_varType(netInfo, pLDName, &Type_id, dstVar) == SD_SUCCESS)
#endif
	{
		ret = get_varvalue_x(netInfo, dstVar, pLDName, Type_id, &pDAValue->Value, 1, DA_DATATYE_FLOAT);
#ifdef _use_mms_string
		mms_str_set(&pDAValue->mmsName, dstVar);
#else
		strcpy(pDAValue->mmsName, dstVar);
#endif
	}

#ifdef _MVL_TYPE_CTRL_use_one_device_
	mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
	mvl_type_id_destroy(Type_id);
#endif

	return ret;
}

// 2014/4/4  获取数据对应的最大值
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::get_DataLimitValInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA
									 , MVL_TYPE_CTRL *mvl_type_ctrl,ST_INT nAinKind, ST_INT nLevel, ST_INT nKind)
#else
ST_RET CMmsApi::get_DataLimitValInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA
									 ,ST_INT nAinKind, ST_INT nLevel, ST_INT nKind)
#endif
{
	ST_INT ret = SD_FAILURE;
	ST_INT Type_id = -1;
	ST_CHAR dstVar[NAMESIZE];

	ASSERT(netInfo!=NULL);
	ASSERT(pDA!=NULL);

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	if (strstr(pDA->DataType,"STRUCT"))
	{
		nLevel++;

		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];
			get_DataLimitValInfo(netInfo, pLDName, nLen, pSubDA, nAinKind, nLevel, nKind);
		}
	}	
	else
	{
// 		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
// 		get_varLimitName(pDA->DAValue.mmsName, dstVar, nLen, nAinKind, nLevel, nKind, 1);
// 		ret = get_DataLimitVal(netInfo, pLDName, dstVar, nKind==0 ? &pDA->MinVal : &pDA->MaxVal);
// 
// 		if (ret != SD_SUCCESS)
// 		{
// 			ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
// 			get_varLimitName(pDA->DAValue.mmsName, dstVar, nLen, nAinKind, nLevel, nKind, 0);
// 			ret = get_DataLimitVal(netInfo, pLDName, dstVar, nKind==0 ? &pDA->MinVal : &pDA->MaxVal);
// 		}

		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
#ifdef _use_mms_string
		get_varLimitName(mms_string(&pDA->DAValue.mmsName), dstVar, nLen, nAinKind, nLevel, nKind, 1);
#else
		get_varLimitName(pDA->DAValue.mmsName, dstVar, nLen, nAinKind, nLevel, nKind, 1);
#endif

		if (get_varType(netInfo, pLDName, &Type_id, dstVar) == SD_SUCCESS)
		{
			ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, nKind==0 ? &pDA->MinVal.Value : &pDA->MaxVal.Value, 1, DA_DATATYE_FLOAT);

			if (nKind == 0)
			{
#ifdef _use_mms_string
				mms_str_set(&pDA->MinVal.mmsName, dstVar);
#else
				strcpy(pDA->MinVal.mmsName, dstVar);
#endif
			}
			else
			{
#ifdef _use_mms_string
				mms_str_set(&pDA->MaxVal.mmsName, dstVar);
#else
				strcpy(pDA->MaxVal.mmsName, dstVar);
#endif
			}
		}
		else
		{
			ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
#ifdef _use_mms_string
			get_varLimitName(mms_string(&pDA->DAValue.mmsName), dstVar, nLen, nAinKind, nLevel, nKind, 0);
#else
			get_varLimitName(pDA->DAValue.mmsName, dstVar, nLen, nAinKind, nLevel, nKind, 0);
#endif

			if (get_varType(netInfo, pLDName, &Type_id, dstVar) == SD_SUCCESS)
			{
				ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, nKind==0 ? &pDA->MinVal.Value : &pDA->MaxVal.Value, 1, DA_DATATYE_FLOAT);

				if (nKind == 0)
				{
#ifdef _use_mms_string
					mms_str_set(&pDA->MinVal.mmsName, dstVar);
#else
					strcpy(pDA->MinVal.mmsName, dstVar);
#endif
				}
				else
				{
#ifdef _use_mms_string
					mms_str_set(&pDA->MaxVal.mmsName, dstVar);
#else
					strcpy(pDA->MaxVal.mmsName, dstVar);
#endif
				}
			}
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif

	}
#endif

	return ret;
}

ST_RET CMmsApi::node_get_DataLimitValInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, tagDA*pDA, ST_INT nLimitKind)
{
	ST_INT ret = SD_FAILURE;
	ST_INT Type_id = -1;
	ST_CHAR dstVar[NAMESIZE];

	if (nLimitKind == 3)
	{
		if (pDA->nDataType != DA_DATATYE_INT 
			&&  pDA->nDataType != DA_DATATYE_UINT
			&& pDA->nDataType != DA_DATATYE_FLOAT
			&& pDA->nDataType != DA_DATATYE_STRUCT)
		{
			return SD_SUCCESS;
		}
	}

#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	ASSERT(netInfo!=NULL);
	ASSERT(pDA!=NULL);

	ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);

	if ((nLimitKind == 0)&&(mms_str_length(&pDA->MinVal.mmsName)>0))
	{
		strcpy(dstVar,mms_string(&pDA->MinVal.mmsName));
	}
	else if ((nLimitKind == 1)&&(mms_str_length(&pDA->MaxVal.mmsName)>0))
	{
		strcpy(dstVar,mms_string(&pDA->MaxVal.mmsName));
	}
	else if ((nLimitKind == 2)&&(mms_str_length(&pDA->StepSize.mmsName)>0))
	{
		strcpy(dstVar,mms_string(&pDA->StepSize.mmsName));
	}
	else if ((nLimitKind == 3)&&(mms_str_length(&pDA->DAUnite.mmsName)>0))
	{
		strcpy(dstVar,mms_string(&pDA->DAUnite.mmsName));
	}
	else
		return ret;

	if (get_varType(netInfo, pLDName, &Type_id, dstVar) == SD_SUCCESS)
	{
		if (nLimitKind == 0)
			ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, &pDA->MinVal.Value, 1, DA_DATATYE_FLOAT);
		else if (nLimitKind == 1)
			ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, &pDA->MaxVal.Value, 1, DA_DATATYE_FLOAT);
		else if (nLimitKind == 2)
			ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, &pDA->StepSize.Value, 1, DA_DATATYE_FLOAT);
		else if (nLimitKind == 3)
			ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, &pDA->DAUnite.Value, 1, DA_DATATYE_FLOAT);
	}

#ifdef _MVL_TYPE_CTRL_use_one_device_
	mvl_type_id_destroy(Type_id, p_mvl_type_ctrl);
#else
	mvl_type_id_destroy(Type_id);
#endif

#endif

	return ret;
}

ST_RET CMmsApi::get_DataStepSizeInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA,ST_INT nAinKind, ST_INT nLevel, ST_INT nKind)
{
	ST_INT ret = SD_FAILURE;
	ST_INT Type_id = -1;
 	ST_CHAR dstVar[NAMESIZE];

	ASSERT(netInfo!=NULL);
	ASSERT(pDA!=NULL);

#ifdef tagDA_use_UNIT_MIN_MAX_STEP

	if (strstr(pDA->DataType,"STRUCT"))
	{
		nLevel++;

		for (int i=0; i<pDA->nSubDANum;i++)
		{
			tagDA*pSubDA = &pDA->pSubDA[i];
			get_DataStepSizeInfo(netInfo, pLDName, nLen, pSubDA, nAinKind, nLevel, nKind);
		}
	}	
	else
	{
		ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
#ifdef _use_mms_string
		get_varStepSizeName(mms_string(&pDA->DAValue.mmsName), dstVar, 1);
#else
		get_varStepSizeName(pDA->DAValue.mmsName, dstVar, 1);
#endif

		if (get_varType(netInfo, pLDName, &Type_id, dstVar) == SD_SUCCESS)
		{
			ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, &pDA->StepSize.Value, 1, DA_DATATYE_FLOAT);
#ifdef _use_mms_string
			mms_str_set(&pDA->StepSize.mmsName, dstVar);
#else
			strcpy(pDA->StepSize.mmsName, dstVar);
#endif
		}
		else
		{
			ZeroMemory(dstVar,sizeof(ST_CHAR)*NAMESIZE);
#ifdef _use_mms_string
			get_varStepSizeName(mms_string(&pDA->DAValue.mmsName), dstVar, 0);
#else
			get_varStepSizeName(pDA->DAValue.mmsName, dstVar, 0);
#endif

			if (get_varType(netInfo, pLDName, &Type_id, dstVar) == SD_SUCCESS)
			{
				ret = get_varvalue_x(netInfo, dstVar, pLDName,Type_id, &pDA->StepSize.Value, 1, DA_DATATYE_FLOAT);
#ifdef _use_mms_string
				mms_str_set(&pDA->StepSize.mmsName, dstVar);
#else
				strcpy(pDA->StepSize.mmsName, dstVar);
#endif
			}
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(Type_id, p_mvl_type_ctrl);
#else
		mvl_type_id_destroy(Type_id);
#endif

	}

#endif

	return ret;
}

/* 2012-09-20  写入的定值数值 */
ST_RET CMmsApi::MMS_WriteData(CFuncParamEx *pFuncParaEx)
{
	ST_INT k;
	ST_INT nDaNum = 0;
	ST_INT nDsIndex;
	ST_INT type_id = -1;
	ST_CHAR varPathbuf[NAMESIZE];
	ST_CHAR buf[60];//zhouhj 20180928 原来字符数值为15  现考虑到字符串类型 改为60
	ST_RET ret;
	tagDA *pDA;
	ST_INT nError = 0;

	ACSI_NODE *pDevice = &pACSINode[pFuncParaEx->get_DevIndex()];
	CGpsPcTimeTickCount  oTickCount32;
	oTickCount32.Enter();

// 	int nWriteIndex = 0;
// 	int nWriteCount = 0;

	// 2013-3-5  延迟一定的时间再进行写操作
	Sleep(50);

	nDsIndex = pFuncParaEx->get_DSID();
 
	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	if (!netInfo)
		return SD_FAILURE;

	ACSI_NODE *pAcsiNode = get_DevACSI_NODEPtr(pFuncParaEx);
	pAcsiNode->nWriteErrorCount = 0;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return SD_FAILURE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	nDaNum = pLD_INFO->numData;
	pDevice->InfoWriteData[0] = 0;
	
// 	for (k=0; k<nDaNum; k++)
// 	{
// 		get_MMStagDAObj(nDsIndex, k, pLD_INFO, &pDA);
// 		if (pDA==NULL)
// 			continue;
// 
// 		if (!pDA->bModify)
// 			continue;
// 
// 		nWriteCount++;
// 	}

	for (k=0; k<nDaNum; k++)
	{
		if (pFuncParaEx->NeedExitFunc())
		{
			break;
		}

		get_MMStagDAObj(nDsIndex, k, pLD_INFO, &pDA);
		if (pDA==NULL)
			continue;

		if (!pDA->bModify)
			continue;

// 		if (pFuncParaEx != NULL)
// 		{
// 			CString strText;
// 			strText.Format(_T("第%d，共%d 【%s】"), nWriteIndex + 1, nWriteCount, mms_GetDADesc(pDA));
// 			pFuncParaEx->ShowMsg(strText);
// 		}
// 
// 		nWriteIndex++;
#ifdef _use_mms_string
		CStringA strData;
		strData = mms_string(&pDA->DAValue.mmsName);
#else
		CStringA strData(pDA->DAValue.mmsName);
#endif

#ifdef _mms_api_rw_use_critic_section_
		CAutoSimpleLock oLock(m_oMmsRWCriticSection);
#endif

		type_id = -1;
		if(strstr(pDA->DataType,"BOOL"))
		{
			type_id = BOOLEAN_TYPEID;
			*(ST_BOOLEAN *)buf = (ST_CHAR)pDA->DAValue.Value.u;
		}
		else if(strstr(pDA->DataType,"INT"))
		{
			type_id = INT32_TYPEID;
			*(ST_INT32 *)buf = pDA->DAValue.Value.l;
		}
		else if(strstr(pDA->DataType,"UINT"))
		{
			type_id = INT32U_TYPEID;
			*(ST_INT32 *)buf = pDA->DAValue.Value.u;
		}
		else if(strstr(pDA->DataType,"FLOAT"))
		{
			type_id = FLOAT32_TYPEID;
			*(ST_FLOAT *)buf = pDA->DAValue.Value.f;
		} 
		else if(strstr(pDA->DataType,"UTF8_STR"))
		{
			type_id = UNICODE_STRING255_TYPEID;
			strcpy(buf,mms_string(&pDA->DAValue.Value.string));
		} 
		else if(strstr(pDA->DataType,"STRUCT"))
		{
			for (int j=0; j<pDA->nSubDANum; j++)
			{
				if (!pDA->pSubDA)
					break;

#ifdef _use_mms_string
				CStringA strPath;
				strPath = mms_string(&pDA->pSubDA[j].DAValue.mmsName);
#else
				CStringA strPath(pDA->pSubDA[j].DAValue.mmsName);
#endif
				if (strPath.Find("setMag") != -1 || strPath.Find("setVal") != -1)
				{
#ifdef _use_mms_string
					strData = mms_string(&pDA->pSubDA[j].DAValue.mmsName);
#else
					strData = pDA->pSubDA[j].DAValue.mmsName;
#endif

					if(strstr(pDA->pSubDA[j].DataType,"BOOL")){
						type_id = BOOLEAN_TYPEID;
						*(ST_BOOLEAN *)buf = (ST_CHAR)pDA->pSubDA[j].DAValue.Value.u;
					}
					else if(strstr(pDA->pSubDA[j].DataType,"INT"))
					{
						type_id = INT32_TYPEID;
						*(ST_INT32 *)buf = pDA->pSubDA[j].DAValue.Value.l;
					}
					else if(strstr(pDA->pSubDA[j].DataType,"UINT"))
					{
						type_id = INT32U_TYPEID;
						*(ST_INT32 *)buf = pDA->pSubDA[j].DAValue.Value.u;
					}
					else if(strstr(pDA->pSubDA[j].DataType,"FLOAT"))
					{
						type_id = FLOAT32_TYPEID;
						*(ST_FLOAT *)buf = pDA->pSubDA[j].DAValue.Value.f;
					} 
					else if(strstr(pDA->pSubDA[j].DataType,"UTF8_STR"))
					{
						type_id = UNICODE_STRING255_TYPEID;
						strcpy(buf,mms_string(&pDA->pSubDA[j].DAValue.Value.string));
					} 
				}
			}
		}

		if (type_id!=-1)
		{
			if (strData.Find("$SG$")!=-1)
				strData.Replace("$SG$","$SE$");

			ZeroMemory(varPathbuf,sizeof(ST_CHAR)*NAMESIZE);
            strcpy(varPathbuf,strData.GetString());

#ifndef UNICODE
			if(strstr(pDA->DataType,"UTF8_STR"))
			{
                MultiByteToUtf8(buf);
            }
#endif

			ret = named_var_write(netInfo,varPathbuf,DOM_SPEC,pLD->LDName,type_id, buf, g_timeOut);
			//ret = set_varvalue(netInfo, varPathbuf, pLD->LDName, type_id, &pDA->DAValue.Value);
			if (ret == SD_SUCCESS)	
			{
				pDA->bModify = SD_FALSE;

// 				if (pFuncParaEx != NULL)
// 				{
// 					pFuncParaEx->StepIt();
// 				}
			}
			else
			{
				CString strInfor;
				long nCurrLen = strlen(pDevice->InfoWriteData);
                strInfor.Format(_T("写数据【%s】【%s】=【%s】失败, 错误码[%d]."), mms_GetDADesc(pDA).GetString(), strData.GetString(), mms_GetDAValue(pDA).GetString(),g_nCurErrorCode);
				pDA->bModify = SD_FALSE;

				if (strInfor.GetLength() + nCurrLen < INFOR_BUFFER_WRITEDATA_LEN)
				{
                    strcat(pDevice->InfoWriteData, strInfor.GetString());
				}

				nError++;
				CLogPrint::LogString(XLOGLEVEL_TRACE, strInfor);
				
			}
		}

#ifdef _mms_api_rw_use_critic_section_
		oLock.Free();
#endif
	}

	if (nError > 0)
	{
		//pFuncParaEx.MySendMessage(SD_FALSE);
		//ret = SD_FAILURE;
	}
	else
	{
        strcpy(pDevice->InfoWriteData, g_sLangTxt_WritDataSucc.GetString());//"写数据成功");
	}

	pAcsiNode->nWriteErrorCount = nError;
	pDevice->tmTotal = oTickCount32.GetTickCountLong();
	
	return ret;
}

/* 2012-09-20  写入的定值数值 */
ST_RET CMmsApi::MMS_WriteDataSingle(CFuncParamEx *pFuncParaEx)
{
	ST_INT k;
	ST_INT nDaNum = 0;
	ST_INT nDsIndex;
	ST_INT type_id = -1;
	ST_CHAR varPathbuf[NAMESIZE];
	ST_CHAR buf[15];
	ST_RET ret;
	tagDA *pDA;
	int nWriteIndex = 0;
	int nWriteCount = 0;
	CString strText;

	// 2013-3-5  延迟一定的时间再进行写操作
	Sleep(50);
	nDsIndex = pFuncParaEx->get_DSID();
 
	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	if (!netInfo)
		return SD_FAILURE;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return SD_FAILURE;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	nDaNum = pLD_INFO->numData;
	
	for (k=0; k<nDaNum; k++)
	{
		get_MMStagDAObj(nDsIndex, k, pLD_INFO, &pDA);
		if (pDA==NULL)
			continue;

		if (!pDA->bModify)
			continue;

		nWriteCount++;
	}

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->SetMaxRange(nWriteCount);
	}

	for (k=0; k<nDaNum; k++)
	{
        get_MMStagDAObj(nDsIndex, k, pLD_INFO, &pDA);
		if (pDA==NULL)
			continue;

		if (!pDA->bModify)
			continue;

		if (pFuncParaEx != NULL)
		{
			CString strValue;
			strValue = mms_GetDAValue(pDA);
            strText.Format(g_sLangTxt_WritDataPrgs.GetString()/*_T("第%d，共%d 【%s】=【%s】")*/
                , nWriteIndex + 1, nWriteCount, mms_GetDADesc(pDA).GetString(), strValue.GetString());
			pFuncParaEx->ShowMsg(strText);
		}

		nWriteIndex++;

#ifdef _use_mms_string
		CStringA strData;
		strData = mms_string(&pDA->DAValue.mmsName);
#else
		CStringA strData(pDA->DAValue.mmsName);
#endif

        type_id = -1;
		if(strstr(pDA->DataType,"BOOL"))
		{
			type_id = BOOLEAN_TYPEID;
			*(ST_BOOLEAN *)buf = (ST_CHAR)pDA->DAValue.Value.u;
		}
		else if(strstr(pDA->DataType,"INT"))
		{
			type_id = INT32_TYPEID;
			*(ST_INT32 *)buf = pDA->DAValue.Value.l;
		}
		else if(strstr(pDA->DataType,"UINT"))
		{
			type_id = INT32U_TYPEID;
			*(ST_INT32 *)buf = pDA->DAValue.Value.u;
		}
		else if(strstr(pDA->DataType,"FLOAT"))
		{
			type_id = FLOAT32_TYPEID;
			*(ST_FLOAT *)buf = pDA->DAValue.Value.f;
		} 
		else if(strstr(pDA->DataType,"UTF8_STR"))
		{
			type_id = UNICODE_STRING255_TYPEID;
			strcpy(buf,mms_string(&pDA->DAValue.Value.string));
		} 
        else if(strstr(pDA->DataType,"STRUCT"))
		{
			for (int j=0; j<pDA->nSubDANum; j++)
			{
				if (!pDA->pSubDA)
					break;

#ifdef _use_mms_string
				CStringA strPath;
				strPath = mms_string(&pDA->pSubDA[j].DAValue.mmsName);
#else
				CStringA strPath(pDA->pSubDA[j].DAValue.mmsName);
#endif
				if (strPath.Find("setMag") != -1 || strPath.Find("setVal") != -1)
				{
#ifdef _use_mms_string
					strData = mms_string(&pDA->pSubDA[j].DAValue.mmsName);
#else
					strData = pDA->pSubDA[j].DAValue.mmsName;
#endif

					if(strstr(pDA->pSubDA[j].DataType,"BOOL")){
						type_id = BOOLEAN_TYPEID;
						*(ST_BOOLEAN *)buf = (ST_CHAR)pDA->pSubDA[j].DAValue.Value.u;
					}
					else if(strstr(pDA->pSubDA[j].DataType,"INT"))
					{
						type_id = INT32_TYPEID;
						*(ST_INT32 *)buf = pDA->pSubDA[j].DAValue.Value.l;
					}
					else if(strstr(pDA->pSubDA[j].DataType,"UINT"))
					{
						type_id = INT32U_TYPEID;
						*(ST_INT32 *)buf = pDA->pSubDA[j].DAValue.Value.u;
					}
					else if(strstr(pDA->pSubDA[j].DataType,"FLOAT"))
					{
						type_id = FLOAT32_TYPEID;
						*(ST_FLOAT *)buf = pDA->pSubDA[j].DAValue.Value.f;
					} 
					else if(strstr(pDA->DataType,"UTF8_STR"))
					{
						type_id = UNICODE_STRING255_TYPEID;
						strcpy(buf,mms_string(&pDA->DAValue.Value.string));
					} 
				}
			}
		}

        if (type_id!=-1)
		{
			ZeroMemory(varPathbuf,sizeof(ST_CHAR)*NAMESIZE);
            strcpy(varPathbuf,strData.GetString());

#ifndef UNICODE
			if(strstr(pDA->DataType,"UTF8_STR"))
			{
                MultiByteToUtf8(buf);
            }
#endif

            ret = named_var_write(netInfo,varPathbuf,DOM_SPEC,pLD->LDName,type_id, buf, g_timeOut);
			//ret = set_varvalue(netInfo, varPathbuf, pLD->LDName, type_id, &pDA->DAValue.Value);

            pDA->bModify = SD_FALSE;

            if (ret == SD_SUCCESS)
			{

				WriteDataAfterWait(pFuncParaEx->m_pProgressInterface, g_nEnaWriteWait,strText, g_sLangTxt_BfExecNext);//_T("执行下一个参数修改前："));

			}
            else
			{
                CString strDesc = mms_GetDADesc(pDA);
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE
					, g_sLangTxt_EditDataFail.GetString()
					, strDesc.GetString(), strData.GetString());
			}

            if (pFuncParaEx != NULL)
            {
                pFuncParaEx->StepIt();
            }
        }
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                , g_sLangTxt_EditDataFail.GetString()/*_T("修改【%s】【%s】失败")*/
                , mms_GetDADesc(pDA).GetString(), strData.GetString());
		}
    }

	return ret;
}

BOOL CMmsApi::MMS_GetNextLdZonePara(CFuncParamEx *pFuncParaEx)
{
	ST_INT nLdIndex = pFuncParaEx->get_LDvIndex();
	ST_INT nDvIndex = pFuncParaEx->get_DevIndex();
	ST_INT nLdIndexCurr = nLdIndex;
	nLdIndex++;
	LD_NODE *pLD = NULL;
	ACSI_NODE *pDvNode = &pACSINode[nDvIndex];

	while (nLdIndex < pDvNode->numLD)
	{
		if (mms_IsSettingsDS(pDvNode->LD[nLdIndex].LDName) && m_nLdIndexBack != nLdIndex)
		{
			pLD = &pDvNode->LD[nLdIndex];
			pFuncParaEx->set_LDvIndex(nLdIndex);
			break;
		}

		nLdIndex++;
	}

	if (pLD == NULL)
	{
		nLdIndex = 0;

		while (nLdIndex < m_nLdIndexBack)
		{
			if (mms_IsSettingsDS(pDvNode->LD[nLdIndex].LDName))
			{
				pLD = &pDvNode->LD[nLdIndex];
				pFuncParaEx->set_LDvIndex(nLdIndex);
				break;
			}

			nLdIndex++;
		}

	}

	if (pLD != NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE
            , g_sLangTxt_GetNexLdZn.GetString()/*_T("获取下一个逻辑设备读取定值区:%d, %d")*/
			, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex());
	}

	return (pLD != NULL);
}

/* 2012-10-11  获取当前定值运行区&定值区数 */
ST_RET CMmsApi::MMS_GetActiveSG(CFuncParamEx *pFuncParaEx)
{
	ST_INT nSGID = 0;
	ST_INT nSGNum = 0;
	ST_INT ret = SD_FAILURE;

	ST_INT nLdIndex = pFuncParaEx->get_LDvIndex();

	if (nLdIndex == -1)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_NoLdHasZn);//_T("*****************没有定值区相关的逻辑设备*****************"));
		return SD_SUCCESS;
	}

	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	MVL_NET_INFO *net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
		return ret;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return ret;


	ACSI_NODE *pCurrDevice = &pACSINode[pFuncParaEx->get_DevIndex()];

	//if (strstr(pLD->LDName,"PROT") || strstr(pLD->LDName,"BRcd"))
	if (mms_IsSettingsDS(pLD->LDName))
	{
		ST_CHAR VarName[NAMESIZE+1];

		ZeroMemory(VarName,NAMESIZE+1);
		strcpy(VarName,"LLN0$SP$SGCB$NumOfSG");
		if (get_varvalue(net_info, VarName, pLD->LDName, INT8U_TYPEID, &nSGNum, 1)!=SD_SUCCESS)
		{
			//m_strMMSApiError = g_sLangTxt_RdSetZnsFail;//"读取定值区数目失败.";
			return ret;
		}

		pCurrDevice->nSGNum = nSGNum;
		pFuncParaEx->set_SGNum(nSGNum);

		ZeroMemory(VarName,NAMESIZE+1);
		strcpy(VarName,"LLN0$SP$SGCB$ActSG");
		if (get_varvalue(net_info, VarName, pLD->LDName, INT8U_TYPEID, &nSGID, 1)!=SD_SUCCESS)
		{
			//m_strMMSApiError = g_sLangTxt_RdCurSetZnsFail;//"读取当前定值运行区号失败.";
			return ret;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadSG:%d, %d"), pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex());
		pFuncParaEx->set_SGID(nSGID);
		pCurrDevice->nRunSGIndex = nSGID;

		ret = SD_SUCCESS;
	}
	else
	{
		//m_strMMSApiError = g_sLangTxt_RdSetZnsFail;//"装置无定值区.";
	}

	return ret;
}

void CMmsApi::FireCmdMsg(CFuncParamEx *pFuncParaEx,UINT nCmdID, UINT nCmdIndex)
{
	mms_FireCmdMsg(pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), 0
		,nCmdID, nCmdIndex); 
}

/* 2012-10-11  设置当前定值运行区号 */
ST_RET CMmsApi::MMS_SetActiveSG(CFuncParamEx *pFuncParaEx)
{
	ST_INT nSGID;
	ST_RET ret = SD_FAILURE;

	nSGID = pFuncParaEx->get_SGID();

	if (g_nCanWriteActiveSG==0)//zhouhj 20180907 金建 中国电科院南自装置测试时, 南网装置要求当前运行定值区定值不允许修改,软件自动切到下一个区, 定值修改后,将定值区切回;此
	{
		long nSleepTime = m_oMmsEngineConfig.m_nSwitchSGWait;

		if ((nSleepTime>0)&&(nSleepTime<10000))
		{
			Sleep(nSleepTime);
		}
	}

	if (!pFuncParaEx->Chck_DevIndex())
		return ret;

	MVL_NET_INFO *net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
		return ret;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return ret;

	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
	
	if (mms_IsSettingsDS(pLD->LDName))
	{
		ST_CHAR VarName[NAMESIZE+1];
		ZeroMemory(VarName,NAMESIZE+1);

		strcpy(VarName,"LLN0$SP$SGCB$ActSG");

		FireCmdMsg(pFuncParaEx,FuncID_SetSGNum, 0); 
		CGpsPcTimeTickCount  oTickCount32;
		ret = set_varvalue(net_info, VarName, pLD->LDName, INT8U_TYPEID, &nSGID);
		pDevice->tmSetSG = oTickCount32.GetTickCountLong();
		pDevice->tmTotal += pDevice->tmSetSG;
		FireCmdMsg(pFuncParaEx,FuncID_SetSGNum, 1); 
	
		if (ret!=SD_SUCCESS)
		{	
			sprintf(pDevice->InfoSetSG, _T("设置当前定值运行区号%d失败,(%d)."), nSGID,g_nCurErrorCode);
			CLogPrint::LogString(XLOGLEVEL_ERROR,pDevice->InfoSetSG);
		}
		else
		{
            sprintf(pDevice->InfoSetSG, g_sLangTxt_SetCurSetZnSucc.GetString()/*"设置当前定值运行区号%d成功."*/, nSGID);
			pDevice->nRunSGIndex = nSGID;
		}
	}
	else
	{
        sprintf(pDevice->InfoSetSG, g_sLangTxt_LdHasNoZn.GetString()/*"逻辑设备【%s】无定值区号."*/, pLD->LDName);
	}

	//m_strMMSApiError = pDevice->InfoSetSG;
	if (g_nCanWriteActiveSG==0)//zhouhj 20180907 金建 中国电科院南自装置测试时, 南网装置要求当前运行定值区定值不允许修改,软件自动切到下一个区, 定值修改后,将定值区切回;此
	{
		long nSleepTime = m_oMmsEngineConfig.m_nSwitchSGWait;

		if ((nSleepTime>0)&&(nSleepTime<10000))
		{
			Sleep(nSleepTime);
		}
	}


	return ret;
}

/* 2012-11-30  设置当前编辑定值运行区 */
ST_RET CMmsApi::MMS_SetEditSG(CFuncParamEx *pFuncParaEx,ST_INT nSGID)
{
	ST_RET ret = SD_FAILURE;

	if (!pFuncParaEx->Chck_DevIndex())
		return ret;

	MVL_NET_INFO *net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
		return ret;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return ret;

	CGpsPcTimeTickCount  oTickCount32;
	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;

	//if (strstr(pLD->LDName,"PROT"))
	//if (mms_IsSettingsDS(pLD->LDName))
	{
		ST_CHAR VarName[NAMESIZE+1];
		ZeroMemory(VarName,NAMESIZE+1);
		strcpy(VarName,"LLN0$SP$SGCB$EditSG");
		ret = set_varvalue(net_info, VarName, pLD->LDName, INT8U_TYPEID, &nSGID);
		pDevice->tmSetSE = oTickCount32.GetTickCountLong();
		pDevice->tmTotal += pDevice->tmSetSE;

		if (ret!=SD_SUCCESS)
		{
			sprintf(pDevice->InfoSetSE
                , g_sLangTxt_SetCurEdtZnFail.GetString()/*_T("【%d】设置当前编辑区【%d】失败.")*/
				, pFuncParaEx->get_DevIndex(), nSGID);
		}
		else
		{
			sprintf(pDevice->InfoSetSE
                , g_sLangTxt_SetCurEdtZnSucc.GetString()/*, _T("【%d】设置当前编辑区【%d】成功")*/
				, pFuncParaEx->get_DevIndex(), nSGID);
		}
	}
// 	else
// 	{
// 		sprintf(pDevice->InfoSetSE, g_sLangTxt_LdHasNoZn, pLD->LDName);
// 	}

	//m_strMMSApiError = pDevice->InfoSetSE;

	return ret;
}


/* 2012-11-30  固化当前编辑定值运行区 */
ST_RET CMmsApi::MMS_CnfEditSG(CFuncParamEx *pFuncParaEx)
{
	ST_BOOLEAN bCnf = SD_TRUE;
	ST_RET ret = SD_FAILURE;

	if (!pFuncParaEx->Chck_DevIndex())
		return ret;

	MVL_NET_INFO *net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
		return ret;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
		return ret;

	CGpsPcTimeTickCount  oTickCount32;
	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;

	//if (strstr(pLD->LDName,"PROT"))
	//if (mms_IsSettingsDS(pLD->LDName))
	{
		ST_CHAR VarName[NAMESIZE+1];

		ZeroMemory(VarName,NAMESIZE+1);
		strcpy(VarName,"LLN0$SP$SGCB$CnfEdit");
	 
		FireCmdMsg(pFuncParaEx,FuncID_CnfSetSE, 0); 

		ret = set_varvalue(net_info, VarName, pLD->LDName, BOOLEAN_TYPEID, &bCnf);
		 pDevice->tmExec = oTickCount32.GetTickCountLong(TRUE);
		FireCmdMsg(pFuncParaEx,FuncID_CnfSetSE, 1);

		if (ret!=SD_SUCCESS)
		{
			sprintf(pDevice->InfoExec
				, "固化定值区【%d】失败, (错误码%d)"
				, pFuncParaEx->get_SEID(),g_nCurErrorCode);
			//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("【%d】固化定值区【%d】失败."), m_FuncParam.get_DevIndex(), m_FuncParam.get_SEID());
			CLogPrint::LogString(XLOGLEVEL_TRACE, pDevice->InfoExec);
		}
		else
		{
            sprintf(pDevice->InfoExec, g_sLangTxt_SolidZnSucc.GetString()/*"固化定值区【%d】成功"*/,pFuncParaEx->get_SEID());
		}
	}
// 	else
// 	{
// 		//m_strMMSApiError.Format(g_sLangTxt_LdHasNoZn, pLD->LDName);// ="逻辑设备无编辑定值区.";
// 	}
	
	//m_strMMSApiError = pDevice->InfoExec;
	pDevice->tmTotal += pDevice->tmExec;

	return ret;
}

/* 2012-10-30  启动读装置报告 */
ST_RET CMmsApi::MMS_StartDevRpt(CFuncParamEx *pFuncParaEx)
{
	ST_INT ret;
	ST_BOOLEAN bGI;

	Sleep(200);//zhouhj 联机后自动启动报告增加

	bGI = pFuncParaEx->get_RptGI();

	if (g_nUseEntryIDUpdate == 1)
	{
		ret = set_StartReadRpt(pFuncParaEx,bGI ,TRUE);
	} 
	else
	{
		ret = set_StartReadRpt(pFuncParaEx,bGI ,FALSE);
	}
	
	return ret;
}

/* 2012-10-30  停止读报告数据 */
ST_RET CMmsApi::MMS_StopDevRpt(CFuncParamEx *pFuncParaEx)
{
	ST_INT ret;
	ST_INT nDsIndex;
		
	nDsIndex = pFuncParaEx->get_DSID();
	ret = set_StopReadRpt(pFuncParaEx,nDsIndex);

	return ret;
}


/* 2012-09-28  将 UTF-8 编码转为宽字符 */ 
CString mms_UTF8ToUnicode(const char* str , int len)
{
    unsigned char *pszRet = NULL;
    int nRetLen = 0;
    CString  strDest;
    utf8_to_gbk_r((const unsigned char *)str, len, &pszRet, &nRetLen);

    if (nRetLen > 0)
    {
        strDest = (char*)pszRet;
        delete pszRet;
    }

    return  strDest;
}

ST_INT mms_UTF8ToUnicodeEx(const char* str , int len, char *pszDest)
{
    int nRetLen = 0;
    utf8_to_gbk((const unsigned char *)str, len, (unsigned char*)pszDest, &nRetLen);

    return nRetLen;
}

/*
size_t g_f_wctou8(char * dest_str, const wchar_t src_wchar)
{
	int count_bytes = 0;
	wchar_t byte_one = 0, byte_other = 0x3f; // 用于位与运算以提取位值0x3f--->00111111
	unsigned char utf_one = 0, utf_other = 0x80; // 用于"位或"置标UTF-8编码0x80--->1000000
	wchar_t tmp_wchar =L'0'; // 用于宽字符位置析取和位移(右移位)
	unsigned char tmp_char =L'0';

	if (!src_wchar)//
		return (size_t)-1;

	for (;;) // 检测字节序列长度
	{
		if (src_wchar <= 0x7f){ // <=01111111
			count_bytes = 1; // ASCII字符: 0xxxxxxx( ~ 01111111)
			byte_one = 0x7f; // 用于位与运算, 提取有效位值, 下同
			utf_one = 0x0;
			break;
		}
		if ( (src_wchar > 0x7f) && (src_wchar <= 0x7ff) ){ // <=0111,11111111
			count_bytes = 2; // 110xxxxx 10xxxxxx[1](最多个位, 简写为*1)
			byte_one = 0x1f; // 00011111, 下类推(1位的数量递减)
			utf_one = 0xc0; // 11000000
			break;
		}
		if ( (src_wchar > 0x7ff) && (src_wchar <= 0xffff) ){ //0111,11111111<=11111111,11111111
			count_bytes = 3; // 1110xxxx 10xxxxxx[2](MaxBits: 16*1)
			byte_one = 0xf; // 00001111
			utf_one = 0xe0; // 11100000
			break;
		}
		if ( (src_wchar > 0xffff) && (src_wchar <= 0x1fffff) ){ //对UCS-4的支持..
			count_bytes = 4; // 11110xxx 10xxxxxx[3](MaxBits: 21*1)
			byte_one = 0x7; // 00000111
			utf_one = 0xf0; // 11110000
			break;
		}
		if ( (src_wchar > 0x1fffff) && (src_wchar <= 0x3ffffff) ){
			count_bytes = 5; // 111110xx 10xxxxxx[4](MaxBits: 26*1)
			byte_one = 0x3; // 00000011
			utf_one = 0xf8; // 11111000
			break;
		}
		if ( (src_wchar > 0x3ffffff) && (src_wchar <= 0x7fffffff) ){
			count_bytes = 6; // 1111110x 10xxxxxx[5](MaxBits: 31*1)
			byte_one = 0x1; // 00000001
			utf_one = 0xfc; // 11111100
			break;
		}
		return (size_t)-1; // 以上皆不满足则为非法序列
	}
	// 以下几行析取宽字节中的相应位, 并分组为UTF-8编码的各个字节
	tmp_wchar = src_wchar;
	for (int i = count_bytes; i > 1; i--)
	{ // 一个宽字符的多字节降序赋值
		tmp_char = (unsigned char)(tmp_wchar & byte_other);///后位与byte_other 00111111
		dest_str[i - 1] = (tmp_char | utf_other);/// 在前面加----跟或
		tmp_wchar >>= 6;//右移位
	}
	//这个时候i=1
	//对UTF-8第一个字节位处理，
	//第一个字节的开头"1"的数目就是整个串中字节的数目
	tmp_char = (unsigned char)(tmp_wchar & byte_one);//根据上面附值得来，有效位个数
	dest_str[0] = (tmp_char | utf_one);//根据上面附值得来1的个数
	// 位值析取分组__End!
	return count_bytes;
}

// 2013-2-18  UNICOD 编码装 UTF_8
int g_f_wcs_to_pchar(CString& wstr,char * p)
{
	wchar_t wc=L'1';
	char c[10]="1";//申请一个缓存
	size_t r=0; //size_t unsigned integer Result of sizeof operator
	int i=0;
	int j=0;
	for (i=0;i<wstr.GetLength();i++)
	{
		wc=wstr.GetAt(i);//得到一个宽字符
		r = g_f_wctou8(c,wc);//将一个宽字符按UTF-8格式转换到p地址
		if (r==-1) // 出错判断
        {
            AfxMessageBox(_T("wcs_to_pchar error"));
        }

		p[j]=c[0];//第一个值附给p
		j++; 
		if(r>1) 
		{
			for(size_t x=1;x<r;x++)
			{
				p[j]=c[x];
				j++;
			}
		}
	}
	//p[j]='0';
	return 1;

}
*/

/*
nACSI:  装置号
pOper_ctlVal :被控对象的变量名 例如：PRS311LD1/LLN0$CO$LEDRs$Oper$ctlVal
*/
ST_INT GetControlMode(ST_INT nACSI, ST_CHAR *DaName, ST_CHAR* pLDName)
{
	MVL_NET_INFO *net_info;	
	ST_INT	ret = -1;
	ST_CHAR varname[NAMESIZE];
	ST_INT  ctlmodel;

	strcpy(varname, DaName);
	strcat(varname, "$ctlModel");
	net_info = (MVL_NET_INFO*)(acsi_ctrl_table[nACSI].pnet_info);

	if (net_info == NULL)
	{
		return -1;
	}

	ctlmodel = 0;

	ret = named_var_read(net_info, varname, DOM_SPEC,pLDName,INT8_TYPEID,&ctlmodel,g_timeOut);

	if(ret == SD_SUCCESS)
		return ctlmodel;
	else
		return -1;
}
ST_INT GetControlModeEx(ST_INT nACSI, ST_CHAR *DaName, ST_CHAR* pLDName)
{
	ST_INT ctlmodel = -1;

	ST_CHAR mmsName[NAMESIZE];
	strcpy(mmsName, DaName);

	ST_CHAR *p = strstr(mmsName, "$ST$");

	if (p == NULL)
	{
		p =  strstr(mmsName, "$CO$");
	}

	if (p != NULL)
	{
		memcpy(p+1, "CF", 2);
		ctlmodel = GetControlMode(nACSI, mmsName, pLDName);
	}

	return ctlmodel;
}

ST_INT GetDAValue_stValue(tagDA *pSbDA, ST_INT nNum, ST_CHAR **ppType)
{
	ST_INT k;

	for (k=0;k<nNum;k++)
	{
		//if (strstr(pSbDA->DAValue.mmsName, "$stVal") != NULL)
		if (mms_Is_SubDA_Value(pSbDA))
		{
			*ppType = pSbDA->DataType;

			if (pSbDA->nDataType == DA_DATATYE_BIT_STR)
			{
				long nValue = 0;
				nValue = CString_To_long(mms_string(&pSbDA->DAValue.Value.string));
				return nValue;
			}
			else
			{
				return pSbDA->DAValue.Value.u;
			}
		}

		pSbDA++;
	}

	return 0;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_INT GetOperEx(MVL_NET_INFO *net_info, ST_CHAR *pOper, ST_CHAR *pDOM, ST_INT nACSI, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_INT GetOperEx(MVL_NET_INFO *net_info, ST_CHAR *pOper, ST_CHAR *pDOM, ST_INT nACSI)
#endif
{
	GETVAR_REQ_INFO getvar_req;
	VAR_ACC_TSPEC *type_spec;
	ST_RET  ret = SD_SUCCESS;
	ST_INT  type_id;
	MVL_REQ_PEND *reqCtrl;

	getvar_req.req_tag = GETVAR_NAME;
	getvar_req.name.domain_id = pDOM;
	getvar_req.name.object_tag = DOM_SPEC;
	getvar_req.name.obj_name.item_id = pOper;

	ret = mvla_getvar (net_info, &getvar_req, &reqCtrl);

	if(ret == SD_SUCCESS)
	{
		ret = waitReqDone(reqCtrl,g_timeOut,nACSI);
	}
	else
	{
		//mpl_init_err(reqCtrl->error_info->eclass, reqCtrl->error_info->code);
		mvl_free_req_ctrl (reqCtrl);
		return -1;
	}

	if(ret == SD_SUCCESS)
	{
		type_spec = &(reqCtrl->u.getvar.resp_info->type_spec);
#ifdef _MVL_TYPE_CTRL_use_one_device_
		type_id = mvl_type_id_create (NULL, type_spec->data, type_spec->len, mvl_type_ctrl);
#else
		type_id = mvl_type_id_create (NULL, type_spec->data, type_spec->len);
#endif
		mvl_free_req_ctrl (reqCtrl);
	
		if(-1 == type_id)
		{
			return  -1;
		}
		else
		{
			return type_id;
		}
	}
	else
	{
		mvl_free_req_ctrl (reqCtrl);//20160507
	}

	return -1;
}

ST_RET CMmsApi::GetBitStringValueFromInt(ST_RET nValue)
{
	ST_RET nBitStringValue = 0;

	if (nValue == 0)
	{
		nBitStringValue = 0;
	}
	else if (nValue == 1)
	{
		nBitStringValue = 0x40;
	}
	else if (nValue == 10)
	{
		nBitStringValue = 0x80;
	}
	else if (nValue == 11)
	{
		nBitStringValue = 0xC0;
	}

	return nBitStringValue;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::OperSBOwEx(ST_INT nACSI, ST_CHAR *pOper, ST_CHAR *pLDName, ST_INT type_id
				  , ST_INT iValue, ST_INT fValue, ST_INT test, ST_INT check, ST_INT nAddSize, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::OperSBOwEx(ST_INT nACSI, ST_CHAR *pOper, ST_CHAR *pLDName, ST_INT type_id
				  , ST_INT iValue, ST_INT fValue, ST_INT test, ST_INT check, ST_INT nAddSize)
#endif
{
	ST_RET ret;
	ST_INT i;
	MVL_NET_INFO *net_info;
	ST_UCHAR  buf[200];
	RUNTIME_TYPE *rt_out;
	ST_INT num_rt_out;
	ST_UCHAR *p;
	int n_nel_size = 0;

#ifdef _MVL_TYPE_CTRL_use_one_device_
	if(SD_SUCCESS != mvl_get_runtime (type_id, &rt_out, &num_rt_out, mvl_type_ctrl))
		return SD_ERROR;	
#else
	if(SD_SUCCESS != mvl_get_runtime (type_id, &rt_out, &num_rt_out))
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR,_T("写压板mvl_get_runtime函数失败."));
		return SD_ERROR;	
	}
#endif
	p = buf;
	memset(buf, 0, 200);
	RUNTIME_TYPE *p_rt_out = NULL;

	for(i=0; i<num_rt_out; i++)
	{
		p_rt_out = rt_out+i;

		if(p_rt_out->comp_name_ptr==NULL)
			continue;
		if(!_stricmp(p_rt_out->comp_name_ptr, "ctlVal"))//zhouhj 190108 增加对双位置 遥调的处理
		{
			if (p_rt_out->el_tag == RT_BIT_STRING)
			{
				*(ST_UCHAR *)p = GetBitStringValueFromInt(iValue);
			}
			else
			{
				*(ST_UCHAR *)p = iValue;
			}
		}
		else if(!_stricmp(p_rt_out->comp_name_ptr, "setMag"))
			*(ST_FLOAT *)p = (ST_FLOAT)fValue;
		else if(!_stricmp(p_rt_out->comp_name_ptr, "Test"))
		{
			if (g_nWriteCtrlCheckMode == 1) // 设置检修实际用此位置  20200421 周宏军
			{
				*(ST_UCHAR *)p = check;  //check;
				*(ST_UCHAR *)(p+1) = check;
//				p_rt_out->el_size = p_rt_out->el_size;// + nAddSize;
				p_rt_out->u.p.el_len = 2;
			}
			else
			{
				*(ST_UCHAR *)p = 0x00;     //check;
			}
//			*(ST_UCHAR *)p = 1;     //iValue;
		}
		else if(!_stricmp(p_rt_out->comp_name_ptr, "orCat"))
			*(ST_UCHAR *)p = 2;
		else if(!_stricmp(p_rt_out->comp_name_ptr, "orIdent"))
		{
			*(ST_UCHAR *)p = 1;
			*(ST_UCHAR *)(p+2) = 0x20;
		}
		else if(!_stricmp(p_rt_out->comp_name_ptr, "Check"))
		{
			*(ST_UCHAR *)p = 0;  //check;  zhouhj  20200715  确保为位串
			*(ST_UCHAR *)(p+1) = 0;
			p_rt_out->u.p.el_len = 2;
//				*(ST_UCHAR *)p = 0x00;     //check;
			}

		n_nel_size = p_rt_out->el_size;
		p = p + n_nel_size;
	}

	net_info = (MVL_NET_INFO*)(acsi_ctrl_table[nACSI].pnet_info);

	ret = named_var_write(net_info,pOper,DOM_SPEC,pLDName,type_id, buf, g_timeOut);

	return ret;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::MMS_CtrlWriteDA(CFuncParamEx *pFuncParaEx,tagDA *pDA, ST_CHAR* pLDName, ST_CHAR *pCoCf, const CString &strWriteTitle, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::MMS_CtrlWriteDA(CFuncParamEx *pFuncParaEx,tagDA *pDA, ST_CHAR* pLDName, ST_CHAR *pCoCf, const CString &strWriteTitle)
#endif
{
	ST_RET ret = SD_FALSE;

	ST_INT iValue;
	ST_INT ctlmodel;
	ST_INT nACSI;
	ST_CHAR OperName[NAMESIZE+1];
	ST_CHAR SBOwName[NAMESIZE+1];
	ST_CHAR mmsName[NAMESIZE+1];
	ST_CHAR *p;
	ST_CHAR *pDataType;
	ST_INT typeID_Oper;
	//CGpsPcTimeTickCount  oTickCount32;
	CGpsPcTimeTickCount oTickCount32;
	ACSI_NODE *pDevice;
	
	pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;

	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	nACSI = pFuncParaEx->get_DevIndex();

	MVL_NET_INFO *net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
		return SD_FAILURE;

	if (pDA==NULL)
		return SD_FAILURE;

	if (!pDA->bModify)
		return SD_FAILURE;

	if (strstr(pDA->DataType,"STRUCT") && pDA->pSubDA != NULL)
	{
#ifdef _use_mms_string
		strcpy(mmsName, mms_string(&pDA->DAValue.mmsName));
#else
		strcpy(mmsName, pDA->DAValue.mmsName);
#endif
		p = strstr(mmsName, "$ST$");

		if (p != NULL)
		{
			memcpy(p+1, pCoCf, 2);
		}

		sprintf(SBOwName,"%s$SBOw",mmsName);
		sprintf(OperName,"%s$Oper",mmsName);

		//if (mms_ena_read_before_write == 1)
		{
			// 读取控制模式
			ctlmodel = GetControlModeEx(nACSI, mmsName, pLDName);
			iValue = GetDAValue_stValue(pDA->pSubDA, pDA->nSubDANum, &pDataType);
#ifdef _MVL_TYPE_CTRL_use_one_device_
			typeID_Oper = GetOperEx(net_info,  OperName, pLDName, nACSI, mvl_type_ctrl);
#else
			typeID_Oper = GetOperEx(net_info,  OperName, pLDName, nACSI);
#endif

			if (typeID_Oper == -1)
			{
				mvl_type_id_destroy(typeID_Oper);  //zhouhj 20200821  修改在ID获取失败后，不在继续执行
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("获取压板操作typeID_Oper失败(错误原因码【%d】,错误class【%d】)."),
					g_nCurErrorCode,g_nCurErrorClass/*,g_nCurErrorInforRpt*/);
				return SD_FAILURE;
			}
			
			if (mms_ena_read_before_write_t > 0)
			{
				Sleep(mms_ena_read_before_write_t);
			}
		}
// 		else
// 		{
// 			iValue = GetDAValue_stValue(pDA->pSubDA, pDA->nSubDANum, &pDataType);
// 			ctlmodel = 4;
// 			
// 			typeID_Oper = GetOperEx(net_info,  OperName, pLDName, nACSI);
// 		}

		FireCmdMsg(pFuncParaEx,FuncID_CtrlWrite, 0); 
		oTickCount32.Enter();
		if ((ctlmodel == 4) ||(ctlmodel == 0)/*||(ctlmodel == 2) || (ctlmodel == -1) */)// 执行预置
		{
			Sleep(1);
			::GetLocalTime(&pDevice->tmStartExc);

#ifdef _MVL_TYPE_CTRL_use_one_device_
			ret = OperSBOwEx(nACSI,SBOwName, pLDName , typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 1, pDevice->p_mvl_type_ctrl);
#else
			ret = OperSBOwEx(nACSI,SBOwName, pLDName , typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 1);
#endif
			Sleep(1);
			pDevice->tmSel = oTickCount32.GetTickCountLong(TRUE);

			if (ret != SD_SUCCESS)
			{
				sprintf(pDevice->InfoSel
                    , g_sLangTxt_SelEnaFail.GetString()/*"选择压板【%s】【%d】失败"*/, mms_string(&pDA->DAValue.mmsName), iValue);
			}
			else
			{
				sprintf(pDevice->InfoSel
                    , g_sLangTxt_SelEnaSucc.GetString()/*"选择压板【%s】【%d】成功"*/, mms_string(&pDA->DAValue.mmsName), iValue);
			}
		}
		else
		{
			pDevice->tmSel = oTickCount32.GetTickCountLong(TRUE);
			sprintf(pDevice->InfoSel
                , g_sLangTxt_SelEnaSucc.GetString()/*"选择压板【%s】=【%d】成功(ctlmodel=%d)"*/
				, mms_string(&pDA->DAValue.mmsName), iValue);//, ctlmodel);
		}

		if (mms_log_error_infor)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, CString(pDevice->InfoSel));
		}

		FireCmdMsg(pFuncParaEx,FuncID_CtrlWrite, 1); 

		WriteDataAfterWait(pFuncParaEx->m_pProgressInterface, g_nEnaWriteWaitAfterSel, strWriteTitle, g_sLangTxt_AfterSelEna);//_T("压板选择后："));

		FireCmdMsg(pFuncParaEx,FuncID_CtrlWrite, 2); 
		oTickCount32.Enter();
#ifdef _MVL_TYPE_CTRL_use_one_device_
		ret = OperSBOwEx(nACSI, OperName, pLDName, typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 0, pDevice->p_mvl_type_ctrl);
#else
		ret = OperSBOwEx(nACSI, OperName, pLDName, typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 0);
#endif
		pDevice->tmExec = oTickCount32.GetTickCountLong();
		pDevice->tmTotal = pDevice->tmExec + pDevice->tmSel;
		FireCmdMsg(pFuncParaEx,FuncID_CtrlWrite, 3); 

		if (ret != SD_SUCCESS)
		{
			sprintf(pDevice->InfoExec
                , g_sLangTxt_ExecEnaFail.GetString()/*"执行压板【%s】【%d】失败"*/, mms_string(&pDA->DAValue.mmsName), iValue);
		}
		else
		{
			sprintf(pDevice->InfoExec
                , g_sLangTxt_ExecEnaSucc.GetString()/*"执行压板【%s】【%d】成功"*/, mms_string(&pDA->DAValue.mmsName), iValue);
		}

		if (mms_log_error_infor)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, CString(pDevice->InfoExec));
		}

		CLogPrint::LogFormatString(XLOGLEVEL_TRACE
            , g_sLangTxt_EnaOptrTime.GetString()/*_T("选择时间=%d   执行时间=%d")*/
			, pDevice->tmSel, pDevice->tmExec);

		//if (mms_ena_read_before_write == 1)
		{
#ifdef _MVL_TYPE_CTRL_use_one_device_
			mvl_type_id_destroy(typeID_Oper, mvl_type_ctrl);
#else
			mvl_type_id_destroy(typeID_Oper);
#endif
		}
	}

	return ret;
}

#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_RET CMmsApi::MMS_CtrlWriteDAEx(CFuncParamEx *pFuncParaEx,tagDA *pDA, tagDA *pDA2, ST_CHAR* pLDName, ST_CHAR *pCoCf, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_RET CMmsApi::MMS_CtrlWriteDAEx(CFuncParamEx *pFuncParaEx,tagDA *pDA, tagDA *pDA2, ST_CHAR* pLDName, ST_CHAR *pCoCf)
#endif
{
	ST_RET ret = SD_FALSE;

	ST_INT iValue, iValue2, nTDelayAfterSel;
	ST_INT nACSI;
	ST_CHAR OperName[NAMESIZE+1];
	ST_CHAR SBOwName[NAMESIZE+1];
	ST_CHAR mmsName[NAMESIZE+1];
	ST_CHAR *p;
	ST_INT typeID_Oper;
	CString strText;

	CGpsPcTimeTickCount  oTickCount32;
	ACSI_NODE *pDevice;

	pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
	iValue = pFuncParaEx->get_DaValue1();
	iValue2 = pFuncParaEx->get_DaValue2();
	nACSI = pFuncParaEx->get_DevIndex();
	nTDelayAfterSel = pFuncParaEx->get_TDelayAfterSel();

	if (!pFuncParaEx->Chck_DevIndex())
	{
		sprintf(pDevice->InfoSel
            , g_sLangTxt_WriteEnaParaErr.GetString()/*"修改压板命令参数错误【Dev=%d  LD=%d DS=%d  DA=%d】"*/
			, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex1());
		sprintf(pDevice->InfoExec
            , g_sLangTxt_WriteEnaParaErr.GetString()/*"修改压板命令参数错误【Dev=%d  LD=%d DS=%d  DA=%d】"*/
			, pFuncParaEx->get_DevIndex(), pFuncParaEx->get_LDvIndex(), pFuncParaEx->get_DSID(), pFuncParaEx->get_DaIndex2());
		return SD_FAILURE;
	}

	MVL_NET_INFO *net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
		return SD_FAILURE;

#ifdef _use_mms_string
	strcpy(mmsName, mms_string(&pDA->DAValue.mmsName));
#else
	strcpy(mmsName, pDA->DAValue.mmsName);
#endif
	p = strstr(mmsName, "$ST$");

	if (p != NULL)
	{
		memcpy(p+1, pCoCf, 2);
	}

	sprintf(SBOwName,"%s$SBOw",mmsName);
	sprintf(OperName,"%s$Oper",mmsName);

	if (iValue>=0)//zhouhj 20201128 中略提出需求，希望能实现只执行"选择"或只执行"执行",用于规约测试,设计为在选择或执行的值小于0时，该项命令不执行
	{
#ifdef _MVL_TYPE_CTRL_use_one_device_
		typeID_Oper = GetOperEx(net_info,  OperName, pLDName, nACSI, mvl_type_ctrl);
#else
		typeID_Oper = GetOperEx(net_info,  OperName, pLDName, nACSI);
#endif

		if (pFuncParaEx != NULL)
		{
            strText.Format(_T("【%s】=【%d】"), mms_GetDADesc(pDA).GetString(), iValue);
			pFuncParaEx->ShowMsg(strText);
		}

		FireCmdMsg(pFuncParaEx,FuncID_CtrlWriteOne, 0); 

		oTickCount32.Enter();
#ifdef _MVL_TYPE_CTRL_use_one_device_
		ret = OperSBOwEx(nACSI, SBOwName, pLDName , typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 1, pDevice->p_mvl_type_ctrl);	// 执行预置
#else
		ret = OperSBOwEx(nACSI, SBOwName, pLDName , typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 1);	// 执行预置
#endif
		pDevice->tmSel = oTickCount32.GetTickCountLong(TRUE);
		FireCmdMsg(pFuncParaEx,FuncID_CtrlWriteOne, 1); 

		if (ret != SD_SUCCESS)
		{
			sprintf(pDevice->InfoSel
                , g_sLangTxt_SelEnaFail.GetString()/*"选择压板【%s】【%d】失败"*/, mms_string(&pDA->DAValue.mmsName), iValue);
		}
		else
		{
			sprintf(pDevice->InfoSel
                , g_sLangTxt_SelEnaSucc.GetString()/*"选择压板【%s】【%d】成功"*/, mms_string(&pDA->DAValue.mmsName), iValue);
		}

		CLogPrint::LogString(XLOGLEVEL_TRACE, CString(pDevice->InfoSel));

		if (ret != SD_SUCCESS)
		{
			return ret;
		}

		if (nTDelayAfterSel > 0)
		{
			if (pFuncParaEx != NULL)
			{
				CString strWait;
				strWait.Format(g_sLangTxt_WriteDataAfterWait/*_T("等待%d毫秒")*/
					, _T(""), _T(""), nTDelayAfterSel);
				pFuncParaEx->ShowMsg(strWait);
				pFuncParaEx->StartTimer(nTDelayAfterSel);
			}

			Sleep(nTDelayAfterSel);

			if (pFuncParaEx != NULL)
			{
				pFuncParaEx->StartTimer(0);
			}
		}

		if (pFuncParaEx != NULL)
		{
            strText.Format(_T("[%s]=[%d]"), mms_GetDADesc(pDA2).GetString(), iValue2);
			pFuncParaEx->ShowMsg(strText);
		}

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(typeID_Oper, mvl_type_ctrl);
#else
		mvl_type_id_destroy(typeID_Oper);
#endif
	}

	if (iValue2>=0)
	{
#ifdef _use_mms_string
		strcpy(mmsName, mms_string(&pDA2->DAValue.mmsName));
#else
		strcpy(mmsName, pDA2->DAValue.mmsName);
#endif
		p = strstr(mmsName, "$ST$");

		if (p != NULL)
		{
			memcpy(p+1, pCoCf, 2);
		}

		sprintf(OperName,"%s$Oper",mmsName);

#ifdef _MVL_TYPE_CTRL_use_one_device_
		typeID_Oper = GetOperEx(net_info,  OperName, pLDName, nACSI, mvl_type_ctrl);
#else
		typeID_Oper = GetOperEx(net_info,  OperName, pLDName, nACSI);
#endif

		FireCmdMsg(pFuncParaEx,FuncID_CtrlWriteOne, 2); 

		oTickCount32.Enter();
		::GetLocalTime(&pDevice->tmStartExc);

#ifdef _MVL_TYPE_CTRL_use_one_device_
		ret = OperSBOwEx(nACSI, OperName, pLDName, typeID_Oper, iValue2, iValue2, 0, g_nSetDeviceCheck, 0, pDevice->p_mvl_type_ctrl);
#else
		ret = OperSBOwEx(nACSI, OperName, pLDName, typeID_Oper, iValue2, iValue2, 0, g_nSetDeviceCheck, 0);
#endif
		pDevice->tmExec = oTickCount32.GetTickCountLong(TRUE);
		pDevice->tmTotal = pDevice->tmSel + pDevice->tmExec;
		FireCmdMsg(pFuncParaEx,FuncID_CtrlWriteOne, 3); 

		if (ret != SD_SUCCESS)
		{
			sprintf(pDevice->InfoExec
                , g_sLangTxt_ExecEnaFail.GetString()/*"执行压板【%s】【%d】失败"*/, mms_string(&pDA->DAValue.mmsName), iValue2);
		}
		else
		{
			sprintf(pDevice->InfoExec
                , g_sLangTxt_ExecEnaSucc.GetString()/*"执行压板【%s】【%d】成功"*/, mms_string(&pDA->DAValue.mmsName), iValue2);
			mms_SetValue(pDA2, iValue2);
		}

		CLogPrint::LogString(XLOGLEVEL_TRACE, CString(pDevice->InfoExec));

#ifdef _MVL_TYPE_CTRL_use_one_device_
		mvl_type_id_destroy(typeID_Oper, mvl_type_ctrl);
#else
		mvl_type_id_destroy(typeID_Oper);
#endif
	}

	return ret;
}

/* 2012-12-3  控制相关write */
ST_RET CMmsApi::MMS_CtrlWrite(CFuncParamEx *pFuncParaEx)
{
	ST_INT nDataNum = 0;
	ST_INT nDsIndex;
	tagDA *pDA;
	tagDA tagData;
	ST_INT nRet = 0;
	ST_INT nACSI;
	int i = 0;
	int nWriteCount = 0;
	CString strText;
	int nWriteIndex = 0;
	long nWriteFailedCount = 0;
	ACSI_NODE *pAcsiNode = get_DevACSI_NODEPtr(pFuncParaEx);

	LD_NODE *pLD = NULL;
	MVL_NET_INFO *net_info = NULL;
	CGpsPcTimeTickCount  oTickCount32;
	CString strValue;
	CString strName;
	ZeroMemory(&tagData, sizeof(tagData));

	nRet = get_BaseOpeData(pFuncParaEx,&net_info,&pLD);
	if (nRet != SD_SUCCESS)
		return nRet;

	nACSI = pFuncParaEx->get_DevIndex();
	nDsIndex = pFuncParaEx->get_DSID();
	nDataNum = get_DataSetNum(pLD,nDsIndex);
	pAcsiNode->nWriteErrorCount = 0;

	for ( i=0; i<nDataNum; i++)
	{
		LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
		get_MMStagDAObj(nDsIndex, i, pLD_INFO, &pDA);

		if (!pDA->bModify)
			continue;

		nWriteCount++;
	}

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->SetMaxRange(nWriteCount);
	}

	for ( i=0; i<nDataNum; i++)
	{
		if (pFuncParaEx->NeedExitFunc())
		{
			break;
		}

		LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
		get_MMStagDAObj(nDsIndex, i, pLD_INFO, &pDA);

		if (!pDA->bModify)
			continue;

		strValue = mms_GetDAValue(pDA);
		strName=mms_GetDADesc(pDA);

		if (strName.GetLength() < 2)
		{
#ifdef _use_mms_string
			strName = mms_string(&pDA->DAValue.mmsName);
#else
			strName = pDA->DAValue.mmsName;
#endif
		}
#ifdef _mms_api_rw_use_critic_section_
		CAutoSimpleLock oLock(m_oMmsRWCriticSection);
#endif

		if (pFuncParaEx != NULL)
		{
            strText.Format(g_sLangTxt_WritDataPrgs.GetString()/*_T("第%d，共%d 【%s】=【%s】")*/
                , nWriteIndex + 1, nWriteCount, strName.GetString(), strValue.GetString());
			pFuncParaEx->ShowMsg(strText);
		}

		nWriteIndex++;

		if (mms_ena_read_before_write == 1)
		{//读取压板的状态数值
			mms_ReleaseData(&tagData);
			mms_CopyData(pDA, &tagData, FALSE);

			CString strDataSetName;
			strDataSetName = pLD_INFO->DataSetID;

			// 2012-12-17  读取装置数据进行比较
			if (strDataSetName.Find("$dsDout") != -1)//zhouhj 20190107 对于控制类的信号做特殊处理
			{
			}
			else if (get_tagDADataValue(net_info, pLD->LDName, &tagData)==SD_SUCCESS)
			{
				if (CompareData(pDA, &tagData)==SD_TRUE)
				{
					mms_ReleaseData(&tagData);

					pDA->bModify = SD_FALSE;

					if (pFuncParaEx != NULL)
					{
						pFuncParaEx->StepIt();
					}

#ifdef _mms_api_rw_use_critic_section_
					oLock.Free();
#endif

					continue;
				}
			}

			mms_ReleaseData(&tagData);
		}
		

		// 控制写数据
		oTickCount32.Enter();
#ifdef _MVL_TYPE_CTRL_use_one_device_
		nRet = MMS_CtrlWriteDA(pFuncParaEx,pDA, pLD->LDName, "CO", strText, pAcsiNode->p_mvl_type_ctrl) ;
#else
		nRet = MMS_CtrlWriteDA(pFuncParaEx,pDA, pLD->LDName, "CO", strText) ;
#endif
		ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;
//		pDevice->tmTotal += oTickCount32.GetTickCountLong(); zhouhj 20200114  在MMS_CtrlWriteDA函数中已经计算总时间，而且总时间不应该包括读取压板值的时间

		if (nRet == SD_SUCCESS)
		{
			pDA->bModify = SD_FALSE;

			if (pFuncParaEx != NULL)
			{
				pFuncParaEx->StepIt();
			}
		}
		else
		{
			pDA->bModify = SD_FALSE;
			pAcsiNode->nWriteErrorCount++;
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR
				, "压板操作【%s】【%s】=【%s】失败.(错误码%d),错误信息报告码【%d】 "
                , pLD->LDName, strName.GetString(), strValue .GetString(),g_nCurErrorCode,g_nCurErrorInforRpt);
			nWriteFailedCount++;
		}

#ifdef _mms_api_rw_use_critic_section_
		oLock.Free();
#endif


		WriteDataAfterWait(pFuncParaEx->m_pProgressInterface, g_nEnaWriteWait, strText, g_sLangTxt_BfExecNext);//_T("下一个压板修改前："));
		// 读装置的数据进行比较
	}

	if (nWriteFailedCount == 0)
	{
		return SD_SUCCESS;
	}
	else
	{
		return SD_FAILURE;
	}
}

ST_RET CMmsApi::MMS_CtrlWriteOne(CFuncParamEx *pFuncParaEx)
{
	ST_INT nDsIndex=0, nDaIndex1=0, nDaIndex2=0;
	tagDA *pDA, *pDA2;
	ST_INT nRet = 0;
	ST_INT nACSI;
	int i = 0;
	int nWriteCount = 0;
	CString strText;
	int nWriteIndex = 0;
	ACSI_NODE *pDevice = Global_get_ACSI_NODE(pFuncParaEx->get_DevIndex());;

	LD_NODE *pLD = NULL;
	MVL_NET_INFO *net_info = NULL;

	nRet = get_BaseOpeData(pFuncParaEx,&net_info,&pLD);
	if (nRet != SD_SUCCESS)
		return nRet;

	nACSI = pFuncParaEx->get_DevIndex();
	nDsIndex = pFuncParaEx->get_DSID();
	nDaIndex1 = pFuncParaEx->get_DaIndex1();
	nDaIndex2 = pFuncParaEx->get_DaIndex2();

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->SetMaxRange(1);
	}

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
	get_MMStagDAObj(nDsIndex, nDaIndex1, pLD_INFO, &pDA);
	get_MMStagDAObj(nDsIndex, nDaIndex2, pLD_INFO, &pDA2);
#ifdef _MVL_TYPE_CTRL_use_one_device_
	nRet = MMS_CtrlWriteDAEx(pFuncParaEx,pDA, pDA2, pLD->LDName, "CO", pDevice->p_mvl_type_ctrl) ;
#else
	nRet = MMS_CtrlWriteDAEx(pFuncParaEx,pDA, pDA2, pLD->LDName, "CO") ;
#endif

	if (pFuncParaEx != NULL)
	{
		pFuncParaEx->StepIt();
	}

	return nRet;
}

/* 2012-12-27  获取数据集的数目 */
ST_INT CMmsApi::get_DataSetNum(LD_NODE *pLD, ST_INT nDsIndex)
{
	ST_INT nDataSetNum = 0;

	if (nDsIndex<0 || nDsIndex>=MAX_DASET_NUM)
		return nDataSetNum;

	LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];

	return pLD_INFO->numData;
}

/* 2012-12-27  获取基本的操作信息 */
ST_RET CMmsApi::get_BaseOpeData(CFuncParamEx *pFuncParaEx,MVL_NET_INFO **net_info,LD_NODE **pLD)
{
	if (!pFuncParaEx->Chck_DevIndex())
		return SD_FAILURE;

	*net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
	{
		//m_strMMSApiError = "创建网络失败.";
		return SD_FAILURE;
	}

	*pLD = get_DevLDPtr(pFuncParaEx);
	if (!pLD)
	{
		//m_strMMSApiError = "未指定逻辑设备.";
		return SD_FAILURE;
	}

	return SD_SUCCESS;
}

// 2012-12-17  释放创建的类型ID
#ifdef _MVL_TYPE_CTRL_use_one_device_
ST_VOID CMmsApi::destroy_typeid(ST_INT TypeID, MVL_TYPE_CTRL *mvl_type_ctrl)
#else
ST_VOID CMmsApi::destroy_typeid(ST_INT TypeID)
#endif
{	
#ifdef _MVL_TYPE_CTRL_use_one_device_
	mvl_type_id_destroy(TypeID, mvl_type_ctrl);
#else
	mvl_type_id_destroy(TypeID);
#endif

	if (TypeID<201 + _mvlu_num_dyn_types)
		ZeroMemory(&mvl_type_ctrl[TypeID],sizeof(mvl_type_ctrl[TypeID]));
}

/* 2013-1-11  装置复归 */
ST_RET CMmsApi::MMS_ResetDev(CFuncParamEx *pFuncParaEx)
{
	ST_INT nACSI = pFuncParaEx->get_DevIndex();
	
	ST_RET nRet = My_DebReset(pFuncParaEx,"PROT");

	if (nRet != SD_SUCCESS)
	{
		nRet = My_DebReset(pFuncParaEx,"LD0");
	}

	if (nRet != SD_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE
            , g_sLangTxt_DvResetFail.GetString()/*_T("装置复归【%d】复归失败")*/, nACSI);
	}

	return nRet;
}

// 2013-5-7  装置复归
ST_RET CMmsApi::My_DebReset(CFuncParamEx *pFuncParaEx,CString strType)
{
	ST_INT nACSI;
	ST_RET nRet = SD_SUCCESS;
	LD_NODE *pLD = NULL;
	nACSI = pFuncParaEx->get_DevIndex();
	ACSI_NODE *pDvNode = &pACSINode[nACSI];

	MVL_NET_INFO *net_info = get_NetInfo(pFuncParaEx);
	if (!net_info)
	{
		//m_strMMSApiError = "创建网络失败.";
		return SD_FAILURE;
	}

	//ST_INT j = m_FuncParam.get_LDvIndex();

	if (nACSI>=0 && nACSI<10)
	{
		
		if (pDvNode)
		{
			for (int j=0; j<pDvNode->numLD; j++)
			{
				pLD = &pDvNode->LD[j]; 
			
				if (pLD != NULL)
				{
                    if (strstr(pLD->LDName,strType.GetString())!=NULL)
					{
						break;
					}
				}
			}
		}
		else
			return SD_FAILURE;
	}
	else
		return SD_FAILURE;

	if (pLD == NULL)
		return SD_FAILURE;

	// 控制写数据
	ST_INT iValue = 1;
	ST_CHAR OperName[NAMESIZE+1];
	ST_INT typeID_Oper;

	sprintf(OperName,"LLN0$CO$LEDRs$Oper",NULL);
#ifdef _MVL_TYPE_CTRL_use_one_device_
	typeID_Oper = GetOperEx(net_info,  OperName, pLD->LDName, nACSI, pDvNode->p_mvl_type_ctrl);
	nRet = OperSBOwEx(nACSI, OperName, pLD->LDName, typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 0, pDvNode->p_mvl_type_ctrl);
	mvl_type_id_destroy(typeID_Oper, pDvNode->p_mvl_type_ctrl);
#else
	typeID_Oper = GetOperEx(net_info,  OperName, pLD->LDName, nACSI);
	nRet = OperSBOwEx(nACSI, OperName, pLD->LDName, typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 0);
	mvl_type_id_destroy(typeID_Oper);
#endif

	if (nRet != SD_SUCCESS)//zhouhj20180828 兼容南网公司 LNN0节点下扩充的 “事故总信号及人工复归”DO
	{
		sprintf(OperName,"LLN0$CO$CBFlt$Oper",NULL);
#ifdef _MVL_TYPE_CTRL_use_one_device_
		typeID_Oper = GetOperEx(net_info,  OperName, pLD->LDName, nACSI, pDvNode->p_mvl_type_ctrl);
		nRet = OperSBOwEx(nACSI, OperName, pLD->LDName, typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 0, pDvNode->p_mvl_type_ctrl);
		mvl_type_id_destroy(typeID_Oper,  pDvNode->p_mvl_type_ctrl);
#else
		typeID_Oper = GetOperEx(net_info,  OperName, pLD->LDName, nACSI);
		nRet = OperSBOwEx(nACSI, OperName, pLD->LDName, typeID_Oper, iValue, iValue, 0, g_nSetDeviceCheck, 0);
		mvl_type_id_destroy(typeID_Oper);
#endif
	}

	if (nRet != SD_SUCCESS)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE
            , g_sLangTxt_DvResetFailEx.GetString()/*"装置复归【%d】【%s】【%s】复归失败"*/
			, nACSI, pLD->LDName, OperName);
	}

	return nRet;
}



//Journal
ST_RET CMmsApi::MMS_ReadJournalCount(CFuncParamEx *pFuncParaEx)
{
	JSTAT_REQ_INFO jstat_req;
	MVL_REQ_PEND *reqCtrl;
	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	ST_RET ret;
	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);
	int nDevNum = pFuncParaEx->get_DevIndex();

	if (!pLD)
		return SD_FAILURE;

	ST_CHAR sz_vmd_spec[NAMESIZE], *psz_item_id = NULL;
 	psz_item_id = pFuncParaEx->get_journal_ref();
	strcpy(sz_vmd_spec, psz_item_id);

	jstat_req.jou_name.obj_name.vmd_spec = psz_item_id;
	psz_item_id = sz_vmd_spec;

	while (*psz_item_id != '\0')
	{
		if (*psz_item_id == '/')
		{
			*psz_item_id = '\0';//日志索引的前半部分为jstat_req.jou_name.domain_id值，后半部分为jstat_req.jou_name.obj_name.vmd_spec值
			psz_item_id++;
			jstat_req.jou_name.obj_name.vmd_spec = psz_item_id;
			break;
		}

		psz_item_id++;
	}

	jstat_req.jou_name.object_tag = DOM_SPEC;
	jstat_req.jou_name.domain_id = sz_vmd_spec;

	ret = mvla_jstat (netInfo, &jstat_req, &reqCtrl);

	if (ret == SD_SUCCESS)
		ret = waitReqDone (reqCtrl, g_timeOut, netInfo->nACSI);

	if (ret != SD_SUCCESS)
	{
		pACSINode[nDevNum].LogTotalNum = 0;
		CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "mvl_jstat () Error, ret = 0x%X.", ret);
	}
	else
	{
		pACSINode[nDevNum].LogTotalNum = reqCtrl->u.jstat.resp_info->cur_entries;
		CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "mvl_jstat OK");
		CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "cur_entries = %lu", reqCtrl->u.jstat.resp_info->cur_entries);
		CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "mms_deletable = %d", reqCtrl->u.jstat.resp_info->mms_deletable);
	}

	mvl_free_req_ctrl (reqCtrl);

	return SD_SUCCESS;
}


ST_BOOLEAN convert_btod_to_timet(MMS_BTOD &btod, tagEVENTTIME &tmEvent)
{
	MMS_UTC_TIME tmUtc;

	asn1_convert_btod_to_utc(&btod, &tmUtc);
	Convert_UTC_To_BCD(&tmEvent, tmUtc);

	return TRUE;
}

CString CMmsApi::find_dataset_by_loginfo(LD_JOURNAL_CTRLS *pJournalCtrls,char *pLogCtrlName)
{
	CString strDataSet,strLogCtrlName;
	LD_LOG_INFO *LogInfo = NULL;
	strLogCtrlName = pLogCtrlName;
	long nIndex = strLogCtrlName.ReverseFind('$');

	if (nIndex != -1)
		strLogCtrlName = strLogCtrlName.Mid(nIndex);

	if (pJournalCtrls == NULL)
		return strDataSet;

	for (nIndex = 0;nIndex<pJournalCtrls->numData;nIndex++)
	{
		LogInfo = &pJournalCtrls->LogInfo[nIndex];

        if (strstr(mms_string(&LogInfo->Name),strLogCtrlName.GetString()) != NULL)
		{
			strDataSet = mms_string(&LogInfo->Dataset);
			break;
		}
	}

	return strDataSet;
}

CString CMmsApi::find_logctrl_by_datasetinfo(LD_JOURNAL_CTRLS *pJournalCtrls,CString strDatasetName)
{
	CString strDataSet,strLogCtrlName;
	LD_LOG_INFO *LogInfo = NULL;
	strDataSet = strDatasetName;
	long nIndex = strDataSet.ReverseFind('$');

	if (nIndex != -1)
		strDataSet = strDataSet.Mid(nIndex);

	if (pJournalCtrls == NULL)
		return strDataSet;

	for (nIndex = 0;nIndex<pJournalCtrls->numData;nIndex++)
	{
		LogInfo = &pJournalCtrls->LogInfo[nIndex];

        if (strstr(mms_string(&LogInfo->Dataset),strDataSet.GetString()) != NULL)
		{
			strLogCtrlName = mms_string(&LogInfo->Name);
			break;
		}
	}

	return strLogCtrlName;
}

BOOL CMmsApi::check_prefix_and_suffix(const CString &strMsgPath,CString &strDirPath)
{
	strDirPath = strMsgPath;
	long nIndex = strMsgPath.Find('^');//查找具有时间段信息的连接符
	BOOL bTime,bNewNum;
	bTime = (nIndex != -1);

	if (bTime)
	{
		strDirPath = strMsgPath.Mid(nIndex+1);
		nIndex = strDirPath.Find('/');

		if (nIndex != -1)
		{
			strDirPath = strDirPath.Mid(nIndex);
		}
		else
			strDirPath = strMsgPath;
	}

	nIndex = strDirPath.Find("/NEWEST_");//查找最新条目数的后缀
	bNewNum = (nIndex != -1);

	if (bNewNum)
	{
		strDirPath = strDirPath.Left(nIndex+1);
	}

	return (bTime||bNewNum);
}

void CMmsApi::find_lcbName(const CString &strLogCtrlPath,char *pszLcbName)
{
	int nIndex = strLogCtrlPath.Find("$lcb");
	CString strTmp;

	if (nIndex == -1)
	{
		nIndex = strLogCtrlPath.Find("lcb");

		if (nIndex == -1)
		{
			return;
		}
	}

	strTmp = strLogCtrlPath.Mid(nIndex);

	nIndex = strTmp.ReverseFind('$');
	if ((nIndex != 0)&&(nIndex != -1))
	{
		strTmp = strTmp.Left(nIndex);
	}

    strcpy(pszLcbName,strTmp.GetString());
}

ST_RET CMmsApi::MMS_ReadJournal(CFuncParamEx *pFuncParaEx)
{
	JREAD_REQ_INFO jread_req;
	MVL_REQ_PEND *reqCtrl;
	MVL_NET_INFO *netInfo = get_NetInfo(pFuncParaEx);
	ST_RET ret;
	MVL_JREAD_RESP_INFO *jread_resp;	/* set to reqCtrl->u.jread_resp_info*/
	MVL_JOURNAL_ENTRY *jou_entry;
	int i, j;
	long long int n_start_entry = pFuncParaEx->get_start_entry();
	DWORD dw_start_entry = 0;
	ST_CHAR sz_vmd_spec[NAMESIZE], *psz_item_id = NULL;
	ST_UCHAR start_entry[10] = {""},entry_id[10] = {""};
	tagEVENTTIME tmEvent;
	ST_UCHAR *pRptData = NULL;
	tagDA *pDA = NULL,*pNewDA =NULL;

	LD_NODE *pLD = get_DevLDPtr(pFuncParaEx);

	if (!pLD)
		return SD_FAILURE;

	psz_item_id = pFuncParaEx->get_journal_ref();
	jread_req.jou_name.obj_name.aa_spec = psz_item_id;

	strcpy(sz_vmd_spec, psz_item_id); 
	psz_item_id = sz_vmd_spec;

	while (*psz_item_id != '\0')
	{
		if (*psz_item_id == '/')
		{
			*psz_item_id = '\0';
			psz_item_id++;
			jread_req.jou_name.obj_name.aa_spec = psz_item_id;
			break;
		}

		psz_item_id++;
	}
 	
	jread_req.jou_name.object_tag = DOM_SPEC;
	jread_req.jou_name.domain_id = sz_vmd_spec;
	jread_req.range_start_pres = pFuncParaEx->get_range_start_pres();
	jread_req.range_stop_pres = pFuncParaEx->get_range_stop_pres();

	jread_req.start_tag = pFuncParaEx->get_start_tag();		/* start tag			*/	/*  0 - starting time		*/	/*  1 - starting entry		*/
	jread_req. start_time = pFuncParaEx->get_start_time();			/* range starting time		*/
	jread_req.start_entry_len = 8/*sizeof(n_start_entry)*/;		/* length of starting entry	*/

	for (i = 0;i<8;i++)
	{
		j = n_start_entry%256;
		start_entry[7-i] = (unsigned char)j;
		n_start_entry /= 256;
	}

	jread_req.start_entry = (unsigned char *)(&start_entry/*n_start_entry*/);		/* pointer to starting entry	*/
	jread_req.range_stop_pres = pFuncParaEx->get_range_stop_pres();		/* range stop spec present	*/
	jread_req.stop_tag = pFuncParaEx->get_stop_tag();			/* stop tag			*/	/*  0 - ending time		*/	/*  1 - number of entries	*/
	jread_req.end_time = pFuncParaEx->get_end_time();			/* range ending time		*/
	jread_req.num_of_entries = pFuncParaEx->get_num_of_entries();		/* number of entries		*/
	jread_req.list_of_var_pres = 0;
	jread_req.sa_entry_pres = 0;
// 	jread_req.time_spec = m_FuncParam.get_start_time();
// 	jread_req.sa_entry_pres = 1;

	CString strEntryID,strEntryPath,strEntryTime,strLogEntryName,strSelectPath;
	int nEntryID = 0,nViewListIndex = 0,nEntryNum = 0;
	strSelectPath = pFuncParaEx->get_vmd_spec();
	BOOL bSymbol1 = FALSE,bSymbol2 = FALSE;
	LD_JOURNAL_DATA *pJournalData = NULL;
	int nDsIndex = 0,nNumDA = 0,nTmp;

	if (strSelectPath.IsEmpty() /*== _T("所有日志控制块")*/)
		bSymbol1 = TRUE;

	mms_JournalDataOfVector_Free(pLD->JournalDatas.Datas,pLD->JournalDatas.numOfData);
	vector_free(&pLD->JournalDatas);

	while (TRUE)
	{
		ret = mvla_jread (netInfo, &jread_req, &reqCtrl);

		if (ret == SD_SUCCESS)
		{
			ret = waitReqDone (reqCtrl, g_timeOut, netInfo->nACSI);
		}
		else
		{
			CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "mvl_jread () Error, ret = 0x%X.", ret);
			mvl_free_req_ctrl (reqCtrl);	/* CRITICAL:		*/
			break;
		}

		if (ret != SD_SUCCESS)
		{
			CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "mvl_jread () Error, ret = 0x%X.", ret);
			mvl_free_req_ctrl (reqCtrl);	/* CRITICAL:		*/
			break;
		}
		else
		{
//			CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "mvl_jread OK");
			jread_resp = reqCtrl->u.jread.resp_info;
// 			CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "num_entry = %d", jread_resp->num_of_jou_entry);
// 			CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "more_follows = %d", jread_resp->more_follows);

			//扩展数据容器jread_resp->num_of_jou_entry
			if (pLD->JournalDatas.capacity <(pLD->JournalDatas.numOfData + jread_resp->num_of_jou_entry))
			{
				vector_add_capacity(&pLD->JournalDatas,jread_resp->num_of_jou_entry);
			}

			for (i = 0;  i < jread_resp->num_of_jou_entry;  i++)
			{
				jou_entry = &jread_resp->jou_entry[i];
				nEntryID = jou_entry->entry_id_len;

				if (nEntryID > 0)
				{
					strEntryID = "";
					CString strTmp;

					for (int nLenth = 0;nLenth<nEntryID;nLenth++)
					{
						strTmp.Format("%02X ",jou_entry->entry_id[nLenth]);
						strEntryID += strTmp;
					}

                    CLogPrint::LogString (XLOGLEVEL_TRACE,  strEntryID);
				}

//				CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "Journal Entry # %d:    entry_id_len = %d", i, jou_entry->entry_id_len);
				
				convert_btod_to_timet(jou_entry->occur_time, tmEvent);
				strEntryTime.Format("%d-%d-%d %d:%d:%d.%d",tmEvent.year, tmEvent.month, tmEvent.day, tmEvent.hour
					, tmEvent.minute, tmEvent.second, tmEvent.ms);
// 				CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "      occur_time = %s", strEntryTime);
// 				CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "      entry_form_tag = %d", jou_entry->entry_form_tag);
			
				//new LD_JOURNAL_DATA对象  pJournalData
			
				if (jou_entry->entry_form_tag == 2)
				{
					if (jou_entry->ef.data.list_of_var_pres)
					{
						if (jou_entry->ef.data.num_of_var>0)
						{
							char szLcbname[100] = {};//用于存放日志控制块名称
							strLogEntryName = jou_entry->ef.data.evcon_name.obj_name.item_id;
							j = strLogEntryName.ReverseFind('$');
							bSymbol2 = (strSelectPath.Find(strLogEntryName.Mid(j+1)) != -1);

							if (bSymbol1 || bSymbol2)
							{
								nEntryNum++;
								vector_set_add_data(&pLD->JournalDatas,(LPVOID*)&pJournalData,(sizeof(LD_JOURNAL_DATA)));
								memcpy(pJournalData->EntryID, jou_entry->entry_id, jou_entry->entry_id_len);
								pJournalData->occur_time = jou_entry->occur_time;
								pJournalData->numData = jou_entry->ef.data.num_of_var;
                                mms_str_set(&pJournalData->LogCtrl,strLogEntryName.GetString());
								find_lcbName(strLogEntryName,szLcbname);
								CString strDataSet = find_dataset_by_loginfo(&pLD->JournalCtrls,szLcbname/*mms_string(&pJournalData->LogCtrl)*/);
                                mms_str_set(&pJournalData->DataSetName,strDataSet.GetString());
								
								
// 								nTmp = strLogEntryName.ReverseFind('$');
// 
// 								if (nTmp != -1)
// 									pLogCtrlName = (jou_entry->ef.data.evcon_name.obj_name.item_id + nTmp);
// 								else
// 									pLogCtrlName = jou_entry->ef.data.evcon_name.obj_name.item_id;

								////new pJournalData的tagDA对象，个数jou_entry->ef.data.num_of_var
								pNewDA = (tagDA*)malloc(jou_entry->ef.data.num_of_var * sizeof(tagDA));
								memset(pNewDA,0,jou_entry->ef.data.num_of_var * sizeof(tagDA));
								pJournalData->DAValue = pNewDA;

								for (j = 0;  j < jou_entry->ef.data.num_of_var;  j++)
								{
									CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "            Var # %d: var_tag = %s   value_spec.len = %d", j,jou_entry->ef.data.list_of_var[j].var_tag
										, jou_entry->ef.data.list_of_var[j].value_spec.len);
									//CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "Var # %d: value_spec.len = %d", j,jou_entry->ef.data.list_of_var[j].value_spec.len);
									pRptData = jou_entry->ef.data.list_of_var[j].value_spec.data;

									//FindDA  根据数据路径查找：jou_entry->ef.data.list_of_var[j].var_tag：遍历当前LD下的所有数据集下的数据对象，匹配ID
									//pNewDA = 克隆一个DA

									if (strLogEntryName.IsEmpty()/*pLogCtrlName == NULL*/)//zhow20180320 南京银山厂家未返回日志控制块信息，导致查询出错
									{
										strDataSet = find_dataset_by_valuepath(pLD,jou_entry->ef.data.list_of_var[j].var_tag);
										strLogEntryName = find_logctrl_by_datasetinfo(&pLD->JournalCtrls,strDataSet);
                                        mms_str_set(&pJournalData->LogCtrl,strLogEntryName.GetString());
                                        mms_str_set(&pJournalData->DataSetName,strDataSet.GetString());
										find_lcbName(strLogEntryName,szLcbname);
// 										nTmp = strLogEntryName.ReverseFind('$');
// 
// 										if (nTmp != -1)
// 											pLogCtrlName = mms_str_pos(&pJournalData->LogCtrl,nTmp);
// 										else
// 											pLogCtrlName = jou_entry->ef.data.evcon_name.obj_name.item_id;
									}

									CString strTmp;
									strTmp = jou_entry->ef.data.list_of_var[j].var_tag;//zhouhj 20180320 对于银山的设备 此路径包括LD的名称，此处将其去掉
									nTmp = strTmp.Find('/');

									if (!My_Pare_JournalID_LD(pLD,&nNumDA,&pDA,&nDsIndex,szLcbname,&jou_entry->ef.data.list_of_var[j].var_tag[nTmp+1]))//查找成功复制，不成功不复制
									{
										mms_CopyData(pDA,&pNewDA[j],TRUE);
										DecodeOneApplyMember_Ex(&pRptData, &pNewDA[j]);
									}
									else
										mms_str_set(&pNewDA[j].DAValue.mmsName,jou_entry->ef.data.list_of_var[j].var_tag);
									
//									nEntrySize = jou_entry->ef.data.list_of_var[j].value_spec.len;
									strEntryPath = jou_entry->ef.data.list_of_var[j].var_tag;
									InsertJournalListCtrl_UI(nEntryNum ,nViewListIndex ,strEntryID ,mms_string(&pJournalData->LogCtrl),strEntryTime,&pNewDA[j]);
									nViewListIndex++;
								}
							}
						}
					}
				}
				else
				{
					CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "annotation = %s",jou_entry->ef.annotation);
				}
			}	/* end "loop"	*/
		}


		if (jread_resp->more_follows == 0)
		{
			mvl_free_req_ctrl (reqCtrl);	/* CRITICAL:		*/
			break;
		}

		//最后一个记录的时间和索引号
		if (jread_resp->num_of_jou_entry != 0)//zhouhj20180119
		{
		jou_entry = &jread_resp->jou_entry[jread_resp->num_of_jou_entry-1];
		jread_req.sa_entry_pres = 1;
		jread_req. time_spec = jou_entry->occur_time;
		jread_req.entry_spec_len = jou_entry->entry_id_len;
		memcpy(entry_id, jou_entry->entry_id, jread_req.entry_spec_len);
		jread_req.entry_spec =entry_id;
		}

		mvl_free_req_ctrl (reqCtrl);	/* CRITICAL:		*/
	}

	CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "查询到的日志总条目数: %d",nEntryNum);
	return SD_SUCCESS;
}

ST_RET CMmsApi::MMS_UploadFile(CFuncParamEx *pFuncParaEx)
{
	ST_INT nDvIndex,ret;
	CString strSrcFilePath;
	strSrcFilePath = pFuncParaEx->get_Path();

	if (!IsFileExist(strSrcFilePath))
	{
        CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "文件路径 %s 不存在;",strSrcFilePath.GetString());
		return SD_FAILURE;
	}

	MVL_NET_INFO *net_info;
	MVL_REQ_PEND *reqCtrl;
	CString strDevicePath;
	long nIndex = strSrcFilePath.ReverseFind('\\');
    strDevicePath = _T("/UPLOAD/") + strSrcFilePath.Mid(nIndex+1);
	nDvIndex = pFuncParaEx->get_DevIndex();
	net_info = (MVL_NET_INFO *)acsi_ctrl_table[nDvIndex].pnet_info;
	char *pszSrcFilePath = NULL,*pszDevicePath = NULL;
	CString_to_char(strSrcFilePath,&pszSrcFilePath);
	CString_to_char(strDevicePath,&pszDevicePath);
	ret = mvla_obtfile(net_info,pszSrcFilePath,pszDevicePath,&reqCtrl);

	if (ret == SD_SUCCESS)
		ret = waitReqDone (reqCtrl, 300, nDvIndex);//文件升级最大超时设置为300s,方式大文件上传失败

	mvl_free_req_ctrl (reqCtrl);

    CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "文件上传路径: %s ;",strSrcFilePath.GetString());

	delete pszSrcFilePath;
	delete pszDevicePath;
	return ret;
}

void CMmsApi::GetLDNameAndDescPath(MMS_DATA_NODE* childNode,CString &strDescPath)
{
	ASSERT(childNode!=NULL);

	if (childNode->pParent != NULL)
	{
		if (strDescPath.IsEmpty())
		{
			strDescPath = mms_string(&childNode->name);
		}
		else
		{
			strDescPath = _T("$") + strDescPath;
			strDescPath = mms_string(&childNode->name) + strDescPath;
		}

		GetLDNameAndDescPath(childNode->pParent,strDescPath);
	}
	else
	{
		strDescPath = _T("$") + strDescPath;
		strDescPath = mms_string(&childNode->name) + strDescPath;
	}
}


//////////////////////////////////////////////////////////////////////////
//2022-10-12  lijunqing  便于向LINUX移植，将平台相关的代码汇总到基类对象

void CMmsApi::InitReadLDeviceFuncParas(ST_INT nDeviceIndex, long nLDeviceIndex)
{
	set_OnlyReadValue(SD_FALSE);
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	if (nLDeviceIndex > pDevice->numLD - 1)
	{
		return;
	}

	LD_NODE *pLD = &pDevice->LD[nLDeviceIndex];
	for (int i=0;i<pLD->numDaSet;i++)
	{
		m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDeviceIndex, FuncID_Read, i, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	}
}

// 2013-3-4  重新枚举定值的数据
void CMmsApi::InitReadLDProtFuncParas(ST_INT nDeviceIndex, long nLDeviceIndex)
{
	set_OnlyReadValue(SD_FALSE);
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	if (nLDeviceIndex > pDevice->numLD - 1)
	{
		return;
	}

	LD_NODE *pLD = &pDevice->LD[nLDeviceIndex];
	CString strName(pLD->LDName);

	//if (strName.Find(_T("PROT"))!=-1)
	if (mms_IsSettingsDS(strName))
	{
		for (int i=0; i<pLD->numDaSet; i++)
		{
			m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDeviceIndex, FuncID_Read, i, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}
}

void CMmsApi::InitReadLDeviceDatasFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDAType)
{
	set_OnlyReadValue(SD_FALSE);
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	if (nLDIndex > pDevice->numLD - 1)
	{
		return;
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nDsDAType, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitReadLDeviceValuesFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDAType)
{
	set_OnlyReadValue(TRUE);
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	if (nLDIndex > pDevice->numLD - 1)
	{
		return;
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nDsDAType,/* m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

//自动测试模式下，联机之后，枚举设备的逻辑设备，在枚举逻辑设备成功之后，在枚举逻辑设备的其他参数
void CMmsApi::InitLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bOnlyLink)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	CFuncParam *pParam = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0, FuncID_Link, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	pParam->set_ServerCmd();

	if (bOnlyLink)
	{
		return;
	}
	else
	{
		m_oFuncParamEx[nDeviceIndex].SetsConnectDevice(TRUE);
	}

	pDevice->nSetRunSGIndexState = 1;

	if (!pDevice->bCanReConnect)
	{
		set_OnlyReadValue(SD_FALSE);
		InitEnumLDFuncPara(nDeviceIndex, FALSE);
	}
}

void CMmsApi::InitLinkDeviceFuncPara_AutoTest(ST_INT nDeviceIndex, BOOL bOnlyLink)
{
	if (m_oFuncParamEx[nDeviceIndex].m_hThread_Proc_Data == NULL)
	{
		CreateDataProcThread(&m_oFuncParamEx[nDeviceIndex]);
	}

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	CFuncParam *pParam = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0, FuncID_Link, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	pParam->set_ClientCmd();

	//此种方式，只有在通讯命令Connect的时候被调用
	if (bOnlyLink)
	{
		return;
	}
	else
	{
		m_oFuncParamEx[nDeviceIndex].SetsConnectDevice(TRUE);
	}

	pDevice->nSetRunSGIndexState = 1;

	if (!pDevice->bCanReConnect)
	{
		set_OnlyReadValue(SD_FALSE);
		InitEnumLDFuncPara(nDeviceIndex, FALSE);
	}
}

void CMmsApi::ExitAllConnFunc(ST_INT nDeviceIndex)
{
	CTickCount32 oTickCount;
	m_oFuncParamEx[nDeviceIndex].m_bExitFunc = TRUE;
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	m_oFuncParamEx[nDeviceIndex].m_posCurrFuncPara = NULL;
	long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();
	long nIndex = 0;

	while((nFuncID != FuncID_TestProc)&&(nIndex<10))
	{
		oTickCount.DoEvents(500);
		nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();
		nIndex++;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"结束装置%d全部通讯命令完成",nDeviceIndex);

	m_oFuncParamEx[nDeviceIndex].m_bExitFunc = FALSE;
}

void CMmsApi::InitUnLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bAutoTest, BOOL bOnlyLink)
{
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();

	if (nFuncID != FuncID_TestProc)
	{
		ExitAllConnFunc(nDeviceIndex);
	}

	CFuncParam *pParam = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0, FuncID_UnLink, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);

	if (bAutoTest)
	{
		pParam->set_ClientCmd();
	}
	else
	{
		pParam->set_ServerCmd();
	}

	if (!bOnlyLink)
	{
		m_oFuncParamEx[nDeviceIndex].SetsConnectDevice(TRUE);
	}
}

void CMmsApi::InitEnumLNFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0,  FuncID_EnumLN,   dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitEnumLDFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	set_OnlyReadValue(SD_FALSE);

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	if (pDevice->nHasDeviceModel != 1)
	{
		m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0,  FuncID_EnumLD,   dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	}
	else
	{
		if (g_bMmsEnumLDAfterReadXml)
		{
			m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, 0,  FuncID_EnumLD,   dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1, FuncID_GetSGNum, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitReadDeviceFuncParas(ST_INT nDeviceIndex, BOOL bReadAll, BOOL bFreeFuncParas)
{
	set_OnlyReadValue(SD_FALSE);
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	long nLDIndex = 0;
	long nLdCount = pDevice->numLD;

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
	{
		LD_NODE *pLD = &pACSINode[nDeviceIndex].LD[nLDIndex];
		for (int i=0;i<pLD->numDaSet;i++)
		{
			if (bReadAll)
			{
				m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, i, /*m_pMmsMsgRcvWnd->m_hWnd, */WM_Notify_Msg);

			}
			else
			{
				if (m_oMmsEngineConfig.IsDatasetUse(pLD->DataInfo[i].DataSetID))
				{
					m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, i, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
				}
			}
		}
	}
}

void CMmsApi::InitDeviceReadDatasFuncParas(ST_INT nDeviceIndex, ST_INT nTypeID)
{
	set_OnlyReadValue(SD_FALSE);
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	long nLDIndex = 0;
	long nLdCount = pDevice->numLD;
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
	{
		m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nTypeID,/* m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	}
}


void CMmsApi::InitWriteDatasFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDAType)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	if (nLDIndex > pDevice->numLD - 1)
	{
		return;
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Write, nDsDAType, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

//读定值区号
void CMmsApi::InitReadLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	if (nLDIndex > pDevice->numLD - 1)
	{
		return;
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_GetSGNum, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

//写定值区号
void CMmsApi::InitWriteLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nZone)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSGNum, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_SGID(nZone);
}

void CMmsApi::InitWriteCurrSetsFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, long nZone, BOOL bDeleteAll)
{
	if (nDsIndex < 0)
	{
		nDsIndex = GetDsIndex(nDeviceIndex, nLDIndex, dsID_Setting);
	}

	if (bDeleteAll)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	ST_INT nSEIndex = pDevice->nRunSGIndex;
	ST_INT nCurrSGIndex = pDevice->nRunSGIndex; //编辑当前运行的区
	//	HWND hWnd = m_pMmsMsgRcvWnd->m_hWnd;
	CFuncParam *pFuncPara=NULL;

	if (nZone > 0)
	{
		nSEIndex = nZone;
	}

    CLogPrint::LogFormatString(XLOGLEVEL_INFOR,g_sLangTxt_Monitor.GetString()/* _T("监视【%d】 RunSGIndex=【%08x】")*/,nDeviceIndex, pDevice->nRunSGIndex);

	//如果两个数据一致，表示正常，否则表示固化定值后没有切换回来，或者其他情况
	//运行区与编辑区相同，则切换运行区
	BOOL bChangeZone = FALSE;

	if ((g_nCanWriteActiveSG==0)&&(nCurrSGIndex == nSEIndex))//zhouhj  在不能改运行区，并且当前运行区与需要修改的定值区相同的情况下，才做切区的操作
	{
		//		if (nCurrSGIndex == nSEIndex)
		{
			nCurrSGIndex++;
		}

		if (nCurrSGIndex >= pDevice->nSGNum)
		{
			nCurrSGIndex = 1;
		}

		pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSGNum, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
		pFuncPara->set_SGID(nCurrSGIndex);

		bChangeZone = TRUE;
	}


	//切换定值编辑区
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSENum, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_SEID(nSEIndex);

	//修改定值
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Write, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_SEID(nSEIndex);

	//定值固化
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CnfSetSE, nDsIndex, /*hWnd, */WM_Notify_Msg);
	pFuncPara->set_SEID(nSEIndex);

	//设置当前定值区
	if (bChangeZone)
	{
		pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_SetSGNum, nDsIndex, /*hWnd,*/ WM_Notify_Msg);
		pFuncPara->set_SGID(nSEIndex);
	}
}

//控制，压板、遥控、......
void CMmsApi::InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDaTypeID)
{
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];

	CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nDsDaTypeID, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}


void CMmsApi::InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	ST_INT nIndex = 0;
	LD_DATASET_INFO			*pDataInfo = pLD_NODE->DataInfo;

	for (nIndex=0; nIndex<pLD_NODE->numDaSet; nIndex++)
	{
		if (strstr(pDataInfo[nIndex].DataSetID, strDataType) != NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitCtrlWriteFuncParas(%d, %d, %s)"), nDeviceIndex, nLDIndex, pDataInfo[nIndex].DataSetID);
			CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nIndex,/* m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}

	// 	DeleteAllFuncParas();
	// 	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	// 
	// 	CFuncParam *pFuncPara = m_oFuncParams.AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nDsDaTypeID, m_pMmsMsgRcvWnd->m_hWnd, WM_Notify_Msg);
}

void CMmsApi::InitCtrlWriteFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bDeleteAll)
{
	if (bDeleteAll)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWrite, nDsIndex, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitCtrlWriteOneFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nDAIndex1, ST_INT nDAIndex2, ST_INT nDAValue1, ST_INT nDAValue2, ST_INT nTDelayAfterSel)
{
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_CtrlWriteOne, nDsIndex, nDAIndex1, nDAIndex2, nDAValue1, nDAValue2, nTDelayAfterSel, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitReadOneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nDataIndex, BOOL bDeleteAll)
{
	if (bDeleteAll)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	CFuncParam *pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(FuncID_ReadOne, nDeviceIndex, nLDIndex, nDsIndex, nDataIndex, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::ResetDevice(ST_INT nDeviceIndex, ST_INT nLDIndex)
{
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Reset, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

// 报告
void CMmsApi::InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, BOOL bFreeFuncParas)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	pDevice->hRptMsgWnd = (unsigned long)m_pMmsMsgRcvWnd->m_hWnd;
	pDevice->nRptMsg = WM_MMS_REPORT;

	long nLdCount = pDevice->numLD;

	if (bFreeFuncParas)
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

	// 2013-4-8  注意定值无相应的报告
	if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,nDsIndex))
		InitCallReportFuncParas(nDeviceIndex, nLDIndex, nDsIndex, bStart);
}

void CMmsApi::InitCallReportFlagDefault(ST_INT nDeviceIndex)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	long nLDIndex = 0;
	long nLdCount = pDevice->numLD;

	for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
	{
		LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

		for (int i=0; i<pLD->numDaSet; i++)
		{
			// 2013-4-8  注意定值无相应的报告
			if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,i))
				mms_SetReportFlag(nDeviceIndex, nLDIndex, i, TRUE);
		}
	}
}

void CMmsApi::InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart)
{
	//定值，则返回
	if (CheckCurSelIsSetting(nDeviceIndex,nLDIndex,nDsIndex))
	{
		return;
	}

	if ((!bStart) && (!mms_HasEnumDataSet(nDeviceIndex, nLDIndex, nDsIndex)))
	{
		return;
	}

	if (mms_GetDsDaDatasNum(nDeviceIndex, nLDIndex, nDsIndex) <= 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NotEnumDataSet.GetString()/*_T("【%d-%d-%d】没有枚举数据集")*/, nDeviceIndex, nLDIndex, nDsIndex);
		return;
	}

	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StartRpt, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_DSID(nDsIndex);//保护事件;遥信报告;压板报告;遥测报告;soe报告;故障信号;告警信号;通信工况;
	//	return;
	//
	// 	BOOL bIsReport = mms_GetReportFlag(nDeviceIndex, nLDIndex, nDsIndex);
	// 	BOOL bIsReportRet = mms_GetReportRet(nDeviceIndex, nLDIndex, nDsIndex);
	// 
	// 	if (bIsReportRet == bIsReport)
	// 	{
	// 		return;
	// 	}
	// 
	// 	if (bIsReport)
	// 	{
	// 		pFuncPara = m_oFuncParams.AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StartRpt, dsType_NULL, m_pMmsMsgRcvWnd->m_hWnd, WM_Notify_Msg);
	// 	}
	// 	else
	// 	{
	// 		pFuncPara = m_oFuncParams.AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StopRpt, dsType_NULL, m_pMmsMsgRcvWnd->m_hWnd, WM_Notify_Msg);
	// 	}
	// 
	// 	pFuncPara->set_DataType(nDsIndex);//保护事件;遥信报告;压板报告;遥测报告;soe报告;故障信号;告警信号;通信工况;
}

void CMmsApi::InitCallReportFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, UINT nBrcbIndex, BOOL bFreeFuncParas)
{
	//定值，则返回
	if (CheckCurSelIsSetting(nDeviceIndex,nLDIndex,nDsIndex))
	{
		return;
	}

	if (!mms_HasEnumDataSet(nDeviceIndex, nLDIndex, nDsIndex))
	{
		return;
	}

	if (mms_GetDsDaDatasNum(nDeviceIndex, nLDIndex, nDsIndex) <= 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NotEnumDataSet.GetString()/*_T("【%d-%d-%d】没有枚举数据集")*/, nDeviceIndex, nLDIndex, nDsIndex);
		return;
	}

	if (bFreeFuncParas)
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	pDevice->hRptMsgWnd = (unsigned long)m_pMmsMsgRcvWnd->m_hWnd;
	pDevice->nRptMsg = WM_MMS_REPORT;

	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StartRpt, dsType_NULL, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_DSID(nDsIndex);//保护事件;遥信报告;压板报告;遥测报告;soe报告;故障信号;告警信号;通信工况;
	pFuncPara->set_BrcbIndex(nBrcbIndex);
}

void CMmsApi::SetReportRet(CFuncParamEx *pFuncParaEx,BOOL bSucc, BOOL bStart_NotStop)
{
	if (bSucc)
	{
		int nDeviceIndex = pFuncParaEx->get_DevIndex();
		int nLDIndex = pFuncParaEx->get_LDvIndex();
		int nDsIndex = pFuncParaEx->get_DSID();

		if (bStart_NotStop)
		{
			BOOL b = mms_GetReportFlag(nDeviceIndex,nLDIndex,nDsIndex);
			mms_SetReportRet(nDeviceIndex,nLDIndex,nDsIndex, b);
		}
		else
		{
			mms_SetReportFlag(nDeviceIndex,nLDIndex,nDsIndex, FALSE);
			mms_SetReportRet(nDeviceIndex,nLDIndex,nDsIndex, FALSE);
		}
	}
}

BOOL CMmsApi::CheckCurSelIsSetting(int nDeviceIndex, int nLDIndex, int nDsIndex)
{
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
		return FALSE;

	CStringA strText(pLD->LDName);
	//if (strText.Find(_T("PROT"))!=-1)

	//兼容测控Ctrl下有定值：2017-11-2
	//if (mms_IsSettingsDS(strText))
	{
		LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
		CStringA str(pLD_INFO->DataSetID);

		if (str.Find("Setting")!=-1)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMmsApi::CheckCurSelIsParameter(int nDeviceIndex, int nLDIndex, int nDsIndex)
{
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
		return FALSE;

	CStringA strText(pLD->LDName);
	//if (strText.Find(_T("PROT"))!=-1)
	//if (mms_IsSettingsDS(strText))
	{
		LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
		CStringA str(pLD_INFO->DataSetID);
		if (str.Find("Parameter")!=-1)
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CMmsApi::CheckCurSelIsDout(int nDeviceIndex, int nLDIndex, int nDsIndex)
{
	LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);

	if (nDsIndex<0 || nDsIndex >= MAX_DASET_NUM)
		return FALSE;

	CStringA strText(pLD->LDName);
	//if (strText.Find(_T("PROT"))!=-1)
	//if (mms_IsSettingsDS(strText))
	{
		LD_DATASET_INFO *pLD_INFO = &pLD->DataInfo[nDsIndex];
		CStringA str(pLD_INFO->DataSetID);

		if (str.Find(key_dsDout) != -1)
		{
			return TRUE;
		}

		str.MakeUpper();
		if (str.Find(key_dsGOOSE) != -1)
		{
			return TRUE;
		}
	}

	return FALSE;
}


void CMmsApi::InitStopReportFuncParas(ST_INT nDeviceIndex, BOOL bFreeFuncParas)
{
	if (pACSINode == NULL)
	{
		return;
	}

	if (nDeviceIndex<0)
		return;

	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];

	if (pDevice == NULL)
	{
		return;
	}

	if (m_pMmsMsgRcvWnd !=NULL)
		pDevice->hRptMsgWnd = (unsigned long)m_pMmsMsgRcvWnd->m_hWnd;

	pDevice->nRptMsg = WM_MMS_REPORT;

	long nLDIndex = 0;
	long nLDCount = pDevice->numLD;

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	for (nLDIndex=0; nLDIndex<nLDCount; nLDIndex++)
	{
		LD_NODE *pLD = &(pACSINode[nDeviceIndex].LD[nLDIndex]);
		for (int i=0; i<pLD->numDaSet; i++)
		{
			// 2013-4-8  如果是定值无需停止
			if (!CheckCurSelIsSetting(nDeviceIndex,nLDIndex,i))
				InitStopReportFuncParas(nDeviceIndex, nLDIndex, i);
		}
	}
}

void CMmsApi::InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
	if (!mms_HasEnumDataSet(nDeviceIndex, nLDIndex, nDsIndex))
	{
		return;
	}

	if (mms_GetDsDaDatasNum(nDeviceIndex, nLDIndex, nDsIndex)<=0)
	{
		return;
	}

	CFuncParam *pFuncPara = NULL;
	BOOL bIsReport = mms_GetReportFlag(nDeviceIndex, nLDIndex, nDsIndex);
	BOOL bIsReportRet = mms_GetReportRet(nDeviceIndex, nLDIndex, nDsIndex);

	if (!(bIsReportRet && bIsReport))
	{
		//return;
	}

	// 	HWND hWnd = NULL;
	// 	if (m_pMmsMsgRcvWnd)
	// 		hWnd = m_pMmsMsgRcvWnd->m_hWnd;

	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_StopRpt, dsType_NULL,/* hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_DSID(nDsIndex);//保护事件;遥信报告;压板报告;遥测报告;soe报告;故障信号;告警信号;通信工况;
}

BOOL CMmsApi::CallFirstFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];
	pFuncParaEx->m_posCurrFuncPara = pFuncParaEx->GetHeadPosition();
	long nCount = m_oFuncParamEx[nDeviceIndex].GetCount();
	//	m_posCurrFuncPara = m_oFuncParamEx[nDeviceIndex].GetHeadPosition();

	ProgDlg_CallFirstFunc(nDeviceIndex);

	return CallCurrFunc(nDeviceIndex);
}

void CMmsApi::ProgDlg_CallFirstFunc(long nDeviceIndex)
{

}

ST_INT CMmsApi::GetDsIndex(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	ST_INT nIndex = 0;
	LD_DATASET_INFO			*pDataInfo = pLD_NODE->DataInfo;

	for (nIndex=0; nIndex<pLD_NODE->numDaSet; nIndex++)
	{
		if (strstr(pDataInfo[nIndex].DataSetID, strDataType) != NULL)
		{
			return nIndex;
		}
	}

	return -1;
}

void CMmsApi::InitReadFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	ST_INT nIndex = 0;
	LD_DATASET_INFO			*pDataInfo = pLD_NODE->DataInfo;

	for (nIndex=0; nIndex<pLD_NODE->numDaSet; nIndex++)
	{
		if (strstr(pDataInfo[nIndex].DataSetID, strDataType) != NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                                       , _T("InitCtrlWriteFuncParas(%d, %d, %s)")
                                       , nDeviceIndex, nLDIndex, pDataInfo[nIndex].DataSetID);

			CFuncParam *pFuncPara = NULL;
			pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nIndex, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}
}

void CMmsApi::InitReadJournalState(ST_INT nDeviceIndex, ST_INT nLDeviceIndex, const CString &strJournalName, HWND hWnd)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_LOG_INFO *pszLogInfo = pDevice->LD[nLDeviceIndex].JournalCtrls.LogInfo;
	int nNum = pDevice->LD[nLDeviceIndex].JournalCtrls.numData;
	CString strLogRef;

	if (pszLogInfo == NULL)
	{
		return;
	}

	for (int nLen = 0;nLen<nNum;nLen++)
	{
		if (strcmp(mms_string(&pszLogInfo[nLen].Name),strJournalName.GetString()) == 0)
		{
			strLogRef = mms_string(&pszLogInfo[nLen].logRef);
			break;
		}
	}

	if (strLogRef.IsEmpty())
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                                   ,_T("初始化读日志数目出错,对应日志索引未查找到,nDeviceIndex=%ld;nLDeviceIndex=%ld;strJournalName=%s;")
                                   ,nDeviceIndex,nLDeviceIndex,strJournalName.GetString());
	}

	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	// 	if (hWnd == NULL)
	// 	{
	// 		hWnd = m_pMmsMsgRcvWnd->m_hWnd;
	// 	}

	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDeviceIndex, FuncID_ReadJournalCount, -1, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_vmd_spec(strJournalName);
	pFuncPara->set_journal_ref(strLogRef);
}

void CMmsApi::InitReadJournal(ST_INT nDeviceIndex, ST_INT nLDeviceIndex, const CString &strJournalName
									  , ST_INT bStart, ST_INT nStartType, CTime &tmStart, long long nStartEntry
									  , ST_INT bEnd, ST_INT nEndType, CTime &tmEnd, ST_INT nEntryNum)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_LOG_INFO *pszLogInfo = pDevice->LD[nLDeviceIndex].JournalCtrls.LogInfo;
	int nNum = pDevice->LD[nLDeviceIndex].JournalCtrls.numData;
	CString strLogRef;

	if (pszLogInfo == NULL)
	{
		return;
	}

	for (int nLen = 0;nLen<nNum;nLen++)
	{
		if (strcmp(mms_string(&pszLogInfo[nLen].Name),strJournalName.GetString()) == 0)
		{
			strLogRef = mms_string(&pszLogInfo[nLen].logRef);
			break;
		}
	}

	if (strLogRef.IsEmpty())
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                                   ,_T("初始化读日志数目出错,对应日志索引未查找到,nDeviceIndex=%ld;nLDeviceIndex=%ld;strJournalName=%s;")
                                   ,nDeviceIndex,nLDeviceIndex,strJournalName.GetString());
	}

	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDeviceIndex, strJournalName,bStart ,nStartType ,tmStart ,nStartEntry ,bEnd ,nEndType ,tmEnd, nEntryNum, FuncID_ReadJournal, -1, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
	pFuncPara->set_journal_ref(strLogRef);
	// 	pFuncPara = m_oFuncParams.AddFuncPara(nDeviceIndex, nLDeviceIndex, FuncID_ReadJournal, -1, m_pMmsMsgRcvWnd->m_hWnd, WM_Notify_Msg);
	// 	MMS_BTOD btod;
	// 	convert_timet_to_btod(tmStart, btod);
	// 	pFuncPara->set_start_time(btod);
	// 	convert_timet_to_btod(tmEnd, btod);
	// 	pFuncPara->set_end_time(btod);
	// 	
	// 	pFuncPara->set_range_start_pres(bStart);
	// 	pFuncPara->set_start_tag(nStartType);
	// 	pFuncPara->set_start_entry(nStartEntry);
	// 
	// 	pFuncPara->set_range_stop_pres(bEnd);
	// 	pFuncPara->set_stop_tag(nEndType);
	// 	pFuncPara->set_num_of_entries(nEntryNum);
	// 
	// 	pFuncPara->set_vmd_spec(strJournalName);
	// 	pFuncPara->set_FuncID(FuncID_ReadJournal);
}

void CMmsApi::InitGetFileDir(ST_INT nDeviceIndex, const CString &strPath,BOOL bOnlyReadCfg)//参数2指装置内的目录，为空表示读根目录下的所有文件及文件夹
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	pDevice->FileDir.nType = 1;
	pDevice->FileDir.bIsNew = 1;

	long nFuncID = m_oFuncParamEx[nDeviceIndex].get_FuncID();

	if (nFuncID != FuncID_TestProc)
	{
		ExitAllConnFunc(nDeviceIndex);
	}

	// 	CFuncParam *pFuncPara = NULL;
	// 	m_FuncParam.Set_Path(strPath);//zhow:20180107 传递读取路径
	// // 	CFuncParam *pParam = (CFuncParam*)m_oFuncParams.GetAt(m_posCurrFuncPara);
	// // 	pParam->Set_Path(strPath);//zhow:20180107 传递读取路径
	// 	ptagFileDir pFileDir = &pDevice->FileDir;
	// 	StrCpy(pFileDir->PathName ,strPath);

	/*pFuncPara = */m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1, strPath ,FuncID_ReadDir, -1,bOnlyReadCfg, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitUploadFile(ST_INT nDeviceIndex, const CString &strPath) //参数2表示上传文件在电脑中的路径，装置内的路径固定为'/UPLOAD/'文件夹下
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1, strPath ,FuncID_UploadFile, -1, FALSE,/*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitUploadFiles(ST_INT nDeviceIndex,const CStringArray &arrPaths) //参数2表示上传文件在电脑中的路径，装置内的路径固定为'/UPLOAD/'文件夹下
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	long nSize = arrPaths.GetSize();
	long nIndex = 0;
	CString strCurFilePath;

	for (nIndex = 0;nIndex<nSize;nIndex++)
	{
		strCurFilePath = arrPaths.GetAt(nIndex);

		if (IsFileExist(strCurFilePath))
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitUploadFiles: path=%s"), strCurFilePath.GetString());
			m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1, strCurFilePath ,FuncID_UploadFile, -1, FALSE,/*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}
}

void CMmsApi::InitReadDevice(ST_INT nDeviceIndex, BOOL bFreeFuncParas) 
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1 ,FuncID_ReadDevice, -1,/* m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitDvmEnum(ST_INT nDeviceIndex,const CString &strFileName,BOOL bEnumSetting,BOOL bEnumRelayEna,BOOL bEnumParameter,
								  BOOL bEnumRelayAin,BOOL bEnumRelayDin,BOOL bEnumTripInfor,BOOL bEnumAlarm_Warning,BOOL bEnumRelayBlk,
								  BOOL bEnumRelayState,BOOL bEnumRelayFunEn,BOOL bEnumLog,BOOL bDevStdMsg,BOOL bFreeFuncParas) 
{
	//2023-3-16  lijunqing

	InitReadDevice(nDeviceIndex, bFreeFuncParas);

	return;


	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];

	if (bFreeFuncParas)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	long nLDIndex = 0;
	long nLdCount = pDevice->numLD;
	CFuncParam *pFuncPara = NULL;
	m_bOnlyReadValue = FALSE;

	for (nLDIndex=0; nLDIndex<nLdCount; nLDIndex++)
	{
		LD_NODE *pLD = &pACSINode[nDeviceIndex].LD[nLDIndex];

		for (int i=0;i<pLD->numDaSet;i++)
		{
			if ((strstr(pLD->DataInfo[i].DataSetID,dsSetting) != NULL)&&bEnumSetting)
			{
				m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, i, /*m_pMmsMsgRcvWnd->m_hWnd, */WM_Notify_Msg);
				pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read_SET, i, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);

				if (pDevice->nRunSGIndex > 0)
				{
					pFuncPara->set_SEID(pDevice->nRunSGIndex);
					pFuncPara->set_SGID(pDevice->nRunSGIndex);
				}
				else
				{
					pFuncPara->set_SEID(1);
					pFuncPara->set_SGID(1);
				}	
			}
			else if (((strstr(pLD->DataInfo[i].DataSetID,dsRelayEna) != NULL)&&bEnumRelayEna)||((strstr(pLD->DataInfo[i].DataSetID,dsParameter) != NULL)&&bEnumParameter)
				||((strstr(pLD->DataInfo[i].DataSetID,dsRelayAin) != NULL)&&bEnumRelayAin)||((strstr(pLD->DataInfo[i].DataSetID,dsRelayDin) != NULL)&&bEnumRelayDin)
				||((strstr(pLD->DataInfo[i].DataSetID,dsTripInfo) != NULL)&&bEnumTripInfor)||((strstr(pLD->DataInfo[i].DataSetID,dsAlarm) != NULL)&&bEnumAlarm_Warning)
				||((strstr(pLD->DataInfo[i].DataSetID,dsWarning) != NULL)&&bEnumAlarm_Warning)||((strstr(pLD->DataInfo[i].DataSetID,dsRelayBlk) != NULL)&&bEnumRelayBlk)
				||((strstr(pLD->DataInfo[i].DataSetID,dsRelayState) != NULL)&&bEnumRelayState)||((strstr(pLD->DataInfo[i].DataSetID,dsRelayFunEn) != NULL)&&bEnumRelayFunEn)
				||((strstr(pLD->DataInfo[i].DataSetID,dsLog) != NULL)&&bEnumLog)||((strstr(pLD->DataInfo[i].DataSetID,dsDevStdMsg) != NULL)&&bDevStdMsg))
			{
				m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, i, /*m_pMmsMsgRcvWnd->m_hWnd, */WM_Notify_Msg);
			}
			else
			{
				mms_Free_LD_DATASET_INFO(&pDevice[nDeviceIndex].LD[nLDIndex].DataInfo[i]);
			}
		}
	}

	if (!strFileName.IsEmpty())
	{
		pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, FuncID_DvmEnum, /*m_pMmsMsgRcvWnd->m_hWnd, */WM_Notify_Msg);
		pFuncPara->Set_FileName(strFileName.GetString());
	}
}

void CMmsApi::InitGetFilePara(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName, const CString &strPostfix)
{
	// 	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	// 	XMMS_FILE_SYS_OBJ *pFileDir = &pDevice->FileDir;
	// 	CString strFileNameAll = "";
	// 	int nLenth = pFileDir->nCount,nIndex;
	// 
	// 	for (nIndex = 0;nIndex<nLenth;nIndex++)
	// 	{
	// 		strFileNameAll += pFileDir->dir[nIndex].filename;
	// 	}
	// 
	CString strNewFileDevicePath;
	strNewFileDevicePath = ChangeFilePostfix(strFileName, strPostfix);
	// 	nIndex = strFileNameAll.Find(strFileName);//防止输入的文件目录路径错误
	// 
	// 	if (nIndex == -1)
	// 		return;

	//	CFuncParam *pFuncPara = NULL;
	/*pFuncPara = */m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1,strPath,strNewFileDevicePath , FuncID_ReadFile, -1, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);//zhow:20180108
	// 	strFileName = ChangeFilePostfix(strFileName, strPostfix);
	// 	pFuncPara->Set_FileName(strFileName.GetString());
	// 	pFuncPara->Set_Path(strPath);
}



void CMmsApi::InitGetFile(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	::CreateAllDirectories(strPath);

	CString strPostFix;
	CFuncParam *pFuncPara = NULL;
	strPostFix = ParseFilePostfix(strFileName);

	if (strPostFix == RECORD_FILE_POSTFIX_CFG || strPostFix == RECORD_FILE_POSTFIX_HDR
		|| strPostFix == RECORD_FILE_POSTFIX_DAT || strPostFix == RECORD_FILE_POSTFIX_MID
		|| strPostFix == RECORD_FILE_POSTFIX_DES)
	{
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_CFG);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_HDR);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DAT);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_MID);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DES);
	}
	else if (strPostFix == RECORD_FILE_POSTFIX_CFG_UPPER || strPostFix == RECORD_FILE_POSTFIX_HDR_UPPER
		|| strPostFix == RECORD_FILE_POSTFIX_DAT_UPPER || strPostFix == RECORD_FILE_POSTFIX_MID_UPPER
		|| strPostFix == RECORD_FILE_POSTFIX_DES_UPPER)
	{
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_CFG_UPPER);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_HDR_UPPER);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DAT_UPPER);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_MID_UPPER);
		InitGetFilePara(nDeviceIndex, strPath, strFileName, RECORD_FILE_POSTFIX_DES_UPPER);
	}
	else
		m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, -1,strPath,strFileName , FuncID_ReadFile, -1,/* m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);//zhow:20180108
}

void CMmsApi::InitReadFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nDsIndex, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitReadFuncPara_Set(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nZone, ST_INT nRunSG, BOOL bDeleteAll)
{
	if (bDeleteAll)
	{
		m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	}

	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read_SET, nDsIndex, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);

	pFuncPara->set_SEID(nZone);
	pFuncPara->set_SGID(nRunSG);
}


void CMmsApi::InitReadFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDataType)
{
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Read, nDataType, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	ST_INT nIndex = 0;
	LD_DATASET_INFO			*pDataInfo = pLD_NODE->DataInfo;

	for (nIndex=0; nIndex<pLD_NODE->numDaSet; nIndex++)
	{
		if (strstr(pDataInfo[nIndex].DataSetID, strDataType) != NULL)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("InitCtrlWriteFuncParas(%d, %d, %s)"), nDeviceIndex, nLDIndex, pDataInfo[nIndex].DataSetID);
			CFuncParam *pFuncPara = NULL;
			pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Write, nIndex, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
		}
	}
}

void CMmsApi::InitWriteFuncParasSingle(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex)
{
	ACSI_NODE *pDevice = &pACSINode[nDeviceIndex];
	LD_NODE *pLD_NODE = &pDevice->LD[nLDIndex];
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_WriteSingle, nDsIndex, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

void CMmsApi::InitWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDataType)
{
	m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();
	CFuncParam *pFuncPara = NULL;
	pFuncPara = m_oFuncParamEx[nDeviceIndex].AddFuncPara(nDeviceIndex, nLDIndex, FuncID_Write, nDataType, /*m_pMmsMsgRcvWnd->m_hWnd,*/ WM_Notify_Msg);
}

BOOL CMmsApi::CallNextFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		mmsi_FunctionCall(nDeviceIndex,FuncID_TestProc);
		return FALSE;
	}

	pFuncParaEx->GetNext(pFuncParaEx->m_posCurrFuncPara);
	return CallCurrFunc(nDeviceIndex);
}

BOOL CMmsApi::CallCurrFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		mmsi_FunctionCall(nDeviceIndex,FuncID_TestProc);
		return FALSE;
	}

	CFuncParam *pParam = (CFuncParam*)m_oFuncParamEx[nDeviceIndex].GetAt(pFuncParaEx->m_posCurrFuncPara);

	ValidateCurrFunc(nDeviceIndex);
	m_oFuncParamEx[nDeviceIndex].InitPara(pParam);//memcpy(&m_FuncParam, pParam, sizeof(m_FuncParam));

	mmsi_FunctionCall(nDeviceIndex,pParam->get_FuncID());
	m_oFuncParamEx[nDeviceIndex].BeginExecDataProc(0);

	ProgDlg_CallCurrFunc(nDeviceIndex);

	return TRUE;
}

void CMmsApi::ProgDlg_CallCurrFunc(long nDeviceIndex)
{

}

void CMmsApi::ValidateCurrFunc(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		return;
	}

	CFuncParam *pParam = (CFuncParam*)m_oFuncParamEx[nDeviceIndex].GetAt(pFuncParaEx->m_posCurrFuncPara);

	if (pParam->get_FuncID() == FuncID_GetSGNum || pParam->get_FuncID() == FuncID_SetSGNum)
	{
		ValidateCurrFunc_ReadZone(pParam);
	}
}

BOOL CMmsApi::IsFuncsAllFinish(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	if (pFuncParaEx->m_posCurrFuncPara == NULL)
	{
		ProgDlg_StopProgress(nDeviceIndex);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CMmsApi::ProgDlg_StopProgress(long nDeviceIndex)
{

}

BOOL CMmsApi::IsInFuncsCallState(long nDeviceIndex)
{
	CFuncParamEx *pFuncParaEx = &m_oFuncParamEx[nDeviceIndex];

	return (pFuncParaEx->m_posCurrFuncPara != NULL);
}

void CMmsApi::OnCallFuncError(long nDeviceIndex)
{
	mmsi_FunctionCall(nDeviceIndex,FuncID_TestProc);
}

void CMmsApi::OnUnlink(CFuncParamEx *pFuncParaEx)
{
	if (g_bMmsEngineDebugMode)
	{
		return;
	}

	ACSI_NODE *pDevice = get_DevACSI_NODEPtr(pFuncParaEx);

	if (pDevice->bTestLinkState)
	{
		return;
	}

	if (pDevice != NULL)
	{
		pDevice->bConnect = FALSE;
	}
}

void CMmsApi::ValidateCurrFunc_ReadZone(CFuncParam *pParam)
{
	ST_INT nDvIndex = pParam->get_DevIndex();
	ST_INT nLdIndex = pParam->get_LDvIndex();

	if (nLdIndex != -1)
	{//验证当前的数据集是不是保护
		ACSI_NODE *pDevice = &pACSINode[nDvIndex];
		ASSERT(pDevice != NULL);
		LD_NODE   *pLD = &(pDevice->LD[nLdIndex]);

		if (pLD != NULL)
		{
			if (mms_IsSettingsDS(pLD->LDName))
			{
				return;
			}
		}
	}

	nLdIndex = mms_FindLDeviceIndex(nDvIndex, "prot");//zhowTest20180111

	if (nLdIndex == -1)
	{
		nLdIndex = mms_FindLDeviceIndex(nDvIndex, "pqld");//zhowTest20180111
	}

	if (nLdIndex == -1)
	{
		nLdIndex =  mms_FindLDeviceIndex(nDvIndex, "rcd");
	}

	if (nDvIndex == -1)
	{
		pParam->set_DevIndex(pParam->get_DevIndex());
	}

	if (nLdIndex == -1)
	{
		ACSI_NODE *pDevice = &pACSINode[nDvIndex];

		if (pDevice != NULL)
		{
			ST_INT nIndex = 0;

			for (nIndex=0; nIndex<pDevice->numLD; nIndex++)
			{
				//if (strstr(pDevice->LD[nIndex].LDName,"PROT") || strstr(pDevice->LD[nIndex].LDName,"BRcd"))
				if (mms_IsSettingsDS(pDevice->LD[nIndex].LDName))
				{
					nLdIndex = nIndex;
					break;
				}
			}
		}
	}

	pParam->set_LDvIndex(nLdIndex);
}


//////////////////////////////////////////////////////////////////////////

//
ST_VOID u_mvl_status_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}

ST_VOID u_mvl_write_ind (MVL_IND_PEND *indCtrl)
{
	int i = 0;
}

ST_VOID u_mvl_obtfile_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}

ST_VOID u_mvl_jstat_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}

ST_VOID u_mvl_jread_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_jinit_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_getvlist_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_getvar_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_namelist_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_getdom_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}

ST_VOID u_mvl_getcl_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_frename_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_fdir_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}

ST_VOID u_mvl_fdelete_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_delvlist_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_defvlist_ind (MVL_IND_PEND *ind)
{
	int i = 0;
}
ST_VOID u_mvl_concl_ind (MVL_COMM_EVENT *event)
{
	int i = 0;
}
ST_VOID u_mvl_ustatus_ind (MVL_COMM_EVENT *event)
{
	int i = 0;
}
ST_VOID _mvl_process_jwrite_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}

ST_VOID _mvl_process_initdown_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_download_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_termdown_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_initupl_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_upload_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_termupl_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_deldom_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_crepi_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_delpi_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_start_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_stop_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_resume_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_reset_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_kill_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_getpi_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}
ST_VOID _mvl_process_getcl_conf (MVL_REQ_PEND *req)
{
	int i = 0;
}

ST_VOID _mvl_process_initdown_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_download_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_termdown_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_initupl_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_upload_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_termupl_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_deldom_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_crepi_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_delpi_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_start_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_stop_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_resume_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_reset_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_kill_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}
ST_VOID _mvl_process_getpi_ind (MVL_IND_PEND *ind_pend)
{
	int i = 0;
}

ST_VOID u_mvl_read_ind (MVL_IND_PEND *indCtrl)
{
	int i = 0;
}

SMEM_POOL_CTRL *u_smem_need_buffers (SMEM_CONTEXT *smemContext, 
									 ST_UINT8 numBuf, ST_UINT bufSize)
{
	SMEM_POOL_CTRL *newSc;

	/* numBuf = # of bufs in last pool created for this bufSize  OR	*/
	/*          0 if this is the first pool created for this bufSize.	*/
	/* If numBuf = 0, then the user must choose an appropriate value.	*/
	if (numBuf == 0)
		numBuf = 10;	/* choose a value	*/
	if (bufSize == 0)
		bufSize = 1000;	/* choose a value	*/

	newSc = smem_add_pool (smemContext, numBuf, bufSize,
		SD_FALSE,	/* autoClone	*/
		0,		/* maxClones	*/
		NULL);		/* poolName	*/
	return (newSc);

}
ST_VOID  u_smem_get_pool_params ( SMEM_CONTEXT *contextName,
								 ST_UINT8 *numBuf, ST_UINT *bufSize,
								 ST_BOOLEAN *autoClone,
								 ST_INT *maxClones,
								 ST_CHAR **poolName)
{
	int i = 0;
}

// double GeCurrTime_double()
// {
// 	SYSTEMTIME tmSys;
// 	::GetLocalTime(&tmSys);
// 	CTime tm(tmSys);
// 	return (double)(tm.GetTime());
// }

ST_VOID GeCurrTime_double(double *pdTime,int *pnTmMs)
{
	SYSTEMTIME tmSys;
	::GetLocalTime(&tmSys);
	CTime tm(tmSys);
	*pdTime = (double)(tm.GetTime());
	*pnTmMs = tmSys.wMilliseconds;
}

CString get_all_filedir_path(XMMS_FILE_SYS_OBJ *pTagFileDir)
{
	if (pTagFileDir == NULL)
	{
        return _T("");
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

long mms_GetDeviceReportCount(ACSI_NODE *pACSI_NODE)
{
	long nBeginIndex = pACSI_NODE->nReportBeginIndex;
	long nEndIndex = pACSI_NODE->nCurrReportIndex;
	long nCount = 0;

	if (nEndIndex == nBeginIndex)
	{
		return 0;
	}

	if (nEndIndex > nBeginIndex)
	{
		nCount = nEndIndex - nBeginIndex;
	}
	else
	{
		nCount = MAX_REPORT_COUNT - nBeginIndex;
		nCount += nEndIndex;
	}

	return nCount;
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

ACSI_NODE* Global_get_ACSI_NODE(const int &nDevIndex)	
{	
	return &pACSINode[nDevIndex];	
}

long MultiByteToUtf8(char* pBuffer)
{
    if (NULL == pBuffer)
	{
        return 0;
	}

    unsigned char *pszUft8 = NULL;
    int nLenRet = 0;
    int nLenSrc = 0;

    nLenSrc = strlen(pBuffer);
    gbk_to_utf8_r((const unsigned char*)pBuffer, nLenSrc, &pszUft8, &nLenRet, 0);

    if (nLenRet > 0)
    {
        memcpy(pBuffer, pszUft8, nLenRet);
        pBuffer[nLenRet] = 0;
        delete pszUft8;
    }

    return nLenRet;
}

//2022-10-12  lijunqing
//单一设备模式，在此模式下
//系统永远不退出设备，这样提高测试效率，这样就不要反复链接设备
BOOL g_bMmsEngineSingleDeviceMode = TRUE; 

//引擎为调试模式，再次模式下：
//1，联机成功：打开模型文件
//2，通讯命令：马上返回
BOOL g_bMmsEngineViewErrorInfor = FALSE; 
BOOL g_bMmsEngineCommError = FALSE; 



//////////////////////////////////////////////////////////////////////////

CString Global_GetFileDirFullPath(XMMS_FILE_SYS_OBJ *pTagFileDir)
{
	if (pTagFileDir == NULL)
	{
        return "";
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


ST_BOOLEAN Global_MarkOldFile(XMMS_FILE_SYS_OBJ *pFileDir)
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


// 2012-12-17  数据比较
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
		else if (strstr(pDst->DataType,"BIT_STR"))
		{
			if (mms_str_cmp(/*mms_string*/(&pSrc->DAValue.Value.string), /*mms_string*/(&pDst->DAValue.Value.string)) == 0) //(.)
				nRet = SD_TRUE;
		}
		else if (strstr(pDst->DataType,"UTC_TIME"))
		{
			//if (pSrc->DAValue.Value.f - pDst->DAValue.Value.f<0.001)
			nRet = SD_TRUE;
		}
		else if (strstr(pDst->DataType,"STRUCT"))
		{
			for (i=0; i<pDst->nSubDANum;i++)
			{
				nRet = CompareData(&pSrc->pSubDA[i], &pDst->pSubDA[i]);
				if (nRet!=SD_TRUE)
					break;
			}
		}
	}
	else
	{
		//2023-5-18 lijunqing DataType=BOOL or ST_BOOLEAN
		if ( strstr(pSrc->DataType, "BOOL") != NULL && strstr(pDst->DataType, "BOOL") != NULL   )
		{
			if (pSrc->DAValue.Value.u == pDst->DAValue.Value.u)
				nRet = SD_TRUE;
		}
	}

	return nRet;
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
