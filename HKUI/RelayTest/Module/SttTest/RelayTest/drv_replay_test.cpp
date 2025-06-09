#include "drv_replay_test.h"
#include"../../SttDevice/RelayTest/SttDriverOper.h"
#include"../../SttDevice/RelayTest/SttDevice.h"
#include <vector>
int HasDecimalNums(float fNum)
{
	int nNum = 0;
	while(fNum != (int)fNum)
	{
		fNum *= 10;
		nNum++;
	}
	return nNum;
}



int TranslateReplayChannel(std::vector<tmt_ReplayChannel> &pChannelData,int nModule)
{
	int nRet = 0;

    if(nModule == 1)
    {
        for(int i = 0;i<24;i++)
        {
            if(pChannelData[i].m_nChannelType == replayIA)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetCurChannelMap(0);
            else if(pChannelData[i].m_nChannelType == replayIB)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetCurChannelMap(1);
            else if(pChannelData[i].m_nChannelType == replayIC)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetCurChannelMap(2);
            else if(pChannelData[i].m_nChannelType == replayIA1)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetCurChannelMap(3);
            else if(pChannelData[i].m_nChannelType == replayIB1)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetCurChannelMap(4);
            else if(pChannelData[i].m_nChannelType == replayIC1)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetCurChannelMap(5);
        }

    }
    else if(nModule == 0)
    {
        for(int i = 0;i<24;i++)
        {
 //           relaytest::ChannelData oPara = oItem.odata(i);
            if(pChannelData[i].m_nChannelType == replayUA)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetVoltChannelMap(0);
            else if(pChannelData[i].m_nChannelType == replayUB)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetVoltChannelMap(1);
            else if(pChannelData[i].m_nChannelType == replayUC)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetVoltChannelMap(2);
            else if(pChannelData[i].m_nChannelType == replayUA1)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetVoltChannelMap(3);
            else if(pChannelData[i].m_nChannelType == replayUB1)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetVoltChannelMap(4);
            else if(pChannelData[i].m_nChannelType == replayUC1)
                nRet |= 1<<CSttDevice::g_pSttDevice->GetVoltChannelMap(5);
        }

    }
    return nRet;
}

//arrX[N],arrY[N]分别存放的是插值节点(Xi,Yi)中的Xi,Yi,参数n为插值节点的个数,而参数x为待求解的插值节点的X值
//函数返回值为求解出来的插值节点X对应的Y值
//注意整个过程涉及的变量，除了循环变量为int外，其他均为float

float Lagrange(float arrX[],float arrY[],int n,float x)
{
    float yResult=0.0;
    float LValue[1000];
    int k,m;
    float temp1,temp2;
    for(k=0;k<n;k++)
    {
        temp1=1.0;
        temp2=1.0;
        for(m=0;m<n;m++)
        {
            if(m==k)
            {
                continue;
            }
            temp1 *= (x-arrX[m]);
            temp2 *= (arrX[k]-arrX[m]);
        }

        LValue[k]=temp1/temp2;

    }

    for(int i=0;i<n;i++)
    {
        yResult += arrY[i]*LValue[i];
    }

    return yResult;
}

