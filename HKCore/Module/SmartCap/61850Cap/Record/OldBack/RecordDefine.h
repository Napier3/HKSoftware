// RecordTestClassDef.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RECORDDEFINE_H__)
#define _RECORDDEFINE_H__

#include "RecordDefine.h"
#include "RecordGlobalDefine.h"

#define RTCLASSID_COMPLEXVARIABLE      (CLASSID_LISTCLASS + 0x00000006)	//组合通道对象ID
#define RTCLASSID_SINGLEVARIABLE       (CLASSID_LISTCLASS + 0x00000007)	//单通道对象ID
#define RTCLASSID_BINARYVARIABLE       (CLASSID_LISTCLASS + 0x00000008)	//开关通道对象ID
#define RTCLASSID_MULTIVARIABLE        (CLASSID_LISTCLASS + 0x00000009)	//复合通道对象ID
#define RTCLASSID_VARIABLE             (CLASSID_LISTCLASS + 0x0000000A)	//通道基类对象ID
#define RTCLASSID_VARIABLES            (CLASSID_LISTCLASS + 0x0000000B)	//通道集合对象ID
#define RTCLASSID_STARTUP              (CLASSID_LISTCLASS + 0x0000000C)	//启动对象ID
#define RTCLASSID_MEMBUFFER            (CLASSID_LISTCLASS + 0x0000000D)	//缓存对象ID
#define RTCLASSID_RECORDTEST           (CLASSID_LISTCLASS + 0x0000000E)	//试验对象ID
#define RTCLASSID_RECORDTESTS          (CLASSID_LISTCLASS + 0x0000000F)	//试验集合对象ID

#define RTCLASSID_SET                  (CLASSID_BASECLASS + 0x00000001)     //定值类
#define RTCLASSID_CHANNEL              (CLASSID_BASECLASS + 0x00000002)     //通道类
#define RTCLASSID_SETS                 (CLASSID_LISTCLASS + 0x00000001)   //定值集合类
#define RTCLASSID_CHANNELS             (CLASSID_LISTCLASS + 0x00000002)   //通道集合类
#define RTCLASSID_DATAATTRIBUTE        (CLASSID_LISTCLASS + 0x00000003)   //数据类
#define RTCLASSID_DATAATTRIBUTES       (CLASSID_LISTCLASS + 0x00000004)     //数据集合类
#define RTCLASSID_ATTRBUFFER           (CLASSID_BASECLASS + 0x00000010)     //属性缓冲区
#define RTCLASSID_ALLOCBUFFER          (CLASSID_LISTCLASS + 0x00000011)   //内存分配

#define RTCLASSID_FILEWRITE            (CLASSID_LISTCLASS + 0x00000012)   //文件写管理对象
#define RTCLASSID_FILEFORMAT           (CLASSID_LISTCLASS + 0x00000013)   //文件写格式定义
#define RTCLASSID_FILEFORMAT_BUFFER    (CLASSID_BASECLASS + 0x00000014)     //文件格式-缓冲区
#define RTCLASSID_SPY                  (CLASSID_BASECLASS + 0x00000015)     //监视

//config
#define RTCLASSID_APPMODEL             (CLASSID_BASECLASS + 0x00000016)     //应用种类
#define RTCLASSID_APPMODELS            (CLASSID_LISTCLASS + 0x00000017)     //应用种类管理
#define RTCLASSID_CFGVARIABLE          (CLASSID_BASECLASS + 0x00000018)	    //通道基类对象ID
#define RTCLASSID_CFGVARIABLES         (CLASSID_LISTCLASS + 0x00000019)	//通道集合对象ID
#define RTCLASSID_CFGRECORDTEST        (CLASSID_LISTCLASS + 0x0000001A)	//试验对象ID
#define RTCLASSID_CFGRECORDTESTS       (CLASSID_LISTCLASS + 0x0000001B)	//试验集合对象ID
#define RTCLASSID_CFGRECORDTESTTYPES   (CLASSID_LISTCLASS + 0x0000001C)	//试验类型集合ID
#define RTCLASSID_CFGRECORDTESTTYPE    (CLASSID_LISTCLASS + 0x0000001D)	//试验集合对象ID

