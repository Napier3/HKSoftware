#include "SttPcapFileRead.h"

#include "../../../Module/API/FileApi.h"
#include "../../../Module/WinPcap/Include/pcap.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/System/TickCount32.h"


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttIecCtrlBlock::CSttIecCtrlBlock()
{
	Init();
}

CSttIecCtrlBlock::~CSttIecCtrlBlock()
{

}

void CSttIecCtrlBlock::Init()
{
	m_dwAppID = 0;
	m_nPkgNum = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CSttIecCtrlBlocks::CSttIecCtrlBlocks()
{
}

CSttIecCtrlBlocks::~CSttIecCtrlBlocks()
{

}

CSttIecCtrlBlock* CSttIecCtrlBlocks::FindByAppID(long dwAppID)
{
	CSttIecCtrlBlock *pSttIecCtrlBlock = NULL,*pFind = NULL;
	POS pos = GetHeadPosition();

	while(pos)
	{
		pSttIecCtrlBlock = (CSttIecCtrlBlock *)GetNext(pos);

		if (pSttIecCtrlBlock->m_dwAppID == dwAppID)
		{
			pFind = pSttIecCtrlBlock;
			break;
		}
	}

	return pFind;
}

void CSttIecCtrlBlocks::AddIecPkg(long dwAppID)
{
	CSttIecCtrlBlock *pSttIecCtrlBlock = FindByAppID(dwAppID);

	if (pSttIecCtrlBlock != NULL)
	{
		pSttIecCtrlBlock->m_nPkgNum++;
	} 
	else
	{
		pSttIecCtrlBlock = new CSttIecCtrlBlock;
		pSttIecCtrlBlock->m_nPkgNum = 1;
		pSttIecCtrlBlock->m_dwAppID = dwAppID;
		AddTail(pSttIecCtrlBlock);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CSttPcapFileRead::CSttPcapFileRead(void)
{
	m_nCurDeliverFiberIndex = 0;
	m_bReadFiberDatasFinish = FALSE;
	m_nCurrDeliverFiberPkgIndex = 0;
	m_pTmtDigReplayParas = NULL;
	m_oCapBufferMngr.SetMaxCount(_STT_PCAP_PARSE_MAX_FRAME_NUM);
}

CSttPcapFileRead::~CSttPcapFileRead(void)
{
}

BOOL CSttPcapFileRead::OpenPcapFile(const CString &strPcapFile)
{
	if (!IsFileExist(strPcapFile))
	{
		return FALSE;
	}

	m_nCurDeliverFiberIndex = 0;
	m_nCurrDeliverFiberPkgIndex = 0;
	m_bReadFiberDatasFinish = FALSE;
	m_oCapBufferMngr.ResetMngr();
	pcap_t* fpPcap_t;
	char errbuf[PCAP_ERRBUF_SIZE];
	fpPcap_t = pcap_open_offline(strPcapFile.GetString(),errbuf);

	if (fpPcap_t == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("Pcap�ļ���ʧ��,����ȱʡPcap�������dll�ļ�."));
		return FALSE;
	}

	//��ȡ�ļ�ֱ����β
	struct pcap_pkthdr* header;		//����ͷ
	const unsigned char* pkt_data;	//��������
	CXSmMemBuffer *pCapBuffer = NULL;
	ETHER_HEADER *pETHER_HEADER = NULL;
	double dTime = 0.0f;
	CSttIecCtrlBlocks oCtrlBlocks_SV,oCtrlBlocks_GS;
	CSttIecCtrlBlock *pSttIecCtrlBlock = NULL;
	u_short uAppID,uEthernetType;  
	long nFrameNum = 0;

	while ((pcap_next_ex(fpPcap_t, &header, &pkt_data)) > 0)
	{
		pETHER_HEADER = (ETHER_HEADER*)pkt_data;

		if (header->len<16)//ȷ�����жϳ�AppID
		{
			continue;
		}

		if (nFrameNum>=_STT_PCAP_PARSE_MAX_FRAME_NUM)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ������֡���ѳ���(%ld),ֻ����ǰ%ld֡����."),nFrameNum,nFrameNum);
			break;
		}

		if (pETHER_HEADER->ether_type == EtherType_Priority)
		{
			if (header->len<20)//����vlan�ı���ȷ�����г�AppID
			{
				continue;
			}

			uEthernetType = ((u_short)pkt_data[17])<<8;
			uEthernetType += pkt_data[16];
			uAppID = ((u_short)pkt_data[18])<<8;
			uAppID += pkt_data[19];
			pCapBuffer = m_oCapBufferMngr.AddFrameBuffer(header, pkt_data);
		}
		else if (pETHER_HEADER->ether_type == EtherType_Smv)
		{
			uEthernetType = EtherType_Smv;
			uAppID = ((u_short)pkt_data[14])<<8;
			uAppID += pkt_data[15];
			pCapBuffer = m_oCapBufferMngr.AddFrameBuffer(header, pkt_data);
		}
		else if (pETHER_HEADER->ether_type == EtherType_Goose)
		{
			uEthernetType = EtherType_Goose;
			uAppID = ((u_short)pkt_data[14])<<8;
			uAppID += pkt_data[15];
			pCapBuffer = m_oCapBufferMngr.AddFrameBuffer(header, pkt_data);
		}
		else
			continue;

		if (uEthernetType == EtherType_Smv)
		{
			oCtrlBlocks_SV.AddIecPkg(uAppID);
		}
		else if (uEthernetType = EtherType_Goose)
		{
			oCtrlBlocks_GS.AddIecPkg(uAppID);
		}

		nFrameNum++;
	}

	Create_PcapIecCtrls(&oCtrlBlocks_SV,&oCtrlBlocks_GS);
	pcap_close(fpPcap_t);
	m_strPcapFilePath = strPcapFile;
	return TRUE;
}

void CSttPcapFileRead::Create_PcapIecCtrls(CSttIecCtrlBlocks *pCtrlBlocks_SV,CSttIecCtrlBlocks *pCtrlBlocks_GS)
{
	m_oPcapCtrls_SV.InitCtrls(pCtrlBlocks_SV->GetCount());
	m_oPcapCtrls_GOOSE.InitCtrls(pCtrlBlocks_GS->GetCount());

	CSttIecCtrlBlock *pCtrlBlock = NULL;
	long nIndex = 0;
	POS pos = pCtrlBlocks_SV->GetHeadPosition();

	while(pos)
	{
		pCtrlBlock = pCtrlBlocks_SV->GetNext(pos);
		m_oPcapCtrls_SV.m_pCtrls[nIndex].InitCtrl(pCtrlBlock->m_dwAppID,pCtrlBlock->m_nPkgNum);
		nIndex++;
	}

	nIndex = 0;
	pos = pCtrlBlocks_GS->GetHeadPosition();

	while(pos)
	{
		pCtrlBlock = pCtrlBlocks_GS->GetNext(pos);
		m_oPcapCtrls_GOOSE.m_pCtrls[nIndex].InitCtrl(pCtrlBlock->m_dwAppID,pCtrlBlock->m_nPkgNum);
		nIndex++;
	}

	AttachAllXSmMemBuffer();
	PcapIecCtrls_ToDigReplayParas();
}

void CSttPcapFileRead::AttachAllXSmMemBuffer()
{
	CFrameMemBuffer* pCXSmMemBuffer = NULL;
	long nMaxFrameNum = m_oCapBufferMngr.GetCurrCount();
	u_short uAppID,uEthernetType;  

	for (int nIndex = 0;nIndex<nMaxFrameNum;nIndex++)
	{
		pCXSmMemBuffer = (CFrameMemBuffer*)m_oCapBufferMngr.GetFrameBuffer(nIndex);

		if (pCXSmMemBuffer == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("AttachAllXSmMemBuffer,��ǰ֡���Ļ�ȡʧ��(%ld)."),nIndex);
			break;
		}

		if (!GetEthernetTypeAppID_ByXSmMemBuffer(pCXSmMemBuffer,uAppID,uEthernetType))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("AttachAllXSmMemBuffer,��ǰ֡����(%ld),�������ͺ�AppID��ȡʧ��."),nIndex);
			continue;
		} 

		if (uEthernetType == EtherType_Smv)
		{
			m_oPcapCtrls_SV.AttachXSmMemBuffer(pCXSmMemBuffer,uAppID,TRUE);
		}
		else if (uEthernetType == EtherType_Goose)
		{
			m_oPcapCtrls_GOOSE.AttachXSmMemBuffer(pCXSmMemBuffer,uAppID,FALSE);
		}
	}
}

