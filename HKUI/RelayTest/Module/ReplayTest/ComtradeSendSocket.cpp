#include "stdafx.h"
#include "ComtradeSendSocket.h"
#include "ComtradeBufMngr.h"
//#include "BigComtradeTransPlay.h"
#ifdef _PSX_QT_LINUX_
#include"../../../Module/OSInterface/QT/XGlobalDefine_QT.h"
#endif


CComtradeSendSocket::CComtradeSendSocket()
{
	m_pbAnalysisFinish = NULL;
	m_pSttComtradeSendThread = NULL;
	m_pSttSocket = NULL;

	m_pClientEngineRef = NULL;
	m_nCurrSendDataIndex = -1;
	m_bSendDataStartAck = FALSE;

// 	if  (!stt_rcd_buf_zip_init())
// 	{
// 		g_nSttRcdSocketUseZip = 0;
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, "internal error - lzo_init() failed !!!\n");
// 		CLogPrint::LogString(XLOGLEVEL_ERROR, "(this usually indicates a compiler bug - try recompiling\nwithout optimizations, and enable '-DLZO_DEBUG' for diagnostics)\n");
// 	}
}

CComtradeSendSocket::~CComtradeSendSocket()
{
	Close();
	WaitForThreadExit();
}

void CComtradeSendSocket::WaitForThreadExit()
{
//	CTickCount32 oTick;

	while(m_pSttComtradeSendThread != NULL)
	{
		Sleep(5);
//		oTick.DoEvents(5);
	}
}

void CComtradeSendSocket::AttatchSocketDatabase(CSttSocketDataBase *pSttSocket)
{
	Close();
	WaitForThreadExit();

	m_pSttSocket = pSttSocket;
	Attach(pSttSocket->Detatch());

#ifdef _PSX_QT_LINUX_
	pthread_create(&m_pSttComtradeSendThread,NULL,SttComtradeSendThread,(LPVOID)this );
#else
	m_pSttComtradeSendThread =  CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)SttComtradeSendThread,(LPVOID)this,0,NULL);
#endif	
}

void CComtradeSendSocket::AttatchClientTestEngine(CSttTestEngineClientData *pEngine)
{
	m_pClientEngineRef = pEngine;
}

void CComtradeSendSocket::OnClose(int nErrorCode)
{
	if(m_pSttSocket != NULL)
	{
		m_pSttSocket->OnSocketClose(nErrorCode);
		m_pSttSocket = NULL;
	}
}

long CComtradeSendSocket::SttRcdSocketSend(BYTE *buffer, long nLen,long nIndex)
{
	long nSendCnt = 0;
	long nZipLen = nLen;
	BYTE *buffer_zip = (BYTE*)m_chSendBuf_Zip;
	long nDelaySendCnt = 0;

	BOOL bSendFast = FALSE;
	if (nIndex <= 2)
	{
		bSendFast = TRUE;
	}

// 	if (g_nSttRcdSocketUseZip)
// 	{
// 		BOOL bRet = stt_rcd_buf_zip(buffer, nLen, buffer_zip, nZipLen);
// 
// 		if (bRet)
// 		{
// 			if (m_hSocket != 0)
// 			{//测试用
// 				int nOnceSendLen = 0;
// 				int nRetLen = 0;
// 				while (nSendCnt != nZipLen)
// 				{
// 					nOnceSendLen = min(4096,nZipLen-nSendCnt);
// 					nRetLen = Send(m_hSocket, (char*)buffer_zip+nSendCnt, nOnceSendLen);
// 					if (nRetLen < 0)
// 					{
// 						nSendCnt = -1;
// 						break;
// 					}
// 					nSendCnt += nRetLen;
// 					Sleep(3);
// 				}
// 				
// 			}
// 		}
// 	}
// 	else
	{
		if (m_hSocket != 0)
		{//测试用

// #ifdef _Stt_Cmtrd_Save_File_	
// 			CString strTemp;
// 			int nWritePos = 0;
// 			int nOnceWrite = 10000;
// 			float*  pTemp = (float*)buffer;
// 			int nTempLen = nZipLen/4;
// 			while (nTempLen > nWritePos)
// 			{
// 				strTemp = _T("");
// 				nOnceWrite = min(10000,nTempLen-nWritePos);
// 				for (int i=0; i<nOnceWrite/8; i++)
// 				{
// 					strTemp.AppendFormat(_T("%.3f\r\n"),pTemp[nWritePos+8*i]);
// 				}
// 				m_oCmtrdSaveFile.Write(strTemp.GetString(),strTemp.GetLength());
// 				nWritePos += nOnceWrite;
// 			}
// 			
// #endif

			int nOnceSendLen = 0;
			int nRetLen = 0;
			while (nSendCnt != nZipLen)
			{
                nOnceSendLen = min((long)9000,nZipLen-nSendCnt);
				nRetLen = Send(m_hSocket, (char*)buffer+nSendCnt, nOnceSendLen);
				if (nRetLen < 0)
				{
					nSendCnt = -1;
					break;
				}
				nSendCnt += nRetLen;

				if (!bSendFast)
				{
					Sleep(5);
				}	
			}

			//nSendCnt = Send(m_hSocket, (char*)buffer, nZipLen);
		}
	}

	return nSendCnt;
}

