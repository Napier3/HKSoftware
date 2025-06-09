#include "ProtocolGlobalDef.h"
#include <vector>
using namespace std; 

typedef struct epAnalysisErr
{ 
	int        nAsdu;
	int        nErrorType;   
	int        nMsgIndex;
}EP_ANALYSIS_ERR, *PEP_ANALYSIS_ERR;

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
	int     nErrorType[8][15];        //SMV 9-2异常类型 默认值为0；默认为8个ASDU；
}EP_ANALYSIS_RESULT_92,  *PEP_ANALYSIS_RESULT_92;


typedef struct epAnalysisResult_GOOSE
{ 
	int     nErrorType[15];        //SMV 9-2异常类型 默认值为0；默认为8个ASDU；
}EP_ANALYSIS_RESULT_GS,  *PEP_ANALYSIS_RESULT_GS;


typedef struct epAnalysisResult
{ 
	int            messageType;
	char         desMAC[6];              //目标地址；
	char         srcMAC[6];               //源地址
	char          APPID[2];                 //APPID 
	DWORD dwPacketIndex;        //此帧所在该缓存中的位置；
	BYTE       Time[8];                     //保留该帧的时间；
	double      dDeltTime;
	DWORD dwMessageLen;       //此帧报文的长度

	union
	{
		EP_ANALYSIS_RESULT_92 rslt_92;
		EP_ANALYSIS_RESULT_GS rslt_gs;
	};
	vector <EP_ANALYSIS_ERR> m_vErr;

}EP_ANALYSIS_RESULT ,*PEP_ANALYSIS_RESULT;