//监视属性
#define RTCLASSID_ATTRSPYCONFIGS	   (CLASSID_LISTCLASS + 0x0000001E)	//监视属性集合ID
#define RTCLASSID_ATTRSPYCONFIG		   (CLASSID_LISTCLASS + 0x0000001F)	//监视属性ID


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//通道计算值
#define  SingleVariableAttrID_Frequancy                      0
#define  SingleVariableAttrID_EffecValue                     1
#define  SingleVariableAttrID_EffecPhase                     2
#define  SingleVariableAttrID_FundValue                      3
#define  SingleVariableAttrID_FundPhase                      4
#define  SingleVariableAttrID_PeakValue                      5
#define  SingleVariableAttrID_VellayValue                    6
#define  SingleVariableAttrID_InstValue                      7
#define  SingleVariableAttrID_AverageValue                   8
#define  SingleVariableAttrID_Harm02Value                    9
#define  SingleVariableAttrID_Harm03Value                    10
#define  SingleVariableAttrID_Harm04Value                    11
#define  SingleVariableAttrID_Harm05Value                    12
#define  SingleVariableAttrID_Harm06Value                    13
#define  SingleVariableAttrID_Harm07Value                    14
#define  SingleVariableAttrID_Harm08Value                    15
#define  SingleVariableAttrID_Harm09Value                    16
#define  SingleVariableAttrID_Harm10Value                    17
#define  SingleVariableAttrID_Harm11Value                    18
#define  SingleVariableAttrID_Harm12Value                    19
#define  SingleVariableAttrID_Harm13Value                    20
#define  SingleVariableAttrID_Harm14Value                    21
#define  SingleVariableAttrID_Harm15Value                    22
#define  SingleVariableAttrID_Harm16Value                    23
#define  SingleVariableAttrID_Harm17Value                    24
#define  SingleVariableAttrID_Harm18Value                    25
#define  SingleVariableAttrID_Harm19Value                    26
#define  SingleVariableAttrID_Harm20Value                    27
#define  SingleVariableAttrID_Harm21Value                    28
#define  SingleVariableAttrID_Harm22Value                    29
#define  SingleVariableAttrID_Harm23Value                    30
#define  SingleVariableAttrID_Harm24Value                    31
#define  SingleVariableAttrID_Harm25Value                    32
#define  SingleVariableAttrID_Harm02Phase                    33
#define  SingleVariableAttrID_Harm03Phase                    34
#define  SingleVariableAttrID_Harm04Phase                    35
#define  SingleVariableAttrID_Harm05Phase                    36
#define  SingleVariableAttrID_Harm06Phase                    37
#define  SingleVariableAttrID_Harm07Phase                    38
#define  SingleVariableAttrID_Harm08Phase                    39
#define  SingleVariableAttrID_Harm09Phase                    40
#define  SingleVariableAttrID_Harm10Phase                    41
#define  SingleVariableAttrID_Harm11Phase                    42
#define  SingleVariableAttrID_Harm12Phase                    43
#define  SingleVariableAttrID_Harm13Phase                    44
#define  SingleVariableAttrID_Harm14Phase                    45
#define  SingleVariableAttrID_Harm15Phase                    46
#define  SingleVariableAttrID_Harm16Phase                    47
#define  SingleVariableAttrID_Harm17Phase                    48
#define  SingleVariableAttrID_Harm18Phase                    49
#define  SingleVariableAttrID_Harm19Phase                    50
#define  SingleVariableAttrID_Harm20Phase                    51
#define  SingleVariableAttrID_Harm21Phase                    52
#define  SingleVariableAttrID_Harm22Phase                    53
#define  SingleVariableAttrID_Harm23Phase                    54
#define  SingleVariableAttrID_Harm24Phase                    55
#define  SingleVariableAttrID_Harm25Phase                    56
#define  MultiVariableAttrID_Impedance                       57
#define  MultiVariableAttrID_PositiveSequence                58
#define  MultiVariableAttrID_NegativeSequence                59
#define  MultiVariableAttrID_ZeroSequence                    60
#define  MultiVariableAttrID_ActivePower                     61
#define  MultiVariableAttrID_ReactivePower                   62
#define  MultiVariableAttrID_ApparentPower                   63
#define  MultiVariableAttrID_Reserve01Value                  64
#define  MultiVariableAttrID_Reserve02Value                  65
#define  MultiVariableAttrID_Reserve03Value                  66
#define  MultiVariableAttrID_Reserve04Value                  67
#define  MultiVariableAttrID_Reserve05Value                  68
#define  MultiVariableAttrID_Reserve06Value                  69
#define  MultiVariableAttrID_Reserve07Value                  70
#define  MultiVariableAttrID_Reserve08Value                  71
#define  BinaryVariableAttrID_Raise							 72
#define  BinaryVariableAttrID_Fall							 73


