#pragma once

#include "mms_global_include.h"

#include "../../../Module/BaseClass/ThreadProgressInterface.h"

#ifdef _PSX_QT_LINUX_
#include <pthread.h>
#endif

//////////////////////////////////////////////////////////////////////////
#define	FuncID_TestProc		100		//测试网络

#define	FuncID_UnKnow		-1		//未知
#define	FuncID_Link			0		//联机
#define	FuncID_UnLink		1       //释放
#define	FuncID_Write		2		//写数据
#define	FuncID_Read			3		//读数据
#define	FuncID_StartRpt		4		//启动报告
#define	FuncID_StopRpt		5		//停止报告
#define FuncID_GetSGNum		6		//获取当前运行区
#define FuncID_SetSGNum		7		//设置当前运行区
#define FuncID_EnumLD		8		//枚举装置目录
#define FuncID_SetSENum		9		//切换编辑定值区
#define FuncID_CnfSetSE     10		//固化编辑定值区
#define FuncID_CtrlWrite    11		//MMS_CtrlWrite
#define FuncID_Reset		12      //装置复归
#define	FuncID_WriteSingle	13		//直接写数据
#define FuncID_CtrlWriteOne 14		//MMS_CtrlWriteOne
#define	FuncID_Read_SET	    15		//读数据-编辑区定值
#define	FuncID_ReadDir	    16		//读数据-文件目录
#define	FuncID_ReadFile	    17		//读数据-文件
#define	FuncID_ReadOne	    18		//读数据-单个
#define	FuncID_ReadJournalCount   19		//读日志条目数
#define	FuncID_ReadJournal   20		//读日志
#define FuncID_EnumLN		21		//枚举模型

