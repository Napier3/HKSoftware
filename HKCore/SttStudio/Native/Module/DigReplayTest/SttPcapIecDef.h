#pragma once
#include "../../../Module/SmartCap/61850Cap/ProtocolBase/FrameMemBuffer.h"
#include "../../../Module/Record/RtMemBuffer/MemBuffer_Float.h"
//从PCAP文件中提取的报文，存放于一个缓存中，可以为CBufferBase，
//报文结构体
typedef struct _pcap_iec_pkg_
{
	CFrameMemBuffer *pXSmMemBuffer;

	//IEC关键信息
	unsigned short wSelect;  
	long nTimeGap;    //us相对上一帧报文的时间间隔
	DWORD dwParent;//报文对应的父节点控制块指针
	__int64 m_n64DataTime_Cal;//按非报文时间回放时,自动计算出的报文时间值
	long m_nSmpCountValue;

	_pcap_iec_pkg_()
	{
		init();
	}
	virtual ~_pcap_iec_pkg_()
	{
	}

	void init()
	{
		wSelect = 1;
		nTimeGap = 0;
		dwParent = NULL;
		m_n64DataTime_Cal = 0;
		m_nSmpCountValue = -1;
		pXSmMemBuffer =0;
	}

	BOOL HasPcapSendData()
	{
		if (wSelect == 0)
		{
			return FALSE;
		}

		if (pXSmMemBuffer == NULL)
		{
			return FALSE;
		}

		return TRUE;
	}

	BOOL UpdatePkgSmpCount();//更新报文内的采样计数器值
}PCAP_IEC_PKG, *P_PCAP_IEC_PKG;

//用于存储单个光口发送的全部报文数据
typedef struct _pcap_iec_fiber_port_
{
	long m_nPkgCount;
	long m_nCurrPkgIndex;
	long m_nFiberIndex;//光口号,从0开始编号
	P_PCAP_IEC_PKG *m_pPkgs;   //根据报文总数动态分配的结构体对象

	_pcap_iec_fiber_port_()
	{
		init();
	}

	virtual ~_pcap_iec_fiber_port_()
	{
		FreePkgs();
	}

	void init()
	{
		m_nPkgCount = 0;
		m_nCurrPkgIndex = 0;
		m_nFiberIndex = 0;
		m_pPkgs = NULL;
	}

	void FreePkgs()
	{
		if (m_pPkgs != NULL)
		{
			delete []m_pPkgs;
			m_pPkgs = NULL;
		}

		m_nPkgCount = 0;
		m_nCurrPkgIndex = 0;
		m_nFiberIndex = 0;
	}

	void InitPkgs(long nFiberIndex,long nCount)
	{
		FreePkgs();
		m_nFiberIndex = nFiberIndex;
		m_nPkgCount = nCount;

		if (nCount>0)
		{
			m_pPkgs = new P_PCAP_IEC_PKG[nCount];
		} 
	}

	BOOL AttachIecPkg(P_PCAP_IEC_PKG pIecPkg)
	{
		if (pIecPkg == NULL)
		{
			return FALSE;
		}

		if (m_nCurrPkgIndex>= m_nPkgCount)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前关联的光口(%ld),报文帧号大于总帧数(%ld)."),m_nFiberIndex,m_nPkgCount);
			return FALSE;
		}

		m_pPkgs[m_nCurrPkgIndex] = pIecPkg;
		pIecPkg->m_n64DataTime_Cal = pIecPkg->pXSmMemBuffer->m_oCapBufferItem.Time;
		m_nCurrPkgIndex++;
		return TRUE;
	}

	void SortAllPkgs();//对所有报文进行排序

}PCAP_IEC_FIBER_PORT, *P_PCAP_IEC_FIBER_PORT;

typedef struct _pcap_iec_fibers_
{
	long m_nFiberCount;
	P_PCAP_IEC_FIBER_PORT m_pFibers;   //根据报文总数动态分配的结构体对象

	_pcap_iec_fibers_()
	{
		init();
	}

	virtual ~_pcap_iec_fibers_()
	{
		FreeFibers();
	}

	void init()
	{
		m_nFiberCount = 0;
		m_pFibers = NULL;
	}

	void FreeFibers()
	{
		if (m_pFibers != NULL)
		{
			for (int nIndex = 0;nIndex<m_nFiberCount;nIndex++)
			{
				m_pFibers[nIndex].FreePkgs();
			}

			delete []m_pFibers;
			m_pFibers = NULL;
		}

		m_nFiberCount = 0;
	}

	void InitFibers(long nFiberCount)
	{
		FreeFibers();
		m_nFiberCount = nFiberCount;

		if (nFiberCount>0)
		{
			m_pFibers = new PCAP_IEC_FIBER_PORT[nFiberCount];
		}
	}

	BOOL AttachIecPkg(P_PCAP_IEC_PKG pIecPkg,long nFiberIndex);
	void SortAllPkgs();//对所有报文进行排序
}PCAP_IEC_FIBERS, *P_PCAP_IEC_FIBERS;

