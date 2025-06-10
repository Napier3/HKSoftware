#include "IEC2MComMngr.h"
#include "OSInterface.h"

long g_nStable2MDataPkgIdxMapPos[MAX_2M_BLOCKS_COUNT] = {0};

CIECStable2MComMngr::CIECStable2MComMngr(QObject *parent) : QObject(parent)
{
    Init();
}

CIECStable2MComMngr::~CIECStable2MComMngr()
{

}

void CIECStable2MComMngr::Init()
{
    memset(m_oStable2MList,0,MAX_2M_BLOCKS_COUNT*sizeof(tmt_Stable2MList));
    for(int i = 0;i < MAX_2M_MODULE_COUNT;i++)
    {
        for(int j = 0;j < MAX_2M_BLOCK_COUNT;j++)
        {
            for(int k = 0;k < MAX_2M_CMDIDX_COUNT;k++)
            {
                m_oStable2MList[i][j].m_oCmdPkg[k].m_nAddr = -1;
            }
        }
    }

    m_oDataPkgList.clear();

    //SubBlocks Init
    memset(m_oStable2MSubList,0,MAX_2M_BLOCKS_COUNT*sizeof(tmt_Stable2MList));
}

void CIECStable2MComMngr::Create2MTmtStruct(CIecCfg2MData *pIecData)
{
    if(pIecData->m_nUseFlag==0)
        return;

    long nPort = pIecData->m_nFiberIndex;
    long nIdx = pIecData->m_nDelayTime;
    long nChanNum = pIecData->m_nChannelNum;
    if(nPort > -1 && nPort < 16)
    {

    }
    else
        return;

    tmt_Stable2M oStable2M;
    oStable2M.m_nPort = nPort;
    oStable2M.m_nChanNum = nChanNum;
    oStable2M.m_nIdxMapChan = 0;
    oStable2M.m_nAddr = pIecData->m_nSmpCntType;//Addr

    CString strAppChId;
    if(nChanNum > MAX_2M_CHANNEL_COUNT)
        return;

    for(int nChan = 0;nChan < nChanNum;nChan++)
    {
        CIecCfg6044CommonCh * m_pCIecCfg2MCh=(CIecCfg6044CommonCh *)pIecData->m_pCfgChs->GetAtIndex(nChan);

        Stable2MChanInfo  *pChanInfo = &oStable2M.m_oChanList[nChan];
        pChanInfo->nLen = m_pCIecCfg2MCh->m_nChLenth;
        pChanInfo->nFirstValue = m_pCIecCfg2MCh->m_nValue;
        strAppChId = m_pCIecCfg2MCh->m_strAppChID;

        if(strAppChId.compare("t-delay") == 0)
        {
            oStable2M.m_nIdxMapChan = nChan + 1;//IdxMap
        }
    }

    if(pIecData->m_nBlockType == 0)
    {
        oStable2M.m_nUseFlag = 1;
        oStable2M.nIdxVal = nIdx;

        if(nIdx > -1 && nIdx < MAX_2M_DATAIDX_VALUE)
            m_oDataPkgList.append(oStable2M);
    }
    else
    {
        oStable2M.m_nUseFlag = 0;//命令报文初始化时，配而不发
        if(nIdx > -1 && nIdx < MAX_2M_CMDIDX_COUNT)
        {
            tmt_Stable2MList *pStable2MList = &m_oStable2MList[nPort/8][nPort%8];
            memcpy(&pStable2MList->m_oCmdPkg[nIdx],&oStable2M,sizeof(tmt_Stable2M));
        }
    }
}

