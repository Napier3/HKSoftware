#include "StdAfx.h"
#include "PpProcedureRun.h"
#include "PpEngineThreadBase.h"
#include "../XLanguageResourcePp.h"
#include "ScriptFunc_Engine.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CPpProcedureRun::CPpProcedureRun(CPpProcedure *pProcedure, CExBaseList *pInterface
								 , CWinThread *pEngineThread, BOOL bIsInitProcedure, CProtoPkgProcessInterface *pProtoPkgPrcss)
{
	CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)pEngineThread;
	m_pCurrNode = NULL;
	m_pProcedure = pProcedure;
	m_pProcedure->m_dwRunState = PP_PROCEDURE_RUN_STATE_NOMAL;

	if (pInterface == NULL)
	{
		m_pInterface = new CExBaseList();
	}
	else
	{
		m_pInterface = (CExBaseList*)pInterface->Clone();
	}	

	m_pPkgSendMngr = pThread->m_pPkgSendMngr;
	m_pListReceivePackage = &pThread->m_listReceivePackage;
	m_pEngineThread = pEngineThread;
	m_nPriorityCounter = 0;
	m_bProcedureExit = FALSE;
	m_dwBeginTickCount = 0;
	m_pProcedure->m_bValid = TRUE;
	m_nSndOptr_Optr = -1;
	m_bIsInitProcedure = bIsInitProcedure;
	m_pProtoPkgPrcss = pProtoPkgPrcss;
}

CPpProcedureRun::~CPpProcedureRun(void)
{
	if (m_pInterface != NULL)
	{
		m_pInterface->DeleteAll();
		delete m_pInterface;
		m_pInterface = NULL;
	}
}

BOOL CPpProcedureRun::CanRunWPackage()
{
	return TRUE;
	//2019-5-27   lijunqing ���������ˣ�����ӽ��ܱ���ִ�й��̴���

// 	if (m_strSndOptr_GlobalVar.GetLength() < 1)
// 	{
// 		return TRUE;
// 	}
// 
// 	char pszGlobalVar[MAX_PATH];
// 	CString_to_char(m_strSndOptr_GlobalVar, pszGlobalVar);
// 	long nValue = script_GetGlobalEx(pszGlobalVar, m_pProcedure);
// 
// 	if (m_nSndOptr_Optr == 0)
// 	{
// 		return nValue > m_nSndOptr_Value;
// 	}
// 	else if (m_nSndOptr_Optr == 1)
// 	{
// 		return nValue < m_nSndOptr_Value;
// 	}
// 	else if (m_nSndOptr_Optr == 2)
// 	{
// 		return nValue >= m_nSndOptr_Value;
// 	}
// 	else if (m_nSndOptr_Optr == 3)
// 	{
// 		return nValue <= m_nSndOptr_Value;
// 	}
// 	else if (m_nSndOptr_Optr == 4)
// 	{
// 		return nValue == m_nSndOptr_Value;
// 	}
// 	else
// 	{
// 		return nValue > m_nSndOptr_Value;
// 	}
}

BOOL Pp_CanRunWPackage(CExBaseObject *pPpObj)
{
	return 0;
}

void CPpProcedureRun::InitRunWPackageScpt()
{
	CPpTemplate *pTemplate = (CPpTemplate*)m_pProcedure->GetAncestor(PPCLASSID_PPTEMPLATE);
	ASSERT (pTemplate != NULL);

	//��������յ����Ĵ���Ķ����򲻴���
	if (pTemplate->m_strOnRecvProcedure != m_pProcedure->m_strID)
	{
		return;
	}

	m_strSndOptr_GlobalVar = pTemplate->m_strSndOptr_GlobalVar;
	m_nSndOptr_Value = pTemplate->m_nSndOptr_Value;

	if (pTemplate->m_strSndOptr_Optr == _T(">"))
	{
		m_nSndOptr_Optr = 0;
	}
	else if (pTemplate->m_strSndOptr_Optr == _T("<"))
	{
		m_nSndOptr_Optr = 1;
	}
	else if (pTemplate->m_strSndOptr_Optr == _T(">="))
	{
		m_nSndOptr_Optr = 2;
	}
	else if (pTemplate->m_strSndOptr_Optr == _T("<="))
	{
		m_nSndOptr_Optr = 3;
	}
	else if (pTemplate->m_strSndOptr_Optr == _T("=="))
	{
		m_nSndOptr_Optr = 4;
	}
	else
	{
		m_nSndOptr_Optr = 0;
	}
}

