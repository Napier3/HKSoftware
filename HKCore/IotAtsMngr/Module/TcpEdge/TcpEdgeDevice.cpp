#include "stdafx.h"
#include "TcpEdgeDevice.h"
#include "../../../../Module/API/GlobalConfigApi.h"

CTcpEdgeDevice::CTcpEdgeDevice()
{
	m_nHasAuth = 0;
	m_bSign = false;
	m_bZlib = false;
	m_bSavePkg = false;
	m_bSaveRpt = false;
	m_pProtocol = NULL;
	m_pWordTool = NULL;

	for(int i = 0; i < 8; i++)
	{
		m_byteRecvR1[i] = 0x00;
	}

	for(int i = 0; i < 8; i++)
	{
		m_byteRecvR2[i] = 0x00;
	}

	for(int i = 0; i < 8; i++)
	{
		m_byteR2[i] = 0x00;
	}
}

CTcpEdgeDevice::~CTcpEdgeDevice()
{
	if(m_pProtocol)
	{
		delete m_pProtocol;
		m_pProtocol = NULL;
	}
}

void CTcpEdgeDevice::InitProtocol(QString strDvmFile)
{
	if (m_pProtocol != NULL)
	{
		QString strPrcdrID = PkgData_Auth;
		m_pProtocol->RunProcedure(strPrcdrID, NULL, NULL);
		return;
	}

	QString strDvmFullFilePath = _P_GetLibraryPath();

	m_oDvmDevice.DeleteAll();
	if(strDvmFile.indexOf(_T("\\")) == -1)
	{
		strDvmFullFilePath += strDvmFile;
	}
	else
	{
		strDvmFullFilePath = strDvmFile;
	}

	m_oDvmDevice.OpenXmlFile(strDvmFullFilePath, CDataMngrXmlRWKeys::g_pXmlKeys);
	m_oDvmDevice.m_strID = strDvmFullFilePath;

	m_pProtocol = new CTcpEdgeProtocol();
	connect(m_pProtocol, SIGNAL(sig_updatePkg(QString,QString,long)), this, SLOT(slot_updatePkg(QString,QString,long)));
	connect(m_pProtocol, SIGNAL(sig_timeout()), this, SLOT(slot_timeout()));
	m_pProtocol->m_strID = m_strID;
	m_pProtocol->AttachDevice(this);
	m_pProtocol->m_pDvmDevice = &m_oDvmDevice;
	m_pProtocol->StartEngineThread();
	QString strPrcdrID = PkgData_Auth;
	m_pProtocol->RunProcedure(strPrcdrID, NULL, NULL);
}

void CTcpEdgeDevice::CreateDevice(QString strIP, long nMngrPort, long nDataPort)
{
	m_strID = m_strName = strIP;
	InitProtocol("边缘网关数据模型V1.xml");
	m_pProtocol->AttachPort(nMngrPort, nDataPort);
}

void CTcpEdgeDevice::UpdateDevice(QString strName, QString strID)
{
	m_strDeviceName = strName;
	m_strDeviceID = strID;
}

void CTcpEdgeDevice::OnRecieve(long nPort, QByteArray bytes)
{
	m_pProtocol->OnTestMsg(nPort, bytes);
}

void CTcpEdgeDevice::Send(long nPort, BYTE* pBuf, QString strPrcdrID, long nLen)
{
	QByteArray bytes;
	for (int i = 0; i < nLen; i++)
	{
		bytes.append(pBuf[i]);
	}

	emit sig_send(m_strID, nPort, strPrcdrID, bytes);
}

void CTcpEdgeDevice::RunProcedure(QString strPkg, bool bIsMngrCh)
{
	if (m_pProtocol)
	{
		m_pProtocol->RunUserProcedure(strPkg, bIsMngrCh);
	}
}

void CTcpEdgeDevice::RunProcedure(QString& strProcedureID, CDvmDataset *pDataset, long nPort)
{
	if (m_pProtocol)
	{
		m_pProtocol->RunProcedure(strProcedureID, NULL, pDataset, nPort);
	}
}

CDvmDataset* CTcpEdgeDevice::FindDatasetByID(QString strID)
{
	return m_oDvmDevice.FindDataset(strID);
}

void CTcpEdgeDevice::slot_timeout()
{
	//心跳超时
	m_pProtocol->ExitEngineThread();
	emit sig_healthTimeout(m_strID);
}

void CTcpEdgeDevice::slot_updatePkg(QString strIP, QString strLog, long nType)
{
	emit sig_updatePkg(strIP, strLog, nType);
}