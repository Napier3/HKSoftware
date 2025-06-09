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
	int     nErrorType[8][PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM];        //SMV 9-2�쳣���� Ĭ��ֵΪ0��Ĭ��Ϊ8��ASDU��
    int     nAsduCnt;
	int     nSmpCountMaxValue;//20220614 zhouhj �洢���ü��������ֵ,���ڼ��������
}EP_ANALYSIS_RESULT_92,  *PEP_ANALYSIS_RESULT_92;


typedef struct epAnalysisResult_GOOSE
{ 
	int     nErrorType[PROTOCOL_61850ANALYSIS_ERROR_TYPE_NUM];        //GOOSE
}EP_ANALYSIS_RESULT_GS,  *PEP_ANALYSIS_RESULT_GS;

typedef struct epAnalysisResult
{ 
	int                nErrorFlag;
	char            desMAC[6];              //Ŀ���ַ��
	char             srcMAC[6];               //Դ��ַ
	DWORD     m_dwAppID;            //APPID 
	DWORD     dwPacketIndex;        //��֡���ڸû����е�λ�ã�
	__int64        n64Time;                     //������֡��ʱ�䣻
	double         dDeltTime;                //����һ֡�Ƚϵ�ʱ��deltʱ�䣻
	DWORD      dMaxValueTime;      //��ǰ֡��Ƚ�ʱ�򣬻�ȡ��deltʱ�䣻
	DWORD      dwMessageLen;       //��֡���ĵĳ���
    long              nChangeBit[GSCHANNEL_CNT];
	long              nChangeFlag[GSCHANNEL_CNT];
	long              nCurChnel;
	long              nChnnelType[GSCHANNEL_CNT];
	long              nPkgNum;//20220614 zhouhj  ����ͳ�Ƶ�ǰ������֡��


	union
	{
		EP_ANALYSIS_RESULT_92 rslt_92;  //SMV 9-2
		EP_ANALYSIS_RESULT_GS rslt_gs; // GOOSE;
	};
	//vector <EP_ANALYSIS_ERR> m_vErr;
}EP_ANALYSIS_RESULT ,*PEP_ANALYSIS_RESULT;

//lijunqing 2020-6-19   ��ʼ����������ṹ��
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

// ���SMV-9-2�ģ�
void ep_protocol_analysis92(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult,
							long *pnChType,long *pnChAngType);

// ���GOOSE�ģ�
void ep_protocol_analysisGS(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult);

//////////////////////////////////////////////////////////////////////////
//2022-5-31  lijunqing  ��������λ�б�
typedef struct ep_gs_binary_turn
{
	DWORD nChType;
	DWORD nChLenth;//20220616 zhouhj ����ͨ���ֽڳ���,˫���Ʒ�ʡ�λ��������,��Ҫͨ����ֵ����
	DWORD nChIndex;
	DWORD nValue;
	__int64 n64Time;  //���ݶ�Ӧ��ʱ�� 
	long nTimeRel; //���ʱ�� us  ��ͬͨ�������α�λ֮���ʱ���
	CExBaseObject *pChRef;  //������ͨ������

	ep_gs_binary_turn()
	{
		nChType = 0;
		nChLenth = 0;
		nChIndex = 0;
		nValue = 0;
		n64Time = 0;  //���ݶ�Ӧ��ʱ�� 
		nTimeRel = 0; //���ʱ�� us  ��ͬͨ�������α�λ֮���ʱ���
		pChRef = NULL;  //������ͨ������
	};
}EP_GOOSE_BINARY_TURN, *PEP_GOOSE_BINARY_TURN;

class CEpGooseBinaryTurns : public CTLinkList<EP_GOOSE_BINARY_TURN>
{
public:
	long m_nCurrReadIndex;  //��ǰ���ʵ���������̬��ӷ���
	CEpGooseBinaryTurns();
	virtual ~CEpGooseBinaryTurns();

public:
	PEP_GOOSE_BINARY_TURN FindPrevTurn(PEP_GOOSE_BINARY_TURN pCurr);//20220605 �޸Ĵ��ζ���Ϊ����,��ֹ����index�ҵ������Լ�,ʱ�����ԶΪ0
	void CalTimeRel(PEP_GOOSE_BINARY_TURN pCurr);
	void CalTimeRel(PEP_GOOSE_BINARY_TURN pPrev,PEP_GOOSE_BINARY_TURN pCurr);
	void Reset();
	PEP_GOOSE_BINARY_TURN New();
};


void ep_get_CapParseData_value(DWORD nChType,DWORD nChLenth, DWORD nValue, DWORD nValue2, CString&strValue);//20220616 zhouhj ��Ҫ�ṹͨ���������ͼ�����ֵ,һ���б�ͨ������,��˫�㡢Ʒ�ʡ�λ��
void ep_get_CapParseData_value(EPCAPPARSEDATA &oChData, CString&strValue);

