#include "IECGooseMngr.h"
#include "OSInterface.h"

CIECGooseMngr::CIECGooseMngr(QObject *parent) : QObject(parent)
{
    Init();
}

CIECGooseMngr::~CIECGooseMngr()
{
}

void CIECGooseMngr::Init()
{
    for(int i = 0; i < 4; i++)
    {
        m_nT[i] = 0;
    }

    data_gseout.clear();
}

void CIECGooseMngr::InitChan(ChanelInfo &chaninfo, CIecCfgGoutCh *ch)
{
    chaninfo.firstvalue = ch->m_strDefaultValue;
    chaninfo.data_type = ch->m_strDataType;
    chaninfo.strMap = ch->m_strAppChID;
    chaninfo.strDevCh = ch->m_strDevChID;
    chaninfo.nBOIndex = 0;
    chaninfo.nBOExIndex = 0;
    chaninfo.nBoPos = 0;
    chaninfo.nLen = 0;
    chaninfo.nPos = 0;
    chaninfo.bHasUTC = 0;
    chaninfo.nUTCPos = 0;
    chaninfo.nTrueValue = 0;
    chaninfo.nFalseVlaue = 0;
}

void CIECGooseMngr::UpdateGooseTmtDataSetList(tmt_goose &otmt_goose)
{
    otmt_goose.m_DataSetList.clear();

    for(int chanid = 0; chanid < otmt_goose.m_ChanNum; chanid++)
    {
        ChanelInfo chaninfo = otmt_goose.vChanelInfo.at(chanid);
        chaninfo.nPos = otmt_goose.m_DataSetList.size();
        QByteArray chanbytes;
        CreateGooseOut_DataSetList(chanbytes, chaninfo, otmt_goose.ntimequality);
        otmt_goose.m_DataSetList.append(chanbytes);
        chaninfo.nLen = chanbytes.size();

		if(QString::compare(chaninfo.data_type, "Timestamp") == 0)
        {
        }
        else
        {
            if(chanid < (otmt_goose.m_ChanNum - 1))
            {
                ChanelInfo Nextchaninfo = otmt_goose.vChanelInfo.at(chanid + 1);

				if(QString::compare(Nextchaninfo.data_type, "Timestamp") == 0)
                {
                    chaninfo.bHasUTC = 1;
                    chaninfo.nUTCPos = otmt_goose.m_DataSetList.size() + 2; //struct:+5
                }
            }
        }
    }
}

void CIECGooseMngr::CreateGooseTmtStruct(CIecCfgGooseDataBase *pIecData)
{
    if(pIecData->m_nUseFlag == 0)
    {
        return;
    }

    tmt_goose m_tmt_goose;
    m_tmt_goose.port = pIecData->m_nFiberIndex;
    m_tmt_goose.m_AppID = QString::number(pIecData->m_dwAppID, 16);
    m_tmt_goose.m_MacDesc = pIecData->m_strDestAddress.replace("-", "");
    m_tmt_goose.m_MacSrc = pIecData->m_strSrcAddress.replace("-", "");
    m_tmt_goose.m_VLanID = QString::number(pIecData->m_dwVLandID);
    m_tmt_goose.m_VLanPri = QString::number(pIecData->m_dwVLandPriority);
    m_tmt_goose.m_NetType = "88B8";
    m_tmt_goose.m_GcRef = pIecData->m_strgocbRef;
    m_tmt_goose.m_TTL = QString::number(pIecData->m_nLiveTime);
    m_tmt_goose.m_DataSetRef = pIecData->m_strDataSet;
    m_tmt_goose.m_GoID = pIecData->m_strGooseId;
    m_tmt_goose.m_NdsCom = QString::number(pIecData->m_bNdsCom);
    m_tmt_goose.m_ConfRev = QString::number(pIecData->m_dwVersion);
    m_tmt_goose.m_TestMode = QString::number(pIecData->m_bTest);
    m_tmt_goose.m_StNum = "00000001";
    m_tmt_goose.m_SqNum = "00000001";
    m_tmt_goose.nreserved1 = 0;
    m_tmt_goose.nreserved2 = 0;
    bool ok;
    m_tmt_goose.ntimequality = (BYTE)(pIecData->m_strTQuality.toInt(&ok, 16) & 0xff);
    m_tmt_goose.nDataSetPos = 0;
    m_tmt_goose.nTestModePos = 0;
    m_tmt_goose.m_DataSetList.clear();
    m_tmt_goose.m_ChanNum = pIecData->m_nChannelNum;

    for(int chanid = 0; chanid < m_tmt_goose.m_ChanNum; chanid++)
    {
        CIecCfgGoutCh *ch = (CIecCfgGoutCh *)pIecData->m_pCfgChs->GetAtIndex(chanid);
        QString m_strMap = ch->m_strAppChID;
        ChanelInfo chaninfo;
        InitChan(chaninfo, ch);
        chaninfo.nPos = m_tmt_goose.m_DataSetList.size();
        QByteArray chanbytes;
        CreateGooseOut_DataSetList(chanbytes, chaninfo, m_tmt_goose.ntimequality);
        m_tmt_goose.m_DataSetList.append(chanbytes);
        chaninfo.nLen = chanbytes.size();

		if(QString::compare(ch->m_strDataType, "Timestamp") == 0)
        {
        }
        else
        {
            if(chanid < (m_tmt_goose.m_ChanNum - 1))
            {
                CIecCfgGoutCh *Nextch = (CIecCfgGoutCh *)pIecData->m_pCfgChs->GetAtIndex(chanid + 1);

				if(QString::compare(Nextch->m_strDataType, "Timestamp") == 0)
                {
                    chaninfo.bHasUTC = 1;
                    chaninfo.nUTCPos = m_tmt_goose.m_DataSetList.size() + 2; //struct:+5
                }
            }

            if(m_strMap.length() > 4)
            {
                if(m_strMap.contains("boutex"))
                {
                    chaninfo.nBOExIndex = m_strMap.replace("boutex", "").toInt();
                }
                else if(QString::compare(m_strMap.left(4), "bout") == 0)
                {
                    chaninfo.nBOIndex = m_strMap.mid(4, m_strMap.length() - 4).toInt();
                }

                qDebug() << QString("GOOSEout[%1] ChanId[%2]  AppChID=%3").arg(data_gseout.size()).
                         arg(QString("%1").arg(chanid, 3, 10, QChar('0'))).arg(m_strMap);
            }
        }

        m_tmt_goose.vChanelInfo.append(chaninfo);
    }

    data_gseout.append(m_tmt_goose);
    m_nT[0] = pIecData->m_nT0;
    m_nT[1] = pIecData->m_nT1;
    m_nT[2] = pIecData->m_nT2;
    m_nT[3] = pIecData->m_nT3;
}

