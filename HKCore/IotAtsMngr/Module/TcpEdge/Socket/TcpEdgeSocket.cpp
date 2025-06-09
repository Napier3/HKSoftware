#include "stdafx.h"
#include "TcpEdgeSocket.h"

CTcpEdgeSocket::CTcpEdgeSocket()
{
	m_nMngrRecvIndex = 0;
	m_nDataRecvIndex = 0;
	m_nMngrPort = 0;
	m_nDataPort = 0;
	m_pMngrSocket = 0;
	m_pDataSocket = 0;
	m_bExit = true;
	m_bExited = false;
}

CTcpEdgeSocket::~CTcpEdgeSocket()
{
	Close();
	while (!m_bExited)
	{
		CTickCount32 event;
		event.DoEvents(50);
	}

	if(m_pMngrSocket)
	{
		delete m_pMngrSocket;
		m_pMngrSocket = NULL;
	}

	if(m_pDataSocket)
	{
		delete m_pDataSocket;
		m_pDataSocket = NULL;
	}
}

void CTcpEdgeSocket::run()
{
	while(!m_bExit)
	{
		QString strIP;
		long nPort = 0;
		if(m_queueBytes.size())
		{
			QByteArray bytes = ReadBytes(strIP, nPort);
			emit sig_pkg(strIP, nPort, bytes);
		}

 		CTickCount32 event;
 		event.DoEvents(10);
	}

	m_bExited = true;
}

bool CTcpEdgeSocket::InitSocket(QString strLocalIP, QString strIP, long nMngrPort, long nDataPort)
{
	m_strIP = strIP;
	m_nMngrPort = nMngrPort;
	m_nDataPort = nDataPort;

	m_pMngrSocket = new CTcpEdgeSocketClient;
	connect(m_pMngrSocket, SIGNAL(readyRead()), this, SLOT(OnMngrRead()));
	connect(m_pMngrSocket, SIGNAL(disconnected()), this, SLOT(OnMngrDisconnect()));

	m_pDataSocket = new CTcpEdgeSocketClient;
	connect(m_pDataSocket, SIGNAL(readyRead()), this, SLOT(OnDataRead()));
	connect(m_pDataSocket, SIGNAL(disconnected()), this, SLOT(OnDataDisconnect()));

	bool bRet = false;
	bRet = m_pMngrSocket->Connect(strLocalIP, m_strIP, m_nMngrPort);
	bRet &= m_pDataSocket->Connect(strLocalIP, m_strIP, m_nDataPort);
	if(bRet)
	{
		m_bExit = false;
	}

	return bRet;
}

void CTcpEdgeSocket::Close()
{
	m_bExit = true;
	m_pDataSocket->Disconnect();
	m_pMngrSocket->Disconnect();
}

void CTcpEdgeSocket::Send(long nPort, QByteArray bytes)
{
	if(nPort == m_nMngrPort)
	{
		m_pMngrSocket->Send(bytes);
	}
	else
	{
		m_pDataSocket->Send(bytes);
	}
}

void CTcpEdgeSocket::WriteBytes(QString strIP, long nPort, QByteArray bytes)
{
	QWriteLocker lock(&m_locker);
	tagBytes tag;
	tag.m_strIP = strIP;
	tag.m_nPort = nPort;
	tag.m_bytes = bytes;
	m_queueBytes.enqueue(tag);
}

QByteArray CTcpEdgeSocket::ReadBytes(QString& strIP, long& nPort)
{
	QReadLocker lock(&m_locker);
	strIP = m_queueBytes.head().m_strIP;
	nPort = m_queueBytes.head().m_nPort;
	QByteArray bytes = m_queueBytes.head().m_bytes;
	m_queueBytes.dequeue();
	return bytes;
}

