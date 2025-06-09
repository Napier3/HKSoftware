// StGlobalDefine.h:
//
//////////////////////////////////////////////////////////////////////


#pragma once

#define  MAX_STRECORD_CHANNELS                128
#define  MAX_STRECORD_VARIABLE_ATTR_BUFFERS   256


//采样率
#define  STRECORD_SAMPLE_RATE   4000    
extern DWORD STRECORD_DFT_CAL_LEN;

//系统用到的修正系数
extern double g_pCoefValue[MAX_STRECORD_CHANNELS];

//系统时间定义
typedef struct RtTime 
{
	WORD wYear; 
    WORD wMonth; 
    WORD wDay; 
    WORD wHour; 
    WORD wMinute; 
    WORD wSecond; 
    WORD wMilliseconds; 
	WORD wMicroseconds;
}*PRTTIME,RTTIME;

void Ep_InitCTimeByRtTime(RTTIME &rtTime, CTime &tm);
void Ep_InitEndCTimeByRtTime(RTTIME &rtTime, DWORD dwLen, CTime &tm);

inline void Ep_InitRtTimeCurrTime(RTTIME &rtTime)
{
	SYSTEMTIME  tmSys;
	GetSystemTime(&tmSys);
	rtTime.wYear = tmSys.wYear;
	rtTime.wMonth = tmSys.wMonth;
	rtTime.wDay = tmSys.wDay;
	rtTime.wHour = tmSys.wHour;
	rtTime.wMinute = tmSys.wMinute;
	rtTime.wSecond = tmSys.wSecond;
	rtTime.wMilliseconds = tmSys.wMilliseconds;
	rtTime.wMicroseconds = 0;
}

inline void Ep_InitRtTime(RTTIME &rtTime)
{
	memset(&rtTime, 0, sizeof(RTTIME));
}

typedef struct RtStartup
{
	char    pszVariableID[32];
	long    nIndex;
	char	pszAttrID[32];
	char	pszSetID[32];
	long	nStartupType;
	char    pszRemark[80];
	double	dAttrValue;
	double	dSetValue;
	__int64 n64StartUpStartPos;
	__int64 n64StartUpReturnPos;
	RTTIME	tmStart;
	RTTIME	tmReturn;
}*PRTSTARTUP, RTSTARTUP;

//Comtrade文件
typedef struct 
{
	CString strFilePath;
	CString strFileName;
	int     nFileSaveMode;//存储模式,0为保存全部数据,1为保存光标之间的数据
}COMTRADEFILE;

#define COMTRADEFILE_SAVE_MODE_ALL       0
#define COMTRADEFILE_SAVE_MODE_CURSOR    1

static DWORD g_nStartUpIndex = 0;
inline long GenerateStartupIndex()
{
	g_nStartUpIndex++;
	return g_nStartUpIndex;
}

//////////////////////////////////////////////////////////////////////////
//系统配置
//////////////////////////////////////////////////////////////////////////
//工频
extern DWORD g_nFrequencyNom;

//示波窗口    //单位ms
extern UINT  g_nOscillographTimeID;         //示波窗口时钟
extern DWORD g_dwOscillographTimeWndLong;    //窗口长度
extern DWORD g_dwOscillographRefreshTime;    //窗口刷新时间
extern DWORD g_dwOscillographMaxTime;
extern DWORD g_dwOscillographMinTime;

//参数监视    //单位ms
extern UINT  g_nParaSpyTimeID;          //参数监视时钟
extern DWORD g_dwParaSpyTimeWndLong;    //参数监视窗口长度
extern DWORD g_dwParaSpyRefreshTime;    //参数监视窗口刷新时间

//计算数据是否添加入缓存
extern BOOL g_bAddDataToBuffer;

//是使用SpyBuffer还是Record的标识
extern WORD g_wBufferState;

//采样间隔
extern long g_nSampleGap;
extern DWORD g_dwSampleRate;

//////////////////////////////////////////////////////////////////////////
//phaseid define

//通道相别定义
#define PHASEID_SINGLE   0x00000000
#define PHASEID_BINARY   0x00010000
#define PHASEID_OTHER    0x00020000
#define PHASEID_COMPLEX  0x00040000

#define MAX_VARIABLE_PHASEID_COUNT		4
#define CHAT_PHASEID_BEGIN_VAL          128
static const char g_pszVariablePhaseID[MAX_VARIABLE_PHASEID_COUNT][4] = {"A", "B", "C" , "N"/*, "AB", "BC", "CA", "ABC"*/};

inline DWORD GetPhaseID(char* pszPhaseID)
{
	DWORD dwPhaseID = 0;
	
	if ('0' <= *pszPhaseID && *pszPhaseID <= '9')
	{
		dwPhaseID = atol(pszPhaseID);
	}
	else
	{
		long nIndex = 0;
		
		for (nIndex=0; nIndex<MAX_VARIABLE_PHASEID_COUNT; nIndex++)
		{
			if (strcmp(pszPhaseID, g_pszVariablePhaseID[nIndex]) == 0)
			{
				dwPhaseID = CHAT_PHASEID_BEGIN_VAL +nIndex;
				break;
			}
		}
	}
	
	return dwPhaseID;
}