BOOL CPpProcedureRun::Run()
{
	if (!m_pProcedure->m_bValid)
	{
		m_bProcedureExit = TRUE;
		return TRUE;
	}

	ResetPriorityCounter();  //��λ���ȼ�������

	if (m_pCurrNode == NULL)
	{//��ǰ�ڵ�Ϊ�գ���ȡ���ڵ㣬ִ�нڵ�
		if (g_bLogEngineDebugInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("------run [%s] -----"), m_pProcedure->m_strName.GetString());
		}

		m_dwBeginTickCount = ::GetTickCount();
		m_pProcedure->LogProcedureRunInfor();

		CPpNode *pRootNode = m_pProcedure->GetRootNode();
		ASSERT (pRootNode != NULL);

		if (pRootNode == NULL)
		{//����û��ͷ�ڵ㣬����
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Procedure \"%s\" root node is null"), m_pProcedure->m_strID.GetString());
			m_bProcedureExit = TRUE;
		}
		else
		{//ִ��ͷ�ڵ�
			//ִ�й��̳�ʼ���ű�
			m_pProcedure->RunInitScript();
			SetCurrNode(pRootNode);

			if (m_pProcedure->m_bValid)
			{
				RunNode();
			}
			else
			{
				m_bProcedureExit = TRUE;
			}
		}

		if (!m_bProcedureExit)
		{
			//��ʼ���̱���ץ��
			OnProcedureStart();
		}
	}
	else
	{
		//����Ƕ�ռ����
		if (IsExclusive())
		{
			if (IsCurrTickCountTimeOut(m_dwBeginTickCount, m_pProcedure->m_nReleaseT))
			{
				m_bProcedureExit = TRUE;
			}
			else
			{
				ProcessNode();
			}
		}
		else
		{
			ProcessNode();
		}
	}

	return TRUE; 
}

void CPpProcedureRun::RunNodePkg(const CString &strPackageID, BOOL bRunInitScript, BOOL bRunEndScript)
{
	CPpPackage *pPackage =  PpFindPackageByID(strPackageID, m_pCurrNode);

	//������ʱʱ��
	m_pCurrNode->BeginTimer();

	if (pPackage == NULL)
	{//�սڵ�
		if (strPackageID.GetLength() > 0)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                     , g_sLangTxt_PointFrameUnExist.GetString()/*L"�ڵ�\"%s\"����������֡\"%s\"������"*/
                     , m_pCurrNode->m_strID.GetString(), strPackageID.GetString());
		}

		ProcessNode();
	}
	else
	{//���ͽڵ�
		//�Ƿ�Ϊ����֡�ж�
		if (pPackage->GetClassID() != PPCLASSID_PPPRODUCEPACKGE)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                    ,g_sLangTxt_PointNotFrame.GetString() /*L"�ڵ�\"%s\"������\"%s\"��������֡"*/
                    , m_pCurrNode->m_strID.GetString(), strPackageID.GetString());
		}
		else
		{
			RunWPackage(pPackage, bRunInitScript, bRunEndScript);
		}
	}
}

