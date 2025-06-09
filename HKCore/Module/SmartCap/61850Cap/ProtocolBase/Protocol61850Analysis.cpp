#include "stdafx.h"
#include "Protocol61850Analysis.h"

#include <math.h>

//2022-11-13  lijunqing
//vector <EP_ANALYSIS_RESULT> g_AnalysisResult;
/*
当控制块是9-2时候：
nErrorType是个数组  默认值为0，当等于1时候表示有错误
第1个元素表示 丢包
第2个元素表示 错序
第3个元素表示 失步
第4个元素表示 品质异常
第5个元素表示 抖动

CString strSVError[20];
strSVError[0]      = "失步";
strSVError[1]      =  "丢包";
strSVError[2]      =  "重复" ;
strSVError[3]      =  "采样序号错";
strSVError[4]      =  "长度参数错";
strSVError[5]      = "APDU编码错";
strSVError[6]      =  "ASDU编码错";
strSVError[7]      =  "超时" ;
strSVError[8]      =  "抖动";
strSVError[9]      =  "通信中断";
strSVError[10]      = "通信恢复";
strSVError[11]      =  "品质异常";
strSVError[12]      =  "采样无效" ;
strSVError[13]      =  "检修状态";
strSVError[14]      =  "通道延时改变";
strSVError[15]      =  "ASDU数目改变";
strSVError[16]      =  "双A/D采样不一致";
strSVError[17]      =  "非法SMV的异常报文";

*/

//void ep_n64_time_to_ctime(__int64 &n64Time, CTime &time)
//{
//	BYTE byTime[8];
//	//::memset(byTime,  0x0, 8);
//	::memcpy(byTime,  &n64Time,   8);

//	BYTE t4 =  byTime[0];
//	BYTE t3 =  byTime[1];
//	BYTE t2 =  byTime[2];
//	BYTE t1 =  byTime[3];
//	BYTE t8 =  byTime[4];
//	BYTE t7 =  byTime[5];
//	BYTE t6 =  byTime[6];
//	BYTE t5 =  byTime[7];

//	//double   usTime1    =   t4  +             t3  *  pow(2.0,  8)    +  t2  *  pow(2.0,  16)      +  t1  *  pow(2.0,  24);
//	double     usTime1    =   byTime[0]  +  byTime[1]  *  256.0  +  byTime[2]  *  65536.0  +  byTime[3]  *  16777216.0;
//	//double  Time1 =   t8               +  t7 *  pow(2.0,   8)   +   t6   *   pow(2.0,   16)     +  t5  *  pow(2.0,  24);
//	double     Time1 =   byTime[4]   +  byTime[5] *  256.0  +   byTime[6]   *   65536.0  +  byTime[7]  *  16777216.0;
//	time = (CTime)(int)Time1;
//}

double g_dGSSync[50] = {0};


