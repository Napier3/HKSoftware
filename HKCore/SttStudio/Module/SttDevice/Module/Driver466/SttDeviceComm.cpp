#include "SttDeviceComm.h"
#include "../../../SttTest/Common/tmt_adjust_sys_para_module_def.h"
#include "../../../SttTest/Common/tmt_adjust_sys_para_trans.h"
#include "../../../SttTest/Common/SttHarmTest.h"
#include "../../../SttTest/Common/SttManuTest.h"
#include "../../../Engine/SttTestServerBase.h"
#include "../Week/SttDevice_Week.h"
#include "math.h"
//CP1258

CSttDeviceComm::CSttDeviceComm()
{

}

CSttDeviceComm::~CSttDeviceComm()
{
	delete m_pDrv_StateItem;
	delete[] m_pCurBins;
	delete[] m_pStateGoosePub;
	delete[] m_pStateFt3Pub;
}

void CSttDeviceComm::InitBuff()
{
	m_nDrvResItemLen = sizeof(Drv_ResultItem);
	m_bRdDegRtData = FALSE;
	m_nSmvAbnDelayOffset = 0;
	m_pDrv_StateItem = new Drv_StateItem;
	m_pCurBins = new tmt_BinaryIns[g_nStateCount];
	m_pStateGoosePub = new tmt_GoosePubs[g_nStateCount];
	m_pStateFt3Pub = new tmt_Ft3Pubs[g_nStateCount];
}

void CSttDeviceComm::GetBoardInfo(BOOL bHasAdjFile)
{
	if(!bHasAdjFile)
	{
		g_theDeviceSystemParameter->m_nModuleCount = 0;
		g_theDeviceSystemParameter->m_nModuleCount_U = 0;
		g_theDeviceSystemParameter->m_nModuleCount_I = 0;
		g_theDeviceSystemParameter->m_nModuleCount_D = 0;
		g_theDeviceSystemParameter->m_nModuleCount_FT3 = 0;
		g_theDeviceSystemParameter->m_nModuleCount_S = 0;
		g_theDeviceSystemParameter->m_nModuleCount_WEEK = 0;
		g_theDeviceSystemParameter->m_nModuleCount_UI = 0;
		g_theDeviceSystemParameter->m_nModuleCount_ADMU = 0;
		return;
	}

	GetModulesFPGAInfo();
	long nModuleType = 0;//0：其他类型，1-电压，2-电流

	for(int i = 1; i < 13; i++)
	{
		switch(m_oBoardinfo.version[i] >> 24)
		{
			case 0x55:
				nModuleType = 1;
				break;

			case 0xaa:
			case 0xa5:
				nModuleType = 2;
				break;

			default:
				nModuleType = 0;
		}

		if(nModuleType == 0)
		{
			continue;
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount; nIndex++)
		{
			STT_MODULE &oModule = g_theDeviceSystemParameter->m_oModules[nIndex];

			if(i == oModule.m_oModuleAttr.m_nModuleIndex)
			{
				if(nModuleType == 1)
				{
					if(oModule.m_oModuleAttr.m_nModuleType != STT_MODULE_TYPE_VOLT)
					{
						oModule.m_oModuleAttr.m_nErr = 1;//模块类型不匹配
					}
				}
				else if(nModuleType == 2)
				{
					if(oModule.m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_CURRENT
							|| oModule.m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
					{
					}
					else
					{
						oModule.m_oModuleAttr.m_nErr = 1;//模块类型不匹配
					}
				}

				break;
			}
		}
	}

	int nDeviceStatusCnt = 0;

	for(long k = 0; k < g_theDeviceSystemParameter->m_nModuleCount; k++)
	{
		STT_MODULE &oModule = g_theDeviceSystemParameter->m_oModules[k];
		nModuleType = oModule.m_oModuleAttr.m_nModuleType;

		if(nModuleType == STT_MODULE_TYPE_CURRENT
				|| nModuleType == STT_MODULE_TYPE_VOLT
				|| nModuleType == STT_MODULE_TYPE_VOLT_CURRENT
				|| nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M
				|| nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M
				|| nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M)
		{
			//模拟量输出监视、数字光功率监视
		}
		else
		{
			continue;
		}

		if(oModule.m_oModuleAttr.m_nUsed == 0)
		{
			//针对PNS330扩展项目，系数文件内配置的模块不启用的话，m_nUsed = 0
			continue;
		}

		if(nModuleType == STT_MODULE_TYPE_CURRENT || nModuleType == STT_MODULE_TYPE_VOLT)
		{
			g_theSttDeviceStatus->m_oModule[nDeviceStatusCnt].m_nChanNum = oModule.m_oModuleAttr.m_nChannelNum;

			for(long nChan = 0; nChan < oModule.m_oModuleAttr.m_nChannelNum; nChan++)
			{
				strcpy(g_theSttDeviceStatus->m_oModule[nDeviceStatusCnt].m_oChannel[nChan].m_pszChId,
					   oModule.m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChan].m_pszChId);
			}
		}

		g_theSttDeviceStatus->m_oModule[nDeviceStatusCnt].m_nModulePos = oModule.m_oModuleAttr.m_nModuleIndex;
		g_theSttDeviceStatus->m_oModule[nDeviceStatusCnt].m_nModuleType = oModule.m_oModuleAttr.m_nModuleType;
		g_theSttDeviceStatus->m_oModule[nDeviceStatusCnt].m_nDisable = oModule.m_oModuleAttr.m_nErr;
		g_theSttDeviceStatus->m_oModule[nDeviceStatusCnt].m_nNeedMonitor = 0;

		if(nModuleType == STT_MODULE_TYPE_VOLT || nModuleType == STT_MODULE_TYPE_CURRENT
				|| nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
		{
			g_theSttDeviceStatus->m_oModule[nDeviceStatusCnt].m_nNeedMonitor = 1;    //仅模拟电压电流FPGA有监视功能
		}

		nDeviceStatusCnt++;
	}

	g_theSttDeviceStatus->m_nAnalogCount = nDeviceStatusCnt;
}

void CSttDeviceComm::setBCodeTime(unsigned int nYear, unsigned int nMonth, unsigned int nday,
								  unsigned int nhour, unsigned int nmin, unsigned int nsecond)
{
	unsigned int nY  = 0;
	nY = (nYear / 10 % 10) << 4 | (nYear % 10);
	unsigned int nMd = 0;
	unsigned int n2m = 28;

	if(nYear % 4 == 0)
	{
		n2m = 29;
	}

	switch(nMonth)
	{
		case 1:
			nMd = 0;
			break;

		case 2:
			nMd = 31;
			break;

		case 3:
			nMd = 31 + n2m;
			break;

		case 4:
			nMd = 31 + n2m + 31;
			break;

		case 5:
			nMd = 31 + n2m + 31 + 30;
			break;

		case 6:
			nMd = 31 + n2m + 31 + 30 + 31;
			break;

		case 7:
			nMd = 31 + n2m + 31 + 30 + 31 + 30;
			break;

		case 8:
			nMd = 31 + n2m + 31 + 30 + 31 + 30 + 31;
			break;

		case 9:
			nMd = 31 + n2m + 31 + 30 + 31 + 30 + 31 + 31;
			break;

		case 10:
			nMd = 31 + n2m + 31 + 30 + 31 + 30 + 31 + 31 + 30;
			break;

		case 11:
			nMd = 31 + n2m + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31;
			break;

		case 12:
			nMd = 31 + n2m + 31 + 30 + 31 + 30 + 31 + 31 + 30 + 31 + 30;
			break;

		default:
			break;
	}

	nMd += nday;
	unsigned int nd = 0;
	nd |= (nMd / 100 % 10) << 28 ;
	nd |= (nMd / 10 % 10) << 24 ;
	nd |= (nMd % 10) << 20;
	nd = nd | (nhour / 10 % 10) << 18 ;
	nd = nd | (nhour % 10) << 14;
	nd = nd | (nmin / 10 % 10) << 11;
	nd = nd | (nmin % 10) << 7;
	nd = nd | (nsecond / 10 % 10) << 4 ;
	nd = nd | (nsecond % 10);
	uint data[2] = {0, 0};
	data[0] = nY;
	data[1] = nd;

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x351, 0);
	write(m_nfd, (char *)data, 8);
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetTestStart(int nTestType)
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0xA00, 0); //停DMA
	g_oDrvMutex.unlock();
	CSttDeviceBase::g_pSttDeviceBase->m_nIecPkgFormat = 1;

	for(int nIndex = 0; nIndex < MAX_CURRENT_COUNT; nIndex++)
	{
		CSttDeviceBase::g_pSttDeviceBase->SetCurrAmp_Monitor(nIndex, 0);
	}

	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL)
	{
		pSttTestBase->ReturnRealTimeEvent();
	}

#ifdef _MainBoard_PI_
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x143, 0); //停用模块内系数补偿功能,由于各模块上电顺序不统一,故每次开始实验都发一次该命令
	g_oDrvMutex.unlock();
#endif

	if(CSttDeviceBase::g_pSttDeviceBase->m_nUseIecCfgCRC)
	{
		m_oCIEC61850CfgMngr.SetGooseSub();
		m_oCIEC61850CfgMngr.SetFT3SubMap();
		CSttDeviceBase::g_pSttDeviceBase->SetDMAType(DMA_TYPE_SUB);
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x126, 0);//停DMA缓存
		g_oDrvMutex.unlock();
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[warning] 当前处于报文探测、合并单元、智能终端等模式，不使用IEC配置中的GOOSE订阅、FT3订阅"));
	}

	PreStartTestPro();
	if(g_theSystemConfig->m_nHasAnalog || g_theSystemConfig->m_nHasWeek)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x100, 1);//打开端口继电器
		g_oDrvMutex.unlock();
	}
	Sleep(100);

	switch(nTestType)
	{
		case GradientTest:
		{
			if(CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas.m_nStepCnt > 0)
			{
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0xA00, 1); //开DMA
				ioctl(m_nfd, 0x103, 7);
				g_oDrvMutex.unlock();
			}
			else
			{
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] 递变步数为0,请核对始值终值及递变类型"));
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x103, 0);
				g_oDrvMutex.unlock();
				AfterTestFinishedPro();

				if(pSttTestBase != NULL)
				{
					pSttTestBase->ReturnTestStateEvent_TestFinish(0, 0, FALSE);
				}
			}
		}
		break;

		case ManualTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 1);
			g_oDrvMutex.unlock();
		}
		break;

		case MUTest:
		{
			if(CSttDeviceBase::g_pSttDeviceBase->m_nUseIecCfgCRC)
			{
				m_oCIEC61850CfgMngr.SetRecordIecIn();
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x126, 1);//开DMA缓存
				g_oDrvMutex.unlock();
			}

			CSttDeviceBase::g_pSttDeviceBase->SetDMAType(DMA_TYPE_RECORD);
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 1);
			g_oDrvMutex.unlock();
		}
		break;

		case StateTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 2);//启动状态序列测试
			g_oDrvMutex.unlock();
		}
		break;

		case BinaryStateTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 0x11);//启动状态序列测试
			g_oDrvMutex.unlock();
		}
		break;

		case BinaryStateExTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 0x14);//启动状态序列测试
			g_oDrvMutex.unlock();
		}
		break;

		case BinaryManuTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 0x13);
			g_oDrvMutex.unlock();
		}
		break;

		case AbnoramlTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 9);//启动异常模拟
			g_oDrvMutex.unlock();
		}
		break;

		case ShakeTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 8);//启动振荡测试
			g_oDrvMutex.unlock();
		}
		break;

		case LtReplayTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 0x0d);//启动故障回放
			g_oDrvMutex.unlock();
		}
		break;

		case SystemDefaultOutput:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x136, 1);
			g_oDrvMutex.unlock();
		}
			break;

		case SOE:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x103, 0xA);
			g_oDrvMutex.unlock();
		}
			break;

		case CboperTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 0x0F);
			g_oDrvMutex.unlock();
		}
		break;

		case SynTest:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0xA00, 1); //开DMA
			ioctl(m_nfd, 0x103, 0x0B);//同期测试
			g_oDrvMutex.unlock();
		}
		break;
	}
}

void CSttDeviceComm::SetTestStop(BOOL bIsSysDefaultOutput)
{
	PowerDAMngr *pPowerDAMngr = &CSttDeviceBase::g_pSttDeviceBase->m_oPowerDAMngr;
	pPowerDAMngr->nUse = 0;
	pPowerDAMngr->nTickCnt = 0;
	pPowerDAMngr->nTickTotal = 0;

	if(bIsSysDefaultOutput)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x136, 0);
		g_oDrvMutex.unlock();
	}
	else
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x103, 0);
		g_oDrvMutex.unlock();
		AfterTestFinishedPro();
	}
}

void CSttDeviceComm::tmt_to_drv_record(tmt_RecordTest *pTmt)
{
	char *pszBuf = stt_test_get_drvparas_buff();
	IecRecvCfg *pDrv = (IecRecvCfg *)pszBuf;
	memset(pDrv, 0, sizeof(IecRecvCfg));
	tmt_RecordParas oParas = pTmt->m_oRecordPara;
	pDrv->ncount = oParas.m_nSubNumber;

	if(oParas.m_nSubNumber > 0)
	{
		pDrv->nType = 4;

		for(int index = 0; index < oParas.m_nSubNumber; index++)
		{
			tmt_RecordPara oPara = oParas.m_paras[index];
			pDrv->oIecSub[index].CRC = CalCRC(oPara.appid, oPara.dest_mac, oPara.port.toInt(), oPara.ntype.toInt());
		}
	}
	else
	{
		pDrv->nType = 0;
	}

	SetTestPara(Record, pszBuf);
}

void CSttDeviceComm::SetTestPara(int nTestType, char *pszBuff)
{
	switch(nTestType)
	{
		case IECDataCfg:
		{
			//拆分多次下载，防止驱动接口锁死
			Drv_IECConfig *pIECConfig = (Drv_IECConfig*)pszBuff;
			g_oDrvMutex.lock();
			ioctl(m_nfd,  0x320, pIECConfig->mdCnt);
			g_oDrvMutex.unlock();

			for(int i = 0;i < pIECConfig->mdCnt;i++)
			{
				if(pIECConfig->item[i].smvCount > 0 || pIECConfig->item[i].gsCount > 0)
				{
					g_oDrvMutex.lock();
					ioctl(m_nfd,  0x323, i);
					write(m_nfd, (char*)&pIECConfig->item[i], sizeof(DatConfigItems));
					g_oDrvMutex.unlock();
					Sleep(10);
				}
			}
		}
		break;

		case Ft3DataCfg:
		{
			//拆分多次下载，防止驱动接口锁死
			Drv_IECConfigFt3 *pIECConfigFt3 = (Drv_IECConfigFt3*)pszBuff;
			g_oDrvMutex.lock();
			ioctl(m_nfd,  0x325, pIECConfigFt3->mdCnt);
			g_oDrvMutex.unlock();

			for(int i = 0;i < pIECConfigFt3->mdCnt;i++)
			{
				if(pIECConfigFt3->item[i].ft3Count > 0)
				{
					g_oDrvMutex.lock();
					ioctl(m_nfd,  0x324, i);
					write(m_nfd, (char*)&pIECConfigFt3->item[i], sizeof(DatConfigItemsFt3));
					g_oDrvMutex.unlock();
					Sleep(10);
				}
			}
		}
		break;

		case IECDataCfg_Stable2M:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x319, 0);//2M
			write(m_nfd, pszBuff, sizeof(Drv_IECConfig_2M));
			g_oDrvMutex.unlock();
		}
		break;

		case SvCtrlCfg:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x321, 1);//1：SMV发送配置
			write(m_nfd, pszBuff, sizeof(SendConfSV));
			g_oDrvMutex.unlock();
		}
		break;

		case GseCtrlCfg:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x321, 2);//2：GOOSE发送配置
			write(m_nfd, pszBuff, sizeof(SendConfGSE));
			g_oDrvMutex.unlock();
		}
		break;

		case Ft3CtrlCfg:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x321, 3);//3：FT3发送配置
			write(m_nfd, pszBuff, sizeof(SendConfFT3));
			g_oDrvMutex.unlock();
		}
		break;

		case ClearSvCfg:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x321, 4);//4：清除SMV发送配置
			g_oDrvMutex.unlock();
		}
		break;

		case FiberCtrlCfg:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x321, 0);//flag = 0:光口配置
			write(m_nfd, pszBuff, sizeof(FiberConf));
			g_oDrvMutex.unlock();
		}
		break;

		case ComDataPkg:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x322, 0);
			write(m_nfd, pszBuff, sizeof(Drv_ComData));
			g_oDrvMutex.unlock();
		}
		break;

		case Record:
		{
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x30C, 1);
			write(m_nfd, pszBuff, sizeof(IecRecvCfg));
			g_oDrvMutex.unlock();
		}
		break;

		case SOE:
		{
		}
		break;
	}
}

void CSttDeviceComm::SetManualBI(char *pszBuff, int nLen)
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x302, 0);
	write(m_nfd, pszBuff, nLen);
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetStateTriger()
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x400, 0);
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetRising(int nRising)
{
	//PPS Test
	g_oDrvMutex.lock();
	if(nRising)
	{
		ioctl(m_nfd, 0x132, 1);
	}
	else
	{
		ioctl(m_nfd, 0x132, 0);
	}
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetPPSTestStart()
{
	if(CSttDeviceBase::g_pSttDeviceBase->m_nIecPkgFormat == 0)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x131, DMA_TYPE_NULL);    //停止探测模式
		g_oDrvMutex.unlock();
	}

	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL)
	{
		pSttTestBase->ReturnRealTimeEvent();
	}

#ifdef _MainBoard_PI_
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x143, 0); //停用模块内系数补偿功能,由于各模块上电顺序不统一,故每次开始实验都发一次该命令
	g_oDrvMutex.unlock();
#endif
	Sleep(100);

	if(g_theSystemConfig->m_nHasAnalog || g_theSystemConfig->m_nHasWeek)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x100, 1);
		g_oDrvMutex.unlock();
		Sleep(100);
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x103, 3);
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetPPSTestStop()
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x103, 0);
	g_oDrvMutex.unlock();
	AfterTestFinishedPro();
}

void CSttDeviceComm::SetADMUChannel(tmt_ManualTest *pTmt)
{
	unsigned int nCmd = 0;
	PSTT_MODULE pModule = NULL;
	long nChannelNum = 0;
	long nModulePos = 0;
	tmt_channel *pTmt_channel;
	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];
			pTmt_channel = pTmt->m_oManuParas.m_uiVOL;
			if(pModule == NULL || nCmd > 0)
			{
				continue;
			}

			nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;
			nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
			for(int i = 0; i < nChannelNum;i++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[i];
				if(m_nTmtPos < 0 || nCmd > 0)
				{
					continue;
				}

				if(pTmt_channel[m_nTmtPos].Harm[1].fAmp > 0.1 && pTmt_channel[m_nTmtPos].Harm[1].fFreq > 20.0)
				{
					nCmd |= (pModule->m_nChDrvPos[i]+1)<<24;
					nCmd |= nModulePos<<16;
					nCmd |= m_nTmtPos + 1;
				}
			}
		}
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];
			pTmt_channel = pTmt->m_oManuParas.m_uiCUR;
			if(pModule == NULL || nCmd > 0)
			{
				continue;
			}

			nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;
			nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
			for(int i = 0; i < nChannelNum;i++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[i];
				if(m_nTmtPos < 0 || nCmd > 0)
				{
					continue;
				}

				if(pTmt_channel[m_nTmtPos].Harm[1].fAmp > 0.1 && pTmt_channel[m_nTmtPos].Harm[1].fFreq > 20.0)
				{
					nCmd |= (pModule->m_nChDrvPos[i]+1)<<24;
					nCmd |= nModulePos<<16;
					nCmd |= 1<<8;
					nCmd |= m_nTmtPos + 1;
				}
			}
		}
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];
			if(pModule == NULL || nCmd > 0)
			{
				continue;
			}

			nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;
			nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
			for(int i = 0; i < nChannelNum;i++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[i];
				if(m_nTmtPos < 0 || nCmd > 0)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					pTmt_channel = pTmt->m_oManuParas.m_uiCUR;
				}
				else
				{
					pTmt_channel = pTmt->m_oManuParas.m_uiVOL;
				}

				if(pTmt_channel[m_nTmtPos].Harm[1].fAmp > 0.1 && pTmt_channel[m_nTmtPos].Harm[1].fFreq > 20.0)
				{
					if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
					{
						nCmd |= 1<<8;
					}
					nCmd |= (pModule->m_nChDrvPos[i]+1)<<24;
					nCmd |= nModulePos<<16;
					nCmd |= m_nTmtPos + 1;
				}
			}
		}
	}

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];
			if(pModule == NULL || nCmd > 0)
			{
				continue;
			}

			nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;
			nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
			for(int i = 0; i < nChannelNum;i++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[i];
				if(m_nTmtPos < 0 || nCmd > 0)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					pTmt_channel = pTmt->m_oManuParas.m_uiCUR;
				}
				else
				{
					pTmt_channel = pTmt->m_oManuParas.m_uiVOL;
				}

				if(pTmt_channel[m_nTmtPos].Harm[1].fAmp > 0.1 && pTmt_channel[m_nTmtPos].Harm[1].fFreq > 20.0)
				{
					if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
					{
						nCmd |= 1<<8;
					}
					nCmd |= (pModule->m_nChDrvPos[i]+1)<<24;
					nCmd |= nModulePos<<16;
					nCmd |= m_nTmtPos + 1;
				}
			}
		}
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];
			if(pModule == NULL || nCmd > 0)
			{
				continue;
			}

			nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;
			nModulePos = pModule->m_oModuleAttr.m_nModuleIndex;
			for(int i = 0; i < nChannelNum;i++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[i];
				if(m_nTmtPos < 0 || nCmd > 0)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					pTmt_channel = pTmt->m_oManuParas.m_uiCUR;
				}
				else
				{
					pTmt_channel = pTmt->m_oManuParas.m_uiVOL;
				}

				if(pTmt_channel[m_nTmtPos].Harm[1].fAmp > 0.1 && pTmt_channel[m_nTmtPos].Harm[1].fFreq > 20.0)
				{
					if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
					{
						nCmd |= 1<<8;
					}
					nCmd |= (pModule->m_nChDrvPos[i]+1)<<24;
					nCmd |= nModulePos<<16;
					nCmd |= m_nTmtPos + 1;
				}
			}
		}
	}

	if(nCmd > 0)
	{
		nCmd |= 1<<31;
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x148, nCmd);
		g_oDrvMutex.unlock();
	}
}

int CSttDeviceComm::SetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int nLen)
{
	int nRet = 0;
	long nModulePos = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x306, nModulePos);
	nRet = write(m_nfd, (char *)pszBuf, nLen);
	g_oDrvMutex.unlock();

	return nRet;
}

BOOL CSttDeviceComm::GetModuleFlash(PSTT_MODULE pModule, BYTE *pszBuf, int &nOffset)
{
	long nModulePos = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x10C, nModulePos);	
	read(m_nfd, (char *)pszBuf, 0x210);//清空缓存
	g_oDrvMutex.unlock();
	int nRet = 0;

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x123, nModulePos);
	g_oDrvMutex.unlock();
	int nLoopReadCnt = 0;
L:
	QEventLoop loop;
	QTimer::singleShot(1000, &loop, SLOT(quit()));
	loop.exec();

	g_oDrvMutex.lock();
	read(m_nfd, (char *)&nRet, 0x208);
	g_oDrvMutex.unlock();

	if((nRet & nModulePos) <= 0)
	{
		if(nLoopReadCnt++ < 5)
		{
			goto L;//超时5秒
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("GetModuleFlash TimeOut = %d s"), nLoopReadCnt);
	g_oDrvMutex.lock();
	int nsize = read(m_nfd, (char *)pszBuf, 0x210);
	g_oDrvMutex.unlock();
	if(nsize <= 0)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CSttDeviceComm::readFlashData nSizeErr"));
		return FALSE;
	}

	nOffset = (pszBuf[0] << 24) + (pszBuf[1] << 16) + (pszBuf[2] << 8) + pszBuf[3];
	nOffset = nOffset > 584 ? 584 : nOffset;
	QByteArray array((char *)pszBuf, nOffset);
	qDebug() << array.toHex();
	return TRUE;
}

void CSttDeviceComm::GetModulesFPGAInfo()
{
	memset(&m_oBoardinfo, 0, sizeof(Drv_BoardVersion));
	g_oDrvMutex.lock();
	read(m_nfd, (char *)&m_oBoardinfo, 0x209);
	g_oDrvMutex.unlock();

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("MainBoardInfo[%08x] Ver=%s"),
							   m_oBoardinfo.version[0], TransVersion(m_oBoardinfo.version[0]).GetString());
	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("DriverInfo[%08x]    Ver=%s"),
							   m_oBoardinfo.version[13], TransVersion(m_oBoardinfo.version[13]).GetString());
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strFPGAVer,
		   TransVersion(m_oBoardinfo.version[0]).GetString());
	if((m_oBoardinfo.version[13]>>16) > 2)
	{
		unsigned int nVal1 = (m_oBoardinfo.version[13] >> 16) & 0xff;
		nVal1 += 2000;
		unsigned int nVal2 = (m_oBoardinfo.version[13] >> 8) & 0xff;
		unsigned int nVal3 = m_oBoardinfo.version[13] & 0xff;

		CString strDriverVer;
		strDriverVer.Format("%d.%d.%d", nVal1, nVal2, nVal3);
		strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverVer,strDriverVer.GetString());
	}
	else
	{
		strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverVer,
			   TransVersion(m_oBoardinfo.version[13]).GetString());
	}

	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strAppName, APP_NAME);
	strcpy(g_theDeviceSystemParameter->m_oDeviceAttrs.m_strDriverName, DRV_NAME);
	long nModuleType;
	CString strBoardType;

	for(int i = 1; i < 13; i++)
	{
		switch(m_oBoardinfo.version[i] >> 24)
		{
			case 0xc0:
				strBoardType = "Digital-0G   ";
				nModuleType = STT_MODULE_TYPE_DIGITAL_0G8M;
				break;

			case 0xc2:
				strBoardType = "Digital-2G   ";
				nModuleType = STT_MODULE_TYPE_DIGITAL_2G6M;
				break;

			case 0xc4:
				strBoardType = "Digital-4G   ";
				nModuleType = STT_MODULE_TYPE_DIGITAL_4G4M;
				break;

			case 0x55:
				strBoardType = "Volt         ";
				nModuleType = STT_MODULE_TYPE_VOLT;
				break;

			case 0xaa:
				strBoardType = "Current      ";
				nModuleType = STT_MODULE_TYPE_CURRENT;
				break;

			case 0xa5:
				strBoardType = "Volt_Current ";
				nModuleType = STT_MODULE_TYPE_VOLT_CURRENT;
				break;

			case 0xcc:
				strBoardType = "FT3          ";
				nModuleType = STT_MODULE_TYPE_FT3;
				break;

			case 0x99:
				strBoardType = "Switch       ";
				nModuleType = STT_MODULE_TYPE_SWITCH;
				break;

			case 0x66:
				strBoardType = "Week(DC_Curr)";//特指直流电流小信号插件
				nModuleType = STT_MODULE_TYPE_WEEK_EX;
				break;

			case 0x88:
				strBoardType = "Week		 ";
				nModuleType = STT_MODULE_TYPE_WEEK_EX;
				break;

			case 0x80:
				strBoardType = "ADMU		 ";
				nModuleType = STT_MODULE_TYPE_ADMU;
				break;

			default:
				if(m_oBoardinfo.version[i] == 0)
				{
					continue;
				}

				strBoardType = "unknow       ";
				nModuleType = -1;
				break;
		}

		CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("Position=%d Type=%s Ver=%s BoardInfo[%08x]"), i,
								   strBoardType.GetString(), TransVersion(m_oBoardinfo.version[i]).GetString(), m_oBoardinfo.version[i]);
		char pszModuleType[32] = {0};
		stt_tmt_adj_para_trans_to_string(nModuleType, "ModuleType", pszModuleType);

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount; nIndex++)
		{
			STT_MODULE &oModule = g_theDeviceSystemParameter->m_oModules[nIndex];

			if(oModule.m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_MEAS_CURRENT
					|| oModule.m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_MEAS_VOLT)
			{
				continue;
			}

			if(i == oModule.m_oModuleAttr.m_nModuleIndex)
			{
				if(nModuleType >= 0)
				{
					CString strTypeCmd;
					strTypeCmd.AppendFormat(_T("%s-%s"), pszModuleType
											, TransVersion(m_oBoardinfo.version[i]).GetString());
					strcpy(oModule.m_oModuleAttr.m_strFPGAVer, strTypeCmd.GetString());
				}

				break;
			}
		}
	}
}

void GetVolReplayCoef(int nChannel, int nModuleUIndex, Drv_ReplayCoefItem *item)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return ;
	}

	float fChMax = pModule->m_oModuleAttr.m_fChMax;

	if(fChMax < EPSINON)
	{
		item->fCoef = 0;//幅值系数
		item->fZero = 0;//交流零漂
		item->fTmtCoef = 1;//变比
		item->fMaxValue = 100;
		return ;
	}

	item->fCoef = 1;//幅值系数
	item->fZero = 0;//交流零漂
	item->fTmtCoef = 1;//变比
	item->fMaxValue = fChMax * 1.414;
	item->fReverse = 0.999999;
	PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj =
		&pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel].m_pChWaveAdj[1];//统一取基波

	if(pChWaveAdj != NULL)
	{
		if(pChWaveAdj->m_nGearCount > 0)
		{
			PSTT_ADJUST_ITEM pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;

			if(pAdjItem != NULL)
			{
				item->fCoef = pAdjItem->m_fCoef;
				item->fZero = pAdjItem->m_fZero;
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("%f %f %f\n"), item->fCoef, item->fZero, item->fMaxValue);
}

void  GetCurReplayCoef(int nChannel, int nModuleIIndex, Drv_ReplayCoefItem *item)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return ;
	}

	float fChMax = pModule->m_oModuleAttr.m_fChMax;

	if(fChMax < EPSINON)
	{
		item->fCoef = 0;//幅值系数
		item->fZero = 0;//交流零漂
		item->fTmtCoef = 1;//变比
		item->fMaxValue = 20;
		return ;
	}

	item->fCoef = 1;//幅值系数
	item->fZero = 0;//交流零漂
	item->fTmtCoef = 1;//变比
	item->fMaxValue = fChMax * 1.414;
	item->fReverse = -0.999999;
	PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj =
		&pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel].m_pChWaveAdj[1];

	if(pChWaveAdj != NULL)
	{
		if(pChWaveAdj->m_nGearCount > 0)
		{
			PSTT_ADJUST_ITEM pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;

			if(pAdjItem != NULL)
			{
				item->fCoef = pAdjItem->m_fCoef;
				item->fZero = pAdjItem->m_fZero;
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("%f %f %f\n"), item->fCoef, item->fZero, item->fMaxValue);
}

void  GetUIReplayCoef(int nChannel, int nModuleIndex, Drv_ReplayCoefItem *item)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return ;
	}

	PSTT_MODULE_CH_DEF pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel];
	float fChMax = pChDef->m_fChACMaxValue;

	if(fChMax < EPSINON)
	{
		item->fCoef = 0;//幅值系数
		item->fZero = 0;//交流零漂
		item->fTmtCoef = 1;//变比
		item->fMaxValue = 20;
		return ;
	}

	item->fCoef = 1;//幅值系数
	item->fZero = 0;//交流零漂
	item->fTmtCoef = 1;//变比
	item->fMaxValue = fChMax * 1.414;

	if(pChDef->m_nEeType == STT_CH_EETYPE_VOLTAGE)
	{
		item->fReverse = 0.999999;
	}
	else
	{
		item->fReverse = -0.999999;
	}

	PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj =
		&pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel].m_pChWaveAdj[1];

	if(pChWaveAdj != NULL)
	{
		if(pChWaveAdj->m_nGearCount > 0)
		{
			PSTT_ADJUST_ITEM pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;

			if(pAdjItem != NULL)
			{
				item->fCoef = pAdjItem->m_fCoef;
				item->fZero = pAdjItem->m_fZero;
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("%f %f %f\n"), item->fCoef, item->fZero, item->fMaxValue);
}

void  GetWeekReplayCoef(int nChannel, int nModuleIndex, Drv_ReplayCoefItem *item)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nModuleIndex];

	if(pModule == NULL)
	{
		return ;
	}

	PSTT_MODULE_CH_DEF pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel];
	float fChMax = pChDef->m_fChACMaxValue;

	if(fChMax < EPSINON)
	{
		item->fCoef = 0;//幅值系数
		item->fZero = 0;//交流零漂
		item->fTmtCoef = pModule->m_fChTmtCoef[nChannel];//变比
		item->fMaxValue = 20;
		return ;
	}

	item->fCoef = 1;//幅值系数
	item->fZero = 0;//交流零漂
	item->fTmtCoef = pModule->m_fChTmtCoef[nChannel];//变比
	item->fMaxValue = fChMax * 1.414213;
	item->fReverse = 0.999999;
	PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj =
		&pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel].m_pChWaveAdj[1];

	if(pChWaveAdj != NULL)
	{
		if(pChWaveAdj->m_nGearCount > 0)
		{
			PSTT_ADJUST_ITEM pAdjItem = &pChWaveAdj->m_oChGearAdj[pChWaveAdj->m_nGearCount - 1].m_oAdjItem;

			if(pAdjItem != NULL)
			{
				item->fCoef = pAdjItem->m_fCoef;
				item->fZero = pAdjItem->m_fZero;
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("%f %f %f\n"), item->fCoef, item->fZero, item->fMaxValue);
}

int GetModuleIndex(PSTT_MODULE *pModule, int nModuleCnt, int nModulePos)
{
	for(int i = 0; i < nModuleCnt; i++)
	{
		if(pModule[i]->m_oModuleAttr.m_nModuleIndex == nModulePos)
		{
			return i;
		}
	}

	return -1;
}

void CSttDeviceComm::ProLtReplayDAPara(DeviceDAPara *pDAPara, tmt_ReplayParas *pTmt)
{
	QList<int> oList;

	for(int i = 0; i < pTmt->m_nModuleCount; i++)
	{
		if(pTmt->m_oModule[i].m_nSel)
		{
			oList.append(pTmt->m_oModule[i].m_nIndex);
		}
	}

	int nModuleIndex = 0;

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(oList.contains(pModule->m_oModuleAttr.m_nModuleIndex))
		{
			CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(pModule->m_oModuleAttr.m_fChMax, g_theSystemConfig->m_fAuxDC_Vol, nIndex, FALSE);
			pDAPara->nvolt[nIndex] = CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nIndex];
		}
	}

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
	CSttPowerCtrlBase *pSttPowerCtrlBase = NULL;

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(oList.contains(pModule->m_oModuleAttr.m_nModuleIndex))
		{
			pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
				pDAPara->nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
			}
		}
	}

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
	pSttPowerCtrlBase = NULL;

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		if(oList.contains(pModule->m_oModuleAttr.m_nModuleIndex))
		{
			pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetVoltDA_State();
				pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
				pDAPara->nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
			}
		}
	}

#ifdef _MainBoard_PN_

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI == NULL)
		{
			return;
		}

		if(pModule_UI->m_oModuleAttr.m_nModulePower != STT_MODULE_UI_V310_C60)
		{
			return;
		}

		if(oList.contains(pModule_UI->m_oModuleAttr.m_nModuleIndex))
		{
			long nCurModuleIndex = -1;

			if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
			{
				nCurModuleIndex += 1;
			}

			if(g_theDeviceSystemParameter->m_nModuleCount_I > 0)
			{
				nCurModuleIndex += 1;
			}

			if(nCurModuleIndex >= 0)
			{
				pDAPara->nvolt[nCurModuleIndex + 1] = (pDAPara->nvolt[nCurModuleIndex] >> 8) & 0xFF;
			}
		}
	}

#endif
}

void CSttDeviceComm::tmt_to_drv_LtReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef)
{
	Drv_LtReplayParam oDrvPara;
	Drv_ReplayCoef *Coef = (Drv_ReplayCoef *)pszReplayCoef;
	memset(&oDrvPara, 0, sizeof(Drv_LtReplayParam));
	oDrvPara.freq = 2500; //20Khz 2500 播放频率快了容易中断，来不及给FPGA传后续数据
	oDrvPara.tripType = pTmt->m_nTripType;

	switch(pTmt->m_nTripType)
	{
		case 0: // 无触发
			oDrvPara.tripLoopCount = pTmt->m_nStartCycleNum; //设置触发计数器
			break;

		case 1: // 手动触发
			oDrvPara.modeAfterTrip = pTmt->m_nTrigAfterMode;
			break;

		case 2: // GPS触发
		{
			short nYear, nMon, nDay, nHour, nMin, nSec;
			TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
			nHour = pTmt->m_tGps.nHour;
			nMin = pTmt->m_tGps.nMinutes;
			nSec = pTmt->m_tGps.nSeconds;
			unsigned int ntime_t;
			TransTimer_To_t(ntime_t, nYear, nMon, nDay, nHour, nMin, nSec);
			ntime_t -= g_theSttDeviceStatus->m_nTimeZone * 3600;
			oDrvPara.tripgpsSec = ntime_t;
			oDrvPara.tripgpsnSec = 0;
			oDrvPara.modeAfterTrip = pTmt->m_nTrigAfterMode;
		}
		break;

		case 3: // bi(开入)
		{
			oDrvPara.stBITrip.nBiLogic = pTmt->m_nBinLogic;
			int i = 0;
			oDrvPara.stBITrip.oValid.nModuleCount = 1;
			oDrvPara.stBITrip.oValid.item[0].nModule = 0x8000;

			for(i = 0; i < MAX_BINARYIN_COUNT; i++)
			{
				if(pTmt->m_binIn[i].nSelect)
				{
					oDrvPara.stBITrip.nBiRef = pTmt->m_binIn[i].nTrigMode;
					oDrvPara.stBITrip.oValid.item[0].nVal1 |= (0x01 << i);
				}
			}

			oDrvPara.modeAfterTrip = pTmt->m_nTrigAfterMode;
		}
		break;
	}

	oDrvPara.moduleCount = pTmt->GetModuleSelCount();

	for(int i = 0; i < pTmt->m_nModuleCount; i++)
	{
		if(pTmt->m_oModule[i].m_nSel)
		{
			oDrvPara.module |=  ModuleIndexTransToDrv(pTmt->m_oModule[i].m_nIndex);
		}
	}

	SetTestCommBo(oDrvPara.oDrvComBoSta, pTmt->m_binOut, pTmt->m_binOutEx);

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x352, 0);
	write(m_nfd, (char *)&oDrvPara, sizeof(Drv_LtReplayParam));
	g_oDrvMutex.unlock();

	CSttDeviceBase::g_pSttDeviceBase->DAPowerCtrl();
	ProLtReplayDAPara(&CSttDeviceBase::g_pSttDeviceBase->m_oDAPara, pTmt);
	int nModuleUIndex = 0;
	int nModuleIIndex = 0;
	int nModuleUIIndex = 0;
	int nModuleWeekIndex = 0;
	PSTT_MODULE pModule;

	for(int i = 0; i < pTmt->m_nModuleCount; i++)
	{
		int nModulePosIndex = pTmt->m_oModule[i].m_nIndex - 1;

		for(int j = 0; j < g_theDeviceSystemParameter->m_nModuleCount; j++)
		{
			pModule = &g_theDeviceSystemParameter->m_oModules[j];
			int nChanSize = pModule->m_oModuleAttr.m_nChannelNum;

			if(pModule->m_oModuleAttr.m_nModuleIndex == (nModulePosIndex + 1))
			{
				if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT) // 电压
				{
					nModuleUIndex = GetModuleIndex(g_theDeviceSystemParameter->m_oModules_U,
												   g_theDeviceSystemParameter->m_nModuleCount_U,
												   pModule->m_oModuleAttr.m_nModuleIndex);
					Coef->Items[nModulePosIndex].nChCnt = 6;
					Coef->Items[nModulePosIndex].nCode = 32;

					for(int k = 0; k < nChanSize; k++)
					{
						Coef->Items[nModulePosIndex].Item[k].nCh = pModule->m_nChDrvPos[k];
						GetVolReplayCoef(k, nModuleUIndex, &Coef->Items[nModulePosIndex].Item[k]);
					}
				}
				else if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_CURRENT)  // 电流
				{
					nModuleIIndex = GetModuleIndex(g_theDeviceSystemParameter->m_oModules_I,
												   g_theDeviceSystemParameter->m_nModuleCount_I,
												   pModule->m_oModuleAttr.m_nModuleIndex);
					Coef->Items[nModulePosIndex].nChCnt = 6;
					Coef->Items[nModulePosIndex].nCode = 32;

					for(int k = 0; k < nChanSize; k++)
					{
						Coef->Items[nModulePosIndex].Item[k].nCh = pModule->m_nChDrvPos[k];
						GetCurReplayCoef(k, nModuleIIndex, &Coef->Items[nModulePosIndex].Item[k]);
					}
				}
				else if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)  // 电压电流
				{
					nModuleUIIndex = GetModuleIndex(g_theDeviceSystemParameter->m_oModules_UI,
													g_theDeviceSystemParameter->m_nModuleCount_UI,
													pModule->m_oModuleAttr.m_nModuleIndex);
					Coef->Items[nModulePosIndex].nChCnt = 6;
					Coef->Items[nModulePosIndex].nCode = 32;

					if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
							||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
							||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
					{
						Coef->Items[nModulePosIndex].nChCnt = 12;
						Coef->Items[nModulePosIndex].nCode = 16;
					}
					else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
					{
						Coef->Items[nModulePosIndex].nChCnt = 8;
						Coef->Items[nModulePosIndex].nCode = 16;
					}

					for(int k = 0; k < nChanSize; k++)
					{
						Coef->Items[nModulePosIndex].Item[k].nCh = pModule->m_nChDrvPos[k];
						GetUIReplayCoef(k, nModuleUIIndex, &Coef->Items[nModulePosIndex].Item[k]);
					}
				}
				else if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_WEEK_EX)
				{
					nModuleWeekIndex = GetModuleIndex(g_theDeviceSystemParameter->m_oModules_WEEK,
													  g_theDeviceSystemParameter->m_nModuleCount_WEEK,
													  pModule->m_oModuleAttr.m_nModuleIndex);
					Coef->Items[nModulePosIndex].nChCnt = 12;
					Coef->Items[nModulePosIndex].nCode = 16;

					if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
					{
						Coef->Items[nModulePosIndex].nChCnt = 8;
						Coef->Items[nModulePosIndex].nCode = 16;
					}

					for(int k = 0; k < nChanSize; k++)
					{
						Coef->Items[nModulePosIndex].Item[k].nCh = pModule->m_nChDrvPos[k];
						GetWeekReplayCoef(k, nModuleWeekIndex, &Coef->Items[nModulePosIndex].Item[k]);
					}
				}
			}
		}
	}

	DeviceDAPara *pDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
	CSttDeviceBase::g_pSttDeviceBase->WriteDApara(pDAPara);

	if(g_theSystemConfig->m_nHasWeek)
	{
		float fMaxOut[12];

		for(int i = 0; i < 12; i++)
		{
			fMaxOut[i] = 0;
		}

		BOOL bSetTap;
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			bSetTap = FALSE;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
			{
				g_nWeekTap = GetTapCode_PIA12DS(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
			{
				g_nWeekTap = GetTapCode_EVTECT(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				g_nWeekTap = GetTapCode_PNS331(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
			{
				g_nWeekTap = GetTapCode_EVTECT_Ex1(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
			{
				g_nWeekTap = GetTapCode_DC6U10V(fMaxOut, TRUE, WeekTap[nIndex], 0);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
			{
				g_nWeekTap = GetTapCode_DC6I20mA(fMaxOut, TRUE, WeekTap[nIndex], 0);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
			{
				g_nWeekTap = GetTapCode_PN_DC6U6I(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
			{
				g_nWeekTap = GetTapCode_L336D(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}

			if(bSetTap)
			{
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap); //实验过程中档位不变
				g_oDrvMutex.unlock();
			}
		}
	}
}

void CSttDeviceComm::tmt_to_drv_ComReplay(tmt_ReplayParas *pTmt, char *pszReplayCoef)
{
}

BOOL CSttDeviceComm::TranslateDigitalVoltCurrentBuffer(tmt_channel *pVChannel, tmt_channel *pIChannel, long *pBuff, PSTT_MODULE pModule,
		int nHarm, BOOL bIsFT3)
{
	tmt_channel *pChannel;
	int nType;
	int nChannelCnt = 37;//U1-U19,I1-I18
	long DrvData[nChannelCnt * 3];
	memset(DrvData, 0, nChannelCnt * 3 * sizeof(long));
	float fAmp, fFre, fPh;
	int nGroupIndex;
	int nTmtPos;
	BOOL bHarm = FALSE;

	if(pModule == NULL)
	{
		return FALSE;
	}

	int nFT3ChsCnt = 0;
	int nFT3VoltChsCnt = 0;
	int nFT3CurrChsCnt = 0;
	BOOL bHarmValid = FALSE;

	for(int i = 0; i < nChannelCnt; i++)
	{		
		fAmp = 0;
		fPh = 0;
		fFre = 50;

		nTmtPos = pModule->m_nChTmtPos[i];
		long nEeType = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType;
		if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
		{
			nEeType = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeTypeEx;
			nTmtPos = pModule->m_nChTmtPosEx[i];
		}

		if(nEeType == STT_CH_EETYPE_VOLTAGE)
		{
			nType = STT_MODULE_TYPE_VOLT;
			pChannel = pVChannel;
			nFT3VoltChsCnt++;
		}
		else
		{
			nType = STT_MODULE_TYPE_CURRENT;
			pChannel = pIChannel;
			nFT3CurrChsCnt++;
		}

		if(nTmtPos >= 0)
		{
			if(nHarm < 0)
			{
				//间谐波
				fAmp = pChannel[nTmtPos].InterHarm.fAmp;
				fPh = pChannel[nTmtPos].InterHarm.fAngle;
				fFre = pChannel[nTmtPos].InterHarm.fFreq;

				if(pChannel[nTmtPos].InterHarm.nSelectIndex < 0)
				{
					return FALSE;
				}
			}
			else if(nHarm == 0)
			{
				//Harm_State
				//状态序列谐波
				for(int nHarmIndex = 2; nHarmIndex < MAX_HARM_COUNT; nHarmIndex++)
				{
					bHarm = pChannel[nTmtPos].Harm[nHarmIndex].m_bSelect;

					if(bHarm)
					{
						fAmp = pChannel[nTmtPos].Harm[nHarmIndex].fAmp;
						fPh = pChannel[nTmtPos].Harm[nHarmIndex].fAngle;
						fFre = pChannel[nTmtPos].Harm[nHarmIndex].fFreq;
						break;//叠加一个谐波
					}
				}
			}
			else if(nHarm == 1)
			{
				//BASE
				fAmp = pChannel[nTmtPos].Harm[1].fAmp;
				fPh = pChannel[nTmtPos].Harm[1].fAngle;
				fFre = pChannel[nTmtPos].Harm[1].fFreq;
			}
			else
			{
				for(int nHarmIndex = 2; nHarmIndex < MAX_HARM_COUNT; nHarmIndex++)
				{
					if((nHarm - 1) == pChannel[nTmtPos].Harm[nHarmIndex].nSelectIndex)
					{
						fAmp = pChannel[nTmtPos].Harm[nHarmIndex].fAmp;
						fPh = pChannel[nTmtPos].Harm[nHarmIndex].fAngle;
						fFre = pChannel[nTmtPos].Harm[nHarmIndex].fFreq;
						bHarmValid = TRUE;
						break;//叠加一个谐波
					}
				}
			}
		}

		if(bIsFT3)
		{
			if(g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
			{
				//柔直
				if(nType == STT_MODULE_TYPE_CURRENT)
				{
					if(nFT3CurrChsCnt <= 12)
					{
						fFre = 0;
					}
				}
				else
				{
					if(nFT3VoltChsCnt <= 6)
					{
						fFre = 0;
					}
				}
			}
		}

		if(nType == STT_MODULE_TYPE_CURRENT)
		{
			nFT3ChsCnt = nFT3CurrChsCnt;
		}
		else
		{
			nFT3ChsCnt = nFT3VoltChsCnt;
		}

		nGroupIndex = nTmtPos / 3;
		TransDigitalChannelToDrv(fAmp, fPh, fFre, nGroupIndex, DrvData + 3 * i, nType, pModule, bIsFT3, nFT3ChsCnt - 1);
	}

	if(!bHarmValid && nHarm > 1)
	{
		return FALSE;    //无有效谐波分量
	}

	if(bIsFT3)
	{
		long nDrvPos;
		long nVoltCnt = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nVoltDrvCnt;
		long nCurrDrvCnt = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvCnt;

		//volt
		for(int j = 0; j < nVoltCnt; j++)
		{
			nDrvPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nVoltDrvPos[j] - 1;
			pBuff[nDrvPos * 3] = DrvData[j * 3];
			pBuff[nDrvPos * 3 + 1] = DrvData[j * 3 + 1];
			pBuff[nDrvPos * 3 + 2] = DrvData[j * 3 + 2];
		}

		//current 19-36
		for(int j = 0; j < nCurrDrvCnt; j++)
		{
			nDrvPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[j] - 1;
			pBuff[nDrvPos * 3] = DrvData[(j + 19) * 3];
			pBuff[nDrvPos * 3 + 1] = DrvData[(j + 19) * 3 + 1];
			pBuff[nDrvPos * 3 + 2] = DrvData[(j + 19) * 3 + 2];
		}
	}
	else
	{
		//volt
		for(int j = 0; j < 12; j++)
		{
			if(j > 2)
			{
				pBuff[(j + 1) * 3] = DrvData[j * 3];
				pBuff[(j + 1) * 3 + 1] = DrvData[j * 3 + 1];
				pBuff[(j + 1) * 3 + 2] = DrvData[j * 3 + 2];
			}
			else
			{
				pBuff[j * 3] = DrvData[j * 3];
				pBuff[j * 3 + 1] = DrvData[j * 3 + 1];
				pBuff[j * 3 + 2] = DrvData[j * 3 + 2];
			}
		}

		for(int j = 12; j < 18; j++)
		{
			pBuff[(j + 13) * 3] = DrvData[j * 3];
			pBuff[(j + 13) * 3 + 1] = DrvData[j * 3 + 1];
			pBuff[(j + 13) * 3 + 2] = DrvData[j * 3 + 2];
		}

		//Uz
		pBuff[9] = DrvData[18 * 3];
		pBuff[10] = DrvData[18 * 3 + 1];
		pBuff[11] = DrvData[18 * 3 + 2];

		//current
		for(int j = 19; j < 31; j++)
		{
			pBuff[(j - 6) * 3] = DrvData[j * 3];
			pBuff[(j - 6) * 3 + 1] = DrvData[j * 3 + 1];
			pBuff[(j - 6) * 3 + 2] = DrvData[j * 3 + 2];
		}

		for(int j = 31; j < 37; j++)
		{
			pBuff[j * 3] = DrvData[j * 3];
			pBuff[j * 3 + 1] = DrvData[j * 3 + 1];
			pBuff[j * 3 + 2] = DrvData[j * 3 + 2];
		}
	}

	return TRUE;
}

int GetDigitalDrvPos(int nChannel)
{
	if(nChannel == 18)
	{
		return 3;
	}

	if(nChannel < 12)
	{
		if(nChannel > 2)
		{
			return nChannel + 1; //4-12
		}
		else
		{
			return nChannel;//0-2
		}
	}
	else if(nChannel < 18)
	{
		return nChannel + 13; //25-
	}
	else if(nChannel < 31) //19-31
	{
		return nChannel - 6; //13-24
	}
	else
	{
		return nChannel;//31-
	}
}

void DigitalGradientPreProcess(float &fStart, float &fEnd, float &fStep, long &nStepCnt, long &nSign)
{
	if(fEnd < fStart)
	{
		nSign = -1;
	}
	else
	{
		nSign = 1;
	}

	float fTemp = fabs(fEnd - fStart) / fStep;
	long  nTemp = (long)fTemp;

	if((fTemp - nTemp) > EPSINON)
	{
		nStepCnt = nTemp + 1;
	}
	else
	{
		nStepCnt = nTemp;
	}
}

void CSttDeviceComm::TranslateDigitalVoltCurrentBuffer_Gradient(tmt_channel *pVChannel, tmt_channel *pIChannel, Drv_StateDeg *pDrvStateDeg,
		PSTT_MODULE pModule, BOOL bIsFT3)
{
	tmt_channel *pChannel;
	int nType;
	int nGroupIndex;
	int nTmtPos;
	int nDrvPos;
//	int nDrvPos_M_FT3;
	long nStepCount;
	float fStart;
	float fEnd;
	float fStep;
	long nSign;
	BOOL bDC;

	if(pModule == NULL)
	{
		return;
	}

	for(int i = 0; i < 37; i++)
	{
		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_VOLTAGE)
		{
			nType = STT_MODULE_TYPE_VOLT;
			pChannel = pVChannel;
		}
		else
		{
			nType = STT_MODULE_TYPE_CURRENT;
			pChannel = pIChannel;
		}

		nTmtPos = pModule->m_nChTmtPos[i];

		if(nTmtPos < 0)
		{
			continue;
		}
		else
		{
			nGroupIndex = nTmtPos / 3;

			if(fabs(pChannel[nTmtPos].Harm[1].fFreq) < EPSINON)
			{
				bDC = true;
			}
			else
			{
				bDC = false;
			}

			long nDrvOffSet = 0;
			if(bIsFT3)
			{
				if(nType == STT_MODULE_TYPE_VOLT)
				{
					nDrvPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nVoltDrvPos[i] - 1;

					if(nTmtPos < 6 && g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
					{
						bDC = true; //直流电压 或 中性母线电压
					}
				}
				else
				{
					//19-30
					nDrvPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[i - 19] - 1;
					//同时计算测量电流
//					nDrvPos_M_FT3 = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[i - 19 + 6] - 1;

					if(nTmtPos < 12 && g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
					{
						bDC = true; //直流电流
					}
				}

				if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
				{
					nDrvOffSet = 1;
				}
			}
			else
			{
				nDrvPos = GetDigitalDrvPos(i);
			}

			if(pChannel[nTmtPos].Ramp[0].nIndex > 0)
			{
				//幅值递变
				fStart = pChannel[nTmtPos].Harm[1].fAmp;
				fEnd = pChannel[nTmtPos].Ramp[0].fEnd;
				fStep = fabs(pChannel[nTmtPos].Ramp[0].fStep);

				if(fStep > EPSINON)
				{
					DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);
					pDrvStateDeg->nCount[3 * nDrvPos + 2 + nDrvOffSet] = nStepCount;
					pDrvStateDeg->changeVal[3 * nDrvPos + 2 + nDrvOffSet] =
						nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, nType, bIsFT3, nTmtPos);
					pDrvStateDeg->lastVal[3 * nDrvPos + 2 + nDrvOffSet] =
						TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, nType, bIsFT3, nTmtPos);
//					if(bIsFT3)
//					{
//						if(nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//						{
//							pDrvStateDeg->nCount[3 * nDrvPos_M_FT3 + 2] =
//								pDrvStateDeg->nCount[3 * nDrvPos + 2];
//							pDrvStateDeg->changeVal[3 * nDrvPos_M_FT3 + 2] =
//								nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, STT_MODULE_TYPE_CURRENT, bIsFT3, nTmtPos + 6);
//							pDrvStateDeg->lastVal[3 * nDrvPos_M_FT3 + 2] =
//								TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, STT_MODULE_TYPE_CURRENT, bIsFT3, nTmtPos + 6);
//						}
//					}
					pDrvStateDeg->nIsChange++;
				}
			}

			if(pChannel[nTmtPos].Ramp[1].nIndex > 0 && (!bDC))
			{
				//相位递变
				fStart = pChannel[nTmtPos].Harm[1].fAngle;
				fEnd = pChannel[nTmtPos].Ramp[1].fEnd;
				fStep = fabs(pChannel[nTmtPos].Ramp[1].fStep);

				if(fStep > StateDegressMinStep)
				{
					DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);
					pDrvStateDeg->nCount[3 * nDrvPos + nDrvOffSet] = nStepCount;
					long  nPh;
					nPh = fStep * 65536 / 360;
					nPh = nPh << 16;
					pDrvStateDeg->changeVal[3 * nDrvPos + nDrvOffSet] = nSign * nPh;
					nPh = fEnd * 65536 / 360;
					nPh = nPh << 16;
					pDrvStateDeg->lastVal[3 * nDrvPos + nDrvOffSet] = nPh;
//					if(bIsFT3)
//					{
//						if(nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//						{
//							pDrvStateDeg->nCount[3 * nDrvPos_M_FT3] =
//								pDrvStateDeg->nCount[3 * nDrvPos];
//							pDrvStateDeg->changeVal[3 * nDrvPos_M_FT3] =
//								pDrvStateDeg->changeVal[3 * nDrvPos];
//							pDrvStateDeg->lastVal[3 * nDrvPos_M_FT3] =
//								pDrvStateDeg->lastVal[3 * nDrvPos];
//						}
//					}
					pDrvStateDeg->nIsChange++;
				}
			}

			if(pChannel[nTmtPos].Ramp[2].nIndex == 1 && (!bDC))
			{
				//单波形输出频率递变
				fStart = fabs(pChannel[nTmtPos].Harm[1].fFreq);
				fEnd = fabs(pChannel[nTmtPos].Ramp[2].fEnd);
				fStep = fabs(pChannel[nTmtPos].Ramp[2].fStep);

				if(fStep > StateDegressMinStep)
				{
					DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);
					pDrvStateDeg->nCount[3 * nDrvPos + 1 + nDrvOffSet] = nStepCount;
					pDrvStateDeg->changeVal[3 * nDrvPos + 1 + nDrvOffSet] = nSign * TranslateDigitalFre(fStep,bIsFT3);
					pDrvStateDeg->lastVal[3 * nDrvPos + 1 + nDrvOffSet] = TranslateDigitalFre(fEnd,bIsFT3);
//					if(bIsFT3)
//					{
//						if(nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//						{
//							pDrvStateDeg->nCount[3 * nDrvPos_M_FT3 + 1] =
//								pDrvStateDeg->nCount[3 * nDrvPos + 1];
//							pDrvStateDeg->changeVal[3 * nDrvPos_M_FT3 + 1] =
//								pDrvStateDeg->changeVal[3 * nDrvPos + 1];
//							pDrvStateDeg->lastVal[3 * nDrvPos_M_FT3 + 1] =
//								pDrvStateDeg->lastVal[3 * nDrvPos + 1];
//						}
//					}
					pDrvStateDeg->nIsChange++;
				}
			}
		}
	}

	if(pDrvStateDeg->nIsChange > 0)
	{
		pDrvStateDeg->nIsChange = 1;
	}
}

void CSttDeviceComm::TransDigitalChannelToDrv(float fAmp, float fAng, float fFre, int nGroupIndex, long *pnDrvData,
		int nType, PSTT_MODULE pModule, BOOL bIsFT3, int nFT3ChannelTypePos)
{
	float fPh = fAng;
	bool bDC = false;

	//数字板硬件需要相位补偿,保证各子板相位同步
	if(!bIsFT3)
	{
		fPh += getDigitalPhRatio(pModule);
	}

	float fGroupAdd = 0;
	//SV块延时,补偿零散相位.整点补偿在SV配置处
	//相位补偿涉及到m_nDelayTime值的初始化来源.
	//尽量避免同一个控制块内出现不同组通道补偿零散相位
	int nDT = 1000000 / m_oCIEC61850CfgMngr.m_o92Mngr.GetSmv92Sample();

	if(!bIsFT3)
	{
		int nDelay = m_oCIEC61850CfgMngr.m_o92Mngr.GetSmv92DelayTime(nGroupIndex);
		fGroupAdd = (nDelay + m_nSmvAbnDelayOffset) * 4.5;
		fGroupAdd = fGroupAdd / nDT;
	}

	fPh -= fGroupAdd;

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	if(fabs(fFre) < EPSINON)
	{
		bDC = true;
		fPh = 90;

		if(fAmp < 0)
		{
			fPh = 270;
			fAmp = fabs(fAmp);
		}
	}
	else
	{
		bDC = false;
	}

	long  nPh = fPh * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	pnDrvData[1] = TranslateDigitalFre(fFre,bIsFT3);

	if(nType == STT_MODULE_TYPE_VOLT)
	{
		pnDrvData[2] = TransDigitalChannelAmp(fAmp, nGroupIndex, bDC, STT_MODULE_TYPE_VOLT, bIsFT3, nFT3ChannelTypePos);
	}
	else
	{
		pnDrvData[2] = TransDigitalChannelAmp(fAmp, nGroupIndex, bDC, STT_MODULE_TYPE_CURRENT, bIsFT3, nFT3ChannelTypePos);
	}

	if(bIsFT3 && bDC)
	{
		//FPGA输出码值补偿
		if(fPh < 270)
		{
			pnDrvData[2] += 1;
		}
		else
		{
			pnDrvData[2] -= 1;
		}
	}
}

long CSttDeviceComm::TransDigitalChannelAmp(float fValue, int nGroup, bool bDC, int nType, BOOL bIsFT3, int nFT3ChannelTypePos)
{
	if(fabs(fValue) < EPSINON)
	{
		return 0;
	}

	if(bIsFT3)
	{
		double fRa = 1;
		int nSampleLen = 3;
		QString strMap = m_oCIEC61850CfgMngr.m_p6044MngrBase->GetFt3ChannelType(nType, nFT3ChannelTypePos);

		if(strMap.length() > 0)
		{
			FT3MapPointer map = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_Ft3ChannelType.value(strMap);
			fRa = map.fRatio;
			nSampleLen = map.nSampleLen;
		}

		float fsqr2 = 1;

		if(!bDC)
		{
			fsqr2 = G2;
		}

		fValue = fValue * fsqr2 * 2 * fRa;
		fValue = fValue * pow(2, (4 - nSampleLen) * 8);
		return (long)fValue;
	}
	else
	{
		if(nGroup >= MAX_DIGITAL_GROUP_NUM)
		{
			return 0;
		}

		float fsqr2 = 1;

		if(!bDC)
		{
			fsqr2 = G2;
		}

		fValue = fValue * fsqr2 * 2;

		if(nType == STT_MODULE_TYPE_VOLT)
		{
			return fValue * g_theSystemConfig->PkgModePTRate(nGroup) / g_theSystemConfig->m_fVRate;
		}
		else
		{
			return fValue * g_theSystemConfig->PkgModeCTRate(nGroup) / g_theSystemConfig->m_fIRate;
		}
	}
}

long CSttDeviceComm::TranslateDigitalFre(float fFre, BOOL bIsFT3)
{
	int nSample = 4000;
	if(bIsFT3)
	{
		if(m_oCIEC61850CfgMngr.m_p6044MngrBase->GetSample() > 0)
		{
			nSample = m_oCIEC61850CfgMngr.m_p6044MngrBase->GetSample();
		}
	}
	else
	{
		if(m_oCIEC61850CfgMngr.m_o92Mngr.GetSmv92Sample() > 0)
		{
			nSample = m_oCIEC61850CfgMngr.m_o92Mngr.GetSmv92Sample();
		}
	}

	double dFre = fFre / nSample;
	if(dFre > 0.999999)
	{
		return 0xFFFFFFFF;
	}
	else
	{
		dFre = dFre * 0xFFFFFFFF;
		return (long)dFre;
	}
}

float CSttDeviceComm::getDigitalPhRatio(PSTT_MODULE pModule)
{
	if(pModule == NULL)
	{
		return 0;
	}

	return pModule->m_oModuleAttr.m_fDigitalDelay;
}

long CSttDeviceComm::TranslateACFre(float fFre)
{
	double dFre = fFre / 400000.0;
	if(dFre > 0.999999)
	{
		return 0xFFFFFFFF;
	}
	else
	{
		dFre = dFre * 0xFFFFFFFF;
		long nFre = dFre + 0.5;//4舍5入，减小递变时累积误差
		return nFre;
	}
}

//volt
void CSttDeviceComm::TransAnalogDCVolToDrv(float fAmp, int nChannel, int nModuleUIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fTmtCoef = pModule->m_fChTmtCoef[nChannel];
	fAmp = fAmp * fTmtCoef; //电压模块有固定比例升压器时使用
	float fChMax = pModule->m_oModuleAttr.m_fChMax;
	float fDefChDcMax = pModule->m_oModuleAttr.m_fDefChDcMax;

	if(fChMax > 0 && fDefChDcMax > 0)
	{
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fVoltMax > 0)
	{
		fVoltMax = qMin(fVoltMax, fDefChDcMax);

		if(fabs(fAmp) > fVoltMax)
		{
			if(fAmp > 0)
			{
				fAmp = fVoltMax;
			}
			else
			{
				fAmp = fVoltMax * (-1);
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0;//getTemperature();
	float fCoef = 1;
	float fZero = 0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust = stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL && bUseDcZero)
	{
		fZero = pChsAdjust->m_fDcZero[0];    //直流零漂
	}

	PSTT_ADJUST_ITEM  pAdjItem = stt_adj_get_ac(fabs(fAmp), pModule, nChannel, fTemperature, 0);

	if(pAdjItem != NULL)
	{
		fCoef = pAdjItem->m_fCoef;    //幅值系数
	}

	fAmp = fAmp * fCoef - fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/

	if(fabs(fAmp) > EPSINON)
	{
		long nH;
		double fH;
		long nL;
		long nRef;

		if(bUseDcZero)
		{
			nRef = 32767;
		}
		else
		{
			nRef = 65535;
		}

		fChMax = fChMax * 1.414;

		if((fabs(fAmp) + 0.00001) < fChMax)
		{
			nH = fAmp * nRef / fChMax; //65536/2=32768
			fH = fAmp * nRef / fChMax;
			nL = (fH - nH) * 65536;
			pDrvData[0] = ((nH << 16) & 0xFFFF0000) + nL; //补偿效果依赖于硬件的输出分辨率
		}
		else
		{
			if(bUseDcZero)
			{
				pDrvData[0] = 0x7fffffff;
			}
			else
			{
				pDrvData[0] = 0xffffffff;
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long CSttDeviceComm::TranslateACVoltAmp(float fAmp, int nChannel, int nModuleUIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	float fTemperature = 0; //getTemperature();
	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fAmp, pModule, nChannel, fTemperature, nHarm);
	float fTmtCoef = pModule->m_fChTmtCoef[nChannel];
	fAmp = fAmp * fTmtCoef; //电压模块有固定比例升压器时使用
	//fChMax算幅值做分母
	float fChMax = pModule->m_oModuleAttr.m_fChMax;

	if(fChMax > 0)
	{
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	//fVoltMax限制fAmp的最大值
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, nHarm);

	if(fVoltMax > 0)
	{
		fVoltMax = qMin(fVoltMax, fChMax);

		if(fAmp > fVoltMax)
		{
			fAmp = fVoltMax;
		}
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂

	if(pAdjItem != NULL)
	{
		fCoef = pAdjItem->m_fCoef;
		fZero = pAdjItem->m_fZero;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef + fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > 0)
	{
		if(fAmp < fChMax)
		{
			long nH = fAmp * 65536 / fChMax;
			double fH = fAmp * 65536 / fChMax;
			long nL = (fH - nH) * 65536;
			return ((nH << 16) & 0xFFFF0000) + nL;
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void CSttDeviceComm::TransAnalogVolToDrv(float fAmp, float fAng, float fFre, int nChannel,
		int nModuleUIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCVolToDrv(fAmp, nChannel, nModuleUIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fAmp, pModule, nChannel, fTemperature);

	if(pAdjItem != NULL)
	{
		faddPh = pAdjItem->m_fAngle;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("volt-channel-%d ph=%f"),nChannel,faddPh);
	faddPh -= g_theDeviceSystemParameter->m_oDeviceAttrs.m_fPhaseForMUTest;
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef);
	pnDrvData[2] = TranslateACVoltAmp(fAmp, nChannel, nModuleUIndex, nHarm + 1);
}

//current
void CSttDeviceComm::TransAnalogDCCurToDrv(float fAmp, int nChannel, int nModuleIIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fTmtCoef = pModule->m_fChTmtCoef[nChannel];
	fAmp = fAmp * fTmtCoef;
	/*************确定合适的fAmp值************/
	float fChMax = pModule->m_oModuleAttr.m_fChMax;
	float fDefChDcMax = pModule->m_oModuleAttr.m_fDefChDcMax;

	if(fChMax > 0 && fDefChDcMax > 0)
	{
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	float fCurrentMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fCurrentMax > 0)
	{
		fCurrentMax = qMin(fCurrentMax, fDefChDcMax);

		if(fabs(fAmp) > fCurrentMax)
		{
			if(fAmp > 0)
			{
				fAmp = fCurrentMax;
			}
			else
			{
				fAmp = fCurrentMax * (-1);
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	float fZero = 0;
	float fMaxRatio = 1;
	float fCoef = 1;
	PSTT_CHANNEL_ADJUSTS pChsAdjust = stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[0];    //直流零漂
		}

		fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;
	}

	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fabs(fAmp), pModule, nChannel, fTemperature, 0);

	if(pAdjItem != NULL)
	{
		fCoef = pAdjItem->m_fCoef;    //幅值系数
	}

	//电流模块通道硬件放大系数fHCoef,比如40A的单通道等于2个20A通道
	//计算40A大电流非线性需要单独20A通道计算,然后线性叠加
	float fHCoef = 1.0f;

	switch(pModule->m_oModuleAttr.m_nChMergeMode)
	{
		case STT_CURRENT_ChMergeMode_1Ch_Fixed:
			if(pModule->m_oModuleAttr.m_nChannelNum == 1)
			{
				//6合1模块
				fHCoef = 1.0/6.0;
			}
			break;
		case STT_CURRENT_ChMergeMode_3Ch_Fixed:
			if(pModule->m_oModuleAttr.m_nChannelNum == 3)
			{
				//6合3模块
				fHCoef = 1.0/2.0;
			}
			break;
	}

	fAmp = -fAmp * fCoef;

	/*************非线性段按20A量程计算************/
	float fAmp2 = fAmp*fHCoef;

	if(fabs(fAmp2) > 5)
	{
		//5A以上非线性段
		float fChMax2 = fChMax*fHCoef;
		fAmp2 = fAmp2 - fAmp2 * (fabs(fAmp2) - 5) * (fabs(fAmp2) - 5) * (fMaxRatio - 1) / ((fChMax2 - 5) * (fChMax2 - 5));
	}

	fAmp = fAmp2/fHCoef;
	/*************非线性段按20A量程计算************/

	fAmp += fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/

	if(fabs(fAmp) > EPSINON)
	{
		long nH;
		double fH;
		long nL;
		long nRef;

		if(bUseDcZero)
		{
			nRef = 32767;
		}
		else
		{
			fAmp = fabs(fAmp);
			nRef = 65535;
		}

		fChMax = fChMax * 1.414;

		if((fabs(fAmp) + 0.00001) < fChMax)
		{
			nH = fAmp * nRef / fChMax; //65536/2=32768
			fH = fAmp * nRef / fChMax;
			nL = (fH - nH) * 65536;
			pDrvData[0] = ((nH << 16) & 0xFFFF0000) + nL; //补偿效果依赖于硬件的输出分辨率
		}
		else
		{
			if(bUseDcZero)
			{
				pDrvData[0] = 0x7fffffff;
			}
			else
			{
				pDrvData[0] = 0xffffffff;
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long CSttDeviceComm::TranslateACCurrentAmp(float fAmp, int nChannel, int nModuleIIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	float fTemperature = 0; //getTemperature();
	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fAmp, pModule, nChannel, fTemperature, nHarm);
	float fTmtCoef = pModule->m_fChTmtCoef[nChannel];
	fAmp = fAmp * fTmtCoef; //电流模块通道合并时使用
	//fChMax算幅值做分母
	float fChMax = pModule->m_oModuleAttr.m_fChMax;

	if(fChMax > 0)
	{
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	//fCurrentMax限制fAmp的最大值
	float fCurrentMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, nHarm);

	if(fCurrentMax > 0)
	{
		fCurrentMax = qMin(fCurrentMax, fChMax);

		if(fAmp > fCurrentMax)
		{
			fAmp = fCurrentMax;
		}
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	PSTT_CHANNEL_ADJUSTS pChsAdjust = stt_adj_find_channel(pModule, nChannel, fTemperature);
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂
	float fMaxRatio = 1.0;

	if(pAdjItem != NULL)
	{
		fCoef = pAdjItem->m_fCoef;
		fZero = pAdjItem->m_fZero;
	}

	if(pChsAdjust != NULL)
	{
		fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Current_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	//电流模块通道硬件放大系数fHCoef,比如40A的单通道等于2个20A通道
	//计算40A大电流非线性需要单独20A通道计算,然后线性叠加
	float fHCoef = 1.0f;

	switch(pModule->m_oModuleAttr.m_nChMergeMode)
	{
		case STT_CURRENT_ChMergeMode_1Ch_Fixed:
			if(pModule->m_oModuleAttr.m_nChannelNum == 1)
			{
				//6合1模块
				fHCoef = 1.0/6.0;
			}
			break;
		case STT_CURRENT_ChMergeMode_3Ch_Fixed:
			if(pModule->m_oModuleAttr.m_nChannelNum == 3)
			{
				//6合3模块
				fHCoef = 1.0/2.0;
			}
			break;
	}

	/*************软件调幅************/
	fAmp = fAmp * fCoef; //5A以内线性段

	/*************非线性段按20A量程计算************/
	float fAmp2 = fAmp*fHCoef;

	if(fAmp2 > 5)
	{
		//5A以上非线性段
		float fChMax2 = fChMax*fHCoef;
		fAmp2 = fAmp2 - fAmp2 * (fAmp2 - 5) * (fAmp2 - 5) * (fMaxRatio - 1) / ((fChMax2 - 5) * (fChMax2 - 5));
	}

	fAmp = fAmp2/fHCoef;
	/*************非线性段按20A量程计算************/

	/*************软件调幅************/

	fAmp += fZero;
	/*************软件调幅************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > 0)
	{
		if(fAmp < fChMax)
		{
			long nH = fAmp * 65536 / fChMax;
			double fH = fAmp * 65536 / fChMax;
			long nL = (fH - nH) * 65536;
			return ((nH << 16) & 0xFFFF0000) + nL;
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void CSttDeviceComm::TransAnalogCurToDrv(float fAmp, float fAng, float fFre, int nChannel,
		int nModuleIIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh = 270 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCCurToDrv(fAmp, nChannel, nModuleIIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;//0:基波
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float fTemperature = 0; //getTemperature();
	float faddPh = 0;
	PSTT_ADJUST_ITEM pAdjItem = stt_adj_get_ac(fAmp, pModule, nChannel, fTemperature); //0:DC,1:基波

	if(pAdjItem != NULL)
	{
		faddPh = pAdjItem->m_fAngle;
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("current-channel-%d ph=%f"),nChannel,faddPh);
	faddPh -= g_theDeviceSystemParameter->m_oDeviceAttrs.m_fPhaseForMUTest;
	fAng -= faddPh * (nHarm + 1);
	fAng += 180;

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
	pnDrvData[1] = TranslateACFre(fFre * fFreCoef);
	pnDrvData[2] = TranslateACCurrentAmp(fAmp, nChannel, nModuleIIndex, nHarm + 1);
}

//UI
void CSttDeviceComm::TransAnalogDCUIToDrv_Volt(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	float fChMax = 0;
	float fChDcMax = 0;
	fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue;
	fChDcMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChDCMaxValue;

	if(fChMax > 0 && fChDcMax > 0)
	{
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fVoltMax > 0)
	{
		fVoltMax = qMin(fVoltMax, fChDcMax);

		if(fabs(fAmp) > fVoltMax)
		{
			if(fAmp > 0)
			{
				fAmp = fVoltMax;
			}
			else
			{
				fAmp = fVoltMax * (-1);
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	float fCoef = 1; //幅值系数
	float fZero = 0; //直流零漂
	PSTT_CHANNEL_ADJUSTS pChsAdjust = stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[0];    //直流零漂
		}

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			STT_CHANNEL_WAVE_ADJUST oChWaveAdj = pChsAdjust->m_pChWaveAdj[0];

			if(fabs(fAmp) >= oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_fGearValue)
			{
				fCoef = oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_oAdjItem.m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < oChWaveAdj.m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= oChWaveAdj.m_oChGearAdj[nIndex].m_fGearValue)
					{
						fCoef = oChWaveAdj.m_oChGearAdj[nIndex].m_oAdjItem.m_fCoef;
						break;
					}
				}
			}
		}
	}

	fAmp = fAmp * fCoef - fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fabs(fAmp) > EPSINON)
	{
		long nH;
		double fH;
		long nL;
		long nRef;

		if(bUseDcZero)
		{
			nRef = 32767;
		}
		else
		{
			nRef = 65535;
		}

		fChMax = fChMax * 1.414;

		if((fabs(fAmp) + 0.00001) < fChMax)
		{
			nH = fAmp * nRef / fChMax; //65536/2=32768
			fH = fAmp * nRef / fChMax;
			nL = (fH - nH) * 65536;
			pDrvData[0] = ((nH << 16) & 0xFFFF0000) + nL; //补偿效果依赖于硬件的输出分辨率
		}
		else
		{
			if(bUseDcZero)
			{
				pDrvData[0] = 0x7fffffff;
			}
			else
			{
				pDrvData[0] = 0xffffffff;
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

void CSttDeviceComm::TransAnalogDCUIToDrv_Current(float fAmp, int nChannel, int nModuleIndex, long *pDrvData, BOOL bUseDcZero)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	float fChMax = 0;
	float fChDcMax = 0;
	fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue;
	fChDcMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChDCMaxValue;

	if(fChMax > 0 && fChDcMax > 0)
	{
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	float fCurrentMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, 0);

	if(fCurrentMax > 0)
	{
		fCurrentMax = qMin(fCurrentMax, fChDcMax);

		if(fabs(fAmp) > fCurrentMax)
		{
			if(fAmp > 0)
			{
				fAmp = fCurrentMax;
			}
			else
			{
				fAmp = fCurrentMax * (-1);
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
		return;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	float fZero = 0;
	float fCoef = 1; //幅值系数
	float fMaxRatio = 1;
	PSTT_CHANNEL_ADJUSTS pChsAdjust = stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(bUseDcZero)
		{
			fZero = pChsAdjust->m_fDcZero[0];    //直流零漂
		}

		fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			STT_CHANNEL_WAVE_ADJUST oChWaveAdj = pChsAdjust->m_pChWaveAdj[0];

			if(fabs(fAmp) >= oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_fGearValue)
			{
				fCoef = oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_oAdjItem.m_fCoef;
			}
			else
			{
				//档位
				for(long nIndex = 0; nIndex < oChWaveAdj.m_nGearCount; nIndex++)
				{
					if(fabs(fAmp) <= oChWaveAdj.m_oChGearAdj[nIndex].m_fGearValue)
					{
						fCoef = oChWaveAdj.m_oChGearAdj[nIndex].m_oAdjItem.m_fCoef;
						break;
					}
				}
			}
		}
	}

	fAmp = -fAmp * fCoef;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
	{
		if(fabs(fAmp) > 15 && fCurrentMax > 15)
		{
			fAmp = fAmp - fAmp * (fAmp - 15) * (fAmp - 15) * (fMaxRatio - 1) / ((fChMax - 15) * (fChMax - 15));
		}
	}
	else
	{
		if(fabs(fAmp) > 5 && fCurrentMax > 5)
		{
			fAmp = fAmp - fAmp * (fAmp - 5) * (fAmp - 5) * (fMaxRatio - 1) / ((fChMax - 5) * (fChMax - 5));
		}
	}

	fAmp += fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fabs(fAmp) > EPSINON)
	{
		long nH;
		double fH;
		long nL;
		long nRef;

		if(bUseDcZero)
		{
			nRef = 32767;
		}
		else
		{
			fAmp = fabs(fAmp);
			nRef = 65535;
		}

		fChMax = fChMax * 1.414;

		if((fabs(fAmp) + 0.00001) < fChMax)
		{
			nH = fAmp * nRef / fChMax; //65536/2=32768
			fH = fAmp * nRef / fChMax;
			nL = (fH - nH) * 65536;
			pDrvData[0] = ((nH << 16) & 0xFFFF0000) + nL; //补偿效果依赖于硬件的输出分辨率
		}
		else
		{
			if(bUseDcZero)
			{
				pDrvData[0] = 0x7fffffff;
			}
			else
			{
				pDrvData[0] = 0xffffffff;
			}
		}
	}
	else
	{
		pDrvData[0] = 0;
	}

	/*************fAmp值转FPGA参数************/
}

long CSttDeviceComm::TranslateACUIAmp_Volt(float fAmp, int nChannel, int nModuleIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	//fChMax算幅值做分母
	float fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue;

	if(fChMax > 0)
	{
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	//fVoltMax限制fAmp的最大值
	float fVoltMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, nHarm);

	if(fVoltMax > 0)
	{
		fVoltMax = qMin(fVoltMax, fChMax);

		if(fAmp > fVoltMax)
		{
			fAmp = fVoltMax;
		}
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂
	PSTT_CHANNEL_ADJUSTS pChsAdjust = stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if(nHarm < pChsAdjust->nHarmCount)
			{
				STT_CHANNEL_WAVE_ADJUST oChWaveAdj = pChsAdjust->m_pChWaveAdj[nHarm];

				if(fabs(fAmp) >= oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_fGearValue)
				{
					fCoef = oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_oAdjItem.m_fCoef;
					fZero = oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_oAdjItem.m_fZero;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < oChWaveAdj.m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= oChWaveAdj.m_oChGearAdj[nIndex].m_fGearValue)
						{
							fCoef = oChWaveAdj.m_oChGearAdj[nIndex].m_oAdjItem.m_fCoef;
							fZero = oChWaveAdj.m_oChGearAdj[nIndex].m_oAdjItem.m_fZero;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Volt_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef + fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > 0)
	{
		if(fAmp < fChMax)
		{
			long nH = fAmp * 65536 / fChMax;
			double fH = fAmp * 65536 / fChMax;
			long nL = (fH - nH) * 65536;
			return ((nH << 16) & 0xFFFF0000) + nL;
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

long CSttDeviceComm::TranslateACUIAmp_Current(float fAmp, int nChannel, int nModuleIndex, int nHarm)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return 0;
	}

	//fChMax算幅值做分母
	float fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue;

	if(fChMax > 0)
	{
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	//fCurrentMax限制fAmp的最大值
	float fCurrentMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, nHarm);

	if(fCurrentMax > 0)
	{
		fCurrentMax = qMin(fCurrentMax, fChMax);

		if(fAmp > fCurrentMax)
		{
			fAmp = fCurrentMax;
		}
	}
	else
	{
		return 0;
	}

	/*************确定合适的fAmp值************/
	/*************fAmp值补偿************/
	float fTemperature = 0; //getTemperature();
	float fCoef = 1; //幅值系数
	float fZero = 0; //交流零漂
	float fMaxRatio = 1.0;
	PSTT_CHANNEL_ADJUSTS pChsAdjust = stt_adj_find_channel(pModule, nChannel, fTemperature);

	if(pChsAdjust != NULL)
	{
		fMaxRatio = pChsAdjust->m_fLargeCurrentRatio;

		if(pChsAdjust->m_pChWaveAdj != NULL)
		{
			if(nHarm < pChsAdjust->nHarmCount)
			{
				STT_CHANNEL_WAVE_ADJUST oChWaveAdj = pChsAdjust->m_pChWaveAdj[nHarm];

				if(fabs(fAmp) >= oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_fGearValue)
				{
					fCoef = oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_oAdjItem.m_fCoef;
					fZero = oChWaveAdj.m_oChGearAdj[oChWaveAdj.m_nGearCount - 1].m_oAdjItem.m_fZero;
				}
				else
				{
					//档位
					for(long nIndex = 0; nIndex < oChWaveAdj.m_nGearCount; nIndex++)
					{
						if(fabs(fAmp) <= oChWaveAdj.m_oChGearAdj[nIndex].m_fGearValue)
						{
							fCoef = oChWaveAdj.m_oChGearAdj[nIndex].m_oAdjItem.m_fCoef;
							fZero = oChWaveAdj.m_oChGearAdj[nIndex].m_oAdjItem.m_fZero;
							break;
						}
					}
				}
			}
		}
	}

	//CLogPrint::LogFormatString(XLOGLEVEL_DEBUG,_T("Current_channel-%d  Coef=%f Zero=%f"),nChannel,fCoef,fZero);
	fAmp = fAmp * fCoef;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
	{
		if(fabs(fAmp) > 15 && fCurrentMax > 15)
		{
			fAmp = fAmp - fAmp * (fAmp - 15) * (fAmp - 15) * (fMaxRatio - 1) / ((fChMax - 15) * (fChMax - 15));
		}
	}
	else
	{
		if(fAmp > 5 && fChMax > 5)
		{
			fAmp = fAmp - fAmp * (fAmp - 5) * (fAmp - 5) * (fMaxRatio - 1) / ((fChMax - 5) * (fChMax - 5));
		}
	}

	fAmp += fZero;
	/*************fAmp值补偿************/

	/*************fAmp值转FPGA参数************/
	if(fAmp > 0)
	{
		if(fAmp < fChMax)
		{
			long nH = fAmp * 65536 / fChMax;
			double fH = fAmp * 65536 / fChMax;
			long nL = (fH - nH) * 65536;
			return ((nH << 16) & 0xFFFF0000) + nL;
		}
		else
		{
			return 0xFFFFFFFF;
		}
	}
	else
	{
		return 0;
	}

	/*************fAmp值转FPGA参数************/
}

void CSttDeviceComm::TransAnalogUIToDrv_Volt(float fAmp, float fAng, float fFre, int nChannel,
		int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh = 90 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCUIToDrv_Volt(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float faddPh = 0;

	if(nChannel > -1 && nChannel < pModule->m_oModuleAttr.m_nChannelNum)
	{
		STT_CHANNEL_ADJUSTS oChsAdjust = pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel];

		if(oChsAdjust.m_pChWaveAdj != NULL)
		{
			if(oChsAdjust.nHarmCount > 1)
			{
				STT_CHANNEL_WAVE_ADJUST oChWaveAdj = oChsAdjust.m_pChWaveAdj[1];

				if(oChWaveAdj.m_nGearCount > 1)
				{
					for(int nGear = 0; nGear < oChWaveAdj.m_nGearCount; nGear++)
					{
						if(fAmp < oChWaveAdj.m_oChGearAdj[nGear].m_fGearValue)
						{
							faddPh = oChWaveAdj.m_oChGearAdj[nGear].m_oAdjItem.m_fAngle;
							break;
						}
					}
				}
				else
				{
					faddPh = oChWaveAdj.m_oChGearAdj[0].m_oAdjItem.m_fAngle;
				}
			}
		}
	}

	faddPh -= g_theDeviceSystemParameter->m_oDeviceAttrs.m_fPhaseForMUTest;
	fAng -= faddPh * (nHarm + 1);

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		fFreCoef = fFreCoef * 8;    //50K
	}

	pnDrvData[1] = TranslateACFre(fFre * fFreCoef);
	pnDrvData[2] = TranslateACUIAmp_Volt(fAmp, nChannel, nModuleIndex, nHarm + 1);
}

void CSttDeviceComm::TransAnalogUIToDrv_Current(float fAmp, float fAng, float fFre, int nChannel,
		int nModuleIndex, long *pnDrvData)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nHarm = 0;
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

	if(m_nEDFre < EPSINON)
	{
		m_nEDFre = 50;
	}

	if(fFre < EPSINON)
	{
		//AC通道出DC
		long  nPh = 270 * 65536 / 360;
		pnDrvData[0] = nPh << 16;
		pnDrvData[1] = 0;
		TransAnalogDCUIToDrv_Current(fAmp, nChannel, nModuleIndex, &pnDrvData[2], FALSE);
		return;
	}

	fAmp = fabs(fAmp);

	if(fFre <= m_nEDFre)
	{
		nHarm = 0;//0:基波
	}
	else
	{
		nHarm  = (fFre + 25) / m_nEDFre - 1;
	}

	float faddPh = 0;

	if(nChannel > -1 && nChannel < pModule->m_oModuleAttr.m_nChannelNum)
	{
		STT_CHANNEL_ADJUSTS oChsAdjust = pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel];

		if(oChsAdjust.m_pChWaveAdj != NULL)
		{
			if(oChsAdjust.nHarmCount > 1)
			{
				STT_CHANNEL_WAVE_ADJUST oChWaveAdj = oChsAdjust.m_pChWaveAdj[1];

				if(oChWaveAdj.m_nGearCount > 1)
				{
					for(int nGear = 0; nGear < oChWaveAdj.m_nGearCount; nGear++)
					{
						if(fAmp < oChWaveAdj.m_oChGearAdj[nGear].m_fGearValue)
						{
							faddPh = oChWaveAdj.m_oChGearAdj[nGear].m_oAdjItem.m_fAngle;
							break;
						}
					}
				}
				else
				{
					faddPh = oChWaveAdj.m_oChGearAdj[0].m_oAdjItem.m_fAngle;
				}
			}
		}
	}

	faddPh -= g_theDeviceSystemParameter->m_oDeviceAttrs.m_fPhaseForMUTest;
	fAng -= faddPh * (nHarm + 1);

	if(pModule->m_oModuleAttr.m_nModulePower != STT_MODULE_UI_V310_C60)
	{
		fAng += 180;
	}

	while((fAng >= 360) || (fAng < 0))
	{
		if(fAng >= 360)
		{
			fAng -= 360;
		}
		else
		{
			fAng += 360;
		}
	}

	long  nPh = fAng * 65536 / 360;
	nPh = nPh << 16;
	pnDrvData[0] = nPh;
	float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		fFreCoef = fFreCoef * 8;    //50K
	}

	pnDrvData[1] = TranslateACFre(fFre * fFreCoef);
	pnDrvData[2] = TranslateACUIAmp_Current(fAmp, nChannel, nModuleIndex, nHarm + 1);
}


void CSttDeviceComm::SetGooseSub(char *pszBuff)
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x30C, 1);
	write(m_nfd, pszBuff, sizeof(IecRecvCfg));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetBoMap(char *pszBuff)
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x30E, 1);
	write(m_nfd, pszBuff, sizeof(Drv_GSOutMap));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetFT3SubMap(char *pszBuff)
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x310, 0);
	write(m_nfd, pszBuff, sizeof(Ft3SubDatas));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetBinaryOutTurnOnVaule(int nValue)
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x137, nValue);
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::SetBinaryOut(BOOL bOpen)
{
	g_oDrvMutex.lock();
	if(bOpen)
	{
		ioctl(m_nfd, 0x107, 0xff);
	}
	else
	{
		ioctl(m_nfd, 0x107, 0);
	}
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::Set_BO_ENABLE(bool bEnable)
{
	g_oDrvMutex.lock();
	if(bEnable)
	{
		ioctl(m_nfd, 0x138, 1);
	}
	else
	{
		ioctl(m_nfd, 0x138, 0);
	}
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::Set_BI_ENABLE(bool bEnable)
{
	g_oDrvMutex.lock();
	if(bEnable)
	{
		ioctl(m_nfd, 0x139, 1);
	}
	else
	{
		ioctl(m_nfd, 0x139, 0);
	}
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::Set_Goose_BO_ENABLE(bool bEnable)
{
	g_oDrvMutex.lock();
	if(bEnable)
	{
		ioctl(m_nfd, 0x140, 1);
	}
	else
	{
		ioctl(m_nfd, 0x140, 0);
	}
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::Set_Goose_BI_ENABLE(bool bEnable)
{
	g_oDrvMutex.lock();
	if(bEnable)
	{
		ioctl(m_nfd, 0x141, 1);
	}
	else
	{
		ioctl(m_nfd, 0x141, 0);
	}
	g_oDrvMutex.unlock();
}

BOOL CSttDeviceComm::getLtReplayBufferAFlag()
{
	g_oDrvMutex.lock();
	BOOL bRet = ioctl(m_nfd, 0x504, 0) & 0x02;
	g_oDrvMutex.unlock();
	return bRet;
}

BOOL CSttDeviceComm::getLtReplayBufferBFlag()
{
	g_oDrvMutex.lock();
	BOOL bRet = ioctl(m_nfd, 0x504, 0) & 0x04;
	g_oDrvMutex.unlock();
	return bRet;
}

void CSttDeviceComm::setLtReplayBufferABLoop(unsigned int size, char *pszDrv, unsigned int ntype)//0 : loop 1: A 2: B
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x357, ntype);
	write(m_nfd, pszDrv, size);
	g_oDrvMutex.unlock();
}

long CSttDeviceComm::TransAuxDcVolt(float fUdc)
{
	long nValue = 0;
	//输出辅助直流,不区分模块,统一值
	float fUdcMax, fCoef, fZero;
	fUdcMax = 300;//典型值
	fCoef = 1.0f;
	fZero = 0.0f;

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_U; i++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[i];

		if(pModule != NULL)
		{
			PSTT_CHANNEL_WAVE_ADJUST pChUdcAdj =
				&pModule->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj;

			if(pChUdcAdj == NULL)
			{
				continue;
			}

			int nGearCnt = pChUdcAdj->m_nGearCount;

			if(nGearCnt > 0)
			{
				fUdcMax = pChUdcAdj->m_oChGearAdj[nGearCnt - 1].m_fGearValue;

				for(int j = 0; j < nGearCnt; j++)
				{
					if(fUdc < pChUdcAdj->m_oChGearAdj[j].m_fGearValue + EPSINON)
					{
						fCoef = pChUdcAdj->m_oChGearAdj[j].m_oAdjItem.m_fCoef;
						fZero = pChUdcAdj->m_oChGearAdj[j].m_oAdjItem.m_fZero;
						break;
					}
				}

				break;
			}
		}
	}

	if(fUdcMax < 1)
	{
		return 0;
	}

	fUdc += fZero;
	fUdc = fUdc * fCoef;
	float fValue = fUdc / fUdcMax * 0.75;
	fValue = qPow(2, 31) * fValue;
	nValue = (long)fValue & 0xFFFFF000;
	return nValue;
}

void CSttDeviceComm::SetAuxDcVolt(float fUdc)
{
	if(g_theDeviceSystemParameter->m_nModuleCount_U == 0)
	{
		return;
	}

	long nValue = TransAuxDcVolt(fUdc);
	CSttDeviceBase::g_pSttDeviceBase->InitDAData();
	BOOL bAuxDcOutput = FALSE;

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule != NULL)
		{
			float fUdcMax = 0;
			PSTT_CHANNEL_WAVE_ADJUST pChUdcAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj;

			if(pChUdcAdj != NULL && pChUdcAdj->m_nGearCount > 0)
			{
				fUdcMax = pChUdcAdj->m_oChGearAdj[pChUdcAdj->m_nGearCount - 1].m_fGearValue;
			}

			long nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;

			if(fUdcMax > EPSINON && nModuleIndex <= ADJUST_MAX_MODULE_COUNT)
			{
				nValue |= ModuleIndexTransToDrv(nModuleIndex);
				CSttPowerCtrlBase *pPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

				if(pPowerCtrlBase != NULL)
				{
					pPowerCtrlBase->SetVoltDA_State();
					pPowerCtrlBase->SetVoltDA_DC_300V(fUdc);
					unsigned long nDa = pPowerCtrlBase->GetModuleDA();
					CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nIndex] = nDa;
					CSttDeviceBase::g_pSttDeviceBase->m_oDAParaForTestStop.nvolt[nIndex] &= 0xFFFFFF00;
					CSttDeviceBase::g_pSttDeviceBase->m_oDAParaForTestStop.nvolt[nIndex] |= (nDa & 0xFF);
					bAuxDcOutput = TRUE;
				}
			}
		}
	}

	if(bAuxDcOutput)
	{
		g_fAuxVolt = fUdc;
		DeviceDAPara *pDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
		CSttDeviceBase::g_pSttDeviceBase->WriteDApara(pDAPara);
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x10f, nValue);
		g_oDrvMutex.unlock();
		CSttDeviceBase::g_pSttDeviceBase->WriteDAparaForTestStop();
	}
}

void CSttDeviceComm::SetSystemConfig()
{
	CSttDeviceBase::g_pSttDeviceBase->SetCurMergeConfig();

	g_oDrvMutex.lock();
	if(g_theSystemConfig->m_bSyncSecond)
	{
		ioctl(m_nfd, 0x110, 1);
	}
	else
	{
		ioctl(m_nfd, 0x110, 0);
	}

	if(g_theSystemConfig->m_bKeepSendIecPkt)
	{
		ioctl(m_nfd, 0x121, 1);
	}
	else
	{
		ioctl(m_nfd, 0x121, 0);
	}

	ioctl(m_nfd, 0x122, g_theSystemConfig->m_nFiberType);//千兆接收不支持自适应必须手动指定
	g_oDrvMutex.unlock();
	Sleep(10);
	//防抖时间
	int nTime = g_theSystemConfig->m_fStabTime * 1000; //ms
	nTime = nTime * 1000000 / 20;

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x120, nTime); //主板开关量模块防抖
	ioctl(m_nfd, 0x142, nTime); //扩展开关量模块防抖

	if(g_theSystemConfig->m_n588Syn)
	{
		ioctl(m_nfd, 0x101, 1);
	}
	else
	{
		ioctl(m_nfd, 0x101, 0);
	}
	g_oDrvMutex.unlock();
	Sleep(10);

	g_oDrvMutex.lock();
	if(g_theSystemConfig->m_nWindSpeed)
	{
		ioctl(m_nfd, 0x104, 1);
	}
	else
	{
		ioctl(m_nfd, 0x104, 0);
	}
	g_oDrvMutex.unlock();
	Sleep(10);

	g_theSttDeviceStatus->m_nTimeZone = g_theSystemConfig->m_nTimeZone;

	g_oDrvMutex.lock();
	if(g_theSystemConfig->m_bGtoB_UseUserTz)
	{
		ioctl(m_nfd, 0x105, g_theSystemConfig->m_nTimeZone);
	}
	else
	{
		ioctl(m_nfd, 0x105, 0);
	}
	g_oDrvMutex.unlock();

	SetPeripheral();
}

void CSttDeviceComm::InitDApara(int fd, BOOL bHasAdjFile)
{
	Sleep(100);//等待驱动初始化完成
	m_nfd = fd;
#ifdef _MainBoard_PI_
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x143, 0); //停用模块内系数补偿功能
	g_oDrvMutex.unlock();
#endif
	/******初始化2.0驱动内相关指针*****/
	m_oCIEC61850CfgMngr.SetGooseSub();
	m_oCIEC61850CfgMngr.SetGseOutMap();
	m_oCIEC61850CfgMngr.InitDigitalModulesInfo();
	/******初始化2.0驱动内相关指针*****/
	unsigned int nBiRegData = 0xffffffff;

	for(int i = 0; i < g_nBinCount && i < MAX_BINARYIN_COUNT; i++)
	{
		nBiRegData &= ~(1 << i); //配置466 PI1000的主板有效开入，防止硬件开入脚悬空产生无效干扰中断，硬过滤
	}

#ifndef _Board_PNS330
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x70005064, nBiRegData);
	//开入模式
	ioctl(m_nfd, 0x70004068, 0xb480b480);
	ioctl(m_nfd, 0x7000406c, 0xb480b480);
	ioctl(m_nfd, 0x70005068, 0xb480b480);
	ioctl(m_nfd, 0x7000506c, 0xb480b480);
	ioctl(m_nfd, 0x70005070, 0xb480b480);
	ioctl(m_nfd, 0x108, 0); //0x7000407c
	ioctl(m_nfd, 0x109, 0xffffffff); //0x70004070
	ioctl(m_nfd, 0x10a, 0xff); //0x70004074
	g_oDrvMutex.unlock();
	Sleep(10);
#endif

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x10D, ~nBiRegData);//驱动配置主板有效开入位，用于开入寄存器值软过滤
	g_oDrvMutex.unlock();
	GetBoardInfo(bHasAdjFile);//自动检测模块位置与类型,与系数文件不符的模块将禁用输出
	/*****开入参考配置****/
	int nBoutDefValue = 0;

	for(int nIndex = 0; nIndex < 16; nIndex++)
	{
		nBoutDefValue += (!g_theDeviceSystemParameter->m_oBoutTurnOnValue.m_nBout[nIndex]) << nIndex;
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x137, nBoutDefValue);
	ioctl(m_nfd, 0x107, 0xff);
	g_oDrvMutex.unlock();
	/*****开入参考配置****/
	CSttDeviceBase::g_pSttDeviceBase->InitDASetting();
	int nYear,nMon,nDay,nHour,nMin, nSec,nNSec;
	CDateTime::GetTime(nYear,nMon,nDay,nHour,nMin,nSec,nNSec);
	setBCodeTime(nYear, nMon, nDay, nHour, nMin, nSec);
	SetDrvMoudlePara();
	SetSystemConfig();//需要使用SetDrvMoudlePara中的模块配置
	//防抖时间
	int nTime = 2;//ms
	nTime = nTime * 1000000 / 20;

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x120, nTime);
	ioctl(m_nfd, 0x142, 0); //扩展开关量模块防抖
	g_oDrvMutex.unlock();

	CSttDeviceBase::g_pSttDeviceBase->m_bDevStaIsInit = TRUE;
}

void CSttDeviceComm::SetBISetting()
{
}

typedef struct
{
	int nZerofloat[6];
	unsigned int nXs[6];
	int nPh[6];
} FlashAjdData;

void CSttDeviceComm::FormatFlashData(PSTT_MODULE pModule, BYTE *pszBuf, long &nLen)
{
	int nOffsetLen = 0;
	BYTE *pszTempBuf = (BYTE *)malloc(nLen + 100);
	memcpy(pszTempBuf, pszBuf, nLen);
	unsigned char byte;
	long nIndex = 0;

	if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_SWITCH)
	{
		nOffsetLen = 8 + 8;

		for(int i = 3; i >= 0; i--)
		{
			byte = nOffsetLen >> i * 8 & 0xFF;
			pszBuf[nIndex] =  byte;
			nIndex++;
		}

		for(int i = 3; i >= 0; i--)
		{
			byte = pModule->m_oModuleAttr.m_nModuleAddr >> i * 8 & 0xFF;
			pszBuf[nIndex] =  byte;
			nIndex++;
		}

		int nSwitch = 0;

		if(pModule->m_oModuleAttr.m_nSwitchIn[0] == 1)
		{
			nSwitch |= 0xFF;
		}
		if(pModule->m_oModuleAttr.m_nSwitchIn[1] == 1)
		{
			nSwitch |= 0xFF00;
		}
		if(pModule->m_oModuleAttr.m_nSwitchIn[2] == 1)
		{
			nSwitch |= 0xFF << 16;
		}
		if(pModule->m_oModuleAttr.m_nSwitchIn[3] == 1)
		{
			nSwitch |= 0xFF00 << 16;
		}

		for(int i = 3; i >= 0; i--)
		{
			byte = nSwitch >> i * 8 & 0xFF;
			pszBuf[nIndex] =  byte;
			nIndex++;
		}

		nSwitch = 0;

		if(pModule->m_oModuleAttr.m_nSwitchIn[4] == 1)
		{
			nSwitch |= 0xFF;
		}
		if(pModule->m_oModuleAttr.m_nSwitchIn[5] == 1)
		{
			nSwitch |= 0xFF00;
		}
		if(pModule->m_oModuleAttr.m_nSwitchIn[6] == 1)
		{
			nSwitch |= 0xFF << 16;
		}
		if(pModule->m_oModuleAttr.m_nSwitchIn[7] == 1)
		{
			nSwitch |= 0xFF00 << 16;
		}

		for(int i = 3; i >= 0; i--)
		{
			byte = nSwitch >> i * 8 & 0xFF;
			pszBuf[nIndex] =  byte;
			nIndex++;
		}
	}
	else
	{
		nOffsetLen = 8 + 4 * 6 * 3;
		float fMax = 200.0;
		int nReverse = 1;
		int nChDrvPos;
		FlashAjdData oFlashAjdData;

		if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT)
		{
			nReverse = -1;
		}
		else if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_CURRENT)
		{
			nReverse = 1;
		}
		else
		{
			nOffsetLen = 8;

			for(int i = 3; i >= 0; i--)
			{
				byte = nOffsetLen >> i * 8 & 0xFF;
				pszBuf[nIndex] =  byte;
				nIndex++;
			}

			for(int i = 3; i >= 0; i--)
			{
				byte = pModule->m_oModuleAttr.m_nModuleAddr >> i * 8 & 0xFF;
				pszBuf[nIndex] =  byte;
				nIndex++;
			}

			memcpy(pszBuf + nIndex, pszTempBuf, nLen);
			nLen += nIndex;
			delete pszTempBuf;
			return;
		}

		fMax = pModule->m_oModuleAttr.m_fChMax * 1.414;

		for(int nChan = 0; nChan < 6; nChan++)
		{
			oFlashAjdData.nXs[nChan] = 1;
			oFlashAjdData.nPh[nChan] = 0;
			oFlashAjdData.nZerofloat[nChan] = 0;
		}

		for(int nChan = 0; nChan < pModule->m_oModuleAttr.m_nChannelNum; nChan++)
		{
			PSTT_CHANNEL_ADJUSTS pChsAdjust = &pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChan];
			nChDrvPos = pModule->m_nChDrvPos[nChan];
			oFlashAjdData.nZerofloat[nChDrvPos] = pChsAdjust->m_fDcZero[0] / fMax * 0x7FFFFFFF;
			PSTT_ADJUST_ITEM pAdjItem = &pChsAdjust->m_pChWaveAdj[1].m_oChGearAdj[0].m_oAdjItem;
			oFlashAjdData.nXs[nChDrvPos] = (int)(pAdjItem->m_fCoef * (1 << 30));
			oFlashAjdData.nPh[nChDrvPos] = (int)(pAdjItem->m_fAngle / 360.0 * (1 << 16));
			oFlashAjdData.nZerofloat[nChDrvPos] = oFlashAjdData.nZerofloat[nChDrvPos] * nReverse;
			oFlashAjdData.nPh[nChDrvPos] = oFlashAjdData.nPh[nChDrvPos] * nReverse;
		}

		for(int i = 3; i >= 0; i--)
		{
			byte = nOffsetLen >> i * 8 & 0xFF;
			pszBuf[nIndex] =  byte;
			nIndex++;
		}

		for(int i = 3; i >= 0; i--)
		{
			byte = pModule->m_oModuleAttr.m_nModuleAddr >> i * 8 & 0xFF;
			pszBuf[nIndex] =  byte;
			nIndex++;
		}

		memcpy(pszBuf + nIndex, (char *)&oFlashAjdData, sizeof(FlashAjdData));
		nIndex += sizeof(FlashAjdData);
	}

	memcpy(pszBuf + nIndex, pszTempBuf, nLen);
	nLen += nIndex;
	delete pszTempBuf;
}

void CSttDeviceComm::SetDrvMoudlePara()
{
	Drv_ModulePara oDrv_ModulePara;
	memset(&oDrv_ModulePara, 0, sizeof(Drv_ModulePara));
	memset(&m_oModuleMaxVaildCnt, 0, sizeof(Drv_ModuleMaxVaildCnt));
	int nModuleIndex = 0;
	int nHarmCnt = 31;

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule_U = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule_U != NULL)
		{
			if(pModule_U->m_oModuleAttr.m_nErr)
			{
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
			}
			else
			{
				nModuleIndex = pModule_U->m_oModuleAttr.m_nModuleIndex;
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
			}

			m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = CHANNEL_MAX + CHANNEL_MAX * 3 * nHarmCnt;
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule_I = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule_I != NULL)
		{
			if(pModule_I->m_oModuleAttr.m_nErr)
			{
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
			}
			else
			{
				nModuleIndex = pModule_I->m_oModuleAttr.m_nModuleIndex;
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
			}

			m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = CHANNEL_MAX + CHANNEL_MAX * 3 * nHarmCnt;
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule_UI != NULL)
		{
			if(pModule_UI->m_oModuleAttr.m_nErr)
			{
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
			}
			else
			{
				nModuleIndex = pModule_UI->m_oModuleAttr.m_nModuleIndex;
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
			}

			m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = CHANNEL_MAX + CHANNEL_MAX * 3 * nHarmCnt;
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//DIGITAL
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
	{
		PSTT_MODULE pModule_D = g_theDeviceSystemParameter->m_oModules_D[nIndex];

		if(pModule_D != NULL)
		{
			if(pModule_D->m_oModuleAttr.m_nErr)
			{
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
			}
			else
			{
				nModuleIndex = pModule_D->m_oModuleAttr.m_nModuleIndex;
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
			}

			m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = DIGITAL_CHANNEL_MAX * nHarmCnt * 3;
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//Week
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
	{
		PSTT_MODULE pModule_W = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

		if(pModule_W != NULL)
		{
			if(pModule_W->m_oModuleAttr.m_nErr)
			{
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
			}
			else
			{
				nModuleIndex = pModule_W->m_oModuleAttr.m_nModuleIndex;
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
			}

			if(pModule_W->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
			{
				m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 48 + 48 * 3 * 2;
			}
			else if(pModule_W->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 8 + 8 * 3 * nHarmCnt;
			}
			else
			{
				m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 12 + 12 * 3 * nHarmCnt;
			}

			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//FT3
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_FT3; nIndex++)
	{
		PSTT_MODULE pModule_FT3 = g_theDeviceSystemParameter->m_oModules_FT3[nIndex];

		if(pModule_FT3 != NULL)
		{
			if(pModule_FT3->m_oModuleAttr.m_nErr)
			{
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
			}
			else
			{
				nModuleIndex = pModule_FT3->m_oModuleAttr.m_nModuleIndex;
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
			}

			m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = DIGITAL_CHANNEL_MAX * nHarmCnt * 3;
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//ADMU
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
	{
		PSTT_MODULE pModule_ADMU = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

		if(pModule_ADMU != NULL)
		{
			if(pModule_ADMU->m_oModuleAttr.m_nErr)
			{
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = 0;
			}
			else
			{
				nModuleIndex = pModule_ADMU->m_oModuleAttr.m_nModuleIndex;
				oDrv_ModulePara.nAlgTable[oDrv_ModulePara.nAlgCnt] = ModuleIndexTransToDrv(nModuleIndex);
			}

			m_oModuleMaxVaildCnt.maxVaildCnt[oDrv_ModulePara.nAlgCnt] = 9 + 8 * 3 * nHarmCnt;
			oDrv_ModulePara.nAlgCnt++;
		}
	}

	//BIO
	oDrv_ModulePara.nBiCnt = 1;
	oDrv_ModulePara.nBiTable[0] = 0x8000;
	oDrv_ModulePara.nBoCnt = 1;
	oDrv_ModulePara.nBoTable[0] = 0x8000;
	CSttDeviceBase::g_pSttDeviceBase->InitSwitchModule();//初始化全局公共变量m_oSwitchModules
	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

	//BIOEx
	for(int nIndex = 0; nIndex < oSwitchModules.m_nModulesCount; nIndex++)
	{
		nModuleIndex = oSwitchModules.oSWITCHINFO[nIndex].m_nModulePos;
		oDrv_ModulePara.nBiTable[oDrv_ModulePara.nBiCnt] = ModuleIndexTransToDrv(nModuleIndex);
		oDrv_ModulePara.nBoTable[oDrv_ModulePara.nBoCnt] = ModuleIndexTransToDrv(nModuleIndex);
		oDrv_ModulePara.nBiCnt++;
		oDrv_ModulePara.nBoCnt++;
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x331, 0);
	write(m_nfd, (char *)&oDrv_ModulePara, sizeof(Drv_ModulePara));
	g_oDrvMutex.unlock();
	Sleep(10);
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x356, 0);
	write(m_nfd, (char *)&m_oModuleMaxVaildCnt, sizeof(Drv_ModuleMaxVaildCnt));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::InitWeekOutputDAData()
{
	Drv_WeekInitDA oWeekInitDA;
	memset(&oWeekInitDA, 0, sizeof(Drv_WeekInitDA));
	int nModuleIndex = 0;
	BOOL bUsed = FALSE;

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I
				|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_WEEK_PN_MAIN
				|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_WEEK_L336D
		  )
		{
			oWeekInitDA.nModule[nModuleIndex] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
			oWeekInitDA.maxVaildCnt[nModuleIndex] = 12 + 12 * 3 * 31;
			nModuleIndex++;
			oWeekInitDA.nCnt++;
			bUsed = TRUE;
		}
		else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
		{
			oWeekInitDA.nModule[nModuleIndex] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
			oWeekInitDA.maxVaildCnt[nModuleIndex] = 8 + 8 * 3 * 31;
			nModuleIndex++;
			oWeekInitDA.nCnt++;
			bUsed = TRUE;
		}
		else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
		{
			oWeekInitDA.nModule[nModuleIndex] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
			oWeekInitDA.maxVaildCnt[nModuleIndex] = 48 + 48 * 3 * 2;
			nModuleIndex++;
			oWeekInitDA.nCnt++;
			bUsed = TRUE;
		}
	}

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];
		oWeekInitDA.nModule[nModuleIndex] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
		oWeekInitDA.maxVaildCnt[nModuleIndex] = 13 + 12 * 3 * 31;
		nModuleIndex++;
		oWeekInitDA.nCnt++;
		bUsed = TRUE;
	}

	if(bUsed)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x359, 0);
		write(m_nfd, (char *)&oWeekInitDA, sizeof(Drv_WeekInitDA));
		g_oDrvMutex.unlock();
	}
}

void CSttDeviceComm::tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt)
{
	Drv_ManuData oDrv_ManuData;
	memset(&oDrv_ManuData, 0, sizeof(Drv_ManuData));

	if(g_theSystemConfig->m_nHasAnalog)
	{
		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			Manual_volt(pTmt->m_uiVOL, (char *)&oDrv_ManuData, 31, nIndex); //31次谐波清除
		}

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			Manual_current(pTmt->m_uiCUR, (char *)&oDrv_ManuData, 31, nIndex); //31次谐波清除
		}

		//DAPara
		float fIsum = 0;
		float fVsum = 0;
		float fIMax = 0;
		CSttDeviceBase::g_pSttDeviceBase->InitDAData();
		float fAmp = 0;

		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			for(int k = 0; k < m_nTmtChanNum; k++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[k];

				if(m_nTmtPos < 0)
				{
					continue;
				}

				fAmp = fabs(pTmt->m_uiVOL[m_nTmtPos].Harm[1].fAmp);

				if(fVsum < fAmp)
				{
					fVsum = fAmp;
				}
			}

			CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(fVsum, g_theSystemConfig->m_fAuxDC_Vol, nIndex, FALSE);
		}

		//Current
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			for(int k = 0; k < m_nTmtChanNum; k++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[k];

				if(m_nTmtPos < 0)
				{
					continue;
				}

				fAmp = fabs(pTmt->m_uiCUR[m_nTmtPos].Harm[1].fAmp);
				fAmp = fAmp * pModule->m_fChTmtCoef[k];
				fIsum += fAmp;

				if(fIMax < fAmp)
				{
					fIMax = fAmp;
				}
			}

			switch(pModule->m_oModuleAttr.m_nChMergeMode)
			{
				case STT_CURRENT_ChMergeMode_1Ch_Fixed:
					if(pModule->m_oModuleAttr.m_nChannelNum == 1)
					{
						//6合1模块
						fIMax = fIMax/6.0;
					}
					break;
				case STT_CURRENT_ChMergeMode_3Ch_Fixed:
					if(pModule->m_oModuleAttr.m_nChannelNum == 3)
					{
						//6合3模块
						fIMax = fIMax/2.0;
					}
					break;
			}

			CSttDeviceBase::g_pSttDeviceBase->SetCurrentDApara_AC(fIsum, nIndex, fIMax);
		}

		DeviceDAPara *pDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
		CSttDeviceBase::g_pSttDeviceBase->WriteDApara(pDAPara, TRUE);
	}

	for(int i = 0; i < g_nBoutCount && i < MAX_BINARYOUT_COUNT; i++) //bo
	{
		oDrv_ManuData.oDrvComBoSta.item[0].nVal1 += ((!pTmt->m_binOut[i].nState) << i);
	}

	//默认扩展开出全恢复断开
	for(int i = 1; i < BIO_MODULE_MAX; i++)
	{
		oDrv_ManuData.oDrvComBoSta.item[i].nVal1 = 0xFFFFFFFF;
		oDrv_ManuData.oDrvComBoSta.item[i].nVal2 = 0xFFFFFFFF;
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x353, 0);
	write(m_nfd, (char *)&oDrv_ManuData, sizeof(Drv_ManuData));
	g_oDrvMutex.unlock();
}

/************公共处理函数部分*************/
void CSttDeviceComm::InitDrvResult()
{
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x144, 0);
	g_oDrvMutex.unlock();
}

//手动 谐波 递变 统一处理驱动结果
void CSttDeviceComm::ProCommDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults = stt_test_get_drvresult_buff();
	g_oDrvMutex.lock();
	int nret = read(m_nfd, pDrvResults, 0x203);
	g_oDrvMutex.unlock();

	if(nret <= 0)
	{
		return;
	}

	long nRealTimeEventCount = 0;
	BOOL bCalcBinAct = TRUE;

	for(int i = 0; i < nret / m_nDrvResItemLen; i++)
	{
		memcpy(&m_oDrvResItem, pDrvResults + i * m_nDrvResItemLen, m_nDrvResItemLen);
		double dTime = m_oDrvResItem.nSec + m_oDrvResItem.nNanoSec * 0.000000001;

		switch(m_oDrvResItem.nType)
		{
			case DrvResult_TestStart:
			{
				m_bRdDegRtData = TRUE;
				m_oStepInfo.dTime = dTime;
				m_oStepInfo.dLastBinTime = -1;
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
				long nCurStepIndex = 0;

				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_dTestStartTime = dTime;
					nCurStepIndex = pSttTestBase->m_nCurStepIndex;
				}

				ProStartBinEvent(m_oDrvResItem.nBi, nRealTimeEventCount, -1, nCurStepIndex, dTime);
				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, -1, nCurStepIndex, dTime, 0);

				if(pSttTestBase != NULL)
				{
					pSttTestBase->ReturnTestStateEvent_TestStart(dTime, 0, TRUE);
					pSttTestBase->ProRtDatasEvent(dTime, 0, nCurStepIndex, -1, 0);
				}

				CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.init();
				PowerDAMngr *pPowerDAMngr = &CSttDeviceBase::g_pSttDeviceBase->m_oPowerDAMngr;
				pPowerDAMngr->nTickCnt = 0;
				pPowerDAMngr->nTickTotal = 2;
				pPowerDAMngr->nUse = 1;
			}
			break;

			case DrvResult_TestFinish:
			{
				GetRtData();
				m_bRdDegRtData = FALSE;

				if(pSttTestBase != NULL)
				{
					pSttTestBase->SetTestStarting(FALSE);
					bTestFinished = TRUE;
					oTestFinishedTime.dTime = dTime;
					oTestFinishedTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				}

				AfterTestFinishedPro();
			}
			break;

			case DrvResult_BI:
			{
				m_oStepInfo.dLastBinTime = dTime;
				long nCurStepIndex = 0;
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					nCurStepIndex = pSttTestBase->m_nCurStepIndex;
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				ProCommBinEvent(m_oDrvResItem, nRealTimeEventCount, -1, nCurStepIndex,
								dTime, dTime - dTestStartTime, bCalcBinAct);
			}
			break;

			case DrvResult_BI_LogicMatch:
			{
				long nCurStepIndex = 0;

				if(pSttTestBase != NULL)
				{
					nCurStepIndex = pSttTestBase->m_nCurStepIndex;
				}

				if(CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient)
				{
					ProGradientResult(nCurStepIndex, m_oStepInfo.dLastBinTime);
				}
				else
				{
					CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nAct = 1;

					if(CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_fTripTime > 0)
					{
						//开入延时阶段再来开入不计入动作时间
					}
					else
						CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_fTripTime =
							m_oStepInfo.dLastBinTime - m_oStepInfo.dTime;
				}
			}
			break;

			case DrvResult_LtReplay_WaveTrip:
			{
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
				oRampRestCom.m_fTripTime = dTime - dTestStartTime;
			}
			break;

			case DrvResult_Degress_BfFault:
			{
				long nCurStepIndex = m_oDrvResItem.nDegressStep;
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_nCurStepIndex = nCurStepIndex;
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				bCalcBinAct = FALSE;
				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, -1,
								 nCurStepIndex, dTime, dTime - dTestStartTime, FALSE);
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
			}
			break;

			case DrvResult_Degress_Fault:
			{
				bCalcBinAct = TRUE;
				m_oStepInfo.nStep = m_oDrvResItem.nDegressStep;
				m_oStepInfo.dTime = dTime;
				m_oStepInfo.dLastBinTime = -1;
				long nCurStepIndex = m_oDrvResItem.nDegressStep;
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_nCurStepIndex = nCurStepIndex;
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, -1,
								 nCurStepIndex, dTime, dTime - dTestStartTime, FALSE);
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
			}
			break;

			case DrvResult_Output_Change:
			{
				if(pSttTestBase != NULL && pSttTestBase->GetTestStarting())
				{
					pSttTestBase->m_dTestStartTime = dTime;
					m_oStepInfo.dTime = dTime;
					m_oStepInfo.dLastBinTime = -1;
					pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);
					pSttTestBase->ProRtDatasEvent(dTime, 0, -1, -1, 0);
					ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, -1,
									 pSttTestBase->m_nCurStepIndex, dTime, 0, FALSE);
					memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
				}

				//复位电源管理
				PowerDAMngr *pPowerDAMngr = &CSttDeviceBase::g_pSttDeviceBase->m_oPowerDAMngr;
				pPowerDAMngr->nTickCnt = 0;
				pPowerDAMngr->nTickTotal = 2;
				pPowerDAMngr->nUse = 1;
			}
			break;

			case DrvResult_Degress_Return:
			{
				long nCurStepIndex = 0;

				if(pSttTestBase != NULL)
				{
					nCurStepIndex = pSttTestBase->m_nCurStepIndex;
				}

				//递变返回
				ProGradientResult(nCurStepIndex, m_oStepInfo.dLastBinTime);
				CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nAct = 1;
			}
			break;

			case DrvResult_PPS:
			{
				//PPS结果通过RTDATA上报
				if(g_theSttDeviceStatus != NULL)
				{
					if(m_oDrvResItem.nStep == 0)
					{
						g_pPPSBuf->Init();
						g_theSttDeviceStatus->m_nPPSReadPos = 0;
						g_theSttDeviceStatus->m_nPPS64ReadSizeTotal = 0;
					}

					char pBuf[8];
					memcpy(pBuf, &m_oDrvResItem.nStep, 4);
					memcpy(pBuf + 4, &m_oDrvResItem.nDegressStep, 4);
					g_pPPSBuf->WriteBuf(pBuf, 8);
				}
			}
			break;

			case DrvResult_STOP_BCODE:
			{
				CLogPrint::LogString(XLOGLEVEL_INFOR, _T("Stop BCode For PPSTest"));
			}
			break;

			case DrvResult_GOOSE_Link:
			{
				CString strAppid = CString("0x%1").arg(CString::number(m_oDrvResItem.nGooseFlag, 16));
				short nYear, nMon, nDay, nHour, nMin, nSec;
				CString strTime;
				TransTimer_t(m_oDrvResItem.nSec + g_theSttDeviceStatus->m_nTimeZone * 3600
							 , nYear, nMon, nDay, nHour, nMin, nSec);
				strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[warning] Goose[%s] 链路通,%s"),
										   strAppid.GetString(), strTime.GetString());
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				ProCommBinEvent_forGooseLink(m_oDrvResItem, nRealTimeEventCount, dTime, dTime - dTestStartTime);
			}
			break;
		}
	}
}

void CSttDeviceComm::ProStartBinEvent(Drv_BIStatus oBiStatus, long &nRealTimeEventCount,
									  int nCurStateIndex, int nStep, double dTime1)
{
	long nStateNum = -1;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL)
	{
		nStateNum = pSttTestBase->GetStateNum(nCurStateIndex);
	}

	//开始实验无法上报GOOSE的初值
	STT_TEST_EVENT obufEvent;
	int nEventIndex = 0;
	obufEvent.oTime.dTime = dTime1;
	obufEvent.oTime.dRealTime = 0;
	obufEvent.oTime.dBinActTime = -1;
	int nBiValue = 0;

	for(int nChanIndex = 0; nChanIndex < MAX_BINARYIN_COUNT && nChanIndex < g_nBinCount; nChanIndex++)
	{
		nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
		nBiValue = nBiValue & 0x1;
		nBiValue = (nBiValue == 0 ? 1 : 0);
		obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
		obufEvent.oEventInfo[nEventIndex].nStateIndex = nCurStateIndex;
		obufEvent.oEventInfo[nEventIndex].nStateNum = nStateNum;
		obufEvent.oEventInfo[nEventIndex].nStepIndex = nStep;
		obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
		obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
		nEventIndex++;
	}

	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

	if(oSwitchModules.m_nModulesCount > 0)
	{
		int nOffSet = 0;

		for(int j = 0; j < oSwitchModules.m_nModulesCount; j++)
		{
			if(j > 0)
			{
				nOffSet += oSwitchModules.oSWITCHINFO[j - 1].m_nBiCount;
			}

			long nBiIndex = 0;
			for(int k = 0; k < 64; k++)
			{
				if(oSwitchModules.oSWITCHINFO[j].m_bBiPos[k] == FALSE)
				{
					continue;
				}

				if(k < 32)
				{
					nBiValue = (oBiStatus.item[j + 1].nVal1 >> k) & 1;
				}
				else
				{
					nBiValue = (oBiStatus.item[j + 1].nVal2 >> (k - 32)) & 1;
				}

				obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_BinEx;
				obufEvent.oEventInfo[nEventIndex].nStateIndex = nCurStateIndex;
				obufEvent.oEventInfo[nEventIndex].nStateNum = nStateNum;
				obufEvent.oEventInfo[nEventIndex].nStepIndex = nStep;
				obufEvent.oEventInfo[nEventIndex].nChannel = nOffSet + nBiIndex + 1;
				obufEvent.oEventInfo[nEventIndex].nValue = nBiValue > 0 ? 0 : 1;
				nEventIndex++;
				nBiIndex++;
			}
		}
	}

	if(nEventIndex > 0)
	{
		obufEvent.nEventInfoCnt = nEventIndex;
		stt_add_test_event(obufEvent);
		nRealTimeEventCount++;
	}
}

#define BIN_TYPE_BI     0
#define BIN_TYPE_GOOSE  1
#define BIN_TYPE_FT3    2
void CSttDeviceComm::ProCommBinEvent_forGooseLink(Drv_ResultItem oResultItem, long &nRealTimeEventCount,
		double dTime1, double dTime2)
{
	//常闭接点第一帧报文即变位的话，1->0，无法判断
	Drv_BIStatus oBiStatus;
	memcpy(&oBiStatus, &oResultItem.nDi, sizeof(Drv_BIStatus));
	STT_TEST_EVENT obufEvent;
	int nEventIndex = 0;
	obufEvent.oTime.dTime = dTime1;
	obufEvent.oTime.dRealTime = dTime2;
	obufEvent.oTime.dBinActTime = -1;

	if(CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient)
	{
		obufEvent.oTime.dBinActTime = dTime1 - m_oStepInfo.dTime;
	}
	else
	{
		obufEvent.oTime.dBinActTime = dTime2;
	}

	GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	int nBiValue = 0;

	for(int nChanIndex = 0; nChanIndex < 8; nChanIndex++)
	{
		nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
		nBiValue = nBiValue & 0x1;
		nBiValue = (nBiValue == 0 ? 1 : 0);

		if(nBiValue == 0)
		{
			continue;
		}

		obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
		obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
		obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
		obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
		obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
		obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
		nEventIndex++;
		int &nBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[nChanIndex];

		if(nBinSwitchCount < BIBO_ACTCOUNT && nBinSwitchCount > -1)
		{
			if(obufEvent.oTime.dBinActTime < 0)
			{
				oRampRestCom.m_frTimeBinAct[nChanIndex][nBinSwitchCount] = obufEvent.oTime.dRealTime;
			}
			else
			{
				oRampRestCom.m_frTimeBinAct[nChanIndex][nBinSwitchCount] = obufEvent.oTime.dBinActTime;
			}

			nBinSwitchCount++;
		}
	}

	//无开关量板时 BinEx:0-63 考虑GOOSE虚端子
	for(int k = 0; k < 64; k++)
	{
		if(k < 32)
		{
			nBiValue = (oBiStatus.item[1].nVal1 >> k) & 1;
		}
		else
		{
			nBiValue = (oBiStatus.item[1].nVal2 >> (k - 32)) & 1;
		}

		nBiValue = nBiValue > 0 ? 0 : 1;

		if(nBiValue == 0)
		{
			continue;
		}

		obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_BinEx;
		obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
		obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
		obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
		obufEvent.oEventInfo[nEventIndex].nChannel = k + 1;
		obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
		nEventIndex++;
		int &nBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[k];

		if(nBinExSwitchCount > -1 && nBinExSwitchCount < BIBO_ACTCOUNT)
		{
			if(obufEvent.oTime.dBinActTime < 0)
			{
				oRampRestCom.m_frTimeBinExAct[k][nBinExSwitchCount] = obufEvent.oTime.dRealTime;
			}
			else
			{
				oRampRestCom.m_frTimeBinExAct[k][nBinExSwitchCount] = obufEvent.oTime.dBinActTime;
			}
		}

		nBinExSwitchCount++;
	}

	if(nEventIndex > 0)
	{
		obufEvent.nEventInfoCnt = nEventIndex;
		stt_add_test_event(obufEvent);
		nRealTimeEventCount++;
	}
}

void CSttDeviceComm::ProCommBinEvent(Drv_ResultItem oResultItem, long &nRealTimeEventCount,
									 int nCurStateIndex, int nStep, double dTime1, double dTime2, BOOL bCalcBinAct)
{
	State_EventRsts &oStateEvents = CSttDeviceBase::g_pSttDeviceBase->m_oStateEvents;
	long nStateNum = -1;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL)
	{
		nStateNum = pSttTestBase->GetStateNum(nCurStateIndex);
	}

	long nBinType = BIN_TYPE_BI;
	long nBinSize = g_nBinCount;//硬件开入取实际数量，数字开入只取8个

	if(g_nBinCount > MAX_BINARYIN_COUNT)
	{
		nBinSize = MAX_BINARYIN_COUNT;
	}

	if(oResultItem.nGooseFlag & 0x10000)
	{
		nBinSize = 8;
		nBinType = BIN_TYPE_GOOSE;
		int nSqNum = oResultItem.nGooseFlag & 0xFFFF;

		if(nSqNum)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("Goose变位,首帧报文SqNum = %d"), nSqNum);
		}
	}
	else if(oResultItem.nGooseFlag & 0x20000)
	{
		nBinSize = 8;
		//Ft3
		nBinType = BIN_TYPE_FT3;
	}

	DrvBIChange  oBiChg = oResultItem.oBiChg;
	Drv_BIStatus oBiStatus;

	if(nBinType == BIN_TYPE_GOOSE || nBinType == BIN_TYPE_FT3)
	{
		memcpy(&oBiStatus, &oResultItem.nDi, sizeof(Drv_BIStatus));
	}
	else
	{
		memcpy(&oBiStatus, &oResultItem.nBi, sizeof(Drv_BIStatus));
	}

	STT_TEST_EVENT obufEvent;
	int nEventIndex = 0;
	obufEvent.oTime.dTime = dTime1;
	obufEvent.oTime.dRealTime = dTime2;
	obufEvent.oTime.dBinActTime = -1;

	if(CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient)
	{
		obufEvent.oTime.dBinActTime = dTime1 - m_oStepInfo.dTime;
	}
	else
	{
		obufEvent.oTime.dBinActTime = dTime2;
	}

	GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	int nBiChang = 0;
	int nBiValue = 0;
	int nBiTemp;

	for(int nChanIndex = 0; nChanIndex < nBinSize; nChanIndex++)
	{
		nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
		nBiValue = nBiValue & 0x1;
		nBiChang = oBiChg.item[0].nVal1 >> nChanIndex;
		nBiChang = nBiChang & 0x1;

		if(nBiChang == 0)
		{
			continue;
		}

		nBiValue = (nBiValue == 0 ? 1 : 0);

		if(nCurStateIndex > -1)
		{
			for(int j = 0; j < oStateEvents.m_nRstCnt && j < 20; j++)
			{
				if(oStateEvents.m_oRst[j].m_nEventType == 2
						&& oStateEvents.m_oRst[j].m_bUsed == FALSE
						&& oStateEvents.m_oRst[j].m_nBinIndex == nChanIndex
						&& oStateEvents.m_oRst[j].m_nBinValue == nBiValue
						&& oStateEvents.m_oRst[j].m_nStateIdx == nStateNum)
				{
					oStateEvents.m_oRst[j].m_dEventTime = dTime1;
					oStateEvents.m_oRst[j].m_bUsed = TRUE;//状态内变位翻转只取第一次
				}
			}
		}

		obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
		obufEvent.oEventInfo[nEventIndex].nStateIndex = nCurStateIndex;
		obufEvent.oEventInfo[nEventIndex].nStateNum = nStateNum;
		obufEvent.oEventInfo[nEventIndex].nStepIndex = nStep;
		obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
		obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
		nEventIndex++;
		int &nBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[nChanIndex];

		if(nBinSwitchCount < BIBO_ACTCOUNT && nBinSwitchCount > -1)
		{
			if(obufEvent.oTime.dBinActTime < 0)
			{
				oRampRestCom.m_frTimeBinAct[nChanIndex][nBinSwitchCount] = obufEvent.oTime.dRealTime;
			}
			else
			{
				oRampRestCom.m_frTimeBinAct[nChanIndex][nBinSwitchCount] = obufEvent.oTime.dBinActTime;
			}

			if(nBinSwitchCount == 0)
			{
				oRampRestCom.m_nBinFirstChgState[nChanIndex] = nBiValue;
			}

			if(pSttTestBase != NULL)
			{
				if(pSttTestBase->m_nCurStateIndex > 0)
				{
					if(nBinType == BIN_TYPE_GOOSE || nBinType == BIN_TYPE_FT3)
					{
						nBiTemp = (m_oStateFirstDi.item[0].nVal1 >> nChanIndex) & 0x1;
					}
					else
					{
						nBiTemp = (m_oStateFirstBi.item[0].nVal1 >> nChanIndex) & 0x1;
					}

					CSttDeviceBase::g_pSttDeviceBase->m_nBinRefState[nChanIndex] = (nBiTemp == 0 ? 1 : 0);
				}
			}

			nBinSwitchCount++;
		}

		if(nCurStateIndex > -1)
		{
			//当前为状态序列实验
			if(nStep > -1)
			{
				//当前为状态序列递变
				oRampRestCom.m_nRampIndex[nChanIndex] = nStep;
			}
		}
	}

	if(nBinType == BIN_TYPE_GOOSE)
	{
		//无开关量板时 BinEx:0-63 考虑GOOSE虚端子
		for(int k = 0; k < g_nBinExCount && k < 64; k++)
		{
			if(k < 32)
			{
				nBiValue = (oBiStatus.item[1].nVal1 >> k) & 1;
				nBiChang = (oBiChg.item[1].nVal1 >> k) & 1;
			}
			else
			{
				nBiValue = (oBiStatus.item[1].nVal2 >> (k - 32)) & 1;
				nBiChang = (oBiChg.item[1].nVal2 >> (k - 32)) & 1;
			}

			if(nBiChang == 0)
			{
				continue;
			}

			nBiValue = nBiValue > 0 ? 0 : 1;
			obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_BinEx;
			obufEvent.oEventInfo[nEventIndex].nStateIndex = nCurStateIndex;
			obufEvent.oEventInfo[nEventIndex].nStateNum = nStateNum;
			obufEvent.oEventInfo[nEventIndex].nStepIndex = nStep;
			obufEvent.oEventInfo[nEventIndex].nChannel = k + 1;
			obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
			nEventIndex++;
			int &nBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[k];

			if(nBinExSwitchCount > -1 && nBinExSwitchCount < BIBO_ACTCOUNT)
			{
				if(obufEvent.oTime.dBinActTime < 0)
				{
					oRampRestCom.m_frTimeBinExAct[k][nBinExSwitchCount] = obufEvent.oTime.dRealTime;
				}
				else
				{
					oRampRestCom.m_frTimeBinExAct[k][nBinExSwitchCount] = obufEvent.oTime.dBinActTime;
				}
			}

			if(nBinExSwitchCount == 0)
			{
				oRampRestCom.m_nBinExFirstChgState[k] = nBiValue;
			}

			if(pSttTestBase != NULL)
			{
				if(pSttTestBase->m_nCurStateIndex > 0)
				{
					if(k < 32)
					{
						nBiTemp = (m_oStateFirstDi.item[1].nVal1 >> k) & 0x1;
					}
					else
					{
						nBiTemp = (m_oStateFirstDi.item[1].nVal2 >> (k - 32)) & 0x1;
					}

					CSttDeviceBase::g_pSttDeviceBase->m_nBinExRefState[k] = nBiTemp > 0 ? 0 : 1;
				}
			}

			nBinExSwitchCount++;
		}
	}
	else if(nBinType == BIN_TYPE_BI)
	{
		SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

		if(oSwitchModules.m_nModulesCount > 0)
		{
			int nOffSet = 0;

			for(int j = 0; j < oSwitchModules.m_nModulesCount; j++)
			{
				if(j > 0)
				{
					nOffSet += oSwitchModules.oSWITCHINFO[j - 1].m_nBiCount;
				}

				long nBiIndex = 0;
				for(int k = 0; k < 64; k++)
				{
					if(oSwitchModules.oSWITCHINFO[j].m_bBiPos[k] == FALSE)
					{
						continue;
					}

					if(k < 32)
					{
						nBiValue = (oBiStatus.item[j + 1].nVal1 >> k) & 1;
						nBiChang = (oBiChg.item[j + 1].nVal1 >> k) & 1;
					}
					else
					{
						nBiValue = (oBiStatus.item[j + 1].nVal2 >> (k - 32)) & 1;
						nBiChang = (oBiChg.item[j + 1].nVal2 >> (k - 32)) & 1;
					}

					if(nBiChang == 0)
					{
						nBiIndex++;
						continue;
					}

					nBiValue = nBiValue > 0 ? 0 : 1;
					obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_BinEx;
					obufEvent.oEventInfo[nEventIndex].nStateIndex = nCurStateIndex;
					obufEvent.oEventInfo[nEventIndex].nStateNum = nStateNum;
					obufEvent.oEventInfo[nEventIndex].nStepIndex = nStep;
					obufEvent.oEventInfo[nEventIndex].nChannel = nOffSet + nBiIndex + 1;
					obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
					nEventIndex++;
					int &nBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[nOffSet + nBiIndex];

					if(nBinExSwitchCount < BIBO_ACTCOUNT && nBinExSwitchCount > -1)
					{
						if(obufEvent.oTime.dBinActTime < 0)
						{
							oRampRestCom.m_frTimeBinExAct[nOffSet + nBiIndex][nBinExSwitchCount] = obufEvent.oTime.dRealTime;
						}
						else
						{
							oRampRestCom.m_frTimeBinExAct[nOffSet + nBiIndex][nBinExSwitchCount] = obufEvent.oTime.dBinActTime;
						}

						if(nBinExSwitchCount == 0)
						{
							oRampRestCom.m_nBinExFirstChgState[nOffSet + nBiIndex] = nBiValue;
						}

						if(pSttTestBase != NULL)
						{
							if(pSttTestBase->m_nCurStateIndex > 0)
							{
								if(k < 32)
								{
									nBiTemp = (m_oStateFirstBi.item[j + 1].nVal1 >> k) & 0x1;
								}
								else
								{
									nBiTemp = (m_oStateFirstBi.item[j + 1].nVal2 >> (k - 32)) & 0x1;
								}

								CSttDeviceBase::g_pSttDeviceBase->m_nBinExRefState[nOffSet + nBiIndex] = nBiTemp > 0 ? 0 : 1;
							}
						}

						nBinExSwitchCount++;
					}

					if(nCurStateIndex > -1)
					{
						//当前为状态序列实验
						if(nStep > -1)
						{
							//当前为状态序列递变
							oRampRestCom.m_nRampIndexEx[nOffSet + nBiIndex] = nStep;
						}
					}
					nBiIndex++;
				}
			}
		}
	}

	if(nEventIndex > 0)
	{
		obufEvent.nEventInfoCnt = nEventIndex;
		stt_add_test_event(obufEvent);
		nRealTimeEventCount++;
	}

	//基础递变实验开入量动作值计算
	if(!CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient)
	{
		return;
	}

	if(!bCalcBinAct)
	{
		return;
	}

	float fUIStepValue = 0.0f;
	int nChannel, nType;
	tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;
	nType = oGradientParas.m_nType;

	if(oGradientParas.m_nStepHarm > -1 && oGradientParas.m_nStepHarm < MAX_HARM_COUNT)
	{
		if(CSttDeviceBase::g_pSttDeviceBase->ChannelCurrs.size() > 0)
		{
			nChannel = CSttDeviceBase::g_pSttDeviceBase->ChannelCurrs.at(0);

			if(nChannel > -1 && nChannel < MAX_CURRENT_COUNT)
			{
				switch(nType)
				{
					case GRADIENT_AMP:
						fUIStepValue = oGradientParas.m_uiCUR[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAmp;
						break;

					case GRADIENT_ANG:
						fUIStepValue = oGradientParas.m_uiCUR[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAngle;
						break;

					case GRADIENT_FRE:
						fUIStepValue = oGradientParas.m_uiCUR[2][nChannel].Harm[1].fFreq;
						break;
				}
			}
		}
		else
		{
			if(CSttDeviceBase::g_pSttDeviceBase->ChannelVolts.size() > 0)
			{
				nChannel = CSttDeviceBase::g_pSttDeviceBase->ChannelVolts.at(0);

				if(nChannel > -1 && nChannel < MAX_VOLTAGE_COUNT)
				{
					switch(nType)
					{
						case GRADIENT_AMP:
							fUIStepValue = oGradientParas.m_uiVOL[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAmp;
							break;

						case GRADIENT_ANG:
							fUIStepValue = oGradientParas.m_uiVOL[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAngle;
							break;

						case GRADIENT_FRE:
							fUIStepValue = oGradientParas.m_uiVOL[2][nChannel].Harm[1].fFreq;
							break;
					}
				}
			}
		}
	}

	if(nStep == oGradientParas.m_nStepCnt)
	{
		fUIStepValue = oGradientParas.m_fStop;
	}
	else
	{
		fUIStepValue += oGradientParas.m_nStepDirection * oGradientParas.m_fStep * nStep;
	}

	if(nCurStateIndex < 0)
	{
		nCurStateIndex = 0;
	}

	for(int nChanIndex = 0; nChanIndex < 10; nChanIndex++)
	{
		if(m_pCurBins[nCurStateIndex].m_binIn[nChanIndex].nSelect == 1)
		{
			if(CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nAct == 0)
			{
				if(oRampRestCom.m_nrBinSwitchCount[nChanIndex] == 1)
				{
					oRampRestCom.m_fTripValueChl[nChanIndex] = fUIStepValue;
				}
			}
		}
	}

	for(int nChanIndex = 0; nChanIndex < g_nBinExCount && nChanIndex < MAX_ExBINARY_COUNT; nChanIndex++)
	{
		if(m_pCurBins[nCurStateIndex].m_binInEx[nChanIndex].nSelect == 1)
		{
			if(CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nAct == 0)
			{
				if(oRampRestCom.m_nrBinExSwitchCount[nChanIndex] == 1)
				{
					oRampRestCom.m_fTripValueChlEx[nChanIndex] = fUIStepValue;
				}
			}
		}
	}
}

void CSttDeviceComm::ProCommBoutEvent(DrvComBoStatus oBoStatus, long &nRealTimeEventCount,
									  int nCurStateIndex, int nStep, double dTime1, double dTime2, BOOL bIsStartTest)
{
	long nStateNum = -1;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase != NULL)
	{
		nStateNum = pSttTestBase->GetStateNum(nCurStateIndex);
	}

	STT_TEST_EVENT obufEvent;
	int nEventIndex = 0;
	obufEvent.oTime.dTime = dTime1;
	obufEvent.oTime.dRealTime = dTime2;
	obufEvent.oTime.dBinActTime = -1;
	GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	unsigned int nBoValue = 0;
	int nPreBoValue = 0;
	int nChanIndex;
	long nBoSize = g_nBoutCount;

	if(g_nBoutCount > MAX_BINARYOUT_COUNT)
	{
		nBoSize = MAX_BINARYOUT_COUNT;
	}

	if(nBoSize < 8)
	{
		nBoSize = 8;//GOOSE至少8开出
	}

	for(nChanIndex = 0; nChanIndex < nBoSize; nChanIndex++)
	{
		nBoValue = oBoStatus.item[0].nVal1 & (1 << nChanIndex);

		if(!bIsStartTest)
		{
			nPreBoValue = m_oPreBoStatus.item[0].nVal1 & (1 << nChanIndex);

			if(nBoValue == nPreBoValue)
			{
				continue;
			}
		}

		obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bout;
		obufEvent.oEventInfo[nEventIndex].nStateIndex = nCurStateIndex;
		obufEvent.oEventInfo[nEventIndex].nStateNum = nStateNum;
		obufEvent.oEventInfo[nEventIndex].nStepIndex = nStep;
		obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
		obufEvent.oEventInfo[nEventIndex].nValue = nBoValue > 0 ? 0 : 1;
		nEventIndex++;
		int &nBoutSwitchCount = oRampRestCom.m_nrBoutSwitchCount[nChanIndex];

		if(nBoutSwitchCount < BIBO_ACTCOUNT && nBoutSwitchCount > -1)
		{
			oRampRestCom.m_frTimeBoutAct[nChanIndex][nBoutSwitchCount] = obufEvent.oTime.dRealTime;
			nBoutSwitchCount++;
		}
	}

	if(oSwitchModules.m_nModulesCount > 0)
	{
		int nOffSet = 0;

		for(int i = 0; i < oSwitchModules.m_nModulesCount; i++)
		{
			if(i > 0)
			{
				nOffSet += oSwitchModules.oSWITCHINFO[i - 1].m_nBoCount;
			}

			long nBoIndex = 0;
			for(int j = 0; j < 64; j++)
			{
				if(oSwitchModules.oSWITCHINFO[i].m_bBoPos[j] == FALSE)
				{
					continue;
				}

				if(j < 32)
				{
					nBoValue = oBoStatus.item[i + 1].nVal1 & (1 << j);
					nPreBoValue = m_oPreBoStatus.item[i + 1].nVal1 & (1 << j);
				}
				else
				{
					nBoValue = oBoStatus.item[i + 1].nVal2 & (1 << (j-32));
					nPreBoValue = m_oPreBoStatus.item[i + 1].nVal2 & (1 << (j-32));
				}

				if(!bIsStartTest)
				{
					if(nBoValue == nPreBoValue)
					{
						nBoIndex++;
						continue;
					}
				}

				obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_BoutEx;
				obufEvent.oEventInfo[nEventIndex].nStateIndex = nCurStateIndex;
				obufEvent.oEventInfo[nEventIndex].nStateNum = nStateNum;
				obufEvent.oEventInfo[nEventIndex].nStepIndex = nStep;
				obufEvent.oEventInfo[nEventIndex].nChannel = nOffSet + nBoIndex + 1;
				obufEvent.oEventInfo[nEventIndex].nValue = nBoValue > 0 ? 0 : 1;
				nEventIndex++;
				int &nBoutExSwitchCount = oRampRestCom.m_nrBoutExSwitchCount[nOffSet + nBoIndex];

				if(nBoutExSwitchCount < BIBO_ACTCOUNT && nBoutExSwitchCount > -1)
				{
					oRampRestCom.m_frTimeBoutExAct[nOffSet + nBoIndex][nBoutExSwitchCount] = obufEvent.oTime.dRealTime;
					nBoutExSwitchCount++;
				}

				nBoIndex++;
			}
		}
	}
	else
	{
		//无开关量板时 BiEx:0-63 考虑GOOSE虚端子
		/***
		for(int k=0;k<64;k++)
		{
			if(k<32)
			{
				nBoValue=oBoStatus.item[1].nVal1&(1<<k);
				nPreBoValue=m_oPreBoStatus.item[1].nVal1&(1<<k);
			}
			else
			{
				nBoValue=oBoStatus.item[1].nVal2&(1<<(k-32));
				nPreBoValue=m_oPreBoStatus.item[1].nVal2&(1<<(k-32));
			}

			if(!bIsStartTest)
			{
				if(nBoValue==nPreBoValue)
					continue;
			}

			obufEvent.oEventInfo[nEventIndex].nType=SttResult_Type_BoutEx;
			obufEvent.oEventInfo[nEventIndex].nStateIndex=nCurStateIndex;
			obufEvent.oEventInfo[nEventIndex].nStateNum=nStateNum;
			obufEvent.oEventInfo[nEventIndex].nStepIndex=nStep;
			obufEvent.oEventInfo[nEventIndex].nChannel=k+1;
			obufEvent.oEventInfo[nEventIndex].nValue=nBoValue>0?0:1;
			nEventIndex++;
		}
		***/
	}

	if(nEventIndex > 0)
	{
		obufEvent.nEventInfoCnt = nEventIndex;
		stt_add_test_event(obufEvent);
		nRealTimeEventCount++;
	}
}

void CSttDeviceComm::ProGradientResult(int nStep, double dTime1)
{
	if(!CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient)
	{
		return;
	}

	GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	float fUIStepValue = 0.0f;
	int nChannel, nType;
	tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;
	nType = oGradientParas.m_nType;

	if(CSttDeviceBase::g_pSttDeviceBase->ChannelCurrs.size() > 0)
	{
		nChannel = CSttDeviceBase::g_pSttDeviceBase->ChannelCurrs.at(0);

		switch(nType)
		{
			case GRADIENT_AMP:
				fUIStepValue = oGradientParas.m_uiCUR[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAmp;
				break;

			case GRADIENT_ANG:
				fUIStepValue = oGradientParas.m_uiCUR[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAngle;
				break;

			case GRADIENT_FRE:
				fUIStepValue = oGradientParas.m_uiCUR[2][nChannel].Harm[1].fFreq;
				break;
		}
	}
	else
	{
		if(CSttDeviceBase::g_pSttDeviceBase->ChannelVolts.size() > 0)
		{
			nChannel = CSttDeviceBase::g_pSttDeviceBase->ChannelVolts.at(0);

			switch(nType)
			{
				case GRADIENT_AMP:
					fUIStepValue = oGradientParas.m_uiVOL[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAmp;
					break;

				case GRADIENT_ANG:
					fUIStepValue = oGradientParas.m_uiVOL[2][nChannel].Harm[oGradientParas.m_nStepHarm].fAngle;
					break;

				case GRADIENT_FRE:
					fUIStepValue = oGradientParas.m_uiVOL[2][nChannel].Harm[1].fFreq;
					break;
			}
		}
	}

	if(nStep == oGradientParas.m_nStepCnt)
	{
		fUIStepValue = oGradientParas.m_fStop;
	}
	else
	{
		fUIStepValue += oGradientParas.m_nStepDirection * oGradientParas.m_fStep * nStep;
	}

	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas.m_nTestMode == 1 && oRampRestCom.m_nAct == 1)
	{
		//测返回系数
		if(dTime1 < 0)
		{
			//返回过程无变位的情况
			oRampRestCom.m_fReturnValue = 0;
			oRampRestCom.m_fReturnTime = 0;
			oRampRestCom.m_fReturnCoef = 0;
		}
		else
		{
			oRampRestCom.m_fReturnValue = fUIStepValue;
			oRampRestCom.m_fReturnTime = dTime1 - m_oStepInfo.dTime;

			if(fabs(oRampRestCom.m_fTripValue) < EPSINON)
			{
				oRampRestCom.m_fReturnCoef = 0;
			}
			else
			{
				oRampRestCom.m_fReturnCoef = oRampRestCom.m_fReturnValue / oRampRestCom.m_fTripValue; //返回值/动作值
			}
		}

		if(pSttTestBase != NULL)
		{
			pSttTestBase->SyncGradientResult(nStep, oRampRestCom.m_fReturnTime, 1); //通知高级全量递变模块
		}
	}
	else
	{
		if(CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nAct == 0)
		{
			CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nAct = 1;
		}
		else
		{
			return;    //满足开入后又有多次开入的情况需要过滤
		}

		//测动作时间
		if(dTime1 < 0)
		{
			oRampRestCom.m_fTripValue = 0;
			oRampRestCom.m_fTripTime = 0;
		}
		else
		{
			oRampRestCom.m_fTripValue = fUIStepValue;
			oRampRestCom.m_fTripTime = dTime1 - m_oStepInfo.dTime;
		}

		if(pSttTestBase != NULL)
		{
			pSttTestBase->SyncGradientResult(nStep, oRampRestCom.m_fTripTime, 0); //通知高级全量递变模块
		}
	}
}

void CSttDeviceComm::Gradient_Manu_Harm(char *pszDrv, tmt_GradientParas &oGradientParas, int nGradientHarm, int nHarmCnt)
{
	Drv_ManuBin oBiSetting;
	memset(&oBiSetting, 0, sizeof(Drv_ManuBin));
	SetManualBI((char *)&oBiSetting, sizeof(Drv_ManuBin));
	CSttDeviceBase::g_pSttDeviceBase->SetChannelSelect(oGradientParas);
	CSttDeviceBase::g_pSttDeviceBase->CalStepValue_Gradient(oGradientParas, nGradientHarm);
	DrvDegressPara *pDrvPara = (DrvDegressPara *)pszDrv;
	memset(pDrvPara, 0, sizeof(DrvDegressPara));
	pDrvPara->isReturn = oGradientParas.m_nTestMode;
	pDrvPara->timeDiv = oGradientParas.m_fStepTime * 1000;

	if(pDrvPara->timeDiv < 1)
	{
		pDrvPara->timeDiv = 1;
	}

	pDrvPara->trip.nBiRef = 0;
	SetTestCommBi(pDrvPara->trip, oGradientParas.m_nBinLogic,
				  oGradientParas.m_binIn, oGradientParas.m_binInEx);
	SetTestCommBo(pDrvPara->boBfChange, oGradientParas.m_binOut[0], oGradientParas.m_binOutEx[0]);
	memcpy(&pDrvPara->boBfFault, &pDrvPara->boBfChange, sizeof(DrvComBoStatus));
	SetTestCommBo(pDrvPara->boFault, oGradientParas.m_binOut[1], oGradientParas.m_binOutEx[1]);
	memcpy(&m_oGradientBo_BfFault, &pDrvPara->boBfFault, sizeof(DrvComBoStatus));
	memcpy(&m_oGradientBo_Fault, &pDrvPara->boFault, sizeof(DrvComBoStatus));
	Gradient_NormalPara(&pDrvPara->AcPara,  &(oGradientParas.m_uiVOL[0][0]),
						&(oGradientParas.m_uiCUR[0][0]), nHarmCnt, 0);
	Gradient_NormalPara(&pDrvPara->AcPara,  &(oGradientParas.m_uiVOL[1][0]),
						&(oGradientParas.m_uiCUR[1][0]), nHarmCnt, 1);
	Gradient_NormalPara(&pDrvPara->AcPara,  &(oGradientParas.m_uiVOL[2][0]),
						&(oGradientParas.m_uiCUR[2][0]), nHarmCnt, 2);
	Gradient_FaultCalc(pDrvPara, oGradientParas);

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x309, 0);
	write(m_nfd, pDrvPara, sizeof(DrvDegressPara));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::Gradient_NormalVolt(tmt_channel *pTmt_channel, Drv_ACPara *pszDrv, int nHarm,
		int nModuleUIndex, BOOL bIsDc, int nStatus)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nChPos;
	float fAmp = 0;

	if(nHarm == 0)
	{
		bIsDc = TRUE;
	}

	long *dat;

	if(nStatus == 0)
	{
		dat = pszDrv->para[nModuleUIndex].bfChangedat;
	}
	else if(nStatus == 1)
	{
		dat = pszDrv->para[nModuleUIndex].bfFaultdat;
	}
	else
	{
		dat = pszDrv->para[nModuleUIndex].FaultBegindat;
	}

	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

	if(bIsDc)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				if(nStatus == 2 && pTmt_channel[m_nTmtPos].Ramp[0].nIndex == 0)
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[nHarm].fAmp;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[1].fAmp;
				}
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCVolToDrv(fAmp, k, nModuleUIndex, dat + nChPos);
		}

		if(nStatus == 0)
		{
			pszDrv->para[nModuleUIndex].nDWcnt = 24;
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];
			//DC
			{
				if(m_nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[0].fAmp;
				}

				nChPos = pModule->m_nChDrvPos[k];
				TransAnalogDCVolToDrv(fAmp, k, nModuleUIndex, dat + nChPos);
			}

			if(m_nTmtPos < 0)
			{
				continue;
			}

			//BASE
			{
				oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;
				TransAnalogVolToDrv(fAmp, fAngle,
									fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3);
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				int nHarmIndex = 0;
				int nHarmTotal = 0;

				for(int j = 2; j < nHarmCount; j++)
				{
					nHarmIndex = pTmt_channel[m_nTmtPos].Harm[j].nSelectIndex;

					if(nHarmIndex > 0 && nHarmIndex < 31)
					{
						oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[j];
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogVolToDrv(fAmp, fAngle,
											fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3 + nHarmIndex * 3 * CHANNEL_MAX);
						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					oTmtHarm = &pTmt_channel[m_nTmtPos].InterHarm;

					if(oTmtHarm->nSelectIndex == 1)
					{
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogVolToDrv(fAmp, fAngle,
											fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3 + (nHarmTotal + 1) * 3 * CHANNEL_MAX);
					}
				}
			}
		}

		if(nStatus == 0)
		{
			if(nHarm > 31)
			{
				nHarm = 31;
			}

			pszDrv->para[nModuleUIndex].nDWcnt = 6 + nHarm * 3 * CHANNEL_MAX;
		}
	}
}

void CSttDeviceComm::Gradient_NormalCurrent(tmt_channel *pTmt_channel, Drv_ACPara *pszDrv, int nHarm,
		int nModuleIIndex, BOOL bIsDc, int nStatus)
{
	int nModuleOffset = nModuleIIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nChPos;
	float fAmp = 0;

	if(nHarm == 0)
	{
		bIsDc = TRUE;
	}

	long *dat;

	if(nStatus == 0)
	{
		dat = pszDrv->para[nModuleOffset].bfChangedat;
	}
	else if(nStatus == 1)
	{
		dat = pszDrv->para[nModuleOffset].bfFaultdat;
	}
	else
	{
		dat = pszDrv->para[nModuleOffset].FaultBegindat;
	}

	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

	if(bIsDc)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				if(nStatus == 2 && pTmt_channel[m_nTmtPos].Ramp[0].nIndex == 0)
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[nHarm].fAmp;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[1].fAmp;
				}
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCCurToDrv(fAmp, k, nModuleIIndex, dat + nChPos);
		}

		if(nStatus == 0)
		{
			pszDrv->para[nModuleOffset].nDWcnt = 24;
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];
			//DC
			{
				if(m_nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[0].fAmp;
				}

				nChPos = pModule->m_nChDrvPos[k];
				TransAnalogDCCurToDrv(fAmp, k, nModuleIIndex, dat + nChPos);
			}

			if(m_nTmtPos < 0)
			{
				continue;
			}

			//BASE
			{
				oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;
				TransAnalogCurToDrv(fAmp, fAngle,
									fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3);
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				int nHarmIndex = 0;
				int nHarmTotal = 0;

				for(int j = 2; j < nHarmCount; j++)
				{
					nHarmIndex = pTmt_channel[m_nTmtPos].Harm[j].nSelectIndex;

					if(nHarmIndex > 0 && nHarmIndex < 31)
					{
						oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[j];
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogCurToDrv(fAmp, fAngle,
											fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3 + nHarmIndex * 3 * CHANNEL_MAX);
						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					oTmtHarm = &pTmt_channel[m_nTmtPos].InterHarm;

					if(oTmtHarm->nSelectIndex == 1)
					{
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogCurToDrv(fAmp, fAngle,
											fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3 + (nHarmTotal + 1) * 3 * CHANNEL_MAX);
					}
				}
			}
		}

		if(nStatus == 0)
		{
			if(nHarm > 31)
			{
				nHarm = 31;
			}

			pszDrv->para[nModuleOffset].nDWcnt = 6 + nHarm * 3 * CHANNEL_MAX;
		}
	}
}

void CSttDeviceComm::Gradient_NormalUI(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, Drv_ACPara *pszDrv, int nHarm,
									   int nModuleIndex, BOOL bIsDc, int nStatus)
{
	int nModuleOffset = nModuleIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nChPos;
	float fAmp = 0;

	if(nHarm == 0)
	{
		bIsDc = TRUE;
	}

	long *dat;

	if(nStatus == 0)
	{
		dat = pszDrv->para[nModuleOffset].bfChangedat;
	}
	else if(nStatus == 1)
	{
		dat = pszDrv->para[nModuleOffset].bfFaultdat;
	}
	else
	{
		dat = pszDrv->para[nModuleOffset].FaultBegindat;
	}

	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	BOOL bChanIsVolt;
	tmt_channel *pTmt_channel;
	int nChanSize = CHANNEL_MAX;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		nChanSize = 12;
	}
	else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
	{
		nChanSize = 8;
	}

	if(bIsDc)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
				bChanIsVolt = TRUE;
			}
			else
			{
				pTmt_channel = pTmt_Current;
				bChanIsVolt = FALSE;
			}

			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				if(nStatus == 2 && pTmt_channel[m_nTmtPos].Ramp[0].nIndex == 0)
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[nHarm].fAmp;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[1].fAmp;
				}
			}

			nChPos = pModule->m_nChDrvPos[k];

			if(bChanIsVolt)
			{
				TransAnalogDCUIToDrv_Volt(fAmp, k, nModuleIndex, dat + nChPos);
			}
			else
			{
				TransAnalogDCUIToDrv_Current(fAmp, k, nModuleIndex, dat + nChPos);
			}
		}

		if(nStatus == 0)
		{
			pszDrv->para[nModuleOffset].nDWcnt = nChanSize + nChanSize * 3;
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
			{
				pTmt_channel = pTmt_Volt;
				bChanIsVolt = TRUE;
			}
			else
			{
				pTmt_channel = pTmt_Current;
				bChanIsVolt = FALSE;
			}

			m_nTmtPos = pModule->m_nChTmtPos[k];
			//DC
			{
				if(m_nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[0].fAmp;
				}

				nChPos = pModule->m_nChDrvPos[k];

				if(bChanIsVolt)
				{
					TransAnalogDCUIToDrv_Volt(fAmp, k, nModuleIndex, dat + nChPos);
				}
				else
				{
					TransAnalogDCUIToDrv_Current(fAmp, k, nModuleIndex, dat + nChPos);
				}
			}

			if(m_nTmtPos < 0)
			{
				continue;
			}

			//BASE
			{
				oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(bChanIsVolt)
				{
					TransAnalogUIToDrv_Volt(fAmp, fAngle,
											fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3);
				}
				else
				{
					TransAnalogUIToDrv_Current(fAmp, fAngle,
											   fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3);
				}
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				int nHarmIndex = 0;
				int nHarmTotal = 0;

				for(int j = 2; j < nHarmCount; j++)
				{
					nHarmIndex = pTmt_channel[m_nTmtPos].Harm[j].nSelectIndex;

					if(nHarmIndex > 0 && nHarmIndex < 31)
					{
						oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[j];
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;

						if(bChanIsVolt)
						{
							TransAnalogUIToDrv_Volt(fAmp, fAngle,
													fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3 + nHarmIndex * 3 * nChanSize);
						}
						else
						{
							TransAnalogUIToDrv_Current(fAmp, fAngle,
													   fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3 + nHarmIndex * 3 * nChanSize);
						}

						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					oTmtHarm = &pTmt_channel[m_nTmtPos].InterHarm;

					if(oTmtHarm->nSelectIndex == 1)
					{
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;

						if(bChanIsVolt)
						{
							TransAnalogUIToDrv_Volt(fAmp, fAngle,
													fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3 + (nHarmTotal + 1) * 3 * nChanSize);
						}
						else
						{
							TransAnalogUIToDrv_Current(fAmp, fAngle,
													   fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3 + (nHarmTotal + 1) * 3 * nChanSize);
						}
					}
				}
			}
		}

		if(nStatus == 0)
		{
			if(nHarm > 31)
			{
				nHarm = 31;
			}

			pszDrv->para[nModuleOffset].nDWcnt = nChanSize + nHarm * 3 * nChanSize;
		}
	}
}

void CSttDeviceComm::Gradient_NormalPara(Drv_ACPara *pDrv, tmt_Channel *puData, tmt_Channel *piData, int nHarm, int nStatus)
{
	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			Gradient_NormalVolt(puData, pDrv, nHarm, nIndex, FALSE, nStatus);
		}

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			Gradient_NormalCurrent(piData, pDrv, nHarm, nIndex, FALSE, nStatus);
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			Gradient_NormalUI(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		int nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U;
		nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_I;
		nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_UI;

		if(nHarm == 0)
		{
			nHarm = 1;

			for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
			{
				if(puData[i].Ramp[0].nIndex == 0)
				{
					puData[i].Harm[1].fAmp = puData[i].Harm[0].fAmp;
				}

				puData[i].Harm[1].fFreq = 0.0f;
			}

			for(int i = 0; i < MAX_CURRENT_COUNT; i++)
			{
				if(piData[i].Ramp[0].nIndex == 0)
				{
					piData[i].Harm[1].fAmp = piData[i].Harm[0].fAmp;
				}

				piData[i].Harm[1].fFreq = 0.0f;
			}
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
		{
			BOOL bIsFT3;

			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];

				if(m_oCIEC61850CfgMngr.m_nUseSmv92 == SMVTYPE_92)
				{
					bIsFT3 = FALSE;
				}
				else
				{
					bIsFT3 = TRUE;
				}

				//不同数字板的硬件相位补偿不同
				long *pBuf;

				if(nStatus == 0)
				{
					pBuf = pDrv->para[nAnalogModuleCnt + nIndex].bfChangedat;
				}
				else if(nStatus == 1)
				{
					pBuf = pDrv->para[nAnalogModuleCnt + nIndex].bfFaultdat;
				}
				else
				{
					pBuf = pDrv->para[nAnalogModuleCnt + nIndex].FaultBegindat;
				}

				//BASE
				TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf, pModule, 1, bIsFT3);

				//Harm
				if(nHarm > 1)
				{
					BOOL bHarmValid;
					int nHarmTotal = 0;

					for(int m = 1; m < 31; m++)
					{
						bHarmValid = TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1),
									 pModule, m + 1, bIsFT3);

						if(bHarmValid)
						{
							nHarmTotal++;
						}
					}

					if(nHarmTotal < 30)
					{
						TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1), pModule, -1, bIsFT3);
					}
				}

				if(nStatus == 0)
				{
					if(nHarm > 31)
					{
						nHarm = 31;
					}

					pDrv->para[nAnalogModuleCnt + nIndex].nDWcnt = DIGITAL_CHANNEL_MAX * 3 * nHarm;
				}
			}
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_FT3 > 0)
		{
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_D;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_WEEK;

			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_FT3; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_FT3[nIndex];
				//不同数字板的硬件相位补偿不同
				long *pBuf;

				if(nStatus == 0)
				{
					pBuf = pDrv->para[nAnalogModuleCnt + nIndex].bfChangedat;
				}
				else if(nStatus == 1)
				{
					pBuf = pDrv->para[nAnalogModuleCnt + nIndex].bfFaultdat;
				}
				else
				{
					pBuf = pDrv->para[nAnalogModuleCnt + nIndex].FaultBegindat;
				}

				//BASE
				TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf, pModule, 1, TRUE);

				//Harm
				if(nHarm > 1)
				{
					BOOL bHarmValid;
					int nHarmTotal = 0;

					for(int m = 1; m < 31; m++)
					{
						bHarmValid = TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1),
									 pModule, m + 1, TRUE);

						if(bHarmValid)
						{
							nHarmTotal++;
						}
					}

					if(nHarmTotal < 30)
					{
						TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1), pModule, -1, TRUE);
					}
				}

				if(nStatus == 0)
				{
					if(nHarm > 31)
					{
						nHarm = 31;
					}

					pDrv->para[nAnalogModuleCnt + nIndex].nDWcnt = DIGITAL_CHANNEL_MAX * 3 * nHarm;
				}
			}
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_ADMU > 0)
		{
			pDrv->ADMUPara.nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_ADMU;
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];
				if(pModule == NULL)
				{
					continue;
				}

				pDrv->ADMUPara.nModule[nIndex] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				//不同数字板的硬件相位补偿不同
				long *pBuf;

				if(nStatus == 0)
				{
					pDrv->ADMUPara.para[nIndex].bfChangedat[0] = 2;
					pBuf = pDrv->ADMUPara.para[nIndex].bfChangedat + 1;
				}
				else if(nStatus == 1)
				{
					pDrv->ADMUPara.para[nIndex].bfFaultdat[0] = 2;
					pBuf = pDrv->ADMUPara.para[nIndex].bfFaultdat + 1;
				}
				else
				{
					pDrv->ADMUPara.para[nIndex].FaultBegindat[0] = 2;
					pBuf = pDrv->ADMUPara.para[nIndex].FaultBegindat + 1;
				}

				//BASE
				TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf, pModule, 1, TRUE);

				//Harm
				if(nHarm > 1)
				{
					BOOL bHarmValid;
					int nHarmTotal = 0;

					for(int m = 1; m < 31; m++)
					{
						bHarmValid = TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1),
									 pModule, m + 1, TRUE);

						if(bHarmValid)
						{
							nHarmTotal++;
						}
					}

					if(nHarmTotal < 30)
					{
						TranslateDigitalVoltCurrentBuffer(puData, piData, pBuf + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1), pModule, -1, TRUE);
					}
				}

				if(nStatus == 0)
				{
					if(nHarm > 31)
					{
						nHarm = 31;
					}

					pDrv->ADMUPara.para[nIndex].nDWcnt = 1 + DIGITAL_CHANNEL_MAX * 3 * nHarm;
				}
			}
		}
	}

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
			{
				Gradient_NormalWeek_PN_Main(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
			{
				Gradient_NormalWeek_PIA48S(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
			{
				Gradient_NormalWeek_PIA12DS(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
			{
				Gradient_NormalWeek_EVTECT(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				Gradient_NormalWeek_PNS331(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
			{
				Gradient_NormalWeek_EVTECT_Ex1(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
			{
				Gradient_NormalWeek_DC6U10V(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
			{
				Gradient_NormalWeek_DC6I20mA(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
			{
				Gradient_NormalWeek_PN_DC6U6I(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
			{
				Gradient_NormalWeek_L336D(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
			}
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			Gradient_NormalWeek_ADMU(puData, piData, pDrv, nHarm, nIndex, FALSE, nStatus);
		}
	}
}

BOOL AnalogGradientPreProcess(float &fStart, float &fEnd, float &fStep, long &nStepCnt,
							  long &nSign, long GradientType, PSTT_MODULE pModule, long nChannel, long nHarmIndex)
{
	if(GradientType == GRADIENT_AMP)
	{
		float fGearMax = stt_adj_get_ac_max_GearVal(nChannel, pModule, nHarmIndex);
		float fChMax;

		if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
		{
			fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChACMaxValue;

			if(nHarmIndex == 0)
			{
				fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_fChDCMaxValue;
			}
		}
		else
		{
			fChMax = pModule->m_oModuleAttr.m_fDefChMax;

			if(nHarmIndex == 0)
			{
				fChMax = pModule->m_oModuleAttr.m_fDefChDcMax;
			}
		}

		if(fGearMax > 0 && fChMax > 0)
		{
			fGearMax = qMin(fGearMax, fChMax);

			if(fEnd < fStart)
			{
				nSign = -1;
			}
			else
			{
				nSign = 1;
			}

			if(fStep > (fGearMax * 0.5))
			{
				fStep = fGearMax * 0.5;
			}

			float fTemp = fabs(fEnd - fStart) / fStep;
			long nTemp = (long)fTemp;

			if((fTemp - nTemp) > EPSINON)
			{
				nStepCnt = nTemp + 1;
			}
			else
			{
				nStepCnt = nTemp;
			}

			float fCoef = 1;

			if(nChannel > -1 && nChannel < pModule->m_oModuleAttr.m_nChannelNum)
			{
				STT_CHANNEL_ADJUSTS oChsAdjust = pModule->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChannel];

				if(oChsAdjust.m_pChWaveAdj != NULL)
				{
					if(nHarmIndex < oChsAdjust.nHarmCount)
					{
						STT_CHANNEL_WAVE_ADJUST oChWaveAdj = oChsAdjust.m_pChWaveAdj[nHarmIndex];

						if(oChWaveAdj.m_nGearCount <= 1)
						{
							fCoef = oChWaveAdj.m_oChGearAdj[0].m_oAdjItem.m_fCoef;
						}
						else
						{
							for(int nGearIndex = 0; nGearIndex < oChWaveAdj.m_nGearCount; nGearIndex++)
							{
								if(fabs(fEnd) <= oChWaveAdj.m_oChGearAdj[nGearIndex].m_fGearValue
										&& fabs(fStart) <= oChWaveAdj.m_oChGearAdj[nGearIndex].m_fGearValue)
								{
									fCoef = oChWaveAdj.m_oChGearAdj[nGearIndex].m_oAdjItem.m_fCoef;
									break;
								}
							}
						}
					}
				}
			}

			fStep = fStep * fCoef;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if(fEnd < fStart)
		{
			nSign = -1;
		}
		else
		{
			nSign = 1;
		}

		float fTemp = fabs(fEnd - fStart) / fStep;
		long nTemp = (long)fTemp;

		if((fTemp - nTemp) > EPSINON)
		{
			nStepCnt = nTemp + 1;
		}
		else
		{
			nStepCnt = nTemp;
		}

		return TRUE;
	}
}

int TranGradientPos(int nGradientType)
{
	int nPos = 0;

	switch(nGradientType)
	{
		case GRADIENT_AMP:
			nPos = 2;
			break;

		case GRADIENT_ANG:
			nPos = 0;
			break;

		case GRADIENT_FRE:
			nPos = 1;
			break;
	}

	return nPos;
}

void CSttDeviceComm::Gradient_FaultCalc(DrvDegressPara *pDrvData, tmt_GradientParas &oGradientParas, int nMode)
{
	m_bRampFreq = FALSE;
	//nMode==0线性模式增量更新电气量, nMode==1非线性模式全量更新电气量
	tmt_GradientProcess &oGradientProcess = CSttDeviceBase::g_pSttDeviceBase->m_oGradientProcess;
	int nCnt = 0;
	if(nMode == 1)
	{
		pDrvData->cnt = oGradientProcess.m_nStepCount;//不含初值
		nCnt = oGradientProcess.m_nStepCount + 1;//含初值
		if(nCnt > GRADIENT_MAX_COUNT)
		{
			nCnt = GRADIENT_MAX_COUNT;
		}
	}

	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	long buff[3];
	int nUTemp, nITemp;
	float fAmp, fAng, fFre;
	int nTempPos, nChPos; //nTempPos_M
	float fStart, fEnd, fStep;
	int nModuleOffset;
	long nSign;
	int nHarmIndex;
	long nStepCount;
	int nStepIndex;

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		nModuleOffset = 0;

		//Volt
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			if(nMode == 0)
			{
				for(int i = 0; i < pDrvData->AcPara.para[nIndex].nDWcnt; i++)
				{
					pDrvData->AcPara.para[nIndex].nFaultLastVal[i] = pDrvData->AcPara.para[nIndex].FaultBegindat[i];
				}

				for(int j = 0; j < m_nTmtChanNum; j++)
				{
					nChPos = pModule->m_nChDrvPos[j];
					m_nTmtPos = pModule->m_nChTmtPos[j];

					if(m_nTmtPos >= 0)
					{
						tmt_channel &uiVOL = oGradientParas.m_uiVOL[2][m_nTmtPos];

						if(uiVOL.Ramp[0].nIndex == 0)
						{
							//手动递变直流
							fStart = fabs(uiVOL.Harm[0].fAmp);
							fEnd = fabs(uiVOL.Ramp[0].fEnd);
							fStep = fabs(uiVOL.Ramp[0].fStep);
							//幅值递变
							BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
																 pModule, j, 0);

							if(bRet)
							{
								float fChMax = pModule->m_oModuleAttr.m_fChMax;
								fChMax = fChMax * 1.414;

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = nChPos;
								long nH = fStep * 32768 / fChMax;
								double fH = fStep * 32768 / fChMax;
								long nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex].nFaultChangVal[nTempPos]
									= nSign * (((nH << 16) & 0xFFFF0000) + nL);
								nH = fEnd * 32768 / fChMax;
								fH = fEnd * 32768 / fChMax;
								nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex].nFaultLastVal[nTempPos]
									= (((nH << 16) & 0xFFFF0000) + nL);
							}
						}

						if(uiVOL.Ramp[0].nIndex > 0)
						{
							nHarmIndex = uiVOL.Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								uiVOL.Harm[nHarmIndex].nSelectIndex = 0;
							}

							fStart = fabs(uiVOL.Harm[nHarmIndex].fAmp);
							fEnd = fabs(uiVOL.Ramp[0].fEnd);
							fStep = fabs(uiVOL.Ramp[0].fStep);
							//幅值递变
							BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
																 pModule, j, nHarmIndex);

							if(bRet)
							{
								float fChMax = pModule->m_oModuleAttr.m_fChMax;

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = CHANNEL_MAX + uiVOL.Harm[nHarmIndex].nSelectIndex * CHANNEL_MAX * 3 + nChPos * 3 + 2;
								long nH = fStep * 65536 / fChMax;
								double fH = fStep * 65536 / fChMax;
								long nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex].nFaultChangVal[nTempPos]
									= nSign * (((nH << 16) & 0xFFFF0000) + nL);
								long nHarm;
								//按照始值计算方式计算终值
								float fFreq = uiVOL.Harm[nHarmIndex].fFreq;

								if(fFreq <= m_nEDFre)
								{
									nHarm = 0;
								}
								else
								{
									nHarm  = (fFreq + 25) / m_nEDFre - 1;
								}

								pDrvData->AcPara.para[nIndex].nFaultLastVal[nTempPos]
									= TranslateACVoltAmp(fEnd, j, nIndex, nHarm + 1);
							}
						}

						if(uiVOL.Ramp[1].nIndex > 0)
						{
							nHarmIndex = uiVOL.Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								uiVOL.Harm[nHarmIndex].nSelectIndex = 0;
							}

							//相位递变
							fStart = uiVOL.Harm[nHarmIndex].fAngle;
							fEnd = uiVOL.Ramp[1].fEnd;
							fStep = fabs(uiVOL.Ramp[1].fStep);
							AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
													 pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = CHANNEL_MAX + uiVOL.Harm[nHarmIndex].nSelectIndex * CHANNEL_MAX * 3 + nChPos * 3;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nIndex].nFaultChangVal[nTempPos] = nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nIndex].nFaultLastVal[nTempPos] = nPh;
						}

						if(uiVOL.Ramp[2].nIndex == 1)
						{
							m_bRampFreq = TRUE;
							//单波形输出频率递变
							fStart = fabs(uiVOL.Harm[1].fFreq);
							fEnd = fabs(uiVOL.Ramp[2].fEnd);
							fStep = fabs(uiVOL.Ramp[2].fStep);
							AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
													 pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							float fFreCoef = 1;

							if(pModule != NULL)
							{
								fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
							}

							pDrvData->AcPara.para[nIndex].nFaultChangVal[CHANNEL_MAX + nChPos * 3 + 1] =
								nSign * TranslateACFre(fStep * fFreCoef);
							pDrvData->AcPara.para[nIndex].nFaultLastVal[CHANNEL_MAX + nChPos * 3 + 1] =
								TranslateACFre(fEnd * fFreCoef);
						}
					}
				}
			}
			else
			{
				for(int i = 0; i < nCnt; i++)
				{
					nUTemp = 0;

					for(int j = 0; j < m_nTmtChanNum; j++)
					{
						if(nUTemp == 12)
						{
							break;    //只支持4U3I 共7个变量
						}

						m_nTmtPos = pModule->m_nChTmtPos[j];

						if(m_nTmtPos < 0 || m_nTmtPos > 5)
						{
							continue;
						}

						if(oGradientProcess.m_nDiretionMode == 0)
						{
							nStepIndex = i;
						}
						else
						{
							nStepIndex = nCnt - 1 - i;
						}

						fAmp = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_AMP];
						fAng = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_ANG];
						fFre = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_FRE];
						memset(buff, 0, sizeof(long) * 3);
						TransAnalogVolToDrv(fAmp, fAng, fFre, j, nIndex, buff);

						if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_AMP] == 1)
						{
							nTempPos = TranGradientPos(GRADIENT_AMP);
							pDrvData->DegData[i].unit[nIndex].pos[nUTemp] = pModule->m_nChDrvPos[j] * 3 + CHANNEL_MAX;
							pDrvData->DegData[i].unit[nIndex].pos[nUTemp] += nTempPos;
							pDrvData->DegData[i].unit[nIndex].dat[nUTemp++] = buff[nTempPos];
						}

						if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_ANG] == 1)
						{
							nTempPos = TranGradientPos(GRADIENT_ANG);
							pDrvData->DegData[i].unit[nIndex].pos[nUTemp] = pModule->m_nChDrvPos[j] * 3 + CHANNEL_MAX;
							pDrvData->DegData[i].unit[nIndex].pos[nUTemp] += nTempPos;
							pDrvData->DegData[i].unit[nIndex].dat[nUTemp++] = buff[nTempPos];
						}

						if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_FRE] == 1)
						{
							nTempPos = TranGradientPos(GRADIENT_FRE);
							pDrvData->DegData[i].unit[nIndex].pos[nUTemp] = pModule->m_nChDrvPos[j] * 3 + CHANNEL_MAX;
							pDrvData->DegData[i].unit[nIndex].pos[nUTemp] += nTempPos;
							pDrvData->DegData[i].unit[nIndex].dat[nUTemp++] = buff[nTempPos];
						}
					}

					pDrvData->DegData[i].unit[nIndex].posCnt = nUTemp;
				}
			}
		}

		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;

		//Current
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			if(nMode == 0)
			{
				for(int i = 0; i < pDrvData->AcPara.para[nIndex + nModuleOffset].nDWcnt; i++)
				{
					pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[i] =
						pDrvData->AcPara.para[nIndex + nModuleOffset].FaultBegindat[i];
				}

				for(int j = 0; j < m_nTmtChanNum; j++)
				{
					nChPos = pModule->m_nChDrvPos[j];
					m_nTmtPos = pModule->m_nChTmtPos[j];

					if(m_nTmtPos >= 0)
					{
						tmt_channel &uiCUR = oGradientParas.m_uiCUR[2][m_nTmtPos];

						if(uiCUR.Ramp[0].nIndex == 0)
						{
							fStart = fabs(uiCUR.Harm[0].fAmp);
							fEnd = fabs(uiCUR.Ramp[0].fEnd);
							fStep = fabs(uiCUR.Ramp[0].fStep);
							//幅值递变
							BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
																 pModule, j, 0);

							if(bRet)
							{
								float fChMax = pModule->m_oModuleAttr.m_fChMax;
								fChMax = fChMax * 1.414;

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = nChPos;
								long nH = fStep * 32768 / fChMax;
								double fH = fStep * 32768 / fChMax;
								long nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[nTempPos]
									= nSign * (((nH << 16) & 0xFFFF0000) + nL) * (-1);
								nH = fEnd * 32768 / fChMax;
								fH = fEnd * 32768 / fChMax;
								nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[nTempPos]
									= (((nH << 16) & 0xFFFF0000) + nL) * (-1);
							}
						}

						if(uiCUR.Ramp[0].nIndex > 0)
						{
							nHarmIndex = uiCUR.Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								uiCUR.Harm[nHarmIndex].nSelectIndex = 0;
							}

							fStart = fabs(uiCUR.Harm[nHarmIndex].fAmp);
							fEnd = fabs(uiCUR.Ramp[0].fEnd);
							fStep = fabs(uiCUR.Ramp[0].fStep);
							//幅值递变
							BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
																 pModule, j, nHarmIndex);

							if(bRet)
							{
								float fChMax = pModule->m_oModuleAttr.m_fChMax;

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = CHANNEL_MAX + uiCUR.Harm[nHarmIndex].nSelectIndex * CHANNEL_MAX * 3 + nChPos * 3 + 2;
								long nH = fStep * 65536 / fChMax;
								double fH = fStep * 65536 / fChMax;
								long nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[nTempPos]
									= nSign * (((nH << 16) & 0xFFFF0000) + nL);
								long nHarm;
								//按照始值计算方式计算终值
								float fFreq = uiCUR.Harm[nHarmIndex].fFreq;

								if(fFreq <= m_nEDFre)
								{
									nHarm = 0;
								}
								else
								{
									nHarm  = (fFreq + 25) / m_nEDFre - 1;
								}

								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[nTempPos]
									= TranslateACCurrentAmp(fEnd, j, nIndex, nHarm + 1);
							}
						}

						if(uiCUR.Ramp[1].nIndex > 0)
						{
							nHarmIndex = uiCUR.Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								uiCUR.Harm[nHarmIndex].nSelectIndex = 0;
							}

							fStart = uiCUR.Harm[nHarmIndex].fAngle;
							fEnd = uiCUR.Ramp[1].fEnd;
							fStep = fabs(uiCUR.Ramp[1].fStep);
							//相位递变
							AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
													 pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = CHANNEL_MAX + uiCUR.Harm[nHarmIndex].nSelectIndex * CHANNEL_MAX * 3 + nChPos * 3;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[nTempPos]
								= nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[nTempPos]
								= nPh;
						}

						if(uiCUR.Ramp[2].nIndex == 1)
						{
							m_bRampFreq = TRUE;
							//单波形输出频率递变
							fStart = fabs(uiCUR.Harm[1].fFreq);
							fEnd = fabs(uiCUR.Ramp[2].fEnd);
							fStep = fabs(uiCUR.Ramp[2].fStep);
							AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
													 pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							float fFreCoef = 1;

							if(pModule != NULL)
							{
								fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
							}

							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[CHANNEL_MAX + nChPos * 3 + 1]
								= nSign * TranslateACFre(fStep * fFreCoef);
							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[CHANNEL_MAX + nChPos * 3 + 1]
								= TranslateACFre(fEnd * fFreCoef);
						}
					}
				}
			}
			else
			{
				for(int i = 0; i < nCnt; i++)
				{
					nITemp = 0;

					for(int j = 0; j < m_nTmtChanNum; j++)
					{
						if(nITemp == 9)
						{
							break;    //只支持4U3I 共7个变量
						}

						m_nTmtPos = pModule->m_nChTmtPos[j];

						if(m_nTmtPos < 0 || m_nTmtPos > 5)
						{
							continue;
						}

						if(oGradientProcess.m_nDiretionMode == 0)
						{
							nStepIndex = i;
						}
						else
						{
							nStepIndex = nCnt - 1 - i;
						}

						fAmp = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_AMP];
						fAng = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_ANG];
						fFre = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_FRE];
						memset(buff, 0, sizeof(long) * 3);
						TransAnalogCurToDrv(fAmp, fAng, fFre, j, nIndex, buff);

						if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_AMP] == 1)
						{
							nTempPos = TranGradientPos(GRADIENT_AMP);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp] = pModule->m_nChDrvPos[j] * 3 + CHANNEL_MAX;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nITemp++] = buff[nTempPos];
						}

						if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_ANG] == 1)
						{
							nTempPos = TranGradientPos(GRADIENT_ANG);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp] = pModule->m_nChDrvPos[j] * 3 + CHANNEL_MAX;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nITemp++] = buff[nTempPos];
						}

						if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_FRE] == 1)
						{
							nTempPos = TranGradientPos(GRADIENT_FRE);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp] = pModule->m_nChDrvPos[j] * 3 + CHANNEL_MAX;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nITemp++] = buff[nTempPos];
						}
					}

					pDrvData->DegData[i].unit[nModuleOffset + nIndex].posCnt = nITemp;
				}
			}
		}

		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
			BOOL bChanIsVolt;
			BOOL bGradient_Amp;
			BOOL bGradient_Ang;
			BOOL bGradient_Fre;
			tmt_channel *pTmt_channel;
			int nChanSize = CHANNEL_MAX;

			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
			{
				nChanSize = 12;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
			{
				nChanSize = 8;
			}

			if(nMode == 0)
			{
				for(int i = 0; i < pDrvData->AcPara.para[nIndex + nModuleOffset].nDWcnt; i++)
				{
					pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[i] =
						pDrvData->AcPara.para[nIndex + nModuleOffset].FaultBegindat[i];
				}

				for(int j = 0; j < m_nTmtChanNum; j++)
				{
					if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_VOLTAGE)
					{
						pTmt_channel = oGradientParas.m_uiVOL[2];
						bChanIsVolt = TRUE;
					}
					else
					{
						pTmt_channel = oGradientParas.m_uiCUR[2];
						bChanIsVolt = FALSE;
					}

					nChPos = pModule->m_nChDrvPos[j];
					m_nTmtPos = pModule->m_nChTmtPos[j];

					if(m_nTmtPos >= 0)
					{
						tmt_channel &Tmtui = pTmt_channel[m_nTmtPos];

						if(Tmtui.Ramp[0].nIndex == 0)
						{
							fStart = fabs(Tmtui.Harm[0].fAmp);
							fEnd = fabs(Tmtui.Ramp[0].fEnd);
							fStep = fabs(Tmtui.Ramp[0].fStep);
							//幅值递变
							BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
																 pModule, j, 0);

							if(bRet)
							{
								float fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_fChACMaxValue;
								fChMax = fChMax * 1.414;

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = nChPos;
								long nH = fStep * 32768 / fChMax;
								double fH = fStep * 32768 / fChMax;
								long nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[nTempPos]
									= nSign * (((nH << 16) & 0xFFFF0000) + nL);
								nH = fEnd * 32768 / fChMax;
								fH = fEnd * 32768 / fChMax;
								nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[nTempPos]
									= (((nH << 16) & 0xFFFF0000) + nL);
							}
						}

						if(Tmtui.Ramp[0].nIndex > 0)
						{
							nHarmIndex = Tmtui.Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								Tmtui.Harm[nHarmIndex].nSelectIndex = 0;
							}

							fStart = fabs(Tmtui.Harm[nHarmIndex].fAmp);
							fEnd = fabs(Tmtui.Ramp[0].fEnd);
							fStep = fabs(Tmtui.Ramp[0].fStep);
							//幅值递变
							BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
																 pModule, j, nHarmIndex);

							if(bRet)
							{
								float fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_fChACMaxValue;

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = nChanSize + Tmtui.Harm[nHarmIndex].nSelectIndex * nChanSize * 3 + nChPos * 3 + 2;
								long nH = fStep * 65536 / fChMax;
								double fH = fStep * 65536 / fChMax;
								long nL = (fH - nH) * 65536;
								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[nTempPos]
									= nSign * (((nH << 16) & 0xFFFF0000) + nL);
								long nFaultLastVal, nHarm;

								if(fFre <= m_nEDFre)
								{
									nHarm = 0;//0:基波
								}
								else
								{
									nHarm  = (fFre + 25) / m_nEDFre - 1;
								}

								if(bChanIsVolt)
								{
									nFaultLastVal = TranslateACUIAmp_Volt(fAmp, j, nIndex, nHarm + 1);
								}
								else
								{
									nFaultLastVal = TranslateACUIAmp_Current(fAmp, j, nIndex, nHarm + 1);
								}

								pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[nTempPos]
									= nFaultLastVal;
							}
						}

						if(Tmtui.Ramp[1].nIndex > 0)
						{
							nHarmIndex = Tmtui.Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								Tmtui.Harm[nHarmIndex].nSelectIndex = 0;
							}

							fStart = Tmtui.Harm[nHarmIndex].fAngle;
							fEnd = Tmtui.Ramp[1].fEnd;
							fStep = fabs(Tmtui.Ramp[1].fStep);
							//相位递变
							AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
													 pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = nChanSize + Tmtui.Harm[nHarmIndex].nSelectIndex * nChanSize * 3 + nChPos * 3;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[nTempPos]
								= nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[nTempPos]
								= nPh;
						}

						if(Tmtui.Ramp[2].nIndex == 1)
						{
							m_bRampFreq = TRUE;
							//单波形输出频率递变
							fStart = fabs(Tmtui.Harm[1].fFreq);
							fEnd = fabs(Tmtui.Ramp[2].fEnd);
							fStep = fabs(Tmtui.Ramp[2].fStep);
							AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
													 pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							float fFreCoef = 1;

							if(pModule != NULL)
							{
								fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;

								if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
										|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
										|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
										|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
								{
									fFreCoef = fFreCoef * 8;    //50K
								}
							}

							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultChangVal[nChanSize + nChPos * 3 + 1]
								= nSign * TranslateACFre(fStep * fFreCoef);
							pDrvData->AcPara.para[nIndex + nModuleOffset].nFaultLastVal[nChanSize + nChPos * 3 + 1]
								= TranslateACFre(fEnd * fFreCoef);
						}
					}
				}
			}
			else
			{
				int nTempUI;

				for(int i = 0; i < nCnt; i++)
				{
					nUTemp = 0;
					nITemp = 0;

					for(int j = 0; j < m_nTmtChanNum; j++)
					{
						if(nUTemp == 12)
						{
							break;    //只支持4U3I 共7个变量
						}

						if(nITemp == 9)
						{
							break;    //只支持4U3I 共7个变量
						}

						m_nTmtPos = pModule->m_nChTmtPos[j];

						if(m_nTmtPos < 0 || m_nTmtPos > 5)
						{
							continue;
						}

						if(oGradientProcess.m_nDiretionMode == 0)
						{
							nStepIndex = i;
						}
						else
						{
							nStepIndex = nCnt - 1 - i;
						}

						if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_VOLTAGE)
						{
							fAmp = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_AMP];
							fAng = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_ANG];
							fFre = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_FRE];
							bChanIsVolt = TRUE;
						}
						else
						{
							fAmp = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_AMP];
							fAng = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_ANG];
							fFre = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_FRE];
							bChanIsVolt = FALSE;
						}

						memset(buff, 0, sizeof(long) * 3);
						bGradient_Amp = FALSE;
						bGradient_Ang = FALSE;
						bGradient_Fre = FALSE;

						if(bChanIsVolt)
						{
							TransAnalogUIToDrv_Volt(fAmp, fAng, fFre, j, nIndex, buff);

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_AMP] == 1)
							{
								bGradient_Amp = TRUE;
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_ANG] == 1)
							{
								bGradient_Ang = TRUE;
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_FRE] == 1)
							{
								bGradient_Fre = TRUE;
							}
						}
						else
						{
							TransAnalogUIToDrv_Current(fAmp, fAng, fFre, j, nIndex, buff);

							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_AMP] == 1)
							{
								bGradient_Amp = TRUE;
							}

							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_ANG] == 1)
							{
								bGradient_Ang = TRUE;
							}

							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_FRE] == 1)
							{
								bGradient_Fre = TRUE;
							}
						}

						if(bGradient_Amp)
						{
							nTempPos = TranGradientPos(GRADIENT_AMP);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}

						if(bGradient_Ang)
						{
							nTempPos = TranGradientPos(GRADIENT_ANG);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}

						if(bGradient_Fre)
						{
							nTempPos = TranGradientPos(GRADIENT_FRE);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}
					}

					pDrvData->DegData[i].unit[nModuleOffset + nIndex].posCnt = nUTemp + nITemp;
				}
			}
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		int nDTempPos;
		BOOL bDC, bIsFT3;
		int nGroupIndex;
		nModuleOffset = 0;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;

		//Digtal
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
		{
			if(m_oCIEC61850CfgMngr.m_nUseSmv92 == SMVTYPE_92)
			{
				bIsFT3 = FALSE;
			}
			else
			{
				bIsFT3 = TRUE;
			}

			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			if(nMode == 1)
			{
				//volt
				for(int i = 0; i < nCnt; i++)
				{
					nUTemp = 0;

					for(int j = 0; j < 18; j++)
					{
						m_nTmtPos = pModule->m_nChTmtPos[j];

						if(m_nTmtPos < 0 || m_nTmtPos > 5)
						{
							continue;
						}

						nGroupIndex = j / 3;
						nTempPos = GetDigitalDrvPos(j) * 3;

						if(oGradientProcess.m_nDiretionMode == 0)
						{
							nStepIndex = i;
						}
						else
						{
							nStepIndex = nCnt - 1 - i;
						}

						fAmp = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_AMP];
						fAng = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_ANG];
						fFre = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_FRE];
						memset(buff, 0, sizeof(long) * 3);
						TransDigitalChannelToDrv(fAmp, fAng, fFre, nGroupIndex, buff, STT_MODULE_TYPE_VOLT, pModule, FALSE, 0);

						if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_AMP] == 1)
						{
							nDTempPos = TranGradientPos(GRADIENT_AMP);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nUTemp] = nTempPos + nDTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nUTemp++] = buff[nDTempPos];
						}

						if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_ANG] == 1)
						{
							nDTempPos = TranGradientPos(GRADIENT_ANG);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nUTemp] = nTempPos + nDTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nUTemp++] = buff[nDTempPos];
						}

						if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_FRE] == 1)
						{
							nDTempPos = TranGradientPos(GRADIENT_FRE);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nUTemp] = nTempPos + nDTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nUTemp++] = buff[nDTempPos];
						}
					}

					if(nUTemp > 12)
					{
						nUTemp = 12;
					}
					else
					{
						m_nTmtPos = pModule->m_nChTmtPos[18];

						if(m_nTmtPos > -1 && m_nTmtPos < 6)
						{
							nGroupIndex = 0;

							if(fabs(oGradientParas.m_uiVOL[2][m_nTmtPos].Harm[1].fFreq) < EPSINON)
							{
								bDC = true;
							}
							else
							{
								bDC = false;
							}

							fAmp = oGradientProcess.m_uiStepData[i].fU[m_nTmtPos][GRADIENT_AMP];
							fAng = oGradientProcess.m_uiStepData[i].fU[m_nTmtPos][GRADIENT_ANG];
							fFre = oGradientProcess.m_uiStepData[i].fU[m_nTmtPos][GRADIENT_FRE];
							memset(buff, 0, sizeof(long) * 3);
							TransDigitalChannelToDrv(fAmp, fAng, fFre, nGroupIndex, buff, STT_MODULE_TYPE_VOLT, pModule, FALSE, 0);

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_AMP] == 1)
							{
								nDTempPos = TranGradientPos(GRADIENT_AMP);
								pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nUTemp] = 9 + nDTempPos;
								pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nUTemp++] = buff[nDTempPos];
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_ANG] == 1)
							{
								nDTempPos = TranGradientPos(GRADIENT_ANG);
								pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nUTemp] = 9 + nDTempPos;
								pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nUTemp++] = buff[nDTempPos];
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_FRE] == 1)
							{
								nDTempPos = TranGradientPos(GRADIENT_FRE);
								pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nUTemp] = 9 + nDTempPos;
								pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nUTemp++] = buff[nDTempPos];
							}
						}

						if(nUTemp > 12)
						{
							nUTemp = 12;
						}
					}

					pDrvData->DegData[i].unit[nModuleOffset + nIndex].posCnt = nUTemp;
				}

				//Current
				for(int i = 0; i < nCnt; i++)
				{
					nUTemp = pDrvData->DegData[i].unit[nModuleOffset + nIndex].posCnt;
					nITemp = 0;

					for(int j = 0; j < 18; j++)
					{
						m_nTmtPos = pModule->m_nChTmtPos[j + 18 + 1];

						if(m_nTmtPos < 0 || m_nTmtPos > 5)
						{
							continue;
						}

						nGroupIndex = j / 3;
						nTempPos = GetDigitalDrvPos(j + 19) * 3;

						if(oGradientProcess.m_nDiretionMode == 0)
						{
							nStepIndex = i;
						}
						else
						{
							nStepIndex = nCnt - 1 - i;
						}

						fAmp = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_AMP];
						fAng = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_ANG];
						fFre = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_FRE];
						memset(buff, 0, sizeof(long) * 3);
						TransDigitalChannelToDrv(fAmp, fAng, fFre, nGroupIndex, buff, STT_MODULE_TYPE_CURRENT, pModule, FALSE, 0);

						if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_AMP] == 1)
						{
							nDTempPos = TranGradientPos(GRADIENT_AMP);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp + nUTemp] = nTempPos + nDTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nITemp + nUTemp] = buff[nDTempPos];
							nITemp++;
						}

						if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_ANG] == 1)
						{
							nDTempPos = TranGradientPos(GRADIENT_ANG);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp + nUTemp] = nTempPos + nDTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nITemp + nUTemp] = buff[nDTempPos];
							nITemp++;
						}

						if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_FRE] == 1)
						{
							nDTempPos = TranGradientPos(GRADIENT_FRE);
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nITemp + nUTemp] = nTempPos + nDTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nITemp + nUTemp] = buff[nDTempPos];
							nITemp++;
						}
					}

					if(nITemp > 9)
					{
						nITemp = 9;
					}

					pDrvData->DegData[i].unit[nModuleOffset + nIndex].posCnt = nITemp + nUTemp;
				}
			}
			else
			{
				for(int i = 0; i < pDrvData->AcPara.para[nModuleOffset + nIndex].nDWcnt; i++)
				{
					pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[i] =
						pDrvData->AcPara.para[nModuleOffset + nIndex].FaultBegindat[i];
				}

				tmt_channel *pChannel;

				for(int i = 0; i < DIGITAL_CHANNEL_MAX; i++)
				{
					m_nTmtPos = pModule->m_nChTmtPos[i];

					if(m_nTmtPos < 0)
					{
						continue;
					}
					else
					{
						if(i == 18 && (!bIsFT3))
						{
							pChannel = &oGradientParas.m_uiVOL[2][m_nTmtPos];

							if(fabs(pChannel->Harm[1].fFreq) < EPSINON)
							{
								bDC = true;
							}
							else
							{
								bDC = false;
							}

							nGroupIndex = 0;

							if(pChannel->Ramp[0].nIndex > 0)
							{
								nHarmIndex = pChannel->Ramp[0].nIndex;

								if(nHarmIndex == 1)
								{
									pChannel->Harm[nHarmIndex].nSelectIndex = 0;
								}

								//幅值递变
								fStart = pChannel->Harm[nHarmIndex].fAmp;
								fEnd = pChannel->Ramp[0].fEnd;
								fStep = fabs(pChannel->Ramp[0].fStep);
								DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = 11 + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3;
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos] =
									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, STT_MODULE_TYPE_VOLT, bIsFT3, m_nTmtPos);
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos] =
									TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, STT_MODULE_TYPE_VOLT, bIsFT3, m_nTmtPos);
							}

							if(pChannel->Ramp[1].nIndex > 0 && (!bDC))
							{
								nHarmIndex = pChannel->Ramp[1].nIndex;
								//相位递变
								fStart = pChannel->Harm[nHarmIndex].fAngle;
								fEnd = pChannel->Ramp[1].fEnd;
								fStep = fabs(pChannel->Ramp[1].fStep);
								DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								nTempPos = 9 + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3;
								long  nPh;
								nPh = fStep * 65536 / 360;
								nPh = nPh << 16;
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos] = nSign * nPh;
								nPh = fEnd * 65536 / 360;
								nPh = nPh << 16;
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos] = nPh;
							}

							if(pChannel->Ramp[2].nIndex == 1 && (!bDC))
							{
								nHarmIndex = pChannel->Ramp[2].nIndex;
								//单波形输出频率递变
								fStart = fabs(pChannel->Harm[1].fFreq);
								fEnd = fabs(pChannel->Ramp[2].fEnd);
								fStep = fabs(pChannel->Ramp[2].fStep);
								DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

								if(pDrvData->cnt == 0)
								{
									pDrvData->cnt = nStepCount;
								}

								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[10] =
									nSign * TranslateDigitalFre(fStep,bIsFT3);
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[10] =
									TranslateDigitalFre(fEnd,bIsFT3);
							}

							continue;
						}

						int nType;

						if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_VOLTAGE)
						{
							pChannel = &oGradientParas.m_uiVOL[2][m_nTmtPos];
							nGroupIndex = i / 3;
							nType = STT_MODULE_TYPE_VOLT;
						}
						else
						{
							pChannel = &oGradientParas.m_uiCUR[2][m_nTmtPos];
							nGroupIndex = (i - 19) / 3;
							nType = STT_MODULE_TYPE_CURRENT;
						}

						if(bIsFT3)
						{
							if(nType == STT_MODULE_TYPE_VOLT)
							{
								nTempPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nVoltDrvPos[i] - 1;
							}
							else
							{
								nTempPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[i - 19] - 1;
//								//同时计算测量电流
//								nTempPos_M = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[i - 19 + 6] - 1;
//								nTempPos_M = nTempPos_M * 3;
							}
						}
						else
						{
							nTempPos = GetDigitalDrvPos(i);
						}

						nTempPos = nTempPos * 3;

						if(pChannel->Ramp[0].nIndex == 0)
						{
							//幅值递变
							fStart = pChannel->Harm[0].fAmp;
							fEnd = pChannel->Ramp[0].fEnd;
							fStep = fabs(pChannel->Ramp[0].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 2] =
								nSign * TransDigitalChannelAmp(fStep, nGroupIndex, TRUE, nType, bIsFT3, m_nTmtPos);
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 2] =
								TransDigitalChannelAmp(fEnd, nGroupIndex, TRUE, nType, bIsFT3, m_nTmtPos);
//							if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//							{
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_M + 2] =
//									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, TRUE, STT_MODULE_TYPE_CURRENT, bIsFT3, m_nTmtPos + 6);
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_M + 2] =
//									TransDigitalChannelAmp(fEnd, nGroupIndex, TRUE, STT_MODULE_TYPE_CURRENT, bIsFT3, m_nTmtPos + 6);
//							}
						}

						if(pChannel->Ramp[0].nIndex > 0)
						{
							nHarmIndex = pChannel->Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								pChannel->Harm[nHarmIndex].nSelectIndex = 0;
							}

							//幅值递变
							fStart = pChannel->Harm[nHarmIndex].fAmp;
							fEnd = pChannel->Ramp[0].fEnd;
							fStep = fabs(pChannel->Ramp[0].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							if(nHarmIndex > 1) //HarmTest
							{
								nTempPos += pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3 + 2;
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos] =
									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, FALSE, nType, bIsFT3, m_nTmtPos);
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos] =
									TransDigitalChannelAmp(fEnd, nGroupIndex, FALSE, nType, bIsFT3, m_nTmtPos);
							}
							else if(nHarmIndex == 1) //ManualTest
							{
								bDC = FALSE;

								if(fabs(pChannel->Harm[1].fFreq) < EPSINON)
								{
									bDC = TRUE;
								}

								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 2] =
									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, nType, bIsFT3, m_nTmtPos);
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 2] =
									TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, nType, bIsFT3, m_nTmtPos);
//								if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//								{
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_M + 2] =
//										nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, STT_MODULE_TYPE_CURRENT, bIsFT3, m_nTmtPos + 6);
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_M + 2] =
//										TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, STT_MODULE_TYPE_CURRENT, bIsFT3, m_nTmtPos + 6);
//								}
							}
						}

						if(pChannel->Ramp[1].nIndex > 0 && (!oGradientParas.m_bManuDc))
						{
							nHarmIndex = pChannel->Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								pChannel->Harm[nHarmIndex].nSelectIndex = 0;
							}

							//相位递变
							fStart = pChannel->Harm[nHarmIndex].fAngle;
							fEnd = pChannel->Ramp[1].fEnd;
							fStep = fabs(pChannel->Ramp[1].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							int nTempPos_Harm = nTempPos + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_Harm] = nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_Harm] = nPh;
//							if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//							{
//								int nTempPos_Harm_M = nTempPos_M + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3;
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_Harm_M] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_Harm];
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_Harm_M] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_Harm];
//							}
						}

						if(pChannel->Ramp[2].nIndex == 1 && (!oGradientParas.m_bManuDc))
						{
							//单波形输出频率递变
							fStart = fabs(pChannel->Harm[1].fFreq);
							fEnd = fabs(pChannel->Ramp[2].fEnd);
							fStep = fabs(pChannel->Ramp[2].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 1] =
								nSign * TranslateDigitalFre(fStep,bIsFT3);
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 1] =
								TranslateDigitalFre(fEnd,bIsFT3);
//							if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//							{
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_M + 1] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 1];
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_M + 1] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 1];
//							}
						}
					}
				}
			}
		}

		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_WEEK;

		//FT3
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_FT3; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_FT3[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			nGroupIndex = 0;

			//普通递变
			if(nMode == 0)
			{
				for(int i = 0; i < pDrvData->AcPara.para[nModuleOffset + nIndex].nDWcnt; i++)
				{
					pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[i] =
						pDrvData->AcPara.para[nModuleOffset + nIndex].FaultBegindat[i];
				}

				tmt_channel *pChannel;

				for(int i = 0; i < DIGITAL_CHANNEL_MAX; i++)
				{
					m_nTmtPos = pModule->m_nChTmtPos[i];

					if(m_nTmtPos < 0)
					{
						continue;
					}
					else
					{
						int nType;

						if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_VOLTAGE)
						{
							pChannel = &oGradientParas.m_uiVOL[2][m_nTmtPos];
							nType = STT_MODULE_TYPE_VOLT;
						}
						else
						{
							pChannel = &oGradientParas.m_uiCUR[2][m_nTmtPos];
							nType = STT_MODULE_TYPE_CURRENT;
						}

						if(nType == STT_MODULE_TYPE_VOLT)
						{
							nTempPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nVoltDrvPos[i] - 1;
						}
						else
						{
							nTempPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[i - 19] - 1;
//							//同时计算测量电流
//							nTempPos_M = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[i - 19 + 6] - 1;
//							nTempPos_M = nTempPos_M * 3;
						}

						nTempPos = nTempPos * 3;

						if(pChannel->Ramp[0].nIndex == 0)
						{
							//幅值递变
							fStart = pChannel->Harm[0].fAmp;
							fEnd = pChannel->Ramp[0].fEnd;
							fStep = fabs(pChannel->Ramp[0].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							if(fStart < 0)
							{
								nSign = nSign * (-1);    //始值已经通过相位270换算过，此处需要处理
							}

							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 2] =
								nSign * TransDigitalChannelAmp(fStep, nGroupIndex, TRUE, nType, TRUE, m_nTmtPos);
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 2] =
								TransDigitalChannelAmp(fEnd, nGroupIndex, TRUE, nType, TRUE, m_nTmtPos);
//							if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//							{
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_M + 2] =
//									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, TRUE, STT_MODULE_TYPE_CURRENT, TRUE, m_nTmtPos + 6);
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_M + 2] =
//									TransDigitalChannelAmp(fEnd, nGroupIndex, TRUE, STT_MODULE_TYPE_CURRENT, TRUE, m_nTmtPos + 6);
//							}
						}

						if(pChannel->Ramp[0].nIndex > 0)
						{
							nHarmIndex = pChannel->Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								pChannel->Harm[nHarmIndex].nSelectIndex = 0;
							}

							//幅值递变
							fStart = pChannel->Harm[nHarmIndex].fAmp;
							fEnd = pChannel->Ramp[0].fEnd;
							fStep = fabs(pChannel->Ramp[0].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							if(nHarmIndex > 1) //HarmTest
							{
								int nTempPos_Harm = nTempPos + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3 + 2;
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_Harm] =
									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, FALSE, nType, TRUE, m_nTmtPos);
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_Harm] =
									TransDigitalChannelAmp(fEnd, nGroupIndex, FALSE, nType, TRUE, m_nTmtPos);
							}
							else if(nHarmIndex == 1) //ManualTest
							{
								bDC = FALSE;

								if(fabs(pChannel->Harm[1].fFreq) < EPSINON)
								{
									bDC = TRUE;
								}

								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 2] =
									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, nType, TRUE, m_nTmtPos);
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 2] =
									TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, nType, TRUE, m_nTmtPos);
//								if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//								{
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_M + 2] =
//										nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, STT_MODULE_TYPE_CURRENT, TRUE, m_nTmtPos + 6);
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_M + 2] =
//										TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, STT_MODULE_TYPE_CURRENT, TRUE, m_nTmtPos + 6);
//								}
							}
						}

						if(pChannel->Ramp[1].nIndex > 0 && (!oGradientParas.m_bManuDc))
						{
							nHarmIndex = pChannel->Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								pChannel->Harm[nHarmIndex].nSelectIndex = 0;
							}

							//相位递变
							fStart = pChannel->Harm[nHarmIndex].fAngle;
							fEnd = pChannel->Ramp[1].fEnd;
							fStep = fabs(pChannel->Ramp[1].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							int nTempPos_Harm = nTempPos + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_Harm] = nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_Harm] = nPh;
//							if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//							{
//								int nTempPos_Harm_M = nTempPos_M + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3;
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_Harm_M] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_Harm];
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_Harm_M] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_Harm];
//							}
						}

						if(pChannel->Ramp[2].nIndex == 1 && (!oGradientParas.m_bManuDc))
						{
							//单波形输出频率递变
							fStart = fabs(pChannel->Harm[1].fFreq);
							fEnd = fabs(pChannel->Ramp[2].fEnd);
							fStep = fabs(pChannel->Ramp[2].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 1] =
								nSign * TranslateDigitalFre(fStep,bIsFT3);
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 1] =
								TranslateDigitalFre(fEnd,bIsFT3);
//							if(m_nTmtPos > 11 && nType == STT_MODULE_TYPE_CURRENT)
//							{
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos_M + 1] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos + 1];
//								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos_M + 1] =
//									pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos + 1];
//							}
						}
					}
				}
			}
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			nGroupIndex = 0;

			//普通递变
			if(nMode == 0)
			{
				for(int i = 0; i < pDrvData->AcPara.ADMUPara.para[nIndex].nDWcnt; i++)
				{
					pDrvData->AcPara.ADMUPara.para[nIndex].nFaultLastVal[i] =
						pDrvData->AcPara.ADMUPara.para[nIndex].FaultBegindat[i];
				}

				tmt_channel *pChannel;

				for(int i = 0; i < DIGITAL_CHANNEL_MAX; i++)
				{
					m_nTmtPos = pModule->m_nChTmtPos[i];

					if(m_nTmtPos < 0)
					{
						continue;
					}
					else
					{
						int nType;

						if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_VOLTAGE)
						{
							pChannel = &oGradientParas.m_uiVOL[2][m_nTmtPos];
							nType = STT_MODULE_TYPE_VOLT;
						}
						else
						{
							pChannel = &oGradientParas.m_uiCUR[2][m_nTmtPos];
							nType = STT_MODULE_TYPE_CURRENT;
						}

						if(nType == STT_MODULE_TYPE_VOLT)
						{
							nTempPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nVoltDrvPos[i] - 1;
						}
						else
						{
							nTempPos = m_oCIEC61850CfgMngr.m_p6044MngrBase->m_nCurrDrvPos[i - 19] - 1;
						}

						nTempPos = nTempPos * 3 + 1;

						if(pChannel->Ramp[0].nIndex == 0)
						{
							//幅值递变
							fStart = pChannel->Harm[0].fAmp;
							fEnd = pChannel->Ramp[0].fEnd;
							fStep = fabs(pChannel->Ramp[0].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							if(fStart < 0)
							{
								nSign = nSign * (-1);    //始值已经通过相位270换算过，此处需要处理
							}

							pDrvData->AcPara.ADMUPara.para[nIndex].nFaultChangVal[nTempPos + 2] =
								nSign * TransDigitalChannelAmp(fStep, nGroupIndex, TRUE, nType, TRUE, m_nTmtPos);
							pDrvData->AcPara.ADMUPara.para[nIndex].nFaultLastVal[nTempPos + 2] =
								TransDigitalChannelAmp(fEnd, nGroupIndex, TRUE, nType, TRUE, m_nTmtPos);
						}

						if(pChannel->Ramp[0].nIndex > 0)
						{
							nHarmIndex = pChannel->Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								pChannel->Harm[nHarmIndex].nSelectIndex = 0;
							}

							//幅值递变
							fStart = pChannel->Harm[nHarmIndex].fAmp;
							fEnd = pChannel->Ramp[0].fEnd;
							fStep = fabs(pChannel->Ramp[0].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							if(nHarmIndex > 1) //HarmTest
							{
								int nTempPos_Harm = nTempPos + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3 + 2;
								pDrvData->AcPara.ADMUPara.para[nIndex].nFaultChangVal[nTempPos_Harm] =
									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, FALSE, nType, TRUE, m_nTmtPos);
								pDrvData->AcPara.ADMUPara.para[nIndex].nFaultLastVal[nTempPos_Harm] =
									TransDigitalChannelAmp(fEnd, nGroupIndex, FALSE, nType, TRUE, m_nTmtPos);
							}
							else if(nHarmIndex == 1) //ManualTest
							{
								bDC = FALSE;

								if(fabs(pChannel->Harm[1].fFreq) < EPSINON)
								{
									bDC = TRUE;
								}

								pDrvData->AcPara.ADMUPara.para[nIndex].nFaultChangVal[nTempPos + 2] =
									nSign * TransDigitalChannelAmp(fStep, nGroupIndex, bDC, nType, TRUE, m_nTmtPos);
								pDrvData->AcPara.ADMUPara.para[nIndex].nFaultLastVal[nTempPos + 2] =
									TransDigitalChannelAmp(fEnd, nGroupIndex, bDC, nType, TRUE, m_nTmtPos);
							}
						}

						if(pChannel->Ramp[1].nIndex > 0 && (!oGradientParas.m_bManuDc))
						{
							nHarmIndex = pChannel->Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								pChannel->Harm[nHarmIndex].nSelectIndex = 0;
							}

							//相位递变
							fStart = pChannel->Harm[nHarmIndex].fAngle;
							fEnd = pChannel->Ramp[1].fEnd;
							fStep = fabs(pChannel->Ramp[1].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							int nTempPos_Harm = nTempPos + pChannel->Harm[nHarmIndex].nSelectIndex * DIGITAL_CHANNEL_MAX * 3;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.ADMUPara.para[nIndex].nFaultChangVal[nTempPos_Harm] = nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.ADMUPara.para[nIndex].nFaultLastVal[nTempPos_Harm] = nPh;
						}

						if(pChannel->Ramp[2].nIndex == 1 && (!oGradientParas.m_bManuDc))
						{
							//单波形输出频率递变
							fStart = fabs(pChannel->Harm[1].fFreq);
							fEnd = fabs(pChannel->Ramp[2].fEnd);
							fStep = fabs(pChannel->Ramp[2].fStep);
							DigitalGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							pDrvData->AcPara.ADMUPara.para[nIndex].nFaultChangVal[nTempPos + 1] =
								nSign * TranslateDigitalFre(fStep,bIsFT3);
							pDrvData->AcPara.ADMUPara.para[nIndex].nFaultLastVal[nTempPos + 1] =
								TranslateDigitalFre(fEnd,bIsFT3);
						}
					}
				}
			}
		}
	}

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		nModuleOffset = 0;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_D;
		BOOL bChanIsVolt;
		BOOL bGradient_Amp;
		BOOL bGradient_Ang;
		BOOL bGradient_Fre;
		tmt_channel *pTmt_channel;
		long nChanSize  = 12;
		float fWeekPT;

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				nChanSize = 8;
			}
			else
			{
				nChanSize  = 12;
			}

			if(nMode == 0)
			{
				for(int i = 0; i < pDrvData->AcPara.para[nModuleOffset + nIndex].nDWcnt; i++)
				{
					pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[i] = pDrvData->AcPara.para[nModuleOffset + nIndex].FaultBegindat[i];
				}

				for(int j = 0; j < m_nTmtChanNum; j++)
				{
					nChPos = pModule->m_nChDrvPos[j];
					m_nTmtPos = pModule->m_nChTmtPos[j];
					fWeekPT = pModule->m_fChTmtCoef[j];

					if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_VOLTAGE)
					{
						pTmt_channel = oGradientParas.m_uiVOL[2];
					}
					else
					{
						pTmt_channel = oGradientParas.m_uiCUR[2];
					}

					if(m_nTmtPos >= 0)
					{
						tmt_channel &Tmtui = pTmt_channel[m_nTmtPos];

						if(Tmtui.Ramp[0].nIndex == 0)
						{
							//手动递变直流
							fStart = fabs(Tmtui.Harm[0].fAmp);
							fEnd = fabs(Tmtui.Ramp[0].fEnd);
							fStep = fabs(Tmtui.Ramp[0].fStep);
							//幅值递变
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
												   pModule, j, 0);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = nChPos;
							float fChMax = 20;

							if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
							{
								if(j < 4)
								{
									//Volt
									if(j == 3)
									{
										fChMax = 8.0;
									}
									else
									{
										fChMax = 4.0;
									}
								}
								else
								{
									//Current
									if(j == 7)
									{
										fChMax = 4;
									}
									else
									{
										fChMax = 20;
									}
								}

								fChMax = fChMax * 1.1;
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
							{
								if(j < 8)
								{
									//Volt
									fChMax = 10.0;
								}
								else
								{
									//Current
									fChMax = 20;
								}

								fChMax = fChMax * 1.2;
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
							{
								fChMax = 7.07;
							}

							if(fWeekPT > EPSINON)
							{
								fStep = fStep / fWeekPT;
							}
							else
							{
								fStep = 0;
							}

							fChMax = fChMax * 1.414;
							long nH = fStep * 32768 / fChMax;
							double fH = fStep * 32768 / fChMax;
							long nL = (fH - nH) * 65536;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos]
								= nSign * (((nH << 16) & 0xFFFF0000) + nL);

							if(fWeekPT > EPSINON)
							{
								fEnd = fEnd / fWeekPT;
							}
							else
							{
								fEnd = 0;
							}

//							nH = fEnd * 32768 / fChMax;
//							fH = fEnd * 32768 / fChMax;
//							nL = (fH - nH) * 65536;
//							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos]
//								= (((nH << 16) & 0xFFFF0000) + nL);
							if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
							{
								long *pData = &pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos];
								TransAnalogDCToDrv_Week_PNS331(fEnd, j, nIndex, pData);
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
							{
								long *pData = &pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos];
								TransAnalogDCToDrv_Week_L336D(fEnd, j, nIndex, pData);
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
							{
								long *pData = &pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos];
								TransAnalogDCToDrv_Week_PIA48S(fEnd, j, nIndex, pData);
							}
						}

						if(Tmtui.Ramp[0].nIndex > 0)
						{
							nHarmIndex = Tmtui.Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								Tmtui.Harm[nHarmIndex].nSelectIndex = 0;
							}

							fStart = fabs(Tmtui.Harm[nHarmIndex].fAmp);
							fEnd = fabs(Tmtui.Ramp[0].fEnd);
							fStep = fabs(Tmtui.Ramp[0].fStep);
							//幅值递变
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
												   pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = nChanSize + Tmtui.Harm[nHarmIndex].nSelectIndex * nChanSize * 3 + nChPos * 3 + 2;
							float fChMax = 20;

							if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
							{
								if(j < 4)
								{
									//Volt
									if(j == 3)
									{
										fChMax = 8.0;
									}
									else
									{
										fChMax = 4.0;
									}
								}
								else
								{
									//Current
									if(j == 7)
									{
										fChMax = 4;
									}
									else
									{
										fChMax = 20;
									}
								}

								fChMax = fChMax * 1.1;
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
							{
								if(j < 8)
								{
									//Volt
									fChMax = 10.0;
								}
								else
								{
									//Current
									fChMax = 20;
								}

								fChMax = fChMax * 1.2;
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
							{
								fChMax = 7.07;
							}

							if(fWeekPT > EPSINON)
							{
								fStep = fStep / fWeekPT;
							}
							else
							{
								fStep = 0;
							}

							long nH = fStep * 65536 / fChMax;
							double fH = fStep * 65536 / fChMax;
							long nL = (fH - nH) * 65536;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos]
								= nSign * (((nH << 16) & 0xFFFF0000) + nL);
							long nHarm;
							//按照始值计算方式计算终值
							float fFreq = Tmtui.Harm[nHarmIndex].fFreq;

							if(fFreq <= m_nEDFre)
							{
								nHarm = 0;
							}
							else
							{
								nHarm  = (fFreq + 25) / m_nEDFre - 1;
							}

							if(fWeekPT > EPSINON)
							{
								fEnd = fEnd / fWeekPT;
							}
							else
							{
								fEnd = 0;
							}

							if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
							{
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos]
									= TranslateACAmp_Week_PNS331(fEnd, j, nIndex, nHarm + 1);
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
							{
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos]
									= TranslateACAmp_Week_L336D(fEnd, j, nIndex, nHarm + 1);
							}
							else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
							{
								pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos]
									= TranslateACAmp_Week_PIA48S(fEnd, j, nIndex, nHarm + 1);
							}
						}

						if(Tmtui.Ramp[1].nIndex > 0)
						{
							nHarmIndex = Tmtui.Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								Tmtui.Harm[nHarmIndex].nSelectIndex = 0;
							}

							//相位递变
							fStart = Tmtui.Harm[nHarmIndex].fAngle;
							fEnd = Tmtui.Ramp[1].fEnd;
							fStep = fabs(Tmtui.Ramp[1].fStep);
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
												   pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = nChanSize + Tmtui.Harm[nHarmIndex].nSelectIndex * nChanSize * 3 + nChPos * 3;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos] = nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos] = nPh;
						}

						if(Tmtui.Ramp[2].nIndex == 1)
						{
							//单波形输出频率递变
							fStart = fabs(Tmtui.Harm[1].fFreq);
							fEnd = fabs(Tmtui.Ramp[2].fEnd);
							fStep = fabs(Tmtui.Ramp[2].fStep);
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
												   pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							float fFreCoef = 1;

							if(pModule != NULL)
							{
								fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
							}

							if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331
									|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
							{
								fFreCoef = fFreCoef * 8;
							}

							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nChanSize + nChPos * 3 + 1] =
								nSign * TranslateACFre(fStep * fFreCoef);
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nChanSize + nChPos * 3 + 1] =
								TranslateACFre(fEnd * fFreCoef);
						}
					}
				}
			}
			else
			{
				int nTempUI;

				for(int i = 0; i < nCnt; i++)
				{
					nUTemp = 0;
					nITemp = 0;

					for(int j = 0; j < m_nTmtChanNum; j++)
					{
						if(nUTemp == 12)
						{
							break;    //只支持4U3I 共7个变量
						}

						if(nITemp == 9)
						{
							break;    //只支持4U3I 共7个变量
						}

						m_nTmtPos = pModule->m_nChTmtPos[j];
						fWeekPT = pModule->m_fChTmtCoef[j];

						if(m_nTmtPos < 0 || m_nTmtPos > 5)
						{
							continue;
						}

						if(oGradientProcess.m_nDiretionMode == 0)
						{
							nStepIndex = i;
						}
						else
						{
							nStepIndex = nCnt - 1 - i;
						}

						if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_VOLTAGE)
						{
							fAmp = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_AMP];
							fAng = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_ANG];
							fFre = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_FRE];
							bChanIsVolt = TRUE;
						}
						else
						{
							fAmp = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_AMP];
							fAng = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_ANG];
							fFre = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_FRE];
							bChanIsVolt = FALSE;
						}

						memset(buff, 0, sizeof(long) * 3);
						bGradient_Amp = FALSE;
						bGradient_Ang = FALSE;
						bGradient_Fre = FALSE;

						if(fWeekPT > EPSINON)
						{
							fAmp = fAmp / fWeekPT;
						}
						else
						{
							fAmp = 0;
						}

						if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
						{
							TransAnalogToDrv_Week_PNS331(fAmp, fAng, fFre, j, nIndex, buff);
						}
						else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
						{
							TransAnalogToDrv_Week_L336D(fAmp, fAng, fFre, j, nIndex, buff);
						}

						if(bChanIsVolt)
						{
							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_AMP] == 1)
							{
								bGradient_Amp = TRUE;
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_ANG] == 1)
							{
								bGradient_Ang = TRUE;
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_FRE] == 1)
							{
								bGradient_Fre = TRUE;
							}
						}
						else
						{
							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_AMP] == 1)
							{
								bGradient_Amp = TRUE;
							}

							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_ANG] == 1)
							{
								bGradient_Ang = TRUE;
							}

							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_FRE] == 1)
							{
								bGradient_Fre = TRUE;
							}
						}

						if(bGradient_Amp)
						{
							nTempPos = TranGradientPos(GRADIENT_AMP);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}

						if(bGradient_Ang)
						{
							nTempPos = TranGradientPos(GRADIENT_ANG);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}

						if(bGradient_Fre)
						{
							nTempPos = TranGradientPos(GRADIENT_FRE);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}
					}

					pDrvData->DegData[i].unit[nModuleOffset + nIndex].posCnt = nUTemp + nITemp;
				}
			}
		}

		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_FT3;
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			nChanSize = 8;
			if(nMode == 0)
			{
				for(int i = 0; i < pDrvData->AcPara.para[nModuleOffset + nIndex].nDWcnt; i++)
				{
					pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[i]
							= pDrvData->AcPara.para[nModuleOffset + nIndex].FaultBegindat[i];
				}

				for(int j = 0; j < m_nTmtChanNum; j++)
				{
					nChPos = pModule->m_nChDrvPos[j];
					m_nTmtPos = pModule->m_nChTmtPos[j];
					fWeekPT = pModule->m_fChTmtCoef[j];

					if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_VOLTAGE)
					{
						pTmt_channel = oGradientParas.m_uiVOL[2];
					}
					else
					{
						pTmt_channel = oGradientParas.m_uiCUR[2];
					}

					if(m_nTmtPos >= 0)
					{
						tmt_channel &Tmtui = pTmt_channel[m_nTmtPos];

						if(Tmtui.Ramp[0].nIndex == 0)
						{
							//手动递变直流
							fStart = fabs(Tmtui.Harm[0].fAmp);
							fEnd = fabs(Tmtui.Ramp[0].fEnd);
							fStep = fabs(Tmtui.Ramp[0].fStep);
							//幅值递变
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
												   pModule, j, 0);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = nChPos + 1;
							float fChMax = 20;

							if(j < 4)
							{
								//Volt
								if(j == 3)
								{
									fChMax = 7.8;
								}
								else
								{
									fChMax = 3.8;
								}
							}
							else
							{
								//Current
								if(j == 7)
								{
									fChMax = 4;
								}
								else
								{
									fChMax = 20;
								}
							}
							fChMax = fChMax*1.2;

							if(fWeekPT > EPSINON)
							{
								fStep = fStep / fWeekPT;
							}
							else
							{
								fStep = 0;
							}

							fChMax = fChMax * 1.414;
							long nH = fStep * 32768 / fChMax;
							double fH = fStep * 32768 / fChMax;
							long nL = (fH - nH) * 65536;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos]
								= nSign * (((nH << 16) & 0xFFFF0000) + nL);

							if(fWeekPT > EPSINON)
							{
								fEnd = fEnd / fWeekPT;
							}
							else
							{
								fEnd = 0;
							}

							long *pData = &pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos];
							TransAnalogDCToDrv_Week_ADMU(fEnd, j, nIndex, pData);
						}

						if(Tmtui.Ramp[0].nIndex > 0)
						{
							nHarmIndex = Tmtui.Ramp[0].nIndex;

							if(nHarmIndex == 1)
							{
								Tmtui.Harm[nHarmIndex].nSelectIndex = 0;
							}

							fStart = fabs(Tmtui.Harm[nHarmIndex].fAmp);
							fEnd = fabs(Tmtui.Ramp[0].fEnd);
							fStep = fabs(Tmtui.Ramp[0].fStep);
							//幅值递变
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
												   pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = nChanSize + Tmtui.Harm[nHarmIndex].nSelectIndex * nChanSize * 3 + nChPos * 3 + 2;
							nTempPos += 1;
							float fChMax = 20;

							if(j < 4)
							{
								//Volt
								if(j == 3)
								{
									fChMax = 7.8;
								}
								else
								{
									fChMax = 3.8;
								}
							}
							else
							{
								//Current
								if(j == 7)
								{
									fChMax = 4;
								}
								else
								{
									fChMax = 20;
								}
							}
							fChMax = fChMax*1.2;

							if(fWeekPT > EPSINON)
							{
								fStep = fStep / fWeekPT;
							}
							else
							{
								fStep = 0;
							}

							long nH = fStep * 65536 / fChMax;
							double fH = fStep * 65536 / fChMax;
							long nL = (fH - nH) * 65536;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos]
								= nSign * (((nH << 16) & 0xFFFF0000) + nL);
							long nHarm;
							//按照始值计算方式计算终值
							float fFreq = Tmtui.Harm[nHarmIndex].fFreq;

							if(fFreq <= m_nEDFre)
							{
								nHarm = 0;
							}
							else
							{
								nHarm  = (fFreq + 25) / m_nEDFre - 1;
							}

							if(fWeekPT > EPSINON)
							{
								fEnd = fEnd / fWeekPT;
							}
							else
							{
								fEnd = 0;
							}

							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos]
								= TranslateACAmp_Week_ADMU(fEnd, j, nIndex, nHarm + 1);
						}

						if(Tmtui.Ramp[1].nIndex > 0)
						{
							nHarmIndex = Tmtui.Ramp[1].nIndex;

							if(nHarmIndex == 1)
							{
								Tmtui.Harm[nHarmIndex].nSelectIndex = 0;
							}

							//相位递变
							fStart = Tmtui.Harm[nHarmIndex].fAngle;
							fEnd = Tmtui.Ramp[1].fEnd;
							fStep = fabs(Tmtui.Ramp[1].fStep);
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
												   pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							nTempPos = nChanSize + Tmtui.Harm[nHarmIndex].nSelectIndex * nChanSize * 3 + nChPos * 3;
							nTempPos += 1;
							long  nPh;
							nPh = fStep * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos] = nSign * nPh;
							nPh = fEnd * 65536 / 360;
							nPh = nPh << 16;
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos] = nPh;
						}

						if(Tmtui.Ramp[2].nIndex == 1)
						{
							//单波形输出频率递变
							fStart = fabs(Tmtui.Harm[1].fFreq);
							fEnd = fabs(Tmtui.Ramp[2].fEnd);
							fStep = fabs(Tmtui.Ramp[2].fStep);
							WeekGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
												   pModule, j, nHarmIndex);

							if(pDrvData->cnt == 0)
							{
								pDrvData->cnt = nStepCount;
							}

							float fFreCoef = 1;

							if(pModule != NULL)
							{
								fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
							}
							fFreCoef = fFreCoef * 8;
							nTempPos = nChanSize + nChPos * 3 + 1;
							nTempPos += 1;

							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultChangVal[nTempPos] =
								nSign * TranslateACFre(fStep * fFreCoef);
							pDrvData->AcPara.para[nModuleOffset + nIndex].nFaultLastVal[nTempPos] =
								TranslateACFre(fEnd * fFreCoef);
						}
					}
				}
			}
			else
			{
				int nTempUI;

				for(int i = 0; i < nCnt; i++)
				{
					nUTemp = 0;
					nITemp = 0;

					for(int j = 0; j < m_nTmtChanNum; j++)
					{
						if(nUTemp == 12)
						{
							break;    //只支持4U3I 共7个变量
						}

						if(nITemp == 9)
						{
							break;    //只支持4U3I 共7个变量
						}

						m_nTmtPos = pModule->m_nChTmtPos[j];
						fWeekPT = pModule->m_fChTmtCoef[j];

						if(m_nTmtPos < 0 || m_nTmtPos > 5)
						{
							continue;
						}

						if(oGradientProcess.m_nDiretionMode == 0)
						{
							nStepIndex = i;
						}
						else
						{
							nStepIndex = nCnt - 1 - i;
						}

						if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[j].m_nEeType == STT_CH_EETYPE_VOLTAGE)
						{
							fAmp = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_AMP];
							fAng = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_ANG];
							fFre = oGradientProcess.m_uiStepData[nStepIndex].fU[m_nTmtPos][GRADIENT_FRE];
							bChanIsVolt = TRUE;
						}
						else
						{
							fAmp = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_AMP];
							fAng = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_ANG];
							fFre = oGradientProcess.m_uiStepData[nStepIndex].fI[m_nTmtPos][GRADIENT_FRE];
							bChanIsVolt = FALSE;
						}

						memset(buff, 0, sizeof(long) * 3);
						bGradient_Amp = FALSE;
						bGradient_Ang = FALSE;
						bGradient_Fre = FALSE;

						if(fWeekPT > EPSINON)
						{
							fAmp = fAmp / fWeekPT;
						}
						else
						{
							fAmp = 0;
						}

						TransAnalogToDrv_Week_ADMU(fAmp, fAng, fFre, j, nIndex, buff);

						if(bChanIsVolt)
						{
							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_AMP] == 1)
							{
								bGradient_Amp = TRUE;
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_ANG] == 1)
							{
								bGradient_Ang = TRUE;
							}

							if(oGradientProcess.m_bUChange[m_nTmtPos][GRADIENT_FRE] == 1)
							{
								bGradient_Fre = TRUE;
							}
						}
						else
						{
							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_AMP] == 1)
							{
								bGradient_Amp = TRUE;
							}

							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_ANG] == 1)
							{
								bGradient_Ang = TRUE;
							}

							if(oGradientProcess.m_bIChange[m_nTmtPos][GRADIENT_FRE] == 1)
							{
								bGradient_Fre = TRUE;
							}
						}

						if(bGradient_Amp)
						{
							nTempPos = TranGradientPos(GRADIENT_AMP);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize + 1;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}

						if(bGradient_Ang)
						{
							nTempPos = TranGradientPos(GRADIENT_ANG);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize + 1;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}

						if(bGradient_Fre)
						{
							nTempPos = TranGradientPos(GRADIENT_FRE);
							nTempUI = nUTemp + nITemp;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] = pModule->m_nChDrvPos[j] * 3 + nChanSize + 1;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].pos[nTempUI] += nTempPos;
							pDrvData->DegData[i].unit[nModuleOffset + nIndex].dat[nTempUI] = buff[nTempPos];

							if(bChanIsVolt)
							{
								nUTemp++;
							}
							else
							{
								nITemp++;
							}
						}
					}

					pDrvData->DegData[i].unit[nModuleOffset + nIndex].posCnt = nUTemp + nITemp;
				}
			}
		}
	}

	if(m_bRampFreq)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x110, 0);//递变频率时，自动关闭秒同步
		g_oDrvMutex.unlock();
	}

	CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas.m_nStepCnt = pDrvData->cnt;
	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("StepCount=%d"), pDrvData->cnt);
}

void CSttDeviceComm::SetTestCommBi(DrvBITrip &oTrip, BOOL bBinLogic, tmt_BinaryIn *pBi, tmt_BinaryIn *pBiEx, int nStateIndex)
{
	m_pCurBins[nStateIndex].init();
	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	oTrip.nBiLogic = bBinLogic;
	oTrip.oValid.nModuleCount = 1;
	oTrip.oValid.item[0].nModule = 0x8000;

	for(int i = 0; i < MAX_BINARYIN_COUNT; i++)
	{
		oTrip.oValid.item[0].nVal1 |= pBi[i].nSelect << i;
		m_pCurBins[nStateIndex].m_binIn[i].nSelect = pBi[i].nSelect;
	}

	//BiEx:0-63 考虑GOOSE虚端子
	oTrip.oValid.nModuleCount += 1;
	oTrip.oValid.item[1].nModule = 0x4000;
	int nBiBit;

	for(int k = 0; k < 64; k++)
	{
		nBiBit = pBiEx[k].nSelect;
		m_pCurBins[nStateIndex].m_binInEx[k].nSelect = pBiEx[k].nSelect;

		if(k < 32)
		{
			oTrip.oValid.item[1].nVal1 |= nBiBit << k;
		}
		else
		{
			oTrip.oValid.item[1].nVal2 |= nBiBit << (k - 32);
		}
	}

	if(oSwitchModules.m_nModulesCount > 0)
	{
		oTrip.oValid.nModuleCount += oSwitchModules.m_nModulesCount;
		int nBiBit;
		int nOffSet = 0;

		for(int i = 0; i < oSwitchModules.m_nModulesCount; i++)
		{
			oTrip.oValid.item[i + 2].nModule = ModuleIndexTransToDrv(oSwitchModules.oSWITCHINFO[i].m_nModulePos);

			if(i > 0)
			{
				nOffSet += oSwitchModules.oSWITCHINFO[i - 1].m_nBiCount;
			}

			long nBiIndex = 0;
			for(int k = 0; k < 64; k++)
			{
				if(oSwitchModules.oSWITCHINFO[i].m_bBiPos[k] == FALSE)
				{
					continue;
				}
				nBiBit = pBiEx[nBiIndex + nOffSet].nSelect;
				m_pCurBins[nStateIndex].m_binInEx[i].nSelect = pBiEx[nBiIndex + nOffSet].nSelect;
				if(k < 32)
				{
					oTrip.oValid.item[i + 2].nVal1 |= nBiBit << k;
				}
				else
				{
					oTrip.oValid.item[i + 2].nVal2 |= nBiBit << (k - 32);
				}

				nBiIndex++;
			}
		}
	}
}

void CSttDeviceComm::SetTestCommBo(DrvComBoStatus &oBoStatus, tmt_BinaryOut *pBo, tmt_BinaryOut *pBoEx)
{
	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	oBoStatus.item[0].nVal1 = 0xFFFFFFFF;

	for(int i = 0; i < MAX_BINARYOUT_COUNT; i++) //bo
	{
		oBoStatus.item[0].nVal1 &= ~(pBo[i].nState << i);
	}

	unsigned int nBoBit;

	if(oSwitchModules.m_nModulesCount > 0)
	{
		int nOffSet = 0;

		for(int i = 0; i < oSwitchModules.m_nModulesCount; i++)
		{
			if(i > 0)
			{
				nOffSet += oSwitchModules.oSWITCHINFO[i - 1].m_nBoCount;
			}

			long nBoIndex = 0;
			for(int j = 0; j < 64; j++)
			{
				if(oSwitchModules.oSWITCHINFO[i].m_bBoPos[j] == FALSE)
				{
					continue;
				}

				nBoBit = pBoEx[nBoIndex + nOffSet].nState > 0 ? 0 : 1;

				if(j < 32)
				{
					oBoStatus.item[i + 1].nVal1 |= nBoBit << j;
				}
				else
				{
					oBoStatus.item[i + 1].nVal2 |= nBoBit << (j - 32);
				}

				nBoIndex++;
			}
		}
	}
	else
	{
		//无开关量板时 考虑BoEx:0-63 GOOSE虚端子
		for(int j = 0; j < 64; j++)
		{
			nBoBit = pBoEx[j].nState > 0 ? 0 : 1;

			if(j < 32)
			{
				oBoStatus.item[1].nVal1 |= nBoBit << j;
			}
			else
			{
				oBoStatus.item[1].nVal2 |= nBoBit << (j - 32);
			}
		}
	}
}

void CSttDeviceComm::Manual_volt(tmt_channel *pTmt_channel, char *pszDrv, int nHarm,
								 int nModuleUIndex, BOOL bIsDc, BOOL bIsModuleOutput)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	int nChPos;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleUIndex].dat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

	if(bIsDc)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = k;

			if(!bIsModuleOutput)
			{
				m_nTmtPos = pModule->m_nChTmtPos[k];
			}

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[m_nTmtPos].Harm[1].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCVolToDrv(fAmp, k, nModuleUIndex, dat + nChPos);
		}

		pDrv->oDrv_HarmParam[nModuleUIndex].nDWcnt = 24;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = k;

			if(!bIsModuleOutput)
			{
				m_nTmtPos = pModule->m_nChTmtPos[k];
			}

			//DC
			{
				if(m_nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[0].fAmp;
				}

				nChPos = pModule->m_nChDrvPos[k];
				TransAnalogDCVolToDrv(fAmp, k, nModuleUIndex, dat + nChPos);
			}

			if(m_nTmtPos < 0)
			{
				continue;
			}

			//BASE
			{
				oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;
				TransAnalogVolToDrv(fAmp, fAngle,
									fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3);
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				int nHarmIndex = 0;
				int nHarmTotal = 0;

				for(int j = 2; j < nHarmCount; j++)
				{
					nHarmIndex = pTmt_channel[m_nTmtPos].Harm[j].nSelectIndex;

					if(nHarmIndex > 0 && nHarmIndex < 31)
					{
						oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[j];
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogVolToDrv(fAmp, fAngle,
											fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3 + nHarmIndex * 3 * CHANNEL_MAX);
						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					oTmtHarm = &pTmt_channel[m_nTmtPos].InterHarm;

					if(oTmtHarm->nSelectIndex == 1)
					{
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogVolToDrv(fAmp, fAngle,
											fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3 + (nHarmTotal + 1) * 3 * CHANNEL_MAX);
					}
				}
			}
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleUIndex].nDWcnt = 6 + nHarm * 3 * CHANNEL_MAX;
	}
}

void CSttDeviceComm::Manual_current(tmt_channel *pTmt_channel, char *pszDrv, int nHarm,
									int nModuleIIndex, BOOL bIsDc, BOOL bIsModuleOutput)
{
	int nModuleOffset = nModuleIIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	int nChPos;
	float fAmp = 0;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

	if(bIsDc)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = k;

			if(!bIsModuleOutput)
			{
				m_nTmtPos = pModule->m_nChTmtPos[k];
			}

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[m_nTmtPos].Harm[1].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCCurToDrv(fAmp, k, nModuleIIndex, dat + nChPos);
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 24;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = k;

			if(!bIsModuleOutput)
			{
				m_nTmtPos = pModule->m_nChTmtPos[k];
			}

			//DC
			{
				if(m_nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[0].fAmp;
				}

				nChPos = pModule->m_nChDrvPos[k];
				TransAnalogDCCurToDrv(fAmp, k, nModuleIIndex, dat + nChPos);
			}

			if(m_nTmtPos < 0)
			{
				continue;
			}

			//BASE
			{
				oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;
				TransAnalogCurToDrv(fAmp, fAngle,
									fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3);
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				int nHarmIndex = 0;
				int nHarmTotal = 0;

				for(int j = 2; j < nHarmCount; j++)
				{
					nHarmIndex = pTmt_channel[m_nTmtPos].Harm[j].nSelectIndex;

					if(nHarmIndex > 0 && nHarmIndex < 31)
					{
						oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[j];
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogCurToDrv(fAmp, fAngle,
											fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3 + nHarmIndex * 3 * CHANNEL_MAX);
						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					oTmtHarm = &pTmt_channel[m_nTmtPos].InterHarm;

					if(oTmtHarm->nSelectIndex == 1)
					{
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;
						TransAnalogCurToDrv(fAmp, fAngle,
											fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3 + (nHarmTotal + 1) * 3 * CHANNEL_MAX);
					}
				}
			}
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = 6 + nHarm * 3 * CHANNEL_MAX;
	}
}

void CSttDeviceComm::Manual_UI(tmt_channel *pTmt_Volt, tmt_channel *pTmt_Current, char *pszDrv, int nHarm,
							   int nIndex, BOOL bIsDc)
{
	int nModuleOffset = nIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	int nChPos;
	float fAmp = 0;
	BOOL bChanIsVolt;
	long *dat = &pDrv->oDrv_HarmParam[nModuleOffset].dat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_channel *pTmt_channel;
	int nChanSize = CHANNEL_MAX;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		nChanSize = 12;
	}
	else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
	{
		nChanSize = 8;
	}

	if(bIsDc)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = pTmt_Volt;
				bChanIsVolt = TRUE;
			}
			else
			{
				pTmt_channel = pTmt_Current;
				bChanIsVolt = FALSE;
			}

			nChPos = pModule->m_nChDrvPos[k];
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[m_nTmtPos].Harm[1].fAmp;
			}

			if(bChanIsVolt)
			{
				TransAnalogDCUIToDrv_Volt(fAmp, k, nIndex, dat + nChPos);
			}
			else
			{
				TransAnalogDCUIToDrv_Current(fAmp, k, nIndex, dat + nChPos);
			}
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = nChanSize + nChanSize * 3;
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
			{
				pTmt_channel = pTmt_Volt;
				bChanIsVolt = TRUE;
			}
			else
			{
				pTmt_channel = pTmt_Current;
				bChanIsVolt = FALSE;
			}

			nChPos = pModule->m_nChDrvPos[k];
			m_nTmtPos = pModule->m_nChTmtPos[k];
			//DC
			{
				if(m_nTmtPos < 0)
				{
					fAmp = 0;
				}
				else
				{
					fAmp = pTmt_channel[m_nTmtPos].Harm[0].fAmp;
				}

				if(bChanIsVolt)
				{
					TransAnalogDCUIToDrv_Volt(fAmp, k, nIndex, dat + nChPos);
				}
				else
				{
					TransAnalogDCUIToDrv_Current(fAmp, k, nIndex, dat + nChPos);
				}
			}

			if(m_nTmtPos < 0)
			{
				continue;
			}

			//BASE
			{
				oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(bChanIsVolt)
				{
					TransAnalogUIToDrv_Volt(fAmp, fAngle,
											fFreq, k, nIndex, dat + nChanSize + nChPos * 3);
				}
				else
				{
					TransAnalogUIToDrv_Current(fAmp, fAngle,
											   fFreq, k, nIndex, dat + nChanSize + nChPos * 3);
				}
			}

			//Harm
			if(nHarm > 1)
			{
				int nHarmCount = pModule->m_oModuleAttr.m_nHarmCount + 1;

				if(nHarmCount > MAX_HARM_COUNT)
				{
					nHarmCount = MAX_HARM_COUNT;
				}

				int nHarmIndex = 0;
				int nHarmTotal = 0;

				for(int j = 2; j < nHarmCount; j++)
				{
					nHarmIndex = pTmt_channel[m_nTmtPos].Harm[j].nSelectIndex;

					if(nHarmIndex > 0 && nHarmIndex < 31)
					{
						oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[j];
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;

						if(bChanIsVolt)
						{
							TransAnalogUIToDrv_Volt(fAmp, fAngle,
													fFreq, k, nIndex, dat + nChanSize + nChPos * 3 + nHarmIndex * 3 * nChanSize);
						}
						else
						{
							TransAnalogUIToDrv_Current(fAmp, fAngle,
													   fFreq, k, nIndex, dat + nChanSize + nChPos * 3 + nHarmIndex * 3 * nChanSize);
						}

						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					oTmtHarm = &pTmt_channel[m_nTmtPos].InterHarm;

					if(oTmtHarm->nSelectIndex == 1)
					{
						fAmp = oTmtHarm->fAmp;
						fAngle = oTmtHarm->fAngle;
						fFreq = oTmtHarm->fFreq;

						if(bChanIsVolt)
						{
							TransAnalogUIToDrv_Volt(fAmp, fAngle,
													fFreq, k, nIndex, dat + nChanSize + nChPos * 3 + (nHarmTotal + 1) * 3 * nChanSize);
						}
						else
						{
							TransAnalogUIToDrv_Current(fAmp, fAngle,
													   fFreq, k, nIndex, dat + nChanSize + nChPos * 3 + (nHarmTotal + 1) * 3 * nChanSize);
						}
					}
				}
			}
		}

		if(nHarm > 31)
		{
			nHarm = 31;
		}

		pDrv->oDrv_HarmParam[nModuleOffset].nDWcnt = nChanSize + nHarm * 3 * nChanSize;
	}
}

/************公共处理函数部分*************/

/************基础实验部分*************/
void CSttDeviceComm::tmt_to_drv_manu(tmt_ManualTest *pTmt, BOOL bIsStartTest)
{
	char *pszDrv = stt_test_get_drvparas_buff();

	if(pTmt->m_oManuParas.m_bAuto)
	{
		CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient = TRUE;
		tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;
		oGradientParas.m_fPrepareTime = EPSINON;
		oGradientParas.m_fPreFaultTime = EPSINON;
		oGradientParas.m_nSttTestMode = GradientTest_Base;
		oGradientParas.m_nTestMode = pTmt->m_oManuParas.m_manuGradient.nMode;
		oGradientParas.m_nType = pTmt->m_oManuParas.m_nGradientTpSelect;
		oGradientParas.m_nChannel = pTmt->m_oManuParas.m_nGradientChSelect;
		oGradientParas.m_fStart = pTmt->m_oManuParas.m_manuGradient.fStart;
		oGradientParas.m_fStop = pTmt->m_oManuParas.m_manuGradient.fEnd;
		oGradientParas.m_fStep = pTmt->m_oManuParas.m_manuGradient.fStep;
		oGradientParas.m_fStepTime = pTmt->m_oManuParas.m_manuGradient.fStepTime;
		oGradientParas.m_nBinLogic = pTmt->m_oManuParas.m_nBinLogic;

		for(int nBiIndex = 0; nBiIndex < MAX_BINARYIN_COUNT; nBiIndex++)
		{
			memcpy(&oGradientParas.m_binIn[nBiIndex],
				   &pTmt->m_oManuParas.m_binIn[nBiIndex], sizeof(tmt_BinaryIn));
			memcpy(&oGradientParas.m_binOut[0][nBiIndex],
				   &pTmt->m_oManuParas.m_binOut[nBiIndex], sizeof(tmt_BinaryOut));
			memcpy(&oGradientParas.m_binOut[1][nBiIndex],
				   &pTmt->m_oManuParas.m_binOut[nBiIndex], sizeof(tmt_BinaryOut));
		}

		for(int nBiExIndex = 0; nBiExIndex < g_nBinExCount && nBiExIndex < MAX_ExBINARY_COUNT; nBiExIndex++)
		{
			memcpy(&oGradientParas.m_binInEx[nBiExIndex],
				   &pTmt->m_oManuParas.m_binInEx[nBiExIndex], sizeof(tmt_BinaryIn));
		}

		for(int nBoExIndex = 0; nBoExIndex < g_nBoutExCount && nBoExIndex < MAX_ExBINARY_COUNT; nBoExIndex++)
		{
			memcpy(&oGradientParas.m_binOutEx[0][nBoExIndex],
				   &pTmt->m_oManuParas.m_binOutEx[nBoExIndex], sizeof(tmt_BinaryOut));
			memcpy(&oGradientParas.m_binOutEx[1][nBoExIndex],
				   &pTmt->m_oManuParas.m_binOutEx[nBoExIndex], sizeof(tmt_BinaryOut));
		}

		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			if(pTmt->m_oManuParas.m_bDC)
			{
				pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq = 0.0f;
			}

			oGradientParas.m_uiVOL[0][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAmp;
			oGradientParas.m_uiVOL[0][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAngle;
			oGradientParas.m_uiVOL[0][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq;
			oGradientParas.m_uiVOL[1][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAmp;
			oGradientParas.m_uiVOL[1][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAngle;
			oGradientParas.m_uiVOL[1][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq;
			oGradientParas.m_uiVOL[2][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAmp;
			oGradientParas.m_uiVOL[2][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fAngle;
			oGradientParas.m_uiVOL[2][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq;
		}

		for(int i = 0; i < MAX_CURRENT_COUNT; i++)
		{
			if(pTmt->m_oManuParas.m_bDC)
			{
				pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq = 0.0f;
			}

			oGradientParas.m_uiCUR[0][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			oGradientParas.m_uiCUR[0][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAngle;
			oGradientParas.m_uiCUR[0][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq;
			oGradientParas.m_uiCUR[1][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			oGradientParas.m_uiCUR[1][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAngle;
			oGradientParas.m_uiCUR[1][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq;
			oGradientParas.m_uiCUR[2][i].Harm[1].fAmp = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAmp;
			oGradientParas.m_uiCUR[2][i].Harm[1].fAngle = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fAngle;
			oGradientParas.m_uiCUR[2][i].Harm[1].fFreq = pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq;
		}

		if(g_theSystemConfig->m_nHasAnalog != 0)
		{
			BOOL bRet = CSttDeviceBase::g_pSttDeviceBase->CheckCurrLoadIsSafe(oGradientParas.m_uiCUR[0], pTmt->m_oManuParas.m_bDC);

			if(!bRet)
			{
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] 电流幅值超限"));
				CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
				pSttTestBase->ReturnTestStateEvent_TestFinish(0, 0, FALSE);
				return;
			}
		}

		if(g_theSystemConfig->m_nHasWeek != 0)
		{
			float fMaxOut[12];

			for(int i = 0; i < 12; i++)
			{
				fMaxOut[i] = 0;
			}

			BOOL bSetTap;
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

				bSetTap = FALSE;
				if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
				{
					g_nWeekTap = GetTapCode_PIA12DS(fMaxOut, TRUE, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
				{
					g_nWeekTap = GetTapCode_EVTECT(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
				{
					g_nWeekTap = GetTapCode_PNS331(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
				{
					g_nWeekTap = GetTapCode_EVTECT_Ex1(fMaxOut, TRUE, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
				{
					g_nWeekTap = GetTapCode_DC6U10V(fMaxOut, TRUE, WeekTap[nIndex], 0);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
				{
					g_nWeekTap = GetTapCode_DC6I20mA(fMaxOut, TRUE, WeekTap[nIndex], 0);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
				{
					g_nWeekTap = GetTapCode_PN_DC6U6I(fMaxOut, TRUE, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
				{
					g_nWeekTap = GetTapCode_L336D(fMaxOut, TRUE, NULL, WeekTap[nIndex]);					
					bSetTap = TRUE;
				}

				if(bSetTap)
				{
					m_nDCTap = g_nWeekTap;
					m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
					g_oDrvMutex.lock();
					ioctl(m_nfd, 0x125, m_nDCTap);
					g_oDrvMutex.unlock();
				}
			}

			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

				g_nWeekTap = GetTapCode_ADMU(fMaxOut, TRUE, NULL, WeekTap[nIndex], 0);
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap);
				g_oDrvMutex.unlock();
			}
		}

		oGradientParas.m_bManuDc = pTmt->m_oManuParas.m_bDC;

		if(oGradientParas.m_bManuDc)
		{
			Gradient_Manu_Harm(pszDrv, oGradientParas, 0, 0);
		}
		else
		{
			Gradient_Manu_Harm(pszDrv, oGradientParas, 1, 1);
		}

		int nDirection = 0;
		float fGradientAmp;

		if(oGradientParas.m_nType == GRADIENT_AMP)
		{
			if(oGradientParas.m_fStart > oGradientParas.m_fStop)
			{
				nDirection = -1;
				fGradientAmp = oGradientParas.m_fStart;
			}
			else
			{
				nDirection = 1;
				fGradientAmp = oGradientParas.m_fStop;
			}
		}

		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
				1, pTmt->m_oManuParas.m_bDC, nDirection, 1, fGradientAmp, g_theSystemConfig->m_fAuxDC_Vol);

		if(g_theSystemConfig->m_nHasDigital != 0)
		{
			SetGooseValue_ManuTest(&pTmt->m_oManuParas.m_oGoosePub[0], TRUE);
		}

		return;
	}

	ManuRtData oRtData;
	memcpy(oRtData.uiVOL, pTmt->m_oManuParas.m_uiVOL, sizeof(tmt_channel)*g_nRtDataVoltCnt);
	memcpy(oRtData.uiCUR, pTmt->m_oManuParas.m_uiCUR, sizeof(tmt_channel)*g_nRtDataCurrCnt);
	CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.append(oRtData);
	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	memset(pDrv, 0, sizeof(Drv_ManuData));

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		BOOL bRet = CSttDeviceBase::g_pSttDeviceBase->CheckCurrLoadIsSafe(pTmt->m_oManuParas.m_uiCUR, pTmt->m_oManuParas.m_bDC);

		if(!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] 电流幅值超限"));

			if(!bIsStartTest)
			{
				CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
			}

			CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
			pSttTestBase->ReturnTestStateEvent_TestFinish(0, 0, FALSE);

			return;
		}
	}

	Drv_ManuBin oBiSetting;
	memset(&oBiSetting, 0, sizeof(Drv_ManuBin));
	oBiSetting.nBinIsStop = false;

	if(pTmt->m_oManuParas.m_bBinStop)
	{
		oBiSetting.nBinIsStop = true;//开入停止
	}

	oBiSetting.nMdelay = pTmt->m_oManuParas.m_manuGradient.fTrigDelay * 1000;
	SetTestCommBi(oBiSetting.oTrip, pTmt->m_oManuParas.m_nBinLogic,
				  pTmt->m_oManuParas.m_binIn, pTmt->m_oManuParas.m_binInEx);
	SetManualBI((char *)&oBiSetting, sizeof(Drv_ManuBin));
	BOOL  bSetAux = FALSE;
	float fAuxMax = g_theSystemConfig->m_fAuxDC_Vol;

	if(fabs(g_theSystemConfig->m_fAuxDC_Vol) < 0.001)
	{
		bSetAux = TRUE;//系统参数辅助直流等于0,使能输出
		fAuxMax = pTmt->m_oManuParas.m_fVolAux;
	}

	if(bSetAux)
	{
		SetManuOrStateAuxVolt(pDrv->nAuxVolt, fAuxMax);
	}

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			Manual_volt(pTmt->m_oManuParas.m_uiVOL, pszDrv, 1, nIndex, pTmt->m_oManuParas.m_bDC);
		}

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			Manual_current(pTmt->m_oManuParas.m_uiCUR, pszDrv, 1, nIndex, pTmt->m_oManuParas.m_bDC);
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			Manual_UI(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, 1,
					  nIndex, pTmt->m_oManuParas.m_bDC);
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			if(pTmt->m_oManuParas.m_bDC)
			{
				pTmt->m_oManuParas.m_uiVOL[i].Harm[1].fFreq = 0.0f;
			}
		}

		for(int i = 0; i < MAX_CURRENT_COUNT; i++)
		{
			if(pTmt->m_oManuParas.m_bDC)
			{
				pTmt->m_oManuParas.m_uiCUR[i].Harm[1].fFreq = 0.0f;
			}
		}

		int nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U;
		nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_I;
		nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_UI;
		int nModuleCnt;

		if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
		{
			SetGooseValue_ManuTest(&pTmt->m_oManuParas.m_oGoosePub[0], bIsStartTest);
			nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_D;
			BOOL bIsFt3;

			for(int i = 0; i < nModuleCnt; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

				if(m_oCIEC61850CfgMngr.m_nUseSmv92 == SMVTYPE_92)
				{
					bIsFt3 = FALSE;
				}
				else
				{
					bIsFt3 = TRUE;
				}

				//不同数字板的硬件相位补偿不同
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
												  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat, pModule, 1, bIsFt3);
				pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].nDWcnt = DIGITAL_CHANNEL_MAX * 3;
			}
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_FT3 > 0)
		{
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_D;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
			nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_FT3;

			for(int i = 0; i < nModuleCnt; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_FT3[i];
				//不同数字板的硬件相位补偿不同
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
												  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat, pModule, 1, TRUE);
				pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].nDWcnt = DIGITAL_CHANNEL_MAX * 3;
			}
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_ADMU > 0)
		{
			nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_ADMU;
			pDrv->oDrv_ADMUHarm.nModuleCnt = nModuleCnt;

			for(int i = 0; i < nModuleCnt; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[i];
				pDrv->oDrv_ADMUHarm.nModule[i] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
				pDrv->oDrv_ADMUHarm.oHarmParam[i].dat[0] = 2;//片选 10
				//不同数字板的硬件相位补偿不同
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
												  pDrv->oDrv_ADMUHarm.oHarmParam[i].dat + 1, pModule, 1, TRUE);
				pDrv->oDrv_ADMUHarm.oHarmParam[i].nDWcnt = 1+ DIGITAL_CHANNEL_MAX * 3;
			}
		}

		SetFt3Value_ManuTest(&pTmt->m_oManuParas.m_oFt3Pub[0], bIsStartTest);
	}

	if(bIsStartTest)
	{
		for(int nBoard = 0; nBoard < m_oCIEC61850CfgMngr.m_pIECConfig_2M->moduleCount; nBoard++)
		{
			for(int index = 0; index < MAX_2M_BLOCK_COUNT; index++)
			{
				memcpy(&m_oPreStable2MList[nBoard][index],
					   &m_oCIEC61850CfgMngr.m_oStable2MMngr.m_oStable2MList[nBoard][index], sizeof(tmt_Stable2MList));
			}
		}
	}

	SetStable2MValue_ManuTest(&pTmt->m_oManuParas.m_o2MOnePortPub[0], bIsStartTest);

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		BOOL bHasSetTap = FALSE;
		BOOL bSetTap;

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			bSetTap = FALSE;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
			{
				Manual_Week_PN_Main(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
									1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
			{
				Manual_Week_PIA48S(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								   1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
			{
				Manual_Week_PIA12DS(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
			{
				Manual_Week_EVTECT(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								   1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				Manual_Week_PNS331(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								   1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
			{
				Manual_Week_EVTECT_Ex1(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex, FALSE);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
			{
				Manual_Week_DC6U10V(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex, FALSE);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
			{
				Manual_Week_DC6I20mA(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex, FALSE);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
			{
				Manual_Week_PN_DC6U6I(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
			{
				Manual_Week_L336D(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								  1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);				
				bSetTap = TRUE;
			}

			if(bSetTap)
			{
				bHasSetTap = TRUE;
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap);
				g_oDrvMutex.unlock();
			}
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];
			Manual_Week_ADMU(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
			m_nDCTap = g_nWeekTap;
			m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x125, m_nDCTap);
			g_oDrvMutex.unlock();
			bHasSetTap = TRUE;
		}

		if(bHasSetTap)
		{
			Sleep(100);
		}
	}

	SetTestCommBo(pDrv->oDrvComBoSta, pTmt->m_oManuParas.m_binOut, pTmt->m_oManuParas.m_binOutEx);

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x300, 0);
	write(m_nfd, pszDrv, sizeof(Drv_ManuData));
	g_oDrvMutex.unlock();

	if(g_theSystemConfig->m_nHasAnalog != 0 || bSetAux)
	{
		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
				1, pTmt->m_oManuParas.m_bDC, 0, 0, 0, fAuxMax);
	}
}

void CSttDeviceComm::tmt_to_drv_moduleoutput(TMT_ADJ_MODULE_OUTPUT *pTmt)
{
	char *pszDrv = stt_test_get_drvparas_buff();
	Drv_ManuData *pDrvManuData = (Drv_ManuData *)pszDrv;
	tmt_channel    m_oTmt_channel[MAX_VOLTAGE_COUNT];

	for(int nIndex = 0; nIndex < MAX_VOLTAGE_COUNT; nIndex++)
	{
		m_oTmt_channel[nIndex].init();
	}

	memset(pDrvManuData, 0, sizeof(Drv_ManuData));
	//DAPara
	float fIsum = 0;
	float fVsum = 0;
	float fIMax = 0;
	float fAmp = 0;
	BOOL bDc = FALSE;
	BOOL bSetDCTap = FALSE;

	if(pTmt->m_nFreqIndex == 0)
	{
		bDc = TRUE;
	}

	pDrvManuData->oDrvComBoSta.item[0].nVal1 = g_theSttAdjustTool.m_nSwitchCtrl;
	CSttDeviceBase::g_pSttDeviceBase->InitDAData();

	if(pTmt->m_nModuleType == STT_MODULE_TYPE_VOLT)
	{
		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE oModule_U = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(oModule_U != NULL)
			{
				if(oModule_U->m_oModuleAttr.m_nModuleIndex == pTmt->m_nModuleIndex)
				{
					for(int nChannel = 0; nChannel < CHANNEL_MAX; nChannel++)
					{
						m_oTmt_channel[nChannel].Harm[1].fAmp =
							pTmt->m_oChannels[nChannel].m_oVector.m_fMag;
						m_oTmt_channel[nChannel].Harm[1].fAngle =
							pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
						m_oTmt_channel[nChannel].Harm[1].fFreq =
							pTmt->m_nFreqIndex * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
						fAmp = fabs(m_oTmt_channel[nChannel].Harm[1].fAmp);

						if(fVsum < fAmp)
						{
							fVsum = fAmp;
						}
					}

					Manual_volt(m_oTmt_channel, pszDrv, 1, nIndex, bDc, TRUE);
					CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(fVsum, g_theSystemConfig->m_fAuxDC_Vol, nIndex, bDc);
					break;
				}
			}
		}
	}
	else
	{
		if(g_theDeviceSystemParameter->m_oModules_U[0] != NULL)
		{
			if(pTmt->m_nModuleType == STT_MODULE_TYPE_CURRENT
					|| pTmt->m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
			{
				//RD33 UAUBUC统一接到测试仪UA,参考UA相位
				m_oTmt_channel[0].Harm[1].fAmp = 50;
				m_oTmt_channel[0].Harm[1].fAngle = 0;
				m_oTmt_channel[0].Harm[1].fFreq = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
				Manual_volt(m_oTmt_channel, pszDrv, 1, 0, FALSE, TRUE);
				CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(50, g_theSystemConfig->m_fAuxDC_Vol, 0, FALSE);
			}
		}

		for(int nIndex = 0; nIndex < MAX_VOLTAGE_COUNT; nIndex++)
		{
			m_oTmt_channel[nIndex].init();
		}

		if(pTmt->m_nModuleType == STT_MODULE_TYPE_CURRENT)
		{
			//CURRENT
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
			{
				PSTT_MODULE oModule_I = g_theDeviceSystemParameter->m_oModules_I[nIndex];

				if(oModule_I != NULL)
				{
					if(oModule_I->m_oModuleAttr.m_nModuleIndex == pTmt->m_nModuleIndex)
					{
						for(int nChannel = 0; nChannel < CHANNEL_MAX; nChannel++)
						{
							m_oTmt_channel[nChannel].Harm[1].fAmp =
								pTmt->m_oChannels[nChannel].m_oVector.m_fMag;
							m_oTmt_channel[nChannel].Harm[1].fAngle =
								pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
							m_oTmt_channel[nChannel].Harm[1].fFreq =
								pTmt->m_nFreqIndex * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
							fAmp = fabs(m_oTmt_channel[nChannel].Harm[1].fAmp);
							fIsum += fAmp;

							if(fIMax < fAmp)
							{
								fIMax = fAmp;
							}
						}

						Manual_current(m_oTmt_channel, pszDrv, 1, nIndex, bDc, TRUE);

						if(bDc)
						{
							CSttDeviceBase::g_pSttDeviceBase->SetCurrentDApara_DC(fIsum, nIndex);
						}
						else
						{
							switch(oModule_I->m_oModuleAttr.m_nChMergeMode)
							{
								case STT_CURRENT_ChMergeMode_1Ch_Fixed:
									if(oModule_I->m_oModuleAttr.m_nChannelNum == 1)
									{
										//6合1模块
										fIMax = fIMax/6.0;
									}
									break;
								case STT_CURRENT_ChMergeMode_3Ch_Fixed:
									if(oModule_I->m_oModuleAttr.m_nChannelNum == 3)
									{
										//6合3模块
										fIMax = fIMax/2.0;
									}
									break;
							}

							CSttDeviceBase::g_pSttDeviceBase->SetCurrentDApara_AC(fIsum, nIndex, fIMax);
						}

						break;
					}
				}
			}

#ifdef  _MainBoard_PN_

			if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
			{
				PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

				if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
				{
					long nCurModuleIndex = -1;

					if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
					{
						nCurModuleIndex += 1;
					}

					if(g_theDeviceSystemParameter->m_nModuleCount_I > 0)
					{
						nCurModuleIndex += 1;
					}

					if(nCurModuleIndex >= 0)
					{
						CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nCurModuleIndex + 1] =
							(CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nCurModuleIndex] >> 8) & 0xFF;
					}
				}
			}

#endif
		}
		else if(pTmt->m_nModuleType == STT_MODULE_TYPE_VOLT_CURRENT)
		{
			float fAngle = 0;
			float fFreq = 0;
			int nChPos;
			int nChannelCnt = CHANNEL_MAX;

			//UI
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
			{
				int nModuleOffset = nIndex;
				nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
				nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
				PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

				if(pModule_UI != NULL)
				{
					if(pModule_UI->m_oModuleAttr.m_nModuleIndex == pTmt->m_nModuleIndex
							|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
							|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
							|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
							|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
					{
						if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
								|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
								|| pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
						{
							pTmt->m_nModuleIndex = pModule_UI->m_oModuleAttr.m_nModuleIndex;
							CSttDeviceBase::g_pSttDeviceBase->DAPowerCtrl();
							nChannelCnt = 12;
						}
						else if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
						{
							pTmt->m_nModuleIndex = pModule_UI->m_oModuleAttr.m_nModuleIndex;
							CSttDeviceBase::g_pSttDeviceBase->DAPowerCtrl();
							nChannelCnt = 8;
						}

						m_nTmtChanNum = pModule_UI->m_oModuleAttr.m_nChannelNum;

						for(int nChannel = 0; nChannel < m_nTmtChanNum; nChannel++)
						{
							nChPos = pModule_UI->m_nChDrvPos[nChannel];
							fAmp = fabs(pTmt->m_oChannels[nChannel].m_oVector.m_fMag);
							fAngle = pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
							fFreq = pTmt->m_nFreqIndex * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;

							if(pModule_UI->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChannel].m_nEeType == STT_CH_EETYPE_VOLTAGE)
							{
								if(bDc)
								{
									TransAnalogDCUIToDrv_Volt(fAmp, nChannel, nIndex, pDrvManuData->oDrv_HarmParam[nModuleOffset].dat + nChPos);
								}
								else
									TransAnalogUIToDrv_Volt(fAmp, fAngle, fFreq, nChannel, nIndex,
															pDrvManuData->oDrv_HarmParam[nModuleOffset].dat + nChannelCnt + nChPos * 3);

								if(fVsum < fAmp)
								{
									fVsum = fAmp;
								}
							}
							else
							{
								if(bDc)
								{
									TransAnalogDCUIToDrv_Current(fAmp, nChannel, nIndex, pDrvManuData->oDrv_HarmParam[nModuleOffset].dat + nChPos);
								}
								else
									TransAnalogUIToDrv_Current(fAmp, fAngle, fFreq, nChannel, nIndex,
															   pDrvManuData->oDrv_HarmParam[nModuleOffset].dat + nChannelCnt + nChPos * 3);
							}
						}

						for(int nChannel = 0; nChannel < m_nTmtChanNum; nChannel++)
						{
							m_oTmt_channel[nChannel].Harm[1].fAmp =
								pTmt->m_oChannels[nChannel].m_oVector.m_fMag;
							m_oTmt_channel[nChannel].Harm[1].fAngle =
								pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
							m_oTmt_channel[nChannel].Harm[1].fFreq =
								pTmt->m_nFreqIndex * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
						}

						BOOL bRet = CSttDeviceBase::g_pSttDeviceBase->CheckCurrLoadIsSafe_moduleoutput(m_oTmt_channel, bDc, pModule_UI);

						if(!bRet)
						{
							CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] 电流幅值超限"));
							CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
							return;
						}

						pDrvManuData->oDrv_HarmParam[nModuleOffset].nDWcnt = nChannelCnt + nChannelCnt * 3;
						CSttPowerCtrlBase *pPowerCtrlBase = pModule_UI->m_oModuleAttr.m_pPowerCtrlBase;

						if(pPowerCtrlBase != NULL)
						{
							pPowerCtrlBase->SetVoltDA(fVsum, bDc);
							pPowerCtrlBase->SetCurrentDA_State(nIndex);
							CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nModuleOffset] = pPowerCtrlBase->GetModuleDA();
						}

#ifdef  _MainBoard_PN_

						if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V130_C20)
						{
							CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(fVsum, 0, 0, bDc);
						}

#endif
						break;
					}
				}
			}
		}
		else if(pTmt->m_nModuleType == STT_MODULE_TYPE_WEEK_EX)
		{
			BOOL bSetTap;
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
			{
				PSTT_MODULE pModule_Week = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

				bSetTap = FALSE;
				if(pModule_Week != NULL)
				{
					if(pModule_Week->m_oModuleAttr.m_nModuleIndex == pTmt->m_nModuleIndex
							|| pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331
							|| pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
							|| pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
					{
						m_nTmtChanNum = pModule_Week->m_oModuleAttr.m_nChannelNum;

						for(int nChannel = 0; nChannel < m_nTmtChanNum; nChannel++)
						{
							m_oTmt_channel[nChannel].Harm[1].fAmp =
								pTmt->m_oChannels[nChannel].m_oVector.m_fMag;
							m_oTmt_channel[nChannel].Harm[1].fAngle =
								pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
							m_oTmt_channel[nChannel].Harm[1].fFreq =
								pTmt->m_nFreqIndex * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
						}

						if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
						{
							Manual_Week_PN_Main(m_oTmt_channel, NULL, pszDrv, 1, nIndex, bDc, TRUE);
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
						{
							Manual_Week_PIA48S(m_oTmt_channel, NULL, pszDrv, 1, nIndex, bDc, TRUE);
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
						{
							Manual_Week_PIA12DS(m_oTmt_channel, NULL, pszDrv, nIndex, TRUE);							
							bSetTap = TRUE;
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
						{
							Manual_Week_EVTECT(m_oTmt_channel, NULL, pszDrv, 1, nIndex, bDc, TRUE);							
							bSetTap = TRUE;
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
						{
							unsigned int nRegCtrlDigital = CSttDeviceBase::g_pSttDeviceBase->m_nRegCtrlDigital;
							nRegCtrlDigital |= 1 << 6; //ON/OFF_KIO
							g_oDrvMutex.lock();
							ioctl(m_nfd, PNS330_RegAddr_DigitalCtrl, nRegCtrlDigital);
							g_oDrvMutex.unlock();
							CSttDeviceBase::g_pSttDeviceBase->m_nRegCtrlDigital = nRegCtrlDigital;
							unsigned int nRegCtrlAnalog = CSttDeviceBase::g_pSttDeviceBase->m_nRegCtrlAnalog;
							nRegCtrlAnalog |= 1 << 9; //ON/OFF_VI
							g_oDrvMutex.lock();
							ioctl(m_nfd, PNS330_RegAddr_AnalogCtrl, nRegCtrlAnalog);
							g_oDrvMutex.unlock();
							CSttDeviceBase::g_pSttDeviceBase->m_nRegCtrlAnalog = nRegCtrlAnalog;
							Manual_Week_PNS331(m_oTmt_channel, NULL, pszDrv, 1, nIndex, bDc, TRUE);							
							bSetTap = TRUE;
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
						{
							Manual_Week_EVTECT_Ex1(m_oTmt_channel, NULL, pszDrv, nIndex, TRUE);							
							bSetTap = TRUE;
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
						{
							Manual_Week_DC6U10V(m_oTmt_channel, NULL, pszDrv, nIndex, TRUE, pTmt->m_nTap);							
							bSetTap = TRUE;
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
						{
							Manual_Week_DC6I20mA(m_oTmt_channel, NULL, pszDrv, nIndex, TRUE, pTmt->m_nTap);							
							bSetTap = TRUE;
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
						{
							Manual_Week_PN_DC6U6I(m_oTmt_channel, NULL, pszDrv, nIndex, TRUE);							
							bSetTap = TRUE;
						}
						else if(pModule_Week->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
						{
							Manual_Week_L336D(m_oTmt_channel, NULL, pszDrv, 1, nIndex, bDc, TRUE);							
							bSetTap = TRUE;
						}

						if(bSetTap)
						{
							bSetDCTap = TRUE;
							m_nDCTap = g_nWeekTap;
							m_nDCTap |= ModuleIndexTransToDrv(pModule_Week->m_oModuleAttr.m_nModuleIndex) << 16;
							g_oDrvMutex.lock();
							ioctl(m_nfd, 0x125, m_nDCTap);
							g_oDrvMutex.unlock();
						}

						break;
					}
				}
			}
		}
		else if(pTmt->m_nModuleType == STT_MODULE_TYPE_ADMU)
		{
			BOOL bSetTap;
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
			{
				PSTT_MODULE pModule_ADMU = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

				bSetTap = FALSE;
				if(pModule_ADMU != NULL)
				{
					if(pModule_ADMU->m_oModuleAttr.m_nModuleIndex == pTmt->m_nModuleIndex)
					{
						m_nTmtChanNum = pModule_ADMU->m_oModuleAttr.m_nChannelNum;

						for(int nChannel = 0; nChannel < m_nTmtChanNum; nChannel++)
						{
							m_oTmt_channel[nChannel].Harm[1].fAmp =
								pTmt->m_oChannels[nChannel].m_oVector.m_fMag;
							m_oTmt_channel[nChannel].Harm[1].fAngle =
								pTmt->m_oChannels[nChannel].m_oVector.m_fAngle;
							m_oTmt_channel[nChannel].Harm[1].fFreq =
								pTmt->m_nFreqIndex * g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
						}

						Manual_Week_ADMU(m_oTmt_channel, NULL, pszDrv,  1, nIndex, bDc, TRUE, pTmt->m_nTap);
						bSetTap = TRUE;

						if(bSetTap)
						{
							bSetDCTap = TRUE;
							m_nDCTap = g_nWeekTap;
							m_nDCTap |= ModuleIndexTransToDrv(pModule_ADMU->m_oModuleAttr.m_nModuleIndex) << 16;
							g_oDrvMutex.lock();
							ioctl(m_nfd, 0x125, m_nDCTap);
							g_oDrvMutex.unlock();
						}
						break;
					}
				}
			}
		}
	}

	if(bSetDCTap)
	{
		Sleep(150);
	}

	DeviceDAPara *pDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
	CSttDeviceBase::g_pSttDeviceBase->WriteDApara(pDAPara);

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x300, 0);
	write(m_nfd, pszDrv, sizeof(Drv_ManuData));
	ioctl(m_nfd, 0x100, 1);
	g_oDrvMutex.unlock();

	Sleep(100);
}

void CSttDeviceComm::tmt_to_drv_harm(tmt_HarmTest *pTmt, BOOL bIsStartTest)
{
	char *pszDrv = stt_test_get_drvparas_buff();

	if(pTmt->m_oHarmParas.m_bAuto)
	{
		CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient = TRUE;
		tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;
		oGradientParas.m_fPrepareTime = EPSINON;
		oGradientParas.m_fPreFaultTime = EPSINON;
		oGradientParas.m_nSttTestMode = GradientTest_Base;
		oGradientParas.m_nTestMode = pTmt->m_oHarmParas.m_oHarmGradient.nMode;
		oGradientParas.m_nType = pTmt->m_oHarmParas.m_nGradientTpSelect;
		oGradientParas.m_nChannel = pTmt->m_oHarmParas.m_nGradientChSelect;
		oGradientParas.m_fStart = pTmt->m_oHarmParas.m_oHarmGradient.fStart;
		oGradientParas.m_fStop = pTmt->m_oHarmParas.m_oHarmGradient.fEnd;
		oGradientParas.m_fStep = pTmt->m_oHarmParas.m_oHarmGradient.fStep;
		oGradientParas.m_fStepTime = pTmt->m_oHarmParas.m_oHarmGradient.fStepTime;
		oGradientParas.m_nBinLogic = pTmt->m_oHarmParas.m_oBinaryConfig.m_nBinLogic;

		for(int nBiIndex = 0; nBiIndex < MAX_BINARYIN_COUNT; nBiIndex++)
		{
			memcpy(&oGradientParas.m_binIn[nBiIndex],
				   &pTmt->m_oHarmParas.m_oBinaryConfig.m_binIn[nBiIndex], sizeof(tmt_BinaryIn));
			memcpy(&oGradientParas.m_binOut[0][nBiIndex],
				   &pTmt->m_oHarmParas.m_oBinaryConfig.m_binOut[nBiIndex], sizeof(tmt_BinaryOut));
			memcpy(&oGradientParas.m_binOut[1][nBiIndex],
				   &pTmt->m_oHarmParas.m_oBinaryConfig.m_binOut[nBiIndex], sizeof(tmt_BinaryOut));
		}

		for(int nBiExIndex = 0; nBiExIndex < g_nBinExCount && nBiExIndex < MAX_ExBINARY_COUNT; nBiExIndex++)
		{
			memcpy(&oGradientParas.m_binInEx[nBiExIndex],
				   &pTmt->m_oHarmParas.m_oBinaryConfig.m_binInEx[nBiExIndex], sizeof(tmt_BinaryIn));
		}

		for(int nBoExIndex = 0; nBoExIndex < g_nBoutExCount && nBoExIndex < MAX_ExBINARY_COUNT; nBoExIndex++)
		{
			memcpy(&oGradientParas.m_binOutEx[0][nBoExIndex],
				   &pTmt->m_oHarmParas.m_oBinaryConfig.m_binOutEx[nBoExIndex], sizeof(tmt_BinaryOut));
			memcpy(&oGradientParas.m_binOutEx[1][nBoExIndex],
				   &pTmt->m_oHarmParas.m_oBinaryConfig.m_binOutEx[nBoExIndex], sizeof(tmt_BinaryOut));
		}

		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			for(int j = 0; j < MAX_HARM_COUNT; j++)
			{
				oGradientParas.m_uiVOL[0][i].Harm[j].fAmp = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fAmp;
				oGradientParas.m_uiVOL[0][i].Harm[j].nSelectIndex = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].nSelectIndex;
				oGradientParas.m_uiVOL[0][i].Harm[j].fAngle = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fAngle;
				oGradientParas.m_uiVOL[0][i].Harm[j].fFreq = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fFreq;
				oGradientParas.m_uiVOL[1][i].Harm[j].fAmp = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fAmp;
				oGradientParas.m_uiVOL[1][i].Harm[j].nSelectIndex = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].nSelectIndex;
				oGradientParas.m_uiVOL[1][i].Harm[j].fAngle = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fAngle;
				oGradientParas.m_uiVOL[1][i].Harm[j].fFreq = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fFreq;
				oGradientParas.m_uiVOL[2][i].Harm[j].fAmp = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fAmp;
				oGradientParas.m_uiVOL[2][i].Harm[j].nSelectIndex = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].nSelectIndex;
				oGradientParas.m_uiVOL[2][i].Harm[j].fAngle = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fAngle;
				oGradientParas.m_uiVOL[2][i].Harm[j].fFreq = pTmt->m_oHarmParas.m_uiVOL[i].Harm[j].fFreq;
			}
		}

		for(int i = 0; i < MAX_CURRENT_COUNT; i++)
		{
			for(int j = 0; j < MAX_HARM_COUNT; j++)
			{
				oGradientParas.m_uiCUR[0][i].Harm[j].fAmp = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAmp;
				oGradientParas.m_uiCUR[0][i].Harm[j].nSelectIndex = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].nSelectIndex;
				oGradientParas.m_uiCUR[0][i].Harm[j].fAngle = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAngle;
				oGradientParas.m_uiCUR[0][i].Harm[j].fFreq = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fFreq;
				oGradientParas.m_uiCUR[1][i].Harm[j].fAmp = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAmp;
				oGradientParas.m_uiCUR[1][i].Harm[j].nSelectIndex = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].nSelectIndex;
				oGradientParas.m_uiCUR[1][i].Harm[j].fAngle = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAngle;
				oGradientParas.m_uiCUR[1][i].Harm[j].fFreq = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fFreq;
				oGradientParas.m_uiCUR[2][i].Harm[j].fAmp = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAmp;
				oGradientParas.m_uiCUR[2][i].Harm[j].nSelectIndex = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].nSelectIndex;
				oGradientParas.m_uiCUR[2][i].Harm[j].fAngle = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fAngle;
				oGradientParas.m_uiCUR[2][i].Harm[j].fFreq = pTmt->m_oHarmParas.m_uiCUR[i].Harm[j].fFreq;
			}
		}

		if(g_theSystemConfig->m_nHasAnalog != 0)
		{
			BOOL bRet = CSttDeviceBase::g_pSttDeviceBase->CheckCurrLoadIsSafe(oGradientParas.m_uiCUR[0], FALSE);

			if(!bRet)
			{
				CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] 电流幅值超限"));
				CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
				pSttTestBase->ReturnTestStateEvent_TestFinish(0, 0, FALSE);
				return;
			}
		}

		if(g_theSystemConfig->m_nHasWeek != 0)
		{
			float fMaxOut[12];

			for(int i = 0; i < 12; i++)
			{
				fMaxOut[i] = 0;
			}

			BOOL bSetTap;
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

				bSetTap = FALSE;
				if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
				{
					g_nWeekTap = GetTapCode_EVTECT(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
				{
					g_nWeekTap = GetTapCode_PNS331(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
				{
					g_nWeekTap = GetTapCode_EVTECT_Ex1(fMaxOut, TRUE, WeekTap[nIndex]);
					bSetTap = TRUE;
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
				{
					g_nWeekTap = GetTapCode_L336D(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
					bSetTap = TRUE;
				}

				if(bSetTap)
				{
					m_nDCTap = g_nWeekTap;
					m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
					g_oDrvMutex.lock();
					ioctl(m_nfd, 0x125, m_nDCTap); //实验过程中档位不变
					g_oDrvMutex.unlock();
				}
			}

			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

				g_nWeekTap = GetTapCode_ADMU(fMaxOut, TRUE, NULL, WeekTap[nIndex], 0);
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap); //实验过程中档位不变
				g_oDrvMutex.unlock();
			}
		}

		int nHarmGradientIndex = pTmt->m_oHarmParas.m_oHarmGradient.nHarmIndex;

		if(nHarmGradientIndex > MAX_HARM_COUNT - 1)
		{
			nHarmGradientIndex = MAX_HARM_COUNT - 1;
		}

		oGradientParas.m_bManuDc = FALSE;
		Gradient_Manu_Harm(pszDrv, oGradientParas, nHarmGradientIndex, MAX_HARM_COUNT - 1);
		int nDirection = 0;
		float fGradientAmp;

		if(oGradientParas.m_nType == GRADIENT_AMP)
		{
			if(oGradientParas.m_fStart > oGradientParas.m_fStop)
			{
				nDirection = -1;
				fGradientAmp = oGradientParas.m_fStart;
			}
			else
			{
				nDirection = 1;
				fGradientAmp = oGradientParas.m_fStop;
			}
		}

		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
				MAX_HARM_COUNT - 1, FALSE, nDirection, nHarmGradientIndex, fGradientAmp, g_theSystemConfig->m_fAuxDC_Vol);

		if(g_theSystemConfig->m_nHasDigital != 0)
		{
			SetGooseValue_ManuTest(&pTmt->m_oHarmParas.m_oGoosePub[0], TRUE);
		}

		return;
	}

	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	memset(pDrv, 0, sizeof(Drv_ManuData));

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		BOOL bRet = CSttDeviceBase::g_pSttDeviceBase->CheckCurrLoadIsSafe(pTmt->m_oHarmParas.m_uiCUR, FALSE);

		if(!bRet)
		{
			CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("[error] 电流幅值超限"));

			if(!bIsStartTest)
			{
				CSttDeviceBase::g_pSttDeviceBase->SetTestStop();
			}

			CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
			pSttTestBase->ReturnTestStateEvent_TestFinish(0, 0, FALSE);

			return;
		}
	}

	Drv_ManuBin oBiSetting;
	memset(&oBiSetting, 0, sizeof(Drv_ManuBin));
	oBiSetting.nBinIsStop = false;

	if(pTmt->m_oHarmParas.m_bBinStop)
	{
		oBiSetting.nBinIsStop = true;//开入停止
	}

	oBiSetting.nMdelay = pTmt->m_oHarmParas.m_oHarmGradient.fTrigDelay * 1000;
	SetTestCommBi(oBiSetting.oTrip, pTmt->m_oHarmParas.m_oBinaryConfig.m_nBinLogic,
				  pTmt->m_oHarmParas.m_oBinaryConfig.m_binIn, pTmt->m_oHarmParas.m_oBinaryConfig.m_binInEx);
	SetManualBI((char *)&oBiSetting, sizeof(Drv_ManuBin));

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		int nHarmCount;

		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			nHarmCount = pModule->m_oModuleAttr.m_nHarmCount;
			Manual_volt(pTmt->m_oHarmParas.m_uiVOL, pszDrv, nHarmCount, nIndex);
		}

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			nHarmCount = pModule->m_oModuleAttr.m_nHarmCount;
			Manual_current(pTmt->m_oHarmParas.m_uiCUR, pszDrv, nHarmCount, nIndex);
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			nHarmCount = pModule->m_oModuleAttr.m_nHarmCount;
			Manual_UI(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR, pszDrv,
					  nHarmCount, nIndex);
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		int nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U;
		nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_I;
		nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_UI;
		int nModuleCnt;

		if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
		{
			SetGooseValue_ManuTest(&pTmt->m_oHarmParas.m_oGoosePub[0], bIsStartTest);
			nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_D;
			BOOL bIsFt3;

			for(int i = 0; i < nModuleCnt; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

				if(m_oCIEC61850CfgMngr.m_nUseSmv92 == SMVTYPE_92)
				{
					bIsFt3 = FALSE;
				}
				else
				{
					bIsFt3 = TRUE;
				}

				//BASE
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
												  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat, pModule, 1, bIsFt3);
				BOOL bHarmValid;
				int nHarmTotal = 0;

				for(int m = 1; m < 31; m++)
				{
					bHarmValid = TranslateDigitalVoltCurrentBuffer(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
								 pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1), pModule, m + 1, bIsFt3);

					if(bHarmValid)
					{
						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					TranslateDigitalVoltCurrentBuffer(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
													  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1), pModule, -1, bIsFt3);
				}

				pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].nDWcnt = DIGITAL_CHANNEL_MAX * 3 * 31;
			}
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_FT3 > 0)
		{
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_D;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
			nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_FT3;

			for(int i = 0; i < nModuleCnt; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_FT3[i];
				//BASE
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
												  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat, pModule, 1, TRUE);
				BOOL bHarmValid;
				int nHarmTotal = 0;

				for(int m = 1; m < 31; m++)
				{
					bHarmValid = TranslateDigitalVoltCurrentBuffer(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
								 pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1), pModule, m + 1, TRUE);

					if(bHarmValid)
					{
						nHarmTotal++;
					}
				}

				if(nHarmTotal < 30)
				{
					TranslateDigitalVoltCurrentBuffer(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
													  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat + DIGITAL_CHANNEL_MAX * 3 * (nHarmTotal + 1), pModule, -1, TRUE);
				}

				pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].nDWcnt = DIGITAL_CHANNEL_MAX * 3 * 31;
			}
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_ADMU > 0)
		{
			nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_ADMU;
			pDrv->oDrv_ADMUHarm.nModuleCnt = nModuleCnt;

			for(int i = 0; i < nModuleCnt; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[i];
				pDrv->oDrv_ADMUHarm.nModule[i] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
				pDrv->oDrv_ADMUHarm.oHarmParam[i].dat[0] = 2;//片选 10
				//不同数字板的硬件相位补偿不同
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
												  pDrv->oDrv_ADMUHarm.oHarmParam[i].dat + 1, pModule, 1, TRUE);
				pDrv->oDrv_ADMUHarm.oHarmParam[i].nDWcnt = 1+ DIGITAL_CHANNEL_MAX * 3;
			}
		}
	}

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		BOOL bHasSetTap = FALSE;
		BOOL bSetTap;

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			bSetTap = FALSE;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
			{
				Manual_Week_PN_Main(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
									pszDrv, 31, nIndex, FALSE, FALSE);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
			{
				Manual_Week_PIA48S(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
								   pszDrv, 31, nIndex, FALSE, FALSE);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
			{
				Manual_Week_EVTECT(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
								   pszDrv, 31, nIndex, FALSE, FALSE);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				Manual_Week_PNS331(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
								   pszDrv, 31, nIndex, FALSE, FALSE);				
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
			{
				Manual_Week_L336D(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
								  pszDrv, 31, nIndex, FALSE, FALSE);				
				bSetTap = TRUE;
			}
			else
			{
			}

			if(bSetTap)
			{
				bHasSetTap = TRUE;
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap);
				g_oDrvMutex.unlock();
			}
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			Manual_Week_ADMU(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
							   pszDrv, 31, nIndex, FALSE, FALSE);
			m_nDCTap = g_nWeekTap;
			m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x125, m_nDCTap);
			g_oDrvMutex.unlock();
			bHasSetTap = TRUE;
		}

		if(bHasSetTap)
		{
			Sleep(100);
		}
	}

	SetTestCommBo(pDrv->oDrvComBoSta, pTmt->m_oHarmParas.m_oBinaryConfig.m_binOut,
				  pTmt->m_oHarmParas.m_oBinaryConfig.m_binOutEx);

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oHarmParas.m_uiVOL, pTmt->m_oHarmParas.m_uiCUR,
				MAX_HARM_COUNT - 1, FALSE, 0, 0, 0, g_theSystemConfig->m_fAuxDC_Vol);
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x300, 0);
	write(m_nfd, pszDrv, sizeof(Drv_ManuData));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::tmt_to_drv_Gradient(tmt_GradientParas *pParas, int nMode)
{
	CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas.m_nTestMode = pParas->m_nTestMode;

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		float fMaxOut[12];

		for(int i = 0; i < 12; i++)
		{
			fMaxOut[i] = 0;
		}

		BOOL bSetTap;
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			bSetTap = FALSE;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
			{
				g_nWeekTap = GetTapCode_PIA12DS(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
			{
				g_nWeekTap = GetTapCode_EVTECT(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				g_nWeekTap = GetTapCode_PNS331(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
			{
				g_nWeekTap = GetTapCode_EVTECT_Ex1(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
			{
				g_nWeekTap = GetTapCode_DC6U10V(fMaxOut, TRUE, WeekTap[nIndex], 0);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
			{
				g_nWeekTap = GetTapCode_DC6I20mA(fMaxOut, TRUE, WeekTap[nIndex], 0);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
			{
				g_nWeekTap = GetTapCode_L336D(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}

			if(bSetTap)
			{
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap); //实验过程中档位不变
				g_oDrvMutex.unlock();
			}
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

			g_nWeekTap = GetTapCode_ADMU(fMaxOut, TRUE, NULL, WeekTap[nIndex], 0);
			m_nDCTap = g_nWeekTap;
			m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x125, m_nDCTap); //实验过程中档位不变
			g_oDrvMutex.unlock();
		}
	}

	char *pszDrv = stt_test_get_drvparas_buff();
	DrvDegressPara *pDrvPara = (DrvDegressPara *)pszDrv;
	memset(pDrvPara, 0, sizeof(DrvDegressPara));
	pDrvPara->mode = nMode;
	pDrvPara->isReturn = pParas->m_nTestMode;
	pDrvPara->timeDiv = pParas->m_fStepTime * 1000;

	if(pDrvPara->timeDiv < 1)
	{
		pDrvPara->timeDiv = 1;
	}

	pDrvPara->timeBfChg = pParas->m_fPrepareTime * 1000;
	pDrvPara->timeBfFault = pParas->m_fPreFaultTime * 1000;
	pDrvPara->boFaultFlipnSec = 0;
	pDrvPara->boFaultFlipSec = 0;
	pDrvPara->trip.nBiRef = 0;
	SetTestCommBi(pDrvPara->trip, pParas->m_nBinLogic, pParas->m_binIn, pParas->m_binInEx);
	SetTestCommBo(pDrvPara->boBfChange, pParas->m_binOut[0], pParas->m_binOutEx[0]);
	memcpy(&pDrvPara->boBfFault, &pDrvPara->boBfChange, sizeof(DrvComBoStatus));
	SetTestCommBo(pDrvPara->boFault, pParas->m_binOut[1], pParas->m_binOutEx[1]);
	memcpy(&m_oGradientBo_BfFault, &pDrvPara->boBfFault, sizeof(DrvComBoStatus));
	memcpy(&m_oGradientBo_Fault, &pDrvPara->boFault, sizeof(DrvComBoStatus));
	tmt_GradientParas &oDevBaseParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;

	if(nMode == 0)
	{
		Gradient_NormalPara(&pDrvPara->AcPara,  oDevBaseParas.m_uiVOL[0], oDevBaseParas.m_uiCUR[0], 1, 0);
		Gradient_NormalPara(&pDrvPara->AcPara, oDevBaseParas.m_uiVOL[1], oDevBaseParas.m_uiCUR[1], 1, 1);
		Gradient_NormalPara(&pDrvPara->AcPara, oDevBaseParas.m_uiVOL[2], oDevBaseParas.m_uiCUR[2], 1, 2);
	}
	else
	{
		Gradient_NormalPara(&pDrvPara->AcPara,  pParas->m_uiVOL[0], pParas->m_uiCUR[0], 1, 0);
		Gradient_NormalPara(&pDrvPara->AcPara, pParas->m_uiVOL[1], pParas->m_uiCUR[1], 1, 1);
	}

	Gradient_FaultCalc(pDrvPara, oDevBaseParas, nMode);

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x309, 0);
	write(m_nfd, pDrvPara, sizeof(DrvDegressPara));
	g_oDrvMutex.unlock();

	int nDirection = 0;
	float fGradientAmp;
	tmt_GradientParas &oGradientParas = CSttDeviceBase::g_pSttDeviceBase->m_oGradientParas;

	if(oGradientParas.m_nType == GRADIENT_AMP)
	{
		if(oGradientParas.m_fStart > oGradientParas.m_fStop)
		{
			nDirection = -1;
			fGradientAmp = oGradientParas.m_fStart;
		}
		else
		{
			nDirection = 1;
			fGradientAmp = oGradientParas.m_fStop;
		}
	}

	if(g_theSystemConfig->m_nHasAnalog != 0)
		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pParas->m_uiVOL[2],
				pParas->m_uiCUR[2], 31, FALSE, nDirection, 1, fGradientAmp, g_theSystemConfig->m_fAuxDC_Vol);

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		SetGooseValue_ManuTest(&pParas->m_oGoosePub[0], TRUE);
	}
}

void CSttDeviceComm::tmt_to_drv_Gradient_NeedStepsValue(tmt_GradientParas *pParas)
{
	tmt_to_drv_Gradient(pParas, 1);
}

/************基础实验部分*************/

/************状态序列部分*************/
void CSttDeviceComm::tmt_to_drv_StatePara(tmt_StateParas *pTmt)
{
	char *pszDrv = stt_test_get_drvparas_buff();
	Drv_StatePara *pDrv = (Drv_StatePara *)pszDrv;
	memset(pDrv, 0, sizeof(Drv_StatePara));
	pDrv->nStateCount = pTmt->m_nStateNumbers;

	if(pDrv->nStateCount > g_nStateCount)
	{
		pDrv->nStateCount = g_nStateCount;
	}

	pDrv->nIsLoop = pTmt->m_nRepeatNumbers;

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x149, 0);//只有开出保持，无触发
	g_oDrvMutex.unlock();

	pDrv->nbiRefFirst = pTmt->m_nBinTripRef;
	Drv_BIStatus gooseInit;
	memset(&gooseInit, 0, sizeof(Drv_BIStatus));
	pDrv->oGooseInit = gooseInit;

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x301, 0);
	write(m_nfd, pszDrv, sizeof(Drv_StatePara));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::DealSmvAbn(structSVabnPara  *pSVabn, tmt_StateAbnormalSMV oTmtAbnPara)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[0];
	pSVabn->module = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
	pSVabn->group = 1 << oTmtAbnPara.m_nGroupIndex;
	pSVabn->ptCnt = 80;

	// 发送方式：0-每周波发送1-每秒发送
	if(oTmtAbnPara.m_nSendMode == 0)
	{
		pSVabn->abnCycle = oTmtAbnPara.m_nCircleNum_TypeCircle;
		pSVabn->normalCycle = 0;
		pSVabn->loop = 1;
	}
	else
	{
		pSVabn->abnCycle = oTmtAbnPara.m_nCircleNum_TypeSecond;
		pSVabn->normalCycle = 50 - pSVabn->abnCycle;
		pSVabn->loop = oTmtAbnPara.m_nSendTime_TypeSecond;
	}

	// 异常类型：1-丢帧2-抖动3-飞点4-错序
	int nDT = 1000000 / m_oCIEC61850CfgMngr.m_o92Mngr.GetSmv92Sample(); //250
	nDT = nDT * 10;
	unsigned int nValid = 0;

	switch(oTmtAbnPara.m_nAbnormalType)
	{
		case 1:
		{
			for(int i = 0; i < 80; i++)
			{
				pSVabn->stSVabn[i].pt = i;
				pSVabn->stSVabn[i].jitter = nDT;
				pSVabn->stSVabn[i].errcmpt = 0;
				pSVabn->stSVabn[i].flyPtEn = 0;
				pSVabn->stSVabn[i].flyPtV = 0;
				pSVabn->stSVabn[i].flyPtI = 0;
				nValid = oTmtAbnPara.m_nAbnormalPoint[i];

				if(nValid)
				{
					pSVabn->stSVabn[i].isLost = 1;
				}
				else
				{
					pSVabn->stSVabn[i].isLost = 0;
				}
			}

			break;
		}

		case 2:
		{
			int nErrCount = 0;

			for(int i = 0; i < 78; i++)
			{
				nValid = oTmtAbnPara.m_nAbnormalPoint[i];

				if(nValid)
				{
					nErrCount++;
				}
			}

			int nCount = 0;
			bool bMark = true;

			for(int i = 0; i < 80; i++)
			{
				pSVabn->stSVabn[i].pt = i;
				pSVabn->stSVabn[i].isLost = 0;
				pSVabn->stSVabn[i].errcmpt = 0;
				pSVabn->stSVabn[i].flyPtEn = 0;
				pSVabn->stSVabn[i].flyPtV = 0;
				pSVabn->stSVabn[i].flyPtI = 0;
				nValid = oTmtAbnPara.m_nAbnormalPoint[i];

				if(i >= 78)
				{
					nValid = 0;
				}

				if(nValid)
				{
					nCount++;

					if(nCount % 2 == 1)
					{
						pSVabn->stSVabn[i].jitter =
							nDT - oTmtAbnPara.m_uFrampShakingValue / 100;
					}
					else if(nCount % 2 == 0)
					{
						pSVabn->stSVabn[i].jitter =
							nDT + oTmtAbnPara.m_uFrampShakingValue / 100;
					}
				}
				else
				{
					if(nCount == nErrCount && nErrCount % 2 == 1 && bMark)
					{
						pSVabn->stSVabn[i].jitter =
							nDT + oTmtAbnPara.m_uFrampShakingValue / 100;
						bMark = false;
					}
					else
					{
						pSVabn->stSVabn[i].jitter = nDT;
					}
				}
			}

			break;
		}

		case 3:
		{
			float	fFlyPointVolt, fFlyPointCurrent;

			for(int i = 0; i < 80; i++)
			{
				pSVabn->stSVabn[i].pt = i;
				pSVabn->stSVabn[i].isLost = 0;
				pSVabn->stSVabn[i].jitter = nDT;
				pSVabn->stSVabn[i].errcmpt = 0;
				pSVabn->stSVabn[i].flyPtEn = 0;
				pSVabn->stSVabn[i].flyPtV = 0;
				pSVabn->stSVabn[i].flyPtI = 0;
				nValid = oTmtAbnPara.m_nAbnormalPoint[i];

				if(nValid)
				{
					//CIEC92Mngr m_ChanMapID 的顺序 Ua1-1 Ub1-2 Uc1-3 Ia1-17 Ib1-18 Ic1-19
					for(int j = 0; j < 3; j++)
					{
						if(oTmtAbnPara.m_nVolChEnable[j])
						{
							pSVabn->stSVabn[i].flyPtEn |= 1 << j;
						}

						if(oTmtAbnPara.m_nCurChEnable[j])
						{
							pSVabn->stSVabn[i].flyPtEn |= 1 << (j + 16);
						}
					}

					fFlyPointVolt = oTmtAbnPara.m_fFlyPointVolt;// 飞点电压值
					fFlyPointCurrent = oTmtAbnPara.m_fFlyPointCurrent;// 飞点电流值
					pSVabn->stSVabn[i].flyPtV = TransDigitalChannelAmp(fFlyPointVolt, 0, TRUE, STT_MODULE_TYPE_VOLT, FALSE, 0) / 2;
					pSVabn->stSVabn[i].flyPtI = TransDigitalChannelAmp(fFlyPointCurrent, 0, TRUE, STT_MODULE_TYPE_CURRENT, FALSE, 0) / 2;
				}
			}

			break;
		}

		case 4:
		{
			int nBit = oTmtAbnPara.m_nOutOfOrderValue;
			/***
			for(int i =0;i<80;i++)
			{
				pSVabn->stSVabn[i].pt = i;
				pSVabn->stSVabn[i].isLost = 0;
				pSVabn->stSVabn[i].jitter = 2500;
				pSVabn->stSVabn[i].errcmpt = 0;
				pSVabn->stSVabn[i].flyPtEn = 0;
				pSVabn->stSVabn[i].flyPtV = 0;
				pSVabn->stSVabn[i].flyPtI = 0;
			}
			int nDeal[80];
			for(int i =0;i<80;i++)
			{
				nDeal[i] = 0;
			}
			for(int i =0;i<80;i++)
			{
				nValid = oTmtAbnPara.m_nAbnormalPoint[i];
				if(nDeal[i] == 1)
					continue;
				if(nValid)
				{

					int nMove;
					nMove = nBit;
					nDeal[i] = 1;
					for(int j =i+nBit;j<80;j+=nBit)
					{
						nValid = oTmtAbnPara.m_nAbnormalPoint[j];
						nDeal[j] = 1;
						if(nValid)
						{
							nMove += nBit;
							pSVabn->stSVabn[j].errcmpt -= nBit;
						}
						else
						{
							pSVabn->stSVabn[i].errcmpt = nMove;
							pSVabn->stSVabn[j].errcmpt -=nBit;
							break;
						}
					}
				}
			}
			***/
			QList<int> list1eft;
			QList<int> listmid;
			QList<int> listright;
			QList<int> list;
			list.clear();
			bool ncmpt[80];

			for(int i = 0; i < 80; i++)
			{
				pSVabn->stSVabn[i].pt = i;
				pSVabn->stSVabn[i].isLost = 0;
				pSVabn->stSVabn[i].jitter = nDT;
				pSVabn->stSVabn[i].errcmpt = 0;
				pSVabn->stSVabn[i].flyPtEn = 0;
				pSVabn->stSVabn[i].flyPtV = 0;
				pSVabn->stSVabn[i].flyPtI = 0;

				if((i + nBit) < 79)
				{
					nValid = oTmtAbnPara.m_nAbnormalPoint[i];

					if(nValid)
					{
						ncmpt[i] = TRUE;
					}
					else
					{
						ncmpt[i] = FALSE;
					}
				}
				else
				{
					ncmpt[i] = FALSE;
				}

				list.append(i);
			}

Loop:

			for(int i = 0; i < 80; i++)
			{
				int nVal = list.at(i);
				list1eft.clear();
				listmid.clear();
				listright.clear();

				if(ncmpt[nVal])
				{
					list1eft = list.mid(0, i);
					listmid = list.mid(i + 1, nBit);
					listright = list.mid(i + nBit + 1, 80 - (i + nBit));
					list.clear();
					list.append(list1eft);
					list.append(listmid);
					list.append(nVal);
					list.append(listright);
					ncmpt[nVal] = FALSE;
					goto Loop;
				}
			}

			for(int i = 0; i < 80; i++)
			{
				pSVabn->stSVabn[i].errcmpt = list.at(i) - i;
			}

			break;
		}

		default:
		{
			for(int i = 0; i < 80; i++)
			{
				pSVabn->stSVabn[i].pt = i;
				pSVabn->stSVabn[i].isLost = 0;
				pSVabn->stSVabn[i].jitter = nDT;
				pSVabn->stSVabn[i].errcmpt = 0;
				pSVabn->stSVabn[i].flyPtEn = 0;
				pSVabn->stSVabn[i].flyPtV = 0;
				pSVabn->stSVabn[i].flyPtI = 0;
			}

			break;
		}
	}
}

BOOL CSttDeviceComm::tmt_to_drv_SmvAbn(Drv_AbnPara *pAbnPara, tmt_StateAbnormalSMV oTmtAbnPara, BOOL bIsUseDefault)
{
	if(oTmtAbnPara.m_nGroupIndex >= m_oCIEC61850CfgMngr.m_o92Mngr.data_92.size())
	{
		pAbnPara->abnType = 0;
		return FALSE;
	}

	tmt_sv_92 oTMtSmvAbn;
	tmt_sv_92 oIecConfigSmv = m_oCIEC61850CfgMngr.m_o92Mngr.data_92.at(oTmtAbnPara.m_nGroupIndex);
	oTMtSmvAbn.m_VLanID = oIecConfigSmv.m_VLanID;
	oTMtSmvAbn.m_VLanPri = oIecConfigSmv.m_VLanPri;
	oTMtSmvAbn.m_SyncMode = oIecConfigSmv.m_SyncMode;
	oTMtSmvAbn.m_NetType = oIecConfigSmv.m_NetType;
	oTMtSmvAbn.m_ConfRev = oIecConfigSmv.m_ConfRev;
	oTMtSmvAbn.m_AppID = oIecConfigSmv.m_AppID;
	oTMtSmvAbn.m_MacDesc = oIecConfigSmv.m_MacDesc;
	oTMtSmvAbn.m_MacSrc = oIecConfigSmv.m_MacSrc;
	oTMtSmvAbn.m_SVID = oIecConfigSmv.m_SVID;
	oTMtSmvAbn.m_Datset = oIecConfigSmv.m_Datset;
	unsigned int nQuality[50];

	for(int i = 0; i < 50; i++)
	{
		nQuality[i] = 0;
	}

	if(oTmtAbnPara.m_nAbnormalType == 0)
	{
		pAbnPara->abnType = 0;

		if(bIsUseDefault)
		{
			pAbnPara->abnType = ABN_TYPE_SMV;
			m_oCIEC61850CfgMngr.DealSmvAbnPacket(&pAbnPara->stSVItem, oTmtAbnPara, oTMtSmvAbn, nQuality); //SMV异常控制块参数
			pAbnPara->reConfig = 1;
			m_oCIEC61850CfgMngr.DealSmvAbnConfig(&pAbnPara->stSendCfg, oTmtAbnPara.m_nGroupIndex, 0, 0, TRUE);
		}

		return FALSE;
	}

	pAbnPara->abnType = ABN_TYPE_SMV;

	if(oTmtAbnPara.m_oSmvMsg.m_nUseOrigPkgSet > 0)
	{
		oTMtSmvAbn.m_VLanID = QString::number(oTmtAbnPara.m_oSmvMsg.m_nVLanID);
		oTMtSmvAbn.m_VLanPri = QString::number(oTmtAbnPara.m_oSmvMsg.m_nVLanPriority);
		oTMtSmvAbn.m_SyncMode = QString::number(oTmtAbnPara.m_oSmvMsg.m_nSyn);

		if(oTmtAbnPara.m_oSmvMsg.m_nNetType == 0)
		{
			oTmtAbnPara.m_oSmvMsg.m_nNetType = 0x88ba;
		}

		oTMtSmvAbn.m_NetType = QString("%1").arg(oTmtAbnPara.m_oSmvMsg.m_nNetType & 0xFFFF, 4, 16, QChar('0'));
		oTMtSmvAbn.m_ConfRev = QString::number(oTmtAbnPara.m_oSmvMsg.m_nVersion);
		oTMtSmvAbn.m_AppID = QString::number(oTmtAbnPara.m_oSmvMsg.m_nAppID, 16);
		oTMtSmvAbn.m_MacDesc = QString(oTmtAbnPara.m_oSmvMsg.m_strMacAddrDst).replace("-", "").trimmed();
		oTMtSmvAbn.m_MacDesc = oTMtSmvAbn.m_MacDesc.rightJustified(12, QChar('0'));
		oTMtSmvAbn.m_MacSrc = QString(oTmtAbnPara.m_oSmvMsg.m_strMacAddrSrc).replace("-", "").trimmed();
		oTMtSmvAbn.m_MacSrc = oTMtSmvAbn.m_MacSrc.rightJustified(12, QChar('0'));
		oTMtSmvAbn.m_SVID = QString(oTmtAbnPara.m_oSmvMsg.m_strSVID);
		oTMtSmvAbn.m_Datset = QString(oTmtAbnPara.m_oSmvMsg.m_strDataset);
	}

	for(int i = 0; i < 50; i++)
	{
		if(oTmtAbnPara.m_nInvalidChanel[i] && oTmtAbnPara.m_nAbnormalType == 8)//8-品质异常
		{
			nQuality[i] = oTmtAbnPara.m_nQualityBit[0];

			for(int j = 1; j < 12; j++)
			{
				nQuality[i] |= oTmtAbnPara.m_nQualityBit[j] << (j + 1);
			}
		}
	}

	BOOL bRet;
	bRet = m_oCIEC61850CfgMngr.DealSmvAbnPacket(&pAbnPara->stSVItem, oTmtAbnPara, oTMtSmvAbn, nQuality); //SMV异常控制块参数

	if(!bRet)
	{
		return FALSE;
	}

	DealSmvAbn(&pAbnPara->stSVabn, oTmtAbnPara); //SMV异常类型配置参数  异常类型：1-丢帧2-抖动3-飞点4-错序
	pAbnPara->reConfig = 0;

	if(bIsUseDefault)
	{
		pAbnPara->reConfig = 1;
		m_oCIEC61850CfgMngr.DealSmvAbnConfig(&pAbnPara->stSendCfg, oTmtAbnPara.m_nGroupIndex, 0, 0, TRUE);
	}

	// 异常类型：
	if(oTmtAbnPara.m_nAbnormalType == 7)
	{
		//7-序号偏差 只改发送初值 不改相位相关的码值
		pAbnPara->reConfig = 1;
		m_oCIEC61850CfgMngr.DealSmvAbnConfig(&pAbnPara->stSendCfg, oTmtAbnPara.m_nGroupIndex,
											 oTmtAbnPara.m_nAbnormalType, oTmtAbnPara.m_nSeqNumDevtValue);
	}
	else if(oTmtAbnPara.m_nAbnormalType == 5)
	{
		//5-延时偏差 改相位相关的码值及发送初值
		pAbnPara->reConfig = 1;
		m_oCIEC61850CfgMngr.DealSmvAbnConfig(&pAbnPara->stSendCfg, oTmtAbnPara.m_nGroupIndex,
											 oTmtAbnPara.m_nAbnormalType, oTmtAbnPara.m_nDelayDeviation);
		m_nSmvAbnDelayOffset = oTmtAbnPara.m_nDelayDeviation;
	}
	else if(oTmtAbnPara.m_nAbnormalType == 6)
	{
		//6-延时变化 只改延时通道值 不改相位相关的码值及发送初值
		pAbnPara->reConfig = 1;
		m_oCIEC61850CfgMngr.DealSmvAbnConfig(&pAbnPara->stSendCfg, oTmtAbnPara.m_nGroupIndex, 0, 0, TRUE);
	}

	return TRUE;
}

BOOL CSttDeviceComm::tmt_to_drv_GseAbn(Drv_AbnPara *pAbnPara, tmt_StatePara  *pTmt_paraState, tmt_StatePara  *pTmt_paraPreState)
{
	pAbnPara->abnType = ABN_TYPE_GOOSE;
	BOOL bRet;
	bRet = m_oCIEC61850CfgMngr.DealGseAbnConfig(&pAbnPara->stGSItem, pTmt_paraState, pTmt_paraPreState);

	if(!bRet)
	{
		pAbnPara->abnType = 0;
		return FALSE;
	}

	return TRUE;
}

void CSttDeviceComm::SetManuOrStateAuxVolt(unsigned int &pDrv_Aux, float fUdc)
{
	pDrv_Aux = 0;

	if(g_theDeviceSystemParameter->m_nModuleCount_U == 0)
	{
		return;
	}

	long nValue = TransAuxDcVolt(fUdc);
	BOOL bAuxDcOutput = FALSE;

	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule != NULL)
		{
			float fUdcMax = 0;
			PSTT_CHANNEL_WAVE_ADJUST pChUdcAdj = &pModule->m_oModuleAdjust.m_oTempAdjust[0].m_oChUdcAdj;

			if(pChUdcAdj->m_nGearCount > 0)
			{
				fUdcMax = pChUdcAdj->m_oChGearAdj[pChUdcAdj->m_nGearCount - 1].m_fGearValue;
			}

			long nModuleIndex = pModule->m_oModuleAttr.m_nModuleIndex;

			if(fUdcMax > EPSINON && nModuleIndex <= ADJUST_MAX_MODULE_COUNT)
			{
				nValue |= ModuleIndexTransToDrv(nModuleIndex);
				bAuxDcOutput = TRUE;
			}
		}
	}

	if(bAuxDcOutput)
	{
		pDrv_Aux = nValue;
		g_fAuxVolt = fUdc;
	}
}

void CSttDeviceComm::ProStateDAPara(DeviceDAPara *pDAPara, float fAuxMax, tmt_StatePara  &oTmt_FirstState)
{	
	DeviceDAPara *pDevBaseDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
	DeviceDAPara *pDAParaForState2 = &CSttDeviceBase::g_pSttDeviceBase->m_oDAParaForState2;
	int nModuleIndex = 0;
	memcpy(pDAPara, pDevBaseDAPara, sizeof(DeviceDAPara));
	memcpy(pDAParaForState2, pDevBaseDAPara, sizeof(DeviceDAPara));

	//VOLT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(pModule->m_oModuleAttr.m_fChMax, fAuxMax, nIndex, FALSE);
		pDAPara->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
		pDAParaForState2->nvolt[nIndex] = pDevBaseDAPara->nvolt[nIndex];
	}

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_U;
	CSttPowerCtrlBase *pSttPowerCtrlBase = NULL;

	//CURRENT
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pSttPowerCtrlBase != NULL)
		{
			pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
			pDevBaseDAPara->nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
			pDAPara->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];
			pDAParaForState2->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];
		}
	}

	nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
	pSttPowerCtrlBase = NULL;

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

		if(pSttPowerCtrlBase != NULL)
		{
			pSttPowerCtrlBase->SetVoltDA_State();
			pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
			pDevBaseDAPara->nvolt[nModuleIndex + nIndex] = pSttPowerCtrlBase->GetModuleDA();
			pDAPara->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];
			pDAParaForState2->nvolt[nModuleIndex + nIndex] = pDevBaseDAPara->nvolt[nModuleIndex + nIndex];
		}
	}

#ifdef _MainBoard_PN_

	if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
	{
		PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

		if(pModule_UI != NULL)
		{
			if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
			{
				long nCurModuleIndex = -1;

				if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
				{
					nCurModuleIndex += 1;
				}

				if(g_theDeviceSystemParameter->m_nModuleCount_I > 0)
				{
					nCurModuleIndex += 1;
				}

				if(nCurModuleIndex >= 0)
				{
					pDAPara->nvolt[nCurModuleIndex + 1] =
						(pDAPara->nvolt[nCurModuleIndex] >> 8) & 0xFF;
					pDAParaForState2->nvolt[nCurModuleIndex + 1] =
						(pDAParaForState2->nvolt[nCurModuleIndex] >> 8) & 0xFF;
				}
			}
		}
	}

#endif
}

void CSttDeviceComm::tmt_to_drv_StateItem(tmt_StateParas *pTmt, long nAbnType)
{
	if(pTmt->m_nStateNumbers == 0)
	{
		return;
	}

	m_bRampFreq = FALSE;
	char *pBuf = stt_test_get_drvparas_buff();
	long nStateNum;
	tmt_StatePara  oTmt_paraState, oTmt_FirstState;
	CSttDeviceBase::g_pSttDeviceBase->m_nCurStateCount = pTmt->m_nStateNumbers;
	DeviceDAPara oDAPara;
	float fAuxMax = g_theSystemConfig->m_fAuxDC_Vol;
	BOOL  bSetAux = FALSE;

	if(fabs(g_theSystemConfig->m_fAuxDC_Vol) < 0.001)
	{
		bSetAux = TRUE;//系统参数辅助直流等于0,使能状态内输出
		BOOL bHasState = FALSE;

		for(nStateNum = 0; nStateNum < g_nStateCount; nStateNum++)
		{
			oTmt_paraState = pTmt->m_paraState[nStateNum];

			if(!oTmt_paraState.m_bSelected)
			{
				continue;
			}

			if(oTmt_paraState.m_fVolAux > fAuxMax)
			{
				fAuxMax = oTmt_paraState.m_fVolAux;
			}

			if(!bHasState)
			{
				bHasState = TRUE;

				if(g_theSystemConfig->m_nHasAnalog != 0)
				{
					oTmt_FirstState = pTmt->m_paraState[nStateNum];
				}
			}
		}
	}

	//DAPara
	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		CSttDeviceBase::g_pSttDeviceBase->DAPowerCtrl();
		CSttDeviceBase::g_pSttDeviceBase->m_bUseDAParaForState2 = TRUE;
		ProStateDAPara(&oDAPara, fAuxMax, oTmt_FirstState);
	}
	else
	{
		CSttDeviceBase::g_pSttDeviceBase->DAPowerCtrl();
		DeviceDAPara *pDevBaseDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
		memcpy(&oDAPara, pDevBaseDAPara, sizeof(DeviceDAPara));

		if(bSetAux)
		{
			//VOLT
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

				if(pModule == NULL)
				{
					continue;
				}

				CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(0, fAuxMax, nIndex, FALSE);
			}
		}
	}

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		float fMaxOut[12];

		for(int i = 0; i < 12; i++)
		{
			fMaxOut[i] = 0;
		}

		BOOL bSetTap;
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			bSetTap = FALSE;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
			{
				g_nWeekTap = GetTapCode_PIA12DS(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
			{
				g_nWeekTap = GetTapCode_EVTECT(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				g_nWeekTap = GetTapCode_PNS331(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
			{
				g_nWeekTap = GetTapCode_EVTECT_Ex1(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
			{
				g_nWeekTap = GetTapCode_DC6U10V(fMaxOut, TRUE, WeekTap[nIndex], 0);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
			{
				g_nWeekTap = GetTapCode_DC6I20mA(fMaxOut, TRUE, WeekTap[nIndex], 0);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
			{
				g_nWeekTap = GetTapCode_PN_DC6U6I(fMaxOut, TRUE, WeekTap[nIndex]);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
			{
				g_nWeekTap = GetTapCode_L336D(fMaxOut, TRUE, NULL, WeekTap[nIndex]);
				bSetTap = TRUE;
			}

			if(bSetTap)
			{
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap); //实验过程中档位不变
				g_oDrvMutex.unlock();
			}
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

			g_nWeekTap = GetTapCode_ADMU(fMaxOut, TRUE, NULL, WeekTap[nIndex], 0);
			m_nDCTap = g_nWeekTap;
			m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x125, m_nDCTap); //实验过程中档位不变
			g_oDrvMutex.unlock();
		}
	}

	long nStateIndex = 0;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	for(nStateNum = 0; nStateNum < g_nStateCount; nStateNum++)
	{
		oTmt_paraState = pTmt->m_paraState[nStateNum];

		if(!oTmt_paraState.m_bSelected)
		{
			continue;
		}

		pSttTestBase->m_nStateNum[nStateIndex] = nStateNum;
		memset(m_pDrv_StateItem, 0, sizeof(Drv_StateItem));

		if(g_theSystemConfig->m_nHasAnalog != 0)
		{
			BOOL bRet = CSttDeviceBase::g_pSttDeviceBase->CheckCurrLoadIsSafe(oTmt_paraState.m_uiCUR, oTmt_paraState.m_bDC);

			if(!bRet)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 电流超限，Ia1=%.1fA,Ib1=%.1fA,Ic1=%.1fA,Ia2=%.1fA,Ib2=%.1fA,Ic2=%.1fA"),
										   oTmt_paraState.m_uiCUR[0].Harm[1].fAmp,
										   oTmt_paraState.m_uiCUR[1].Harm[1].fAmp,
										   oTmt_paraState.m_uiCUR[2].Harm[1].fAmp,
										   oTmt_paraState.m_uiCUR[3].Harm[1].fAmp,
										   oTmt_paraState.m_uiCUR[4].Harm[1].fAmp,
										   oTmt_paraState.m_uiCUR[5].Harm[1].fAmp);
				pTmt->m_nStateNumbers = 0;
				tmt_to_drv_StatePara(pTmt);
				pSttTestBase->ReturnTestStateEvent_TestFinish(-1, 0, FALSE);
				return;
			}

			if(nStateIndex == 1)
			{
				//如果含时间触发，小于2秒那么不更新电源
				if(oTmt_paraState.m_nTriggerCondition == TMT_MDSTATE_TIMETRIGGER
						|| oTmt_paraState.m_nTriggerCondition == TMT_MDSTATE_TIMEBINTRIGGER)
				{
					if(oTmt_paraState.m_fTimeState < 2.0)
					{
						CSttDeviceBase::g_pSttDeviceBase->m_bUseDAParaForState2 = FALSE;
					}
				}
			}
		}

		m_pDrv_StateItem->nChangemSec = oTmt_paraState.m_nRampTimeGrad;
		m_pDrv_StateItem->oStBo.nTripMode = oTmt_paraState.m_binOut[0].nMode;
		m_pDrv_StateItem->oStBo.nPreTripTime = oTmt_paraState.m_binOut[0].fTimeTrig * 1000;
		m_pDrv_StateItem->oStBo.nOutPutTime = oTmt_paraState.m_binOut[0].fHoldTime * 1000;
		SetTestCommBo(m_pDrv_StateItem->oStBo.boValue, oTmt_paraState.m_binOut, oTmt_paraState.m_binOutEx);

		if(m_pDrv_StateItem->oStBo.nTripMode == 1)
		{
			m_pDrv_StateItem->oStBo.boValue.item[0].nVal1 = 0;

			//开入触发翻转时，需指定具体翻转关联的开出点
			for(int i = 0; i < MAX_BINARYOUT_COUNT; i++) //bovalid
			{
				m_pDrv_StateItem->oStBo.boValue.item[0].nVal1 |=
					oTmt_paraState.m_binOut[i].nState << i;
			}
		}

		if(bSetAux)
		{
			SetManuOrStateAuxVolt(m_pDrv_StateItem->nAuxVolt, oTmt_paraState.m_fVolAux);
		}

		if(g_theSystemConfig->m_nHasAnalog != 0)
		{
			//VOLT
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

				if(pModule == NULL)
				{
					continue;
				}

				State_volt(m_pDrv_StateItem, oTmt_paraState, nIndex);
				State_volt_Gradient(m_pDrv_StateItem, oTmt_paraState, nIndex);
			}

			//CURRENT
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

				if(pModule == NULL)
				{
					continue;
				}

				State_current(m_pDrv_StateItem, oTmt_paraState, nIndex);
				State_current_Gradient(m_pDrv_StateItem, oTmt_paraState, nIndex);
			}

			//UI
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

				if(pModule == NULL)
				{
					continue;
				}

				State_UI(m_pDrv_StateItem, oTmt_paraState, nIndex);
				State_UI_Gradient(m_pDrv_StateItem, oTmt_paraState, nIndex);
			}
		}

		if(g_theSystemConfig->m_nHasDigital != 0)
		{
			for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
			{
				if(oTmt_paraState.m_bDC)
				{
					oTmt_paraState.m_uiVOL[i].Harm[1].fFreq = 0.0f;
				}
			}

			for(int i = 0; i < MAX_CURRENT_COUNT; i++)
			{
				if(oTmt_paraState.m_bDC)
				{
					oTmt_paraState.m_uiCUR[i].Harm[1].fFreq = 0.0f;
				}
			}

			int nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_I;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_UI;
			int nModuleCnt;

			if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
			{
				BOOL bRet, bHasGseAbn;
				m_nSmvAbnDelayOffset = 0;
				bHasGseAbn = FALSE;

				if(nAbnType == ABN_TYPE_SMV)
				{
					BOOL bIsUseDefault = FALSE;
					unsigned int nAbnormalType;

					if(nStateIndex > 0)
					{
						long nPreStateNum = pSttTestBase->GetStateNum(nStateIndex - 1);
						nAbnormalType = pTmt->m_paraState[nPreStateNum].m_oAbnormalSMV.m_nAbnormalType;

						if(nAbnormalType == 5 || nAbnormalType == 6 || nAbnormalType == 7 || nAbnormalType == 8)
						{
							bIsUseDefault = TRUE;
						}
					}
					else
					{
						nAbnormalType = pTmt->m_paraState[0].m_oAbnormalSMV.m_nAbnormalType;
					}

					bRet = tmt_to_drv_SmvAbn(&m_pDrv_StateItem->oAbnPara, oTmt_paraState.m_oAbnormalSMV, bIsUseDefault);

					if(!bRet && oTmt_paraState.m_oAbnormalSMV.m_nAbnormalType > SMV_ABNORMAL_TYPE_NULL)
					{
						CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 状态%d SV异常模拟设置失败"), nStateNum + 1);
					}
				}
				else if(nAbnType == ABN_TYPE_GOOSE)
				{
					if(nStateIndex == 0)
					{
						bRet = tmt_to_drv_GseAbn(&m_pDrv_StateItem->oAbnPara, &oTmt_paraState, NULL);
					}
					else
					{
						long nPreStateNum = pSttTestBase->GetStateNum(nStateIndex - 1);
						bRet = tmt_to_drv_GseAbn(&m_pDrv_StateItem->oAbnPara, &oTmt_paraState, &pTmt->m_paraState[nPreStateNum]);
					}

					if(!bRet)
					{
						CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] 状态%d GOOSE异常模拟设置失败"), nStateNum + 1);
					}
					else
					{
						bHasGseAbn = TRUE;
					}
				}

				BOOL bIsFt3;
				nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_D;

				for(int i = 0; i < nModuleCnt; i++)
				{
					PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

					if(m_oCIEC61850CfgMngr.m_nUseSmv92 == SMVTYPE_92)
					{
						bIsFt3 = FALSE;
					}
					else
					{
						bIsFt3 = TRUE;
					}

					m_pDrv_StateItem->oAcParam.item[nAnalogModuleCnt + i].DWCount = DIGITAL_CHANNEL_MAX * 3 * 2;
					TranslateDigitalVoltCurrentBuffer(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
													  m_pDrv_StateItem->oAcParam.item[nAnalogModuleCnt + i].nVal, pModule, 1, bIsFt3);
					TranslateDigitalVoltCurrentBuffer(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
													  m_pDrv_StateItem->oAcParam.item[nAnalogModuleCnt + i].nVal + DIGITAL_CHANNEL_MAX * 3, pModule, 0, bIsFt3);
					TranslateDigitalVoltCurrentBuffer_Gradient(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
							&m_pDrv_StateItem->oStChange[nAnalogModuleCnt + i], pModule, bIsFt3);
				}

				m_nSmvAbnDelayOffset = 0;//恢复默认值
				SetGooseValue_StateTest(pTmt, nStateIndex, m_pDrv_StateItem, bHasGseAbn);
			}

			if(g_theDeviceSystemParameter->m_nModuleCount_FT3 > 0)
			{
				nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_D;
				nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_WEEK;
				nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_FT3;

				for(int i = 0; i < nModuleCnt; i++)
				{
					PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_FT3[i];
					m_pDrv_StateItem->oAcParam.item[nAnalogModuleCnt + i].DWCount = DIGITAL_CHANNEL_MAX * 3 * 2;
					TranslateDigitalVoltCurrentBuffer(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
													  m_pDrv_StateItem->oAcParam.item[nAnalogModuleCnt + i].nVal, pModule, 1, TRUE);
					TranslateDigitalVoltCurrentBuffer(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
													  m_pDrv_StateItem->oAcParam.item[nAnalogModuleCnt + i].nVal + DIGITAL_CHANNEL_MAX * 3, pModule, 0, TRUE);
					TranslateDigitalVoltCurrentBuffer_Gradient(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
							&m_pDrv_StateItem->oStChange[nAnalogModuleCnt + i], pModule, TRUE);
				}
			}

			if(g_theDeviceSystemParameter->m_nModuleCount_ADMU > 0)
			{
				nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_ADMU;
				m_pDrv_StateItem->oADMUPara.nModulesCnt = nModuleCnt;

				for(int i = 0; i < nModuleCnt; i++)
				{
					PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[i];
					m_pDrv_StateItem->oADMUPara.nModule[i] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
					m_pDrv_StateItem->oADMUPara.oADMUACPara[i].DWCount = 1 + DIGITAL_CHANNEL_MAX * 3 * 2;
					m_pDrv_StateItem->oADMUPara.oADMUACPara[i].nVal[0] = 2;//片选 10

					TranslateDigitalVoltCurrentBuffer(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
													  m_pDrv_StateItem->oADMUPara.oADMUACPara[i].nVal + 1, pModule, 1, TRUE);
					TranslateDigitalVoltCurrentBuffer(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
													  m_pDrv_StateItem->oADMUPara.oADMUACPara[i].nVal + 1 + DIGITAL_CHANNEL_MAX * 3, pModule, 0, TRUE);
					TranslateDigitalVoltCurrentBuffer_Gradient(oTmt_paraState.m_uiVOL, oTmt_paraState.m_uiCUR,
							&m_pDrv_StateItem->oADMUPara.oADMUStChange[i], pModule, TRUE);
				}
			}

			SetFt3Value_StateTest(pTmt, nStateIndex, m_pDrv_StateItem);
		}

		if(g_theSystemConfig->m_nHasWeek != 0)
		{
			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

				if(pModule == NULL)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
				{
					State_Week_PN_Main(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
				{
					State_Week_PIA48S(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
				{
					State_Week_PIA12DS(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
				{
					State_Week_EVTECT(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
				{
					State_Week_PNS331(m_pDrv_StateItem, oTmt_paraState, nIndex);
					State_Week_PNS331_Gradient(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
				{
					State_Week_EVTECT_Ex1(m_pDrv_StateItem, oTmt_paraState, nIndex);
					State_Gradient_Week_EVTECT_Ex1(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
				{
					State_Week_DC6U10V(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
				{
					State_Week_DC6I20mA(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
				{
					State_Week_PN_DC6U6I(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
				else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
				{
					State_Week_L336D(m_pDrv_StateItem, oTmt_paraState, nIndex);
					State_Week_L336D_Gradient(m_pDrv_StateItem, oTmt_paraState, nIndex);
				}
			}

			for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];

				if(pModule == NULL)
				{
					continue;
				}

				State_Week_ADMU(m_pDrv_StateItem, oTmt_paraState, nIndex);
				State_Week_ADMU_Gradient(m_pDrv_StateItem, oTmt_paraState, nIndex);
			}
		}

		setTriger(oTmt_paraState, m_pDrv_StateItem, nStateIndex);
		float fVolCloseAngle = oTmt_paraState.m_oCloseAngle.m_fVolCloseAngle;
		float fCurCloseAngle = oTmt_paraState.m_oCloseAngle.m_fCurCloseAngle;

		if(oTmt_paraState.m_oCloseAngle.m_nFaultIncMode == 1)
		{
			//设置合闸角
			CloseAngle(m_pDrv_StateItem, fVolCloseAngle, fCurCloseAngle, oTmt_paraState.m_oCloseAngle.m_nCloseChannel);
		}

		BOOL bPlusDC = FALSE;
		float fTao = 0;

		switch(pTmt->m_nPlusDC)
		{
		case 0:
			//无叠加
			break;
		case 1:
		{
			//有叠加
			bPlusDC = TRUE;
			fTao = pTmt->m_fTao;
		}
			break;
		case 2:
		{
			//按状态叠加
			if(oTmt_paraState.m_bPlusDC)
			{
				bPlusDC = TRUE;
				fTao = oTmt_paraState.m_fTao;
			}
		}
			break;
		}

		if(bPlusDC)
		{
			int nT = fTao * 1000; //只允许nT<=100

			if(g_theSystemConfig->m_nHasAnalog != 0)
			{
				Acyclic_Analog(m_pDrv_StateItem, oTmt_paraState, nT);
			}

			if(g_theSystemConfig->m_nHasDigital != 0)
			{
				Acyclic_Digital(m_pDrv_StateItem, oTmt_paraState, nT);
			}
		}

		memcpy(pBuf + nStateIndex * sizeof(Drv_StateItem), m_pDrv_StateItem, sizeof(Drv_StateItem));
		nStateIndex++;

		if(nStateIndex == pTmt->m_nStateNumbers)
		{
			break;
		}
	}

	if(g_theSystemConfig->m_nHasAnalog != 0 || bSetAux)
	{
		CSttDeviceBase::g_pSttDeviceBase->WriteDApara(&oDAPara);
	}

	if(m_bRampFreq)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x110, 0);//有一个状态包含频率递变，就关闭秒同步
		g_oDrvMutex.unlock();
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x301, 1);
	write(m_nfd, pBuf, pTmt->m_nStateNumbers * sizeof(Drv_StateItem));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::setTriger(tmt_StatePara  oTmt_paraState, Drv_StateItem *oDrv_StateItem, int nIndex)
{
	switch(oTmt_paraState.m_nTriggerCondition)
	{
		case TMT_MDSTATE_MEARSURETRIGGER://手动触发
		{
			oDrv_StateItem->nTirpType = State_Trig_Manual;
		}
		break;

		case TMT_MDSTATE_TIMETRIGGER://时间触发
		{
			oDrv_StateItem->nTirpType = State_Trig_TimeDelay;
			float fTm = oTmt_paraState.m_fTimeState * 1000;
			oDrv_StateItem->oTm.oTime.nMsec = fTm;
			oDrv_StateItem->oTm.oTime.nUsec = (fTm - (int)fTm) * 1000;
		}
		break;

		case TMT_MDSTATE_BINTRIGGER:
		{
			oDrv_StateItem->nTirpType = State_Trig_Bin;
			oDrv_StateItem->obiTrip.nBiLogic = 0;

			if(oTmt_paraState.m_nBinLogic == TMT_BINLOGIC_AND)
			{
				oDrv_StateItem->obiTrip.nBiLogic = 1;
			}

			oDrv_StateItem->obiTrip.nBiRef  = oTmt_paraState.m_eBinReversal;
			oDrv_StateItem->oTm.oTime.nDelay = oTmt_paraState.m_fTimeAfterTrigger * 1000;
			SetTestCommBi(oDrv_StateItem->obiTrip, oDrv_StateItem->obiTrip.nBiLogic,
						  oTmt_paraState.m_binIn, oTmt_paraState.m_binInEx, nIndex);
		}
		break;

		case TMT_MDSTATE_GPSBTRIGGER://GPS触发,注意传参的时区+8/-8问题
		{
			oDrv_StateItem->oTm.oGps.nNsec = oTmt_paraState.m_tGps.nMilliSeconds * 1000000; //纳秒值转换
			oDrv_StateItem->nTirpType = State_Trig_GPS;
//            QDateTime datetime = QDateTime::fromTime_t(g_theSttDeviceStatus->m_nUser_s);
//            QTime time;
//            time.setHMS(oTmt_paraState.m_tGps.nHour, oTmt_paraState.m_tGps.nMinutes, oTmt_paraState.m_tGps.nSeconds);
//            datetime.setTime(time);
//            QDateTime oNewDate = datetime.addSecs(-g_theSttDeviceStatus->m_nTimeZone * 3600);
//            oDrv_StateItem->oTm.oGps.nSec = oNewDate.toTime_t();
			short nYear, nMon, nDay, nHour, nMin, nSec;
			TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
			nHour = oTmt_paraState.m_tGps.nHour;
			nMin = oTmt_paraState.m_tGps.nMinutes;
			nSec = oTmt_paraState.m_tGps.nSeconds;
			unsigned int ntime_t;
			TransTimer_To_t(ntime_t, nYear, nMon, nDay, nHour, nMin, nSec);
			ntime_t -= g_theSttDeviceStatus->m_nTimeZone * 3600;
			oDrv_StateItem->oTm.oGps.nSec = ntime_t;
		}
		break;

		case TMT_MDSTATE_TIMEBINTRIGGER:
		{
			oDrv_StateItem->nTirpType = State_Trig_Bin_TimeDelay;
			oDrv_StateItem->obiTrip.nBiLogic = 0;

			if(oTmt_paraState.m_nBinLogic == TMT_BINLOGIC_AND)
			{
				oDrv_StateItem->obiTrip.nBiLogic = 1;
			}

			oDrv_StateItem->obiTrip.nBiRef  = oTmt_paraState.m_eBinReversal;
			float fTm = oTmt_paraState.m_fTimeState * 1000;
			oDrv_StateItem->oTm.oTime.nMsec = fTm;
			oDrv_StateItem->oTm.oTime.nUsec = (fTm - (int)fTm) * 1000;
			oDrv_StateItem->oTm.oTime.nDelay = oTmt_paraState.m_fTimeAfterTrigger * 1000;
			SetTestCommBi(oDrv_StateItem->obiTrip, oDrv_StateItem->obiTrip.nBiLogic,
						  oTmt_paraState.m_binIn, oTmt_paraState.m_binInEx, nIndex);
		}
		break;

		default:
			break;
	}
}

void CSttDeviceComm::State_volt(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
								int nModuleUIndex)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Voltanal;
	memset(&Voltanal, 0, sizeof(structACParamItem));
	Voltanal.DWCount = 42;
	BOOL bHarm = FALSE;
	int nChPos;
	float fAmp;
	long *dat = &Voltanal.nVal[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_ChannelHarm *oTmtHarm;
	float fFreq = 0;
	float fAngle = 0;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[1].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCVolToDrv(fAmp, k, nModuleUIndex, dat + nChPos);

			if(m_nTmtPos < 0)
			{
				continue;
			}

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;
					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogVolToDrv(fAmp, fAngle,
										fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3);
					break;
				}
			}
		}
	}
	else
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[0].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCVolToDrv(fAmp, k, nModuleUIndex, dat + nChPos);

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(oTmt_paraState.m_uiVOL[m_nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogVolToDrv(fAmp, fAngle,
								fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3);

			if(m_nTmtPos < 0)
			{
				continue;
			}

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;
					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogVolToDrv(fAmp, fAngle,
										fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + CHANNEL_MAX * 3 + nChPos * 3);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleUIndex], &Voltanal, sizeof(structACParamItem));
}

void CSttDeviceComm::State_volt_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
		int nModuleUIndex)
{
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_StateDeg oDrvStateDeg;
	memset(&oDrvStateDeg, 0, sizeof(Drv_StateDeg));
	float fStart;
	float fEnd;
	float fStep;
	long nStepCount;
	long nSign;
	int nChPos;
	float fFreCoef;
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

	for(int i = 0; i < oDrv_StateItem->oAcParam.item[nModuleUIndex].DWCount; i++)
	{
		oDrvStateDeg.lastVal[i] = oDrv_StateItem->oAcParam.item[nModuleUIndex].nVal[i];
	}

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		nChPos = pModule->m_nChDrvPos[k];
		m_nTmtPos = pModule->m_nChTmtPos[k];

		if(m_nTmtPos >= 0)
		{
			tmt_channel &uiVOL = oTmt_paraState.m_uiVOL[m_nTmtPos];

			if(uiVOL.Ramp[0].nIndex > 0)
			{
				fStart = fabs(uiVOL.Harm[1].fAmp);
				fEnd = fabs(uiVOL.Ramp[0].fEnd);
				fStep = fabs(uiVOL.Ramp[0].fStep);
				//幅值递变
				BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
													 pModule, k, 1);

				if(bRet && fStep > StateDegressMinStep)
				{
					float fChMax = pModule->m_oModuleAttr.m_fChMax;
					oDrvStateDeg.nCount[CHANNEL_MAX + nChPos * 3 + 2] = nStepCount;
					long nH = fStep * 65536 / fChMax;
					double fH = fStep * 65536 / fChMax;
					long nL = (fH - nH) * 65536;
					oDrvStateDeg.changeVal[CHANNEL_MAX + nChPos * 3 + 2] = nSign * (((nH << 16) & 0xFFFF0000) + nL);
					long nHarm;
					//按照始值计算方式计算终值
					float fFreq = uiVOL.Harm[1].fFreq;

					if(fFreq <= m_nEDFre)
					{
						nHarm = 0;
					}
					else
					{
						nHarm  = (fFreq + 25) / m_nEDFre - 1;
					}

					oDrvStateDeg.lastVal[CHANNEL_MAX + nChPos * 3 + 2] =
						TranslateACVoltAmp(fEnd, k, nModuleUIndex, nHarm + 1);
					oDrvStateDeg.nIsChange++;
				}
			}

			if(uiVOL.Ramp[1].nIndex > 0)
			{
				//相位递变
				fStart = uiVOL.Harm[1].fAngle;
				fEnd = uiVOL.Ramp[1].fEnd;
				fStep = fabs(uiVOL.Ramp[1].fStep);

				if(fStep > StateDegressMinStep)
				{
					AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
											 pModule, k, 1);
					oDrvStateDeg.nCount[CHANNEL_MAX + nChPos * 3] = nStepCount;
					long  nPh;
					nPh = fStep * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.changeVal[CHANNEL_MAX + nChPos * 3] = nSign * nPh;
					nPh = fEnd * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.lastVal[CHANNEL_MAX + nChPos * 3] = nPh;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(uiVOL.Ramp[2].nIndex == 1)
			{
				m_bRampFreq = TRUE;
				//单波形输出频率递变
				fStart = fabs(uiVOL.Harm[1].fFreq);
				fEnd = fabs(uiVOL.Ramp[2].fEnd);
				fStep = fabs(uiVOL.Ramp[2].fStep);

				if(fStep > StateDegressMinStep)
				{
					AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
											 pModule, k, 1);
					oDrvStateDeg.nCount[CHANNEL_MAX + nChPos * 3 + 1] = nStepCount;
					fFreCoef = 1;

					if(pModule != NULL)
					{
						fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
					}

					oDrvStateDeg.changeVal[CHANNEL_MAX + nChPos * 3 + 1] = nSign * TranslateACFre(fStep * fFreCoef);
					oDrvStateDeg.lastVal[CHANNEL_MAX + nChPos * 3 + 1] = TranslateACFre(fEnd * fFreCoef);
					oDrvStateDeg.nIsChange++;
				}
			}
		}
	}

	if(oDrvStateDeg.nIsChange > 0)
	{
		oDrvStateDeg.nIsChange = 1;
	}

	memcpy(&oDrv_StateItem->oStChange[nModuleUIndex], &oDrvStateDeg, sizeof(Drv_StateDeg));
}

void CSttDeviceComm::State_current(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
								   int nModuleIIndex)
{
	int nModuleOffset = nModuleIIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Curanal;
	memset(&Curanal, 0, sizeof(structACParamItem));
	Curanal.DWCount = 42;
	BOOL bHarm = FALSE;
	int nChPos;
	float fAmp;
	long *dat = &Curanal.nVal[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_ChannelHarm *oTmtHarm;
	float fFreq = 0;
	float fAngle = 0;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[1].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCCurToDrv(fAmp, k, nModuleIIndex, dat + nChPos);

			if(m_nTmtPos < 0)
			{
				continue;
			}

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;
					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogCurToDrv(fAmp, fAngle,
										fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3);
					break;
				}
			}
		}
	}
	else
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[0].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCCurToDrv(fAmp, k, nModuleIIndex, dat + nChPos);

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(oTmt_paraState.m_uiCUR[m_nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			TransAnalogCurToDrv(fAmp, fAngle,
								fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3);

			if(m_nTmtPos < 0)
			{
				continue;
			}

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;
					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;
					TransAnalogCurToDrv(fAmp, fAngle,
										fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + CHANNEL_MAX * 3 + nChPos * 3);
					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Curanal, sizeof(structACParamItem));
}

void CSttDeviceComm::State_current_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
		int nModuleIIndex)
{
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	int nModuleOffset = nModuleIIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_StateDeg oDrvStateDeg;
	memset(&oDrvStateDeg, 0, sizeof(Drv_StateDeg));
	float fStart;
	float fEnd;
	float fStep;
	long nStepCount;
	long nSign;
	int nChPos;
	float fFreCoef;
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

	for(int i = 0; i < oDrv_StateItem->oAcParam.item[nModuleOffset].DWCount; i++)
	{
		oDrvStateDeg.lastVal[i] = oDrv_StateItem->oAcParam.item[nModuleOffset].nVal[i];
	}

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		nChPos = pModule->m_nChDrvPos[k];
		m_nTmtPos = pModule->m_nChTmtPos[k];

		if(m_nTmtPos >= 0)
		{
			tmt_channel &uiCUR = oTmt_paraState.m_uiCUR[m_nTmtPos];

			if(uiCUR.Ramp[0].nIndex > 0)
			{
				fStart = fabs(uiCUR.Harm[1].fAmp);
				fEnd = fabs(uiCUR.Ramp[0].fEnd);
				fStep = fabs(uiCUR.Ramp[0].fStep);
				//幅值递变
				BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
													 pModule, k, 1);

				if(bRet && fStep > StateDegressMinStep)
				{
					float fChMax = pModule->m_oModuleAttr.m_fChMax;
					oDrvStateDeg.nCount[CHANNEL_MAX + nChPos * 3 + 2] = nStepCount;
					long nH = fStep * 65536 / fChMax;
					double fH = fStep * 65536 / fChMax;
					long nL = (fH - nH) * 65536;
					oDrvStateDeg.changeVal[CHANNEL_MAX + nChPos * 3 + 2] = nSign * (((nH << 16) & 0xFFFF0000) + nL);
					long nHarm;
					//按照始值计算方式计算终值
					float fFreq = uiCUR.Harm[1].fFreq;

					if(fFreq <= m_nEDFre)
					{
						nHarm = 0;
					}
					else
					{
						nHarm  = (fFreq + 25) / m_nEDFre - 1;
					}

					oDrvStateDeg.lastVal[CHANNEL_MAX + nChPos * 3 + 2] =
						TranslateACCurrentAmp(fEnd, k, nModuleIIndex, nHarm + 1);
					oDrvStateDeg.nIsChange++;
				}
			}

			if(uiCUR.Ramp[1].nIndex > 0)
			{
				//相位递变
				fStart = uiCUR.Harm[1].fAngle;
				fEnd = uiCUR.Ramp[1].fEnd;
				fStep = fabs(uiCUR.Ramp[1].fStep);

				if(fStep > StateDegressMinStep)
				{
					AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
											 pModule, k, 1);
					oDrvStateDeg.nCount[CHANNEL_MAX + nChPos * 3] = nStepCount;
					long  nPh;
					nPh = fStep * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.changeVal[CHANNEL_MAX + nChPos * 3] = nSign * nPh;
					nPh = fEnd * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.lastVal[CHANNEL_MAX + nChPos * 3] = nPh;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(uiCUR.Ramp[2].nIndex == 1)
			{
				m_bRampFreq = TRUE;
				//单波形输出频率递变
				fStart = fabs(uiCUR.Harm[1].fFreq);
				fEnd = fabs(uiCUR.Ramp[2].fEnd);
				fStep = fabs(uiCUR.Ramp[2].fStep);

				if(fStep > StateDegressMinStep)
				{
					AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
											 pModule, k, 1);
					oDrvStateDeg.nCount[CHANNEL_MAX + nChPos * 3 + 1] = nStepCount;
					fFreCoef = 1;

					if(pModule != NULL)
					{
						fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
					}

					oDrvStateDeg.changeVal[CHANNEL_MAX + nChPos * 3 + 1] = nSign * TranslateACFre(fStep * fFreCoef);
					oDrvStateDeg.lastVal[CHANNEL_MAX + nChPos * 3 + 1] = TranslateACFre(fEnd * fFreCoef);
					oDrvStateDeg.nIsChange++;
				}
			}
		}
	}

	if(oDrvStateDeg.nIsChange > 0)
	{
		oDrvStateDeg.nIsChange = 1;
	}

	memcpy(&oDrv_StateItem->oStChange[nModuleOffset], &oDrvStateDeg, sizeof(Drv_StateDeg));
}

void CSttDeviceComm::State_UI(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
							  int nModuleIndex)
{
	int nModuleOffset = nModuleIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	structACParamItem Curanal;
	memset(&Curanal, 0, sizeof(structACParamItem));
	BOOL bHarm = FALSE;
	BOOL bChanIsVolt;
	int nChPos;
	float fAmp;
	long *dat = &Curanal.nVal[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_channel *pTmt_channel;
	int nChanSize = CHANNEL_MAX;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		nChanSize = 12;
	}
	else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
	{
		nChanSize = 8;
	}

	Curanal.DWCount = nChanSize + nChanSize * 3 * 2;

	if(oTmt_paraState.m_bDC)
	{
		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
				bChanIsVolt = TRUE;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
				bChanIsVolt = FALSE;
			}

			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[m_nTmtPos].Harm[1].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];

			if(bChanIsVolt)
			{
				TransAnalogDCUIToDrv_Volt(fAmp, k, nModuleIndex, dat + nChPos);
			}
			else
			{
				TransAnalogDCUIToDrv_Current(fAmp, k, nModuleIndex, dat + nChPos);
			}
		}
	}
	else
	{
		tmt_ChannelHarm *oTmtHarm;
		float fFreq = 0;
		float fAngle = 0;

		for(int k = 0; k < m_nTmtChanNum; k++)
		{
			if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
			{
				pTmt_channel = oTmt_paraState.m_uiVOL;
				bChanIsVolt = TRUE;
			}
			else
			{
				pTmt_channel = oTmt_paraState.m_uiCUR;
				bChanIsVolt = FALSE;
			}

			m_nTmtPos = pModule->m_nChTmtPos[k];

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
			}
			else
			{
				fAmp = pTmt_channel[m_nTmtPos].Harm[0].fAmp;
			}

			nChPos = pModule->m_nChDrvPos[k];

			if(bChanIsVolt)
			{
				TransAnalogDCUIToDrv_Volt(fAmp, k, nModuleIndex, dat + nChPos);
			}
			else
			{
				TransAnalogDCUIToDrv_Current(fAmp, k, nModuleIndex, dat + nChPos);
			}

			if(m_nTmtPos < 0)
			{
				fAmp = 0;
				fFreq = 50;
			}
			else
			{
				oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
				fAmp = oTmtHarm->fAmp;
				fAngle = oTmtHarm->fAngle;
				fFreq = oTmtHarm->fFreq;

				if(pTmt_channel[m_nTmtPos].Ramp[2].nIndex == 1)
				{
					if(fFreq < EPSINON)
					{
						fFreq = 0.001;
					}
				}
			}

			if(bChanIsVolt)
			{
				TransAnalogUIToDrv_Volt(fAmp, fAngle,
										fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3);
			}
			else
			{
				TransAnalogUIToDrv_Current(fAmp, fAngle,
										   fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3);
			}

			if(m_nTmtPos < 0)
			{
				continue;
			}

			for(int nHarmIndex = 2; nHarmIndex <= pModule->m_oModuleAttr.m_nHarmCount; nHarmIndex++)
			{
				bHarm = pTmt_channel[m_nTmtPos].Harm[nHarmIndex].m_bSelect;

				if(bHarm)
				{
					oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[nHarmIndex];
					fAmp = oTmtHarm->fAmp;
					fAngle = oTmtHarm->fAngle;
					fFreq = oTmtHarm->fFreq;

					if(bChanIsVolt)
					{
						TransAnalogUIToDrv_Volt(fAmp, fAngle,
												fFreq, k, nModuleIndex, dat + nChanSize + nChanSize * 3 + nChPos * 3);
					}
					else
					{
						TransAnalogUIToDrv_Current(fAmp, fAngle,
												   fFreq, k, nModuleIndex, dat + nChanSize + nChanSize * 3 + nChPos * 3);
					}

					break;
				}
			}
		}
	}

	memcpy(&oDrv_StateItem->oAcParam.item[nModuleOffset], &Curanal, sizeof(structACParamItem));
}

void CSttDeviceComm::State_UI_Gradient(Drv_StateItem *oDrv_StateItem, tmt_StatePara  oTmt_paraState,
									   int nModuleIndex)
{
	int m_nEDFre = g_theDeviceSystemParameter->m_oDeviceAttrs.m_fBaseFre;
	int nModuleOffset = nModuleIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	Drv_StateDeg oDrvStateDeg;
	memset(&oDrvStateDeg, 0, sizeof(Drv_StateDeg));
	float fStart;
	float fEnd;
	float fStep;
	long nStepCount;
	long nSign;
	int nChPos;
	float fFreCoef;
	BOOL bChanIsVolt;
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_channel *pTmt_channel;
	int nChanSize = CHANNEL_MAX;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		nChanSize = 12;
	}
	else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
	{
		nChanSize = 8;
	}

	for(int i = 0; i < oDrv_StateItem->oAcParam.item[nModuleOffset].DWCount; i++)
	{
		oDrvStateDeg.lastVal[i] = oDrv_StateItem->oAcParam.item[nModuleOffset].nVal[i];
	}

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE) //'U'
		{
			pTmt_channel = oTmt_paraState.m_uiVOL;
			bChanIsVolt = TRUE;
		}
		else
		{
			pTmt_channel = oTmt_paraState.m_uiCUR;
			bChanIsVolt = FALSE;
		}

		nChPos = pModule->m_nChDrvPos[k];
		m_nTmtPos = pModule->m_nChTmtPos[k];

		if(m_nTmtPos >= 0)
		{
			tmt_channel &Tmtui = pTmt_channel[m_nTmtPos];

			if(Tmtui.Ramp[0].nIndex > 0)
			{
				fStart = fabs(Tmtui.Harm[1].fAmp);
				fEnd = fabs(Tmtui.Ramp[0].fEnd);
				fStep = fabs(Tmtui.Ramp[0].fStep);
				//幅值递变
				BOOL bRet = AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_AMP,
													 pModule, k, 1);

				if(bRet && fStep > StateDegressMinStep)
				{
					float fChMax = pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_fChACMaxValue;
					oDrvStateDeg.nCount[nChanSize + nChPos * 3 + 2] = nStepCount;
					long nH = fStep * 65536 / fChMax;
					double fH = fStep * 65536 / fChMax;
					long nL = (fH - nH) * 65536;
					oDrvStateDeg.changeVal[nChanSize + nChPos * 3 + 2] = nSign * (((nH << 16) & 0xFFFF0000) + nL);
					long nHarm, nlastVal;
					//按照始值计算方式计算终值
					float fFreq = Tmtui.Harm[1].fFreq;

					if(fFreq <= m_nEDFre)
					{
						nHarm = 0;
					}
					else
					{
						nHarm  = (fFreq + 25) / m_nEDFre - 1;
					}

					if(bChanIsVolt)
					{
						nlastVal = TranslateACUIAmp_Volt(fEnd, k, nModuleIndex, nHarm + 1);
					}
					else
					{
						nlastVal = TranslateACUIAmp_Current(fEnd, k, nModuleIndex, nHarm + 1);
					}

					oDrvStateDeg.lastVal[nChanSize + nChPos * 3 + 2] = nlastVal;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[1].nIndex > 0)
			{
				//相位递变
				fStart = Tmtui.Harm[1].fAngle;
				fEnd = Tmtui.Ramp[1].fEnd;
				fStep = fabs(Tmtui.Ramp[1].fStep);

				if(fStep > StateDegressMinStep)
				{
					AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_ANG,
											 pModule, k, 1);
					oDrvStateDeg.nCount[nChanSize + nChPos * 3] = nStepCount;
					long  nPh;
					nPh = fStep * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.changeVal[nChanSize + nChPos * 3] = nSign * nPh;
					nPh = fEnd * 65536 / 360;
					nPh = nPh << 16;
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3] = nPh;
					oDrvStateDeg.nIsChange++;
				}
			}

			if(Tmtui.Ramp[2].nIndex == 1)
			{
				m_bRampFreq = TRUE;
				//单波形输出频率递变
				fStart = fabs(Tmtui.Harm[1].fFreq);
				fEnd = fabs(Tmtui.Ramp[2].fEnd);
				fStep = fabs(Tmtui.Ramp[2].fStep);

				if(fStep > StateDegressMinStep)
				{
					AnalogGradientPreProcess(fStart, fEnd, fStep, nStepCount, nSign, GRADIENT_FRE,
											 pModule, k, 1);
					oDrvStateDeg.nCount[nChanSize + nChPos * 3 + 1] = nStepCount;
					fFreCoef = 1;

					if(pModule != NULL)
					{
						fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;

						if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
								|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
								|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
								|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
						{
							fFreCoef = fFreCoef * 8;    //50K
						}
					}

					oDrvStateDeg.changeVal[nChanSize + nChPos * 3 + 1] = nSign * TranslateACFre(fStep * fFreCoef);
					oDrvStateDeg.lastVal[nChanSize + nChPos * 3 + 1] = TranslateACFre(fEnd * fFreCoef);
					oDrvStateDeg.nIsChange++;
				}
			}
		}
	}

	if(oDrvStateDeg.nIsChange > 0)
	{
		oDrvStateDeg.nIsChange = 1;
	}

	memcpy(&oDrv_StateItem->oStChange[nModuleOffset], &oDrvStateDeg, sizeof(Drv_StateDeg));
}

double dBinActTime;
void CSttDeviceComm::ProStateDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
{
	State_EventRsts &oStateEvents = CSttDeviceBase::g_pSttDeviceBase->m_oStateEvents;
	STT_TEST_EVENT obufEvent;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults = stt_test_get_drvresult_buff();
	g_oDrvMutex.lock();
	int nret = read(m_nfd, pDrvResults, 0x203);
	g_oDrvMutex.unlock();

	if(nret <= 0)
	{
		return;
	}

	long nRealTimeEventCount = 0;

	for(int i = 0; i < nret / m_nDrvResItemLen; i++)
	{
		memcpy(&m_oDrvResItem, pDrvResults + i * m_nDrvResItemLen, m_nDrvResItemLen);
		double dTime = m_oDrvResItem.nSec + m_oDrvResItem.nNanoSec * 0.000000001;

		switch(m_oDrvResItem.nType)
		{
			case DrvResult_TestStart:
			{
				m_bRdDegRtData = TRUE;
				long nCurStateIndex = 0;

				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_dTestStartTime = dTime;
					nCurStateIndex = pSttTestBase->m_nCurStateIndex;
				}

				m_oStepInfo.dTime = dTime;
				ProStartBinEvent(m_oDrvResItem.nBi, nRealTimeEventCount, nCurStateIndex, -1, dTime);
				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, nCurStateIndex, -1, dTime, 0);
				m_nCurStateRealTime = dTime;
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));

				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_nCurStepIndex = -1;
					pSttTestBase->ReturnTestStateEvent_TestStart(dTime, 0, TRUE);
					pSttTestBase->ProRtDatasEvent(dTime, 0, -1, 0, 0);
				}

				for(int j = 0; j < oStateEvents.m_nRstCnt && j < 20; j++)
				{
					oStateEvents.m_oRst[j].m_dEventTime = 0;
					oStateEvents.m_oRst[j].m_bUsed = FALSE;
				}

				oStateEvents.m_nBinTripCnt = 0;

				if(pSttTestBase != NULL)
				{
					long nStateNum = pSttTestBase->GetStateNum(0);

					for(int j = 0; j < oStateEvents.m_nRstCnt && j < 20; j++)
					{
						if(oStateEvents.m_oRst[j].m_nEventType == 1
								&& oStateEvents.m_oRst[j].m_nStateIdx == nStateNum)
						{
							oStateEvents.m_oRst[j].m_dEventTime = dTime;
							oStateEvents.m_oRst[j].m_bUsed = TRUE;
							break;
						}
					}
				}

				GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
				oRampRestCom.init();
				oRampRestCom.m_frInTime = dTime;
				oRampRestCom.m_frTimeStateBegin = 0;
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CurStateIndex=0"));

				if(g_theSystemConfig->m_nHasDigital != 0)
				{
					int nGseOutCnt = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.count();

					for(int index = 0; index < nGseOutCnt; index++)
					{
						for(int j = 0; j < MAX_GOOSE_CHANNEL_COUNT; j++)
						{
							m_oPreGoosePub[index].m_strChannel[j] =
								m_pStateGoosePub[0].m_oGoosePub[index].m_strChannel[j];
						}
					}

					int nFt3OutCnt = m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044.count();

					for(int index = 0; index < nFt3OutCnt; index++)
					{
						for(int j = 0; j < MAX_FT3_CHANNEL_COUNT; j++)
						{
							m_oPreFt3Pub[index].m_strChannel[j] =
								m_pStateFt3Pub[0].m_oFt3Pub[index].m_strChannel[j];
						}
					}
				}

				PowerDAMngr *pPowerDAMngr = &CSttDeviceBase::g_pSttDeviceBase->m_oPowerDAMngr;
				pPowerDAMngr->nTickCnt = 0;
				pPowerDAMngr->nTickTotal = 2;
				pPowerDAMngr->nUse = 1;
			}
			break;

			case DrvResult_TestFinish:
			{
				GetRtData();
				m_bRdDegRtData = FALSE;

				if(pSttTestBase != NULL)
				{
					pSttTestBase->SetTestStarting(FALSE);
					pSttTestBase->SyncSingleStateTmtResult();
					bTestFinished = TRUE;
					oTestFinishedTime.dTime = dTime;
					oTestFinishedTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				}

				AfterTestFinishedPro();
				CLogPrint::LogString(XLOGLEVEL_INFOR, _T("CSttDeviceComm TestFinish"));
			}
			break;

			case DrvResult_BI:
			{
				if(pSttTestBase != NULL && pSttTestBase->m_nCurStepIndex > -1)
				{
					CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CurStateIndex=%d,DegressIndex=%d,BinAct"),
											   pSttTestBase->m_nCurStateIndex, pSttTestBase->m_nCurStepIndex);
				}

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("dBinActTime=%f"), dTime);
				dBinActTime = dTime;

				if(pSttTestBase != NULL && pSttTestBase->m_nCurStepIndex > -1)
				{
					CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient = TRUE;
				}
				else
				{
					CSttDeviceBase::g_pSttDeviceBase->m_bCurTestIsGradient = FALSE;
				}

				long nCurStateIndex = m_oDrvResItem.nStep;
				ProCommBinEvent(m_oDrvResItem, nRealTimeEventCount, nCurStateIndex,
								pSttTestBase->m_nCurStepIndex, dTime, dTime - m_nCurStateRealTime);
			}
			break;

			case DrvResult_State_BI_DI_REF:
			{
				//第一态结束同步参考值
				memcpy(&m_oStateFirstBi, &m_oDrvResItem.nBi, sizeof(Drv_BIStatus));
				memcpy(&m_oStateFirstDi, &m_oDrvResItem.nDi, sizeof(Drv_BIStatus));
			}
			break;

			case DrvResult_State_StateChg:
			{
				if(m_oDrvResItem.nStep == 1)
				{
					if(g_theSystemConfig->m_nHasAnalog != 0)
					{
						CSttDeviceBase *pSttDeviceBase = CSttDeviceBase::g_pSttDeviceBase;
						if(pSttDeviceBase->m_bUseDAParaForState2)
						{
							pSttDeviceBase->WriteDApara(&pSttDeviceBase->m_oDAParaForState2);//解决电流模块异响
						}
					}
				}

				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CurStateIndex=%d"), m_oDrvResItem.nStep);

				if(m_oDrvResItem.nSource == 3 || m_oDrvResItem.nSource == 4) //开入量触发
				{
					CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_fTripTime = dBinActTime - m_oStepInfo.dTime;
					CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nAct = 1;

					if(pSttTestBase != NULL && pSttTestBase->m_nCurStepIndex > -1)
					{
						CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.m_nTripStep = pSttTestBase->m_nCurStepIndex;
					}

					long nIdx = oStateEvents.m_nBinTripCnt;

					if(nIdx < 20 && pSttTestBase != NULL)
					{
						oStateEvents.m_oBinTripRst[nIdx].m_dEventTime = dTime;
						oStateEvents.m_oBinTripRst[nIdx].m_nStateIdx =
							pSttTestBase->GetStateNum(m_oDrvResItem.nStep);//记录触发后的状态号，用于减触发后延时
						oStateEvents.m_nBinTripCnt++;
					}
				}

				if(pSttTestBase != NULL)
				{
					pSttTestBase->SyncSingleStateTmtResult();
				}

				if(m_oDrvResItem.nStep == 0)
				{
					if(pSttTestBase != NULL)
					{
						pSttTestBase->m_nCurStateIndex++;
						pSttTestBase->SyncSingleStateTmtResult();
					}

					//状态序列循环
					CSttTestServerBase *pSttTestServerBase = CSttTestServerBase::GetServerEngine();
					pSttTestServerBase->Process_Cmd_Test_GetReport(FALSE);

					if(pSttTestBase != NULL)
					{
						pSttTestBase->m_nCurStateLoopIndex++;
						pSttTestBase->InitStateLoopResults();
					}

					for(int j = 0; j < oStateEvents.m_nRstCnt && j < 20; j++)
					{
						oStateEvents.m_oRst[j].m_dEventTime = 0;
						oStateEvents.m_oRst[j].m_bUsed = FALSE;
					}

					oStateEvents.m_nBinTripCnt = 0;

					if(pSttTestBase != NULL)
					{
						long nStateNum = pSttTestBase->GetStateNum(0);

						for(int j = 0; j < oStateEvents.m_nRstCnt && j < 20; j++)
						{
							if(oStateEvents.m_oRst[j].m_nEventType == 1
									&& oStateEvents.m_oRst[j].m_nStateIdx == nStateNum)
							{
								oStateEvents.m_oRst[j].m_dEventTime = dTime;
								oStateEvents.m_oRst[j].m_bUsed = TRUE;
								break;
							}
						}
					}
				}

				if(m_oDrvResItem.nStep < CSttDeviceBase::g_pSttDeviceBase->m_nCurStateCount)
				{
					if(pSttTestBase != NULL)
					{
						long nStateNum = pSttTestBase->GetStateNum(m_oDrvResItem.nStep);

						for(int j = 0; j < oStateEvents.m_nRstCnt && j < 20; j++)
						{
							if(oStateEvents.m_oRst[j].m_nEventType == 1
									&& oStateEvents.m_oRst[j].m_nStateIdx == nStateNum
									&& m_oDrvResItem.nStep > 0)
							{
								oStateEvents.m_oRst[j].m_dEventTime = dTime;
								oStateEvents.m_oRst[j].m_bUsed = TRUE;
								break;
							}
						}
					}

					double dTestStartTime = dTime;

					if(pSttTestBase != NULL)
					{
						pSttTestBase->m_nCurStateIndex = m_oDrvResItem.nStep;
						pSttTestBase->m_nCurStepIndex = -1;
						dTestStartTime = pSttTestBase->m_dTestStartTime;
					}

					GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
					oRampRestCom.init();
					oRampRestCom.m_frInTime = dTime;
					oRampRestCom.m_frTimeStateBegin = dTime - dTestStartTime;
					m_nCurStateRealTime = dTime;
					m_oStepInfo.dTime = dTime;
					obufEvent.oTime.dTime = dTime;
					obufEvent.oTime.dRealTime = dTime - dTestStartTime;
					obufEvent.oTime.dBinActTime = -1;
					obufEvent.oEventInfo[0].nType = SttResult_Type_StateChange;
					obufEvent.oEventInfo[0].nStateIndex = m_oDrvResItem.nStep;
					long nStateNum = -1;

					if(pSttTestBase != NULL)
					{
						nStateNum = pSttTestBase->GetStateNum(m_oDrvResItem.nStep);
					}

					obufEvent.oEventInfo[0].nStateNum = nStateNum;
					obufEvent.oEventInfo[0].nStepIndex = -1;
					obufEvent.oEventInfo[0].nChannel = -1;
					obufEvent.oEventInfo[0].nValue = 0;
					obufEvent.nEventInfoCnt = 1;
					stt_add_test_event(obufEvent);
					nRealTimeEventCount++;
					ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, m_oDrvResItem.nStep,
									 -1, dTime, dTime - dTestStartTime, FALSE);					
					memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));					
					if(pSttTestBase != NULL)
					{
						pSttTestBase->ProRtDatasEvent(dTime, dTime - dTestStartTime, -1, m_oDrvResItem.nStep, 1);
					}

					if(g_theSystemConfig->m_nHasDigital != 0)
					{
						int nGseOutCnt = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.count();

						for(int index = 0; index < nGseOutCnt && index < MAX_MODULES_GOOSEPUB_COUNT; index++)
						{
							for(int j = 0; j < MAX_GOOSE_CHANNEL_COUNT; j++)
							{
								if(m_oDrvResItem.nStep < g_nStateCount)
								{
									m_oPreGoosePub[index].m_strChannel[j] =
										m_pStateGoosePub[m_oDrvResItem.nStep].m_oGoosePub[index].m_strChannel[j];
								}
							}
						}

						int nFt3OutCnt = m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044.count();

						for(int index = 0; index < nFt3OutCnt && index < MAX_MODULES_FT3PUB_COUNT; index++)
						{
							for(int j = 0; j < MAX_FT3_CHANNEL_COUNT; j++)
							{
								if(m_oDrvResItem.nStep < g_nStateCount)
								{
									m_oPreFt3Pub[index].m_strChannel[j] =
										m_pStateFt3Pub[m_oDrvResItem.nStep].m_oFt3Pub[index].m_strChannel[j];
								}
							}
						}
					}
				}
				else
				{
					if(pSttTestBase != NULL)
					{
						pSttTestBase->m_nCurStateIndex = m_oDrvResItem.nStep;
						pSttTestBase->SyncSingleStateTmtResult();
					}
				}
			}
			break;

			case DrvResult_State_BO:
			{
				long nCurStateIndex = 0;
				long nCurStepIndex = 0;
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					nCurStateIndex = pSttTestBase->m_nCurStateIndex;
					nCurStepIndex = pSttTestBase->m_nCurStepIndex;
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, nCurStateIndex,
								 nCurStepIndex, dTime, dTime - dTestStartTime, FALSE);
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
			}
			break;

			case DrvResult_State_Degress:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_nCurStepIndex = m_oDrvResItem.nDegressStep;
				}

				//			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("CurStepIndex=%d,Degress"),pSttTestBase->m_nCurStepIndex);
				m_oStepInfo.dTime = dTime;
				//			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("m_oStepInfo.dTime=%f"),dTime);
			}
			break;

			case DrvResult_State_DegressStop:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_nCurStepIndex = m_oDrvResItem.nDegressStep;
				}

				//			CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("CurStepIndex=%d,DegressStop"),pSttTestBase->m_nCurStepIndex);
				m_oStepInfo.dTime = dTime;
			}
			break;

			case DrvResult_GOOSE_Link:
			{
				CString strAppid = CString("0x%1").arg(CString::number(m_oDrvResItem.nGooseFlag, 16));
//                QDateTime oDate = QDateTime::fromTime_t(m_oDrvResItem.nSec + g_theSttDeviceStatus->m_nTimeZone * 3600);
//                CString strTime = oDate.toString("yyyy-MM-dd HH:mm:ss");
				short nYear, nMon, nDay, nHour, nMin, nSec;
				CString strTime;
				TransTimer_t(m_oDrvResItem.nSec + g_theSttDeviceStatus->m_nTimeZone * 3600
							 , nYear, nMon, nDay, nHour, nMin, nSec);
				strTime.Format("%04d-%02d-%02d %02d:%02d:%02d", nYear, nMon, nDay, nHour, nMin, nSec);
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[warning] Goose[%s] 链路通,%s"),
										   strAppid.GetString(), strTime.GetString());
			}
			break;
		}
	}
}
/************状态序列部分*************/

/************开关量序列部分*************/
void CSttDeviceComm::tmt_to_drv_BinaryManu(tmt_ManualTest *pTmt, BOOL bIsStartTest)
{
	char *pszDrv = stt_test_get_drvparas_buff();
	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	memset(pDrv, 0, sizeof(Drv_ManuData));

	Drv_ManuBin oBiSetting;
	memset(&oBiSetting, 0, sizeof(Drv_ManuBin));
	oBiSetting.nBinIsStop = false;

	if(pTmt->m_oManuParas.m_bBinStop)
	{
		oBiSetting.nBinIsStop = true;//开入停止
	}

	SetTestCommBi(oBiSetting.oTrip, pTmt->m_oManuParas.m_nBinLogic,
				  pTmt->m_oManuParas.m_binIn, pTmt->m_oManuParas.m_binInEx);
	SetManualBI((char *)&oBiSetting, sizeof(Drv_ManuBin));
	if(!bIsStartTest)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x147, 0);//通知驱动记录时间
		g_oDrvMutex.unlock();
	}
	if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
	{
		SetGooseValue_ManuTest(&pTmt->m_oManuParas.m_oGoosePub[0], bIsStartTest);
	}

	SetTestCommBo(pDrv->oDrvComBoSta, pTmt->m_oManuParas.m_binOut, pTmt->m_oManuParas.m_binOutEx);

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x303, 0);
	write(m_nfd, pszDrv, sizeof(Drv_ManuData));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::tmt_to_drv_BinaryStateItem(tmt_StateParas *pTmt)
{
	if(pTmt->m_nStateNumbers == 0)
	{
		return;
	}

	CSttDeviceBase::g_pSttDeviceBase->m_nCurStateCount = pTmt->m_nStateNumbers;
	char *pBuf = stt_test_get_drvparas_buff();
	tmt_StatePara  oTmt_paraState;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	for(int nStateIndex = 0; nStateIndex < pTmt->m_nStateNumbers; nStateIndex++)
	{
		oTmt_paraState = pTmt->m_paraState[nStateIndex];
		pSttTestBase->m_nStateNum[nStateIndex] = nStateIndex;
		memset(m_pDrv_StateItem, 0, sizeof(Drv_StateItem));
		m_pDrv_StateItem->nBoType = oTmt_paraState.m_nBinaryOutType;
		m_pDrv_StateItem->oStBo.nTripMode = oTmt_paraState.m_binOut[0].nMode;
		m_pDrv_StateItem->oStBo.nPreTripTime = oTmt_paraState.m_binOut[0].fTimeTrig * 1000;
		m_pDrv_StateItem->oStBo.nOutPutTime = oTmt_paraState.m_binOut[0].fHoldTime * 1000;
		SetTestCommBo(m_pDrv_StateItem->oStBo.boValue, oTmt_paraState.m_binOut, oTmt_paraState.m_binOutEx);

		if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
		{
			memcpy(&m_pDrv_StateItem->oGseChgParas, m_oCIEC61850CfgMngr.m_pGseChgParas, sizeof(DrvGseChgParas));
			BOOL bRet = FALSE;
			BOOL bSetGooseValue;
			BOOL bTestValid;
			BOOL bIsCompare = TRUE;
			int nPreTestMode;
			int nCurTestMode;
			int nGseOutCnt =  m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.count();

			for(int index = 0; index < nGseOutCnt; index++)
			{
				tmt_goose otmt_goose = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.at(index);

				if(!oTmt_paraState.m_oGoosePub[index].m_bUseFlag)
				{
					continue;    //无需变位
				}

				bTestValid = oTmt_paraState.m_oGoosePub[index].m_bHasTest;
				nCurTestMode = oTmt_paraState.m_oGoosePub[index].m_nTest;
				m_pDrv_StateItem->GooseTest.nCount = m_pDrv_StateItem->oGseChgParas.nModulesCnt;

				for(int i = 0; i < m_pDrv_StateItem->oGseChgParas.nModulesCnt; i++)
				{
					m_pDrv_StateItem->GooseTest.dat[i].module = m_pDrv_StateItem->oGseChgParas.oModule[i].nModuleIndex;
				}

				int nGSTestdataCnt;

				if(nStateIndex == 0)
				{
					for(int i = 0; i < m_pDrv_StateItem->GooseTest.nCount; i++)
					{
						nGSTestdataCnt = m_pDrv_StateItem->GooseTest.dat[i].nCount;

						if(m_pDrv_StateItem->GooseTest.dat[i].module == otmt_goose.m_nModuleIndex)
						{
							m_pDrv_StateItem->GooseTest.dat[i].gs[nGSTestdataCnt].group = otmt_goose.group;
							m_pDrv_StateItem->GooseTest.dat[i].gs[nGSTestdataCnt].value = nCurTestMode;
							m_pDrv_StateItem->GooseTest.dat[i].gs[nGSTestdataCnt].pos = otmt_goose.nTestModePos;
							m_pDrv_StateItem->GooseTest.dat[i].nCount++;
						}
					}
				}
				else
				{
					//有检修位改变需求
					if(bTestValid)
					{
						nPreTestMode = pTmt->m_paraState[nStateIndex - 1].m_oGoosePub[index].m_nTest;

						if(nPreTestMode != nCurTestMode)
						{
							for(int i = 0; i < m_pDrv_StateItem->GooseTest.nCount; i++)
							{
								nGSTestdataCnt = m_pDrv_StateItem->GooseTest.dat[i].nCount;

								if(m_pDrv_StateItem->GooseTest.dat[i].module == otmt_goose.m_nModuleIndex)
								{
									m_pDrv_StateItem->GooseTest.dat[i].gs[nGSTestdataCnt].group = otmt_goose.group;
									m_pDrv_StateItem->GooseTest.dat[i].gs[nGSTestdataCnt].value = nCurTestMode;
									m_pDrv_StateItem->GooseTest.dat[i].gs[nGSTestdataCnt].pos = otmt_goose.nTestModePos;
									m_pDrv_StateItem->GooseTest.dat[i].nCount++;
								}
							}
						}
					}
				}

				tmt_GoosePub *pPreGoosePub;

				if(nStateIndex == 0)
				{
					//实验开始也需要比较,防止开始实验虚变位
					//bIsCompare=FALSE;
					//pPreGoosePub=NULL;
					bIsCompare = TRUE;
					pPreGoosePub = &m_oPreGoosePub[index];
				}
				else
				{
					bIsCompare = TRUE;
					pPreGoosePub = &pTmt->m_paraState[nStateIndex - 1].m_oGoosePub[index];
				}

				bSetGooseValue = SetGooseValue_Com(&oTmt_paraState.m_oGoosePub[index],
													   &otmt_goose, &m_pDrv_StateItem->oGseChgParas, pPreGoosePub, bIsCompare);

				if(bSetGooseValue)
				{
					bRet = TRUE;
				}

				for(int j = 0; j < MAX_GOOSE_CHANNEL_COUNT; j++)
				{
					m_pStateGoosePub[nStateIndex].m_oGoosePub[index].m_strChannel[j] =
							oTmt_paraState.m_oGoosePub[index].m_strChannel[j];
				}
			}

			if(bRet)
			{
				m_pDrv_StateItem->nGseChgValid = 1;
			}
		}

		setTriger(oTmt_paraState, m_pDrv_StateItem, nStateIndex);
		memcpy(pBuf + nStateIndex * sizeof(Drv_StateItem), m_pDrv_StateItem, sizeof(Drv_StateItem));
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x301, 1);
	write(m_nfd, pBuf, pTmt->m_nStateNumbers * sizeof(Drv_StateItem));
	g_oDrvMutex.unlock();
}

/************开关量序列部分*************/

/************整组实验*************/
void CSttDeviceComm::tmt_to_drv_CboperPara(tmt_ImpBaseParas *pTmt)
{
	char *pszDrv = stt_test_get_drvparas_buff();
	Drv_CboperPara *pDrv = (Drv_CboperPara *)pszDrv;
	memset(pDrv, 0, sizeof(Drv_CboperPara));
	pDrv->nStateCount = pTmt->m_pStateParas->m_nStateNumbers;//*pTmt->m_oStateParas.m_nRepeatNumbers
	pDrv->nIsLoop = 0;
	pDrv->nbiRefFirst = pTmt->m_pStateParas->m_nBinTripRef;
	pDrv->nFaultTime = pTmt->m_fImpBaseFaultTime * 1000;
	pDrv->nTripTime = pTmt->m_fImpBaseTripTime * 1000;
	pDrv->nTransitionalTime = pTmt->m_fImpBaseTransTime * 1000;
	pDrv->bIsPermanent = pTmt->m_bImpBaseIsPermanent;
	pDrv->bIsTransitionalFault = pTmt->m_bImpBaseTransFault;
	pDrv->nReclosingTime = pTmt->m_fImpBaseReclosingTime * 1000;
	pDrv->nStopTime = pTmt->m_fImpBaseStopTime * 1000;
	Drv_BIStatus gooseInit;
	memset(&gooseInit, 0, sizeof(Drv_BIStatus));
	pDrv->oGooseInit = gooseInit;

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x314, 0); //整组实验参数
	write(m_nfd, pszDrv, sizeof(Drv_CboperPara));
	g_oDrvMutex.unlock();
}
/************整组实验*************/

/************振荡实验*************/
void CSttDeviceComm::tmt_to_drv_SwingTestPara(tmt_SwingParas *pTmt, int nStepCnt, char *pszDrv)
{
	memset(pszDrv, 0, sizeof(Drv_Swing));
	Drv_Swing *pSwing = (Drv_Swing *)pszDrv;
	pSwing->shakeCount = nStepCnt;
	SetTestCommBo(pSwing->oDrvComBoSta, pTmt->m_binOut, pTmt->m_binOutEx);
	pSwing->isRecip = pTmt->m_bReciprocating;
	pSwing->timeBfShake = pTmt->m_fPreFaultTime * 1000;
	pSwing->timeDiv = pTmt->m_fCycle * 1000 * 1000 / nStepCnt;

	if(pSwing->isRecip)
	{
		pSwing->timeDiv /= 2;
	}

	double fsumtime = pTmt->m_fCycle * 1000 * 1000 * pTmt->m_nSwingCount;

	if(pTmt->m_bTransFault)
	{
		pSwing->shakeMax = pTmt->m_fFaultTime * 1000 * 1000 / pSwing->timeDiv;
		pSwing->faultMax = (fsumtime - pTmt->m_fFaultTime * 1000 * 1000) / pSwing->timeDiv;
	}
	else
	{
		pSwing->shakeMax = fsumtime / pSwing->timeDiv;
		pSwing->faultMax = 0;
	}

	pSwing->stBITrip.oValid.nModuleCount = 1;
	pSwing->stBITrip.oValid.item[0].nModule = 0x8000;
	pSwing->stBITrip.oValid.item[0].nVal1 |= 1 << pTmt->m_nTripPoint; //跳闸接入点
	pSwing->stBITrip.oValid.item[0].nVal1 |= 1 << pTmt->m_nTripSpeedUp; //加速信号接点
	pSwing->stBITrip.oValid.item[0].nVal1 |= 1 << pTmt->m_nTripSpeedDown; //减速信号接点

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
		{
			SetGooseValue_ManuTest(&pTmt->m_oGoosePub[0], TRUE);
		}
	}
}

void CSttDeviceComm::Swing_volt(tmt_StepUI *pTmt, Drv_ShakePara *pszDrv, int nModuleUIndex)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nChPos;
	long *dat = &pszDrv->stData[nModuleUIndex].dat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	float fAmp = 0;
	float fFreq = 0;
	float fAngle = 0;

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		m_nTmtPos = pModule->m_nChTmtPos[k];
		nChPos = pModule->m_nChDrvPos[k];

		if(m_nTmtPos < 0)
		{
			continue;
		}
		else
		{
			fAmp = pTmt->fU[m_nTmtPos][0];
			fAngle = pTmt->fU[m_nTmtPos][1];
			fFreq = pTmt->fU[m_nTmtPos][2];
		}

		//		TransAnalogDCVolToDrv(fAmp,k,nModuleUIndex,dat+nChPos);
		TransAnalogVolToDrv(fAmp, fAngle,
							fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3);
	}

	pszDrv->stData[nModuleUIndex].nCnt = 24;
}

void CSttDeviceComm::Swing_current(tmt_StepUI *pTmt, Drv_ShakePara *pszDrv, int nModuleIIndex)
{
	int nModuleOffset = nModuleIIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nModuleIIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nChPos;
	long *dat = &pszDrv->stData[nModuleOffset].dat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	float fAmp = 0;
	float fFreq = 0;
	float fAngle = 0;

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		m_nTmtPos = pModule->m_nChTmtPos[k];
		nChPos = pModule->m_nChDrvPos[k];

		if(m_nTmtPos < 0)
		{
			continue;
		}
		else
		{
			fAmp = pTmt->fI[m_nTmtPos][0];
			fAngle = pTmt->fI[m_nTmtPos][1];
			fFreq = pTmt->fI[m_nTmtPos][2];
		}

		//		TransAnalogDCCurToDrv(fAmp,k,nModuleIIndex,dat+nChPos);
		TransAnalogCurToDrv(fAmp, fAngle,
							fFreq, k, nModuleIIndex, dat + CHANNEL_MAX + nChPos * 3);
	}

	pszDrv->stData[nModuleOffset].nCnt = 24;
}

void CSttDeviceComm::Swing_UI(tmt_StepUI *pTmt, Drv_ShakePara *pszDrv, int nModuleIndex)
{
	int nModuleOffset = nModuleIndex;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nChPos;
	BOOL bChanIsVolt;
	long *dat = &pszDrv->stData[nModuleOffset].dat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	float fAmp = 0;
	float fFreq = 0;
	float fAngle = 0;
	int nChanSize = CHANNEL_MAX;

	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		nChanSize = 12;
	}
	else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
	{
		nChanSize = 8;
	}

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		m_nTmtPos = pModule->m_nChTmtPos[k];
		nChPos = pModule->m_nChDrvPos[k];

		if(m_nTmtPos < 0)
		{
			continue;
		}

		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[k].m_nEeType == STT_CH_EETYPE_VOLTAGE)//'U'
		{
			fAmp = pTmt->fU[m_nTmtPos][0];
			fAngle = pTmt->fU[m_nTmtPos][1];
			fFreq = pTmt->fU[m_nTmtPos][2];
			bChanIsVolt = TRUE;
		}
		else
		{
			fAmp = pTmt->fI[m_nTmtPos][0];
			fAngle = pTmt->fI[m_nTmtPos][1];
			fFreq = pTmt->fI[m_nTmtPos][2];
			bChanIsVolt = FALSE;
		}

		if(bChanIsVolt)
		{
			TransAnalogUIToDrv_Volt(fAmp, fAngle,
									fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3);
		}
		else
		{
			TransAnalogUIToDrv_Current(fAmp, fAngle,
									   fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3);
		}
	}

	pszDrv->stData[nModuleOffset].nCnt = nChanSize + nChanSize * 3;
}

void CSttDeviceComm::TranslateDigitalVoltCurrentBuffer_Swing(tmt_StepUI *pTmt, long *pBuff, int ndigmoduleindex,
		int nType)
{
	int nChannelCnt = DIGITAL_CHANNEL_MAX / 2;
	long DrvData[nChannelCnt * 3];
	memset(DrvData, 0, nChannelCnt * 3 * sizeof(long));
	float fAmp, fFre, fPh;
	int nGroupIndex;
	int nTmtPos;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[ndigmoduleindex];

	if(pModule == NULL)
	{
		return;
	}

	for(int i = 0; i < 6; i++)
	{
		nTmtPos = pModule->m_nChTmtPos[i];

		if(nType == STT_MODULE_TYPE_CURRENT)
		{
			nTmtPos = pModule->m_nChTmtPos[i + nChannelCnt + 1];
		}

		if(nTmtPos < 0)
		{
			fAmp = 0;
			fPh = 0;
			fFre = 50;
		}
		else
		{
			if(nType == STT_MODULE_TYPE_VOLT)
			{
				fAmp = pTmt->fU[nTmtPos][0];
				fPh = pTmt->fU[nTmtPos][1];
				fFre = pTmt->fU[nTmtPos][2];
			}
			else
			{
				fAmp = pTmt->fI[nTmtPos][0];
				fPh = pTmt->fI[nTmtPos][1];
				fFre = pTmt->fI[nTmtPos][2];
			}
		}

		nGroupIndex = nTmtPos / 3;
		TransDigitalChannelToDrv(fAmp, fPh, fFre, nGroupIndex, DrvData + 3 * i, nType, pModule, FALSE, 0);
	}

	if(nType == STT_MODULE_TYPE_VOLT)
	{
		for(int j = 0; j < 12; j++)
		{
			if(j > 2)
			{
				pBuff[(j + 1) * 3] = DrvData[j * 3];
				pBuff[(j + 1) * 3 + 1] = DrvData[j * 3 + 1];
				pBuff[(j + 1) * 3 + 2] = DrvData[j * 3 + 2];
			}
			else
			{
				pBuff[j * 3] = DrvData[j * 3];
				pBuff[j * 3 + 1] = DrvData[j * 3 + 1];
				pBuff[j * 3 + 2] = DrvData[j * 3 + 2];
			}
		}

		for(int j = 0; j < 6; j++)
		{
			pBuff[(j + 25) * 3] = DrvData[(j + 12) * 3];
			pBuff[(j + 25) * 3 + 1] = DrvData[(j + 12) * 3 + 1];
			pBuff[(j + 25) * 3 + 2] = DrvData[(j + 12) * 3 + 2];
		}

		//Uz
		nTmtPos = pModule->m_nChTmtPos[nChannelCnt]; //U1~U18 Uz

		if(nTmtPos > -1)
		{
			fAmp = pTmt->fU[nTmtPos][0];
			fPh = pTmt->fU[nTmtPos][1];
			fFre = pTmt->fU[nTmtPos][2];
			nGroupIndex = 0;
			memset(DrvData, 0, 3 * sizeof(long));
			TransDigitalChannelToDrv(fAmp, fPh, fFre, nGroupIndex, DrvData, STT_MODULE_TYPE_VOLT, pModule, FALSE, 0);
			pBuff[9] = DrvData[0];
			pBuff[10] = DrvData[1];
			pBuff[11] = DrvData[2];
		}
	}
	else if(nType == STT_MODULE_TYPE_CURRENT)
	{
		for(int j = 0; j < 12; j++)
		{
			pBuff[(j + 13) * 3] = DrvData[j * 3];
			pBuff[(j + 13) * 3 + 1] = DrvData[j * 3 + 1];
			pBuff[(j + 13) * 3 + 2] = DrvData[j * 3 + 2];
		}

		for(int j = 0; j < 6; j++)
		{
			pBuff[(j + 25 + 6) * 3] = DrvData[(j + 12) * 3];
			pBuff[(j + 25 + 6) * 3 + 1] = DrvData[(j + 12) * 3 + 1];
			pBuff[(j + 25 + 6) * 3 + 2] = DrvData[(j + 12) * 3 + 2];
		}
	}
}

void CSttDeviceComm::tmt_to_drv_SwingAcPara(tmt_StepUI *pTmt, char *pszDrv, int nStep, int nType)
{
	Drv_Swing *pSwing = (Drv_Swing *)pszDrv;
	Drv_ShakePara *pShakePara;

	if(nType == 0)
	{
		//振荡前
		pShakePara = &pSwing->bfShake;
	}
	else if(nType == 1)
	{
		//振荡
		pShakePara = &pSwing->shake[nStep];
	}
	else if(nType == 2)
	{
		//故障
		pShakePara = &pSwing->fault[nStep];
	}

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			Swing_volt(pTmt, pShakePara, nIndex);
		}

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			Swing_current(pTmt, pShakePara, nIndex);
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			Swing_UI(pTmt, pShakePara, nIndex);
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
		{
			int nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_I;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_UI;

			for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
			{
				TranslateDigitalVoltCurrentBuffer_Swing(pTmt, pShakePara->stData[nAnalogModuleCnt + i].dat, i, STT_MODULE_TYPE_VOLT);
				TranslateDigitalVoltCurrentBuffer_Swing(pTmt, pShakePara->stData[nAnalogModuleCnt + i].dat, i, STT_MODULE_TYPE_CURRENT);
				pShakePara->stData[nAnalogModuleCnt + i].nCnt = DIGITAL_CHANNEL_MAX * 3;
			}
		}
	}
}

void CSttDeviceComm::SetSwingPara(char *pszDrv)
{
	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		CSttDeviceBase::g_pSttDeviceBase->DAPowerCtrl();
		int nModuleIndex;
		CSttDeviceBase::g_pSttDeviceBase->InitDAData();

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE oModule_U = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(oModule_U == NULL)
			{
				continue;
			}

			CSttDeviceBase::g_pSttDeviceBase->SetVoltDApara(oModule_U->m_oModuleAttr.m_fChMax,
					g_theSystemConfig->m_fAuxDC_Vol, nIndex, FALSE);
		}

		CSttPowerCtrlBase *pSttPowerCtrlBase = NULL;

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
				nModuleIndex = nIndex + g_theDeviceSystemParameter->m_nModuleCount_U;
				CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
			}
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetVoltDA_State();
				pSttPowerCtrlBase->SetCurrentDA_State(nIndex);
				nModuleIndex = nIndex + g_theDeviceSystemParameter->m_nModuleCount_U;
				nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
				CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
			}
		}

#ifdef _MainBoard_PN_

		if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
		{
			PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

			if(pModule_UI != NULL)
			{
				if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
				{
					long nCurModuleIndex = -1;

					if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
					{
						nCurModuleIndex += 1;
					}

					if(g_theDeviceSystemParameter->m_nModuleCount_I > 0)
					{
						nCurModuleIndex += 1;
					}

					if(nCurModuleIndex >= 0)
					{
						CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nCurModuleIndex + 1] =
							(CSttDeviceBase::g_pSttDeviceBase->m_oDAPara.nvolt[nCurModuleIndex] >> 8) & 0xFF;
					}
				}
			}
		}

#endif
		DeviceDAPara *pDAPara = &CSttDeviceBase::g_pSttDeviceBase->m_oDAPara;
		CSttDeviceBase::g_pSttDeviceBase->WriteDApara(pDAPara);
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x311, 0); //振荡实验参数
	write(m_nfd, pszDrv, sizeof(Drv_Swing));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::ProSwingDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
{
	STT_TEST_EVENT obufEvent;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults = stt_test_get_drvresult_buff();
	g_oDrvMutex.lock();
	int nret = read(m_nfd, pDrvResults, 0x203);
	g_oDrvMutex.unlock();

	if(nret <= 0)
	{
		return;
	}

	long nRealTimeEventCount = 0;

	for(int i = 0; i < nret / m_nDrvResItemLen; i++)
	{
		memcpy(&m_oDrvResItem, pDrvResults + i * m_nDrvResItemLen, m_nDrvResItemLen);
		double dTime = m_oDrvResItem.nSec + m_oDrvResItem.nNanoSec * 0.000000001;

		switch(m_oDrvResItem.nType)
		{
			case DrvResult_TestStart:
			{
				m_oStepInfo.dTime = dTime;
				m_oStepInfo.dLastBinTime = -1;
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
				ProStartBinEvent(m_oDrvResItem.nBi, nRealTimeEventCount, -1, -1, dTime);
				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, -1, -1, dTime, 0);

				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_dTestStartTime = dTime;
					pSttTestBase->m_dwCurTickCount = 0;
					pSttTestBase->ReturnTestStateEvent_TestStart(dTime, 0, TRUE);
				}

				CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom.init();
			}
			break;

			case DrvResult_TestFinish:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->SyncSingleStateTmtResult();
					pSttTestBase->SetTestStarting(FALSE);
					bTestFinished = TRUE;
					oTestFinishedTime.dTime = dTime;
					oTestFinishedTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				}

				AfterTestFinishedPro();
			}
			break;

			case DrvResult_BI:
			{
				DrvBIChange  oBiChg = m_oDrvResItem.oBiChg;
				Drv_BIStatus oBiStatus;
				long nBiSize = g_nBinCount;

				if(g_nBinCount > MAX_BINARYIN_COUNT)
				{
					nBiSize = MAX_BINARYIN_COUNT;
				}

				if(m_oDrvResItem.nGooseFlag & 0x10000)
				{
					nBiSize = 8;
					memcpy(&oBiStatus, &m_oDrvResItem.nDi, sizeof(Drv_BIStatus));
				}
				else
				{
					memcpy(&oBiStatus, &m_oDrvResItem.nBi, sizeof(Drv_BIStatus));
				}

				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				STT_TEST_EVENT obufEvent;
				int nEventIndex = 0;
				obufEvent.oTime.dTime = dTime;
				obufEvent.oTime.dRealTime = dTime - dTestStartTime;
				obufEvent.oTime.dBinActTime = obufEvent.oTime.dTime - m_oStepInfo.dTime;
				GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
				int nBiChang = 0;
				int nBiValue = 0;

				for(int nChanIndex = 0; nChanIndex < nBiSize; nChanIndex++)
				{
					nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
					nBiValue = nBiValue & 0x1;
					nBiChang = oBiChg.item[0].nVal1 >> nChanIndex;
					nBiChang = nBiChang & 0x1;

					if(nBiChang == 0)
					{
						continue;
					}

					nBiValue = (nBiValue == 0 ? 1 : 0);
					obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
					obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
					obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
					obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
					obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
					obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
					nEventIndex++;
					int &nBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[nChanIndex];

					if(nBinSwitchCount < BIBO_ACTCOUNT && nBinSwitchCount > -1)
					{
						oRampRestCom.m_frTimeBinAct[nChanIndex][nBinSwitchCount] = obufEvent.oTime.dTime - m_oStepInfo.dTime;
						nBinSwitchCount++;
					}
				}

				if(nEventIndex > 0)
				{
					obufEvent.nEventInfoCnt = nEventIndex;
					stt_add_test_event(obufEvent);
					nRealTimeEventCount++;
				}
			}
			break;

			case DrvResult_BI_LogicMatch:
			{
				GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
				oRampRestCom.m_nAct = 1;
			}
			break;

			case DrvResult_SwingType_Swing://切换到振荡态
			{
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				m_oStepInfo.dTime = dTime;
				obufEvent.oTime.dTime = dTime;
				obufEvent.oTime.dRealTime = dTime - dTestStartTime;
				obufEvent.oTime.dBinActTime = -1;
				obufEvent.oEventInfo[0].nType = SttResult_Type_Swing_Swing;
				obufEvent.oEventInfo[0].nStateIndex = -1;
				obufEvent.oEventInfo[0].nStateNum = -1;
				obufEvent.oEventInfo[0].nStepIndex = -1;
				obufEvent.oEventInfo[0].nChannel = -1;
				obufEvent.oEventInfo[0].nValue = 0;
				obufEvent.nEventInfoCnt = 1;
				stt_add_test_event(obufEvent);
			}
			break;

			case DrvResult_SwingType_Fault://切换到故障
			{
				double dTestStartTime = dTime;

				if(pSttTestBase != NULL)
				{
					dTestStartTime = pSttTestBase->m_dTestStartTime;
				}

				m_oStepInfo.dTime = dTime;
				obufEvent.oTime.dTime = dTime;
				obufEvent.oTime.dRealTime = dTime - dTestStartTime;
				obufEvent.oTime.dBinActTime = -1;
				obufEvent.oEventInfo[0].nType = SttResult_Type_Swing_Fault;
				obufEvent.oEventInfo[0].nStateIndex = -1;
				obufEvent.oEventInfo[0].nStateNum = -1;
				obufEvent.oEventInfo[0].nStepIndex = -1;
				obufEvent.oEventInfo[0].nChannel = -1;
				obufEvent.oEventInfo[0].nValue = 0;
				obufEvent.nEventInfoCnt = 1;
				stt_add_test_event(obufEvent);
			}
			break;
		}
	}
}

/************振荡实验*************/

/************异常模拟实验*************/
void CSttDeviceComm::tmt_to_drv_AbnPara(tmt_StateParas *pTmt, long nAbnType)
{
	tmt_to_drv_StatePara(pTmt);
	tmt_to_drv_StateItem(pTmt, nAbnType);
}
/************异常模拟实验*************/

/************同期实验*************/
//电压递变量
void CSttDeviceComm::SynPara_VolDeg(tmt_SynParas *pTmt, Drv_SyncAcData *pDrv)
{
	float fStep = pTmt->m_fDrvStepV;
	long nChPos;

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		//Volt
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			Drv_SyncUnit *pSyncUnit = &pDrv->SyncUnit[nIndex];
			float fChMax = pModule->m_oModuleAttr.m_fChMax;
			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			for(int j = 0; j < m_nTmtChanNum; j++)
			{
				nChPos = pModule->m_nChDrvPos[j];
				m_nTmtPos = pModule->m_nChTmtPos[j];

				if(m_nTmtPos < 0 || m_nTmtPos > 5)
				{
					continue;
				}

				tmt_channel &uiVOL = pTmt->m_uiVOL[m_nTmtPos];

				if(uiVOL.Ramp[0].nIndex == 1)
				{
					long nTempPos = CHANNEL_MAX + nChPos * 3 + 2;
					long nH = fStep * 65536 / fChMax;
					double fH = fStep * 65536 / fChMax;
					long nL = (fH - nH) * 65536;
					pSyncUnit->StepAmp[nTempPos] = ((nH << 16) & 0xFFFF0000) + nL;
				}
			}
		}

		int nModuleOffSet = 0;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_I;
		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			Drv_SyncUnit *pSyncUnit = &pDrv->SyncUnit[nModuleOffSet + nIndex];
			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			long nChanSize = CHANNEL_MAX;
			float fChMax;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
			{
				nChanSize = 12;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
			{
				nChanSize = 8;
			}

			for(int j = 0; j < m_nTmtChanNum; j++)
			{
				PSTT_MODULE_CH_DEFS pChDefs = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs;
				if(pChDefs->m_oChDef[j].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					continue;
				}

				fChMax = pChDefs->m_oChDef[j].m_fChACMaxValue;
				nChPos = pModule->m_nChDrvPos[j];
				m_nTmtPos = pModule->m_nChTmtPos[j];

				if(m_nTmtPos < 0 || m_nTmtPos > 5)
				{
					continue;
				}

				tmt_channel &uiVOL = pTmt->m_uiVOL[m_nTmtPos];
				if(uiVOL.Ramp[0].nIndex == 1)
				{
					long nTempPos = nChanSize + nChPos * 3 + 2;
					long nH = fStep * 65536 / fChMax;
					double fH = fStep * 65536 / fChMax;
					long nL = (fH - nH) * 65536;
					pSyncUnit->StepAmp[nTempPos] = ((nH << 16) & 0xFFFF0000) + nL;
				}
			}
		}

	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		int nModuleOffSet = 0;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_I;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_UI;

		long nTempPos, nGroupIndex;

		//Digtal
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
		{
			if(m_oCIEC61850CfgMngr.m_nUseSmv92 != SMVTYPE_92)
			{
				continue;
			}

			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			for(int i = 0; i < DIGITAL_CHANNEL_MAX; i++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[i];

				if(m_nTmtPos < 0 || m_nTmtPos > 5)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					nGroupIndex = i / 3;
				}
				else
				{
					continue;
				}

				nTempPos = GetDigitalDrvPos(i) * 3;
				nTempPos += 2;
				tmt_channel &uiVOL = pTmt->m_uiVOL[m_nTmtPos];

				if(uiVOL.Ramp[0].nIndex == 1)
				{
					//幅值递变
					pDrv->SyncUnit[nModuleOffSet + nIndex].StepAmp[nTempPos] =
						TransDigitalChannelAmp(fStep, nGroupIndex, FALSE, STT_MODULE_TYPE_VOLT, FALSE, 0);
				}
			}
		}
	}
}

//频率递变量
void CSttDeviceComm::SynPara_FreqDeg(tmt_SynParas *pTmt, Drv_SyncAcData *pDrv)
{
	float fStep = pTmt->m_fDrvStepF;
	long nChPos;
	int nModuleOffSet = 0;

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		//Volt
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
			Drv_SyncUnit *pSyncUnit = &pDrv->SyncUnit[nIndex];
			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			for(int j = 0; j < m_nTmtChanNum; j++)
			{
				nChPos = pModule->m_nChDrvPos[j];
				m_nTmtPos = pModule->m_nChTmtPos[j];

				if(m_nTmtPos < 0 || m_nTmtPos > 5)
				{
					continue;
				}

				tmt_channel &uiVOL = pTmt->m_uiVOL[m_nTmtPos];

				if(uiVOL.Ramp[2].nIndex == 1)
				{
					long nTempPos = CHANNEL_MAX + nChPos * 3 + 1;
					pSyncUnit->StepFre[nTempPos] = TranslateACFre(fStep * fFreCoef);
				}
			}
		}

		int nModuleOffSet = 0;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_I;
		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			float fFreCoef = pModule->m_oModuleAttr.m_fFreCoef;
			Drv_SyncUnit *pSyncUnit = &pDrv->SyncUnit[nModuleOffSet + nIndex];
			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			long nChanSize = CHANNEL_MAX;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
			{
				nChanSize = 12;
				fFreCoef = fFreCoef * 8;    //50K
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
			{
				nChanSize = 8;
				fFreCoef = fFreCoef * 8;    //50K
			}

			for(int j = 0; j < m_nTmtChanNum; j++)
			{
				PSTT_MODULE_CH_DEFS pChDefs = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs;
				if(pChDefs->m_oChDef[j].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					continue;
				}

				nChPos = pModule->m_nChDrvPos[j];
				m_nTmtPos = pModule->m_nChTmtPos[j];

				if(m_nTmtPos < 0 || m_nTmtPos > 5)
				{
					continue;
				}

				tmt_channel &uiVOL = pTmt->m_uiVOL[m_nTmtPos];

				if(uiVOL.Ramp[2].nIndex == 1)
				{
					long nTempPos = nChanSize + nChPos * 3 + 1;
					pSyncUnit->StepFre[nTempPos] = TranslateACFre(fStep * fFreCoef);
				}
			}
		}

	}

	nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_I;
	nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_UI;

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		int nModuleOffSet = 0;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_I;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_UI;
		long nTempPos;

		//Digtal
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
		{
			if(m_oCIEC61850CfgMngr.m_nUseSmv92 != SMVTYPE_92)
			{
				continue;
			}

			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			for(int i = 0; i < DIGITAL_CHANNEL_MAX; i++)
			{
				m_nTmtPos = pModule->m_nChTmtPos[i];

				if(m_nTmtPos < 0 || m_nTmtPos > 5)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					continue;
				}

				nTempPos = GetDigitalDrvPos(i) * 3;
				nTempPos += 1;
				tmt_channel &uiVOL = pTmt->m_uiVOL[m_nTmtPos];

				if(uiVOL.Ramp[2].nIndex == 1)
				{
					pDrv->SyncUnit[nModuleOffSet + nIndex].StepFre[nTempPos] =
						TranslateDigitalFre(fStep);
				}
			}
		}
	}
}

void CSttDeviceComm::Syn_volt(tmt_channel *pTmt_channel, Drv_SyncAcData *pDrv, int nModuleUIndex)
{
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nModuleUIndex];

	if(pModule == NULL)
	{
		return;
	}

	int nChPos;
	float fAmp = 0;
	long *dat = &pDrv->SyncUnit[nModuleUIndex].Begindat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_ChannelHarm *oTmtHarm;
	float fFreq = 0;
	float fAngle = 0;

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		m_nTmtPos = k;
		//DC
		{
			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCVolToDrv(0, k, nModuleUIndex, dat + nChPos);
		}

		if(m_nTmtPos < 0 || m_nTmtPos > 5)
		{
			continue;
		}

		//BASE
		{
			oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
			fAmp = oTmtHarm->fAmp;
			fAngle = oTmtHarm->fAngle;
			fFreq = oTmtHarm->fFreq;
			TransAnalogVolToDrv(fAmp, fAngle,
								fFreq, k, nModuleUIndex, dat + CHANNEL_MAX + nChPos * 3);
		}
	}

	pDrv->SyncUnit[nModuleUIndex].DWCount = 6 + 3 * CHANNEL_MAX;
}

void CSttDeviceComm::Syn_UI(tmt_channel *pTmt_channel, Drv_SyncAcData *pDrv, int nModuleIndex)
{
	int nModuleOffSet = g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_I;
	PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nModuleIndex];

	if(pModule == NULL)
	{
		return;
	}

	long nChanSize = CHANNEL_MAX;
	if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
			|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
	{
		nChanSize = 12;
	}
	else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331)
	{
		nChanSize = 8;
	}

	int nChPos;
	float fAmp = 0;
	long *dat = &pDrv->SyncUnit[nModuleOffSet + nModuleIndex].Begindat[0];
	m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;
	tmt_ChannelHarm *oTmtHarm;
	float fFreq = 0;
	float fAngle = 0;

	for(int k = 0; k < m_nTmtChanNum; k++)
	{
		PSTT_MODULE_CH_DEFS pChDefs = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs;
		if(pChDefs->m_oChDef[k].m_nEeType == STT_CH_EETYPE_CURRENT)
		{
			continue;
		}

		m_nTmtPos = k;
		//DC
		{
			nChPos = pModule->m_nChDrvPos[k];
			TransAnalogDCUIToDrv_Volt(0, k, nModuleIndex, dat + nChPos);
		}
		if(m_nTmtPos < 0 || m_nTmtPos > 5)
		{
			continue;
		}

		//BASE
		{
			oTmtHarm = &pTmt_channel[m_nTmtPos].Harm[1];
			fAmp = oTmtHarm->fAmp;
			fAngle = oTmtHarm->fAngle;
			fFreq = oTmtHarm->fFreq;
			TransAnalogUIToDrv_Volt(fAmp, fAngle,
								fFreq, k, nModuleIndex, dat + nChanSize + nChPos * 3);
		}
	}



	pDrv->SyncUnit[nModuleOffSet + nModuleIndex].DWCount = nChanSize + 3 * nChanSize;
}

void CSttDeviceComm::Syn_volt_Digital92(tmt_channel *pTmt_channel, Drv_SyncUnit *pSyncUnit, PSTT_MODULE pModule)
{
	if(pModule == NULL)
	{
		return;
	}

	int nChannelCnt = 37;
	long DrvData[nChannelCnt * 3];
	memset(DrvData, 0, nChannelCnt * 3 * sizeof(long));
	float fAmp, fFre, fPh;
	int nGroupIndex;
	int nTmtPos;

	for(int i = 0; i < nChannelCnt; i++)
	{
		nTmtPos = pModule->m_nChTmtPos[i];

		if(nTmtPos < 0 || nTmtPos > 5)
		{
			continue;
		}

		fAmp = 0;
		fPh = 0;
		fFre = 50;

		if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_VOLTAGE)
		{
			//BASE
			fAmp = pTmt_channel[nTmtPos].Harm[1].fAmp;
			fPh = pTmt_channel[nTmtPos].Harm[1].fAngle;
			fFre = pTmt_channel[nTmtPos].Harm[1].fFreq;
		}
		else
		{
			continue;
		}

		nGroupIndex = nTmtPos / 3;
		TransDigitalChannelToDrv(fAmp, fPh, fFre, nGroupIndex, DrvData + 3 * i, STT_MODULE_TYPE_VOLT, pModule, FALSE, 0);
	}

	long *pBuff = &pSyncUnit->Begindat[0];

	//volt
	for(int j = 0; j < 12; j++)
	{
		if(j > 2)
		{
			pBuff[(j + 1) * 3] = DrvData[j * 3];
			pBuff[(j + 1) * 3 + 1] = DrvData[j * 3 + 1];
			pBuff[(j + 1) * 3 + 2] = DrvData[j * 3 + 2];
		}
		else
		{
			pBuff[j * 3] = DrvData[j * 3];
			pBuff[j * 3 + 1] = DrvData[j * 3 + 1];
			pBuff[j * 3 + 2] = DrvData[j * 3 + 2];
		}
	}

	for(int j = 12; j < 18; j++)
	{
		pBuff[(j + 13) * 3] = DrvData[j * 3];
		pBuff[(j + 13) * 3 + 1] = DrvData[j * 3 + 1];
		pBuff[(j + 13) * 3 + 2] = DrvData[j * 3 + 2];
	}

	//Uz
	pBuff[9] = DrvData[18 * 3];
	pBuff[10] = DrvData[18 * 3 + 1];
	pBuff[11] = DrvData[18 * 3 + 2];

	//current
	for(int j = 19; j < 31; j++)
	{
		pBuff[(j - 6) * 3] = DrvData[j * 3];
		pBuff[(j - 6) * 3 + 1] = DrvData[j * 3 + 1];
		pBuff[(j - 6) * 3 + 2] = DrvData[j * 3 + 2];
	}

	for(int j = 31; j < 37; j++)
	{
		pBuff[j * 3] = DrvData[j * 3];
		pBuff[j * 3 + 1] = DrvData[j * 3 + 1];
		pBuff[j * 3 + 2] = DrvData[j * 3 + 2];
	}
}

void CSttDeviceComm::Syn_NormalPara(tmt_SynParas *pTmt, Drv_SyncParam *pDrv)
{
	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			Syn_volt(pTmt->m_uiVOL, &pDrv->stData, nIndex);
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			Syn_UI(pTmt->m_uiVOL, &pDrv->stData, nIndex);
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		int nModuleOffSet = 0;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_I;
		nModuleOffSet += g_theDeviceSystemParameter->m_nModuleCount_UI;

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];
			Syn_volt_Digital92(pTmt->m_uiVOL, &pDrv->stData.SyncUnit[nModuleOffSet + nIndex], pModule);
			pDrv->stData.SyncUnit[nModuleOffSet + nIndex].DWCount = DIGITAL_CHANNEL_MAX * 3;
		}
	}
}

void CSttDeviceComm::tmt_to_drv_SynPara(tmt_SynParas *pTmt)
{
	char *pszDrv = stt_test_get_drvparas_buff();
	Drv_SyncParam *pDrv = (Drv_SyncParam *)pszDrv;
	memset(pDrv, 0, sizeof(Drv_SyncParam));
	pDrv->trip.syn = 1 << pTmt->m_binIn_Syn;
	pDrv->trip.incA = 1 << pTmt->m_binIn_IncV;
	pDrv->trip.decA = 1 << pTmt->m_binIn_DecV;
	pDrv->trip.incF = 1 << pTmt->m_binIn_IncF;
	pDrv->trip.decF = 1 << pTmt->m_binIn_DecF;
	Syn_NormalPara(pTmt, pDrv); //电气量初始值
	pDrv->stParaRef.RefBeginAmp = pTmt->m_fVg_Mag * 1000 * 1000; //uV
	pDrv->stParaRef.RefBeginFre = pTmt->m_fVg_Fre * 1000 * 1000; //uHz
	pDrv->stParaRef.RefNormalFre = pTmt->m_fVs_Fre * 1000 * 1000; //uHz
	pDrv->stBo.nB4Bit = 3;//4 - 1
	pDrv->stBo.nB4FlipTime = pTmt->m_fBoutKeepTime * 1000;
	pDrv->stBo.nB4FlipType = pTmt->m_nBoutType;
	pDrv->stBo.nBout = 0xFF;

	for(int i = 0; i < 8; i++)
	{
		if(pTmt->m_binOut[i] > 0)
		{
			pDrv->stBo.nBout &= ~(1 << i);
		}
	}

	switch(pTmt->m_nTestType)
	{
		case Stt_Syn_Test_Type_VoltageBoder:
		{
			pDrv->RunType = 0;
			pDrv->StepTime = pTmt->m_fUt * 1000;
			pDrv->stParaRef.RefStepAmp = pTmt->m_fDrvStepV * 1000 * 1000;
			pDrv->stParaRef.RefMaxAmp = pTmt->m_fVoltMax * 1000 * 1000;
			pDrv->stParaRef.RefMinAmp = pTmt->m_fVoltMin * 1000 * 1000;

			if(pTmt->m_fVg_Mag > pTmt->m_fVoltMax)
			{
				pTmt->m_fVoltMax = pTmt->m_fVg_Mag;
			}

			if(pTmt->m_fVs_Mag > pTmt->m_fVg_Mag)
			{
				pDrv->StepType = 1 << 0; //增压
			}
			else
			{
				pDrv->StepType = 1 << 1; //减压
			}

			SynPara_VolDeg(pTmt, &pDrv->stData);
		}
		break;

		case Stt_Syn_Test_Type_FreqBoder:
		{
			pDrv->RunType = 0;
			pDrv->StepTime = pTmt->m_fFt * 1000;
			pDrv->stParaRef.RefStepFre = pTmt->m_fDrvStepF * 1000 * 1000;
			pDrv->stParaRef.RefMaxFre = pTmt->m_fFreMax * 1000 * 1000;
			pDrv->stParaRef.RefMinFre = pTmt->m_fFreMin * 1000 * 1000;
			pTmt->m_fVoltMax = pTmt->m_fVs_Mag * 1.2;

			if(pTmt->m_fVg_Mag > pTmt->m_fVoltMax)
			{
				pTmt->m_fVoltMax = pTmt->m_fVg_Mag;
			}

			if(pTmt->m_fVs_Fre > pTmt->m_fVg_Fre)
			{
				pDrv->StepType = 1 << 2; //增频
			}
			else
			{
				pDrv->StepType = 1 << 3; //减频
			}

			SynPara_FreqDeg(pTmt, &pDrv->stData);
		}
		break;

		case Stt_Syn_Test_Type_AdjVolCycle:
		{
			pDrv->RunType = 1;
			pDrv->StepTime = pTmt->m_fUt * 2 * 1000; //调压周期定值
			pTmt->m_fVoltMax = pTmt->m_fVs_Mag * 1.2;

			if(pTmt->m_fVg_Mag > pTmt->m_fVoltMax)
			{
				pTmt->m_fVoltMax = pTmt->m_fVg_Mag;
			}
		}
		break;

		case Stt_Syn_Test_Type_AdjFreqCycle:
		{
			pDrv->RunType = 2;
			pDrv->StepTime = pTmt->m_fFt * 2 * 1000; //调频周期定值
			pTmt->m_fVoltMax = pTmt->m_fVs_Mag * 1.2;

			if(pTmt->m_fVg_Mag > pTmt->m_fVoltMax)
			{
				pTmt->m_fVoltMax = pTmt->m_fVg_Mag;
			}
		}
		break;

		case Stt_Syn_Test_Type_AutoAdj:
		{
			pDrv->RunType = 3;
			pDrv->StepTime = 1;
			pDrv->stParaRef.RefStepAmp = pTmt->m_fDrvStepV * 1000 * 1000;
			pDrv->stParaRef.RefMaxAmp = pTmt->m_fVoltMax * 1000 * 1000;
			pDrv->stParaRef.RefMinAmp = pTmt->m_fVoltMin * 1000 * 1000;
			pDrv->stParaRef.RefStepFre = pTmt->m_fDrvStepF * 1000 * 1000;
			pDrv->stParaRef.RefMaxFre = pTmt->m_fFreMax * 1000 * 1000;
			pDrv->stParaRef.RefMinFre = pTmt->m_fFreMin * 1000 * 1000;

			if(pTmt->m_fVg_Mag > pTmt->m_fVoltMax)
			{
				pTmt->m_fVoltMax = pTmt->m_fVg_Mag;
			}

			SynPara_VolDeg(pTmt, &pDrv->stData);
			SynPara_FreqDeg(pTmt, &pDrv->stData);
		}
		break;

		case Stt_Syn_Test_Type_LeadAngle:
		{
			pDrv->RunType = 4;
			pDrv->StepTime = pTmt->m_fFt * 1000;
			pTmt->m_fVoltMax = pTmt->m_fVs_Mag * 1.2;

			if(pTmt->m_fVg_Mag > pTmt->m_fVoltMax)
			{
				pTmt->m_fVoltMax = pTmt->m_fVg_Mag;
			}
		}
		break;
	}

	//DA計算
	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		CSttDeviceBase *pSttDeviceBase = CSttDeviceBase::g_pSttDeviceBase;
		pSttDeviceBase->DAPowerCtrl();
		int nModuleIndex;
		pSttDeviceBase->InitDAData();

		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			pSttDeviceBase->SetVoltDApara(pTmt->m_fVoltMax, g_theSystemConfig->m_fAuxDC_Vol, nIndex, FALSE);
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			CSttPowerCtrlBase *pSttPowerCtrlBase = pModule->m_oModuleAttr.m_pPowerCtrlBase;

			if(pSttPowerCtrlBase != NULL)
			{
				pSttPowerCtrlBase->SetVoltDA(pTmt->m_fVoltMax, FALSE);

				nModuleIndex = g_theDeviceSystemParameter->m_nModuleCount_U;
				nModuleIndex += g_theDeviceSystemParameter->m_nModuleCount_I;
				nModuleIndex += nIndex;
				pSttDeviceBase->m_oDAPara.nvolt[nModuleIndex] = pSttPowerCtrlBase->GetModuleDA();
			}
		}

#ifdef _MainBoard_PN_
		if(g_theDeviceSystemParameter->m_nModuleCount_UI > 0)
		{
			PSTT_MODULE pModule_UI = g_theDeviceSystemParameter->m_oModules_UI[0];

			if(pModule_UI != NULL)
			{
				if(pModule_UI->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_V310_C60)
				{
					long nCurModuleIndex = -1;

					if(g_theDeviceSystemParameter->m_nModuleCount_U > 0)
					{
						nCurModuleIndex += 1;
					}

					if(g_theDeviceSystemParameter->m_nModuleCount_I > 0)
					{
						nCurModuleIndex += 1;
					}

					if(nCurModuleIndex >= 0)
					{
						pSttDeviceBase->m_oDAPara.nvolt[nCurModuleIndex + 1] =
								(pSttDeviceBase->m_oDAPara.nvolt[nCurModuleIndex] >> 8) & 0xFF;
					}
				}
			}
		}
#endif
		pSttDeviceBase->WriteDApara(&pSttDeviceBase->m_oDAPara);
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x350, 0);
	write(m_nfd, pDrv, sizeof(Drv_SyncParam));
	g_oDrvMutex.unlock();
}

void CSttDeviceComm::ProSynDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
{
	SynResult &oSynResult = CSttDeviceBase::g_pSttDeviceBase->m_oSynResult;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults = stt_test_get_drvresult_buff();
	g_oDrvMutex.lock();
	int nret = read(m_nfd, pDrvResults, 0x203);
	g_oDrvMutex.unlock();

	if(nret <= 0)
	{
		return;
	}

	for(int i = 0; i < nret / m_nDrvResItemLen; i++)
	{
		memcpy(&m_oDrvResItem, pDrvResults + i * m_nDrvResItemLen, m_nDrvResItemLen);
		double dTime = m_oDrvResItem.nSec + m_oDrvResItem.nNanoSec * 0.000000001;

		switch(m_oDrvResItem.nType)
		{
			case DrvResult_TestStart:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_dTestStartTime = dTime;
					pSttTestBase->m_dwCurTickCount = 0;
					STT_TEST_EVENT obufEvent;
					obufEvent.oTime.dTime = dTime;
					obufEvent.oTime.dRealTime = 0;
					obufEvent.oTime.dBinActTime = 0;
					long nEventIndex = 0;
					int nBiValue;
					int nBoValue;

					for(int nChanIndex = 0; nChanIndex < 8; nChanIndex++)
					{
						nBiValue = m_oDrvResItem.nBi.item[0].nVal1 >> nChanIndex;
						nBiValue = nBiValue & 0x1;
						nBiValue = (nBiValue == 0 ? 1 : 0);
						obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
						obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
						obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
						obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
						obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
						obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
						nEventIndex++;
					}

					obufEvent.nEventInfoCnt = nEventIndex;
					stt_add_test_event(obufEvent);
					nEventIndex = 0;
					unsigned int nBout = m_oDrvResItem.nStep;

					for(int nChanIndex = 0; nChanIndex < 8; nChanIndex++)
					{
						nBoValue = nBout & (1 << nChanIndex);
						obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bout;
						obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
						obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
						obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
						obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
						obufEvent.oEventInfo[nEventIndex].nValue = (nBoValue == 0 ? 1 : 0);
						nEventIndex++;
					}

					obufEvent.nEventInfoCnt = nEventIndex;
					stt_add_test_event(obufEvent);
					pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, TRUE);
					pSttTestBase->m_nCurStepIndex = 0;
					oSynResult.init();
				}
			}
			break;

			case DrvResult_TestFinish:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->SetTestStarting(FALSE);
					bTestFinished = TRUE;
					oTestFinishedTime.dTime = dTime;
					oTestFinishedTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				}

				AfterTestFinishedPro();
			}
			break;

			case DrvResult_Sync_Bin_Syn:
			{
				oSynResult.m_nAct = 1;
				oSynResult.m_fTripValueV = m_oDrvResItem.nStep * 0.000001; //uV 动作值
				oSynResult.m_fTripValueF = m_oDrvResItem.nDegressStep * 0.000001; //uHz 动作值
				oSynResult.m_dActTime = dTime;
			}
			break;

			case DrvResult_Sync_Bo_Flip:
			{
				unsigned int nBout = m_oDrvResItem.nStep;
				unsigned int nBit = m_oDrvResItem.nDegressStep;
				STT_TEST_EVENT obufEvent;
				obufEvent.oTime.dTime = dTime;
				obufEvent.oTime.dRealTime = 0;

				if(pSttTestBase != NULL)
				{
					obufEvent.oTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				}

				obufEvent.oTime.dBinActTime = obufEvent.oTime.dRealTime;
				obufEvent.oEventInfo[0].nType = SttResult_Type_Bout;
				obufEvent.oEventInfo[0].nStateIndex = -1;
				obufEvent.oEventInfo[0].nStateNum = -1;
				obufEvent.oEventInfo[0].nStepIndex = -1;
				obufEvent.oEventInfo[0].nChannel = nBit + 1;
				unsigned int nBoValue = (nBout >> nBit) & 0x1;
				obufEvent.oEventInfo[0].nValue = nBoValue > 0 ? 0 : 1;
				obufEvent.nEventInfoCnt = 1;
				stt_add_test_event(obufEvent);
			}
			break;

			case DrvResult_Sync_Bin_Report:
			{
				BOOL bSrcIsGoose = FALSE;

				if(m_oDrvResItem.nGooseFlag & 0x10000)
				{
					bSrcIsGoose = TRUE;
				}
				else if(m_oDrvResItem.nGooseFlag & 0x20000)
				{
					//FT3
				}

				long nBiChg = m_oDrvResItem.nStep;
				Drv_BIStatus oBiStatus;

				if(bSrcIsGoose)
				{
					memcpy(&oBiStatus, &m_oDrvResItem.nDi, sizeof(Drv_BIStatus));
				}
				else
				{
					memcpy(&oBiStatus, &m_oDrvResItem.nBi, sizeof(Drv_BIStatus));
				}

				STT_TEST_EVENT obufEvent;
				obufEvent.oTime.dTime = dTime;

				if(pSttTestBase != NULL)
				{
					obufEvent.oTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				}

				obufEvent.oTime.dBinActTime = obufEvent.oTime.dRealTime;
				long nEventIndex = 0;
				int nBiValue;

				for(int nChanIndex = 0; nChanIndex < 8; nChanIndex++)
				{
					long nChanChg = 1 << nChanIndex;

					if(nBiChg == nChanChg)
					{
						nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
						nBiValue = nBiValue & 0x1;
						nBiValue = (nBiValue == 0 ? 1 : 0);
						obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
						obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
						obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
						obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
						obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
						obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
						nEventIndex++;
						int nActCount = oSynResult.m_nBinSwitchCount[nChanIndex];

						if(nActCount < BIBO_ACTCOUNT && nActCount > -1)
						{
							oSynResult.m_dTimeBinAct[nChanIndex][nActCount] = dTime;
							oSynResult.m_nBinSwitchCount[nChanIndex]++;
						}
					}
				}

				obufEvent.nEventInfoCnt = nEventIndex;
				stt_add_test_event(obufEvent);
			}
			break;

			case DrvResult_Sync_Degress:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_nCurStepIndex = m_oDrvResItem.nDegressStep;
				}
			}
			break;
		}
	}
}
/************同期实验*************/

/************SOE实验*************/
void CSttDeviceComm::tmt_to_drv_soe(tmt_SoeTest *pTmt)
{
	SwitchModules oSwitchPara = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	char *pszDrv = stt_test_get_drvparas_buff();
	Drv_SoeExPara *stBinOut = (Drv_SoeExPara *)pszDrv;
	memset(stBinOut, 0, sizeof(Drv_SoeExPara));

	if(pTmt->m_oSoeParas.m_nMode == 0)
	{
		stBinOut->nTripType = 0;
	}
	else
	{
		stBinOut->nGPS_Nsec = 0;//纳秒值转换
		stBinOut->nTripType = 1;
		short nYear, nMon, nDay, nHour, nMin, nSec;
		TransTimer_t(g_theSttDeviceStatus->m_nUser_s, nYear, nMon, nDay, nHour, nMin, nSec);
		nHour = pTmt->m_oSoeParas.m_tGps.nHour;
		nMin = pTmt->m_oSoeParas.m_tGps.nMinutes;
		nSec = pTmt->m_oSoeParas.m_tGps.nSeconds;
		unsigned int ntime_t;
		TransTimer_To_t(ntime_t, nYear, nMon, nDay, nHour, nMin, nSec);
		ntime_t -= g_theSttDeviceStatus->m_nTimeZone * 3600;
		stBinOut->nGPS_Sec = ntime_t;
	}

	stBinOut->nModuleCnt = oSwitchPara.m_nModulesCount;
	stBinOut->nMode = pTmt->m_oSoeParas.m_nSelect;
	stBinOut->nUseBiRes = pTmt->m_oSoeParas.m_nBiAct;
	int nBoutOffset = 0;
	int nBoutIndex = 0;
	int nIndex = 0;
	unsigned int time0, time1, time2;

	if(pTmt->m_oSoeParas.m_nSelect == 0)
	{
		for(int nIndex = 0; nIndex < 8; nIndex++)
		{
			if(pTmt->m_oSoeParas.m_binOut[nIndex].isValid == 1)
			{
				time0 = pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[0].time;
				if(time0 > 0)
				{
					//有变化前时间
					if(pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[0].val == 1)
					{
						stBinOut->item[0].nBinOut[0] |= 1<<nIndex;
					}
				}
				else
				{
					if(pTmt->m_oSoeParas.m_binOut[nIndex].cnt > 0)
					{
						if(pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[0].val == 0)
						{
							//按初值直接翻转
							stBinOut->item[0].nBinOut[0] |= 1<<nIndex;
						}
					}
				}
			}
		}
	}
	else if(pTmt->m_oSoeParas.m_nSelect == 1)
	{
		for(int nModule = 0; nModule < stBinOut->nModuleCnt; nModule++)
		{
			if(nModule > 0)
			{
				nBoutOffset = oSwitchPara.oSWITCHINFO[nModule - 1].m_nBoCount;
			}

			stBinOut->item[nModule].nModule = ModuleIndexTransToDrv(oSwitchPara.oSWITCHINFO[nModule].m_nModulePos);
			stBinOut->item[nModule].nDelayTime = 0;
			stBinOut->item[nModule].nBinOut[0] = 0xffffffff;
			stBinOut->item[nModule].nBinOut[1] = 0xffffffff;

			long nExBo = 0;
			for(int i = 0; i < 64; i++)
			{
				if(oSwitchPara.oSWITCHINFO[nModule].m_bBoPos[i] == FALSE)
				{
					continue;
				}

				time0 = pTmt->m_oSoeParas.m_binOutEx[nExBo + nBoutOffset].otmt_SoeState[0].time * 50000;
				time1 = pTmt->m_oSoeParas.m_binOutEx[nExBo + nBoutOffset].otmt_SoeState[1].time * 50000;
				time2 = pTmt->m_oSoeParas.m_binOutEx[nExBo + nBoutOffset].otmt_SoeState[2].time * 50000;

				if(pTmt->m_oSoeParas.m_binOutEx[nExBo + nBoutOffset].isValid == 1)
				{
					nIndex = nExBo + nBoutIndex - 1;

					if((nExBo + nBoutIndex) > 32)
					{
						stBinOut->item[nModule].nType[1] |= 1 << (nIndex - 32);
					}
					else
					{
						stBinOut->item[nModule].nType[0] |= 1 << nIndex;
					}

					stBinOut->item[nModule].nBeginTime[nIndex] = time0;
					stBinOut->item[nModule].param[nIndex].nTmHigh = time2;
					stBinOut->item[nModule].param[nIndex].nTmLow = time1;
					stBinOut->item[nModule].param[nIndex].nflipCnt =
						pTmt->m_oSoeParas.m_binOutEx[nExBo + nBoutOffset].cnt;
				}

				nExBo++;
			}
		}
	}

	stBinOut->nHoldTime = pTmt->m_oSoeParas.m_fHoldTime;
	stBinOut->nHoldTime += 1;
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x340, 0);
	write(m_nfd, (char *)stBinOut, sizeof(Drv_SoeExPara));
	g_oDrvMutex.unlock();

	if(pTmt->m_oSoeParas.m_nSelect == 0)
	{
		unsigned int nInitBo = stBinOut->item[0].nBinOut[0];
		char *pszDrv = stt_test_get_drvresult_buff();
		Drv_SoePara *stBOut = (Drv_SoePara *)pszDrv;
		memset(stBOut, 0, sizeof(Drv_SoePara));
		char *pszTmt = stt_test_get_drvparas_buff();
		Tmt_SoeParas *pSoeParas = (Tmt_SoeParas *)pszTmt;
		memset(pSoeParas, 0, sizeof(Tmt_SoeParas));

		for(int nIndex = 0; nIndex < 8; nIndex++)
		{
			time0 = pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[0].time;//翻转前时间
			time1 = pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[1].time;//闭合时间
			time2 = pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[2].time;//断开时间

			if(pTmt->m_oSoeParas.m_binOut[nIndex].isValid == 1
					&& pTmt->m_oSoeParas.m_binOut[nIndex].cnt > 0)
			{
				long nflipCnt = 0;
				if(time0 > 0)
				{
					pSoeParas->oTmt_SoePara[nIndex].oStep[0].nMsTime = time0;
					if(pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[0].val == 0)
						pSoeParas->oTmt_SoePara[nIndex].oStep[0].nBo = 1;
					else
						pSoeParas->oTmt_SoePara[nIndex].oStep[0].nBo = 0;
				}
				else
				{
					if(pTmt->m_oSoeParas.m_binOut[nIndex].otmt_SoeState[0].val == 0)
					{
						pSoeParas->oTmt_SoePara[nIndex].oStep[0].nMsTime = time1;
						pSoeParas->oTmt_SoePara[nIndex].oStep[0].nBo = 0;
					}
					else
					{
						pSoeParas->oTmt_SoePara[nIndex].oStep[0].nMsTime = time2;
						pSoeParas->oTmt_SoePara[nIndex].oStep[0].nBo = 1;
					}
				}
				nflipCnt++;

				while(1)
				{
					if(nflipCnt == pTmt->m_oSoeParas.m_binOut[nIndex].cnt || nflipCnt == 1005)
					{
						pSoeParas->oTmt_SoePara[nIndex].nStepCnt = nflipCnt;
						break;
					}

					if(pSoeParas->oTmt_SoePara[nIndex].oStep[nflipCnt - 1].nBo == 0)
					{
						pSoeParas->oTmt_SoePara[nIndex].oStep[nflipCnt].nMsTime = time2
								+ pSoeParas->oTmt_SoePara[nIndex].oStep[nflipCnt - 1].nMsTime;
						pSoeParas->oTmt_SoePara[nIndex].oStep[nflipCnt].nBo = 1;
					}
					else
					{
						pSoeParas->oTmt_SoePara[nIndex].oStep[nflipCnt].nMsTime = time1
								+ pSoeParas->oTmt_SoePara[nIndex].oStep[nflipCnt - 1].nMsTime;
						pSoeParas->oTmt_SoePara[nIndex].oStep[nflipCnt].nBo = 0;
					}
					nflipCnt++;
				}
			}
		}

		long nFlipIndex[8];
		unsigned int nMinTime = 0xFFFFFFFF;
		for(int nIndex = 0; nIndex < 8; nIndex++)
		{
			nFlipIndex[nIndex] = 0;			
		}

		while(1)
		{
			if(nFlipIndex[0] == pSoeParas->oTmt_SoePara[0].nStepCnt
					&& nFlipIndex[1] == pSoeParas->oTmt_SoePara[1].nStepCnt
					&& nFlipIndex[2] == pSoeParas->oTmt_SoePara[2].nStepCnt
					&& nFlipIndex[3] == pSoeParas->oTmt_SoePara[3].nStepCnt
					&& nFlipIndex[4] == pSoeParas->oTmt_SoePara[4].nStepCnt
					&& nFlipIndex[5] == pSoeParas->oTmt_SoePara[5].nStepCnt
					&& nFlipIndex[6] == pSoeParas->oTmt_SoePara[6].nStepCnt
					&& nFlipIndex[7] == pSoeParas->oTmt_SoePara[7].nStepCnt)
			{
				break;
			}

			nMinTime = 0xFFFFFFFF;
			for(int nIndex = 0; nIndex < 8; nIndex++)
			{
				if(nFlipIndex[nIndex] < pSoeParas->oTmt_SoePara[nIndex].nStepCnt)
				{
					Tmt_SoeStep *pSoeStep = &pSoeParas->oTmt_SoePara[nIndex].oStep[nFlipIndex[nIndex]];
					if(pSoeStep->nMsTime < nMinTime)
					{
						nMinTime = pSoeStep->nMsTime;
					}
				}
			}

			long nStepIndex = stBOut->nStepCnt;
			if(nStepIndex == 0)
			{
				stBOut->nBo[nStepIndex] = nInitBo;
			}
			else
			{
				stBOut->nBo[nStepIndex] = stBOut->nBo[nStepIndex - 1];
			}

			for(int nIndex = 0; nIndex < 8; nIndex++)
			{
				Tmt_SoeStep *pSoeStep = &pSoeParas->oTmt_SoePara[nIndex].oStep[nFlipIndex[nIndex]];
				if(nFlipIndex[nIndex] < pSoeParas->oTmt_SoePara[nIndex].nStepCnt)
				{					
					if(pSoeStep->nMsTime == nMinTime)
					{
						if(pSoeStep->nBo == 1)
						{
							stBOut->nBo[nStepIndex] |= 1 << nIndex;
						}
						else
						{
							stBOut->nBo[nStepIndex] &= ~(1 << nIndex);
						}

						stBOut->nDiffTime[nStepIndex] = nMinTime;
						nFlipIndex[nIndex]++;
					}
				}
				else
				{
					pSoeStep->nMsTime = 0xFFFFFFFF;
				}
			}
			stBOut->nStepCnt++;

			if(stBOut->nStepCnt == SOE_MAX - 1)
			{
				break;
			}
		}

		unsigned int nDiffTimes[SOE_MAX];
		nDiffTimes[0] = stBOut->nDiffTime[0];
		for(int nIndex = 1; nIndex < stBOut->nStepCnt; nIndex++)
		{
			nDiffTimes[nIndex] = stBOut->nDiffTime[nIndex] - stBOut->nDiffTime[nIndex - 1];
		}
		for(int nIndex = 1; nIndex < stBOut->nStepCnt; nIndex++)
		{
			stBOut->nDiffTime[nIndex] = nDiffTimes[nIndex];
		}

		long nStepIndex = stBOut->nStepCnt;
		if(nStepIndex > 0)
		{
			stBOut->nBo[nStepIndex] = stBOut->nBo[nStepIndex - 1];
			stBOut->nDiffTime[nStepIndex] = 1000;
			stBOut->nStepCnt++;
		}

		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x340, 1);
		write(m_nfd, (char *)stBOut, sizeof(Drv_SoePara));
		g_oDrvMutex.unlock();
	}
}

void CSttDeviceComm::ProSoeDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
{
	GradientResult_Com &oRampRestCom = CSttDeviceBase::g_pSttDeviceBase->m_oRampRestCom;
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	char *pDrvResults = stt_test_get_drvresult_buff();
	g_oDrvMutex.lock();
	int nret = read(m_nfd, pDrvResults, 0x203);
	g_oDrvMutex.unlock();

	if(nret <= 0)
	{
		return;
	}

	double dTime;

	for(int i = 0; i < nret / m_nDrvResItemLen; i++)
	{
		memcpy(&m_oDrvResItem, pDrvResults + i * m_nDrvResItemLen, m_nDrvResItemLen);
		dTime = m_oDrvResItem.nSec + m_oDrvResItem.nNanoSec * 0.000000001;

		switch(m_oDrvResItem.nType)
		{
			case DrvResult_TestStart:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->m_dTestStartTime = dTime;
					oRampRestCom.init();
					pSttTestBase->ReturnTestStateEvent_TestStart(pSttTestBase->m_dTestStartTime, 0, FALSE);
					pSttTestBase->ProRtDatasEvent(dTime, 0, 0, 0, 0);
				}
			}
			break;

			case DrvResult_TestFinish:
			{
				if(pSttTestBase != NULL)
				{
					pSttTestBase->SetTestStarting(FALSE);
					bTestFinished = TRUE;
					oTestFinishedTime.dTime = dTime;
					oTestFinishedTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				}
			}
			break;

			case DrvResult_BI:
			{
				DrvBIChange  oBiChg = m_oDrvResItem.oBiChg;
				Drv_BIStatus oBiStatus = m_oDrvResItem.nBi;
				BOOL bUseBiTime = oBiStatus.nitem0Valid;
				STT_TEST_EVENT obufEvent;
				int nEventIndex = 0;
				obufEvent.oTime.dTime = dTime;
				obufEvent.oTime.dRealTime = dTime - pSttTestBase->m_dTestStartTime;
				obufEvent.oTime.dBinActTime = -1;
				int nBiChang = 0;
				int nBiValue = 0;

				for(int nChanIndex = 0; nChanIndex < MAX_BINARYIN_COUNT && nChanIndex < g_nBinCount; nChanIndex++)
				{
					nBiValue = oBiStatus.item[0].nVal1 >> nChanIndex;
					nBiValue = nBiValue & 0x1;
					nBiChang = oBiChg.item[0].nVal1 >> nChanIndex;
					nBiChang = nBiChang & 0x1;

					if(nBiChang == 0)
					{
						continue;
					}

					nBiValue = (nBiValue == 0 ? 1 : 0);
					obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
					obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
					obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
					obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
					obufEvent.oEventInfo[nEventIndex].nChannel = nChanIndex + 1;
					obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
					nEventIndex++;
#ifdef _MainBoard_PI_

					if(bUseBiTime)
					{
						double dTimeBi = oBiStatus.item0.nSec[nChanIndex] +
										 oBiStatus.item0.nNSec[nChanIndex] * 0.000000001;
						obufEvent.oTime.dTime = dTimeBi;
						obufEvent.oTime.dRealTime = dTimeBi - pSttTestBase->m_dTestStartTime;
					}

#endif
					int &nBinSwitchCount = oRampRestCom.m_nrBinSwitchCount[nChanIndex];

					if(nBinSwitchCount < BIBO_ACTCOUNT && nBinSwitchCount > -1)
					{
						oRampRestCom.m_frTimeBinAct[nChanIndex][nBinSwitchCount] = obufEvent.oTime.dRealTime;
						nBinSwitchCount++;
					}

#ifdef _MainBoard_PI_

					if(bUseBiTime)
					{
						obufEvent.nEventInfoCnt = 1;
						stt_add_test_event(obufEvent);
						nEventIndex = 0;
					}

#endif
				}

				SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;

				if(oSwitchModules.m_nModulesCount > 0)
				{
					int nOffSet = 0;

					for(int j = 0; j < oSwitchModules.m_nModulesCount; j++)
					{
						if(j > 0)
						{
							nOffSet += oSwitchModules.oSWITCHINFO[j - 1].m_nBiCount;
						}

						long nBiIndex = 0;
						for(int k = 0; k < 64; k++)
						{
							if(oSwitchModules.oSWITCHINFO[j].m_bBiPos[k] == FALSE)
							{
								continue;
							}
							if(k < 32)
							{
								nBiValue = (oBiStatus.item[j + 1].nVal1 >> k) & 1;
								nBiChang = (oBiChg.item[j + 1].nVal1 >> k) & 1;
							}
							else
							{
								nBiValue = (oBiStatus.item[j + 1].nVal2 >> (k - 32)) & 1;
								nBiChang = (oBiChg.item[j + 1].nVal2 >> (k - 32)) & 1;
							}

							if(nBiChang == 0)
							{
								nBiIndex++;
								continue;
							}
							obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_BinEx;
							obufEvent.oEventInfo[nEventIndex].nStateIndex = -1;
							obufEvent.oEventInfo[nEventIndex].nStateNum = -1;
							obufEvent.oEventInfo[nEventIndex].nStepIndex = -1;
							obufEvent.oEventInfo[nEventIndex].nChannel = nOffSet + nBiIndex + 1;
							obufEvent.oEventInfo[nEventIndex].nValue = nBiValue > 0 ? 0 : 1;
							nEventIndex++;
							int &nBinExSwitchCount = oRampRestCom.m_nrBinExSwitchCount[nOffSet + nBiIndex];

							if(nBinExSwitchCount < BIBO_ACTCOUNT && nBinExSwitchCount > -1)
							{
								oRampRestCom.m_frTimeBinExAct[nOffSet + nBiIndex][nBinExSwitchCount] = obufEvent.oTime.dRealTime;
								nBinExSwitchCount++;
							}

							nBiIndex++;
						}
					}
				}

				if(nEventIndex > 0)
				{
					obufEvent.nEventInfoCnt = nEventIndex;
					stt_add_test_event(obufEvent);
				}
			}
			break;

			case DrvResult_BO:
			{
				long nRealTimeEventCount = 0;
				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, -1, -1,
								 dTime, dTime - pSttTestBase->m_dTestStartTime, FALSE);
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
			}
			break;

			case DrvResult_BO_REFVAL:
			{
				long nRealTimeEventCount = 0;
				ProCommBoutEvent(m_oDrvResItem.nBo, nRealTimeEventCount, -1, -1,
								 dTime, dTime - pSttTestBase->m_dTestStartTime);
				memcpy(&m_oPreBoStatus, &m_oDrvResItem.nBo, sizeof(DrvComBoStatus));
			}
			break;
		}
	}
}
/************SOE实验*************/

/************合并单元实验*************/
void CSttDeviceComm::tmt_to_drv_MUTest(tmt_ManualTest *pTmt, BOOL bIsStartTest)
{
	if(bIsStartTest && g_theDeviceSystemParameter->m_nModuleCount_D > 0)
	{
		//强制发B码
		Drv_ComData oComData;
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[0];
		long nSample = m_oCIEC61850CfgMngr.m_p6044MngrBase->GetSample();
		unsigned short nT = 10000000 / nSample;
		oComData.nModule = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
		oComData.dat[0] = 0x05640564;
		oComData.dat[1] = 9;
		oComData.dat[2] = 0x1006;
		oComData.dat[3] = nSample << 16 | nT;

		for(int i = 0; i < 12; i++)
		{
			oComData.dat[4] |= 1 << (i + 20);
		}

		SetTestPara(ComDataPkg, (char *)&oComData);
	}

	char *pszDrv = stt_test_get_drvparas_buff();
	ManuRtData oRtData;
	memcpy(oRtData.uiVOL, pTmt->m_oManuParas.m_uiVOL, sizeof(tmt_channel)*g_nRtDataVoltCnt);
	memcpy(oRtData.uiCUR, pTmt->m_oManuParas.m_uiCUR, sizeof(tmt_channel)*g_nRtDataCurrCnt);
	CSttDeviceBase::g_pSttDeviceBase->m_oManuRtList.append(oRtData);
	Drv_ManuData *pDrv = (Drv_ManuData *)pszDrv;
	memset(pDrv, 0, sizeof(Drv_ManuData));

	if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
	{
		pDrv->nReLoadFT3 = 1;//强制恢复B码
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[0];
		pDrv->nFT3Module = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
	}

	if(pTmt->m_oManuParas.m_nFuncType == 4)
	{
		//守时实验
		pDrv->nPPSDelayTime = pTmt->m_oManuParas.m_oMuParas.nSynTime;
	}

	long nHarm = 1;

	if(pTmt->m_oManuParas.m_nSelHarm)
	{
		nHarm = 2;

		for(int i = 0; i < MAX_VOLTAGE_COUNT; i++)
		{
			pTmt->m_oManuParas.m_uiVOL[i].Harm[pTmt->m_oManuParas.m_nHarmIndex].nSelectIndex = 1;
		}

		for(int i = 0; i < MAX_CURRENT_COUNT; i++)
		{
			pTmt->m_oManuParas.m_uiCUR[i].Harm[pTmt->m_oManuParas.m_nHarmIndex].nSelectIndex = 1;
		}
	}

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		//VOLT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			Manual_volt(pTmt->m_oManuParas.m_uiVOL, pszDrv, nHarm, nIndex);
		}

		//CURRENT
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			Manual_current(pTmt->m_oManuParas.m_uiCUR, pszDrv, nHarm, nIndex);
		}

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			Manual_UI(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nHarm, nIndex);
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		if(g_theDeviceSystemParameter->m_nModuleCount_D > 0)
		{
			int nAnalogModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_U;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_I;
			nAnalogModuleCnt += g_theDeviceSystemParameter->m_nModuleCount_UI;

			for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];
				//BASE
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
												  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat, pModule, 1);

				for(int m = 1; m < 31; m++)
				{
					TranslateDigitalVoltCurrentBuffer(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
													  pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].dat + DIGITAL_CHANNEL_MAX * 3 * m, pModule, m + 1);
				}

				pDrv->oDrv_HarmParam[nAnalogModuleCnt + i].nDWcnt = DIGITAL_CHANNEL_MAX * 3 * 31;
			}

			SetGooseValue_ManuTest(&pTmt->m_oManuParas.m_oGoosePub[0], bIsStartTest);
		}

		if(g_theDeviceSystemParameter->m_nModuleCount_ADMU > 0)
		{
			int nModuleCnt = g_theDeviceSystemParameter->m_nModuleCount_ADMU;
			pDrv->oDrv_ADMUHarm.nModuleCnt = nModuleCnt;

			for(int i = 0; i < nModuleCnt; i++)
			{
				PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[i];
				pDrv->oDrv_ADMUHarm.nModule[i] = ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex);
				pDrv->oDrv_ADMUHarm.oHarmParam[i].dat[0] = 2;//片选 10
				//不同数字板的硬件相位补偿不同
				TranslateDigitalVoltCurrentBuffer(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
												  pDrv->oDrv_ADMUHarm.oHarmParam[i].dat + 1, pModule, 1, TRUE);
				pDrv->oDrv_ADMUHarm.oHarmParam[i].nDWcnt = 1+ DIGITAL_CHANNEL_MAX * 3;
			}
		}
	}

	if(g_theSystemConfig->m_nHasWeek != 0)
	{
		BOOL bHasSetTap = FALSE;
		BOOL bSetTap;

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_WEEK; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_WEEK[nIndex];

			bSetTap = FALSE;
			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN)
			{
				Manual_Week_PN_Main(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
									1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA48S)
			{
				Manual_Week_PIA48S(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								   1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS)
			{
				Manual_Week_PIA12DS(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT)
			{
				Manual_Week_EVTECT(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								   1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331)
			{
				Manual_Week_PNS331(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								   1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT_Ex1)
			{
				Manual_Week_EVTECT_Ex1(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex, FALSE);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V)
			{
				Manual_Week_DC6U10V(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex, FALSE);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA)
			{
				Manual_Week_DC6I20mA(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex, FALSE);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_DC6U6I)
			{
				Manual_Week_PN_DC6U6I(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv, nIndex);
				bSetTap = TRUE;
			}
			else if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
			{
				Manual_Week_L336D(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								  1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
				bSetTap = TRUE;
			}

			if(bSetTap)
			{
				bHasSetTap = TRUE;
				m_nDCTap = g_nWeekTap;
				m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
				g_oDrvMutex.lock();
				ioctl(m_nfd, 0x125, m_nDCTap);
				g_oDrvMutex.unlock();
			}
		}

		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_ADMU; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_ADMU[nIndex];
			Manual_Week_ADMU(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR, pszDrv,
								1, nIndex, pTmt->m_oManuParas.m_bDC, FALSE);
			m_nDCTap = g_nWeekTap;
			m_nDCTap |= ModuleIndexTransToDrv(pModule->m_oModuleAttr.m_nModuleIndex) << 16;
			g_oDrvMutex.lock();
			ioctl(m_nfd, 0x125, m_nDCTap);
			g_oDrvMutex.unlock();
			bHasSetTap = TRUE;
		}

		if(bHasSetTap)
		{
			Sleep(100);
		}
	}

	SetTestCommBo(pDrv->oDrvComBoSta, pTmt->m_oManuParas.m_binOut, pTmt->m_oManuParas.m_binOutEx);

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x300, 0);
	write(m_nfd, pszDrv, sizeof(Drv_ManuData));
	g_oDrvMutex.unlock();

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		CSttDeviceBase::g_pSttDeviceBase->DAValueCalc_Comm(pTmt->m_oManuParas.m_uiVOL, pTmt->m_oManuParas.m_uiCUR,
				1, pTmt->m_oManuParas.m_bDC, 0, 0, 0, g_theSystemConfig->m_fAuxDC_Vol);
	}
}
/************合并单元实验*************/

void CSttDeviceComm::SetIEC61850Para()
{
	//下载IEC配置的处理入口
	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x121, 0);//先关闭数字保持
	ioctl(m_nfd, 0xA00, 0); //关DMA
	ioctl(m_nfd, 0x103, 0);
	g_oDrvMutex.unlock();

	m_oCIEC61850CfgMngr.InitIEC61850Para();
	int nGseOutCnt = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.count();

	for(int index = 0; index < nGseOutCnt && index < MAX_MODULES_GOOSEPUB_COUNT; index++)
	{
		tmt_goose otmt_goose = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.at(index);

		for(int chanid = 0; chanid < otmt_goose.vChanelInfo.size(); chanid++)
		{
			if(chanid < MAX_GOOSE_CHANNEL_COUNT)
			{
				ChanelInfo oChanelInfo = otmt_goose.vChanelInfo.at(chanid);
				m_oPreGoosePub[index].m_strChannel[chanid] = oChanelInfo.firstvalue;
			}
		}
	}

	int nFt3OutCnt = m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044.count();
	const tmt_ft3_6044 *p_ft3_6044;

	for(int index = 0; index < nFt3OutCnt && index < MAX_MODULES_FT3PUB_COUNT; index++)
	{
		p_ft3_6044 = &(m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044.at(index));

		for(int chanid = 0; chanid < p_ft3_6044->m_oChanList.size(); chanid++)
		{
			if(chanid < MAX_FT3_CHANNEL_COUNT)
			{
				FT3ChanInfo oChanelInfo = p_ft3_6044->m_oChanList.at(chanid);
				m_oPreFt3Pub[index].m_strChannel[chanid] = CString::number(oChanelInfo.nFirstValue);
			}
		}
	}
}

void *CSttDeviceComm::GetIecCfgDatasMngr()
{
	return &(m_oCIEC61850CfgMngr.m_oIecCfgDatasMngr);
}

BOOL CSttDeviceComm::SetGooseValue_Com(tmt_GoosePub *pCurGoosePub, tmt_goose *ptmt_goose,
									   DrvGseChgParas *pGseChgParas, tmt_GoosePub *pPreGoosePub, BOOL bIsCompare)
{
	BOOL bRet = FALSE;
	QString strPreChanVal, strCurChanVal, strMap;
	BOOL bIsChanChgValid;

	for(int chanid = 0; chanid < ptmt_goose->vChanelInfo.size(); chanid++)
	{
		if(chanid >= MAX_GOOSE_CHANNEL_COUNT)
		{
			return bRet;
		}

		ChanelInfo oChanelInfo = ptmt_goose->vChanelInfo.at(chanid);
		strMap = oChanelInfo.data_type;

		if(QString::compare(strMap, "Timestamp") == 0)	//UTC通道不允许改值
		{
			continue;
		}

		if(oChanelInfo.nBOIndex > 0 || oChanelInfo.nBOExIndex > 0) //绑定开出映射不允许改值
		{
			continue;
		}

		strCurChanVal = pCurGoosePub->m_strChannel[chanid];

		if(strCurChanVal.length() == 0)
		{
			continue;    //通道值数据无效
		}

		bIsChanChgValid = FALSE;

		if(bIsCompare)
		{
			strPreChanVal = pPreGoosePub->m_strChannel[chanid];

			if(strPreChanVal.length() == 0)
			{
				continue;    //通道值数据无效
			}

			if(strPreChanVal.compare(strCurChanVal) != 0)
			{
				bIsChanChgValid = TRUE;
			}
		}
		else
		{
			bIsChanChgValid = TRUE;
		}

		if(bIsChanChgValid)
		{
			oChanelInfo.firstvalue = strCurChanVal;
			QByteArray ovalue;

			if(!m_oCIEC61850CfgMngr.m_oGooseMngr.CreateGooseOut_DataSetList(ovalue, oChanelInfo, ptmt_goose->ntimequality))
			{
				continue;    //数值与配置类型不匹配时
			}

			int nGroup = ptmt_goose->group;

			for(int nMIndex = 0; nMIndex < pGseChgParas->nModulesCnt; nMIndex++)
			{
				if(pGseChgParas->oModule[nMIndex].nModuleIndex == ptmt_goose->m_nModuleIndex)
				{
					for(int nGIndex = 0; nGIndex < pGseChgParas->oModule[nMIndex].nItemsCnt; nGIndex++)
					{
						if(pGseChgParas->oModule[nMIndex].oItem[nGIndex].nGroupIndex == nGroup)
						{
							DrvGseChgItem *pGseChgItem = &pGseChgParas->oModule[nMIndex].oItem[nGIndex];
							int nDatCnt = pGseChgItem->nDatCnt;
							memcpy(pGseChgItem->oDat[nDatCnt].szdat, ovalue, ovalue.size());
							pGseChgItem->oDat[nDatCnt].nPos = ptmt_goose->nDataSetPos + oChanelInfo.nPos;
							pGseChgItem->oDat[nDatCnt].nCnt = ovalue.size();
							pGseChgItem->nDatCnt++;
							int nUTCCnt = pGseChgItem->nUTCCnt;

							if(oChanelInfo.bHasUTC)
							{
								pGseChgItem->nUTCPos[nUTCCnt] = ptmt_goose->nDataSetPos + oChanelInfo.nUTCPos;
								pGseChgItem->nUTCCnt++;
							}

							bRet = TRUE;
							break;
						}
					}

					break;
				}
			}
		}
	}

	return bRet;
}

void CSttDeviceComm::SetGooseValue_StateTest(tmt_StateParas *pStateParas, int nIndex, Drv_StateItem *pDrvState, BOOL bHasGseAbn)
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	long nStateNum = pSttTestBase->GetStateNum(nIndex);

	if(nStateNum < 0)
	{
		return;
	}

	memcpy(&pDrvState->oGseChgParas, m_oCIEC61850CfgMngr.m_pGseChgParas, sizeof(DrvGseChgParas));
	BOOL bRet = FALSE;
	BOOL bSetGooseValue;
	BOOL bTestValid;
	BOOL bIsCompare = TRUE;
	int nPreTestMode;
	int nCurTestMode;
	int nGseOutCnt =  m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.count();

	for(int index = 0; index < nGseOutCnt && index < MAX_MODULES_GOOSEPUB_COUNT; index++)
	{
		tmt_goose otmt_goose = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.at(index);

		if(!pStateParas->m_paraState[nStateNum].m_oGoosePub[index].m_bUseFlag)
		{
			continue;    //无需变位
		}

		if(bHasGseAbn)
		{
			if(index == pStateParas->m_paraState[nStateNum].m_oAbnormalGOOSE.m_nGroupIndex)
			{
				continue;//异常模拟不走变位逻辑
			}
		}

		bTestValid = pStateParas->m_paraState[nStateNum].m_oGoosePub[index].m_bHasTest;
		nCurTestMode = pStateParas->m_paraState[nStateNum].m_oGoosePub[index].m_nTest;
		pDrvState->GooseTest.nCount = pDrvState->oGseChgParas.nModulesCnt;

		for(int i = 0; i < pDrvState->oGseChgParas.nModulesCnt; i++)
		{
			pDrvState->GooseTest.dat[i].module = pDrvState->oGseChgParas.oModule[i].nModuleIndex;
		}

		int nGSTestdataCnt;

		if(nIndex == 0)
		{
			for(int i = 0; i < pDrvState->GooseTest.nCount; i++)
			{
				nGSTestdataCnt = pDrvState->GooseTest.dat[i].nCount;

				if(pDrvState->GooseTest.dat[i].module == otmt_goose.m_nModuleIndex)
				{
					pDrvState->GooseTest.dat[i].gs[nGSTestdataCnt].group = otmt_goose.group;
					pDrvState->GooseTest.dat[i].gs[nGSTestdataCnt].value = nCurTestMode;
					pDrvState->GooseTest.dat[i].gs[nGSTestdataCnt].pos = otmt_goose.nTestModePos;
					pDrvState->GooseTest.dat[i].nCount++;
				}
			}
		}
		else
		{
			//有检修位改变需求
			if(bTestValid)
			{
				long nPreStateNum = pSttTestBase->GetStateNum(nIndex - 1);

				if(nPreStateNum < 0)
				{
					return;
				}

				nPreTestMode = pStateParas->m_paraState[nPreStateNum].m_oGoosePub[index].m_nTest;

				if(nPreTestMode != nCurTestMode)
				{
					for(int i = 0; i < pDrvState->GooseTest.nCount; i++)
					{
						nGSTestdataCnt = pDrvState->GooseTest.dat[i].nCount;

						if(pDrvState->GooseTest.dat[i].module == otmt_goose.m_nModuleIndex)
						{
							pDrvState->GooseTest.dat[i].gs[nGSTestdataCnt].group = otmt_goose.group;
							pDrvState->GooseTest.dat[i].gs[nGSTestdataCnt].value = nCurTestMode;
							pDrvState->GooseTest.dat[i].gs[nGSTestdataCnt].pos = otmt_goose.nTestModePos;
							pDrvState->GooseTest.dat[i].nCount++;
						}
					}
				}
			}
		}

		tmt_GoosePub *pPreGoosePub;

		if(nIndex == 0)
		{
			//实验开始也需要比较,防止开始实验虚变位
			//bIsCompare=FALSE;
			//pPreGoosePub=NULL;
			bIsCompare = TRUE;
			pPreGoosePub = &m_oPreGoosePub[index];
		}
		else
		{
			bIsCompare = TRUE;
			long nPreStateNum = pSttTestBase->GetStateNum(nIndex - 1);

			if(nPreStateNum < 0)
			{
				return;
			}

			pPreGoosePub = &pStateParas->m_paraState[nPreStateNum].m_oGoosePub[index];
		}

		bSetGooseValue = SetGooseValue_Com(&pStateParas->m_paraState[nStateNum].m_oGoosePub[index],
										   &otmt_goose, &pDrvState->oGseChgParas, pPreGoosePub, bIsCompare);

		if(bSetGooseValue)
		{
			bRet = TRUE;
		}

		for(int j = 0; j < MAX_GOOSE_CHANNEL_COUNT; j++)
		{
			m_pStateGoosePub[nIndex].m_oGoosePub[index].m_strChannel[j] =
				pStateParas->m_paraState[nStateNum].m_oGoosePub[index].m_strChannel[j];
		}
	}

	if(bRet)
	{
		pDrvState->nGseChgValid = 1;
	}
}

void CSttDeviceComm::SetGooseValue_ManuTest(tmt_GoosePub *pCurGoosePub, BOOL bIsStartTest)
{
	Drv_GseTest oGSTest;
	memset(&oGSTest, 0, sizeof(Drv_GseTest));
	DrvGseChgParas oGseChgParas;
	memcpy(&oGseChgParas, m_oCIEC61850CfgMngr.m_pGseChgParas, sizeof(DrvGseChgParas));
	oGSTest.nCount = oGseChgParas.nModulesCnt;

	for(int i = 0; i < oGseChgParas.nModulesCnt; i++)
	{
		oGSTest.dat[i].module = oGseChgParas.oModule[i].nModuleIndex;
	}

	BOOL bTestValid;
	BOOL bRet = FALSE;
	BOOL bSetGooseValue;
	int nGSTestdataCnt;
	int nGseOutCnt = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.count();

	for(int index = 0; index < nGseOutCnt && index < MAX_MODULES_GOOSEPUB_COUNT; index++)
	{
		tmt_goose otmt_goose = m_oCIEC61850CfgMngr.m_oGooseMngr.data_gseout.at(index);

		if(!pCurGoosePub[index].m_bUseFlag)
		{
			continue;    //无需变位
		}

		bTestValid = pCurGoosePub[index].m_bHasTest;

		if(bTestValid)
		{
			for(int i = 0; i < oGSTest.nCount; i++)
			{
				nGSTestdataCnt = oGSTest.dat[i].nCount;

				if(oGSTest.dat[i].module == otmt_goose.m_nModuleIndex)
				{
					oGSTest.dat[i].gs[nGSTestdataCnt].group = otmt_goose.group;
					oGSTest.dat[i].gs[nGSTestdataCnt].value = pCurGoosePub[index].m_nTest;
					oGSTest.dat[i].gs[nGSTestdataCnt].pos = otmt_goose.nTestModePos;
					oGSTest.dat[i].nCount++;
				}
			}
		}

		//实验开始也需要比较,防止开始实验虚变位
		//if(bIsStartTest)
		//{
		//bSetGooseValue=SetGooseValue_Com(&pCurGoosePub[index],&otmt_goose,&oGseChgParas);
		//if(bSetGooseValue)
		//	bRet=TRUE;
		//}
		//else
		{
			bSetGooseValue = SetGooseValue_Com(&pCurGoosePub[index], &otmt_goose,
											   &oGseChgParas, &m_oPreGoosePub[index], TRUE);

			if(bSetGooseValue)
			{
				bRet = TRUE;
			}
		}

		for(int i = 0; i < MAX_GOOSE_CHANNEL_COUNT; i++)
		{
			m_oPreGoosePub[index].m_strChannel[i] = pCurGoosePub[index].m_strChannel[i];
		}
	}

	g_oDrvMutex.lock();
	ioctl(m_nfd, 0x30D, 1);
	write(m_nfd, &oGSTest, sizeof(Drv_GseTest));
	g_oDrvMutex.unlock();

	if(bRet)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x30B, 1);
		write(m_nfd, &oGseChgParas, sizeof(DrvGseChgParas));
		g_oDrvMutex.unlock();
	}
}

BOOL CSttDeviceComm::SetFt3Value_Com(tmt_Ft3Pub *pCurFt3Pub, tmt_ft3_6044 *ptmt_ft3_6044,
									 DrvFT3ChgParas *pFt3ChgParas, tmt_Ft3Pub *pPreFt3Pub, BOOL bIsCompare)
{
	BOOL bRet = FALSE;
	QString strPreChanVal, strCurChanVal;
	BOOL bIsChanChgValid = FALSE;

	for(int chanid = 0; chanid < ptmt_ft3_6044->m_oChanList.size(); chanid++)
	{
		if(chanid >= MAX_FT3_CHANNEL_COUNT)
		{
			return FALSE;
		}

		FT3ChanInfo &oChanelInfo = ptmt_ft3_6044->m_oChanList[chanid];
		strCurChanVal = pCurFt3Pub->m_strChannel[chanid];

		if(strCurChanVal.length() == 0)
		{
			continue;    //通道值数据无效
		}

		oChanelInfo.nFirstValue = strCurChanVal.toInt();

		if(bIsCompare)
		{
			strPreChanVal = pPreFt3Pub->m_strChannel[chanid];

			if(strPreChanVal.length() == 0)
			{
				continue;    //通道值数据无效
			}

			if(strPreChanVal.compare(strCurChanVal) != 0)
			{
				bIsChanChgValid = TRUE;
			}
		}
		else
		{
			bIsChanChgValid = TRUE;
		}
	}

	if(!bIsChanChgValid)
	{
		return FALSE;
	}

	int nBoard = -1;
	for(int i = 0; i < m_oCIEC61850CfgMngr.m_pIECConfigFt3->mdCnt; i++)
	{
		DatConfigItemsFt3 &pItemFt3 = m_oCIEC61850CfgMngr.m_pIECConfigFt3->item[i];
		if(pItemFt3.moduletype == STT_MODULE_TYPE_DIGITAL_0G8M
				|| pItemFt3.moduletype == STT_MODULE_TYPE_DIGITAL_2G6M
				|| pItemFt3.moduletype == STT_MODULE_TYPE_DIGITAL_4G4M)
		{
			if(m_oCIEC61850CfgMngr.m_nUseSmv92 == SMVTYPE_92)
			{
				continue;
			}
		}

		if(ptmt_ft3_6044->port >= pItemFt3.nSTSendBeginIdx
				&& ptmt_ft3_6044->port <= pItemFt3.nSTSendEndIdx)
		{
			nBoard = i;
			break;
		}
	}	

	if(nBoard >= 0)
	{
		QByteArray ovalue;
		m_oCIEC61850CfgMngr.m_p6044MngrBase->Create6044ComByteArray(*ptmt_ft3_6044, ovalue);

		if(ovalue.size() <= 200)
		{
			int nItemCnt = pFt3ChgParas->oModule[nBoard].nItemsCnt;
			pFt3ChgParas->oModule[nBoard].oItem[nItemCnt].nDatCnt = ovalue.size();
			pFt3ChgParas->oModule[nBoard].oItem[nItemCnt].nGroupWithBit =
				1 << (ptmt_ft3_6044->port - m_oCIEC61850CfgMngr.m_pIECConfigFt3->item[nBoard].nSTSendBeginIdx);
			memcpy(pFt3ChgParas->oModule[nBoard].oItem[nItemCnt].szdat, ovalue.constData(), ovalue.size());
			pFt3ChgParas->oModule[nBoard].nItemsCnt++;
			bRet = TRUE;
		}
	}

	return bRet;
}

void CSttDeviceComm::SetFt3Value_StateTest(tmt_StateParas *pStateParas, int nIndex, Drv_StateItem *pDrvState)
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();
	long nStateNum = pSttTestBase->GetStateNum(nIndex);

	if(nStateNum < 0)
	{
		return;
	}

	pDrvState->oFt3ChgParas.nModulesCnt = m_oCIEC61850CfgMngr.m_pIECConfigFt3->mdCnt;

	for(int i = 0; i < pDrvState->oFt3ChgParas.nModulesCnt; i++)
	{
		pDrvState->oFt3ChgParas.oModule[i].nModuleIndex = m_oCIEC61850CfgMngr.m_pIECConfigFt3->item[i].module;
		pDrvState->oFt3ChgParas.oModule[i].nItemsCnt = 0;
	}

	BOOL bRet = FALSE;
	BOOL bSetFt3Value;
	BOOL bIsCompare = TRUE;
	int nFt3OutCnt =  m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044.count();
	tmt_ft3_6044 *p_ft3_6044;

	for(int index = 0; index < nFt3OutCnt && index < MAX_MODULES_FT3PUB_COUNT; index++)
	{
		p_ft3_6044 = &(m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044[index]);

		if(!pStateParas->m_paraState[nStateNum].m_oFt3Pub[index].m_bUseFlag)
		{
			continue;    //无需变位
		}

		tmt_Ft3Pub *pPreFt3Pub;

		if(nIndex == 0)
		{
			bIsCompare = FALSE;
			pPreFt3Pub = NULL;
		}
		else
		{
			bIsCompare = TRUE;
			long nPreStateNum = pSttTestBase->GetStateNum(nIndex - 1);

			if(nPreStateNum < 0)
			{
				return;
			}

			pPreFt3Pub = &pStateParas->m_paraState[nPreStateNum].m_oFt3Pub[index];
		}

		bSetFt3Value = SetFt3Value_Com(&pStateParas->m_paraState[nStateNum].m_oFt3Pub[index],
									   p_ft3_6044, &pDrvState->oFt3ChgParas, pPreFt3Pub, bIsCompare);

		if(bSetFt3Value)
		{
			bRet = TRUE;
		}

		for(int j = 0; j < MAX_FT3_CHANNEL_COUNT; j++)
		{
			m_pStateFt3Pub[nIndex].m_oFt3Pub[index].m_strChannel[j] =
				pStateParas->m_paraState[nStateNum].m_oFt3Pub[index].m_strChannel[j];
		}
	}

	if(bRet)
	{
		pDrvState->nFt3ChgValid = 1;
	}
}

void CSttDeviceComm::SetFt3Value_ManuTest(tmt_Ft3Pub *pCurFt3Pub, BOOL bIsStartTest)
{
	DrvFT3ChgParas oFT3ChgParas;
	oFT3ChgParas.nModulesCnt = m_oCIEC61850CfgMngr.m_pIECConfigFt3->mdCnt;

	for(int i = 0; i < oFT3ChgParas.nModulesCnt; i++)
	{
		oFT3ChgParas.oModule[i].nModuleIndex = m_oCIEC61850CfgMngr.m_pIECConfigFt3->item[i].module;
		oFT3ChgParas.oModule[i].nItemsCnt = 0;
	}

	BOOL bRet = FALSE;
	BOOL bSetFT3Value;
	int nFT3OutCnt = m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044.count();

	for(int index = 0; index < nFT3OutCnt; index++)
	{
		if(!pCurFt3Pub[index].m_bUseFlag)
		{
			continue;    //无需变位
		}

		tmt_ft3_6044 *p_tmt_6044 = &(m_oCIEC61850CfgMngr.m_p6044MngrBase->data_6044[index]);

		if(bIsStartTest)
		{
			bSetFT3Value = SetFt3Value_Com(&pCurFt3Pub[index], p_tmt_6044,
										   &oFT3ChgParas, NULL, FALSE);
		}
		else
		{
			bSetFT3Value = SetFt3Value_Com(&pCurFt3Pub[index], p_tmt_6044,
										   &oFT3ChgParas, &m_oPreFt3Pub[index], TRUE);
		}

		if(bSetFT3Value)
		{
			bRet = TRUE;
		}

		for(int i = 0; i < MAX_MODULES_FT3PUB_COUNT; i++)
		{
			m_oPreFt3Pub[index].m_strChannel[i] = pCurFt3Pub[index].m_strChannel[i];
		}
	}

	if(bRet)
	{
		g_oDrvMutex.lock();
		ioctl(m_nfd, 0x30A, 1);
		write(m_nfd, &oFT3ChgParas, sizeof(DrvFT3ChgParas));
		g_oDrvMutex.unlock();
	}
}

void CSttDeviceComm::UpdateStable2MValue_ManuTest(tmt_Stable2MList &oStable2MList, tmt_2MOnePortPub oOnePortPub)
{
	tmt_Stable2MPub *pStable2MPub;

	for(int j = 0; j < MAX_2M_CMDIDX_COUNT; j++)
	{
		pStable2MPub = &oOnePortPub.m_oStable2M_CmdPub[j];
		oStable2MList.m_oCmdPkg[j].m_nUseFlag = 0;

		if(pStable2MPub->m_bBlockUseFlag)
		{
			for(int i = 0; i < MAX_2M_CHANNEL_COUNT; i++)
			{
				if(pStable2MPub->m_bChanUseFlag[i])
				{
					if(oStable2MList.m_oCmdPkg[j].m_nIdxMapChan == 0 || (oStable2MList.m_oCmdPkg[j].m_nIdxMapChan - 1) != i)
					{
						oStable2MList.m_oCmdPkg[j].m_oChanList[i].nFirstValue =
							pStable2MPub->m_nChanValue[i];
						oStable2MList.m_oCmdPkg[j].m_nUseFlag = 1;
					}
				}
			}
		}
	}

	long nIdxVal;

	for(int j = 0; j < oStable2MList.m_nDataPkgCount; j++)
	{
		nIdxVal = oStable2MList.m_oDataPkg[j].nIdxVal;
		pStable2MPub = &oOnePortPub.m_oStable2M_DataPub[nIdxVal];

		if(pStable2MPub->m_bBlockUseFlag)
		{
			for(int i = 0; i < MAX_2M_CHANNEL_COUNT; i++)
			{
				if(pStable2MPub->m_bChanUseFlag[i])
				{
					if(oStable2MList.m_oDataPkg[j].m_nIdxMapChan == 0 || (oStable2MList.m_oDataPkg[j].m_nIdxMapChan - 1) != i)
					{
						oStable2MList.m_oDataPkg[j].m_oChanList[i].nFirstValue =
							pStable2MPub->m_nChanValue[i];
					}
				}
			}
		}
	}
}

void CSttDeviceComm::SetStable2MValue_ManuTest(tmt_2MOnePortPub *p2MOnePortPub, BOOL bIsStartTest)
{
	memset(&m_o2MChgParas, 0, sizeof(Drv_IECConfig_2M));
	m_o2MChgParas.moduleCount = m_oCIEC61850CfgMngr.m_pIECConfig_2M->moduleCount;

	for(int i = 0; i < MAX_2M_MODULE_COUNT; i++)
	{
		m_o2MChgParas.item[i].module = m_oCIEC61850CfgMngr.m_pIECConfig_2M->item[i].module;
	}

	BOOL bRet = FALSE;

	for(int i = 0; i < MAX_2M_BLOCKS_COUNT; i++)
	{
		for(int j = 0; j < MAX_2M_CMDIDX_COUNT; j++)
		{
			if(p2MOnePortPub[i].m_oStable2M_CmdPub[j].m_bBlockUseFlag)
			{
				bRet = TRUE;
				break;
			}
		}

		for(int j = 0; j < MAX_2M_DATAIDX_VALUE; j++)
		{
			if(p2MOnePortPub[i].m_oStable2M_DataPub[j].m_bBlockUseFlag)
			{
				bRet = TRUE;
				break;
			}
		}

		if(bRet)
		{
			break;
		}
	}

	if(bRet)
	{
		QByteArray obytearray;

		for(int nBoard = 0; nBoard < m_oCIEC61850CfgMngr.m_pIECConfig_2M->moduleCount; nBoard++)
		{
			for(int index = 0; index < MAX_2M_BLOCK_COUNT; index++)
			{
				obytearray.clear();
				UpdateStable2MValue_ManuTest(m_oPreStable2MList[nBoard][index], p2MOnePortPub[nBoard * MAX_2M_BLOCK_COUNT + index]);
				m_oCIEC61850CfgMngr.m_oStable2MMngr.Create2MListByteArray(m_oPreStable2MList[nBoard][index], index, obytearray);
				memcpy(m_o2MChgParas.item[nBoard].dats[index].dat, obytearray.constData(), obytearray.size());
				m_o2MChgParas.item[nBoard].dats[index].count = obytearray.size();
			}
		}

		SetTestPara(IECDataCfg_Stable2M, (char *)&m_o2MChgParas);
	}
}

//合闸角对电压有效，非周期对电流有效
//合闸角
void CSttDeviceComm::CloseAngle(Drv_StateItem *pDrv_StateItem, float fAngle, float fCurAngle, int nChanel)
{
	int nModuleOffset = 0;
	int nDrvPos = 0;

	if(g_theSystemConfig->m_nHasAnalog != 0)
	{
		while((fAngle >= 360) || (fAngle < 0))
		{
			if(fAngle >= 360)
			{
				fAngle -= 360;
			}
			else
			{
				fAngle += 360;
			}
		}

		fCurAngle += 180;

		while((fCurAngle >= 360) || (fCurAngle < 0))
		{
			if(fCurAngle >= 360)
			{
				fCurAngle -= 360;
			}
			else
			{
				fCurAngle += 360;
			}
		}

		long nAngle = fAngle * 65536 / 360;
		long nCurAngle = fCurAngle * 65536 / 360;
		long nAngle_U, nAngle_I;

		//Volt
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_U; nIndex++)
		{
			nAngle_U = nAngle;
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_U[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			if(nChanel > 5)
			{
				break;
			}

			nDrvPos = pModule->m_nChDrvPos[nChanel];
			nAngle_U |= 1 << nDrvPos << 16;
			pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nPhase = nAngle_U;
		}

		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;

		//Current
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
		{
			nAngle_I = nCurAngle;
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			if(nChanel > 5)
			{
				break;
			}

			nDrvPos = pModule->m_nChDrvPos[nChanel];
			nAngle_I |= 1 << nDrvPos << 16;
			//电流不需要设置合闸角，但是为了与电压模块保持时序同步，所以增加合闸效果。
			pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nPhase = nAngle_I;
		}

		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;

		//UI
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
		{
			nAngle_U = nAngle;
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
					|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
			{
				if(nChanel > 2)
				{
					break;
				}

				nDrvPos = pModule->m_nChDrvPos[nChanel];
				nAngle_U |= 1 << nDrvPos << 16;
				pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nPhase = nAngle_U;
			}
		}
	}

	if(g_theSystemConfig->m_nHasDigital != 0)
	{
		if(fAngle < 1)
		{
			fAngle += 359;    //zhangsen 20181224
		}

		fAngle = fAngle - 1; //角度-1 原因是FPGA修改复杂，上面发送数据做的修正 模拟量不修改

		while((fAngle >= 360) || (fAngle < 0))
		{
			if(fAngle >= 360)
			{
				fAngle -= 360;
			}
			else
			{
				fAngle += 360;
			}
		}

		long nAngle = fAngle * 65536 / 360;

		if(nChanel > 5)
		{
			return;
		}

		nAngle |= 1 << (16 + nChanel + 6);
		nModuleOffset = g_theDeviceSystemParameter->m_nModuleCount_U;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;
		nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;

		//Digital
		for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
		{
			PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];

			if(pModule == NULL)
			{
				continue;
			}

			pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nPhase = nAngle;
		}
	}
}

//-Imax*sin(fCurCloseAngle-fZAngle)
//非周期分量
void CSttDeviceComm::Acyclic_Analog(Drv_StateItem *pDrv_StateItem, tmt_StatePara  oTmt_paraState, int nT)
{
	unsigned int nconfig = 0xff;

	if(nT <= 10)
	{
		nconfig |= 0x010000;
	}
	else if(nT > 10 && nT <= 30)
	{
		nconfig |= 0x020000;
	}
	else if(nT > 30 && nT <= 50)
	{
		nconfig |= 0x040000;
	}
	else if(nT > 50 && nT <= 80)
	{
		nconfig |= 0x080000;
	}
	else
	{
		nconfig |= 0x100000;
	}

	float fCurCloseAngle = oTmt_paraState.m_oCloseAngle.m_fCurCloseAngle;
	int nChanel = oTmt_paraState.m_oCloseAngle.m_nCloseChannel;
	float fValue;
	float fIAngle, fVAngle;
	float fCloseAngle;
	float fout;
	float fZAngle;//阻抗角
	int nDrvPos;
	int nModuleOffset = g_theDeviceSystemParameter->m_nModuleCount_U;

	//Current
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_I; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_I[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

		for(int i = 0; i < m_nTmtChanNum; i++)
		{
			nDrvPos = pModule->m_nChDrvPos[i];
			m_nTmtPos = pModule->m_nChTmtPos[i];

			if(m_nTmtPos < 0)
			{
				continue;
			}

			fValue = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[1].fAmp;
			fVAngle = oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[1].fAngle;
			fIAngle = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[1].fAngle;
			fZAngle = fVAngle - fIAngle;

			if(nChanel == m_nTmtPos)
			{
				fCloseAngle = fCurCloseAngle;
			}
			else
			{
				fCloseAngle = 0;
			}

			float fAngle = (fCloseAngle - fZAngle) * 3.141593 / 180;
			fout = -sin(fAngle) * 1.414214 * fValue;
			long *pData = &pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nexp[nDrvPos];
			TransAnalogDCCurToDrv(fout * 0.5, i, nIndex, pData, FALSE); //有符号数是满量程的一半
		}

		pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nexpconfig = nconfig;
	}

	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_I;

	//UI
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_UI; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_UI[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		nconfig &= 0xffffff00;

		if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS331
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_H
				|| pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_UI_PNS330_ABC_20)
		{
			m_nTmtChanNum = pModule->m_oModuleAttr.m_nChannelNum;

			for(int i = 0; i < m_nTmtChanNum; i++)
			{
				nDrvPos = pModule->m_nChDrvPos[i];
				m_nTmtPos = pModule->m_nChTmtPos[i];

				if(m_nTmtPos < 0)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nEeType == STT_CH_EETYPE_CURRENT)
				{
					fValue = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[1].fAmp;
					fVAngle = oTmt_paraState.m_uiVOL[m_nTmtPos].Harm[1].fAngle;
					fIAngle = oTmt_paraState.m_uiCUR[m_nTmtPos].Harm[1].fAngle;
					fZAngle = fVAngle - fIAngle;

					if(nChanel == m_nTmtPos)
					{
						fCloseAngle = fCurCloseAngle;
					}
					else
					{
						fCloseAngle = 0;
					}

					float fAngle = (fCloseAngle - fZAngle) * 3.141593 / 180;
					fout = -sin(fAngle) * 1.414214 * fValue;
					long *pData = &pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nexp[nDrvPos];
					TransAnalogDCUIToDrv_Current(fout * 0.5, i, nIndex, pData, FALSE);
					nconfig |= 1 << nDrvPos;
				}
			}

			pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nexpconfig = nconfig;
		}
	}
}

void CSttDeviceComm::Acyclic_Digital(Drv_StateItem *pDrv_StateItem, tmt_StatePara  oTmt_paraState, int nT)
{
	unsigned int nconfig = 0xfff;//使能顺序不是通道映射的顺序,保险做法全部使能

	if(nT <= 10)
	{
		nconfig |= 0x10000;
	}
	else if(nT > 10 && nT <= 30)
	{
		nconfig |= 0x20000;
	}
	else if(nT > 30 && nT <= 50)
	{
		nconfig |= 0x40000;
	}
	else if(nT > 50 && nT <= 80)
	{
		nconfig |= 0x80000;
	}
	else
	{
		nconfig |= 0x100000;
	}

	float fCurCloseAngle = oTmt_paraState.m_oCloseAngle.m_fCurCloseAngle;
	int nChanel = oTmt_paraState.m_oCloseAngle.m_nCloseChannel;
	float fValue;
	float fIAngle, fVAngle;
	float fCloseAngle;
	float fout;
	float fZAngle;//阻抗角
	long nValue;
	int nModuleOffset = g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_U;
	nModuleOffset += g_theDeviceSystemParameter->m_nModuleCount_UI;

	//Digital
	for(int nIndex = 0; nIndex < g_theDeviceSystemParameter->m_nModuleCount_D; nIndex++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[nIndex];

		if(pModule == NULL)
		{
			continue;
		}

		for(int i = 0; i < 6; i++)
		{
			fValue = oTmt_paraState.m_uiCUR[i].Harm[1].fAmp;
			fVAngle = oTmt_paraState.m_uiVOL[i].Harm[1].fAngle;
			fIAngle = oTmt_paraState.m_uiCUR[i].Harm[1].fAngle;
			fZAngle = fVAngle - fIAngle;

			if(i == nChanel)
			{
				fCloseAngle = fCurCloseAngle;
			}
			else
			{
				fCloseAngle = 0;
			}

			float fAngle = (fCloseAngle - fZAngle) * 3.141593 / 180;
			fout = -sin(fAngle) * 1.414214 * fValue;
			nValue = fout * g_theSystemConfig->PkgModeCTRate(i / 3) / g_theSystemConfig->m_fIRate;
			pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nexp[i + 6] = nValue;
		}

		pDrv_StateItem->oAcParam.item[nModuleOffset + nIndex].nexpconfig = nconfig;
	}
}

void CSttDeviceComm::GetRtData()
{
	if(m_pDegressMsg == NULL)
	{
		return;
	}

	if(!m_bRdDegRtData)
	{
		return;
	}

	int nWriteCount = m_pDegressMsg->nWriteCount;
	int nReadCount = m_pDegressMsg->nReadCount;

	if(nReadCount < 0 || nReadCount > STT_DRV_RTDATA_MSG_MAX_COUNT
			|| nWriteCount <= 0 || nWriteCount > STT_DRV_RTDATA_MSG_MAX_COUNT)
	{
		return;
	}

	if(nReadCount == nWriteCount)
	{
		return;
	}

	m_oRtDataList.clear();

	if(nReadCount < nWriteCount)
	{
		for(int i = nReadCount; i < nWriteCount; i++)
		{
			Drv_DegressData oData;
			memcpy(&oData, m_pDegressMsg->oData + i, sizeof(Drv_DegressData));
			m_oRtDataList.append(oData);
		}
	}
	else
	{
		for(int i = nReadCount; i < STT_DRV_RTDATA_MSG_MAX_COUNT; i++)
		{
			Drv_DegressData oData;
			memcpy(&oData, m_pDegressMsg->oData + i, sizeof(Drv_DegressData));
			m_oRtDataList.append(oData);
		}

		for(int i = 0; i < nWriteCount; i++)
		{
			Drv_DegressData oData;
			memcpy(&oData, m_pDegressMsg->oData + i, sizeof(Drv_DegressData));
			m_oRtDataList.append(oData);
		}
	}

	ProVoltCurRtData();
	m_pDegressMsg->nReadCount = nWriteCount;
}

void CSttDeviceComm::ProVoltCurRtData()
{
	CSttTestBase *pSttTestBase = CSttServerTestCtrlCntr::GetCurrTest();

	if(pSttTestBase == NULL)
	{
		return;
	}

	double dTime;
	long nRealTimeEventCount;

	for(int i = 0; i < m_oRtDataList.count(); i++)
	{
		Drv_DegressData oDegData = m_oRtDataList.at(i);
		dTime = oDegData.nUtcH + oDegData.nUtcL * 0.000000001;
		pSttTestBase->ProRtDatasEvent(dTime, dTime - pSttTestBase->m_dTestStartTime, oDegData.nCurStep, oDegData.nCurState, oDegData.nType);

		if(oDegData.nType == 2)
		{
			if(pSttTestBase->m_nCurStateIndex == -1)
			{
				ProCommBoutEvent(m_oGradientBo_Fault, nRealTimeEventCount, -1,
								 oDegData.nCurStep, dTime, dTime - pSttTestBase->m_dTestStartTime, FALSE);
				memcpy(&m_oPreBoStatus, &m_oGradientBo_Fault, sizeof(DrvComBoStatus));
			}
		}
		else
		{
			if(pSttTestBase->m_nCurStateIndex == -1)
			{
				ProCommBoutEvent(m_oGradientBo_BfFault, nRealTimeEventCount, -1,
								 oDegData.nCurStep, dTime, dTime - pSttTestBase->m_dTestStartTime, FALSE);
				memcpy(&m_oPreBoStatus, &m_oGradientBo_BfFault, sizeof(DrvComBoStatus));
			}
		}
	}

	pSttTestBase->ReturnRealTimeEvent();
}
