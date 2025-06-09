// ProtocolBase.h: interface for the CProtocolBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_PROTOCOLBASE_H__)
#define _PROTOCOLBASE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProtocolGlobalBaseDefine.h"
#include "EpCycleMemBuffer.h"

//���Ļ��࣬���졢������ƥ�䱨��
class CProtocolBase : public CExBaseList  
{
public:
	CProtocolBase();
	virtual ~CProtocolBase();

//����
public:
	EPBUFFERPOS m_bufPos;
	DWORD m_dwPrototcol;   //��Լ������
	long m_nYxAddr;
	long m_nYcAddr;
	long m_nYtAddr;
	long m_nYkAddr;
	long m_nODDRLen;

//����
public:
	virtual CExBaseObject* Match(PEPBUFFERPOS pBufferPos) = 0;
	virtual CExBaseObject* Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList) = 0;

	virtual CExBaseObject* Match(CEpCycleMemBuffer *pBuffer)
	{
		ZeroMemory(&m_bufPos, sizeof(EPBUFFERPOS));
		//Ep_ZeroEpBufferPos(&m_bufPos);
		pBuffer->GetBufferPos(&m_bufPos);
		CExBaseObject *p = Match(&m_bufPos);
		return p;
	}

	virtual CExBaseObject* Parse(CEpCycleMemBuffer *pBuffer, CExBaseList *pDetailList, BOOL bAddDetail)
	{
		ZeroMemory(&m_bufPos, sizeof(EPBUFFERPOS));
		//Ep_ZeroEpBufferPos(&m_bufPos);
		m_bufPos.bAddDetail = bAddDetail;
		pBuffer->GetBufferPos(&m_bufPos);
		CExBaseObject *p = Parse(&m_bufPos, pDetailList);
		pBuffer->SetCurrPos(&m_bufPos);
		return p;
	}

	virtual void OnExit(){}

private:
};

class CProtocolBaseList : public CExBaseList
{
public:
	CProtocolBaseList()
	{

	}

	virtual ~CProtocolBaseList()
	{

	}

	CProtocolBase* FindByProtocolID(DWORD dwProtocolID)
	{
		POS pos = GetHeadPosition();
		CProtocolBase *pProtocol = NULL;
		CProtocolBase *pFind = NULL;

		while (pos != NULL)
		{
			pProtocol = (CProtocolBase *)GetNext(pos);

			if (pProtocol->m_dwPrototcol == dwProtocolID)
			{
				pFind = pProtocol;
				break;
			}
		}

		return pFind;
	}
};

#endif // !defined(_PROTOCOLBASE_H__)
