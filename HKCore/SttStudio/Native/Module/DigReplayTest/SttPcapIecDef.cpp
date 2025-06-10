#include "SttPcapIecDef.h"
/////////////////////////////////////////////////////////////////_pcap_iec_pkg_/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL _pcap_iec_pkg_::UpdatePkgSmpCount()
{
	if (pXSmMemBuffer == NULL)
	{
		return FALSE;
	}

	m_nSmpCountValue = pXSmMemBuffer->GetSmpCount();
	return TRUE;
}

/////////////////////////////////////////////////////////////////_pcap_iec_fiber_port_/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void _pcap_iec_fiber_port_::SortAllPkgs()
{
	PCAP_IEC_PKG *pIecPkg = NULL;
	long nCurrMaxNum = m_nCurrPkgIndex;

	//冒泡排序
	for (int nPkgIndex = 1;nPkgIndex<m_nCurrPkgIndex;nPkgIndex++)
	{
		nCurrMaxNum = m_nCurrPkgIndex - nPkgIndex + 1;

		for (int nPkgIndex2 = 1;nPkgIndex2<nCurrMaxNum;nPkgIndex2++)
		{
			if (m_pPkgs[nPkgIndex2-1]->pXSmMemBuffer->m_oCapBufferItem.Time>m_pPkgs[nPkgIndex2]->pXSmMemBuffer->m_oCapBufferItem.Time)
			{
				pIecPkg = m_pPkgs[nPkgIndex2-1];
				m_pPkgs[nPkgIndex2-1] = m_pPkgs[nPkgIndex2];
				m_pPkgs[nPkgIndex2] = pIecPkg;
			}
		}
	}
}

/////////////////////////////////////////////////////////////////_pcap_iec_fibers_/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void _pcap_iec_fibers_::SortAllPkgs()
{
	for (int nIndex = 0;nIndex<m_nFiberCount;nIndex++)
	{
		m_pFibers[nIndex].SortAllPkgs();
	}
}

BOOL _pcap_iec_fibers_::AttachIecPkg(P_PCAP_IEC_PKG pIecPkg,long nFiberIndex)
{
	if (pIecPkg == NULL)
	{
		return FALSE;
	}

	for (int nIndex = 0;nIndex<m_nFiberCount;nIndex++)
	{
		if (m_pFibers[nIndex].m_nFiberIndex == nFiberIndex)
		{
			return m_pFibers[nIndex].AttachIecPkg(pIecPkg);
		}
	}

	return FALSE;
}


/////////////////////////////////////////////////////////////////_pcap_iec_ctrl_/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void _pcap_iec_ctrl_::init()
{
	m_nPkgCount = 0;
	m_nCurrPkgIndex = 0;
	m_pPkgs = NULL;
	m_wAppID = 0;
	m_wSelect = 1;
	m_nChNum = 0;
	m_nAsduNum = 0;
	m_pPcapChDatas = NULL;
	m_dwTmtCtrl_Attached = NULL;
	m_dwIecCfgData = NULL;
}

void _pcap_iec_ctrl_::FreePkgs()
{
	if (m_pPkgs != NULL)
	{
		delete []m_pPkgs;
		m_pPkgs = NULL;
	}

	m_nPkgCount = 0;
	m_nCurrPkgIndex = 0;
	m_wAppID = 0;
	m_wSelect = 1;
	m_nChNum = 0;
	m_nAsduNum = 0;
	m_pPcapChDatas = NULL;
	m_dwTmtCtrl_Attached = NULL;
	m_dwIecCfgData = NULL;
	FreeChDatas();
}

void _pcap_iec_ctrl_::FreeChDatas()
{
	if (m_pPcapChDatas != NULL)
	{
		delete []m_pPcapChDatas;
		m_pPcapChDatas = NULL;
	}
}

void _pcap_iec_ctrl_::InitCtrl(unsigned short wAppID,long nCount)
{
	FreePkgs();
	m_nPkgCount = nCount;
	m_wAppID = wAppID;

	if (nCount>0)
	{
		m_pPkgs = new PCAP_IEC_PKG[nCount];

		for (int nIndex = 0;nIndex<nCount;nIndex++)
		{
			m_pPkgs[nIndex].dwParent = (DWORD)this;
		}
	} 
}

