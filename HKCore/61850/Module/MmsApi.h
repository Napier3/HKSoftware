// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the MMSAPI_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// MMSAPI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#pragma once

#include "61850ClientAPI/FuncParamEx.h"

//////////////////////////////////////////////////////////////////////////

extern ST_CHAR OSICFG_PATH[255];
extern ST_CHAR SECMANCFG_PATH[255];

#include "MmsConfig/MmsEngineConfig.h"
#include "../../Module/BaseClass/ThreadProgressInterface.h"
#include "../../Module/DataMngr/DvmDevice.h"
#include "../../Module/CriticalSection/SynCriticalSection.h"

extern ST_INT gThreadCounter;

//////////////////////////////////////////////////////////////////////////
// 2012-11-22  ���ܲ�������
//////////////////////////////////////////////////////////////////////////

#include "MMS_STACK_CFG/MMS_STACK_CFG.h"
#include "MmsDataNode.h"

#ifdef _PSX_QT_LINUX_
#include <pthread.h>
#endif


#define SERVER_USE_TWO_THREAD

#define _mms_api_rw_use_critic_section_


//////////////////////////////////////////////////////////////////////////
// 2012-11-22  MMS�������ƶ���
//////////////////////////////////////////////////////////////////////////
extern BOOL bInit_ACSI;

typedef CTLinkList<tagDA> CTagDAList;

//////////////////////////////////////////////////////////////////////////
//CMmsDvmDevice
class CMmsDvmDevice : public CDvmDevice
{
public:
	CMmsDvmDevice();
	virtual ~CMmsDvmDevice();

	CDvmDataset m_oDsJournal;
	CDvmDataset m_oDsReport;

};

//////////////////////////////////////////////////////////////////////////
//CMmsApi
class CMmsApi
{
public:
	CMmsApi();
	virtual ~CMmsApi();
	virtual void ExitMmsApi();

	CWnd *m_pMmsMsgRcvWnd;
protected:
#ifdef _mms_api_rw_use_critic_section_
	//CAutoSimpleLock
	CAutoCriticSection m_oMmsRWCriticSection;
#endif

public:
//	CFuncParam	m_FuncParam;			//���ܲ���
	CFuncParamEx   m_oFuncParamEx[MAX_DEVICE];			//���ܲ���

	//2023-1-29 lijunqing ��װ��ͨ�ţ�Զ��ͨ�ŷ���ÿ��װ�ö���һ��������ͨ�Ź���
	//�����ƶ���CFuncParamEx��
	//CThreadProgressInterface *m_pProgressInterface;

// 	ST_BOOLEAN m_bEmnuRpt;
	ST_BOOLEAN m_bEnumLN;
	ST_BOOLEAN	m_bMmsDisConBfConnected;		//���� ��־
	ST_INT	m_bMaxMmsConnectedTimes;		//���� ��־ �����������

	BOOL m_bAutoSetIP;

	void AttatchProgress(long nDeviceIndex, CThreadProgressInterface *pProgressInterface)
	{
		if (0 <= nDeviceIndex && nDeviceIndex < MAX_DEVICE)
		{
			m_oFuncParamEx[nDeviceIndex].m_pProgressInterface = pProgressInterface;
		}
	}

protected:
	CExBaseList m_listDevice;

	CMmsDvmDevice* GetDvmDevice(long nDvIndex);
	CDvmDataset* GetDsJournal(long nDvIndex);
	CDvmDataset* GetDsReport(long nDvIndex);

	CDvmData* AddJournal(long nDvIndex, tagDA *pDA);

/* �ڲ����� */
protected:	
	long m_nDeviceCount;
	CString     m_strMMSApiError;		

	ST_BOOLEAN	m_bMMSConnected;		//���� ��־
 
//	HANDLE		m_hThread_Notify;		//����֪ͨ�߳̾��

#ifdef _PSX_QT_LINUX_
    pthread_t m_hThread_Proc;
#else
    HANDLE      m_hThread_Proc;			//�������ݴ����߳̾��
#endif

#ifdef SERVER_USE_TWO_THREAD
//	HANDLE      m_hThread_Proc_Data;	
#endif

	ST_BOOLEAN m_bOnlyReadValue; //������ʱ��ֻ��ȡ��ֵ
	
	CMmsEngineConfig m_oMmsEngineConfig;
	BOOL m_bExitServeACSIServer;

	CMMS_STACK_CFG m_oMMS_STACK_CFG;
	char m_pszMinValKey[40];
	char m_pszMaxValKey[40];
	BOOL m_bIsAinMinMax;

public:
	void OnCreateDevice();//	{	m_nDeviceCount++;	}
	void OnReleaseDevice();//	{	m_nDeviceCount--;	}
	BOOL HasDevice()		{	return m_nDeviceCount;	}
	void ReleaseAllDevice()	{	m_nDeviceCount = 0;	}
	void ReleaseObjData(ACSI_NODE *pDvNode);	//2022-11-26  lijunqing

/* �������� */
public:
	char* mms_GetDatasetKey(const CString &strDatasetID)	
	{
		return m_oMmsEngineConfig.mms_GetDatasetKey(strDatasetID);	
	}