#define MAX_CHANNEL_ATTRID_KEYS                   74
#define VariableAttrID_NULL                       0xFFFF

static const char* g_pszChannelKeyAttrID[MAX_CHANNEL_ATTRID_KEYS] = 
{
	"Frequancy",
	"EffecValue",
	"EffecPhase",
	"FundValue",
	"FundPhase",
	"PeakValue",
	"VellayValue",
	"InstValue",
	"AverageValue",
	"Harm02Value",
	"Harm03Value",
	"Harm04Value",
	"Harm05Value",
	"Harm06Value",
	"Harm07Value",
	"Harm08Value",
	"Harm09Value",
	"Harm10Value",
	"Harm11Value",
	"Harm12Value",
	"Harm13Value",
	"Harm14Value",
	"Harm15Value",
	"Harm16Value",
	"Harm17Value",
	"Harm18Value",
	"Harm19Value",
	"Harm20Value",
	"Harm21Value",
	"Harm22Value",
	"Harm23Value",
	"Harm24Value",
	"Harm25Value",
	"Harm02Phase",
	"Harm03Phase",
	"Harm04Phase",
	"Harm05Phase",
	"Harm06Phase",
	"Harm07Phase",
	"Harm08Phase",
	"Harm09Phase",
	"Harm10Phase",
	"Harm11Phase",
	"Harm12Phase",
	"Harm13Phase",
	"Harm14Phase",
	"Harm15Phase",
	"Harm16Phase",
	"Harm17Phase",
	"Harm18Phase",
	"Harm19Phase",
	"Harm20Phase",
	"Harm21Phase",
	"Harm22Phase",
	"Harm23Phase",
	"Harm24Phase",
	"Harm25Phase",
	"Impedance",
	"PositiveSequence",
	"NegativeSequence",
	"ZeroSequence",
	"ActivePower",
	"ReactivePower",
	"ApparentPower",
	"Reserve01",
	"Reserve02",
	"Reserve03",
	"Reserve04",
	"Reserve05",
	"Reserve06",
	"Reserve07",
	"Reserve08",
	"BinaryRaise",
	"BinaryFall"
};