void ep_protocol_analysis92(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult,long *pnChType,long *pnChAngType)
{
	//SMV判断异常
	//当是第一帧的时候不做比较，直接返回，第一帧的标识就是==0
	if (pPrevData->nFirstPacket==0)
	{
		return;
	}

	//提高效率，增加临时变量
	EP_ANALYSIS_RESULT_92 *p_rslt_92 = &pResult->rslt_92;
	EP92PARSEDATA *pData92 = &pDatas->oData92;

	//pPrevData->oData92.nFirstPacket    =  1;
	int nIndexAsdu = 0;
    int nMaxSmpCnt   = 3999;
	int nCurASDUCnt = pData92->Num_ASDU;
	p_rslt_92->nAsduCnt   =   nCurASDUCnt;

	//默认最大的采样帧数为3999;
	//asdu参数如果是小于等于0，则认为ASDU编码错误；
	if (nCurASDUCnt <= 0)
	{
		p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_ASDUCodeErr] += 1;
		pResult->nErrorFlag = 1;
	}

	//APDU参数如果是小于等于0，则认为APDU编码错误；
	if (pData92->APDULen <= 0)
	{
		p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_APDUCodeErr] += 1;
		pResult->nErrorFlag = 1;
	}

	if (pData92->Num_ASDU != pPrevData->oData92.Num_ASDU)//zhouhj 20230708
	{
		p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_ASDUNumChanged] += 1;
	}

	for (nIndexAsdu = 0;  nIndexAsdu  < nCurASDUCnt ; nIndexAsdu++)
	{
		int nPreSmpCnt = pPrevData->oData92.Asdu[nIndexAsdu].smpCnt;
		int nCurSmpCnt = pData92->Asdu[nIndexAsdu].smpCnt;

		//若两者相等则认为没有丢包；
		if (nCurSmpCnt  -  nPreSmpCnt == nCurASDUCnt )//不丢包；
		{

		}
		else 
		{
			if ((nCurSmpCnt  + nPreSmpCnt + 1) % 4000==0)//不丢包,这里的意思就是3999，变到0的时候，认为不丢包；
			{
			}
			else 
			{
				if (nPreSmpCnt  -  nCurSmpCnt  !=  nMaxSmpCnt)
				{	
					if (nCurSmpCnt   -   nPreSmpCnt == 0 )//重复
					{
						p_rslt_92->nErrorType[nIndexAsdu][Cap_Smv92Error_Repeat]  += 1;	
						pResult->nErrorFlag = 1;	
					}
					else if (nCurSmpCnt   -   nPreSmpCnt <= 0 )//错序
					{
						p_rslt_92->nErrorType[nIndexAsdu][Cap_Smv92Error_NumErr]  += 1;	
						pResult->nErrorFlag = 1;	
					}
					else //丢包
					{
						p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_Loss] += 1;
//   						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("出现丢帧,SmpCnt(%d)(%d)差值%ld,AppID(%d)(%d),Time(%llX)(%llX)."),
//   							nPreSmpCnt,nCurSmpCnt,(nCurSmpCnt-nPreSmpCnt),pPrevData->APPID,pDatas->APPID,pPrevData->n64Time,pDatas->n64Time
//   							);
						pResult->nErrorFlag = 1;
					}
				}
			}
		}

		//丢失同步信号；
		int nSmpSynch   =   pData92->Asdu[nIndexAsdu].smpSynch;
		if (nSmpSynch==0)
		{
			p_rslt_92->nErrorType[nIndexAsdu][Cap_Smv92Error_LoseSyn] += 1;	
			pResult->nErrorFlag = 1;	
		}

		//品质异常；
		int   nChCnt   =  pData92->nChCount;   //获取通道数量；
		bool bHasQualityErr = false,bHasADError = false,bHasTestStatus = false,bHasSVInvalid = false;
	
		for (int nIndex = 0;  nIndex  <  nChCnt;  nIndex++)
		{
			if ((nIndex>0)&&(!bHasADError))//从第2个通道开始,与前一个通道比较,通道类型和通道相位类型相同
			{
				if ((pnChType[nIndex] == pnChType[nIndex-1])&&(pnChAngType[nIndex] == pnChAngType[nIndex-1])
					&&(pnChAngType[nIndex]<3))
				{

					//,但数值不同,则双AD不一致
					if ((pDatas->pDatas[nIndex].dwValue != pDatas->pDatas[nIndex-1].dwValue))
					{
						double dDiffValue = abs(pDatas->pDatas[nIndex].dwValue - pDatas->pDatas[nIndex-1].dwValue);//双AD的差值绝对值
						double dMaxValue = abs(pDatas->pDatas[nIndex].dwValue);

						if (dMaxValue < abs(pDatas->pDatas[nIndex-1].dwValue))//两个AD大值中的较大的值
						{
							dMaxValue = abs(pDatas->pDatas[nIndex-1].dwValue);
						}

						if ((dMaxValue > 0.001f)&&((dDiffValue/dMaxValue) > 0.2f))//双AD差值与其中最大值的比率值大于阈值0.2时,认定为双AD不一致
						{
							p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_ADIncstc] += 1;
							bHasADError = true;
						}
					}
				}
			}

			//通道为延时通道时,与前一个比较,如果不一致则延时改变
			if (pnChType[nIndex] == 2/*CAPDEVICE_CHTYPE_T*/)
			{
				if (pDatas->pDatas[nIndex].dwValue != pPrevData->pDatas[nIndex].dwValue)
				{
					p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_DelayChanged] += 1;
				}
			}

			if (pDatas->pDatas[nIndex].dwValue2 != 0)  //2022-6-19  lijunqing 四个字节进行判断，等效于直接使用dwValue2进行判断
			{
				//zhouhj 2023.9.9 检修状态不按通道标记,按报文帧统计
				if ((pDatas->pDatas[nIndex].dwValue2 & 0x0800)&&(!bHasTestStatus))
				{
					p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_TestStatus] += 1;
					bHasTestStatus = true;
				}

				//zhouhj 2023.9.9 品质无效不按通道标记,按报文帧统计
				if ((pDatas->pDatas[nIndex].dwValue2 & 0x0001)&&(!bHasSVInvalid))
				{
					p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_SVInvalid] += 1;
					bHasSVInvalid = true;
				}

				if (!bHasQualityErr)
				{
					if ((pDatas->pDatas[nIndex].dwValue2 != 0x0800)&&(pDatas->pDatas[nIndex].dwValue2 != 0))
					{
						p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_QualityErr] += 1;
						pResult->nErrorFlag = 1;	
						bHasQualityErr = true;
					}
				}
			}
		}
	}	