int InsertPoint_large(tmt_ReplyPara *pTmtPara)//拉格朗日插值法
{
    float fArx[9];
    float fAry[9];
    float ftime = 0;
	tmt_CalPara *pCalPara = &pTmtPara->m_oCalPara;

    for(int j=0; j<pTmtPara->m_oConfigData.m_nUIChannels; j++)
    {
        std::vector<float> data = pCalPara->m_fNchanneldata[j];
        pCalPara->m_fNchanneldata[j].clear();
        for(int i=0; i<pTmtPara->m_oConfigData.m_nRates; i++)
        {
            int nTotalPoint, nSectionCount, nStatCount, nEndCount, nSamp;
			nEndCount = pTmtPara->m_oConfigData.m_nEndSample[i];
			nSamp = pTmtPara->m_oConfigData.m_nSample[i];
			
            if (i==0)
            {
                ftime = (float)nEndCount/nSamp;
                nTotalPoint = ftime*50000;
                nSectionCount = nTotalPoint/nEndCount-1;
                nStatCount = 0;
            }
            else
            {
				int nEndCountPre = pTmtPara->m_oConfigData.m_nEndSample[i-1];
                ftime = (float)(nEndCount - nEndCountPre)/nSamp;
                nTotalPoint = ftime*50000;
                nSectionCount = nTotalPoint/(nEndCount - nEndCountPre)-1;
                nStatCount = nEndCountPre;
            }
            qDebug()<<"data.size"<<data.size()<<"nEndCount"<<nEndCount;
            for(int k=nStatCount; k<nEndCount; k++)
            {
                fArx[0] = k;
                fArx[1] = k+1;
                fArx[2] = k+2;
                fArx[3] = k+3;
                fArx[4] = k+4;

                if(k+8 >= data.size())
                {
                    fAry[0] = data[k];
                    fAry[1] = data[k-1];
                    fAry[2] = data[k-2];
                    fAry[3] = data[k-3];
                    fAry[4] = data[k-4];
                }
                else
                {
                    fAry[0] = data[k];
                    fAry[1] = data[k+1];
                    fAry[2] = data[k+2];
                    fAry[3] = data[k+3];
                    fAry[4] = data[k+4];
                }
                pCalPara->m_fNchanneldata[j].push_back(data[k]);
                if(j == 0)
                {
                    if(k == pCalPara->m_nInsertPoint[0])
                        pCalPara->m_nNewCyclePoint[0] = pCalPara->m_fNchanneldata[j].size();
                    else if(k == pCalPara->m_nInsertPoint[1])
                        pCalPara->m_nNewCyclePoint[1] = pCalPara->m_fNchanneldata[j].size();
                    else if(k == pCalPara->m_nInsertPoint[2])
                        pCalPara->m_nNewCyclePoint[2] = pCalPara->m_fNchanneldata[j].size();
                    else if(k == pCalPara->m_nInsertPoint[3])
                        pCalPara->m_nNewCyclePoint[3] = pCalPara->m_fNchanneldata[j].size();
                    else if(k == pCalPara->m_nInsertPoint[4])
                        pCalPara->m_nNewCyclePoint[4] = pCalPara->m_fNchanneldata[j].size();
                    else if(k == pCalPara->m_nInsertPoint[5])
                        pCalPara->m_nNewCyclePoint[5] = pCalPara->m_fNchanneldata[j].size();
                }
                for(int l = 0;l<nSectionCount;l++)
                {
                    float fTemp = (float)1/nSectionCount*(l+1)+k;//插值计算方式
                    float fValue = Lagrange(fArx,fAry,5,fTemp);
                    pCalPara->m_fNchanneldata[j].push_back(fValue);
                }
            }
        }
        int nNum = pCalPara->m_fNchanneldata[j].size()%4;
        if(nNum == 3)
            pCalPara->m_fNchanneldata[j].push_back(0);
        else if(nNum == 2)
        {
            pCalPara->m_fNchanneldata[j].push_back(0);
            pCalPara->m_fNchanneldata[j].push_back(0);
        }
        else if(nNum == 1)
        {
            pCalPara->m_fNchanneldata[j].push_back(0);
            pCalPara->m_fNchanneldata[j].push_back(0);
            pCalPara->m_fNchanneldata[j].push_back(0);
        }
        pCalPara->m_nFrePoint = pCalPara->m_fSuntime*1000000*100/pCalPara->m_fNchanneldata[0].size();
        pCalPara->m_nFrePoint = 1000000*100/50000;
        qDebug()<<"data.size"<<data.size()<<"nEndCount"<<pCalPara->m_fNchanneldata[j].size();

    }
}

float linear(float arrX[],float arrY[],int n,float x)
{
    float yResult=0.0;
    yResult = arrY[0]+(arrY[1]-arrY[0])*(x-arrX[0])/(arrX[1]-arrX[0]);
    return yResult;
}

