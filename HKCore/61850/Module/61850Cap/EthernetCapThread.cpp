#include "StdAfx.h"
#include "EthernetCapThread.h"
#include "..\..\..\Module\MemBuffer\BinaryTextConvert.h"

// #define _cap_use_const_frame_

#ifdef _cap_use_const_frame_
#define _cap_const_frame_count  6
BYTE g_pCapConstFrameBuffer[_cap_const_frame_count][4096];
long g_nCapConstFrameBuffer[_cap_const_frame_count];
long g_nCapConstFrameBufferIndex = 0;

void st_ConvertFrameTextToBinary(const CString &strText, BYTE *pBuffer, long &nLen)
{
	CBinaryTextConvert oConvert;
	oConvert.SetText(strText);
	oConvert.ConvertTextToBinary(FALSE);
	BYTE *pHex = NULL;
	oConvert.GetBinaryRef(&pHex, nLen);

	memcpy(pBuffer, pHex, nLen);
}

#endif



CEthernetCapThread::CEthernetCapThread(void)
{
	m_adhandle = NULL;
//	SetCaptureLoopMode();
 	SetCaptureNextMode();
// 	m_packet_filter = NULL;
	m_bRestartWinCap = FALSE;
	m_nEthernetCapError = 0;

#ifdef _cap_use_const_frame_
	CString strFrameText;// = _T("010ccd040001010ccd04010188ba400100510000000080470002002c0201000104b00000006e00000017001700170000001700170017c7c77fc4b8ba0017001700000000047850010015020100030000000000000002a300929c7804795001");
// 	switch (nSel)
// 	{
// 	case 0://"9-1"
	strFrameText = _T("010ccd040901010ccd04091188ba4001003a0000000080300001002c0201000104b00000006e01f4fc113969caca028aff94fe260017001700170000000000000000000008195001");
	st_ConvertFrameTextToBinary(strFrameText, g_pCapConstFrameBuffer[0], g_nCapConstFrameBuffer[0]);
// 		break;
// 	case 1://"9-1带状态数据集"
// 		m_strFrameText = _T("010ccd040001010ccd04010188ba400100510000000080470002002c0201000104b00000006e00000017001700170000001700170017c7c77fc4b8ba0017001700000000047850010015020100030000000000000002a300929c7804795001");
// 		break;
// 	case 2://"9-2"
	strFrameText = _T("010ccd040002010ccd04010288ba400100dc000000006081d1800101a281cb3081c880065356494430318202000e8304000000018501018781b0000000000000000000083809000000000008380900000000fffe156500000000fffe156500000000fff9b29200000000fff9b2920000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000d17d900000000000d17d900000000fffcf30700000000fffcf30700000000fff5f50500000000fff5f505000000000000000000000000000000000000000000000000000000000000000000000000");
	st_ConvertFrameTextToBinary(strFrameText, g_pCapConstFrameBuffer[1], g_nCapConstFrameBuffer[1]);
// 		break;
// 	case 3://"60044-8"
// 		m_strFrameText = _T("0564003e02fe000304b00000006e000002662a8d00000000000000000000000000008059cacb3aa9452a000000000000000000000000254f00000000000000000000000000000000ffff");
// 		break;
// 	case 4://GOOSE
	strFrameText = _T("010ccd010011010ccd01011188b81001006900000000615f800c676f636252656630314f5554810400004e20820b44617453657430314f5554830c474f4f5345494430314f55548408000000c03793de508504000000018604000000108701008804000000018901008a0103ab09830100830100830100");
	st_ConvertFrameTextToBinary(strFrameText, g_pCapConstFrameBuffer[2], g_nCapConstFrameBuffer[2]);
// 		break;
// 	default:
// 		m_strFrameText = _T("010ccd040002010ccd04010288ba400100dc000000006081d1800101a281cb3081c880065356494430318202000e8304000000018501018781b0000000000000000000083809000000000008380900000000fffe156500000000fffe156500000000fff9b29200000000fff9b2920000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000d17d900000000000d17d900000000fffcf30700000000fffcf30700000000fff5f50500000000fff5f505000000000000000000000000000000000000000000000000000000000000000000000000");
// 		break;
// 	}

	strFrameText = _T("010ccd040002010ccd04010388ba400200dc000000006081d1800101a281cb3081c880065356494430318202000e8304000000018501018781b0000000000000000000083809000000000008380900000000fffe156500000000fffe156500000000fff9b29200000000fff9b2920000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000d17d900000000000d17d900000000fffcf30700000000fffcf30700000000fff5f50500000000fff5f505000000000000000000000000000000000000000000000000000000000000000000000000");
	st_ConvertFrameTextToBinary(strFrameText, g_pCapConstFrameBuffer[3], g_nCapConstFrameBuffer[3]);

	strFrameText = _T("010ccd050001010ccd05010188ba400100510000000080470002002c0201000104b00000006e00000017001700170000001700170017c7c77fc4b8ba0017001700000000047850010015020100030000000000000002a300929c7804795001");
	st_ConvertFrameTextToBinary(strFrameText, g_pCapConstFrameBuffer[4], g_nCapConstFrameBuffer[4]);

	strFrameText = _T("010ccd010170010ccd01011188b80170012d0000000061820121801f49423232305f4d4c5f41525049542f4c4c4e3024474f245075625f4f505354810400002710821d49423232305f4d4c5f41525049542f4c4c4e3024474f2464734f5053548315525049542f4c4c4e3024474f245075625f4f5053548408000003f79532615085040000000b8604000000358701008804000000018901008a0124ab819c830100830101830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100830100840206409108000003f795326150840206809108000003f795326150840206009108000003f795326150840206009108000003f795326150840206009108000003f795326150840206009108000003f795326150");
	st_ConvertFrameTextToBinary(strFrameText, g_pCapConstFrameBuffer[5], g_nCapConstFrameBuffer[5]);

#endif
}