	ST_VOID set_OnlyReadValue(ST_BOOLEAN b= SD_TRUE)	{		m_bOnlyReadValue = b;	}
	ST_BOOLEAN get_OnlyReadValue()						{	return m_bOnlyReadValue;	}

	/* 2012-10-17  ��ȡ��ǰ������״̬ */
	ST_BOOLEAN get_MMSConnected(){ return m_bMMSConnected; }

	/* 2012-10-30  �������������־ */
	//ST_BOOLEAN get_StartBrcbCtrl(){ return m_bStartBrcbCtrl; }
	
	/* 2012-11-22  ��ȡ������Ϣ */
	ST_VOID get_LastError(CString &strError){ strError = m_strMMSApiError; };

	/* 2012-10-08  ���������ĵ�λ */
	ST_VOID My_PareVarUnite(int nValue, CString &strText);

	// 2012-10-15  ������������
	ST_VOID My_PareVarType_Array_MmsName(tagDA *pDA, ST_CHAR *pArrayIndex);
	ST_VOID My_PareVarType_Array_Set_Sub_MmsName(tagDA *pDA, ST_CHAR *pValName);

#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_VOID My_PareVarType(ST_INT type_id, tagDA *pDA, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	ST_VOID My_PareVarType(ST_INT type_id, tagDA *pDA);
#endif

	ST_VOID My_PareVarType_Struct(CTagDAList &listDA, ST_CHAR *DAName, ST_INT num_rt_out, ST_INT &index, RUNTIME_TYPE* &rt_out);
	ST_VOID My_PareVarType_Array(tagDA *pDA, ST_INT num_rt_out, ST_INT &index, RUNTIME_TYPE* &rt_out);
	ST_INT My_PareVarType_Value(CTagDAList &listDA, RUNTIME_TYPE* rt_out, ST_CHAR *DAName);


	/* 2012-11-09  �������������� */
	ST_VOID My_GetRptData(ST_INT nDsIndex, CString *strRpt);

	// 2012-10-23  ��ȡװ�õ�ĳ���߼��豸
	LD_NODE* get_DevLDPtr(CFuncParamEx *pFuncParaEx);

	// ��ȡװ��
	ACSI_NODE* get_DevACSI_NODEPtr(CFuncParamEx *pFuncParaEx);

/* װ�ò��� */
public:
	void SaveMmsEngineConfig();

	/* 2012-09-20  ��ʼ�� MMS ���� */
 	ST_RET mmsi_InitMMSData(ST_INT  nSelPipe, ST_BOOLEAN bInit=SD_FALSE);
	void ReadMmsEngineConfig();
 
 	/* 2012-09-20  �ͷ� MMS ���� */
 	ST_VOID mmsi_ReleaseMMSData(ST_INT  nSelPipe);
	ST_VOID mmsi_DisConnectServer(ST_INT  nSelPipe);
#ifdef _use_pip_use_counter
	ST_VOID mmsi_ResetSocketInfoTable();
#endif

	/* 2012-11-22  ���ù���ID */
	ST_RET mmsi_FunctionCall(ST_INT nDeviceIndex, ST_INT nFuncID);

	/* 2012-11-09  ���ձ������� */
	virtual ST_VOID mmsi_RecvRptData()=0;

	ST_RET node_get_tagDAData(MVL_NET_INFO *net_info, LD_NODE *pLD, tagDA *pDA);//zhouhj 20180703
	MMS_DATA_NODE* find_node_by_name(MMS_DATA_NODE *FC_node,const CString&strDescPath);
	void add_child_tagDA(tagDA *pDA,MMS_DATA_NODE *pNode_Data);
	void get_node_tagDA(tagDA **ppDA,MMS_DATA_NODE *pNode_Data);
	void init_tagDA_data(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child,ST_CHAR *pValuePath);
	void init_tagDA_datatype(tagDA *pNewDA,MMS_DATA_NODE *pNode_Child);
	void add_node_tagDA_ARRAY(tagDA *pDA,MMS_DATA_NODE *pNode_Data);
	void get_node_numbers(MMS_DATA_NODE *pNode_Data,ST_INT &nSubNum);
	void node_get_desc_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE);
	void node_get_LimitVal_path(tagDA *pDA,MMS_DATA_NODE *pLN_NODE);
	void node_find_dU(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail);
	void node_find_MinMaxStepUnit(tagDA *pDA,MMS_DATA_NODE *FC_node,CString &strPathHead,CString &strPathTail,ST_INT nLimitKind);

#ifdef _MVL_TYPE_CTRL_use_one_device_
	void node_get_rcbs_lcbs( MVL_NET_INFO *netInfo,LD_NODE *pLD, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	void node_get_rcbs_lcbs( MVL_NET_INFO *netInfo,LD_NODE *pLD);
#endif
	

#ifdef _MVL_TYPE_CTRL_use_one_device_
	void node_get_rpt_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node, char *strRptPath, MVL_TYPE_CTRL *mvl_type_ctrl);
	void node_get_lcb_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node, char *strLogPath, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	void node_get_rpt_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node, char *strRptPath);
	void node_get_lcb_dataset(MVL_NET_INFO *netInfo,LD_NODE *pLD,MMS_DATA_NODE *FC_node,  char *strLogPath);