int InsertPoint_linear(tmt_ReplyPara *pTmtPara)
{
    float fArx[2];
    float fAry[2];
    float fTime = 0;
	tmt_CalPara *pCalPara = &pTmtPara->m_oCalPara;
	
    for(int j =0;j<pTmtPara->m_oConfigData.m_nUIChannels;j++)
    {
        std::vector<float> data = pCalPara->m_fNchanneldata[j];
        pCalPara->m_fNchanneldata[j].clear();
        for(int i=0; i<pTmtPara->m_oConfigData.m_nRates; i++)
        {
            int nTotalPoint, nSectionCount, nStatCount, nEndCount, nSamp;
			nEndCount = pTmtPara->m_oConfigData.m_nEndSample[i];
			nSamp = pTmtPara->m_oConfigData.m_nSample[i];
			
            if (i==0)
            {
                fTime = (float)nEndCount/nSamp;
                nTotalPoint = fTime*50000;
                nSectionCount = nTotalPoint/nEndCount-1;
                nStatCount = 0;
            }
            else
            {
				nStatCount = pTmtPara->m_oConfigData.m_nEndSample[i-1];
                fTime = (float)(nEndCount-nStatCount)/nSamp;
                nTotalPoint = fTime*50000;
                nSectionCount = nTotalPoint/(nEndCount-nStatCount)-1;
            }
            qDebug()<<"data.size"<<data.size()<<"nEndCount"<<nEndCount;
            for(int k = nStatCount;k<nEndCount;k++)
            {					
                fArx[0] = k;
                fArx[1] = k+1;

                if(k+1 >= data.size())
                {
                    fAry[0] = data[k];
                    fAry[1] = data[k-1];
                }
                else
                {
                    fAry[0] = data[k];
                    fAry[1] = data[k+1];
                }

      
                for(int l = 0;l<nSectionCount;l++)
                {
                    float fTemp = (float)1/nSectionCount*(l+1)+k;
                    float fValue = linear(fArx,fAry,2,fTemp);
                    pCalPara->m_fNchanneldata[j].push_back(fValue);
                }
            }
        }
        int nNum = pCalPara->m_fNchanneldata[j].size()%4;
        if(nNum == 3)
            pCalPara->m_fNchanneldata[j].push_back(0);
        else if(nNum == 2)
        {
            pCalPara->m_fNchanneldata[j].push_back(0);
            pCalPara->m_fNchanneldata[j].push_back(0);
        }
        else if(nNum == 1)
        {
            pCalPara->m_fNchanneldata[j].push_back(0);
            pCalPara->m_fNchanneldata[j].push_back(0);
            pCalPara->m_fNchanneldata[j].push_back(0);
        }
        //pCalPara->m_nFrePoint = pCalPara->m_fSuntime*1000000*100/pCalPara->m_fNchanneldata[0].size();
        pCalPara->m_nFrePoint = 1000000*100/50000;
        qDebug()<<"data.size"<<data.size()<<"nEndCount"<<pCalPara->m_fNchanneldata[j].size();
    }
}

int DeletePoint(tmt_ReplyPara *pRplyData, int nSectionCount)
{
	tmt_CalPara &oCalPara = pRplyData->m_oCalPara;
    for(int j =0;j<pRplyData->m_oConfigData.m_nUIChannels;j++)//几个通道
    {
		for(int k=0; k<6; k++)//计算缩点后的插入循环点号
		{
			oCalPara.m_nNewCyclePoint[k] = oCalPara.m_nInsertPoint[k]/nSectionCount;
		}

        std::vector<float> data = oCalPara.m_fNchanneldata[j];
        oCalPara.m_fNchanneldata[j].clear();
        for(int i = 0;i< data.size();i+=nSectionCount)//按照50k的速率缩点
        {
            oCalPara.m_fNchanneldata[j].push_back(data[i]);
        }
        int nNum = oCalPara.m_fNchanneldata[j].size()%4;//最后的点数不足4的倍数，则需要补齐
        if(nNum == 3)
            oCalPara.m_fNchanneldata[j].push_back(0);
        else if(nNum == 2)
        {
            oCalPara.m_fNchanneldata[j].push_back(0);
            oCalPara.m_fNchanneldata[j].push_back(0);
        }
        else if(nNum == 1)
        {
            oCalPara.m_fNchanneldata[j].push_back(0);
            oCalPara.m_fNchanneldata[j].push_back(0);
            oCalPara.m_fNchanneldata[j].push_back(0);
        }
        qDebug()<<__FUNCTION__<<oCalPara.m_fNchanneldata[j].size();
    }
}