/*
	//2022-6-19 lijunqing 简化计算，发现time, time2;没有用到
	CTime time, time2;
	ep_n64_time_to_ctime(pPrevData->n64Time, time);
	ep_n64_time_to_ctime(pDatas->n64Time, time2);
*/

// 	__int64 nCur = (pDatas->n64Time >> 32) * 1000000000 + (pDatas->n64Time & 0xFFFFFFFF);
// 	__int64 nPre = (pPrevData->n64Time >> 32) * 1000000000 + (pPrevData->n64Time & 0xFFFFFFFF);
//	__int64 nTimeRel_NS = nCur - nPre;//n64Time对应时间为ns,nTimeRel对应时间为μs,故此处除以1000

	double dDeltN =  GetTimeGap_EpcapBufferItem(pDatas->n64Time,pPrevData->n64Time,FALSE);/*nTimeRel_NS*/;//ep_tm_n64_sub(pDatas->n64Time ,pPrevData->n64Time)*1000000000;//这里换算成纳秒；
	int nPreSmpCnt = pPrevData->oData92.Asdu[0].smpCnt;
	int nCurSmpCnt = pData92->Asdu[0].smpCnt;

	if (((nCurSmpCnt==0)&&(nPreSmpCnt==3999))||((nCurSmpCnt  -  nPreSmpCnt)==1))
	{
		pResult->dDeltTime  = dDeltN - 250000.0f;	

		if (fabs(pResult->dDeltTime)   >  1000.0f)//大于正负1 us 算作抖动
		{
			p_rslt_92->nErrorType[0][Cap_Smv92Error_Shake] += 1;
		}
	}
// 	else 
// 	{	
// 		double dDelt  = 0;
// 		dDelt  = dDeltN -  250000;//同样减去的单位也是纳秒；
// 
// 		if (abs((long)dDelt)   >  1000)//大于正负10 us 算作抖动 0.2us 
// 		{
// 			p_rslt_92->nErrorType[0][Cap_Smv92Error_Shake] += 1;
// 		}
// 
// 		//这里只考虑不丢包的情况
//         if (fabs((double)pResult->dDeltTime)   <=  fabs((double)dDelt)  && (nCurSmpCnt  -  nPreSmpCnt)==1)
// 		{		
// 			pResult->dDeltTime  = dDelt;	
// 		}
// 	}
}

