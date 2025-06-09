#include "stdafx.h"
#include "RTDeviceCtrl.h"
#include "../IotSensorSvrEngine.h"
#include "../IotPpTemplate/IotPpProcedures.h"
#include "../SensorProtocol/SensorProtocalEngine.h"
#include "../../../../Module/GpsPcTime/GpsPcTime.h"
#include "../../IotEngineGlobalDef.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CRTDeviceCtrl::CRTDeviceCtrl()
{
	m_pIotTemplate = NULL;
	m_pProtoEventInterface = NULL;
	m_bCanDelete = FALSE;
	m_bInsertHisDataTimer = FALSE;
}

CRTDeviceCtrl::~CRTDeviceCtrl()
{
}

//��ȡ����δ����ı��ģ����ڹ��̴���
void CRTDeviceCtrl::GetNotProcessedPkgs(CExBaseList &oList)
{
	POS pos = m_listRcvPkg.GetHeadPosition();
	CXSensorPkg *p = NULL;

	while(pos != NULL)
	{
		p = (CXSensorPkg *)m_listRcvPkg.GetNext(pos);

		if (p->IsPkgState_NotProcessed())
		{
			oList.AddTail(p);
		}
	}
}

//ɾ��������Ч���ģ���֤������Ϊ��
void CRTDeviceCtrl::DeleteUnvalidPkgs(SYSTEMTIME &tmCur,long nValidTimeLong)
{
	if (nValidTimeLong <= 0)
	{
		return;
	}

	long nPkgCnt = m_listRcvPkg.GetCount();
	if (nPkgCnt <= 1)
	{//��֤������Ϊ��
		return;
	}

	long nPkgLifeTime = 0;
	POS pos = m_listRcvPkg.GetHeadPosition();
	POS posTail = m_listRcvPkg.GetTailPosition();
	POS prePos = NULL;
	CXSensorPkg *p = NULL;

	while(pos != NULL)
	{
		if (pos == posTail)
		{//��֤���һ���ڵ㲻��ɾ��������AddTail�Ͳ����ͻ
			break;
		}

		prePos = pos;
		p = (CXSensorPkg *)m_listRcvPkg.GetNext(pos);

		if (p->IsPkgState_CanDelete())
		{
			m_listRcvPkg.DeleteAt(prePos);
			continue;
		}

		nPkgLifeTime = GetSpanMSeconds(p->m_tmPkg,tmCur);
		if (nPkgLifeTime >= nValidTimeLong)
		{//���ĳ�����Ч����������δ����������
			m_listRcvPkg.DeleteAt(prePos);
			continue;
		}
	}
}

void CRTDeviceCtrl::AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface)
{
	m_pProtoEventInterface = pProtoEventInterface;
}

//����ָ�����ݼ�
CDvmDataset *CRTDeviceCtrl::UpdateDataset(CDvmDataset *pSrcDataset)
{
	if (pSrcDataset == NULL)
	{
		return NULL;
	}

	CString strDsID = GetIDFromPath(pSrcDataset->m_strID,'$');
	CDvmDataset *pDstDataset = m_oDvmDevice.FindDataset(strDsID);
	if (pDstDataset != NULL)
	{
		pDstDataset->UpdateDataValue(pSrcDataset);
	}

	return pDstDataset;
}