int dealRelayData(tmt_ReplyPara *pTmtPara)
{    
    int defaultpoint = pTmtPara->m_oCalPara.m_fPlayTime*50000;
    int nTotalPoint = pTmtPara->m_oFileData.m_nTotalPoints;//总点数
    qDebug()<<"nTotalPoint"<<nTotalPoint<<"defaultpoint"<<defaultpoint<<"pTmtPara->m_oCalPara.m_fPlayTime"<<pTmtPara->m_oCalPara.m_fPlayTime;
    if(defaultpoint < nTotalPoint)
	{
        DeletePoint(pTmtPara,nTotalPoint/defaultpoint);
	}
    else
    {
		if(pTmtPara->m_oSetPara.m_nInterpolation == 1)//线性插值法
		{
            InsertPoint_linear(pTmtPara);
		}
        else//拉格朗日插值法
		{
            InsertPoint_large(pTmtPara);
		}
    }
}


void sendDataToDevice(std::vector<float> data,int nType,int channel)
{
    clock_t start,end;
    start = clock();
	
    drv_ReplayData *reData=(drv_ReplayData *)malloc(sizeof(drv_ReplayData));
    int tranlaover = 1<<channel%6;
    qDebug()<<"the channel is"<<tranlaover;
    reData->modular = nType;
    reData->lenth = data.size()+4;
    reData->dat[0] = 0x05640564;
    reData->dat[1] = data.size()+2;
    qDebug()<<"data.size is"<<data.size();
    qDebug()<<"reData->datis "<<reData->dat[1];
    reData->dat[2] = 0x01;
    reData->dat[3] = 1<<channel;//channel

    if(nType == 2)
    {
        for(int i=0;i<data.size()-1;i++)
        {
            long nCode =  CSttDeviceBase::g_pSttDeviceBase->TranslateReplayVoltAmp(data.at(i), channel);
            reData->dat[i+4]  = nCode;
        }
    }
    else
    {
        for(int i=0;i<data.size()-1;i++)
        {
            long nCode = CSttDeviceBase::g_pSttDeviceBase->TranslateReplayCurrentAmp(data.at(i), channel);
            reData->dat[i+4]  = nCode;
        }
    }

    qDebug()<<"~~~~~ nType"<<nType<<"channel"<<channel;

    //msleep(500);
    char* pBuff = (char*)reData;
    int nLen = sizeof(drv_ReplayData);
    qDebug()<<"~~~~~~~the structReplaydata size is"<<data.size()*4+8+8;
    CSttDriverOper::setRelayData(pBuff,data.size()*4+8+8);
    free(reData);
    end = clock();
    float second = (float)(end-start)/CLOCKS_PER_SEC;
    qDebug()<<"the calc time is"<<second;
}