/*
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

以如下为准；
strGSError[0]  =  "虚变位";
strGSError[1]  =  "sqNum丢失";
strGSError[2]  =  "sqNum初值错误";
strGSError[3]  =  "sqNum错序";
strGSError[4]  =  "sqNum重复";
strGSError[5]  =  "stNum丢失";
strGSError[6]  =  "装置重启";
strGSError[7]  =  "stNum错序";
strGSError[8]  =  "APDU编码错";
strGSError[9]  =  "ASDU编码错";
strGSError[10]  =  "长度参数错";
strGSError[11]  =  "超时";
strGSError[12]  =  "通信中断";
strGSError[13]  =  "通讯恢复";
strGSError[14]  =  "存活时间无效";
strGSError[15]  =  "时钟故障";
strGSError[16]  =  "时钟未同步";
strGSError[17]  =   "非法GOOSE的次数和状态";
*/
long GetData_0x83_0x84(int nType, DWORD dwValue)
{   
	long nRet = 0;

	if (nType==0x83)
	{
		nRet = dwValue;
		return  nRet ;
	}
	else if (nType==0x84)
	{
	}

	short nTemp =  dwValue;
	CString strMy;
	CString strMyTemp;
	int  nSubLen   =  (nTemp  & 0xff00)>>8;
	int  nLength =  (nTemp & 0x00ff); // 这里获得了差值，就是最低的那nDeltValue位不要了，抹去；
	BYTE byTemp[80] = {0};
	::memcpy(byTemp, &nTemp, 2);
	byTemp[0] = nLength;
	byTemp[1] = nSubLen;

	for (int i = 0 ;i < 1;i++)
	{
		strMyTemp.Format(_T("%.2X"), byTemp[0]);
		strMy += strMyTemp;
	}

	CString str_Bin = HexToBin(strMy);
	int t_RL = str_Bin.GetLength();
	int nValueLength = nLength;
	nValueLength = 2;

	for (int i = t_RL; i < (nValueLength - 1) * 8; i++)
		str_Bin.Insert(0, '0');

	CString strResult;
	strResult = str_Bin.Mid(0, str_Bin.GetLength() - nSubLen);
	int adf = 0;

	if (strResult=="01")
		nRet  = 0;
	else if (strResult=="10")
		nRet  = 1;

	return nRet;
}

