#if !defined(_SHAREMEM)
#define _SHAREMEM

#include "61850ClientGlobalDef.h"
#include "mms_string.h"
#include "DataAddrVector.h"

#define _use_mms_string
// #define _use_tagRelaySOEFIFO

#define   MAX_DEVICE	395
#define   MAX_RCB_VMD	60
#define   NAMESIZE		300  //zhouhj 20210528  由于电科院一致性测试,部分rptID名称达到接近220,故改为300  原来为64
#define	  LEVELSIZE		20

#define   MAX_LD_VMD	1300    //zhouhj 20210401  从50改为1300
#define   MAX_DA_VMD	100
#define   MAX_DA_DS		1000
#define   MAX_DS_VMD	50
#define   MAX_LN_VMD	500
#define   MAX_DA_NUM	1000
#define   MAX_DASET_NUM 100	
#define   MAX_REPORT_COUNT	800//zhouhj  原来3000 
#define   MAX_ITEMCOUNT_FOR_DATACHANGEMSG	30

#define   CMD_NULL			0
#define   CMD_DIR			1
#define   CMD_START_RCB		2
#define   CMD_STOP_RCB		3
#define   CMD_CONTROL		4
#define   CMD_READ_SG		5
#define   CMD_READ_SG_ZONE	6
#define   CMD_WRITE_SE		7
#define   CMD_CONNECT		8
#define   CMD_TEST			9


#define	  STAT_NULL			0
#define	  STAT_END			1
#define	  STAT_ERROR		2
#define	  STAT_TIMEOUT		3
#define	  STAT_WAIT			4
#define	  INFOR_BUFFER_WRITEDATA_LEN			2048

#define DA_DATATYE_BOOL              0x03
#define DA_DATATYE_INT                 0x05
#define DA_DATATYE_UINT               0x06
#define DA_DATATYE_FLOAT             0x07
#define DA_DATATYE_OCTET_STR             0x09 //zhouhj20180516
#define DA_DATATYE_VISIBLE_STR             0x0e  //zhouhj20180516   原来为0x0a
#define DA_DATATYE_BIT_STR          0x04
#define DA_DATATYE_UTC_TIME        0x11
#define DA_DATATYE_UTF8_STR        0x13   //zhouhj 20180928  原来为0x08但解析UTF8_STR出错, 测试后应该为0x31  即#define UNICODE_STRING255_TYPEID		19

#define DA_DATATYE_BYTE               0x06
#define DA_DATATYE_UBYTE               0x06
#define DA_DATATYE_OVSTRING64               0x06
#define DA_DATATYE_BVSTRING2               0x06


#define DA_DATATYE_STRING           0xF0
#define DA_DATATYE_ARRAY             0xF1
#define DA_DATATYE_STRUCT           0xF2

#define _use_dynamic_mem

//for cms  2022-12-30
/************************************************************************/
#define MMS_BTOD4	4
#define MMS_BTOD6	6
/************************************************************************/

typedef struct mms_utc_time_tag
{
	ST_UINT32 secs;      	/* Number of seconds since January 1, 1970	*/
	ST_UINT32 fraction;  	/* Fraction of a second				*/
	ST_UINT32 qflags;	/* Quality flags, 8 least-significant bits only	*/
} MMS_UTC_TIME;

typedef struct btod_data
{
	ST_INT form;	 	/* MMS_BTOD6, MMS_BTOD4				*/
	ST_INT32 ms;	      	/* Number of milliseconds since midnight	*/
	ST_INT32 day;	      	/* Number of days since Jan 1, 1984		*/
} MMS_BTOD;

typedef struct
{
	ST_INT32 ms;		/* Number of milliseconds since midnight	*/
	ST_INT32 day;		/* Number of days since Jan 1, 1984		*/
} MMS_BTIME6;


/* File Directory */
typedef struct
{
	ST_UINT32  fsize; 			/* file size (# bytes)		*/
	ST_BOOLEAN mtimpres;			/* last modified time present	*/
	time_t     mtime; 			/* last modified time		*/
	MMS_MEM_STRING filename;
} MVL_DIR_ENT;
//for cms