int selectChannel(int nChannel, tmt_ReplyPara *pReplayPara)
{
    int nRet = 0;
    tmt_ReplayChannel data = pReplayPara->m_oFileData.m_ReplayChannel[0];
    if(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].size()!=0)
    {
        switch (data.m_nChannelType)
        {
        case replayIA:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],4,CSttDevice::g_pSttDevice->GetCurChannelMap(0));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayIB:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],4,CSttDevice::g_pSttDevice->GetCurChannelMap(1));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayIC:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],4,CSttDevice::g_pSttDevice->GetCurChannelMap(2));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayIA1:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],4,CSttDevice::g_pSttDevice->GetCurChannelMap(3));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayIB1:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],4,CSttDevice::g_pSttDevice->GetCurChannelMap(4));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayIC1:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],4,CSttDevice::g_pSttDevice->GetCurChannelMap(5));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayUA:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],2,CSttDevice::g_pSttDevice->GetVoltChannelMap(0));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayUB:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],2,CSttDevice::g_pSttDevice->GetVoltChannelMap(1));
			pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayUC:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],2,CSttDevice::g_pSttDevice->GetVoltChannelMap(2));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayUA1:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],2,CSttDevice::g_pSttDevice->GetVoltChannelMap(3));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayUB1:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],2,CSttDevice::g_pSttDevice->GetVoltChannelMap(4));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        case replayUC1:
            sendDataToDevice(pReplayPara->m_oCalPara.m_fNchanneldata[nChannel],2,CSttDevice::g_pSttDevice->GetVoltChannelMap(5));
            pReplayPara->m_oCalPara.m_fNchanneldata[nChannel].clear();
            nRet = 1;
            break;
        default:
            nRet = 0;
            break;
        }
    }
    return nRet;

}

void SortPoint(float *pPoint, int nDelNums)
{
	// 将删除数据段按时间先后排序
	for (int j=nDelNums;j>0;j--)
	{
		for (int i=0;i<j-1;i++)
		{
			if (pPoint[i*2]>pPoint[(i+1)*2])
			{
				float nTemp1 = pPoint[i*2];
				float nTemp2 = pPoint[i*2+1];
				pPoint[i*2] = pPoint[(i+1)*2];
				pPoint[i*2+1] = pPoint[(i+1)*2+1];
				pPoint[(i+1)*2] = nTemp1;
				pPoint[(i+1)*2+1] = nTemp2;
			}
		}
	}
	
	// 将删除段落重叠的部分删除
    for (int i=0;i<nDelNums-1;i++)
	{
		if (pPoint[i*2+1]>pPoint[(i+1)*2])
			pPoint[i*2+1] = pPoint[(i+1)*2];
	}
}
//int TransfromTimetoPoint(float fTime, tmt_FileData &oFileData, tmt_CfgData &oCfgData) ??
int TransfromTimetoPoint(float fTime,  const tmt_CfgData &oCfgData)
{
	if (oCfgData.m_nRates <=1)
	{
//		double nProportion = (double)oFileData.m_Xscale.size()/oCfgData.fSuntime;		
		int nRet = (int)(fTime*oCfgData.m_nSample[0]);
		return nRet;
	}
	else
	{
		float fSuntime = 0;
		for (int i=0;i<oCfgData.m_nRates;i++)
		{
			float fTemp = 0;
			if (i==0)
			{
				fTemp = (float)oCfgData.m_nEndSample[i]/oCfgData.m_nSample[i];
				fSuntime += fTemp;
			}  
			else
			{
				fTemp = (float)(oCfgData.m_nEndSample[i]-oCfgData.m_nEndSample[i-1])/oCfgData.m_nSample[i];
				fSuntime += fTemp;
			}
			if (fTime <= fSuntime)
			{
				if(i == 0)
				{
					double nProportion = (double)(oCfgData.m_nEndSample[i])/fTemp;
					int nTemp = (int)(fTime*nProportion);
					int nRet = nTemp;
					return nRet;
				}
				else
				{
					double nProportion = (double)(oCfgData.m_nEndSample[i]-oCfgData.m_nEndSample[i-1])/fTemp;
					fTime = fTime - fSuntime+fTemp;
					int nTemp = (int)(fTime*nProportion);
					int nRet = oCfgData.m_nEndSample[i-1]+nTemp;
					return nRet;
				}  
			}
		}
	} 

//	return 0;
}

void CalCycleTm(float *pInPtTm, float *pDelPtTm, int nDel, int nIn)
{
	for(int i=nIn; i>0; i--)
	{
		for(int j=0; j<i-1; j++)
		{
			for(int k=0; k<nDel; k++)
			{
				if(pInPtTm[j*2]>pDelPtTm[2*k])
				{
					pInPtTm[2*j] -= pDelPtTm[k*2+1]-pDelPtTm[k*2];
					pInPtTm[2*j+1] -= pDelPtTm[k*2+1]-pDelPtTm[k*2];
				}
				else//插入删除时间轴大小已经排序，小到大排列
				{
					break;
				}
			}			
		}
	}
}