bool CTcpEdgeSocket::AnalysisMngrRecvBuf()
{
	BYTE *pTemp = (BYTE *)m_oMngrExpandRecvBuf.GetDataBuffer();
	long nDataLen = m_oMngrExpandRecvBuf.GetDataLength();
	long nReadPos = 0;
	long nPkgDataLen = 0;
	long nPkgLen = 0;
	bool bSucc = true;

	while(nDataLen - nReadPos >= TCPEDGE_PKG_HEAD_LEN)
	{
		if(!tcp_edge_pkg_match_head(pTemp))
		{
			nReadPos += 1;
			pTemp += 1;
			continue;
		}

		nPkgDataLen = tcp_edge_pkg_get_data_len(pTemp);
		if (nPkgDataLen < 0 || nPkgDataLen > TCPEDGE_PKG_DATA_MAXLEN)
		{
			nReadPos += 2;
			pTemp += 2;
			continue;
		}

		nPkgLen = nPkgDataLen + TCPEDGE_PKG_HEAD_LEN;

		if (nPkgLen > nDataLen - nReadPos)
		{
			//余下的报文长度不够一个完整的报文
			break;
		}

		//获取网关分配的ID
		char strGatewayID[24] = {0};
		strncpy(strGatewayID, (char*)&pTemp[TCPEDGE_PKG_INDEX_GATEWAYID], 23);
		strGatewayID[23] = 0;

		//记录鉴权认证时鉴权标志的状态
		BYTE auth = pTemp[TCPEDGE_PKG_HEAD_LEN];
		if(auth == 0x01 || auth == 0x03)
		{
			if(!tcp_edge_pkg_has_auth(pTemp))
			{
				//协议帧鉴权过程鉴权标记为0,不符合规定
				return false;
			}	
		}

		//获取当前帧ASDU之前先确定是否校验签名
		if(tcp_edge_pkg_has_sign(pTemp))
		{
			SM2_SIGNATURE_STRUCT sm2;
			BYTE* strSignData = pTemp + TCPEDGE_PKG_HEAD_LEN + nPkgDataLen;
			BYTE* strSignCal = new BYTE[TCPEDGE_PKG_HEAD_LEN + nPkgDataLen];
			tcp_edge_sm2_cal(pTemp, TCPEDGE_PKG_HEAD_LEN + nPkgDataLen, sm2, strSignCal);
			for (int i = 0; i < TCPEDGE_PKG_HEAD_LEN + nPkgDataLen; i++)
			{
				if(strSignCal[i] != strSignData[i])
				{
					delete strSignData;
					return false;
				}
			}

			delete strSignData;
		}

		//获取ASDU
		if(m_nMngrRecvIndex = tcp_edge_pkg_get_passage_id(pTemp))
		{
			//报文是一个分段
			m_oMngrPassageRecvBuf[m_nMngrRecvIndex].AppendBuffer(pTemp + TCPEDGE_PKG_HEAD_LEN, nPkgDataLen);
			m_oMngrPassageRecvLen[m_nMngrRecvIndex] += nPkgDataLen;
			if(!tcp_edge_pkg_has_passage(pTemp))
			{
				//该分段是最后一个,补齐ASDU后解析并移除
				BYTE *pPassageString = (BYTE *)m_oMngrPassageRecvBuf[m_nMngrRecvIndex].GetDataBuffer();
				//补齐后如果是压缩则需要解压再操作
				if (tcp_edge_pkg_has_deflate(pTemp))
				{
					//由于协议文档规定单个ASDU长度上限约束为65535字节
					//用压缩后65535估算压缩前的值
					long nCompressLen = compressBound(65535);
					uLongf nUncompressLen = m_oMngrPassageRecvLen[m_nMngrRecvIndex] / (nCompressLen / 65535) + 1;
					BYTE* pUncompress = new BYTE[nUncompressLen];
					memset(pUncompress, 0, nUncompressLen);
					long nRet = uncompress(pUncompress, &nUncompressLen, pPassageString, m_oMngrPassageRecvLen[m_nMngrRecvIndex]);
					if(nRet != Z_OK)
					{
						return false;
					}

					ProcessRecvMngrPacket(strGatewayID, pUncompress, nUncompressLen);
					delete pUncompress;
				}
				else
				{
					ProcessRecvMngrPacket(strGatewayID, pPassageString, m_oMngrPassageRecvLen[m_nMngrRecvIndex]);
				}
				m_oMngrPassageRecvBuf[m_nMngrRecvIndex].FreeBuffer();
				m_oMngrPassageRecvLen[m_nMngrRecvIndex] = 0;
			}
		}
		else
		{
			BYTE* strPkgData = pTemp + TCPEDGE_PKG_HEAD_LEN;
			ProcessRecvMngrPacket(strGatewayID, strPkgData, nPkgDataLen);
		}

		nReadPos += nPkgLen;
		pTemp += nPkgLen ;
	}

	//非完整包数据移到缓存开头
	m_oMngrExpandRecvBuf.PosMoveByUsedLen(nReadPos);

	return true;
}