typedef union
{
	ST_UCHAR	u;
	ST_INT      i;
	ST_LONG     l;
	ST_FLOAT    f;

#ifdef _use_mms_string
	MMS_MEM_STRING string;
#else
	ST_CHAR     string[NAMESIZE*2];
#endif

	MMS_UTC_TIME  utctime;
}tagValue;

typedef union
{
	ST_UCHAR	u;
	ST_INT      i;
	ST_LONG     l;
	ST_FLOAT    f;
	ST_CHAR     string[NAMESIZE*2];
	MMS_UTC_TIME  utctime;
}tagValueX;

typedef struct
{
	ST_UCHAR     repEnd;		/*hmi clear 遥控 1-选择 2-执行 3-取消*/
	ST_UCHAR     *pnet_info;	/* *MVL_NET_INFO */
	ST_UCHAR     needTest;	/*网络测试*/
	ST_UCHAR     needDirectory;  /*获取目录*/
	ST_UCHAR     needData;  /*获取目录*/
	ST_CHAR      DataName[NAMESIZE];  /*获取目录*/
	ST_UCHAR     needConnect;	/*网络重连*/
	ST_UCHAR     needSBO;		/*遥控 1-选择 2-执行 3-取消*/
	ST_INT       iValue;		//control 值
	ST_CHAR      ctrlVarName[NAMESIZE];
	ST_UCHAR     readSG;		/*读保护定值*/
	ST_UCHAR     bConnect;	/*已连接*/
	ST_UCHAR     writeSG;		/*写保护定值*/
	ST_UCHAR     activeZone;	/*激活保护定值区*/
	ST_INT       zoneSet;		//保护定值区号
	ST_UCHAR     startRCB[MAX_RCB_VMD];	/*启动报告*/
	ST_UCHAR     stopRCB[MAX_RCB_VMD];	/*停止报告*/
	ST_INT       g_timeOut;
	ST_UCHAR     IsEnd;		//0-无效  1-结束  2-出错 3-超时 4-请求中
	ST_UCHAR     CMD;			//当前服务命令
	ST_UCHAR	   bShow;		//目录已获取，可以显示
	ST_UCHAR	   testCount;	//测试网络次数
	ST_INT	   idleCount;	//下行命令空闲时间
}ACSI_CTRL;

typedef struct
{
#ifdef _use_mms_string
	MMS_MEM_STRING mmsName;
#else
	ST_CHAR	  mmsName[NAMESIZE];
#endif
	tagValue  Value;
}tagDAValue;

typedef struct
{

#ifdef _use_mms_string
	MMS_MEM_STRING   DataType;	//INT, BOOL 等
	MMS_MEM_STRING   mmsName;
#else
	ST_CHAR   DataType[16];	//INT, BOOL 等
	ST_CHAR	  mmsName[NAMESIZE];
#endif

	tagValue  Value;
}tagDAValueEx;

 #define tagDA_use_UNIT_MIN_MAX_STEP

typedef struct tagDA
{	
	ST_CHAR   ReasonCode;
	ST_INT	  Type_id;
	ST_CHAR   DataType[10];	//INT, BOOL 等
	ST_INT     nDataType;
	ST_INT    ApplyType;
	ST_INT    EventNum;
	ST_CHAR   bWrite;		//0-不可写 1-可写
	ST_CHAR   bModify;		//0-未修改 1-已修改

// 	ST_CHAR   bDescri;		//0-读取 1-不读取 描述
// 	ST_CHAR   bUnite;		//0-读取 1-不读取 单位

	tagDAValue DAValue;		//数值
	tagDAValue DADescri;	//描述

	tagDAValue DAUnite;		//单位
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	tagDAValue MaxVal;		//最大值
	tagDAValue MinVal;		//最小值
	tagDAValue StepSize;		//stepsize
#endif
	
	ST_INT    nSubDANum;
	DWORD dwDsMapObj;
	struct tagDA *pSubDA;
}tagDA;

