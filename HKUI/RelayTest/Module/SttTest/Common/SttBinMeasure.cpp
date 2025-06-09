#include "SttBinMeasure.h"

CString CSttBinMeasure::m_strMacroName = "开入采集";
CString CSttBinMeasure::m_strMacroID = STT_MACRO_ID_BinMeas;
CString CSttBinMeasure::m_strFilePostFix = "stttst";
CString CSttBinMeasure::m_strMacroVer ="1.0";

CSttBinMeasure::CSttBinMeasure()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	SetTestStarting(FALSE);
	Init();
}

CSttBinMeasure::~CSttBinMeasure()
{
	Stop();
}

void CSttBinMeasure::Init()
{

}

void CSttBinMeasure::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
	pXmlSerialize->xml_serialize("起停使能(0-停止采集，1-开始采集)", "Enable", "", "long", m_nWorkMode);
	pXmlSerialize->xml_serialize("采样率HZ", "Sample", "", "long", m_oBinSetting.nSample);
	CSttXmlSerializeBase *pBinGroup;
	CString strName,strID;
	char strTemp[11] = "ABCDEFGHIJ";
	long nMeasGear,nEType;
	float fSwitchVolt;
	for(int i = 0;i < 10;i++)
	{
		strName.Format("开入%c",strTemp[i]);
		strID.Format("Bin%c",strTemp[i]);
		pBinGroup = pXmlSerialize->xml_serialize(strName.GetString(), strID.GetString(), "Bin", stt_ParaGroupKey());
		if(pBinGroup == NULL)
		{
			continue;
		}

		pBinGroup->xml_serialize("0-无效，1-电压，2-电流，3-有源开关量，4-无源开关量", "EType", "", "long", nEType);
		pBinGroup->xml_serialize("有源开关量翻转阈值", "SwitchVolt", "", "float", fSwitchVolt);
		pBinGroup->xml_serialize("采集档位(0-600V,1-100V,2-10V,3-1V,4-0.1V)", "MeasGear",
									 "", "long", nMeasGear);

		m_oBinSetting.nMeasGear[i] = Gear_600V;
		m_oBinSetting.nEType[i] = 0;

		switch(nMeasGear)
		{
		case 1:
			m_oBinSetting.nMeasGear[i] = Gear_100V;
			break;
		case 2:
			m_oBinSetting.nMeasGear[i] = Gear_10V;
			break;
		case 3:
			m_oBinSetting.nMeasGear[i] = Gear_1V;
			break;
		case 4:
			m_oBinSetting.nMeasGear[i] = Gear_01V;
			break;
		}

		switch(nEType)
		{
		case 0:
		{
			m_oBinSetting.nMeasGear[i] = Gear_600V;
		}
			break;
		case 4:
		{
			m_oBinSetting.nEType[i] = 1;
		}
			break;
		}
	}	
#endif
}

BOOL CSttBinMeasure::EventProcess()
{
	if(!GetTestStarting())
	{
		return FALSE;
	}

	BOOL bTestFinished = FALSE;
#ifdef _PSX_QT_LINUX_
	// CSttDeviceBase::g_pSttDeviceBase->ProCommDrvResult(bTestFinished, m_oTestFinishedTime);
#endif
	return bTestFinished;
}

void CSttBinMeasure::StartTest()
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttBinMeasure::StartTest >>>>>>");
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas == 0)
	{
		ReturnTestStateEvent_TestStart(0, 0, FALSE);
		return;
	}

	if(GetTestStarting())
	{
		Stop();
		Sleep(100);
	}

	CSttDeviceBase::g_pSttDeviceBase->InitDrvResult();
	SetTestStarting(TRUE);	
	if(!g_oSttRcdSendSocket.m_bRunning)
	{
		g_oSttRcdSendSocket.m_bRunning = TRUE;
		pthread_mutex_unlock(&g_oSttRcdSendMutex);
	}
	if(!bIecRecordRun)
	{
		bIecRecordRun = TRUE;
		pthread_t nthreadid;
		int nRet = pthread_create(&nthreadid, NULL, IecPkgCapThread, (LPVOID)CSttDeviceBase::g_pSttDeviceBase);
#ifdef _PSX_QT_LINUX_
		if(nRet == 0)
		{
			qDebug() << ">>>>>>Create IecPkgCapThread";
		}
#endif
	}

	CSttDeviceBase::g_pSttDeviceBase->m_nIsIecMode = 2;
	unsigned int nCode = 0;
	//采集功能
	CSttDeviceBase::g_pSttDeviceBase->Set_BinaryGear(&m_oBinSetting);

	nCode |= 1<<31;
	nCode |= (1000000000/m_oBinSetting.nSample/50)<<10;
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();

	Drv_BinMeas oBinMeas;
	memset(&oBinMeas,0,sizeof(Drv_BinMeas));
	oBinMeas.tirpType = 0;

	g_nNeedReportDevExcept = 0;
	g_nNeedReportUTC = 0;

	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x126, 1);
	ioctl(nFd, 0x7000407c, nCode);
	ioctl(nFd, 0x315, 0);
	write(nFd,(char*)&oBinMeas,sizeof(Drv_BinMeas));
	ioctl(nFd, 0x103, 0x16);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	ReturnTestStateEvent_TestStart(0, 0, FALSE);
}

