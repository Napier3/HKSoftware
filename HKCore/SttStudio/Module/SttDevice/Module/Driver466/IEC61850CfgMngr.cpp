#include "IEC61850CfgMngr.h"
#include "../../../SttTest/Common/tmt_adjust_sys_para_module_def.h"
#include "OSInterface.h"

CIEC61850CfgMngr::CIEC61850CfgMngr(QObject *parent) : QObject(parent)
{
	confsv = (SendConfSV *)malloc(sizeof(SendConfSV));
	fiber = (FiberConf *)malloc(sizeof(FiberConf));
	confgse = (SendConfGSE *)malloc(sizeof(SendConfGSE));
	confFt3 = (SendConfFT3 *)malloc(sizeof(SendConfFT3));
	m_pIECConfig = (Drv_IECConfig *)malloc(sizeof(Drv_IECConfig));	
	m_pIECConfig_2M = (Drv_IECConfig_2M *)malloc(sizeof(Drv_IECConfig_2M));
	ft3subs = (Ft3SubDatas *)malloc(sizeof(Ft3SubDatas));
	gsesub = (IecRecvCfg *)malloc(sizeof(IecRecvCfg));
	stMaps = (Drv_GSOutMap *)malloc(sizeof(Drv_GSOutMap));
	m_pGseChgParas = new DrvGseChgParas;
	memset(ft3subs, 0, sizeof(Ft3SubDatas));
	m_nUseSmv92 = SMVTYPE_92;
	m_p6044MngrBase = (CIEC6044MngrBase *)&m_o6044ComMngr;
	m_nSysParasFT3baud = 0;
}

CIEC61850CfgMngr::~CIEC61850CfgMngr()
{
	free(confsv);
	free(fiber);
	free(confgse);
	free(confFt3);
	free(m_pIECConfig);	
	free(m_pIECConfig_2M);
	free(ft3subs);
	free(gsesub);
	free(stMaps);
	delete m_pGseChgParas;
	m_pGseChgParas = NULL;
}

void CIEC61850CfgMngr::FiberClose()
{
	for(int i = 0; i < m_pIECConfig->mdCnt; i++)
	{
		memset(fiber, 0, sizeof(FiberConf));
		fiber->data0 = m_pIECConfig->item[i].module;
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(FiberCtrlCfg, (char *)fiber);
	}

	for(int i = 0; i < m_pIECConfigFt3->mdCnt; i++)
	{
		unsigned int nbaud = confFt3->baud;

		for(int j = 0; j < 12; j++)
		{
			nbaud &= ~(1 << (j + 3)); //关闭FT3发送使能
		}

		memset(confFt3, 0, sizeof(SendConfFT3));
		confFt3->module = m_pIECConfigFt3->item[i].module;
		confFt3->baud = nbaud;
		long nSample = m_p6044MngrBase->GetSample();
		unsigned short nT = 10000000 / nSample;
		confFt3->sampleCnt = nSample << 16 | nT;
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Ft3CtrlCfg, (char *)confFt3);
	}
}

void CIEC61850CfgMngr::FiberOpen()
{
	for(int i = 0; i < m_pIECConfig->mdCnt; i++)
	{
		memset(fiber, 0, sizeof(FiberConf));
		fiber->data0 = m_pIECConfig->item[i].module;

		if(m_nUseSmv92 == SMVTYPE_92)
		{
			for(int index = 0; index < m_pIECConfig->item[i].smvCount; index++)
			{
				int group = m_pIECConfig->item[i].sv[index].GroupIdxWithNum;
				int port = m_pIECConfig->item[i].sv[index].PortIdx;

				if(group < 4)
				{
					fiber->data4 |= (1 << port) << ((3 - group) * 8); //sv1-4
				}
				else
				{
					fiber->data5 |= (1 << port) << ((7 - group) * 8); //sv5-8
				}
			}
		}

		for(int index = 0; index < m_pIECConfig->item[i].gsCount; index++)
		{
			int group = m_pIECConfig->item[i].gs[index].GroupIdxWithNum;
			int port = m_pIECConfig->item[i].gs[index].PortIdx;

			switch(group)
			{
				case 0:
				case 1:
				case 2:
				case 3:
					fiber->data6 |= (1 << port) << ((3 - group) * 8);
					break;

				case 4:
				case 5:
				case 6:
				case 7:
					fiber->data7 |= (1 << port) << ((7 - group) * 8);
					break;

				case 8:
				case 9:
				case 10:
				case 11:
					fiber->data8 |= (1 << port) << ((11 - group) * 8);
					break;

				case 12:
				case 13:
				case 14:
				case 15:
					fiber->data9 |= (1 << port) << ((15 - group) * 8);
					break;
			}
		}

		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(FiberCtrlCfg, (char *)fiber);
	}
}

void CIEC61850CfgMngr::InitDigitalModulesInfo()
{
	memset(m_pIECConfig, 0, sizeof(Drv_IECConfig));
	m_pIECConfigFt3 = CSttDeviceBase::g_pSttDeviceBase->m_pIECConfigFt3;
	memset(m_pIECConfigFt3, 0, sizeof(Drv_IECConfigFt3));
	memset(m_pIECConfig_2M, 0, sizeof(Drv_IECConfig_2M));
	memset(m_pGseChgParas, 0, sizeof(DrvGseChgParas));
	m_pIECConfig->mdCnt = g_theDeviceSystemParameter->m_nModuleCount_D;
	m_pIECConfigFt3->mdCnt = m_pIECConfig->mdCnt;
	m_pIECConfigFt3->mdCnt += g_theDeviceSystemParameter->m_nModuleCount_FT3;
	m_pIECConfigFt3->mdCnt += g_theDeviceSystemParameter->m_nModuleCount_ADMU;

	if(m_pIECConfig->mdCnt > Digital_MODULE_MAX)
	{
		m_pIECConfig->mdCnt = Digital_MODULE_MAX;
	}
	if(m_pIECConfigFt3->mdCnt > ALG_MODULE_MAX)
	{
		m_pIECConfigFt3->mdCnt = ALG_MODULE_MAX;
	}

	m_pGseChgParas->nModulesCnt = m_pIECConfig->mdCnt;
	m_pIECConfig_2M->moduleCount = g_theDeviceSystemParameter->m_nModuleCount_Stable2M;
	m_pIECConfig_2M->moduleCount = m_pIECConfig_2M->moduleCount > 2 ? 2 : m_pIECConfig_2M->moduleCount;
	//多板卡数字光口排序，与IEC配置光口序号关联

	long nLCBeginIdx = 0;
	long nSTSendBeginIdx = 0;
	long nSTRecvBeginIdx = 0;
	int nModuleIndex = 0;
	int nModule;

	//FT3、数字板、ADMU统一按位置序号排序光口
	for(int k = 1; k < 16; k++)
	{
		for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount; i++)
		{
			PSTT_MODULE pModule = &g_theDeviceSystemParameter->m_oModules[i];

			if(pModule == NULL)
			{
				continue;
			}
			nModule = pModule->m_oModuleAttr.m_nModuleIndex;

			if(nModule != k)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M
					|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M
					|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M
					|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_FT3
					|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
			{
				m_pIECConfigFt3->item[nModuleIndex].moduletype = pModule->m_oModuleAttr.m_nModuleType;
				m_pIECConfigFt3->item[nModuleIndex].module = ModuleIndexTransToDrv(nModule);
				m_pIECConfigFt3->item[nModuleIndex].nSTSendBeginIdx = nSTSendBeginIdx;
				m_pIECConfigFt3->item[nModuleIndex].nSTSendEndIdx = nSTSendBeginIdx
													  + pModule->m_oModuleAttr.m_nFiberPortNum_STSend - 1;
				nSTSendBeginIdx += pModule->m_oModuleAttr.m_nFiberPortNum_STSend;
				m_pIECConfigFt3->item[nModuleIndex].nSTRecvBeginIdx = nSTRecvBeginIdx;
				m_pIECConfigFt3->item[nModuleIndex].nSTRecvEndIdx = nSTRecvBeginIdx
													  + pModule->m_oModuleAttr.m_nFiberPortNum_STRecv - 1;
				nSTRecvBeginIdx += pModule->m_oModuleAttr.m_nFiberPortNum_STRecv;
				nModuleIndex++;
			}
		}
	}

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

		if(pModule == NULL)
		{
			continue;
		}

		nModule = pModule->m_oModuleAttr.m_nModuleIndex;
		m_pIECConfig->item[i].module = ModuleIndexTransToDrv(nModule);
		m_pGseChgParas->oModule[i].nModuleIndex = m_pIECConfig->item[i].module;
		m_pIECConfig->item[i].nLCBeginIdx = nLCBeginIdx;
		m_pIECConfig->item[i].nLCEndIdx = nLCBeginIdx
				+ pModule->m_oModuleAttr.m_nFiberPortNum_LC - 1;
		nLCBeginIdx += pModule->m_oModuleAttr.m_nFiberPortNum_LC;		
	}

	for(int i = 0; i < m_pIECConfig_2M->moduleCount; i++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_Stable2M[i];

		if(pModule == NULL)
		{
			continue;
		}

		nModule = pModule->m_oModuleAttr.m_nModuleIndex;
		m_pIECConfig_2M->item[i].module = ModuleIndexTransToDrv(nModule);
	}
}