typedef struct tagDA_List_Node
{
	tagDA *DA;
	struct tagDA_List_Node *pNext;
	struct tagDA_List_Node *pPrevious;
}MMS_TAGDA_LIST_NODE;

typedef struct LdJournalData
{
	ST_CHAR    EntryID[8];
	MMS_MEM_STRING LogCtrl;
	MMS_MEM_STRING DataSetName;
	MMS_BTOD occur_time;			/* occurrence time		*/
	ST_INT		numData;			//数据个数
	tagDA*   DAValue;	//数据
}LD_JOURNAL_DATA;

typedef struct
{
	ST_CHAR		rcbName[NAMESIZE];
	ST_CHAR		dsName[NAMESIZE];
	ST_CHAR		RptID[NAMESIZE];
}RCB_NODE;

typedef struct
{
	ST_INT		numData;

#ifdef _use_mms_string
	MMS_MEM_STRING dsName;
	MMS_MEM_STRING mmsVARName[MAX_DA_DS];
#else
	ST_CHAR		dsName[NAMESIZE];
	ST_CHAR     mmsVARName[MAX_DA_DS][NAMESIZE];
#endif
}DATASET_NODE;

typedef struct
{
#ifdef _use_mms_string
	MMS_MEM_STRING LNName;
#else
	ST_CHAR   LNName[NAMESIZE];
#endif
	ST_INT    numDA;
	ST_INT	  lnType;		/*1-测控  2-保护	*/
}LN_NODE;

typedef struct 
{
	ST_INT num;
	ST_BOOLEAN bHasEnum;
	tagDA das[MAX_DA_NUM];
}tagDAList;

typedef struct
{
	ST_BOOLEAN	bHasEnum;			//是否已枚举
	ST_INT      curRcbIndex;		//当前启动的报告索引
	ST_INT		numRcb;				//报告控制块数目
	RCB_NODE	RCB[MAX_RCB_VMD];	//报告控制块
	ST_INT		numData;			//数据个数
	ST_CHAR	DaSetDesc[NAMESIZE];	//数据集描述
	ST_CHAR DataSetID[NAMESIZE];	//数据集名字
	ST_BOOLEAN  bReportFlag;		//判断是否启动报告
	ST_BOOLEAN  bReportRet;			//判断报告是否已上传

#ifdef _use_dynamic_mem
	tagDA*   DataSet;	//数据数组
#else
	tagDA   DataSet[MAX_DA_NUM];	//数据数组
#endif
	DWORD dwDsMapObj;
	DWORD dwTreeItemData;

	ST_CHAR LogCtrl[NAMESIZE];//zhow20180306
}LD_DATASET_INFO;

typedef struct tagJournal
{	
	MMS_MEM_STRING Name;
	MMS_MEM_STRING Dataset;	
	UINT intgPD;//完整性周期 单位ms
	MMS_MEM_STRING logRef;	
	ST_BOOLEAN logEna;		
	ST_UCHAR trgOps;		
}LD_LOG_INFO;

typedef struct
{
//	ST_BOOLEAN	bHasEnum;			//是否已枚举
	ST_INT		    numData;			//数据个数
	ST_CHAR	    Desc[NAMESIZE];	//描述

	LD_LOG_INFO *LogInfo;
}LD_JOURNAL_CTRLS;

//
//////////////////////////////////////////////////////////////////////////

/*数据变化原因：*/
enum UPDATA_REASON
{
	UPDATA_REASON_NULL,       /**< resvr    */
	UPDATA_REASON_DCHG,      /**< Data Change */
	UPDATA_REASON_QCHG,      /**< Quality Change*/
	UPDATA_REASON_DUPD,      /**< Data Updata */
	UPDATA_REASON_INTGPD,    /**< priority */
	UPDATA_REASON_GI        /**< GI     */
};

