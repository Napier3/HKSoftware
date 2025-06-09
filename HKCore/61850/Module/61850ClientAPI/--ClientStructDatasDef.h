#if !defined(_SHAREMEM)
#define _SHAREMEM

#include "61850ClientGlobalDef.h"
#include "mms_string.h"
#include "DataAddrVector.h"

#define _use_mms_string
// #define _use_tagRelaySOEFIFO

#define   MAX_DEVICE	395
#define   MAX_RCB_VMD	60
#define   NAMESIZE		300  //zhouhj 20210528  ���ڵ��Ժһ���Բ���,����rptID���ƴﵽ�ӽ�220,�ʸ�Ϊ300  ԭ��Ϊ64
#define	  LEVELSIZE		20

#define   MAX_LD_VMD	1300    //zhouhj 20210401  ��50��Ϊ1300
#define   MAX_DA_VMD	100
#define   MAX_DA_DS		1000
#define   MAX_DS_VMD	50
#define   MAX_LN_VMD	500
#define   MAX_DA_NUM	1000
#define   MAX_DASET_NUM 100	
#define   MAX_REPORT_COUNT	800//zhouhj  ԭ��3000 
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
#define DA_DATATYE_VISIBLE_STR             0x0e  //zhouhj20180516   ԭ��Ϊ0x0a
#define DA_DATATYE_BIT_STR          0x04
#define DA_DATATYE_UTC_TIME        0x11
#define DA_DATATYE_UTF8_STR        0x13   //zhouhj 20180928  ԭ��Ϊ0x08������UTF8_STR����, ���Ժ�Ӧ��Ϊ0x31  ��#define UNICODE_STRING255_TYPEID		19

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
	ST_UCHAR     repEnd;		/*hmi clear ң�� 1-ѡ�� 2-ִ�� 3-ȡ��*/
	ST_UCHAR     *pnet_info;	/* *MVL_NET_INFO */
	ST_UCHAR     needTest;	/*�������*/
	ST_UCHAR     needDirectory;  /*��ȡĿ¼*/
	ST_UCHAR     needData;  /*��ȡĿ¼*/
	ST_CHAR      DataName[NAMESIZE];  /*��ȡĿ¼*/
	ST_UCHAR     needConnect;	/*��������*/
	ST_UCHAR     needSBO;		/*ң�� 1-ѡ�� 2-ִ�� 3-ȡ��*/
	ST_INT       iValue;		//control ֵ
	ST_CHAR      ctrlVarName[NAMESIZE];
	ST_UCHAR     readSG;		/*��������ֵ*/
	ST_UCHAR     bConnect;	/*������*/
	ST_UCHAR     writeSG;		/*д������ֵ*/
	ST_UCHAR     activeZone;	/*�������ֵ��*/
	ST_INT       zoneSet;		//������ֵ����
	ST_UCHAR     startRCB[MAX_RCB_VMD];	/*��������*/
	ST_UCHAR     stopRCB[MAX_RCB_VMD];	/*ֹͣ����*/
	ST_INT       g_timeOut;
	ST_UCHAR     IsEnd;		//0-��Ч  1-����  2-���� 3-��ʱ 4-������
	ST_UCHAR     CMD;			//��ǰ��������
	ST_UCHAR	   bShow;		//Ŀ¼�ѻ�ȡ��������ʾ
	ST_UCHAR	   testCount;	//�����������
	ST_INT	   idleCount;	//�����������ʱ��
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
	MMS_MEM_STRING   DataType;	//INT, BOOL ��
	MMS_MEM_STRING   mmsName;
#else
	ST_CHAR   DataType[16];	//INT, BOOL ��
	ST_CHAR	  mmsName[NAMESIZE];
#endif

	tagValue  Value;
}tagDAValueEx;

 #define tagDA_use_UNIT_MIN_MAX_STEP