void CPpProcedureRun::RunNode()
{
	ASSERT (m_pCurrNode != NULL);

	if (m_pCurrNode == NULL)
	{
		m_bProcedureExit = TRUE;
		return;
	}

	if (m_pCurrNode->IsEndNode())
	{
		m_bProcedureExit = TRUE;
	}
	else
	{
		BOOL bRunInitScript = TRUE;
		BOOL bRunEndScript = TRUE;
		CString strPackageID = m_pCurrNode->GetNodePackageID();
		CPpPackageRefs *pPkgRefs = m_pCurrNode->GetPackageRefs();
		strPackageID.Trim();
		long nPkgRefCount = pPkgRefs->GetCount();

		if (nPkgRefCount > 0)
		{
			bRunEndScript = FALSE;
		}

		RunNodePkg(strPackageID, bRunInitScript, bRunEndScript);
		bRunInitScript = FALSE;
		long nPkgIndex = 1;

		if (nPkgRefCount > 0)
		{
			POS pos = pPkgRefs->GetHeadPosition();
			CPpPackageRef *pPkgRef = NULL;

			while (pos != NULL)
			{
				pPkgRef = (CPpPackageRef *)pPkgRefs->GetNext(pos);
				strPackageID = pPkgRef->m_strPkgID;
				strPackageID.Trim();

				if (nPkgIndex == nPkgRefCount)
				{
					bRunEndScript = TRUE;
				}

				RunNodePkg(strPackageID, bRunInitScript, bRunEndScript);
				nPkgIndex++;
			}
		}

		//CPpPackage *pPackage =  PpFindPackageByID(strPackageID, m_pCurrNode);

		////������ʱʱ��
		//m_pCurrNode->BeginTimer();

		//if (pPackage == NULL)
		//{//�սڵ�
		//	if (strPackageID.GetLength() > 0)
		//	{
		//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, g_sLangTxt_PointFrameUnExist/*L"�ڵ�\"%s\"����������֡\"%s\"������"*/, m_pCurrNode->m_strID, strPackageID);
		//	}

		//	ProcessNode();
		//}
		//else
		//{//���ͽڵ�
		//	//�Ƿ�Ϊ����֡�ж�
		//	if (pPackage->GetClassID() != PPCLASSID_PPPRODUCEPACKGE)
		//	{
		//		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,g_sLangTxt_PointNotFrame /*L"�ڵ�\"%s\"������\"%s\"��������֡"*/, m_pCurrNode->m_strID, strPackageID);
		//	}
		//	else
		//	{
		//		RunWPackage(pPackage);
		//	}
		//}

	}
}

void CPpProcedureRun::ProcessNode()
{
	if (m_pProcedure->m_strID == L"Call_YC")
	{
		int i = 0;
	}

	CPpNode* pNodeToRun = NULL;
	
	pNodeToRun = ProcessNodeProcess();

	if (pNodeToRun == NULL)
	{
		pNodeToRun = ProcessNodeJumps();
	}

	if (pNodeToRun == NULL)
	{
		pNodeToRun = ProcessNodeTimers();
	}

	if (pNodeToRun != NULL)
	{
		m_pCurrNode->KillTimer();
		//m_pCurrNode = pNodeToRun;
		//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("goto node %s"), pNodeToRun->m_strName);
		SetCurrNode(pNodeToRun);
		RunNode();
	}
}

CPpNode* CPpProcedureRun::ProcessNodeProcess()
{
	ASSERT (m_pListReceivePackage != NULL);
	ASSERT (m_pEngineThread != NULL);

	if (m_pCurrNode->m_pResponseNodes == NULL)
	{
		return NULL;
	}

	POS posPkg = NULL;
	POS posPkgPrev = NULL;
	CPpNodes *pNodes = m_pCurrNode->m_pResponseNodes;
	POS posNode = pNodes->GetHeadPosition();
	CPpNode *pNode = NULL;
	CPpEngineThreadBase *pEngineThread = (CPpEngineThreadBase*)m_pEngineThread;
	CPpPackageDetail *pPkgDetail = NULL;
	CPpNode *pNodeToRun = NULL;
	CExBaseList oList;

	//����֡������������������֡��������,Ϊ������ٶȣ��������и������ݳ���
	//CAutoSimpleLock oLock(&pEngineThread->m_oRcvPkgCriticSection);
	oList.RemoveAll();
	oList.Append(*m_pListReceivePackage);
	//oLock.Free();

	//������Ӧ�ڵ�
	while (posNode != NULL)
	{
		pNode = (CPpNode*)pNodes->GetNext(posNode);

// 		//����֡������������������֡��������,Ϊ������ٶȣ��������и������ݳ���
		posPkg = oList.GetHeadPosition();

		while (posPkg != NULL)
		{
			posPkgPrev = posPkg;
			pPkgDetail = (CPpPackageDetail*)oList.GetNext(posPkg);

			if (pPkgDetail->m_bUsed)
			{
				continue;
			}

			if (pNode->IsPackageResponse(pPkgDetail))
			{//PackageΪNode����Ӧ
				pNode->ResetTimer();
				pPkgDetail->m_bUsed = TRUE;
				m_pProcedure->m_pPackageRef = pPkgDetail;
				pNodeToRun = pNode->RunJumps(pPkgDetail);
				m_pProcedure->m_pPackageRef = NULL;
			}
		}

		if (pNodeToRun != NULL)
		{
			break;
		}
	}//end of "������Ӧ�ڵ�"

	oList.RemoveAll();

	return pNodeToRun;
}