/*数据值联合体*/
typedef union _DAT_UNIONOO
{
	ST_BOOLEAN  valBool;
	ST_INT8     valByte;
	ST_INT16	valShort;
	ST_INT32	valLong;
	ST_INT64    valInt64;

	ST_UINT8	valUbyte;
	ST_UINT16 	valUshort;
	ST_UINT32   valUlong;
	ST_UINT64   valUint64;

	ST_FLOAT 	valFloat;
	ST_DOUBLE   valDouble;

	ST_UINT16	  q;        /*数据的品质位-对应的数据类型为BVstring13*/

	ST_CHAR valUtf8[256];   /**< 值为UTF8字符串类型时，指向字符串指针 */
	struct
	{
		ST_UINT8	q;			/**< 时间的品质 */
		ST_UINT16	ms;			/**< 数据携带的毫秒信息，已经转化，直接使用；小于1秒 */
		ST_UINT32	secs;		/**< UTC时间，自1970-01-01至今的秒计数 */
	} t;
	ST_CHAR   strTime[50];	//时间字符串格式，一般用这种格式
}_DAT_UNIONOO;

/*节点类型*/
enum NODE_TYPE
{
	IED_TYPE,
	LD_TYPE,
	LN_TYPE,
	FC_TYPE,
	DO_TYPE,
	DA_TYPE,
	ERROR_TYPE
};

/*数据值类型*/
enum VALUE_TYPE
{
	BOOL_TYPE,
	BYTE_TYPE,
	SHORT_TYPE,
	LONG_TYPE,
	UBYTE_TYPE,
	USHORT_TYPE,
	ULONG_TYPE,
	FLOAT_TYPE,
	DOUBLE_TYPE,
	UTCTIME_TYPE,

	UTF8VSTRING255_TYPE,
	BTIME6_TYPE,
	BSTRING2_TYPE,   //value-ST_UINT8--DbPos
	BVSTRING2_TYPE,  //value-ST_UINT8--check
	BVSTRING6_TYPE,
	BVSTRING10_TYPE,
	BVSTRING13_TYPE,
	VSTRING64_TYPE,
	VSTRING65_TYPE,
	VSTRING129_TYPE,
	VSTRING255_TYPE,
	OSTRING8_TYPE,
	OVSTRING64_TYPE,
	UNDEFINE_TYPE
};

typedef struct Data_Node_Struct
{
#ifdef _use_mms_string
	MMS_MEM_STRING name;
#else
	ST_CHAR        name[NAMESIZE+1];
#endif

	enum NODE_TYPE        type;//NODE_TYPE
	ST_CHAR   DataType[16];	//INT, BOOL 等
	_DAT_UNIONOO     data; //_DAT_UNIONOO
	enum UPDATA_REASON  upReason;//UPDATA_REASON

	struct Data_Node_Struct *pParent;
	struct Data_Node_Struct *pFirstChild;
	struct Data_Node_Struct *pNext;
	struct Data_Node_Struct *pPrevious;
}MMS_DATA_NODE;

//////////////////////////////////////////////////////////////////////////
typedef struct
{
	ST_CHAR			LDDesc[NAMESIZE+1];
	ST_CHAR         LDName[NAMESIZE+1];
	ST_INT			numDaSet;		//数据集个数

#ifdef _use_dynamic_mem
	LD_DATASET_INFO			*DataInfo;
#else
	LD_DATASET_INFO			DataInfo[MAX_DASET_NUM];
#endif
	//LD_INFO			*DataInfo;
	DWORD dwTreeItemData;

	MMS_DATA_NODE *mms_data_node;
	LD_JOURNAL_CTRLS JournalCtrls;
	MMS_ADDR_VECTOR JournalDatas;//zhouhj20180129
	//LD_DATASET_INFO dsDout;
}LD_NODE;

typedef struct
{
	ST_CHAR		DeviceModel[100];
	ST_LONG 	IP1;
	ST_LONG 	IP2;
}DEVICE_NODE;


#define _tagRpt_use_DA_ref
#ifdef _tagRpt_use_DA_ref
typedef struct tagRptValue
{
	tagValue Value;
	ST_INT   bString;
}tagRptValue;
#endif