inline CString GetPhaseIDString(DWORD dwPhaseID)
{
	CString strPhaseID;
	
	dwPhaseID = dwPhaseID & 0x0000FFFF;
	
	if (dwPhaseID >= CHAT_PHASEID_BEGIN_VAL + MAX_VARIABLE_PHASEID_COUNT)
	{
		strPhaseID = "";
	}
	else
	{
		if (dwPhaseID < CHAT_PHASEID_BEGIN_VAL)
		{
			strPhaseID.Format(_T("%d"), dwPhaseID);
		}
		else
		{
			strPhaseID = g_pszVariablePhaseID[dwPhaseID - CHAT_PHASEID_BEGIN_VAL];
		}
	}
	
	return strPhaseID;
}

inline DWORD GetPhaseID(DWORD dwPhaseID)
{
	return (dwPhaseID & 0x0000FFFF);
}

inline BOOL IsSinglePhaseID(DWORD dwPhaseID)
{
	if ((dwPhaseID & 0xFFFF0000) == PHASEID_SINGLE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline BOOL IsBinaryPhaseID(DWORD dwPhaseID)
{
	if ((dwPhaseID & 0xFFFF0000) == PHASEID_BINARY)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline BOOL IsMultiPhaseID(DWORD dwPhaseID)
{
	if ((dwPhaseID & 0xFFFF0000) == PHASEID_OTHER)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

inline BOOL IsComplexPhaseID(DWORD dwPhaseID)
{
	if ((dwPhaseID & 0xFFFF0000) == PHASEID_COMPLEX)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

//保存图片
HBITMAP GethBitmap(CRect Rect);
void WriteBmpToFile(HBITMAP hBitmap, CString strRTName);

//开关量通道缓存相关函数
static const char *g_pszBinaryChannelMemID = "_Binary_";

inline void Ep_GetBinaryChannelID(UINT nBinaryID, CString &strChID)
{
	UINT nChID = nBinaryID / 16;
	strChID.Format(_T("%s%d"),g_pszBinaryChannelMemID, nChID);
}

inline BOOL Ep_IsBinaryChannelID(const CString &strChID)
{
	return (strChID.Find(CString(g_pszBinaryChannelMemID), 0) >= 0);
}

inline UINT Ep_GetBinaryChannelID(const CString &strChID)
{
	ASSERT (Ep_IsBinaryChannelID(strChID));
	CString strTemp = strChID.Mid(strlen(g_pszBinaryChannelMemID));

	if (strTemp.GetLength() > 0)
	{
		return CString_To_long(strTemp);
	}
	else
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////
//系统分析管理
#define MAX_DRAW_VARIABLE 128
#define ANALOG_DRAW_RECT_RATIO 0.8
#define BINARY_DRAW_RECT_RATIO (1 - ANALOG_DRAW_RECT_RATIO)

//绘图对象的
typedef struct DrawVarStruct
{
	long   nShow;
	double dRange;
	long   nUse;
	double dTopRatio;
	double dBottomRatio;
	long   *m_pnMinValue;
	long   *m_pnMaxValue;
}DRAWVAR,*PDRAWVAR;

//参数监视设置
typedef struct ChAttrDatasMngr
{
	short nAttrState[MAX_STRECORD_CHANNELS][MAX_STRECORD_VARIABLE_ATTR_BUFFERS];
}CHATTRDATASMNGR, *PCHATTRDATASMNGR;


typedef struct StSysAnalyseMngr
{
	//示波窗、分析窗设置
	unsigned long     nDrawVarCount;
	DRAWVAR			  oDrawVars[MAX_DRAW_VARIABLE];
	double			  dLastTimeLen;//上次的时间长度
	CPoint            ptTrigCursor;//TrigCursor的位置
	
	//参数监视设置
	CHATTRDATASMNGR  oAttrSpy;
	
	//系统默认设置（示波窗）
	CHATTRDATASMNGR  oAttrDefault;
}StSYSANALYSEMNGR,*PStSYSANALYSEMNGR;


extern StSYSANALYSEMNGR g_oStSysAnalyseMngr;

void ClearStSysAnalyseMngr();
void InitStSysAnalyseMngr();
void ValidateStSysAnalyseMngrDrawVar(BOOL &bNeedInitPos);    //有效性验证


static const char *g_pszKeyType               = "type";
static const char *g_pszKeyType_U			  = "U";
static const char *g_pszKeyType_I             = "I";
static const char *g_pszKeyType_C             = "C";
static const char *g_pszKeyType_NONE          = "NONE";

#define  RTVARIABLE_TYPE_U    0
#define  RTVARIABLE_TYPE_I    1
#define  RTVARIABLE_TYPE_NONE 2
#define  RTVARIABLE_TYPE_C    3

inline long InitVariableType(char* pszType)
{
	long nType = RTVARIABLE_TYPE_NONE;

	if (strcmp(pszType, g_pszKeyType_U) == 0)
	{
		nType = RTVARIABLE_TYPE_U;
	}
	else if (strcmp(pszType, g_pszKeyType_I) == 0)
	{
		nType = RTVARIABLE_TYPE_I;
	}
	else if (strcmp(pszType, g_pszKeyType_NONE) == 0)
	{
		nType = RTVARIABLE_TYPE_NONE;
	}
	else if (strcmp(pszType, g_pszKeyType_C) == 0)
	{
		nType = RTVARIABLE_TYPE_C;
	}
	else
	{
		nType = RTVARIABLE_TYPE_NONE;
	}

	return nType;
}

inline CString GetStringType(long nType)
{
	CString strType = _T("");

	if (nType == RTVARIABLE_TYPE_U) 
	{
		strType = g_pszKeyType_U;
	}
	else if (nType == RTVARIABLE_TYPE_I)
	{
		strType = g_pszKeyType_I;
	}
	else if (nType == RTVARIABLE_TYPE_NONE)
	{
	}
	else if (nType == RTVARIABLE_TYPE_C)
	{
		strType = g_pszKeyType_C;
	}
	else
	{
	}

	return strType;
}

inline BOOL IsVariableTypeU(long nType)
{
	BOOL bTRUE = FALSE;
	
	if (nType == RTVARIABLE_TYPE_U)
	{
		bTRUE = TRUE;
	}
	else
	{
		
	}
	
	return bTRUE;
}

inline BOOL IsVariableTypeI(long nType)
{
	BOOL bTRUE = FALSE;
	
	if (nType == RTVARIABLE_TYPE_I)
	{
		bTRUE = TRUE;
	}
	else
	{
		
	}
	
	return bTRUE;
}


static const char *g_pszKeyVariableType_Empty       = "empty";
static const char *g_pszKeyVariableType_Electricity = "electricity";

#define  RTVARIABLE_TYPE_EMPTY          0
#define  RTVARIABLE_TYPE_ELECTRICITY    1

inline long InitBinaryVariableType(char *pszType)
{
	long nType = RTVARIABLE_TYPE_EMPTY;
	
	if (strcmp(pszType, g_pszKeyVariableType_Empty) == 0)
	{
		nType = RTVARIABLE_TYPE_EMPTY;
	}
	else if (strcmp(pszType, g_pszKeyVariableType_Electricity) == 0)
	{
		nType = RTVARIABLE_TYPE_ELECTRICITY;
	}
	else
	{
		nType = RTVARIABLE_TYPE_NONE;
	}
	
	return nType;
}

inline CString GetBinaryStringType(long nType)
{
	CString strType = _T("");

	if (nType == RTVARIABLE_TYPE_EMPTY)
	{
		strType = g_pszKeyVariableType_Empty;
	}
	else if (nType == RTVARIABLE_TYPE_ELECTRICITY)
	{
		strType = g_pszKeyVariableType_Electricity;
	}
	else
	{

	}
	return strType;
}

#define END_FREQ_NONE 0
#define END_FREQ_1800 1
#define END_FREQ_300  2
#define END_FREQ_50   3

long ChangeBinaryDataToAlgorism(CString strData);
extern long sgc_unSampleGap[9];

#define WM_RECORD_TIMER_DRAW					(WM_USER + 89)
#define WM_DRAW									(WM_USER + 90)
#define WM_INVALIDATE_RANGESTATEAXIS		    (WM_USER + 91)
#define WM_VARIABLE_SIZE_CHANGED				(WM_USER + 92)
#define WM_VARIABLE_POS_CHANGED					(WM_USER + 93)
#define WM_VARIABLE_SELECT_CHANGED				(WM_USER + 94)
#define WM_TIMEAXIS_CHANGED						(WM_USER + 95)
#define WM_TIMECURSOR_POS_CHANGE				(WM_USER + 96)
#define WM_TIMECURSOR_SELECT_CHANGE				(WM_USER + 97)
#define WM_TIME_CHANGED							(WM_USER + 98)
#define WM_VARIABLE_ADD_REMOVE					(WM_USER + 99)


#define WM_FINISH_RECORD						(WM_USER + 1010)
#define WM_START_RECORD							(WM_USER + 1011)	
#define WM_DRAW_VARIABLESEL						(WM_USER + 1012)
#define WM_SAVECOMTRADEFILE						(WM_USER + 1013)
#define WM_READCOMTRADEFILE						(WM_USER + 1014)
#define WM_SETVARIABLEAXISRANGE					(WM_USER + 1015)
#define WM_EXITINSTANCE							(WM_USER + 1016)
#define WM_UPDATEWNDSHOWBYSET					(WM_USER + 10000)//根据定值信息修改各个窗口

//UIWndOscillograph
#define WM_OSCIL_SETVARIABLEAXISRANGEANDSHOW	(WM_USER + 9002)

//示波/分析时显示设置的结构体信息
typedef struct VARIABLESHOWANDRANGE
{
	long nVariableIndex;
	double dRange;
	long nShowSet;
}VAR_SHOW_RANGE, *PVAR_SHOW_RANGE;

#define SET_VARIABLE_SHOW    0
#define SET_VARIABLE_RANGE   1

#define ZERO_VALUE     0.0001

#define _SHOW_PARA
