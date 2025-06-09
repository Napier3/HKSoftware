#include "stdafx.h"
#include"SttAdjust_BinaryOutput.h"
#include "../../SttDevice/SttDeviceBase.h"

CString CSttAdjust_BinaryOutput::m_strMacroName = "开关量导通值输出";
CString CSttAdjust_BinaryOutput::m_strMacroID = STT_MACRO_ID_BinaryOutput;
CString CSttAdjust_BinaryOutput::m_strFilePostFix = "stthrt";
CString CSttAdjust_BinaryOutput::m_strMacroVer ="1.0";

CSttAdjust_BinaryOutput::CSttAdjust_BinaryOutput() : CSttTestBase()
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

void CSttAdjust_BinaryOutput::StartTest()
{
	int nBoutDefValue=0;
	for(int nIndex=0;nIndex<8;nIndex++)
	{
		nBoutDefValue+=(!m_nBoutTurnOnValue[nIndex])<<nIndex;
	}

#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetBinaryOutTurnOnVaule(nBoutDefValue);
	CSttDeviceBase::g_pSttDeviceBase->SetBinaryOut();//全导通,开关量闭合
#endif
	CLogPrint::LogString(XLOGLEVEL_TRACE,"CSttAdjust_BinaryOutput::DataDownload Finished");
}

void CSttAdjust_BinaryOutput::Stop()
{
#ifdef _PSX_QT_LINUX_
	CSttDeviceBase::g_pSttDeviceBase->SetBinaryOut(TRUE);//开关量全断开
#endif
}

void CSttAdjust_BinaryOutput::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
	stt_xml_serialize(this,pXmlSerialize);
}


