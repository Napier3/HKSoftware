#include "StdAfx.h"
#include "EpDeviceCmmChannel.h"
#include "EpCmmChannelCreateMngr.h"

CEpDeviceCmmChannel::CEpDeviceCmmChannel(void)
{
	m_pDeviceConfig = NULL;
	m_bConnecting = FALSE;
}

CEpDeviceCmmChannel::~CEpDeviceCmmChannel(void)
{
	m_oCmmRcvSndTimeMngr.DeleteAll();
}


//管理通道连接的相关函数

//与设备建立连接
//遍历子对象的CmmChannel对象
//调用其连接函数CreateChannel
BOOL CEpDeviceCmmChannel::ConnectDevice(CEpDeviceCmmConfig *pDeviceConfig)
{
	m_bConnecting = TRUE;
	m_pDeviceConfig = pDeviceConfig;
	ConnectDevice();

	return TRUE;
}

BOOL CEpDeviceCmmChannel::ConnectDevice()
{
	ASSERT (m_pDeviceConfig != NULL);

	if (m_pDeviceConfig == NULL)
	{
		return FALSE;
	}

	CreateCmmChannel();

	CEpCmmChannel *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpCmmChannel*)GetNext(pos);
		p->ResetState();
	}

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpCmmChannel*)GetNext(pos);
		p->Connect();
	}
	
	return FALSE;
}

BOOL CEpDeviceCmmChannel::DisConnectDevice()
{
	CEpCmmChannel *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CEpCmmChannel*)GetNext(pos);
		p->DisConnect();
	}
	return FALSE;
}

void CEpDeviceCmmChannel::CreateCmmChannel()
{
	ASSERT (m_pDeviceConfig != NULL);

	POS pos = m_pDeviceConfig->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = m_pDeviceConfig->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case EPCLASSID_CMM_SERIAL_CONFIG:
			{
				CEpCmmSerialChannel *pChannel = new CEpCmmSerialChannel();
				pChannel->SetParent(this);
				pChannel->Create(p);
				pChannel->m_strID = p->m_strID;
				AddTail(pChannel);
			}

			break;

		case EPCLASSID_NET_CONFIG:
			{
				CEpCmmNetConfig *pCmmNetConfig = (CEpCmmNetConfig*)p;
				POS posEx = pCmmNetConfig->GetHeadPosition();
				CExBaseObject *pObj = NULL;
				UINT nClassIDEx = 0;
				while (posEx != NULL)
				{
					pObj = pCmmNetConfig->GetNext(posEx);
					nClassIDEx = pObj->GetClassID();
					switch (nClassIDEx)
					{
					case EPCLASSID_CMM_TCP_CLIENT_CONFIG:
						{
							CEpCmmTcpClientChannel *pChannel = new CEpCmmTcpClientChannel();
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->Create(pObj);
							pChannel->m_strID = pObj->m_strID;
							AddTail(pChannel);
						}

						break;

					case EPCLASSID_CMM_TCP_SERVER_CONFIG:
						{
							CEpCmmTcpServerChannel *pChannel = new CEpCmmTcpServerChannel();
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->Create(pObj);
							AddTail(pChannel);
							pChannel->m_strID = pObj->m_strID;
						}

						break;

					case EPCLASSID_CMM_UDP_CONFIG:
						{
							CEpCmmUdpClientChannel *pChannel = new CEpCmmUdpClientChannel();
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->Create(pObj);
							pChannel->m_strID = pObj->m_strID;
							AddTail(pChannel);
						}

						break;

					case EPCLASSID_CMM_UDP_SERVER_CONFIG:
						{
							CEpCmmUdpServerChannel *pChannel = new CEpCmmUdpServerChannel();
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->Create(pObj);
							pChannel->m_strID = pObj->m_strID;
							AddTail(pChannel);
						}

						break;
					}
				}
			}

			break;
		
		}//end of "switch (nClassID)"
	}//end of "while (pos != NULL)"
}

BOOL CEpDeviceCmmChannel::OnReceive(CEpCmmChannel *pChannel, CEpCmmRcvSndTime *pCmmTime)
{
	m_oCmmRcvSndTimeMngr.AddTail(pCmmTime);
//	((CEpEngineThread*)m_pThread)->PostThreadMessage(WM_THREAD_RECEIVE, (WPARAM)pChannel, (LPARAM)pCmmTime);
	return TRUE;
}

