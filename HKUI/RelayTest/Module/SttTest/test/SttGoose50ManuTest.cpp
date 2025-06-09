#include "stdafx.h"
#include"SttGoose50ManuTest.h"

CString CSttGoose50ManuTest::m_strMacroName = "电压电流试验";
CString CSttGoose50ManuTest::m_strMacroID = "Goose50ManuTest";
CString CSttGoose50ManuTest::m_strFilePostFix = "sttuit";
tmt_Goose50Paras *g_pGoose50Paras = NULL;

CSttGoose50ManuTest::CSttGoose50ManuTest()
{
    m_strName = m_strMacroName;
    m_strID = m_strMacroID;//"1";
    m_strTestID = m_strMacroID;
    SetTestStarting(FALSE);
    m_dTestStartTime = 0;
#ifdef _PSX_QT_LINUX_
    m_nFd = CSttDevicetest::g_pSttDevicePNS330->m_nCommfd;
#endif
}

void CSttGoose50ManuTest::Init()
{
    g_pGoose50Paras->init();
    CSttTestBase::Init();
    m_uStartTimeS = 0;
    m_uStartTimeNS = 0;
}

long CSttGoose50ManuTest::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
    return 0;
}

CSttGoose50ManuTest::~CSttGoose50ManuTest(void)
{
}

BOOL CSttGoose50ManuTest::EventProcess()
{
    if(!GetTestStarting())
    {
        return FALSE;
    }

    BOOL bTestFinished = FALSE;
    return bTestFinished;
}

long CSttGoose50ManuTest::SetParameter(DWORD dwState)
{
    return 0;
}

void CSttGoose50ManuTest::StartTest()
{
    CSttTestBase::StartTest();
    TtmToDrv();

    if(!GetTestStarting())
    {
        SetTestStarting(TRUE);
#ifdef _PSX_QT_LINUX_
        ioctl(m_nFd, 0x103, 1);
#endif
        ReturnTestStateEvent_TestStart(0, 0, FALSE);
    }

    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttGoose50ManuTest::StartTest >>>>>>");
}

void CSttGoose50ManuTest::Stop()
{
#ifdef _PSX_QT_LINUX_
    ioctl(m_nFd, 0x103, 0);
#endif
    SetTestStarting(FALSE);
    ReturnTestStateEvent_TestFinish(0, 0, FALSE);
}

void CSttGoose50ManuTest::SetGooseValue(tmt_GoosePub *pCurGoosePub, tmt_goose *ptmt_goose,
                                        GooseChgItem *pGooseChgItem, tmt_GoosePub *pPreGoosePub)
{
    CIECGooseMngr *pGooseMngr = &CSttDevicetest::g_pSttDevicePNS330->m_oCIEC61850CfgMngr.m_oGooseMngr;
    QString strPreChanVal, strCurChanVal, strMap;
    BOOL bIsChanChgValid;

    for(int chanid = 0; chanid < ptmt_goose->vChanelInfo.size(); chanid++)
    {
        if(chanid >= 20)
        {
            return;
        }

        ChanelInfo oChanelInfo = ptmt_goose->vChanelInfo.at(chanid);
        strMap = oChanelInfo.data_type;
        strCurChanVal = pCurGoosePub->m_strChannel[chanid];

        if(strCurChanVal.length() == 0)
        {
            continue;    //通道值数据无效
        }

        bIsChanChgValid = FALSE;
        strPreChanVal = pPreGoosePub->m_strChannel[chanid];

        if(strPreChanVal.length() == 0)
        {
            continue;    //通道值数据无效
        }

        if(strPreChanVal.compare(strCurChanVal) != 0)
        {
            bIsChanChgValid = TRUE;
        }

        if(bIsChanChgValid)
        {
            oChanelInfo.firstvalue = strCurChanVal;
            QByteArray ovalue;

            if(!pGooseMngr->CreateGooseOut_DataSetList(ovalue, oChanelInfo, ptmt_goose->ntimequality))
            {
                continue;    //数值与配置类型不匹配时
            }

            int nDatCnt = pGooseChgItem->count;
            memcpy(pGooseChgItem->dat[nDatCnt].dat, ovalue, ovalue.size());
            pGooseChgItem->dat[nDatCnt].pos = ptmt_goose->nDataSetPos + oChanelInfo.nPos;
            pGooseChgItem->dat[nDatCnt].count = ovalue.size();
            pGooseChgItem->count++;
            pGooseChgItem->StNumChg = 1;//是否需要2,2,4,8
        }
    }
}

void CSttGoose50ManuTest::TtmToDrv()
{
#ifdef _PSX_QT_LINUX_
    GooseChgItems  *pGooseChgItems = &CSttDevicetest::g_pSttDevicePNS330->m_oGooseChgItems;
    GooseItems  *pGooseItems = &CSttDevicetest::g_pSttDevicePNS330->m_oGooseItems;
    CIECGooseMngr *pGooseMngr = &CSttDevicetest::g_pSttDevicePNS330->m_oCIEC61850CfgMngr.m_oGooseMngr;
    tmt_GoosePub *pPreGoosePub = CSttDevicetest::g_pSttDevicePNS330->m_oPreGoosePub;
    int nGseOutCnt = pGooseMngr->data_gseout.count();
    memset(pGooseChgItems, 0, sizeof(GooseChgItems));

    for(int index = 0; index < nGseOutCnt; index++)
    {
        tmt_goose otmt_goose = pGooseMngr->data_gseout.at(index);

        if(!g_pGoose50Paras->m_oGoosePub[index].m_bUseFlag)
        {
            continue;    //无需变位
        }

        int nIndex = -1;

        for(int i = 0; i < 50; i++)
        {
            if(pGooseItems->gs[i].index == index)
            {
                nIndex = i;
                break;
            }
        }

        if(nIndex < 0)
        {
            continue;
        }

        GooseChgItem *pGooseChgItem = &pGooseChgItems->dat[nIndex];
        SetGooseValue(&g_pGoose50Paras->m_oGoosePub[index], &otmt_goose,
                      pGooseChgItem, &pPreGoosePub[index]);

        for(int i = 0; i < 20; i++)
        {
            pPreGoosePub[index].m_strChannel[i] = g_pGoose50Paras->m_oGoosePub[index].m_strChannel[i];
        }
    }

    //判断是否有变位

    for(int i = 0; i < 50; i++)
    {
        if(!GetTestStarting())
        {
            pGooseChgItems->dat[i].StNumChg = 0;
        }

        pGooseChgItems->dat[i].valid = pGooseItems->gs[i].valid;
    }

    ioctl(m_nFd, 0x303, 0);
    write(m_nFd, (char *)pGooseChgItems, sizeof(GooseChgItems));
#endif
}

void CSttGoose50ManuTest::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    stt_xml_serialize(g_pGoose50Paras, pXmlSerialize);
}

void CSttGoose50ManuTest::UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
    Para_XmlSerialize(pXmlSerialize);
    CSttTestBase::StartTest();//实验开始时间重新赋值
    TtmToDrv();
    CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttGoose50ManuTest::UpdatePara Finished");
}