#endif

	ST_RET node_get_DataLimitValInfoAll( MVL_NET_INFO *netInfo, ST_CHAR*pLDName,tagDA*pDA);
	ST_RET node_get_DataLimitValInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, tagDA*pDA, ST_INT nLimitKind=0);
	MMS_DATA_NODE* node_find_child(MMS_DATA_NODE *pLN_NODE,const CString &strTmp);
	CString remove_tail_digit(const CString &strRptName);

	void mms_set_dataset_desc(LD_DATASET_INFO *pDatasetInfor);//zhouhj 20191230

protected:
 	/* 2012-10-23  ������װ�ñ��� */
 	ST_RET set_StartReadRpt(CFuncParamEx *pFuncParaEx,ST_BOOLEAN bGI=SD_TRUE,ST_BOOLEAN bUpdateEntryID = FALSE);

	/* 2012-10-23  ֹͣ���������� */
	ST_RET set_StopReadRpt(CFuncParamEx *pFuncParaEx,ST_INT nDsIndex);

	/* 2012-10-24  ��ȡ�����ʹ��״̬ */
	ST_RET get_RptEnableState(MVL_NET_INFO *netInfo, ST_CHAR *domName, 
		ST_CHAR *rcbItem, ST_BOOLEAN *RptEna);

	/* 2012-10-23  ʹ�ܱ�����ƿ� */
#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_RET set_RCBEnable(MVL_NET_INFO *netInfo, ST_CHAR *domName,
		ST_CHAR *rcbItem, ST_UCHAR *OptFlds, ST_UCHAR *TrgOps,ST_BOOLEAN bUpdateEntryID	, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	ST_RET set_RCBEnable(MVL_NET_INFO *netInfo, ST_CHAR *domName,
		ST_CHAR *rcbItem, ST_UCHAR *OptFlds, ST_UCHAR *TrgOps,ST_BOOLEAN bUpdateEntryID);	
#endif

	/* 2012-10-23  ֹͣʹ�ܱ�����ƿ� */
	ST_RET set_RCBDisable(MVL_NET_INFO *netInfo, ST_CHAR *domName, ST_CHAR *rcbItem);

	/* 2012-11-12  ��ʼ���豸���ݼ� */
	ST_VOID Init_DevDataSet(LD_NODE *pLD, ST_INT nDsIndex);

	/* 2012-11-21   */
	ST_VOID get_MMStagDAObj(ST_INT nDsIndex, ST_INT index, LD_DATASET_INFO*pLD_INFO, tagDA **pDA);

	/* 2012-11-22  */
	MVL_NET_INFO *get_NetInfo(CFuncParamEx *pFuncParaEx);

	// 2012-11-21  �ͷŶ�����������ڴ�
	ST_VOID ReleaseObjData();	//zhouhj ���˳�appʱ�����ͷ�

	// 2012-11-15  �ͷ�MMS������ڴ�
	ST_VOID ReleaseMMSData();
	
	BOOL HasUnit(char *pszDsId);
	BOOL HasMinMax(char *pszDsId);
	BOOL HasStepSize(char *pszDsId);

public:
	/* 2012-11-20  �������߳� */
	ST_RET CreateDataProcThread();
	ST_RET CreateDataProcThread(CFuncParamEx *pFuncParaEx);

	/* 2012-11-20  �����������߳� */
	ST_RET DestroyDataProcThread();

	/* 2012-11-01  ������������߳� */
//	ST_RET CreateMMSRecvThread();

	/* 2012-11-01  ���ٱ�������߳� */
//	ST_RET DestroyMMSRecvThread();

	/* 2012-11-09  ����֪ͨ */
//	ST_VOID RecvRptNotify();

	/* 2012-11-19  У������״̬ */
	ST_VOID MmsAcsiServerThread();
	ST_VOID MmsAcsiServerThread_DataProc(CFuncParamEx *pFuncParaEx);

/*private*/public://Ϊ���ṩ��XmlRpcʹ�ÿ���
	/* 2012-11-22  ��װ������ */
	ST_RET MMS_LinkDev(CFuncParamEx *pFuncParaEx);

	/* 2012-11-22  ��װ�öϿ����� */
	ST_RET MMS_UnLinkDev(CFuncParamEx *pFuncParaEx);

	/* 2012-11-22  ����MMS������� */
	ST_RET MMS_TestNetProc(CFuncParamEx *pFuncParaEx);
	ST_VOID Mms_TestNetsProc();
	ST_RET Mms_TestNetProc(ST_INT nDeviceIndex);

	/* 2012-11-22  �������ݲ������� */
	virtual long MMS_DataOpeProc(CFuncParamEx *pFuncParaEx);