//INT32U
//0-0x7F 01
//0x80-0x7FFF 02
//0x8000-0xFFFF 03
//0x10000-0x7FFFFFFF 04
//0x80000000-0xFFFFFFFF 05
void CIECGooseMngr::CreateGooseByteArray(QByteArray &oAr, tmt_goose &t_GOOSE)
{
    GooseStruct GoosePacketStruct;
    //ï¿½ï¿½ï¿½ï¿½Í·ï¿½ï¿½ï¿½ï¿½
    AddLongStrToByte(t_GOOSE.m_MacDesc, GoosePacketStruct.m_DesMac, 6); //DesMac
    AddLongStrToByte(t_GOOSE.m_MacSrc, GoosePacketStruct.m_SrcMac, 6); //SrcMac
    QString t2 = HexToBin(t_GOOSE.m_VLanID);
    QString t1 = HexToBin(t_GOOSE.m_VLanPri);

    while(t2.length() < 12)
    {
        QString t3 = ("0");
        t3 += t2;
        t2 = t3;
    }

    QString t_VLANValue = BinToHex(t1 + ("0") + t2);
    AddLongStrToByte(("8100"), GoosePacketStruct.m_VLan, 2);    //VLAN
    AddLongStrToByte(t_VLANValue, GoosePacketStruct.m_VLan, 2); //VLAN
    AddLongStrToByte(t_GOOSE.m_NetType, GoosePacketStruct.m_Type, 2);    //TYPE
    //GooseDataProcess
    GoosePacketStruct.m_GoosePdu.m_DataSetList.append(t_GOOSE.m_DataSetList);
    int nDataSetLen = GoosePacketStruct.m_GoosePdu.m_DataSetList.size();
    ProcessGooseDataSetList(GoosePacketStruct.m_GoosePdu.m_DataSetList);
    int t_PduLength = GoosePacketStruct.m_GoosePdu.m_DataSetList.size();
    GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(0x8A);

    if(t_GOOSE.m_ChanNum < 0x80)
    {
        GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(0x01);
        GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(t_GOOSE.m_ChanNum);
    }
    else
    {
        GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(0x02);
        QString t_DecStr = "";
        QString t_HexPduLength = "";
        t_DecStr = t_DecStr.setNum(t_GOOSE.m_ChanNum);
        t_HexPduLength = DecToHex(t_DecStr);
        t_HexPduLength = Get0String(4 - t_HexPduLength.length()) + t_HexPduLength;
        GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(GetIntegerFromString(t_HexPduLength.mid(0, 2)));
        GoosePacketStruct.m_GoosePdu.m_EntriesNum.push_back(GetIntegerFromString(t_HexPduLength.mid(2, 2)));
    }

    t_PduLength += GoosePacketStruct.m_GoosePdu.m_EntriesNum.size();
    ///////////////////////////////////ndscom////////////////////////////////////////
    GoosePacketStruct.m_GoosePdu.m_NdsCom.push_back(0x89);
    GoosePacketStruct.m_GoosePdu.m_NdsCom.push_back(0x01);
    GoosePacketStruct.m_GoosePdu.m_NdsCom.push_back(t_GOOSE.m_NdsCom.toInt());
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_NdsCom.size();
    ///////////////////////////////////ConfRev/////////////////////////////////
    GoosePacketStruct.m_GoosePdu.m_ConfRev.push_back(0x88);
    QByteArray ConfRevBytes;
    ConfRevBytes.clear();
    char nConfRevBytes = 0;
    QString t_RevHex;
    bool ok;
    unsigned int nConfRev = t_GOOSE.m_ConfRev.toUInt(&ok, 10);
    t_RevHex = QString("%1").arg(nConfRev, 10, 16, QChar('0'));

    if(nConfRev > 0x7FFFFFFF)
    {
        ConfRevBytes.push_back(GetIntegerFromString(t_RevHex.mid(0, 2)));
        nConfRevBytes++;
    }

    if(nConfRev > 0xFFFF)
    {
        ConfRevBytes.push_back(GetIntegerFromString(t_RevHex.mid(2, 2)));
        nConfRevBytes++;
    }

    if(nConfRev > 0x7FFF)
    {
        ConfRevBytes.push_back(GetIntegerFromString(t_RevHex.mid(4, 2)));
        nConfRevBytes++;
    }

    if(nConfRev > 0x7F)
    {
        ConfRevBytes.push_back(GetIntegerFromString(t_RevHex.mid(6, 2)));
        nConfRevBytes++;
    }

    ConfRevBytes.push_back(GetIntegerFromString(t_RevHex.mid(8, 2)));
    nConfRevBytes++;
    GoosePacketStruct.m_GoosePdu.m_ConfRev.push_back(nConfRevBytes);
    GoosePacketStruct.m_GoosePdu.m_ConfRev.push_back(ConfRevBytes);
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_ConfRev.size();
    ///////////////////////////////////TestMode//////////////////////////////////////////
    GoosePacketStruct.m_GoosePdu.m_TestMode.push_back(0x87);
    GoosePacketStruct.m_GoosePdu.m_TestMode.push_back(0x01);
    GoosePacketStruct.m_GoosePdu.m_TestMode.push_back(t_GOOSE.m_TestMode.toInt());
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_TestMode.size();
    ////////////////////////////////////SqNum/////////////////////////////////////////////////////////
    GoosePacketStruct.m_GoosePdu.m_SqNum.push_back(0x86);
    QString t_SqNum = t_GOOSE.m_SqNum;
    t_SqNum.replace((" "), (""));
    int t_SqLength =  t_SqNum.length() / 2;
    GoosePacketStruct.m_GoosePdu.m_SqNum.push_back(t_SqLength);

    for(int m = 0; m < t_SqLength; m++)
    {
        GoosePacketStruct.m_GoosePdu.m_SqNum.push_back(GetIntegerFromString(t_SqNum.mid(m * 2, 2)));
    }

    t_PduLength += GoosePacketStruct.m_GoosePdu.m_SqNum.size();
    ///////////////////////////////////StNum/////////////////////////////////////////////////////
    GoosePacketStruct.m_GoosePdu.m_StNum.push_back(0x85);
    QString t_StNum = t_GOOSE.m_StNum;
    t_StNum.replace((" "), (""));
    int t_StLength =  t_StNum.length() / 2;
    GoosePacketStruct.m_GoosePdu.m_StNum.push_back(t_StLength);

    for(int m = 0; m < t_StLength; m++)
    {
        GoosePacketStruct.m_GoosePdu.m_StNum.push_back(GetIntegerFromString(t_StNum.mid(m * 2, 2)));
    }

    t_PduLength += GoosePacketStruct.m_GoosePdu.m_StNum.size();
    /////////////////////////////////Event Time/////////////////////////////////////////////////////
    int t_HexTime = g_theSttDeviceStatus->m_nUtc_s;
    QString t_strHexTime("%1");
    t_strHexTime = t_strHexTime.arg(t_HexTime, 2, 16, QChar('0'));
    t_strHexTime = Get0String(8 - t_strHexTime.length()) + t_strHexTime;
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(0x84);
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(0x08);
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(GetIntegerFromString(t_strHexTime.mid(0, 2)));
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(GetIntegerFromString(t_strHexTime.mid(2, 2)));
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(GetIntegerFromString(t_strHexTime.mid(4, 2)));
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(GetIntegerFromString(t_strHexTime.mid(6, 2)));
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back((char)0);
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back((char)0);
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back((char)0);
    GoosePacketStruct.m_GoosePdu.m_TimeStamp.push_back(t_GOOSE.ntimequality);
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_TimeStamp.size();
    /////////////////////////////////goID///////////////////////////////////////////////
    int t_GoIDLength = t_GOOSE.m_GoID.length();
    GoosePacketStruct.m_GoosePdu.m_GoID.push_back(0x83);

    if(t_GoIDLength >= 0x80)
    {
        GoosePacketStruct.m_GoosePdu.m_GoID.push_back(0x81);
    }

    GoosePacketStruct.m_GoosePdu.m_GoID.push_back(t_GoIDLength);
    GoosePacketStruct.m_GoosePdu.m_GoID.append(t_GOOSE.m_GoID.toLatin1());
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_GoID.size();
    /////////////////////////////////DataSetRef///////////////////////////////////
    int t_DataSetLength = t_GOOSE.m_DataSetRef.length();
    GoosePacketStruct.m_GoosePdu.m_DataSetRef.push_back(0x82);

    if(t_DataSetLength >= 0x80)
    {
        GoosePacketStruct.m_GoosePdu.m_DataSetRef.push_back(0x81);
    }

    GoosePacketStruct.m_GoosePdu.m_DataSetRef.push_back(t_DataSetLength);
    GoosePacketStruct.m_GoosePdu.m_DataSetRef.append(t_GOOSE.m_DataSetRef.toLatin1());
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_DataSetRef.size();
    /////////////////////////////////TTL////////////////////////////////////////////////////
    GoosePacketStruct.m_GoosePdu.m_TTL.push_back(0x81);
    //qDebug()<<"m_GooseSrcStruct.m_TTL="<<m_GooseSrcStruct.m_TTL;
    QString t_TTLHex = DecToHex(t_GOOSE.m_TTL);
    t_TTLHex = Get0String(4 - t_TTLHex.length()) + t_TTLHex;
    GoosePacketStruct.m_GoosePdu.m_TTL.push_back(0x02);
    GoosePacketStruct.m_GoosePdu.m_TTL.push_back(GetIntegerFromString(t_TTLHex.mid(0, 2)));
    GoosePacketStruct.m_GoosePdu.m_TTL.push_back(GetIntegerFromString(t_TTLHex.mid(2, 2)));
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_TTL.size();
    ///////////////////////////////GcRef////////////////////////////////////////
    int t_GcRef = t_GOOSE.m_GcRef.length();
    GoosePacketStruct.m_GoosePdu.m_GcRef.push_back(0x80);

    if(t_GcRef >= 0x80)
    {
        GoosePacketStruct.m_GoosePdu.m_GcRef.push_back(0x81);
    }

    GoosePacketStruct.m_GoosePdu.m_GcRef.push_back(t_GcRef);
    GoosePacketStruct.m_GoosePdu.m_GcRef.append(t_GOOSE.m_GcRef.toLatin1());
    t_PduLength += GoosePacketStruct.m_GoosePdu.m_GcRef.size();
    ////////////////////////////////PDU Length//////////////////////////////////////////////////
    GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(0x61);

    if(t_PduLength >= 0x80 && t_PduLength <= 0xFF)
    {
        GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(0x81);
        GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(t_PduLength);
    }
    else
    {
        if(t_PduLength > 0xFF)
        {
            GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(0x82);
            QString t_DecStr = "";
            QString t_HexPduLength = "";
            t_DecStr = t_DecStr.setNum(t_PduLength);
            t_HexPduLength = DecToHex(t_DecStr);
            t_HexPduLength = Get0String(4 - t_HexPduLength.length()) + t_HexPduLength;
            GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(GetIntegerFromString(t_HexPduLength.mid(0, 2)));
            GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(GetIntegerFromString(t_HexPduLength.mid(2, 4)));
        }
        else
        {
            GoosePacketStruct.m_GoosePdu.m_PduLength.push_back(t_PduLength);
        }
    }

    int t_ApplicationLength = t_PduLength + GoosePacketStruct.m_GoosePdu.m_PduLength.size();
    BYTE t_V00 = 0x00;
    /////////////////////////////////////ReServed1,Resverved2,AppID,Length////////////////////////////////////////////////////
    GoosePacketStruct.m_Reserve1.push_back((unsigned char)(t_GOOSE.nreserved1 >> 8));
    GoosePacketStruct.m_Reserve1.push_back((unsigned char)(t_GOOSE.nreserved1));
    GoosePacketStruct.m_Reserve2.push_back((unsigned char)(t_GOOSE.nreserved2 >> 8));
    GoosePacketStruct.m_Reserve2.push_back((unsigned char)(t_GOOSE.nreserved2));
    QString t_AppID = t_GOOSE.m_AppID;
    t_AppID = Get0String(4 - t_AppID.length()) + t_AppID;
    GoosePacketStruct.m_AppID.push_back(GetIntegerFromString(t_AppID.mid(0, 2)));
    GoosePacketStruct.m_AppID.push_back(GetIntegerFromString(t_AppID.mid(2, 2)));
    t_ApplicationLength += 8;
    QString t_HexAppLength = "";
    t_HexAppLength = t_HexAppLength.setNum(t_ApplicationLength);
    t_HexAppLength = DecToHex(t_HexAppLength);
    t_HexAppLength = Get0String(4 - t_HexAppLength.length()) + t_HexAppLength;
    GoosePacketStruct.m_ApplicationLength.push_back(GetIntegerFromString(t_HexAppLength.mid(0, 2)));
    GoosePacketStruct.m_ApplicationLength.push_back(GetIntegerFromString(t_HexAppLength.mid(2, 2)));
    /////////////////////////////////////////////////////////////////////////////////
    BYTE t_SaveData[20000];
    int t_FLength = 0;

    for(int m = 0; m < 6; m++)
    {
        t_SaveData[m] = GoosePacketStruct.m_DesMac.at(m);
    }

    t_FLength += 6;

    for(int m = 0; m < 6; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_SrcMac.at(m);
    }

    t_FLength += 6;

    for(int m = 0; m < 4; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_VLan.at(m);
    }

    t_FLength += 4;

    for(int m = 0; m < 2; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_Type.at(m);
    }

    t_FLength += 2;

    for(int m = 0; m < 2; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_AppID.at(m);
    }

    t_FLength += 2;

    for(int m = 0; m < 2; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_ApplicationLength.at(m);
    }

    t_FLength += 2;

    for(int m = 0; m < 2; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_Reserve1.at(m);
    }

    t_FLength += 2;

    for(int m = 0; m < 2; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_Reserve2.at(m);
    }

    t_FLength += 2;
    int l = GoosePacketStruct.m_GoosePdu.m_PduLength.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_PduLength.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_GcRef.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_GcRef.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_TTL.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_TTL.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_DataSetRef.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_DataSetRef.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_GoID.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_GoID.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_TimeStamp.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_TimeStamp.at(m);
    }

    int t_iUTCPos = t_FLength + 2;
    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_StNum.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_StNum.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_SqNum.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_SqNum.at(m);
    }

    t_FLength += l;
    t_GOOSE.nTestModePos = t_FLength + 2;
    l = GoosePacketStruct.m_GoosePdu.m_TestMode.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_TestMode.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_ConfRev.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_ConfRev.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_NdsCom.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_NdsCom.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_EntriesNum.size();

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_EntriesNum.at(m);
    }

    t_FLength += l;
    l = GoosePacketStruct.m_GoosePdu.m_DataSetList.size();
    int t_iGooseDataPos;

    if(nDataSetLen >= 0x80 && nDataSetLen <= 0xFF)
    {
        t_iGooseDataPos = t_FLength + 3;//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ý¼ï¿½
    }
    else if(nDataSetLen > 0xFF)
    {
        t_iGooseDataPos = t_FLength + 4;
    }
    else if(nDataSetLen < 0x80)
    {
        t_iGooseDataPos = t_FLength + 2;
    }

    t_GOOSE.nDataSetPos = t_iGooseDataPos;

    for(int m = 0; m < l; m++)
    {
        t_SaveData[t_FLength + m] = GoosePacketStruct.m_GoosePdu.m_DataSetList.at(m);
    }

    t_FLength += l;
    QByteArray &t_WaitToSendStructArray = oAr;
    QString t_strAll = QString::number(t_FLength, 16);
    QString t_UTCPos;
    t_UTCPos = QString("%1").arg(t_iUTCPos, 2, 16, QChar('0'));
    t_UTCPos = Get0String(4 - t_UTCPos.length()) + t_UTCPos;
    AddLongStrToByte(Get0String(4 - t_strAll.length()) + t_strAll, t_WaitToSendStructArray, 2); //All
    AddLongStrToByte(t_UTCPos, t_WaitToSendStructArray, 2); //UTCPos

    for(int m = 0; m < t_FLength; m++)
    {
        t_WaitToSendStructArray.push_back(t_SaveData[m]);
    }

    t_GOOSE.nUTCPos = t_iUTCPos + 4; //ÓÃÓÚÒì³£Ä£ÄâÇý¶¯ÐÞ¸ÄUTC,FPGA´ËÊ±²»Ö÷¶¯¸üÐÂ´ËUTC
    t_GOOSE.nDataSetPos += 4;
    t_GOOSE.nTestModePos += 4;
}

