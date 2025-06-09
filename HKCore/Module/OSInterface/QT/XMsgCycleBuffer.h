#pragma once

 //2023.10.26 zhouhj 100 ��Ϊ200   330�ڲ���ʱ������ʱ,ԭ100����ȫ������
#define XMSG_CYCLE_BUF_MAX  200 

class CXMsgCycleBuffer
{
public:
    typedef struct xmsg_def
    {
        unsigned long flag;  //flag == 0 / 1  2022-10-31  lijunqing
        unsigned long nMsgID;
        unsigned long wParam;   //nMsgID==WM_TIMER; wParam=nIDEvent
        unsigned long lParam;  //nMsgID==WM_TIMER; lParam=nElapse
        unsigned long time;
    }XMSG_DEF, *PXMSG_DEF;

public:
    CXMsgCycleBuffer();
    ~CXMsgCycleBuffer();

public:
    void AddMsg(unsigned long nMsgID, unsigned long wParam, unsigned long lParam);
    bool PeekMsg( unsigned long &nMsgID, unsigned long &wParam, unsigned long &lParam);
    void RemoveMsg(unsigned long nMsgID, unsigned long wParam);

protected:
/*
    long m_nLockFlag; //���ʵ�ʱ�򣬼����ı��
    long m_nMaxCount;
    long m_nCurrIndex;
    long m_nCurrCount;

    long m_nCurrReadIndex;  //��ǰд�����ݿ��λ��
*/

    XMSG_DEF m_oXmsg[XMSG_CYCLE_BUF_MAX];

    unsigned long CalTickCountLong(unsigned long dwEndTick, unsigned long dwBeginTick)
    {
        unsigned long dwLong = 0;

        if (dwEndTick < dwBeginTick)
        {
            dwLong = 0xFFFFFFFF - dwBeginTick;
            dwLong += dwEndTick;
        }
        else
        {
            dwLong = dwEndTick - dwBeginTick;
        }

        return dwLong;
    }
/*
protected:
    void stt_cycle_buffer_increase_curr_index();
    long stt_cycle_buffer_get_count(long nIndexFrom);
    long stt_cycle_buffer_get_read_count();
    void stt_cycle_buffer_set_read_index(long nIndex);
*/
};
