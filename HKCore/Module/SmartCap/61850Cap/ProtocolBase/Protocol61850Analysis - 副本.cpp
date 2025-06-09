#include "stdafx.h"
#include "Protocol61850Analysis.h"

#include <math.h>

vector <EP_ANALYSIS_RESULT> g_AnalysisResult;
/*
当控制块是9-2时候：
nErrorType是个数组  默认值为0，当等于1时候表示有错误
第1个元素表示 丢包
第2个元素表示 错序
第3个元素表示 失步
第4个元素表示 品质异常
第5个元素表示 抖动

当控制块是GOOSE时候
nGSErrorType是个数组  默认值为0，当等于1时候表示有错误
第1个元素表示 状态改变/StNO丢失
第2个元素表示 装置重启 
第3个元素表示 虚变位 
第4个元素表示 StNum 错误
第5个元素表示 状态改变
第6个元素表示 SqNO 重复
第7个元素表示 SqNO 丢失
第8个元素表示 GOOSE生存时间为0
第9个元素表示 SqNO初值错误
第10个元素表示 GOOSE 延时
第11个元素表示 GOOSE 中断
第12个元素表示 时钟未同步
*/

void ep_protocol_analysis92(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult)
{
	EP_ANALYSIS_RESULT AnalysisResult;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SMV判断异常
	//当是第一帧的时候不做比较，直接返回，第一帧的标识就是==0
	if (pPrevData->oData92.nFirst==0)
		return;
	pPrevData->oData92.nFirst = 1;
    int nMaxSmpCnt  = 4000;
	int nCurASDUCnt = pDatas->oData92.Num_ASDU;

    int nIndexAsdu = 0;
	//默认最大的采样帧数为3999;
	for (nIndexAsdu = 0;  nIndexAsdu  < nCurASDUCnt ; nIndexAsdu++)
	{
		int nPreSmpCnt = pPrevData->oData92.asdu[nIndexAsdu].smpCnt;
		int nCurSmpCnt = pDatas->oData92.asdu[nIndexAsdu].smpCnt;

		//若两者相等则认为没有丢包；
		if (nCurSmpCnt  -  nPreSmpCnt == nCurASDUCnt )//不丢包；
		{
		}
		else if ((nCurSmpCnt  + nPreSmpCnt + 1) % 4000==0)//不丢包,这里的意思就是3999，变到0的时候，认为不丢包；
		{
		}

		if (nPreSmpCnt  -  nCurSmpCnt  !=  nMaxSmpCnt)
		{	
			if (nCurSmpCnt   -   nPreSmpCnt <= 0 )//错序
			{
				AnalysisResult.rslt_92.nErrorType[nIndexAsdu][1]  = 1;	
				AnalysisResult.messageType = 1;	
				goto  SAVE;
			}
			else //丢包
			{
				AnalysisResult.rslt_92.nErrorType[nIndexAsdu] [0] = 1;
				AnalysisResult.messageType = 1;
				goto  SAVE;
			}
		}

		//丢失同步信号；
		int nSmpSynch = pDatas->oData92.asdu[nIndexAsdu].smpSynch;
		if (nSmpSynch==0)
		{
			AnalysisResult.rslt_92.nErrorType[nIndexAsdu][2] = 1;	
			AnalysisResult.messageType = 1;	
			goto  SAVE;
		}

		//品质异常；
		int   nChCnt = pDatas->oData92.asdu[nIndexAsdu].nChCount;   //获取通道数量；
		for (int nIndex = 0;  nIndex  <  nChCnt;  nIndex++)
		{
			BYTE Byte0,   Byte1,  Byte2,  Byte3;
			Byte0 = (BYTE)(pDatas->pDatas[nIndex].dwValue >> 24); 
			Byte1 = (BYTE)(pDatas->pDatas[nIndex].dwValue >> 16);
			Byte2 = (BYTE)(pDatas->pDatas[nIndex].dwValue >> 8);
			Byte3 = (BYTE)(pDatas->pDatas[nIndex].dwValue); 
			if (Byte0 != 0  || Byte1 != 0  ||  Byte2  !=  0  || Byte3 != 0)
			{
				AnalysisResult.rslt_92.nErrorType[nIndexAsdu] [3] = 1;
				AnalysisResult.messageType = 1;	
				goto  SAVE;
				break;
			}
		}
	}	

	//离散度: 就是找那个最大值
	BYTE byTime[8];
	::memset(byTime,  0x0, 8);
	::memcpy(byTime,  &pPrevData->n64Time,   8);
	BYTE t4 =  byTime[0];	
	BYTE t3 =  byTime[1];
	BYTE t2 =  byTime[2];
	BYTE t1 =  byTime[3];
	BYTE t8 =  byTime[4];	
	BYTE t7 =  byTime[5];
	BYTE t6 =  byTime[6];
	BYTE t5 =  byTime[7];
	double Time1      =   t4  +  t3  *  pow(2.0,  8)  +  t2  *  pow(2.0,  16)  +  t1  *  pow(2.0,  24);
	double usTime1  =   t8   +  t7 *  pow(2.0,   8)  +   t6   *   pow(2.0,   16)  +  t5  *  pow(2.0,  24);

	::memset(byTime,  0x0, 8);
	::memcpy(byTime,  &pDatas->n64Time,   8);
	::memcpy(AnalysisResult.Time,  &pDatas->n64Time,   8);
	 t4 =  byTime[0];	
	 t3 =  byTime[1];
	 t2 =  byTime[2];
	 t1 =  byTime[3];
	 t8 =  byTime[4];	
	 t7 =  byTime[5];
	 t6 =  byTime[6];
	 t5 =  byTime[7];
	 double Time2      =   t4  +  t3  *  pow(2.0,  8)  +  t2  *  pow(2.0,  16)  +  t1  *  pow(2.0,  24);
	 double usTime2  =   t8   +  t7 *  pow(2.0,   8)  +   t6   *   pow(2.0,   16)  +  t5  *  pow(2.0,  24);
	 int    nSecDif = Time2 - Time1;
	 unsigned long nResult  = 0;
	 nResult   = nSecDif    *  1000000  +  usTime2  -  usTime1;//这里存储两帧之间的时间的差值；
	  AnalysisResult.dDeltTime  =  nResult  - 250000;   //计算出两帧之间的时间差值与250000之间的delt，然后判断delt值正负和绝对值；
	 //AnalysisResult.nGSErrorType[4]  = 1;

    //小潘叮嘱：两组smv第一帧的时标给过去，就是smpcnt为0的那个东西，goose变位后的第一帧的时标给过去，



SAVE:
	g_AnalysisResult.push_back(AnalysisResult);
}