CEthernetCapThread::~CEthernetCapThread(void)
{
	
}

void CEthernetCapThread::SetCapConfig(PETHER_CAP_CONFIG pConfig, DWORD dwMask)
{
	if( (CAPCFGMASK_USESRCMAC & dwMask) == CAPCFGMASK_USESRCMAC)
	{
		m_oEtherCapConfig.nUseSrcMac = pConfig->nUseSrcMac;
	}

	if( (CAPCFGMASK_SRCMAC & dwMask) == CAPCFGMASK_SRCMAC)
	{
		memcpy(m_oEtherCapConfig.byteSrcMac, pConfig->byteSrcMac, 6);
	}	

	if( (CAPCFGMASK_USEDESTMAC & dwMask) == CAPCFGMASK_USEDESTMAC)
	{
		m_oEtherCapConfig.nUseDestMac = pConfig->nUseDestMac;
	}

	if( (CAPCFGMASK_DESTMAC & dwMask) == CAPCFGMASK_DESTMAC)
	{
		memcpy(m_oEtherCapConfig.byteDestMac, pConfig->byteDestMac, 6);
	}

	if( (CAPCFGMASK_CAPSMV & dwMask) == CAPCFGMASK_CAPSMV)
	{
		m_oEtherCapConfig.nCapSmv = pConfig->nCapSmv;
	}

	if( (CAPCFGMASK_CAPGOOSE & dwMask) == CAPCFGMASK_CAPGOOSE)
	{
		m_oEtherCapConfig.nCapGoose = pConfig->nCapGoose;
	}

	if( (CAPCFGMASK_CARDINDEX & dwMask) == CAPCFGMASK_CARDINDEX)
	{
		m_oEtherCapConfig.nNetCardIndex = pConfig->nNetCardIndex;
	}
}

void CEthernetCapThread::SetCaptureLoopMode()
{
	ASSERT (m_pCaptureThread == NULL && m_adhandle == NULL);
	
	m_bLoopMode = TRUE;
}

void CEthernetCapThread::SetCaptureNextMode()
{
	ASSERT (m_pCaptureThread == NULL && m_adhandle == NULL);
	
	m_bLoopMode = FALSE;
}