bool CTcpEdgeSocket::ProcessRecvMngrPacket(QString strGatewayID, BYTE *pBuf, long nLen)
{
	BYTE* pTempBuf = pBuf - 32;
	QByteArray bytes;
	for (int i = 0; i < nLen + 32; i++)
	{
		bytes.append(pTempBuf[i]);
	}

	QString strIP = QString("%1$%2").arg(strGatewayID).arg(m_strIP);
	WriteBytes(strIP, m_nMngrPort, bytes);
	return true;
}

void CTcpEdgeSocket::OnMngrReceiveBuffer(QByteArray bytes)
{
	long nLen = bytes.size();
	if (nLen <= 0)
	{
		return;
	}

	m_oMngrExpandRecvBuf.AppendBuffer((BYTE*)bytes.data(), nLen);
	AnalysisMngrRecvBuf();
}

bool CTcpEdgeSocket::AnalysisDataRecvBuf()
{
	BYTE *pTemp = (BYTE *)m_oDataExpandRecvBuf.GetDataBuffer();
	long nDataLen = m_oDataExpandRecvBuf.GetDataLength();
	long nReadPos = 0;
	long nPkgDataLen = 0;
	long nPkgLen = 0;
	bool bSucc = true;

	while(nDataLen - nReadPos >= TCPEDGE_PKG_HEAD_LEN)
	{
		if(!tcp_edge_pkg_match_head(pTemp))
		{
			nReadPos += 1;
			pTemp += 1;
			continue;
		}

		nPkgDataLen = tcp_edge_pkg_get_data_len(pTemp);
		if (nPkgDataLen < 0 || nPkgDataLen > TCPEDGE_PKG_DATA_MAXLEN)
		{
			nReadPos += 2;
			pTemp += 2;
			continue;
		}

		nPkgLen = nPkgDataLen + TCPEDGE_PKG_HEAD_LEN;

		if (nPkgLen > nDataLen - nReadPos)
		{
			//余下的报文长度不够一个完整的报文
			break;
		}

		//获取网关分配的ID
		char strGatewayID[24] = {0};
		strncpy(strGatewayID, (char*)&pTemp[TCPEDGE_PKG_INDEX_GATEWAYID], 23);
		strGatewayID[23] = 0;

		//记录鉴权认证时鉴权标志的状态
		BYTE auth = pTemp[TCPEDGE_PKG_HEAD_LEN];
		if(auth == 0x01 || auth == 0x03)
		{
			if(!tcp_edge_pkg_has_auth(pTemp))
			{
				//协议帧鉴权过程鉴权标记为0,不符合规定
				return false;
			}	
		}

		//获取当前帧ASDU之前先确定是否校验签名
		if(tcp_edge_pkg_has_sign(pTemp))
		{
			SM2_SIGNATURE_STRUCT sm2;
			BYTE* strSignData = pTemp + TCPEDGE_PKG_HEAD_LEN + nPkgDataLen;
			BYTE* strSignCal = new BYTE[TCPEDGE_PKG_HEAD_LEN + nPkgDataLen];
			tcp_edge_sm2_cal(pTemp, TCPEDGE_PKG_HEAD_LEN + nPkgDataLen, sm2, strSignCal);
			for (int i = 0; i < TCPEDGE_PKG_HEAD_LEN + nPkgDataLen; i++)
			{
				if(strSignCal[i] != strSignData[i])
				{
					delete strSignData;
					return false;
				}
			}

			delete strSignData;
		}

		//获取ASDU
		if(m_nDataRecvIndex = tcp_edge_pkg_get_passage_id(pTemp))
		{
			//报文是一个分段
			m_oDataPassageRecvBuf[m_nDataRecvIndex].AppendBuffer(pTemp + TCPEDGE_PKG_HEAD_LEN, nPkgDataLen);
			m_oDataPassageRecvLen[m_nDataRecvIndex] += nPkgDataLen;
			if(!tcp_edge_pkg_has_passage(pTemp))
			{
				//该分段是最后一个,补齐ASDU后解析并移除
				BYTE *pPassageString = (BYTE *)m_oDataPassageRecvBuf[m_nDataRecvIndex].GetDataBuffer();
				//补齐后如果是压缩则需要解压再操作
				if (tcp_edge_pkg_has_deflate(pTemp))
				{
					//由于压缩率大概率不超过1:10,所以按照收到报文的长度十倍来定义缓冲
					uLongf nUncompressLen = m_oDataPassageRecvLen[m_nDataRecvIndex] * 10;
					BYTE* pUncompress = new BYTE[nUncompressLen];
					memset(pUncompress, 0, nUncompressLen);
					long nRet = uncompress(pUncompress, &nUncompressLen, pPassageString, m_oDataPassageRecvLen[m_nDataRecvIndex]);
					if(nRet != Z_OK)
					{
						return false;
					}

					ProcessRecvDataPacket(strGatewayID, pTemp, TCPEDGE_PKG_HEAD_LEN, pUncompress, nUncompressLen);
					delete pUncompress;
				}
				else
				{
					ProcessRecvDataPacket(strGatewayID, pTemp, TCPEDGE_PKG_HEAD_LEN, pPassageString, m_oDataPassageRecvLen[m_nDataRecvIndex]);
				}
				m_oDataPassageRecvBuf[m_nDataRecvIndex].FreeBuffer();
				m_oDataPassageRecvLen[m_nDataRecvIndex] = 0;
			}
		}
		else
		{
			BYTE* strPkgData = pTemp + TCPEDGE_PKG_HEAD_LEN;
			//如果是压缩则需要解压再操作
			if (tcp_edge_pkg_has_deflate(pTemp))
			{
				uLongf nUncompressLen = nPkgDataLen * 10;
				BYTE* pUncompress = new BYTE[nUncompressLen];
				memset(pUncompress, 0, nUncompressLen);
				long nRet = uncompress(pUncompress, &nUncompressLen, strPkgData, nPkgDataLen);
				if(nRet != Z_OK)
				{
					return false;
				}

				ProcessRecvDataPacket(strGatewayID, pTemp, TCPEDGE_PKG_HEAD_LEN, pUncompress, nUncompressLen);
				delete pUncompress;
			}
			else
			{
				ProcessRecvDataPacket(strGatewayID, pTemp, TCPEDGE_PKG_HEAD_LEN, strPkgData, nPkgDataLen);
			}
		}

		nReadPos += nPkgLen;
		pTemp += nPkgLen ;
	}

	//非完整包数据移到缓存开头
	m_oDataExpandRecvBuf.PosMoveByUsedLen(nReadPos);

	return true;
}