void ep_protocol_analysisGS(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas,  PEP_ANALYSIS_RESULT pResult)
{
	//怎么能知道是第一帧，目前还不清楚如何判断，
	if (pPrevData->nFirstPacket==0)
		return;
	//pPrevData->oDataGs.nFirstPacket = 1;


	//结果结构体中存储当前帧的时间值；
	pResult->n64Time = pDatas->n64Time;

	//GOOSE判断异常；
	int nChIndex = 0;	

	// 变位的情况下如下判断；
	// 不等于0表示有变位
	int  nCompRet = 0/* = memcmp(pPrevData->oDataGs.chData , pDatas->oDataGs.chData,  pDatas->oDataGs.nChCnt  *  sizeof(EPGOOSECHDATA))*/;
//	nCompRet = 0;
	for (int nChIndex = 0;  nChIndex <  pDatas->oDataGs.nChCnt ;  nChIndex++)
	{
		//时间通道不参与比较;
		if (pPrevData->oDataGs.chData[nChIndex].wChType != 0x91)
		{
			if (pPrevData->oDataGs.chData[nChIndex].dwValue  != pDatas->oDataGs.chData[nChIndex].dwValue)
			{
				nCompRet = 1;
				break;
			}
		}
	}

	//PNI302  mym 2020-11-02 add;
	//查找出变位的具体通道；当通道是BOOL 或者双位置节点的时候根据前后两帧来判断是否变位，由FASLE---》TRUE；
	if (pDatas->oDataGs.nChCnt > GSCHANNEL_CNT)
		pDatas->oDataGs.nChCnt  = GSCHANNEL_CNT;
	for (int nChIndex = 0;  nChIndex <  pDatas->oDataGs.nChCnt ;  nChIndex++)
	{
		//当是BOOL量的时候，前一帧是FALSE，后一帧是TRUE的时候表示则是变位；
		if (pPrevData->oDataGs.chData[nChIndex].wChType == 0x83||pPrevData->oDataGs.chData[nChIndex].wChType == 0x84)
		{
			long nPrevData = GetData_0x83_0x84(pPrevData->oDataGs.chData[nChIndex].wChType, pPrevData->oDataGs.chData[nChIndex].dwValue);
			long nCurData = GetData_0x83_0x84(pDatas->oDataGs.chData[nChIndex].wChType,  pDatas->oDataGs.chData[nChIndex].dwValue);

			pResult->nChnnelType[nChIndex]  = pDatas->oDataGs.chData[nChIndex].wChType;

			// mym 2021-4-1 把后面==0的判断注销掉
			if (nPrevData == 0 && nCurData == 1 && pResult->nChangeFlag[nChIndex]==0)//获取一次就行了；
			{
				pResult->nChangeBit[nChIndex]  = 1;
				pResult->nChangeFlag[nChIndex] = 1;
				pResult->nCurChnel  =  nChIndex;
			}
		}
	}

	if ( nCompRet != 0)
	{
		// 变位的情况下如下判断；
		//SqNO初值错误
		if ( pDatas->oDataGs.sqNO   !=   0)
		{
			pResult->nErrorFlag  = 1;
			pResult->rslt_gs.nErrorType [Cap_GsError_SQNumInitError] += 1;
		}
		else 
		{
			// 变位的情况下这样判断;
			//变位   ///这里后来改的暂时定位虚变位；
// 			if ( pDatas->oDataGs.stNO   -   pPrevData->oDataGs.stNO <= 1)//20220624 zhouhj此处为正常变位 不需要记录
// 			{
// 				pResult->nErrorFlag  =  1;
// 				pResult->rslt_gs.nErrorType [0]  += 1;
// 			}
		}
	}

	//装置重启
	if (pDatas->oDataGs.sqNO==1  &&  pDatas->oDataGs.stNO == 1)
	{
		pResult->nErrorFlag  =  1;
		pResult->rslt_gs.nErrorType [Cap_GsError_DevRestart]  += 1;
	}
	else
		{
	//StNum 错误
	if ((pDatas->oDataGs.stNO - pPrevData->oDataGs.stNO)  > 1)
	{
		pResult->nErrorFlag  =  1;
		pResult->rslt_gs.nErrorType[Cap_GsError_STNumLoss]  += 1;
	}
	else if (pDatas->oDataGs.stNO < pPrevData->oDataGs.stNO)
	{
		pResult->nErrorFlag  =  1;
		pResult->rslt_gs.nErrorType[Cap_GsError_STNumDisorder]  += 1;
	}

	//SqNO 重复 
	if ( pDatas->oDataGs.sqNO == pPrevData->oDataGs.sqNO )
	{
		pResult->nErrorFlag  = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_SQNumRepeat]  += 1;
	}
	else if ((pDatas->oDataGs.sqNO - pPrevData->oDataGs.sqNO)  > 1)//SqNO 丢失
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_SQNumLoss] += 1;
	}
	else if ((pDatas->oDataGs.sqNO < pPrevData->oDataGs.sqNO)&&(pDatas->oDataGs.sqNO > 0))//SqNO 错序
	{
		pResult->nErrorFlag = 1;
			pResult->rslt_gs.nErrorType [Cap_GsError_SQNumDisorder] += 1;
		}
	}
	
	//虚变位
	if (/*pDatas->oDataGs.sqNO  ==  0  &&*/  (pDatas->oDataGs.stNO   -  pPrevData->oDataGs.stNO) == 1)
	{
		if (nCompRet==0)//而且当前数据集和前一帧的数据集相等则判为虚变位；
		{
			pResult->nErrorFlag  =  1;
			pResult->rslt_gs.nErrorType [Cap_GsError_DummyBit]  += 1;//20220624 zhouhj 虚变位为0不是2 修改为0 
		}	
	}

	//GOOSE生存时间为0
	if ( pDatas->oDataGs.TimeAllowedToLive  ==  0)
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_LivingTimeInvalid] += 1;
	}

	//GOOSE 延时
	if (((pDatas->oDataGs.EventTimeSample - pPrevData->oDataGs.EventTimeSample) > pDatas->oDataGs.TimeAllowedToLive) &&
		((pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample) < (2 * pDatas->oDataGs.TimeAllowedToLive)))
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_TimeOut]  += 1;
	}

	//GOOSE 中断 
	if ((pDatas->oDataGs.EventTimeSample -  pPrevData->oDataGs.EventTimeSample) >=  2 * pDatas->oDataGs.TimeAllowedToLive )
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_CommLoss] += 1;
		//goto  SAVE;
	}

	//时钟未同步
	if ( pDatas->oDataGs.ClockFlag== 0x2a )
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_ClockNotSyn] += 1;
	}
	else if (pDatas->oDataGs.ClockFlag== 0x4a )
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_ClockFault] += 1;
	}
}


//////////////////////////////////////////////////////////////////////////
//
CEpGooseBinaryTurns::CEpGooseBinaryTurns()
{
	m_nCurrReadIndex = 0;
}

CEpGooseBinaryTurns::~CEpGooseBinaryTurns()
{

}