BOOL CEpDeviceCmmChannel::ConnetAllClient( CEpCmmUdpServerChannel *pUdpServerChannel )
{
	POS pos = GetHeadPosition();
	CEpCmmChannel *pChannel = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pChannel = (CEpCmmChannel*)GetNext(pos);
		nClassID = pChannel->GetClassID();

		if (nClassID == EPCMMCLASSID_TCP_CLIENT_CHANNEL
			|| nClassID == EPCMMCLASSID_UDP_CLIENT_CHANNEL)
		{
			if (!pChannel->IsConnectSuccessful())
			{
				ConnetClient(pUdpServerChannel, pChannel);
			}
		}
	}

	return TRUE;
}

BOOL CEpDeviceCmmChannel::IsConnectSuccessful()
{
	POS pos = GetHeadPosition();

	if (pos == NULL)
	{
		return FALSE;
	}

	CEpCmmChannel *pChannel = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pChannel = (CEpCmmChannel*)GetNext(pos);
		
		if (! pChannel->IsConnectSuccessful())
		{
			bSucc = FALSE;
			break;
		}
	}

	return bSucc;
}


void CEpDeviceCmmChannel::OnCmmChannelConnectFinish()
{
//	CEpEngineThread *pThread = (CEpEngineThread*)m_pThread;
	
	BOOL bConnectFinish = TRUE;
	POS pos = GetHeadPosition();
	CEpCmmChannel *pChannel = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pChannel = (CEpCmmChannel*)GetNext(pos);

		if (! pChannel->HasConnected())
		{
			bConnectFinish = FALSE;
			break;
		}
	}

// 	if (bConnectFinish)
// 	{
// 		pThread->OnDeviceConnectFinish(IsConnectSuccessful());
// 	}

	m_bConnecting = FALSE;
}

BOOL CEpDeviceCmmChannel::IsAllCmmChannelExit()
{
	POS pos = GetHeadPosition();
	CEpCmmChannel *pChannel = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pChannel = (CEpCmmChannel*)GetNext(pos);

		if (! pChannel->IsEpCmmChannelExit())
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

BOOL CEpDeviceCmmChannel::ConnetClient(CEpCmmUdpServerChannel *pUdpServerChannel, CEpCmmChannel *pClientChannel)
{
	UINT nClassID = pClientChannel->GetClassID();

	if (nClassID == EPCMMCLASSID_TCP_CLIENT_CHANNEL)
	{
		CEpCmmTcpClientChannel *pTcpClient = (CEpCmmTcpClientChannel*)pClientChannel;
		pTcpClient->m_pConfig->m_strRemoteIP = inet_ntoa(pUdpServerChannel->m_oSocketAddrIn.sin_addr);
		pTcpClient->Connect();
	}
	else if (nClassID == EPCMMCLASSID_UDP_CLIENT_CHANNEL)
	{
		//暂时不考虑此种方式
	}
	else
	{

	}

	return TRUE;
}

CEpCmmChannel* CEpDeviceCmmChannel::FindCmmChannel(const CString &strChannelID)
{
	POS pos = GetHeadPosition();
	CEpCmmChannel *pChannel = NULL;
	CEpCmmChannel *pFind = NULL;
	CEpCmmChannel *pTemp = NULL;

	while (pos != NULL)
	{
		pChannel = (CEpCmmChannel *)GetNext(pos);
		pTemp = pChannel->FindCmmChannel(strChannelID);

		if (pTemp != NULL)
		{
			pFind = pTemp;
			break;
		}
	}

	return pFind;
}

CEpCmmChannel* CEpDeviceCmmChannel::FindCmmChannel(UINT nClassID)
{
	POS pos = GetHeadPosition();
	CEpCmmChannel *pChannel = NULL;
	CEpCmmChannel *pFind = NULL;
	CEpCmmChannel *pTemp = NULL;

	while (pos != NULL)
	{
		pChannel = (CEpCmmChannel *)GetNext(pos);
		pTemp = pChannel->FindCmmChannel(nClassID);

		if (pTemp != NULL)
		{
			pFind = pTemp;
			break;
		}
	}

	return pFind;
}