void CSttPcapFileRead::PcapIecCtrls_ToDigReplayParas()
{
	if (m_pTmtDigReplayParas == NULL)
	{
		return;
	}

	m_pTmtDigReplayParas->m_nCBNum_SV92 = m_oPcapCtrls_SV.m_nCtrlCount;
	m_pTmtDigReplayParas->m_nCBNum_GOOSE = m_oPcapCtrls_GOOSE.m_nCtrlCount;
	long nIndex = 0;

	for (nIndex = 0;nIndex<m_pTmtDigReplayParas->m_nCBNum_SV92;nIndex++)
	{
		PcapIecCtrl_ToDigReplayParas(&m_oPcapCtrls_SV.m_pCtrls[nIndex],&m_pTmtDigReplayParas->m_oCB_SV92[nIndex]);
	}

	for (nIndex = 0;nIndex<m_pTmtDigReplayParas->m_nCBNum_GOOSE;nIndex++)
	{
		PcapIecCtrl_ToDigReplayParas(&m_oPcapCtrls_GOOSE.m_pCtrls[nIndex],&m_pTmtDigReplayParas->m_oCB_GOOSE[nIndex]);
	}
}

void CSttPcapFileRead::PcapIecCtrl_ToDigReplayParas(P_PCAP_IEC_CTRL pPcapIecCtrl,TMT_DIG_REPLAY_CB *pTmtCB)
{
	pPcapIecCtrl->m_dwTmtCtrl_Attached = (DWORD)pTmtCB;//��tmt���ƿ�ṹ��ָ����������Ŀ��ƿ�
	pTmtCB->m_nAppID = pPcapIecCtrl->m_wAppID;
	pTmtCB->m_nSelCB = pPcapIecCtrl->m_wSelect;
	pTmtCB->m_nTotalFrames = pPcapIecCtrl->m_nPkgCount;
	pTmtCB->m_nBeginFrameIndex = 0;
	pTmtCB->m_nEndFrameIndex = 0;
	pTmtCB->m_fOffsetTime = 0.0f;
	pTmtCB->m_nFiberNum = 0;

	if (pTmtCB->m_nTotalFrames>0)
	{
		pTmtCB->m_nBeginFrameIndex = 1;
		pTmtCB->m_nEndFrameIndex = pTmtCB->m_nTotalFrames;
	}
}

BOOL CSttPcapFileRead::GetEthernetTypeAppID_ByXSmMemBuffer(CXSmMemBuffer *pCXSmMemBuffer,u_short &uAppID,u_short &uEthernetType)
{
	if (pCXSmMemBuffer == NULL)
	{
		return FALSE;
	}

	BYTE* pkt_data = pCXSmMemBuffer->GetBuffer();
	uEthernetType = ((u_short)pkt_data[13])<<8;
	uEthernetType += pkt_data[12];

	if (uEthernetType == EtherType_Priority)
	{
		uEthernetType = ((u_short)pkt_data[17])<<8;
		uEthernetType += pkt_data[16];
		uAppID = ((u_short)pkt_data[18])<<8;
		uAppID += pkt_data[19];
	}
	else if (uEthernetType == EtherType_Smv)
	{
		uAppID = ((u_short)pkt_data[14])<<8;
		uAppID += pkt_data[15];
	}
	else if (uEthernetType == EtherType_Goose)
	{
		uAppID = ((u_short)pkt_data[14])<<8;
		uAppID += pkt_data[15];
	}
	else
		return FALSE;

	return TRUE;
}

void CSttPcapFileRead::FreeAll()
{
	m_oPcapCtrls_SV.FreeCtrls();
	m_oPcapCtrls_GOOSE.FreeCtrls();
	m_oPcapFibersDatas.FreeFibers();
	m_oCapBufferMngr.FreeBuffer();
}