BOOL CEthernetCapThread::CanRestartNetCap(BOOL bReset)
{
	if (bReset)
	{
		m_nEthernetCapError = 0;
		return FALSE;
	}
	else
	{
		m_nEthernetCapError++;

		if (m_nEthernetCapError > 10)
		{
			m_nEthernetCapError = 0;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
// 	if (m_bLoopMode)
// 	{
// 		m_nEthernetCapError++;
// 
// 		if (m_nEthernetCapError > 20)
// 		{
// 			m_nEthernetCapError = 0;
// 			return TRUE;
// 		}
// 		else
// 		{
// 			return FALSE;
// 		}
// 	}
// 	else
// 	{
// 		return (m_nEthernetCapError > 2000);
// 	}
}

DWORD CEthernetCapThread::CreateCaptureThread()
{
	m_pCaptureThread = AfxBeginThread(CaptureThread,this);
	m_pCaptureThread->m_bAutoDelete = TRUE;

	if (m_bUseParseThread)
	{
		m_pParseThread = AfxBeginThread(ParseThread,this);
		m_pParseThread->m_bAutoDelete = TRUE;
	}

	return 0;
}

void CEthernetCapThread::ExitCapture()
{
	if (m_bLoopMode)
	{
		if (m_adhandle != NULL)
		{
			pcap_breakloop(m_adhandle);
			m_adhandle = NULL;
		}
	}
}

void CEthernetCapThread::packet_handler(u_char *param, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	CEthernetCapThread *pCapNetThread = (CEthernetCapThread*)param;

	if (pCapNetThread->IsCaptureStop())
	{
		return;
	}

	pCapNetThread->packet_handler_r(header, pkt_data);
}

void CEthernetCapThread::packet_handler_r(const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	if (IsCaptureStop())
	{
		return;
	}

	struct ether_header *eth = (ether_header *)pkt_data;

	if (eth->ether_type == EtherType_Priority || eth->ether_type == EtherType_Smv || eth->ether_type == EtherType_Goose)
	{
		//double dTimeSnamp = header->ts.tv_sec + 1E-6 * header->ts.tv_usec;
		CFrameMemBuffer *pCapBuffer = NULL;
		pCapBuffer = m_oCapBufferMngr.AddFrameBuffer(header, pkt_data);
		m_pProtocol->Parse(pCapBuffer, 0);
	}
	else
	{
		return;
	}
}

void CEthernetCapThread::CloseWinCap()
{
	if (m_adhandle != NULL)
	{
		pcap_close(m_adhandle);
// 		delete m_packet_filter;
		m_adhandle  = NULL;
	}

}


long CEthernetCapThread::StartWinPcap()
{
	int i=0;
	pcap_t *adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;

	struct bpf_program fcode;
	CString strMsg;

	// 跳至选择的网络设备
	long nNetCardIndex = GetNetCardIndex();

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("启动网卡%d监视......"), nNetCardIndex+1);

	CStNetCardInforList *pNetCardList = CStNetCardInforList::Create();
	CStNetCardInfor *pNetCard = pNetCardList->GetAtIndex(nNetCardIndex);

	if (pNetCard == NULL)
	{
		m_pCaptureThread = NULL;
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("不能打开网络适配器,请在网卡设置中进行设置"), m_strName);
		CStNetCardInforList::Release();
		return 0;
	}

	m_strName.Format(_T("%s(%s)"), CString(pNetCard->m_strInfor), CString(pNetCard->m_strIP));
	m_strID = pNetCard->m_strID;

	adhandle = pcap_open(pNetCard->m_strID,					//设备名
		65536,							//要捕捉的数据包的部分 
		PCAP_OPENFLAG_PROMISCUOUS,		//混杂模式
		1000,								//读取超时时间(ms)
		NULL,							//远程机器验证
		errbuf);	

	//if((adhandle= pcap_open_live(d->name, 65536, 1 , 10, errbuf)) == NULL)
	if (adhandle == NULL)
	{
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("不能打开网络适配器,请在网卡设置中进行设置"));
		CStNetCardInforList::Release();
		return 0;  
	}

	// 检查链路层
	if(pcap_datalink(adhandle) != DLT_EN10MB)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("该程序仅支持以太网设备"));
		CStNetCardInforList::Release();
		return 0;
	}

	// 设置掩码
	netmask=0xffffff; 

	CString strFilter;
	GetFilterString(strFilter);
	CString_to_char(strFilter, m_packet_filter);

	// 编译搜索过滤字符串
	if (pcap_compile(adhandle, &fcode, m_packet_filter, 0, netmask) <0 )
	{
		CLogPrint::LogString(LOGLEVEL_ERROR,  _T("编译过滤字符串失败"));
// 		pcap_freealldevs(alldevs);
// 		delete m_packet_filter;
// 		m_packet_filter = NULL;
		CStNetCardInforList::Release();

		return 0;
	}

	// 设置过滤器
	if (pcap_setfilter(adhandle, &fcode)<0)
	{
		CLogPrint::LogString(LOGLEVEL_ERROR, _T("设置过滤器失败") );
// 		pcap_freealldevs(alldevs);
// 		delete m_packet_filter;
// 		m_packet_filter = NULL;
		CStNetCardInforList::Release();

		return 0;
	}