BOOL _pcap_iec_ctrl_::AttachXSmMemBuffer(CFrameMemBuffer *pCXSmMemBuffer, BOOL bIsSmvCtrl/* = FALSE*/)
{
	if (pCXSmMemBuffer == NULL)
	{
		return FALSE;
	}

	if (m_nCurrPkgIndex>= m_nPkgCount)
	{
		return FALSE;
	}

	m_pPkgs[m_nCurrPkgIndex].pXSmMemBuffer = pCXSmMemBuffer;
	pCXSmMemBuffer->m_dwReserved = (DWORD)&m_pPkgs[m_nCurrPkgIndex];//将当前报文结构体相互关联

	if (m_nCurrPkgIndex > 0)
	{
		m_pPkgs[m_nCurrPkgIndex].nTimeGap = 
			GetTimeGap_EpcapBufferItem(&m_pPkgs[m_nCurrPkgIndex].pXSmMemBuffer->m_oCapBufferItem , &m_pPkgs[m_nCurrPkgIndex - 1].pXSmMemBuffer->m_oCapBufferItem);
	}
	else
	{
		m_pPkgs[m_nCurrPkgIndex].nTimeGap = 0;
		FreeChDatas();
		m_nChNum = pCXSmMemBuffer->GetPkgChNum();

		if (bIsSmvCtrl && (m_nChNum>0))
		{
			m_nAsduNum = pCXSmMemBuffer->GetAsduNum();
			m_pPcapChDatas = new CComplexMemBuffer_Float[m_nChNum];

			for (int nIndex = 0;nIndex<m_nChNum;nIndex++)
			{
				m_pPcapChDatas[nIndex].SetBufferLength(m_nPkgCount*m_nAsduNum);
			}
		}
	}

	if (bIsSmvCtrl)
	{
		m_pPkgs[m_nCurrPkgIndex].UpdatePkgSmpCount();//更新报文的采样计数器
	}

	if (bIsSmvCtrl && (m_nChNum>0))//将当前通道数据设置到通道数据内
	{
		SetPcapChDatas(pCXSmMemBuffer,m_nCurrPkgIndex);
	}

	m_nCurrPkgIndex++;
	return TRUE;
}

void _pcap_iec_ctrl_::SetPcapChDatas(CFrameMemBuffer *pCXSmMemBuffer,long nCurrPkgIndex)
{
	if ((pCXSmMemBuffer == NULL)||(m_pPcapChDatas == NULL))
	{
		return;
	}

	BYTE *pBuffer = pCXSmMemBuffer->GetBuffer();
	long nBufferLength = pCXSmMemBuffer->GetBufferLength();
	WORD wValue = 0,wValue2 = 0;
	long dwValue = 0;
	float* pfChData = NULL;
	long nCurrDataIndex = nCurrPkgIndex*m_nAsduNum;
	

	//跳过前面MAC等内容,开始查找时间同步信号
	for (int nIndex = 40; nIndex<nBufferLength;)
	{
		wValue = Ep_BufferGetWord(&pBuffer[nIndex]);//找到时间同步信号
		wValue2 = Ep_BufferGetWord(&pBuffer[nIndex + 3]);//紧跟着采样通道数量
		
		if ((wValue == 0x8501)&&(wValue2 == 0x8781))
		{
			for (int nChIndex = 0;nChIndex <m_nChNum;nChIndex++)
			{
				dwValue = Ep_BufferGetDWord(&pBuffer[nIndex + 6 + nChIndex*8]);
				pfChData = m_pPcapChDatas[nChIndex].GetBuffer_float();

// 				if (dwValue<0)
// 				{
// 					CLogPrint::LogFormatString(XLOGLEVEL_INFOR,_T("%ld"),dwValue);
// 				}
				//pfChData[nCurrDataIndex] = dwValue;
				m_pPcapChDatas[nChIndex].AddValue(dwValue);
			}

			nCurrDataIndex++;
			nIndex += (m_nChNum*8);
		}
		else
		{
			nIndex++;
		}
	}
}

BOOL _pcap_iec_ctrl_::HasPcapSendDatas()
{
	for (int nIndex = 0;nIndex<m_nPkgCount;nIndex++)
	{
		if (m_pPkgs[nIndex].HasPcapSendData())
		{
			return TRUE;
		}
	}

	return FALSE;
}

long _pcap_iec_ctrl_::FindMemBufer(CFrameMemBuffer *pCXSmMemBuffer)
{
	int nCurrIndex = -1;

	for( int nIndex = 0;nIndex < m_nPkgCount; nIndex++  )
	{
		if (m_pPkgs[nIndex].pXSmMemBuffer == pCXSmMemBuffer)
		{
			nCurrIndex = nIndex;
			
			return nCurrIndex;
			
		}
	}

	return nCurrIndex;

}

/////////////////////////////////////////////////////////////////_pcap_iec_ctrls_/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

P_PCAP_IEC_CTRL _pcap_iec_ctrls_::FindPcapIecCtrl(long nAppID)
{
	P_PCAP_IEC_CTRL pPcapIecCtrl = NULL;

	for (int nIndex = 0;nIndex<m_nCtrlCount;nIndex++)
	{
		if (m_pCtrls[nIndex].m_wAppID == nAppID)
		{
			pPcapIecCtrl = &m_pCtrls[nIndex];
			break;
		}
	}

	return pPcapIecCtrl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