#ifdef _PSX_QT_LINUX_
void *SttComtradeSendThread(LPVOID pParam)
{
#else
UINT CComtradeSendSocket::SttComtradeSendThread(LPVOID pParam)
{
	InitSocket();
#endif

	int nCurIndex = -1;
	int nCurDataLen = 0;
	long nSendCnt = 0;
	CComtradeDataBuffer *pComtradeBuf = NULL;
	CComtradeSendSocket *pSocket = (CComtradeSendSocket*)pParam;
	BYTE *buffer_zip = (BYTE*)pSocket->m_chSendBuf_Zip;
	pSocket->m_bClosing = FALSE;

//	stt_rcd_zip_buf_match_head(buffer_zip);

	while (1)
	{
		if (pSocket->m_hSocket == 0)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("ExitComtradeSendThread  m_hSocket <= 0"));
			break;
		}

// 		if( pSocket->IsSocketClose())
// 		{
// 			pSocket->m_bClosing = FALSE;
// 			pSocket->CWinBaseSocket::Close();
// 			break;
// 		}

		if( pSocket->m_bClosing)
		{
			pSocket->m_bClosing = FALSE;
			pSocket->CWinBaseSocket::Close();
			break;
		}

		nCurIndex = pSocket->m_nCurrSendDataIndex;
		pSocket->m_nCurrSendDataIndex = -1;

		if (nCurIndex < 0)
		{//没读到数据
			Sleep(1);
			continue;
		}

		pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nCurIndex);
		if (!pComtradeBuf->CanRead())
		{//数据未准备好，继续查询该缓存是否准备好
			pSocket->m_nCurrSendDataIndex = nCurIndex;
			Sleep(1);
			continue;
		}
		
		nCurDataLen = pComtradeBuf->GetDataLen() * sizeof(float);

		//开始发送数据命令
		pSocket->m_bSendDataStartAck = FALSE;
		long nSendLenth = pSocket->m_pClientEngineRef->Comtrade_SendDataStart(nCurIndex,nCurDataLen);
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("Comtrade_SendDataStart  ---  nCurIndex=%d;nCurDataLen=%d;nSendLenth=%ld;"),nCurIndex,nCurDataLen,nSendLenth);

		while(!pSocket->m_bSendDataStartAck)
		{
			if (pSocket->m_hSocket == 0)
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR,_T("ExitComtradeSendThread  m_hSocket <= 0"));
				break;
			}

			if( pSocket->m_bClosing)
			{
				pSocket->m_bClosing = FALSE;
				pSocket->CWinBaseSocket::Close();
				break;
			}

			Sleep(5);
		}
		if (!pSocket->m_bSendDataStartAck)
		{//异常断链
			break;
		}

		//压缩发送
		nSendCnt = pSocket->SttRcdSocketSend((BYTE*)pComtradeBuf->GetCurDataBuf(), nCurDataLen,nCurIndex);

		if (nSendCnt > 0)
		{
			//发送成功，设置数据可写标记
			pComtradeBuf->SetRWState(COMTRADE_DATABUF_MODE_WRITE);

			//约定：AB缓存始终是满的，否则认为为最后数据
			BOOL bLast = FALSE;
			if (nCurIndex > 0)
			{//只有ReplayBuf为空，且下个ABBuf也为空才认为数据已发完

				if ((pSocket->m_pbAnalysisFinish != NULL)&&(*pSocket->m_pbAnalysisFinish)/*g_theBigComtradeTransPlay->m_oBigComtradeFileRead.IsAnalysisFinish()*/)
				{
					pComtradeBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nCurIndex+1);
					bLast = !pComtradeBuf->CanRead();

// #ifdef _Stt_Cmtrd_Save_File_
// 					if (bLast)
// 					{
// 						CloseCmtrdSaveFile();
// 					}
// #endif
				}
			}

			//发送完成命令
			pSocket->m_pClientEngineRef->Comtrade_SendDataFinish(nCurIndex,nSendCnt,bLast);
		}
		else
		{//disconnect
			pSocket->Close();
			CLogPrint::LogString(XLOGLEVEL_INFOR,_T("SttRcdSocketSend error  IsSocketClose==TRUE"));
			break;
		}
	}

	pSocket->OnClose(0);
	pSocket->m_pSttComtradeSendThread = NULL;

	return 0;
}