// 	CString strText;
// 	strText.Format(_T("------开始监听设备 { %s }------"), CString(d->description));
	CLogPrint::LogString(LOGLEVEL_TRACE, _T("------开始监听设备------"));

	// 释放设备列表
	m_adhandle = adhandle;
	CStNetCardInforList::Release();
	return 1;
}


UINT CEthernetCapThread::CaptureThread(LPVOID pParam)
{
	CEthernetCapThread* pThis = (CEthernetCapThread*)pParam;

#ifdef _cap_use_const_frame_
	struct pcap_pkthdr oTestHeader;
	oTestHeader.caplen = g_nCapConstFrameBuffer[0];
	oTestHeader.len = g_nCapConstFrameBuffer[0];
	oTestHeader.ts.tv_sec = 42*365*24*60*60;//2012年
	oTestHeader.ts.tv_usec = 0;
#endif

	if (pThis->StartWinPcap() == 0)
	{
// 		pThis->m_packet_filter = NULL;
		pThis->m_adhandle  = NULL;

		pThis->m_pCaptureThread = NULL;
		CLogPrint::LogString(LOGLEVEL_TRACE, _T("启动监视监视线程失败"));
		return 0;
	}

	if (pThis->m_bLoopMode)
	{
		pcap_loop(pThis->m_adhandle, 0, packet_handler, (u_char*)pThis);	
	}
	else
	{
// 		CTickCount32 oTick;
		long nLenCap = 0;
		struct pcap_pkthdr *header;
		const u_char *data;

		//adhandle后不调用pcap_loop，而用下面的方法：
 		while(TRUE)
 		{
			if (pThis->m_bExitCapture)
			{
				break;
			}

 			long res = 0;

#ifdef _cap_use_const_frame_
			oTestHeader.ts.tv_usec += 250;
			if (oTestHeader.ts.tv_usec >= 1000000)
			{
				oTestHeader.ts.tv_usec = 0;
				oTestHeader.ts.tv_sec++;
			}
	
			res = g_nCapConstFrameBuffer[g_nCapConstFrameBufferIndex];
			oTestHeader.caplen = g_nCapConstFrameBuffer[g_nCapConstFrameBufferIndex];
			oTestHeader.len = g_nCapConstFrameBuffer[g_nCapConstFrameBufferIndex];
			header = &oTestHeader;
			data = g_pCapConstFrameBuffer[g_nCapConstFrameBufferIndex];
			g_nCapConstFrameBufferIndex++;

			if (g_nCapConstFrameBufferIndex >= _cap_const_frame_count)
			{
				g_nCapConstFrameBufferIndex = 0;
			}
			Sleep(10);

#else
			res = pcap_next_ex(pThis->m_adhandle,&header,&data);
#endif
	 	
 			if(res <= 0)
 			{
 				Sleep(1);
 				//continue;
 			}
 			else
 			{
				nLenCap += header->caplen;
				pThis->packet_handler_r(header, data);
 			}

// 			if (oTick.GetTickCountLong(FALSE) > 2000)
// 			{
// 				CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("接受到%d字节"), nLenCap);
// 				nLenCap = 0;
// 				oTick.GetTickCountLong(TRUE);
// 			}
 		}
	}

	if (!pThis->m_bLoopMode)
	{
		pcap_close(pThis->m_adhandle);
	}

// 	delete pThis->m_packet_filter;
// 	pThis->m_packet_filter = NULL;
	pThis->m_adhandle  = NULL;

	//pThis->FreeAllCapDatas();
	pThis->m_pCaptureThread = NULL;
	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("监视线程（%s）结束"), pThis->m_strName);

	return 0;
}


UINT CEthernetCapThread::ParseThread(LPVOID pParam)
{
	CEthernetCapThread *pThis = (CEthernetCapThread*)pParam;

//	pThis->Parse();
	pThis->m_pParseThread = NULL;

	return 0;
}

void CEthernetCapThread::GetFilterString(CString &strFilter)
{
	strFilter = _T("");// _T("(ether proto 0xBA88) or (ether proto 0xB888)");
}


void CEthernetCapThread::InitFilters()
{
	
}