PEP_GOOSE_BINARY_TURN CEpGooseBinaryTurns::FindPrevTurn(PEP_GOOSE_BINARY_TURN pCurr)
{
	POS pos = Find(pCurr);
	GetPrev(pos);
	PEP_GOOSE_BINARY_TURN p = NULL, pFind = NULL;

	while (pos != NULL)
	{
		p = GetPrev(pos);

		if (p->nChIndex == pCurr->nChIndex)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CEpGooseBinaryTurns::CalTimeRel(PEP_GOOSE_BINARY_TURN pPrev,PEP_GOOSE_BINARY_TURN pCurr)
{
	if (pPrev == NULL)
	{
		pCurr->nTimeRel = 0;
	}
	else
	{
		__int64 nCur = (pCurr->n64Time >> 32) * 1000000000 + (pCurr->n64Time & 0xFFFFFFFF);
		__int64 nPre = (pPrev->n64Time >> 32) * 1000000000 + (pPrev->n64Time & 0xFFFFFFFF);
		pCurr->nTimeRel = (nCur - nPre) / 1000;//n64Time对应时间为ns,nTimeRel对应时间为μs,故此处除以1000
	}
}

void CEpGooseBinaryTurns::CalTimeRel(PEP_GOOSE_BINARY_TURN pCurr)
{
	PEP_GOOSE_BINARY_TURN pPrev =FindPrevTurn(pCurr);
	CalTimeRel(pPrev,pCurr);
}

void CEpGooseBinaryTurns::Reset()
{
	DeleteAll();
	m_nCurrReadIndex = 0;
}

PEP_GOOSE_BINARY_TURN CEpGooseBinaryTurns::New()
{
	PEP_GOOSE_BINARY_TURN pNew = new EP_GOOSE_BINARY_TURN;
	AddTail(pNew);
	return pNew;
}

void ep_get_CapParseData_value(DWORD nChType,DWORD nChLenth, DWORD nValue, DWORD nValue2, CString&strValue)
{
	switch(nChType)
	{
	case 0x83:   //单点
		strValue.Format(_T("%d"), nValue);
		break;
	case 0x85://枚举
		strValue.Format(_T("%d"), nValue);
		break;
	case 0x86://UINT
		strValue.Format(_T("%lu"), nValue);
		break;
	case 0x91://时间
		struct timeval ts;
		EPTIME64EX tm;
		ts.tv_sec = nValue;   //秒
		ts.tv_usec = nValue2 / 1000;  //ns ==>> us
		ep_cap_timeval_to_64timeex(ts, tm);
		Ep_EPTIME64Ex_To_String(tm, strValue);
		break;
	case 0x87://浮点
	case 0x8A:
		{
			float fValue = 0;
			memcpy(&fValue,&nValue,sizeof(float));
			strValue.Format(_T("%.3f"), fValue);
			break;
		}
	case 0x84://双点

		if (nChLenth == 2)//2字节长度为双点
		{
			long nPosLenth = ((nValue>>8)&0x7);
			strValue = _T("");

			for (int nIndex = 7;nIndex>=nPosLenth;nIndex--)
			{
				strValue.AppendFormat("%d",((nValue>>nIndex)&0x01));
			}
		}
		else if (nChLenth == 3)//3字节长度为品质
		{
			long nPosLenth = ((nValue>>8)&0xF);
			strValue = _T("");

			for (int nIndex = 15;nIndex>=nPosLenth;nIndex--)
			{
				strValue.AppendFormat("%d",((nValue>>nIndex)&0x01));
			}
		}
		else
		{
			long nMaxLenth = (nChLenth-1)*8 - 1;
			long nNewValue = 0;

			for (int nIndex = nMaxLenth;nIndex>=0;nIndex--)
			{
				nNewValue += ((nValue>>nIndex)&0x01)<<(nMaxLenth-nIndex);
			}

			strValue.Format("%lu",nNewValue);
		}
		
		break;
	default:
		strValue.Format(_T("%d"), nValue);
		break;
	}
}

void ep_get_CapParseData_value(EPCAPPARSEDATA &oChData, CString&strValue)
{
	ep_get_CapParseData_value(oChData.wChType,oChData.wLength, oChData.dwValue, oChData.dwValue2, strValue);
}