void DealReplayWavePt(tmt_SetPara &oSetPara, tmt_CalPara &oCalPara, const tmt_CfgData &oCfgData)
{
	//先要解析Comtrde文件生成FileData和CfgData
	//需要限制循环的点号不能在删除的点号里面？？？
	SortPoint(oSetPara.m_fDelPtTm, oSetPara.m_nDelNums);
    SortPoint(oSetPara.m_fInPtTm, oSetPara.m_nInNums);
    float *pDelPtTm = oSetPara.m_fDelPtTm;
	//波形解析完毕之后，先删除几段点号
    float *pInPtTm = oSetPara.m_fInPtTm;
	CalCycleTm(pInPtTm, pDelPtTm, oSetPara.m_nDelNums, oSetPara.m_nInNums);//直接删除需要去掉的波形段

	for(int i=0; i<3; i++)
	{
		oCalPara.m_fDelTime[i] = (float)(pDelPtTm[i*2+1]-pDelPtTm[i*2]);
		oCalPara.m_fcycletime[i] = (float)(pInPtTm[i*2+1]-pInPtTm[i*2]);
	}

	// 将时刻转换为点数 TEMP
	for (int i=0;i<6;i++)
	{
		oCalPara.m_nInsertPoint[i] = TransfromTimetoPoint(pInPtTm[i], oCfgData);
		oCalPara.m_nDelPoint[i] = TransfromTimetoPoint(pDelPtTm[i], oCfgData);
        qDebug()<<__FUNCTION__<<pInPtTm[i]<<pDelPtTm[i]<<oCalPara.m_nInsertPoint[i]<<oCalPara.m_nDelPoint[i];
	}
}

void CalPlayTime(tmt_CalPara &oCalPara, const tmt_CfgData &oCfgData)
{
	for (int i=0; i<oCfgData.m_nRates; i++)
	{
		if (i==0)
		{
			float fTemp = (float)oCfgData.m_nEndSample[i]/oCfgData.m_nSample[i];
			oCalPara.m_fPlayTime += fTemp;
		}		
		else
		{
			float fTemp = (float)(oCfgData.m_nEndSample[i]-oCfgData.m_nEndSample[i-1])/oCfgData.m_nSample[i];
			oCalPara.m_fPlayTime += fTemp;
		}		
	}

    float nTemp = 0;
	for (int i=0; i<3; i++)
	{
		nTemp += oCalPara.m_fDelTime[i];
	}
	oCalPara.m_fSuntime = oCalPara.m_fPlayTime - nTemp;

	if (oCalPara.m_fPlayTime > 60)	// 最长回放时间60s
	{
		oCalPara.m_fPlayTime = 60;
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("超出60s，需要删除点号"));
	}
}