BOOL CSttPcapFileRead::HasPcapSendDatas()
{
	//���SV��GOOSE���ƿ鶼û������,��û�з�������
	if ((!m_oPcapCtrls_SV.HasPcapSendDatas()) && (!m_oPcapCtrls_GOOSE.HasPcapSendDatas()))
	{
		return FALSE;
	}

	if (m_pTmtDigReplayParas == NULL)
	{
		return FALSE;
	}

	return m_pTmtDigReplayParas->HasPcapSendDatas();
}

void CSttPcapFileRead::GenerateFibersDatas()
{
	m_nCurDeliverFiberIndex = 0;
	m_nCurrDeliverFiberPkgIndex = 0;
	m_bReadFiberDatasFinish = FALSE;

	ASSERT(m_pTmtDigReplayParas);
	long nUseFiberNum = m_pTmtDigReplayParas->GetUseFiberNum();
	m_oPcapFibersDatas.InitFibers(nUseFiberNum);
	long nCurrFiberPkgNum = 0,nCurrUseIndex = 0;

	for (int nFiberIndex = 0;nFiberIndex<DIG_REPLAY_FIBER_MAX_NUM;nFiberIndex++)
	{
		nCurrFiberPkgNum = m_pTmtDigReplayParas->GetTotalPkgNum(nFiberIndex);

		if (nCurrFiberPkgNum>0)
		{
			if (nCurrUseIndex < nUseFiberNum)
			{
				if (m_pTmtDigReplayParas->m_nReplayMode_SV == DIG_REPLAY_MODE_PkgTime)//�����ʵ�ʱ���ʱ��ط�
				{
					GenerateFiberDatas_ActPkgOrder(&m_oPcapFibersDatas.m_pFibers[nCurrUseIndex],nFiberIndex,nCurrFiberPkgNum);
				}
				else
				{
					GenerateFiberDatas_NeedSort(&m_oPcapFibersDatas.m_pFibers[nCurrUseIndex],nFiberIndex,nCurrFiberPkgNum);
				}
			}
			else
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰͳ�Ƴ�������,nCurrUseIndex(%ld)>=nUseFiberNum(%ld)"),nCurrUseIndex,nUseFiberNum);
			}

			nCurrUseIndex++;
		}
	}

	if (m_pTmtDigReplayParas->m_nReplayMode_SV == DIG_REPLAY_MODE_EqualInterval)//������ȼ��
	{
		GenerateEqualIntervalPkgsTime();//�Զ����ɵȼ������ʱ��
	}

	if ((m_pTmtDigReplayParas->m_nReplayMode_SV != DIG_REPLAY_MODE_PkgTime)&&(m_pTmtDigReplayParas->GetCurSelCtrlNum_SVGOOSE()>1))//���ֻ��1�����ƿ�,����Ҫ��������
	{
		m_oPcapFibersDatas.SortAllPkgs();
	}
}

//����1Ϊ��һ֡���ľ���ʱ��,����2Ϊ��ǰ���ƿ����ʱʱ��,����3Ϊ��Ա����ƿ��һ֡���ĵ����ʱ��
__int64 Global_CalPkgTime(__int64 nBeginPkgTime_Int64,double dCurrCB_DelayTime,double dCurrRelativeTime)
{
	__int64 dwTime_S = nBeginPkgTime_Int64 >> 32;
	DWORD dwTime_NS = nBeginPkgTime_Int64 & 0xFFFFFFFF;
	double dTotalRelativeTime = dCurrCB_DelayTime + dCurrRelativeTime;
	long nTmpValue = dTotalRelativeTime/1000000;
	dwTime_S += nTmpValue;
	dTotalRelativeTime -= (nTmpValue*1000000);
	dwTime_NS += dTotalRelativeTime;

	if (dwTime_NS>= 1000000)
	{
		dwTime_S++;
		dwTime_NS -=1000000;
	}

	__int64 nCalTime_Int64 = (dwTime_S<<32);
	nCalTime_Int64 += dwTime_NS;
	return nCalTime_Int64;
}

void CSttPcapFileRead::GenerateEqualIntervalPkgsTime()
{
	CFrameMemBuffer *pCXSmMemBuffer = (CFrameMemBuffer*)m_oCapBufferMngr.GetFrameBuffer(0);

	if (pCXSmMemBuffer == NULL)
	{
		return;
	}

	__int64 nBeginPkgTime_Int64 = pCXSmMemBuffer->m_oCapBufferItem.Time;//��ȡ��ʼ֡����ʱ��
	__int64 n64DataTime_Cal = 0;
	double dCurrCB_DelayTime = 0;

	for (int nCBIndex = 0;nCBIndex< m_oPcapCtrls_SV.m_nCtrlCount;nCBIndex++)
	{
		if (!m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].HasSendDatas())
		{
			continue;
		}

		dCurrCB_DelayTime = m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_fOffsetTime;

		for (int nPkgIndex = 0;nPkgIndex<m_oPcapCtrls_SV.m_pCtrls[nCBIndex].m_nPkgCount;nPkgIndex++)
		{
			n64DataTime_Cal = Global_CalPkgTime(nBeginPkgTime_Int64,dCurrCB_DelayTime,nPkgIndex*m_pTmtDigReplayParas->m_fEqualIntervalTimeSV);
			m_oPcapCtrls_SV.m_pCtrls[nCBIndex].m_pPkgs[nPkgIndex].m_n64DataTime_Cal = n64DataTime_Cal;
		}
	}
}