private:
	/* 2012-11-22  ö��װ�õ��߼��ڵ�Ŀ¼ */
	ST_RET MMS_EnumLDDir(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_EnumLNDir(CFuncParamEx *pFuncParaEx);

	ST_RET GetLogicalNodeDirectory(ST_INT _iNetInfo,LD_NODE *_LDNode);
	ST_RET Get_LNX_Attributte(ST_INT _iNetInfo,ST_CHAR *pLDName,MMS_DATA_NODE* _FCNode, enum NODE_TYPE nTypeDepp_1);
	ST_RET Pharse_LNX_Attributte(MVL_NET_INFO *connectInfo,ST_CHAR *_pStrLine, ST_CHAR *pLDName, MMS_DATA_NODE* _FCNode, enum NODE_TYPE nTypeDepp_1);
	ST_RET Get_Nodes_Detail(ST_INT nDeviceIndex);
	ST_RET Get_Node_Value(ST_INT nDeviceIndex, LD_NODE*pLD, ST_CHAR pszParentPath, MMS_DATA_NODE* _FCNode);

	ST_RET GetLLN0Attributte(ST_INT _iNetInfo,ST_CHAR *pLDName,MMS_DATA_NODE* _FCNode);
	ST_RET PharseLLN0Attributte(ST_CHAR *_pStrLine, MMS_DATA_NODE* _FCNode);
	ST_RET GetLogicalNodeAttributte(ST_INT _iNetInfo,ST_CHAR *_pLDName,MMS_DATA_NODE* _LNNode, ST_INT nTypeDepp_1, ST_INT object_tag);
	ST_RET PharseLogicalNodeAttributte(ST_CHAR *_pStrLine,MMS_DATA_NODE* _LNNode);
	ST_RET GetControlDirectory(ST_INT nDeviceIndex);
	ST_VOID Init_tagDA_by_DATA_NODE(tagDA *pDA, MMS_DATA_NODE *pNode);
	ST_INT GeCount_DATA_NODE(MMS_DATA_NODE *pNode);
	MMS_DATA_NODE* Get_DATA_NODE_Oper(MMS_DATA_NODE *pNode);
	MMS_DATA_NODE* Find_DATA_NODE(MMS_DATA_NODE *pParent, char *pName);
	ST_VOID Init_tagDA_by_DATA_NODE2(tagDA *pDA, MMS_DATA_NODE *pNode);
	ST_VOID Set_DATA_NODE_DataType(MMS_DATA_NODE *pNode, ST_CHAR *strDataType);
	void MMS_CopyJournal(LD_LOG_INFO *pDest, LD_LOG_INFO *pSrc);
	void get_all_subdir(ST_INT nDvIndex,XMMS_FILE_SYS_OBJ *pTagFileDir, CFuncParamEx *pFuncParaEx,BOOL bOnlyReadCfg);
	CString find_dataset_by_valuepath(LD_NODE *pLD,char *pLogValuePath);

	BOOL mms_Is_CO_CtrlMode_1_4(ST_INT nDeviceIndex, char *pLdName, tagDA *pDa);

	
#ifdef _MVL_TYPE_CTRL_use_one_device_
	void mms_Init_desc_data_node(ST_INT nDeviceIndex, char *pLdName, tagDA *pDa, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	void mms_Init_desc_data_node(ST_INT nDeviceIndex, char *pLdName, tagDA *pDa);
#endif

	/* 2012-10-09  ��ȡ���� */
	ST_RET MMS_ReadData(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_ReadOneData(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_ReadDataSetting(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_ReadDir(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_ReadFile(CFuncParamEx *pFuncParaEx);

	/* 2012-09-20  д��Ķ�ֵ��ֵ */
	ST_RET MMS_WriteData(CFuncParamEx *pFuncParaEx);
	
	/* д�����ֵ */
	ST_RET MMS_WriteDataSingle(CFuncParamEx *pFuncParaEx);

	/* 2012-11-22  ��ȡ��ǰ��ֵ������&��ֵ���� */
	ST_RET MMS_GetActiveSG(CFuncParamEx *pFuncParaEx);

	/* 2012-11-22  ���õ�ǰ��������ֵ */
	ST_RET MMS_SetActiveSG(CFuncParamEx *pFuncParaEx);

	/* 2012-11-30  ���õ�ǰ�༭��ֵ������ */
	ST_RET MMS_SetEditSG(CFuncParamEx *pFuncParaEx,ST_INT nSGID);

	/* 2012-11-30  �̻���ǰ�༭��ֵ������ */
	ST_RET MMS_CnfEditSG(CFuncParamEx *pFuncParaEx);
public:
	/* 2012-10-30  ������װ�ñ��� */
	ST_RET MMS_StartDevRpt(CFuncParamEx *pFuncParaEx);
	/* 2012-10-30  ֹͣ���������� */
	ST_RET MMS_StopDevRpt(CFuncParamEx *pFuncParaEx);
private:
	/* 2012-12-3  �������write */
	ST_RET MMS_CtrlWrite(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_CtrlWriteOne(CFuncParamEx *pFuncParaEx);

	/* 2013-01-11  װ�ø��� */
	ST_RET MMS_ResetDev(CFuncParamEx *pFuncParaEx);

	//Journal
	ST_RET MMS_ReadJournalCount(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_ReadJournal(CFuncParamEx *pFuncParaEx);
	CString find_dataset_by_loginfo(LD_JOURNAL_CTRLS *pJournalCtrls,char *pLogCtrlName);
	CString find_logctrl_by_datasetinfo(LD_JOURNAL_CTRLS *pJournalCtrls,CString strDatasetName);
	BOOL check_prefix_and_suffix(const CString &strMsgPath,CString &strDirPath);
	void find_lcbName(const CString &strLogCtrlPath,char *pszLcbName);
public:
	//2018-5-16 zhouhj
	ST_RET MMS_UploadFile(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_ReadDevice(CFuncParamEx *pFuncParaEx);
	ST_RET MMS_DvmEnum(CFuncParamEx *pFuncParaEx);

private:
	// 2013-5-7  װ�ø���
	ST_RET My_DebReset(CFuncParamEx *pFuncParaEx,CString strType);

	ST_INT ClarifymmsVarName(ST_CHAR *mmsVarName);

	// 2012-12-17  ��ȡ����
#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_RET CMmsApi::get_tagDAData(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	ST_RET get_tagDAData(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA);
#endif

	ST_RET get_tagDADataValue(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA);
	ST_RET get_tagDADataValue2(MVL_NET_INFO *net_info, ST_CHAR*pLDName, char *pDataType, tagDAValue *pDAValue, ST_INT nDataType);
	ST_RET get_tagDAData_Set(MVL_NET_INFO *net_info, ST_CHAR*pLDName, tagDA *pDA, ST_BOOLEAN bReadSE);

	// 2013-4-17  ��ȡ���ݵ�����
#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_RET get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl, ST_INT nAinKind=-1,ST_INT nLevel=-1);
	ST_RET node_get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl);

	// 2013-4-17  ��ȡ���ݵĵ�λ
	ST_RET get_DataUniteInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl, ST_INT nAinKind=-1,ST_INT nLevel=-1);

	// 2014/4/4  ��ȡ���ݶ�Ӧ�����ֵ
	ST_RET get_DataLimitValInfo(    MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl,ST_INT nAinKind=-1, ST_INT nLevel=-1, ST_INT nKind=0);
	ST_RET get_DataLimitValInfoAll( MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA, MVL_TYPE_CTRL *mvl_type_ctrl,ST_INT nAinKind=-1, ST_INT nLevel=-1, ST_INT nKind=0);
#else
	ST_RET get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA, ST_INT nAinKind=-1,ST_INT nLevel=-1);
	ST_RET node_get_DataDescInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, tagDA*pDA);

	// 2013-4-17  ��ȡ���ݵĵ�λ
	ST_RET get_DataUniteInfo(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA, ST_INT nAinKind=-1,ST_INT nLevel=-1);

	// 2014/4/4  ��ȡ���ݶ�Ӧ�����ֵ
	ST_RET get_DataLimitValInfo(    MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA,ST_INT nAinKind=-1, ST_INT nLevel=-1, ST_INT nKind=0);
	ST_RET get_DataLimitValInfoAll( MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA,ST_INT nAinKind=-1, ST_INT nLevel=-1, ST_INT nKind=0);
#endif
	


#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_RET get_DataLimitVal(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_CHAR* dstVar, tagDAValue *pDAValue, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	ST_RET get_DataLimitVal(MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_CHAR* dstVar, tagDAValue *pDAValue);
#endif

#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_RET OperSBOwEx(ST_INT nACSI, ST_CHAR *pOper, ST_CHAR *pLDName, ST_INT type_id
		, ST_INT iValue, ST_INT fValue, ST_INT test, ST_INT check, ST_INT nAddSize, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	ST_RET OperSBOwEx(ST_INT nACSI, ST_CHAR *pOper, ST_CHAR *pLDName, ST_INT type_id
		, ST_INT iValue, ST_INT fValue, ST_INT test, ST_INT check, ST_INT nAddSize);
#endif

	ST_RET GetBitStringValueFromInt(ST_RET nValue);

	ST_RET get_DataStepSizeInfo(    MVL_NET_INFO *netInfo, ST_CHAR*pLDName, ST_INT nLen, tagDA*pDA,ST_INT nAinKind=-1, ST_INT nLevel=-1, ST_INT nKind=0);

	// 2013-4-10  ��ȡ������ƿ�
#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_RET get_ReportCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class, ST_BOOLEAN bBR, MVL_TYPE_CTRL *mvl_type_ctrl);
	ST_RET get_LogCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class, MVL_TYPE_CTRL *mvl_type_ctrl);// 2018-1-17  ��ȡ��־���ƿ� zhouhj
#else
	ST_RET get_ReportCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class, ST_BOOLEAN bBR);
	ST_RET get_LogCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class);// 2018-1-17  ��ȡ��־���ƿ� zhouhj
#endif
	

	// 2016-12-7  ��ȡ��־���ƿ�
	ST_RET get_JournalCtrl(ST_INT nACSI, LD_NODE*pLD, ST_INT mms_class);

	/* 2012-12-27  ��ȡ�����Ĳ�����Ϣ */
	ST_RET get_BaseOpeData(CFuncParamEx *pFuncParaEx,MVL_NET_INFO **net_info,LD_NODE **pLD);

	/* 2012-12-27  ��ȡ���ݼ�����Ŀ */
	ST_INT get_DataSetNum(LD_NODE *pLD, ST_INT nDataSetType);

	// 2012-09-27  ��ȡ��������������
	ST_VOID get_varDesrName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind=-1, ST_INT nLevel=0);

	// 2012-09-27  ��ȡ����������λ��
	ST_VOID get_varUnitName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind=-1, ST_INT nLevel=0);

	// 2014-04-04  ��ȡ�����Сֵ������
	ST_VOID get_varLimitName(ST_CHAR*pSrc, ST_CHAR*pDst, ST_INT nSize, ST_INT nAinKind=-1, ST_INT nLevel=0, int nKind=0, int nHas_F=0);
	ST_VOID get_varStepSizeName(ST_CHAR*pSrc, ST_CHAR*pDst, int nHas_F);

	// 2012-11-07  �ͷ������ڲ���̬������ڴ�
	ST_VOID ReleaseTagDAAry(tagDA*pDA, ST_INT *nSize);