bool CTcpEdgeSocket::ProcessRecvDataPacket(QString strGatewayID, BYTE *pHead, long nHeadLen, BYTE *pBuf, long nLen)
{
	QByteArray bytes;
	for (int i = 0; i < nHeadLen; i++)
	{
		bytes.append(pHead[i]);
	}

	for (int i = 0; i < nLen; i++)
	{
		bytes.append(pBuf[i]);
	}

	QString strIP = QString("%1$%2").arg(strGatewayID).arg(m_strIP);
	WriteBytes(strIP, m_nDataPort, bytes);
	return true;
}

void CTcpEdgeSocket::OnDataReceiveBuffer(QByteArray bytes)
{
	long nLen = bytes.size();
	if (nLen <= 0)
	{
		return;
	}

	m_oDataExpandRecvBuf.AppendBuffer((BYTE*)bytes.data(), nLen);
	AnalysisDataRecvBuf();
}

void CTcpEdgeSocket::OnMngrRead()
{
	QByteArray bytes = m_pMngrSocket->readAll();
	OnMngrReceiveBuffer(bytes);
}

void CTcpEdgeSocket::OnDataRead()
{
	QByteArray bytes = m_pDataSocket->readAll();
	OnDataReceiveBuffer(bytes);
}

void CTcpEdgeSocket::OnMngrDisconnect()
{
	emit sig_disconnect(m_strIP, m_nMngrPort);
}

void CTcpEdgeSocket::OnDataDisconnect()
{
	emit sig_disconnect(m_strIP, m_nDataPort);
}