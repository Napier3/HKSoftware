#include "StdAfx.h"
#include "DeviceCmmChannel.h"
#include "CmmChannelCreateMngr.h"
#include "../PpEngineThreadBase.h"

CDeviceCmmChannel::CDeviceCmmChannel(void)
{
	m_pDeviceConfig = NULL;
	m_bConnecting = FALSE;
	m_dwCommMode = COMMMODE_NORMAL;
	m_pXPkgFullRcvJdgInterface = NULL;
	m_pProtoPkgPrcss = NULL;
	m_pEngineDataRef = NULL;
}

CDeviceCmmChannel::~CDeviceCmmChannel(void)
{
	m_oCmmRcvSndTimeMngr.DeleteAll();
}

void SetCommMode(const CString &strMode)
{

}


//管理通道连接的相关函数

//与设备建立连接
//遍历子对象的CmmChannel对象
//调用其连接函数CreateChannel
BOOL CDeviceCmmChannel::ConnectDevice(CDeviceCmmConfig *pDeviceConfig, BOOL bCreateChannel)
{
	m_bConnecting = TRUE;
	m_pDeviceConfig = pDeviceConfig;
	
	if ( !ConnectDevice(bCreateChannel) )
	{
		m_bConnecting = FALSE;
	}

	return TRUE;
}

BOOL CDeviceCmmChannel::ConnectDevice(BOOL bCreateChannel)
{
	ASSERT (m_pDeviceConfig != NULL);

	if (m_pDeviceConfig == NULL)
	{
		return FALSE;
	}

	if (bCreateChannel)
	{
		CreateCmmChannel();
	}

	CCmmChannel *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCmmChannel*)GetNext(pos);
		p->ResetState();
	}

	pos = GetHeadPosition();
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		p = (CCmmChannel*)GetNext(pos);

		if (!p->Connect() )
		{
            //底层自动测试时，联机监视到connect被拒绝，此处再连接一次；
            //shaolei 20201214
            CTickCount32 oTick;
            oTick.DoEvents(2000);

            if (!p->Connect() )
            {
                p->OnConnectFinished();  //shaolei 20201214
                bTrue = FALSE;
            }
		}
	}
	
	return bTrue;
}

#include"../../../../Module/API/GlobalConfigApi.h"
#include"../../../../Module/API/FileApi.h"

void Global_WriteLogTxtFile_IotPxEngineServerDisConnectDevice(const CString &strLogString)
{
//	if (g_nWriteLogTxtFile == 0)
//	{
//		return;
//	}

	CFile oFile;
	CString strPath;
	strPath = _P_GetBinPath();
	strPath += "IotProtoServer_DisConnectDevice.txt";
	BOOL bRet = FALSE;

	if (!IsFileExist(strPath))
	{
		bRet = oFile.Open(strPath, CFile::modeCreate | CFile::modeWrite);
	}
	else
	{
#ifdef _PSX_IDE_QT_
		bRet = oFile.Open(strPath, CFile::modeNoTruncate/*modeWrite*/);
#else
		bRet = oFile.Open(strPath, CFile::modeWrite);
#endif
	}
 
	if (bRet)
	{
		oFile.SeekToEnd();
		SYSTEMTIME tm;
		CString strTmp;
		::GetLocalTime(&tm);
		strTmp.Format(_T("%d-%d-%d %d-%d-%d.%d   "), tm.wYear, tm.wMonth, tm.wDay
			, tm.wHour, tm.wMinute, tm.wSecond,tm.wMilliseconds);

		strTmp += strLogString;
		char *pWriteString = NULL;
		CString_to_char(strTmp,&pWriteString);
		oFile.Write(pWriteString, strlen(pWriteString));
		oFile.Write("\r\n", 2);
		oFile.Close();
		delete pWriteString;

	}
}

BOOL CDeviceCmmChannel::DisConnectDevice()
{
	CExBaseList oList;
	oList.Append(this);
	RemoveAll();
	CCmmChannel *p = NULL;
	POS pos = oList.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CCmmChannel*)oList.GetNext(pos);
		p->DisConnect();
	}

	//等待通讯线程结束
