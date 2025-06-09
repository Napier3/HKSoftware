#include "stdafx.h"
#include "SttUartConfig.h"
#include "tmt_common_def.h"
#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

CString CSttUartConfig::m_strMacroName = "串口参数设置";
CString CSttUartConfig::m_strMacroID = STT_MACRO_ID_UartConfig;

CSttUartConfig::CSttUartConfig()
{
    m_strName =m_strMacroName;
    m_strID = m_strMacroID;//"1";
}

CSttUartConfig::~CSttUartConfig(void)
{

}

void CSttUartConfig::Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize)
{
#ifdef _PSX_QT_LINUX_
	if(g_pFpgaUart != NULL)
	{
		UartSettings oUartSettings;
		memcpy(&oUartSettings,&g_pFpgaUart->m_oUartSettings,sizeof(UartSettings));
		CString strID;
		for(int i = 0;i < oUartSettings.nUartCnt && i < UartTotal;i++)
		{
			strID.Format("UART%d",i+1);
			CSttXmlSerializeBase *pUartXmlSerialize =pXmlSerialize->xml_serialize("", strID.GetString(), "UART", stt_ParaGroupKey());
			if(pUartXmlSerialize == NULL)
			{
				continue;
			}

			UartSetting *pUartSetting = &oUartSettings.oUartSetting[i];
			pUartXmlSerialize->xml_serialize("波特率","BandRate","","long",pUartSetting->nBand);
			pUartXmlSerialize->xml_serialize("数据位(5,6,7,8)","DataLen","","long",pUartSetting->nDatalen);
			pUartXmlSerialize->xml_serialize("校验位(0-None,1-Odd,2-Even,3-Mark)","Check","","long",pUartSetting->nCheck);
			pUartXmlSerialize->xml_serialize("停止位(0-'1',1-'1.5',2-'2')","StopBit","","long",pUartSetting->nStopBit);
			pUartXmlSerialize->xml_serialize("端口电平(0-'RS485',1-'RS232')","Output","","long",pUartSetting->nOutput);
		}

		g_pFpgaUart->InitUart(&oUartSettings);
	}
#endif
}

void CSttUartConfig::StartTest()
{
	ReturnTestStateEvent_TestFinish(0, 0, FALSE);
}
