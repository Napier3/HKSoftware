// RecordGlobalDefine.h:
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RecordGlobalDefine_h__)
#define _RecordGlobalDefine_h__

#include "../API/StringApi.h"

//xupf
// #ifdef _PSX_IDE_QT_
// #include<string.h>
// #define _stricmp strcasecmp
// #endif


#define CMTRDCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00450000)
#define CMTRDCLASSID_LISTCLASS       (CLASSID_LISTCLASS +  0X00450000)

#define CMTRDCLASSID_ANALOG           (CMTRDCLASSID_BASECLASS + 0X00000000)
#define CMTRDCLASSID_BINARY          (CMTRDCLASSID_BASECLASS + 0X00000001)
#define CMTRDCLASSID_CHANNELS           (CMTRDCLASSID_BASECLASS + 0X00000002)
#define CMTRDCLASSID_COMTRADE           (CMTRDCLASSID_BASECLASS + 0X00000003)
// #define CMTRDCLASSID_RANGESTATEAXIS           (CMTRDCLASSID_BASECLASS + 0X00000004)

#define CMTRDCLASSID_BINARYVARIABLE			CMTRDCLASSID_BASECLASS + 0x00000011	//��������
#define CMTRDCLASSID_ANALOGVARIABLE			CMTRDCLASSID_BASECLASS + 0x00000012	//ģ������
#define CMTRDCLASSID_TIMEAXIS				CMTRDCLASSID_BASECLASS + 0x00000013	//ʱ������
#define CMTRDCLASSID_TIMECURSOR				CMTRDCLASSID_BASECLASS + 0x00000014	//ʱ������
#define CMTRDCLASSID_TRIGCURSOR				CMTRDCLASSID_BASECLASS + 0x00000015	//���������
#define CMTRDCLASSID_VARIABLESMNGR			CMTRDCLASSID_LISTCLASS   + 0x00000016	//ͨ��������
#define CMTRDCLASSID_BINARYVARIABLEGROUP     CMTRDCLASSID_LISTCLASS   + 0x00000017	//������Ⱥ������
#define CMTRDCLASSID_ATTRSPYVARIABLE			CMTRDCLASSID_BASECLASS + 0x00000018	//���Լ�������
#define CMTRDCLASSID_RANGESTATEAXIS			CMTRDCLASSID_BASECLASS + 0x00000019	//
#define CMTRDCLASSID_COMPLEXVARIABLE			CMTRDCLASSID_BASECLASS + 0x0000001A	//ģ����������

#define CMTRDCLASSID_WNDWAVEANALYSE			CMTRDCLASSID_LISTCLASS + 0x0000001B
#define CMTRDCLASSID_CMPANALOGVARIABLE			CMTRDCLASSID_BASECLASS + 0x0000001C

//########################################################################
//��������
//########################################################################
//��Ƶ
extern DWORD g_nFrequencyNom;
//�������
// extern unsigned short g_nSampleGap;
// extern DWORD g_dwSampleRate;

//########################################################################
//RecordTest���ܲ���
//########################################################################
#define  MAX_MR1200_CHANNELS                4096
#define  MAX_RTVARIABLES                       4096
#define  MAX_MR1200_VARIABLE_ATTR_BUFFERS   256

//ͨ�������
#define PHASEID_SINGLE   0x00000000
#define PHASEID_BINARY   0x00010000
#define PHASEID_OTHER    0x00020000
#define PHASEID_COMPLEX  0x00040000

#define MAX_VARIABLE_PHASEID_COUNT		4
#define CHAT_PHASEID_BEGIN_VAL          128
static const char g_pszVariablePhaseID[MAX_VARIABLE_PHASEID_COUNT][4] = {"A", "B", "C" , "N"/*, "AB", "BC", "CA", "ABC"*/};

inline DWORD GetPhaseID(const char *pszPhaseID)
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
			if (_stricmp(pszPhaseID, g_pszVariablePhaseID[nIndex]) == 0)
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
		strPhaseID = _T("");
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