#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_RET MMS_CtrlWriteDA(CFuncParamEx *pFuncParaEx,tagDA *pDA, ST_CHAR *pLDName, ST_CHAR *pCoCf, const CString &strWriteTitle, MVL_TYPE_CTRL *mvl_type_ctrl);
	ST_RET MMS_CtrlWriteDAEx(CFuncParamEx *pFuncParaEx,tagDA *pDA, tagDA *pDA2, ST_CHAR *pLDName, ST_CHAR *pCoCf, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	ST_RET MMS_CtrlWriteDA(CFuncParamEx *pFuncParaEx,tagDA *pDA, ST_CHAR *pLDName, ST_CHAR *pCoCf, const CString &strWriteTitle);
	ST_RET MMS_CtrlWriteDAEx(CFuncParamEx *pFuncParaEx,tagDA *pDA, tagDA *pDA2, ST_CHAR *pLDName, ST_CHAR *pCoCf);
#endif
	

	// 2012-12-17  �ͷŴ���������ID
#ifdef _MVL_TYPE_CTRL_use_one_device_
	ST_VOID CMmsApi::destroy_typeid(ST_INT TypeID, MVL_TYPE_CTRL *mvl_type_ctrl);
#else
	ST_VOID destroy_typeid(ST_INT TypeID);
#endif


	//��ȡ��һ���߼��豸�Ķ�ֵ��
	BOOL MMS_GetNextLdZonePara(CFuncParamEx *pFuncParaEx);
	ST_INT  m_nLdIndexBack;

	ST_INT get_Type_id(ST_CHAR *pDataType);
	ST_VOID set_mmsname_SE(ST_CHAR *mmsname);

	void FireCmdMsg(CFuncParamEx *pFuncParaEx,UINT nCmdID, UINT nCmdIndex);

//���Ա��Ľ���
public:
	BOOL m_bTestMms_handle_data;
	unsigned char m_buf_handle_data[8192];
	long m_len_buf_handle_data;
	void Test_handle_data();
	void Test_handle_data(BYTE *pBuffer, long nLen);
	void GetLDNameAndDescPath(MMS_DATA_NODE* childNode,CString &strDescPath);

	virtual void InsertJournalListCtrl_UI(int nEntryNum,int nViewListIndex,const CString &strEntryID,char *pLogEntryName ,const CString &strEntryTime, tagDA *pDA){return;}//zhouhj 20180122 ���������־���б���ͼ

	void ExitAllFunc()
	{
		long nMmsDvIndex = 0;

		for (nMmsDvIndex = 0; nMmsDvIndex < numDevice; nMmsDvIndex++)
		{
			m_oFuncParamEx[nMmsDvIndex].m_bExitFunc = TRUE;
		}
	}

//2022-10-12  lijunqing  ������LINUX��ֲ����ƽ̨��صĴ�����ܵ��������
public:
	//����
	void InitLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bOnlyLink=FALSE);
	void InitLinkDeviceFuncPara_AutoTest(ST_INT nDeviceIndex, BOOL bOnlyLink=FALSE);
	void InitUnLinkDeviceFuncPara(ST_INT nDeviceIndex, BOOL bAutoTest=FALSE, BOOL bOnlyLink=FALSE);
	//ö���豸�߼��豸
	void InitEnumLNFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas=FALSE);
	void InitEnumLDFuncPara(ST_INT nDeviceIndex, BOOL bFreeFuncParas=FALSE);
	//ö��ȫ������
	void InitReadDeviceFuncParas(ST_INT nDeviceIndex,BOOL bReadAll, BOOL bFreeFuncParas=TRUE);
	//ö���߼��豸����
	void InitReadLDeviceFuncParas(ST_INT nDeviceIndex, long nLDeviceIndex);
	// 2013-3-4  ����ö�ٶ�ֵ������
	void InitReadLDProtFuncParas(ST_INT nDeviceIndex, long nLDeviceIndex);
	//ö���߼��豸LN����
	void InitReadLDeviceDatasFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nTypeID);
	//ö���߼��豸LN��ֵ
	void InitReadLDeviceValuesFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nTypeID);
	//ö���豸ĳ�����͵�����
	void InitDeviceReadDatasFuncParas(ST_INT nDeviceIndex, ST_INT nTypeID);
	//ö���߼��豸LN����
	void InitWriteDatasFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nTypeID);
	//����ֵ����
	void InitReadLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex);
	//д��ֵ����
	void InitWriteLDeviceZoneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nZone);
	//д��ֵ
	//void InitWriteSetsFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nSEIndex=-1);
	void InitWriteCurrSetsFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, long nZone, BOOL bDeleteAll);
	//���ƣ�ѹ�塢ң�ء�......
	void InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsDaTypeID);
	void InitCtrlWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType);
	void InitCtrlWriteFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bDeleteAll=TRUE);
	void InitCtrlWriteOneFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex
		, ST_INT nDAIndex1, ST_INT nDAIndex2, ST_INT nDAValue1, ST_INT nDAValue2, ST_INT nTDelayAfterSel);
	void InitCtrlWriteOneFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex
		, CString &strSelID, ST_INT nDAValueSel, CString &strExecID, ST_INT nDAValueExec, ST_INT nTDelayAfterSel);
	void InitReadOneFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nDataIndex, BOOL bDeleteAll);

	//����װ��
	void ResetDevice(ST_INT nDeviceIndex, ST_INT nLDIndex);

	//����
	void InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, BOOL bFreeFuncParas);
	void InitCallReportFlagDefault(ST_INT nDeviceIndex);
	void InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart);
	void InitCallReportFuncParasEx(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, UINT nBrcbIndex, BOOL bFreeFuncParas);
	void InitStopReportFuncParas(ST_INT nDeviceIndex, BOOL bFreeFuncParas);
	void InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);

	ST_INT GetDsIndex(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType);

	//��д����
	void InitReadJournalState(ST_INT nDeviceIndex, ST_INT nLDeviceIndex, const CString &strJournalName, HWND hWnd);
	void InitReadJournal(ST_INT nDeviceIndex, ST_INT nLDeviceIndex, const CString &strJournalName
		,ST_INT bStart, ST_INT nStartType, CTime &tmStart, long long nStartEntry
		, ST_INT bEnd, ST_INT nEndType, CTime &tmEnd, ST_INT nEntryNum);
	void InitGetFileDir(ST_INT nDeviceIndex, const CString &strPath,BOOL bOnlyReadCfg = FALSE);
	void InitUploadFile(ST_INT nDeviceIndex, const CString &strPath);
	void InitUploadFiles(ST_INT nDeviceIndex, const CStringArray &arrPaths);
	void InitReadDevice(ST_INT nDeviceIndex, BOOL bFreeFuncParas = TRUE) ;
	//	void InitGetFile();
	void InitDvmEnum(ST_INT nDeviceIndex,const CString &strFileName,BOOL bEnumSetting,BOOL bEnumRelayEna,BOOL bEnumParameter,
		BOOL bEnumRelayAin,BOOL bEnumRelayDin,BOOL bEnumTripInfor,BOOL bEnumAlarm_Warning,BOOL bEnumRelayBlk,
		BOOL bEnumRelayState,BOOL bEnumRelayFunEn,BOOL bEnumLog,BOOL bDevStdMsg,BOOL bFreeFuncParas); 
	void InitGetFile(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName);
	void InitGetFilePara(ST_INT nDeviceIndex, const CString &strPath,const CString &strFileName, const CString &strPostfix);
	void InitReadFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDataType);
	void InitReadFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType);
	void InitReadFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);
	void InitReadFuncPara_Set(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, ST_INT nZone, ST_INT nSG, BOOL bDeleteAll);

	void InitWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDataType);
	void InitWriteFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_CHAR *strDataType);
	void InitWriteFuncParasSingle(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex);

	void SetReportRet(CFuncParamEx *pFuncParaEx,BOOL bSucc, BOOL bStart_NotStop);

	// 2013-4-8  ADD
	BOOL CheckCurSelIsSetting(int nDeviceIndex, int nLDIndex, int nDsIndex);
	BOOL CheckCurSelIsParameter(int nDeviceIndex, int nLDIndex, int nDsIndex);
	BOOL CheckCurSelIsDout(int nDeviceIndex, int nLDIndex, int nDsIndex);

	void ValidateCurrFunc(long nDeviceIndex);
	BOOL CallFirstFunc(long nDeviceIndex);
	BOOL CallCurrFunc(long nDeviceIndex);
	BOOL CallNextFunc(long nDeviceIndex);
	BOOL IsFuncsAllFinish(long nDeviceIndex);
	BOOL IsInFuncsCallState(long nDeviceIndex);
	void OnCallFuncError(long nDeviceIndex);
	void OnUnlink(CFuncParamEx *pFuncParaEx);

	void ExitAllConnFunc(ST_INT nDeviceIndex);
	void ValidateCurrFunc_ReadZone(CFuncParam *pParam);

	virtual void ProgDlg_CallFirstFunc(long nDeviceIndex);
	virtual void ProgDlg_CallCurrFunc(long nDeviceIndex);
	virtual void ProgDlg_StopProgress(long nDeviceIndex);
};

