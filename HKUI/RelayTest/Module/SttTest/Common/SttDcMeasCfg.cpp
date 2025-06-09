#include "stdafx.h"
#include "SttDcMeasCfg.h"
#include "tmt_common_def.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttDcMeasCfg::m_strMacroName = "直流测量设置";
CString CSttDcMeasCfg::m_strMacroID = STT_MACRO_ID_BinConfig;
CSttDcMeasCfg g_oDcMeasCfg;

CSttDcMeasCfg::CSttDcMeasCfg()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
}

CSttDcMeasCfg::~CSttDcMeasCfg(void)
{

}

void CSttDcMeasCfg::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nDCMeas == 0)
	{
		return;
	}

	pXmlSerialize->xml_serialize("主板直流电流测量档位(0-大档，1-小档)", "DCI_Gear", "", "long", g_oDcMeasCfg.m_nDCInGear_I);
	if(g_oDcMeasCfg.m_nDCInGear_I != 0)
	{
		g_oDcMeasCfg.m_nDCInGear_I = 1;
	}

#ifdef _PSX_QT_LINUX_
	int nfd = CSttDeviceBase::g_pSttDeviceBase->GetDriverFd();
	g_oDrvMutex.lock(__FILE__,__FUNCTION__,__LINE__);
	ioctl(nfd, 0x14D, g_oDcMeasCfg.m_nDCInGear_I);
	g_oDrvMutex.unlock(__FILE__,__FUNCTION__,__LINE__);
#endif
}

void CSttDcMeasCfg::StartTest()
{
	ReturnTestStateEvent_TestFinish(0,0,FALSE);
}
