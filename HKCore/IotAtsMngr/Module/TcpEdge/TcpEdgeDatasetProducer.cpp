#include "stdafx.h"
#include "TcpEdgeDatasetProducer.h"
#include "Pkg/TcpEdgePkgData_TimeSyncReq.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateReq.h"
#include "Pkg/TcpEdgePkgData_DeviceCtrlReq.h"
#include "Pkg/TcpEdgePkgData_DeviceConfigReq.h"
#include "Pkg/TcpEdgePkgData_ConInstallReq.h"

CTcpEdgeDatasetProducer::CTcpEdgeDatasetProducer()
{
	m_pHead = NULL;
	m_pData = NULL;
	m_pDataset = NULL;
}

CTcpEdgeDatasetProducer::~CTcpEdgeDatasetProducer()
{
	if(m_pHead)
	{
		delete m_pHead;
		m_pHead = NULL;
	}

	if(m_pData)
	{
		delete m_pData;
		m_pData = NULL;
	}

	if(m_pDataset)
	{
		delete m_pDataset;
		m_pDataset = NULL;
	}
}

 CDvmDataset* CTcpEdgeDatasetProducer::Produce(const CString& strPrcdrID)
 {
 	//m_pHead = new CTcpEdgePkgHead;
	m_pData = CTcpEdgePkgData::GetPrcdrDataByID(strPrcdrID);

	if(m_pDataset)
	{
		delete m_pDataset;
		m_pDataset = NULL;
	}

	if (!m_pData)
	{
		return NULL;
	}

	m_pDataset = new CDvmDataset;
	m_pDataset->m_strID = strPrcdrID;
	m_pDataset->m_strDataType = PkgData_Type_Object;
	//记录Data的类型
	m_pDataset->m_dwItemData = (DWORD)m_pData;
	m_pDataset->AddNewChild(m_pHead->ToDataset());
	m_pDataset->AddNewChild(m_pData->ToDataset());
	m_pDataset->GetTail()->m_dwItemData = 1;

	CString strTime;
	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	strTime.Format(_T("%d-%d-%d %d:%d:%d.%d"), tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);

	CDvmDataset* pDataset = (CDvmDataset*)m_pDataset->FindByID(PkgData_Node_Head);
	CDvmData* pData = (CDvmData*)pDataset->FindByID(PkgData_Node_FunName);
	pData->m_strValue = strPrcdrID;
	pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Mid);
	pData->m_strValue = "1";
	pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Cot);
	pData->m_strValue = PkgData_Value_CotReq;
	pData = (CDvmData*)pDataset->FindByID(PkgData_Node_Timestamp);
	pData->m_strValue = strTime;

	return m_pDataset;
}

 void CTcpEdgeDatasetProducer::CopyItemData(CExBaseList* pDest, CExBaseList* pSrc)
 {
	 for (int i = 0; i < pSrc->GetCount(); i++)
	 {
		 CExBaseList* pDestChild = (CExBaseList*)pDest->GetAt(i);
		 CExBaseList* pSrcChild = (CExBaseList*)pSrc->GetAt(i);
		 pDestChild->m_dwItemData = pSrcChild->m_dwItemData;
		 if(pSrcChild->GetCount())
		 {
			 CopyItemData(pDestChild, pSrcChild);
		 }
	 }
 }

CDvmDataset* CTcpEdgeDatasetProducer::GetDataset()
{
	//确保内部创建的数据集能正确析构
	if(m_pDataset)
	{
		CDvmDataset* pClone = (CDvmDataset*)m_pDataset->CloneEx(TRUE, TRUE);
		CopyItemData(pClone, m_pDataset);
		return pClone;
	}
	return NULL;
}