void CSttPcapFileRead::GenerateFiberDatas_NeedSort(PCAP_IEC_FIBER_PORT *pPcapIecFiber,long nFiberPortIndex,long nPkgNum)
{
	ASSERT(m_pTmtDigReplayParas);
	pPcapIecFiber->InitPkgs(nFiberPortIndex,nPkgNum);

	long nTotalPkgNum = 0;
	P_PCAP_IEC_CTRL pPcapIecCtrl = NULL;

	for (int nCBIndex = 0;nCBIndex<m_pTmtDigReplayParas->m_nCBNum_SV92;nCBIndex++)
	{
		if (!m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].HasSendDatas())
		{
			continue;
		}

		if (!m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].HasSelCurrFiberIndex(nFiberPortIndex))
		{
			continue;
		}

		pPcapIecCtrl = m_oPcapCtrls_SV.FindPcapIecCtrl(m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_nAppID);

		if (pPcapIecCtrl != NULL)
		{
			AddFiberCtrlDatas(pPcapIecFiber,pPcapIecCtrl,m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_nBeginFrameIndex,
				m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_nEndFrameIndex);
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�ڲ���ֵ���Ŀ��ƿ�m_oPcapCtrls_SV�в���AppID(0x%04X)ʧ��."),m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_nAppID);
		}
	}

	for (int nCBIndex = 0;nCBIndex<m_pTmtDigReplayParas->m_nCBNum_GOOSE;nCBIndex++)
	{
		if (!m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].HasSendDatas())
		{
			continue;
		}

		if (!m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].HasSelCurrFiberIndex(nFiberPortIndex))
		{
			continue;
		}

		pPcapIecCtrl = m_oPcapCtrls_GOOSE.FindPcapIecCtrl(m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].m_nAppID);

		if (pPcapIecCtrl != NULL)
		{
			AddFiberCtrlDatas(pPcapIecFiber,pPcapIecCtrl,m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].m_nBeginFrameIndex,
				m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].m_nEndFrameIndex);
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��GOOSE���Ŀ��ƿ�m_oCB_GOOSE�в���AppID(0x%04X)ʧ��."),m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].m_nAppID);
		}
	}
}

void CSttPcapFileRead::GenerateFiberDatas_ActPkgOrder(PCAP_IEC_FIBER_PORT *pPcapIecFiber,long nFiberPortIndex,long nPkgNum)
{
	ASSERT(m_pTmtDigReplayParas);
	pPcapIecFiber->InitPkgs(nFiberPortIndex,nPkgNum);

	PCAP_IEC_PKG *pIecPkg = NULL;
	P_PCAP_IEC_CTRL pPcapIecCtrl = NULL;
	TMT_DIG_REPLAY_CB *pTmtDigReplayCB = NULL;
	CFrameMemBuffer* pCXSmMemBuffer = NULL;
	long nMaxFrameNum = m_oCapBufferMngr.GetCurrCount();
	u_short uAppID,uEthernetType;  
	int nFrameIndex = 0;

	if (m_pTmtDigReplayParas->m_nReplayIntervalType)//Ϊ1�ǲ��ֻط�ģʽ
	{
		nFrameIndex = m_pTmtDigReplayParas->m_nTotalFrameBeginIndex - 1;

		if (nFrameIndex<0)
		{
			nFrameIndex = 0;
		}

		nMaxFrameNum = m_pTmtDigReplayParas->m_nTotalFrameEndIndex;
	}

	for (;nFrameIndex<nMaxFrameNum;nFrameIndex++)
	{
		pCXSmMemBuffer = (CFrameMemBuffer*)m_oCapBufferMngr.GetFrameBuffer(nFrameIndex);

		if (pCXSmMemBuffer == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("GenerateFiberDatas_ActPkgOrder,��ǰ֡���Ļ�ȡʧ��(%ld)."),nFrameIndex);
			break;
		}

		if (pCXSmMemBuffer->m_dwReserved == NULL)
		{
			continue;
		}

		pIecPkg = (PCAP_IEC_PKG *)pCXSmMemBuffer->m_dwReserved;
		pPcapIecCtrl = (PCAP_IEC_CTRL*)pIecPkg->dwParent;
		pTmtDigReplayCB = (TMT_DIG_REPLAY_CB*)pPcapIecCtrl->m_dwTmtCtrl_Attached;

		if (pTmtDigReplayCB == NULL)
		{
			continue;
		}

		if ((!pTmtDigReplayCB->HasSendDatas())||(!pTmtDigReplayCB->HasSelCurrFiberIndex(nFiberPortIndex)))
		{
			continue;
		}

		pPcapIecFiber->AttachIecPkg(pIecPkg);
	}
}

void CSttPcapFileRead::AddFiberCtrlDatas(PCAP_IEC_FIBER_PORT *pPcapIecFiber,P_PCAP_IEC_CTRL pPcapIecCtrl,long nBeginFrameIndex,long nEndFrameIndex)
{
	if (nBeginFrameIndex <= 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ���ƿ�(0x%04X)����ʼ֡��(%ld)С�ڵ���0."),pPcapIecCtrl->m_wAppID,nBeginFrameIndex);
		return;
	}

	if (nEndFrameIndex>pPcapIecCtrl->m_nPkgCount)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ���ƿ�(0x%04X)�Ľ���֡��(%ld)����ʵ�ʽ������ı�����֡��(%ld)."),
			pPcapIecCtrl->m_wAppID,nEndFrameIndex,pPcapIecCtrl->m_nPkgCount);
		return;
	}

	for (int nFrameIndex = nBeginFrameIndex;nFrameIndex<=nEndFrameIndex;nFrameIndex++)
	{
		pPcapIecFiber->AttachIecPkg(&pPcapIecCtrl->m_pPkgs[nFrameIndex - 1]);
	}
}


//���ABBuf����
BOOL CSttPcapFileRead::GenerateABBuf(int nIndex)
{
	CComtradeDataBuffer *pABBuf = CComtradeBufMngr::g_pComtradeBufMngr->GetBufByIndex(nIndex);
	pABBuf->ResetWritePos();

 	while(TRUE)
 	{
 		//��һ������ReplayBufԭʼ���������pABBuf
 		if(GenerateABBufFromReplayBuf(pABBuf))
 		{//˵����ɻ��������
 			break;
 		}
 
 		//˵��pABBufδ������ReplayBuf����
 		if (m_bReadFiberDatasFinish)
 		{
// 			m_bAnalysisFinish = TRUE;
 			break;
 		}
 	}

	pABBuf->SetRWState(COMTRADE_DATABUF_MODE_READ);

	return TRUE;
}

long CSttPcapFileRead::GetPkgDataAreaLenth32bits_SinglePkg(CFrameMemBuffer *pXSmMemBuffer,BOOL bCalFourMultiple)
{
	long nPkgLenth = pXSmMemBuffer->GetBufferLength();
	long nPkgDataAreaLenth_32bits = 4 + (nPkgLenth/4);//�������ݳ���,��λΪ4�ֽ�(ǰ�汨��ͷ�����ĳ��ȡ�ʱ��ռ�ÿռ�Ϊ4)

	if ((nPkgLenth%4)>0)//����������ݲ��ֳ��Ȳ�Ϊ4��������,�̶���1,����Ĳ��ֺ�����0
	{
		nPkgDataAreaLenth_32bits++;
	}

	if (bCalFourMultiple)
	{
		int nRemainder = nPkgDataAreaLenth_32bits%4;

		if (nRemainder>0)//��������(N)����Ҫ��֤Ϊ4��������,�˴�����ȷ��
		{
			nPkgDataAreaLenth_32bits += (4 - nRemainder);
		}
	}
	
	return nPkgDataAreaLenth_32bits;
}