typedef struct
{
	ST_INT		dvIndex;
	ST_INT		dsIndex;
	ST_INT		ldIndex;
	double      tmRcv;
	ST_UINT16   nTmRcvMs;//zhouhj 20200113增加用于当前报文接收时间的毫秒段值
	ST_INT      nTimeGapMs;
	ST_CHAR     EntryID[8];//zhouhj 增加用于传递EntryID

#ifdef _tagRpt_use_DA_ref
	tagDA	         *pDaRef;
	tagRptValue    *Value;
	ST_INT capacity;
	ST_INT size;
#else
	tagDA	    DA;
#endif
}tagRpt;

typedef struct
{
	ST_ULONG  hMsgWnd;
	ST_ULONG  nMsg;
	tagDA   *pRefDA;
	ST_INT  nAcsi;
	ST_INT  nLdIndex;
	ST_INT  nDsIndex;
	ST_INT  nDataIndex;
	ST_CHAR PathName[NAMESIZE];

	//cmd
	ST_INT nCmdID;
	ST_INT nCmdState;
	ST_INT wParam;
	ST_INT lParam;
}tagDataChangeDef;

typedef struct  
{
	ST_INT    Count;
	tagDataChangeDef DataChangeDef[MAX_ITEMCOUNT_FOR_DATACHANGEMSG];
}tagDataChangeMsg, *ptagDataChangeMsg;

#define MAX_MVL_DIR_ENT_COUNT   500
// typedef struct
// {
// 	ST_CHAR PathName[NAMESIZE];
// 	ST_INT nCount;
// 	MVL_DIR_ENT dir[MAX_MVL_DIR_ENT_COUNT];
// } tagFileDir, *ptagFileDir;

typedef struct structMmsFileSysObj
{
	ST_BOOLEAN bIsNew;
	ST_BOOLEAN readfailed;     //读取失败标记位  
	ST_INT nType;  //0=file  1=dir ,根据规则，最后一个字符为‘\’或者‘/’就是目录
	MVL_DIR_ENT filedir;

	struct structMmsFileSysObj  *parent;
	MMS_ADDR_VECTOR subFiles; 
	ST_INT bFirstRead;
}XMMS_FILE_SYS_OBJ, *PXMMS_FILE_SYS_OBJ;

//for cms 2022-12-30  lijunqing
typedef struct structDltRpcMethod
{
#ifdef _use_mms_string
	MMS_MEM_STRING paraFuncation;
	MMS_MEM_STRING paraCallName;
	MMS_MEM_STRING paraCallID;
#else
	ST_CHAR        paraFuncation[NAMESIZE+1];
	ST_CHAR        paraCallName[NAMESIZE+1];
	ST_CHAR        paraCallID[NAMESIZE+1];
#endif

	long nVersion;
	long nTimeout;
	long nRequestType;
	long nResponseType;

#ifdef _use_dynamic_mem
	tagDA   oDataModel;	//数据模型
#else
	tagDA   oDataModel;	//数据模型
#endif

}XDLT_RPC_METHOD, *PXDLT_RPC_METHOD;