void CIEC61850CfgMngr::InitIECConfig()
{
	m_pIECConfig->item[0].gsSubCount = 0;

	for(int j = 0; j < GOOSE_MAX; j++)
	{
		memset(&m_pIECConfig->item[0].gsSub[j], 0, sizeof(DatConfig));
	}

	for(int i = 0; i < m_pIECConfig->mdCnt; i++)
	{
		m_pIECConfig->item[i].gsCount = 0;

		for(int j = 0; j < GOOSE_MAX; j++)
		{
			memset(&m_pIECConfig->item[i].gs[j], 0, sizeof(DatConfig));
		}

		m_pIECConfig->item[i].smvCount = 0;

		for(int j = 0; j < SMV_MAX; j++)
		{
			memset(&m_pIECConfig->item[i].sv[j], 0, sizeof(DatConfig));
		}
	}

	for(int i = 0; i < m_pIECConfigFt3->mdCnt; i++)
	{
		m_pIECConfigFt3->item[i].ft3Count = 0;

		for(int j = 0; j < FT3_MAX; j++)
		{
			memset(&m_pIECConfigFt3->item[i].ft3[j], 0, sizeof(DatConfig));
		}
	}

	for(int i = 0; i < m_pGseChgParas->nModulesCnt; i++)
	{
		m_pGseChgParas->oModule[i].nItemsCnt = 0;

		for(int j = 0; j < GOOSE_MAX; j++)
		{
			memset(&m_pGseChgParas->oModule[i].oItem[j], 0, sizeof(DrvGseChgItem));
		}
	}

	for(int i = 0; i < m_pIECConfig_2M->moduleCount; i++)
	{
		for(int j = 0; j < MAX_2M_BLOCK_COUNT; j++)
		{
			m_pIECConfig_2M->item[i].dats[j].count = 0;
		}
	}
}

void CIEC61850CfgMngr::InitIEC61850Para()
{
	m_nUseSmv92 = SMVTYPE_92;

	if(g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8DC)
	{
		m_nUseSmv92 = SMVTYPE_6044_COMMON;//柔直
		m_p6044MngrBase = (CIEC6044MngrBase *)&m_o6044ComMngr;
	}
	else if(g_theSystemConfig->m_nIecFormat == STT_IEC_FORMAT_60044_8)
	{
		m_nUseSmv92 = SMVTYPE_6044;//普通FT3
		m_p6044MngrBase = (CIEC6044MngrBase *)&m_o6044Mngr;
	}

	FiberClose();
	InitIECConfig();
	m_o92Mngr.Init();
	m_p6044MngrBase->Init();
	m_oGooseMngr.Init();
	m_oStable2MMngr.Init();
	FT3DbgChansInfo *pFT3DbgChansInfo =
		&CSttDeviceBase::g_pSttDeviceBase->m_oFT3DbgChansInfo;
	for(int index = 0; index < 16; index++)
	{
		pFT3DbgChansInfo->oFT3ChanInfo[index].nCount = 0;
	}

	int nSmvCnt = m_oIecCfgDatasMngr.GetSmvMngr()->GetCount();

	if(m_oIecCfgDatasMngr.GetSmvMngr()->m_nDatasUse == 0)
	{
		nSmvCnt = 0;
	}

	CIecCfgDataBase *pIecCfgDataBase;

	for(int index = 0; index < nSmvCnt; index++)
	{
		pIecCfgDataBase = (CIecCfgDataBase *)m_oIecCfgDatasMngr.GetSmvMngr()->GetAt(index);

		if(pIecCfgDataBase == NULL)
		{
			continue;
		}

		if(pIecCfgDataBase->GetXmlElementKey() == CCfgDataMngrXmlRWKeys::CIecCfgData92Key())
		{
			m_o92Mngr.Create92TmtStruct((CIecCfg92Data *)pIecCfgDataBase);
		}
		else if(pIecCfgDataBase->GetXmlElementKey() == CCfgDataMngrXmlRWKeys::CIecCfgData6044CommonKey())
		{
			//统一使用cfg-6044-common group
			m_p6044MngrBase->Create6044ComTmtStruct((CIecCfg6044CommonData *)pIecCfgDataBase);
		}
		else if(pIecCfgDataBase->GetXmlElementKey() == CCfgDataMngrXmlRWKeys::CIecCfgData2MKey())
		{
			m_oStable2MMngr.Create2MTmtStruct((CIecCfg2MData *)pIecCfgDataBase);
		}
		else if(pIecCfgDataBase->GetXmlElementKey() == CCfgDataMngrXmlRWKeys::CIecCfgSmvRatesKey())
		{
			m_p6044MngrBase->InitFT3Rates((CIecCfgSmvRates *)pIecCfgDataBase);
		}
	}

	m_oStable2MMngr.AfterCreate2MTmt();//排序
	int nGseCnt = m_oIecCfgDatasMngr.GetGOUTCount();

	if(m_oIecCfgDatasMngr.GetGoutMngr()->m_nDatasUse == 0)
	{
		nGseCnt = 0;
	}

	for(int index = 0; index < nGseCnt; index++)
	{
		CIecCfgGooseDataBase *pGoose = (CIecCfgGooseDataBase *)m_oIecCfgDatasMngr.GetGoutCfgData(index);
		m_oGooseMngr.CreateGooseTmtStruct(pGoose);
	}

	CIecCfgDatasSmvIn *pSmvInMngr = m_oIecCfgDatasMngr.GetSmvInMngr();

	if(pSmvInMngr != NULL)
	{
		int nSmvInCnt = pSmvInMngr->GetCount();

		if(pSmvInMngr->m_nDatasUse == 0)
		{
			nSmvInCnt = 0;
		}

		for(int index = 0; index < nSmvInCnt; index++)
		{
			pIecCfgDataBase = (CIecCfgDataBase *)pSmvInMngr->GetAt(index);

			if(pIecCfgDataBase == NULL)
			{
				continue;
			}

			if(pIecCfgDataBase->GetXmlElementKey() == CCfgDataMngrXmlRWKeys::CIecCfgData2MInKey())
			{
				m_oStable2MMngr.Create2MSubTmtStruct((CIecCfg2MInData *)pIecCfgDataBase);
			}
			else if(pIecCfgDataBase->GetXmlElementKey() == CCfgDataMngrXmlRWKeys::CIecCfgData92InKey())
			{
				m_o92Mngr.Create92SubTmtStruct((CIecCfg92InData *)pIecCfgDataBase);
			}
			else if(pIecCfgDataBase->GetXmlElementKey() == CCfgDataMngrXmlRWKeys::CIecCfgData6044CommonInKey())
			{
				m_p6044MngrBase->Create6044ComSubTmtStruct((CIecCfg6044CommonInData *)pIecCfgDataBase);
			}
		}

		if(m_p6044MngrBase->data_6044Sub.size() > 0)
		{
			long n6044Count = m_p6044MngrBase->data_6044Sub.size();
			const tmt_ft3_6044 *p_ft3_6044;
			FT3DbgChanInfo *pChanInfo;

			for(int i = 0; i < n6044Count; i++)
			{
				p_ft3_6044 = &(m_p6044MngrBase->data_6044Sub.at(i));
				long nPort = p_ft3_6044->port;
				if(nPort < 16)
				{
					pChanInfo = &(CSttDeviceBase::g_pSttDeviceBase->m_oFT3DbgChansInfo.oFT3ChanInfo[nPort]);
					pChanInfo->nCount = p_ft3_6044->m_nChanNum;
					long nTotal = 0;

					for(int j = 0; j < p_ft3_6044->m_nChanNum; j++)
					{
						pChanInfo->nChanLen1[j] = p_ft3_6044->m_oChanList.at(j).nChanLen1;
						pChanInfo->nChanLen2[j] = p_ft3_6044->m_oChanList.at(j).nChanLen2;
						pChanInfo->bContainCRC[j] = FALSE;
						nTotal += pChanInfo->nChanLen1[j];

						if(pChanInfo->nChanLen2[j] > 0)
						{
							nTotal = pChanInfo->nChanLen2[j];
						}

						if(nTotal == 16)
						{
							if(j < (p_ft3_6044->m_nChanNum - 1))
							{
								pChanInfo->bContainCRC[j] = TRUE;
							}
						}
					}
				}
			}
		}
	}

	CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("解析出 %d个SMV，%d个GOOSE，%d个FT3"),
							   m_o92Mngr.data_92.size(), m_oGooseMngr.data_gseout.size(),
							   m_p6044MngrBase->data_6044.size());
	AfterInitIEC61850();
}