#ifdef _PSX_QT_LINUX_//zhouhj 2025.1.16 在Linux下增加等待时间
	Global_WriteLogTxtFile_IotPxEngineServerDisConnectDevice("CDeviceCmmChannel::DisConnectDevice()");
	Sleep(100);
	oList.DeleteAll();
//    oList.RemoveAll();
#else
	Sleep(5);
	oList.DeleteAll();
#endif

	return FALSE;
}

void CDeviceCmmChannel::CreateCmmChannel()
{
	ASSERT (m_pDeviceConfig != NULL);

	POS pos = m_pDeviceConfig->GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;
	DeleteAll();

	while (pos != NULL)
	{
		p = m_pDeviceConfig->GetNext(pos);
		nClassID = p->GetClassID();

		switch (nClassID)
		{
		case DMCLASSID_CMM_SERIAL_CONFIG:
			{
#ifndef _PSX_IDE_QT_
                CCmmSerialChannel *pChannel = new CCmmSerialChannel();
				pChannel->SetParent(this);
				pChannel->m_pXPkgFullRcvJdgInterface = m_pXPkgFullRcvJdgInterface;
				pChannel->m_pProtoPkgPrcss = m_pProtoPkgPrcss;
				pChannel->Create(p);
				pChannel->m_strID = p->m_strID;
				AddTail(pChannel);
#endif
            }

			break;

		case DMCLASSID_NET_CONFIG:
			{
				CCmmNetConfig *pCmmNetConfig = (CCmmNetConfig*)p;
				POS posEx = pCmmNetConfig->GetHeadPosition();
				CExBaseObject *pObj = NULL;
				UINT nClassIDEx = 0;
				while (posEx != NULL)
				{
					pObj = pCmmNetConfig->GetNext(posEx);
					nClassIDEx = pObj->GetClassID();
					switch (nClassIDEx)
					{
					case DMCLASSID_CMM_TCP_CLIENT_CONFIG:
						{
							CCmmTcpClientChannel *pChannel = new CCmmTcpClientChannel();
							pChannel->m_pXPkgFullRcvJdgInterface = m_pXPkgFullRcvJdgInterface;
							pChannel->m_pProtoPkgPrcss = m_pProtoPkgPrcss;
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->Create(pObj);
							pChannel->m_strID = pObj->m_strID;
							AddTail(pChannel);
						}

						break;

					case DMCLASSID_CMM_TCP_SERVER_CONFIG:
						{
                            CCmmTcpServerChannel *pChannel = new CCmmTcpServerChannel();
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->m_pXPkgFullRcvJdgInterface = m_pXPkgFullRcvJdgInterface;
							pChannel->m_pProtoPkgPrcss = m_pProtoPkgPrcss;
							pChannel->Create(pObj);
							AddTail(pChannel);
							pChannel->m_strID = pObj->m_strID;
                        }

						break;

					case DMCLASSID_CMM_UDP_CLIENT_CONFIG:
						{
                            CCmmUdpClientChannel *pChannel = new CCmmUdpClientChannel();
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->m_pXPkgFullRcvJdgInterface = m_pXPkgFullRcvJdgInterface;
							pChannel->m_pProtoPkgPrcss = m_pProtoPkgPrcss;
							pChannel->Create(pObj);
							pChannel->m_strID = pObj->m_strID;
							AddTail(pChannel);
                        }

						break;

					case DMCLASSID_CMM_UDP_SERVER_CONFIG:
						{
#ifndef _PSX_IDE_QT_
                            CCmmUdpServerChannel *pChannel = new CCmmUdpServerChannel();
							((CExBaseObject*)pChannel)->SetParent(this);
							pChannel->m_pXPkgFullRcvJdgInterface = m_pXPkgFullRcvJdgInterface;
							pChannel->m_pProtoPkgPrcss = m_pProtoPkgPrcss;
							pChannel->Create(pObj);
							pChannel->m_strID = pObj->m_strID;
							AddTail(pChannel);
#endif
                        }

						break;
					}
				}
			}

			break;
		
		}//end of "switch (nClassID)"
	}//end of "while (pos != NULL)"
}

