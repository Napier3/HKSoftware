// EpProtocolBase.h: interface for the CEpProtocolBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EPPROTOCOLBASE_H__)
#define _EPPROTOCOLBASE_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\ProtocolBase\ProtocolBase.h"
#include "EpProcedures.h"
#include "EpFrameGroup.h"
//#include "..\CmmChannel\config\EpDeviceCmmConfig.h"
#include "..\Device\EpDevice.h"

//���Ļ��࣬���졢������ƥ�䱨��
class CEpProtocolBase : public CProtocolBase  
{
public:
	CEpProtocolBase();
	virtual ~CEpProtocolBase();

//����
public:
	CEpFrameGroup  *m_pParseFrames;   //����֡����
	CEpFrameGroup  *m_pProduceFrames; //����֡����
	CEpFrameGroups *m_pFrameGroups;  //��Լ֡�����
//	CEpProcedures   *m_pEpProcedures;  //���̹���
//	CEpDeviceCmmConfig *m_pCmmConfig;
	CString m_strDefaultChannel;

	long m_nFrameMaxLength;
	long m_nFrameMinLength;


public:
	UINT GetClassID()	{	return EPCLASSID_PROTOCOL;	}

public:
	void AddParseFrame(CEpFrameBase *pFrame);
	void AddProduceFrame(CEpFrameBase *pFrame);
	void AddFrameGroup(CEpFrameGroup *pGroup);
	void AddProcedure(CEpProcedure *pProcedure);

	CEpFrameBase* Match(PEPBUFFERPOS pBufferPos);
	CEpFrameBase* Parse(PEPBUFFERPOS pBufferPos, CExBaseList *pDetailList);

	CEpFrameBase* FindFrameByID(DWORD dwClassID);

public:
	virtual void InitDeviceNodes(){}

//////////////////////////////////////////////////////////////////////////
//ͨѶͨ������
protected:
	CEpDevice *m_pDevice;
	//CEpDeviceCmmChannel *m_pDeviceCmmChannel;    //�������豸ͨѶ����

public:
	void AttachDevice(CEpDevice *pDevice);
	//void AttachDeviceCmmChannel(CEpDeviceCmmChannel *pChannel);
	//CEpCmmChannel* FindCmmChannel(const CString &strChannelID);

	long GetDeviceAddress()
	{
		if (m_pDevice == NULL)
		{
			return 0;
		}

		return m_pDevice->m_nAddress;
	}
};

CEpCmmChannel* Ep_FindCmmChannel(CExBaseObject *pObj, const CString &strChannelID);

#endif // !defined(_EPPROTOCOLBASE_H__)
