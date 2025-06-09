#include "ProtocolGlobalDef.h"
#include <vector>
using namespace std; 
#include "../CapGlobalDef.h"
#define GSCHANNEL_CNT 256
#define PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM      20      


typedef struct epAnalysisErr
{ 
	int        nAsdu;
	int        nErrorType;   
	int        nMsgIndex;
}EP_ANALYSIS_ERR, *PEP_ANALYSIS_ERR;

typedef struct epSVDelay
{
		long dwValue;
}EP_SVDELAY, *PEP_SVDELAY;
/*
typedef struct epAnalysisErrType
{ 
	int             nAsdu;
	int             nErrorType;   
}EP_ANALYSIS_ERR, *PEP_ANALYSIS_RESULT_GS;

typedef struct epAnalysisErrGs
{ 
	int              nMsgIndex;
	int              nErrCount;
	int            *pnErrorType;   
}EP_ANALYSIS_ERR,  *PEP_ANALYSIS_RESULT_GS;
*/

typedef struct epAnalysisResult_92 
{ 
	int     nErrorType[8][PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM];        //SMV 9-2异常类型 默认值为0；默认为8个ASDU；
    int     nAsduCnt;
	int     nSmpCountMaxValue;//20220614 zhouhj 存储采用计数器最大值,用于计算采样率
}EP_ANALYSIS_RESULT_92,  *PEP_ANALYSIS_RESULT_92;


typedef struct epAnalysisResult_GOOSE
{ 
	int     nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM];        //GOOSE
}EP_ANALYSIS_RESULT_GS,  *PEP_ANALYSIS_RESULT_GS;

typedef struct epAnalysisResult
{ 
	int                nErrorFlag;
	char            desMAC[6];              //目标地址；
	char             srcMAC[6];               //源地址
	DWORD     m_dwAppID;            //APPID 
	DWORD     dwPacketIndex;        //此帧所在该缓存中的位置；
	__int64        n64Time;                     //保留该帧的时间；
	double         dDeltTime;                //与上一帧比较的时候delt时间；
	DWORD      dMaxValueTime;      //以前帧相比较时候，获取的delt时间；
	DWORD      dwMessageLen;       //此帧报文的长度
    long              nChangeBit[GSCHANNEL_CNT];
	long              nChangeFlag[GSCHANNEL_CNT];
	long              nCurChnel;
	long              nChnnelType[GSCHANNEL_CNT];
	long              nPkgNum;//20220614 zhouhj  用于统计当前报文总帧数


	union
	{
		EP_ANALYSIS_RESULT_92 rslt_92;  //SMV 9-2
		EP_ANALYSIS_RESULT_GS rslt_gs; // GOOSE;
	};
	//vector <EP_ANALYSIS_ERR> m_vErr;
}EP_ANALYSIS_RESULT ,*PEP_ANALYSIS_RESULT;

//lijunqing 2020-6-19   初始化分析结果结构体
inline void ep_protocol_analysis_init(EP_ANALYSIS_RESULT &oResult)
{
	oResult.nErrorFlag = 0;
	oResult.dDeltTime = 0;
	oResult.nPkgNum = 0;
	oResult.rslt_92.nSmpCountMaxValue = 0;
	//oResult.m_vErr.empty();
	::memset(oResult.rslt_92.nErrorType, 0x0, sizeof(int) * 8 *PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM); 
	::memset(oResult.rslt_gs.nErrorType, 0x0, sizeof(int)  *PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM); 
	::memset(oResult.nChangeBit, 0x0, sizeof(long)  *GSCHANNEL_CNT); 
	::memset(oResult.nChangeFlag, 0x0, sizeof(long)  *GSCHANNEL_CNT); 
	::memset(oResult.nChnnelType, 0x0, sizeof(long)  *GSCHANNEL_CNT); 

	oResult.nCurChnel = -1;
}

inline void ep_protocol_analysis_init(PEP_ANALYSIS_RESULT pResult)
{
	ep_protocol_analysis_init(*pResult);
}

// 检查SMV-9-2的；
void ep_protocol_analysis92(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult,
							long *pnChType,long *pnChAngType);

// 检查GOOSE的；
void ep_protocol_analysisGS(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult);

//////////////////////////////////////////////////////////////////////////
//2022-5-31  lijunqing  开关量变位列表
typedef struct ep_gs_binary_turn
{
	DWORD nChType;
	DWORD nChLenth;//20220616 zhouhj 增加通道字节长度,双点和品质、位串的区分,需要通过该值区分
	DWORD nChIndex;
	DWORD nValue;
	__int64 n64Time;  //数据对应的时间 
	long nTimeRel; //相对时间 us  相同通道，两次变位之间的时间差
	CExBaseObject *pChRef;  //关联的通道对象

	ep_gs_binary_turn()
	{
		nChType = 0;
		nChLenth = 0;
		nChIndex = 0;
		nValue = 0;
		n64Time = 0;  //数据对应的时间 
		nTimeRel = 0; //相对时间 us  相同通道，两次变位之间的时间差
		pChRef = NULL;  //关联的通道对象
	};
}EP_GOOSE_BINARY_TURN, *PEP_GOOSE_BINARY_TURN;

class CEpGooseBinaryTurns : public CTLinkList<EP_GOOSE_BINARY_TURN>
{
public:
	long m_nCurrReadIndex;  //当前访问的索引，动态添加访问
	CEpGooseBinaryTurns();
	virtual ~CEpGooseBinaryTurns();

public:
	PEP_GOOSE_BINARY_TURN FindPrevTurn(PEP_GOOSE_BINARY_TURN pCurr);//20220605 修改传参对象为自身,防止根据index找到的是自己,时间差永远为0
	void CalTimeRel(PEP_GOOSE_BINARY_TURN pCurr);
	void CalTimeRel(PEP_GOOSE_BINARY_TURN pPrev,PEP_GOOSE_BINARY_TURN pCurr);
	void Reset();
	PEP_GOOSE_BINARY_TURN New();
};


void ep_get_CapParseData_value(DWORD nChType,DWORD nChLenth, DWORD nValue, DWORD nValue2, CString&strValue);//20220616 zhouhj 需要结构通道报文类型及长度值,一起判别通道类型,如双点、品质、位串
void ep_get_CapParseData_value(EPCAPPARSEDATA &oChData, CString&strValue);