/******************************
����Э���������У���������ʼ��ProcedureRun����󣬲���ӵ�g_pIotSensorSvrEngine��m_listPrcdr������
******************************/
long CRTDeviceCtrl::RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
										  ,CDvmDataset *pDataset,const CString &strRecordMode)
{
	if(m_pProtoEventInterface == NULL)
	{
		return 0;
	}

	CDvmDataset* pAttrs = m_oDvmDevice.GetDeviceAttrs();
	if (strProcedureID == PROCEDURE_ID_WriteMmsAttr)
	{//����Ǹ���ȫ�����ݼ�����		
		pAttrs->UpdateDataValue(pDataset);

//		m_pProtoEventInterface->OnPrcdrFinishedEx(RUNPROCEDURE_EVENT_CommFinish,pAttrs);

		//��ӵ���������,��֤���������Ҳ���Ȼ�Reply��ظ��¼�
		//�����������m_pProcedure=NULL��
		g_pIotSensorSvrEngine->AddProcedureRun(this,NULL,NULL,pAttrs,_T(""));
		return 1;
	}
	
	//�ӹ�Լģ�����ҵ���Ӧ�Ĺ��̶���
	CIotPpProcedure *pProcedure = m_pIotTemplate->FindPpProcedure(strProcedureID);
	if (pProcedure == NULL)
	{
		return 0;
	}

	//��¡���ݣ���ProcedureRun���ͷ�
	CIotPpProcedure *pDstProcedure = (CIotPpProcedure *)pProcedure->Clone();

	//���²����б�
	CIotPpInterface* pDstInterface = pDstProcedure->GetIotPpInterface();
	if (pDstInterface != NULL)
	{
		pDstInterface->UpdateInterfaceValue(pListDatas);
	}

	//�������ݼ�, pDataset���Զ������·�RunProcedure���������Я�������ݼ�����
	CDvmDataset *pDstDataset = UpdateDataset(pDataset);

	//��ȡ���̶����г�ʱ����:����Dataset��Զ��ȫ��attr���ݼ�
	pDstProcedure->UpdateNodeTimers(pAttrs);

	//��ӵ���������
	g_pIotSensorSvrEngine->AddProcedureRun(this,pDstProcedure,pListDatas,pDstDataset,strRecordMode);

	return 1;
}

long CRTDeviceCtrl::PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset)
{
	return 0;
}

long CRTDeviceCtrl::PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen)
{
	return 0;
}

long CRTDeviceCtrl::GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset)
{
	CString strDsID = GetIDFromPath(strDatasetPath,'$');

	oRetDataset.DeleteAll();

	CDvmDataset *pSrcDataset = m_oDvmDevice.FindDataset(strDsID);
	if (pSrcDataset != NULL)
	{
		pSrcDataset->Copy(&oRetDataset);
	}

	oRetDataset.m_strID = strDatasetPath;

	return 1;
}

long CRTDeviceCtrl::ConfigDevice(const CString &strConfig)
{
	return 0;
}

long CRTDeviceCtrl::CloseDevice()
{
	//��ת���ӿ�ģ��ָ����0
	m_pProtoEventInterface = NULL;

	//����ɾ����־�������߳̿�ʼλ��ͳһɾ��
	m_bCanDelete = TRUE;

	return 0;
}

//��ʼ��Э�����ģ��ӿ�
void CRTDeviceCtrl::InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
				  ,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	m_strID = strDeviceID;

	m_oDvmDevice.DeleteAll();
	m_oDvmDevice.m_strID = strDvmFile;
	m_oDvmDevice.OpenXmlFile(strDvmFile,CDataMngrXmlRWKeys::g_pXmlKeys);

	//��Լģ��������CreateDevice���⴦���߼�ǰ�벿���Ѿ���ʼ������
	m_pIotTemplate = g_pIotSensorSvrEngine->GetIotTemplate(strPpxmlFile);
}