typedef struct tagDA
{	
	ST_CHAR   ReasonCode;
	ST_INT	  Type_id;
	ST_CHAR   DataType[10];	//INT, BOOL ��
	ST_INT     nDataType;
	ST_INT    ApplyType;
	ST_INT    EventNum;
	ST_CHAR   bWrite;		//0-����д 1-��д
	ST_CHAR   bModify;		//0-δ�޸� 1-���޸�

// 	ST_CHAR   bDescri;		//0-��ȡ 1-����ȡ ����
// 	ST_CHAR   bUnite;		//0-��ȡ 1-����ȡ ��λ

	tagDAValue DAValue;		//��ֵ
	tagDAValue DADescri;	//����

	tagDAValue DAUnite;		//��λ
#ifdef tagDA_use_UNIT_MIN_MAX_STEP
	tagDAValue MaxVal;		//���ֵ
	tagDAValue MinVal;		//��Сֵ
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
	ST_INT		numData;			//���ݸ���
	tagDA*   DAValue;	//����
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
	ST_INT	  lnType;		/*1-���  2-����	*/
}LN_NODE;

typedef struct 
{
	ST_INT num;
	ST_BOOLEAN bHasEnum;
	tagDA das[MAX_DA_NUM];
}tagDAList;

typedef struct
{
	ST_BOOLEAN	bHasEnum;			//�Ƿ���ö��
	ST_INT      curRcbIndex;		//��ǰ�����ı�������
	ST_INT		numRcb;				//������ƿ���Ŀ
	RCB_NODE	RCB[MAX_RCB_VMD];	//������ƿ�
	ST_INT		numData;			//���ݸ���
	ST_CHAR	DaSetDesc[NAMESIZE];	//���ݼ�����
	ST_CHAR DataSetID[NAMESIZE];	//���ݼ�����
	ST_BOOLEAN  bReportFlag;		//�ж��Ƿ���������
	ST_BOOLEAN  bReportRet;			//�жϱ����Ƿ����ϴ�

#ifdef _use_dynamic_mem
	tagDA*   DataSet;	//��������
#else
	tagDA   DataSet[MAX_DA_NUM];	//��������
#endif
	DWORD dwDsMapObj;
	DWORD dwTreeItemData;

	ST_CHAR LogCtrl[NAMESIZE];//zhow20180306
}LD_DATASET_INFO;

typedef struct tagJournal
{	
	MMS_MEM_STRING Name;
	MMS_MEM_STRING Dataset;	
	UINT intgPD;//���������� ��λms
	MMS_MEM_STRING logRef;	
	ST_BOOLEAN logEna;		
	ST_UCHAR trgOps;		
}LD_LOG_INFO;

typedef struct
{
//	ST_BOOLEAN	bHasEnum;			//�Ƿ���ö��
	ST_INT		    numData;			//���ݸ���
	ST_CHAR	    Desc[NAMESIZE];	//����

	LD_LOG_INFO *LogInfo;
}LD_JOURNAL_CTRLS;

//
//////////////////////////////////////////////////////////////////////////

/*���ݱ仯ԭ��*/
enum UPDATA_REASON
{
	UPDATA_REASON_NULL,       /**< resvr    */
	UPDATA_REASON_DCHG,      /**< Data Change */
	UPDATA_REASON_QCHG,      /**< Quality Change*/
	UPDATA_REASON_DUPD,      /**< Data Updata */
	UPDATA_REASON_INTGPD,    /**< priority */
	UPDATA_REASON_GI        /**< GI     */
};

/*����ֵ������*/
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

	ST_UINT16	  q;        /*���ݵ�Ʒ��λ-��Ӧ����������ΪBVstring13*/

	ST_CHAR valUtf8[256];   /**< ֵΪUTF8�ַ�������ʱ��ָ���ַ���ָ�� */
	struct
	{
		ST_UINT8	q;			/**< ʱ���Ʒ�� */
		ST_UINT16	ms;			/**< ����Я���ĺ�����Ϣ���Ѿ�ת����ֱ��ʹ�ã�С��1�� */
		ST_UINT32	secs;		/**< UTCʱ�䣬��1970-01-01���������� */
	} t;
	ST_CHAR   strTime[50];	//ʱ���ַ�����ʽ��һ�������ָ�ʽ
}_DAT_UNIONOO;

/*�ڵ�����*/
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

