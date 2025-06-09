// RecordTestClassDef.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_RECORDDEFINE_H__)
#define _RECORDDEFINE_H__

#include "RecordDefine.h"
#include "RecordGlobalDefine.h"

#define RTCLASSID_COMPLEXVARIABLE      (CLASSID_LISTCLASS + 0x00000006)	//���ͨ������ID
#define RTCLASSID_SINGLEVARIABLE       (CLASSID_LISTCLASS + 0x00000007)	//��ͨ������ID
#define RTCLASSID_BINARYVARIABLE       (CLASSID_LISTCLASS + 0x00000008)	//����ͨ������ID
#define RTCLASSID_MULTIVARIABLE        (CLASSID_LISTCLASS + 0x00000009)	//����ͨ������ID
#define RTCLASSID_VARIABLE             (CLASSID_LISTCLASS + 0x0000000A)	//ͨ���������ID
#define RTCLASSID_VARIABLES            (CLASSID_LISTCLASS + 0x0000000B)	//ͨ�����϶���ID
#define RTCLASSID_STARTUP              (CLASSID_LISTCLASS + 0x0000000C)	//��������ID
#define RTCLASSID_MEMBUFFER            (CLASSID_LISTCLASS + 0x0000000D)	//�������ID
#define RTCLASSID_RECORDTEST           (CLASSID_LISTCLASS + 0x0000000E)	//�������ID
#define RTCLASSID_RECORDTESTS          (CLASSID_LISTCLASS + 0x0000000F)	//���鼯�϶���ID

#define RTCLASSID_SET                  (CLASSID_BASECLASS + 0x00000001)     //��ֵ��
#define RTCLASSID_CHANNEL              (CLASSID_BASECLASS + 0x00000002)     //ͨ����
#define RTCLASSID_SETS                 (CLASSID_LISTCLASS + 0x00000001)   //��ֵ������
#define RTCLASSID_CHANNELS             (CLASSID_LISTCLASS + 0x00000002)   //ͨ��������
#define RTCLASSID_DATAATTRIBUTE        (CLASSID_LISTCLASS + 0x00000003)   //������
#define RTCLASSID_DATAATTRIBUTES       (CLASSID_LISTCLASS + 0x00000004)     //���ݼ�����
#define RTCLASSID_ATTRBUFFER           (CLASSID_BASECLASS + 0x00000010)     //���Ի�����
#define RTCLASSID_ALLOCBUFFER          (CLASSID_LISTCLASS + 0x00000011)   //�ڴ����

#define RTCLASSID_FILEWRITE            (CLASSID_LISTCLASS + 0x00000012)   //�ļ�д�������
#define RTCLASSID_FILEFORMAT           (CLASSID_LISTCLASS + 0x00000013)   //�ļ�д��ʽ����
#define RTCLASSID_FILEFORMAT_BUFFER    (CLASSID_BASECLASS + 0x00000014)     //�ļ���ʽ-������
#define RTCLASSID_SPY                  (CLASSID_BASECLASS + 0x00000015)     //����

//config
#define RTCLASSID_APPMODEL             (CLASSID_BASECLASS + 0x00000016)     //Ӧ������
#define RTCLASSID_APPMODELS            (CLASSID_LISTCLASS + 0x00000017)     //Ӧ���������
#define RTCLASSID_CFGVARIABLE          (CLASSID_BASECLASS + 0x00000018)	    //ͨ���������ID
#define RTCLASSID_CFGVARIABLES         (CLASSID_LISTCLASS + 0x00000019)	//ͨ�����϶���ID
#define RTCLASSID_CFGRECORDTEST        (CLASSID_LISTCLASS + 0x0000001A)	//�������ID
#define RTCLASSID_CFGRECORDTESTS       (CLASSID_LISTCLASS + 0x0000001B)	//���鼯�϶���ID
#define RTCLASSID_CFGRECORDTESTTYPES   (CLASSID_LISTCLASS + 0x0000001C)	//�������ͼ���ID
#define RTCLASSID_CFGRECORDTESTTYPE    (CLASSID_LISTCLASS + 0x0000001D)	//���鼯�϶���ID