typedef struct
{
	ST_INT		numLD;
	ST_INT		numRCB;
	ST_INT		numDA;

#ifdef _use_dynamic_mem
	LD_NODE      *LD;
#else
	LD_NODE		 LD[MAX_LD_VMD];
#endif

	RCB_NODE	 rcb[MAX_RCB_VMD];
	tagDA	     DA[MAX_DA_VMD];
 
	ST_BOOLEAN bConnect;
	ST_BOOLEAN bCanReConnect;
	ST_BOOLEAN bTestLinkState;

	//报告循环缓存
	ST_INT		nReportBeginIndex;
	//ST_INT		nReportEndIndex;
	ST_INT		nCurrReportIndex;
	ST_INT		nCurrReportCount;
	tagRpt	    Reports[MAX_REPORT_COUNT];

	//外部消息定义
	ST_ULONG  hMsgWnd;
	ST_ULONG  nMsg;
	ST_ULONG  hSysMsgWnd;
	ST_ULONG  nSysMsg;

	ST_INT   nSGNum;   //定值区的个数
// 	ST_INT   nCurrSGIndex;  //当前运行定值区
	ST_ULONG  hRptMsgWnd;
	ST_ULONG  nRptMsg;

	ST_CHAR devName[NAMESIZE];

	ST_INT   nRunSGIndex;   //记录当前运行定值区，在修改定值时防止切换不回来
	ST_INT   nEditSGIndex;   //2022-12-30  lijunqing  for cms
	ST_INT   nSetRunSGIndexState;   //是否在设置当前运行区的状态中
	ST_CHAR devID[NAMESIZE];   //装置的ID，用于外部系统创建时访问
	ST_INT   nHasDeviceModel;
	ST_INT   nWriteErrorCount;  //写数据过程中出现的错误
	ST_CHAR  DeviceFilePath[250];//存放设备数据模型文件路径
	MMS_MEM_STRING RcdFilePath;//zhouhj 20180314 用于存放录波文件路径
	MMS_MEM_STRING IpAddr;
	ST_INT  LogTotalNum;//zhouhj 20180322 用于存放日志总数量

	tagDataChangeMsg DataChangeMsg; //2015-3-26添加
	XMMS_FILE_SYS_OBJ       FileDir;
	MMS_ADDR_VECTOR oRpcMethods; //zhouhj 20210719 对应的RPC调用方法   //2022-12-30  lijunqing  for cms

	ST_INT tmSel,		tmExec,		tmTotal;
	ST_INT tmSetSE,		tmSetSG;
	ST_CHAR InfoSel[NAMESIZE],  InfoExec[NAMESIZE];
	ST_CHAR InfoSetSE[NAMESIZE],InfoSetSG[NAMESIZE];
	ST_CHAR InfoWriteData[INFOR_BUFFER_WRITEDATA_LEN];
	ST_CHAR RefDaPath[NAMESIZE];   //报文参考的ID路径
	SYSTEMTIME tmStartExc;//zhouhj20200111 开始执行软压板修改的时刻

	//录波相关
	ST_INT nRecordFileTotalSize; //
	ST_INT nRecordFileSpeen;     //
	ST_INT nRecordFileTotalNum; //
	DWORD dwTreeItemData;

	DWORD num_entries;

	ST_CHAR psw[NAMESIZE]; 
	ST_CHAR key[NAMESIZE]; 

#ifdef _MVL_TYPE_CTRL_use_one_device_
	MVL_TYPE_CTRL *p_mvl_type_ctrl;
#endif

}ACSI_NODE;

#define MAX_SOE_RPT		50

typedef struct
{
	ST_INT		readp;
	ST_INT      writep;
	ST_INT      numSOE;
	ST_CHAR     SoeRPT[MAX_SOE_RPT][120];		//IP最后一个字节，mms变量名，状态值，时间
}tagSOEFIFO;

typedef struct
{
	ST_INT		readp;
	ST_INT      writep;
	ST_INT      numSOE;
	//IP最后一个字节，mms变量名，方向/非方向，状态值，故障类型（汉字），方向故障类型（汉字），时间
	//非方向保护事件不包括方向故障类型
	ST_CHAR     RelaySoeRPT[MAX_SOE_RPT][200];
}tagRelaySOEFIFO;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
	ST_INT		year;
	ST_INT		month;
	ST_INT		day;
	ST_INT		hour;
	ST_INT		minute;
	ST_INT		second;
	ST_INT		ms;
}tagEVENTTIME;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


