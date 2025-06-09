#include "stdafx.h"
#include "Protocol61850Analysis.h"

#include <math.h>

//2022-11-13  lijunqing
//vector <EP_ANALYSIS_RESULT> g_AnalysisResult;
/*
�����ƿ���9-2ʱ��
nErrorType�Ǹ�����  Ĭ��ֵΪ0��������1ʱ���ʾ�д���
��1��Ԫ�ر�ʾ ����
��2��Ԫ�ر�ʾ ����
��3��Ԫ�ر�ʾ ʧ��
��4��Ԫ�ر�ʾ Ʒ���쳣
��5��Ԫ�ر�ʾ ����

CString strSVError[20];
strSVError[0]      = "ʧ��";
strSVError[1]      =  "����";
strSVError[2]      =  "�ظ�" ;
strSVError[3]      =  "������Ŵ�";
strSVError[4]      =  "���Ȳ�����";
strSVError[5]      = "APDU�����";
strSVError[6]      =  "ASDU�����";
strSVError[7]      =  "��ʱ" ;
strSVError[8]      =  "����";
strSVError[9]      =  "ͨ���ж�";
strSVError[10]      = "ͨ�Żָ�";
strSVError[11]      =  "Ʒ���쳣";
strSVError[12]      =  "������Ч" ;
strSVError[13]      =  "����״̬";
strSVError[14]      =  "ͨ����ʱ�ı�";
strSVError[15]      =  "ASDU��Ŀ�ı�";
strSVError[16]      =  "˫A/D������һ��";
strSVError[17]      =  "�Ƿ�SMV���쳣����";

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
	//SMV�ж��쳣
	//���ǵ�һ֡��ʱ�����Ƚϣ�ֱ�ӷ��أ���һ֡�ı�ʶ����==0
	if (pPrevData->nFirstPacket==0)
	{
		return;
	}

	//���Ч�ʣ�������ʱ����
	EP_ANALYSIS_RESULT_92 *p_rslt_92 = &pResult->rslt_92;
	EP92PARSEDATA *pData92 = &pDatas->oData92;

	//pPrevData->oData92.nFirstPacket    =  1;
	int nIndexAsdu = 0;
    int nMaxSmpCnt   = 3999;
	int nCurASDUCnt = pData92->Num_ASDU;
	p_rslt_92->nAsduCnt   =   nCurASDUCnt;

	//Ĭ�����Ĳ���֡��Ϊ3999;
	//asdu���������С�ڵ���0������ΪASDU�������
	if (nCurASDUCnt <= 0)
	{
		p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_ASDUCodeErr] += 1;
		pResult->nErrorFlag = 1;
	}

	//APDU���������С�ڵ���0������ΪAPDU�������
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

		//�������������Ϊû�ж�����
		if (nCurSmpCnt  -  nPreSmpCnt == nCurASDUCnt )//��������
		{

		}
		else 
		{
			if ((nCurSmpCnt  + nPreSmpCnt + 1) % 4000==0)//������,�������˼����3999���䵽0��ʱ����Ϊ��������
			{
			}
			else 
			{
				if (nPreSmpCnt  -  nCurSmpCnt  !=  nMaxSmpCnt)
				{	
					if (nCurSmpCnt   -   nPreSmpCnt == 0 )//�ظ�
					{
						p_rslt_92->nErrorType[nIndexAsdu][Cap_Smv92Error_Repeat]  += 1;	
						pResult->nErrorFlag = 1;	
					}
					else if (nCurSmpCnt   -   nPreSmpCnt <= 0 )//����
					{
						p_rslt_92->nErrorType[nIndexAsdu][Cap_Smv92Error_NumErr]  += 1;	
						pResult->nErrorFlag = 1;	
					}
					else //����
					{
						p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_Loss] += 1;
//   						CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("���ֶ�֡,SmpCnt(%d)(%d)��ֵ%ld,AppID(%d)(%d),Time(%llX)(%llX)."),
//   							nPreSmpCnt,nCurSmpCnt,(nCurSmpCnt-nPreSmpCnt),pPrevData->APPID,pDatas->APPID,pPrevData->n64Time,pDatas->n64Time
//   							);
						pResult->nErrorFlag = 1;
					}
				}
			}
		}

		//��ʧͬ���źţ�
		int nSmpSynch   =   pData92->Asdu[nIndexAsdu].smpSynch;
		if (nSmpSynch==0)
		{
			p_rslt_92->nErrorType[nIndexAsdu][Cap_Smv92Error_LoseSyn] += 1;	
			pResult->nErrorFlag = 1;	
		}

		//Ʒ���쳣��
		int   nChCnt   =  pData92->nChCount;   //��ȡͨ��������
		bool bHasQualityErr = false,bHasADError = false,bHasTestStatus = false,bHasSVInvalid = false;
	
		for (int nIndex = 0;  nIndex  <  nChCnt;  nIndex++)
		{
			if ((nIndex>0)&&(!bHasADError))//�ӵ�2��ͨ����ʼ,��ǰһ��ͨ���Ƚ�,ͨ�����ͺ�ͨ����λ������ͬ
			{
				if ((pnChType[nIndex] == pnChType[nIndex-1])&&(pnChAngType[nIndex] == pnChAngType[nIndex-1])
					&&(pnChAngType[nIndex]<3))
				{

					//,����ֵ��ͬ,��˫AD��һ��
					if ((pDatas->pDatas[nIndex].dwValue != pDatas->pDatas[nIndex-1].dwValue))
					{
						double dDiffValue = abs(pDatas->pDatas[nIndex].dwValue - pDatas->pDatas[nIndex-1].dwValue);//˫AD�Ĳ�ֵ����ֵ
						double dMaxValue = abs(pDatas->pDatas[nIndex].dwValue);

						if (dMaxValue < abs(pDatas->pDatas[nIndex-1].dwValue))//����AD��ֵ�еĽϴ��ֵ
						{
							dMaxValue = abs(pDatas->pDatas[nIndex-1].dwValue);
						}

						if ((dMaxValue > 0.001f)&&((dDiffValue/dMaxValue) > 0.2f))//˫AD��ֵ���������ֵ�ı���ֵ������ֵ0.2ʱ,�϶�Ϊ˫AD��һ��
						{
							p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_ADIncstc] += 1;
							bHasADError = true;
						}
					}
				}
			}

			//ͨ��Ϊ��ʱͨ��ʱ,��ǰһ���Ƚ�,�����һ������ʱ�ı�
			if (pnChType[nIndex] == 2/*CAPDEVICE_CHTYPE_T*/)
			{
				if (pDatas->pDatas[nIndex].dwValue != pPrevData->pDatas[nIndex].dwValue)
				{
					p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_DelayChanged] += 1;
				}
			}

			if (pDatas->pDatas[nIndex].dwValue2 != 0)  //2022-6-19  lijunqing �ĸ��ֽڽ����жϣ���Ч��ֱ��ʹ��dwValue2�����ж�
			{
				//zhouhj 2023.9.9 ����״̬����ͨ�����,������֡ͳ��
				if ((pDatas->pDatas[nIndex].dwValue2 & 0x0800)&&(!bHasTestStatus))
				{
					p_rslt_92->nErrorType[nIndexAsdu] [Cap_Smv92Error_TestStatus] += 1;
					bHasTestStatus = true;
				}

				//zhouhj 2023.9.9 Ʒ����Ч����ͨ�����,������֡ͳ��
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
	//2022-6-19 lijunqing �򻯼��㣬����time, time2;û���õ�
	CTime time, time2;
	ep_n64_time_to_ctime(pPrevData->n64Time, time);
	ep_n64_time_to_ctime(pDatas->n64Time, time2);
*/

// 	__int64 nCur = (pDatas->n64Time >> 32) * 1000000000 + (pDatas->n64Time & 0xFFFFFFFF);
// 	__int64 nPre = (pPrevData->n64Time >> 32) * 1000000000 + (pPrevData->n64Time & 0xFFFFFFFF);
//	__int64 nTimeRel_NS = nCur - nPre;//n64Time��Ӧʱ��Ϊns,nTimeRel��Ӧʱ��Ϊ��s,�ʴ˴�����1000

	double dDeltN =  GetTimeGap_EpcapBufferItem(pDatas->n64Time,pPrevData->n64Time,FALSE);/*nTimeRel_NS*/;//ep_tm_n64_sub(pDatas->n64Time ,pPrevData->n64Time)*1000000000;//���ﻻ������룻
	int nPreSmpCnt = pPrevData->oData92.Asdu[0].smpCnt;
	int nCurSmpCnt = pData92->Asdu[0].smpCnt;

	if (((nCurSmpCnt==0)&&(nPreSmpCnt==3999))||((nCurSmpCnt  -  nPreSmpCnt)==1))
	{
		pResult->dDeltTime  = dDeltN - 250000.0f;	

		if (fabs(pResult->dDeltTime)   >  1000.0f)//��������1 us ��������
		{
			p_rslt_92->nErrorType[0][Cap_Smv92Error_Shake] += 1;
		}
	}
// 	else 
// 	{	
// 		double dDelt  = 0;
// 		dDelt  = dDeltN -  250000;//ͬ����ȥ�ĵ�λҲ�����룻
// 
// 		if (abs((long)dDelt)   >  1000)//��������10 us �������� 0.2us 
// 		{
// 			p_rslt_92->nErrorType[0][Cap_Smv92Error_Shake] += 1;
// 		}
// 
// 		//����ֻ���ǲ����������
//         if (fabs((double)pResult->dDeltTime)   <=  fabs((double)dDelt)  && (nCurSmpCnt  -  nPreSmpCnt)==1)
// 		{		
// 			pResult->dDeltTime  = dDelt;	
// 		}
// 	}
}