long CSttBinMeasure::SetParameter(DWORD dwState)
{
	CLogPrint::LogString(XLOGLEVEL_DEBUG, _T("CSttBinMeasure::SetParameter >>>>>>"));
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas == 0)
	{
		return 0;
	}

	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();

	if(m_nWorkMode == 0)
	{
		CSttDeviceBase::g_pSttDeviceBase->m_nIsIecMode = 0;
		if(g_oSttRcdSendSocket.m_bRunning)
		{
			pthread_mutex_lock(&g_oSttRcdSendMutex);
			g_oSttRcdSendSocket.m_bRunning = FALSE;
		}
		if(bIecRecordRun)
		{			
			bIecRecordRun = FALSE;
			Sleep(120);
		}

		CSttDeviceBase::g_pSttDeviceBase->Reset_BinaryConfig();
		Sleep(20);
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nFd, 0x131, 0);
		ioctl(nFd, 0x126, 0);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

		g_nNeedReportDevExcept = 1;
		g_nNeedReportUTC = 1;
	}
	else
	{
		CSttDeviceBase::g_pSttDeviceBase->m_nIsIecMode = 2;
		if(!g_oSttRcdSendSocket.m_bRunning)
		{
			g_oSttRcdSendSocket.m_bRunning = TRUE;
			pthread_mutex_unlock(&g_oSttRcdSendMutex);
		}
		if(!bIecRecordRun)
		{
			bIecRecordRun = TRUE;
			pthread_t nthreadid;
			int nRet = pthread_create(&nthreadid, NULL, IecPkgCapThread, (LPVOID)CSttDeviceBase::g_pSttDeviceBase);
	#ifdef _PSX_QT_LINUX_
			if(nRet == 0)
			{
				qDebug() << ">>>>>>Create IecPkgCapThread";
			}
	#endif
		}

		unsigned int nCode = 0;
		//采集功能
		CSttDeviceBase::g_pSttDeviceBase->Set_BinaryGear(&m_oBinSetting);

		nCode |= 1<<31;
		nCode |= 1<<30;
		nCode |= (1000000000/m_oBinSetting.nSample/50)<<10;

		g_nNeedReportDevExcept = 0;
		g_nNeedReportUTC = 0;

		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nFd, 0x126, 1);
		ioctl(nFd, 0x131, 0x03);//数字录波
		ioctl(nFd, 0x7000407c, nCode);
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}
	return 0;
}

void CSttBinMeasure::Stop()
{
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas == 0)
	{
		return;
	}

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->m_nIsIecMode = 0;
	if(g_oSttRcdSendSocket.m_bRunning)
	{
		pthread_mutex_lock(&g_oSttRcdSendMutex);
		g_oSttRcdSendSocket.m_bRunning = FALSE;
	}
	if(bIecRecordRun)
	{
		bIecRecordRun = FALSE;
		Sleep(120);
	}

	CSttDeviceBase::g_pSttDeviceBase->Reset_BinaryConfig();
	Sleep(20);
	if(CSttDeviceBase::g_pSttDeviceBase->m_nSetAmpPowerCnt < 0xFFFFFFFF)
	{
		CSttDeviceBase::g_pSttDeviceBase->m_nSetAmpPowerCnt++;
	}
	int nFd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x103, 0);
	ioctl(nFd, 0x126, 0);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
	SetTestStarting(FALSE);

	g_nNeedReportDevExcept = 1;
	g_nNeedReportUTC = 1;
}
