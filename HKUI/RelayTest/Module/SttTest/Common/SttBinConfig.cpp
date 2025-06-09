#include "stdafx.h"
#include "SttBinConfig.h"
#include "tmt_common_def.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttBinConfig::m_strMacroName = "开入设置";
CString CSttBinConfig::m_strMacroID = STT_MACRO_ID_BinConfig;

CSttBinConfig::CSttBinConfig()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
}

CSttBinConfig::~CSttBinConfig(void)
{

}

void CSttBinConfig::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	if(g_theDeviceSystemParameter->m_oDeviceAttrs.m_nBinVoltMeas == 0)
	{
		return;
	}

	Drv_BinarySetting *pBinSetting = &CSttDeviceBase::g_pSttDeviceBase->m_oBinSetting;

	CString strID;
	char pszBInName[11] = "ABCDEFGHIJ";

	for(int i = 0;i < 10;i++)
	{
		strID.Format("Bin%cType",pszBInName[i]);
		pXmlSerialize->xml_serialize("开入模式(0-电压，1-空接点)", strID.GetString(), "", "number", pBinSetting->nEType[i]);
		strID.Format("Bin%cVolt",pszBInName[i]);
		pXmlSerialize->xml_serialize("开入翻转阈值", strID.GetString(), "", "float", pBinSetting->fTripVolt[i]);
		pBinSetting->nMeasGear[i] = CSttDeviceBase::g_pSttDeviceBase->GetGear_ByValue(pBinSetting->fTripVolt[i]/0.7);
	}

#ifdef _PSX_QT_LINUX_
	/*****根据开入额定电压设置开入档位****/
	CSttDeviceBase::g_pSttDeviceBase->Set_BinaryGear(pBinSetting);
	CSttDeviceBase::g_pSttDeviceBase->Set_BinaryConfig(pBinSetting);
#endif
}

void CSttBinConfig::StartTest()
{
	ReturnTestStateEvent_TestFinish(0,0,FALSE);
}