long CSttPcapFileRead::GetPkgDataAreaLenth_32bits(CFrameMemBuffer *pXSmMemBuffer,long nPrevPkgDataAreaLenth)
{
	long nPkgLenth = pXSmMemBuffer->GetBufferLength();
	long nPkgDataAreaLenth_32bits = 4 + (nPkgLenth/4);//�������ݳ���,��λΪ4�ֽ�(ǰ�汨��ͷ�����ĳ��ȡ�ʱ��ռ�ÿռ�Ϊ4)

	if ((nPkgLenth%4)>0)//����������ݲ��ֳ��Ȳ�Ϊ4��������,�̶���1,����Ĳ��ֺ�����0
	{
		nPkgDataAreaLenth_32bits++;
	}

	int nRemainder = (nPkgDataAreaLenth_32bits + nPrevPkgDataAreaLenth)%4;

	if (nRemainder>0)//��������(N)����Ҫ��֤Ϊ4��������,�˴�����ȷ��
	{
		nPkgDataAreaLenth_32bits += (4 - nRemainder);
	}

	return nPkgDataAreaLenth_32bits;
}

long CSttPcapFileRead::FillPkgData_Single(CComtradeDataBuffer *pABBuf,PCAP_IEC_PKG *pP_PCAP_IEC_PKG,long &nCurrDeliverFiberPkgIndex)
{
	long nFillDataLenth = GetPkgDataAreaLenth32bits_SinglePkg(pP_PCAP_IEC_PKG->pXSmMemBuffer,FALSE);//�������ݳ���,��λΪ4�ֽ�(ǰ�汨��ͷ�����ĳ��ȡ�ʱ��ռ�ÿռ�Ϊ4)
	DWORD dwValue = 0x0000aaaa;
	pABBuf->WriteData((BYTE*)&dwValue,4);//��������ͷ
	dwValue = pP_PCAP_IEC_PKG->pXSmMemBuffer->GetBufferLength();
	pABBuf->WriteData((BYTE*)&dwValue,4);//����1��Pcap������Ч����
	double dNs_Value = 0.0f;

	if (m_pTmtDigReplayParas->m_nReplayMode_SV == DIG_REPLAY_MODE_PkgTime)//Ŀǰֻ�ж�SV�Ļط�ģʽ,����ͳһΪ��ͬ�Ļط�ģʽ
	{
		dwValue = pP_PCAP_IEC_PKG->pXSmMemBuffer->m_oCapBufferItem.Time >> 32;
		pABBuf->WriteData((BYTE*)&dwValue,4);//������ֵʱ��
		dwValue = pP_PCAP_IEC_PKG->pXSmMemBuffer->m_oCapBufferItem.Time & 0xFFFFFFFF;
//		dwValue *= 1000;//��������ֵʱ��
		dNs_Value = dwValue*0.000001f;
		dNs_Value *= 0xFFFFFFFF;
		dwValue = dNs_Value;
		pABBuf->WriteData((BYTE*)&dwValue,4);//��������ֵʱ��
	} 
	else
	{
		dwValue = pP_PCAP_IEC_PKG->m_n64DataTime_Cal >> 32;
		pABBuf->WriteData((BYTE*)&dwValue,4);//������ֵʱ��
		dwValue = pP_PCAP_IEC_PKG->m_n64DataTime_Cal & 0xFFFFFFFF;
//		dwValue *= 1000;//��������ֵʱ��
		dNs_Value = dwValue*0.000001f;
		dNs_Value *= 0xFFFFFFFF;
		dwValue = dNs_Value;
		pABBuf->WriteData((BYTE*)&dwValue,4);//��������ֵʱ��
	}
	
	pABBuf->WriteData((BYTE*)pP_PCAP_IEC_PKG->pXSmMemBuffer->GetBuffer(),pP_PCAP_IEC_PKG->pXSmMemBuffer->GetBufferLength());
	nCurrDeliverFiberPkgIndex++;
	return nFillDataLenth;
}