//��������
#define RTCLASSID_ATTRSPYCONFIGS	   (CLASSID_LISTCLASS + 0x0000001E)	//�������Լ���ID
#define RTCLASSID_ATTRSPYCONFIG		   (CLASSID_LISTCLASS + 0x0000001F)	//��������ID


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//ͨ������ֵ
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
	"msFrequancy",		//"Ƶ��",
	"msEffecValue",		//"����Чֵ",
	"msEffecPhasic",	//"��λ",
	"msFundValue",		//"������Чֵ",
	"msFundPhase",		//"������λ",
	"msPeakValue",		//"��ֵ",
	"msVellayValue",	//"��ֵ",
	"msInstValue",		//"˲ʱֵ",
	"msAverageValue",	//"ƽ��ֵ",
	"msHarm02Value",	//"2��г����Чֵ",
	"msHarm03Value",	//"3��г����Чֵ",
	"msHarm04Value",	//"4��г����Чֵ",
	"msHarm05Value",	//"5��г����Чֵ",
	"msHarm06Value",	//"6��г����Чֵ",
    "msHarm07Value",	//"7��г����Чֵ",
	"msHarm08Value",	//"8��г����Чֵ",
	"msHarm09Value",	//"9��г����Чֵ",
	"msHarm10Value",	//"10��г����Чֵ",
	"msHarm11Value",	//"11��г����Чֵ",
	"msHarm12Value",	//"12��г����Чֵ",
	"msHarm13Value",	//"13��г����Чֵ",
	"msHarm14Value",	//"14��г����Чֵ",
	"msHarm15Value",	//"15��г����Чֵ",
	"msHarm16Value",	//"16��г����Чֵ",
	"msHarm17Value",	//"17��г����Чֵ",
	"msHarm18Value",	//"18��г����Чֵ",
	"msHarm19Value",	//"19��г����Чֵ",
	"msHarm20Value",	//"20��г����Чֵ",
	"msHarm21Value",	//"21��г����Чֵ",
	"msHarm22Value",	//"22��г����Чֵ",
	"msHarm23Value",	//"23��г����Чֵ",
	"msHarm24Value",	//"24��г����Чֵ",
	"msHarm25Value",	//"25��г����Чֵ",

	"msHarm02Phase",	//"2��г����λ",
	"msHarm03Phase",	//"3��г����λ",
	"msHarm04Phase",	//"4��г����λ",
	"msHarm05Phase",	//"5��г����λ",
	"msHarm06Phase",	//"6��г����λ",
    "msHarm07Phase",	//"7��г����λ",
	"msHarm08Phase",	//"8��г����λ",
	"msHarm09Phase",	//"9��г����λ",
	"msHarm10Phase",	//"10��г����λ",
	"msHarm11Phase",	//"11��г����λ",
	"msHarm12Phase",	//"12��г����λ",
	"msHarm13Phase",	//"13��г����λ",
	"msHarm14Phase",	//"14��г����λ",
	"msHarm15Phase",	//"15��г����λ",
	"msHarm16Phase",	//"16��г����λ",
	"msHarm17Phase",	//"17��г����λ",
	"msHarm18Phase",	//"18��г����λ",
	"msHarm19Phase",	//"19��г����λ",
	"msHarm20Phase",	//"20��г����λ",
	"msHarm21Phase",	//"21��г����λ",
	"msHarm22Phase",	//"22��г����λ",
	"msHarm23Phase",	//"23��г����λ",
	"msHarm24Phase",	//"24��г����λ",
	"msHarm25Phase",	//"25��г����λ",

	"msImpedance",		//"�迹",
	"msPositiveSequence",	//"����",
	"msNegativeSequence",	//"����",
	"msZeroSequence",		//"����",	
	"msActivePower",	//"�й�����",
	"msReactivePower",	//"�޹�����",
	"msApparentPower",	//	"���ڹ���",
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
	//������λ
	double dPositiveSequencePhase;
	double dNegativeSequencePhase;
	double dZeroSequencePhase;
}* PRTCHANNELATTRVALUE, RTCHANNELATTRVALUE;

