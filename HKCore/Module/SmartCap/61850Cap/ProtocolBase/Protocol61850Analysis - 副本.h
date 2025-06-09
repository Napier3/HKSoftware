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
	int     nErrorType[8][15];        //SMV 9-2�쳣���� Ĭ��ֵΪ0��Ĭ��Ϊ8��ASDU��
}EP_ANALYSIS_RESULT_92,  *PEP_ANALYSIS_RESULT_92;


typedef struct epAnalysisResult_GOOSE
{ 
	int     nErrorType[15];        //SMV 9-2�쳣���� Ĭ��ֵΪ0��Ĭ��Ϊ8��ASDU��
}EP_ANALYSIS_RESULT_GS,  *PEP_ANALYSIS_RESULT_GS;


typedef struct epAnalysisResult
{ 
	int            messageType;
	char         desMAC[6];              //Ŀ���ַ��
	char         srcMAC[6];               //Դ��ַ
	char          APPID[2];                 //APPID 
	DWORD dwPacketIndex;        //��֡���ڸû����е�λ�ã�
	BYTE       Time[8];                     //������֡��ʱ�䣻
	double      dDeltTime;
	DWORD dwMessageLen;       //��֡���ĵĳ���

	union
	{
		EP_ANALYSIS_RESULT_92 rslt_92;
		EP_ANALYSIS_RESULT_GS rslt_gs;
	};
	vector <EP_ANALYSIS_ERR> m_vErr;

}EP_ANALYSIS_RESULT ,*PEP_ANALYSIS_RESULT;