ST_RET asn1_convert_timet_to_btime6 (time_t tThis, MMS_BTIME6 *bTime6);
void rpt_quit_value(tagRptValue *pValue);
void rpt_quit(tagRpt *pRpt);
ST_VOID mms_Free_Data_Node(MMS_DATA_NODE *p_mms_data_node);
ST_VOID mms_ReleaseValue(tagDAValue *pValue, BOOL bValString);
ST_VOID mms_ReleaseData(tagDA*pData);
ST_VOID mms_Free_tagDA(tagDA*pData);
void mms_Free_tagDAs(tagDA *pTagDAs, ST_INT nCount);
void mms_Free_LD_DATASET_INFO(LD_DATASET_INFO *pDataSet);
ST_VOID mms_Free_Journal(LD_LOG_INFO *Journal);
ST_VOID mms_Free_LD_JOURNAL_CTRLS(LD_JOURNAL_CTRLS *pJournal);
ST_VOID mms_JournalDataOfVector_Free(unsigned long* pJournalDatas,ST_INT nNumOfData);
ST_VOID mms_Free_LD_NODE(LD_NODE *pLdevice);
ST_VOID mms_file_sys_free(XMMS_FILE_SYS_OBJ *pMmsFileSysObj);
ST_VOID mms_Free_ACSI_NODE(ACSI_NODE *pDevice);
ACSI_NODE* mms_New_ACSI_NODE_numLD(ACSI_NODE *pDevice, ST_INT numLD, BOOL bDelete);
MMS_DATA_NODE* mms_node_append_sibling(MMS_DATA_NODE *pParent, MMS_DATA_NODE** ppSiblingNode, const char *pName, enum NODE_TYPE type);
MMS_DATA_NODE* mms_node_append_sibling2(MMS_DATA_NODE *pParent, MMS_DATA_NODE** ppSiblingNode);
ST_VOID mms_New_LD_JOURNAL_CTRLS_numData(LD_JOURNAL_CTRLS *pDataSet, ST_INT numData);
ST_VOID mms_New_LD_NODE_numDataset(LD_NODE *pLdevice, ST_INT numDataset);
ST_VOID mms_New_LD_NODE_numJournal(LD_NODE *pLdevice, ST_INT numJournal);//2018.1.17zhouhj
ST_VOID mms_New_LD_DATASET_INFO_numData(LD_DATASET_INFO *pDataSet, ST_INT numData);
ST_VOID mms_InitData(tagDA*pDA);
ST_VOID mms_InitDatas(tagDA*pDA, long nCount);
ST_VOID mms_InitDA_DataType(tagDA*pSrc);
ST_VOID Convert_UTC_To_BCD(tagEVENTTIME* lpTimeBCD, MMS_UTC_TIME UTCTime);
ST_VOID mms_CopyData(tagDA*pSrc, tagDA*pDst, BOOL bRpt);
BOOL convert_btod_to_timet(MMS_BTOD &btod, tagEVENTTIME &tmEvent);
long Global_GetSysObjFileNum_CurDir(XMMS_FILE_SYS_OBJ *pFileDir);
CString Global_GetFileDirFullPath(XMMS_FILE_SYS_OBJ *pTagFileDir);
BOOL Global_MarkOldFile(XMMS_FILE_SYS_OBJ *pFileDir);
XMMS_FILE_SYS_OBJ* Global_CheckRepeatOfSysobj(const char *pName, XMMS_FILE_SYS_OBJ *pFileDir);
ST_RET CompareData(tagDA*pSrc, tagDA*pDst);
ST_RET asn1_convert_btod_to_utc (MMS_BTOD *btod, MMS_UTC_TIME *utc);
XDLT_RPC_METHOD* Global_RpcMethodAddNewMethod(MMS_ADDR_VECTOR *pVector,const char *pParaFuncation);
XDLT_RPC_METHOD* Global_FindRpcMethod(MMS_ADDR_VECTOR *pVector,const char *pParaFuncation);



extern ST_CHAR g_strTrgOps[NAMESIZE];
extern ST_CHAR g_strOptFlds[NAMESIZE];
//extern long  g_nCanWriteActiveSG;
extern long  g_nWriteCtrlCheckMode;
//extern long  g_nEnaWriteWait;
//extern long g_bMmsReadUseReport; 
extern long g_bResetOnlyClearReport; 

extern long g_nMaxReportCount;
extern ST_INT g_nCurErrorCode;//错误原因码
extern ST_INT g_nCurErrorClass;//错误class
extern ST_INT g_nCurErrorInforRpt;//压板类单独上送的错误码值

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern ST_INT	g_nCfgMaxDevNum;//从配置文件中读取到的最大装置数量

#endif