void CIEC61850CfgMngr::GetSysParas()
{
	CIecCfgSysParas *pSysParasMngr = m_oIecCfgDatasMngr.GetSysParasMngr();

	if(pSysParasMngr != NULL)
	{
		CIecCfgFiberParas *pFiberParas = pSysParasMngr->GetFiberParas();

		if(pFiberParas != NULL)
		{
			CString strID;
			CIecCfgFiberPara *pFiberPara;

			for(int nIndex = 0; nIndex < MAX_FT3_FiberPort_NUM; nIndex++)
			{
				strID.Format(_T("ST%d"), nIndex + 1);
				pFiberPara = (CIecCfgFiberPara *)pFiberParas->FindByID(strID);

				if(pFiberPara != NULL)
				{
					if(pFiberPara->m_ntype == _IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_)
					{
						m_nSysParasFT3baud |= 1 << (20 + nIndex);
					}
				}
			}

			int nLCFiberPort = 0xff; //默认全百兆，千兆接收不支持自适应必须手动指定

			for(int nIndex = 0; nIndex < MAX_SV_FiberPort_NUM; nIndex++)
			{
				strID.Format(_T("LC%d"), nIndex + 1);
				pFiberPara = (CIecCfgFiberPara *)pFiberParas->FindByID(strID);

				if(pFiberPara != NULL)
				{
					if(pFiberPara->m_ntype == _IECCFG_SYSPARAS_LC_PORT_TYPE_1000M_)
					{
						nLCFiberPort &= ~(1 << nIndex);
					}
				}
			}

			g_theSystemConfig->m_nFiberType = nLCFiberPort;
			CIecCfgFiberParasIn *pFiberParasIn = pSysParasMngr->GetFiberParasIn();

			if(pFiberParasIn != NULL)
			{
				unsigned int nMainSTMode = 0;
				CIecCfgFiberPara *pFiberPara;

				for(int nIndex = 0; nIndex < 4; nIndex++)
				{
					strID.Format(_T("ST%d"), nIndex + 1);
					pFiberPara = (CIecCfgFiberPara *)pFiberParasIn->FindByID(strID);

					if(pFiberPara != NULL)
					{
						switch(pFiberPara->m_ntype)
						{
							case _IECCFG_SYSPARAS_ST_PORT_TYPE_BCode_:
								nMainSTMode |= 3 << (nIndex * 2);
								break;

							case _IECCFG_SYSPARAS_ST_PORT_TYPE_FT3_:
								nMainSTMode |= 1 << (nIndex * 2);
								break;

							case 2:
								nMainSTMode |= 2 << (nIndex * 2);
								break;
						}
					}
				}

				CSttDeviceBase::g_pSttDeviceBase->m_nMainSTMode = nMainSTMode;
			}
		}
	}
}

