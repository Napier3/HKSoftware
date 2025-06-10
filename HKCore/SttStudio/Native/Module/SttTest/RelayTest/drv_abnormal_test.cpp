#include "stdafx.h"
#include "drv_abnormal_test.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../SttDevice/RelayTest/SttDevice.h"
#include<math.h>
#define PPC				80
#define FLY_MAP_MAX		12
#define ABN_ALG_PARA_CNT	24
#define ABN_SV_PARA_CNT	75
#define ABN_STATE_MAX		500

#define ABN_TYPE_SMV		0x01
#define ABN_TYPE_GOOSE		0x02

#define ABN_STATE_TRIP_MANU			0
#define ABN_STATE_TRIP_TIME			1
#define ABN_STATE_TRIP_GPS			2
#define ABN_STATE_TRIP_DI_OR			3
#define ABN_STATE_TRIP_DI_AND			4
#define ABN_STATE_TRIP_TIME_DI_OR		5
#define ABN_STATE_TRIP_TIME_DI_AND	6

//QVector<int> ChannelVolts,ChannelCurrs;

void translate_qltyenable_to_string(const tmt_SvQlty_Set &oQlty, QString &strQuality)
{
    int nQuality = oQlty.nValid;
    nQuality |= oQlty.bOverflow<<2;
    nQuality |= oQlty.bOutRange<<3;
    nQuality |= oQlty.bBadBmVal<<4;
    nQuality |= oQlty.bJitter<<5;
    nQuality |= oQlty.bFault<<6;
    nQuality |= oQlty.bOldDataOT<<7;
    nQuality |= oQlty.bInconformity<<8;
    nQuality |= oQlty.bImprecise<<9;
    nQuality |= oQlty.bSrc<<10;
    nQuality |= oQlty.bTest<<11;
    nQuality |= oQlty.bOprLock<<12;

    QString m_strHighQuality=QString("%1").arg(nQuality,4,16,QChar('0'));
    QString m_strLowQuality="0000";
    strQuality = m_strHighQuality+m_strLowQuality;
}


void tmt_to_drv_smv_config(int nGroup, int nErrIndex, int &nSndCfg, drv_smvconfig *pSmvConfig)
{
//   int nGroup = oSmvAbn.nSvGroupSel;
   nSndCfg = 1;
   pSmvConfig = (drv_smvconfig *)CIEC61850CfgMngr::g_pIEC61850CfgMngr->confsv;

   UINT nChange = pSmvConfig->nsmvsamplebegin[nGroup/2];
//   UINT nNew = nOld;
   ushort nTemp;

   if(nGroup%2 == 0)
   {
       nTemp = nChange >> 16;
       nTemp -= nErrIndex;
       nChange &= 0xFFFF;//取低16位
       nChange |= (nTemp<<16);
       pSmvConfig->nsmvsamplebegin[nGroup/2] = nChange;
   }
   else
   {
        nTemp = nChange & 0xFFFF;
        nTemp -= nErrIndex;
        nChange &= 0xFFFF0000;
        nChange |= nTemp;
        pSmvConfig->nsmvsamplebegin[nGroup/2] = nChange;
   }
}

void tmt_to_drv_analog(const tmt_channel *puiVOL, const tmt_Channel *puiCUR, drv_acanalogpara &acAnalog) //电压参数 电流参数  输出的模拟量参数
{
    acAnalog.oModuledata[0].nModule = VOL_CHANNEL_MARK;
    acAnalog.oModuledata[1].nModule = CUR_CHANNEL_MARK;

    for (int i=0; i<CHANNEL_MAX; i++) //电压通道数
    {
            CSttDevice::g_pSttDevice->TransAnalogVolToDrv(puiVOL[i].Harm[1].fAmp,
                    puiVOL[i].Harm[1].fAngle,
                    puiVOL[i].Harm[1].fFreq, i ,
                    acAnalog.oModuledata[0].nData);
    }

    for (int i=0; i<CHANNEL_MAX; i++)
    {
            CSttDevice::g_pSttDevice->TransAnalogCurToDrv(puiCUR[i].Harm[1].fAmp,
                    puiCUR[i].Harm[1].fAngle,
                    puiCUR[i].Harm[1].fFreq, i ,
                    acAnalog.oModuledata[1].nData);
    }
}



