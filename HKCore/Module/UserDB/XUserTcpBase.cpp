#include "StdAfx.h"
#include "XUserTcpClient.h"
#include "DeviceCmmChannel.h"
#include "..\PpEngineThread.h"
#include "..\DeviceModel\CmmOnConnect.h"

CXUserTcpBase::CXUserTcpBase(void)
{
	
}

CXUserTcpBase::~CXUserTcpBase(void)
{

}


CString CXUserTcpBase::GetError(DWORD error)
{
	CString strError;

	switch(error)
	{
	case WSANOTINITIALISED:
		strError=_T("��ʼ������");
		break;
	case WSAENOTCONN:
		strError=_T("�Է�û������");
		break;
	case WSAEWOULDBLOCK :
		strError=_T("�Է��Ѿ��ر�");
		break;
	case WSAECONNREFUSED:
		strError=_T("���ӵĳ��Ա��ܾ�");
		break;
	case WSAENOTSOCK:
		strError=_T("��һ�����׽����ϳ�����һ������");
		break;
	case WSAEADDRINUSE:
		strError=_T("�ض��ĵ�ַ����ʹ����");
		break;
	case WSAECONNRESET:
		strError=_T("�����������ӱ��ر�");
		break;
	default:
		strError=_T("һ�����");	
	}

	return strError;	
}

UINT CXUserTcpClient::TcpClientThread(LPVOID cs)
{
	char buffer[255] = {0};
	int numrcv;
	SOCKET clientSocket = (SOCKET)cs;

	while (1)
	{
		numrcv = recv(clientSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);

		if ((numrcv == 0) || (numrcv == SOCKET_ERROR))
		{
			CLogPrint::LogFormatString(LOGLEVEL_ERROR, _T("RecvThread:Connection terminated!  %s\n"),
				GetError(GetLastError()) );
			break;
		}

		buffer[numrcv] = '\0';
		char type[10];		//�жϽ��յ�����Ϣ����
		for (int i=0; i<9; i++)
		{
			type[i] = buffer[i];
		}
		type[9] = '\0';	//"SendFile!"��9���ַ�
		if (strcmp(type, "SendFile!") == 0)		//�Է�Ҫ���ҷ����ļ�
		{
			char senderName[20];
			for (i=0; buffer[i+9]!='~'; i++)
			{
				senderName[i] = buffer[i+9];
			}
			senderName[i] = '\0';
			char str[80];
			strcpy(str, senderName);
			strcat(str, "   ����㷢���ļ���\n���հ����ǡ����ܾ�������");
			if (AfxMessageBox(str, MB_YESNO) == IDYES)
			{
				AfxBeginThread(recvFile, (LPVOID*)(buffer+9));	//��ʼ�����ļ��߳�
			}
			else
			{
				CString strRefuse;
				strRefuse = senderName;
				strRefuse += ":";
				strRefuse += "Refuse!";
				send(clientSocket, strRefuse, strRefuse.GetLength(), 0);//���;����ļ���Ϣ
			}
			continue;
		}
		type[7] = '\0';	//"Refuse!"��7���ַ�
	
		if (strcmp(type, "Refuse!") == 0)	//�Է��ܾ������ļ�
		{
			AfxMessageBox("�Է��ܾ������ļ���\n��ȡ���رնԻ���", MB_OK);
			//TerminateThread(pSendFile, 0);
			continue;
		}

		::PostMessage(recvWnd, WM_RECVDATA, DWORD((LPSTR)buffer), numrcv);//��ͨ��Ϣ
	}

	closesocket(clientSocket);

	return 1;

	return 0;

}

///////////////////////�����ļ��̣߳��ͻ���ģʽ��////////////////////////////
UINT recvFile(void *data)
{
	
	return 0;
}
long CXUserTcpClient::OnReceive()
{
	m_nReceiveLen = 0;

	if (m_pCycleRcvBuffer == NULL)
	{
		return 0;
	}

	BYTE *pBuffer = m_pCycleRcvBuffer->GetBuffer();

	if (pBuffer == NULL)
	{
		return 0;
	}

	CCmmRcvSndTime *pCmmTime = NULL;//new CCmmRcvSndTime();
	long nFillBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();

	while (TRUE)
	{
		long nLen = ReceiveOwnSocket(m_byteReceiveBuffer, CMM_RECEIVEBUFFER_LENGTH);

		if (nLen <= 0)
		{
			break;
		}

		pCmmTime = new CCmmRcvSndTime();
		pCmmTime->InitTime();
		m_nReceiveLen += nLen;

		nFillBeginPos = m_pCycleRcvBuffer->GetDataFillBeginPosition();
		m_pCycleRcvBuffer->AppendBuffer(m_byteReceiveBuffer, nLen);
		m_pCycleRcvBuffer->GetBufferPos(nFillBeginPos, nLen, pCmmTime->m_oCycleBufferPos);
		CCmmChannel::OnChannelReceive(m_pCycleRcvBuffer, pCmmTime,  NULL);
	}

	return m_nReceiveLen;
}

BOOL CXUserTcpClient::IsCmmChannelExit()
{
	if (m_pThread == NULL)
	{
		if (m_hSocket != NULL)
		{
			Close();
			m_hSocket = NULL;
		}
	}

	return (m_hSocket == NULL && m_hWnd == NULL);
}

BOOL CXUserTcpClient::TerminateChannel()
{
	return TRUE;
}



BEGIN_MESSAGE_MAP(CXUserTcpClient, CWnd)
	//{{AFX_MSG_MAP(CThreadSocket)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_TCPIP,OnTCPIP)
END_MESSAGE_MAP()


LRESULT CXUserTcpClient::OnTCPIP(WPARAM wParam, LPARAM lParam)
{
	switch(WSAGETSELECTEVENT(lParam)) 
	{
	case FD_ACCEPT:
		//CWinTcpSocket::Accept();
		break;
	case FD_READ:
		OnReceive();
		break;
	case FD_CLOSE:
		OnClose();
		break;
	default:
		break;
	}

	return S_OK;
}