void CIEC61850CfgMngr::AfterInitIEC61850()
{
	memset(&m_oSvCfgTotal, 0, sizeof(SvConfigTotal));
	memset(confFt3, 0, sizeof(SendConfFT3));
	memset(confgse, 0, sizeof(SendConfGSE));
	m_nSysParasFT3baud = 0;
	GetSysParas();

	for(int i = 0; i < g_theDeviceSystemParameter->m_nModuleCount_D; i++)
	{
		PSTT_MODULE pModule = g_theDeviceSystemParameter->m_oModules_D[i];

		if(pModule == NULL)
		{
			continue;
		}

		confgse->module = m_pIECConfig->item[i].module;
		confgse->data4 = m_oGooseMngr.m_nT[0] * 50000;
		confgse->data5 = m_oGooseMngr.m_nT[1] * 50000;
		confgse->data6 = m_oGooseMngr.m_nT[2] * 50000;
		confgse->data7 = m_oGooseMngr.m_nT[3] * 50000;
		CSttDeviceBase::g_pSttDeviceBase->SetTestPara(GseCtrlCfg, (char *)confgse);
	}

	//目前上位机只能选择一种报文类型，无法针对FT3、ADMU、9-2的硬件分别设置
	QByteArray ba;
	//初始化9-2控制块
	if(m_nUseSmv92 == SMVTYPE_92)
	{
		for(int index = 0; index < m_o92Mngr.data_92.count(); index++)
		{
			ba.clear();
			tmt_sv_92 m_tmt_sv_92 = m_o92Mngr.data_92.at(index);
			CString t_AppID = m_tmt_sv_92.m_AppID;
			t_AppID = Get0String(4 - t_AppID.length()) + t_AppID;
			int nBoard = -1;

			for(int i = 0; i < m_pIECConfig->mdCnt; i++)
			{
				if(m_tmt_sv_92.port >= m_pIECConfig->item[i].nLCBeginIdx
						&& m_tmt_sv_92.port <= m_pIECConfig->item[i].nLCEndIdx)
				{
					nBoard = i;
					break;
				}
			}

			if(nBoard < 0)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] SV AppId=0x%s 光口配置超过硬件光口总数,配置无效"), t_AppID.GetString());
				continue;
			}			

			int nSmvIndex = m_pIECConfig->item[nBoard].smvCount;

			if(nSmvIndex == SMV_MAX)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] SV数量已达上限%d,AppId=0x%s被忽略"), SMV_MAX, t_AppID.GetString());
				break;
			}

			m_o92Mngr.Create92ByteArray(m_tmt_sv_92, ba);

			if(ba.size() > 1536)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] SV AppId=0x%s 报文总长度超过1536字节,配置无效"), t_AppID.GetString());
				continue;
			}

			m_pIECConfig->item[nBoard].sv[nSmvIndex].datCnt = ba.size();
			m_pIECConfig->item[nBoard].sv[nSmvIndex].GroupWithBit = 1 << nSmvIndex;
			memcpy(m_pIECConfig->item[nBoard].sv[nSmvIndex].dat, ba.constData(), ba.size());
			m_pIECConfig->item[nBoard].smvCount++;
			m_pIECConfig->item[nBoard].sv[nSmvIndex].GroupIdxWithNum = nSmvIndex;
			m_pIECConfig->item[nBoard].sv[nSmvIndex].IecXmlIndex = index;
			m_pIECConfig->item[nBoard].sv[nSmvIndex].PortIdx = m_tmt_sv_92.port
					- m_pIECConfig->item[nBoard].nLCBeginIdx;
			m_pIECConfig->item[nBoard].sv[nSmvIndex].Delaytime = m_tmt_sv_92.m_DelayTimeValue.toInt();
		}
	}
	else
	{
		//初始化FT3控制块
		long n6044Count = m_p6044MngrBase->data_6044.count();
		const tmt_ft3_6044 *p_tmt_6044;
		for(int index = 0; index < n6044Count; index++)
		{
			ba.clear();
			p_tmt_6044 = &(m_p6044MngrBase->data_6044.at(index));
			int nBoard = -1;

			for(int i = 0; i < m_pIECConfigFt3->mdCnt; i++)
			{
				if(p_tmt_6044->port >= m_pIECConfigFt3->item[i].nSTSendBeginIdx
						&& p_tmt_6044->port <= m_pIECConfigFt3->item[i].nSTSendEndIdx)
				{
					nBoard = i;
					break;
				}
			}

			if(nBoard < 0)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] FT3 发送口配置超过硬件光口总数,发送口%d无效"), p_tmt_6044->port);
				continue;
			}

			int nFt3Index = m_pIECConfigFt3->item[nBoard].ft3Count;

			if(nFt3Index == FT3_MAX)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] FT3数量已达上限%d,光口%d被忽略"), FT3_MAX, p_tmt_6044->port);
				break;
			}

			m_p6044MngrBase->Create6044ComByteArray(*p_tmt_6044, ba);

			if(ba.size() > 200)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] FT3 光口%d 报文总长度超过200字节,配置无效"), p_tmt_6044->port);
				continue;
			}			

			qDebug() << "##########################";
			qDebug() << "FT3 PortIdx = " << p_tmt_6044->port << ",PkgLen = " << ba.size() - 12;
			long nByteCount = ba.size();
			nByteCount = 4 - nByteCount % 4;

			for(int i = 0; i < nByteCount; i++)
			{
				ba.append((char)0);
			}

			QByteArray baDbg;

			for(int j = 0; j < 12; j++)
			{
				baDbg.append(ba.at(j));
			}

			qDebug() << baDbg.toHex();
			baDbg.clear();

			for(int j = 14; j < ba.size() - nByteCount; j++)
			{
				baDbg.append(ba.at(j));

				if(baDbg.size() == 18)
				{
					qDebug() << baDbg.toHex();
					baDbg.clear();
				}
			}

			if(baDbg.size() > 0)
			{
				qDebug() << baDbg.toHex();
			}

			qDebug() << "##########################";
			m_pIECConfigFt3->item[nBoard].ft3[nFt3Index].datCnt = ba.size();
			m_pIECConfigFt3->item[nBoard].ft3[nFt3Index].GroupWithBit =
				1 << (p_tmt_6044->port - m_pIECConfigFt3->item[nBoard].nSTSendBeginIdx); //光口设置,该变量含义与SV/GSE不同
			memcpy(m_pIECConfigFt3->item[nBoard].ft3[nFt3Index].dat, ba.constData(), ba.size());
			m_pIECConfigFt3->item[nBoard].ft3Count++;
			m_pIECConfigFt3->item[nBoard].ft3[nFt3Index].GroupIdxWithNum = nFt3Index;
			m_pIECConfigFt3->item[nBoard].ft3[nFt3Index].PortIdx = p_tmt_6044->port
					- m_pIECConfigFt3->item[nBoard].nSTSendBeginIdx;
			m_pIECConfigFt3->item[nBoard].ft3[nFt3Index].Delaytime = p_tmt_6044->m_nDelayTimeValue;
		}
	}

	memset(confsv, 0, sizeof(SendConfSV));
	long nSample;
	long nBaudRate;
	unsigned short nT;
	int nDelayPoint[8];
	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(ClearSvCfg, NULL);


	if(m_nUseSmv92 == SMVTYPE_92)
	{
		for(int i = 0; i < m_pIECConfig->mdCnt; i++)
		{
			nSample = m_o92Mngr.GetSmv92Sample();
			nT = 10000000 / nSample;
			int nDT = 1000000 / nSample;
			//sampleCnt FT3和9-2在FPGA中共用以最后下发的为准
			//FT3控制要提前发,不然会导致SV光口控制失败
			//根据配置是否发B码
			confFt3->module = m_pIECConfig->item[i].module;
			confFt3->baud = m_nSysParasFT3baud;

	//            nSample = m_o6044ComMngr.GetSample();
	//            nT = 10000000/nSample;
			confFt3->sampleCnt = nSample << 16 | nT;
			CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Ft3CtrlCfg, (char *)confFt3);
			confsv->module = m_pIECConfig->item[i].module;
			confsv->sampleCount = nSample << 16 | nT;

			for(int j = 0; j < 8; j++)
			{
				nDelayPoint[j] = nSample;
			}

			for(int j = 0; j < m_pIECConfig->item[i].smvCount; j++)
			{
				nDelayPoint[j] = m_pIECConfig->item[i].sv[j].Delaytime / nDT % nSample; //SV配置,整点补偿
			}

			for(int j = 0; j < 8; j++)
			{
				if(nDelayPoint[j] == 0)
				{
					nDelayPoint[j] = nSample;
				}
			}

			confsv->beginCode[0] = (nSample - nDelayPoint[0]) << 16;
			confsv->beginCode[0] |= nSample - nDelayPoint[1];
			confsv->beginCode[1] = (nSample - nDelayPoint[2]) << 16;
			confsv->beginCode[1] |= nSample - nDelayPoint[3];
			confsv->beginCode[2] = (nSample - nDelayPoint[4]) << 16;
			confsv->beginCode[2] |= nSample - nDelayPoint[5];
			confsv->beginCode[3] = (nSample - nDelayPoint[6]) << 16;
			confsv->beginCode[3] |= nSample - nDelayPoint[7];
			CSttDeviceBase::g_pSttDeviceBase->SetTestPara(SvCtrlCfg, (char *)confsv);
			memcpy(&m_oSvCfgTotal.confsv[m_oSvCfgTotal.Cnt], confsv, sizeof(SendConfSV));
			m_oSvCfgTotal.Cnt++;
		}
	}
	else
	{
		for(int i = 0; i < m_pIECConfigFt3->mdCnt; i++)
		{
			nSample = m_p6044MngrBase->GetSample();
			nBaudRate = m_p6044MngrBase->GetBaudRate();
			nT = 10000000 / nSample;
			//FT3及ST光口配置
			confFt3->module = m_pIECConfigFt3->item[i].module;
			confFt3->baud = m_nSysParasFT3baud;
			confFt3->sampleCnt = nSample << 16 | nT;

			switch(nBaudRate)
			{
				case 1:
					confFt3->baud |= 0b01;
					break;

				case 2:
					confFt3->baud |= 0b10;
					break;

				case 3:
					confFt3->baud |= 0b11;
					break;
			}

			int nbegin = 0;
			int nPort;

			for(int j = 0; j < m_pIECConfigFt3->item[i].ft3Count; j++)
			{
	//				nbegin = m_pIECConfig->item[i].ft3[j].Delaytime / 250;
				nPort = m_pIECConfigFt3->item[i].ft3[j].PortIdx;
				confFt3->baud |= 1 << (nPort + 3);
				confFt3->dat[0] = 0;
				confFt3->dat[1] = 0;
				confFt3->dat[2] = 0;
				confFt3->dat[3] = 0;
				confFt3->dat[4] = 0;
				confFt3->dat[5] = 0;
	//				if(nPort % 2 == 0)
	//				{
	//					confFt3->dat[nPort / 2] |= (nSample - nbegin) << 16;
	//				}
	//				else
	//				{
	//					confFt3->dat[nPort / 2] |= nSample - nbegin;
	//				}
			}

			CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Ft3CtrlCfg, (char *)confFt3);
		}
	}

	//初始化goose控制块
	for(int index = 0; index < m_oGooseMngr.data_gseout.count(); index++)
	{
		ba.clear();
		tmt_goose &m_tmt_goose = m_oGooseMngr.data_gseout[index];
		CString t_AppID = m_tmt_goose.m_AppID;
		t_AppID = Get0String(4 - t_AppID.length()) + t_AppID;
		int nBoard = -1;

		for(int i = 0; i < m_pIECConfig->mdCnt; i++)
		{
			if(m_tmt_goose.port >= m_pIECConfig->item[i].nLCBeginIdx
					&& m_tmt_goose.port <= m_pIECConfig->item[i].nLCEndIdx)
			{
				nBoard = i;
				break;
			}
		}

		if(nBoard < 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] GOOSE AppId=0x%s 光口配置超过硬件光口总数,配置无效"), t_AppID.GetString());
			continue;
		}

		int GsIndex = m_pIECConfig->item[nBoard].gsCount;

		if(GsIndex == GOOSE_MAX)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] GOOSE数量已达上限%d,AppId=0x%s被忽略"), GOOSE_MAX, t_AppID.GetString());
			break;
		}

		m_oGooseMngr.CreateGooseByteArray(ba, m_tmt_goose);

		if(ba.size() > 1536)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] GOOSE AppId=0x%s 报文总长度超过1536字节,配置无效"), t_AppID.GetString());
			continue;
		}		

		m_tmt_goose.m_nModuleIndex = m_pIECConfig->item[nBoard].module;
		m_pIECConfig->item[nBoard].gs[GsIndex].datCnt = ba.size();
		m_pIECConfig->item[nBoard].gs[GsIndex].GroupWithBit = 1 << GsIndex;
		m_tmt_goose.group = m_pIECConfig->item[nBoard].gs[GsIndex].GroupWithBit;
		memcpy(m_pIECConfig->item[nBoard].gs[GsIndex].dat, ba.constData(), ba.size());
		DrvGseChgModule *pseChgModule = &m_pGseChgParas->oModule[nBoard];
		DrvGseChgItem *pItem = &pseChgModule->oItem[GsIndex];
		pItem->nGroupIndex = m_tmt_goose.group;
		m_pIECConfig->item[nBoard].gsCount++;
		pseChgModule->nItemsCnt = m_pIECConfig->item[nBoard].gsCount;
		m_pIECConfig->item[nBoard].gs[GsIndex].GroupIdxWithNum = GsIndex;
		m_pIECConfig->item[nBoard].gs[GsIndex].PortIdx = m_tmt_goose.port
				- m_pIECConfig->item[nBoard].nLCBeginIdx;
		m_pIECConfig->item[nBoard].gs[GsIndex].IecXmlIndex = index;
	}

	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(IECDataCfg, (char *)m_pIECConfig);
	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(Ft3DataCfg, (char *)m_pIECConfigFt3);	
	FiberOpen();

	//稳控2M
	for(int nBoard = 0; nBoard < m_pIECConfig_2M->moduleCount; nBoard++)
	{
		for(int index = 0; index < MAX_2M_BLOCK_COUNT; index++)
		{
			ba.clear();
			tmt_Stable2MList oStable2MList = m_oStable2MMngr.m_oStable2MList[nBoard][index];
			m_oStable2MMngr.Create2MListByteArray(oStable2MList, index, ba);
			memcpy(m_pIECConfig_2M->item[nBoard].dats[index].dat, ba.constData(), ba.size());
			m_pIECConfig_2M->item[nBoard].dats[index].count = ba.size();
		}
	}

	CSttDeviceBase::g_pSttDeviceBase->SetTestPara(IECDataCfg_Stable2M, (char *)m_pIECConfig_2M);
	SetGseOutMap();	
}