//����AB�����Ƿ��������
BOOL CSttPcapFileRead::FillPkgDatas(CComtradeDataBuffer *pABBuf,PCAP_IEC_FIBER_PORT *pFibers,long &nCurrDeliverFiberPkgIndex)
{
	BOOL bRet = FALSE;
	long nABBuffRemainSpace = pABBuf->GetRemainSpace();//��ȡpABBuf��ǰ������ܳ���
	//�������1֡����,��ͳ�����1֡��������Ŀռ�,ǰ��Ϊ�Ǳ������ݲ���ռ�õĳ���
	long nSendDataLenth = 4 + GetPkgDataAreaLenth32bits_SinglePkg(pFibers->m_pPkgs[nCurrDeliverFiberPkgIndex]->pXSmMemBuffer,TRUE);

	if (nABBuffRemainSpace<nSendDataLenth)
	{
		return TRUE;
	}

	DWORD dwValue = STT_AT02_FIXED_HEAD;
	pABBuf->WriteData((BYTE*)&dwValue,4);//��д֡ͷ
	dwValue = nSendDataLenth - 2;
	long *pnPkgLenth = (long*)pABBuf->WriteData((BYTE*)&dwValue,4);//����֡����,���ں�������ʵ�ʳ�����������;
	dwValue = 0x0000100e;
	pABBuf->WriteData((BYTE*)&dwValue,4);//����֡����
	dwValue = 1<<pFibers->m_nFiberIndex;
	*pnPkgLenth = 2;

 	if (nCurrDeliverFiberPkgIndex == 0)//��1֡����  
 	{
 		dwValue += (1<<30);
 		pABBuf->WriteData((BYTE*)&dwValue,4);//���õ�1֡���
 		*pnPkgLenth += FillPkgData_Single(pABBuf,pFibers->m_pPkgs[nCurrDeliverFiberPkgIndex],nCurrDeliverFiberPkgIndex);
 	}
	//2023.9.2 zhouhj ���һ֡���ٵ�������
//  	else if (nCurrDeliverFiberPkgIndex == (pFibers->m_nPkgCount - 1))//���һ֡����
//  	{
//  		dwValue += (1<<31);
//  		pABBuf->WriteData((BYTE*)&dwValue,4);//�������1֡���
//  		*pnPkgLenth += FillPkgData_Single(pABBuf,pFibers->m_pPkgs[nCurrDeliverFiberPkgIndex],nCurrDeliverFiberPkgIndex);
//  	}
 	else//�м�֡����
	{
		pABBuf->WriteData((BYTE*)&dwValue,4);//�����м�֡���

		while(nABBuffRemainSpace>=nSendDataLenth)
		{
			*pnPkgLenth += FillPkgData_Single(pABBuf,pFibers->m_pPkgs[nCurrDeliverFiberPkgIndex],nCurrDeliverFiberPkgIndex);

			//2023.9.2 zhouhj ���һ֡���ٵ�������,��ǰ֡���ڵ�����֡��,��ǰ���������
			if (nCurrDeliverFiberPkgIndex >= (pFibers->m_nPkgCount/* - 1*/))//�����һ֡Ϊ���1֡,���������
			{
				break;
			}

			nABBuffRemainSpace = pABBuf->GetRemainSpace();//��ȡpABBuf��ǰ������ܳ���
			nSendDataLenth = GetPkgDataAreaLenth_32bits(pFibers->m_pPkgs[nCurrDeliverFiberPkgIndex]->pXSmMemBuffer,(*pnPkgLenth)-2);
		}

		if (nABBuffRemainSpace < nSendDataLenth)
		{
			bRet = TRUE;
		}
	}

	long nDataAreaLenth = (*pnPkgLenth) - 2;
	int nRemainder = nDataAreaLenth%4;

	if (nRemainder>0)//��������(N)����Ҫ��֤Ϊ4��������,�˴�����ȷ��
	{
		(*pnPkgLenth) += (4 - nRemainder);
		pABBuf->WriteData_Zero(4 - nRemainder);
	}


	return bRet;
}


//�ɻطŻ���ReplayBuf���AB����,������������򷵻�TRUE,���򷵻�FALSE
BOOL CSttPcapFileRead::GenerateABBufFromReplayBuf(CComtradeDataBuffer *pABBuf)
{
//	CString strTextFilePath;
// 	SYSTEMTIME tm;
// 	::GetLocalTime(&tm);
// 	strTextFilePath = _P_GetBinPath();
// 	strTextFilePath.AppendFormat(_T("sttComtrade_local-%04d.%02d.%02d_%02d-%02d-%02d-%03d.txt"),
// 		tm.wYear,tm.wMonth,tm.wDay, tm.wHour, tm.wMinute, tm.wSecond ,tm.wMilliseconds);
// 	OpenCmtrdSaveFile(strTextFilePath);
 	//AB�������������TRUE,ReplayBuf�������AB����δ��������FALSE
	BOOL bHasFillFull = FALSE;//�Ƿ��Ѿ�����

	while ((m_nCurDeliverFiberIndex < m_oPcapFibersDatas.m_nFiberCount)&&(!bHasFillFull))
	{
		if (m_nCurrDeliverFiberPkgIndex == 0)//�ж��Ƿ�Ϊ�ù�ڵ�һ֡����
		{
			bHasFillFull = FillPkgDatas(pABBuf,&m_oPcapFibersDatas.m_pFibers[m_nCurDeliverFiberIndex],m_nCurrDeliverFiberPkgIndex);
		}

		//�ж��Ƿ�Ϊ��ǰ����м�֡����
		if ((m_nCurrDeliverFiberPkgIndex>0) && (!bHasFillFull) &&
			(m_nCurrDeliverFiberPkgIndex<(m_oPcapFibersDatas.m_pFibers[m_nCurDeliverFiberIndex].m_nPkgCount/*-1*/)))
		{
			bHasFillFull = FillPkgDatas(pABBuf,&m_oPcapFibersDatas.m_pFibers[m_nCurDeliverFiberIndex],m_nCurrDeliverFiberPkgIndex);
		}

// 		//�ж��Ƿ�Ϊ���һ֡���� 
// 		if ((!bHasFillFull)&&(m_nCurrDeliverFiberPkgIndex == (m_oPcapFibersDatas.m_pFibers[m_nCurDeliverFiberIndex].m_nPkgCount-1)))
// 		{
// 			bHasFillFull = FillPkgDatas(pABBuf,&m_oPcapFibersDatas.m_pFibers[m_nCurDeliverFiberIndex],m_nCurrDeliverFiberPkgIndex);
// 		}

		//���m_nCurrDeliverFiberPkgIndex���ڵ��ڱ�����֡��,��ǰ������һ֡����������
		if (m_nCurrDeliverFiberPkgIndex >= m_oPcapFibersDatas.m_pFibers[m_nCurDeliverFiberIndex].m_nPkgCount)
		{
			m_nCurrDeliverFiberPkgIndex = 0;
			m_nCurDeliverFiberIndex++;
		}
	}
	
	if (m_nCurDeliverFiberIndex >= m_oPcapFibersDatas.m_nFiberCount)
	{
		m_nCurDeliverFiberIndex = 0;
		m_nCurrDeliverFiberPkgIndex = 0;
		m_bReadFiberDatasFinish = TRUE;
	}

//	m_oCmtrdSaveFile.Write(pABBuf->GetBuffer(),pABBuf->GetDataLen()*4);
//	CloseCmtrdSaveFile();
 	return bHasFillFull;
}