void CIECGooseMngr::GetGooseIn_DataPosAndValue(CIecCfgGooseDataBase *gsein_data, int nIndex, unsigned long &nlastByte, unsigned long &nTrueValue, unsigned long &nFalseValue)
{
    QByteArray t_DataArray;
    int nDecount = 0;
    int nSize = gsein_data->m_nChannelNum;

    for(int i = 0; i < nSize; i++)
    {
        if(i < nIndex)
        {
            continue;
        }

        CIecCfgGoutCh *ch = (CIecCfgGoutCh *)gsein_data->m_pCfgChs->GetAtIndex(i);
        EncoDerGooseDataAtom(t_DataArray, ch);

        if(i == nIndex)
        {
            if(QString::compare(ch->m_strDataType, "BOOLEAN") == 0)
            {
                nTrueValue = 1;
                nFalseValue = 0;
                nDecount = 2;
                continue;
            }

            if(QString::compare(ch->m_strDataType, "VisString64") == 0)
            {
                nDecount = 3;
                nTrueValue = 0x80;
                nFalseValue = 0x40;
                continue;
            }

            if(QString::compare(ch->m_strDataType, "Dbpos") == 0)
            {
                nDecount = 3;
                nTrueValue = 0x80;
                nFalseValue = 0x40;
                continue;
            }
        }
    }

    nlastByte = t_DataArray.size() - nDecount - 1;
}