/* 2012-09-28  �� UTF-8 ����תΪ���ַ� */
CString mms_UTF8ToUnicode(const char* str , int len);
ST_INT mms_UTF8ToUnicodeEx(const char* str , int len, char *pszDest);

CString get_all_filedir_path(XMMS_FILE_SYS_OBJ *pTagFileDir);//

// 2013-2-18  UNICOD ����װ UTF_8
int g_f_wcs_to_pchar(CString& wstr,char * p);
ST_BOOLEAN convert_btod_to_timet(MMS_BTOD &btod, tagEVENTTIME &tmEvent);

ACSI_NODE* Global_get_ACSI_NODE(const int &nDevIndex);

extern CMmsApi *theMmsApi;
extern BOOL g_bMmsEngineDebugMode; 
extern BOOL g_bMmsEnumLDAfterReadXml; 
extern long g_nExitAppForException; 
extern BOOL g_bUseDvmMapFile; 
extern 	BOOL g_bMultDevModel;
extern long g_nSetDeviceCheck;
extern long g_nIntgPd;
extern BOOL g_bExportModelAuto; 
extern BOOL g_bUseDsDout; 
extern BOOL g_bAutoGenModelDatas; 

CString mms_CONFIG_PATH();
CString mms_VMD_PATH();

long mms_GetDeviceReportCount(ACSI_NODE *pACSI_NODE);
long MultiByteToUtf8(char* pBuffer);