BOOL CDeviceCmmChannel::OnReceive(CCmmChannel *pChannel, CCmmRcvSndTime *pCmmTime)
{
	m_oCmmRcvSndTimeMngr.AddTail(pCmmTime);
	m_oCmmRcvSndTimeMngr.DeletePrev(pCmmTime);
	((CPpEngineThreadBase*)m_pThread)->PostThreadMessage(WM_THREAD_RECEIVE, (WPARAM)pChannel, (LPARAM)pCmmTime);
	return TRUE;
}

BOOL CDeviceCmmChannel::OnCmmChannelClose(CCmmChannel *pChannel)
{
	((CPpEngineThreadBase*)m_pThread)->OnCmmChannelClose(pChannel);
	return TRUE;
}

BOOL CDeviceCmmChannel::ConnetAllClient( CCmmUdpServerChannel *pUdpServerChannel )
{
	POS pos = GetHeadPosition();
	CCmmChannel *pChannel = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		pChannel = (CCmmChannel*)GetNext(pos);
		nClassID = pChannel->GetClassID();

		if (nClassID == CMMCLASSID_TCP_CLIENT_CHANNEL
			|| nClassID == CMMCLASSID_UDP_CLIENT_CHANNEL)
		{
			if (!pChannel->IsConnectSuccessful())
			{
				ConnetClient(pUdpServerChannel, pChannel);
			}
		}
	}

	return TRUE;
}

BOOL CDeviceCmmChannel::IsConnectSuccessful()
{
	POS pos = GetHeadPosition();

	if (pos == NULL)
	{
		return FALSE;
	}

	CCmmChannel *pChannel = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pChannel = (CCmmChannel*)GetNext(pos);
		
		if (! pChannel->IsConnectSuccessful())
		{
			bSucc = FALSE;
			break;
		}
	}

	return bSucc;
}


void CDeviceCmmChannel::OnCmmChannelConnectFinish()
{
// 	CPpEngineThread *pThread = (CPpEngineThread*)m_pThread;
	BOOL bConnectFinish = TRUE;
	POS pos = GetHeadPosition();
	CCmmChannel *pChannel = NULL;
	BOOL bSucc = TRUE;

	while (pos != NULL)
	{
		pChannel = (CCmmChannel*)GetNext(pos);

		if (! pChannel->HasConnected())
		{
			bConnectFinish = FALSE;
			break;
		}
	}

	if (bConnectFinish)
	{
		//pThread->OnDeviceConnectFinish(IsConnectSuccessful());
		BOOL bSuccesss = IsConnectSuccessful();
		m_pThread->PostThreadMessage(WM_THREAD_CONNECT_FINISHED, bSuccesss, bSuccesss);
	}

	m_bConnecting = FALSE;
}

void CDeviceCmmChannel::OnCmmChannelConnectFailed()
{
	BOOL bConnectFinish = TRUE;
	BOOL bSuccesss = IsConnectSuccessful();
	m_pThread->PostThreadMessage(WM_THREAD_CONNECT_FAILED, bSuccesss, bSuccesss);
}

BOOL CDeviceCmmChannel::IsAllCmmChannelExit()
{
	POS pos = GetHeadPosition();
	CCmmChannel *pChannel = NULL;
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		pChannel = (CCmmChannel*)GetNext(pos);

		if (! pChannel->IsCmmChannelExit())
		{
			bTrue = FALSE;
			break;
		}
	}

	return bTrue;
}

BOOL CDeviceCmmChannel::ConnetClient(CCmmUdpServerChannel *pUdpServerChannel, CCmmChannel *pClientChannel)
{
	UINT nClassID = pClientChannel->GetClassID();

	if (nClassID == CMMCLASSID_TCP_CLIENT_CHANNEL)
	{
		CCmmTcpClientChannel *pTcpClient = (CCmmTcpClientChannel*)pClientChannel;
		pTcpClient->m_pConfig->m_strRemoteIP = inet_ntoa(pUdpServerChannel->m_oSocketAddrIn.sin_addr);
		pTcpClient->Connect();
	}
	else if (nClassID == CMMCLASSID_UDP_CLIENT_CHANNEL)
	{
		//暂时不考虑此种方式
	}
	else
	{

	}

	return TRUE;
}