#define	FuncID_UploadFile   22		//上传文件到UPLOAD目录 //zhouhj
#define	FuncID_ReadDevice   23		//通过解析读节点方式读取的node读取new装置所有数据集数据 //zhouhj
#define FuncID_DvmEnum      24      //根据参数重新枚举模型,读取模型数据值
#define FuncID_ReadRPC      25      //读取远程调用方法
#define FuncID_RpcCall      26      //读取远程调用过程

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define WM_Notify_Msg		WM_USER + 3010


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CMDTYPE_SERVER  0
#define CMDTYPE_CLIENT  1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CFuncParam
{
public:
	CFuncParam()
	{
//		m_hNotifyWnd = NULL;
		m_nFuncID = FuncID_TestProc/*FuncID_EnumLD*/;//zhouhj 20210327
		m_nDvID = 0;
		m_nLDID = 0;		
		m_nDSID = 0;
		m_nSGID = 0;		
		m_nSGNum = 0;		
		m_nRptGI = SD_FALSE;
		m_nDaIndex1 = 0;
		m_nDaIndex2 = 0;
		m_nTDelayAfterSel = 0;
		m_nDaValue1 = 0;
		m_nDaValue2 = 0;
		m_nSEID = 0;
		m_nCmdType = CMDTYPE_SERVER;

		memset(m_pszPath,0,MAX_FILE_NAME+1);
		memset(m_pszFileName,0,MAX_FILE_NAME+1);

		//journal
		m_psz_vmd_spec[0] = 0;

		m_b_range_start_pres = 0;		/* range start spec present	*/
		m_n_start_tag = 0;		/* start tag			*/	/*  0 - starting time		*/	/*  1 - starting entry		*/
		ZeroMemory(&m_start_time, sizeof(m_start_time));;			/* range starting time		*/
		m_n_start_entry = 0;		/* length of starting entry	*/

		m_range_stop_pres = 0;		/* range stop spec present	*/
		m_stop_tag = 0;			/* stop tag			*/	/*  0 - ending time		*/	/*  1 - number of entries	*/
		ZeroMemory(&m_start_time, sizeof(m_end_time));			/* range ending time		*/
		m_num_of_entries = 0;		/* number of entries		*/
		m_nBrcbIndex = 0;
	}

	~CFuncParam(){}

protected:
//	HWND m_hNotifyWnd;  //窗口句柄

private:
	ST_INT m_nFuncID;	//功能ID
	ST_INT m_nDvID;		//装置索引
	ST_INT m_nLDID;		//逻辑设备索引
	ST_INT m_nDSID;		//数据集类型
	ST_INT m_nSGNum;	//定值区数
	ST_INT m_nSGID;		//当前运行定值区
	ST_INT m_nSEID;		//当前编辑定值区
	ST_BOOLEAN m_nRptGI;	//是否总召报告
	ST_INT m_nCmdType;

	ST_INT m_nDaIndex1, m_nDaIndex2, m_nTDelayAfterSel;//zhouhj 181102 用m_nDaIndex2来标识是否只读取后缀为“*.cfg”的文件目录；为1表示只读取后缀为“*.cfg”的文件目录
	ST_INT m_nDaValue1, m_nDaValue2;
	ST_CHAR m_pszPath[MAX_FILE_NAME+1];//文件本地存放的根文件夹路径
	ST_CHAR m_pszFileName[MAX_FILE_NAME+1];//文件装置内部全路径名称

	//日志部分
	//JSTAT_REQ_INFO jstat_req;
	//JREAD_REQ_INFO jread_req;
	ST_CHAR m_psz_vmd_spec[MAX_IDENT_LEN+1];
	ST_CHAR m_psz_journal_ref[MAX_IDENT_LEN+1];//zhouhj20180117

	ST_BOOLEAN  m_b_range_start_pres;		/* range start spec present	*/
	ST_INT16    m_n_start_tag;		/* start tag			*/	/*  0 - starting time		*/	/*  1 - starting entry		*/
	MMS_BTOD  m_start_time;			/* range starting time		*/
	long long int      m_n_start_entry;		/* length of starting entry	*/

	ST_BOOLEAN  m_range_stop_pres;		/* range stop spec present	*/
	ST_INT16    m_stop_tag;			/* stop tag			*/	/*  0 - ending time		*/	/*  1 - number of entries	*/
	MMS_BTOD m_end_time;			/* range ending time		*/
	ST_INT32    m_num_of_entries;		/* number of entries		*/

	// 	ST_BOOLEAN  m_list_of_var_pres;		/* list of variables present	*/
	// 	ST_INT      m_num_of_var;		/* number of variables		*/
	// 	ST_BOOLEAN  sm_a_entry_pres;		/* start after entry present	*/
	// 	MMS_BTOD m_time_spec;			/* time specification		*/
	// 	ST_INT      m_entry_spec_len;		/* entry specification length	*/
	// 	ST_UCHAR    *m_entry_spec;		/* entry specification		*/	/*  list of pointers to variables*/	/*  ST_CHAR *list_of_var [num_of_var];	*/

	ST_INT m_nBrcbIndex;
public: 
	void InitPara(CFuncParam *pPara)
	{
//		m_hNotifyWnd = pPara->m_hNotifyWnd;  //窗口句柄
		m_nFuncID = pPara->m_nFuncID;	//功能ID
		m_nDvID = pPara->m_nDvID;		//装置索引
		m_nLDID = pPara->m_nLDID;		//逻辑设备索引
		m_nDSID = pPara->m_nDSID;		//数据集类型
		m_nSGNum = pPara->m_nSGNum;	//定值区数
		m_nSGID = pPara->m_nSGID;		//当前运行定值区
		m_nSEID = pPara->m_nSEID;		//当前编辑定值区
		m_nRptGI = pPara->m_nRptGI;	//是否总召报告
		m_nDaIndex1 = pPara->m_nDaIndex1;	
		m_nDaIndex2 = pPara->m_nDaIndex2;	
		m_nTDelayAfterSel = pPara->m_nTDelayAfterSel;	
		m_nDaValue1 = pPara->m_nDaValue1;
		m_nDaValue2 = pPara->m_nDaValue2;
		m_nCmdType = pPara->m_nCmdType;
		memcpy(m_pszPath, pPara->m_pszPath, MAX_FILE_NAME+1);
		memcpy(m_pszFileName, pPara->m_pszFileName, MAX_FILE_NAME+1);


		//journal
		memcpy(m_psz_vmd_spec, pPara->m_psz_vmd_spec, MAX_IDENT_LEN+1);
		memcpy(m_psz_journal_ref, pPara->m_psz_journal_ref, MAX_IDENT_LEN+1);

		m_b_range_start_pres = pPara->m_b_range_start_pres;		/* range start spec present	*/
		m_n_start_tag = pPara->m_n_start_tag;		/* start tag			*/	/*  0 - starting time		*/	/*  1 - starting entry		*/
		m_start_time = pPara->m_start_time;			/* range starting time		*/
		m_n_start_entry = pPara->m_n_start_entry;		/* length of starting entry	*/

		m_range_stop_pres =pPara->m_range_stop_pres;		/* range stop spec present	*/
		m_stop_tag = pPara->m_stop_tag;			/* stop tag			*/	/*  0 - ending time		*/	/*  1 - number of entries	*/
		m_end_time = pPara->m_end_time;			/* range ending time		*/
		m_num_of_entries = pPara->m_num_of_entries;		/* number of entries		*/
		m_nBrcbIndex = pPara->m_nBrcbIndex;
	}

public:

	/* 2012-11-22  设置窗口句柄 */
//	ST_VOID set_hNotifyWnd(HWND hWnd){ m_hNotifyWnd = hWnd; }

	/* 2012-11-22  获取功能ID */
	ST_INT get_FuncID(){ return m_nFuncID; }

	/* 2012-11-22  获取功能ID */
	ST_VOID set_FuncID(ST_INT nFuncID){ m_nFuncID = nFuncID; }

	/* 2012-11-22  校验数据的合法性 */
	ST_BOOLEAN Chck_DevIndex()
	{
		ST_BOOLEAN bRet = m_nDvID>=0&&m_nDvID<MAX_DEVICE;
		return bRet;
	}

	/* 2012-10-17  获取装置索引号 */
	ST_INT get_DevIndex(){ return m_nDvID; }
//	ACSI_NODE* get_ACSI_NODE()	{	return &pACSINode[m_nDvID];	}

	/* 2012-10-17  设置装置索引号 */
	ST_VOID set_DevIndex(ST_INT nDvID){ m_nDvID = nDvID; }

	/* 2012-10-17  获取逻辑设备索引号 */
	ST_INT get_LDvIndex(){ return m_nLDID; }

	/* 2012-10-17  获取逻辑设备索引号 */
	ST_VOID set_LDvIndex(ST_INT nLDID){ m_nLDID = nLDID; }

	/* 2012-10-17  获取装置当前定值组号 */
	ST_INT get_SGID(){ return m_nSGID; }
	ST_INT get_SEID(){ return m_nSEID; }

	/* 2012-10-17  设置装置当前定值组号 */
	ST_VOID set_SGID(ST_INT nSGID){ m_nSGID = nSGID; }
	ST_VOID set_SEID(ST_INT nSEID){ m_nSEID = nSEID; }

	/* 2012-10-17  获取装置定值组数 */
	ST_INT get_SGNum(){ return m_nSGNum; }

	/* 2012-10-17  获取装置定值组数 */
	ST_VOID set_SGNum(ST_INT nSGNum){ m_nSGNum = nSGNum; }

	/* 2012-10-17  设置当前操作的逻辑设备数据类型 */
	ST_VOID set_DSID(ST_INT nType){ m_nDSID = nType; }

	/* 2012-10-17  获取当前操作的逻辑设备数据类型 */
	ST_INT get_DSID(){ return m_nDSID; }

	ST_VOID set_TDelayAfterSel(ST_INT nValue)	{ m_nTDelayAfterSel = nValue; }
	ST_INT get_TDelayAfterSel()					{ return m_nTDelayAfterSel; }

	ST_VOID set_DaIndex1(ST_INT nValue)	{ m_nDaIndex1 = nValue; }
	ST_INT get_DaIndex1()					{ return m_nDaIndex1; }

	ST_VOID set_DaIndex2(ST_INT nValue)	{ m_nDaIndex2 = nValue; }
	ST_INT get_DaIndex2()					{ return m_nDaIndex2; }

	ST_VOID set_DaValue1(ST_INT nValue)	{ m_nDaValue1 = nValue; }
	ST_INT get_DaValue1()					{ return m_nDaValue1; }

	ST_VOID set_DaValue2(ST_INT nValue)	{ m_nDaValue2 = nValue; }
	ST_INT get_DaValue2()					{ return m_nDaValue2; }

	/* 2012-10-17  获取报告是否总招 */
	ST_BOOLEAN get_RptGI(){  return m_nRptGI; }
	/* 2013-4-8  设置报告是否总招 */
	ST_VOID set_RptGI(ST_BOOLEAN bGI){  m_nRptGI = bGI; }

	ST_CHAR* get_Path()	{	return m_pszPath;	}//文件本地存放路径
	void     Set_Path(const ST_CHAR *pszPath)	{	strcpy(m_pszPath, pszPath);	}

	ST_CHAR* get_FileName()	{	return m_pszFileName;	}//文件在装置内部的全路径名称
	void     Set_FileName(const ST_CHAR *pszFileName)	{	strcpy(m_pszFileName, pszFileName);	}

	bool is_ClientCmd()		{	return m_nCmdType == CMDTYPE_CLIENT;	}
	void set_ClientCmd()	{	m_nCmdType = CMDTYPE_CLIENT;	}
	void set_ServerCmd()	{	m_nCmdType = CMDTYPE_SERVER;	}

	//Journal
	void set_range_start_pres(ST_INT nVal)	{	m_b_range_start_pres = nVal;	}
	ST_INT get_range_start_pres()	{	return	m_b_range_start_pres;	}

	void set_start_tag(ST_INT nVal)	{	m_n_start_tag = nVal;	}
	ST_INT get_start_tag()	{	return	m_n_start_tag;	}
	void set_start_time(MMS_BTOD Val)	{	m_start_time = Val;	}
	MMS_BTOD get_start_time()	{	return	m_start_time;;	}
	void set_start_entry(long long int nVal)	{	m_n_start_entry = nVal;	}
	long long int get_start_entry()	{	return	m_n_start_entry;	}

	void set_range_stop_pres(ST_INT nVal)	{	m_range_stop_pres = nVal;	}
	ST_INT get_range_stop_pres()	{	return	m_range_stop_pres;	}
	void set_stop_tag(ST_INT nVal)	{	m_stop_tag = nVal;	}
	ST_INT get_stop_tag()	{	return	m_stop_tag ;	}
	void set_end_time(MMS_BTOD Val)	{	m_end_time = Val;	}
	MMS_BTOD get_end_time()	{	return 	m_end_time;	}
	void set_num_of_entries(ST_INT nVal)	{	m_num_of_entries = nVal;	}
	ST_INT get_num_of_entries()	{	return	m_num_of_entries;	}

    void set_vmd_spec(const CString &str_vmd_spec)		{	strcpy(m_psz_vmd_spec, str_vmd_spec.GetString());	}
	ST_CHAR* get_vmd_spec()	{	return m_psz_vmd_spec;	}

    void set_journal_ref(const CString &str_journal_ref)		{	strcpy(m_psz_journal_ref, str_journal_ref.GetString());	}//zhouhj20180117
	ST_CHAR* get_journal_ref()	{	return m_psz_journal_ref;	}//zhouhj20180117

	void set_BrcbIndex(ST_INT nBrcbIndex)	{	m_nBrcbIndex = nBrcbIndex;	}//zhouhj  m_nBrcbIndex从0开始编号,在实际查找时,标识数组编号
	ST_INT get_BrcbIndex()		{		return m_nBrcbIndex;		}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CFuncParams : public CTLinkList<CFuncParam>
{
public:
	CFuncParams(){}
	virtual ~CFuncParams()	{};

	CFuncParam* AddFuncPara(ST_INT nDeviceIndex, ST_INT nFuncID, UINT nMsg)
	{
		CFuncParam *pNew = new CFuncParam();
		pNew->set_DevIndex(nDeviceIndex);
		pNew->set_FuncID(nFuncID);
		AddTail(pNew);
		return pNew;
	}

	CFuncParam* AddFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, 
		ST_INT nFuncID, ST_INT nDsIndex,/* HWND hWnd,*/ UINT nMsg)
	{
		CFuncParam *pNew = new CFuncParam();
		pNew->set_DevIndex(nDeviceIndex);
		pNew->set_LDvIndex(nLDIndex);
		pNew->set_FuncID(nFuncID);
//		pNew->set_hNotifyWnd(hWnd);
		pNew->set_DSID(nDsIndex);
		AddTail(pNew);
		return pNew;
	}

	CFuncParam* AddFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, const CString &strJournalName
		, ST_INT bStart, ST_INT nStartType, CTime &tmStart, long long int nStartEntry
		, ST_INT bEnd, ST_INT nEndType, CTime &tmEnd, ST_INT nEntryNum,   //zhow 写日志用
		ST_INT nFuncID, ST_INT nDsIndex, /*HWND hWnd,*/ UINT nMsg);

	CFuncParam* AddFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex,const CString &strPath,//zhow:20180108 增加传递目录路径的参数 
		ST_INT nFuncID, ST_INT nDsIndex,BOOL bOnlyReadCfg, /*HWND hWnd,*/ UINT nMsg)
	{
		CFuncParam *pNew = new CFuncParam();
		pNew->set_DevIndex(nDeviceIndex);
		pNew->set_LDvIndex(nLDIndex);
        pNew->Set_Path(strPath.GetString());//zhow:20180107 传递读取路径
		pNew->set_FuncID(nFuncID);
//		pNew->set_hNotifyWnd(hWnd);
		pNew->set_DSID(nDsIndex);
		pNew->set_DaIndex2(bOnlyReadCfg);
		AddTail(pNew);
		return pNew;
	}

	CFuncParam* AddFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex,const CString &strLocalRootPath,const CString &strRemoteFileName,//zhow:20180108 增加传递目录路径的参数 
		ST_INT nFuncID, ST_INT nDsIndex, /*HWND hWnd,*/ UINT nMsg)
	{
		CFuncParam *pNew = new CFuncParam();
		pNew->set_DevIndex(nDeviceIndex);
		pNew->set_LDvIndex(nLDIndex);
        pNew->Set_Path(strLocalRootPath.GetString());//zhow:20180107 本地文件夹路径
        pNew->Set_FileName(strRemoteFileName.GetString());//zhow:20180107 远端路径
		pNew->set_FuncID(nFuncID);
//		pNew->set_hNotifyWnd(hWnd);
		pNew->set_DSID(nDsIndex);
		AddTail(pNew);
		return pNew;
	}

	CFuncParam* AddFuncPara(ST_INT nDeviceIndex, ST_INT nLDIndex, 
		ST_INT nFuncID, ST_INT nDsIndex
		, ST_INT nDAIndex1, ST_INT nDAIndex2
		, ST_INT nDAValue1, ST_INT nDAValue2
		, ST_INT nTDelayAfterSel
		, /*HWND hWnd,*/ UINT nMsg)
	{
		CFuncParam *pNew = new CFuncParam();
		pNew->set_DevIndex(nDeviceIndex);
		pNew->set_LDvIndex(nLDIndex);
		pNew->set_FuncID(nFuncID);
//		pNew->set_hNotifyWnd(hWnd);
		pNew->set_DSID(nDsIndex);
		pNew->set_DaIndex1(nDAIndex1);
		pNew->set_DaIndex2(nDAIndex2);
		pNew->set_DaValue1(nDAValue1);
		pNew->set_DaValue2(nDAValue2);
		pNew->set_TDelayAfterSel(nTDelayAfterSel);
		AddTail(pNew);
		return pNew;
	}

	CFuncParam* AddFuncPara(ST_INT nFuncID, ST_INT nDeviceIndex, ST_INT nLDIndex
		, ST_INT nDsIndex, ST_INT nDAIndex
		, /*HWND hWnd,*/ UINT nMsg)
	{
		CFuncParam *pNew = new CFuncParam();
		pNew->set_DevIndex(nDeviceIndex);
		pNew->set_LDvIndex(nLDIndex);
		pNew->set_FuncID(nFuncID);
//		pNew->set_hNotifyWnd(hWnd);
		pNew->set_DSID(nDsIndex);
		pNew->set_DaIndex1(nDAIndex);
		AddTail(pNew);
		return pNew;
	}
	CFuncParam* AddFuncParaRpcCall(ST_INT nDeviceIndex,ST_INT nFuncID,const CString &strParaFunction,
		const CString &strParaCallName,const CString &strParaCallID,
		 ST_INT nVersion, ST_INT nTimeout, ST_INT nRequestType, ST_INT nResponseType
		, /*HWND hWnd,*/ UINT nMsg)
	{
		CFuncParam *pNew = new CFuncParam();
		pNew->set_DevIndex(nDeviceIndex);
		pNew->set_FuncID(nFuncID);
        pNew->Set_Path(strParaFunction.GetString());
        pNew->Set_FileName(strParaCallName.GetString());
		pNew->set_vmd_spec(strParaCallID);
		pNew->set_DaIndex1(nVersion);
		pNew->set_DaIndex2(nTimeout);
		pNew->set_DaValue1(nRequestType);
		pNew->set_DaValue2(nResponseType);
		AddTail(pNew);
		return pNew;
	}
};