void tmt_to_drv_digital(const tmt_channel *puiVOL, const tmt_Channel *puiCUR, drv_digitalpara &digAnalog)
{
    digAnalog.oModuledata[0].module = DIGITAL_CHANNEL_MARK;

    int nChannelA_drv_Index_Volt,nChannelA_drv_Index_Curr;
    for(int i=0; i<MAX_DIGITAL_GROUP_NUM; i++)
    {
	   // bool ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Volt,VOLT);
	   // ret=CSttDevice::g_pSttDevice->GetDrvChannelAIndex_Dig(i,nChannelA_drv_Index_Curr,CURRENT);

		nChannelA_drv_Index_Volt=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,VOLT,Ang);
		nChannelA_drv_Index_Curr=CSttDevice::g_pSttDevice->GetDrvChannel_Digital(i,CURRENT,Ang);

        for(int channel=0;channel<3;channel++)//A B C
        {
            CSttDevice::g_pSttDevice->TransDigitalVolToDrv(puiVOL[i*3+channel].Harm[1].fAmp,
                    puiVOL[i*3+channel].Harm[1].fAngle,
                    puiVOL[i*3+channel].Harm[1].fFreq, i ,
                    &digAnalog.oModuledata[0].dat[nChannelA_drv_Index_Volt+channel*3]);

            CSttDevice::g_pSttDevice->TransDigitalCurToDrv(puiCUR[i*3+channel].Harm[1].fAmp,
                    puiCUR[i*3+channel].Harm[1].fAngle,
                    puiCUR[i*3+channel].Harm[1].fFreq, i ,
                    &digAnalog.oModuledata[0].dat[nChannelA_drv_Index_Curr+channel*3]);

        }
    }
}
//0 : 无异常
//1 ： 丢帧测试
//2 ： 费电测试
//3 ： 抖动测试 先加后减
//4 ： 错序测试 先加后减
//5 ： 延时偏差
//6 ： 延时变化
//7 ： 序号偏差
//8 ： 品质异常
// 	TYPE_NORMAL = 0,
//	TYPE_LOST   = 1,
//	TYPE_JITTE  = 2,
//	TYPE_FLYPOINT = 3,
//	TYPE_ERRCMPT  = 4,
//	TYPE_DELAYOFFSET = 5,
//	TYPE_DELAYMODEFY = 6,
//	TYPE_INDEXERR = 7,
//	TYPE_QUALITYERR = 8
void tmt_to_drv_smvabnormal(const tmt_SmvAbnormal & t_SmvAbnormal, drv_smvabnormal & t_drv_smvabnormal)
{
    t_drv_smvabnormal.nmodule   = DIGITAL_CHANNEL_MARK;
    t_drv_smvabnormal.ngroup    = (1<<t_SmvAbnormal.nSvGroupSel);

    int index = 0;
    int ndirection = -1;
    for ( index = 0; index < 80; index++) // 80个点的数据
    {
        t_drv_smvabnormal.smv_abnormal[index].npoint = index;
        t_drv_smvabnormal.smv_abnormal[index].nerrcmpt = 0;
        t_drv_smvabnormal.smv_abnormal[index].nflypoint = 0;
        t_drv_smvabnormal.smv_abnormal[index].nflyPointIValue = 0;
        t_drv_smvabnormal.smv_abnormal[index].nflyPointVValue = 0;
        t_drv_smvabnormal.smv_abnormal[index].njitter = 2500;
        t_drv_smvabnormal.smv_abnormal[index].nlost = 0;
        if(t_SmvAbnormal.bSVAbnSet[index]) // 寻找其中的异常点
        {
            switch(t_SmvAbnormal.nAbnType)
            {
            case TYPE_SMV_NORMAL:
                ;
                break;
            case TYPE_SMV_LOST:
                t_drv_smvabnormal.smv_abnormal[index].nlost = 1; //丢点使能
                break;
            case TYPE_SMV_FLYPOINT:
            {
                int i = 0;
                for( i = 0; i < 16; i++)
                {
                   t_drv_smvabnormal.smv_abnormal[index].nflypoint |= (t_SmvAbnormal.bVolFly[i]<<i);
                }

                for( i = 16; i < 32; i++)
                {
                   t_drv_smvabnormal.smv_abnormal[index].nflypoint |= (t_SmvAbnormal.bCurFly[i-16]<<i);
                }

                t_drv_smvabnormal.smv_abnormal[index].nflyPointVValue = t_SmvAbnormal.fFlyPointVolt * 220000;
                t_drv_smvabnormal.smv_abnormal[index].nflyPointIValue = t_SmvAbnormal.fFlyPointCur * 160000;// PT or CT 参数和电压或者电流系数


            }
                break;
            case TYPE_SMV_JITTE:
            {
                if (ndirection == 1)
                {
                    t_drv_smvabnormal.smv_abnormal[index].njitter += t_SmvAbnormal.nJitter / 100; // ns to 0.1 us
                } else {
                    t_drv_smvabnormal.smv_abnormal[index].njitter -= t_SmvAbnormal.nJitter / 100; // ns to 0.1 us
                }
                ndirection = 0 - ndirection; // 变化方向间隔改变

            }
                break;
            case TYPE_SMV_ERRCMPT:
            {
                t_drv_smvabnormal.smv_abnormal[index].nerrcmpt = ndirection * t_SmvAbnormal.nErrCmpt;
                ndirection = 0 - ndirection;//同上

            }
                break;
            case TYPE_SMV_DELAYOFFSET:
            case TYPE_SMV_DELAYMODEFY:
            case TYPE_SMV_INDEXERR:
            case TYPE_SMV_QUALITYERR:
                break;
            default:
                break;
            }
        } else {

        }

    }

    qDebug()<<t_SmvAbnormal.nInvDataSndTyp<<t_SmvAbnormal.nCircle<<t_SmvAbnormal.nHoldTime<<t_SmvAbnormal.nCirclePerSecond;
    t_drv_smvabnormal.nptCnt = 80;
    // TYPE_CIRCLE = 0,
    // TYPE_SECOND = 1
    if(t_SmvAbnormal.nInvDataSndTyp == TYPE_CIRCLE)
    {
        t_drv_smvabnormal.nabnormalcircle = t_SmvAbnormal.nCircle;
        t_drv_smvabnormal.nroopcount = 1;
        t_drv_smvabnormal.nnormalcircle = 0;
    } else {
        t_drv_smvabnormal.nroopcount = t_SmvAbnormal.nHoldTime;
        t_drv_smvabnormal.nabnormalcircle = t_SmvAbnormal.nCirclePerSecond;
        t_drv_smvabnormal.nnormalcircle = 0;
    }

}