BOOL CIEC61850CfgMngr::DealSmvAbnPacket(StructComAbn *pSvItem, tmt_StateAbnormalSMV oTmtAbnPara, tmt_sv_92 oTMtSmvAbn, unsigned int nQuality[50])
{
	unsigned int nGroup = oTmtAbnPara.m_nGroupIndex;

	if(nGroup < m_o92Mngr.data_92.size())
	{
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] SV组号[%d]无效"), oTmtAbnPara.m_nGroupIndex);
		return FALSE;
	}

	tmt_sv_92 oTMt = m_o92Mngr.data_92.at(nGroup);
	int nPort = oTMt.port;
	int nBoard = nPort / 8;
	int nSvIndex = -1;

	for(int i = 0; i < m_pIECConfig->item[nBoard].smvCount; i++)
	{
		if(m_pIECConfig->item[nBoard].sv[i].IecXmlIndex == nGroup)
		{
			nSvIndex = m_pIECConfig->item[nBoard].sv[i].GroupIdxWithNum;
			break;
		}
	}

	if(nSvIndex < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] SV组号[%d]与IEC配置内容不符"), oTmtAbnPara.m_nGroupIndex);
		return FALSE;
	}

	QByteArray ba;
	oTMt.m_VLanID = oTMtSmvAbn.m_VLanID;
	oTMt.m_VLanPri = oTMtSmvAbn.m_VLanPri;
	oTMt.m_SyncMode = oTMtSmvAbn.m_SyncMode;
	oTMt.m_NetType = oTMtSmvAbn.m_NetType;
	oTMt.m_ConfRev = oTMtSmvAbn.m_ConfRev;
	oTMt.m_AppID = oTMtSmvAbn.m_AppID;
	oTMt.m_MacDesc = oTMtSmvAbn.m_MacDesc;
	oTMt.m_MacSrc = oTMtSmvAbn.m_MacSrc;
	oTMt.m_SVID = oTMtSmvAbn.m_SVID;
	oTMt.m_Datset = oTMtSmvAbn.m_Datset;
	oTMt.m_FactorList.clear();
	QString strHighQuality = "0000";
	QString strLowQuality;

	for(int i = 0; i < oTMt.m_ChanValueList.size(); i++)
	{
		strLowQuality = QString("%1").arg(nQuality[i], 4, 16, QChar('0'));
		oTMt.m_FactorList.append(strHighQuality + strLowQuality);
	}

	if(oTmtAbnPara.m_nAbnormalType == 6)
	{
		oTMt.m_DelayTimeValue = QString::number(oTmtAbnPara.m_nDelayChangeValue);
	}

	m_o92Mngr.Create92ByteArray(oTMt, ba);

	if(ba.size() <= 1536)
	{
		pSvItem->len = ba.size();
		memcpy(pSvItem->dat, ba.constData(), ba.size());
		pSvItem->group = m_pIECConfig->item[nBoard].sv[nSvIndex].GroupWithBit;
		pSvItem->module = m_pIECConfig->item[nBoard].module;
		return TRUE;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] SV[%d]异常模拟控制块报文总长度超过1536字节"), oTmtAbnPara.m_nGroupIndex);
		return FALSE;
	}
}

void CIEC61850CfgMngr::DealSmvAbnConfig(SendConfSV	*pSVCfg, unsigned int nGroup, unsigned int nSmvAbnType, unsigned int nSmvAbnValue, BOOL bIsDefault)
{
	if(nGroup < m_o92Mngr.data_92.size())
	{
	}
	else
	{
		return;
	}

	tmt_sv_92 oTMt = m_o92Mngr.data_92.at(nGroup);
	int nPort = oTMt.port;
	int nBoard = nPort / 8;
	int nSvIndex = -1;

	for(int i = 0; i < m_pIECConfig->item[nBoard].smvCount; i++)
	{
		if(m_pIECConfig->item[nBoard].sv[i].IecXmlIndex == nGroup)
		{
			nSvIndex = m_pIECConfig->item[nBoard].sv[i].GroupIdxWithNum;
			break;
		}
	}

	if(nSvIndex < 0)
	{
		return;
	}

	memcpy(pSVCfg, &m_oSvCfgTotal.confsv[nBoard], sizeof(SendConfSV));

	if(bIsDefault)
	{
	}
	else
	{
		// 异常类型：5-延时偏差7-序号偏差
		unsigned int nOffSet = 0;

		if(nSmvAbnType == 5)
		{
			int nDT = 1000000 / m_o92Mngr.GetSmv92Sample();
			nOffSet = nSmvAbnValue / nDT;
		}
		else if(nSmvAbnType == 7)
		{
			nOffSet = nSmvAbnValue;
		}
		else
		{
			return;
		}

		unsigned int nOld = pSVCfg->beginCode[nSvIndex / 2];
		unsigned int nNew = nOld;
		unsigned short nv = 0;

		if(nSvIndex % 2 == 0)
		{
			nv = nOld >> 16;

			if(nv > nOffSet)
			{
				nv = nv - nOffSet;
			}
			else
			{
				nv = m_o92Mngr.GetSmv92Sample() + nv - nOffSet;
			}

			nNew &= 0xFFFF;
			nNew = (nv << 16) | nNew;
			pSVCfg->beginCode[nSvIndex / 2] = nNew;
		}
		else
		{
			nv = nOld & 0xFFFF;

			if(nv > nOffSet)
			{
				nv = nv - nOffSet;
			}
			else
			{
				nv = m_o92Mngr.GetSmv92Sample() + nv - nOffSet;
			}

			nNew &= 0xFFFF0000;
			nNew = nv | nNew;
			pSVCfg->beginCode[nSvIndex / 2] = nNew;
		}
	}
}

