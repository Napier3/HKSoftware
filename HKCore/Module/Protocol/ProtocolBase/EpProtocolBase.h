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

//报文基类，制造、解析、匹配报文
class CEpProtocolBase : public CProtocolBase  
{
public:
	CEpProtocolBase();
	virtual ~CEpProtocolBase();

//属性
public:
	CEpFrameGroup  *m_pParseFrames;   //解析帧管理
	CEpFrameGroup  *m_pProduceFrames; //制造帧管理
	CEpFrameGroups *m_pFrameGroups;  //规约帧组管理
//	CEpProcedures   *m_pEpProcedures;  //过程管理
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
//通讯通道定义
protected:
	CEpDevice *m_pDevice;
	//CEpDeviceCmmChannel *m_pDeviceCmmChannel;    //关联的设备通讯对象

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