void tmt_to_drv_abnormalconfigs(const tmt_SmvAbnormal & t_SmvAbnormal,  drv_abnormalconfigs &smvconfig, drv_smvconfig &pSmvConfig, int &nSndCfg)
{
    /*
    <data name="源Mac地址" id="SrcMac" unit="" data-type="SrcMac" default="" value=""/>
    <data name="目的Mac地址" id="DestMac" unit="" data-type="DestMac" default="" value=""/>
    <data name="VlanID" id="VLANID" unit="" data-type="VLANID" default="0" value="0"/>
    <data name="Vlan优先级" id="VlanPrrty" unit="" data-type="VlanPrrty" default="0" value="0"/>
    <data name="网络标识" id="NetType" unit="" data-type="NetType" default="0" value="0"/>
    <data name="AppID" id="APPID" unit="" data-type="APPID" default="28" value="28"/>
    <data name="同步方式" id="SyncMode" unit="" data-type="SyncMode" default="0" value="0"/>
    <data name="版本号" id="ConfRev" unit="" data-type="ConfRev" default="0" value="0"/>
    <data name="采样延时" id="DelayTime" unit="" data-type="DelayTime" default="0" value="0"/>
    <data name="数据集" id="DataSet" unit="" data-type="DataSet" default="" value=""/>
    <data name="RefrTm" id="RefrTm" unit="" data-type="RefrTm" default="0" value="0"/>
    <data name="SVID" id="SVID" unit="" data-type="SVID" default="" value=""/>

            */
    tmt_sv_92 t_92;
    const QVector<tmt_sv_92> & vec_sv_92 = CIEC61850CfgMngr::g_pIEC61850CfgMngr->data_92;
    if(t_SmvAbnormal.nSvGroupSel < vec_sv_92.size())
    {
        t_92 = vec_sv_92[t_SmvAbnormal.nSvGroupSel];
        t_92.m_MacDesc = t_SmvAbnormal.oIec61850_9_2Msg.m_MacDesc;
        t_92.m_MacSrc = t_SmvAbnormal.oIec61850_9_2Msg.m_MacSrc;
        t_92.m_SVID = t_SmvAbnormal.oIec61850_9_2Msg.m_SVID;
        t_92.m_AppID = t_SmvAbnormal.oIec61850_9_2Msg.m_AppID;
        t_92.m_SyncMode = t_SmvAbnormal.oIec61850_9_2Msg.m_SyncMode;
        t_92.m_ConfRev = t_SmvAbnormal.oIec61850_9_2Msg.m_ConfRev;
        t_92.m_VLanID = t_SmvAbnormal.oIec61850_9_2Msg.m_VLanID;
        t_92.m_VLanPri = t_SmvAbnormal.oIec61850_9_2Msg.m_VLanPri;
        t_92.m_NetType = t_SmvAbnormal.oIec61850_9_2Msg.m_NetType;
        t_92.m_Datset = t_SmvAbnormal.oIec61850_9_2Msg.m_Datset;
    } else {
        memset(&smvconfig, 0, sizeof(smvconfig));
        if(TYPE_SMV_INDEXERR == t_SmvAbnormal.nAbnType)
        {
            tmt_to_drv_smv_config(t_SmvAbnormal.nSvGroupSel, t_SmvAbnormal.nErrIndex, nSndCfg, &pSmvConfig);
        }
        return;
    }

    //group 0 - 7 表示IEC界面配置中的1-8组 与tvec_sv_92 对应
    QByteArray result;
    smvconfig.nmodule = DIGITAL_CHANNEL_MARK;
    smvconfig.ncount = 1;

    switch(t_SmvAbnormal.nAbnType)
    {
    case TYPE_SMV_NORMAL:
    case TYPE_SMV_LOST:
    case TYPE_SMV_JITTE:
    case TYPE_SMV_FLYPOINT:
    case TYPE_SMV_ERRCMPT:
        break;
    case TYPE_SMV_DELAYOFFSET:
    {
        t_92.m_DelayTimeValue = QString().number(t_92.m_DelayTimeValue.toInt() - t_SmvAbnormal.fOffsetTime/1000); // us to ms
        break;
    }
    case TYPE_SMV_DELAYMODEFY:
    {
        t_92.m_DelayTimeValue = QString().number(t_SmvAbnormal.fDelayTime/1000); // us to ms
        break;
    }
    case TYPE_SMV_INDEXERR:
    {
        tmt_to_drv_smv_config(t_SmvAbnormal.nSvGroupSel, t_SmvAbnormal.nErrIndex, nSndCfg, &pSmvConfig);
        break;
    }
    case TYPE_SMV_QUALITYERR:
    {
        QString str;
        translate_qltyenable_to_string(t_SmvAbnormal.QltySet, str);
        for(int i = 0; i < t_92.m_FactorList.size(); i++)
        {
            if(t_SmvAbnormal.bQltyInvChannel[i])
            {
                t_92.m_FactorList[i] = str;
            }
        }

        break;
    }
    default:
        break;
    }

    CIEC61850CfgMngr::g_pIEC61850CfgMngr->Create92Packet(t_92, result, QString(""), 0);
    smvconfig.dat[0].ncount = result.size();
    smvconfig.dat[0].ngroup = (0x01 << t_SmvAbnormal.nSvGroupSel);
    if(smvconfig.dat[0].ncount <= DATA_MAX)
    {
        for(int j = 0 ; j < smvconfig.dat[0].ncount; j++)
        {
            smvconfig.dat[0].szdat[j] = result[j];
        }
    }

}