class CFuncParamEx : public CFuncParam ,public CFuncParams
{
	//CMmsApi *m_pMmsApi; //theMmsApi  【使用全局API对象】
public:
	CFuncParamEx()
	{
		m_nConnDevIndex = 0;
		m_hThread_Proc_Data = NULL;
		SetsConnectDevice(FALSE);
		m_bHasPostMsg = FALSE;
		m_bEnaRpt = FALSE;
		m_bExitFunc = FALSE;
		m_pProgressInterface = NULL;
	}

	virtual ~CFuncParamEx(){};
	long m_nConnDevIndex;  //装置的编号

#ifdef _PSX_QT_LINUX_
    pthread_t m_hThread_Proc_Data;
#else
	HANDLE m_hThread_Proc_Data;//装置的线程句本
#endif

	ST_BOOLEAN m_bMmsDisConBfConnected;		//联机标志
	BOOL m_bHasPostMsg;
	BOOL m_bEnaRpt;
	BOOL m_bExitFunc;   //终止执行通讯命令

	//2023-1-29 lijunqing 多装置通信，远程通信服务，每个装置都有一个独立的通信过程
	//所以从CMmsApi移动到CFuncParamEx中
	CThreadProgressInterface *m_pProgressInterface;

public:
	void DeleteAllFuncParas()	{	DeleteAll();}
	BOOL IsConnectDevice()
	{
		return m_bIsConnectDevice;
	}

	void SetsConnectDevice(BOOL b=TRUE)
	{
		m_bIsConnectDevice = b;
	}
	POS m_posCurrFuncPara;

	void BeginExecDataProc(CFuncParam *pPara)
	{
		m_bHasPostMsg = FALSE;
	}

	BOOL NeedExitFunc()
	{
		return m_bExitFunc;
	}

	void ClearExitFunc()
	{
		if (m_bExitFunc)
		{
			m_posCurrFuncPara = NULL;
			DeleteAllFuncParas();

			m_bExitFunc = FALSE;
		}
	}

private:
	//将主程序类中原成员变量移动到该类中  以及相关标识连接状态的函数
	BOOL m_bIsConnectDevice;

public:
	void SetTitle(const CString &strTitle);
	void SetMaxRange(long nMaxRange);
	void ResetProcess();
	void StepIt();
	void ShowMsg(const CString &strMsg);
	void StartTimer(long nTimerLong);

	void Finish(DWORD dwParam=0);
	void StepPos(long nPos);
	void Exit();

};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL convert_timet_to_btod(CTime &tmStart, MMS_BTOD &btod);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////