CPpNode* CPpProcedureRun::ProcessNodeJumps()
{
	if (m_pCurrNode->m_pJumps == NULL)
	{
		return NULL;
	}

	CPpNode *pNodeToRun = NULL;
	
	//��ʱ�����Ƿ��ͽڵ����ת���
	CPpPackageSend *pSend = (CPpPackageSend*)m_pCurrNode->GetPackageSend();

	if (pSend == NULL)
	{
		if (m_pCurrNode->m_pJumps != NULL)
		{
			pNodeToRun = m_pCurrNode->m_pJumps->RunJumps(NULL);
		}
		//return NULL;
	}
	else
	{
		CPpPackageDetail *pDetail = pSend->m_pPackageDetail;

		if (pDetail == NULL)
		{
			return NULL;
		}

		if (m_pCurrNode->m_pJumps != NULL)
		{
			m_pProcedure->m_pPackageRef = pDetail;
			pNodeToRun = m_pCurrNode->m_pJumps->RunJumps(pDetail);
			m_pProcedure->m_pPackageRef = NULL;
		}
	}

	return pNodeToRun;
}

CPpNode* CPpProcedureRun::ProcessNodeTimers()
{
	CPpNode *pNodeToRun = NULL;

	if (m_pCurrNode->m_pTimers != NULL)
	{
		DWORD dwTickCount = ::GetTickCount();
		pNodeToRun = m_pCurrNode->RunTimers(dwTickCount);
	}

	return pNodeToRun;
}

void CPpProcedureRun::SetCurrNode(CPpNode *pNode)
{
	ASSERT (pNode != NULL);

	if (m_pCurrNode != NULL)
	{
		//��ǰ�ڵ��������ִ�н����ű�
		if (m_pCurrNode != pNode )
		{
			m_pCurrNode->RunEndScript(NULL);
		}

		m_pCurrNode->SetPackageSend(NULL);
	}

	//������ǽ����ڵ㣬��ִ�г�ʼ���ű�
	if (pNode != g_pPpEndNode && pNode != m_pCurrNode)
	{
		pNode->RunInitScript(NULL);
	}

	m_pCurrNode = pNode;
}