void CIECStable2MComMngr::AfterCreate2MTmt()
{   
    for(int i = 0;i < MAX_2M_MODULE_COUNT;i++)
    {
        for(int j = 0;j < MAX_2M_BLOCK_COUNT;j++)
        {
            m_oStable2MList[i][j].m_nDataPkgCount = 0;
        }
    }

    tmt_Stable2M *pStable2M;
    tmt_Stable2MList *pStable2MList;
    long nPort;
    for(int nPortIdx = 0;nPortIdx < MAX_2M_BLOCK_COUNT;nPortIdx++)
    {
        for(int i = 0;i < MAX_2M_DATAIDX_VALUE;i++)
        {
            for(int j = 0;j < m_oDataPkgList.size();j++)
            {
                pStable2M = &m_oDataPkgList[j];
                nPort = pStable2M->m_nPort;

                if(i == pStable2M->nIdxVal && nPortIdx == (nPort%8))
                {
                    pStable2MList = &m_oStable2MList[nPort/8][nPortIdx];
                    long nCount = pStable2MList->m_nDataPkgCount;
                    if(nCount < MAX_2M_DATAIDX_COUNT)
                    {
                        memcpy(&pStable2MList->m_oDataPkg[nCount],pStable2M,sizeof(tmt_Stable2M));
                        pStable2MList->m_nDataPkgCount++;
                    }
                }
            }
        }
    }
}

void CIECStable2MComMngr::Create2MListByteArray(tmt_Stable2MList oStable2MList,long nPort,QByteArray &oPackage)
{
    oPackage.clear();

    oPackage.push_back((char)0);
    oPackage.push_back((char)0);
    oPackage.push_back(0xE0);
    oPackage.push_back(0x01);

    for(int i = 0;i < 6;i++)
    {
        //FPGA 要求报文对齐
        oPackage.push_back((char)0);
    }

    QByteArray ba;
    for(int i = 0;i < MAX_2M_CMDIDX_COUNT;i++)
    {
        Create2MByteArray(oStable2MList.m_oCmdPkg[i],nPort,ba,FALSE);
        oPackage.push_back(ba);
        oPackage.push_back(ba);
        oPackage.push_back(ba);
    }

    for(int i = 0;i < MAX_2M_DATAIDX_COUNT;i++)
    {
        Create2MByteArray(oStable2MList.m_oDataPkg[i],nPort,ba,TRUE);
        oPackage.push_back(ba);
    }

    switch(oPackage.size()%4)
    {
    case 1:
        oPackage.push_back((char)0);
        oPackage.push_back((char)0);
        oPackage.push_back((char)0);
        break;
    case 2:
        oPackage.push_back((char)0);
        oPackage.push_back((char)0);
        break;
    case 3:
        oPackage.push_back((char)0);
        break;
    }
}

