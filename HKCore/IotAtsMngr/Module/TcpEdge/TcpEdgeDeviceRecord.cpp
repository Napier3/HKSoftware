#include "stdafx.h"
#include "TcpEdgeDeviceRecord.h"

CTcpEdgeDeviceRecord::CTcpEdgeDeviceRecord()
{

}

CTcpEdgeDeviceRecord::~CTcpEdgeDeviceRecord()
{

}

CModelRecord* CTcpEdgeDeviceRecord::FindModelByFileName(QString strFileName)
{
	for(int i = 0; i < m_models.GetCount(); i++)
	{
		CModelRecord* pTemp = (CModelRecord*)m_models.GetAt(i);
		QString strTempFileName = pTemp->m_strFullPathFileName;
		if((pTemp->m_strFullPathFileName.indexOf("\\" + strFileName) != -1)
			|| (pTemp->m_strFullPathFileName.indexOf("/" + strFileName) != -1)
			|| (pTemp->m_strFullPathFileName.indexOf(strFileName) != -1))
		{
			return pTemp;
		}
	}

	return NULL;
}

CModelRecord* CTcpEdgeDeviceRecord::FindModelByDeviceId(QString strDeviceId)
{
	for(int i = 0; i < m_models.GetCount(); i++)
	{
		CModelRecord* pTemp = (CModelRecord*)m_models.GetAt(i);
		if(pTemp->m_devs.FindByID(strDeviceId))
		{
			return pTemp;
		}
	}

	return NULL;
}

CContianerRecord::CContianerRecord()
{

}

CContianerRecord::~CContianerRecord()
{

}

CAppRecord::CAppRecord()
{

}

CAppRecord::~CAppRecord()
{

}

CModelRecord::CModelRecord()
{

}

CModelRecord::~CModelRecord()
{

}

CModelDeviceRecord::CModelDeviceRecord()
{

}

CModelDeviceRecord::~CModelDeviceRecord()
{

}