inline COLORREF GetPhaseColorByPhaseID(const char* strPhID)
{
	COLORREF crColor = RGB(0,0,255);

	if (_stricmp(strPhID , g_pszVariablePhaseID[0]) == 0)
	{
		crColor = RGB(255,255,0);
	}
	else if (_stricmp(strPhID , g_pszVariablePhaseID[1]) == 0)
	{
		crColor = RGB(0,255,0);
	}
	else if (_stricmp(strPhID , g_pszVariablePhaseID[2]) == 0)
	{
		crColor = RGB(255,0,0);
	}
	else
	{
		crColor = RGB(0,0,255);
	}

	return crColor;
}

inline COLORREF GetPhaseColorByPhaseID(const CString &strPhID)
{
	char pszPhID[32];
	CString_to_char(strPhID, pszPhID);
	return GetPhaseColorByPhaseID(pszPhID);
}

inline COLORREF GetPhaseColorByPhaseID(CString &strPhID, const CString &strChID)
{
	COLORREF crColor = RGB(0,0,255);

	if (strPhID.GetLength() > 0)
	{
		crColor = GetPhaseColorByPhaseID(strPhID);
	}
	else
	{
		if (strChID.GetLength() > 0)
		{
			long nIndex = CString_To_long(strChID.Right(1));
			nIndex = nIndex % 4;
			crColor = GetPhaseColorByPhaseID(g_pszVariablePhaseID[nIndex]);
		}
		else
		{
		}
	}

	return crColor;
}

//������ͨ��������غ���
static const char *g_pszBinaryChannelMemID = "_Binary_";

inline void rcd_GetBinaryChannelID(UINT nBinaryID, CString &strChID)
{
	UINT nChID = nBinaryID / 16;
	strChID.Format(_T("%s%d"),g_pszBinaryChannelMemID, nChID);
}

inline BOOL rcd_IsBinaryChannelID(const CString &strChID)
{
	return (strChID.Find(CString(g_pszBinaryChannelMemID), 0) >= 0);
}

