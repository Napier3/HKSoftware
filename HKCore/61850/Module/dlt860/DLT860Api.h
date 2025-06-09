#pragma once

#include "../61850ClientAPI/FuncParamEx.h"     //ok
#include "../../../Module/BaseClass/ThreadProgressInterface.h"
#include "../../../Module/CriticalSection/SynCriticalSection.h"

#define _mms_api_rw_use_critic_section_

class CRemoteDev;
class CFuncParamEx;

class CDLT860Api
{
public:
	CDLT860Api(void);
	virtual ~CDLT860Api(void);

	CWnd *m_pMmsMsgRcvWnd;

public:
	/* 基本数据操作过程 */
	virtual long Client61850_DataOpeProc(CFuncParamEx *pFuncParaEx);

public://全部通讯命令
	/*  和装置联机 */
	ST_RET Client61850_LinkDev(CFuncParamEx *pFuncParaEx);

	/*和装置断开连接 */
	ST_RET Client61850_UnLinkDev(CFuncParamEx *pFuncParaEx);

public:
	void set_OnlyReadValue(BOOL b= TRUE)	{		m_bOnlyReadValue = b;	}
	/*网络监控线程 */
//	ST_RET CreateDataProcThread();
	ST_RET CreateDataProcThread(const long &nDevIndex);
	ST_VOID MmsAcsiServerThread_DataProc(CFuncParamEx *pFuncParaEx);
	/*  销毁网络监控线程 */
	ST_RET DestroyDataProcThread();

	ACSI_NODE* GetAcsiNode(const long nDevIndex);
	CString mms_GetDAName(tagDA *pDA);
	tagDA* get_MMStagDAObj(LD_DATASET_INFO *pLD_INFO,ST_INT index);

	CFuncParamEx   m_oFuncParamEx[MAX_DEVICE];			//功能参数

public://初始化链表
	//联机
	void InitLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bOnlyLink=FALSE);
	void InitLinkDeviceFuncPara_AutoTest(ST_INT nDeviceIndex, BOOL bOnlyLink=FALSE);
	void InitUnLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bAutoTest=FALSE, BOOL bOnlyLink=FALSE);
	void InitEnumLDFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas=FALSE);
	//控制，压板、遥控、......
	void InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDaTypeID);
	void InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType);
	void InitCtrlWriteFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bDeleteAll=TRUE);

	void InitWriteFuncParasSingle(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);

	virtual BOOL InitStopReportFuncParas(ST_INT nDeviceIndex, BOOL bFreeFuncParas);
	virtual BOOL InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);
	void InitGetFile(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName);
	void InitUploadFile(ST_INT nDeviceIndex, const CString &strLocalFilePath,const CString &strDevPath);
	void InitGetFilePara(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName, const CString &strPostfix);
	//读定值区号
	void InitReadLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex);
	//写定值区号
	void InitWriteLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nZone);
	void InitReadLDeviceValuesFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nTypeID);
	void InitReadFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);
	void InitReadFuncPara_Set(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nZone, ST_INT nRunSG, BOOL bDeleteAll);
	void InitWriteCurrSetsFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, long nZone, BOOL bDeleteAll);

	void InitGetFileDir(ST_INT nDeviceIndex, const CString &strPath,BOOL bOnlyReadCfg = FALSE);
	void InitReadDeviceRPC_FuncParas(ST_INT nDeviceIndex);
	void InitRpcCall(ST_INT nDeviceIndex,const CString &strParaFunction,const CString &strParaCallName,const CString &strParaCallID,
		long nVersion,long nTimeout,long nRequestType,long nResponseType);

	void InitReadOneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nDataIndex, BOOL bDeleteAll);
	void InitCtrlWriteOneFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nDAIndex1, ST_INT nDAIndex2,
		ST_INT nDAValue1, ST_INT nDAValue2, ST_INT nTDelayAfterSel);

	void InitReadJournal(ST_INT nDeviceIndex, ST_INT nLDeviceIndex, const CString &strJournalName
		,ST_INT bStart, ST_INT nStartType, CTime &tmStart, long long nStartEntry
		, ST_INT bEnd, ST_INT nEndType, CTime &tmEnd, ST_INT nEntryNum);

	void InitReadDevice(ST_INT nDeviceIndex, BOOL bFreeFuncParas);

	//复归装置
	void ResetDevice(ST_INT nDeviceIndex, ST_INT nLDIndex);

	//报告
	virtual BOOL InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, BOOL bFreeFuncParas);
	void InitCallReportFlagDefault(ST_INT nDeviceIndex);
	void InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart);
	virtual BOOL InitCallReportFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, UINT nBrcbIndex, BOOL bFreeFuncParas);
	BOOL IsInFuncsCallState(long nDeviceIndex);

	void ValidateCurrFunc(long nDeviceIndex);
	virtual BOOL CallFirstFunc(long nDeviceIndex);
	virtual BOOL CallCurrFunc(long nDeviceIndex);
	virtual BOOL CallNextFunc(long nDeviceIndex);
	virtual void ProgDlg_StopProgress(long nDeviceIndex);

	BOOL CheckCurSelIsSetting(int nDeviceIndex, int nLDIndex, int nDsIndex);
	BOOL CheckCurSelIsParameter(int nDeviceIndex, int nLDIndex, int nDsIndex);
	BOOL CheckCurSelIsDout(int nDeviceIndex, int nLDIndex, int nDsIndex);

	void FireCmdMsg(CFuncParamEx *pFuncParaEx,UINT nCmdID, UINT nCmdIndex);
	static void FireCmdMsg_CtrlWrite(DWORD dwFuncParaEx, UINT nCmdIndex);

    CRemoteDev* GetRemoteDev(const long nDevIndex);