BOOL CIEC61850CfgMngr::DealGseAbnConfig(StructComAbn *pGSItem, tmt_StatePara  *pTmt_paraState, tmt_StatePara  *pTmt_paraPreState)
{
	tmt_StateAbnormalGOOSE oTmtAbnPara = pTmt_paraState->m_oAbnormalGOOSE;
	unsigned int nGroup = oTmtAbnPara.m_nGroupIndex;

	if(nGroup < m_oGooseMngr.data_gseout.size())
	{
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] GOOSE组号[%d]无效"), oTmtAbnPara.m_nGroupIndex);
		return FALSE;
	}

	tmt_goose oTMt = m_oGooseMngr.data_gseout.at(nGroup);

	if(oTmtAbnPara.m_bSrcMac_Sel)
	{
		oTMt.m_MacSrc = QString(oTmtAbnPara.m_strSrcMac).replace("-", "").trimmed();
		oTMt.m_MacSrc = oTMt.m_MacSrc.rightJustified(12, QChar('0'));
	}

	if(oTmtAbnPara.m_bDestMac_Sel)
	{
		oTMt.m_MacDesc = QString(oTmtAbnPara.m_strDestMac).replace("-", "").trimmed();
		oTMt.m_MacDesc = oTMt.m_MacDesc.rightJustified(12, QChar('0'));
	}

	if(oTmtAbnPara.m_bGocbRef_Sel)
	{
		oTMt.m_GcRef = QString(oTmtAbnPara.m_strGocbRef);
	}

	if(oTmtAbnPara.m_bGoID_Sel)
	{
		oTMt.m_GoID = QString(oTmtAbnPara.m_strGoID);
	}

	if(oTmtAbnPara.m_bDataSet_Sel)
	{
		oTMt.m_DataSetRef = QString(oTmtAbnPara.m_strDataSet);
	}

	if(oTmtAbnPara.m_bAppID_Sel)
	{
		oTMt.m_AppID = QString::number(oTmtAbnPara.m_nAppID, 16);
	}

	if(oTmtAbnPara.m_bNdsCom_Sel)
	{
		oTMt.m_NdsCom = QString::number(oTmtAbnPara.m_nNdsCom);
	}

	if(oTmtAbnPara.m_bTestFlag_Sel)
	{
		oTMt.m_TestMode = QString::number(oTmtAbnPara.m_nTestFlag);
	}

	if(oTmtAbnPara.m_bStNumSet_Sel)
	{
		oTMt.m_StNum = QString("%1").arg(oTmtAbnPara.m_nStNum, 8, 10, QChar('0'));
	}

	if(oTmtAbnPara.m_bSqNumSet_Sel)
	{
		oTMt.m_SqNum = QString("%1").arg(oTmtAbnPara.m_nSqNum, 8, 10, QChar('0'));
	}

	if(oTmtAbnPara.m_bTtlSet_Sel)
	{
		oTMt.m_TTL = QString::number(oTmtAbnPara.m_nTimeAllowToLive);
	}

	if(oTmtAbnPara.m_bVlanSet_Sel)
	{
		oTMt.m_VLanID = QString::number(oTmtAbnPara.m_nVlanID);
	}

	if(oTmtAbnPara.m_bNetTypeSet_Sel)
	{
		if(oTmtAbnPara.m_nNetType == 0)
		{
			oTmtAbnPara.m_nNetType = 0x88b8;
		}

		oTMt.m_NetType = QString("%1").arg(oTmtAbnPara.m_nNetType & 0xFFFF, 4, 16, QChar('0'));
	}

	if(oTmtAbnPara.m_bConfRecvSet_Sel)
	{
		oTMt.m_ConfRev = QString::number(oTmtAbnPara.m_nConfRecv);
	}

	oTMt.m_VLanPri = QString::number(oTmtAbnPara.m_nVLanPriority);
	oTMt.ntimequality = (char)(oTmtAbnPara.m_nTimequality & 0xFF);
	BOOL bUpdateUtc[MAX_GOOSE_CHANNEL_COUNT];
	CString strChannel, strDataType;

	for(int nChanId = 0; nChanId < oTMt.m_ChanNum; nChanId++)
	{
		ChanelInfo &chaninfo = oTMt.vChanelInfo[nChanId];
		strChannel = pTmt_paraState->m_oGoosePub[nGroup].m_strChannel[nChanId];
		strDataType = chaninfo.data_type;

		if(QString::compare(strDataType, "Dbpos") == 0 ||
				QString::compare(strDataType, "VisString64") == 0)
		{
			strChannel.replace("[", "").replace("]", "");
		}

		if(pTmt_paraPreState == NULL)
		{
			bUpdateUtc[nChanId] = FALSE;
			chaninfo.firstvalue = strChannel;
		}
		else
		{
			CString strPreChannel = pTmt_paraPreState->m_oGoosePub[nGroup].m_strChannel[nChanId];

			if(QString::compare(strDataType, "Dbpos") == 0 ||
					QString::compare(strDataType, "VisString64") == 0)
			{
				strPreChannel.replace("[", "").replace("]", "");
			}

			if(strChannel.compare(strPreChannel) == 0)
			{
				bUpdateUtc[nChanId] = FALSE;
				chaninfo.firstvalue = strPreChannel;
			}
			else
			{
				bUpdateUtc[nChanId] = TRUE;
				chaninfo.firstvalue = strChannel;
			}
		}
	}

	int nPort = oTMt.port;
	int nBoard = nPort / 8;
	int nGseIndex = -1;

	for(int i = 0; i < m_pIECConfig->item[nBoard].gsCount; i++)
	{
		if(m_pIECConfig->item[nBoard].gs[i].IecXmlIndex == nGroup)
		{
			nGseIndex = m_pIECConfig->item[nBoard].gs[i].GroupIdxWithNum;
			break;
		}
	}

	if(nGseIndex < 0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] GOOSE组号[%d]与IEC配置内容不符"), oTmtAbnPara.m_nGroupIndex);
		return FALSE;
	}

	m_oGooseMngr.UpdateGooseTmtDataSetList(oTMt);//更新通道值
	QByteArray ba;
	m_oGooseMngr.CreateGooseByteArray(ba, oTMt); //更新控制块信息

//    qDebug()<<ba.toHex();
	if(ba.size() <= 1536)
	{
		pGSItem->gsTimePos = oTMt.nUTCPos;
		pGSItem->group = m_pIECConfig->item[nBoard].gs[nGseIndex].GroupWithBit;
		pGSItem->module = m_pIECConfig->item[nBoard].module;
		pGSItem->len = ba.size();

		for(int chanid = 0; chanid < oTMt.m_ChanNum; chanid++)
		{
			ChanelInfo chaninfo = oTMt.vChanelInfo.at(chanid);

			if(chaninfo.bHasUTC && bUpdateUtc[chanid])
			{
				pGSItem->nUTCPos[pGSItem->nUTCCnt] = oTMt.nDataSetPos + chaninfo.nUTCPos;
				pGSItem->nUTCCnt++;
			}
		}

		memcpy(pGSItem->dat, ba.constData(), ba.size());
		return TRUE;
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] GOOSE[%d]异常模拟控制块报文总长度超过1536字节"), oTmtAbnPara.m_nGroupIndex);
		return FALSE;
	}
}

