#include "stdafx.h"
#include "Protocol61850Analysis.h"

#include <math.h>

vector <EP_ANALYSIS_RESULT> g_AnalysisResult;
/*
�����ƿ���9-2ʱ��
nErrorType�Ǹ�����  Ĭ��ֵΪ0��������1ʱ���ʾ�д���
��1��Ԫ�ر�ʾ ����
��2��Ԫ�ر�ʾ ����
��3��Ԫ�ر�ʾ ʧ��
��4��Ԫ�ر�ʾ Ʒ���쳣
��5��Ԫ�ر�ʾ ����

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
*/

void ep_protocol_analysis92(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult)
{
	EP_ANALYSIS_RESULT AnalysisResult;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SMV�ж��쳣
	//���ǵ�һ֡��ʱ�����Ƚϣ�ֱ�ӷ��أ���һ֡�ı�ʶ����==0
	if (pPrevData->oData92.nFirst==0)
		return;
	pPrevData->oData92.nFirst = 1;
    int nMaxSmpCnt  = 4000;
	int nCurASDUCnt = pDatas->oData92.Num_ASDU;

    int nIndexAsdu = 0;
	//Ĭ�����Ĳ���֡��Ϊ3999;
	for (nIndexAsdu = 0;  nIndexAsdu  < nCurASDUCnt ; nIndexAsdu++)
	{
		int nPreSmpCnt = pPrevData->oData92.asdu[nIndexAsdu].smpCnt;
		int nCurSmpCnt = pDatas->oData92.asdu[nIndexAsdu].smpCnt;

		//�������������Ϊû�ж�����
		if (nCurSmpCnt  -  nPreSmpCnt == nCurASDUCnt )//��������
		{
		}
		else if ((nCurSmpCnt  + nPreSmpCnt + 1) % 4000==0)//������,�������˼����3999���䵽0��ʱ����Ϊ��������
		{
		}

		if (nPreSmpCnt  -  nCurSmpCnt  !=  nMaxSmpCnt)
		{	
			if (nCurSmpCnt   -   nPreSmpCnt <= 0 )//����
			{
				AnalysisResult.rslt_92.nErrorType[nIndexAsdu][1]  = 1;	
				AnalysisResult.messageType = 1;	
				goto  SAVE;
			}
			else //����
			{
				AnalysisResult.rslt_92.nErrorType[nIndexAsdu] [0] = 1;
				AnalysisResult.messageType = 1;
				goto  SAVE;
			}
		}

		//��ʧͬ���źţ�
		int nSmpSynch = pDatas->oData92.asdu[nIndexAsdu].smpSynch;
		if (nSmpSynch==0)
		{
			AnalysisResult.rslt_92.nErrorType[nIndexAsdu][2] = 1;	
			AnalysisResult.messageType = 1;	
			goto  SAVE;
		}

		//Ʒ���쳣��
		int   nChCnt = pDatas->oData92.asdu[nIndexAsdu].nChCount;   //��ȡͨ��������
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

	//��ɢ��: �������Ǹ����ֵ
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
	 nResult   = nSecDif    *  1000000  +  usTime2  -  usTime1;//����洢��֮֡���ʱ��Ĳ�ֵ��
	  AnalysisResult.dDeltTime  =  nResult  - 250000;   //�������֮֡���ʱ���ֵ��250000֮���delt��Ȼ���ж�deltֵ�����;���ֵ��
	 //AnalysisResult.nGSErrorType[4]  = 1;

    //С�˶���������smv��һ֡��ʱ�����ȥ������smpcntΪ0���Ǹ�������goose��λ��ĵ�һ֡��ʱ�����ȥ��



SAVE:
	g_AnalysisResult.push_back(AnalysisResult);
}


void ep_protocol_analysisGS(PEPCAPPARSEDATAS pPrevData,  PEPCAPPARSEDATAS pDatas, PEP_ANALYSIS_RESULT pResult)
{
	EP_ANALYSIS_RESULT AnalysisResult;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//SMV�ж��쳣
	//���ǵ�һ֡��ʱ�����Ƚϣ�ֱ�ӷ��أ���һ֡�ı�ʶ����==0
	if (pPrevData->oData92.nFirst==0)
		return;
	pPrevData->oData92.nFirst = 1;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//GOOSE�ж��쳣��
	int nChIndex = 0;	

	// ��λ������������жϣ�
	// ������0��ʾ�б�λ
    int  nCompRet = memcmp(pPrevData->oDataGs.chData , pDatas->oDataGs.chData,  pDatas->oDataGs.nChCnt  *  sizeof(EPGOOSECHDATA));
	if ( nCompRet != 0)
	{
		// ��λ������������жϣ�
		//SqNO��ֵ����
		if ( pDatas->oDataGs.sqNO   !=   0)
		{
			AnalysisResult.messageType  = 2;
			AnalysisResult.rslt_gs.nErrorType [8] = 1;
		}
		else 
		{
			//״̬�ı�/StNO��ʧ
			if (pDatas->oDataGs.sqNO==0  &&  pDatas->oDataGs.sqNO  -  pPrevData->oDataGs.sqNO > 1)
			{
				AnalysisResult.messageType  =  2;
				AnalysisResult.rslt_gs.nErrorType [0]  = 1;
			}

			// ��λ������������ж�;
			//��λ
			if ( pDatas->oDataGs.stNO   -   pPrevData->oDataGs.stNO <= 1)
			{
				AnalysisResult.messageType  =  2;
				AnalysisResult.rslt_gs.nErrorType [4]  = 1;
			}
		}
	}

	//װ������
	if (pDatas->oDataGs.sqNO==1  &&  pDatas->oDataGs.stNO == 1)
	{
		AnalysisResult.messageType  =  2;
		AnalysisResult.rslt_gs.nErrorType [1]  = 1;
	}
	
	//���λ
	if (pDatas->oDataGs.sqNO  ==  0  &&  pDatas->oDataGs.stNO   -  pPrevData->oDataGs.stNO == 1)
	{
		if (nCompRet==0)//���ҵ�ǰ���ݼ���ǰһ֡�����ݼ��������Ϊ���λ��
		{
			AnalysisResult.messageType  =  2;
			AnalysisResult.rslt_gs.nErrorType [2]  = 1;
		}	
	}

	//StNum ����
	if ( pDatas->oDataGs.stNO   -   pPrevData->oDataGs.stNO  > 1)
	{
		AnalysisResult.messageType  =  2;
		AnalysisResult.rslt_gs.nErrorType [3]  = 1;
	}

	//SqNO �ظ� 
	if ( pDatas->oDataGs.stNO  ==  pPrevData->oDataGs.stNO )
	{
		AnalysisResult.messageType  = 2;
		AnalysisResult.rslt_gs.nErrorType [5]  = 1;
	}

	//SqNO ��ʧ
	if ( pDatas->oDataGs.stNO  -  pPrevData->oDataGs.stNO  > 1)
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [6] = 1;
	}

	//GOOSE����ʱ��Ϊ0
	if ( pDatas->oDataGs.TimeAllowedToLive  ==  0)
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [7] = 1;
	}

	//GOOSE ��ʱ
	if ( pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample  >  pDatas->oDataGs.TimeAllowedToLive &&
		pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample   <  2 * pDatas->oDataGs.TimeAllowedToLive)
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [9]  = 1;
	}

	//GOOSE �ж� 
	if ( pDatas->oDataGs.EventTimeSample  -  pPrevData->oDataGs.EventTimeSample  >  2 * pDatas->oDataGs.TimeAllowedToLive )
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [10] = 1;
		//goto  SAVE;
	}

	//ʱ��δͬ��
	if ( pDatas->oDataGs.sqNO!=0 )
	{
		AnalysisResult.messageType = 2;
		AnalysisResult.rslt_gs.nErrorType [11] = 1;
	}

SAVE:
	g_AnalysisResult.push_back(AnalysisResult);
}