#include "stdafx.h"
#include "RingMemBufShm.h"

#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "QEventLoop"
#include "QTimer"
#include "QNetworkInterface"
#include "QTextCodec"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

CRingMemBufShm::CRingMemBufShm()
{
    m_shm = NULL;
    m_nShareMemoryId = -1;
    m_nShmkey = 2022;
}

CRingMemBufShm::~CRingMemBufShm()
{
    if(m_nShareMemoryId != -1)
    {
        shmdt(m_shm);
        shmctl(m_nShareMemoryId, IPC_RMID, 0);
    }
}


void CRingMemBufShm::ShmCreateServer()
{
    //需要申请共享内存
    m_nShareMemoryId = shmget((key_t)m_nShmkey, DEFAULT_CIRCLEBUF_LEN, 0666|IPC_CREAT);

    if(m_nShareMemoryId == -1)
    {
        CLogPrint::LogString(XLOGLEVEL_ERROR,_T("Requset ShareMemoryId Fail"));
    }

   m_shm = shmat(m_nShareMemoryId, (void *)0, 0);
    if(m_shm == (void*)-1)
    {
        CLogPrint::LogString(XLOGLEVEL_ERROR,_T("Requset ShareMemoryAddr Fail"));
    }

    Attatch((char*)m_shm,DEFAULT_CIRCLEBUF_LEN, true);
}

void CRingMemBufShm::ShmCreateClient()
{
   m_nShareMemoryId = shmget((key_t)m_nShmkey, DEFAULT_CIRCLEBUF_LEN, 0666|IPC_CREAT);

    if(m_nShareMemoryId == -1)
    {
        CLogPrint::LogString(XLOGLEVEL_ERROR,"nShareMemoryId fail");
    }

    m_shm = shmat(m_nShareMemoryId, (void *)0, 0);
    
    if(m_shm == (void*)-1)
    {
        CLogPrint::LogString(XLOGLEVEL_ERROR,"ShareMemoryAddr fail");
    }

     Attatch((char*)m_shm,DEFAULT_CIRCLEBUF_LEN, false);
}