//��������ҵ�����߼�
void CRTDeviceCtrl::ProcessSensorPkg(char *pBuf,long nLen)
{
	//����������ΪSensorPkgInfo�ṹ��
	SensorPkgInfo *pSensorPkgInfo = new SensorPkgInfo;
	long nRet = CSensorProtocalEngine::PraseSensorPkgInfo(pBuf,nLen,*pSensorPkgInfo);
	if (nRet)
	{//��Ƭ�������
		if (PP_PRASE_ErrType_FRAG == nRet)
		{//��Ƭ���ģ����������ѱ��浽ȫ��CSensorFragMngr::m_vecSensorFragSDU������
			delete pSensorPkgInfo;
		}
		else
		{//�Ǵ�����
			
			//��������Ļ���
			pSensorPkgInfo->m_pPkgBuf = new BYTE[nLen];
			pSensorPkgInfo->m_nPkgBufLen = nLen;
			memcpy(pSensorPkgInfo->m_pPkgBuf,pBuf,nLen);
			
			CXSensorPkg *pPkg = new CXSensorPkg;
			pPkg->m_pSensorPkgInfo = pSensorPkgInfo;
			pPkg->SetPkgState(PX_PKG_STATE_ERROR);
			m_listRcvPkg.AddNewChild(pPkg);
		}

		return;
	}

	//�����Ż��߼�����Ƭ�ְ���ƴ���߼��ŵ�DeviceCtrl��
// 	if (��Ƭ����)
// 	{
//		��ӵ��б�ĩβ
// 		if����Ƭ�����һ֡��
// 		{
// 			���ҷ�Ƭ��һ֡���������Ͳ��ң�
// 			��������ͬ���͵ķ�Ƭƴ�ӵ���һ֡��m_pFragSDUBuf
// 			������һ֡��m_pFragSDUBuf : CSensorProtocalEngine::PraseSensorPkgInfo(m_pFragSDUBuf,nLen,*pSensorPkgInfo);
// 			��ת�����ݴ���
// 		}
// 		else
// 		{
// 			return
// 		}
// 	}

	//��ȷ�������ĺ��߼�

	//����֡ͷ����ƥ������ڵ�
	CIotPpParse *pPrase = m_pIotTemplate->FindPpParse(pSensorPkgInfo->m_nPkgType,pSensorPkgInfo->m_nCtrlType
		,pSensorPkgInfo->m_nRequestSetFlag);
	if (pPrase == NULL)
	{//���ǹ�Լģ��ƥ��ı���
		CXSensorPkg *pPkg = new CXSensorPkg;
		pPkg->m_pSensorPkgInfo = pSensorPkgInfo;
		pPkg->SetPkgState(PX_PKG_STATE_PROCESSED_NOTMATCH);
		m_listRcvPkg.AddNewChild(pPkg);
		return;
	}

	CString strDatasetID = pPrase->GetDatasetID();

	if (pPrase->IsModelOptr_Write())
	{//�������ݼ�
		CDvmDataset *pDataset = m_oDvmDevice.FindDataset(strDatasetID);
		ASSERT(pDataset != NULL);

		//���ݱ��Ľṹ��������ݼ�
		UpdateDatasetValue(*pSensorPkgInfo,pDataset);

		//for debug
// 		if (m_strID == _T("A92E082D1F02"))
// 		{
// 			int x = 0;
// 		}

		if (strDatasetID == _T("dsAin"))
		{//���򱨾�����

			//�������ݿ�
			BOOL bWarning = (SENSOR_PKG_TYPE_WARNING == pSensorPkgInfo->m_nPkgType);

			//����װ��ʵʱ���ݿ��
			g_pIotSensorSvrEngine->UpdateRTDeviceData(m_strID,pDataset,bWarning);
			//����װ����ʷʵʱ���ݿ�����ڿ̻���������
			g_pIotSensorSvrEngine->UpdateRTDeviceHisData(m_strID, pDataset);
			//g_pIotSensorSvrEngine->PostRTDeviceHisDataMessage(this);
			//���»����������
			g_pIotSensorSvrEngine->UpdateMonitorData(m_strID, pDataset);

			if (bWarning)
			{
				//���±����¼�
				g_pIotSensorSvrEngine->UpdateWarningEvent(m_pIotTemplate->m_strID, m_strID, pDataset);
			}
		}
	}

	//��ӵ����ձ���������
	CXSensorPkg *pPkg = new CXSensorPkg;
	pPkg->m_pSensorPkgInfo = pSensorPkgInfo;
	m_listRcvPkg.AddNewChild(pPkg);
}

//���̽����¼����ؽӿڣ�m_pProtoEventInterfaceָ�����CIotEngineToSensor
void CRTDeviceCtrl::OnPrcdrFinished(const CString &strEventID,CDvmDataset *pDataset)
{
	if (m_bCanDelete)
	{
		return;
	}

	if (m_pProtoEventInterface != NULL)
	{
		m_pProtoEventInterface->OnPrcdrFinishedEx((char *)strEventID.GetString(),pDataset);
	}
}


/////////////////////////////////////////////
//�����ݼ������б����ɵ�ʽ�����浽װ��ʵʱ���ݱ���
void GetEqualExprFromDataset(CDvmDataset *pDataset,CString &strExpr)
{
	if (pDataset == NULL)
	{
		return;
	}

	strExpr.Empty();

	POS pos = pDataset->GetHeadPosition();
	CDvmData *pData = NULL;
	CString strUnit;

	while(pos != NULL)
	{
		pData = (CDvmData *)pDataset->GetNext(pos);

		if (pData->m_strValue.IsEmpty())
		{
			continue;
		}

		pData->GetValueByID(SENSOR_MODEL_ID_Unit,strUnit);
		strExpr.AppendFormat(_T("%s%s;"),pData->m_strValue,strUnit);
	}
}