protected:
	ST_INT GetDsIndex(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType);
	BOOL GetAcsiiLD_Node(CFuncParamEx *pFuncParaEx,CRemoteDev **ppRemoteDev,ACSI_NODE **ppDevice,LD_NODE **ppLD);
	ST_INT get_DataSetNum(LD_NODE *pLD, ST_INT nDsIndex);

#ifdef _mms_api_rw_use_critic_section_
	CAutoCriticSection m_oMmsRWCriticSection;
#endif

	CThreadProgressInterface *m_pProgressInterface;

private:
	ST_RET Client61850_EnumLDDir(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_EnumLNDir(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ReadData(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ReadOneData(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_WriteData(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_WriteDataSingle(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ReadDataSetting(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ReadDir(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ReadRPC(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_RpcCall(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ReadFile(CFuncParamEx *pFuncParaEx);
	/*  获取当前定值运行区&定值区数 */
	ST_RET Client61850_GetActiveSG(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_SetActiveSG(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_StartDevRpt(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_StopDevRpt(CFuncParamEx *pFuncParaEx);

	//获取下一个逻辑设备的定值区
	BOOL Client61850_GetNextLdZonePara(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_SetEditSG(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_CnfEditSG(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_CtrlWrite(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_CtrlWriteOne(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ResetDev(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_UploadFile(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850_ReadJournal(CFuncParamEx *pFuncParaEx);
	ST_RET Client61850__ReadDevice(CFuncParamEx *pFuncParaEx);

	void ValidateCurrFunc_ReadZone(CFuncParam *pParam);
	void ExitAllConnFunc(ST_INT nDeviceIndex);

	BOOL HasUnit(char *pszDsId);
	BOOL HasMinMax(char *pszDsId);
	BOOL HasStepSize(char *pszDsId);

	ST_RET node_get_tagDAData( LD_NODE *pLD, tagDA *pDA);
	MMS_DATA_NODE* find_node_by_name(MMS_DATA_NODE *FC_node,const CString&strDescPath);
	void init_tagDA_datatype(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child);
	void add_child_tagDA(tagDA *pDA,MMS_DATA_NODE *pNode_Data);
	MMS_DATA_NODE* node_find_child(MMS_DATA_NODE *pLN_NODE,const CString &strTmp);
	void node_get_desc_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE);
	void node_find_dU(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail);
	void init_tagDA_data(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child,ST_CHAR *pValuePath);
	void get_node_tagDA(tagDA **ppDA,MMS_DATA_NODE *pNode_Data);
	void add_node_tagDA_ARRAY(tagDA *pDA,MMS_DATA_NODE *pNode_Data);
	void get_node_numbers(MMS_DATA_NODE *pNode_Data,ST_INT &nSubNum);
	ST_VOID My_PareVarType_Array_MmsName(tagDA *pDA, ST_CHAR *pArrayIndex);
	void node_get_LimitVal_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE);
	void node_find_MinMaxStepUnit(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail,ST_INT nLimitKind);
	

	BOOL m_bExitServeACSIServer;
	BOOL m_bOnlyReadValue; //读数据时，只读取数值

	ST_INT  m_nLdIndexBack;
	BOOL m_bIsAinMinMax;
};

extern CDLT860Api *g_oDLT860Api;
extern BOOL g_bMmsEngineDebugMode; 


