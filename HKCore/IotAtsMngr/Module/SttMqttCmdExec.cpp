#include "stdafx.h"
#include "SttMqttCmdExec.h"
#include "SttMqttClientEngineConfig.h"
#include "..\..\Module\System\TickCount32.h"

#include "MqttClientEngineBase.h"

CSttMqttCmdExec::CSttMqttCmdExec(const CString &strPpTemplateFile, const CString &strDeviceFile,const CString &strDeviceID)
{
	m_pPrjDevices = NULL;
	m_pModelDataset = NULL;

	m_hMsgWnd = 0;
	m_nMsg = 0;
	m_hSysMsgWnd = 0;
	m_nSysMsg = 0;

	if (!m_oMqttPpTemplate.OpenXmlFile(strPpTemplateFile,CMqttPpCfgXmlRWKeys::g_pXmlKeys))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("�򿪹�Լģ�塾%s��ʧ�ܡ�"), strPpTemplateFile);
	}

	if (!m_oDvmDevice.OpenXmlFile(strDeviceFile,CDataMngrXmlRWKeys::g_pXmlKeys))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("��ģ���ļ���%s��ʧ�ܡ�"), strDeviceFile);
	}

	if (strDeviceID.IsEmpty())
	{
		m_strID = strDeviceFile;
	}
	else
	{
		m_strID = strDeviceID;
	}	

	m_bExitThread = FALSE;
	SetSuspendThread();

	m_pThread = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)TestCmdExecThread,this,0,NULL);
}

CSttMqttCmdExec::~CSttMqttCmdExec()
{
	m_bExitThread = TRUE;

	CTickCount32 oTick;
	while(m_pThread != NULL)
	{
		oTick.DoEvents(5);
	}

	if (m_pPrjDevices != NULL)
	{
		delete m_pPrjDevices;
		m_pPrjDevices = NULL;
	}
}

BOOL CSttMqttCmdExec::ConnectDevice()
{
	if (CSttMqttClientTool::IsConnectSuccessful())
	{
		return TRUE;
	}

	CString strIP,strClientID,strServerURI;
	long nPort = 0,nQos = 0;
	CSttMqttClientEngineConfig::GetMqttDefualtQos(nQos);
	CSttMqttClientEngineConfig::GetMqttServerIP(strIP);
	CSttMqttClientEngineConfig::GetMqttServerPort(nPort);
	CSttMqttClientEngineConfig::GetMqttClientID(strClientID);
	strServerURI.Format(_T("tcp://%s:%d"),strIP,nPort);

	BOOL bRet = CSttMqttClientTool::InitMqttClient(strServerURI,strClientID+_T("_Engine"));

	if (bRet)
	{
		//������������
		g_pMqttClientEngineBase->SubcribeMqttTopic(nQos);

		CommVm_PostDeviceSysMessage(this,0,engineConnectDeviceSuccessful);
	}
	else
	{
		CommVm_PostDeviceSysMessage(this,0,engineConnectDeviceFailed);
	}
	
	return bRet;
}

BOOL CSttMqttCmdExec::IsConnectSuccessful()
{
	return CSttMqttClientTool::IsConnectSuccessful();
}

long CSttMqttCmdExec::RunProcedure(const CString &strProcedureID, const CString &strDsID)
{
	//���µ�ǰģ�����ݼ��ʹ�������Լ�������ݼ�
	m_pModelDataset = m_oDvmDevice.FindDataset(strDsID);
	CMqttPpProcedure *pProcedure = m_oMqttPpTemplate.FindProcedure(strProcedureID);

	ASSERT(pProcedure != NULL);
	ASSERT(m_pPrjDevices != NULL);

	CMqttPpProduce *pProduce = NULL;
	if (!pProcedure->m_strPp_Pkg.IsEmpty())
	{//�Ƕ�����ֵ,��������ģ������б�ֵ����
		pProduce = m_oMqttPpTemplate.FindProduce(pProcedure->m_strPp_Pkg);
		pProduce->UpdateParaValue(m_pModelDataset);
	}
	
	//��������߳�
	m_bSuspendThread = FALSE;

	POS pos = m_pPrjDevices->GetHeadPosition();
	CPpPrjDevice *pDevice = NULL;
	while(pos != NULL)
	{
		pDevice = (CPpPrjDevice *)m_pPrjDevices->GetNext(pos);

		if (pProduce != NULL)
		{//�Ƕ�����ֵ,�����װ�����ݼ�
			pDevice->UpdateDataset(m_pModelDataset);
		}
		
		pDevice->RunProcedure(pProcedure,pProduce);
	}

	return 1;
}

void CSttMqttCmdExec::SetSuspendThread()
{
	m_bSuspendThread = TRUE;
	m_pModelDataset = NULL;	
	m_strCurItemPath = _T("");

	POS pos = m_pPrjDevices->GetHeadPosition();
	CPpPrjDevice *pDevice = NULL;
	while(pos != NULL)
	{
		pDevice = (CPpPrjDevice *)m_pPrjDevices->GetNext(pos);
		pDevice->SetTestProgress_NoStart();
	}
}

