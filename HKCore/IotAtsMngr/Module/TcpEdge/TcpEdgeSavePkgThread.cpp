#include "stdafx.h"
#include "TcpEdgeSavePkgThread.h"
#include <QDir>

CTcpEdgeSavePkgThread::CTcpEdgeSavePkgThread()
{
	m_pParam = NULL;
}

CTcpEdgeSavePkgThread::~CTcpEdgeSavePkgThread()
{

}

void CTcpEdgeSavePkgThread::run()
{
	if(!m_pParam)
	{
		return;
	}

	long nPathIndex = m_strFullFileName.lastIndexOf("\\");
	if(nPathIndex == -1)
	{
		nPathIndex = m_strFullFileName.lastIndexOf("/");
	}

	QString strFullPath = m_strFullFileName.left(nPathIndex);
	QDir dir(strFullPath);
	if (!dir.exists())
	{
		dir.mkpath(strFullPath);
	}

	QFile file(m_strFullFileName);
	file.open(QIODevice::Append);
	for (int i = 0; i < m_vecBuffer.size(); i++)
	{
		file.write(m_vecBuffer[i].GetString());
	}
	file.close();

	*(bool*)m_pParam = false;
}