inline UINT rcd_GetBinaryChannelID(const CString &strChID)
{
	ASSERT (rcd_IsBinaryChannelID(strChID));
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

static const char *g_pszKeyVariableACDC       = "ACDC";
static const char *g_pszKeyVariableAC		  = "AC";
static const char *g_pszKeyVariableDC         = "DC";

#define  RTVARIABLE_ACDC     0
#define  RTVARIABLE_AC		 1
#define  RTVARIABLE_DC		 2

#define  RTVARIABLE_TYPE_U    0
#define  RTVARIABLE_TYPE_I    1
#define  RTVARIABLE_TYPE_NONE 2
#define  RTVARIABLE_TYPE_C    3

inline long InitVariableACDC(const char *pszACDC)
{
	long nACDC;
	
	if (_stricmp(pszACDC, g_pszKeyVariableACDC) == 0)
	{
		nACDC = RTVARIABLE_ACDC;
	}
	else if (_stricmp(pszACDC, g_pszKeyVariableAC) == 0)
	{
		nACDC = RTVARIABLE_AC;
	}
	else if (_stricmp(pszACDC, g_pszKeyVariableDC) == 0)
	{
		nACDC = RTVARIABLE_DC;
	}
	else
	{
	}
	
	return nACDC;
}


static const char *g_pszKeyVariableType_Empty       = "empty";
static const char *g_pszKeyVariableType_Electricity = "electricity";

#define  RTVARIABLE_TYPE_EMPTY          0
#define  RTVARIABLE_TYPE_ELECTRICITY    1

inline long InitBinaryVariableType(const char *pszType)
{
	long nType = RTVARIABLE_TYPE_EMPTY;
	
	if (_stricmp(pszType, g_pszKeyVariableType_Empty) == 0)
	{
		nType = RTVARIABLE_TYPE_EMPTY;
	}
	else if (_stricmp(pszType, g_pszKeyVariableType_Electricity) == 0)
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
	CString strType;
	
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

static const char *g_pszKeyType               = "type";
static const char *g_pszKeyType_U			  = "U";
static const char *g_pszKeyType_I             = "I";
static const char *g_pszKeyType_C             = "C";
static const char *g_pszKeyType_NONE          = "NONE";


inline long RT_GetUibVariableType(const char *pszType)
{
	long nType = RTVARIABLE_TYPE_NONE;
	
	if (_stricmp(pszType, g_pszKeyType_U) == 0)
	{
		nType = RTVARIABLE_TYPE_U;
	}
	else if (_stricmp(pszType, g_pszKeyType_I) == 0)
	{
		nType = RTVARIABLE_TYPE_I;
	}
	else if (_stricmp(pszType, g_pszKeyType_NONE) == 0)
	{
		nType = RTVARIABLE_TYPE_NONE;
	}
	else if (_stricmp(pszType, g_pszKeyType_C) == 0)
	{
		nType = RTVARIABLE_TYPE_C;
	}
	else
	{
		nType = RTVARIABLE_TYPE_NONE;
	}
	
	return nType;
}

inline CString RT_GetStringUIBType(long nType)
{
	CString strType;
	
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

inline BOOL RT_IsVariableTypeU(long nType)
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

inline BOOL RT_IsVariableTypeI(long nType)
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


//########################################################################
//���沿��
//########################################################################
static const char* g_pszOscillographTimeID = "oscillograph_timeid";
static const char* g_pszParaSpyTimeID      = "paraspy_timeid";

//ʾ������    //��λms
extern UINT  g_nOscillographTimeID;         //ʾ������ʱ��
extern DWORD g_dwOscillographTimeWndLong;    //���ڳ���
extern DWORD g_dwOscillographRefreshTime;    //����ˢ��ʱ��
extern DWORD g_dwOscillographMaxTime;
extern DWORD g_dwOscillographMinTime;

extern BOOL g_bCanFireOscillgraphTimerOptr;

//��������    //��λms
extern UINT  g_nParaSpyTimeID;          //��������ʱ��
extern DWORD g_dwParaSpyTimeWndLong;    //�������Ӵ��ڳ���
extern DWORD g_dwParaSpyRefreshTime;    //�������Ӵ���ˢ��ʱ��

#define MAX_DRAW_VARIABLE 64
#define ANALOG_DRAW_RECT_RATIO 0.8
#define BINARY_DRAW_RECT_RATIO (1 - ANALOG_DRAW_RECT_RATIO)

//��ͼ�����
#define  RECORDDRAW_OBJECT_GAP      2     //��ͼ����֮��ļ��
#define  RECORDDRAW_TOPBOTTOM_GAP   4     //��ͼ�������ͼ���򶥲����ײ��ļ��
#define  RECORDDRAW_ANALOG_MINHEIGHT  50
#define  RECORDDRAW_BINARY_HEIGHT     12
#define  RECORDDRAW_BINARY_HIGH     2
#define  ANALOG_BINARY_HEIGHT_RATE   4

typedef struct structRecordDrawObjectContrl
{
	long   nShow;
	double dRange;     //ͨ����ͼ��������ֵ
	long   nUse;
	double dCenter;    //�������λ��
	double dRangeGrid; //ͨ�������ֵ
	
	//	UINT   nType; //��Ӧ���ǿ��صĻ���ģ���0-ģ�⣬1-����
}RECORDDRAWOBJECTCONTROL,*PRECORDDRAWOBJECTCONTROL;

//////////////////////////////////////////////////////////////////////////
//г����״ͼ����
#define MAX_HARM_INDEX  25
typedef struct HarmHistogram 
{
	long  nChIndex;
	BOOL  bHarmShow[100];  //���100��г��
	BOOL  bAxisFixed;
	double dMaxHarmValue;
}HARMHISTOGRAM, *PHARMHISTOGRAM;

inline void InitHarmHistogram(HARMHISTOGRAM &oHarmHisto)
{
	memset(&oHarmHisto, 0, sizeof(HARMHISTOGRAM));
	
	BOOL *p = oHarmHisto.bHarmShow;
	BOOL *pEnd = p + MAX_HARM_INDEX;
	
	while (p < pEnd)
	{
		*p=TRUE;
		p++;
	}
}

//������������
typedef struct ChAttrDatasMngr
{
	short nAttrState[MAX_MR1200_CHANNELS][MAX_MR1200_VARIABLE_ATTR_BUFFERS];
}CHATTRDATASMNGR, *PCHATTRDATASMNGR;

//������ʽ�ĺ궨��
#define TRIGMODE_NOMAL   0
#define TRIGMODE_SINGLE  1

typedef struct MR1200SysAnalyseMngr
{
	//ʾ����������������
	unsigned long     nCurrDrawObjectCount;
	RECORDDRAWOBJECTCONTROL	  oDrawControl[MAX_DRAW_VARIABLE];
	double			  dLastTimeLen;//�ϴε�ʱ�䳤��
	CPoint            ptTrigCursor;//TrigCursor��λ��
	BOOL			  bShowMidLine;//��ʾ�����ߣ�0-����ʾ�� 1-��ʾ
	
	//г����������
	HARMHISTOGRAM     oHarmHistogram;    //г����������
	
	//������������
	CHATTRDATASMNGR  oAttrSpy;
	
	//ϵͳĬ�����ã�ʾ������
	CHATTRDATASMNGR  oAttrDefault;
	
	char szTrigVariable[20];//����ͨ������
	unsigned short nTrigMode;//������ʽ��0-���������� 1-���δ���
	double dTrigElectricValue;//������ƽ
	char szRefVariable[20];//�ο�ͨ������
}MR1200SYSANALYSEMNGR,*PMR1200SYSANALYSEMNGR;


// void ClearMR1200SysAnalyseMngr(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
void InitMR1200SysAnalyseMngr(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr);
BOOL ValidateMR1200SysAnalyseMngrDrawControl();    //��Ч����֤
void InitMR1200SysAnalyseMngrDrawControl(MR1200SYSANALYSEMNGR &oMR1200SysAnalyseMngr, long nAnalogs, long nBinarys);
void InitSysAnalyseMngrDrawControl(PRECORDDRAWOBJECTCONTROL pDrawControl, long nAnalogs, long nBinarys);

BOOL ReadMR1200SysAnalyseMngrFromFile(LPCTSTR pszFile);
BOOL WriteMR1200SysAnalyseMngrFromFile(LPCTSTR pszFile);

typedef enum eSystemInforType
{
	SIT_NONE					=0x00000000
	, SIT_DELTAT				=0x00000001
	, SIT_DELTAPH				=0x00000002
	, SIT_RECORDBEGINTIME		=0x00000004//¼����ʼʱ��
	, SIT_SAMPLERATE			=0x00000008//������
	, SIT_T1TIME				=0x00000010
	, SIT_T2TIME				=0x00000020
	, SIT_RECORDDRAWBEGINTIME	=0x00000040
	, SIT_MAXRECORDTIMELENGTH	=0x00000080
	, SIT_CURRRECORDTIMELENGTH	=0x00000100
	, SIT_ONLINERECORDSAVEMODE	=0x00000200
	, SIT_ONLINERECORDFILE		=0x00000400
	, SIT_COMTRADEFILE			=0x00000800
	, SIT_SYSTRACEINFOR			=0x00001000
	, SIT_SYSERRORINFOR			=0x00002000
	, SIT_FILE_NAME				=0x00004000//�ļ�����
	, SIT_FILE_SIZE				=0x00008000//�ļ���С
	, SIT_FILE_CREATETIME		=0x00010000//�ļ�����ʱ��
	, SIT_FILE_TESTTYPE			=0x00020000//�ļ���������
	, SIT_RECORDSTARTUPTIME		=0x00040000//¼��������ʱ��
	, SIT_RECORDTIMELONG		=0x00080000//¼��ʱ�䳤��
	, SIT_TESTBEGINTIME         =0x00100000//������ʼʱ��
	, SIT_TESTENDTIME			=0x00200000//�������ʱ��
	, SIT_TRIGVARIABLE          =0x00400000//����ͨ��,fdp add 2010.10.11
	, SIT_TRIGELECTRICVALUE     =0x00800000//������ƽ,fdp add 2010.10.11
	, SIT_ONLINEDATAAREABEGINTIME     =0x01000000//Online��ȡ�����ݶ����ʱ��
	, SIT_RECORDENDTIME			=0x02000000//¼������ʱ��
}ESYSTEMINFORTYPE;


#define TRACE_SYSINFOR_BUFFER_LENGTH   2048

//////////////////////////////////////////////////////////////////////////
//ϵͳ��������


//########################################################################
//ϵͳʱ�ӹ���ϵͳ��������
//########################################################################
//ϵͳʱ�䶨��
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

inline BOOL RtTimeSscanf(RTTIME &oTm, const char* pszTime)
{
	memset(&oTm, 0, sizeof(RTTIME));
	sscanf(pszTime, "%d-%d-%d %d:%d:%d %d", &oTm.wYear, &oTm.wMonth, &oTm.wDay, &oTm.wHour, &oTm.wMinute, &oTm.wSecond, &oTm.wMilliseconds);
	return TRUE;
}

void rcd_InitCTimeByRtTime(RTTIME &rtTime, CTime &tm);

inline void rcd_InitRtTime(RTTIME &rtTime, SYSTEMTIME &tmSys)
{
	rtTime.wYear = tmSys.wYear;
	rtTime.wMonth = tmSys.wMonth;
	rtTime.wDay = tmSys.wDay;
	rtTime.wHour = tmSys.wHour;
	rtTime.wMinute = tmSys.wMinute;
	rtTime.wSecond = tmSys.wSecond;
	rtTime.wMilliseconds = tmSys.wMilliseconds;
	rtTime.wMicroseconds = 0;
}

void rcd_InitEndCTimeByRtTime(RTTIME &rtTime, DWORD dwLen, CTime &tm);

inline void rcd_InitRtTimeCurrTime(RTTIME &rtTime)
{
	SYSTEMTIME  tmSys;
	::GetLocalTime(&tmSys);
	rcd_InitRtTime(rtTime, tmSys);
}

inline void rcd_InitRtTime(RTTIME &rtTime)
{
	memset(&rtTime, 0, sizeof(RTTIME));
}

static const char *g_pszSysOptrFinishRecord         = "SysOptr_FinishRecord";
static const char *g_pszSysOptrStartRecord          = "SysOptr_StartRecord";
static const char* g_pszSystemOptrID_TimerCurrsorMove = "sysoptr_timer_currsor_move";
static const char* g_pszSystemOptrID_OpenComtradeFile = "sysoptr_timer_open_comtrade_file";
static const char* g_pszSystemOptrID_OpenSetFile      = "sysoptr_timer_open_set_file";

//########################################################################
//¼�����������ʵʱ����
//########################################################################
//������ID
static const char* g_pszGPSBufferID        = "_GPS_SPY";
static const char* g_pszGPSChannelID       = "_GPS_";
static const char* g_pszAttrTimeBufferID   = "_Attr_Time_Buffer_";

extern BOOL g_bCarry_For_AttrCalUsePoints;


//��ͨ������������FIFO�е�λ��
extern unsigned short g_pChannelFIFOIndex[MAX_MR1200_CHANNELS];

//һ��FIFO�Ĵ�С
extern UINT g_nFIFOUnitSize;

//�������
// extern unsigned short g_nSampleGap;
// extern DWORD g_dwSampleRate;

//���������Ƿ�����뻺��
extern BOOL g_bAddDataToBuffer;
//extern BOOL g_bCalUseRecordBuffer;

//��ʹ��SpyBuffer����Record�ı�ʶ
extern WORD g_wBufferState;

//У׼ʱ������Ϣ��У׼����\����
#define ADJUST_CAL     0
#define ADJUST_SAVE	   1
extern BOOL g_bInAdjustingZeroCalState; //�Ƿ���У׼״̬�����������ϵ��ʹ��

//ADStart��״̬
#define ADSART_SCCUSESS			0//��ʾAD��ʼ�ɹ���
#define ADSART_SIZEINVALIDATE	1//��ʾ������¼���ݿռ䲻���� 
#define ADSART_HASDATA			2//��ʾ������¼�������Ѿ������ݣ�

#define END_FREQ_NONE 0
#define END_FREQ_1800 1
#define END_FREQ_300  2
#define END_FREQ_50   3

////MrOnlineRecordEx����ģʽ
#define MRONLINE_RECORDEX_MODE_OSCILLOGRAPH    0  
#define MRONLINE_RECORDEX_MODE_COMTRADE        1
#define MRONLINE_RECORDEX_MODE_ONLINERECORD    2


//Comtrade�ļ�
typedef struct 
{
	char strFilePath[MAX_PATH];
	char strFileName[MAX_PATH];
	int  nFileSaveMode;//�洢ģʽ,0Ϊ����ȫ������,1Ϊ������֮�������

	//�ļ���С(byte)
	DWORD dwFileSize;

	//ʵ��¼��ʱ�䳤��(s)
	long nRealRecordTime;	
}COMTRADEFILE;

#define COMTRADEFILE_SAVE_MODE_ALL       0
#define COMTRADEFILE_SAVE_MODE_CURSOR    1

//¼���ļ����·������
#define MAX_RECORD_FILE_PATHS  8
extern char  g_pszRecordFilePaths[MAX_RECORD_FILE_PATHS][MAX_PATH];

//zhouhj 2024.9.12 ȥ��ԭnot_use_FreqCalFix50Hz��,��ֵС��1ʱ,����ʵʱ��ȡƵ�ʵķ�ʽ,�����ô˷�ʽ,�������з�ֵ����ʱ,�ᶪʧ���־���,���ù̶�Ƶ�ʼ���ķ�ʽ,����㾫�ȸ���
//��ֵȱʡΪ50Hz�����ݲ�ͬ��Ӧ�ó���,�ɸ��������Զ����øù̶�Ƶ�ʼ���ʱ��Ƶ��ֵ
extern double g_dFixFreqCalValue;

//�ļ����
//��������/�ļ���׺��
static const char *g_pRtTestFileType_oscillograph = "oscillograph";
static const char *g_pRtTestFileType_online = "online";
static const char *g_pRtTestFileType_gsht = "gsht";
static const char *g_pRtTestFileType_gopn = "gopn";
static const char *g_pRtTestFileType_gexc_online = "gexc-online";
static const char *g_pRtTestFileType_gsyn_online = "gsyn-online";
static const char *g_pRtTestFileType_gstp_online = "gstp-online";
static const char *g_pRtTestFileType_mrtt  = "mrtt";

//Ӳ���任��λ�úͱ任���е�ͨ��λ�õ���Ϣ
typedef struct
{
	char m_strDCAC[6];
	double m_dRange;
	char strTranModel[20];
	long nTranIndex;//�任����λ������
	long nTranChIndex;//�任���е�ͨ��λ������
	long nTranFirstChannelHdIndex; //���任����һ��ͨ��������ͨ���е�����λ��
	long nVoltageTranindex;//��ѹ�任���е�����
	long nCurrentTranindex;//�����任���е�����
	long nTranAnologChCount;//ģ��任����ͨ������
	long nTranAnologCount;//ģ��任��������
	long nTranBinaryChCount;//���ر任����ͨ������
	long nTranBinaryCount;//���ر任��������
	BOOL bDCTran;//ͨ�����ڵı任���Ƿ���ֱ���任��
	long nDCUIChIndexInTran;//ֱ���任���ĵ�������ѹ��ͨ����ֱ���任���е�λ��
	//BOOL bMaxSigleVariable;//��ͨ�������Ƿ�ﵽ���12��
}HDINFO;

// extern long USE_RT_FILTER_BUFFER_LEN;//   81
// extern long RT_FILTER_DATA_LEN_PREV;// 40
// extern long RT_FILTER_DATA_LEN_NEXT;// 40
// extern long RTATTRIBUTECAL_MIN_BUFFER_LEN;

typedef struct record_cal_len_para
{
	unsigned short g_nSampleGap;
	DWORD g_dwSampleRate;

	long Analyse_Cal_Length;// = 2000;

	long USE_RT_FILTER_BUFFER_LEN;// =  81;
	long RT_FILTER_DATA_LEN_PREV;// = 40;
	long RT_FILTER_DATA_LEN_NEXT;// = 40;
	long RTATTRIBUTECAL_MIN_BUFFER_LEN;//   =    (7000+RT_FILTER_BUFFER_LEN); //20000
}RECORD_CAL_LEN_PARA, *PRECORD_CAL_LEN_PARA;


DWORD rcd_CalCyclePoints(DWORD dwSampRate, double dFreq);
DWORD rcd_CalCyclePoints(DWORD dwSampRate, double dFreq, bool bCarry);
DWORD rcd_CalCyclePoints(double dCyclePoints, bool bCarry);

//2021-1-16   lijunqing
#define XRCD_ANALYSIS_DRAW_FILE_POSTFIX    _T("rcdrw")

#endif // !defined(_RecordGlobalDefine_h__)