/*����ֵ����*/
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
	ST_CHAR   DataType[16];	//INT, BOOL ��
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
	ST_INT			numDaSet;		//���ݼ�����

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
	ST_UINT16   nTmRcvMs;//zhouhj 20200113�������ڵ�ǰ���Ľ���ʱ��ĺ����ֵ
	ST_INT      nTimeGapMs;
	ST_CHAR     EntryID[8];//zhouhj �������ڴ���EntryID

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
	ST_BOOLEAN readfailed;     //��ȡʧ�ܱ��λ  
	ST_INT nType;  //0=file  1=dir ,���ݹ������һ���ַ�Ϊ��\�����ߡ�/������Ŀ¼
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
	tagDA   oDataModel;	//����ģ��
#else
	tagDA   oDataModel;	//����ģ��
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

	//����ѭ������
	ST_INT		nReportBeginIndex;
	//ST_INT		nReportEndIndex;
	ST_INT		nCurrReportIndex;
	ST_INT		nCurrReportCount;
	tagRpt	    Reports[MAX_REPORT_COUNT];

	//�ⲿ��Ϣ����
	ST_ULONG  hMsgWnd;
	ST_ULONG  nMsg;
	ST_ULONG  hSysMsgWnd;
	ST_ULONG  nSysMsg;

	ST_INT   nSGNum;   //��ֵ���ĸ���
// 	ST_INT   nCurrSGIndex;  //��ǰ���ж�ֵ��
	ST_ULONG  hRptMsgWnd;
	ST_ULONG  nRptMsg;

	ST_CHAR devName[NAMESIZE];

	ST_INT   nRunSGIndex;   //��¼��ǰ���ж�ֵ�������޸Ķ�ֵʱ��ֹ�л�������
	ST_INT   nEditSGIndex;   //2022-12-30  lijunqing  for cms
	ST_INT   nSetRunSGIndexState;   //�Ƿ������õ�ǰ��������״̬��
	ST_CHAR devID[NAMESIZE];   //װ�õ�ID�������ⲿϵͳ����ʱ����
	ST_INT   nHasDeviceModel;
	ST_INT   nWriteErrorCount;  //д���ݹ����г��ֵĴ���
	ST_CHAR  DeviceFilePath[250];//����豸����ģ���ļ�·��
	MMS_MEM_STRING RcdFilePath;//zhouhj 20180314 ���ڴ��¼���ļ�·��
	MMS_MEM_STRING IpAddr;
	ST_INT  LogTotalNum;//zhouhj 20180322 ���ڴ����־������

	tagDataChangeMsg DataChangeMsg; //2015-3-26���
	XMMS_FILE_SYS_OBJ       FileDir;
	MMS_ADDR_VECTOR oRpcMethods; //zhouhj 20210719 ��Ӧ��RPC���÷���   //2022-12-30  lijunqing  for cms

	ST_INT tmSel,		tmExec,		tmTotal;
	ST_INT tmSetSE,		tmSetSG;
	ST_CHAR InfoSel[NAMESIZE],  InfoExec[NAMESIZE];
	ST_CHAR InfoSetSE[NAMESIZE],InfoSetSG[NAMESIZE];
	ST_CHAR InfoWriteData[INFOR_BUFFER_WRITEDATA_LEN];
	ST_CHAR RefDaPath[NAMESIZE];   //���Ĳο���ID·��
	SYSTEMTIME tmStartExc;//zhouhj20200111 ��ʼִ����ѹ���޸ĵ�ʱ��

	//¼�����
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
	ST_CHAR     SoeRPT[MAX_SOE_RPT][120];		//IP���һ���ֽڣ�mms��������״ֵ̬��ʱ��
}tagSOEFIFO;

typedef struct
{
	ST_INT		readp;
	ST_INT      writep;
	ST_INT      numSOE;
	//IP���һ���ֽڣ�mms������������/�Ƿ���״ֵ̬���������ͣ����֣�������������ͣ����֣���ʱ��
	//�Ƿ��򱣻��¼������������������
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
extern ST_INT g_nCurErrorCode;//����ԭ����
extern ST_INT g_nCurErrorClass;//����class
extern ST_INT g_nCurErrorInforRpt;//ѹ���൥�����͵Ĵ�����ֵ

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern ST_INT	g_nCfgMaxDevNum;//�������ļ��ж�ȡ�������װ������

#endif