typedef struct _pcap_iec_ctrl_
{
	long m_nPkgCount;
	long m_nCurrPkgIndex;
	P_PCAP_IEC_PKG m_pPkgs;   //根据报文总数动态分配的结构体对象

	//IEC关键信息
	unsigned short m_wAppID;
	unsigned short m_wSelect;
	long m_nChNum;//通道数量
	long m_nAsduNum;
	CComplexMemBuffer_Float *m_pPcapChDatas;
	DWORD m_dwTmtCtrl_Attached;//关联的tmt控制块指针
	DWORD m_dwIecCfgData;//关联的IEC配置信息

	_pcap_iec_ctrl_()
	{
		init();
	}

	virtual ~_pcap_iec_ctrl_()
	{
		FreePkgs();
	}

	void init();
	void FreePkgs();
	void FreeChDatas();
	void InitCtrl(unsigned short wAppID,long nCount);
	BOOL AttachXSmMemBuffer(CFrameMemBuffer *pCXSmMemBuffer, BOOL bIsSmvCtrl/* = FALSE*/);
	
	long FindMemBufer(CFrameMemBuffer *pCXSmMemBuffer);//查找m_pPkgs中对应的pCXSmMemBuffer的Index

	void SetPcapChDatas(CFrameMemBuffer *pCXSmMemBuffer,long nCurrPkgIndex);//设置当前通道数据值
	BOOL HasPcapSendDatas();
}PCAP_IEC_CTRL, *P_PCAP_IEC_CTRL;


typedef struct _pcap_iec_ctrls_
{
	long m_nCtrlCount;
	P_PCAP_IEC_CTRL m_pCtrls;   //根据报文总数动态分配的结构体对象

	_pcap_iec_ctrls_()
	{
		init();
	}

	virtual ~_pcap_iec_ctrls_()
	{
		FreeCtrls();
	}

	void init()
	{
		m_nCtrlCount = 0;
		m_pCtrls = NULL;
	}

	void FreeCtrls()
	{
		if (m_pCtrls != NULL)
		{
			for (int nIndex = 0;nIndex<m_nCtrlCount;nIndex++)
			{
				m_pCtrls[nIndex].FreePkgs();
			}

			delete []m_pCtrls;
			m_pCtrls = NULL;
		}

		m_nCtrlCount = 0;
	}

	void InitCtrls(long nCtrlCount)
	{
		FreeCtrls();
		m_nCtrlCount = nCtrlCount;

		if (nCtrlCount>0)
		{
			m_pCtrls = new PCAP_IEC_CTRL[nCtrlCount];
		}
	}

	BOOL AttachXSmMemBuffer(CFrameMemBuffer *pCXSmMemBuffer,unsigned short uAppID, BOOL bIsSmvCtrl /*= FALSE*/)//参数3为是否设置通道数据,SV数据需要增加通道数据
	{
		if (pCXSmMemBuffer == NULL)
		{
			return FALSE;
		}

		for (int nIndex = 0;nIndex<m_nCtrlCount;nIndex++)
		{
			if (m_pCtrls[nIndex].m_wAppID == uAppID)
			{
				return m_pCtrls[nIndex].AttachXSmMemBuffer(pCXSmMemBuffer,bIsSmvCtrl);
			}
		}

		return FALSE;
	}

	BOOL HasPcapSendDatas()
	{
		for (int nIndex = 0;nIndex<m_nCtrlCount;nIndex++)
		{
			if (m_pCtrls[nIndex].HasPcapSendDatas())
			{
				return TRUE;
			}
		}

		return FALSE;
	}

	P_PCAP_IEC_CTRL FindPcapIecCtrl(long nAppID);
}PCAP_IEC_CTRLS, *P_PCAP_IEC_CTRLS;
