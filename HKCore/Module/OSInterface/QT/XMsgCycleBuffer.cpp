#include "stdafx.h"
#include "XMsgCycleBuffer.h"

CXMsgCycleBuffer::CXMsgCycleBuffer()
{
/*
    m_nLockFlag = 0; //访问的时候，加锁的标记
    m_nMaxCount = XMSG_CYCLE_BUF_MAX;
    m_nCurrIndex = 0;
    m_nCurrCount = 0;

    m_nCurrReadIndex = 0;  //当前写入数据库的位置
*/
    memset(m_oXmsg, 0, sizeof(XMSG_DEF)*XMSG_CYCLE_BUF_MAX);
}

CXMsgCycleBuffer::~CXMsgCycleBuffer()
{

}

void CXMsgCycleBuffer::AddMsg(unsigned long nMsgID, unsigned long wParam, unsigned long lParam)
{
    long nIndex = 0;
    PXMSG_DEF pFind = NULL;

    for (nIndex=0; nIndex<XMSG_CYCLE_BUF_MAX; nIndex++)
    {
        PXMSG_DEF pMsg = &m_oXmsg [nIndex];

        if (pMsg->flag != 0)
        {
            continue;
        }

        pMsg->nMsgID = nMsgID;
        pMsg->wParam = wParam;
        pMsg->lParam = lParam;
        pMsg->time = ::GetTickCount();
        pMsg->flag = 1;  // set flag == 1; the msg can used
        pFind = pMsg;
        break;
    }

    if (pFind == NULL)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("AddMsg(%d, %d, %d) error"), nMsgID, wParam, lParam);
    }
}

bool CXMsgCycleBuffer::PeekMsg( unsigned long &nMsgID, unsigned long &wParam, unsigned long &lParam)
{
    long nIndex = 0;
    unsigned long nCurrTick = ::GetTickCount();

    for (nIndex=0; nIndex<XMSG_CYCLE_BUF_MAX; nIndex++)
    {
        PXMSG_DEF pMsg = &m_oXmsg [nIndex];

        if (pMsg->flag == 0)
        {
            continue;
        }

        if (pMsg->nMsgID == WM_TIMER)
        {
            if (CalTickCountLong(nCurrTick, pMsg->time) >= pMsg->lParam)
            {//nMsgID==WM_TIMER; lParam=nElapse
                nMsgID = pMsg->nMsgID;
                wParam = pMsg->wParam;
                lParam  = pMsg->lParam ;
                pMsg->time = nCurrTick;
                return true;
            }
        }
        else
        {
            pMsg->flag = 0;
            nMsgID = pMsg->nMsgID;
            wParam = pMsg->wParam;
            lParam  = pMsg->lParam ;
            pMsg->nMsgID = 0;
            return true;
        }
    }

    return false;
}

void CXMsgCycleBuffer::RemoveMsg(unsigned long nMsgID, unsigned long wParam)
{
    long nIndex = 0;

    for (nIndex=0; nIndex<XMSG_CYCLE_BUF_MAX; nIndex++)
    {
        PXMSG_DEF pMsg = &m_oXmsg [nIndex];

        if (pMsg->flag == 0)
        {
            continue;
        }

        if ((pMsg->nMsgID == nMsgID) && (pMsg->wParam == wParam))
        {
            pMsg->flag = 0;
             pMsg->nMsgID = 0;
        }
    }
}

/*
void CXMsgCycleBuffer::stt_cycle_buffer_increase_curr_index()
{
    m_nCurrIndex++;

    if (m_nCurrIndex >= m_nMaxCount)
    {
        m_nCurrIndex = 0;
    }

    m_nCurrCount++;

    if (m_nCurrCount >= m_nMaxCount)
    {
        m_nCurrCount = m_nMaxCount;
    }
}

long CXMsgCycleBuffer::stt_cycle_buffer_get_count(long nIndexFrom)
{
    long nCurrCount = m_nCurrCount;
    long nCurrIndex = m_nCurrIndex;

    if (nCurrCount == m_nMaxCount)
    {
        if (nCurrIndex >= nIndexFrom)
        {
            return nCurrIndex - nIndexFrom;
        }
        else
        {
            return nCurrCount - nIndexFrom + nCurrIndex;
        }
    }
    else
    {
        if (nCurrIndex >= nIndexFrom)
        {
            return nCurrIndex - nIndexFrom;
        }
        else
        {
            return 0;
        }
    }
}

long CXMsgCycleBuffer::stt_cycle_buffer_get_read_count()
{
    return stt_cycle_buffer_get_count(m_nCurrReadIndex);
}

void CXMsgCycleBuffer::stt_cycle_buffer_set_read_index(long nIndex)
{
    m_nCurrReadIndex = nIndex;

    if (m_nCurrReadIndex >= m_nMaxCount)
    {
        m_nCurrReadIndex = 0;
    }
}
*/