static const char* g_pszChannelKeyAttrName[MAX_CHANNEL_ATTRID_KEYS] = 
{
	"msFrequancy",		//"频率",
	"msEffecValue",		//"真有效值",
	"msEffecPhasic",	//"相位",
	"msFundValue",		//"基波有效值",
	"msFundPhase",		//"基波相位",
	"msPeakValue",		//"峰值",
	"msVellayValue",	//"谷值",
	"msInstValue",		//"瞬时值",
	"msAverageValue",	//"平均值",
	"msHarm02Value",	//"2次谐波有效值",
	"msHarm03Value",	//"3次谐波有效值",
	"msHarm04Value",	//"4次谐波有效值",
	"msHarm05Value",	//"5次谐波有效值",
	"msHarm06Value",	//"6次谐波有效值",
    "msHarm07Value",	//"7次谐波有效值",
	"msHarm08Value",	//"8次谐波有效值",
	"msHarm09Value",	//"9次谐波有效值",
	"msHarm10Value",	//"10次谐波有效值",
	"msHarm11Value",	//"11次谐波有效值",
	"msHarm12Value",	//"12次谐波有效值",
	"msHarm13Value",	//"13次谐波有效值",
	"msHarm14Value",	//"14次谐波有效值",
	"msHarm15Value",	//"15次谐波有效值",
	"msHarm16Value",	//"16次谐波有效值",
	"msHarm17Value",	//"17次谐波有效值",
	"msHarm18Value",	//"18次谐波有效值",
	"msHarm19Value",	//"19次谐波有效值",
	"msHarm20Value",	//"20次谐波有效值",
	"msHarm21Value",	//"21次谐波有效值",
	"msHarm22Value",	//"22次谐波有效值",
	"msHarm23Value",	//"23次谐波有效值",
	"msHarm24Value",	//"24次谐波有效值",
	"msHarm25Value",	//"25次谐波有效值",

	"msHarm02Phase",	//"2次谐波相位",
	"msHarm03Phase",	//"3次谐波相位",
	"msHarm04Phase",	//"4次谐波相位",
	"msHarm05Phase",	//"5次谐波相位",
	"msHarm06Phase",	//"6次谐波相位",
    "msHarm07Phase",	//"7次谐波相位",
	"msHarm08Phase",	//"8次谐波相位",
	"msHarm09Phase",	//"9次谐波相位",
	"msHarm10Phase",	//"10次谐波相位",
	"msHarm11Phase",	//"11次谐波相位",
	"msHarm12Phase",	//"12次谐波相位",
	"msHarm13Phase",	//"13次谐波相位",
	"msHarm14Phase",	//"14次谐波相位",
	"msHarm15Phase",	//"15次谐波相位",
	"msHarm16Phase",	//"16次谐波相位",
	"msHarm17Phase",	//"17次谐波相位",
	"msHarm18Phase",	//"18次谐波相位",
	"msHarm19Phase",	//"19次谐波相位",
	"msHarm20Phase",	//"20次谐波相位",
	"msHarm21Phase",	//"21次谐波相位",
	"msHarm22Phase",	//"22次谐波相位",
	"msHarm23Phase",	//"23次谐波相位",
	"msHarm24Phase",	//"24次谐波相位",
	"msHarm25Phase",	//"25次谐波相位",

	"msImpedance",		//"阻抗",
	"msPositiveSequence",	//"正序",
	"msNegativeSequence",	//"负序",
	"msZeroSequence",		//"零序",	
	"msActivePower",	//"有功功率",
	"msReactivePower",	//"无功功率",
	"msApparentPower",	//	"视在功率",
	"Reserve01",
	"Reserve02",
	"Reserve03",
	"Reserve04",
	"Reserve05",
	"Reserve06",
	"Reserve07",
	"Reserve08",
	"msBinaryRaise",
	"msBinaryFall"
};

inline UINT GetVariableAttributeID(char *pszID)
{
	UINT nAttrID = VariableAttrID_NULL;
	UINT nIndex = 0;

	for (nIndex=0; nIndex<MAX_CHANNEL_ATTRID_KEYS; nIndex++)
	{
		if (strcmp(pszID, g_pszChannelKeyAttrID[nIndex]) == 0)
		{
			nAttrID = nIndex;
			break;
		}
	}

	return nAttrID;
}

typedef struct RtChannelAttrValue
{
	double dFrequency;
	double dEffecValue;
	double dEffecPhase;
	double dFundValue;
	double dFundPhase;
	double dPeakValue;
	double dVellayValue;
	double dInstValue;
	double dAverageValue;
	double dHarmValue[24];
	double dHarmPhase[24];
	double dImpedance;
	double dPositiveSequence;
	double dNegativeSequence;
	double dZeroSequence;
	double dActivePower;
	double dReactivePower;
	double dApparentPower;
	double dReserveValue[10];
	//////////////////////////////////////////////////////////////////////////
	//序量相位
	double dPositiveSequencePhase;
	double dNegativeSequencePhase;
	double dZeroSequencePhase;
}* PRTCHANNELATTRVALUE, RTCHANNELATTRVALUE;

typedef struct RtChannelAttrValue * PMULTICHANNELVALUE;
typedef struct RtChannelAttrValue MULTICHANNELVALUE;
typedef struct RtChannelAttrValue *PSINGLECHANNELV;
typedef struct RtChannelAttrValue SINGLECHANNELVALUE;