void ep_protocol_analysisGS(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult)
{
	EP_ANALYSIS_RESULT AnalysisResult;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SMV判断异常
	//当是第一帧的时候不做比较，直接返回，第一帧的标识就是==0
	if (pPrevData->oData92.nFirst==0)
		return;
	pPrevData->oData92.nFirst = 1;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//GOOSE判断异常；
	int nChIndex = 0;	

	// 变位的情况下如下判断；
	// 不等于0表示有变位
    int  nCompRet = memcmp(pPrevData->oDataGs.chData , pDatas->oDataGs.chData,  pDatas->oDataGs.nChCnt  *  sizeof(EPGOOSECHDATA));
	if ( nCompRet != 0)
	{
		// 变位的情况下如下判断；
		//SqNO初值错误
		if ( pDatas->oDataGs.sqNO   !=   0)
		{
			AnalysisResult.messageType  = 2;
			AnalysisResult.rslt_gs.nErrorType [8] = 1;
		}
		else 
		{
			//状态改变/StNO丢失
			if (pDatas->oDataGs.sqNO==0  &&  pDatas->oDataGs.sqNO  -  pPrevData->oDataGs.sqNO > 1)
			{
				AnalysisResult.messageType  =  2;
				AnalysisResult.rslt_gs.nErrorType [0]  = 1;
			}

			// 变位的情况下这样判断;
			//变位
			if ( pDatas->oDataGs.stNO   -   pPrevData->oDataGs.stNO <= 1)
			{
				AnalysisResult.messageType  =  2;
				AnalysisResult.rslt_gs.nErrorType [4]  = 1;
			}
		}
	}

	//装置重启
	if (pDatas->oDataGs.sqNO==1  &&  pDatas->oDataGs.stNO == 1)
	{
		AnalysisResult.messageType  =  2;
		AnalysisResult.rslt_gs.nErrorType [1]  = 1;
	}
	
	//虚变位
	if (pDatas->oDataGs.sqNO  ==  0  &&  pDatas->oDataGs.stNO   -  pPrevData->oDataGs.stNO == 1)
	{
		if (nCompRet==0)//而且当前数据集和前一帧的数据集相等则判为虚变位；
		{
			AnalysisResult.messageType  =  2;
			AnalysisResult.rslt_gs.nErrorType [2]  = 1;
		}	
	}

	//StNum 错误
	if ( pDatas->oDataGs.stNO   -   pPrevData->oDataGs.stNO  > 1)
	{
		AnalysisResult.messageType  =  2;
		AnalysisResult.rslt_gs.nErrorType [3]  = 1;
	}

	//SqNO 重复 
	if ( pDatas->oDataGs.stNO  ==  pPrevData->oDataGs.stNO )
	{
		AnalysisResult.messageType  = 2;
		AnalysisResult.rslt_gs.nErrorType [5]  = 1;
	}

	//SqNO 丢失
	if ( pDatas->oDataGs.stNO  -  pPrevData->oDataGs.stNO  > 1)
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [6] = 1;
	}

	//GOOSE生存时间为0
	if ( pDatas->oDataGs.TimeAllowedToLive  ==  0)
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [7] = 1;
	}

	//GOOSE 延时
	if ( pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample  >  pDatas->oDataGs.TimeAllowedToLive &&
		pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample   <  2 * pDatas->oDataGs.TimeAllowedToLive)
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [9]  = 1;
	}

	//GOOSE 中断 
	if ( pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample  >  2 * pDatas->oDataGs.TimeAllowedToLive )
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [10] = 1;
		//goto  SAVE;
	}

	//时钟未同步
	if ( pDatas->oDataGs.sqNO!=0 )
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [11] = 1;
	}

SAVE:
	g_AnalysisResult.push_back(AnalysisResult);
}