void CSttPcapFileRead::CalOutputTime()
{
	PCAP_IEC_CTRL *pPcapIecCtrl = NULL;
	__int64 nBeginTime = -1,nEndTime = -1,nTmp64Data = 0;
	long nBeginFrameIndex = 0,nEndFrameIndex = 0,nCurrFrameIndex = 0;

	for (int nCBIndex = 0;nCBIndex<m_pTmtDigReplayParas->m_nCBNum_SV92;nCBIndex++)
	{
		if (!m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].HasSendDatas())
		{
			continue;
		}

		pPcapIecCtrl = m_oPcapCtrls_SV.FindPcapIecCtrl(m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_nAppID);

		if (pPcapIecCtrl == NULL)
		{
			continue;
		}

		nBeginFrameIndex = m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_nBeginFrameIndex;
		nEndFrameIndex = m_pTmtDigReplayParas->m_oCB_SV92[nCBIndex].m_nEndFrameIndex;

		if ((nBeginFrameIndex<=0)||(nBeginFrameIndex>pPcapIecCtrl->m_nPkgCount))
		{
			continue;
		}

		if((nEndFrameIndex<=0)||(nEndFrameIndex>pPcapIecCtrl->m_nPkgCount))
		{
			continue;
		}

		nCurrFrameIndex = nBeginFrameIndex - 1;

		for (;nCurrFrameIndex<nEndFrameIndex;nCurrFrameIndex++)
		{
			nTmp64Data = pPcapIecCtrl->m_pPkgs[nCurrFrameIndex].pXSmMemBuffer->m_oCapBufferItem.Time;

			if (m_pTmtDigReplayParas->m_nReplayMode_SV != DIG_REPLAY_MODE_PkgTime)
			{
				nTmp64Data = pPcapIecCtrl->m_pPkgs[nCurrFrameIndex].m_n64DataTime_Cal;
			}
			if (nBeginTime < 0)
			{
				nBeginTime = nTmp64Data;
			}

			if (nBeginTime > nTmp64Data)
			{
				nBeginTime = nTmp64Data;
			}

			if (nEndTime < nTmp64Data)
			{
				nEndTime = nTmp64Data;
			}
		}
	}

	for (int nCBIndex = 0;nCBIndex<m_pTmtDigReplayParas->m_nCBNum_GOOSE;nCBIndex++)
	{
		if (!m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].HasSendDatas())
		{
			continue;
		}

		pPcapIecCtrl = m_oPcapCtrls_GOOSE.FindPcapIecCtrl(m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].m_nAppID);

		if (pPcapIecCtrl == NULL)
		{
			continue;
		}

		nBeginFrameIndex = m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].m_nBeginFrameIndex;
		nEndFrameIndex = m_pTmtDigReplayParas->m_oCB_GOOSE[nCBIndex].m_nEndFrameIndex;

		if ((nBeginFrameIndex<=0)||(nBeginFrameIndex>pPcapIecCtrl->m_nPkgCount))
		{
			continue;
		}

		if((nEndFrameIndex<=0)||(nEndFrameIndex>pPcapIecCtrl->m_nPkgCount))
		{
			continue;
		}

		nCurrFrameIndex = nBeginFrameIndex - 1;

		for (;nCurrFrameIndex<nEndFrameIndex;nCurrFrameIndex++)
		{
			nTmp64Data = pPcapIecCtrl->m_pPkgs[nCurrFrameIndex].pXSmMemBuffer->m_oCapBufferItem.Time;

			if (m_pTmtDigReplayParas->m_nReplayMode_SV != DIG_REPLAY_MODE_PkgTime)
			{
				nTmp64Data = pPcapIecCtrl->m_pPkgs[nCurrFrameIndex].m_n64DataTime_Cal;
			}
			if (nBeginTime < 0)
			{
				nBeginTime = nTmp64Data;
			}

			if (nBeginTime > nTmp64Data)
			{
				nBeginTime = nTmp64Data;
			}

			if (nEndTime < nTmp64Data)
			{
				nEndTime = nTmp64Data;
			}
		}
	}

	if (nBeginTime < 0)
	{
		m_pTmtDigReplayParas->m_fOutPutTime = 0.5;
	}
	else
	{
		DWORD dwBeginTime_s = nBeginTime >> 32;
		DWORD dwBeginTime_us = nBeginTime & 0xFFFFFFFF;
		DWORD dwEndTime_s = nEndTime >> 32;
		DWORD dwEndTime_us = nEndTime & 0xFFFFFFFF;
		double dTmp = dwEndTime_us; 
		dTmp -= dwBeginTime_us;
		dTmp /= 1000000;
		m_pTmtDigReplayParas->m_fOutPutTime = dwEndTime_s - dwBeginTime_s;
		m_pTmtDigReplayParas->m_fOutPutTime += dTmp;
		m_pTmtDigReplayParas->m_fOutPutTime += 0.5;//����0.5s��ԣ��
	}


//	m_pTmtDigReplayParas->m_fOutPutTime = ;
}

CString CSttPcapFileRead::GetNetCardID(long nIndex)
{
	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs;

	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		return _T("");
	}

	pcap_if_t *d;
	int nCurrIndex = 0;
	CString strCardID;

	/* Print the list */
	for (d = alldevs; d; d = d->next)
	{
 		if (nCurrIndex == nIndex)
		{
			strCardID = d->name;
			pcap_freealldevs(alldevs);
			return strCardID;
		}

		nCurrIndex++;
	}

	pcap_freealldevs(alldevs);
	return _T("");
}