void tmt_to_drv_stt_bin(unsigned long &nAndValid, unsigned long &nOrValid, int nLogic, tmt_BinaryIn *pBin)
{
    unsigned int nLogicValid = 0;

    for (int i=0; i<8; i++)
    {
        nLogicValid |= ((pBin[i].nSelect?1:0)<<i);
    }

    if(nLogic)//And
    {
        nAndValid = nLogicValid;
        nOrValid = 0;
    }
    else//Or
    {
        nAndValid  = 0;
        nOrValid = nLogicValid;
    }
}

void tmt_to_drv_stt_bo(drv_analogbosetting &oBo, tmt_BinaryOut *pBo)
{
    long nIndex = 0;
   memset(&oBo, 0, sizeof(drv_analogbosetting));
   for (;nIndex<10;nIndex++)
   {
       oBo.nBoValue += ((!pBo[nIndex].nState)*(1<<nIndex));

       if(pBo[nIndex].nMode >= 2)
       {
           oBo.nreverse = 0;
       }
       else if (pBo[nIndex].nMode == 1)
       {
           oBo.ntrigerMode = 1;
           oBo.nreverse = 1;
       }
       else
       {
           if(pBo[nIndex].fTimeTrig>0)
           {
               oBo.ntimeDelay = pBo[nIndex].fTimeTrig*1000;
           }
           oBo.ntrigerMode = 0;
           oBo.nreverse = 1;
       }

       if (pBo[nIndex].fHoldTime>0)
       {
           oBo.nHoldTime = pBo[nIndex].fHoldTime*1000;
       }
   }
}