/*
�����ƿ���GOOSEʱ��
nGSErrorType�Ǹ�����  Ĭ��ֵΪ0��������1ʱ���ʾ�д���
��1��Ԫ�ر�ʾ ״̬�ı�/StNO��ʧ
��2��Ԫ�ر�ʾ װ������ 
��3��Ԫ�ر�ʾ ���λ 
��4��Ԫ�ر�ʾ StNum ����
��5��Ԫ�ر�ʾ ״̬�ı�
��6��Ԫ�ر�ʾ SqNO �ظ�
��7��Ԫ�ر�ʾ SqNO ��ʧ
��8��Ԫ�ر�ʾ GOOSE����ʱ��Ϊ0
��9��Ԫ�ر�ʾ SqNO��ֵ����
��10��Ԫ�ر�ʾ GOOSE ��ʱ
��11��Ԫ�ر�ʾ GOOSE �ж�
��12��Ԫ�ر�ʾ ʱ��δͬ��

������Ϊ׼��
strGSError[0]  =  "���λ";
strGSError[1]  =  "sqNum��ʧ";
strGSError[2]  =  "sqNum��ֵ����";
strGSError[3]  =  "sqNum����";
strGSError[4]  =  "sqNum�ظ�";
strGSError[5]  =  "stNum��ʧ";
strGSError[6]  =  "װ������";
strGSError[7]  =  "stNum����";
strGSError[8]  =  "APDU�����";
strGSError[9]  =  "ASDU�����";
strGSError[10]  =  "���Ȳ�����";
strGSError[11]  =  "��ʱ";
strGSError[12]  =  "ͨ���ж�";
strGSError[13]  =  "ͨѶ�ָ�";
strGSError[14]  =  "���ʱ����Ч";
strGSError[15]  =  "ʱ�ӹ���";
strGSError[16]  =  "ʱ��δͬ��";
strGSError[17]  =   "�Ƿ�GOOSE�Ĵ�����״̬";
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
	int  nLength =  (nTemp & 0x00ff); // �������˲�ֵ��������͵���nDeltValueλ��Ҫ�ˣ�Ĩȥ��
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
	//��ô��֪���ǵ�һ֡��Ŀǰ�����������жϣ�
	if (pPrevData->nFirstPacket==0)
		return;
	//pPrevData->oDataGs.nFirstPacket = 1;


	//����ṹ���д洢��ǰ֡��ʱ��ֵ��
	pResult->n64Time = pDatas->n64Time;

	//GOOSE�ж��쳣��
	int nChIndex = 0;	

	// ��λ������������жϣ�
	// ������0��ʾ�б�λ
	int  nCompRet = 0/* = memcmp(pPrevData->oDataGs.chData , pDatas->oDataGs.chData,  pDatas->oDataGs.nChCnt  *  sizeof(EPGOOSECHDATA))*/;