typedef struct RtChannelAttrValue * PMULTICHANNELVALUE;
typedef struct RtChannelAttrValue MULTICHANNELVALUE;
typedef struct RtChannelAttrValue *PSINGLECHANNELV;
typedef struct RtChannelAttrValue SINGLECHANNELVALUE;


//���㺯�������ṹ��
typedef struct RtAttributeCalBufferPos
{
	long nBuffer1Pos;
	long nBuffer2Pos;
	long nBuffer1Len;
	long nBuffer2Len;
	long nDataLength;    //pnBuffer��pfBuffer�������ܳ���
	long nBufferLength;  //pnBuffer��pfBuffer�Ļ���������
	
	long nDftBuffer1Pos;
	long nDftBuffer2Pos;
	long nDftBuffer1Len;
	long nDftBuffer2Len;
}*PRTATTRIBUTECALBUFFERPOS, RTATTRIBUTECALBUFFERPOS;

typedef struct RtAttributeCalFuncPara
{
	DWORD *pdwFreqZeroPosition;     //�ο�ͨ���Ĺ����λ��
	UINT  *pnFreqZeroPosCount;
	DWORD *pdwRefFreqZeroPosition;  //��ͨ���Ĺ����λ��
	UINT  *pnRefFreqZeroPosCount;
	
	long *pnBuffer;       //������
	float          *pfBuffer;

	//���㻺������λ�úͳ���
	long nBuffer1Pos;
	long nBuffer2Pos;
	long nBuffer1Len;
	long nBuffer2Len;
	long nDataLength;    //pnBuffer��pfBuffer�������ܳ���
	long nBufferLength;  //pnBuffer��pfBuffer�Ļ���������
	
	long nDftBuffer1Pos;
	long nDftBuffer2Pos;
	long nDftBuffer1Len;
	long nDftBuffer2Len;
	
	long nBinaryBitIndex; //������ͨ����Ӧ������λ
	long nChIndex;    //channel index
	double *pRefFrequency;//�ο�ͨ����Ƶ��
	
	double dCeofValue;
	double dZeroValue;
	PRTCHANNELATTRVALUE pRefRtChAttrVal;  //�����Ĳο�����ֵ����
	PRTCHANNELATTRVALUE pRtChAttrVal;  //����������ֵ����
	PRTCHANNELATTRVALUE pRtChanAttr[6];//���������Զ��󣬸���ͨ��ʹ��
	long nChanCount;	//ͨ��������������ͨ��ʹ��
}* PRTATTRIBUTECALFUNCPARA, RTATTRIBUTECALFUNCPARA;

typedef struct RtAttributeCalFuncPara *PRTSINGLECALFUNCPARA;
typedef struct RtAttributeCalFuncPara  RTSINGLECALFUNCPARA;

typedef struct RtAttributeCalFuncPara* PRTMULTICALFUNCPARA;
typedef struct RtAttributeCalFuncPara RTMULTICALFUNCPARA;

typedef struct RtAttributeCalFuncPara* PRTCALFUNCPARA;
typedef struct RtAttributeCalFuncPara  RTCALFUNCPARA;



//û���õ�
//�������ṹ��
typedef struct RtMemBuffer
{
	long nBufferLen;
	long *pBuffer1;
	long nBuffer1Len;
	long *pBuffer2;
	long nBuffer2Len;
}*PRTMEMBUFFER,RTMEMBUFFER; 

//ָ�뺯��
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