void tmt_to_drv_stt_abngoose(tmt_goose &oAbnGS, drv_gooseabnormal &oabnGoose)
{
    oabnGoose.ngoosemodule = 1;//????????
    oabnGoose.ngroup = CIEC61850CfgMngr::g_pIEC61850CfgMngr->data_gse.count();
    QByteArray qByteSend;
    CIEC61850CfgMngr::g_pIEC61850CfgMngr->CreateGooseData(qByteSend, oAbnGS);
    oabnGoose.ngooselen = qByteSend.size();
    memcpy(oabnGoose.szgoosebuf, qByteSend.data(), oabnGoose.ngooselen);
    tmt_goose oTemp = CIEC61850CfgMngr::g_pIEC61850CfgMngr->data_gse.at(0);
    oabnGoose.nTimePos = oTemp.nUTCPos;
}


void tmt_to_drv(tmt_AbnStatePara &oTmtState,drv_abnstate &oDrvState)
{
    oDrvState.nReversal = oTmtState.m_eBinReversal;

    tmt_to_drv_stt_bin(oDrvState.nAndValid, oDrvState.nOrValid, oTmtState.m_nBinLogic, oTmtState.m_binIn);

    //oDrvState.gpsSec = oTmtState.m_tGps.Year + oTmtState.m_tGps;
    oDrvState.nGpsSec = oTmtState.m_tGps.nSeconds;//秒值
    oDrvState.nGpsnSec = oTmtState.m_tGps.nMilliSeconds*1000000;//纳秒值转换
    oDrvState.nTimemSec = oTmtState.m_fTimeState*1000;
    oDrvState.nDelay = oTmtState.m_fTimeAfterTrigger*1000;

    oDrvState.nabnormaltype = oTmtState.m_nAbnormalType;


    //设置模拟量值
    tmt_to_drv_analog(oTmtState.m_uiVOL, oTmtState.m_uiCUR, oDrvState.acAnalog);
    //设置数字量值
    tmt_to_drv_digital(oTmtState.m_uiVOL, oTmtState.m_uiCUR, oDrvState.acDigital);
    //设置开出量
    tmt_to_drv_stt_bo(oDrvState.oBo, oTmtState.m_binOut);


    qDebug()<<__FUNCTION__<<__LINE__<<"oTmtState.m_nTriggerCondition"<<oTmtState.m_nTriggerCondition;
    //设置触发条件
    switch(oTmtState.m_nTriggerCondition)//nTirpType
    {
    case TMT_MDSTATE_TIMETRIGGER:
        oDrvState.nTirpType = ABN_STATE_TRIP_TIME;
        break;
    case TMT_MDSTATE_TIMEBINTRIGGER:
        oDrvState.nTirpType = ABN_STATE_TRIP_TIME_DI_OR;
        break;
    case TMT_MDSTATE_BINTRIGGER:
    {
        if (oTmtState.m_nBinLogic)
        {
            oDrvState.nTirpType = ABN_STATE_TRIP_DI_OR;
        }
        else
        {
            oDrvState.nTirpType = ABN_STATE_TRIP_DI_AND;
        }
    }
        break;
    case TMT_MDSTATE_MEARSURETRIGGER:
        oDrvState.nTirpType = ABN_STATE_TRIP_MANU;
        break;
    case TMT_MDSTATE_GPSBTRIGGER:
        oDrvState.nTirpType = ABN_STATE_TRIP_GPS;
        break;
    }

    oDrvState.nabnormaltype =  oTmtState.m_nAbnormalType;

    switch(oDrvState.nabnormaltype)
    {
    case TYPE_NORMAL:
        break;
    case TYPE_SMV_ABNORMAL:
        tmt_to_drv_smvabnormal(oTmtState.m_smvAbnormalPara, oDrvState.osmvabnormal);

        tmt_to_drv_abnormalconfigs(oTmtState.m_smvAbnormalPara \
                                   , oDrvState.oabnormalcomfig \
                                   , oDrvState.oconfig \
                                   , oDrvState.nsendconfig);

        break;
    case TYPE_GOOSE_ABNORMAL:
        //goose异常smv异常
        tmt_to_drv_stt_abngoose(oTmtState.m_gooseAbnormalPara, oDrvState.ogooseabnormal);
        break;
    default:
        break;

    }




}