long Global_GetSysObjFileNum_CurDir(XMMS_FILE_SYS_OBJ *pFileDir);

//#define _use_debug_malloc

//2022-10-12  lijunqing
extern BOOL g_bMmsEngineSingleDeviceMode; 

//����Ϊ����ģʽ���ڴ�ģʽ�£�
//1�������ɹ�����ģ���ļ�
//2��ͨѶ������Ϸ���
extern BOOL g_bMmsEngineViewErrorInfor; 
extern BOOL g_bMmsEngineCommError; 

//////////////////////////////////////////////////////////////////////////
#define WM_PROGRESS_START   WM_USER+1010
#define WM_PROGRESS_STOP	WM_USER+1011
#define WM_PROCEDURE_RESET	(WM_USER+1012)

#define WM_SAVE_ALL_DEVICES_RCD_FILES  (WM_USER+1013)
#define WM_UPDATE_DEVICE_IP_DESC  (WM_USER+1014)


//2022-12-30 lijunqing for cms
CString Global_GetFileDirFullPath(XMMS_FILE_SYS_OBJ *pTagFileDir);
//2022-12-30  lijunqing for cms
ST_RET asn1_convert_timet_to_btime6 (time_t tThis, MMS_BTIME6 *bTime6);
ST_BOOLEAN convert_btod_to_timet(MMS_BTOD &btod, tagEVENTTIME &tmEvent);
long Global_GetSysObjFileNum_CurDir(XMMS_FILE_SYS_OBJ *pFileDir);
ST_BOOLEAN Global_MarkOldFile(XMMS_FILE_SYS_OBJ *pFileDir);
XMMS_FILE_SYS_OBJ* Global_CheckRepeatOfSysobj(const char *pName, XMMS_FILE_SYS_OBJ *pFileDir);
ST_RET CompareData(tagDA*pSrc, tagDA*pDst);
ST_RET asn1_convert_btod_to_utc (MMS_BTOD *btod, MMS_UTC_TIME *utc);
XDLT_RPC_METHOD* Global_RpcMethodAddNewMethod(MMS_ADDR_VECTOR *pVector,const char *pParaFuncation);
XDLT_RPC_METHOD* Global_FindRpcMethod(MMS_ADDR_VECTOR *pVector,const char *pParaFuncation);
ST_VOID mms_ReleaseValue(tagDAValue *pValue, BOOL bValString);
ST_VOID mms_Free_Journal(LD_LOG_INFO *Journal);
ST_VOID Convert_UTC_To_BCD(tagEVENTTIME* lpTimeBCD, MMS_UTC_TIME UTCTime);
//2022-12-30  lijunqing for cms

void WriteDataAfterWait(CThreadProgressInterface *pThread, long nWaiteTime, const CString &strWriteTitle, const CString &strText);
tagDA* mms_new_tagda(long nCount);
tagDA* mms_new_tagda();
