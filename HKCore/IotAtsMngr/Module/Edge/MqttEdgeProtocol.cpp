#include "stdafx.h"
#include "MqttEdgeProtocol.h"
#include "../Factory/ProcedureFactory.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif

CMqttEdgeProtocol::CMqttEdgeProtocol()
{

}

CMqttEdgeProtocol::~CMqttEdgeProtocol()
{

}


long CMqttEdgeProtocol::RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
								   ,CDvmDataset *pDataset,const CString &strRecordMode)
{
	//���ݹ���ID������ͬ�Ĺ��̶�����ӵ�����������
	CPxPrcdrBase *pProcedure = CProcedureFactory::CreateProcedure(strProcedureID);

	if (pProcedure == NULL)
	{
		return 0;
	}

	pProcedure->InitProcedure(strProcedureID,pListDatas,pDataset,strRecordMode);

	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	m_listTempPrcdr.AddTail(pProcedure);

	return 1;
}

long CMqttEdgeProtocol::PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset)
{
	return 0;
}

long CMqttEdgeProtocol::PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen)
{
	return 0;
}

long CMqttEdgeProtocol::GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset)
{
	return 0;
}

long CMqttEdgeProtocol::ConfigDevice(const CString &strConfig)
{
	return 0;
}

long CMqttEdgeProtocol::CloseDevice()
{
	return 0;
}