void CIECGooseMngr::EncoDerGooseDataAtom(QByteArray &oAr, CIecCfgGoutCh *ch)
{
    if(QString::compare(ch->m_strDataType, "BOOLEAN") == 0)
    {
        char value = 0x01;

        if(QString::compare(ch->m_strDefaultValue, "FALSE") == 0)
        {
            value = 0x00;
        }

        oAr.push_back(0x83);
        oAr.push_back(0x01);
        oAr.push_back(value);
        return;
    }

    if(QString::compare(ch->m_strDataType, "Dbpos") == 0)
    {
        //2bits
        bool ok;
        unsigned char value = ch->m_strDefaultValue.toInt(&ok, 2) & 0xff;
        oAr.push_back(0x84);
        unsigned char Zl = 2; //ï¿½ï¿½ï¿½ï¿½
        oAr.push_back(Zl);
        //ï¿½î³¤
        int CL = 6;
        oAr.push_back(CL);
        oAr.push_back(value << CL);
        return;
    }

    if(QString::compare(ch->m_strDataType, "VisString64") == 0 || QString::compare(ch->m_strDataType, "Quality") == 0)
    {
        //13bits
        bool ok;
        short value = ch->m_strDefaultValue.toShort(&ok, 2); //= pAtom->vuint();
        oAr.push_back(0x84);
        unsigned char Zl = 3; //ï¿½ï¿½ï¿½ï¿½
        oAr.push_back(Zl);
        //ï¿½î³¤
        int CL = 3;
        oAr.push_back(CL);
        value = value << CL;
        oAr.append(value >> 8);
        oAr.append(value & 0xff);
        return;
    }

    if(QString::compare(ch->m_strDataType, "INT32") == 0)
    {
        int value = ch->m_strDefaultValue.toInt();
        oAr.push_back(0x85);
        oAr.push_back(4);
        oAr.push_back((unsigned char)(value >> 24));
        oAr.push_back((unsigned char)(value >> 16));
        oAr.push_back((unsigned char)(value >> 8));
        oAr.push_back((unsigned char)(value));
        return;
    }

    if(QString::compare(ch->m_strDataType, "INT32U") == 0)
    {
        unsigned int value = ch->m_strDefaultValue.toUInt();
        oAr.push_back(0x86);
        oAr.push_back(4);
        oAr.push_back((unsigned char)(value >> 24));
        oAr.push_back((unsigned char)(value >> 16));
        oAr.push_back((unsigned char)(value >> 8));
        oAr.push_back((unsigned char)(value));
        return;
    }

    if(QString::compare(ch->m_strDataType, "FLOAT32") == 0)
    {
        float value = ch->m_strDefaultValue.toFloat();
        ConverStruct t_s;//ï¿½ï¿½ï¿½Ã¹ï¿½ï¿½ï¿½ï¿½ï¿½×ª
        t_s.f = value;
        oAr.push_back(0x87);
        oAr.push_back(0x05);
        oAr.push_back(0x08);
        oAr.push_back(t_s.b[3]);
        oAr.push_back(t_s.b[2]);
        oAr.push_back(t_s.b[1]);
        oAr.push_back(t_s.b[0]);
        return;
    }

    if(QString::compare(ch->m_strDataType, "Timestamp") == 0)
    {
        BYTE t_V = 0x00;
        int t_HexTime = g_theSttDeviceStatus->m_nUtc_s;
        QString t_strHexTime("%1");
        t_strHexTime = t_strHexTime.arg(t_HexTime, 2, 16, QChar('0'));
        t_strHexTime = Get0String(8 - t_strHexTime.length()) + t_strHexTime;
        oAr.push_back(0x91);
        oAr.push_back(0x08);
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(0, 2)));
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(2, 2)));
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(4, 2)));
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(6, 2)));
        oAr.push_back(t_V);
        oAr.push_back(t_V);
        oAr.push_back(t_V);
        oAr.push_back(0x01);
        return;
    }

    if(QString::compare(ch->m_strDataType, "STRUCT") == 0)
    {
        //		QByteArray ot;
        //		int nSize = pAtom->vstru_size();
        //		for(int j=0;j<nSize;j++)
        //		{
        //			 hqyGooseCommon::DataAtom* pA = pAtom->mutable_vstru(j);
        //			EncoDerGooseDataAtom(ot,pA);
        //		}
        //		oAr.push_back(0xA2);
        //		oAr.push_back(ot.size());
        //		oAr.append(ot);
    }
}