void CIECStable2MComMngr::Create2MByteArray(tmt_Stable2M otmtStable2M,long nPort,QByteArray &oPackage,BOOL bIsDataPkg)
{
    oPackage.clear();
    switch(nPort)
    {
    case 0:
        oPackage.push_back(0xE1);
        break;
    case 1:
        oPackage.push_back(0xE2);
        break;
    case 2:
        oPackage.push_back(0xE3);
        break;
    case 3:
        oPackage.push_back(0xE4);
        break;
    case 4:
        oPackage.push_back(0xE5);
        break;
    case 5:
        oPackage.push_back(0xE6);
        break;
    case 6:
        oPackage.push_back(0xE7);
        break;
    case 7:
        oPackage.push_back(0xE8);
        break;
    }

    for(int i = 0;i < 15;i++)
    {
        oPackage.push_back((char)0);
    }

    if(otmtStable2M.m_nUseFlag == 0 || otmtStable2M.m_nAddr == -1)
    {
        for(int i = 0;i < 48;i++)
        {
            oPackage.push_back((char)0);
        }
        return;
    }

    QByteArray obytearray,obytearray2;
    obytearray.clear();
    obytearray2.clear();

    //Addr
    obytearray.push_back(otmtStable2M.m_nAddr & 0xFF);

    //Type
    if(bIsDataPkg)
    {
        obytearray.push_back(0x55);
    }
    else
    {
        obytearray.push_back(0x99);
    }

    long nFirstValue;
    for(int i = 0;i < MAX_2M_CHANNEL_COUNT;i++)
    {
        if(i < otmtStable2M.m_nChanNum)
        {
            Stable2MChanInfo  oChanInfo = otmtStable2M.m_oChanList[i];
            nFirstValue = oChanInfo.nFirstValue;

            if((otmtStable2M.m_nIdxMapChan - 1) == i)
            {
                nFirstValue = otmtStable2M.nIdxVal;
            }

            if(oChanInfo.nLen == 1)
            {
                obytearray.push_back(nFirstValue & 0xFF);
            }
            else
            {
                //小端模式
                obytearray.push_back(nFirstValue & 0xFF);
                obytearray.push_back((nFirstValue >> 8) & 0xFF);
            }
        }
    }
    long nNum = obytearray.size();
    if(nNum > 44)
    {
        nNum = 44;
        obytearray2.push_back(obytearray.left(44));
    }
    else
    {
        obytearray2.push_back(obytearray);
    }

    unsigned short nSum = SumCheck((unsigned char *)(obytearray2.data()),nNum);
    obytearray2.push_back(nSum & 0xFF);
    obytearray2.push_back((nSum >> 8) & 0xFF);

    unsigned short nCRC = CRC16((unsigned char *)(obytearray2.data()),nNum + 2,0xffff,0x1021,0xffff,true,true);
    obytearray2.push_back(nCRC & 0xFF);
    obytearray2.push_back((nCRC >> 8) & 0xFF);

    oPackage[1] = obytearray2.size();

    nNum = 48 - obytearray2.size();
    if(nNum < 0)
    {

    }
    else
    {
        for(int i = 0;i < nNum;i++)
        {
            obytearray2.push_back((char)0);
        }
    }

    oPackage.push_back(obytearray2);
}

void CIECStable2MComMngr::Create2MSubTmtStruct(CIecCfg2MInData *pIecData)
{
    if(pIecData->m_nUseFlag==0 || pIecData->m_nBlockType == 1)
        return;//数据报文暂时不用订阅判断，直接透传

    long nPort = pIecData->m_nFiberIndex;
    long nChanNum = pIecData->m_nChannelNum;
    if(nPort > -1 && nPort < 16)
    {

    }
    else
        return;

    long nDataPkgIdx = m_oStable2MSubList[nPort/8][nPort%8].m_nDataPkgCount;
    tmt_Stable2M *pStable2M = &m_oStable2MSubList[nPort/8][nPort%8].m_oDataPkg[nDataPkgIdx];
    pStable2M->m_nAddr = pIecData->m_nSmpCntType;//Addr
    pStable2M->nIdxVal = pIecData->m_nDelayTime;
    pStable2M->m_nIdxMapChan = 0;

    CString strAppChId;
    if(nChanNum > MAX_2M_CHANNEL_COUNT)
        return;

    long nPos = 2;// 02 55
    for(int nChan = 0;nChan < nChanNum;nChan++)
    {
        CIecCfg6044CommonCh * m_pCIecCfg2MCh=(CIecCfg6044CommonCh *)pIecData->m_pCfgChs->GetAtIndex(nChan);

        Stable2MChanInfo  *pChanInfo = &pStable2M->m_oChanList[nChan];
        if(m_pCIecCfg2MCh->m_nChLenth > 2)
            m_pCIecCfg2MCh->m_nChLenth = 2;
        pChanInfo->nLen = m_pCIecCfg2MCh->m_nChLenth;
        pChanInfo->nPos = nPos;
        nPos += pChanInfo->nLen;
        pChanInfo->nFirstValue = m_pCIecCfg2MCh->m_nValue;
        strAppChId = m_pCIecCfg2MCh->m_strAppChID;

        if(strAppChId.compare("t-delay") == 0)
        {
            pStable2M->m_nIdxMapChan = pChanInfo->nPos;//IdxMapPos
        }
    }

    pStable2M->m_nPkgLen = nPos + 4;//4字节校验位

    m_oStable2MSubList[nPort/8][nPort%8].m_nDataPkgCount++;
}