void CIEC61850CfgMngr::SetGseOutMap()
{
	memset(stMaps, 0, sizeof(Drv_GSOutMap));
	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	structBOMap *pBoMap;
	int index;
	int nBoIndex;
	int nFlag;
	int nBoardIndex;

	for(int i = 0; i < m_oGooseMngr.data_gseout.count(); i++)
	{
		tmt_goose otmt_goose = m_oGooseMngr.data_gseout[i];

		for(int chan = 0; chan < otmt_goose.vChanelInfo.count(); chan++)
		{
			ChanelInfo oChanelInfo = otmt_goose.vChanelInfo[chan];

			if(oChanelInfo.nBOIndex > 0)
			{
				nBoIndex = oChanelInfo.nBOIndex - 1;
				index = stMaps->boMd[0].info[nBoIndex].cnt;

				if(index == 16)
				{
					continue;
				}

				pBoMap = &(stMaps->boMd[0].info[nBoIndex].stMap[index]);
				pBoMap->group = otmt_goose.group;
				pBoMap->module = otmt_goose.m_nModuleIndex;
				pBoMap->falseValue = oChanelInfo.nFalseVlaue;
				pBoMap->trueValue = oChanelInfo.nTrueValue;
				pBoMap->hasUTC = oChanelInfo.bHasUTC;
				pBoMap->utcPos = otmt_goose.nDataSetPos + oChanelInfo.nUTCPos;
				pBoMap->pos = otmt_goose.nDataSetPos + oChanelInfo.nBoPos;
				stMaps->boMd[0].info[nBoIndex].cnt++;
			}
			else if(oChanelInfo.nBOExIndex > 0)
			{
				//扩展开关量板
				nBoIndex = oChanelInfo.nBOExIndex - 1;

				if(oSwitchModules.m_nModulesCount == 0)
				{
					//无扩展板情况下，限制nBoIndex:0-63
					if(nBoIndex > -1 && nBoIndex < 64)
					{
						index = stMaps->boMd[1].info[nBoIndex].cnt;

						if(index < 16)
						{
							pBoMap = &(stMaps->boMd[1].info[nBoIndex].stMap[index]);
							pBoMap->module = otmt_goose.m_nModuleIndex;
							pBoMap->group = otmt_goose.group;
							pBoMap->falseValue = oChanelInfo.nFalseVlaue;
							pBoMap->trueValue = oChanelInfo.nTrueValue;
							pBoMap->hasUTC = oChanelInfo.bHasUTC;
							pBoMap->utcPos = otmt_goose.nDataSetPos + oChanelInfo.nUTCPos;
							pBoMap->pos = otmt_goose.nDataSetPos + oChanelInfo.nBoPos;
							stMaps->boMd[1].info[nBoIndex].cnt++;
						}
					}

					continue;
				}

				int nOffSet = 0;
				nBoardIndex = -1;

				for(int j = 0; j < oSwitchModules.m_nModulesCount; j++)
				{
					nOffSet += oSwitchModules.oSWITCHINFO[j].m_nBoCount;

					if(nBoIndex < nOffSet)
					{
						nBoardIndex = j + 1;
						break;
					}
				}

				if(nBoardIndex < 1)
				{
					continue;
				}

				nFlag = nBoIndex;

				for(int j = 0; j < nBoardIndex - 1; j++)
				{
					nFlag -= oSwitchModules.oSWITCHINFO[j].m_nBoCount;
				}

				index = stMaps->boMd[nBoardIndex].info[nFlag].cnt;

				if(index == 16)
				{
					continue;
				}

				pBoMap = &(stMaps->boMd[nBoardIndex].info[nFlag].stMap[index]);
				pBoMap->group = otmt_goose.group;
				pBoMap->module = otmt_goose.m_nModuleIndex;
				pBoMap->falseValue = oChanelInfo.nFalseVlaue;
				pBoMap->trueValue = oChanelInfo.nTrueValue;
				pBoMap->hasUTC = oChanelInfo.bHasUTC;
				pBoMap->utcPos = otmt_goose.nDataSetPos + oChanelInfo.nUTCPos;
				pBoMap->pos = otmt_goose.nDataSetPos + oChanelInfo.nBoPos;
				stMaps->boMd[nBoardIndex].info[nFlag].cnt++;
			}
		}
	}

	CSttDeviceBase::g_pSttDeviceBase->SetBoMap((char *)stMaps);
}

void CIEC61850CfgMngr::SetGooseSub()
{
	int ngsesubIndex = 0;
	int nBiIndex = 0;
	int nCnt;
	long nCrc;
	CString strLog;
	int nGseInCnt = m_oIecCfgDatasMngr.GetGINCount();

	for(int index = 0; index < nGseInCnt; index++)
	{
		CIecCfgGinData *gsein_data = (CIecCfgGinData *)m_oIecCfgDatasMngr.GetGinCfgData(index);
		QString m_AppID = QString("%1").arg(gsein_data->m_dwAppID, 4, 16, QChar('0'));
		QString m_MacDesc = gsein_data->m_strDestAddress.replace("-", "");
		nCrc = CalCRC(m_AppID, m_MacDesc, gsein_data->m_nFiberIndex, 2);

		if(gsein_data->m_nUseFlag == 0)
		{
			continue;
		}

		if(ngsesubIndex == 16)
		{
			continue;
		}

		switch(gsein_data->m_bTest)
		{
			case 0:
			case 1:
				gsesub->oIecSub[ngsesubIndex].oItem.testMode = gsein_data->m_bTest;

			default:
				gsesub->oIecSub[ngsesubIndex].oItem.testMode = 2;//参数异常，默认不判断该标记
		}

		if(gsein_data->m_nUseGooseID)
		{
			gsesub->oIecSub[ngsesubIndex].oItem.paramAdvance = 1;
			QByteArray ba;
			CString strGOCB = gsein_data->m_strgocbRef;
			ba = strGOCB.toLatin1();
			gsesub->oIecSub[ngsesubIndex].oItem.gocbLen = ba.size();
			memcpy(gsesub->oIecSub[ngsesubIndex].oItem.GOCB, ba, ba.size());
			CString strGOID = gsein_data->m_strGooseId;
			ba = strGOID.toLatin1();
			gsesub->oIecSub[ngsesubIndex].oItem.goidLen = ba.size();
			memcpy(gsesub->oIecSub[ngsesubIndex].oItem.GOID, ba, ba.size());
			CString strDataSet = gsein_data->m_strDataSet;
			ba = strDataSet.toLatin1();
			gsesub->oIecSub[ngsesubIndex].oItem.dataSetLen = ba.size();
			memcpy(gsesub->oIecSub[ngsesubIndex].oItem.dataSet, ba, ba.size());
		}
		else
		{
			gsesub->oIecSub[ngsesubIndex].oItem.paramAdvance = 0;
		}

		//AT02D只有位置四可以订阅GOOSE
		gsesub->oIecSub[ngsesubIndex].CRC = nCrc;
		strLog = QString("SubMode GOOSEin[%1] AppId[%2] CRC=%3 TestMode=%4").arg(ngsesubIndex).arg(m_AppID).
				 arg(QString("0x%1").arg(gsesub->oIecSub[ngsesubIndex].CRC, 4, 16, QChar('0'))).
				 arg(gsesub->oIecSub[ngsesubIndex].oItem.testMode);
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s"), strLog.GetString());
		unsigned long nLastByte, nTrueValue, nFalseValue;
		gsesub->oIecSub[ngsesubIndex].oItem.count = 0;

		for(int chanid = 0; chanid < gsein_data->m_nChannelNum; chanid++)
		{
			CIecCfgGoutCh *ch = (CIecCfgGoutCh *)gsein_data->m_pCfgChs->GetAtIndex(chanid);
			QString m_strBiMap = ch->m_strAppChID;
			QStringList binlist = m_strBiMap.split(";");

			if(binlist.count() < 2)
			{
				continue;//以";"作为判断字符串合法的依据
			}

			m_oGooseMngr.GetGooseIn_DataPosAndValue(gsein_data, chanid, nLastByte, nTrueValue, nFalseValue);
			QString strMapInfo;

			foreach(QString strbin, binlist)
			{
				nCnt = gsesub->oIecSub[ngsesubIndex].oItem.count;

				if(nCnt == 64)
				{
					continue;
				}

				if(strbin.contains("binex"))
				{
					strMapInfo.append(strbin);
					strMapInfo.append(" ");
					nBiIndex = strbin.replace("binex", "").toInt() - 1;
					gsesub->oIecSub[ngsesubIndex].oItem.val[nCnt].mdPos = 1;
					gsesub->oIecSub[ngsesubIndex].oItem.val[nCnt].index = nBiIndex;
				}
				else if(strbin.contains("bin"))
				{
					strMapInfo.append(strbin);
					strMapInfo.append(" ");
					nBiIndex = strbin.replace("bin", "").toInt() - 1;
					gsesub->oIecSub[ngsesubIndex].oItem.val[nCnt].mdPos = 0;
					gsesub->oIecSub[ngsesubIndex].oItem.val[nCnt].index = nBiIndex;
				}
				else
				{
					continue;
				}

				gsesub->oIecSub[ngsesubIndex].oItem.val[nCnt].pos = nLastByte;
				gsesub->oIecSub[ngsesubIndex].oItem.val[nCnt].falseValue = nFalseValue;
				gsesub->oIecSub[ngsesubIndex].oItem.val[nCnt].trueValue = nTrueValue;
				gsesub->oIecSub[ngsesubIndex].oItem.count++;
			}

			if(strMapInfo.length() > 0)
			{
				strLog = QString("SubMode GOOSEin[%1] AppId[%2] ChanId[%3] MapId=%4").arg(ngsesubIndex).
						 arg(m_AppID).arg(QString("%1").arg(chanid, 3, 10, QChar('0'))).arg(strMapInfo);
				CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s"), strLog.GetString());
			}
		}

		strLog = QString("SubMode GOOSEin[%1] AppId[%2] MapCount=%3").arg(ngsesubIndex).
				 arg(m_AppID).arg(gsesub->oIecSub[ngsesubIndex].oItem.count);
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s"), strLog.GetString());
		m_pIECConfig->item[0].gsSub[ngsesubIndex].PortIdx = gsein_data->m_nFiberIndex;
		ngsesubIndex++;
	}

	gsesub->nType = 4;
	gsesub->ncount = ngsesubIndex;
	m_pIECConfig->item[0].gsSubCount = ngsesubIndex;
	CSttDeviceBase::g_pSttDeviceBase->SetGooseSub((char *)gsesub);
}