void CIECGooseMngr::ProcessGooseDataSetList(QByteArray &oAr)
{
    QByteArray oByteArray;
    oByteArray.push_back(0xAB);
    int t_L = oAr.size();

    if(t_L >= 0x80 && t_L <= 0xFF)
    {
        oByteArray.push_back(0x81);
        oByteArray.push_back(t_L);
    }
    else
    {
        if(t_L > 0xFF)
        {
            oByteArray.push_back(0x82);
            QString t_strL = "";
            t_strL = t_strL.setNum(t_L);
            QString t_HexL = DecToHex(t_strL);
            t_HexL = Get0String(4 - t_HexL.length()) + t_HexL;
            oByteArray.push_back(GetIntegerFromString(t_HexL.mid(0, 2)));
            oByteArray.push_back(GetIntegerFromString(t_HexL.mid(2, 2)));
        }
        else
        {
            oByteArray.push_back(t_L);
        }
    }

    for(int i = oByteArray.size() - 1; i > -1; i--)
    {
        oAr.push_front(oByteArray.at(i));
    }
}

BOOL CIECGooseMngr::CreateGooseOut_DataSetList(QByteArray &oAr, ChanelInfo &chan, char timequality)
{
    QString data_type = chan.data_type;
    BOOL bRet = TRUE; //ÀàÐÍÓë³õÖµÊÇ·ñÆ¥Åä
    BOOL bTransFlag;

    if(QString::compare(data_type, "BOOLEAN") == 0)
    {
        char value = 0x00;

        if(QString::compare(chan.firstvalue, "TRUE") == 0)
        {
            value = 0x01;
        }
        else if(QString::compare(chan.firstvalue, "FALSE") == 0)
        {
        }
        else
        {
            chan.firstvalue = "FALSE";
            bRet = FALSE;
        }

        oAr.push_back(0x83);
        oAr.push_back(0x01);
        oAr.push_back(value);
        chan.nFalseVlaue = 0;
        chan.nTrueValue = 1;
        chan.nBoPos = chan.nPos + 2;
        return bRet;
    }

    if(QString::compare(data_type, "Dbpos") == 0)
    {
        chan.firstvalue.replace("[", "").replace("]", "");
        //2bits
        unsigned char value = chan.firstvalue.toInt(&bTransFlag, 2) & 0xff;

        if(!bTransFlag)
        {
            value = 0x01;
            chan.firstvalue = "01";
            bRet = FALSE;
        }

        oAr.push_back(0x84);
        unsigned char Zl = 2;
        oAr.push_back(Zl);
        int CL = 6;
        oAr.push_back(CL);
        oAr.push_back(value << CL);
        chan.nFalseVlaue = 0x40;
        chan.nTrueValue = 0x80;
        chan.nBoPos = chan.nPos + 3;
        return bRet;
    }

    if(QString::compare(data_type, "Timestamp") == 0)
    {
        BYTE t_V = 0x00;
        long nSecond = g_theSttDeviceStatus->m_nUtc_s;
        int t_HexTime = nSecond;
        QString t_strHexTime("%1");
        t_strHexTime = t_strHexTime.arg(t_HexTime, 2, 16, QChar('0'));
        t_strHexTime = Get0String(8 - t_strHexTime.length()) + t_strHexTime;
        oAr.push_back(0x91);
        oAr.push_back(0x08);
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(0, 2)));
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(2, 2)));
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(4, 2)));
        oAr.push_back(GetIntegerFromString(t_strHexTime.mid(6, 2)));
        oAr.push_back(t_V);
        oAr.push_back(t_V);
        oAr.push_back(t_V);
        oAr.push_back(timequality);
        return TRUE;
    }

    if(QString::compare(data_type, "VisString64") == 0)
    {
        chan.firstvalue.replace("[", "").replace("]", "");
        int t_VL = chan.firstvalue.length();
        oAr.push_back(0x84);
        unsigned char Zl = t_VL / 8 + 2;
        oAr.push_back(Zl);
        int CL = 8 - t_VL % 8;
        oAr.push_back(CL);
        int t_RVL = t_VL / 8 + 1;

        for(int m = 0; m < CL; m++)
        {
            chan.firstvalue.insert(t_VL, '0');
        }

        long t_V = chan.firstvalue.toLong(&bTransFlag, 2);

        if(!bTransFlag)
        {
            t_V = 0;
            chan.firstvalue = "0000000000000";
            bRet = FALSE;
        }

        QString t_Hex = QString("%1").arg(t_V, t_RVL * 2, 16, QChar('0'));

        for(int n = 0; n < t_RVL; n++)
        {
            oAr.push_back(GetIntegerFromString(t_Hex.mid(n * 2, 2)));
        }

        return bRet;
    }

    if(QString::compare(data_type, "Quality") == 0)
    {
        chan.firstvalue = chan.firstvalue.right(4); //"0~0x1FFF"
        //13bits
        short value = chan.firstvalue.toShort(&bTransFlag, 16);

        if(!bTransFlag)
        {
            value = 0;
            chan.firstvalue = "0000000000000";
            bRet = FALSE;
        }

        oAr.push_back(0x84);
        unsigned char Zl = 3;
        oAr.push_back(Zl);
        int CL = 3;
        oAr.push_back(CL);
        value = value << CL;
        oAr.append(value >> 8);
        oAr.append(value & 0xff);
        return bRet;
    }

    if(QString::compare(data_type, "INT32") == 0)
    {
        int value = chan.firstvalue.toInt(&bTransFlag);

        if(!bTransFlag)
        {
            chan.firstvalue = "0";
            bRet = FALSE;
        }

        oAr.push_back(0x85);
        oAr.push_back(4);
        oAr.push_back((unsigned char)(value >> 24));
        oAr.push_back((unsigned char)(value >> 16));
        oAr.push_back((unsigned char)(value >> 8));
        oAr.push_back((unsigned char)(value & 0xff));
        return bRet;
    }

    if(QString::compare(data_type, "INT32U") == 0)
    {
        unsigned int value = chan.firstvalue.toUInt(&bTransFlag);

        if(!bTransFlag)
        {
            chan.firstvalue = "0";
            bRet = FALSE;
        }

        oAr.push_back(0x86);
        oAr.push_back(4);
        oAr.push_back((unsigned char)(value >> 24));
        oAr.push_back((unsigned char)(value >> 16));
        oAr.push_back((unsigned char)(value >> 8));
        oAr.push_back((unsigned char)(value & 0xff));
        return bRet;
    }

    if(QString::compare(data_type, "FLOAT32") == 0)
    {
        float value = chan.firstvalue.toFloat(&bTransFlag);

        if(!bTransFlag)
        {
            value = 0.0000001;
            chan.firstvalue = "0.0000001";
            bRet = FALSE;
        }

        ConverStruct t_s;//ï¿½ï¿½ï¿½Ã¹ï¿½ï¿½ï¿½ï¿½ï¿½×ª
        t_s.f = value;
        oAr.push_back(0x87);
        oAr.push_back(0x05);
        oAr.push_back(0x08);
        oAr.push_back(t_s.b[3]);
        oAr.push_back(t_s.b[2]);
        oAr.push_back(t_s.b[1]);
        oAr.push_back(t_s.b[0]);
        return bRet;
    }

    if(QString::compare(data_type, "Struct") == 0)
    {
        //ÔÝ²»Ö§³Ö´ËÀàÐÍ
        QByteArray ba;
        ba.resize(2);
        ba[0] = 0xA2;
        ba[1] = 0;
        oAr.push_back(ba);
        return bRet;
    }

    chan.firstvalue = "";
    return FALSE;//²»Ö§³ÖµÄÊý¾ÝÀàÐÍ·µ»Ø FALSE
}
