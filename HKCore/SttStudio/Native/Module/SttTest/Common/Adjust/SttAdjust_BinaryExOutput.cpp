#include "stdafx.h"
#include"SttAdjust_BinaryExOutput.h"

CString CSttAdjust_BinaryExOutput::m_strMacroName = "开关量插件输出";
CString CSttAdjust_BinaryExOutput::m_strMacroID = STT_MACRO_ID_BinaryExOutput;
CString CSttAdjust_BinaryExOutput::m_strFilePostFix = "stthrt";
CString CSttAdjust_BinaryExOutput::m_strMacroVer = "1.0";

CSttAdjust_BinaryExOutput::CSttAdjust_BinaryExOutput()
{
	m_strName = m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttAdjust_BinaryExOutput::Init()
{
	TMT_ADJ_BINARYEX_OUTPUT::init();
}

CSttAdjust_BinaryExOutput::~CSttAdjust_BinaryExOutput(void)
{
}

long CSttAdjust_BinaryExOutput::OnTimer(BOOL &bFinish, long nTimerLongMs)
{
	if(!GetTestStarting())
	{
		return 0;
	}

	int nFd = CSttDeviceBase::g_pSttDeviceBase->m_nCommfd;
#ifdef _PSX_QT_LINUX_
	char *pDrvResults = stt_test_get_drvresult_buff();
	int nret = 0;
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	nret = read(nFd, pDrvResults, 0x202);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(nret == sizeof(Drv_BIStatus))
	{
		if(nModuleDrvIdx > 0)
		{
			memcpy(&m_oBIStatus, pDrvResults, nret);
			STT_TEST_EVENT obufEvent;
			int nEventIndex = 0;
			obufEvent.oTime.dTime = 0;
			obufEvent.oTime.dRealTime = 0;
			obufEvent.oTime.dBinActTime = -1;
			long nBiValue;

			for(int i = 0; i < 32; i++)
			{
				nBiValue = (m_oBIStatus.item[nModuleDrvIdx].nVal1 >> i) & 0x1;
				nBiValue = (nBiValue == 0 ? 1 : 0);
				obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
				obufEvent.oEventInfo[nEventIndex].nStateIndex = 0;
				obufEvent.oEventInfo[nEventIndex].nStateNum = 0;
				obufEvent.oEventInfo[nEventIndex].nStepIndex = 0;
				obufEvent.oEventInfo[nEventIndex].nChannel = i + 1;
				obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
				nEventIndex++;
			}

			for(int i = 0; i < 32; i++)
			{
				nBiValue = (m_oBIStatus.item[nModuleDrvIdx].nVal2 >> i) & 0x1;
				nBiValue = (nBiValue == 0 ? 1 : 0);
				obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
				obufEvent.oEventInfo[nEventIndex].nStateIndex = 0;
				obufEvent.oEventInfo[nEventIndex].nStateNum = 0;
				obufEvent.oEventInfo[nEventIndex].nStepIndex = 0;
				obufEvent.oEventInfo[nEventIndex].nChannel = i + 32 + 1;
				obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
				nEventIndex++;
			}

			obufEvent.nEventInfoCnt = nEventIndex;
			stt_add_test_event(obufEvent);
		}
	}

#endif
	return 0;
}

void CSttAdjust_BinaryExOutput::StartTest()
{
#ifdef _PSX_QT_LINUX_
	int nFd = CSttDeviceBase::g_pSttDeviceBase->m_nCommfd;
	Drv_ComData oComData;
	oComData.nModule = ModuleIndexTransToDrv(m_nModuleIndex + 1) << 16;
	oComData.dat[0] = 0x05640564;
	oComData.dat[1] = 5;
	oComData.dat[2] = 0x3001;
	oComData.dat[4] = 0;
	oComData.dat[5] = 0;
	oComData.dat[6] = 0;
	unsigned int nVal = 0;

	for(int i = 0 ; i < 32; i++)
	{
		if(m_nBoutExValue[i] == 0)
		{
			nVal |= 1 << i;
		}
	}

	oComData.dat[3] = nVal;
	nVal = 0;

	for(int i = 0 ; i < 32; i++)
	{
		if(m_nBoutExValue[i + 32] == 0)
		{
			nVal |= 1 << i;
		}
	}

	oComData.dat[4] = nVal;
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x322, 0);
	write(nFd, (char *)&oComData, sizeof(Drv_ComData));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	if(!GetTestStarting())
	{
		oComData.dat[1] = 2;
		oComData.dat[2] = 0x10;
		oComData.dat[3] = 0x8;
		
		g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
		ioctl(nFd, 0x322, 0);
		write(nFd, (char *)&oComData, sizeof(Drv_ComData));
		g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
	}

#endif
	SetTestStarting(TRUE);
	CLogPrint::LogString(XLOGLEVEL_DEBUG, "CSttAdjust_BinaryExOutput::StartTest >>>>>>");
}

void CSttAdjust_BinaryExOutput::Stop()
{
#ifdef _PSX_QT_LINUX_
	//开关量全断开
	SetTestStarting(FALSE);
	int nFd = CSttDeviceBase::g_pSttDeviceBase->m_nCommfd;
	Drv_ComData oComData;
	oComData.nModule = ModuleIndexTransToDrv(m_nModuleIndex + 1) << 16;
	oComData.dat[0] = 0x05640564;
	oComData.dat[1] = 5;
	oComData.dat[2] = 0x3001;
	oComData.dat[3] = 0xFFFFFFFF;
	oComData.dat[4] = 0xFFFFFFFF;
	oComData.dat[5] = 0;
	oComData.dat[6] = 0;
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x322, 0);
	write(nFd, (char *)&oComData, sizeof(Drv_ComData));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);

	oComData.dat[1] = 2;
	oComData.dat[2] = 0x10;
	oComData.dat[3] = 0;
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nFd, 0x322, 0);
	write(nFd, (char *)&oComData, sizeof(Drv_ComData));
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
}

void CSttAdjust_BinaryExOutput::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	pXmlSerialize->xml_serialize("模块位置(0-11)", "ModuleIndex", "", "ModuleIndex", m_nModuleIndex);
	CString strID;

	for(int i = 0; i < 64; i++)
	{
		strID.Format(_T("BoutEx%d"), i + 1);
		pXmlSerialize->xml_serialize("", strID.GetString(), "", "long", m_nBoutExValue[i]);
	}

	SwitchModules oSwitchModules = CSttDeviceBase::g_pSttDeviceBase->m_oSwitchModules;
	nModuleDrvIdx = -1;

	//BIOEx
	for(int nIndex = 0; nIndex < oSwitchModules.m_nModulesCount; nIndex++)
	{
		long nModuleIndex = oSwitchModules.oSWITCHINFO[nIndex].m_nModulePos - 1;

		if(nModuleIndex == m_nModuleIndex)
		{
			nModuleDrvIdx = nIndex;
			break;
		}
	}

	if(nModuleDrvIdx > -1)
	{
		nModuleDrvIdx += 1;//0是主板开入
	}
}


