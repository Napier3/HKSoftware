#include "stdafx.h"
#include"SttAdjust_BinaryOutput.h"

CString CSttAdjust_BinaryOutput::m_strMacroName = "开关量导通值输出";
CString CSttAdjust_BinaryOutput::m_strMacroID = STT_MACRO_ID_BinaryOutput;
CString CSttAdjust_BinaryOutput::m_strFilePostFix = "stthrt";
CString CSttAdjust_BinaryOutput::m_strMacroVer ="1.0";

CSttAdjust_BinaryOutput::CSttAdjust_BinaryOutput()
{
	m_strName =m_strMacroName;
	m_strID = m_strMacroID;//"1";
	m_strTestID = m_strMacroID;
	m_strTestVer = m_strMacroVer;
	Init();
}

void CSttAdjust_BinaryOutput::Init()
{
	TMT_ADJ_BINARY_OUTPUT::init();
}

CSttAdjust_BinaryOutput::~CSttAdjust_BinaryOutput(void)
{

}

long CSttAdjust_BinaryOutput::OnTimer(BOOL &bFinish, long nTimerLongMs)
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
		memcpy(&m_oBIStatus, pDrvResults, nret);
		STT_TEST_EVENT obufEvent;
		int nEventIndex = 0;
		obufEvent.oTime.dTime = 0;
		obufEvent.oTime.dRealTime = 0;
		obufEvent.oTime.dBinActTime = -1;
		long nBiValue;

		for(int i = 0; i < 16; i++)
		{
			nBiValue = (m_oBIStatus.item[0].nVal1 >> i) & 0x1;
			nBiValue = (nBiValue == 0 ? 1 : 0);
			obufEvent.oEventInfo[nEventIndex].nType = SttResult_Type_Bin;
			obufEvent.oEventInfo[nEventIndex].nStateIndex = 0;
			obufEvent.oEventInfo[nEventIndex].nStateNum = 0;
			obufEvent.oEventInfo[nEventIndex].nStepIndex = 0;
			obufEvent.oEventInfo[nEventIndex].nChannel = i + 1;
			obufEvent.oEventInfo[nEventIndex].nValue = nBiValue;
			nEventIndex++;
		}

		obufEvent.nEventInfoCnt = nEventIndex;
		stt_add_test_event(obufEvent);
	}

#endif

	return 0;
}

void CSttAdjust_BinaryOutput::StartTest()
{
    int nBoutDefValue = 0;

    for(int nIndex = 0; nIndex < 16; nIndex++)
	{
        nBoutDefValue += (!m_nBoutTurnOnValue[nIndex]) << nIndex;
	}

	int nBoutValue = 0xFFFFFFFF;

	for(int nIndex = 0; nIndex < 16; nIndex++)
	{
		nBoutValue &= ~(m_nBoutValue[nIndex] << nIndex);
	}

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetBinaryOutTurnOnVaule(nBoutDefValue);
	int fd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(fd, 0x107, nBoutValue);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
	SetTestStarting(TRUE);
	CLogPrint::LogString(XLOGLEVEL_DEBUG,"CSttAdjust_BinaryOutput::StartTest >>>>>>");
}

void CSttAdjust_BinaryOutput::Stop()
{
	SetTestStarting(FALSE);
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->Reset_BinaryConfig();
	CSttDeviceBase::g_pSttDeviceBase->SetBinaryOut(TRUE);//开关量全断开
#endif
}

void CSttAdjust_BinaryOutput::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);
	m_oBinSetting.nWorkMode = 0;

	long nBinType = 1;
	pXmlSerialize->xml_serialize("开入模式", "BinType", "", "number", nBinType);
	for(int i = 0;i < 10;i++)
	{
		m_oBinSetting.nEType[i] = nBinType;
		for(int j = 0;j < ADJUST_MAX_GEAR_COUNT;j++)
		{
			m_oBinSetting.fCoef[i][j] = CSttDeviceBase::g_pSttDeviceBase->m_oBinSetting.fCoef[i][j];
			m_oBinSetting.fZero[i][j] = CSttDeviceBase::g_pSttDeviceBase->m_oBinSetting.fZero[i][j];
		}
	}

	CString strID;
	float fNom;
	for(int i = 0;i < 10;i++)
	{
		strID.Format("BinMargin%d",i+1);
		pXmlSerialize->xml_serialize("开入翻转阈值", strID.GetString(), "", "number", m_oBinSetting.fTripVolt[i]);		

		strID.Format("BinNom%d",i+1);
		pXmlSerialize->xml_serialize("开入额定电压", strID.GetString(), "", "number", fNom);
		m_oBinSetting.nMeasGear[i] = CSttDeviceBase::g_pSttDeviceBase->GetGear_ByValue(fNom);
	}

	/*****根据开入额定电压设置开入档位****/
	CSttDeviceBase::g_pSttDeviceBase->Set_BinaryGear(&m_oBinSetting);

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->Set_BinaryConfig(&m_oBinSetting);
#endif
}