//	nCompRet = 0;
	for (int nChIndex = 0;  nChIndex <  pDatas->oDataGs.nChCnt ;  nChIndex++)
	{
		//ʱ��ͨ��������Ƚ�;
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
	//���ҳ���λ�ľ���ͨ������ͨ����BOOL ����˫λ�ýڵ��ʱ�����ǰ����֡���ж��Ƿ��λ����FASLE---��TRUE��
	if (pDatas->oDataGs.nChCnt > GSCHANNEL_CNT)
		pDatas->oDataGs.nChCnt  = GSCHANNEL_CNT;
	for (int nChIndex = 0;  nChIndex <  pDatas->oDataGs.nChCnt ;  nChIndex++)
	{
		//����BOOL����ʱ��ǰһ֡��FALSE����һ֡��TRUE��ʱ���ʾ���Ǳ�λ��
		if (pPrevData->oDataGs.chData[nChIndex].wChType == 0x83||pPrevData->oDataGs.chData[nChIndex].wChType == 0x84)
		{
			long nPrevData = GetData_0x83_0x84(pPrevData->oDataGs.chData[nChIndex].wChType, pPrevData->oDataGs.chData[nChIndex].dwValue);
			long nCurData = GetData_0x83_0x84(pDatas->oDataGs.chData[nChIndex].wChType,  pDatas->oDataGs.chData[nChIndex].dwValue);

			pResult->nChnnelType[nChIndex]  = pDatas->oDataGs.chData[nChIndex].wChType;

			// mym 2021-4-1 �Ѻ���==0���ж�ע����
			if (nPrevData == 0 && nCurData == 1 && pResult->nChangeFlag[nChIndex]==0)//��ȡһ�ξ����ˣ�
			{
				pResult->nChangeBit[nChIndex]  = 1;
				pResult->nChangeFlag[nChIndex] = 1;
				pResult->nCurChnel  =  nChIndex;
			}
		}
	}

	if ( nCompRet != 0)
	{
		// ��λ������������жϣ�
		//SqNO��ֵ����
		if ( pDatas->oDataGs.sqNO   !=   0)
		{
			pResult->nErrorFlag  = 1;
			pResult->rslt_gs.nErrorType [Cap_GsError_SQNumInitError] += 1;
		}
		else 
		{
			// ��λ������������ж�;
			//��λ   ///��������ĵ���ʱ��λ���λ��
// 			if ( pDatas->oDataGs.stNO   -   pPrevData->oDataGs.stNO <= 1)//20220624 zhouhj�˴�Ϊ������λ ����Ҫ��¼
// 			{
// 				pResult->nErrorFlag  =  1;
// 				pResult->rslt_gs.nErrorType [0]  += 1;
// 			}
		}
	}

	//װ������
	if (pDatas->oDataGs.sqNO==1  &&  pDatas->oDataGs.stNO == 1)
	{
		pResult->nErrorFlag  =  1;
		pResult->rslt_gs.nErrorType [Cap_GsError_DevRestart]  += 1;
	}
	else
		{
	//StNum ����
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

	//SqNO �ظ� 
	if ( pDatas->oDataGs.sqNO == pPrevData->oDataGs.sqNO )
	{
		pResult->nErrorFlag  = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_SQNumRepeat]  += 1;
	}
	else if ((pDatas->oDataGs.sqNO - pPrevData->oDataGs.sqNO)  > 1)//SqNO ��ʧ
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_SQNumLoss] += 1;
	}
	else if ((pDatas->oDataGs.sqNO < pPrevData->oDataGs.sqNO)&&(pDatas->oDataGs.sqNO > 0))//SqNO ����
	{
		pResult->nErrorFlag = 1;
			pResult->rslt_gs.nErrorType [Cap_GsError_SQNumDisorder] += 1;
		}
	}
	
	//���λ
	if (/*pDatas->oDataGs.sqNO  ==  0  &&*/  (pDatas->oDataGs.stNO   -  pPrevData->oDataGs.stNO) == 1)
	{
		if (nCompRet==0)//���ҵ�ǰ���ݼ���ǰһ֡�����ݼ��������Ϊ���λ��
		{
			pResult->nErrorFlag  =  1;
			pResult->rslt_gs.nErrorType [Cap_GsError_DummyBit]  += 1;//20220624 zhouhj ���λΪ0����2 �޸�Ϊ0 
		}	
	}

	//GOOSE����ʱ��Ϊ0
	if ( pDatas->oDataGs.TimeAllowedToLive  ==  0)
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_LivingTimeInvalid] += 1;
	}

	//GOOSE ��ʱ
	if (((pDatas->oDataGs.EventTimeSample - pPrevData->oDataGs.EventTimeSample) > pDatas->oDataGs.TimeAllowedToLive) &&
		((pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample) < (2 * pDatas->oDataGs.TimeAllowedToLive)))
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_TimeOut]  += 1;
	}

	//GOOSE �ж� 
	if ((pDatas->oDataGs.EventTimeSample -  pPrevData->oDataGs.EventTimeSample) >=  2 * pDatas->oDataGs.TimeAllowedToLive )
	{
		pResult->nErrorFlag = 1;
		pResult->rslt_gs.nErrorType [Cap_GsError_CommLoss] += 1;
		//goto  SAVE;
	}

	//ʱ��δͬ��
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
		pCurr->nTimeRel = (nCur - nPre) / 1000;//n64Time��Ӧʱ��Ϊns,nTimeRel��Ӧʱ��Ϊ��s,�ʴ˴�����1000
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
	case 0x83:   //����
		strValue.Format(_T("%d"), nValue);
		break;
	case 0x85://ö��
		strValue.Format(_T("%d"), nValue);
		break;
	case 0x86://UINT
		strValue.Format(_T("%lu"), nValue);
		break;
	case 0x91://ʱ��
		struct timeval ts;
		EPTIME64EX tm;
		ts.tv_sec = nValue;   //��
		ts.tv_usec = nValue2 / 1000;  //ns ==>> us
		ep_cap_timeval_to_64timeex(ts, tm);
		Ep_EPTIME64Ex_To_String(tm, strValue);
		break;
	case 0x87://����
	case 0x8A:
		{
			float fValue = 0;
			memcpy(&fValue,&nValue,sizeof(float));
			strValue.Format(_T("%.3f"), fValue);
			break;
		}
	case 0x84://˫��

		if (nChLenth == 2)//2�ֽڳ���Ϊ˫��
		{
			long nPosLenth = ((nValue>>8)&0x7);
			strValue = _T("");

			for (int nIndex = 7;nIndex>=nPosLenth;nIndex--)
			{
				strValue.AppendFormat("%d",((nValue>>nIndex)&0x01));
			}
		}
		else if (nChLenth == 3)//3�ֽڳ���ΪƷ��
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