//计算函数参数结构体
typedef struct RtAttributeCalBufferPos
{
	long nBuffer1Pos;
	long nBuffer2Pos;
	long nBuffer1Len;
	long nBuffer2Len;
	long nDataLength;    //pnBuffer、pfBuffer的数据总长度
	long nBufferLength;  //pnBuffer、pfBuffer的缓冲区长度
	
	long nDftBuffer1Pos;
	long nDftBuffer2Pos;
	long nDftBuffer1Len;
	long nDftBuffer2Len;
}*PRTATTRIBUTECALBUFFERPOS, RTATTRIBUTECALBUFFERPOS;

typedef struct RtAttributeCalFuncPara
{
	DWORD *pdwFreqZeroPosition;     //参考通道的过零点位置
	UINT  *pnFreqZeroPosCount;
	DWORD *pdwRefFreqZeroPosition;  //本通道的过零点位置
	UINT  *pnRefFreqZeroPosCount;
	
	long *pnBuffer;       //缓冲区
	float          *pfBuffer;

	//计算缓冲区的位置和长度
	long nBuffer1Pos;
	long nBuffer2Pos;
	long nBuffer1Len;
	long nBuffer2Len;
	long nDataLength;    //pnBuffer、pfBuffer的数据总长度
	long nBufferLength;  //pnBuffer、pfBuffer的缓冲区长度
	
	long nDftBuffer1Pos;
	long nDftBuffer2Pos;
	long nDftBuffer1Len;
	long nDftBuffer2Len;
	
	long nBinaryBitIndex; //开关量通道对应的数据位
	long nChIndex;    //channel index
	double *pRefFrequency;//参考通道的频率
	
	double dCeofValue;
	double dZeroValue;
	PRTCHANNELATTRVALUE pRefRtChAttrVal;  //关连的参考属性值对象
	PRTCHANNELATTRVALUE pRtChAttrVal;  //关连的属性值对象
	PRTCHANNELATTRVALUE pRtChanAttr[6];//关联的属性对象，复合通道使用
	long nChanCount;	//通道的数量，复合通道使用
}* PRTATTRIBUTECALFUNCPARA, RTATTRIBUTECALFUNCPARA;

typedef struct RtAttributeCalFuncPara *PRTSINGLECALFUNCPARA;
typedef struct RtAttributeCalFuncPara  RTSINGLECALFUNCPARA;

typedef struct RtAttributeCalFuncPara* PRTMULTICALFUNCPARA;
typedef struct RtAttributeCalFuncPara RTMULTICALFUNCPARA;

typedef struct RtAttributeCalFuncPara* PRTCALFUNCPARA;
typedef struct RtAttributeCalFuncPara  RTCALFUNCPARA;



//没有用到
//缓冲区结构体
typedef struct RtMemBuffer
{
	long nBufferLen;
	long *pBuffer1;
	long nBuffer1Len;
	long *pBuffer2;
	long nBuffer2Len;
}*PRTMEMBUFFER,RTMEMBUFFER; 

//指针函数
typedef void (CALFUNC) (PRTCALFUNCPARA pCalFuncPara);


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//variable type define

inline void InitSysAnalyseMngr_AttrSpy(PCHATTRDATASMNGR p)
{
	long nIndex=0;
	memset(p, 0, sizeof(CHATTRDATASMNGR));
	short *pAttrData = NULL;
	
	for (nIndex=0; nIndex<MAX_STRECORD_CHANNELS; nIndex++)
	{
		pAttrData = p->nAttrState[nIndex];
		
		*(pAttrData + SingleVariableAttrID_Frequancy) = 1;
		*(pAttrData + SingleVariableAttrID_EffecValue) = 1;
		*(pAttrData + SingleVariableAttrID_FundValue) = 0;
	}
}

inline void InitSysAnalyseMngr_AttrDefault(PCHATTRDATASMNGR p)
{
	long nIndex=0;
	memset(p, 0, sizeof(CHATTRDATASMNGR));
	short *pAttrData = NULL;
	
	for (nIndex=0; nIndex<MAX_STRECORD_CHANNELS; nIndex++)
	{
		pAttrData = p->nAttrState[nIndex];
		
		*(pAttrData + SingleVariableAttrID_Frequancy) = 1;
		*(pAttrData + SingleVariableAttrID_EffecValue) = 1;
		*(pAttrData + SingleVariableAttrID_FundValue) = 0;
	}
}



#endif // !defined(_RECORDDEFINE_H__)