void DelPt(tmt_ReplyPara *pTmtPara)
{
	float fTime;
	int   nTempDelPt[6];
	tmt_CalPara *pCalPara = &pTmtPara->m_oCalPara;

	memcpy(nTempDelPt, pTmtPara->m_oCalPara.m_nDelPoint, sizeof(nTempDelPt));

    for(int i = 0; i < 6; i++)
        qDebug()<<"nTempDelPt["<<i<<"]"<<nTempDelPt[i];
    for(int j=0; j<pTmtPara->m_oConfigData.m_nUIChannels; j++)
    {
        std::vector<double> data = pTmtPara->m_oFileData.m_ReplayChannel[j].m_fChannelValue;
		
        for(int i=0; i<pTmtPara->m_oConfigData.m_nRates; i++)
        {
            int nStatCount, nEndCount;
			nEndCount = pTmtPara->m_oConfigData.m_nEndSample[i];
			
            if (i==0)
            {
                nStatCount = 0;
            }
            else
            {
				nStatCount = pTmtPara->m_oConfigData.m_nEndSample[i-1]; 
            }
            for(int k=nStatCount; k<nEndCount; k++)
            {
				if(nTempDelPt[0]>=0 && nTempDelPt[1]>0 && nTempDelPt[1]>nTempDelPt[0])
                {
                    if(k>nTempDelPt[0] && k<nTempDelPt[1])
					{
                        continue;
					}
                }
                if(nTempDelPt[2]>0 && nTempDelPt[3]>0 && nTempDelPt[3]>nTempDelPt[2])
                {
                    if(k>nTempDelPt[2] && k<=nTempDelPt[3])
					{
                        continue;
					}
                }
                if(nTempDelPt[4]>0 && nTempDelPt[5]>0 && nTempDelPt[5]>nTempDelPt[4])
                {
                    if(k>nTempDelPt[4] && k<=nTempDelPt[5])
					{
                        continue;
					}
                }				

                pCalPara->m_fNchanneldata[j].push_back(data[k]);
                if(j == 0)//只计算一次值，每个通道都一样
                {
                    if(k == pCalPara->m_nInsertPoint[0])
                    {
                        pCalPara->m_nNewCyclePoint[0] = pCalPara->m_fNchanneldata[j].size();
                    }
                    else if(k == pCalPara->m_nInsertPoint[1])
                    {
                        pCalPara->m_nNewCyclePoint[1] = pCalPara->m_fNchanneldata[j].size();
                    }
                    else if(k == pCalPara->m_nInsertPoint[2])
					{
                        pCalPara->m_nNewCyclePoint[2] = pCalPara->m_fNchanneldata[j].size();
					}
                    else if(k == pCalPara->m_nInsertPoint[3])
					{
                        pCalPara->m_nNewCyclePoint[3] = pCalPara->m_fNchanneldata[j].size();
					}
                    else if(k == pCalPara->m_nInsertPoint[4])
					{
                        pCalPara->m_nNewCyclePoint[4] = pCalPara->m_fNchanneldata[j].size();
					}
                    else if(k == pCalPara->m_nInsertPoint[5])
					{
                        pCalPara->m_nNewCyclePoint[5] = pCalPara->m_fNchanneldata[j].size();
					}

                }
			}
		}
	}
}
void tmt_to_drv(tmt_ReplyPara *pReplayPara, drv_ReplayParam *pDrvPara, drv_ReplayData *pDrvData)
{
	DealReplayWavePt(pReplayPara->m_oSetPara, pReplayPara->m_oCalPara, pReplayPara->m_oConfigData);
	CalPlayTime(pReplayPara->m_oCalPara, pReplayPara->m_oConfigData);
	DelPt(pReplayPara);
	
	dealRelayData(pReplayPara);
	pDrvPara->nStartType = 0;//默认0
	//GPS触发
	for (int i=1; i<4; i++)
	{
		pDrvPara->nGpsSec += pReplayPara->m_oSetPara.m_nGpsTrigTime[i]*pow(60,i-1);
	}
	pDrvPara->nGpsnSec = pReplayPara->m_oSetPara.m_nGpsTrigTime[0]*1000000;
	//时间触发
	pDrvPara->nmDelay = pReplayPara->m_oSetPara.m_nTripTimeSec*1000;
	
	pDrvPara->nmSec = pReplayPara->m_oCalPara.m_fPlayTime*1000;
    qDebug()<<pDrvPara->nmSec;
	for(int i =0;i<3;i++)
    {
        pDrvPara->nLoopCount[i] = pReplayPara->m_oSetPara.m_nCycleNums[i];
    }
	
	for(int i =0;i<2;i++)//
    {
        drv_ReplayChannel ch;
        ch.nModule = 1<<(i+1);
        ch.nCh = TranslateReplayChannel(pReplayPara->m_oFileData.m_ReplayChannel, i);
        pDrvPara->ch[i] = ch;
    }

	//开入触发
	pDrvPara->nBiLogic = pReplayPara->m_oSetPara.m_nInputLogic;
	pDrvPara->nSwitchlogic = pReplayPara->m_oSetPara.m_nInputLogic;    //不知道那个起作用
	for(int i=0; i<MAX_BINARYIN_COUNT; i++)
	{
        pDrvPara->nBiRef = pReplayPara->m_oSetPara.m_binIn[0].nTrigMode;
        pDrvPara->nBiValid |= pReplayPara->m_oSetPara.m_binIn[i].nSelect ? 1:0 << i;
        pDrvPara->nValidchannel |= pReplayPara->m_oSetPara.m_binIn[i].nSelect ? 1:0 << i;
	}
	
	
	pDrvPara->nTripType = pReplayPara->m_oSetPara.m_nTripType;   
	
	
	if(pReplayPara->m_oSetPara.m_nTripType == 0)
	{
		pDrvPara->nDegressType = 0;
		float fTime = 0.0;
		for(int i=0; i<3; i++)
		{
            fTime += pReplayPara->m_oCalPara.m_fcycletime[i]*1000*pReplayPara->m_oSetPara.m_nCycleNums[i];
		}
        pDrvPara->nmSec = fTime +  pReplayPara->m_oCalPara.m_fPlayTime*1000;
        qDebug()<<pDrvPara->nmSec;
	}
	else
	{
		pDrvPara->nDegressType = 0x80000000;
		pDrvPara->nLoopCount[0] = 1;
	}
	
	if(pReplayPara->m_oCalPara.m_nNewCyclePoint[0]>0 && pReplayPara->m_oCalPara.m_nNewCyclePoint[1]>0 && pDrvPara->nLoopCount[0]>0)
    {
        int nNum = pReplayPara->m_oCalPara.m_nNewCyclePoint[0]%4;
        pDrvPara->nSOL1 = pReplayPara->m_oCalPara.m_nNewCyclePoint[0]+4-nNum+1;
        int nNum1 = (pReplayPara->m_oCalPara.m_nNewCyclePoint[1]+4-nNum)%4;
        pDrvPara->nEOL1 = pReplayPara->m_oCalPara.m_nNewCyclePoint[1]+8-nNum-nNum1;
    }
    if(pReplayPara->m_oCalPara.m_nNewCyclePoint[2]>0 && pReplayPara->m_oCalPara.m_nNewCyclePoint[3]>0 && pDrvPara->nLoopCount[1]>0)
    {
       int nSecNum = pReplayPara->m_oCalPara.m_nNewCyclePoint[2] - pDrvPara->nEOL1;
       if(nSecNum>0)
       {
           int nNum = pReplayPara->m_oCalPara.m_nNewCyclePoint[2]%4;
           pDrvPara->nSOL2 = pReplayPara->m_oCalPara.m_nNewCyclePoint[2]+4-nNum+1;
           int nNum1 = (pReplayPara->m_oCalPara.m_nNewCyclePoint[3]+4-nNum)%4;
           pDrvPara->nEOL2 = pReplayPara->m_oCalPara.m_nNewCyclePoint[3]+8-nNum-nNum1;
       }
    }
    if(pReplayPara->m_oCalPara.m_nNewCyclePoint[4]>0 && pReplayPara->m_oCalPara.m_nNewCyclePoint[5]>0 && pDrvPara->nLoopCount[2]>0)
    {
       int nSecNum = pReplayPara->m_oCalPara.m_nNewCyclePoint[4] - pDrvPara->nEOL2;
       if(nSecNum>0)
       {
           int nNum = pReplayPara->m_oCalPara.m_nNewCyclePoint[4]%4;
           pDrvPara->nSOL3 = pReplayPara->m_oCalPara.m_nNewCyclePoint[4]+4-nNum+1;
           int nNum1 = (pReplayPara->m_oCalPara.m_nNewCyclePoint[5]+4-nNum)%4;
           pDrvPara->nEOL3 = pReplayPara->m_oCalPara.m_nNewCyclePoint[5]+8-nNum-nNum1;
       }
    }
    pReplayPara->m_oCalPara.m_nFrePoint = 100000000/50000;
	pDrvPara->nFreq = pReplayPara->m_oCalPara.m_nFrePoint;
    qDebug()<<pDrvPara->nFreq;

}