BOOL CSttPcapFileRead::SimulateSendPcap(const CString &strNetCardID)
{
	long nMaxFrameNum = m_oCapBufferMngr.GetCurrCount();

	if (nMaxFrameNum <=0)
	{
		return FALSE;
	}

	char errbuf[PCAP_ERRBUF_SIZE];
	pcap_if_t *alldevs;

	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		return FALSE;
	}

	pcap_if_t *d;
	CString strName;
	BOOL bHasFind = FALSE;

	/* Print the list */
	for (d = alldevs; d; d = d->next)
	{
		strName = d->name;

		if (strName == strNetCardID)
		{
			bHasFind = TRUE;
			break;
		}
	}

	if (!bHasFind)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("δ���ҵ���Ӧ����(%s)."),strNetCardID.GetString());
		return FALSE;
	}

	 pcap_t *fp;

	/* Open the adapter */
	if ((fp = pcap_open_live(d->name,   // name of the device
		65536,         // portion of the packet to capture.
		// 65536 grants that the whole packet will be captured on all the MACs.
		1,             // promiscuous mode (nonzero means promiscuous)
		1000,          // read timeout
		errbuf         // error buffer
		)) == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Unable to open the adapter. %s is not supported by WinPcap.")
			,d->name);
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return FALSE;
	}

	u_short uAppID,uEthernetType; 
	CFrameMemBuffer *pCXSmMemBuffer = NULL;
	CTickCount32 oTickCount(TRUE);
	__int64 u64_BeginTime = 0;
	unsigned long nPkgTimeGap = 0,nActTimeGap = 0;
	pCXSmMemBuffer = (CFrameMemBuffer*)m_oCapBufferMngr.GetFrameBuffer(0);
	u64_BeginTime = pCXSmMemBuffer->m_oCapBufferItem.Time;

	for (int nIndex = 0;nIndex<nMaxFrameNum;nIndex++)
	{
		pCXSmMemBuffer = (CFrameMemBuffer*)m_oCapBufferMngr.GetFrameBuffer(nIndex);

		if (pCXSmMemBuffer == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ֡���Ļ�ȡʧ��(%ld)."),nIndex);
			break;
		}

		nPkgTimeGap = GetTimeGap_EpcapBufferItem(pCXSmMemBuffer->m_oCapBufferItem.Time,u64_BeginTime);
		nActTimeGap = oTickCount.GetTickCountLong(FALSE);

		//1����ǰʱ�����һ�����Ŀ�ʼ����ʱ��ʱ��С�ڣ���ǰ�������һ֡����ʱ���ʱ����ȴ�����ʱ�䵽
		while(nActTimeGap*1000 < nPkgTimeGap)
		{
			oTickCount.DoEvents(1);
			nActTimeGap = oTickCount.GetTickCountLong(FALSE);
		}

		//pcap_sendpacket(fp,   packet, 100 );
		// Send down the packet
		if (pcap_sendpacket(fp, // Adapter
			pCXSmMemBuffer->GetBuffer(),              // buffer with the packet
			(pCXSmMemBuffer->GetBufferLength())                   // size
			) != 0)
		{
			pcap_freealldevs(alldevs);
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Error sending the packet: %s."), pcap_geterr(fp));
			return FALSE;
		}
	}

	pcap_freealldevs(alldevs);
	return TRUE;
}

void CSttPcapFileRead::SetPkgsPlayBackDatas(long nBeginIndex,long nAllCBEndIndex)
{
	m_pTmtDigReplayParas->InitAllCB_TotalFrames();

// 	//�����ʼ֡С��1 ֱ�ӷ���  //���÷�Χ��A��1��A��B��B��N��NΪ���п��ƿ���֡�������ֵ
// 	long nCurrCount = m_oCapBufferMngr.GetCurrCount();
// 
// 	if (nBeginIndex < 1)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��ʼ֡Ϊ%ld������С��1."),nBeginIndex);
// 		return;
// 	}
// 	else if (nBeginIndex > nAllCBEndIndex)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ��ʼ֡Ϊ%ld���ڽ���֡%ld."),nBeginIndex,nAllCBEndIndex);
// 		return;
// 	}
// 	else if (nAllCBEndIndex > nCurrCount)
// 	{
// 		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����֡%ld�������п��ƿ����֡��%ld."),nAllCBEndIndex,nCurrCount);
// 		return;
// 	}

	//���ҿ��ƿ�ID
	CFrameMemBuffer* pCXSmMemBuffer = NULL;
	u_short uAppID,uEthernetType;
	PCAP_IEC_CTRL *pPcapIecCtrl = NULL;

 	TMT_DIG_REPLAY_CB *pReplayCB = NULL;

 	int nTotalFrames = 0;
	QList<long> nListAppID;

	for (int nIndex = nBeginIndex-1;nIndex<nAllCBEndIndex;nIndex++ )
	{
		pCXSmMemBuffer = (CFrameMemBuffer*)m_oCapBufferMngr.GetFrameBuffer(nIndex);
		
		if (pCXSmMemBuffer == NULL)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("AttachAllXSmMemBuffer,��ǰ֡���Ļ�ȡʧ��(%ld)."),nIndex);
			break;
		}

		if (!GetEthernetTypeAppID_ByXSmMemBuffer(pCXSmMemBuffer,uAppID,uEthernetType))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("AttachAllXSmMemBuffer,��ǰ֡����(%ld),�������ͺ�AppID��ȡʧ��."),nIndex);
			continue;
		} 


		if (uEthernetType == EtherType_Smv)
		{
			pReplayCB = m_pTmtDigReplayParas->FindTotalPkgCtrl_SV(uAppID);
		
 			pPcapIecCtrl = m_oPcapCtrls_SV.FindPcapIecCtrl(uAppID);

			if((pPcapIecCtrl == NULL) || (pReplayCB == NULL))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�ڿ��ƿ��в���AppID(0x%04X)ʧ��."),uAppID);
				continue;
			}

			long nCurrIndex = pPcapIecCtrl->FindMemBufer(pCXSmMemBuffer);

			if (nCurrIndex <0)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�ڿ��ƿ��в���(0x%04X)ʧ��."),nCurrIndex);

				continue;
			}

			nCurrIndex++;

			if (pReplayCB->m_nBeginFrameIndex<0)
			{
				pReplayCB->m_nBeginFrameIndex = nCurrIndex;
			}
			
			pReplayCB->m_nEndFrameIndex = nCurrIndex++;
			
		}
		
		if (uEthernetType == EtherType_Goose)
		{
			pReplayCB = m_pTmtDigReplayParas->FindTotalPkgCtrl_GOOSE(uAppID);

			pPcapIecCtrl = m_oPcapCtrls_GOOSE.FindPcapIecCtrl(uAppID);
	
			if((pPcapIecCtrl == NULL) || (pReplayCB == NULL))
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�ڿ��ƿ��в���AppID(0x%04X)ʧ��."),uAppID);
				continue;
			}

			long nCurrIndex = pPcapIecCtrl->FindMemBufer(pCXSmMemBuffer);

			if (nCurrIndex <0)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("�ڿ��ƿ��в���(0x%04X)ʧ��."),nCurrIndex);

				continue;
			}

			nCurrIndex++;

			if (pReplayCB->m_nBeginFrameIndex<0)
			{
				pReplayCB->m_nBeginFrameIndex = nCurrIndex;
			}

			pReplayCB->m_nEndFrameIndex = nCurrIndex++;
			

		}

	}

}