void CPpProcedureRun::RunWPackage(CPpPackage *pPackage, BOOL bRunInitScript, BOOL bRunEndScript)
{
	CString strTemp = pPackage->m_strID;
	strTemp.MakeLower();

	//������������ģ��򲻴���
	if (strTemp.Find(_T("heart")) < 0)
	{
		if (!CanRunWPackage())
		{
			return;
		}
	}
// 	if (m_pCurrNode->GetPackageSend() != NULL)
// 	{//����Ѿ�����,�򷵻�
// 		return;
// 	}
	pPackage->m_bValid = TRUE;
	CPpEngineThreadBase *pEngineThread = (CPpEngineThreadBase*)m_pEngineThread;
	CPpProducePackage *pRoducePkg = (CPpProducePackage*)pPackage;
	CExBaseList listInterface;
	CPpPackageRef *pPackageRef = m_pCurrNode->m_pPackageRef;
	CPpDataInterface *pDataInterface = NULL;
	CBbVariable *pVarSrc = NULL, *pVarDst = NULL;
	CPpProcedure *pProcedure = (CPpProcedure*)m_pCurrNode->GetAncestor(PPCLASSID_PPPROCEDURE);
	ASSERT (pProcedure != NULL);

	CBbVariables oSrcVariables(_T(""));

	if (pProcedure->m_pDataInterface != NULL)
	{
		pProcedure->m_pDataInterface->Append(oSrcVariables);
	}

	if (pProcedure->m_pVariables != NULL)
	{
		pProcedure->m_pVariables->Append(oSrcVariables);
	}


	//���ù�Լ֡���ݽӿ�ֵ
	pRoducePkg->GetDataInterface(listInterface);
	POS pos = pPackageRef->GetHeadPosition();

	while (pos != NULL)
	{
		pDataInterface = (CPpDataInterface*)pPackageRef->GetNext(pos);
		pVarDst = (CBbVariable*)listInterface.FindByID(pDataInterface->m_strPackageDataID);

		if (pVarDst == NULL)
		{
			//CLogPrint::LogFormatString(XLOGLEVEL_ERROR, L"֡\"%s\"û�ж������ݽӿ�\"%s\"", pRoducePkg->m_strID, pDataInterface->m_strPackageDataID);
		}
		else
		{
			if (IsStringNumber(pDataInterface->m_strProcedureDataID))
			{
				pVarDst->m_strValue = pDataInterface->m_strProcedureDataID;
			}
			else
			{
				pVarSrc = (CBbVariable*)oSrcVariables.FindByID(pDataInterface->m_strProcedureDataID);

				if (pVarSrc == NULL)
				{
                    CLogPrint::LogFormatString(XLOGLEVEL_ERROR
                             , g_sLangTxt_PrcsNoData.GetString()/*L"����\"%s\"û�ж������ݽӿ�\"%s\""*/
                             , pProcedure->m_strID.GetString(), pDataInterface->m_strProcedureDataID.GetString());
				}
				else
				{
					pVarDst->m_strValue = pVarSrc->m_strValue;
				}
			}
		}//else of "if(pVarDst == NULL)"
	}//end of while "pPackageRef

	//ִ�нڵ�ĳ�ʼ���ű�
	m_pProcedure->m_pPackageRef = pRoducePkg;

// 	if (bRunInitScript)
// 	{
// 		m_pCurrNode->RunInitScript(pRoducePkg);
// 	}

	m_pProcedure->m_pPackageRef = NULL;

	oSrcVariables.RemoveAll();
	listInterface.RemoveAll();

	//��������֡�����Լ����
	CPpPackageSend *pPkgSend = pEngineThread->AddPackageSend(this);
	if (pPkgSend == NULL)
	{
		return;
	}

	pPkgSend->m_pEngineThread = pEngineThread;

	if (pRoducePkg != NULL)
	{
		pRoducePkg->m_nPkgNum = pPkgSend->m_pChannel->GetSendIndex();

		if (pRoducePkg->m_pTtPackage != NULL)
		{
			pRoducePkg->m_pTtPackage->m_nPkgNum = pPkgSend->m_pChannel->GetSendIndex();
		}
	}

	PACKAGEBUFFERPOS oPkgBufPos;
	pPkgSend->GetPackageBufferPos(oPkgBufPos);

	CTickCount32 oCTickCount32;
	pRoducePkg->Produce(oPkgBufPos, pPkgSend->m_pPackageDetail);
	pPkgSend->m_oBuffer.OffsetDataFillBeginPosition(oPkgBufPos.nIndex);
	
	if (m_pProtoPkgPrcss != NULL)
	{
		long nLen = pPkgSend->m_oBuffer.GetDataLength();
		m_pProtoPkgPrcss->PrcssAfterProduce(pPkgSend->m_oBuffer.GetBuffer(), nLen);
		pPkgSend->m_oBuffer.ResetOffsetDataFillBeginPosition(nLen, nLen );
	}


	if (g_bLogPackageInfor)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Produce:%d"), oCTickCount32.GetTickCountLong());
	}

	//Ϊ�ڵ��������֡
	m_pCurrNode->SetPackageSend(pPkgSend);

	//���͹�Լ����
	if (pPackage->m_bValid)
	{
		pEngineThread->ResetSendTick();
		pPkgSend->Send();

		if (g_bLogPackageInfor)
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("SendPkg:%s"), pPkgSend->m_pPackageDetail->m_strName.GetString());
		}
	}
	else
	{
		pPkgSend->m_bHasSended = TRUE;
	}

	//ִ�нڵ�Ľ����ű�
	m_pProcedure->m_pPackageRef = pRoducePkg;

// 	if (bRunEndScript)
// 	{
// 		m_pCurrNode->RunEndScript(pRoducePkg);
// 	}

	m_pProcedure->m_pPackageRef = NULL;
}

void CPpProcedureRun::CopyDataInterfaceToPackage()
{
	if (m_pInterface == NULL)
	{
		return;
	}
	
	POS pos = m_pInterface->GetHeadPosition();
	CBbVariable *pVarSrc = NULL;
	CBbVariable *pVarDst = NULL;
	while (pos != NULL)
	{
		pVarSrc = (CBbVariable*)m_pInterface->GetNext(pos);

		pVarDst = (CBbVariable*)m_pProcedure->m_pDataInterface->FindByID(pVarSrc->m_strID);

		if (pVarDst != NULL)
		{
			pVarDst->m_strValue = pVarSrc->m_strValue;
		}
	}
}

void CPpProcedureRun::OnProcedureExit()
{
	((CPpEngineThreadBase*)m_pEngineThread)->OnProcedureExit(this);
}

void CPpProcedureRun::OnProcedureStart()
{
	((CPpEngineThreadBase*)m_pEngineThread)->OnProcedureStart(this);
}