void CIEC61850CfgMngr::SetRecordIecIn()
{
	//合并单元实验
	memset(gsesub, 0, sizeof(IecRecvCfg));
	BOOL bOk;
	long nCrc;
	long nAppID;
	QString m_AppID;
	long nIecSubIndex = 0;
	CString strLog;

	for(int index = 0; index < m_o92Mngr.data_92Sub.count(); index++)
	{
		tmt_sv_92 oTmt92 = m_o92Mngr.data_92Sub.at(index);
		nAppID = oTmt92.m_AppID.toUInt(&bOk, 16);
		m_AppID = QString("%1").arg(nAppID, 4, 16, QChar('0'));
		nCrc = CalCRC(m_AppID, oTmt92.m_MacDesc, oTmt92.port, 1);

		if(nIecSubIndex == 16)
		{
			continue;
		}

		gsesub->oIecSub[nIecSubIndex].CRC = nCrc;
		strLog = QString("RecordMode SmvIn[%1] AppId[%2] CRC=%3").arg(nIecSubIndex).arg(m_AppID).
				 arg(QString("0x%1").arg(gsesub->oIecSub[nIecSubIndex].CRC, 4, 16, QChar('0')));
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s"), strLog.GetString());
		nIecSubIndex++;
	}

	//智能终端实验
	int nGseInCnt = m_oIecCfgDatasMngr.GetGINCount();

	for(int index = 0; index < nGseInCnt; index++)
	{
		CIecCfgGinData *gsein_data = (CIecCfgGinData *)m_oIecCfgDatasMngr.GetGinCfgData(index);
		m_AppID = QString("%1").arg(gsein_data->m_dwAppID, 4, 16, QChar('0'));
		QString m_MacDesc = gsein_data->m_strDestAddress.replace("-", "");
		nCrc = CalCRC(m_AppID, m_MacDesc, gsein_data->m_nFiberIndex, 2);

		if(nIecSubIndex == 16)
		{
			continue;
		}

		gsesub->oIecSub[nIecSubIndex].CRC = nCrc;
		strLog = QString("RecordMode GooseIn[%1] AppId[%2] CRC=%3").arg(nIecSubIndex).arg(m_AppID).
				 arg(QString("0x%1").arg(gsesub->oIecSub[nIecSubIndex].CRC, 4, 16, QChar('0')));
		CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("%s"), strLog.GetString());
		nIecSubIndex++;
	}

	gsesub->nType = 4;
	gsesub->ncount = nIecSubIndex;
	m_pIECConfig->item[0].gsSubCount = nIecSubIndex;
	CSttDeviceBase::g_pSttDeviceBase->SetGooseSub((char *)gsesub);
}

void CIEC61850CfgMngr::SetFT3SubMap()
{
	memset(ft3subs, 0, sizeof(Ft3SubDatas));
	ft3subs->nModuleCnt = m_pIECConfigFt3->mdCnt;
	unsigned int nBaud[4] = {5, 10, 20, 40};

	for(int i = 0; i < m_pIECConfigFt3->mdCnt; i++)
	{
		ft3subs->ft3SubData[i].nModule = m_pIECConfigFt3->item[i].module;
		ft3subs->ft3SubData[i].nOffset = m_pIECConfigFt3->item[i].nSTRecvBeginIdx;
	}

	long n6044Count  = m_p6044MngrBase->data_6044Sub.count();
	const tmt_ft3_6044 *ptmt_6044;

	for(int i = 0; i < n6044Count; i++)
	{
		ptmt_6044 = &(m_p6044MngrBase->data_6044Sub.at(i));
		int nBoard = -1;

		for(int j = 0; j < m_pIECConfigFt3->mdCnt; j++)
		{
			if(ptmt_6044->port >= m_pIECConfigFt3->item[j].nSTRecvBeginIdx
					&& ptmt_6044->port <= m_pIECConfigFt3->item[j].nSTRecvEndIdx)
			{
				nBoard = j;
				break;
			}
		}

		if(nBoard < 0)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] FT3 接收口配置超过硬件光口总数,接收口%d无效"), ptmt_6044->port);
			continue;
		}
		Ft3SubData *pft3sub = &ft3subs->ft3SubData[nBoard];
		int nBlockIdx = pft3sub->nCnt;

		if(nBlockIdx == FT3_Recv_MAX)
		{
			CLogPrint::LogFormatString(XLOGLEVEL_DEBUG, _T("[error] FT3接收数量已达上限%d,光口%d被忽略"), FT3_Recv_MAX, ptmt_6044->port);
			break;
		}

		pft3sub->ft3Item[nBlockIdx].nPort = ptmt_6044->port - m_pIECConfigFt3->item[nBoard].nSTRecvBeginIdx;
		pft3sub->ft3Item[nBlockIdx].nPortEx = ptmt_6044->port;
		pft3sub->ft3Item[nBlockIdx].npacketLen = ptmt_6044->m_nTotalSizeSub;
		pft3sub->ft3Item[nBlockIdx].nbaud = 200 / nBaud[ptmt_6044->m_nBaudValSub];//自适应时，要留出18个字节逻辑时间给FPGA
		pft3sub->ft3Item[nBlockIdx].nMapCnt = 0;
		long nChanCnt = ptmt_6044->m_oChanList.count();

		for(int nChan = 0; nChan < nChanCnt; nChan++)
		{
			long nMapIdx = pft3sub->ft3Item[nBlockIdx].nMapCnt;

			if(nMapIdx < 8)
			{
				FT3ChanInfo oInfo = ptmt_6044->m_oChanList.at(nChan);

				if(oInfo.nValidBitSub > 0)
				{
					Ft3SubChanel *pft3Chanel = &pft3sub->ft3Item[nBlockIdx].ft3Chanel[nMapIdx];
					pft3Chanel->nValidBit = oInfo.nValidBitSub;
					pft3Chanel->nChanPos1 = oInfo.nChanPos1;
					pft3Chanel->nChanLen1 = oInfo.nChanLen1;
					pft3Chanel->nChanPos2 = oInfo.nChanPos2;
					pft3Chanel->nChanLen2 = oInfo.nChanLen2;

					for(int nBitIdx = 0; nBitIdx < 16; nBitIdx++)
					{
						pft3Chanel->nBiSwitch[nBitIdx] = oInfo.nBiIdxSub[nBitIdx];
					}

					pft3sub->ft3Item[nBlockIdx].nMapCnt++;
				}
			}
		}

		pft3sub->nCnt++;
	}


	CSttDeviceBase::g_pSttDeviceBase->SetFT3SubMap((char *)ft3subs);
}