void tmt_to_drv(tmt_AbnSimulationTest *pTmt, drv_abnstate_test *pDrv)
{

    memset(pDrv, 0, sizeof(drv_abnstate_test));
    pDrv->nModuleCount = 2;//模拟模块总数
    pDrv->nStateModuleCount = 1;//数字模块总数
 //   pDrv->nDcmodule=0;//直流模块总数
    pDrv->nStateCount  = pTmt->m_oAbnSimulationParas.m_nStateNumbers;//状态数
//    pDrv->nSequence = pTmt->m_oStateParas.m_bSequence;//是否位顺序状态序列
    pDrv->nloop = pTmt->m_oAbnSimulationParas.m_bRepeat;//是否循环
    pDrv->nReverRefence = pTmt->m_oAbnSimulationParas.m_nBinTripRef;//0：开入量以第一态为参考
    //1：以上一态为参考
    pDrv->noriginal = 0;//goose开入初始值
    for (int nIndex = 0;nIndex<pTmt->m_oAbnSimulationParas.m_nStateNumbers;nIndex++)
    {
        pDrv->stabnState[nIndex].nStateNum = nIndex;
        qDebug()<<__FUNCTION__<<__LINE__<<"nIndex"<<nIndex;
        tmt_to_drv(pTmt->m_oAbnSimulationParas.m_AbnStatepara[nIndex],pDrv->stabnState[nIndex]);
    }
}