BOOL CSttMqttCmdExec::OnMqttMsgRecieve(CPpPrjDevice *pPrjDevice,char *pBuf,long nLen)
{
	ASSERT(pPrjDevice != NULL);

	return pPrjDevice->ProcessRecvPacket(&m_oMqttPpTemplate,pBuf,nLen);
}

void CSttMqttCmdExec::OnTestItemFinish()
{
	//����δ���ر������ݵı����¼
	POS pos = m_pPrjDevices->GetHeadPosition();
	CPpPrjDevice *pDevice = NULL;
	while(pos != NULL)
	{
		pDevice = (CPpPrjDevice *)m_pPrjDevices->GetNext(pos);
#if 1
		//��Ե�װ�ò��ԣ�����com�ӿ������ݼ�
		pDevice->UpdateDataset2(m_pModelDataset);
#else
		//��Զ�װ�ò��ԣ����³�ʱװ�ñ��������ļ�
		if (!pDevice->IsTestProgress_HasReport())
		{
			//��ʱ
			pDevice->UpdateReportFile(2,m_pModelDataset);
		}
#endif
	}

	//��ͣ����߳�
	SetSuspendThread();

	CommVm_PostDeviceCommCmdMessage(this, 0, engineCommFinish);
}

CDvmDataset *CSttMqttCmdExec::GetDeviceAttr()
{
	return m_oDvmDevice.GetDeviceAttrs();
}

CDvmDataset *CSttMqttCmdExec::FindDataset(const CString &strDatasetID)
{
	return m_oDvmDevice.FindDataset(strDatasetID);
}

BOOL CSttMqttCmdExec::GetDeviceAttrValueByID(const CString &strID,CString &strValue)
{
	CDvmDataset *pDeviceAttr = GetDeviceAttr();
	if (pDeviceAttr == NULL)
	{
		return FALSE;
	}

	CDvmData *pFind = (CDvmData *)pDeviceAttr->FindByID(strID);
	if (pFind == NULL)
	{
		return FALSE;
	}

	strValue = pFind->m_strValue;
	return TRUE;
}

BOOL CSttMqttCmdExec::GetDeviceAttrValueByID(const CString &strID,long &nValue)
{
	CString strValue = _T("");
	BOOL bRet = GetDeviceAttrValueByID(strID,strValue);
	if (!bRet)
	{
		return FALSE;
	}
	nValue = CString_To_long(strValue);
	return TRUE;
}

BOOL CSttMqttCmdExec::IsTestItemFinish()
{
	BOOL bRet = TRUE;
	DWORD dwCurTime = GetTickCount();

	POS pos = m_pPrjDevices->GetHeadPosition();
	CPpPrjDevice *pDevice = NULL;
	while(pos != NULL)
	{
		pDevice = (CPpPrjDevice *)m_pPrjDevices->GetNext(pos);

		if (!pDevice->IsTestProgress_Finish(dwCurTime))
		{
			bRet = FALSE;
			break;
		}
	}

	return bRet;
}

void *CSttMqttCmdExec::TestCmdExecThread(LPVOID lParam)
{
	CSttMqttCmdExec *pCmdExec = (CSttMqttCmdExec *)lParam;

	while(TRUE)
	{
		if (pCmdExec->m_bExitThread)
		{
			break;
		}

		if (pCmdExec->m_bSuspendThread)
		{
			Sleep(100);
			continue;
		}

		if (pCmdExec->IsTestItemFinish())
		{
			pCmdExec->OnTestItemFinish();
			continue;
		}

		Sleep(20);
	}

	pCmdExec->m_pThread = NULL;
	return (void *)0;
}

//////////////////////////////////


void CommVm_PostDeviceSysMessage(CSttMqttCmdExec *pTestCtrl, WPARAM wParam, LPARAM lParam)
{
	ASSERT(pTestCtrl != NULL);

	HWND hWnd = (HWND)pTestCtrl->m_hSysMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("���Ͳ��������Ϣ ��%08x�� ���Ǵ��ڡ�Sys��"), pTestCtrl->m_hSysMsgWnd);
		return;
	}

	::PostMessage(hWnd, pTestCtrl->m_nSysMsg, wParam, lParam);
}

void CommVm_PostDeviceCommCmdMessage(CSttMqttCmdExec *pTestCtrl, WPARAM wParam, LPARAM lParam)
{
	ASSERT(pTestCtrl != NULL);

	HWND hWnd = (HWND)pTestCtrl->m_hMsgWnd;

	if (!::IsWindow((hWnd)))
	{
		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("���Ͳ��������Ϣ ��%08x�� ���Ǵ��ڡ�CommCmd��"), pTestCtrl->m_hMsgWnd);
		return;
	}

	::PostMessage(hWnd, pTestCtrl->m_nMsg, wParam, lParam);
}

CString GetIDFromPath(const CString &strPath,char chSeperator)
{
	CString strID;
	long nPos = strPath.ReverseFind(chSeperator);
	if (nPos >= 0)
	{
		strID = strPath.Mid(nPos + 1);
	}
	else
	{
		strID = strPath;
	}

	return strID;
}