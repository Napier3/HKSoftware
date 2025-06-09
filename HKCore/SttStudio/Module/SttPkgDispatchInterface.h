#pragma once
#include "../../Module/CriticalSection/SynCriticalSection.h"

//#ifdef _PSX_IDE_QT_
//#include "../../Module/OSInterface/OSInterface.h"
//#endif


//2022-2-12  lijunqing 报文转发,例如：自动测试控制服务，收到的测试仪事件报文，通过自动测试控制通信通道转发给上位机软件
class CSttPkgDispatchInterface
{
public:
    CSttPkgDispatchInterface(){}
    virtual ~CSttPkgDispatchInterface(){}

    virtual void DispatchMsg(unsigned char *pBuf, long nLen) = 0;

};

#define SttPkgDispatchInterfaces_count 10

class CSttPkgDispatchInterfaces
{
public:
	CSttPkgDispatchInterfaces()
	{
		int i = 0;

		for (i=0; i<SttPkgDispatchInterfaces_count; i++)
		{
			m_arInterface[i] = 0;
		}
	}

	virtual ~CSttPkgDispatchInterfaces(){};

	CSttPkgDispatchInterface* m_arInterface[SttPkgDispatchInterfaces_count];
	CAutoCriticSection m_oCriticSection;

public:
    void DispatchMsg(unsigned char *pBuf, long nLen)
	{
		CAutoSimpleLock oLock(m_oCriticSection);
		int i = 0;

		for (i=0; i<SttPkgDispatchInterfaces_count; i++)
		{
			if (m_arInterface[i] != 0)
			{
				m_arInterface[i]->DispatchMsg(pBuf, nLen);
			}
		}
	}

	void Add(CSttPkgDispatchInterface *p)
	{
		CAutoSimpleLock oLock(m_oCriticSection);

		if (IsExist(p))
		{
			return;
		}

		int i = 0;

		for (i=0; i<SttPkgDispatchInterfaces_count; i++)
		{
			if (m_arInterface[i] == 0)
			{
				m_arInterface[i] = p;
                break;
			}
		}
	}

	void Remove(CSttPkgDispatchInterface *p)
	{
		CAutoSimpleLock oLock(m_oCriticSection);
		int i = 0;

		for (i=0; i<SttPkgDispatchInterfaces_count; i++)
		{
			if (m_arInterface[i] == p)
			{
				m_arInterface[i] =  0;
			}
		}
	}

    bool IsExist(CSttPkgDispatchInterface *p)
	{
		int i = 0;

		for (i=0; i<SttPkgDispatchInterfaces_count; i++)
		{
			if (m_arInterface[i] == p)
			{
                return true;
			}
		}

        return false;
	}

};
